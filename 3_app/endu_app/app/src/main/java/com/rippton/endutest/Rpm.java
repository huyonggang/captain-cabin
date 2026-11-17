package com.rippton.endutest;

/**
 * Open-loop rpm estimate from the Rogue R12 single-motor tank table (12.3 V, firmware 20251123,
 * left motor, file "单电机水槽电流转速测试 固件20251123（船型待确认）.xlsx"). Forward only was measured;
 * reverse is assumed symmetric (unverified). 1780 us row is a range (6100-6300), its midpoint is used.
 */
public final class Rpm {
    static final int[] PWM = {1500, 1549, 1550, 1560, 1570, 1580, 1590, 1600, 1610, 1620, 1630, 1640, 1650, 1660, 1670,
            1680, 1690, 1700, 1710, 1720, 1730, 1740, 1750, 1760, 1770, 1780, 1790, 1800};
    static final int[] RPM = {0, 0, 522, 732, 953, 1204, 1420, 1648, 1863, 2098, 2342, 2568, 2812, 3046, 3294,
            3530, 3774, 4033, 4283, 4548, 4790, 5086, 5332, 5634, 5900, 6200, 6500, 6800};
    static final float[] AMP = {0, 0, .10f, .16f, .20f, .23f, .26f, .31f, .38f, .44f, .48f, .56f, .64f, .69f, .81f,
            .91f, 1.01f, 1.15f, 1.30f, 1.50f, 1.69f, 1.89f, 2.15f, 2.45f, 2.78f, 3.1f, 3.5f, 4.1f};

    /** pct of capped range (0..100) -> PWM offset from trim (forward side), same mapping as firmware pct_to_pwm(). */
    static float pwm(float pct, float start, float max) { return pct < 0.5f ? 1500 : start + pct * 0.01f * (max - start); }
    static float interp(int[] x, float[] y, float v) {
        if (v <= x[0]) return y[0];
        for (int i = 1; i < x.length; i++) if (v <= x[i]) { float t = (v - x[i - 1]) / (float) (x[i] - x[i - 1]); return y[i - 1] + t * (y[i] - y[i - 1]); }
        return y[y.length - 1];
    }
    static float rpm(float pwm) { float[] r = new float[RPM.length]; for (int i = 0; i < r.length; i++) r[i] = RPM[i]; return interp(PWM, r, pwm); }
    static float amp(float pwm) { return interp(PWM, AMP, pwm); }
}
