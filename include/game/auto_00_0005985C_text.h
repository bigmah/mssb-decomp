#ifndef __AUTO_00_0005985C_TEXT_GAME_H__
#define __AUTO_00_0005985C_TEXT_GAME_H__

#include "mssbTypes.h"

typedef struct {
    /*0x00*/ s16 runs;
    /*0x02*/ u8 _02[0x24];
} TeamScore; // size: 0x26

// Layout of g_Scores (game.rel .bss 0x317C0). Other units still see it as u8[].
typedef struct {
    /*0x00*/ s32 inning;
    /*0x04*/ TeamScore team[2];
    /*0x50*/ u8 _50[0x4C];
    /*0x9C*/ s16 _9C; // runners that crossed home this play
    /*0x9E*/ s16 _9E;
    /*0xA0*/ s16 _A0;
    /*0xA2*/ s16 _A2;
    /*0xA4*/ s16 winningTeam; // 2: tie
    /*0xA6*/ u8 _A6[4];
    /*0xAA*/ u8 finalInning;
    /*0xAB*/ u8 _AB;
    /*0xAC*/ u8 inningStage; // see fn_3_5C530
    /*0xAD*/ u8 bottomHalf;
    /*0xAE*/ u8 _AE[0x13];
    /*0xC1*/ u8 _C1;
    /*0xC2*/ u8 _C2;
    /*0xC3*/ u8 _C3;
    /*0xC4*/ u8 _C4;
    /*0xC5*/ u8 _C5;
    /*0xC6*/ u8 _C6;
    /*0xC7*/ u8 _C7;
} ScoresStruct; // size: 0xC8

void fn_3_5985C(s32 arg0, s32 arg1);

void fn_3_598D0(void);

s32 fn_3_5DCE0(void);

s32 fn_3_59BCC(s32 stage);

void fn_3_5EDD8(void);

void fn_3_5FE88(void);

void fn_3_5F720(void);

void fn_3_5CD24(void);

void fn_3_5AE0C(void);

s32 fn_3_5C530(s32 inning);

void fn_3_5D9F8(void);

void fn_3_5C69C(s32 type);

void fn_3_5D51C(void);

void fn_3_5B408(void);

void fn_3_5B368(void);

void fn_3_5A684(void);

void fn_3_59AC0(s32 unused1, s32 unused2, void* allocation);

void fn_3_59A90(void);

s32 fn_3_59AE4(void);

void fn_3_5A6D4(u8 status);

void fn_3_5ED98(void);

void fn_3_59B20(void);
void fn_3_5A6A0(s32 a, s32 b, s32 c, s32 d);
void fn_3_5CFD0(void);
void fn_3_5C5C8(void);
void fn_3_5C418(void);
void fn_3_5D3FC(void);
s32 fn_3_5B220(s32 arg);
void fn_3_5ACA0(void);
void fn_3_59918(s32 x, s32 unused);
void fn_3_5EE58(void);
void fn_3_5EFEC(void);
void fn_3_5F7A8(void);
s32 fn_3_5B380(void);
void fn_3_5B0C4(void);
void fn_3_5B41C(void);

#endif
