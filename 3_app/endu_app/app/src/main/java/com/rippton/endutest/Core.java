package com.rippton.endutest;

import android.app.PendingIntent;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbManager;
import android.net.Uri;
import android.os.Build;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.provider.MediaStore;
import android.widget.Toast;

import com.hoho.android.usbserial.driver.UsbSerialDriver;
import com.hoho.android.usbserial.driver.UsbSerialPort;
import com.hoho.android.usbserial.driver.UsbSerialProber;

import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.file.Files;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

/**
 * Link + logging core. Owned by the foreground LinkService so the MAVLink link, the realtime
 * keep-alive and CSV logging keep running when the App is in the background or the phone dozes.
 * The Activity is only a view onto this object.
 */
public final class Core {
    public interface ParamListener { void onParam(String name, float value); }
    static final String ACTION_USB = "com.rippton.endutest.USB_PERMISSION";
    static final String[] PARAMS = {"ET_FWD_S", "ET_STOP_S", "ET_REV_S", "ET_THR", "ET_REV_THR",
            "ET_BRST_INT", "ET_BRST_ON", "ET_BRST_OFF", "ET_BRST_N", "ET_DAY_S", "ET_REST_S",
            "ET_RAMP", "ET_MOT", "ET_RT_TMO", "ET_IMAX", "ET_VMIN", "ET_TOTAL_H", "ET_PWM_MAX", "ET_PWM_START"};
    final Map<String, Float> params = new LinkedHashMap<>();   // last values read back from the boat
    volatile String linkName = "未连接";

    private static Core instance;
    public static synchronized Core get(Context c) { if (instance == null) instance = new Core(c.getApplicationContext()); return instance; }

    final Context ctx;
    final Mav mav = new Mav();
    final Handler ui = new Handler(Looper.getMainLooper());
    final Map<String, Float> nv = new LinkedHashMap<>();
    volatile ParamListener paramListener;
    volatile OutputStream usbOut; volatile UsbSerialPort usbPort;
    volatile DatagramSocket udp; volatile SocketAddress udpPeer;
    volatile java.net.Socket tcp; volatile OutputStream tcpOut;
    volatile boolean relayed;   // true = through the remote controller (boat SERIAL1 shared with the IO board): never change stream rates
    volatile boolean running;
    volatile int tsys = 1, tcomp = 1;
    volatile long lastRx;
    volatile float volt = -1, curr = -1; volatile int pwmL, pwmR, mode = -1; volatile boolean armed;
    volatile String lastText = "";
    volatile boolean rtOn; volatile float rtL, rtR;
    FileWriter csv; File csvFile;

    private Core(Context c) { ctx = c; }

    synchronized void start() {
        if (running) return;
        running = true;
        openCsv();
        new Thread(this::txLoop, "tx").start();
    }
    synchronized void shutdown() { running = false; disconnect(); try { if (csv != null) csv.close(); } catch (IOException ignored) {} csv = null; }
    boolean linkUp() { return System.currentTimeMillis() - lastRx < 3000; }
    void toast(String s) { ui.post(() -> Toast.makeText(ctx, s, Toast.LENGTH_SHORT).show()); }

    // ---------------- links ----------------
    void connectUsb() {
        mav.wire = Mav.WIRE_V2; relayed = false;
        UsbManager um = (UsbManager) ctx.getSystemService(Context.USB_SERVICE);
        List<UsbSerialDriver> drivers = UsbSerialProber.getDefaultProber().findAllDrivers(um);
        if (drivers.isEmpty()) { toast("没找到USB串口设备（CP2102）"); return; }
        UsbSerialDriver d = drivers.get(0);
        UsbDevice dev = d.getDevice();
        if (!um.hasPermission(dev)) {
            int fl = Build.VERSION.SDK_INT >= 31 ? PendingIntent.FLAG_MUTABLE : 0;
            Intent it = new Intent(ACTION_USB).setPackage(ctx.getPackageName());
            um.requestPermission(dev, PendingIntent.getBroadcast(ctx, 0, it, fl)); return;
        }
        UsbDeviceConnection conn = um.openDevice(dev);
        if (conn == null) { toast("USB打开失败"); return; }
        try {
            UsbSerialPort port = d.getPorts().get(0);
            port.open(conn);
            port.setParameters(921600, 8, UsbSerialPort.STOPBITS_1, UsbSerialPort.PARITY_NONE);
            // ESP32 auto-reset circuit (DTR/RTS -> EN/IO0): keep both released so the board is not reset
            port.setDTR(false); port.setRTS(false);
            usbPort = port;
            usbOut = new OutputStream() { public void write(int x) throws IOException { write(new byte[]{(byte) x}); }
                public void write(byte[] bb) throws IOException { UsbSerialPort pp = usbPort; if (pp != null) pp.write(bb, 200); } };
            new Thread(this::usbRxLoop, "usbrx").start();
            linkName = "USB 921600"; toast("USB已连接 921600");
            afterConnect();
        } catch (IOException e) { toast("USB错误: " + e.getMessage()); }
    }
    void usbRxLoop() {
        byte[] b = new byte[4096];
        while (running && usbPort != null) {
            try { int n = usbPort.read(b, 200); for (int i = 0; i < n; i++) handle(mav.parse(b[i])); }
            catch (IOException e) { usbPort = null; usbOut = null; toast("USB断开"); }
        }
    }
    void connectUdp() {
        new Thread(() -> {
            try {
                DatagramSocket s = new DatagramSocket(null); s.setReuseAddress(true); s.bind(new InetSocketAddress(14550)); s.setSoTimeout(500);
                udp = s; linkName = "Wi-Fi UDP 14550"; toast("Wi-Fi：监听 UDP 14550（船 AP 192.168.4.1）");
                if (udpPeer == null) udpPeer = new InetSocketAddress("192.168.4.1", 14550);
                byte[] b = new byte[2048];
                afterConnect();
                while (running && udp == s) {
                    DatagramPacket pk = new DatagramPacket(b, b.length);
                    try { s.receive(pk); } catch (java.net.SocketTimeoutException te) { continue; }
                    udpPeer = pk.getSocketAddress();
                    for (int i = 0; i < pk.getLength(); i++) handle(mav.parse(b[i]));
                }
            } catch (IOException e) { toast("UDP错误: " + e.getMessage()); }
        }, "udp").start();
    }
    /** Phone -> remote ESP8684 Wi-Fi -> remote MCU -> 5.8G -> boat SERIAL1. Framing: MAVLink v1, STX 0xC3, CRC 0xFF1E, sysid 200. */
    void connectRemote(String host, int port, boolean useTcp) {
        disconnect();
        mav.wire = Mav.WIRE_V1_SELFMOD; relayed = true;
        new Thread(() -> {
            try {
                if (useTcp) {
                    java.net.Socket so = new java.net.Socket(); so.connect(new InetSocketAddress(host, port), 4000); so.setSoTimeout(500); so.setTcpNoDelay(true);
                    tcp = so; tcpOut = so.getOutputStream(); linkName = "遥控器 TCP " + host + ":" + port; toast("已连接遥控器 " + host + ":" + port + " (TCP)");
                    afterConnect();
                    java.io.InputStream in = so.getInputStream(); byte[] b = new byte[2048];
                    while (running && tcp == so) {
                        int n; try { n = in.read(b); } catch (java.net.SocketTimeoutException te) { continue; }
                        if (n < 0) { toast("遥控器连接断开"); break; }
                        for (int i = 0; i < n; i++) handle(mav.parse(b[i]));
                    }
                } else {
                    DatagramSocket s = new DatagramSocket(null); s.setReuseAddress(true); s.bind(new InetSocketAddress(port)); s.setSoTimeout(500);
                    udpPeer = new InetSocketAddress(host, port); udp = s;
                    linkName = "遥控器 UDP " + host + ":" + port; toast("遥控器：UDP " + host + ":" + port);
                    afterConnect();
                    byte[] b = new byte[2048];
                    while (running && udp == s) {
                        DatagramPacket pk = new DatagramPacket(b, b.length);
                        try { s.receive(pk); } catch (java.net.SocketTimeoutException te) { continue; }
                        for (int i = 0; i < pk.getLength(); i++) handle(mav.parse(b[i]));
                    }
                }
            } catch (IOException e) { toast("遥控器连接失败: " + e.getMessage()); }
        }, "remote").start();
    }
    void disconnect() {
        rtOn = false;
        try { if (usbPort != null) usbPort.close(); } catch (IOException ignored) {}
        usbPort = null; usbOut = null;
        if (udp != null) udp.close(); udp = null; udpPeer = null; linkName = "未连接";
        try { if (tcp != null) tcp.close(); } catch (IOException ignored) {} tcp = null; tcpOut = null;
    }
    void afterConnect() { new Thread(() -> { sleep(300); if (!relayed) send(mav.requestStreams(tsys, tcomp, 4)); for (String p : PARAMS) { send(mav.paramRead(tsys, tcomp, p)); sleep(30); } }).start(); }
    synchronized void send(byte[] f) {
        try {
            OutputStream o = usbOut; if (o != null) o.write(f);
            OutputStream t = tcpOut; if (t != null) t.write(f);
            DatagramSocket s = udp; SocketAddress a = udpPeer; if (s != null && a != null) s.send(new DatagramPacket(f, f.length, a));
        } catch (IOException e) { /* link gone; boat-side watchdog stops motors in realtime mode */ }
    }
    static void sleep(long ms) { try { Thread.sleep(ms); } catch (InterruptedException ignored) {} }

    void txLoop() {
        long hb = 0, st = 0;
        while (running) {
            long now = System.currentTimeMillis();
            if (now - hb >= 1000) { hb = now; send(mav.heartbeat()); }
            // never on the relayed link: SR1 rates also drive SERVO_OUTPUT_RAW to the IO board / ESCs
            if (!relayed && now - st >= 10000) { st = now; send(mav.requestStreams(tsys, tcomp, 4)); }
            if (rtOn) send(mav.commandLong(tsys, tcomp, Mav.CMD_USER_2, rtL, rtR, 0));
            sleep(200);
        }
    }

    void writeParams(Map<String, String> vals) {
        new Thread(() -> {
            for (Map.Entry<String, String> e : vals.entrySet()) {
                String s = e.getValue().trim();
                if (s.isEmpty()) continue;
                try { send(mav.paramSet(tsys, tcomp, e.getKey(), Float.parseFloat(s))); sleep(40); } catch (NumberFormatException ignored) {}
            }
            toast("参数已发送（看回读值确认）");
        }).start();
    }

    // ---------------- receive ----------------
    void handle(Mav.Msg m) {
        if (m == null) return;
        if (m.sysid == 255) return;
        lastRx = System.currentTimeMillis();
        switch (m.id) {
            case Mav.HEARTBEAT:
                if ((m.p.get(4) & 0xff) == 6) return;  // other GCS
                if ((m.p.get(5) & 0xff) == 8 || m.sysid == 0xA5 || m.sysid == 0xAF || m.sysid >= 250) return;  // not an autopilot (remote 0xA5, sonar DTU 0xAF, GCS/remote 255)
                tsys = m.sysid; tcomp = m.compid; mode = m.p.getInt(0); armed = (m.p.get(6) & 0x80) != 0; break;
            case Mav.SYS_STATUS:
                volt = (m.p.getShort(14) & 0xffff) / 1000f; curr = m.p.getShort(16) / 100f; break;
            case Mav.SERVO_OUTPUT_RAW:
                pwmL = m.p.getShort(4) & 0xffff; pwmR = m.p.getShort(6) & 0xffff; break;
            case Mav.NAMED_VALUE_FLOAT: {
                String n = m.str(8, 10); float v = m.p.getFloat(4);
                synchronized (nv) { nv.put(n, v); }
                if (n.equals("ET_OUTR")) logRow();
                break;
            }
            case Mav.PARAM_VALUE: {
                String n = m.str(8, 16); float v = m.p.getFloat(0);
                synchronized (params) { params.put(n, v); }
                ParamListener pl = paramListener;
                if (pl != null) ui.post(() -> pl.onParam(n, v));
                break;
            }
            case Mav.STATUSTEXT: {
                lastText = m.str(1, 50);
                logEvent("TEXT", lastText);
                break;
            }
            case Mav.COMMAND_ACK: {
                int cmd = m.p.getShort(0) & 0xffff, res = m.p.get(2) & 0xff;
                if (cmd != Mav.CMD_USER_2 || res != 0) logEvent("ACK", cmd + "=" + res);
                if (cmd != Mav.CMD_USER_2 && res != 0) toast("命令 " + cmd + " 被拒绝: " + res);
                break;
            }
        }
    }
    float g(String k) { synchronized (nv) { Float f = nv.get(k); return f == null ? -1 : f; } }

    // ---------------- CSV log ----------------
    synchronized void openCsv() {
        try {
            if (csv != null) csv.close();
            File dir = ctx.getExternalFilesDir(null);
            csvFile = new File(dir, "endu_" + new SimpleDateFormat("yyyyMMdd_HHmmss", Locale.US).format(new Date()) + ".csv");
            csv = new FileWriter(csvFile, true);
            csv.write("time,type,state,phase,remain_s,cycles,bursts,cum_h,out_l_pct,out_r_pct,pwm_l,pwm_r,volt_v,curr_a,mode,armed,text\n");
            csv.flush();
        } catch (IOException e) { toast("日志文件失败: " + e.getMessage()); }
    }
    String now() { return new SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.US).format(new Date()); }
    synchronized void logRow() {
        if (csv == null) return;
        try {
            csv.write(String.format(Locale.US, "%s,DATA,%d,%d,%.1f,%d,%d,%.4f,%.1f,%.1f,%d,%d,%.3f,%.2f,%d,%d,\n", now(),
                    (int) g("ET_ST"), (int) g("ET_PH"), g("ET_REM"), (int) g("ET_CYC"), (int) g("ET_BRST"), g("ET_CUMH"),
                    g("ET_OUTL"), g("ET_OUTR"), pwmL, pwmR, volt, curr, mode, armed ? 1 : 0));
            csv.flush();
        } catch (IOException ignored) {}
    }
    synchronized void logEvent(String type, String text) {
        if (csv == null) return;
        try { csv.write(now() + "," + type + ",,,,,,,,,,,,,,,\"" + text.replace("\"", "'") + "\"\n"); csv.flush(); } catch (IOException ignored) {}
    }
    void exportCsv() {
        File dir = ctx.getExternalFilesDir(null);
        File[] files = dir == null ? null : dir.listFiles((d, n) -> n.endsWith(".csv"));
        if (files == null || files.length == 0) { toast("没有日志"); return; }
        int ok = 0;
        for (File f : files) {
            try {
                if (Build.VERSION.SDK_INT >= 29) {
                    ContentValues cv = new ContentValues();
                    cv.put(MediaStore.Downloads.DISPLAY_NAME, f.getName());
                    cv.put(MediaStore.Downloads.MIME_TYPE, "text/csv");
                    cv.put(MediaStore.Downloads.RELATIVE_PATH, Environment.DIRECTORY_DOWNLOADS + "/RogueEndurance");
                    Uri u = ctx.getContentResolver().insert(MediaStore.Downloads.EXTERNAL_CONTENT_URI, cv);
                    if (u == null) continue;
                    try (OutputStream o = ctx.getContentResolver().openOutputStream(u)) { o.write(Files.readAllBytes(f.toPath())); }
                    if (f.equals(csvFile)) {
                        Intent share = new Intent(Intent.ACTION_SEND).setType("text/csv").putExtra(Intent.EXTRA_STREAM, u).addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
                        ctx.startActivity(Intent.createChooser(share, "分享当前日志").addFlags(Intent.FLAG_ACTIVITY_NEW_TASK));
                    }
                } else {
                    File out = new File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS), "RogueEndurance");
                    out.mkdirs();
                    try (InputStream in = new java.io.FileInputStream(f); OutputStream o = new FileOutputStream(new File(out, f.getName()))) {
                        byte[] b = new byte[8192]; int n; while ((n = in.read(b)) > 0) o.write(b, 0, n);
                    }
                }
                ok++;
            } catch (Exception e) { toast("导出失败: " + e.getMessage()); }
        }
        toast("已导出 " + ok + " 个文件到 下载/RogueEndurance");
    }

    float param(String n, float def) { synchronized (params) { Float f = params.get(n); return f == null ? def : f; } }
    /** realtime command in percent of the capped range: +forward, -reverse; firmware clamps to ET_PWM_MAX again. */
    void setRealtime(float pct) { rtL = rtR = Math.round(Math.max(-100f, Math.min(100f, pct)) * 10) / 10f; }
    void estop() { rtOn = false; rtL = rtR = 0; send(mav.commandLong(tsys, tcomp, Mav.CMD_USER_1, 0)); }
}
