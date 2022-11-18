/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --font /home/developer/sources/epink_desktop/squareline_studio_project/assets/NeverMindHand-Bold.ttf -o /home/developer/sources/epink_desktop/squareline_studio_project/assets/ui_font_NeverMindHandBold12.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_NEVERMINDHANDBOLD12
#define UI_FONT_NEVERMINDHANDBOLD12 1
#endif

#if UI_FONT_NEVERMINDHANDBOLD12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xc3, 0xc0,

    /* U+0022 "\"" */
    0xcf, 0x3c, 0xf3,

    /* U+0023 "#" */
    0x1a, 0x1e, 0x7f, 0x7f, 0x1e, 0x7f, 0x7f, 0x1e,
    0x12,

    /* U+0024 "$" */
    0x0, 0x79, 0xf3, 0x6, 0x7, 0x7, 0x43, 0xc6,
    0xf8, 0x60,

    /* U+0025 "%" */
    0x62, 0x7b, 0x3f, 0x1d, 0x81, 0x81, 0xd8, 0xde,
    0xcf, 0x67, 0x0,

    /* U+0026 "&" */
    0x78, 0xf8, 0xcc, 0xf8, 0x78, 0x7e, 0xde, 0xff,
    0x7b,

    /* U+0027 "'" */
    0xfc,

    /* U+0028 "(" */
    0x33, 0x66, 0xcc, 0xcc, 0xce, 0x66,

    /* U+0029 ")" */
    0xcc, 0x66, 0x33, 0x33, 0x36, 0x66,

    /* U+002A "*" */
    0x27, 0xdd, 0xf2, 0x0,

    /* U+002B "+" */
    0x30, 0x60, 0xd7, 0xef, 0xc2, 0x4, 0x0,

    /* U+002C "," */
    0xfe,

    /* U+002D "-" */
    0xff,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x8, 0xc6, 0x63, 0x19, 0x8c, 0x66, 0x30, 0x0,

    /* U+0030 "0" */
    0x39, 0xec, 0xf3, 0xcf, 0x3c, 0xdf, 0x78,

    /* U+0031 "1" */
    0xdb, 0x6d, 0xb7, 0x40,

    /* U+0032 "2" */
    0x79, 0xfb, 0x34, 0x60, 0xc3, 0x1c, 0x7f, 0xfc,

    /* U+0033 "3" */
    0x7c, 0xf8, 0x61, 0xe3, 0xe0, 0xf1, 0xbe, 0x38,

    /* U+0034 "4" */
    0x18, 0x1c, 0x3c, 0x2c, 0x6c, 0x7f, 0x7e, 0xc,
    0xc,

    /* U+0035 "5" */
    0x7c, 0xf9, 0x3, 0xc7, 0xc1, 0x83, 0x7e, 0xf0,

    /* U+0036 "6" */
    0x10, 0x86, 0x1c, 0xfb, 0x2c, 0xbe, 0x70,

    /* U+0037 "7" */
    0xff, 0xf0, 0x86, 0x10, 0xc6, 0x18, 0x40,

    /* U+0038 "8" */
    0x73, 0xec, 0xbe, 0x73, 0x6c, 0xff, 0x78,

    /* U+0039 "9" */
    0x7b, 0xec, 0xfe, 0x78, 0xc3, 0x8, 0x20,

    /* U+003A ":" */
    0xf0, 0x3c,

    /* U+003B ";" */
    0xf0, 0xfe,

    /* U+003C "<" */
    0x19, 0xee, 0x38, 0x78, 0x70, 0xc0,

    /* U+003D "=" */
    0xfb, 0xe7, 0xff,

    /* U+003E ">" */
    0x1, 0xc3, 0xc7, 0x39, 0xc4, 0x0,

    /* U+003F "?" */
    0x73, 0xed, 0xb6, 0x18, 0xc3, 0x0, 0x30, 0xc0,

    /* U+0040 "@" */
    0x1e, 0x3f, 0x9e, 0xff, 0xbf, 0x5f, 0xaf, 0xfd,
    0xf4, 0x7c, 0x1c, 0x0,

    /* U+0041 "A" */
    0x10, 0x70, 0xe1, 0x66, 0xcf, 0xdf, 0xe1, 0x2,

    /* U+0042 "B" */
    0xf3, 0xfc, 0xf3, 0xfb, 0x3c, 0x7f, 0xf8,

    /* U+0043 "C" */
    0x1e, 0x7f, 0xe3, 0xc0, 0xc0, 0xc0, 0xe3, 0x7f,
    0x3e,

    /* U+0044 "D" */
    0xf9, 0xfb, 0x3e, 0x3c, 0x78, 0xf3, 0x7e, 0xf0,

    /* U+0045 "E" */
    0xfb, 0xec, 0x3f, 0xff, 0xc, 0x7f, 0xf8,

    /* U+0046 "F" */
    0xff, 0xfc, 0x30, 0xff, 0xc, 0x30, 0xc0,

    /* U+0047 "G" */
    0x3c, 0x7e, 0xe0, 0xc6, 0xcf, 0xc3, 0xe7, 0x7e,
    0x3c,

    /* U+0048 "H" */
    0xcf, 0x3c, 0xf3, 0xff, 0x3c, 0xf3, 0xcc,

    /* U+0049 "I" */
    0xff, 0xff, 0xc0,

    /* U+004A "J" */
    0x18, 0xc6, 0x31, 0x8e, 0x7f, 0x70,

    /* U+004B "K" */
    0xc7, 0x9b, 0x67, 0x8f, 0x1f, 0x37, 0x67, 0xc6,

    /* U+004C "L" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x3f, 0x7c,

    /* U+004D "M" */
    0x40, 0xf8, 0xff, 0x7f, 0x7b, 0xdc, 0xf2, 0x3c,
    0xf, 0x3, 0x40, 0xc0,

    /* U+004E "N" */
    0x0, 0xc3, 0xe3, 0xf3, 0xdb, 0xdb, 0xcf, 0xc7,
    0xc2,

    /* U+004F "O" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e,
    0x3c,

    /* U+0050 "P" */
    0x7b, 0xfc, 0xf1, 0xdb, 0xcc, 0x30, 0x40,

    /* U+0051 "Q" */
    0x1e, 0x1f, 0x1c, 0xcc, 0x66, 0x37, 0x79, 0xb8,
    0xff, 0x39, 0x80,

    /* U+0052 "R" */
    0xf9, 0xfb, 0x16, 0x2d, 0xdf, 0x33, 0x62, 0xc4,

    /* U+0053 "S" */
    0x3c, 0xf9, 0x83, 0x1, 0x81, 0xb1, 0xff, 0x7c,

    /* U+0054 "T" */
    0x7f, 0xbf, 0xc3, 0x1, 0x80, 0xc0, 0x60, 0x30,
    0x18, 0xc, 0x0,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe6, 0x7e,
    0x3c,

    /* U+0056 "V" */
    0x81, 0xc3, 0x43, 0x66, 0x66, 0x3c, 0x3c, 0x38,
    0x18,

    /* U+0057 "W" */
    0xc0, 0x34, 0x43, 0x66, 0x66, 0x66, 0x26, 0x43,
    0xfc, 0x3f, 0xc1, 0x9c, 0x1, 0x80,

    /* U+0058 "X" */
    0x41, 0xb1, 0xcd, 0xc3, 0xc1, 0xc1, 0xf1, 0xdc,
    0xc6, 0xc1, 0x0,

    /* U+0059 "Y" */
    0x3, 0x8f, 0x1b, 0x66, 0xc7, 0x6, 0xc, 0x18,
    0x30,

    /* U+005A "Z" */
    0x7e, 0xfe, 0xc, 0x18, 0x18, 0x30, 0x62, 0xfe,
    0xf8,

    /* U+005B "[" */
    0x7e, 0xcc, 0xcc, 0xcc, 0xce, 0x60,

    /* U+005C "\\" */
    0xc6, 0x18, 0xc6, 0x18, 0xc7, 0x18, 0xc2,

    /* U+005D "]" */
    0x67, 0x33, 0x33, 0x33, 0x3f, 0xe0,

    /* U+005E "^" */
    0x6, 0xfd,

    /* U+005F "_" */
    0xff, 0xc0,

    /* U+0060 "`" */
    0xb0,

    /* U+0061 "a" */
    0x73, 0xe9, 0x9e, 0xcf, 0xf7, 0x80,

    /* U+0062 "b" */
    0xc1, 0x83, 0xf7, 0xec, 0x78, 0xf1, 0xff, 0xfc,

    /* U+0063 "c" */
    0x39, 0xfc, 0x30, 0xc1, 0xf3, 0x80,

    /* U+0064 "d" */
    0xc, 0x37, 0xff, 0xcf, 0x3c, 0xff, 0x7c,

    /* U+0065 "e" */
    0x7b, 0xfc, 0xff, 0xc1, 0xf3, 0x80,

    /* U+0066 "f" */
    0x39, 0xff, 0xf6, 0x31, 0x84, 0x20,

    /* U+0067 "g" */
    0x3d, 0xfc, 0x71, 0xcf, 0xf7, 0x5f, 0x78,

    /* U+0068 "h" */
    0xc3, 0xd, 0xbf, 0xef, 0xbc, 0xf3, 0xc4,

    /* U+0069 "i" */
    0xf3, 0xff, 0xf0,

    /* U+006A "j" */
    0x13, 0x33, 0x33, 0x33, 0x37, 0xe0,

    /* U+006B "k" */
    0xc3, 0xc, 0xf6, 0xf3, 0xcd, 0xb3, 0xc4,

    /* U+006C "l" */
    0xdb, 0x6d, 0xb6, 0xec,

    /* U+006D "m" */
    0xf7, 0x7f, 0xf7, 0x7b, 0x3d, 0x9e, 0xcf, 0x66,

    /* U+006E "n" */
    0xfb, 0xfc, 0xf3, 0xcf, 0x30, 0xc0,

    /* U+006F "o" */
    0x3c, 0xfb, 0x1e, 0x3c, 0x7f, 0x8e, 0x0,

    /* U+0070 "p" */
    0x81, 0xfb, 0xfe, 0x3c, 0x7f, 0xfe, 0x60, 0xc1,
    0x80,

    /* U+0071 "q" */
    0x3e, 0xff, 0x96, 0x2c, 0xdf, 0x9f, 0x3, 0x6,

    /* U+0072 "r" */
    0xff, 0xec, 0xcc, 0xc0,

    /* U+0073 "s" */
    0x39, 0xf6, 0xe, 0x4f, 0xf3, 0x80,

    /* U+0074 "t" */
    0x30, 0xcf, 0xff, 0x30, 0xc3, 0xf, 0x1c,

    /* U+0075 "u" */
    0xf, 0x3c, 0xf3, 0xcf, 0x3f, 0x9c,

    /* U+0076 "v" */
    0x7, 0x34, 0xda, 0x38, 0xe3, 0x0,

    /* U+0077 "w" */
    0xc8, 0xf2, 0x34, 0xd9, 0xb6, 0x6f, 0xf, 0xc3,
    0x20,

    /* U+0078 "x" */
    0xcf, 0x37, 0x8c, 0x7b, 0xbc, 0x40,

    /* U+0079 "y" */
    0xc7, 0x8d, 0xb3, 0x63, 0x87, 0x6, 0x38, 0x70,

    /* U+007A "z" */
    0xfd, 0xf8, 0x61, 0xc7, 0x1f, 0xde, 0x0,

    /* U+007B "{" */
    0x37, 0x66, 0x6c, 0x66, 0x63, 0x30,

    /* U+007C "|" */
    0xdb, 0x6d, 0xb6, 0xfd, 0x80,

    /* U+007D "}" */
    0x63, 0x8c, 0x63, 0x1c, 0xc6, 0x33, 0x18,

    /* U+007E "~" */
    0xf7, 0xfe, 0x70
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 56, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 60, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 116, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 7, .adv_w = 139, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 26, .adv_w = 166, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 126, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 53, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 47, .adv_w = 89, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 53, .adv_w = 88, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 59, .adv_w = 87, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 63, .adv_w = 131, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 70, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 71, .adv_w = 89, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 72, .adv_w = 72, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 88, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 81, .adv_w = 104, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 90, .box_w = 3, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 117, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 126, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 120, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 104, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 102, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 72, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 73, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 157, .adv_w = 119, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 122, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 166, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 109, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 180, .adv_w = 158, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 192, .adv_w = 122, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 120, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 147, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 138, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 119, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 109, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 144, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 129, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 54, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 100, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 181, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 152, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 140, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 145, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 121, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 129, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 137, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 353, .adv_w = 144, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 144, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 193, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 150, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 124, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 405, .adv_w = 132, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 414, .adv_w = 85, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 420, .adv_w = 88, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 427, .adv_w = 79, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 433, .adv_w = 100, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 435, .adv_w = 69, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 437, .adv_w = 113, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 438, .adv_w = 106, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 108, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 117, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 108, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 471, .adv_w = 94, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 477, .adv_w = 110, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 484, .adv_w = 117, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 56, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 71, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 500, .adv_w = 111, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 73, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 511, .adv_w = 173, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 117, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 525, .adv_w = 115, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 532, .adv_w = 125, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 541, .adv_w = 130, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 549, .adv_w = 87, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 553, .adv_w = 106, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 559, .adv_w = 107, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 566, .adv_w = 122, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 572, .adv_w = 105, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 578, .adv_w = 158, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 587, .adv_w = 106, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 111, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 601, .adv_w = 120, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 608, .adv_w = 80, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 614, .adv_w = 67, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 619, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 626, .adv_w = 141, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 2, 0, 0, 0, 0, 3, 0,
    4, 5, 6, 7, 8, 9, 0, 10,
    11, 0, 12, 0, 0, 0, 0, 0,
    0, 0, 13, 14, 15, 16, 0, 17,
    5, 0, 0, 18, 19, 20, 0, 0,
    5, 21, 5, 22, 23, 24, 18, 25,
    26, 27, 11, 28, 0, 0, 0, 0,
    0, 0, 29, 1, 1, 30, 1, 31,
    32, 30, 30, 0, 33, 30, 30, 30,
    1, 1, 0, 34, 32, 32, 32, 35,
    35, 36, 35, 37, 0, 0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 0, 1, 0, 0, 2, 0,
    0, 0, 3, 0, 0, 4, 5, 4,
    6, 7, 8, 9, 10, 11, 12, 11,
    13, 14, 15, 16, 14, 0, 0, 0,
    0, 0, 6, 17, 7, 17, 17, 0,
    7, 17, 0, 18, 0, 17, 0, 0,
    7, 17, 7, 17, 19, 20, 21, 22,
    22, 23, 24, 25, 0, 0, 0, 0,
    0, 0, 26, 2, 27, 27, 27, 28,
    27, 2, 29, 30, 2, 31, 32, 32,
    27, 32, 27, 33, 34, 35, 32, 36,
    36, 37, 36, 37, 0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, -3, -4, 0, 0, -6, 6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, -11, -11, -22,
    0, 0, 0, -3, 0, -11, 0, 0,
    0, 0, -3, -5, -7, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -7,
    0, 0, 0, 0, 0, 0, 5, 0,
    0, 0, 0, -8, 0, -7, 0, -7,
    0, 5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -21, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -9, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -11, -15, -10, -9, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -8, 0, -8, 0, -8,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -8, 0, -6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, -6, 0, -4, -6, 0, -2, 0,
    0, 0, 0, 0, 0, -6, 0, -8,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, 0, 0,
    0, -11, 0, -1, 0, 0, 0, 0,
    0, 0, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -38, -18, -21,
    -7, 0, -6, 0, -19, -6, 0, -11,
    -8, -17, 0, 0, -11, 0, -8, 0,
    0, 0, 0, -14, -14, 0, 0, 0,
    0, -11, 0, -20, 0, 0, -6, 0,
    0, 0, -19, 0, -20, 0, 0, 0,
    0, -13, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, 0, -9, 0, 0, 0, 0, 0,
    0, 0, -17, 0, 1, 0, 0, -21,
    -11, -16, 0, -26, 0, -6, -2, -8,
    0, -4, -7, 0, 0, 0, 0, -12,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -11,
    -14, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, -8, 0, 0,
    0, 0, 0, -6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 2, 0, 1, -6, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -14, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -14, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -19, 0, -9, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, -1, 0, 0, -11, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -20, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -11, 0,
    0, 0, 0, -2, -5, -6, 0, 0,
    0, 0, 0, 0, -8, -7, 0, -9,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -24, -8, -24, 0, -36, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -15, -21, 0, 0, 0, 0, -28,
    0, -16, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -34, -8, 0,
    0, -7, -18, -9, 0, -7, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -7,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -9, -7, -8, 4, 0,
    2, 0, -3, -5, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -10, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, -6, 0, -19, 5,
    -23, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -14, -21, 0, -3,
    -11, 0, -11, -17, -20, 0, -3, 0,
    0, 0, 0, -21, 5, -16, -11, 0,
    0, 0, -7, 0, 0, 0, -6, 0,
    0, 0, -9, 0, -8, 0, 0, 0,
    0, -11, -10, 0, 0, -4, 0, -12,
    0, -17, 0, -11, -11, 0, -3, 0,
    -13, 5, -13, -6, 0, 0, 0, -9,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, -8, 0, 0, 0, 0, -7, -11,
    0, 0, 0, 0, -11, 0, -11, 0,
    0, -11, 0, 0, 0, 0, -14, 0,
    -12, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, -14, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -7, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, 0, -11, 0,
    0, 0, 0, 0, -7, 0, 0, 0,
    0, -22, 0, -17, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -9,
    -10, 0, 0, -5, 0, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -11, 0,
    -15, 0, -3, 0, 0, 0, 0, 0,
    -11, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 5, -7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -22, -17, -17, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, -7,
    0, 0, 0, 0, 0, 0, -6, 0,
    3, 0, 0, 0, 0, -21, 0, -21,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -11, 0, 4, 0, 0,
    0, 0, 0, -3, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -14, 0, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -7, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 37,
    .right_class_cnt     = 37,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t ui_font_NeverMindHandBold12 = {
#else
lv_font_t ui_font_NeverMindHandBold12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_NEVERMINDHANDBOLD12*/

