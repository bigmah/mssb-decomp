#ifndef __GAME_rep_36D8_H_
#define __GAME_rep_36D8_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "static/Camera.h"

// One g_Runners entry (InMemRunnerType, size 0x154), only the fields used here.
// This unit declares g_Runners as bytes, so it reaches the fields through this view.
typedef struct RepRunnerView {
    /*0x000*/ u8 _000[0x64];
    /*0x064*/ f32 fractionalBasesRan;
    /*0x068*/ u8 _068[0x137 - 0x68];
    /*0x137*/ u8 runningDirectionCode;
    /*0x138*/ u8 _138[0x154 - 0x138];
} RepRunnerView;

// Target that moves along the base path (g_Minigame + 0xCB0).
typedef struct RepTarget {
    /*0x00*/ Vec pos;
    /*0x0C*/ Vec vel;
    /*0x18*/ f32 bases; // position along the base path, 0..4
    /*0x1C*/ s16 timer;
    /*0x1E*/ u8 active;
} RepTarget;

// This minigame's view of g_Minigame. This unit declares g_Minigame as bytes,
// so new code reaches the fields through this view (REP_MG).
typedef struct RepMinigameView {
    /*0x0000*/ u8 _0000[0xCB0];
    /*0x0CB0*/ RepTarget target;
    /*0x0CD0*/ u8 _0CD0[0x1890 - 0xCD0];
    /*0x1890*/ s16 points[4];
    /*0x1898*/ u8 _1898[0x18FC - 0x1898];
    /*0x18FC*/ s8 _18FC[4]; // per runner slot; < 0: none
    /*0x1900*/ u8 _1900[0x1B19 - 0x1900];
    /*0x1B19*/ u8 phase;
    /*0x1B1A*/ u8 _1B1A[0x1B20 - 0x1B1A];
    /*0x1B20*/ u8 _1B20[15];
    /*0x1B2F*/ u8 _1B2F[0x1D58 - 0x1B2F];
    /*0x1D58*/ s16 _1D58;
    /*0x1D5A*/ u8 _1D5A[0x1D74 - 0x1D5A];
    /*0x1D74*/ s8 _1D74; // -1: none
} RepMinigameView;

void fn_3_13C7BC(void);
u32 fn_3_13D578(s8 a);
s32 fn_3_13D5E8(f32* a, f32* b);
void fn_3_13D618(void);
s32 fn_3_13DA20(f32* a, f32* b);
f32 fn_3_13DA50(s8 idx, f32 ang, s8* dir);
void fn_3_13DC48(s8 idx, f32 ang, f32* out1, f32* out2);
f32 fn_3_13DDE0(f32 a, f32 b, u8 mode);
void fn_3_13DEA4(void);
void fn_3_13DFBC(camera_803c639c_s* cam);
void fn_3_13E174(u8 a);
void fn_3_13E21C(RepTarget* t);
void fn_3_13E3A4(RepTarget* t);
void fn_3_13E670(void);
void fn_3_13E6D4(void);
void fn_3_13E7D4(void);
void fn_3_13EA30(void);
void fn_3_13EC44(void);
void fn_3_13F484(void);
void fn_3_13F6C8(void);
void fn_3_13F7E4(void);
void fn_3_13F8C4(void);
void fn_3_13FC24(void);
void fn_3_140284(void);
void fn_3_140484(void);
void fn_3_1405D8(void);
void fn_3_1406F4(void);
void fn_3_1409AC(void);
void fn_3_140BCC(void);
void fn_3_140CE0(void);
void fn_3_1410F0(void);
void fn_3_1412BC(void);
void fn_3_1413E4(void);
void fn_3_1414AC(void);

#endif // !__GAME_rep_36D8_H_
