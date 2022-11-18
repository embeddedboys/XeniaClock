/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --font /home/developer/sources/epink_desktop/squareline_studio_project/assets/NeverMindSemiSerif-Bold.ttf -o /home/developer/sources/epink_desktop/squareline_studio_project/assets/ui_font_NeverMindSemiSerifBold12.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_NEVERMINDSEMISERIFBOLD12
#define UI_FONT_NEVERMINDSEMISERIFBOLD12 1
#endif

#if UI_FONT_NEVERMINDSEMISERIFBOLD12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xf0, 0xc0,

    /* U+0022 "\"" */
    0xff, 0xf0,

    /* U+0023 "#" */
    0x12, 0x19, 0x1f, 0xc6, 0xc3, 0x61, 0xb3, 0xfc,
    0x48, 0x64, 0x0,

    /* U+0024 "$" */
    0x7b, 0x1c, 0x3c, 0xf9, 0xf1, 0xc3, 0x8d, 0xe0,

    /* U+0025 "%" */
    0x63, 0x3c, 0x8f, 0x61, 0x90, 0x8, 0x2, 0xe1,
    0x6c, 0x9b, 0x23, 0x80,

    /* U+0026 "&" */
    0x78, 0x66, 0x33, 0xf, 0x83, 0x7, 0xd3, 0x79,
    0x9c, 0x7b, 0x0,

    /* U+0027 "'" */
    0xfc,

    /* U+0028 "(" */
    0x2d, 0x6d, 0xb6, 0x4c, 0x80,

    /* U+0029 ")" */
    0x99, 0x36, 0xdb, 0x7a, 0x0,

    /* U+002A "*" */
    0x23, 0x9e, 0x40,

    /* U+002B "+" */
    0x30, 0xc3, 0x3f, 0x30, 0xc3, 0x0,

    /* U+002C "," */
    0xe8,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0xc, 0x18, 0x20, 0xc1, 0x86, 0xc, 0x10, 0x60,
    0xc3, 0x0,

    /* U+0030 "0" */
    0x79, 0x3c, 0xf3, 0xcf, 0x3c, 0xf2, 0x78,

    /* U+0031 "1" */
    0xed, 0xb6, 0xdb, 0x60,

    /* U+0032 "2" */
    0x7b, 0x30, 0xc3, 0x1c, 0xe7, 0x38, 0xfc,

    /* U+0033 "3" */
    0x7e, 0x18, 0x61, 0xc3, 0xe0, 0xc1, 0xa3, 0x7c,

    /* U+0034 "4" */
    0xc, 0x38, 0xf1, 0xe6, 0xd9, 0xbf, 0x86, 0xc,

    /* U+0035 "5" */
    0x7d, 0xc, 0x3e, 0xc, 0x30, 0xe3, 0xf8,

    /* U+0036 "6" */
    0x18, 0x30, 0xc1, 0xe6, 0x6c, 0xd1, 0xb3, 0x3c,

    /* U+0037 "7" */
    0xfc, 0x31, 0x86, 0x10, 0xc3, 0x18, 0x60,

    /* U+0038 "8" */
    0x7b, 0x3c, 0xff, 0x7b, 0x7c, 0xf3, 0x78,

    /* U+0039 "9" */
    0x7b, 0x3c, 0xf3, 0x78, 0x63, 0xc, 0x30,

    /* U+003A ":" */
    0xc0, 0x30,

    /* U+003B ";" */
    0xc0, 0xfc,

    /* U+003C "<" */
    0x4, 0xff, 0x30, 0xf0, 0xf0, 0xc0,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0x83, 0x83, 0x83, 0x3b, 0x88, 0x0,

    /* U+003F "?" */
    0x79, 0x30, 0xc7, 0x38, 0xc3, 0x0, 0x30,

    /* U+0040 "@" */
    0x1f, 0xe, 0x39, 0x83, 0xef, 0xbf, 0x37, 0xe6,
    0xfc, 0xdf, 0xfe, 0x60, 0x7, 0x80,

    /* U+0041 "A" */
    0x8, 0x4, 0x7, 0x2, 0x83, 0x61, 0xb1, 0xfc,
    0x86, 0xc1, 0x0,

    /* U+0042 "B" */
    0xfb, 0x3c, 0xf2, 0xfb, 0x3c, 0xf3, 0xf8,

    /* U+0043 "C" */
    0x3e, 0x63, 0xc2, 0xc0, 0xc0, 0xc1, 0xc1, 0x63,
    0x3c,

    /* U+0044 "D" */
    0xfc, 0x66, 0x63, 0x63, 0x63, 0x63, 0x63, 0x66,
    0x7c,

    /* U+0045 "E" */
    0xff, 0xc, 0x30, 0xfb, 0xc, 0x30, 0xfc,

    /* U+0046 "F" */
    0xff, 0xc, 0x30, 0xfb, 0xc, 0x30, 0xc0,

    /* U+0047 "G" */
    0x3e, 0x62, 0xe0, 0xc0, 0xc0, 0xc7, 0xc7, 0x67,
    0x7b,

    /* U+0048 "H" */
    0xc7, 0x8f, 0x1e, 0x3f, 0xf8, 0xf1, 0xe3, 0xc6,

    /* U+0049 "I" */
    0xed, 0xb6, 0xdb, 0xe0,

    /* U+004A "J" */
    0x1c, 0x61, 0x86, 0x18, 0x61, 0xa6, 0xf0,

    /* U+004B "K" */
    0xc6, 0xcc, 0xdc, 0xd8, 0xf0, 0xd8, 0xcc, 0xce,
    0xc6,

    /* U+004C "L" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xfc,

    /* U+004D "M" */
    0x80, 0xe0, 0xf8, 0xfe, 0xfd, 0xde, 0x4f, 0x7,
    0x83, 0xc1, 0x80,

    /* U+004E "N" */
    0x83, 0xc3, 0xe3, 0xf3, 0xdb, 0xcf, 0xc7, 0xc3,
    0xc1,

    /* U+004F "O" */
    0x3e, 0x31, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x6,
    0xc6, 0x3e, 0x0,

    /* U+0050 "P" */
    0x7c, 0xcd, 0x9b, 0x3f, 0xcc, 0x18, 0x30, 0x60,

    /* U+0051 "Q" */
    0x3e, 0x31, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x1e,
    0xc6, 0x3f, 0x80,

    /* U+0052 "R" */
    0xf9, 0x9b, 0x36, 0x6f, 0x9b, 0x36, 0x66, 0xcc,

    /* U+0053 "S" */
    0x7f, 0x3c, 0x3c, 0x7c, 0xf0, 0xe3, 0xf8,

    /* U+0054 "T" */
    0xfe, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18, 0x30,

    /* U+0055 "U" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xa6, 0x78,

    /* U+0056 "V" */
    0xc1, 0xb1, 0x98, 0xc6, 0xc3, 0x60, 0xe0, 0x70,
    0x30, 0x8, 0x0,

    /* U+0057 "W" */
    0xc6, 0x13, 0x31, 0x98, 0x8c, 0x6e, 0xc3, 0x76,
    0xe, 0xe0, 0x77, 0x1, 0x10, 0x8, 0x80,

    /* U+0058 "X" */
    0x61, 0x8c, 0xc3, 0xe0, 0x78, 0x1c, 0x7, 0x83,
    0x31, 0xce, 0x61, 0x80,

    /* U+0059 "Y" */
    0xc3, 0x67, 0x76, 0x3c, 0x3c, 0x18, 0x18, 0x18,
    0x18,

    /* U+005A "Z" */
    0xfe, 0x18, 0x70, 0xc3, 0x6, 0x18, 0x30, 0xfe,

    /* U+005B "[" */
    0xfb, 0x6d, 0xb6, 0xdb, 0x80,

    /* U+005C "\\" */
    0xc2, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6,

    /* U+005D "]" */
    0xed, 0xb6, 0xdb, 0x6f, 0x80,

    /* U+005E "^" */
    0x63, 0x3d, 0x20,

    /* U+005F "_" */
    0xf8,

    /* U+0060 "`" */
    0x40,

    /* U+0061 "a" */
    0x3e, 0xdf, 0x1e, 0x3c, 0x79, 0xdf, 0x80,

    /* U+0062 "b" */
    0xc1, 0x83, 0xf6, 0x7c, 0x78, 0xf1, 0xe7, 0xfc,

    /* U+0063 "c" */
    0x3d, 0x9c, 0x30, 0xc3, 0x97, 0xc0,

    /* U+0064 "d" */
    0x6, 0xc, 0xfb, 0x3c, 0x78, 0xf1, 0xe7, 0x7e,

    /* U+0065 "e" */
    0x78, 0x9b, 0x17, 0xfc, 0x18, 0x9f, 0x0,

    /* U+0066 "f" */
    0x1, 0xcc, 0xf3, 0x18, 0xc6, 0x31, 0x8d, 0xc0,

    /* U+0067 "g" */
    0x3e, 0xcf, 0x1e, 0x3c, 0x79, 0xdf, 0x83, 0x7c,

    /* U+0068 "h" */
    0xc3, 0xf, 0xbb, 0xcf, 0x3c, 0xf3, 0xcc,

    /* U+0069 "i" */
    0xc3, 0x6d, 0xb7, 0xe0,

    /* U+006A "j" */
    0x30, 0x7, 0x33, 0x33, 0x33, 0x3e,

    /* U+006B "k" */
    0xc1, 0x83, 0x36, 0xed, 0x9e, 0x36, 0x6c, 0xcc,

    /* U+006C "l" */
    0xdb, 0x6d, 0xb7, 0xe0,

    /* U+006D "m" */
    0xfb, 0xb3, 0xbc, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xcc,

    /* U+006E "n" */
    0xfb, 0xbc, 0xf3, 0xcf, 0x3c, 0xc0,

    /* U+006F "o" */
    0x38, 0xdb, 0x1e, 0x3c, 0x6d, 0x8e, 0x0,

    /* U+0070 "p" */
    0xfe, 0x67, 0x63, 0x63, 0x63, 0x67, 0x7e, 0x60,
    0x60,

    /* U+0071 "q" */
    0x3e, 0xdf, 0x1e, 0x3c, 0x79, 0xdf, 0x83, 0x6,

    /* U+0072 "r" */
    0xff, 0x31, 0x8c, 0x63, 0x0,

    /* U+0073 "s" */
    0x7e, 0x78, 0xf1, 0xcf, 0xc0,

    /* U+0074 "t" */
    0x66, 0xf6, 0x66, 0x67, 0x70,

    /* U+0075 "u" */
    0xcd, 0x9b, 0x36, 0x6c, 0xdb, 0x9f, 0x80,

    /* U+0076 "v" */
    0xc6, 0x99, 0xb3, 0xc3, 0x86, 0x4, 0x0,

    /* U+0077 "w" */
    0xcc, 0x6c, 0x99, 0x9b, 0x17, 0xc3, 0xb8, 0x36,
    0x4, 0x40,

    /* U+0078 "x" */
    0x66, 0x3c, 0x1c, 0x1c, 0x3c, 0x66, 0x66,

    /* U+0079 "y" */
    0xc6, 0xcd, 0x91, 0x63, 0xc7, 0x6, 0xc, 0x70,

    /* U+007A "z" */
    0xfc, 0x63, 0x8c, 0x61, 0x8f, 0xc0,

    /* U+007B "{" */
    0x19, 0x8c, 0x63, 0x70, 0xc6, 0x31, 0x86,

    /* U+007C "|" */
    0xff, 0xff, 0xff,

    /* U+007D "}" */
    0xc6, 0x66, 0x63, 0x66, 0x66, 0xc0,

    /* U+007E "~" */
    0xe0, 0x70
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 56, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 61, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 82, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 6, .adv_w = 140, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 122, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 176, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 141, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 42, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 49, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 54, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 59, .adv_w = 89, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 62, .adv_w = 116, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 59, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 69, .adv_w = 84, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 70, .adv_w = 61, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 71, .adv_w = 105, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 81, .adv_w = 114, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 78, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 110, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 111, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 133, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 116, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 130, .adv_w = 113, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 110, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 61, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 60, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 155, .adv_w = 110, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 113, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 164, .adv_w = 110, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 106, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 177, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 191, .adv_w = 138, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 209, .adv_w = 140, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 138, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 111, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 109, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 241, .adv_w = 141, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 67, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 93, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 133, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 109, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 170, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 143, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 150, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 155, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 335, .adv_w = 131, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 119, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 145, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 377, .adv_w = 204, .box_w = 13, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 156, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 135, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 76, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 426, .adv_w = 88, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 433, .adv_w = 73, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 438, .adv_w = 98, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 441, .adv_w = 68, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 442, .adv_w = 113, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 443, .adv_w = 122, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 119, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 111, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 113, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 479, .adv_w = 87, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 487, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 495, .adv_w = 114, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 55, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 56, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 512, .adv_w = 114, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 520, .adv_w = 53, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 524, .adv_w = 174, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 114, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 539, .adv_w = 122, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 546, .adv_w = 121, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 555, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 563, .adv_w = 83, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 93, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 573, .adv_w = 77, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 578, .adv_w = 115, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 113, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 592, .adv_w = 173, .box_w = 11, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 602, .adv_w = 124, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 609, .adv_w = 116, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 617, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 84, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 630, .adv_w = 66, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 633, .adv_w = 84, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 639, .adv_w = 116, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 3}
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
    0, 0, 0, 0, 0, 0, 1, 2,
    0, 0, 0, 3, 0, 4, 5, 4,
    6, 7, 0, 8, 9, 10, 0, 11,
    12, 13, 14, 0, 0, 0, 0, 0,
    0, 0, 15, 16, 17, 18, 0, 19,
    0, 0, 0, 20, 21, 22, 0, 0,
    7, 23, 7, 24, 25, 26, 20, 27,
    28, 29, 12, 30, 0, 31, 0, 0,
    0, 0, 32, 1, 1, 33, 1, 34,
    32, 35, 36, 0, 37, 38, 32, 35,
    1, 1, 33, 39, 40, 0, 32, 41,
    41, 42, 41, 43, 0, 0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 0, 1, 0, 2, 3, 4,
    0, 0, 5, 6, 0, 7, 8, 7,
    9, 10, 0, 11, 12, 13, 14, 13,
    15, 2, 16, 17, 18, 0, 0, 0,
    0, 0, 9, 0, 10, 0, 0, 0,
    10, 0, 0, 19, 0, 0, 20, 0,
    10, 0, 10, 0, 21, 22, 23, 24,
    24, 25, 26, 27, 0, 28, 29, 0,
    0, 0, 30, 3, 31, 31, 31, 32,
    31, 3, 3, 33, 3, 34, 35, 35,
    31, 35, 31, 35, 36, 37, 35, 38,
    38, 39, 38, 39, 0, 0, 40, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, -2, 0, 0, 0, 0, 0,
    -4, 4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -9, 0, -17,
    -9, -22, 0, 0, 0, 0, 0, -2,
    0, 0, 0, 0, 0, -6, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -19, 0, -26,
    0, -19, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -17, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -11, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -21,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -17, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -11, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -17, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, -9,
    -11, -9, -7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -4, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -7, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -9, 0, 0, 0, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -7, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -15, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -7, 0, 0, 0, 0, -26, -15,
    -32, -9, -4, 0, -19, 0, 0, -7,
    -11, -6, 0, 0, -7, 0, -6, 0,
    0, 0, 0, 0, 0, -21, -22, -11,
    0, 0, -10, -13, -7, 0, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -26, 0,
    -26, 0, 0, -11, -9, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -11, 0, -7,
    0, -7, 0, 0, 0, 0, 0, -17,
    0, 0, 0, 0, 0, -19, -7, -32,
    0, -28, 0, 0, 0, -4, -6, -6,
    -3, -6, 0, 0, 0, -17, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -11, 0, -11,
    -7, -17, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -4, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -7,
    -6, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, 0, -9, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -7, 0, -11,
    -11, -13, -4, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -19, 0,
    -22, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -19, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, -6, 0,
    0, 0, 0, 0, 0, 0, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -19,
    0, -17, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -11, 0, -7, 0,
    0, 0, 0, 0, 0, -9, -9, -7,
    0, 0, 0, 0, -7, -7, 0, 0,
    -9, 0, 0, 0, 0, -11, 0, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -22, -6, -26,
    0, -30, 0, 0, 0, 0, 0, -4,
    0, 0, 0, 0, -7, -19, 0, 0,
    0, 0, 0, 0, 0, 0, -22, 0,
    -30, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -22, 0, -6, 0, 0, -6,
    -15, -7, 0, 0, 0, -6, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -7, -7, -6, -11,
    0, -15, 0, 0, 0, -6, -9, 0,
    0, 0, 0, 0, 0, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, -7, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -4, -7, 0, 0, -22, -19,
    -21, -6, 0, 0, 0, 0, 0, 0,
    -11, 0, -19, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -15, -22, -11,
    -4, 0, -11, 0, 0, -6, -6, 0,
    0, 0, 0, -7, 0, 0, -24, -11,
    -37, -9, 0, 0, -19, 0, 0, -4,
    0, 0, -30, 0, -7, 0, -6, 0,
    0, 0, 0, 0, 0, -22, -19, 0,
    -3, 0, -9, -13, -7, -7, -7, 0,
    0, 0, -2, -11, 0, 0, -30, -11,
    -32, -11, 0, 0, -11, 0, 0, 0,
    -11, 0, -30, 0, -4, 0, -6, 0,
    0, 0, 0, 0, 0, -19, -19, -7,
    0, 0, -7, -11, -4, 0, -7, 0,
    0, 0, 0, 0, 0, 0, 0, -11,
    0, -11, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, 0, -4, 0,
    0, 0, 0, 0, 0, 0, -11, -7,
    0, 0, 0, 0, -11, -11, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, -2, -7, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -19, -7, -22,
    0, -26, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -11, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -7, 0, -11,
    0, -17, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -7,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -11,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, -6, 0,
    0, 0, 0, 0, 0, 0, -9, 0,
    -15, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -6, 0,
    -4, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -7, 0, -17,
    0, 0, 0, -11, 0, 0, -2, 0,
    0, 0, 0, 0, 0, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -7, -7, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -7, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -7, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -2, -7, 0,
    0, 0, 0, 0, 0, 2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -7,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -21, 0,
    -24, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -9, 0, 0, 0, 0, 0,
    -11, -7, 0, 0, 0, -7, -7, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -9,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -7, 0, 0, 0, 0, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -7, 0, 0, 0, 0, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 43,
    .right_class_cnt     = 40,
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
const lv_font_t ui_font_NeverMindSemiSerifBold12 = {
#else
lv_font_t ui_font_NeverMindSemiSerifBold12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 12,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_NEVERMINDSEMISERIFBOLD12*/

