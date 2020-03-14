/*
 * rarely used EEPROM code
 * (C) notaz, 2006-2008
 *
 * This work is licensed under the terms of MAME license.
 * See COPYING file in the top-level directory.
 */

#include "pico_int.h"

// H-counter table for hvcounter reads in 40col mode, starting at HINT
const unsigned char hcounts_40[] = {
0xa5,0xa6,0xa7,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xae,0xaf,0xb0,0xb1,0xb2,
0xb3,0xb4,0xb5,0xb5,0xe4,0xe5,0xe6,0xe7,0xe8,0xe8,0xe9,0xea,0xea,0xeb,0xec,0xed,
0xed,0xee,0xef,0xef,0xf0,0xf1,0xf2,0xf2,0xf3,0xf4,0xf4,0xf5,0xf6,0xf7,0xf7,0xf8,
0xf9,0xfa,0xfb,0xfc,0xfd,0xfd,0xfe,0xff,0x00,0x01,0x02,0x03,0x04,0x04,0x05,0x06,
0x07,0x08,0x09,0x0a,0x0b,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x12,0x13,0x14,
0x15,0x16,0x17,0x18,0x19,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x20,0x20,0x21,0x22,
0x23,0x24,0x25,0x26,0x27,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2e,0x2f,0x30,
0x31,0x32,0x33,0x34,0x35,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3c,0x3d,0x3e,
0x3f,0x40,0x41,0x42,0x43,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4a,0x4b,0x4c,
0x4d,0x4e,0x4f,0x50,0x51,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x58,0x59,0x5a,
0x5b,0x5c,0x5d,0x5e,0x5f,0x5f,0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x66,0x67,0x68,
0x69,0x6a,0x6b,0x6c,0x6d,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x74,0x75,0x76,
0x77,0x78,0x79,0x7a,0x7b,0x7b,0x7c,0x7d,0x7e,0x7f,0x80,0x81,0x82,0x82,0x83,0x84,
0x85,0x86,0x87,0x88,0x89,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x90,0x91,0x92,
0x93,0x94,0x95,0x96,0x97,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9e,0x9f,0xa0,
0xa1,0xa2,0xa3,0xa4,0xa5,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xac,0xad,0xae,
};

// H-counter table for hvcounter reads in 32col mode, starting at HINT
const unsigned char hcounts_32[] = {
0x85,0x86,0x86,0x87,0x88,0x88,0x89,0x8a,0x8a,0x8b,0x8c,0x8d,0x8d,0x8e,0x8f,0x8f,
0x90,0x91,0x91,0x92,0x93,0xe9,0xe9,0xea,0xeb,0xeb,0xec,0xed,0xed,0xee,0xef,0xf0,
0xf0,0xf1,0xf2,0xf2,0xf3,0xf4,0xf4,0xf5,0xf6,0xf7,0xf7,0xf8,0xf9,0xf9,0xfa,0xfb,
0xfb,0xfc,0xfd,0xfe,0xfe,0xff,0x00,0x00,0x01,0x02,0x02,0x03,0x04,0x05,0x05,0x06,
0x07,0x07,0x08,0x09,0x09,0x0a,0x0b,0x0c,0x0c,0x0d,0x0e,0x0e,0x0f,0x10,0x10,0x11,
0x12,0x13,0x13,0x14,0x15,0x15,0x16,0x17,0x17,0x18,0x19,0x1a,0x1a,0x1b,0x1c,0x1c,
0x1d,0x1e,0x1e,0x1f,0x20,0x21,0x21,0x22,0x23,0x23,0x24,0x25,0x25,0x26,0x27,0x28,
0x28,0x29,0x2a,0x2a,0x2b,0x2c,0x2c,0x2d,0x2e,0x2f,0x2f,0x30,0x31,0x31,0x32,0x33,
0x33,0x34,0x35,0x36,0x36,0x37,0x38,0x38,0x39,0x3a,0x3a,0x3b,0x3c,0x3d,0x3d,0x3e,
0x3f,0x3f,0x40,0x41,0x41,0x42,0x43,0x44,0x44,0x45,0x46,0x46,0x47,0x48,0x48,0x49,
0x4a,0x4b,0x4b,0x4c,0x4d,0x4d,0x4e,0x4f,0x4f,0x50,0x51,0x52,0x52,0x53,0x54,0x54,
0x55,0x56,0x56,0x57,0x58,0x59,0x59,0x5a,0x5b,0x5b,0x5c,0x5d,0x5d,0x5e,0x5f,0x60,
0x60,0x61,0x62,0x62,0x63,0x64,0x64,0x65,0x66,0x67,0x67,0x68,0x69,0x69,0x6a,0x6b,
0x6b,0x6c,0x6d,0x6e,0x6e,0x6f,0x70,0x70,0x71,0x72,0x72,0x73,0x74,0x75,0x75,0x76,
0x77,0x77,0x78,0x79,0x79,0x7a,0x7b,0x7c,0x7c,0x7d,0x7e,0x7e,0x7f,0x80,0x80,0x81,
0x82,0x83,0x83,0x84,0x85,0x85,0x86,0x87,0x87,0x88,0x89,0x8a,0x8a,0x8b,0x8c,0x8c,
};

// VDP transfer slots for blanked and active display in 32col and 40col mode.
// 1 slot is 488/171 = 2.8538 68k cycles in h32, and 488/210 = 2.3238 in h40
// In blanked display, all slots but 5(h32) / 6(h40) are usable for transfers,
// in active display only 16(h32) / 18(h40) slots can be used.

// XXX inactive tables by slot#=cycles*maxslot#/488. should be through hv tables
// VDP transfer slots in inactive (blanked) display 32col mode.
// refresh slots: 250, 26, 58, 90, 122 -> 32, 64, 96, 128, 160
const unsigned char vdpcyc2sl_32_bl[] = { // 68k cycles/2 to slot #
//  0   2   4   6   8  10  12  14  16  18  20  22  24  26  28  30
    0,  0,  1,  2,  2,  3,  4,  4,  5,  6,  6,  7,  8,  8,  9, 10,
   10, 11, 12, 12, 13, 14, 14, 15, 16, 17, 17, 18, 19, 19, 20, 21,
   21, 22, 23, 23, 24, 25, 25, 26, 27, 27, 28, 29, 29, 30, 31, 31,
   32, 33, 34, 34, 35, 36, 36, 37, 38, 38, 39, 40, 40, 41, 42, 42,
   43, 44, 44, 45, 46, 46, 47, 48, 48, 49, 50, 51, 51, 52, 53, 53,
   54, 55, 55, 56, 57, 57, 58, 59, 59, 60, 61, 61, 62, 63, 63, 64,
   65, 65, 66, 67, 68, 68, 69, 70, 70, 71, 72, 72, 73, 74, 74, 75,
   76, 76, 77, 78, 78, 79, 80, 80, 81, 82, 83, 83, 84, 85, 85, 86,
   87, 87, 88, 89, 89, 90, 91, 91, 92, 93, 93, 94, 95, 95, 96, 97,
   97, 98, 99,100,100,101,102,102,103,104,104,105,106,106,107,108,
  108,109,110,110,111,112,112,113,114,114,115,116,117,117,118,119,
  119,120,121,121,122,123,123,124,125,125,126,127,127,128,129,129,
  130,131,131,132,133,134,134,135,136,136,137,138,138,139,140,140,
  141,142,142,143,144,144,145,146,146,147,148,148,149,150,151,151,
  152,153,153,154,155,155,156,157,157,158,159,159,160,161,161,162,
  163,163,164,165,166,166,167,168,168,169,170,170,171,172,172,173,
};
// VDP transfer slots in inactive (blanked) display 40col mode.
// refresh slots: 250, 26, 58, 90, 122, 154 -> 40, 72, 104, 136, 168, 200
const unsigned char vdpcyc2sl_40_bl[] = { // 68k cycles/2 to slot #
//  0   2   4   6   8  10  12  14  16  18  20  22  24  26  28  30
    0,  0,  1,  2,  3,  4,  5,  5,  6,  7,  8,  9, 10, 10, 11, 12,
   13, 14, 15, 15, 16, 17, 18, 19, 20, 20, 21, 22, 23, 24, 25, 25,
   26, 27, 28, 29, 30, 30, 31, 32, 33, 34, 35, 35, 36, 37, 38, 39,
   40, 40, 41, 42, 43, 44, 45, 45, 46, 47, 48, 49, 50, 51, 51, 52,
   53, 54, 55, 56, 56, 57, 58, 59, 60, 61, 61, 62, 63, 64, 65, 66,
   66, 67, 68, 69, 70, 71, 71, 72, 73, 74, 75, 76, 76, 77, 78, 79,
   80, 81, 81, 82, 83, 84, 85, 86, 86, 87, 88, 89, 90, 91, 91, 92,
   93, 94, 95, 96, 96, 97, 98, 99,100,101,102,102,103,104,105,106,
  107,107,108,109,110,111,112,112,113,114,115,116,117,117,118,119,
  120,121,122,122,123,124,125,126,127,127,128,129,130,131,132,132,
  133,134,135,136,137,137,138,139,140,141,142,142,143,144,145,146,
  147,147,148,149,150,151,152,153,153,154,155,156,157,158,158,159,
  160,161,162,163,163,164,165,166,167,168,168,169,170,171,172,173,
  173,174,175,176,177,178,178,179,180,181,182,183,183,184,185,186,
  187,188,188,189,190,191,192,193,193,194,195,196,197,198,198,199,
  200,201,202,203,204,204,205,206,207,208,209,209,210,211,212,213,
};
// VDP transfer slots in active display 32col mode. Transfer slots (Hint=0):
// 11,25,40,48,56,72,80,88,104,112,120,136,144,152,167,168
const unsigned char vdpcyc2sl_32[] = { // 68k cycles/2 to slot #
//  0   2   4   6   8  10  12  14  16  18  20  22  24  26  28  30
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3,  3,
    3,  3,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  5,
    5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
    5,  5,  5,  5,  5,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
    6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8,  8,  8,  8,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 10,
   10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11,
   11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
   11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13,
   13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14,
   14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15,
   16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
};
// VDP transfer slots in active display 40col mode. Transfer slots (Hint=0):
// 21,47,55,63,79,87,95,111,119,127,143,151,159,175,183,191,206,207
const unsigned char vdpcyc2sl_40[] = { // 68k cycles/2 to slot #
//  0   2   4   6   8  10  12  14  16  18  20  22  24  26  28  30
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, //   0
    0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1, //  32
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, //  64
    1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2, //  96
    3,  3,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  4,  4, // 128
    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  5,  5,  5,  5, // 160
    5,  5,  5,  5,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  7,  7, // 192
    7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, // 224
    7,  8,  8,  8,  8,  8,  8,  8,  8,  8,  9,  9,  9,  9,  9,  9, // 256
    9,  9,  9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, // 288
   10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, // 320
   12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, // 352
   13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, // 384
   14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, // 416
   16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, // 448
   18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, // 480
};

// XXX inactive tables by cyc=slot#*488/maxslot#. should be through hv tables
const unsigned short vdpsl2cyc_32_bl[] = { // slot # to 68k cycles/2
     0,  2,  3,  5,  6,  8,  9, 11, 12, 14, 15, 17, 18, 20, 21, 23,
    24, 25, 27, 28, 30, 31, 33, 34, 36, 37, 39, 40, 42, 43, 45, 46,
    48, 49, 50, 52, 53, 55, 56, 58, 59, 61, 62, 64, 65, 67, 68, 70,
    71, 73, 74, 75, 77, 78, 80, 81, 83, 84, 86, 87, 89, 90, 92, 93,
    95, 96, 98, 99,100,102,103,105,106,108,109,111,112,114,115,117,
   118,120,121,122,124,125,127,128,130,131,133,134,136,137,139,140,
   142,143,145,146,147,149,150,152,153,155,156,158,159,161,162,164,
   165,167,168,170,171,172,174,175,177,178,180,181,183,184,186,187,
   189,190,192,193,195,196,197,199,200,202,203,205,206,208,209,211,
   212,214,215,217,218,220,221,222,224,225,227,228,230,231,233,234,
   236,237,239,240,242,243,244,246,
};
const unsigned short vdpsl2cyc_40_bl[] = { // slot # to 68k cycles/2
     0,  2,  3,  4,  5,  6,  8,  9, 10, 11, 12, 14, 15, 16, 17, 18,
    20, 21, 22, 23, 24, 26, 27, 28, 29, 30, 32, 33, 34, 35, 36, 38,
    39, 40, 41, 42, 44, 45, 46, 47, 48, 50, 51, 52, 53, 54, 56, 57,
    58, 59, 60, 61, 63, 64, 65, 66, 67, 69, 70, 71, 72, 73, 75, 76,
    77, 78, 79, 81, 82, 83, 84, 85, 87, 88, 89, 90, 91, 93, 94, 95,
    96, 97, 99,100,101,102,103,105,106,107,108,109,111,112,113,114,
   115,117,118,119,120,121,122,124,125,126,127,128,130,131,132,133,
   134,136,137,138,139,140,142,143,144,145,146,148,149,150,151,152,
   154,155,156,157,158,160,161,162,163,164,166,167,168,169,170,172,
   173,174,175,176,178,179,180,181,182,183,185,186,187,188,189,191,
   192,193,194,195,197,198,199,200,201,203,204,205,206,207,209,210,
   211,212,213,215,216,217,218,219,221,222,223,224,225,227,228,229,
   230,231,233,234,235,236,237,239,240,241,242,243,244,246,
};
const unsigned short vdpsl2cyc_32[] = { // slot # to 68k cycles/2
    0, 16, 36, 56, 67, 79,102,113,125,148,159,171,194,205,217,239,
  240,260
};
const unsigned short vdpsl2cyc_40[] = { // slot # to 68k cycles/2
    0, 24, 55, 64, 73, 92,101,110,129,138,147,166,175,184,203,212,
  221,239,240,268
};

#ifndef _ASM_MISC_C
PICO_INTERNAL_ASM void memcpy16bswap(unsigned short *dest, void *src, int count)
{
	unsigned char *src_ = src;

	for (; count; count--, src_ += 2)
		*dest++ = (src_[0] << 8) | src_[1];
}

#ifndef _ASM_MISC_C_AMIPS
PICO_INTERNAL_ASM void memset32(void *dest_in, int c, int count)
{
	int *dest = dest_in;

	for (; count >= 8; count -= 8, dest += 8)
		dest[0] = dest[1] = dest[2] = dest[3] =
		dest[4] = dest[5] = dest[6] = dest[7] = c;

	while (count--)
		*dest++ = c;
}
void memset32_uncached(int *dest, int c, int count) { memset32(dest, c, count); }
#endif
#endif

