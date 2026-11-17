package com.rippton.endutest;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ServiceInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.os.PowerManager;
import android.util.Log;

import java.util.Locale;

/**
 * Foreground service (type connectedDevice) that keeps the MAVLink link, realtime keep-alive and CSV logging
 * alive in background / Doze. v0.3: started only when the user connects or starts a test (never at launch),
 * every step is guarded; if the system refuses the foreground service the App keeps working in the foreground
 * (Core runs without the service) and tells the user.
 */
public class LinkService extends Service {
    static final String TAG = "ENDU";
    static final String CH = "endu";
    static final String ACT_ESTOP = "com.rippton.endutest.ESTOP", ACT_QUIT = "com.rippton.endutest.QUIT";
    static volatile boolean fgActive;          // true while running as a foreground service
    static volatile String lastError = "";     // why the foreground service could not start (shown in UI)
    PowerManager.WakeLock wl; WifiManager.WifiLock wifiLock;
    final Handler h = new Handler(Looper.getMainLooper());

    /** @return true if the start request was accepted by the system. Never throws. */
    static boolean start(Context c) {
        Core.get(c).start();   // the link works even if the service is refused
        if (fgActive) return true;
        try {
            Intent i = new Intent(c, LinkService.class);
            if (Build.VERSION.SDK_INT >= 26) c.startForegroundService(i); else c.startService(i);
            return true;
        } catch (Throwable e) {   // ForegroundServiceStartNotAllowedException (API 31+), SecurityException, IllegalStateException
            lastError = "前台服务启动被拒绝：" + e.getClass().getSimpleName() + " " + e.getMessage();
            Log.e(TAG, "startForegroundService failed", e);
            return false;
        }
    }

    @Override public void onCreate() {
        super.onCreate();
        try {
            NotificationManager nm = getSystemService(NotificationManager.class);
            if (Build.VERSION.SDK_INT >= 26 && nm != null) nm.createNotificationChannel(new NotificationChannel(CH, "耐久测试链路", NotificationManager.IMPORTANCE_LOW));
            Notification n = build("运行中");
            if (Build.VERSION.SDK_INT >= 29) startForeground(1, n, ServiceInfo.FOREGROUND_SERVICE_TYPE_CONNECTED_DEVICE);
            else startForeground(1, n);
            fgActive = true; lastError = "";
            Log.i(TAG, "foreground service started");
        } catch (Throwable e) {
            fgActive = false;
            lastError = "前台服务不可用（" + e.getClass().getSimpleName() + "），App 需保持在前台：" + e.getMessage();
            Log.e(TAG, "startForeground failed, running without foreground service", e);
        }
        try {
            PowerManager pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
            wl = pm.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, "endu:link"); wl.setReferenceCounted(false); wl.acquire();
        } catch (Throwable e) { Log.e(TAG, "wake lock failed", e); }
        try {
            WifiManager wm = (WifiManager) getApplicationContext().getSystemService(Context.WIFI_SERVICE);
            if (wm != null) { wifiLock = wm.createWifiLock(WifiManager.WIFI_MODE_FULL_HIGH_PERF, "endu:udp"); wifiLock.setReferenceCounted(false); wifiLock.acquire(); }
        } catch (Throwable e) { Log.e(TAG, "wifi lock failed", e); }
        Core.get(this).start();
        if (fgActive) h.post(tick); else stopSelf();   // must not linger as a non-foreground "foreground" service
    }

    @Override public int onStartCommand(Intent i, int flags, int id) {
        try {
            if (i != null && ACT_ESTOP.equals(i.getAction())) Core.get(this).estop();
            if (i != null && ACT_QUIT.equals(i.getAction())) { Core.get(this).estop(); Core.get(this).shutdown(); stopSelf(); }
        } catch (Throwable e) { Log.e(TAG, "onStartCommand", e); }
        return START_STICKY;
    }

    final Runnable tick = new Runnable() { public void run() {
        try {
            Core c = Core.get(LinkService.this);
            String s = (c.linkUp() ? "已连接" : "无数据") + String.format(Locale.US, "  %.2fV %.2fA  PWM %d/%d", c.volt, c.curr, c.pwmL, c.pwmR)
                    + (c.rtOn ? "  实时控制中" : "");
            NotificationManager nm = getSystemService(NotificationManager.class);
            if (nm != null && (Build.VERSION.SDK_INT < 24 || nm.areNotificationsEnabled())) nm.notify(1, build(s));
        } catch (Throwable e) { Log.e(TAG, "notify", e); }
        h.postDelayed(this, 2000);
    }};

    Notification build(String text) {
        int fl = Build.VERSION.SDK_INT >= 23 ? PendingIntent.FLAG_IMMUTABLE : 0;
        PendingIntent open = PendingIntent.getActivity(this, 0, new Intent(this, MainActivity.class), fl);
        PendingIntent stop = PendingIntent.getService(this, 1, new Intent(this, LinkService.class).setAction(ACT_ESTOP), fl);
        PendingIntent quit = PendingIntent.getService(this, 2, new Intent(this, LinkService.class).setAction(ACT_QUIT), fl);
        Notification.Builder b = Build.VERSION.SDK_INT >= 26 ? new Notification.Builder(this, CH) : new Notification.Builder(this);
        return b.setContentTitle("Rogue 耐久测试").setContentText(text).setSmallIcon(android.R.drawable.stat_sys_data_bluetooth)
                .setOngoing(true).setContentIntent(open)
                .addAction(android.R.drawable.ic_delete, "急停", stop)
                .addAction(android.R.drawable.ic_menu_close_clear_cancel, "急停并退出", quit).build();
    }

    @Override public void onDestroy() {
        h.removeCallbacks(tick);
        fgActive = false;
        try { if (wl != null && wl.isHeld()) wl.release(); } catch (Throwable ignored) {}
        try { if (wifiLock != null && wifiLock.isHeld()) wifiLock.release(); } catch (Throwable ignored) {}
        super.onDestroy();
    }
    @Override public IBinder onBind(Intent i) { return null; }
}
