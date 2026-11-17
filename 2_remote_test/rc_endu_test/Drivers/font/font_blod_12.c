/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --no-compress --font MiSans-Bold.ttf --symbols  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
电量低超时启关闭船锚菜单提示弹框删除存项不所有蓝牙无标记扳机键能通讯类型到达的当前备硬软件松开始速巡航抛仓自
任务传输进度指令失败功短长摇杆校准配对模式选择语言版本信息重置退出动两个一圈按下步保持回中完成简体文确定恢复
为默认设？！：取消字大小点断联正在发送已止手义固更新请试上后击 --format lvgl -o font_blod_12.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef FONT_BLOD_12
#define FONT_BLOD_12 1
#endif

#if FONT_BLOD_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xf3, 0xc0,

    /* U+0022 "\"" */
    0x7a, 0xd6, 0xb0,

    /* U+0023 "#" */
    0x32, 0x36, 0xff, 0xff, 0x24, 0xff, 0xff, 0x6c,
    0x4c,

    /* U+0024 "$" */
    0x31, 0xef, 0xf3, 0xc3, 0xc3, 0xc3, 0xcf, 0xf7,
    0x8c,

    /* U+0025 "%" */
    0x70, 0x9f, 0x33, 0xec, 0x3b, 0x0, 0x5c, 0x1f,
    0xc6, 0xd9, 0x9f, 0x21, 0xc0,

    /* U+0026 "&" */
    0x3c, 0x3e, 0x19, 0x8e, 0x7, 0xb6, 0xfb, 0x39,
    0xfe, 0x7b, 0x80,

    /* U+0027 "'" */
    0xd5,

    /* U+0028 "(" */
    0x6f, 0x6d, 0xb6, 0x6c,

    /* U+0029 ")" */
    0xd9, 0xb6, 0xdb, 0xd8,

    /* U+002A "*" */
    0x23, 0xde, 0x40,

    /* U+002B "+" */
    0x30, 0xcf, 0xff, 0x30, 0xc0,

    /* U+002C "," */
    0xf5, 0x80,

    /* U+002D "-" */
    0xff,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x18, 0xcc, 0x63, 0x39, 0x8c, 0x60,

    /* U+0030 "0" */
    0x38, 0xfb, 0xbe, 0x3c, 0x78, 0xfb, 0xbe, 0x38,

    /* U+0031 "1" */
    0x7f, 0xb3, 0x33, 0x33, 0x30,

    /* U+0032 "2" */
    0x7b, 0xfc, 0xc3, 0x18, 0xc6, 0x3f, 0xfc,

    /* U+0033 "3" */
    0xff, 0xf3, 0x9c, 0x7c, 0x3c, 0xff, 0x78,

    /* U+0034 "4" */
    0x1c, 0x78, 0xf3, 0x66, 0xdf, 0xff, 0x86, 0xc,

    /* U+0035 "5" */
    0x7e, 0xfd, 0x83, 0xe7, 0xe0, 0xd1, 0xbf, 0x3c,

    /* U+0036 "6" */
    0x38, 0x61, 0xf3, 0xfc, 0x78, 0xf1, 0xfe, 0x38,

    /* U+0037 "7" */
    0xff, 0xf1, 0x86, 0x38, 0xc3, 0x18, 0x60,

    /* U+0038 "8" */
    0x7d, 0xff, 0x1b, 0xe7, 0xd8, 0xf1, 0xff, 0x7c,

    /* U+0039 "9" */
    0x39, 0xff, 0x1e, 0x3f, 0xef, 0x87, 0xc, 0x38,

    /* U+003A ":" */
    0xf0, 0x3c,

    /* U+003B ";" */
    0xf0, 0x3d, 0x60,

    /* U+003C "<" */
    0x2, 0x1c, 0xff, 0x8e, 0xf, 0x7, 0x87, 0x2,

    /* U+003D "=" */
    0xff, 0xf0, 0x3f, 0xfc,

    /* U+003E ">" */
    0x1, 0x83, 0xc1, 0xe0, 0xe7, 0xbc, 0x60, 0x0,

    /* U+003F "?" */
    0x7b, 0xfc, 0xc7, 0x38, 0xc0, 0xc, 0x30,

    /* U+0040 "@" */
    0x1f, 0x1f, 0xef, 0xff, 0xff, 0xf3, 0xff, 0xff,
    0xd9, 0xfc, 0x1e, 0x0,

    /* U+0041 "A" */
    0x1c, 0xe, 0x7, 0x86, 0xc3, 0x33, 0xf9, 0xfc,
    0xc3, 0xe1, 0x80,

    /* U+0042 "B" */
    0xfd, 0xff, 0x1f, 0xff, 0xd8, 0xf1, 0xff, 0xfc,

    /* U+0043 "C" */
    0x3c, 0x7e, 0xe2, 0xc0, 0xc0, 0xc0, 0xe2, 0x7f,
    0x3c,

    /* U+0044 "D" */
    0xfc, 0xfe, 0xc7, 0xc3, 0xc3, 0xc3, 0xc7, 0xfe,
    0xfc,

    /* U+0045 "E" */
    0xff, 0xff, 0x7, 0xef, 0xd8, 0x30, 0x7f, 0xfe,

    /* U+0046 "F" */
    0xff, 0xfc, 0x3f, 0xff, 0xc, 0x30, 0xc0,

    /* U+0047 "G" */
    0x3e, 0x7f, 0xe2, 0xcf, 0xcf, 0xc3, 0xe3, 0x7f,
    0x3c,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xff, 0xff, 0xc3, 0xc3, 0xc3,
    0xc3,

    /* U+0049 "I" */
    0xff, 0xff, 0xc0,

    /* U+004A "J" */
    0xc, 0x30, 0xc3, 0xc, 0x3c, 0xff, 0x78,

    /* U+004B "K" */
    0xc7, 0xce, 0xdc, 0xf8, 0xf8, 0xfc, 0xcc, 0xce,
    0xc7,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x7f, 0xfe,

    /* U+004D "M" */
    0xc0, 0xf8, 0x7f, 0x3f, 0xcf, 0xde, 0xf7, 0xbc,
    0xcf, 0x3, 0xc0, 0xc0,

    /* U+004E "N" */
    0xc3, 0xe3, 0xf3, 0xfb, 0xdb, 0xdf, 0xcf, 0xc7,
    0xc3,

    /* U+004F "O" */
    0x3e, 0x3f, 0xb8, 0xf8, 0x3c, 0x1e, 0xf, 0x8e,
    0xfe, 0x3e, 0x0,

    /* U+0050 "P" */
    0xfd, 0xff, 0x1e, 0x3f, 0xff, 0xb0, 0x60, 0xc0,

    /* U+0051 "Q" */
    0x3e, 0x3f, 0xb8, 0xf8, 0x3c, 0x1e, 0xf, 0x8e,
    0xfe, 0x3f, 0x80, 0x80,

    /* U+0052 "R" */
    0xfd, 0xff, 0x1e, 0x3f, 0xff, 0xb3, 0x67, 0xc6,

    /* U+0053 "S" */
    0x79, 0xff, 0x1f, 0x7, 0xc1, 0xf1, 0xff, 0x7c,

    /* U+0054 "T" */
    0xff, 0xfc, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e,
    0x3c,

    /* U+0056 "V" */
    0xe1, 0xb0, 0xd8, 0xce, 0x63, 0x71, 0xb0, 0x78,
    0x38, 0x1c, 0x0,

    /* U+0057 "W" */
    0xc3, 0x1d, 0x9c, 0x66, 0x79, 0x99, 0xe6, 0x6d,
    0xb0, 0xf3, 0xc3, 0xcf, 0xe, 0x3c, 0x38, 0x60,

    /* U+0058 "X" */
    0x63, 0x99, 0x8f, 0x83, 0xc1, 0xc0, 0xf0, 0xdc,
    0xe6, 0x63, 0x80,

    /* U+0059 "Y" */
    0xc3, 0xe7, 0x66, 0x3c, 0x3c, 0x18, 0x18, 0x18,
    0x18,

    /* U+005A "Z" */
    0xff, 0xfc, 0x30, 0xe3, 0x8e, 0x18, 0x7f, 0xfe,

    /* U+005B "[" */
    0xff, 0xcc, 0xcc, 0xcc, 0xcf, 0xf0,

    /* U+005C "\\" */
    0xc3, 0x18, 0xc6, 0x18, 0xc6, 0x18,

    /* U+005D "]" */
    0xff, 0x33, 0x33, 0x33, 0x3f, 0xf0,

    /* U+005E "^" */
    0x31, 0xe7, 0xb3,

    /* U+005F "_" */
    0xff, 0xf0,

    /* U+0060 "`" */
    0x6, 0x60,

    /* U+0061 "a" */
    0x7b, 0xf4, 0xdf, 0xff, 0xf7, 0xc0,

    /* U+0062 "b" */
    0xc1, 0x83, 0x77, 0xfc, 0x78, 0xf1, 0xff, 0xdc,

    /* U+0063 "c" */
    0x39, 0xfc, 0xb0, 0xc9, 0xf3, 0x80,

    /* U+0064 "d" */
    0x6, 0xd, 0xff, 0xfc, 0x78, 0xf1, 0xff, 0x7e,

    /* U+0065 "e" */
    0x3c, 0xff, 0xff, 0xfc, 0x4f, 0x8e, 0x0,

    /* U+0066 "f" */
    0x3, 0xdf, 0xff, 0xb1, 0x8c, 0x63, 0x0,

    /* U+0067 "g" */
    0x77, 0xff, 0x1e, 0x3c, 0x7f, 0xdd, 0xa3, 0xfe,
    0x78,

    /* U+0068 "h" */
    0xc3, 0xd, 0xbf, 0xcf, 0x3c, 0xf3, 0xcc,

    /* U+0069 "i" */
    0x33, 0xff, 0xf0,

    /* U+006A "j" */
    0x3, 0x3, 0x33, 0x33, 0x33, 0x3f, 0xe0,

    /* U+006B "k" */
    0xc1, 0x83, 0x76, 0xcf, 0x1e, 0x3e, 0x6e, 0xcc,

    /* U+006C "l" */
    0xdb, 0x6d, 0xb7, 0xe0,

    /* U+006D "m" */
    0xdb, 0xbf, 0xfc, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xcc,

    /* U+006E "n" */
    0xdb, 0xfc, 0xf3, 0xcf, 0x3c, 0xc0,

    /* U+006F "o" */
    0x38, 0xfb, 0x1e, 0x3c, 0x6f, 0x9e, 0x0,

    /* U+0070 "p" */
    0xdd, 0xff, 0x1e, 0x3c, 0x7f, 0xf7, 0x60, 0xc1,
    0x80,

    /* U+0071 "q" */
    0x77, 0xff, 0x1e, 0x3c, 0x7f, 0xdd, 0x83, 0x6,
    0xc,

    /* U+0072 "r" */
    0xdf, 0xf9, 0x8c, 0x63, 0x0,

    /* U+0073 "s" */
    0x7b, 0xfc, 0x9e, 0x4f, 0xf7, 0x80,

    /* U+0074 "t" */
    0x63, 0x3f, 0xf6, 0x31, 0x8f, 0x38,

    /* U+0075 "u" */
    0xcf, 0x3c, 0xf3, 0xcf, 0xf6, 0xc0,

    /* U+0076 "v" */
    0xc6, 0x66, 0x66, 0x6c, 0x3c, 0x38, 0x18,

    /* U+0077 "w" */
    0xce, 0x6d, 0xcd, 0xbb, 0x35, 0xe7, 0xbc, 0x77,
    0xe, 0x60,

    /* U+0078 "x" */
    0x66, 0x7c, 0x3c, 0x18, 0x3c, 0x7e, 0xe6,

    /* U+0079 "y" */
    0xc7, 0x66, 0x66, 0x7c, 0x3c, 0x3c, 0x18, 0x18,
    0x30, 0x30,

    /* U+007A "z" */
    0xff, 0xf1, 0x8c, 0x63, 0xff, 0xc0,

    /* U+007B "{" */
    0x1, 0xce, 0x63, 0x7b, 0xc6, 0x31, 0x8e, 0x30,

    /* U+007C "|" */
    0xff, 0xff, 0xf0,

    /* U+007D "}" */
    0x83, 0xcf, 0xc, 0x30, 0xf3, 0xcc, 0x30, 0xcf,
    0x38,

    /* U+007E "~" */
    0x72, 0xfe, 0x4c,

    /* U+4E00 "一" */
    0xff, 0xff, 0xfc,

    /* U+4E0A "上" */
    0xc, 0x1, 0x80, 0x30, 0x7, 0xf0, 0xc0, 0x18,
    0x3, 0x0, 0x60, 0xc, 0x1f, 0xff, 0xff, 0x80,

    /* U+4E0B "下" */
    0xff, 0xe1, 0x80, 0x30, 0x7, 0xc0, 0xdc, 0x19,
    0x83, 0x10, 0x60, 0xc, 0x1, 0x80,

    /* U+4E0D "不" */
    0xff, 0xc3, 0x0, 0xc0, 0x70, 0x3f, 0x1f, 0x6e,
    0xcf, 0x31, 0xc, 0x3, 0x0, 0xc0,

    /* U+4E24 "两" */
    0xff, 0xe3, 0x60, 0x6c, 0x7f, 0xfd, 0xb7, 0xb6,
    0xf7, 0xff, 0xff, 0xf6, 0xf8, 0x8f, 0x7, 0x0,

    /* U+4E2A "个" */
    0x6, 0x0, 0xf0, 0x1f, 0x83, 0x9c, 0xf6, 0xf4,
    0x62, 0x6, 0x0, 0x60, 0x6, 0x0, 0x60, 0x6,
    0x0,

    /* U+4E2D "中" */
    0xc, 0x3, 0xf, 0xff, 0x33, 0xcc, 0xf3, 0x3f,
    0xfc, 0x30, 0xc, 0x3, 0x0, 0xc0,

    /* U+4E3A "为" */
    0x4c, 0x1b, 0x2, 0xc3, 0xff, 0xc, 0xc7, 0xb1,
    0xbc, 0xc3, 0x70, 0xf9, 0xfc, 0x7c,

    /* U+4E49 "义" */
    0xc, 0x4, 0xd8, 0xdb, 0x18, 0x61, 0x98, 0x3f,
    0x3, 0xc0, 0x78, 0x3f, 0xcf, 0x1d, 0x80, 0x80,

    /* U+4ED3 "仓" */
    0x6, 0x1, 0xe0, 0x6e, 0x38, 0xff, 0xfe, 0x63,
    0xc, 0x61, 0xbe, 0x30, 0x66, 0xc, 0xff, 0x0,

    /* U+4EE4 "令" */
    0xc, 0x7, 0x83, 0x33, 0xb7, 0xcc, 0xdf, 0xe2,
    0x38, 0xf8, 0x1e, 0x1, 0x80,

    /* U+4EF6 "件" */
    0x33, 0xd, 0x61, 0xbf, 0x7d, 0x8f, 0xb1, 0xc6,
    0x1f, 0xfb, 0x18, 0x63, 0xc, 0x61, 0x8c, 0x0,

    /* U+4EFB "任" */
    0x30, 0x45, 0xfd, 0x8c, 0x71, 0x8e, 0x31, 0xdf,
    0xd8, 0xc3, 0x18, 0x63, 0xd, 0xfd, 0xbf, 0x80,

    /* U+4F20 "传" */
    0x33, 0x7, 0xfd, 0x98, 0x73, 0xf, 0xff, 0xc8,
    0x1b, 0xf3, 0x6, 0x6f, 0x8c, 0x79, 0x83, 0x0,

    /* U+4F4E "低" */
    0x30, 0xcf, 0xf9, 0xa6, 0x74, 0xce, 0xfd, 0xd3,
    0x1a, 0x63, 0x54, 0x6e, 0xad, 0xdd, 0xad, 0x0,

    /* U+4F53 "体" */
    0x32, 0x4, 0x41, 0xff, 0x33, 0x8e, 0x79, 0xdd,
    0x3a, 0xb3, 0x93, 0x7f, 0xcc, 0x41, 0x88, 0x0,

    /* U+4FDD "保" */
    0x3f, 0xcd, 0x9, 0xa1, 0x77, 0xee, 0x31, 0xc6,
    0x3f, 0xfb, 0x3c, 0x6f, 0xcf, 0x6d, 0x8c, 0x0,

    /* U+4FE1 "信" */
    0x22, 0xf, 0xfd, 0x80, 0x3f, 0xee, 0x1, 0xff,
    0xb8, 0x3, 0xfe, 0x78, 0xcf, 0xf9, 0xe3, 0x0,

    /* U+5173 "关" */
    0x63, 0x8c, 0xcf, 0xfc, 0x30, 0xc, 0x3f, 0xf0,
    0xc0, 0xf8, 0xf3, 0xf8, 0x70,

    /* U+51C6 "准" */
    0x5, 0x86, 0xd8, 0x6f, 0xf3, 0xd8, 0x1f, 0xf7,
    0xd8, 0x6f, 0xf6, 0xd8, 0x6d, 0x8c, 0xff, 0xc,
    0x0,

    /* U+51FA "出" */
    0xc, 0x33, 0x3c, 0xcf, 0x33, 0xff, 0xc3, 0xc,
    0xcf, 0x33, 0xcc, 0xff, 0xf0, 0xc,

    /* U+51FB "击" */
    0x4, 0x0, 0x81, 0xff, 0x2, 0x0, 0x41, 0xff,
    0xc1, 0x3, 0x26, 0x64, 0xcf, 0xf9, 0xff, 0x0,

    /* U+5220 "删" */
    0x6e, 0x5a, 0xf6, 0xbd, 0xaf, 0xff, 0xda, 0xf6,
    0xbf, 0xaf, 0xea, 0x7f, 0x9b, 0x7c,

    /* U+5230 "到" */
    0xfc, 0xda, 0xfc, 0xff, 0xff, 0xff, 0xcc, 0xff,
    0xfc, 0xcf, 0x30, 0xff, 0x3f, 0xdc,

    /* U+524D "前" */
    0x11, 0x6, 0x73, 0xff, 0x80, 0x7, 0xd4, 0x9a,
    0x9f, 0x52, 0x6a, 0x7d, 0x49, 0x89, 0x31, 0x2e,
    0xe0,

    /* U+529F "功" */
    0x6, 0x3d, 0x86, 0xfd, 0x9b, 0x66, 0xd9, 0xb6,
    0x6d, 0xd3, 0xfc, 0xfb, 0x31, 0xbc,

    /* U+52A1 "务" */
    0x30, 0x1f, 0xef, 0x38, 0x78, 0xf3, 0xe6, 0xf,
    0xfc, 0x62, 0x30, 0x98, 0x2c, 0x78,

    /* U+52A8 "动" */
    0x7b, 0x1, 0xf0, 0x7c, 0x1f, 0xfb, 0x58, 0xd7,
    0xb5, 0x6d, 0xdb, 0x7f, 0x90, 0x7c,

    /* U+5355 "单" */
    0x11, 0x7, 0x71, 0xff, 0x32, 0x67, 0xfc, 0xc9,
    0x9f, 0xf0, 0x20, 0xff, 0xe0, 0x80, 0x10, 0x0,

    /* U+53D1 "发" */
    0xd9, 0x36, 0x6f, 0xfc, 0x40, 0x30, 0xf, 0xe7,
    0x99, 0xbc, 0xce, 0x2f, 0xff, 0x1c,

    /* U+53D6 "取" */
    0xf8, 0x37, 0xff, 0xef, 0xeb, 0xda, 0xbe, 0xed,
    0xbb, 0xee, 0xfb, 0xe7, 0xb1, 0xc4,

    /* U+540E "后" */
    0xf, 0xcf, 0xf9, 0x80, 0x3f, 0xf6, 0x0, 0xc0,
    0x1f, 0xf3, 0xc6, 0xd8, 0xdb, 0xf8, 0x63, 0x0,

    /* U+542F "启" */
    0x6, 0xf, 0xfd, 0x81, 0xb0, 0x37, 0xfe, 0xc0,
    0x1f, 0xfb, 0xc3, 0xd8, 0x7b, 0xfc, 0x61, 0x80,

    /* U+56DE "回" */
    0xff, 0xf0, 0x3c, 0xf, 0x7b, 0xd2, 0xf4, 0xbd,
    0xef, 0x3, 0xc0, 0xff, 0xfc, 0xc,

    /* U+56FA "固" */
    0xff, 0xf0, 0x3c, 0xcf, 0xff, 0xcc, 0xf7, 0xbd,
    0x2f, 0x7b, 0xc0, 0xff, 0xfc, 0xc,

    /* U+5708 "圈" */
    0xff, 0xfa, 0x2f, 0x7d, 0xff, 0xff, 0xff, 0xa6,
    0xff, 0xfe, 0xbb, 0xdf, 0x7f, 0xff, 0x1, 0x80,

    /* U+5728 "在" */
    0x18, 0x3f, 0xf3, 0x1, 0x88, 0x62, 0x3b, 0xfe,
    0x21, 0x88, 0x62, 0x1f, 0xf6, 0x0,

    /* U+578B "型" */
    0xfe, 0xda, 0xbf, 0xef, 0xfb, 0x48, 0xf0, 0x74,
    0x1d, 0xfe, 0xc, 0x3, 0xf, 0xfc,

    /* U+5907 "备" */
    0x30, 0x1f, 0xef, 0x39, 0x78, 0x7f, 0xfc, 0xf7,
    0xf9, 0xb6, 0x7f, 0x9f, 0xe6, 0x18,

    /* U+590D "复" */
    0x18, 0x3, 0xff, 0x70, 0xf, 0xfe, 0x70, 0x63,
    0xfe, 0x3f, 0xe3, 0xfe, 0x3f, 0xe6, 0xdc, 0x1f,
    0xe7, 0x87,

    /* U+5927 "大" */
    0xc, 0x3, 0x0, 0xc3, 0xff, 0xc, 0x7, 0x1,
    0xe0, 0xcc, 0x73, 0xb0, 0x78, 0x0,

    /* U+5931 "失" */
    0x4c, 0x1b, 0x7, 0xff, 0x30, 0x4c, 0x3f, 0xf0,
    0xe0, 0x7c, 0x73, 0xb8, 0x70, 0x4,

    /* U+59CB "始" */
    0x42, 0x8, 0xd3, 0xf3, 0x2f, 0xef, 0x5, 0xe0,
    0x3f, 0xf3, 0x66, 0x7c, 0xdb, 0xfa, 0x33, 0x0,

    /* U+5B57 "字" */
    0xc, 0x3f, 0xfc, 0xc, 0x0, 0x3f, 0x1, 0xc0,
    0xe3, 0xff, 0xc, 0x3, 0x1, 0xc0,

    /* U+5B58 "存" */
    0x18, 0x3f, 0xf3, 0x1, 0xbf, 0xe1, 0xb8, 0xcf,
    0xfd, 0x8c, 0x63, 0x18, 0xc6, 0xe0,

    /* U+5B8C "完" */
    0xc, 0x3f, 0xfc, 0xc, 0x0, 0x7f, 0x80, 0xf,
    0xfc, 0x5a, 0x36, 0xd9, 0xbc, 0x7c,

    /* U+5B9A "定" */
    0xc, 0x1f, 0xff, 0x1, 0x80, 0xf, 0xfc, 0x18,
    0x1b, 0xe3, 0x60, 0x6c, 0x1f, 0x83, 0x7f, 0x80,

    /* U+5BF9 "对" */
    0x0, 0xdf, 0x18, 0x7f, 0xec, 0x67, 0x4c, 0xed,
    0x8c, 0xb3, 0x96, 0x78, 0xd9, 0x1a, 0xf, 0x0,

    /* U+5C0F "小" */
    0x6, 0x0, 0x60, 0x36, 0xc3, 0x6c, 0x66, 0xc6,
    0x66, 0x66, 0x6c, 0x66, 0x46, 0x1, 0xe0, 0x1e,
    0x0,

    /* U+5DE1 "巡" */
    0x40, 0x4d, 0xad, 0xbd, 0x5, 0x6f, 0xa8, 0xf5,
    0x9a, 0xf3, 0x7b, 0x6d, 0xfe, 0x3, 0xff, 0x80,

    /* U+5DF2 "已" */
    0xff, 0x80, 0x60, 0x18, 0x6, 0xff, 0xb0, 0xc,
    0x3, 0x3, 0xc0, 0xf0, 0x3f, 0xfc,

    /* U+5EA6 "度" */
    0x6, 0xf, 0xfd, 0xb3, 0x3f, 0xf6, 0xcc, 0xdf,
    0x9f, 0xfb, 0x66, 0x67, 0x9b, 0xfc, 0x40, 0x0,

    /* U+5F00 "开" */
    0x7f, 0xe6, 0x30, 0xc6, 0x18, 0xc3, 0x19, 0xff,
    0xcc, 0x61, 0x8c, 0x71, 0x9c, 0x31, 0x6, 0x0,

    /* U+5F0F "式" */
    0x3, 0xc0, 0x7b, 0xff, 0x81, 0x80, 0x31, 0xfe,
    0xc, 0xc1, 0x99, 0x7d, 0xfe, 0x3c, 0x3, 0x0,

    /* U+5F39 "弹" */
    0x2, 0x3d, 0xa3, 0x28, 0xdf, 0xf5, 0x7d, 0xfc,
    0x57, 0xdf, 0x31, 0xf, 0xf3, 0x13, 0xc4,

    /* U+5F53 "当" */
    0x4c, 0xbb, 0x36, 0xd8, 0xb4, 0xff, 0xc0, 0x37,
    0xfc, 0x3, 0x0, 0xff, 0xf0, 0xc,

    /* U+6062 "恢" */
    0x6c, 0xf, 0xfb, 0xf4, 0x76, 0xae, 0xd5, 0xdf,
    0x9f, 0xc3, 0x9c, 0x76, 0xcd, 0x9d, 0xa1, 0x0,

    /* U+606F "息" */
    0xc, 0xf, 0xf9, 0x83, 0x3f, 0xe6, 0xc, 0xff,
    0x98, 0x33, 0xfe, 0x4, 0x4e, 0xdb, 0x55, 0x8f,
    0xa0,

    /* U+6210 "成" */
    0x3, 0xc0, 0x34, 0x7f, 0xe6, 0x14, 0x7d, 0x66,
    0xdc, 0x6d, 0xc6, 0xdb, 0x7f, 0xac, 0x6e, 0x40,
    0x60,

    /* U+6240 "所" */
    0x1c, 0x67, 0xff, 0x63, 0x7, 0xbf, 0x6b, 0xf6,
    0xb6, 0x7b, 0x66, 0x36, 0x67, 0x66, 0x66, 0x44,
    0x60,

    /* U+624B "手" */
    0x0, 0xcf, 0xf8, 0x18, 0x3, 0x7, 0xfc, 0xc,
    0x3f, 0xf8, 0x30, 0x6, 0x7, 0xc0, 0x70, 0x0,

    /* U+6273 "扳" */
    0x47, 0xcb, 0xfb, 0xe0, 0x2f, 0xe7, 0xcd, 0xfd,
    0xb7, 0xe2, 0xdc, 0x5b, 0xa, 0xf3, 0xf3, 0x0,
    0x20,

    /* U+629B "抛" */
    0x59, 0x96, 0x7f, 0xdd, 0x77, 0x7d, 0xff, 0x5d,
    0xf5, 0x5f, 0x55, 0x55, 0x1f, 0x7c,

    /* U+62E9 "择" */
    0x5f, 0xd3, 0x6e, 0xd9, 0x3f, 0x7d, 0xf8, 0x8d,
    0xfd, 0x8, 0x5f, 0xf7, 0xfc, 0x20,

    /* U+6301 "持" */
    0x61, 0xc, 0xff, 0xc4, 0x37, 0xf7, 0xd, 0xe1,
    0xbb, 0xfb, 0x26, 0x66, 0xcc, 0xdb, 0x8f, 0x0,

    /* U+6307 "指" */
    0x6c, 0x4d, 0xff, 0xfc, 0xb7, 0xf7, 0x7f, 0xff,
    0xfb, 0x1b, 0x7f, 0x6c, 0x6d, 0xff, 0xb1, 0x80,

    /* U+6309 "按" */
    0x43, 0xb, 0xff, 0xe1, 0xa3, 0x7, 0xff, 0xd9,
    0xb3, 0x62, 0x7c, 0x47, 0x89, 0xfb, 0x73, 0x80,
    0x0,

    /* U+63D0 "提" */
    0x4f, 0xc9, 0xb, 0xbf, 0x24, 0x24, 0xfd, 0xff,
    0xf0, 0xc2, 0xde, 0x5b, 0xb, 0xe3, 0xdf, 0x80,

    /* U+6447 "摇" */
    0x5f, 0xfd, 0x6f, 0xaf, 0x24, 0x27, 0xff, 0xf6,
    0x3c, 0xc6, 0xff, 0x5b, 0x7b, 0xff, 0x7f, 0x80,

    /* U+6587 "文" */
    0x4, 0x0, 0xc3, 0xff, 0x98, 0xc3, 0x18, 0x36,
    0x7, 0xc0, 0x70, 0x3f, 0x9e, 0x3d, 0x1, 0x0,

    /* U+65AD "断" */
    0x8, 0xfd, 0xff, 0xbe, 0x6f, 0x8f, 0xff, 0xb6,
    0xbb, 0xd7, 0x5a, 0xc3, 0x5f, 0x4b, 0xf9, 0x0,

    /* U+65B0 "新" */
    0x20, 0x7f, 0xf5, 0x61, 0x58, 0xff, 0xc9, 0xff,
    0xee, 0xbb, 0xee, 0xeb, 0xb6, 0xcc,

    /* U+65E0 "无" */
    0x7f, 0xc1, 0x80, 0x30, 0x6, 0xf, 0xfe, 0x18,
    0x7, 0x0, 0xf0, 0x3e, 0x6e, 0xcf, 0x8f, 0x80,

    /* U+65F6 "时" */
    0xf8, 0xdb, 0xff, 0x7f, 0xec, 0x6f, 0xed, 0xb5,
    0xb6, 0xf6, 0xc6, 0xf8, 0xd8, 0x18, 0xf, 0x0,

    /* U+66F4 "更" */
    0xff, 0xe0, 0x81, 0xff, 0x32, 0x67, 0xfc, 0xc9,
    0x9f, 0xf3, 0x60, 0x3c, 0x7, 0xc3, 0xff, 0x80,

    /* U+6709 "有" */
    0x18, 0x1f, 0xfc, 0xc0, 0x3f, 0xe6, 0xd, 0xff,
    0xa8, 0x35, 0x6, 0x3f, 0xc4, 0x18, 0x8f, 0x0,

    /* U+672C "本" */
    0xc, 0x3, 0xf, 0xfc, 0x78, 0x1e, 0xf, 0xc6,
    0xdb, 0x33, 0xbf, 0x43, 0x0, 0xc0,

    /* U+673A "机" */
    0x6f, 0x8d, 0xb3, 0xf6, 0x36, 0xc6, 0xd9, 0xfb,
    0x3f, 0x67, 0x6f, 0xed, 0xed, 0x3d, 0xe7, 0x80,

    /* U+6746 "杆" */
    0x6f, 0xd8, 0xcf, 0x31, 0x8c, 0x63, 0x3f, 0xff,
    0x33, 0x8c, 0x63, 0x18, 0xc6, 0x30,

    /* U+677E "松" */
    0x65, 0x8c, 0xd3, 0xf3, 0x36, 0x36, 0xb5, 0xf4,
    0x3d, 0xa7, 0x34, 0x6c, 0xcd, 0xf9, 0xa1, 0x0,

    /* U+6807 "标" */
    0x6f, 0xfe, 0x3, 0xc0, 0x78, 0x6, 0xfe, 0xe2,
    0x3d, 0x57, 0x6a, 0xed, 0x6d, 0x2d, 0x9c, 0x0,

    /* U+6821 "校" */
    0x61, 0xd, 0xff, 0xff, 0xb3, 0x66, 0xc7, 0xed,
    0xbd, 0xa7, 0x1c, 0x67, 0x8f, 0xdd, 0xa1, 0x80,

    /* U+6846 "框" */
    0x5f, 0xfe, 0xf, 0x83, 0xff, 0x59, 0x3f, 0xff,
    0x93, 0x7f, 0x58, 0x16, 0x5, 0xfc,

    /* U+6A21 "模" */
    0x5f, 0xff, 0xff, 0xbf, 0x27, 0xee, 0xfd, 0xff,
    0xb3, 0xf2, 0xff, 0x47, 0x8b, 0xbd, 0x61, 0x0,

    /* U+6B62 "止" */
    0x3, 0x0, 0x60, 0xcc, 0x19, 0xf3, 0x3e, 0x66,
    0xc, 0xc1, 0x98, 0x33, 0x1f, 0xff, 0xff, 0x80,

    /* U+6B63 "正" */
    0x7f, 0xc1, 0x80, 0x60, 0x18, 0x66, 0x19, 0xf6,
    0x61, 0x98, 0x66, 0x3f, 0xf0,

    /* U+6B65 "步" */
    0x6, 0x4, 0xfc, 0x98, 0x13, 0xf, 0xfe, 0xc,
    0x8d, 0xbf, 0x3e, 0x4f, 0x1f, 0xc3, 0x80, 0x0,

    /* U+6D88 "消" */
    0xca, 0x3e, 0xb4, 0xab, 0x7f, 0x58, 0xc7, 0xf7,
    0x8d, 0xff, 0xd8, 0xf6, 0x3d, 0x9c,

    /* U+70B9 "点" */
    0xc, 0x3, 0xf0, 0xc1, 0xff, 0x60, 0xd8, 0x37,
    0xfd, 0xaa, 0xda, 0x76, 0xd0,

    /* U+7248 "版" */
    0x57, 0xea, 0xfd, 0x58, 0x3f, 0xf4, 0x76, 0x8e,
    0xdd, 0xf2, 0xbe, 0x5e, 0xcb, 0xfd, 0x7c, 0x80,

    /* U+7259 "牙" */
    0xff, 0xc0, 0xc6, 0x31, 0xc, 0xff, 0xc3, 0xc1,
    0xb0, 0xcc, 0x63, 0x30, 0xc8, 0xe0,

    /* U+7535 "电" */
    0xc, 0x1f, 0xfb, 0x33, 0x66, 0x6f, 0xfd, 0x99,
    0xb3, 0x37, 0xfe, 0xc, 0x61, 0x8c, 0x3f, 0x80,

    /* U+7684 "的" */
    0x22, 0x8, 0x8f, 0xff, 0x73, 0xd8, 0xff, 0xbd,
    0xbf, 0x63, 0xd8, 0xfe, 0x3c, 0x3c,

    /* U+77ED "短" */
    0x0, 0x1f, 0xff, 0x3, 0xc0, 0xaf, 0xff, 0x3f,
    0xfd, 0x92, 0x75, 0x95, 0x6c, 0xfc, 0x0,

    /* U+786C "硬" */
    0xf, 0xfe, 0x21, 0xbf, 0x26, 0xaf, 0xfd, 0xba,
    0x97, 0xf2, 0xa8, 0x77, 0x89, 0xfd, 0x30, 0x0,

    /* U+786E "确" */
    0x2, 0x3d, 0xf4, 0xc9, 0x3f, 0xfd, 0x7f, 0xff,
    0xd5, 0xff, 0x7f, 0xdf, 0x54, 0x9c,

    /* U+793A "示" */
    0x7f, 0xcf, 0xf8, 0x0, 0x0, 0xf, 0xfe, 0xd,
    0xd, 0xe3, 0x36, 0xc6, 0x6b, 0xc8, 0x70, 0x0,

    /* U+7B80 "简" */
    0x31, 0xf, 0xff, 0x7b, 0x37, 0xf2, 0xfe, 0xde,
    0xdb, 0xdb, 0x4b, 0x6f, 0x6c, 0xd, 0x87, 0x80,

    /* U+7C7B "类" */
    0x4c, 0x9b, 0x62, 0xd3, 0xff, 0x3f, 0xf8, 0x38,
    0xc7, 0xff, 0x1e, 0x3c, 0xfc, 0xc,

    /* U+7F6E "置" */
    0x7f, 0xcb, 0x69, 0xff, 0x7f, 0xf7, 0xfc, 0xff,
    0x9f, 0xf3, 0xfe, 0x7f, 0xcc, 0x1b, 0xff, 0x80,

    /* U+8054 "联" */
    0x2, 0x1f, 0x4b, 0x4b, 0x6b, 0xff, 0x11, 0xa2,
    0x3d, 0xfe, 0x8c, 0xfb, 0x9f, 0x7a, 0x59, 0x8a,
    0x20,

    /* U+80FD "能" */
    0x62, 0x7c, 0xff, 0xa7, 0x39, 0xfb, 0xe6, 0xf,
    0xae, 0x6e, 0xfa, 0x66, 0x9b, 0xbc,

    /* U+81EA "自" */
    0x18, 0x7f, 0xf0, 0x7f, 0xff, 0xfe, 0xf, 0xff,
    0x83, 0xc1, 0xff, 0xf0, 0x60,

    /* U+822A "航" */
    0x63, 0x3f, 0xff, 0x2, 0x5e, 0xf5, 0xa5, 0x6f,
    0x5b, 0xd7, 0x9d, 0xfe, 0x70,

    /* U+8239 "船" */
    0x0, 0x6, 0xf9, 0xfb, 0x37, 0x67, 0xef, 0xf8,
    0xff, 0xf3, 0x72, 0x7e, 0x49, 0xc9, 0x3f, 0x3f,
    0x20,

    /* U+83DC "菜" */
    0x11, 0x1f, 0xfc, 0x1, 0x7f, 0xe4, 0xcc, 0xcb,
    0x3f, 0xf8, 0xf8, 0x75, 0xdc, 0x9e, 0x10, 0x0,

    /* U+84DD "蓝" */
    0xff, 0xff, 0xfd, 0x4c, 0x29, 0xf5, 0x7e, 0xbf,
    0x80, 0x33, 0xfe, 0x6a, 0xdf, 0xfc,

    /* U+8A00 "言" */
    0xe, 0x1f, 0xfc, 0x0, 0x3f, 0xe0, 0x0, 0xff,
    0x80, 0x3, 0xfe, 0x60, 0xcf, 0xf9, 0x83, 0x0,

    /* U+8BA4 "认" */
    0x63, 0xc, 0x60, 0x8c, 0x1, 0x8e, 0x30, 0xc7,
    0x1d, 0xe3, 0xb6, 0x7c, 0xcf, 0xc, 0x20, 0x0,

    /* U+8BAF "讯" */
    0x6f, 0xc2, 0x4c, 0x4, 0xce, 0x4c, 0xe4, 0xc7,
    0xfc, 0x64, 0xc6, 0x4f, 0x74, 0xf7, 0x4e, 0x44,
    0x60,

    /* U+8BB0 "记" */
    0x0, 0x6, 0xfe, 0x20, 0x62, 0x6, 0xe0, 0x6e,
    0xfe, 0x6c, 0x6, 0xc0, 0x7c, 0x37, 0xc3, 0x7c,
    0x36, 0xff,

    /* U+8BBE "设" */
    0xe7, 0x8e, 0x90, 0xb2, 0xe, 0x6e, 0x80, 0xdf,
    0x9b, 0x33, 0xbc, 0x73, 0xf, 0xfc, 0x21, 0x0,

    /* U+8BD5 "试" */
    0x41, 0xcc, 0x3c, 0xbf, 0xf0, 0xce, 0x18, 0xdf,
    0x19, 0x63, 0xad, 0x76, 0xad, 0xdc, 0x1, 0x0,

    /* U+8BED "语" */
    0xef, 0xec, 0xc0, 0x3f, 0x7, 0xee, 0x64, 0xff,
    0xd8, 0x3, 0x7f, 0x7c, 0x6d, 0xfc, 0x31, 0x80,

    /* U+8BF7 "请" */
    0x41, 0x6, 0xfe, 0xf, 0xef, 0xff, 0xff, 0xf6,
    0xfe, 0x6f, 0xe7, 0xfe, 0x7f, 0xe6, 0xc6, 0x4c,
    0xe0,

    /* U+8D25 "败" */
    0xf6, 0x25, 0x8f, 0x7f, 0xf6, 0xfd, 0xbd, 0xcf,
    0x31, 0xde, 0xdd, 0xe2, 0x30,

    /* U+8D85 "超" */
    0x37, 0xe7, 0xb6, 0x33, 0xef, 0xee, 0xfc, 0x3,
    0x7e, 0x7e, 0x67, 0xe6, 0xf7, 0xef, 0x0, 0xbf,
    0xe0,

    /* U+8F6F "软" */
    0x26, 0x1f, 0xfd, 0xdd, 0xef, 0xad, 0xfd, 0xf6,
    0xc, 0xe7, 0xfc, 0xf6, 0xc7, 0x9c, 0xd1, 0x80,

    /* U+8F93 "输" */
    0x61, 0x1e, 0x73, 0xdb, 0x37, 0xfe, 0xf7, 0xff,
    0xff, 0xf9, 0xff, 0xff, 0xe5, 0xec, 0xbf, 0x0,

    /* U+8FBE "达" */
    0x43, 0x1c, 0x61, 0xbf, 0x87, 0xfe, 0x30, 0xc7,
    0x19, 0xe3, 0x66, 0x6c, 0x5f, 0xb, 0x7f, 0x80,

    /* U+8FDB "进" */
    0x4d, 0x8d, 0xb1, 0xff, 0x6, 0xce, 0xd8, 0xff,
    0x9b, 0x63, 0xec, 0xe8, 0x1f, 0x3, 0xff, 0x0,

    /* U+9000 "退" */
    0xcf, 0xcd, 0x98, 0x3f, 0x76, 0x6e, 0xfc, 0xdc,
    0xdb, 0xf3, 0x7e, 0x6e, 0xdf, 0x8b, 0xff, 0x80,

    /* U+9001 "送" */
    0x44, 0xdc, 0xd1, 0xbf, 0x81, 0x8e, 0x31, 0xff,
    0xd8, 0xc3, 0x3c, 0x6c, 0xff, 0xb, 0xff, 0x80,

    /* U+9009 "选" */
    0x49, 0x9d, 0xb1, 0xbf, 0x84, 0xcf, 0xfe, 0xcd,
    0x1b, 0xab, 0xe7, 0xe8, 0x1e, 0x3, 0xff, 0x80,

    /* U+901A "通" */
    0xcf, 0xec, 0xf8, 0x3f, 0xf5, 0xbe, 0xfe, 0xd6,
    0xdb, 0xfb, 0x5b, 0x6b, 0xfe, 0x3, 0x7f, 0x80,

    /* U+901F "速" */
    0x43, 0x6, 0xfe, 0x63, 0x0, 0xfe, 0xeb, 0x66,
    0xfe, 0x67, 0x87, 0xfe, 0x6b, 0x6f, 0x0, 0xdf,
    0xe0,

    /* U+914D "配" */
    0xff, 0xef, 0xd, 0xe1, 0xfe, 0x3f, 0xff, 0xfe,
    0x33, 0xc7, 0xf9, 0xcf, 0x3f, 0xef, 0x7, 0x80,

    /* U+91CD "重" */
    0x7f, 0xdf, 0xff, 0xff, 0xbf, 0xe6, 0x4c, 0xff,
    0x9f, 0xf3, 0xfe, 0x7f, 0xdf, 0xfc,

    /* U+91CF "量" */
    0x7f, 0xcf, 0xf9, 0xff, 0x7f, 0xf0, 0x0, 0xff,
    0x9f, 0xf3, 0xfe, 0x7f, 0xc0, 0x83, 0xff, 0x80,

    /* U+951A "锚" */
    0x66, 0xcf, 0xff, 0x1b, 0x7f, 0xf6, 0xff, 0xfa,
    0x7f, 0xfb, 0x69, 0x7d, 0x2f, 0xfd, 0x30, 0x80,

    /* U+952E "键" */
    0x5f, 0xfd, 0x96, 0x2f, 0xfc, 0x5f, 0xff, 0xdf,
    0xff, 0xfa, 0xdf, 0x7c, 0x8f, 0x81, 0xdf, 0x80,

    /* U+957F "长" */
    0x61, 0x99, 0xe6, 0xe1, 0xa0, 0xff, 0xd9, 0x6,
    0x61, 0xae, 0x79, 0xd8, 0x0,

    /* U+95ED "闭" */
    0x0, 0x3f, 0xf4, 0xc, 0x3, 0xff, 0xf3, 0xbc,
    0xef, 0x7b, 0xf6, 0xf9, 0xbc, 0xef, 0x7,

    /* U+9664 "除" */
    0xe2, 0x29, 0x4b, 0xdf, 0xfe, 0xe2, 0x28, 0x8b,
    0xfa, 0xa8, 0xeb, 0xa6, 0xb9, 0x60,

    /* U+9879 "项" */
    0xff, 0xfe, 0x61, 0x8c, 0x37, 0xf6, 0xf6, 0xde,
    0xdb, 0xdb, 0xfb, 0xf7, 0xc3, 0x9c, 0x20, 0x80,

    /* U+9ED8 "默" */
    0xfb, 0xba, 0xff, 0xb3, 0xff, 0xff, 0xfe, 0xc2,
    0x33, 0xee, 0xde, 0xbf, 0x38, 0x44,

    /* U+FF01 "！" */
    0xff, 0xf3, 0xc0,

    /* U+FF1A "：" */
    0xf0, 0x3c,

    /* U+FF1F "？" */
    0x7b, 0xfc, 0xc7, 0x38, 0xc3, 0x0, 0x30, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 69, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 65, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 88, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 7, .adv_w = 146, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 122, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 25, .adv_w = 176, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 152, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 46, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 50, .adv_w = 74, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 54, .adv_w = 74, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 58, .adv_w = 87, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 61, .adv_w = 126, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 66, .adv_w = 61, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 68, .adv_w = 79, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 69, .adv_w = 59, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 131, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 99, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 126, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 113, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 59, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 61, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 155, .adv_w = 126, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 126, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 167, .adv_w = 126, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 109, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 170, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 151, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 142, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 145, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 120, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 149, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 155, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 59, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 113, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 151, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 121, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 185, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 151, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 159, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 137, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 159, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 343, .adv_w = 136, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 131, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 148, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 152, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 387, .adv_w = 220, .box_w = 14, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 153, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 414, .adv_w = 148, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 423, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 73, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 437, .adv_w = 79, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 73, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 449, .adv_w = 96, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 452, .adv_w = 92, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 454, .adv_w = 66, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 456, .adv_w = 114, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 127, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 117, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 476, .adv_w = 127, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 122, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 83, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 498, .adv_w = 127, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 507, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 59, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 517, .adv_w = 59, .box_w = 4, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 524, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 532, .adv_w = 58, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 183, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 545, .adv_w = 122, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 124, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 558, .adv_w = 127, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 567, .adv_w = 127, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 576, .adv_w = 93, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 581, .adv_w = 107, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 587, .adv_w = 87, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 122, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 123, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 180, .box_w = 11, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 124, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 126, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 633, .adv_w = 107, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 79, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 647, .adv_w = 53, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 650, .adv_w = 79, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 659, .adv_w = 124, .box_w = 8, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 662, .adv_w = 192, .box_w = 11, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 665, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 681, .adv_w = 192, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 695, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 709, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 725, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 742, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 756, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 770, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 786, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 802, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 815, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 831, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 847, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 863, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 879, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 895, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 911, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 927, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 940, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 957, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 971, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 987, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1001, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1015, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1032, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1046, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1060, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1074, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1090, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1104, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1118, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1134, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1150, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1164, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1178, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1194, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1208, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1222, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1236, .adv_w = 192, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1254, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1268, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1282, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1298, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1312, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1326, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1340, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1356, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1372, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1389, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1405, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1419, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1435, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1451, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1467, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1482, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1496, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1512, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1529, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1546, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1563, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1579, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1596, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1610, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1624, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1640, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1656, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1673, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1689, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1705, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1721, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1737, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1751, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1767, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1783, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1799, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1815, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1829, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1845, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1859, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1875, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1891, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1907, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1921, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1937, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1953, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1966, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1982, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1996, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2009, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2025, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2039, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2055, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2069, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2084, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2100, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2114, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2130, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2146, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2160, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2176, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2193, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2207, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2220, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2233, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2250, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2266, .adv_w = 192, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2280, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2296, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2312, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2329, .adv_w = 192, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2347, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2363, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2379, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2395, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2412, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2425, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2442, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2458, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2474, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2490, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2506, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2522, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2538, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2554, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2570, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2587, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2603, .adv_w = 192, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2617, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2633, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2649, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2665, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2678, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2693, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2707, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2723, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2737, .adv_w = 192, .box_w = 2, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2740, .adv_w = 192, .box_w = 2, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2742, .adv_w = 192, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0}
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
    -4, -4, -7, -4, -4, -15, -4, -13,
    -8, -19, -6, -5, -5, -5, -3, -5,
    -4, -5, -5, -7, -14, -9, -14, -15,
    -5, -10, -15, -5, -10, -15, -10, -3,
    -1, -2, -4, -4, -4, -4, -4, -4,
    -5, -4, -6, -6, -2, -23, -23, -14,
    -2, -13, -12, -4, -2, -3, -14, -14,
    -10, -4, -2, -4, -1, -7, -7, -7,
    -7, -26, -3, -22, -14, -22, -3, -3,
    -3, -3, -3, -3, -9, -5, -9, -4,
    -5, -4, -3, -4, -7, -2, -4, -1,
    -4, -2, -4, -4, -4, -4, -4, -7,
    -2, -2, -4, -4, -2, -4, -6, -6,
    -6, -7, -3, -10, -10, -7, -2, -2,
    -3, -3, -3, -3, -2, -2, -2, -5,
    -12, -28, -2, -4, -10, -3, -3, -3,
    -3, -3, -3, -4, -2, -2, -8, -2,
    -2, -4, -6, -8, -3, -5, -12, -2,
    -2, -5, -6, -4, -5, -4, -8, -12,
    -12, -13, -12, -12, -6, -10, -6, -10,
    -10, -10, -10, -10, -10, -2, -9, -10,
    -15, -12, -15, -8, -8, -8, -8, -26,
    -4, -23, -16, -26, -4, -12, -2, -17,
    -10, -17, -6, -6, -6, -7, -3, -10,
    -10, -7, -2, -8, -16, -38, -4, -7,
    -6, -13, -11, -4, -11, -10, -10, -10,
    -10, -10, -10, -7, -8, -5, -6, -4,
    -4, -8, -10, -2, -3, -1, -1, -6,
    -1, -1, -4, -3, -2, -6, -3, -4,
    -4, -4, -4, -4, -4, -4, -4, -2,
    -5, -2, -4, -4, -2, -4, -3, -12,
    -26, -7, -7, -36, -7, -7, -5, -7,
    -19, -19, -19, -19, -10, -19, -17, -17,
    -19, -17, -19, -17, -25, -4, -19, -21,
    -19, -21, -21, -22, -3, -2, -4, -13,
    -22, -7, -7, -29, -7, -7, -2, -17,
    -15, -15, -15, -7, -15, -15, -15, -15,
    -15, -15, -15, -14, -4, -14, -6, -6,
    -8, -6, -8, -7, -14, -3, -3, -16,
    -3, -3, -1, -10, -8, -8, -8, -4,
    -8, -9, -9, -8, -9, -8, -9, -9,
    -2, -8, -6, -6, -8, -6, -8, -4,
    -10, -10, -10, -10, -2, -7, -4, -2,
    -7, -7, -7, -4, -7, -2, -3, -3,
    -7, -3, -7, -3, -6, -10, -8, -16,
    -14, -16, -15, -22, -10, -10, -31, -10,
    -10, -6, -29, -27, -27, -27, -10, -27,
    -29, -29, -27, -29, -27, -29, -25, -12,
    -27, -19, -18, -20, -19, -21, -8, -10,
    -10, -10, -10, -3, -3, -3, -3, -3,
    -3, -3, -6, -6, -8, -8, -8, 18,
    -17, -16, -10, -3, -30, -1, -2, -1,
    -1, -3, -19, -15, -8, -7, -27, -2,
    -6, -2, -9, -6, -2, -19, -9, -7,
    -3, -23, -6, -7, -6, -19, -12, -7,
    -6, -22, -4, -1, -2, -4, -3, -11,
    -12, -5, -4, -4, -4, -4, -4, -4,
    -3, -3, -17, -15, -10, -27, 1, -17,
    -16, -10, -3, -30, -1, -2, -1, -1,
    -3, -4, -4, -4, -4, -28, -2, -9,
    -6, -15, -3, -9, -9, -9, -9, -2,
    -9, -9, -4, -4, -5, -1, -2, -2,
    -2, -2, -2, -2, -1, -2, -17, -16,
    -10, -3, -30, -1, -2, -1, -1, -17,
    -16, -10, -3, -30, -1, -2, -1, -1,
    -3, -19, -15, -8, -7, -27, -2, -6,
    -2, -9, -6, -2, -3, -19, -15, -8,
    -7, -27, -2, -6, -2, -9, -6, -2,
    -17, -15, -10, -27, 1, -10, -17, -17,
    -14, -10, -5, -4, -4, -4, -4, -4,
    -4, -3, -5, -24, -10, -8, -6, -23,
    -4, -4, -4, -2, -10, -2, -2, -2,
    -2, -2, -2, -2, -1, -17, -15, -10,
    -27, 1, -8, -9, -19, -21, -6, -6,
    -16, -19, -10, -4, -6, -6, -6, -6,
    -6, -6, -2, -3, -5, -12, -19, -6,
    -6, -14, -18, -8, -3, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -21, -8, -8, -20, -3, -9, -9,
    -9, -9, -2, -9, -9, -4, -2, -8,
    -9, -19, -21, -6, -6, -16, -19, -10,
    -4, -6, -6, -6, -6, -6, -6, -2,
    -2, -2, -2, -2, -2, -21, -6, -9,
    -21, -4, -4, -4, -4, -4, -4, -2,
    -2
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 673,
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
const lv_font_t font_blod_12 = {
#else
lv_font_t font_blod_12 = {
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



#endif /*#if FONT_BLOD_12*/

