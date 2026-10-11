#ifndef __GAME_rep_18E8_H_
#define __GAME_rep_18E8_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

// g_Fielders entry (stride 0x268); only the fields used here.
typedef struct RepFielder {
    /*0x000*/ VecXYZ pos;
    /*0x00C*/ u8 _00C[0x14 - 0xC];
    /*0x014*/ VecXYZ dest; // destination
    /*0x020*/ u8 _020[0x30 - 0x20];
    /*0x030*/ f32 velX;
    /*0x034*/ f32 velZ;
    /*0x038*/ u8 _038[0x48 - 0x38];
    /*0x048*/ f32 facing;
    /*0x04C*/ u8 _04C[0x50 - 0x4C];
    /*0x050*/ f32 speed;
    /*0x054*/ u8 _054[0x70 - 0x54];
    /*0x070*/ f32 _070;
    /*0x074*/ u8 _074[0x84 - 0x74];
    /*0x084*/ f32 distToFielder[9];
    /*0x0A8*/ f32 distToBase[4];
    /*0x0B8*/ f32 _0B8;
    /*0x0BC*/ u8 _0BC[0x120 - 0xBC];
    /*0x120*/ f32 _120;
    /*0x124*/ f32 _124;
    /*0x128*/ u8 _128[0x174 - 0x128];
    /*0x174*/ f32 _174;
    /*0x178*/ s16 rosterID;
    /*0x17A*/ s16 _17A; // action id (lbl_3_data_7E34 index)
    /*0x17C*/ s16 _17C;
    /*0x17E*/ s16 framesToDest;
    /*0x180*/ u8 _180[0x18C - 0x180];
    /*0x18C*/ s16 coveringBase;
    /*0x18E*/ u8 _18E[0x192 - 0x18E];
    /*0x192*/ s16 _192;
    /*0x194*/ u8 _194[0x1AC - 0x194];
    /*0x1AC*/ s16 _1AC;
    /*0x1AE*/ u8 _1AE[0x1C2 - 0x1AE];
    /*0x1C2*/ s16 _1C2; // angle
    /*0x1C4*/ u8 _1C4[0x1CD - 0x1C4];
    /*0x1CD*/ u8 _1CD; // speed-related stat
    /*0x1CE*/ u8 _1CE;
    /*0x1CF*/ u8 _1CF[0x1D7 - 0x1CF];
    /*0x1D7*/ u8 _1D7;
    /*0x1D8*/ u8 _1D8[0x1ED - 0x1D8];
    /*0x1ED*/ u8 _1ED;
    /*0x1EE*/ u8 _1EE;
    /*0x1EF*/ u8 _1EF[0x1F5 - 0x1EF];
    /*0x1F5*/ s8 _1F5; // base
    /*0x1F6*/ u8 _1F6;
    /*0x1F7*/ s8 _1F7;
    /*0x1F8*/ u8 _1F8;
    /*0x1F9*/ u8 _1F9[0x200 - 0x1F9];
    /*0x200*/ u8 _200;
    /*0x201*/ u8 _201[0x20D - 0x201];
    /*0x20D*/ u8 minigamePlayer;
    /*0x20E*/ u8 _20E[0x211 - 0x20E];
    /*0x211*/ u8 _211;
    /*0x212*/ u8 _212; // state
    /*0x213*/ u8 _213; // runner index
    /*0x214*/ u8 _214; // lbl_3_data_4860 index
    /*0x215*/ u8 _215;
    /*0x216*/ u8 _216[0x268 - 0x216];
} RepFielder; // size: 0x268

extern RepFielder g_Fielders[9];

// g_RunningLogic (0x20 bytes); only the fields used here.
typedef struct RepRunningLogic {
    /*0x00*/ s16 _00; // one nibble per base
    /*0x02*/ u8 _02[0x20 - 0x2];
} RepRunningLogic;

extern RepRunningLogic g_RunningLogic;
extern GameScores g_Scores;

void fn_3_A009C(void);
s32 fn_3_A1D04(void);
int fn_3_A1DA0(void);
int fn_3_A1F3C(void);
int fn_3_A2048(void);
int fn_3_A222C(void);
int fn_3_A2404(void);
int fn_3_A25C4(void);
int fn_3_A295C(void);
int fn_3_A2B6C(void);
int fn_3_A2C9C(void);
int fn_3_A2DDC(void);
int fn_3_A2FD8(void);
int fn_3_A31E8(void);
int fn_3_A32B8(void);
int fn_3_A3374(void);
int fn_3_A36BC(void);
int fn_3_A372C(void);
int fn_3_A3768(void);
int fn_3_A37BC(void);
void fn_3_A384C(void);
void fn_3_A3B30(void);
void fn_3_A3C00(void);
void fn_3_A3CC0(void);
void fn_3_A4158(int);
void fn_3_A41E8(void);
int fn_3_A46A0(s32 i);
void fn_3_A4A10(void);
void fn_3_A4F50(void);
void fn_3_A53DC(s32 i);
void fn_3_A5704(void);
void fn_3_A5B4C(void);
void fn_3_A63E4(void);
void fn_3_A67E8(s32 i);
s32 fn_3_A6810(f32, f32, f32, f32);
s32 fn_3_A6ABC(f32, f32);
void fn_3_A6D48(void);
void fn_3_A6E98(s32 fielder);
void fn_3_A7040(void);
void fn_3_A76B4(void);
void fn_3_A7C88(void);
void fn_3_A7EF8(void);
void fn_3_A8074(s32 idx);
void fn_3_A8338(s32 idx);
s32 fn_3_A8478(s32* out0, s32* out1);
void fn_3_A85C8(void);
void fn_3_A89D4(void);
void fn_3_A9354(int fi, int mode);
void fn_3_A96FC(int);
void fn_3_A9984(int);
void fn_3_A9C74(int);
void fn_3_A9D20(void);
void fn_3_AAA3C(int);
int fn_3_AABF8(void);
void fn_3_AAC84(f32* x, f32* z);
void fn_3_AAFF0(void);
void fn_3_AB554(void);
void fn_3_AB5B0(void);
void fn_3_ABDD0(void);

#endif // !__GAME_rep_18E8_H_
