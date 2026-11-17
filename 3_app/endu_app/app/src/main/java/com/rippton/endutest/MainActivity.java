package com.rippton.endutest;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.graphics.Typeface;
import android.graphics.drawable.GradientDrawable;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.text.InputType;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.SeekBar;
import android.widget.TextView;

import java.io.File;
import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.Locale;
import java.util.Map;

/**
 * Rogue Max motor endurance TEST App v0.2 (untested on hardware).
 * Tabs: 连接 / 参数 / 监控 / 日志. v0.3b default link: via the remote controller Wi-Fi (MAVLink v1 0xC3/0xFF1E, sysid 200). USB-OTG is the fallback.
 * Throttle: two stepless bars (0-100.0 % of the CAPPED range; 100% = ET_PWM_MAX ≈ 6000 rpm), forward and reverse (default 80%).
 */
public class MainActivity extends Activity {
    static final String[] STATES = {"空闲", "自动运行", "已暂停", "实时控制", "实时-断链已停", "测试完成", "故障停机"};
    static final String[] PHASES = {"-", "正转", "停1", "反转", "停2", "点动开", "点动停", "每日休息"};
    static final String[] TABS = {"连接", "参数", "监控", "日志"};
    static final String[][] PARAM_LABELS = {
            {"ET_FWD_S", "正转时长 s"}, {"ET_STOP_S", "停机时长 s"}, {"ET_REV_S", "反转时长 s"},
            {"ET_BRST_INT", "点动间隔(累计运行) s"}, {"ET_BRST_ON", "点动开 s"}, {"ET_BRST_OFF", "点动停 s"}, {"ET_BRST_N", "点动次数"},
            {"ET_DAY_S", "每日工作 s"}, {"ET_REST_S", "每日休息 s"}, {"ET_RAMP", "斜坡 %/s"}, {"ET_MOT", "电机(1左2右3双)"},
            {"ET_RT_TMO", "实时断链停机 ms"}, {"ET_IMAX", "过流停机 A"}, {"ET_VMIN", "欠压停机 V"}, {"ET_TOTAL_H", "总时长 h(0不限)"},
            {"ET_PWM_MAX", "PWM上限(6000rpm)"}, {"ET_PWM_START", "PWM起转点"}};

    final Handler ui = new Handler(Looper.getMainLooper());
    final Map<String, EditText> paramEdits = new LinkedHashMap<>();
    final LinearLayout[] pages = new LinearLayout[4];
    final Button[] tabBtns = new Button[4];
    Core c;
    TextView connStatus, monBig, monDetail, rtState, logInfo, fwdLabel, revLabel, banner;
    SeekBar fwdBar, revBar;
    int rtDir = 0;          // realtime: 0 stop, +1 forward, -1 reverse
    float fwdPct = 0, revPct = 80;
    View rootView;
    boolean demo;           // screenshot/demo mode: fills the screen with sample data, no link

    @Override protected void onCreate(Bundle b) {
        super.onCreate(b);
        c = Core.get(this);
        demo = getIntent() != null && getIntent().getBooleanExtra("demo", false);
        if (getIntent() != null && getIntent().getBooleanExtra("crashtest", false)) new Handler(Looper.getMainLooper()).postDelayed(() -> { throw new RuntimeException("crash handler self-test (adb --ez crashtest true)"); }, 1500);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);   // screen stays on during a test
        // v0.3: the foreground service is NOT started here any more; it starts on 连接 / 开始 (ensureService()).
        if (!demo) c.start();

        LinearLayout root = new LinearLayout(this); root.setOrientation(LinearLayout.VERTICAL); root.setBackgroundColor(Color.rgb(245, 247, 250));
        banner = new TextView(this); banner.setText("Rogue Max 电机耐久测试  ·  测试固件专用"); banner.setTextColor(Color.WHITE);
        banner.setBackgroundColor(Color.rgb(0, 82, 155)); banner.setPadding(32, 28, 32, 28); banner.setTextSize(17); banner.setTypeface(null, Typeface.BOLD);
        root.addView(banner);
        LinearLayout tabs = new LinearLayout(this); tabs.setOrientation(LinearLayout.HORIZONTAL); root.addView(tabs);
        for (int i = 0; i < 4; i++) {
            final int k = i; Button t = new Button(this); t.setText(TABS[i]); t.setAllCaps(false);
            t.setOnClickListener(v -> showTab(k)); tabs.addView(t, new LinearLayout.LayoutParams(0, -2, 1)); tabBtns[i] = t;
        }
        ScrollView sv = new ScrollView(this); LinearLayout body = new LinearLayout(this); body.setOrientation(LinearLayout.VERTICAL); body.setPadding(28, 16, 28, 16);
        sv.addView(body); root.addView(sv, new LinearLayout.LayoutParams(-1, 0, 1));
        for (int i = 0; i < 4; i++) { pages[i] = new LinearLayout(this); pages[i].setOrientation(LinearLayout.VERTICAL); body.addView(pages[i]); }
        Button stop = new Button(this); stop.setText("急停 + 上锁"); stop.setTextSize(18); stop.setTextColor(Color.WHITE); stop.setBackgroundColor(Color.rgb(211, 47, 47));
        stop.setOnClickListener(v -> { rtDir = 0; c.estop(); updateRt(); }); root.addView(stop, new LinearLayout.LayoutParams(-1, 150));
        setContentView(root); rootView = root;

        buildConnect(pages[0]); buildParams(pages[1]); buildMonitor(pages[2]); buildLog(pages[3]);
        c.paramListener = (n, v) -> {
            EditText e = paramEdits.get(n);
            if (e != null) e.setText(v == Math.rint(v) ? String.valueOf((long) v) : String.valueOf(v));
            if (n.equals("ET_THR")) setBar(fwdBar, v);
            if (n.equals("ET_REV_THR")) setBar(revBar, v);
            refreshBarLabels();
        };
        registerReceiver(usbReceiver, new IntentFilter(Core.ACTION_USB), Build.VERSION.SDK_INT >= 33 ? Context.RECEIVER_NOT_EXPORTED : 0);
        if (demo) loadDemo();
        else ui.postDelayed(() -> { showLastCrash(); askNotificationPermission(); }, 600);
        if (!demo && getIntent() != null && getIntent().getBooleanExtra("fgstest", false)) ui.postDelayed(this::ensureService, 3000);   // adb test hook
        int tab = getIntent() == null ? 0 : getIntent().getIntExtra("tab", 0);
        showTab(tab);
        ui.postDelayed(uiTick, 300);
        if (demo && getIntent().getBooleanExtra("snap", false)) ui.postDelayed(() -> snap(0), 4000);
    }

    // ---------------- helpers ----------------
    LinearLayout card(LinearLayout p, String title) {
        LinearLayout cd = new LinearLayout(this); cd.setOrientation(LinearLayout.VERTICAL); cd.setPadding(28, 20, 28, 24);
        GradientDrawable bg = new GradientDrawable(); bg.setColor(Color.WHITE); bg.setCornerRadius(24); bg.setStroke(2, Color.rgb(220, 225, 232)); cd.setBackground(bg);
        LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(-1, -2); lp.setMargins(0, 12, 0, 12); p.addView(cd, lp);
        TextView t = new TextView(this); t.setText(title); t.setTextSize(16); t.setTypeface(null, Typeface.BOLD); t.setTextColor(Color.rgb(0, 82, 155)); cd.addView(t);
        return cd;
    }
    LinearLayout row(LinearLayout p) { LinearLayout r = new LinearLayout(this); r.setOrientation(LinearLayout.HORIZONTAL); r.setGravity(Gravity.CENTER_VERTICAL); p.addView(r); return r; }
    Button btn(LinearLayout p, String t, View.OnClickListener l) { Button b = new Button(this); b.setText(t); b.setAllCaps(false); b.setOnClickListener(l); p.addView(b, new LinearLayout.LayoutParams(0, -2, 1)); return b; }
    TextView text(LinearLayout p, String s, float size) { TextView v = new TextView(this); v.setText(s); v.setTextSize(size); v.setTextColor(Color.rgb(33, 33, 33)); p.addView(v); return v; }
    void showTab(int k) {
        for (int i = 0; i < 4; i++) { pages[i].setVisibility(i == k ? View.VISIBLE : View.GONE); tabBtns[i].setTextColor(i == k ? Color.rgb(0, 82, 155) : Color.GRAY); tabBtns[i].setTypeface(null, i == k ? Typeface.BOLD : Typeface.NORMAL); }
    }

    // ---------------- 连接 ----------------
    void buildConnect(LinearLayout p) {
        LinearLayout w = card(p, "① 遥控器 Wi-Fi 中继（默认）");
        text(w, "链路：手机 → 遥控器 Wi-Fi(ESP8684) → 遥控器 → 5.8G → 船 SERIAL1。帧格式自动用船端加密 MAVLink v1（0xC3 / CRC 0xFF1E），App sysid 200。\n地址和端口请按原厂 App 连遥控器时用的填（遥控器源码里没有，待确认）。", 13);
        android.content.SharedPreferences sp = getSharedPreferences("endu", 0);
        LinearLayout hr = row(w);
        final EditText host = new EditText(this); host.setText(sp.getString("rhost", "192.168.4.1")); host.setTextSize(14); hr.addView(host, new LinearLayout.LayoutParams(0, -2, 2));
        final EditText port = new EditText(this); port.setText(String.valueOf(sp.getInt("rport", 14550))); port.setInputType(InputType.TYPE_CLASS_NUMBER); port.setTextSize(14); hr.addView(port, new LinearLayout.LayoutParams(0, -2, 1));
        final android.widget.CheckBox tcpBox = new android.widget.CheckBox(this); tcpBox.setText("TCP"); tcpBox.setChecked(sp.getBoolean("rtcp", false)); hr.addView(tcpBox);
        btn(row(w), "连接遥控器", v -> {
            int pt; try { pt = Integer.parseInt(port.getText().toString().trim()); } catch (Exception e) { pt = 14550; }
            sp.edit().putString("rhost", host.getText().toString().trim()).putInt("rport", pt).putBoolean("rtcp", tcpBox.isChecked()).apply();
            ensureService(); c.connectRemote(host.getText().toString().trim(), pt, tcpBox.isChecked());
        });
        LinearLayout u = card(p, "② USB-OTG 有线（备用）");
        text(u, "OTG 线插船端 USB 口（CP2102，921600，标准 MAVLink2）。不会复位主控（DTR/RTS 保持释放）。", 14);
        btn(row(u), "连接 USB", v -> { ensureService(); c.connectUsb(); });
        text(u, "遥控器只能「上锁」急停：不能进入/退出测试，测试中杆量和模式切换无效。", 12);
        LinearLayout s = card(p, "状态");
        connStatus = text(s, "未连接", 15);
        LinearLayout r = row(s);
        btn(r, "进入测试模式(30)", v -> c.send(c.mav.commandLong(c.tsys, c.tcomp, Mav.CMD_DO_SET_MODE, 1, 30)));
        btn(r, "断开", v -> c.disconnect());
        text(s, "提示：测试期间屏幕常亮；切到后台由前台服务保持链路和日志。", 12);
        buildGuide(p);
    }

    // ---------------- v0.3: permissions, vivo guide, crash report ----------------
    TextView permState;
    void buildGuide(LinearLayout p) {
        LinearLayout g = card(p, "③ 手机设置（vivo / iQOO 必看，防止后台被杀）");
        permState = text(g, "", 14);
        text(g, "1. 通知：设置 → 通知与状态栏 → 应用通知管理 → Rogue耐久测试 → 允许通知（不开也能用，只是看不到通知栏急停）。\n"
              + "2. 自启动：i管家 → 应用管理 → 权限管理 → 自启动 → 打开 Rogue耐久测试。\n"
              + "3. 后台耗电：设置 → 电池 → 后台耗电管理 → Rogue耐久测试 → 「允许后台高耗电」/「允许后台运行」（老系统在 i管家 → 后台高耗电）。\n"
              + "4. 锁定：打开最近任务，把本 App 卡片下拉（或点卡片上的锁）锁住，「一键清理」就不会杀它。\n"
              + "5. 测试时保持 App 在前台、屏幕常亮、插着充电器最稳。", 13);
        LinearLayout r1 = row(g);
        btn(r1, "通知设置", v -> openNotificationSettings());
        btn(r1, "自启动/i管家", v -> openVivoAutostart());
        LinearLayout r2 = row(g);
        btn(r2, "电池优化", v -> openBatterySettings());
        btn(r2, "应用详情", v -> openAppDetails());
    }
    boolean notifGranted() {
        if (Build.VERSION.SDK_INT >= 33 && checkSelfPermission("android.permission.POST_NOTIFICATIONS") != android.content.pm.PackageManager.PERMISSION_GRANTED) return false;
        try { android.app.NotificationManager nm = getSystemService(android.app.NotificationManager.class); return nm == null || Build.VERSION.SDK_INT < 24 || nm.areNotificationsEnabled(); } catch (Throwable e) { return false; }
    }
    boolean batteryIgnored() {
        try { android.os.PowerManager pm = (android.os.PowerManager) getSystemService(POWER_SERVICE); return Build.VERSION.SDK_INT < 23 || pm.isIgnoringBatteryOptimizations(getPackageName()); } catch (Throwable e) { return false; }
    }
    void refreshPermState() {
        if (permState == null) return;
        permState.setText("通知：" + (notifGranted() ? "已允许 ✓" : "未允许（不影响测试）") + "    电池优化：" + (batteryIgnored() ? "已忽略 ✓" : "未忽略")
                + "\n前台服务：" + (LinkService.fgActive ? "运行中 ✓" : "未运行（连接后启动）") + (LinkService.lastError.isEmpty() ? "" : "\n⚠ " + LinkService.lastError));
    }
    void askNotificationPermission() {
        try {
            if (Build.VERSION.SDK_INT >= 33 && !notifGranted() && !getSharedPreferences("endu", 0).getBoolean("askedNotif", false)) {
                getSharedPreferences("endu", 0).edit().putBoolean("askedNotif", true).apply();
                requestPermissions(new String[]{"android.permission.POST_NOTIFICATIONS"}, 1);
            }
        } catch (Throwable e) { android.util.Log.e("ENDU", "requestPermissions", e); }
    }
    @Override public void onRequestPermissionsResult(int code, String[] perms, int[] res) {
        super.onRequestPermissionsResult(code, perms, res);
        boolean ok = res.length > 0 && res[0] == android.content.pm.PackageManager.PERMISSION_GRANTED;
        android.widget.Toast.makeText(this, ok ? "通知已允许" : "未允许通知：App 照常可用，通知栏不显示急停。可在「③ 手机设置」里再开。", android.widget.Toast.LENGTH_LONG).show();
        refreshPermState();
    }
    void ensureService() {
        if (demo) return;
        boolean ok = LinkService.start(this);
        if (!ok) android.widget.Toast.makeText(this, "后台服务没起来，测试时请保持 App 在前台。" , android.widget.Toast.LENGTH_LONG).show();
        ui.postDelayed(this::refreshPermState, 800);
    }
    boolean tryStart(Intent i) {
        try { i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK); startActivity(i); return true; } catch (Throwable e) { return false; }
    }
    void openAppDetails() { tryStart(new Intent(android.provider.Settings.ACTION_APPLICATION_DETAILS_SETTINGS, android.net.Uri.parse("package:" + getPackageName()))); }
    void openNotificationSettings() {
        Intent i = new Intent("android.settings.APP_NOTIFICATION_SETTINGS").putExtra("android.provider.extra.APP_PACKAGE", getPackageName())
                .putExtra("app_package", getPackageName()).putExtra("app_uid", getApplicationInfo().uid);
        if (!tryStart(i)) openAppDetails();
    }
    void openBatterySettings() {
        if (Build.VERSION.SDK_INT >= 23 && !batteryIgnored()
                && tryStart(new Intent(android.provider.Settings.ACTION_REQUEST_IGNORE_BATTERY_OPTIMIZATIONS, android.net.Uri.parse("package:" + getPackageName())))) return;
        if (!tryStart(new Intent(android.provider.Settings.ACTION_IGNORE_BATTERY_OPTIMIZATION_SETTINGS))) openAppDetails();
    }
    void openVivoAutostart() {
        String[][] cands = {   // vivo / iQOO background-startup managers differ by OS version; try each, fall back to app details
                {"com.vivo.permissionmanager", "com.vivo.permissionmanager.activity.BgStartUpManagerActivity"},
                {"com.iqoo.secure", "com.iqoo.secure.ui.phoneoptimize.BgStartUpManager"},
                {"com.iqoo.secure", "com.iqoo.secure.ui.phoneoptimize.AddWhiteListActivity"},
                {"com.vivo.permissionmanager", "com.vivo.permissionmanager.activity.PurviewTabActivity"}};
        for (String[] cn : cands) if (tryStart(new Intent().setClassName(cn[0], cn[1]))) return;
        Intent launch = getPackageManager().getLaunchIntentForPackage("com.iqoo.secure");
        if (launch != null && tryStart(launch)) return;
        android.widget.Toast.makeText(this, "没找到 i管家，请手动：i管家 → 应用管理 → 自启动", android.widget.Toast.LENGTH_LONG).show();
        openAppDetails();
    }
    void showLastCrash() {
        try {
            File dir = getExternalFilesDir(null); if (dir == null) dir = getFilesDir();
            File f = new File(dir, App.CRASH_FILE);
            if (!f.exists()) return;
            String txt = new String(java.nio.file.Files.readAllBytes(f.toPath()), "UTF-8");
            f.renameTo(new File(dir, "last_crash_seen.txt"));
            TextView tv = new TextView(this); tv.setText(txt); tv.setTextSize(11); tv.setPadding(32, 16, 32, 16); tv.setTextIsSelectable(true);
            ScrollView sc = new ScrollView(this); sc.addView(tv);
            new android.app.AlertDialog.Builder(this).setTitle("上次 App 崩溃了（已存到 下载/RogueEndurance）").setView(sc)
                    .setPositiveButton("知道了", null)
                    .setNeutralButton("复制", (d, w) -> { android.content.ClipboardManager cm = (android.content.ClipboardManager) getSystemService(CLIPBOARD_SERVICE); cm.setPrimaryClip(android.content.ClipData.newPlainText("crash", txt)); })
                    .show();
        } catch (Throwable e) { android.util.Log.e("ENDU", "showLastCrash", e); }
    }
    @Override protected void onResume() { super.onResume(); refreshPermState(); }

    // ---------------- 参数 ----------------
    SeekBar bar(LinearLayout p, boolean fwd) {
        SeekBar s = new SeekBar(this); s.setMax(1000);   // 0.1 % resolution = stepless
        s.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar sb, int v, boolean u) { if (fwd) fwdPct = v / 10f; else revPct = v / 10f; refreshBarLabels(); if (c.rtOn) updateRt(); }
            public void onStartTrackingTouch(SeekBar sb) {}
            public void onStopTrackingTouch(SeekBar sb) {   // auto mode: write on release
                if (!c.rtOn && !demo) c.send(c.mav.paramSet(c.tsys, c.tcomp, fwd ? "ET_THR" : "ET_REV_THR", fwd ? fwdPct : revPct));
            }
        });
        p.addView(s, new LinearLayout.LayoutParams(-1, 110));
        return s;
    }
    void setBar(SeekBar s, float pct) { if (s != null) s.setProgress(Math.round(Math.max(0, Math.min(100, pct)) * 10)); }
    void buildParams(LinearLayout p) {
        LinearLayout t = card(p, "油门（无级，100% = 上限 ≈ 6000 rpm）");
        fwdLabel = text(t, "", 15); fwdBar = bar(t, true);
        revLabel = text(t, "", 15); revBar = bar(t, false);
        setBar(fwdBar, fwdPct); setBar(revBar, revPct);
        text(t, "转速为水槽表(12.3V)开环估算；反转按正转表估。松手即写入船（ET_THR / ET_REV_THR）。", 12);
        LinearLayout cyc = card(p, "循环参数");
        for (String[] pl : PARAM_LABELS) {
            LinearLayout r = row(cyc);
            TextView lb = new TextView(this); lb.setText(pl[1] + "\n" + pl[0]); lb.setTextSize(13); r.addView(lb, new LinearLayout.LayoutParams(0, -2, 1.3f));
            EditText e = new EditText(this); e.setInputType(InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_DECIMAL); e.setTextSize(15);
            r.addView(e, new LinearLayout.LayoutParams(0, -2, 1)); paramEdits.put(pl[0], e);
        }
        LinearLayout r1 = row(cyc);
        btn(r1, "读取", v -> { for (String n : Core.PARAMS) c.send(c.mav.paramRead(c.tsys, c.tcomp, n)); });
        btn(r1, "应用(写入)", v -> applyParams());
        LinearLayout ctl = card(p, "模式1 自动循环（固件自己跑，手机可断开）");
        LinearLayout r2 = row(ctl);
        btn(r2, "开始(清零)", v -> { ensureService(); c.send(c.mav.commandLong(c.tsys, c.tcomp, Mav.CMD_USER_1, 1, 1)); });
        btn(r2, "开始(续计)", v -> { ensureService(); c.send(c.mav.commandLong(c.tsys, c.tcomp, Mav.CMD_USER_1, 1, 0)); });
        LinearLayout r3 = row(ctl);
        btn(r3, "暂停", v -> c.send(c.mav.commandLong(c.tsys, c.tcomp, Mav.CMD_USER_1, 2)));
        btn(r3, "继续", v -> c.send(c.mav.commandLong(c.tsys, c.tcomp, Mav.CMD_USER_1, 3)));
    }
    void applyParams() {
        Map<String, String> v = new LinkedHashMap<>();
        v.put("ET_THR", String.valueOf(fwdPct)); v.put("ET_REV_THR", String.valueOf(revPct));
        for (Map.Entry<String, EditText> e : paramEdits.entrySet()) v.put(e.getKey(), e.getValue().getText().toString());
        c.writeParams(v);
    }
    String barText(String name, float pct) {
        float start = c.param("ET_PWM_START", 1550), max = c.param("ET_PWM_MAX", 1773);
        float pwm = Rpm.pwm(pct, start, max);
        return String.format(Locale.US, "%s  %.1f %%   ≈ %.0f rpm   ≈ %.1f A/电机   (PWM %s%.0f)", name, pct, Rpm.rpm(pwm), Rpm.amp(pwm),
                name.equals("反转") ? "-" : "+", pwm - 1500);
    }
    void refreshBarLabels() { if (fwdLabel != null) { fwdLabel.setText(barText("正转", fwdPct)); revLabel.setText(barText("反转", revPct)); } }

    // ---------------- 监控 ----------------
    void buildMonitor(LinearLayout p) {
        LinearLayout m = card(p, "实时数据");
        monBig = text(m, "", 26); monBig.setTypeface(Typeface.MONOSPACE, Typeface.BOLD);
        monDetail = text(m, "", 15);
        LinearLayout rt = card(p, "模式2 实时控制（手机须保持连接，断链 " + "1 s 自动停）");
        LinearLayout r = row(rt);
        btn(r, "进入实时", v -> { ensureService(); c.send(c.mav.commandLong(c.tsys, c.tcomp, Mav.CMD_USER_1, 4)); rtDir = 0; c.rtOn = true; updateRt(); });
        btn(r, "退出实时", v -> { rtDir = 0; updateRt(); c.rtOn = false; });
        LinearLayout r2 = row(rt);
        btn(r2, "◀ 反转", v -> { rtDir = -1; updateRt(); });
        btn(r2, "■ 停", v -> { rtDir = 0; updateRt(); });
        btn(r2, "正转 ▶", v -> { rtDir = 1; updateRt(); });
        rtState = text(rt, "", 15);
        text(rt, "拖动「参数」页的油门条即时生效（受 ET_RAMP 斜坡限速，固件再按 ET_PWM_MAX 限幅）。", 12);
    }
    void updateRt() {
        float pct = rtDir > 0 ? fwdPct : rtDir < 0 ? -revPct : 0;
        c.setRealtime(pct);
        if (rtState != null) rtState.setText(String.format(Locale.US, "实时指令：%s %.1f %%%s", rtDir > 0 ? "正转" : rtDir < 0 ? "反转" : "停", Math.abs(pct), c.rtOn ? "  （发送中 5 Hz）" : "  （未进入实时）"));
    }

    // ---------------- 日志 ----------------
    void buildLog(LinearLayout p) {
        LinearLayout l = card(p, "CSV 日志（每秒一行 + 事件）");
        logInfo = text(l, "", 14);
        LinearLayout r = row(l);
        btn(r, "一键导出", v -> c.exportCsv());
        btn(r, "新建日志", v -> c.openCsv());
        text(l, "导出到：下载/RogueEndurance/，并弹出分享（微信/邮件）。\n字段：time,type,state,phase,remain_s,cycles,bursts,cum_h,out_l_pct,out_r_pct,pwm_l,pwm_r,volt_v,curr_a,mode,armed,text\n手机断开期间的数据在船上 SD 卡日志（ETST）里。", 12);
        btn(row(l), "急停并退出 App", v -> { c.estop(); try { stopService(new Intent(this, LinkService.class)); } catch (Throwable ignored) {} c.shutdown(); finish(); });
    }

    final Runnable uiTick = new Runnable() { public void run() {
        boolean link = demo || c.linkUp();
        int st = (int) c.g("ET_ST"), ph = (int) c.g("ET_PH");
        connStatus.setText((link ? "● 已连接  " : "○ 无数据  ") + c.linkName + "\n飞控 sys " + c.tsys + "   模式 " + c.mode + (c.mode == 30 ? " (ENDU)" : "") + (c.armed ? "   已解锁" : "   未解锁")
                + "\n最后消息：" + c.lastText);
        monBig.setText(String.format(Locale.US, "%5.2f V   %5.2f A", c.volt, c.curr));
        float cr = Rpm.rpm(c.pwmL);
        monDetail.setText(String.format(Locale.US, "状态 %s   阶段 %s   剩余 %.0f s\n左 PWM %d (≈%.0f rpm)   右 PWM %d (≈%.0f rpm)\n输出 %.1f%% / %.1f%%\n循环 %d   点动组 %d   累计运行 %.2f h\n%s",
                st >= 0 && st < STATES.length ? STATES[st] : "-", ph >= 0 && ph < PHASES.length ? PHASES[ph] : "-", Math.max(0, c.g("ET_REM")),
                c.pwmL, Rpm.rpm(Math.abs(c.pwmL - 1500) + 1500), c.pwmR, Rpm.rpm(Math.abs(c.pwmR - 1500) + 1500), c.g("ET_OUTL"), c.g("ET_OUTR"),
                (int) c.g("ET_CYC"), (int) c.g("ET_BRST"), c.g("ET_CUMH"), "电流为整船总电流（<1A 有盲区）；rpm 为开环估算"));
        File dir = getExternalFilesDir(null); File[] fs = dir == null ? null : dir.listFiles((d, n) -> n.endsWith(".csv"));
        StringBuilder sb = new StringBuilder("当前：" + (c.csvFile != null ? c.csvFile.getName() : "-") + "\n");
        if (demo) sb.append("endu_20261117_091502.csv   2.1 MB\nendu_20261116_083010.csv   4.6 MB\n");
        else if (fs != null) { Arrays.sort(fs); for (File f : fs) sb.append(f.getName()).append(String.format(Locale.US, "   %.1f KB\n", f.length() / 1024f)); }
        logInfo.setText(sb.toString());
        if (!demo) { updateRt(); refreshPermState(); }
        ui.postDelayed(this, 500);
    }};

    void loadDemo() {   // sample values for screenshots only
        c.linkName = "Wi-Fi UDP 14550"; c.tsys = 1; c.mode = 30; c.armed = true; c.volt = 12.08f; c.curr = 6.84f; c.pwmL = 1721; c.pwmR = 1721;
        c.lastText = "ENDU: auto test started";
        synchronized (c.nv) { c.nv.put("ET_ST", 1f); c.nv.put("ET_PH", 1f); c.nv.put("ET_REM", 1312f); c.nv.put("ET_CYC", 17f); c.nv.put("ET_BRST", 4f); c.nv.put("ET_CUMH", 18.62f); c.nv.put("ET_OUTL", 76.5f); c.nv.put("ET_OUTR", 76.5f); }
        float[] vals = {1800, 300, 1800, 14400, 10, 5, 50, 79200, 7200, 50, 3, 1000, 15, 10.5f, 0, 1773, 1550};
        for (int i = 0; i < Core.PARAMS.length && i < vals.length + 2; i++) { }
        String[] names = {"ET_FWD_S", "ET_STOP_S", "ET_REV_S", "ET_BRST_INT", "ET_BRST_ON", "ET_BRST_OFF", "ET_BRST_N", "ET_DAY_S", "ET_REST_S", "ET_RAMP", "ET_MOT", "ET_RT_TMO", "ET_IMAX", "ET_VMIN", "ET_TOTAL_H", "ET_PWM_MAX", "ET_PWM_START"};
        for (int i = 0; i < names.length; i++) { EditText e = paramEdits.get(names[i]); if (e != null) e.setText(vals[i] == Math.rint(vals[i]) ? String.valueOf((long) vals[i]) : String.valueOf(vals[i])); }
        fwdPct = 76.5f; revPct = 80f; setBar(fwdBar, fwdPct); setBar(revBar, revPct); refreshBarLabels();
        rtDir = 1; if (rtState != null) rtState.setText("实时指令：正转 76.5 %  （发送中 5 Hz）");
    }

    /** demo+snap: renders each tab of this real Activity into a PNG via View.draw() (works even if the emulator display compositor is broken). */
    void snap(int k) {
        showTab(k);
        ui.postDelayed(() -> {
            try {
                int W = 1080, H = 2280;   // 1080x2400 screen minus status bar
                View root = rootView;
                root.measure(View.MeasureSpec.makeMeasureSpec(W, View.MeasureSpec.EXACTLY), View.MeasureSpec.makeMeasureSpec(H, View.MeasureSpec.EXACTLY));
                root.layout(0, 0, W, H);
                android.graphics.Bitmap bm = android.graphics.Bitmap.createBitmap(W, H, android.graphics.Bitmap.Config.ARGB_8888);
                root.draw(new android.graphics.Canvas(bm));
                View body = (View) pages[k].getParent();   // whole scroll content, un-clipped
                body.measure(View.MeasureSpec.makeMeasureSpec(W, View.MeasureSpec.EXACTLY), View.MeasureSpec.makeMeasureSpec(0, View.MeasureSpec.UNSPECIFIED));
                body.layout(0, 0, W, body.getMeasuredHeight());
                android.graphics.Bitmap full = android.graphics.Bitmap.createBitmap(W, Math.max(1, body.getMeasuredHeight()), android.graphics.Bitmap.Config.ARGB_8888);
                android.graphics.Canvas fc = new android.graphics.Canvas(full); fc.drawColor(Color.rgb(245, 247, 250)); body.draw(fc);
                root.requestLayout();
                File d = getExternalFilesDir("snap");
                try (java.io.FileOutputStream o = new java.io.FileOutputStream(new File(d, "tab" + k + ".png"))) { bm.compress(android.graphics.Bitmap.CompressFormat.PNG, 100, o); }
                try (java.io.FileOutputStream o = new java.io.FileOutputStream(new File(d, "tab" + k + "_full.png"))) { full.compress(android.graphics.Bitmap.CompressFormat.PNG, 100, o); }
            } catch (Exception e) { android.util.Log.e("ENDU", "snap", e); }
            if (k < 3) snap(k + 1); else android.util.Log.i("ENDU", "SNAP_DONE");
        }, 2500);
    }

    final BroadcastReceiver usbReceiver = new BroadcastReceiver() {
        public void onReceive(Context cx, Intent i) { if (Core.ACTION_USB.equals(i.getAction())) { ensureService(); c.connectUsb(); } }
    };
    @Override protected void onDestroy() {
        c.paramListener = null;
        try { unregisterReceiver(usbReceiver); } catch (Exception ignored) {}
        super.onDestroy();
    }
}
