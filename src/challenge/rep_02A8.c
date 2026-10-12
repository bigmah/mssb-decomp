#include "challenge/rep_02A8.h"
#define REP_HEADER_FN repHeader_02A8
#include "header_rep_inline.h"
#include "challenge/rep_0010.h"


#include "static/UnknownHomes_Static.h"
#include "musyx/musyx.h"
#include "Dolphin/os.h"

// The sound manager (main/file_80021308.h).
#include "main/file_80021308.h" // SoundManager
extern SoundManager lbl_800EF808;


extern void fn_1_A250(void);

extern void fn_1_9F04(void);
extern void fn_1_A464(void);

extern ChSound3DTest lbl_1_common_bss_49994;
extern ChSoundEmitterParams lbl_1_common_bss_49980;
extern ChSoundListenerParams lbl_1_common_bss_49970;
extern void fn_1_A95C(void);

extern void fn_1_BFB0(void);
extern void fn_1_BC00(void);

extern s8 lbl_1_common_bss_49A78[];
extern void fn_1_C2A4(void);


// Unreferenced: older copies of the tables below and the 3D test defaults.
static u8 lbl_1_data_FC0[0x798] = {
    0x1B, 0x1A, 0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0F, 0x0E, 0x0D, 0x0C,
    0x0B, 0x0A, 0x23, 7, 9, 0x21, 0x22, 8, 0x30, 0x2E, 0x27, 0x2F, 0x32, 0x25, 0x24, 0x26,
    1, 0x44, 1, 0x37, 1, 0x2A, 1, 0x1D, 1, 0x10, 1, 3, 0, 0xF6, 0, 0xE9,
    0, 0xDC, 0, 0xCF, 0, 0xC2, 0, 0xB5, 0, 0xA8, 0, 0x9B, 0, 0x8E, 0, 0x81,
    0, 0x74, 0, 0x67, 2, 1, 0, 0x40, 0, 0x5A, 1, 0xE7, 1, 0xE7, 1, 0xE7,
    1, 0xF4, 1, 0xF4, 1, 0xF4, 0, 0x4D, 2, 0x77, 0, 0x9B, 0, 0x9B, 0, 0x9B,
    0, 0x9B, 2, 0x5D, 2, 0x5D, 2, 0x5D, 2, 0x5D, 2, 0x35, 2, 0x6A, 2, 0xC9,
    2, 0x1B, 2, 0x0E, 0, 0xA8, 0, 0x5A, 0, 0x74, 0, 0x74, 0, 0x74, 0, 0x74,
    2, 0x28, 2, 0x28, 2, 0x28, 2, 0x28, 0, 0x4D, 0, 0x4D, 0x2A, 0x2B, 0x2C, 0x34,
    2, 1, 6, 0, 2, 0x48, 2, 0x4A, 2, 0x52, 3, 0x0F, 0, 0x10, 0, 1,
    0, 0x22, 0, 0, 2, 0x49, 2, 0x51, 2, 0x58, 0, 0x0F, 0, 0x17, 0, 0x0F,
    0, 0x3F, 0, 0, 2, 0xD6, 2, 0xD7, 2, 0xD8, 2, 0xD9, 2, 0xE1, 2, 0xE2,
    2, 0xE3, 2, 0xE4, 2, 0xE5, 2, 0xE6, 2, 0xDD, 2, 0xDE, 2, 0xDF, 2, 0xE0,
    2, 0xDA, 2, 0xDB, 2, 0xDC, 2, 0xE7, 2, 0xE8, 2, 0xE9, 2, 0xEA, 2, 0xEB,
    2, 0xEC, 2, 0xED, 2, 0xEE, 2, 0xEF, 2, 0xF0, 2, 0xF1, 2, 0xF2, 2, 0xF3,
    2, 0xF4, 2, 0xF5, 2, 0xF6, 2, 0xF7, 2, 0xF8, 2, 0xF9, 2, 0xFA, 2, 0xFB,
    2, 0xFC, 2, 0xFD, 2, 0xFE, 2, 0xFF, 3, 0, 3, 1, 3, 2, 3, 3,
    3, 4, 3, 5, 3, 6, 3, 7, 3, 8, 3, 9, 3, 0x0A, 3, 0x0B,
    3, 0x0C, 3, 0x0D, 3, 0x0E, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0, 0, 0x7F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0x7F, 0, 0, 0, 0, 0, 0, 0, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0, 0, 0,
    0, 0, 0, 0, 0x4B, 0x28, 0x4B, 0x28, 0x55, 0x28, 0x55, 0x28, 0x55, 0x28, 0x55, 0x28,
    0x55, 0x28, 0x55, 0x28, 0x55, 0x28, 0x5A, 0x28, 0x55, 0x28, 0x55, 0x28, 0x55, 0x28, 0x55, 0x28,
    0x55, 0x28, 0x55, 0x28, 0x5A, 0x28, 0x5F, 0x28, 0x69, 0x28, 0, 0, 0x55, 0x28, 0, 0,
    0x7F, 0, 0x7F, 0, 0x7F, 0, 0x46, 0, 0x4B, 0, 0x55, 0, 0x5A, 0, 0x5A, 0,
    0x64, 0, 0x7F, 0, 0x64, 0, 0x78, 0, 0x64, 0, 0x7F, 0, 0x64, 0, 0x64, 0,
    0x64, 0, 0x64, 0, 0x64, 0, 0x64, 0, 0x64, 0, 0x64, 0, 0x64, 0, 0x64, 0,
    0x7F, 0, 0x64, 0, 0x6E, 0, 0x7F, 0, 0x75, 0, 0x75, 0, 0x64, 0, 0x64, 0,
    0x57, 0, 0x64, 0, 0x64, 0, 0x57, 0, 0x64, 0, 0x64, 0, 0x64, 0, 0x7F, 0,
    0x7F, 0, 0x75, 0, 0x54, 0, 0x64, 0, 0x64, 0, 0x50, 0, 0x5A, 0, 0x7F, 0,
    0x7F, 0, 0x7F, 0, 0x7F, 0, 0x7F, 0, 0x7F, 0, 0x64, 0, 0x64, 0, 0x64, 0,
    0x75, 0, 0x6B, 0, 0x64, 0, 0x73, 0, 0x7F, 0, 0x7F, 0, 0x7F, 0, 0x7F, 0,
    0x7F, 0, 0x7F, 0, 0x7F, 0, 0x7F, 0, 0x7F, 0, 0x6B, 0, 0x55, 0, 0x6B, 0,
    0x6B, 0, 0x7F, 0, 0x7F, 0, 0x75, 0, 0x66, 0, 0x75, 0, 0x7F, 0, 0x55, 0,
    0x64, 0, 0x64, 0, 0x64, 0, 0x64, 0, 0x64, 0, 0x6E, 0, 0x64, 0, 0x64, 0,
    0x73, 0, 0x6E, 0, 0x5A, 0, 0x6E, 0, 0x7F, 0, 0x7F, 0, 0x6B, 0, 0x7F, 0,
    0x75, 0, 0x7F, 0, 0x7F, 0, 0x73, 0, 0x7F, 0, 0x7F, 0, 0x3C, 0, 0x5A, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7F, 0, 0x7F, 0, 0x7F, 0,
    0x69, 0, 0x7F, 0, 0x7F, 0, 0x7F, 0, 0x7F, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0x7F, 0, 0x7F, 0, 0x7F, 0, 0x7F, 0,
    0x7F, 0, 0x7F, 0, 0x7F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0x7F, 0, 0x7F, 0, 0x7F, 0, 0x64, 0, 0x7F, 0,
    0x41, 0, 0x46, 0, 0x46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0x7F, 0, 0x7F, 0, 0x7F, 0, 0x32, 0, 0x4D, 0, 0x4D, 0,
    0x57, 0, 0x57, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0x7F, 0, 0x64, 0, 0x64, 0, 0x64, 0, 0x7F, 0, 0x7F, 0, 0x3C, 0,
    0x3C, 0, 0x69, 0, 0x7F, 0, 0x6E, 0, 0x7F, 0, 0x6E, 0, 0x7F, 0, 0x7F, 0,
    0x7F, 0, 0x6B, 0, 0x64, 0, 0x5F, 0, 0x75, 0, 0x70, 0, 0x6B, 0, 0x7F, 0,
    0x6B, 0, 0x7F, 0, 0x7F, 0, 0x7F, 0, 0x4B, 0, 0x7F, 0, 0x7F, 0, 0x7F, 0,
    0x64, 0, 0x64, 0, 0x69, 0, 0x75, 0, 0x69, 0, 0x5F, 0, 0x5F, 0, 0x69, 0,
    0x64, 0, 0x6E, 0, 0x78, 0, 0x6E, 0, 0x6E, 0, 0x7F, 0, 0x6B, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x4D, 0x4D, 0x7F, 0x61, 0x6B, 0x61, 0x61, 0x7F, 0x6B, 0x5F, 0x69, 0x43, 0x37,
    0x7F, 0x7F, 0x7F, 0x69, 0x7F, 0x61, 0x75, 0x75, 0x64, 0x5F, 0x7F, 0x64, 0x64, 0x7F, 0x69, 0x5A,
    0x64, 0x6B, 0x7F, 0x7F, 0x5A, 0x7F, 0x7F, 0x75, 0x7F, 0x7F, 0x73, 0x64, 0x73, 0x6E, 0x6E, 0x7F,
    0x73, 0x73, 0x7F, 0x7F, 0x78, 0, 0, 0, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
    0x64, 0x64, 0x64, 0x64, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x19, 0x99, 0x9A, 0x42, 0x48, 0, 0,
    0, 0, 0, 0, 0x42, 0xFE, 0, 0, 0x41, 0x20, 0, 0, 0x42, 0x48, 0, 0,
    0, 0, 0, 0, 0x42, 0xFE, 0, 0, 0x41, 0x20, 0, 0, 0x42, 0x48, 0, 0,
    0, 0, 0, 0, 0x42, 0xFE, 0, 0, 0x41, 0x20, 0, 0, 0x42, 0x48, 0, 0,
    0, 0, 0, 0, 0x42, 0xFE, 0, 0, 0x41, 0x20, 0, 0, 0x42, 0xC8, 0, 0,
    0, 0, 0, 0, 0x42, 0xFE, 0, 0, 0x41, 0x20, 0, 0, 0x42, 0xC8, 0, 0,
    0, 0, 0, 0, 0x42, 0xFE, 0, 0, 0x41, 0x20, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0x61,
    0, 0, 0, 0x61, 0x42, 0x48, 0, 0, 0x42, 0x48, 0, 0, 0x3F, 0x80, 0, 0,
    0x20, 0, 0x3B, 0, 0, 3, 0, 0x2D, 0, 0x46, 0, 0, 0x20, 0, 0x3F, 0xFF,
    0, 1, 0, 0x3C, 0, 0x7F, 0, 0, 0x20, 0, 0x3F, 0xFF, 0, 0x14, 0, 0xA5,
    0, 0x7F, 0, 0, 3, 3, 0, 0,
};
// Sound test page names.
static const char* lbl_1_data_1758[19] = {
    "Voice Test", "Voice Test2", "Training Se Test", "SE Test",
    "Surround Test", "VOICE NO ", "HAPPY", "POWER_UP_P",
    "POWER_UP_B", "SWING_WIDE", "STRUCK_OUT", "RELEASE FAST",
    "RELEASE G_FAST", "NO 1", "MAX SWING OUT", "LOSE",
    "DEAD BALL", "FIRE BALL", "end",
};
static u8 lbl_1_data_17A4[0x20] = {
    0x1B, 0x1A, 0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0F, 0x0E, 0x0D, 0x0C,
    0x0B, 0x0A, 0x23, 7, 9, 8, 0x25, 0x24, 0x26, 0x21, 0x22, 0x2E, 0x27, 0x2F, 0x30, 0x32,
};
static u16 lbl_1_data_17C4[18] = {
    0x144, 0x137, 0x12A, 0x11D, 0x110, 0x103, 0xF6, 0xE9, 0xDC,
    0xCF, 0xC2, 0xB5, 0xA8, 0x9B, 0x8E, 0x81, 0x74, 0x67,
};
static u16 lbl_1_data_17E8[14] = {
    0x201, 0x40, 0x5A, 0x4D, 0x21B, 0x20E, 0x228,
    0x1E7, 0x1F4, 0x25D, 0x235, 0x26A, 0x277, 0x2C9,
};
// Character names.
static const char* lbl_1_data_1804[32] = {
    "MARIO      ", "LUIGI      ", "DONKEY     ", "DIDDY      ",
    "PEACH      ", "DAISY      ", "YOSHI      ", "BABYMARIO  ",
    "BABYLUIGI  ", "KOOPA      ", "WARIO      ", "WALUIGI    ",
    "NOKONOKO   ", "KINOPIO    ", "TERESA     ", "KINOPIKO   ",
    "HEIHO R    ", "CATHERINE  ", "CHOROPU    ", "KOOPA JR.  ",
    "PATA_P     ", "HAMM BROS  ", "KURIBO     ", "PATA_K     ",
    "KARON      ", "MONTE      ", "MARE       ", "KAMEKKU    ",
    "KING TERESA", "BOSS PAKKUN", "KINOJI     ", "DIXY       ",
};
static u8 lbl_1_data_1884[8] = {
    0x2A, 0x2B, 0x2C, 0x34, 2, 1, 6, 0,
};
static u16 lbl_1_data_188C[48] = {
    0x248, 0x249, 0x24A, 0x24B, 0x24C, 0x24D, 0x24E, 0x24F, 0x250, 0x252, 0x253, 0x254,
    0x255, 0x256, 0x257, 0x30F, 0x310, 0x311, 0x312, 0x313, 0x314, 0x315, 0x316, 0x10,
    0x11, 0x12, 0x13, 1, 2, 3, 4, 5, 6, 7, 8, 0x22,
    0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2F,
};
static u16 lbl_1_data_18EC[24] = {
    0x2D6, 0x2D7, 0x2D8, 0x2D9, 0x2DA, 0x2DB, 0x2DC, 0x2DD, 0x2DE, 0x2DF, 0x2E0, 0x2E1,
    0x2E2, 0x2E3, 0x2E4, 0x2E5, 0x2E6, 0x2E7, 0x2E8, 0x2E9, 0x2EA, 0x2EB, 0x2EC, 0x17,
};
// 3D sound test rows: listener values, then emitter values.
static const char* lbl_1_data_191C[20] = {
    "POS_X", "POS_Y", "POS_Z", "DIR_X", "DIR_Y",
    "DIR_Z", "HEAD_X", "HEAD_Y", "HEAD_Z", "UP_X",
    "UP_Y", "UP_Z", "VOL", "POS_X", "POS_Y",
    "POS_Z", "DIR_X", "DIR_Y", "DIR_Z", "VOL",
};
// Sound groups of the challenge mode (loaded by fn_1_9F04).
ChFileEntry lbl_1_data_196C[50] = {
    { 0x0, 0x2B060, 0x7742000, 0x2B060 },
    { 0x0, 0x415EA0, 0x776D800, 0x415EA0 },
    { 0x0, 0x103340, 0x7B83800, 0x103340 },
    { 0x0, 0x29D520, 0x7C87000, 0x29D520 },
    { 0x0, 0x1364E0, 0x7F24800, 0x1364E0 },
    { 0x0, 0x2BB40, 0x805B000, 0x2BB40 },
    { 0x0, 0x28800, 0x8087000, 0x28800 },
    { 0x0, 0x3DC00, 0x80AF800, 0x3DC00 },
    { 0x0, 0x39DC0, 0x80ED800, 0x39DC0 },
    { 0x0, 0x22260, 0x8127800, 0x22260 },
    { 0x0, 0x1B180, 0x814A000, 0x1B180 },
    { 0x0, 0x21140, 0x8165800, 0x21140 },
    { 0x0, 0x2E080, 0x8187000, 0x2E080 },
    { 0x0, 0x29500, 0x81B5800, 0x29500 },
    { 0x0, 0x2FEA0, 0x81DF000, 0x2FEA0 },
    { 0x0, 0x2D360, 0x820F000, 0x2D360 },
    { 0x0, 0x39DC0, 0x823C800, 0x39DC0 },
    { 0x0, 0xF760, 0x8276800, 0xF760 },
    { 0x0, 0x23EA0, 0x8286000, 0x23EA0 },
    { 0x0, 0x26600, 0x82AA000, 0x26600 },
    { 0x0, 0x1D8C0, 0x82D0800, 0x1D8C0 },
    { 0x0, 0x21DE0, 0x82EE800, 0x21DE0 },
    { 0x0, 0x35100, 0x8310800, 0x35100 },
    { 0x0, 0x16F40, 0x8346000, 0x16F40 },
    { 0x0, 0x246A0, 0x835D000, 0x246A0 },
    { 0x0, 0x13240, 0x8381800, 0x13240 },
    { 0x0, 0x1D020, 0x83E3000, 0x1D020 },
    { 0x0, 0x16BA0, 0x84A5800, 0x16BA0 },
    { 0x0, 0x1A500, 0x84BC800, 0x1A500 },
    { 0x0, 0x1A060, 0x84D7000, 0x1A060 },
    { 0x0, 0x2CB20, 0x8395000, 0x2CB20 },
    { 0x0, 0x20BE0, 0x83C2000, 0x20BE0 },
    { 0x0, 0x26280, 0x841A000, 0x26280 },
    { 0x0, 0x217A0, 0x8440800, 0x217A0 },
    { 0x0, 0x1A000, 0x8462000, 0x1A000 },
    { 0x0, 0x190E0, 0x8400800, 0x190E0 },
    { 0x0, 0x291C0, 0x847C000, 0x291C0 },
    { 0x0, 0x16BA0, 0x84A5800, 0x16BA0 },
    { 0x0, 0x1A500, 0x84BC800, 0x1A500 },
    { 0x0, 0x1A060, 0x84D7000, 0x1A060 },
    { 0x0, 0x334600, 0x84F1800, 0x334600 },
    { 0x0, 0x1B65E0, 0x8826000, 0x1B65E0 },
    { 0x0, 0x47F20, 0x89DC800, 0x47F20 },
    { 0x0, 0x353E0, 0x8A24800, 0x353E0 },
    { 0x0, 0x20FA0, 0x8A5A000, 0x20FA0 },
    { 0x0, 0x444E0, 0x8A7B000, 0x444E0 },
    { 0x0, 0x145C0, 0x8ABF800, 0x145C0 },
    { 0x0, 0x44CA0, 0x8AD4000, 0x44CA0 },
    { 0x0, 0x10F6A0, 0x8B19000, 0x10F6A0 },
    { 0x0, 0x1622E0, 0x8C28800, 0x1622E0 },
};
// Sound test pages.
static void (*lbl_1_data_1C8C[5])(void) = {
    fn_1_C188, fn_1_BDD8, fn_1_A634, fn_1_BA64, fn_1_B4A4,
};
static u8 lbl_1_data_1CA0[2] = { 0x12, 0 }; // [0]: voice test 2 voice group, 0..31
static s16 lbl_1_data_1CA2 = 0x151; // sound test row 0: sound effect id, 0x151..0x1B6
static s16 lbl_1_data_1CA4 = 0x151;
static u32 lbl_1_data_1CA8 = 0x151;

// .bss: laid out in reverse definition order; the functions reach it through
// one pooled base (lbl_1_bss_2FD8).
static u8 lbl_1_bss_3058[0x18];  // unused
static s16 lbl_1_bss_3056;
static s16 lbl_1_bss_3054;
static u32 lbl_1_bss_3050;       // sound test row 0 voice
static u32 lbl_1_bss_304C;       // row 1 voice
static u32 lbl_1_bss_3048;       // row 2 voice
static u32 lbl_1_bss_3044;       // fn_80062890 result
static u32 lbl_1_bss_3040;       // unused
static f32 lbl_1_bss_300C[13];   // 3D test: listener values shown on screen
static f32 lbl_1_bss_2FF0[7];    // 3D test: emitter values shown on screen
static u8 lbl_1_bss_2FEF;        // unused
static u8 lbl_1_bss_2FEE;
static s8 lbl_1_bss_2FED;        // 3D test: emitter row 0..6
static s8 lbl_1_bss_2FEC;        // 3D test: listener row 0..12
static s16 lbl_1_bss_2FEA;       // 3D test: index into lbl_1_data_188C, 0..2
static u8 lbl_1_bss_2FE9;        // unused
static u8 lbl_1_bss_2FE8;
static s16 lbl_1_bss_2FE6;       // row 3 argument for fn_80062890, 0..68
static s16 lbl_1_bss_2FE4;       // row 2 index into lbl_1_data_18EC, 0..23
static s16 lbl_1_bss_2FE2;       // row 1 index into lbl_1_data_188C, 0..47
static u8 lbl_1_bss_2FE1;        // sound test row 0..3
static u8 lbl_1_bss_2FE0;        // sound test page: 0 = test active, 1 = paused (Y/X)
static u8 lbl_1_bss_2FDF;
static u8 lbl_1_bss_2FDE;
static u8 lbl_1_bss_2FDD;
static u8 lbl_1_bss_2FDC;        // unused
static u8 lbl_1_bss_2FDB;
static u8 lbl_1_bss_2FDA;
static u8 lbl_1_bss_2FD9;
static u8 lbl_1_bss_2FD8;        // unused

// MusyX 3D API (src/musyx/snd3d.c); the update calls take a trailing room argument.
extern u32 sndAddEmitter(SND_EMITTER* em, SND_FVECTOR* pos, SND_FVECTOR* dir, f32 maxDis, f32 comp, u32 flags,
                         u16 fxid, u8 maxVol, u8 minVol, SND_ROOM* room);
extern u32 sndRemoveEmitter(SND_EMITTER* em);
extern u32 sndUpdateEmitter(SND_EMITTER* em, SND_FVECTOR* pos, SND_FVECTOR* dir, u8 maxVol, SND_ROOM* room);
extern u32 sndAddListener(SND_LISTENER* li, SND_FVECTOR* pos, SND_FVECTOR* dir, SND_FVECTOR* heading,
                          SND_FVECTOR* up, f32 frontSur, f32 backSur, f32 soundSpeed, u32 flags, u8 vol,
                          f32* unk);
extern u32 sndRemoveListener(SND_LISTENER* li);
extern u32 sndUpdateListener(SND_LISTENER* li, SND_FVECTOR* pos, SND_FVECTOR* dir, SND_FVECTOR* heading,
                             SND_FVECTOR* up, u8 vol, SND_ROOM* room);


static inline struct SoundGroupData* SoundOptionValue(s32 index) {
    return lbl_800EF808.groups[(u32)index]; // (u32): index is added before the shift, as the original does
}


// .text:0x0000C188 size:0x11C
void fn_1_C188(void) {
    ChTaskHeader* queue = lbl_803CC1B8;
    switch ((s32)lbl_1_bss_2FDD) {
    case 0: {
        s32 option;
        ChSoundGroupTask* child;
        queue->result = 0;
        option = lbl_1_bss_2FD9 + 5;
        child = fn_800B0A5C_insertQueue((void*)fn_1_9F04, 1);
        child->step = 0;
        child->group = option;
        child->callback = fn_1_A908;
        ((ChTaskHeader*)lbl_803CC1B8)->result = 0;
        lbl_1_bss_2FDD++;
        break;
    }
    case 1:
        if (queue->result != 0) {
            if (lbl_1_bss_2FD9 != 17) {
                lbl_1_bss_2FD9++;
                lbl_1_bss_2FDD = 0;
            } else {
                queue->result = 0;
                lbl_1_bss_2FDD++;
            }
        }
        break;
    case 2:
        queue->func = fn_1_BFB0;
        lbl_1_bss_2FDD = 0;
        break;
    }
}

// .text:0x0000BFB0 size:0x1D8
void fn_1_BFB0(void) {
    u16 pressed = lbl_803C77B8._02;
    u16 held = lbl_803C77B8._04;
    if (pressed & 0x100) {
        u16 effect = lbl_1_bss_3056 % 13 + lbl_1_data_17C4[lbl_1_bss_3056 / 13];
        fn_1_BF34(effect);
    } else if (pressed & 0x1200) {
        fn_1_A718();
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_A348;
    } else if (held & 1) {
        if (held & 0x800) {
            lbl_1_bss_3056 -= 10;
        } else {
            lbl_1_bss_3056--;
        }
        if (lbl_1_bss_3056 < 0) {
            lbl_1_bss_3056 = 0xE9;
        }
    } else if (held & 2) {
        s16 next = lbl_1_bss_3056 + 1;
        if (held & 0x800) {
            next = lbl_1_bss_3056 + 10;
        }
        lbl_1_bss_3056 = next;
        if (next > 0xE9) {
            lbl_1_bss_3056 = 0;
        }
    }
}

// .text:0x0000BF34 size:0x7C
static inline const char* ReverbStatusName(u32 success) {
    return success != 0 ? "succeed" : "failed";
}

u32 fn_1_BF34(s16 effect) {
    u32 voice = sndFXStartEx(effect, 127, 63, 0);
    const char* status = ReverbStatusName(sndFXCtrl(voice, 0x5B, fn_800211F0()));
    OSReport("sndFXReverb was %s.\n", status);
    return voice;
}

// .text:0x0000BEF4 size:0x40
void fn_1_BEF4(s16 voice) {
    sndFXKeyOff(voice);
    sndFXCtrl(voice, 7, 0);
}

// .text:0x0000BDD8 size:0x11C
void fn_1_BDD8(void) {
    ChTaskHeader* queue = lbl_803CC1B8;
    switch ((s32)lbl_1_bss_2FDE) {
    case 0: {
        s32 option;
        ChSoundGroupTask* child;
        queue->result = 0;
        option = lbl_1_data_1CA0[0] + 5;
        child = fn_800B0A5C_insertQueue((void*)fn_1_9F04, 1);
        child->step = 0;
        child->group = option;
        child->callback = fn_1_A8B4;
        ((ChTaskHeader*)lbl_803CC1B8)->result = 0;
        lbl_1_bss_2FDE++;
        break;
    }
    case 1:
        if (queue->result != 0) {
            if (lbl_1_data_1CA0[0] != 31) {
                lbl_1_data_1CA0[0]++;
                lbl_1_bss_2FDE = 0;
            } else {
                queue->result = 0;
                lbl_1_bss_2FDE++;
            }
        }
        break;
    case 2:
        queue->func = fn_1_BC00;
        lbl_1_bss_2FDE = 0;
        break;
    }
}

// .text:0x0000BC00 size:0x1D8
void fn_1_BC00(void) {
    u16 pressed = lbl_803C77B8._02;
    u16 held = lbl_803C77B8._04;
    if (pressed & 0x100) {
        u16 effect = lbl_1_bss_3054 % 13 + lbl_1_data_17E8[lbl_1_bss_3054 / 13];
        fn_1_BF34(effect);
    } else if (pressed & 0x1200) {
        fn_1_A718();
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_A348;
    } else if (held & 1) {
        if (held & 0x800) {
            lbl_1_bss_3054 -= 10;
        } else {
            lbl_1_bss_3054--;
        }
        if (lbl_1_bss_3054 < 0) {
            lbl_1_bss_3054 = 0xB5;
        }
    } else if (held & 2) {
        s16 next = lbl_1_bss_3054 + 1;
        if (held & 0x800) {
            next = lbl_1_bss_3054 + 10;
        }
        lbl_1_bss_3054 = next;
        if (next > 0xB5) {
            lbl_1_bss_3054 = 0;
        }
    }
}

// .text:0x0000BA64 size:0x19C
// Sound test: loads the menu sound groups, then hands over to fn_1_B5B8.
void fn_1_BA64(void) {
    ChTaskHeader* task = lbl_803CC1B8;
    ChSoundGroupTask* child;

    switch (lbl_1_bss_2FDF) {
    case 0:
        task->result = 0;
        child = fn_800B0A5C_insertQueue((void*)fn_1_9F04, 1);
        child->step = 0;
        child->group = 1;
        child->callback = fn_1_A880;
        ((ChTaskHeader*)lbl_803CC1B8)->result = 0;
        lbl_1_bss_2FDF++;
        break;
    case 1:
        if (task->result != 0) {
            task->result = 0;
            lbl_1_bss_2FDF++;
        }
        break;
    case 2:
        task->result = 0;
        lbl_1_bss_2FDF++;
        break;
    case 3:
        task->result = 0;
        lbl_1_bss_2FDF++;
        break;
    case 4:
        lbl_1_bss_2FDF++;
        break;
    case 5:
        lbl_1_bss_2FDF++;
        break;
    case 6:
        task->result = 0;
        child = fn_800B0A5C_insertQueue((void*)fn_1_9F04, 1);
        child->step = 0;
        child->group = 0x29;
        child->callback = fn_1_A77C;
        ((ChTaskHeader*)lbl_803CC1B8)->result = 0;
        lbl_1_bss_2FDF++;
        break;
    case 7:
        if (task->result != 0) {
            task->result = 0;
            lbl_1_bss_2FDF++;
        }
        break;
    case 8:
        task->func = fn_1_B5B8;
        lbl_1_bss_2FDF = 0;
        break;
    }
}

// .text:0x0000B5B8 size:0x4AC
void fn_1_B5B8(void) {
    u16 down = lbl_803C77B8._02;
    u16 repeat = lbl_803C77B8._04;
    s32 fast = repeat & 0x800;
    s16 next;

    if (fast) {
        lbl_1_bss_2FE0 = 0;
    } else if (repeat & 0x400) {
        lbl_1_bss_2FE0 = 1;
    } else if (lbl_1_bss_2FE0 == 0) {
        if (down & 0x100) {
            if (lbl_1_bss_2FE1 == 0) {
                fn_1_BEF4((s16)lbl_1_bss_3050);
                lbl_1_bss_3050 = fn_1_BF34(lbl_1_data_1CA2);
            } else if (lbl_1_bss_2FE1 == 1) {
                u16 effect = lbl_1_data_188C[lbl_1_bss_2FE2];
                fn_1_BEF4((s16)lbl_1_bss_304C);
                lbl_1_bss_304C = fn_1_BF34(effect);
            } else if (lbl_1_bss_2FE1 == 2) {
                u16 effect = lbl_1_data_18EC[lbl_1_bss_2FE4];
                fn_1_BEF4((s16)lbl_1_bss_3048);
                lbl_1_bss_3048 = fn_1_BF34(effect);
            } else if (lbl_1_bss_2FE1 == 3) {
                lbl_1_bss_3044 = fn_80062890(lbl_1_bss_2FE6);
            }
        } else if (down & 0x1200) {
            fn_1_A718();
            fn_800ACFB0(lbl_800EF808.groups[0x29]);
            fn_800ACFB0(lbl_800EF808.groups[0x1]);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_A348;
        } else if (repeat & 1) {
            if (lbl_1_bss_2FE1 == 0) {
                if (fast) {
                    lbl_1_data_1CA2 -= 10;
                } else {
                    lbl_1_data_1CA2--;
                }
                if (lbl_1_data_1CA2 < 0x151) {
                    lbl_1_data_1CA2 = 0x1B6;
                }
            } else if (lbl_1_bss_2FE1 == 1) {
                if (--lbl_1_bss_2FE2 < 0) {
                    lbl_1_bss_2FE2 = 47;
                }
            } else if (lbl_1_bss_2FE1 == 2) {
                if (--lbl_1_bss_2FE4 < 0) {
                    lbl_1_bss_2FE4 = 23;
                }
            } else if (lbl_1_bss_2FE1 == 3) {
                if (--lbl_1_bss_2FE6 < 0) {
                    lbl_1_bss_2FE6 = 68;
                }
            }
        } else if (repeat & 2) {
            if (lbl_1_bss_2FE1 == 0) {
                next = lbl_1_data_1CA2 + 1;
                if (fast) {
                    next = lbl_1_data_1CA2 + 10;
                }
                lbl_1_data_1CA2 = next;
                if (next > 0x1B6) {
                    lbl_1_data_1CA2 = 0x151;
                }
            } else if (lbl_1_bss_2FE1 == 1) {
                if (++lbl_1_bss_2FE2 > 47) {
                    lbl_1_bss_2FE2 = 0;
                }
            } else if (lbl_1_bss_2FE1 == 2) {
                if (++lbl_1_bss_2FE4 > 23) {
                    lbl_1_bss_2FE4 = 0;
                }
            } else if (lbl_1_bss_2FE1 == 3) {
                if (++lbl_1_bss_2FE6 > 68) {
                    lbl_1_bss_2FE6 = 0;
                }
            }
        } else if (repeat & 8) {
            lbl_1_bss_2FE1--;
        } else if (repeat & 4) {
            if (++lbl_1_bss_2FE1 > 3) {
                lbl_1_bss_2FE1 = 0;
            }
        }
    }
}

// .text:0x0000B4A4 size:0x114
void fn_1_B4A4(void) {
    ChTaskHeader* queue = lbl_803CC1B8;
    switch ((s32)lbl_1_bss_2FE8) {
    case 0: {
        ChSoundGroupTask* child;
        queue->result = 0;
        child = fn_800B0A5C_insertQueue((void*)fn_1_9F04, 1);
        child->step = 0;
        child->group = 0x2A;
        child->callback = fn_1_A7E4;
        ((ChTaskHeader*)lbl_803CC1B8)->result = 0;
        lbl_1_bss_2FE8++;
        break;
    }
    case 1:
        if (queue->result != 0) {
            lbl_800EF808.soundMode = 2;
            sndOutputMode(SND_OUTPUTMODE_SURROUND);
            queue->result = 0;
            lbl_1_bss_2FE8++;
        }
        break;
    case 2:
        queue->func = fn_1_A95C;
        lbl_1_common_bss_49994.active = 0;
        lbl_1_bss_2FE8 = 0;
        break;
    }
}

// .text:0x0000A95C size:0xB48
// 3D sound test: A starts an emitter + listener, Y/X + left/right edits listener/emitter values.
void fn_1_A95C(void) {
    u16 down = lbl_803C77B8._02;
    u16 held = lbl_803C77B8._00;
    u16 repeat = lbl_803C77B8._04;
    s32 i;

    if (down & 0x100) {
        u16 effect = lbl_1_data_188C[lbl_1_bss_2FEA];

        if (lbl_1_common_bss_49994.active) {
            sndRemoveListener(&lbl_1_common_bss_49994.listener);
            sndRemoveEmitter(&lbl_1_common_bss_49994.emitter);
        }
        lbl_1_common_bss_49980.fxid = effect;
        lbl_1_common_bss_49980.maxVol = 127.0f;
        lbl_1_common_bss_49980.minVol = 0.0f;
        lbl_1_common_bss_49980.comp = 0.0f;
        lbl_1_common_bss_49980.maxDis = 100.0f;
        sndAddEmitter(&lbl_1_common_bss_49994.emitter, &lbl_1_common_bss_49994.emitter.pos, &lbl_1_common_bss_49994.emitter.dir, lbl_1_common_bss_49980.maxDis,
                      lbl_1_common_bss_49980.comp, SND_EMITTER_CONTINUOUS, lbl_1_common_bss_49980.fxid,
                      (u8)lbl_1_common_bss_49980.maxVol, (u8)lbl_1_common_bss_49980.minVol, NULL);

        lbl_1_common_bss_49970.frontSur = 100.0f;
        lbl_1_common_bss_49970.backSur = 10.0f;
        lbl_1_common_bss_49970.vol = 127;
        lbl_1_common_bss_49970.soundSpeed = 1.0f;
        lbl_1_common_bss_49994.listener.heading.x = 0.0f;
        lbl_1_common_bss_49994.listener.heading.y = 0.0f;
        lbl_1_common_bss_49994.listener.heading.z = -1.0f;
        lbl_1_common_bss_49994.listener.up.x = 0.0f;
        lbl_1_common_bss_49994.listener.up.y = 1.0f;
        lbl_1_common_bss_49994.listener.up.z = 0.0f;
        sndAddListener(&lbl_1_common_bss_49994.listener, &lbl_1_common_bss_49994.listener.pos, &lbl_1_common_bss_49994.listener.dir, &lbl_1_common_bss_49994.listener.heading,
                       &lbl_1_common_bss_49994.listener.up, lbl_1_common_bss_49970.frontSur, lbl_1_common_bss_49970.backSur,
                       lbl_1_common_bss_49970.soundSpeed, 0, lbl_1_common_bss_49970.vol, NULL);
        lbl_1_common_bss_49994.active = 1;
    } else if (down & 0x1200) {
        lbl_1_common_bss_49994.active = 0;
        fn_1_A718();
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_A348;
    } else if (held & 0x800) {
        // Y held: edit the listener (note rows 3 and 4 both edit dir.y)
        if (repeat & 1) {
            switch (lbl_1_bss_2FEC) {
            case 0: lbl_1_common_bss_49994.listener.pos.x -= 0.1; break;
            case 1: lbl_1_common_bss_49994.listener.pos.y -= 0.1; break;
            case 2: lbl_1_common_bss_49994.listener.pos.z -= 0.1; break;
            case 3: lbl_1_common_bss_49994.listener.dir.y -= 0.1; break;
            case 4: lbl_1_common_bss_49994.listener.dir.y -= 0.1; break;
            case 5: lbl_1_common_bss_49994.listener.dir.z -= 0.1; break;
            case 6: lbl_1_common_bss_49994.listener.heading.x -= 0.1; break;
            case 7: lbl_1_common_bss_49994.listener.heading.y -= 0.1; break;
            case 8: lbl_1_common_bss_49994.listener.heading.z -= 0.1; break;
            case 9: lbl_1_common_bss_49994.listener.up.x -= 0.1; break;
            case 10: lbl_1_common_bss_49994.listener.up.y -= 0.1; break;
            case 11: lbl_1_common_bss_49994.listener.up.z -= 0.1; break;
            case 12: lbl_1_common_bss_49994.listener.vol -= 10.0; break;
            }
        } else if (repeat & 2) {
            switch (lbl_1_bss_2FEC) {
            case 0: lbl_1_common_bss_49994.listener.pos.x += 0.1; break;
            case 1: lbl_1_common_bss_49994.listener.pos.y += 0.1; break;
            case 2: lbl_1_common_bss_49994.listener.pos.z += 0.1; break;
            case 3: lbl_1_common_bss_49994.listener.dir.y += 0.1; break;
            case 4: lbl_1_common_bss_49994.listener.dir.y += 0.1; break;
            case 5: lbl_1_common_bss_49994.listener.dir.z += 0.1; break;
            case 6: lbl_1_common_bss_49994.listener.heading.x += 0.1; break;
            case 7: lbl_1_common_bss_49994.listener.heading.y += 0.1; break;
            case 8: lbl_1_common_bss_49994.listener.heading.z += 0.1; break;
            case 9: lbl_1_common_bss_49994.listener.up.x += 0.1; break;
            case 10: lbl_1_common_bss_49994.listener.up.y += 0.1; break;
            case 11: lbl_1_common_bss_49994.listener.up.z += 0.1; break;
            case 12: lbl_1_common_bss_49994.listener.vol += 10.0; break;
            }
        } else if (repeat & 8) {
            lbl_1_bss_2FEC--;
            if (lbl_1_bss_2FEC < 0) {
                lbl_1_bss_2FEC = 12;
            }
        } else if (repeat & 4) {
            lbl_1_bss_2FEC++;
            if (lbl_1_bss_2FEC == 13) {
                lbl_1_bss_2FEC = 0;
            }
        }
    } else if (held & 0x400) {
        // X held: edit the emitter (note rows 3 and 4 both edit dir.y)
        if (repeat & 1) {
            switch (lbl_1_bss_2FED) {
            case 0: lbl_1_common_bss_49994.emitter.pos.x -= 0.1; break;
            case 1: lbl_1_common_bss_49994.emitter.pos.y -= 0.1; break;
            case 2: lbl_1_common_bss_49994.emitter.pos.z -= 0.1; break;
            case 3: lbl_1_common_bss_49994.emitter.dir.y -= 0.1; break;
            case 4: lbl_1_common_bss_49994.emitter.dir.y -= 0.1; break;
            case 5: lbl_1_common_bss_49994.emitter.dir.z -= 0.1; break;
            case 6: lbl_1_common_bss_49994.emitter.maxVol -= 10.0; break;
            }
        } else if (repeat & 2) {
            switch (lbl_1_bss_2FED) {
            case 0: lbl_1_common_bss_49994.emitter.pos.x += 0.1; break;
            case 1: lbl_1_common_bss_49994.emitter.pos.y += 0.1; break;
            case 2: lbl_1_common_bss_49994.emitter.pos.z += 0.1; break;
            case 3: lbl_1_common_bss_49994.emitter.dir.y += 0.1; break;
            case 4: lbl_1_common_bss_49994.emitter.dir.y += 0.1; break;
            case 5: lbl_1_common_bss_49994.emitter.dir.z += 0.1; break;
            case 6: lbl_1_common_bss_49994.emitter.maxVol += 10.0; break;
            }
        } else if (repeat & 8) {
            lbl_1_bss_2FED--;
            if (lbl_1_bss_2FED < 0) {
                lbl_1_bss_2FED = 6;
            }
        } else if (repeat & 4) {
            lbl_1_bss_2FED++;
            if (lbl_1_bss_2FED == 7) {
                lbl_1_bss_2FED = 0;
            }
        }
    } else if (repeat & 1) {
        if (--lbl_1_bss_2FEA < 0) {
            lbl_1_bss_2FEA = 1;
        }
    } else if (repeat & 2) {
        if (++lbl_1_bss_2FEA > 2) {
            lbl_1_bss_2FEA = 0;
        }
    }

    if (lbl_1_common_bss_49994.active) {
        sndUpdateListener(&lbl_1_common_bss_49994.listener, &lbl_1_common_bss_49994.listener.pos, &lbl_1_common_bss_49994.listener.dir, &lbl_1_common_bss_49994.listener.heading,
                          &lbl_1_common_bss_49994.listener.up, 0x80, NULL);
        sndUpdateEmitter(&lbl_1_common_bss_49994.emitter, &lbl_1_common_bss_49994.emitter.pos, &lbl_1_common_bss_49994.emitter.dir, 0x80, NULL);
    }

    // The original switches on the selected row rather than on i, so only that row's value is refreshed.
    for (i = 0; i < 13; i++) {
        switch (lbl_1_bss_2FEC) {
        case 0: lbl_1_bss_300C[0] = lbl_1_common_bss_49994.listener.pos.x; break;
        case 1: lbl_1_bss_300C[1] = lbl_1_common_bss_49994.listener.pos.y; break;
        case 2: lbl_1_bss_300C[2] = lbl_1_common_bss_49994.listener.pos.z; break;
        case 3: lbl_1_bss_300C[3] = lbl_1_common_bss_49994.listener.dir.y; break;
        case 4: lbl_1_bss_300C[4] = lbl_1_common_bss_49994.listener.dir.y; break;
        case 5: lbl_1_bss_300C[5] = lbl_1_common_bss_49994.listener.dir.z; break;
        case 6: lbl_1_bss_300C[6] = lbl_1_common_bss_49994.listener.heading.x; break;
        case 7: lbl_1_bss_300C[7] = lbl_1_common_bss_49994.listener.heading.y; break;
        case 8: lbl_1_bss_300C[8] = lbl_1_common_bss_49994.listener.heading.z; break;
        case 9: lbl_1_bss_300C[9] = lbl_1_common_bss_49994.listener.up.x; break;
        case 10: lbl_1_bss_300C[10] = lbl_1_common_bss_49994.listener.up.y; break;
        case 11: lbl_1_bss_300C[11] = lbl_1_common_bss_49994.listener.up.z; break;
        case 12: lbl_1_bss_300C[12] = lbl_1_common_bss_49994.listener.vol; break;
        }
    }
    for (i = 0; i < 7; i++) {
        switch (lbl_1_bss_2FED) {
        case 0: lbl_1_bss_2FF0[0] = lbl_1_common_bss_49994.emitter.pos.x; break;
        case 1: lbl_1_bss_2FF0[1] = lbl_1_common_bss_49994.emitter.pos.y; break;
        case 2: lbl_1_bss_2FF0[2] = lbl_1_common_bss_49994.emitter.pos.z; break;
        case 3: lbl_1_bss_2FF0[3] = lbl_1_common_bss_49994.emitter.dir.y; break;
        case 4: lbl_1_bss_2FF0[4] = lbl_1_common_bss_49994.emitter.dir.y; break;
        case 5: lbl_1_bss_2FF0[5] = lbl_1_common_bss_49994.emitter.dir.z; break;
        case 6: lbl_1_bss_2FF0[6] = lbl_1_common_bss_49994.emitter.maxVol; break;
        }
    }
}

// .text:0x0000A908 size:0x54
s32 fn_1_A908(void) {
    s32 index = lbl_1_bss_2FD9;
    fn_80021518(lbl_1_data_17A4[index], SoundOptionValue(index + 5));
    return 0;
}

// .text:0x0000A8B4 size:0x54
s32 fn_1_A8B4(void) {
    s32 index = lbl_1_data_1CA0[0];
    fn_80021518(lbl_1_data_17A4[index], SoundOptionValue(index + 5));
    return 0;
}

// .text:0x0000A880 size:0x34
s32 fn_1_A880(void) {
    fn_80021518(0x1C, lbl_800EF808.groups[0x1]);
    return 0;
}

// .text:0x0000A838 size:0x48
s32 fn_1_A838(void) {
    fn_80021518(0x1C, lbl_800EF808.groups[0x3]);
    fn_80021518(0x36, lbl_800EF808.groups[0x3]);
    return 0;
}

// .text:0x0000A7E4 size:0x54
s32 fn_1_A7E4(void) {
    s32 index = lbl_1_bss_2FDB;
    fn_80021518(lbl_1_data_1884[index], SoundOptionValue(index + 0x2A));
    return 0;
}

// .text:0x0000A7B0 size:0x34
s32 fn_1_A7B0(void) {
    fn_80021518(0x33, lbl_800EF808.groups[0x31]); // past groups[47]: the original reads the start of reverb here
    return 0;
}

// .text:0x0000A77C size:0x34
s32 fn_1_A77C(void) {
    fn_80021518(0x31, lbl_800EF808.groups[0x29]);
    return 0;
}

// .text:0x0000A718 size:0x64
s32 fn_1_A718(void) {
    s16 count = (s8)lbl_800EF808.groupStackCount;
    s8 remaining = count - 1;
    while (remaining > 0) {
        if (fn_800214D0() == 0) {
            return 0;
        }
        remaining--;
    }
    return 1;
}

// .text:0xA714 size:0x4
void fn_1_A714(void) {
}

// .text:0x0000A634 size:0xE0
void fn_1_A634(void) {
    ChTaskHeader* queue = lbl_803CC1B8;
    switch ((s32)lbl_1_bss_2FEE) {
    case 0: {
        ChSoundGroupTask* child;
        queue->result = 0;
        child = fn_800B0A5C_insertQueue((void*)fn_1_9F04, 1);
        child->step = 0;
        child->group = 3;
        child->callback = fn_1_A838;
        ((ChTaskHeader*)lbl_803CC1B8)->result = 0;
        lbl_1_bss_2FEE++;
        break;
    }
    case 1:
        if (queue->result != 0) {
            queue->result = 0;
            lbl_1_bss_2FEE++;
        }
        break;
    case 2:
        queue->func = fn_1_A464;
        lbl_1_bss_2FEE = 0;
        break;
    }
}

// .text:0x0000A464 size:0x1D0
void fn_1_A464(void) {
    u16 pressed = lbl_803C77B8._02;
    u16 held = lbl_803C77B8._04;
    if (pressed & 0x100) {
        fn_1_BEF4((s16)lbl_1_data_1CA8);
        lbl_1_data_1CA8 = fn_1_BF34(lbl_1_data_1CA4);
    } else if (pressed & 0x1200) {
        fn_1_A718();
        fn_800ACFB0(lbl_800EF808.groups[0x3]);
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_A348;
    } else if (held & 1) {
        if (held & 0x800) {
            lbl_1_data_1CA4 -= 10;
        } else {
            lbl_1_data_1CA4--;
        }
        if (lbl_1_data_1CA4 < 0x1AD) {
            lbl_1_data_1CA4 = 0x1B6;
        }
    } else if (held & 2) {
        s16 next = lbl_1_data_1CA4 + 1;
        if (held & 0x800) {
            next = lbl_1_data_1CA4 + 10;
        }
        lbl_1_data_1CA4 = next;
        if (next > 0x1B6) {
            lbl_1_data_1CA4 = 0x151;
        }
    }
}

// .text:0x0000A348 size:0x11C
void fn_1_A348(void) {
    u16 held = lbl_803C77B8._04;
    u16 pressed = lbl_803C77B8._02;
    if (held & 8) {
        lbl_1_common_bss_49A78[0] = (lbl_1_common_bss_49A78[0] + 4) % 5;
        return;
    }
    if (held & 4) {
        lbl_1_common_bss_49A78[0] = (lbl_1_common_bss_49A78[0] + 6) % 5;
        return;
    }
    if (pressed & 0x100) {
        ((ChTaskHeader*)lbl_803CC1B8)->func = lbl_1_data_1C8C[lbl_1_common_bss_49A78[0]];
        lbl_1_common_bss_49A78[1] = 0;
        return;
    }
    if (pressed & 0x1200) {
        lbl_1_bss_2FDA = 0;
        lbl_1_bss_2FD9 = 0;
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_C2A4;
    }
}

// .text:0x0000A2E4 size:0x64
void fn_1_A2E4(void) {
    switch ((s32)lbl_1_bss_2FDA) {
    case 0:
        lbl_1_bss_2FDA++;
        break;
    case 1:
        lbl_1_bss_2FDA++;
        break;
    case 2:
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_A250;
        break;
    }
}
