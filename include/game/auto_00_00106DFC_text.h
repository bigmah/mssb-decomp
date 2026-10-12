#ifndef __AUTO_00_00106DFC_TEXT_GAME_H__
#define __AUTO_00_00106DFC_TEXT_GAME_H__

#include "mssbTypes.h"

// Minigame result / high-score table entry.
typedef struct {
    /*0x0*/ s32 score;
    /*0x4*/ s16 sub;    // secondary score (tie-breaker)
    /*0x6*/ s16 charId; // roster value at +0x24 of the player's character
} RankEnt; // size: 0x8

// View of lbl_803C6CF8 (ARAMLoader in main/aramloader.h, whose `idle` is a volatile s8;
// this unit reads it as a plain byte).
typedef struct {
    /*0x000*/ u8 _000[0x715];
    /*0x715*/ u8 _715; // 1 when the pending disc/ARAM transfer finished (ARAMLoader.idle)
    /*0x716*/ u8 _716[0x724 - 0x716];
} ARAMLoaderView; // size: 0x724

// The minigame's scene task (g_Minigame._1E04, from fn_800B0A5C_insertQueue), only the fields used here.
typedef struct MinigameTask {
    /*0x00*/ u8 _00[0x18];
    /*0x18*/ u16 _18; // nonzero: the minigame asks to quit
    /*0x1A*/ u16 _1A; // nonzero: the minigame finished
} MinigameTask;

// lbl_3_common_bss_32724 (GameHudFlags in game/auto_00_00097144_text.h, which also
// declares lbl_3_common_bss_34C90 with a different view), only the fields used here.
typedef struct HudFlagsView {
    /*0x00*/ u8 _00[0xB8];
    /*0xB8*/ u8 _B8;
    /*0xB9*/ u8 _B9;
    /*0xBA*/ u8 _BA;
    /*0xBB*/ u8 _BB;
    /*0xBC*/ u8 _BC[0xC4 - 0xBC];
    /*0xC4*/ u8 _C4;
    /*0xC5*/ u8 _C5[0xD8 - 0xC5];
    /*0xD8*/ u8 loadStep; // fn_3_1665E4 trail-file load state
    /*0xD9*/ u8 _D9[0x124 - 0xD9];
} HudFlagsView; // size: 0x124

// lbl_3_data_228 (0x14 bytes, RandSeedObj in auto_00_0000FF4C_text.c).
typedef struct RandSeedView {
    /*0x00*/ u32 counter;
    /*0x04*/ u8 _04[0xC];
    /*0x10*/ u8 _10;
    /*0x11*/ u8 _11[3];
} RandSeedView; // size: 0x14

void fn_3_106EB0(void);
void fn_3_107078(void);
void fn_3_10F550(s8 a, s16 b);
void fn_3_1104A8(void);
void fn_3_106DFC(void);
s32 fn_3_106E50(void);
s32 fn_3_107988(u32 v);
RankEnt* fn_3_109D88(void);
void fn_3_10FB74(void);
void fn_3_10C7A4(void);
void fn_3_10B200(void);
void fn_3_10A01C(void);
u8 fn_3_107D70(s8 i);
u8 fn_3_107DB4(s8 i);
u8 fn_3_107DF8(s8 i);
u8 minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased(s8 i);
s32 fn_3_107C40(void);
s32 fn_3_107C88(void);
u8 fn_3_107CD0(void);
void fn_3_1078F8(void);
void fn_3_10AD48(void);
void fn_3_10AE18(void);
void fn_3_10768C(void);
s32 fn_3_107B9C(void* a, void* b);
s32 fn_3_107BD0(void* a, void* b);
s32 fn_3_107C04(void* a, void* b);
s32 fn_3_107D34(void* a, void* b);
s32 fn_3_10F564(void);
void fn_3_10C58C(void);
void fn_3_107784(void);
struct StatInput;
void fn_3_10754C(struct StatInput* dst);
void fn_3_10C450(s32 a, s32 b);
void fn_3_10F5BC(void);
void fn_3_10F1D4(void);
void fn_3_1070A4(void);
s32 fn_3_108854(void);
void fn_3_1079C8(u8* out, s32 mode);
u32 fn_3_109CE8(RankEnt* p);
void fn_3_10EFAC(void);
void fn_3_1089E8(void);
void fn_3_108230(void);
void fn_3_109254(void);
void fn_3_10AEF0(void);
void fn_3_107E80(void);
void fn_3_1104D4(void);
void fn_3_10F3D8(void);
void fn_3_106ED4(void);
void fn_3_10FBE4(void);
void fn_3_109DE0(RankEnt* out);
void fn_3_10F91C(void);
void fn_3_10F684(void);
void fn_3_10722C(void);
void fn_3_1084B4(void);
void fn_3_10C81C(void);
void fn_3_10B8D0(void);
void fn_3_10BE7C(void);
void fn_3_108C54(void);
void fn_3_10B27C(void);
void fn_3_10FDC8(void);
void fn_3_10952C(void);
void fn_3_10E60C(void);
void fn_3_10A0A0(void);
void fn_3_10CC20(void);

#endif
