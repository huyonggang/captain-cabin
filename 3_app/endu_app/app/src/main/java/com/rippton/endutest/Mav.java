package com.rippton.endutest;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.charset.StandardCharsets;

/** Minimal MAVLink v1/v2 codec for the endurance test App.
 *  v0.3: also the Rippton "self-modified" MAVLink used on the boat SERIAL1 / remote link (SR1_ENC 1):
 *  MAVLink v1 frame, STX 0xC3 (v2 would be 0xC4), CRC init 0xFF1E instead of 0xFFFF; everything else standard.
 *  Source: modules/mavlink/pymavlink/0001-mavlink-to-support-self-modified-header-and-crc.patch (boat) and
 *  remote V1.01.42 Middlewares/MAVLINK/minimal/mavlink.h + checksum.h (STX1 0xC3, X25_INIT_CRC2 0xff1e, v1 only). */
public final class Mav {
    public static final int HEARTBEAT = 0, SYS_STATUS = 1, PARAM_REQUEST_READ = 20, PARAM_SET = 23,
            PARAM_VALUE = 22, SERVO_OUTPUT_RAW = 36, REQUEST_DATA_STREAM = 66, COMMAND_LONG = 76,
            COMMAND_ACK = 77, BATTERY_STATUS = 147, NAMED_VALUE_FLOAT = 251, STATUSTEXT = 253;
    public static final int CMD_DO_SET_MODE = 176, CMD_USER_1 = 31010, CMD_USER_2 = 31011;

    static int crcExtra(int id) {
        switch (id) {
            case HEARTBEAT: return 50;
            case SYS_STATUS: return 124;
            case PARAM_REQUEST_READ: return 214;
            case PARAM_VALUE: return 220;
            case PARAM_SET: return 168;
            case SERVO_OUTPUT_RAW: return 222;
            case REQUEST_DATA_STREAM: return 148;
            case COMMAND_LONG: return 152;
            case COMMAND_ACK: return 143;
            case BATTERY_STATUS: return 154;
            case NAMED_VALUE_FLOAT: return 170;
            case STATUSTEXT: return 83;
            default: return -1;
        }
    }
    static int msgLen(int id) {
        switch (id) {
            case HEARTBEAT: return 9;
            case SYS_STATUS: return 43;
            case PARAM_VALUE: return 25;
            case SERVO_OUTPUT_RAW: return 37;
            case COMMAND_ACK: return 10;
            case BATTERY_STATUS: return 54;
            case NAMED_VALUE_FLOAT: return 18;
            case STATUSTEXT: return 54;
            default: return 255;
        }
    }

    static int crcAcc(int b, int crc) {
        int tmp = (b ^ crc) & 0xff;
        tmp = (tmp ^ (tmp << 4)) & 0xff;
        return ((crc >> 8) ^ (tmp << 8) ^ (tmp << 3) ^ (tmp >> 4)) & 0xffff;
    }

    public static final class Msg {
        public final int id, sysid, compid;
        public final ByteBuffer p;   // little endian, zero-extended to full length
        Msg(int id, int sysid, int compid, byte[] payload) {
            this.id = id; this.sysid = sysid; this.compid = compid;
            byte[] full = new byte[Math.max(payload.length, msgLen(id) == 255 ? payload.length : msgLen(id))];
            System.arraycopy(payload, 0, full, 0, payload.length);
            p = ByteBuffer.wrap(full).order(ByteOrder.LITTLE_ENDIAN);
        }
        public String str(int off, int len) {
            byte[] b = new byte[len];
            for (int i = 0; i < len; i++) b[i] = p.get(off + i);
            int n = 0; while (n < len && b[n] != 0) n++;
            return new String(b, 0, n, StandardCharsets.US_ASCII);
        }
    }

    // ---------------- encoder ----------------
    private int seq = 0;
    public volatile int sysid = 200, compid = 190;   // 200 = ET_APP_SYSID default; the remote itself uses 255
    public static final int WIRE_V2 = 0, WIRE_V1_SELFMOD = 1;
    public volatile int wire = WIRE_V2;

    public synchronized byte[] frame(int id, byte[] payload) {
        if (wire == WIRE_V1_SELFMOD) return frameV1(id, payload, 0xC3, 0xFF1E);
        return frameV2(id, payload);
    }
    /** MAVLink v1: payload must be the full base length (remote checks len == table length). */
    synchronized byte[] frameV1(int id, byte[] payload, int stx, int crcInit) {
        int len = payload.length;
        byte[] f = new byte[8 + len];
        f[0] = (byte) stx; f[1] = (byte) len; f[2] = (byte) (seq++ & 0xff); f[3] = (byte) sysid; f[4] = (byte) compid; f[5] = (byte) (id & 0xff);
        System.arraycopy(payload, 0, f, 6, len);
        int crc = crcInit;
        for (int i = 1; i < 6 + len; i++) crc = crcAcc(f[i] & 0xff, crc);
        crc = crcAcc(crcExtra(id), crc);
        f[6 + len] = (byte) (crc & 0xff); f[7 + len] = (byte) (crc >> 8);
        return f;
    }
    synchronized byte[] frameV2(int id, byte[] payload) {
        int len = payload.length;
        byte[] f = new byte[12 + len];
        f[0] = (byte) 0xFD; f[1] = (byte) len; f[2] = 0; f[3] = 0; f[4] = (byte) (seq++ & 0xff);
        f[5] = (byte) sysid; f[6] = (byte) compid;
        f[7] = (byte) (id & 0xff); f[8] = (byte) ((id >> 8) & 0xff); f[9] = (byte) ((id >> 16) & 0xff);
        System.arraycopy(payload, 0, f, 10, len);
        int crc = 0xffff;
        for (int i = 1; i < 10 + len; i++) crc = crcAcc(f[i] & 0xff, crc);
        crc = crcAcc(crcExtra(id), crc);
        f[10 + len] = (byte) (crc & 0xff); f[11 + len] = (byte) (crc >> 8);
        return f;
    }
    static ByteBuffer le(int n) { return ByteBuffer.allocate(n).order(ByteOrder.LITTLE_ENDIAN); }
    static void putId(ByteBuffer b, String id, int n) {
        byte[] s = id.getBytes(StandardCharsets.US_ASCII);
        for (int i = 0; i < n; i++) b.put(i < s.length ? s[i] : 0);
    }
    public byte[] heartbeat() {
        ByteBuffer b = le(9); b.putInt(0); b.put((byte) 6 /*GCS*/); b.put((byte) 8 /*INVALID*/); b.put((byte) 0); b.put((byte) 0); b.put((byte) 3);
        return frame(HEARTBEAT, b.array());
    }
    public byte[] commandLong(int tsys, int tcomp, int cmd, float... prm) {
        ByteBuffer b = le(33);
        for (int i = 0; i < 7; i++) b.putFloat(i < prm.length ? prm[i] : 0f);
        b.putShort((short) cmd); b.put((byte) tsys); b.put((byte) tcomp); b.put((byte) 0);
        return frame(COMMAND_LONG, b.array());
    }
    public byte[] paramSet(int tsys, int tcomp, String name, float v) {
        ByteBuffer b = le(23); b.putFloat(v); b.put((byte) tsys); b.put((byte) tcomp); putId(b, name, 16); b.put((byte) 9 /*REAL32*/);
        return frame(PARAM_SET, b.array());
    }
    public byte[] paramRead(int tsys, int tcomp, String name) {
        ByteBuffer b = le(20); b.putShort((short) -1); b.put((byte) tsys); b.put((byte) tcomp); putId(b, name, 16);
        return frame(PARAM_REQUEST_READ, b.array());
    }
    public byte[] requestStreams(int tsys, int tcomp, int hz) {
        ByteBuffer b = le(6); b.putShort((short) hz); b.put((byte) tsys); b.put((byte) tcomp); b.put((byte) 0 /*ALL*/); b.put((byte) 1);
        return frame(REQUEST_DATA_STREAM, b.array());
    }

    // ---------------- decoder (byte-at-a-time state machine) ----------------
    private final byte[] buf = new byte[280];
    private int pos = 0, need = 0;
    public int crcErrors = 0;

    /** feed one byte; returns a message when a valid frame completes, else null. */
    public Msg parse(int c) {
        c &= 0xff;
        if (pos == 0) {
            if (c != 0xFD && c != 0xFE && c != 0xC3 && c != 0xC4) return null;
            buf[pos++] = (byte) c; need = 0; return null;
        }
        buf[pos++] = (byte) c;
        int stx = buf[0] & 0xff;
        boolean v2 = stx == 0xFD || stx == 0xC4;
        int crcInit = (stx == 0xC3 || stx == 0xC4) ? 0xFF1E : 0xFFFF;
        int hdr = v2 ? 10 : 6;
        if (pos == 2) {
            int len = buf[1] & 0xff;
            need = hdr + len + 2;
        }
        if (pos == 3 && v2 && ((buf[2] & 0xff) & ~0x01) != 0) { pos = 0; return null; }  // unknown incompat flags
        if (need > 0 && pos == need) {
            pos = 0;
            int len = buf[1] & 0xff;
            int id = v2 ? ((buf[7] & 0xff) | ((buf[8] & 0xff) << 8) | ((buf[9] & 0xff) << 16)) : (buf[5] & 0xff);
            int extra = crcExtra(id);
            if (extra < 0) return null;
            int crc = crcInit;
            for (int i = 1; i < hdr + len; i++) crc = crcAcc(buf[i] & 0xff, crc);
            crc = crcAcc(extra, crc);
            int got = (buf[hdr + len] & 0xff) | ((buf[hdr + len + 1] & 0xff) << 8);
            if (got != crc) { crcErrors++; return null; }
            if (v2 && ((buf[2] & 0xff) & 0x01) != 0) { /* signed frame: signature not checked */ }
            byte[] pl = new byte[len];
            System.arraycopy(buf, hdr, pl, 0, len);
            return new Msg(id, buf[v2 ? 5 : 3] & 0xff, buf[v2 ? 6 : 4] & 0xff, pl);
        }
        if (pos >= buf.length) pos = 0;
        return null;
    }
}
