/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --no-compress --font MiSans-Normal.ttf --symbols  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
电量低超时启关闭船锚菜单提示弹框删除存项不所有蓝牙无标记扳机键能通讯类型到达的当前备硬软件松开始速巡航抛仓自
任务传输进度指令失败功短长摇杆校准配对模式选择语言版本信息重置退出动两个一圈按下步保持回中完成简体文确定恢复
为默认设？！：取消字大小点断联正在发送已止手义固更新请试上后击 --format lvgl -o font_12.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef FONT_12
#define FONT_12 1
#endif

#if FONT_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfe, 0x40,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x12, 0x12, 0x14, 0x7f, 0x24, 0x24, 0xfe, 0x28,
    0x48, 0x48,

    /* U+0024 "$" */
    0x10, 0x73, 0x5c, 0x89, 0xe, 0x7, 0x9, 0x13,
    0x2d, 0xf0, 0x80,

    /* U+0025 "%" */
    0x61, 0x49, 0x25, 0x12, 0x86, 0x80, 0x40, 0x4c,
    0x49, 0x24, 0xa1, 0x80,

    /* U+0026 "&" */
    0x38, 0x44, 0x44, 0x4c, 0x30, 0x50, 0x8a, 0x86,
    0xc6, 0x7b,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x16, 0xaa, 0xa5,

    /* U+0029 ")" */
    0x29, 0x55, 0x5a,

    /* U+002A "*" */
    0x5f, 0xa0,

    /* U+002B "+" */
    0x21, 0x9, 0xf2, 0x10,

    /* U+002C "," */
    0xc0,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x11, 0x12, 0x22, 0x44, 0x44,

    /* U+0030 "0" */
    0x79, 0x28, 0x61, 0x86, 0x18, 0x61, 0x49, 0xc0,

    /* U+0031 "1" */
    0x74, 0x92, 0x49, 0x24,

    /* U+0032 "2" */
    0x39, 0x10, 0x41, 0x8, 0x21, 0x8, 0x43, 0xf0,

    /* U+0033 "3" */
    0xf8, 0x21, 0x8, 0x38, 0x30, 0x41, 0xcd, 0xe0,

    /* U+0034 "4" */
    0x18, 0x62, 0x8a, 0x49, 0x28, 0xbf, 0x8, 0x20,

    /* U+0035 "5" */
    0xfb, 0xc, 0x20, 0xbb, 0x30, 0x41, 0xcd, 0xe0,

    /* U+0036 "6" */
    0x10, 0x82, 0x10, 0xfb, 0x38, 0x61, 0xcd, 0xe0,

    /* U+0037 "7" */
    0xf8, 0x44, 0x21, 0x10, 0x88, 0x42, 0x0,

    /* U+0038 "8" */
    0x7b, 0x38, 0x73, 0x33, 0x38, 0x61, 0xcd, 0xe0,

    /* U+0039 "9" */
    0x7b, 0x38, 0x61, 0xcd, 0xf0, 0x84, 0x10, 0x80,

    /* U+003A ":" */
    0x82,

    /* U+003B ";" */
    0x83, 0x0,

    /* U+003C "<" */
    0xc, 0xcc, 0x30, 0x30, 0x20, 0x40,

    /* U+003D "=" */
    0xf8, 0x1, 0xf0,

    /* U+003E ">" */
    0xc0, 0xc1, 0x82, 0x33, 0x0, 0x0,

    /* U+003F "?" */
    0x74, 0x42, 0x11, 0x10, 0x80, 0x1, 0x0,

    /* U+0040 "@" */
    0x1e, 0x31, 0x90, 0x73, 0xda, 0x2d, 0x16, 0x74,
    0x80, 0x60, 0xf, 0x0,

    /* U+0041 "A" */
    0x18, 0x18, 0x18, 0x2c, 0x24, 0x24, 0x7e, 0x42,
    0x42, 0x81,

    /* U+0042 "B" */
    0xfa, 0x38, 0x63, 0xf2, 0x38, 0x61, 0x8f, 0xe0,

    /* U+0043 "C" */
    0x3c, 0x87, 0x4, 0x8, 0x10, 0x20, 0x60, 0x62,
    0x78,

    /* U+0044 "D" */
    0xf9, 0x1a, 0x1c, 0x18, 0x30, 0x60, 0xc3, 0x8d,
    0xf0,

    /* U+0045 "E" */
    0xfe, 0x8, 0x20, 0xfa, 0x8, 0x20, 0x83, 0xf0,

    /* U+0046 "F" */
    0xfc, 0x21, 0x8, 0x7e, 0x10, 0x84, 0x0,

    /* U+0047 "G" */
    0x3c, 0x8f, 0x4, 0x8, 0x11, 0xe0, 0xe1, 0x46,
    0x78,

    /* U+0048 "H" */
    0x83, 0x6, 0xc, 0x1f, 0xf0, 0x60, 0xc1, 0x83,
    0x4,

    /* U+0049 "I" */
    0xff, 0xc0,

    /* U+004A "J" */
    0x8, 0x42, 0x10, 0x84, 0x21, 0x4b, 0x80,

    /* U+004B "K" */
    0x85, 0x12, 0x45, 0xc, 0x14, 0x24, 0x4c, 0x89,
    0x8,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x83, 0xf0,

    /* U+004D "M" */
    0x80, 0xe0, 0xf0, 0x74, 0x5a, 0x6c, 0xa6, 0x63,
    0x11, 0x80, 0xc0, 0x40,

    /* U+004E "N" */
    0x83, 0x87, 0x8d, 0x19, 0x32, 0x62, 0xc7, 0x87,
    0x4,

    /* U+004F "O" */
    0x3c, 0x42, 0xc3, 0x81, 0x81, 0x81, 0x81, 0xc3,
    0x42, 0x3c,

    /* U+0050 "P" */
    0xfa, 0x38, 0x61, 0x8f, 0xe8, 0x20, 0x82, 0x0,

    /* U+0051 "Q" */
    0x3c, 0x42, 0xc3, 0x81, 0x81, 0x81, 0x81, 0xc7,
    0x46, 0x3e, 0x1,

    /* U+0052 "R" */
    0xfa, 0x38, 0x61, 0x8f, 0xe9, 0x22, 0x8a, 0x10,

    /* U+0053 "S" */
    0x7b, 0x38, 0x20, 0x60, 0x60, 0x41, 0x8d, 0xe0,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20,

    /* U+0055 "U" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x44,
    0x70,

    /* U+0056 "V" */
    0x81, 0x42, 0x42, 0x42, 0x24, 0x24, 0x24, 0x18,
    0x18, 0x18,

    /* U+0057 "W" */
    0x84, 0x28, 0xc5, 0x18, 0xa5, 0x24, 0xa4, 0x92,
    0x8a, 0x51, 0x8a, 0x30, 0x86, 0x10,

    /* U+0058 "X" */
    0x42, 0x88, 0x91, 0xc1, 0x3, 0xa, 0x12, 0x45,
    0x84,

    /* U+0059 "Y" */
    0x82, 0x89, 0x11, 0x42, 0x82, 0x4, 0x8, 0x10,
    0x20,

    /* U+005A "Z" */
    0xfc, 0x10, 0x84, 0x10, 0x82, 0x10, 0x83, 0xf0,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x70,

    /* U+005C "\\" */
    0x84, 0x44, 0x42, 0x22, 0x31,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0xf0,

    /* U+005E "^" */
    0x21, 0x94, 0x90,

    /* U+005F "_" */
    0xf8,

    /* U+0060 "`" */
    0x48, 0x0,

    /* U+0061 "a" */
    0x70, 0x42, 0xf8, 0xcd, 0xa0,

    /* U+0062 "b" */
    0x82, 0x8, 0x2e, 0xce, 0x18, 0x61, 0xce, 0xe0,

    /* U+0063 "c" */
    0x7e, 0x61, 0x8, 0x65, 0xc0,

    /* U+0064 "d" */
    0x4, 0x10, 0x5d, 0xce, 0x18, 0x61, 0xcd, 0xd0,

    /* U+0065 "e" */
    0x7b, 0x38, 0x7f, 0x83, 0x17, 0x80,

    /* U+0066 "f" */
    0x34, 0x4f, 0x44, 0x44, 0x44,

    /* U+0067 "g" */
    0x77, 0x38, 0x61, 0x87, 0x37, 0x41, 0xcd, 0xe0,

    /* U+0068 "h" */
    0x84, 0x21, 0x6c, 0xc6, 0x31, 0x8c, 0x40,

    /* U+0069 "i" */
    0x9f, 0xc0,

    /* U+006A "j" */
    0x20, 0x12, 0x49, 0x24, 0x9e,

    /* U+006B "k" */
    0x84, 0x21, 0x3b, 0x73, 0x94, 0x94, 0x40,

    /* U+006C "l" */
    0xaa, 0xaa, 0xb0,

    /* U+006D "m" */
    0xb7, 0x66, 0x62, 0x31, 0x18, 0x8c, 0x46, 0x22,

    /* U+006E "n" */
    0xb6, 0x63, 0x18, 0xc6, 0x20,

    /* U+006F "o" */
    0x7b, 0x38, 0x61, 0x87, 0x37, 0x80,

    /* U+0070 "p" */
    0xbb, 0x38, 0x61, 0x87, 0x3b, 0xa0, 0x82, 0x0,

    /* U+0071 "q" */
    0x77, 0x38, 0x61, 0x87, 0x37, 0x41, 0x4, 0x10,

    /* U+0072 "r" */
    0xbc, 0x88, 0x88, 0x80,

    /* U+0073 "s" */
    0x74, 0x60, 0xe0, 0xc5, 0xc0,

    /* U+0074 "t" */
    0x44, 0xf4, 0x44, 0x44, 0x70,

    /* U+0075 "u" */
    0x8c, 0x63, 0x18, 0xcd, 0xa0,

    /* U+0076 "v" */
    0x85, 0x24, 0x92, 0x30, 0xc3, 0x0,

    /* U+0077 "w" */
    0x88, 0xc6, 0x55, 0x2a, 0xa5, 0x51, 0x98, 0x88,

    /* U+0078 "x" */
    0x49, 0x23, 0x8, 0x31, 0x2c, 0x80,

    /* U+0079 "y" */
    0x85, 0x14, 0x92, 0x30, 0xc3, 0x8, 0x20, 0x80,

    /* U+007A "z" */
    0xf8, 0xc4, 0x44, 0x63, 0xe0,

    /* U+007B "{" */
    0x29, 0x24, 0xa2, 0x49, 0x10,

    /* U+007C "|" */
    0xff, 0xf0,

    /* U+007D "}" */
    0x89, 0x24, 0x8a, 0x49, 0x40,

    /* U+007E "~" */
    0xc9, 0x80,

    /* U+4E00 "一" */
    0xff, 0xe0,

    /* U+4E0A "上" */
    0x8, 0x2, 0x0, 0x80, 0x3f, 0x8, 0x2, 0x0,
    0x80, 0x20, 0x8, 0x3f, 0xf0,

    /* U+4E0B "下" */
    0xff, 0xc2, 0x0, 0x80, 0x38, 0x9, 0x2, 0x20,
    0x80, 0x20, 0x8, 0x2, 0x0,

    /* U+4E0D "不" */
    0xff, 0xc1, 0x0, 0x80, 0x20, 0x1a, 0xa, 0x44,
    0x8a, 0x21, 0x8, 0x2, 0x0, 0x80,

    /* U+4E24 "两" */
    0xff, 0xc4, 0x81, 0x21, 0xfe, 0x92, 0xa4, 0xaa,
    0xea, 0x96, 0x48, 0xa0, 0x28, 0x38,

    /* U+4E2A "个" */
    0x4, 0x1, 0x40, 0x44, 0x10, 0x44, 0x45, 0x8,
    0x41, 0x0, 0x20, 0x4, 0x0, 0x80, 0x10, 0x0,

    /* U+4E2D "中" */
    0x8, 0x4, 0x3f, 0xf1, 0x18, 0x8c, 0x47, 0xfe,
    0x10, 0x8, 0x4, 0x2, 0x0,

    /* U+4E3A "为" */
    0x24, 0x9, 0x0, 0x41, 0xff, 0x4, 0x42, 0x90,
    0xa4, 0x25, 0x10, 0x48, 0x14, 0x3c,

    /* U+4E49 "义" */
    0x8, 0x12, 0x24, 0x50, 0x84, 0x21, 0x4, 0x80,
    0xc0, 0x30, 0x12, 0x18, 0x68, 0x4,

    /* U+4ED3 "仓" */
    0xc, 0x2, 0x81, 0x11, 0x82, 0xbf, 0x48, 0x42,
    0x10, 0x9c, 0x20, 0x48, 0x13, 0xf8,

    /* U+4EE4 "令" */
    0xc, 0x3, 0x40, 0xc4, 0x22, 0x68, 0x40, 0xff,
    0x0, 0x61, 0x98, 0x1e, 0x0, 0xc0, 0x0, 0x0,

    /* U+4EF6 "件" */
    0x11, 0x4, 0xa0, 0x9f, 0x94, 0x86, 0x91, 0x42,
    0xb, 0xf9, 0x8, 0x21, 0x4, 0x20, 0x84, 0x0,

    /* U+4EFB "任" */
    0x10, 0x65, 0xf0, 0x84, 0x10, 0x86, 0x11, 0x5f,
    0xc8, 0x41, 0x8, 0x21, 0x5, 0xfc, 0x80, 0x0,

    /* U+4F20 "传" */
    0x12, 0x2, 0x40, 0xbf, 0x91, 0x6, 0x20, 0xdf,
    0xe9, 0x1, 0x3e, 0x20, 0x45, 0x90, 0x8e, 0x10,
    0x20,

    /* U+4F4E "低" */
    0x0, 0x2, 0x7c, 0xb2, 0x14, 0x46, 0x88, 0xdf,
    0xea, 0x21, 0x44, 0x28, 0x85, 0x6c, 0xb9, 0x94,
    0xa0,

    /* U+4F53 "体" */
    0x11, 0x1, 0x10, 0x2f, 0xe2, 0x38, 0x63, 0x8a,
    0x54, 0x25, 0x42, 0x92, 0x37, 0xc2, 0x10, 0x21,
    0x0,

    /* U+4FDD "保" */
    0x0, 0x3, 0xf8, 0xa1, 0x14, 0x22, 0xfc, 0xc2,
    0x28, 0x41, 0x7f, 0x23, 0x84, 0xb0, 0xa5, 0x90,
    0x80,

    /* U+4FE1 "信" */
    0x24, 0x17, 0xf4, 0x1, 0x7e, 0xc0, 0x37, 0xe4,
    0x1, 0x7e, 0x50, 0x97, 0xe5, 0x8,

    /* U+5173 "关" */
    0x1, 0x8, 0x41, 0x21, 0xfe, 0x8, 0x2, 0xf,
    0xfc, 0x30, 0xc, 0x4, 0x86, 0x1a, 0x1,

    /* U+51C6 "准" */
    0xa, 0x24, 0x89, 0xfd, 0xc8, 0x5f, 0xd4, 0x85,
    0xfe, 0x48, 0x92, 0x27, 0xf1, 0x0,

    /* U+51FA "出" */
    0x8, 0x44, 0x62, 0x31, 0x1f, 0xf8, 0x40, 0x21,
    0x11, 0x88, 0xff, 0xc0, 0x20,

    /* U+51FB "击" */
    0x8, 0x2, 0x7, 0xf8, 0x20, 0x8, 0x3f, 0xf0,
    0x81, 0x22, 0x48, 0x9f, 0xe0, 0x8,

    /* U+5220 "删" */
    0x6c, 0x6b, 0x5a, 0xd6, 0xb5, 0xff, 0x6b, 0x5a,
    0xd6, 0xb5, 0xb4, 0x6d, 0x1f, 0x5c,

    /* U+5230 "到" */
    0xfc, 0x48, 0x94, 0xa6, 0x29, 0xfe, 0x48, 0x9f,
    0xe4, 0x89, 0x20, 0x7f, 0x10, 0x1c,

    /* U+524D "前" */
    0x0, 0x2, 0x23, 0xff, 0x80, 0x0, 0x4, 0xf4,
    0x92, 0x93, 0xd2, 0x4a, 0x4f, 0x49, 0x21, 0x2c,
    0xe0,

    /* U+529F "功" */
    0x2, 0x3c, 0x84, 0xfd, 0x9, 0x42, 0x50, 0x94,
    0x25, 0x59, 0xe4, 0x42, 0x11, 0x9c,

    /* U+52A1 "务" */
    0x10, 0xf, 0xe6, 0x12, 0x78, 0x73, 0xa4, 0x1f,
    0xf8, 0x42, 0x10, 0x88, 0x2c, 0x70,

    /* U+52A8 "动" */
    0x2, 0x3e, 0x80, 0x7c, 0x9, 0xfa, 0x48, 0x95,
    0x25, 0x49, 0x8e, 0x7f, 0x10, 0x5c,

    /* U+5355 "单" */
    0x21, 0x4, 0x87, 0xf9, 0x22, 0x48, 0x9f, 0xe4,
    0x89, 0xfe, 0x8, 0x3f, 0xf0, 0x80, 0x20,

    /* U+53D1 "发" */
    0x48, 0x89, 0x1, 0xff, 0x84, 0x1, 0x0, 0x3f,
    0x86, 0x21, 0x24, 0x27, 0x8, 0xe2, 0xe3, 0x80,

    /* U+53D6 "取" */
    0xf8, 0x25, 0xf9, 0x45, 0xca, 0x92, 0x9c, 0xa9,
    0x1a, 0x44, 0xfa, 0x85, 0x91, 0x40,

    /* U+540E "后" */
    0x0, 0x9f, 0xc4, 0x1, 0xff, 0x40, 0x10, 0x5,
    0xf9, 0x42, 0xd0, 0xa7, 0xe9, 0x8,

    /* U+542F "启" */
    0x4, 0x3f, 0xd0, 0x28, 0x17, 0xfa, 0x1, 0x7e,
    0xc1, 0xa0, 0xcf, 0xc8, 0x20,

    /* U+56DE "回" */
    0xff, 0xc0, 0x60, 0x37, 0xda, 0x2d, 0x16, 0xfb,
    0x1, 0x80, 0xff, 0xe0, 0x20,

    /* U+56FA "固" */
    0xff, 0xe0, 0x18, 0x87, 0xfd, 0x88, 0x6f, 0x9a,
    0x26, 0xf9, 0x80, 0x7f, 0xf8, 0x4,

    /* U+5708 "圈" */
    0xff, 0xe1, 0x59, 0xa6, 0xb5, 0xff, 0xe4, 0x9b,
    0xf6, 0x57, 0x9f, 0x60, 0x1f, 0xfc,

    /* U+5728 "在" */
    0x8, 0x4, 0xf, 0xfc, 0x40, 0x22, 0x8, 0x85,
    0xff, 0x8, 0x42, 0x10, 0x85, 0xfd, 0x0,

    /* U+578B "型" */
    0xfe, 0x92, 0xa4, 0xab, 0xfa, 0x48, 0x92, 0x68,
    0x91, 0xfe, 0x8, 0x2, 0xf, 0xfc,

    /* U+5907 "备" */
    0x10, 0x7, 0xf9, 0x82, 0x4d, 0x81, 0xf1, 0xc1,
    0xdf, 0xf2, 0x22, 0x7f, 0xcf, 0xf9, 0x1, 0x0,

    /* U+590D "复" */
    0x10, 0x7, 0xfd, 0x0, 0x5f, 0xe3, 0xfc, 0x40,
    0x87, 0xe0, 0xfe, 0x78, 0x80, 0xe1, 0xe3, 0x80,

    /* U+5927 "大" */
    0x8, 0x2, 0x0, 0x83, 0xff, 0x8, 0x3, 0x0,
    0xc0, 0x48, 0x31, 0x10, 0x28, 0x4,

    /* U+5931 "失" */
    0x4, 0x9, 0x7, 0xf9, 0x10, 0x4, 0x3f, 0xf0,
    0xc0, 0x30, 0x12, 0x18, 0x68, 0x4,

    /* U+59CB "始" */
    0x42, 0x8, 0x53, 0xd1, 0x2f, 0xe5, 0x3, 0x20,
    0x29, 0xf3, 0x22, 0x54, 0x48, 0xfa, 0x11, 0x0,

    /* U+5B57 "字" */
    0x8, 0x1, 0xf, 0xfe, 0x1, 0xbf, 0x40, 0x80,
    0x43, 0xff, 0x4, 0x1, 0x0, 0x40, 0x60,

    /* U+5B58 "存" */
    0x10, 0x3f, 0xf1, 0x0, 0xbe, 0x41, 0xb0, 0x8d,
    0xfd, 0x8, 0x42, 0x10, 0x84, 0xe0,

    /* U+5B8C "完" */
    0x4, 0x3f, 0xf8, 0x4, 0xfc, 0x0, 0x0, 0xf,
    0xfc, 0x48, 0x12, 0x48, 0x9c, 0x3c,

    /* U+5B9A "定" */
    0x4, 0x7, 0xfe, 0x40, 0x20, 0x0, 0x7f, 0xe0,
    0x40, 0x27, 0xc2, 0x40, 0x24, 0x5, 0x40, 0x4f,
    0xe0, 0x0,

    /* U+5BF9 "对" */
    0x0, 0xbc, 0x21, 0xfe, 0x42, 0x60, 0x99, 0x22,
    0x29, 0x42, 0x50, 0xa0, 0x20, 0x38,

    /* U+5C0F "小" */
    0x4, 0x0, 0x80, 0x94, 0x12, 0x42, 0x48, 0x88,
    0x91, 0x14, 0x22, 0x84, 0x20, 0x80, 0x70, 0x0,

    /* U+5DE1 "巡" */
    0x88, 0x52, 0x90, 0xa8, 0x52, 0xd5, 0x15, 0x25,
    0x29, 0x29, 0x49, 0x68, 0x9, 0xfc,

    /* U+5DF2 "已" */
    0xff, 0x80, 0x24, 0x9, 0x2, 0x7f, 0x90, 0x4,
    0x1, 0x1, 0x40, 0x50, 0x17, 0xfc,

    /* U+5EA6 "度" */
    0x2, 0xf, 0xfd, 0x22, 0x3f, 0xf4, 0x88, 0x8e,
    0x17, 0xf2, 0x44, 0x45, 0x13, 0xf2, 0x81, 0x80,

    /* U+5F00 "开" */
    0xff, 0xc2, 0x20, 0x44, 0x8, 0x81, 0x11, 0xff,
    0xc4, 0x40, 0x88, 0x21, 0x4, 0x23, 0x4, 0x0,

    /* U+5F0F "式" */
    0x5, 0x1, 0x2f, 0xfc, 0x8, 0x2, 0x3e, 0x82,
    0x20, 0x88, 0x22, 0x7e, 0x50, 0x18,

    /* U+5F39 "弹" */
    0x8, 0x9c, 0xa0, 0xbf, 0x15, 0x2e, 0xa5, 0x1f,
    0xa2, 0x97, 0x7e, 0x22, 0x7, 0xfc, 0x88, 0x71,
    0x0,

    /* U+5F53 "当" */
    0x8, 0xa4, 0xda, 0x41, 0xf, 0xf8, 0x7, 0xfe,
    0x1, 0x0, 0xff, 0xc0, 0x20,

    /* U+6062 "恢" */
    0x24, 0x5, 0xfd, 0xd0, 0x52, 0x8a, 0x53, 0x4e,
    0x8a, 0xf1, 0x4c, 0x32, 0x84, 0x48, 0xb0, 0x80,

    /* U+606F "息" */
    0x8, 0xf, 0xf1, 0x2, 0x3f, 0xc4, 0x8, 0xff,
    0x1f, 0xe0, 0x40, 0xa5, 0x54, 0x2a, 0x7c, 0x0,

    /* U+6210 "成" */
    0x2, 0x80, 0x49, 0xff, 0xa1, 0x7, 0xa4, 0x95,
    0x12, 0x62, 0x49, 0x7b, 0x30, 0x9a, 0x13, 0x0,

    /* U+6240 "所" */
    0x18, 0xd8, 0xc4, 0x21, 0xe8, 0x4b, 0xd2, 0xa7,
    0xc9, 0x12, 0x44, 0xb1, 0x28, 0x48,

    /* U+624B "手" */
    0x0, 0xcf, 0xc0, 0x10, 0x2, 0x7, 0xfc, 0x8,
    0x3f, 0xf8, 0x20, 0x4, 0x0, 0x80, 0x70, 0x0,

    /* U+6273 "扳" */
    0x20, 0xc9, 0x4f, 0x80, 0x9f, 0x2c, 0x9e, 0xaa,
    0xa8, 0xa4, 0x29, 0xc, 0xad, 0x44,

    /* U+629B "抛" */
    0x51, 0xa, 0x23, 0xf7, 0x2a, 0xa5, 0x55, 0xea,
    0x95, 0x92, 0xb7, 0x54, 0x2a, 0x87, 0x9f, 0x80,

    /* U+62E9 "择" */
    0x4f, 0x92, 0x2e, 0x59, 0x1c, 0x5d, 0xd8, 0x8d,
    0xfd, 0x8, 0x5f, 0xd0, 0x8c, 0x20,

    /* U+6301 "持" */
    0x42, 0x13, 0xfe, 0x21, 0x8, 0x5f, 0xd8, 0x2d,
    0xfd, 0x2, 0x48, 0x90, 0x2c, 0x70,

    /* U+6307 "指" */
    0x50, 0x2b, 0xfe, 0x29, 0x14, 0x76, 0x7d, 0x42,
    0x9f, 0x50, 0xa7, 0xf4, 0x20,

    /* U+6309 "按" */
    0x42, 0x17, 0xff, 0x5, 0x10, 0x44, 0x1f, 0xfc,
    0x89, 0x24, 0x47, 0x11, 0x6d, 0x84,

    /* U+63D0 "提" */
    0x4f, 0x94, 0x2e, 0xf9, 0x42, 0x4f, 0x98, 0xc,
    0xf9, 0x4f, 0x5a, 0x16, 0x8e, 0x7c,

    /* U+6447 "摇" */
    0x5f, 0xd0, 0x9f, 0x29, 0x2, 0x6f, 0xf4, 0x85,
    0xfd, 0x8, 0x52, 0x54, 0x9d, 0xfc,

    /* U+6587 "文" */
    0x8, 0x1, 0xf, 0xfc, 0x84, 0x21, 0x4, 0x81,
    0x20, 0x30, 0xc, 0xc, 0xcc, 0xc,

    /* U+65AD "断" */
    0x90, 0xdb, 0x42, 0xe8, 0x49, 0xf, 0xbf, 0x25,
    0x2e, 0xa6, 0x94, 0x92, 0x9f, 0x90, 0x12, 0x0,

    /* U+65B0 "新" */
    0x20, 0x7f, 0xb1, 0x28, 0x25, 0xf, 0xde, 0x44,
    0xbf, 0x91, 0x52, 0x6a, 0x54, 0x49, 0x91, 0x0,

    /* U+65E0 "无" */
    0x7f, 0x82, 0x0, 0x80, 0x20, 0xff, 0xc2, 0x1,
    0x40, 0x50, 0x24, 0x59, 0x1c, 0x7c,

    /* U+65F6 "时" */
    0x0, 0xbc, 0x29, 0xfe, 0x42, 0x94, 0xbd, 0x29,
    0x2a, 0x42, 0xf0, 0xa0, 0x20, 0x38,

    /* U+66F4 "更" */
    0xff, 0xc2, 0x7, 0xf9, 0x22, 0x7f, 0x92, 0x27,
    0xf8, 0x20, 0x28, 0x7, 0xe, 0x3c,

    /* U+6709 "有" */
    0x8, 0x4, 0xf, 0xfc, 0x80, 0x3f, 0x98, 0x2b,
    0xf8, 0x82, 0x3f, 0x88, 0x22, 0x8, 0x8c,

    /* U+672C "本" */
    0x8, 0x2, 0xf, 0xfc, 0x50, 0x1a, 0xa, 0x82,
    0x91, 0x22, 0xbf, 0x42, 0x0, 0x80,

    /* U+673A "机" */
    0x47, 0x88, 0x93, 0xd2, 0x22, 0x46, 0x49, 0xa9,
    0x31, 0x26, 0x45, 0x48, 0xa9, 0x15, 0x43, 0x80,

    /* U+6746 "杆" */
    0x40, 0x8, 0xfb, 0xc4, 0x20, 0x84, 0x11, 0x7f,
    0xf4, 0x46, 0x8, 0x41, 0x8, 0x21, 0x4, 0x0,

    /* U+677E "松" */
    0x41, 0x8, 0x93, 0xd2, 0x24, 0x26, 0xa5, 0xa4,
    0x30, 0x86, 0x24, 0x44, 0x89, 0xf9, 0x1, 0x0,

    /* U+6807 "标" */
    0x20, 0x4, 0xf8, 0x80, 0x78, 0x6, 0xfe, 0xc2,
    0x2d, 0x55, 0x2a, 0x29, 0x25, 0x24, 0x9c, 0x0,

    /* U+6821 "校" */
    0x21, 0x5, 0xff, 0xc0, 0x32, 0x46, 0x45, 0x79,
    0x68, 0xa1, 0x18, 0x23, 0x4, 0x98, 0xa1, 0x80,

    /* U+6846 "框" */
    0x4f, 0xd4, 0xf, 0x7d, 0x44, 0x51, 0x3d, 0xfd,
    0x11, 0x5f, 0x50, 0x13, 0xf4, 0x0,

    /* U+6A21 "模" */
    0x45, 0x17, 0xfe, 0x1, 0x7e, 0x4f, 0xbc, 0x2c,
    0xf1, 0x7f, 0x42, 0x11, 0x47, 0x8c,

    /* U+6B62 "止" */
    0x4, 0x1, 0x2, 0x40, 0x9f, 0x24, 0x9, 0x2,
    0x40, 0x90, 0x24, 0x3f, 0xf0,

    /* U+6B63 "正" */
    0x7f, 0xc1, 0x2, 0x40, 0x90, 0x27, 0xc9, 0x2,
    0x40, 0x90, 0xff, 0xc0,

    /* U+6B65 "步" */
    0x4, 0x4, 0xf8, 0x90, 0x12, 0xf, 0xfe, 0x8,
    0xd, 0x13, 0x24, 0x3, 0x3, 0x83, 0x80, 0x0,

    /* U+6D88 "消" */
    0x41, 0x5, 0x24, 0x15, 0x27, 0xf2, 0x82, 0x1f,
    0xca, 0x9, 0x7f, 0x48, 0x29, 0x5, 0x23, 0x80,

    /* U+70B9 "点" */
    0x8, 0x3, 0xf0, 0x81, 0xfe, 0x40, 0x90, 0x27,
    0xf8, 0x2, 0x54, 0xa4, 0x98, 0x0,

    /* U+7248 "版" */
    0x50, 0xea, 0xe1, 0x50, 0x3f, 0xe4, 0x64, 0x8c,
    0x9d, 0x52, 0xac, 0x54, 0x8b, 0x2a, 0x78, 0x80,

    /* U+7259 "牙" */
    0xff, 0xc0, 0x84, 0x21, 0x8, 0x7f, 0xc1, 0x80,
    0xa0, 0x48, 0x22, 0x30, 0x80, 0xe0,

    /* U+7535 "电" */
    0x8, 0x3f, 0xe8, 0x8a, 0x22, 0xff, 0xa2, 0x28,
    0x8b, 0xff, 0x8, 0x42, 0x10, 0xfc,

    /* U+7684 "的" */
    0x42, 0x10, 0x8f, 0x7e, 0x71, 0x94, 0x7c, 0x99,
    0x16, 0x41, 0x90, 0x7c, 0x18, 0x3c,

    /* U+77ED "短" */
    0x40, 0x9, 0xfd, 0xc0, 0x50, 0xa, 0x7c, 0x48,
    0x99, 0xf1, 0x0, 0x64, 0x8a, 0x51, 0x2, 0x47,
    0xf0, 0x0,

    /* U+786C "硬" */
    0xf, 0xfe, 0x21, 0x4, 0x27, 0xe7, 0x7d, 0xb2,
    0x95, 0xf2, 0xa8, 0x72, 0x8, 0xf0, 0x63, 0x0,

    /* U+786E "确" */
    0x2, 0x3d, 0xe4, 0xc9, 0x3f, 0x69, 0x79, 0xfe,
    0x95, 0xa5, 0x6f, 0xda, 0x54, 0x9c,

    /* U+793A "示" */
    0x7f, 0x80, 0x0, 0x0, 0x0, 0xff, 0xc1, 0x2,
    0x51, 0x12, 0x44, 0xa1, 0x11, 0x80,

    /* U+7B80 "简" */
    0x21, 0xf, 0xff, 0x52, 0x17, 0xe2, 0x4, 0xbe,
    0x94, 0x52, 0xfa, 0x5f, 0x48, 0x9, 0x7, 0x0,

    /* U+7C7B "类" */
    0x48, 0x8a, 0x4f, 0xfc, 0x70, 0x3b, 0xb0, 0x30,
    0x83, 0xff, 0xc, 0x4, 0x8e, 0x1c,

    /* U+7F6E "置" */
    0x7f, 0xc9, 0x48, 0xd6, 0x7f, 0xf0, 0x40, 0x77,
    0xf, 0xe1, 0xfc, 0x3f, 0x84, 0x13, 0xff, 0x80,

    /* U+8054 "联" */
    0x4, 0x5e, 0x8a, 0x8a, 0x57, 0xf6, 0x11, 0x42,
    0x1b, 0xfd, 0x8, 0xa2, 0x9e, 0x50, 0x91, 0x14,
    0x10,

    /* U+80FD "能" */
    0x44, 0x29, 0x6f, 0x64, 0x11, 0xf7, 0xe4, 0xf,
    0x5b, 0xd9, 0x94, 0x65, 0x1b, 0x7c,

    /* U+81EA "自" */
    0x10, 0x10, 0xff, 0x81, 0x81, 0xff, 0x81, 0xff,
    0x81, 0x81, 0xff, 0x81,

    /* U+822A "航" */
    0x21, 0x7, 0x88, 0x4f, 0xe6, 0x80, 0x4b, 0xc7,
    0xa4, 0x4a, 0x46, 0xa4, 0x4a, 0x54, 0xa5, 0xbc,
    0x60,

    /* U+8239 "船" */
    0x20, 0x4, 0x39, 0xe9, 0x25, 0x25, 0xa4, 0x90,
    0x5e, 0xfb, 0x51, 0x5a, 0x29, 0x45, 0x2f, 0xdd,
    0x10,

    /* U+83DC "菜" */
    0x12, 0x3f, 0xf1, 0x23, 0xfe, 0x48, 0x89, 0x4f,
    0xfc, 0x30, 0x3b, 0x32, 0x30, 0x80,

    /* U+84DD "蓝" */
    0x12, 0x3f, 0xf1, 0x21, 0x4f, 0x54, 0x16, 0x60,
    0x1, 0xfe, 0x52, 0x94, 0xaf, 0xfc,

    /* U+8A00 "言" */
    0x4, 0x1f, 0xfc, 0x0, 0x3f, 0xe0, 0x0, 0xff,
    0x80, 0x3, 0xfe, 0x40, 0x4f, 0xf9, 0x1, 0x0,

    /* U+8BA4 "认" */
    0x82, 0x10, 0x82, 0x20, 0x8, 0xc2, 0x10, 0x84,
    0x51, 0x14, 0x6c, 0x92, 0x31, 0x4,

    /* U+8BAF "讯" */
    0x0, 0xb, 0xf1, 0x12, 0x2, 0x40, 0x49, 0x89,
    0x17, 0xe2, 0x24, 0x44, 0x88, 0x95, 0x92, 0xa2,
    0x20,

    /* U+8BB0 "记" */
    0x0, 0x17, 0xe4, 0x8, 0x2, 0xc0, 0x93, 0xe4,
    0x81, 0x20, 0x48, 0x5a, 0x16, 0x85, 0x3e,

    /* U+8BBE "设" */
    0x47, 0x8c, 0x90, 0x12, 0x4, 0x7c, 0x0, 0x9f,
    0x92, 0x12, 0x24, 0x53, 0xc, 0xf0, 0x61, 0x80,

    /* U+8BD5 "试" */
    0x81, 0x8, 0x28, 0x7f, 0x80, 0x8c, 0x10, 0xba,
    0x12, 0x42, 0x48, 0x69, 0x2b, 0xd4, 0x3, 0x0,

    /* U+8BED "语" */
    0x5f, 0xd9, 0x1, 0xf8, 0x12, 0xc8, 0x97, 0xf4,
    0x1, 0x3e, 0x68, 0x93, 0xe0, 0x88,

    /* U+8BF7 "请" */
    0x2, 0x17, 0xf1, 0xfc, 0x8, 0xdd, 0xd7, 0xe5,
    0x9, 0x7e, 0x7f, 0x94, 0x21, 0x18,

    /* U+8D25 "败" */
    0x1, 0xf, 0x21, 0x28, 0x25, 0xf6, 0xa4, 0xdc,
    0x9a, 0xa3, 0x4c, 0x31, 0x85, 0x79, 0x19, 0x80,

    /* U+8D85 "超" */
    0x27, 0xdf, 0x48, 0x89, 0x12, 0xef, 0x80, 0x4f,
    0x99, 0x12, 0xe2, 0x67, 0xd4, 0x2, 0xff, 0x80,

    /* U+8F6F "软" */
    0x22, 0x4, 0x43, 0xff, 0xb2, 0xaa, 0x95, 0xf2,
    0x8, 0x41, 0x14, 0xf2, 0x84, 0x88, 0xa0, 0x80,

    /* U+8F93 "输" */
    0x43, 0x8, 0x63, 0xd2, 0x4f, 0xfc, 0x1, 0x9e,
    0x9b, 0xd2, 0x5a, 0xef, 0x49, 0x49, 0x3b, 0x0,

    /* U+8FBE "达" */
    0x41, 0x4, 0x20, 0x3f, 0x80, 0x86, 0x10, 0x46,
    0x8, 0xa1, 0x22, 0x28, 0x2a, 0x1, 0x3f, 0x80,

    /* U+8FDB "进" */
    0x88, 0x92, 0x25, 0xfc, 0x22, 0xc8, 0x97, 0xf4,
    0x89, 0x22, 0x50, 0xa8, 0x9, 0xfc,

    /* U+9000 "退" */
    0x9f, 0x94, 0x21, 0xf8, 0x42, 0xdf, 0x94, 0x15,
    0x79, 0x44, 0x5c, 0xe8, 0x9, 0xfc,

    /* U+9001 "送" */
    0x88, 0x91, 0x45, 0xfc, 0x8, 0xc2, 0x17, 0xf4,
    0x21, 0x14, 0x58, 0xa8, 0x9, 0xfc,

    /* U+9009 "选" */
    0x2, 0x32, 0x84, 0xf8, 0x48, 0xdf, 0xd1, 0x44,
    0x55, 0x35, 0x59, 0xe8, 0x9, 0xfc,

    /* U+901A "通" */
    0x9f, 0x92, 0x41, 0xfb, 0x52, 0x5f, 0x95, 0x25,
    0xf9, 0x52, 0x55, 0xa8, 0x9, 0xfc,

    /* U+901F "速" */
    0x82, 0xb, 0xf9, 0x8, 0xf, 0xed, 0x24, 0xbf,
    0x91, 0x82, 0x5e, 0x52, 0x14, 0x2, 0x7f, 0x80,

    /* U+914D "配" */
    0xff, 0xcc, 0x13, 0x7, 0xf1, 0xb4, 0x6d, 0xec,
    0xe2, 0x18, 0xfe, 0x7f, 0x98, 0x3c,

    /* U+91CD "重" */
    0x7f, 0x82, 0xf, 0xfc, 0x20, 0x7f, 0x9f, 0xe4,
    0x88, 0xfc, 0x7f, 0x82, 0xf, 0xfc,

    /* U+91CF "量" */
    0x7f, 0xcf, 0xf9, 0x1, 0x1f, 0xcf, 0xfe, 0xff,
    0x9f, 0xf3, 0xfe, 0x7f, 0xc0, 0x83, 0xff, 0x80,

    /* U+951A "锚" */
    0x24, 0x8f, 0xfd, 0x12, 0x78, 0x7, 0xfc, 0x52,
    0xbf, 0xf1, 0x4a, 0x39, 0x45, 0xf8, 0x21, 0x0,

    /* U+952E "键" */
    0x9f, 0xfa, 0x59, 0x7f, 0x45, 0x9f, 0xe2, 0x4f,
    0xba, 0x7f, 0xa9, 0x16, 0x5, 0x7c,

    /* U+957F "长" */
    0x20, 0x88, 0xc2, 0xc0, 0x80, 0xff, 0xc9, 0x2,
    0x40, 0x88, 0x29, 0x8c, 0x30,

    /* U+95ED "闭" */
    0x0, 0x27, 0xc8, 0x20, 0x5b, 0xfc, 0x36, 0x2b,
    0x35, 0xb2, 0xd1, 0x63, 0x30, 0x30,

    /* U+9664 "除" */
    0xe3, 0x14, 0xa3, 0x22, 0x6b, 0xec, 0x21, 0x44,
    0x2f, 0xf5, 0x14, 0xea, 0x52, 0x4a, 0x18, 0x0,

    /* U+9879 "项" */
    0x1f, 0xfc, 0x41, 0x8, 0x27, 0xe5, 0x4, 0xa4,
    0x94, 0x92, 0x92, 0xe7, 0x1, 0x90, 0x41, 0x80,

    /* U+9ED8 "默" */
    0xf9, 0xaa, 0x5f, 0x96, 0xbf, 0xf9, 0x8, 0x4f,
    0x93, 0xea, 0xa, 0xb7, 0x18, 0x44,

    /* U+FF01 "！" */
    0xfc, 0x80,

    /* U+FF1A "：" */
    0x84,

    /* U+FF1F "？" */
    0x74, 0x42, 0x21, 0x10, 0x80, 0x1, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 68, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 50, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 64, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 5, .adv_w = 136, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 110, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 26, .adv_w = 157, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 37, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 49, .adv_w = 58, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 52, .adv_w = 58, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 55, .adv_w = 85, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 57, .adv_w = 116, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 61, .adv_w = 49, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 62, .adv_w = 75, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 63, .adv_w = 46, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 75, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 77, .adv_w = 75, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 108, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 99, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 46, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 49, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 147, .adv_w = 116, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 153, .adv_w = 116, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 156, .adv_w = 116, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 162, .adv_w = 94, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 158, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 126, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 127, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 109, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 141, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 241, .adv_w = 137, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 46, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 90, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 123, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 108, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 276, .adv_w = 167, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 140, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 150, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 119, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 150, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 326, .adv_w = 121, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 116, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 115, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 126, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 370, .adv_w = 184, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 118, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 410, .adv_w = 66, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 415, .adv_w = 65, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 66, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 425, .adv_w = 84, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 428, .adv_w = 87, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 429, .adv_w = 49, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 431, .adv_w = 102, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 102, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 457, .adv_w = 107, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 66, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 468, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 476, .adv_w = 111, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 483, .adv_w = 46, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 47, .box_w = 3, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 490, .adv_w = 97, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 497, .adv_w = 47, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 169, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 111, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 110, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 527, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 535, .adv_w = 72, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 539, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 67, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 549, .adv_w = 111, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 96, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 560, .adv_w = 151, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 93, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 574, .adv_w = 98, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 582, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 587, .adv_w = 67, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 592, .adv_w = 42, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 594, .adv_w = 67, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 599, .adv_w = 100, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 601, .adv_w = 192, .box_w = 11, .box_h = 1, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 603, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 629, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 643, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 657, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 673, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 686, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 700, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 714, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 728, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 744, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 760, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 776, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 793, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 810, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 827, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 844, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 858, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 873, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 887, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 900, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 914, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 928, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 942, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 959, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 973, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 987, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1001, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1016, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1032, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1046, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1060, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1073, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1086, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1100, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1114, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1129, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1143, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1159, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1175, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1189, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1203, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1219, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1234, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1248, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1262, .adv_w = 192, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1280, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1294, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1310, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1324, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1338, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1354, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1370, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1384, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1401, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1414, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1430, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1446, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1462, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1476, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1492, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1506, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1522, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1536, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1550, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1563, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1577, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1591, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1605, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1619, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1635, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1651, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1665, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1679, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1693, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1708, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1722, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1738, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1754, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1770, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1786, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1802, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1816, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1830, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1843, .adv_w = 192, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1855, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1871, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1887, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1901, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1917, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1931, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1945, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1959, .adv_w = 192, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1977, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1993, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2007, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2021, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2037, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2051, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2067, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2084, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2098, .adv_w = 192, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 2110, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2127, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2144, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2158, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2172, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2188, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2202, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2219, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2234, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2250, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2266, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2280, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2294, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2310, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2326, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2342, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2358, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2374, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2388, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2402, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2416, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2430, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2444, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2460, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2474, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2488, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2504, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2520, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2534, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2547, .adv_w = 192, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2561, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2577, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2593, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2607, .adv_w = 192, .box_w = 1, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2609, .adv_w = 192, .box_w = 1, .box_h = 6, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 2610, .adv_w = 192, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0xa, 0xb, 0xd, 0x24, 0x2a, 0x2d, 0x3a,
    0x49, 0xd3, 0xe4, 0xf6, 0xfb, 0x120, 0x14e, 0x153,
    0x1dd, 0x1e1, 0x373, 0x3c6, 0x3fa, 0x3fb, 0x420, 0x430,
    0x44d, 0x49f, 0x4a1, 0x4a8, 0x555, 0x5d1, 0x5d6, 0x60e,
    0x62f, 0x8de, 0x8fa, 0x908, 0x928, 0x98b, 0xb07, 0xb0d,
    0xb27, 0xb31, 0xbcb, 0xd57, 0xd58, 0xd8c, 0xd9a, 0xdf9,
    0xe0f, 0xfe1, 0xff2, 0x10a6, 0x1100, 0x110f, 0x1139, 0x1153,
    0x1262, 0x126f, 0x1410, 0x1440, 0x144b, 0x1473, 0x149b, 0x14e9,
    0x1501, 0x1507, 0x1509, 0x15d0, 0x1647, 0x1787, 0x17ad, 0x17b0,
    0x17e0, 0x17f6, 0x18f4, 0x1909, 0x192c, 0x193a, 0x1946, 0x197e,
    0x1a07, 0x1a21, 0x1a46, 0x1c21, 0x1d62, 0x1d63, 0x1d65, 0x1f88,
    0x22b9, 0x2448, 0x2459, 0x2735, 0x2884, 0x29ed, 0x2a6c, 0x2a6e,
    0x2b3a, 0x2d80, 0x2e7b, 0x316e, 0x3254, 0x32fd, 0x33ea, 0x342a,
    0x3439, 0x35dc, 0x36dd, 0x3c00, 0x3da4, 0x3daf, 0x3db0, 0x3dbe,
    0x3dd5, 0x3ded, 0x3df7, 0x3f25, 0x3f85, 0x416f, 0x4193, 0x41be,
    0x41db, 0x4200, 0x4201, 0x4209, 0x421a, 0x421f, 0x434d, 0x43cd,
    0x43cf, 0x471a, 0x472e, 0x477f, 0x47ed, 0x4864, 0x4a79, 0x50d8,
    0xb101, 0xb11a, 0xb11f
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 19968, .range_length = 45344, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 139, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    7, 36,
    7, 40,
    7, 43,
    7, 48,
    7, 50,
    7, 53,
    7, 54,
    7, 55,
    7, 56,
    7, 58,
    7, 66,
    7, 68,
    7, 69,
    7, 70,
    7, 71,
    7, 72,
    7, 77,
    7, 80,
    7, 82,
    7, 85,
    7, 87,
    7, 88,
    7, 90,
    13, 18,
    13, 21,
    13, 26,
    15, 18,
    15, 21,
    15, 26,
    16, 21,
    16, 23,
    17, 19,
    17, 24,
    19, 17,
    19, 20,
    19, 21,
    19, 23,
    20, 19,
    20, 26,
    21, 20,
    21, 24,
    21, 26,
    23, 18,
    23, 24,
    23, 26,
    24, 13,
    24, 15,
    24, 16,
    24, 17,
    24, 21,
    24, 23,
    24, 25,
    25, 24,
    25, 26,
    26, 13,
    26, 15,
    26, 16,
    26, 21,
    26, 23,
    26, 25,
    34, 7,
    34, 36,
    34, 40,
    34, 48,
    34, 50,
    34, 53,
    34, 54,
    34, 55,
    34, 56,
    34, 58,
    34, 68,
    34, 69,
    34, 70,
    34, 72,
    34, 80,
    34, 82,
    34, 87,
    34, 88,
    34, 90,
    35, 34,
    35, 53,
    35, 55,
    35, 56,
    35, 57,
    35, 58,
    35, 59,
    35, 87,
    35, 89,
    35, 90,
    35, 91,
    36, 36,
    36, 40,
    36, 48,
    36, 50,
    36, 53,
    36, 57,
    36, 58,
    36, 59,
    36, 87,
    36, 88,
    36, 89,
    36, 90,
    37, 34,
    37, 43,
    37, 53,
    37, 55,
    37, 56,
    37, 57,
    37, 58,
    37, 59,
    37, 91,
    38, 7,
    38, 36,
    38, 40,
    38, 48,
    38, 50,
    38, 87,
    38, 88,
    38, 90,
    39, 7,
    39, 34,
    39, 43,
    39, 52,
    39, 57,
    39, 66,
    39, 68,
    39, 69,
    39, 70,
    39, 72,
    39, 80,
    39, 82,
    39, 86,
    39, 87,
    39, 88,
    39, 89,
    39, 90,
    39, 91,
    40, 34,
    40, 53,
    40, 55,
    40, 56,
    40, 57,
    40, 58,
    40, 59,
    40, 84,
    40, 87,
    40, 88,
    40, 89,
    40, 90,
    43, 57,
    44, 7,
    44, 36,
    44, 40,
    44, 43,
    44, 48,
    44, 50,
    44, 52,
    44, 54,
    44, 66,
    44, 68,
    44, 69,
    44, 70,
    44, 72,
    44, 80,
    44, 82,
    44, 84,
    44, 85,
    44, 86,
    44, 87,
    44, 88,
    44, 90,
    45, 36,
    45, 40,
    45, 48,
    45, 50,
    45, 53,
    45, 54,
    45, 55,
    45, 56,
    45, 58,
    45, 71,
    45, 85,
    45, 86,
    45, 87,
    45, 88,
    45, 90,
    48, 34,
    48, 43,
    48, 53,
    48, 55,
    48, 56,
    48, 57,
    48, 58,
    48, 59,
    48, 91,
    49, 7,
    49, 34,
    49, 43,
    49, 53,
    49, 55,
    49, 56,
    49, 57,
    49, 58,
    49, 59,
    49, 66,
    49, 68,
    49, 69,
    49, 70,
    49, 72,
    49, 80,
    49, 82,
    49, 84,
    49, 86,
    50, 34,
    50, 53,
    50, 55,
    50, 56,
    50, 57,
    50, 58,
    50, 59,
    51, 7,
    51, 36,
    51, 40,
    51, 43,
    51, 48,
    51, 50,
    51, 53,
    51, 55,
    51, 56,
    51, 58,
    51, 66,
    51, 68,
    51, 69,
    51, 70,
    51, 72,
    51, 80,
    51, 82,
    51, 86,
    52, 53,
    52, 55,
    52, 57,
    52, 58,
    52, 87,
    52, 88,
    52, 89,
    52, 90,
    52, 91,
    53, 7,
    53, 34,
    53, 36,
    53, 40,
    53, 43,
    53, 48,
    53, 50,
    53, 52,
    53, 57,
    53, 66,
    53, 68,
    53, 69,
    53, 70,
    53, 71,
    53, 72,
    53, 78,
    53, 79,
    53, 80,
    53, 81,
    53, 82,
    53, 83,
    53, 84,
    53, 85,
    53, 86,
    53, 87,
    53, 88,
    53, 89,
    53, 90,
    53, 91,
    54, 34,
    54, 43,
    54, 57,
    55, 7,
    55, 34,
    55, 36,
    55, 40,
    55, 43,
    55, 48,
    55, 50,
    55, 52,
    55, 66,
    55, 68,
    55, 69,
    55, 70,
    55, 71,
    55, 72,
    55, 78,
    55, 79,
    55, 80,
    55, 81,
    55, 82,
    55, 83,
    55, 84,
    55, 85,
    55, 86,
    55, 87,
    55, 88,
    55, 89,
    55, 90,
    55, 91,
    56, 7,
    56, 34,
    56, 36,
    56, 40,
    56, 43,
    56, 48,
    56, 50,
    56, 52,
    56, 66,
    56, 68,
    56, 69,
    56, 70,
    56, 71,
    56, 72,
    56, 78,
    56, 79,
    56, 80,
    56, 81,
    56, 82,
    56, 83,
    56, 84,
    56, 85,
    56, 86,
    56, 87,
    56, 88,
    56, 89,
    56, 90,
    56, 91,
    57, 7,
    57, 36,
    57, 40,
    57, 48,
    57, 50,
    57, 52,
    57, 53,
    57, 54,
    57, 66,
    57, 68,
    57, 69,
    57, 70,
    57, 71,
    57, 72,
    57, 77,
    57, 78,
    57, 79,
    57, 80,
    57, 81,
    57, 82,
    57, 83,
    57, 84,
    57, 85,
    57, 86,
    57, 87,
    57, 88,
    57, 90,
    58, 7,
    58, 34,
    58, 36,
    58, 40,
    58, 43,
    58, 48,
    58, 50,
    58, 52,
    58, 66,
    58, 68,
    58, 69,
    58, 70,
    58, 71,
    58, 72,
    58, 78,
    58, 79,
    58, 80,
    58, 81,
    58, 82,
    58, 83,
    58, 84,
    58, 85,
    58, 86,
    58, 87,
    58, 88,
    58, 89,
    58, 90,
    58, 91,
    59, 7,
    59, 36,
    59, 40,
    59, 48,
    59, 50,
    59, 54,
    59, 68,
    59, 69,
    59, 70,
    59, 72,
    59, 80,
    59, 82,
    59, 85,
    59, 86,
    59, 87,
    59, 88,
    59, 90,
    64, 75,
    66, 53,
    66, 55,
    66, 56,
    66, 57,
    66, 58,
    66, 87,
    66, 88,
    66, 89,
    66, 90,
    67, 34,
    67, 53,
    67, 55,
    67, 56,
    67, 57,
    67, 58,
    67, 59,
    67, 87,
    67, 88,
    67, 89,
    67, 90,
    67, 91,
    68, 53,
    68, 55,
    68, 56,
    68, 57,
    68, 58,
    68, 87,
    68, 89,
    68, 90,
    70, 53,
    70, 55,
    70, 56,
    70, 57,
    70, 58,
    70, 87,
    70, 88,
    70, 89,
    70, 90,
    71, 7,
    71, 34,
    71, 43,
    71, 66,
    71, 68,
    71, 69,
    71, 70,
    71, 72,
    71, 80,
    71, 82,
    71, 84,
    71, 86,
    72, 53,
    72, 55,
    72, 56,
    72, 58,
    72, 75,
    73, 53,
    73, 55,
    73, 56,
    73, 57,
    73, 58,
    73, 87,
    73, 88,
    73, 89,
    73, 90,
    76, 7,
    76, 36,
    76, 40,
    76, 48,
    76, 50,
    76, 53,
    76, 54,
    76, 55,
    76, 56,
    76, 58,
    76, 66,
    76, 68,
    76, 69,
    76, 70,
    76, 72,
    76, 77,
    76, 80,
    76, 82,
    76, 84,
    76, 85,
    76, 86,
    77, 7,
    77, 36,
    77, 40,
    77, 48,
    77, 50,
    77, 86,
    77, 87,
    77, 88,
    77, 90,
    78, 53,
    78, 55,
    78, 56,
    78, 57,
    78, 58,
    78, 87,
    78, 88,
    78, 89,
    78, 90,
    79, 53,
    79, 55,
    79, 56,
    79, 57,
    79, 58,
    79, 87,
    79, 88,
    79, 89,
    79, 90,
    80, 34,
    80, 53,
    80, 55,
    80, 56,
    80, 57,
    80, 58,
    80, 59,
    80, 87,
    80, 88,
    80, 89,
    80, 90,
    80, 91,
    81, 34,
    81, 53,
    81, 55,
    81, 56,
    81, 57,
    81, 58,
    81, 59,
    81, 87,
    81, 88,
    81, 89,
    81, 90,
    81, 91,
    82, 53,
    82, 55,
    82, 56,
    82, 58,
    82, 75,
    83, 7,
    83, 53,
    83, 57,
    83, 58,
    83, 59,
    83, 66,
    83, 68,
    83, 69,
    83, 70,
    83, 72,
    83, 80,
    83, 82,
    83, 84,
    83, 86,
    84, 53,
    84, 55,
    84, 56,
    84, 57,
    84, 58,
    84, 89,
    85, 53,
    85, 55,
    85, 56,
    85, 58,
    85, 68,
    85, 69,
    85, 70,
    85, 72,
    85, 80,
    85, 82,
    85, 84,
    85, 86,
    86, 53,
    86, 55,
    86, 56,
    86, 58,
    86, 75,
    87, 7,
    87, 34,
    87, 43,
    87, 53,
    87, 55,
    87, 56,
    87, 57,
    87, 58,
    87, 59,
    87, 66,
    87, 68,
    87, 69,
    87, 70,
    87, 72,
    87, 80,
    87, 82,
    87, 84,
    88, 7,
    88, 34,
    88, 43,
    88, 53,
    88, 55,
    88, 56,
    88, 57,
    88, 58,
    88, 59,
    88, 66,
    88, 68,
    88, 69,
    88, 70,
    88, 72,
    88, 80,
    88, 82,
    88, 84,
    89, 7,
    89, 36,
    89, 40,
    89, 48,
    89, 50,
    89, 53,
    89, 55,
    89, 56,
    89, 58,
    89, 66,
    89, 68,
    89, 69,
    89, 70,
    89, 72,
    89, 77,
    89, 80,
    89, 82,
    89, 84,
    89, 86,
    90, 7,
    90, 34,
    90, 43,
    90, 53,
    90, 55,
    90, 56,
    90, 57,
    90, 58,
    90, 59,
    90, 66,
    90, 68,
    90, 69,
    90, 70,
    90, 72,
    90, 80,
    90, 82,
    90, 84,
    91, 7,
    91, 36,
    91, 40,
    91, 48,
    91, 50,
    91, 53,
    91, 55,
    91, 56,
    91, 58,
    91, 66,
    91, 68,
    91, 69,
    91, 70,
    91, 72,
    91, 80,
    91, 82,
    91, 84,
    91, 86
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -2, -2, -5, -2, -2, -15, -4, -13,
    -8, -19, -3, -2, -2, -2, 0, -2,
    -4, -2, -2, -1, -7, -5, -7, -11,
    -9, -12, -11, -9, -12, -13, -10, -6,
    -4, -3, -5, -7, -4, -4, -2, -4,
    -5, -4, -6, -8, -2, -27, -27, -18,
    -4, -14, -13, -4, -4, -3, -21, -21,
    -10, -4, -2, -4, -2, -5, -5, -5,
    -5, -26, -3, -21, -14, -22, -3, -3,
    -3, -3, -3, -3, -9, -5, -9, -4,
    -5, -4, -3, -4, -7, -2, -2, -1,
    -2, -2, -4, -4, -4, -4, -2, -4,
    -2, -2, -4, -4, -2, -4, -6, -12,
    -6, -7, -3, -10, -10, -7, -2, -4,
    -3, -3, -3, -3, -2, -2, -2, -5,
    -12, -20, -2, -4, -12, -5, -5, -5,
    -5, -5, -5, -4, -2, -2, -8, -2,
    -2, -4, -6, -8, -3, -5, -12, -2,
    -2, -5, -6, -4, -5, -3, -8, -12,
    -12, -8, -12, -12, -6, -10, -6, -10,
    -10, -10, -10, -10, -10, -2, -9, -10,
    -15, -12, -15, -8, -8, -8, -8, -26,
    -4, -23, -16, -26, -4, -7, -5, -15,
    -10, -15, -6, -12, -6, -7, -3, -10,
    -10, -7, -2, -8, -16, -31, -4, -5,
    -3, -8, -6, -4, -11, -10, -10, -10,
    -10, -10, -10, -7, -8, -5, -6, -4,
    -4, -8, -10, -2, -3, -1, -1, -5,
    -1, -1, -4, -3, -2, -6, -3, -4,
    -4, -4, -4, -4, -4, -4, -4, -2,
    -5, -2, -4, -4, -2, -4, -3, -12,
    -26, -6, -6, -30, -6, -6, -5, -5,
    -19, -19, -19, -19, -10, -19, -17, -17,
    -19, -17, -19, -17, -25, -4, -19, -21,
    -19, -21, -21, -22, -3, -5, -3, -13,
    -21, -7, -7, -30, -7, -7, -2, -17,
    -15, -15, -15, -7, -15, -15, -15, -15,
    -15, -15, -15, -14, -4, -14, -6, -6,
    -8, -6, -8, -7, -14, -3, -3, -18,
    -3, -3, -1, -10, -8, -8, -8, -4,
    -8, -9, -9, -8, -9, -8, -9, -9,
    -2, -8, -6, -6, -8, -6, -8, -4,
    -10, -10, -10, -10, -2, -5, -3, -2,
    -7, -7, -7, -4, -7, -1, -3, -3,
    -7, -3, -7, -3, -6, -10, -8, -16,
    -14, -16, -15, -22, -10, -10, -33, -10,
    -10, -6, -29, -27, -27, -27, -10, -27,
    -29, -29, -27, -29, -27, -29, -25, -12,
    -27, -19, -18, -20, -19, -21, -8, -10,
    -10, -10, -10, -3, -3, -3, -3, -3,
    -3, -3, -6, -6, -8, -8, -8, 13,
    -19, -16, -10, -3, -30, -1, -1, -2,
    -1, -3, -19, -15, -8, -7, -27, -2,
    -2, -2, -6, -2, -1, -19, -9, -7,
    -3, -23, -2, -3, -2, -19, -12, -7,
    -6, -22, -2, -1, -3, -2, -6, -11,
    -14, -4, -3, -3, -3, -3, -3, -3,
    -3, -2, -17, -15, -10, -27, 0, -19,
    -16, -10, -3, -30, -1, -1, -2, -1,
    -3, -4, -4, -4, -4, -28, -2, -9,
    -6, -15, -2, -3, -3, -3, -3, -1,
    -3, -3, -2, -1, -3, -3, -3, -3,
    -3, -3, -1, -2, -1, -2, -19, -16,
    -10, -3, -30, -1, -1, -2, -1, -19,
    -16, -10, -3, -30, -1, -1, -2, -1,
    -3, -19, -15, -8, -7, -27, -2, -2,
    -2, -6, -2, -1, -3, -19, -15, -8,
    -7, -27, -2, -2, -2, -6, -2, -1,
    -17, -15, -10, -27, 0, -10, -17, -15,
    -14, -10, -2, -2, -2, -2, -2, -2,
    -2, -2, -3, -24, -10, -8, -6, -23,
    -4, -4, -4, -2, -10, -1, -1, -1,
    -1, -1, -1, -1, -1, -17, -15, -10,
    -27, 0, -8, -9, -17, -21, -6, -6,
    -16, -19, -10, -1, -2, -2, -2, -2,
    -2, -2, -2, -4, -5, -14, -19, -6,
    -6, -14, -18, -8, -2, -2, -2, -2,
    -2, -2, -2, -1, -2, -2, -2, -2,
    -2, -21, -8, -8, -20, -3, -7, -7,
    -7, -7, -2, -7, -7, -4, -2, -8,
    -9, -17, -21, -6, -6, -16, -19, -10,
    -1, -2, -2, -2, -2, -2, -2, -2,
    -7, -6, -6, -6, -6, -21, -6, -9,
    -21, -1, -3, -3, -3, -3, -3, -3,
    -1, -1
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 674,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t font_12 = {
#else
lv_font_t font_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if FONT_12*/

