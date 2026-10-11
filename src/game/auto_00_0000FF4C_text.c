#include "game/auto_00_0000FF4C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_540.h"
#include "Dolphin/rand.h"

// lbl_3_data_228 is a 0x14-byte object; its first word is a running counter.
typedef struct {
    /*0x00*/ u32 counter;
    /*0x04*/ u8 _04[0x10];
} RandSeedObj;
extern RandSeedObj lbl_3_data_228;

static inline s32 RandStep(s32 x, s32 s) { return (x * 8 + (x >> s) + (x & 0x505)) & 0x7FFF; }

// .text:0x0000FF4C size:0x4C mapped:0x8064EFE0
void fn_3_FF4C(void) {
    g_Ball.StaticRandomInt1 = RandStep(g_Ball.StaticRandomInt1, 1);
    g_Ball.StaticRandomInt2 = RandStep(g_Ball.StaticRandomInt2, 2);
}

// .text:0x0000FF98 size:0x98 mapped:0x8064F02C
void fn_3_FF98(void) {
    return;
}

// .text:0x00010030 size:0x11C mapped:0x8064F0C4
void fn_3_10030(void) {
    return;
}

// .text:0x0001014C size:0x17C mapped:0x8064F1E0
void ballPhysica(void) {
    return;
}
