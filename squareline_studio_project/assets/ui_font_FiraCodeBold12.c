/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --font /home/developer/sources/epink_desktop/squareline_studio_project/assets/FiraCode-Bold.ttf -o /home/developer/sources/epink_desktop/squareline_studio_project/assets/ui_font_FiraCodeBold12.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_FIRACODEBOLD12
#define UI_FONT_FIRACODEBOLD12 1
#endif

#if UI_FONT_FIRACODEBOLD12

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
    0xff, 0xf0,

    /* U+0023 "#" */
    0x6d, 0xbf, 0xd2, 0x49, 0x2f, 0xf6, 0xd8,

    /* U+0024 "$" */
    0x20, 0x87, 0xba, 0xe3, 0x87, 0x8f, 0x2f, 0xff,
    0x88, 0x20,

    /* U+0025 "%" */
    0xe5, 0xcb, 0xa7, 0x41, 0x3, 0x86, 0x9d, 0x4c,

    /* U+0026 "&" */
    0x79, 0x83, 0x1, 0xfc, 0xd9, 0xb3, 0x66, 0x7c,

    /* U+0027 "'" */
    0xfc,

    /* U+0028 "(" */
    0x13, 0x66, 0xcc, 0xcc, 0xc6, 0x63, 0x10,

    /* U+0029 ")" */
    0x8c, 0x66, 0x33, 0x33, 0x36, 0x6c, 0x80,

    /* U+002A "*" */
    0x18, 0x25, 0xf9, 0xe3, 0x8d, 0x88, 0x0,

    /* U+002B "+" */
    0x30, 0x60, 0xc7, 0xf3, 0x6, 0xc, 0x0,

    /* U+002C "," */
    0xfe, 0x80,

    /* U+002D "-" */
    0xf8,

    /* U+002E "." */
    0xff, 0x80,

    /* U+002F "/" */
    0x6, 0x8, 0x30, 0x61, 0x83, 0xc, 0x18, 0x60,
    0xc3, 0x0,

    /* U+0030 "0" */
    0x79, 0x2d, 0xf7, 0xdf, 0xbe, 0xd2, 0x78,

    /* U+0031 "1" */
    0x38, 0xf1, 0xe0, 0xc1, 0x83, 0x6, 0xc, 0x7e,

    /* U+0032 "2" */
    0x79, 0x30, 0xc3, 0x1c, 0xe3, 0x18, 0xfc,

    /* U+0033 "3" */
    0xfa, 0x30, 0xc3, 0x30, 0x30, 0xe3, 0xf8,

    /* U+0034 "4" */
    0x0, 0x86, 0x18, 0x5b, 0x6f, 0xc6, 0x18,

    /* U+0035 "5" */
    0x7e, 0xc1, 0x83, 0xe6, 0xe0, 0xc1, 0xa3, 0x78,

    /* U+0036 "6" */
    0x39, 0x8c, 0x3e, 0xcf, 0x3c, 0xd3, 0x78,

    /* U+0037 "7" */
    0xfc, 0x31, 0x86, 0x30, 0xc6, 0x18, 0x20,

    /* U+0038 "8" */
    0x7b, 0x3c, 0xfe, 0x7b, 0x7c, 0xf3, 0x78,

    /* U+0039 "9" */
    0x7b, 0x3c, 0xf3, 0x7c, 0x73, 0x9c,

    /* U+003A ":" */
    0xf0, 0x3c,

    /* U+003B ";" */
    0xf0, 0xfe, 0x80,

    /* U+003C "<" */
    0x8, 0x77, 0x38, 0xe1, 0xc1, 0xc2,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0x43, 0x83, 0x87, 0x1c, 0xee, 0x10,

    /* U+003F "?" */
    0x79, 0x30, 0xc6, 0x30, 0xc0, 0xc, 0x30,

    /* U+0040 "@" */
    0x79, 0x18, 0x1b, 0xfd, 0xfb, 0xf7, 0xef, 0x7e,
    0x18,

    /* U+0041 "A" */
    0x38, 0x38, 0x3c, 0x6c, 0x6c, 0x6e, 0x7e, 0xc6,
    0xc6,

    /* U+0042 "B" */
    0xfb, 0x3c, 0xf3, 0xf3, 0x3c, 0xf3, 0xf8,

    /* U+0043 "C" */
    0x3c, 0xcb, 0x6, 0xc, 0x18, 0x30, 0x32, 0x3c,

    /* U+0044 "D" */
    0xf3, 0x6c, 0xf3, 0xcf, 0x3c, 0xf6, 0xf0,

    /* U+0045 "E" */
    0xfb, 0xc, 0x30, 0xfb, 0xc, 0x30, 0xfc,

    /* U+0046 "F" */
    0xfb, 0xc, 0x30, 0xfb, 0xc, 0x30, 0xc0,

    /* U+0047 "G" */
    0x3e, 0xcb, 0x6, 0xc, 0xf8, 0xf1, 0xb3, 0x3e,

    /* U+0048 "H" */
    0xcf, 0x3c, 0xf3, 0xff, 0x3c, 0xf3, 0xcc,

    /* U+0049 "I" */
    0xfc, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0xfc,

    /* U+004A "J" */
    0x7c, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xf8,

    /* U+004B "K" */
    0xcd, 0x9b, 0x67, 0x8f, 0x1b, 0x36, 0x66, 0xcc,

    /* U+004C "L" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xfc,

    /* U+004D "M" */
    0xef, 0xdf, 0xbf, 0x7e, 0xfb, 0xf5, 0xe3, 0xc6,

    /* U+004E "N" */
    0xef, 0xbe, 0xfb, 0xff, 0x7d, 0xf7, 0xdc,

    /* U+004F "O" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xb6, 0x38,

    /* U+0050 "P" */
    0xfb, 0x3c, 0xf3, 0xcf, 0xec, 0x30, 0xc0,

    /* U+0051 "Q" */
    0x38, 0x4c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x4c,
    0x38, 0x6, 0x3,

    /* U+0052 "R" */
    0xf9, 0x9b, 0x36, 0x6f, 0x9b, 0x36, 0x66, 0xcc,

    /* U+0053 "S" */
    0x7b, 0xc, 0x3c, 0x7c, 0xf0, 0xe3, 0xf8,

    /* U+0054 "T" */
    0xfe, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18,

    /* U+0055 "U" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0x78,

    /* U+0056 "V" */
    0xc7, 0x8d, 0x9b, 0x26, 0xcd, 0x8f, 0x1c, 0x38,

    /* U+0057 "W" */
    0xc7, 0xbf, 0x7f, 0xff, 0xed, 0xdb, 0xb7, 0x6e,

    /* U+0058 "X" */
    0x66, 0xd8, 0xf1, 0xc3, 0x87, 0x9b, 0x33, 0xc6,

    /* U+0059 "Y" */
    0xe7, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x18, 0x18,
    0x18,

    /* U+005A "Z" */
    0x7e, 0x1c, 0x30, 0xe1, 0x86, 0x1c, 0x30, 0xfe,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf,

    /* U+005C "\\" */
    0xc0, 0xc1, 0x81, 0x83, 0x3, 0x6, 0x6, 0xc,
    0x8, 0x18,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x3f,

    /* U+005E "^" */
    0x18, 0x71, 0xb3, 0x30,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0x1c, 0x80,

    /* U+0061 "a" */
    0x78, 0x30, 0xdf, 0xcf, 0x37, 0x40,

    /* U+0062 "b" */
    0xc3, 0xc, 0x3e, 0xcf, 0x3c, 0xf3, 0xcf, 0xe0,

    /* U+0063 "c" */
    0x7d, 0x8c, 0x30, 0xc3, 0x7, 0xc0,

    /* U+0064 "d" */
    0xc, 0x30, 0xdf, 0xcf, 0x3c, 0xf3, 0xcd, 0xf0,

    /* U+0065 "e" */
    0x3c, 0xcd, 0x9f, 0xf6, 0xc, 0xf, 0x80,

    /* U+0066 "f" */
    0x1e, 0x60, 0xc1, 0x8f, 0xc6, 0xc, 0x18, 0x30,
    0x60,

    /* U+0067 "g" */
    0x2, 0x3e, 0x66, 0x66, 0x66, 0x3c, 0x60, 0x3e,
    0x6, 0x66, 0x7c,

    /* U+0068 "h" */
    0xc3, 0xc, 0x3e, 0xcf, 0x3c, 0xf3, 0xcf, 0x30,

    /* U+0069 "i" */
    0x1, 0x80, 0xf, 0x18, 0xc6, 0x31, 0xbe,

    /* U+006A "j" */
    0x0, 0xc0, 0x7, 0x8c, 0x63, 0x18, 0xce, 0xe6,
    0x0,

    /* U+006B "k" */
    0xc3, 0xc, 0x33, 0xdb, 0x6f, 0x36, 0xdf, 0x30,

    /* U+006C "l" */
    0xf0, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0x70,

    /* U+006D "m" */
    0xff, 0xef, 0xdf, 0xbf, 0x7e, 0xfd, 0x80,

    /* U+006E "n" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3c, 0xc0,

    /* U+006F "o" */
    0x7b, 0x3c, 0xf3, 0xcf, 0x37, 0x80,

    /* U+0070 "p" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3f, 0xb0, 0xc2, 0x0,

    /* U+0071 "q" */
    0x7f, 0x3c, 0xf3, 0xcf, 0x37, 0xc3, 0xc, 0x10,

    /* U+0072 "r" */
    0xed, 0xf6, 0xd8, 0x61, 0x8f, 0x0,

    /* U+0073 "s" */
    0x7b, 0x2f, 0x3e, 0x3a, 0x2f, 0x0,

    /* U+0074 "t" */
    0x30, 0x63, 0xf1, 0x83, 0x6, 0xc, 0x18, 0x1e,

    /* U+0075 "u" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x37, 0xc0,

    /* U+0076 "v" */
    0x66, 0xcd, 0xb3, 0x63, 0xc7, 0xe, 0x0,

    /* U+0077 "w" */
    0xc3, 0xbf, 0x7a, 0xf6, 0xed, 0xdb, 0x0,

    /* U+0078 "x" */
    0x6c, 0xd8, 0xe1, 0xc3, 0xcd, 0x99, 0x80,

    /* U+0079 "y" */
    0xe6, 0xcd, 0xb3, 0x62, 0xc7, 0xe, 0xc, 0x70,
    0xc0,

    /* U+007A "z" */
    0x7c, 0x31, 0x8c, 0x31, 0x8f, 0xc0,

    /* U+007B "{" */
    0x39, 0x8, 0x62, 0x61, 0x86, 0x23, 0x8, 0x70,

    /* U+007C "|" */
    0xff, 0xff, 0xfc,

    /* U+007D "}" */
    0xc3, 0x18, 0xc6, 0xd, 0x8c, 0x63, 0x19, 0x80,

    /* U+007E "~" */
    0x73, 0xbc, 0x30
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 118, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 118, .box_w = 2, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 118, .box_w = 4, .box_h = 3, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 6, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 13, .adv_w = 118, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 23, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 118, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 40, .adv_w = 118, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 47, .adv_w = 118, .box_w = 4, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 54, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 61, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 68, .adv_w = 118, .box_w = 2, .box_h = 5, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 70, .adv_w = 118, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 71, .adv_w = 118, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 118, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 83, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 118, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 154, .adv_w = 118, .box_w = 2, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 118, .box_w = 2, .box_h = 9, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 159, .adv_w = 118, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 118, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 168, .adv_w = 118, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 118, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 190, .adv_w = 118, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 279, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 118, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 320, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 335, .adv_w = 118, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 118, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 118, .box_w = 4, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 398, .adv_w = 118, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 408, .adv_w = 118, .box_w = 4, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 414, .adv_w = 118, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 418, .adv_w = 118, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 419, .adv_w = 118, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 421, .adv_w = 118, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 427, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 435, .adv_w = 118, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 441, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 456, .adv_w = 118, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 118, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 476, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 118, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 118, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 500, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 118, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 529, .adv_w = 118, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 535, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 543, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 551, .adv_w = 118, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 118, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 563, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 118, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 577, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 584, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 591, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 598, .adv_w = 118, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 607, .adv_w = 118, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 613, .adv_w = 118, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 621, .adv_w = 118, .box_w = 2, .box_h = 11, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 624, .adv_w = 118, .box_w = 5, .box_h = 12, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 632, .adv_w = 118, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = 3}
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
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
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
const lv_font_t ui_font_FiraCodeBold12 = {
#else
lv_font_t ui_font_FiraCodeBold12 = {
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
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_FIRACODEBOLD12*/

