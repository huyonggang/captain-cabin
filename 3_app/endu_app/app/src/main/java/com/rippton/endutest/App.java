package com.rippton.endutest;

import android.app.Application;
import android.content.ContentValues;
import android.net.Uri;
import android.os.Build;
import android.os.Environment;
import android.provider.MediaStore;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

/** Installs a crash handler: stack trace -> app files (shown on next launch) + 下载/RogueEndurance/crash_*.txt. */
public class App extends Application {
    static final String CRASH_FILE = "last_crash.txt";

    @Override public void onCreate() {
        super.onCreate();
        final Thread.UncaughtExceptionHandler prev = Thread.getDefaultUncaughtExceptionHandler();
        Thread.setDefaultUncaughtExceptionHandler((t, e) -> {
            try { writeCrash(t, e); } catch (Throwable ignored) {}
            if (prev != null) prev.uncaughtException(t, e); else System.exit(2);
        });
    }

    static String deviceInfo() {
        return "App 0.3-test | " + Build.MANUFACTURER + " " + Build.MODEL + " | Android " + Build.VERSION.RELEASE + " (API " + Build.VERSION.SDK_INT + ")"
                + (Build.VERSION.SDK_INT >= 23 ? " | patch " + Build.VERSION.SECURITY_PATCH : "") + " | " + Build.DISPLAY;
    }

    void writeCrash(Thread t, Throwable e) throws Exception {
        String ts = new SimpleDateFormat("yyyyMMdd_HHmmss", Locale.US).format(new Date());
        StringWriter sw = new StringWriter(); e.printStackTrace(new PrintWriter(sw));
        String text = "Rogue 耐久测试 App 崩溃记录 " + ts + "\n" + deviceInfo() + "\nthread: " + t.getName() + "\n\n" + sw;
        byte[] b = text.getBytes("UTF-8");
        File dir = getExternalFilesDir(null); if (dir == null) dir = getFilesDir();
        try (FileOutputStream o = new FileOutputStream(new File(dir, CRASH_FILE))) { o.write(b); }
        String name = "crash_" + ts + ".txt";
        if (Build.VERSION.SDK_INT >= 29) {
            ContentValues cv = new ContentValues();
            cv.put(MediaStore.Downloads.DISPLAY_NAME, name);
            cv.put(MediaStore.Downloads.MIME_TYPE, "text/plain");
            cv.put(MediaStore.Downloads.RELATIVE_PATH, Environment.DIRECTORY_DOWNLOADS + "/RogueEndurance");
            Uri u = getContentResolver().insert(MediaStore.Downloads.EXTERNAL_CONTENT_URI, cv);
            if (u != null) try (OutputStream o = getContentResolver().openOutputStream(u)) { o.write(b); }
        } else {
            File out = new File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS), "RogueEndurance");
            out.mkdirs();
            try (FileOutputStream o = new FileOutputStream(new File(out, name))) { o.write(b); }
        }
    }
}
