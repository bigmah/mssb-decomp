#ifndef __GAME_rep_4090_H_
#define __GAME_rep_4090_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "main/file_800263FC.h" // Emitter, Particle

// g_Fielders entry (stride 0x268), only the fields used here.
typedef struct DustFielder {
    /*0x000*/ Vec pos;
    /*0x00C*/ u8 _00C[0x50 - 0xC];
    /*0x050*/ f32 speed;
    /*0x054*/ u8 _054[0x268 - 0x54];
} DustFielder; // size: 0x268

s32 fn_3_16C548(Emitter* e);
void fn_3_16C878(Vec* pos, Emitter* e, s32 n);
void fn_3_16CC2C(Vec* pos, u8 who);
s32 fn_3_16D4D8(s32 id, f32 x);
void fn_3_16D5E4(u8 who);

#endif // !__GAME_rep_4090_H_
