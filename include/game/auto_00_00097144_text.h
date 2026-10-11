#ifndef __GAME_AUTO_00_00097144_TEXT_H_
#define __GAME_AUTO_00_00097144_TEXT_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_8000F150.h"  // LayoutSlot lbl_80371C30
#include "main/file_800527C4.h"  // MenuDef, fn_80053FE8
#include "main/file_800639BC.h"  // lbl_8034E9A0 (captain), fn_80069A98
#include "main/menu_globals.h"   // lbl_8034E978, lbl_803297E0

// In-game HUD flags (lbl_3_common_bss_32724, 0x124 bytes); only the fields used here.
typedef struct GameHudFlags {
    /*0x00*/ u8 _00[0x96];
    /*0x96*/ u8 hudOff; // set when the HUD is being torn down (fn_3_972C8)
    /*0x97*/ u8 _97;
    /*0x98*/ u8 _98;
    /*0x99*/ u8 _99;
    /*0x9A*/ u8 _9A[0xA5 - 0x9A];
    /*0xA5*/ u8 _A5;
    /*0xA6*/ u8 _A6;
    /*0xA7*/ u8 _A7;
    /*0xA8*/ u8 _A8;
    /*0xA9*/ u8 _A9;
    /*0xAA*/ u8 pauseTitleShown; // fn_3_98DE0 task alive
    /*0xAB*/ u8 pauseMenuShown;  // fn_3_9894C task alive
    /*0xAC*/ u8 _AC;
    /*0xAD*/ u8 _AD;
    /*0xAE*/ u8 _AE;
    /*0xAF*/ u8 _AF;
    /*0xB0*/ u8 _B0;
    /*0xB1*/ u8 _B1;
    /*0xB2*/ u8 _B2;
    /*0xB3*/ u8 _B3;
    /*0xB4*/ u8 _B4;
    /*0xB5*/ u8 _B5;
    /*0xB6*/ u8 _B6;
    /*0xB7*/ u8 _B7[0xBC - 0xB7];
    /*0xBC*/ u8 _BC;
    /*0xBD*/ u8 _BD;
    /*0xBE*/ u8 _BE;
    /*0xBF*/ u8 _BF;
    /*0xC0*/ u8 _C0;
    /*0xC1*/ u8 _C1;
    /*0xC2*/ u8 _C2;
    /*0xC3*/ u8 _C3;
    /*0xC4*/ u8 _C4;
    /*0xC5*/ u8 _C5;
    /*0xC6*/ u8 _C6;
    /*0xC7*/ u8 _C7;
    /*0xC8*/ u8 _C8[0xCD - 0xC8];
    /*0xCD*/ u8 _CD;
    /*0xCE*/ u8 _CE;
    /*0xCF*/ u8 _CF;
    /*0xD0*/ u8 _D0;
    /*0xD1*/ u8 _D1;
    /*0xD2*/ u8 _D2[0xD6 - 0xD2];
    /*0xD6*/ u8 _D6;
    /*0xD7*/ u8 _D7[0xD9 - 0xD7];
    /*0xD9*/ u8 _D9;
    /*0xDA*/ u8 _DA;
    /*0xDB*/ u8 _DB[0x124 - 0xDB];
} GameHudFlags; // size: 0x124

extern GameHudFlags lbl_3_common_bss_32724;

// Pause / in-game menu state (lbl_3_common_bss_34C90, 0x264 bytes); only the fields used here.
typedef struct GamePauseState {
    /*0x000*/ u8 team; // team that opened the menu
    /*0x001*/ u8 _001[0x12 - 0x1];
    /*0x012*/ s16 _012;
    /*0x014*/ u8 _014[0x1D0 - 0x14];
    /*0x1D0*/ u8 layout;  // index into the item layout table (lbl_3_data_D860)
    /*0x1D1*/ u8 menu;
    /*0x1D2*/ u8 state;
    /*0x1D3*/ u8 _1D3;
    /*0x1D4*/ u8 _1D4[0x1D9 - 0x1D4];
    /*0x1D9*/ u8 itemsState; // 0: opening, 2: closed, 3: done
    /*0x1DA*/ s8 cursor;
    /*0x1DB*/ u8 _1DB[0x221 - 0x1DB];
    /*0x221*/ u8 _221;
    /*0x222*/ u8 _222[0x23F - 0x222];
    /*0x23F*/ u8 _23F[2]; // per team
    /*0x241*/ u8 _241[0x264 - 0x241];
} GamePauseState; // size: 0x264

extern GamePauseState lbl_3_common_bss_34C90;

// HUD sprite task (lbl_803CC1B8 while one of this unit's tasks runs); only the fields used here.
typedef struct HudTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 _04[0x14 - 0x4];
    /*0x14*/ u16 baseIdx; // first slot in lbl_80371C30
    /*0x16*/ u16 _16;
    /*0x18*/ u16 timer;
    /*0x1A*/ u16 _1A;
    /*0x1C*/ u16 state;
    /*0x1E*/ u16 _1E;
    /*0x20*/ u16 _20;
} HudTask;

#define HUD_TASK ((HudTask*)lbl_803CC1B8)
#define HUD_OBJ(task, i) (lbl_80371C30[(task)->baseIdx + (i)].obj)

// Mirror of SavedSettings (main/file_8004207C.h, lbl_800E8754).
typedef struct HudPortSettings {
    /*0x0*/ u8 _0;
    /*0x1*/ u8 _1;
    /*0x2*/ u8 _2;
    /*0x3*/ u8 _3;
    /*0x4*/ u8 _4;
    /*0x5*/ u8 _5;
    /*0x6*/ u8 _6;
} HudPortSettings; // size: 0x7

typedef struct HudSavedSettings {
    /*0x00*/ u8 innings;
    /*0x01*/ u8 _01[3];
    /*0x04*/ u8 _04;
    /*0x05*/ u8 _05;
    /*0x06*/ u8 _06;
    /*0x07*/ HudPortSettings port[4];
    /*0x23*/ u8 _23[5];
} HudSavedSettings; // size: 0x28

extern HudSavedSettings lbl_800E8754;
extern MenuDef lbl_800FEF70[];

// g_Scores (0xC8 bytes); only the fields used here.
typedef struct HudScores {
    /*0x00*/ s32 inning;
    /*0x04*/ u8 _04[0xAD - 0x4];
    /*0xAD*/ u8 _AD;
    /*0xAE*/ u8 _AE[0xC8 - 0xAE];
} HudScores;

extern HudScores g_Scores;

// Main.dol calls used here.
extern void fn_80035CA4(s32 id);
extern void fn_8003649C(void* owner, s32 idx, s32 track, u16 animId, u32 frame);
extern void fn_80034E20(void* group, void* descs);
extern void fn_8004CC4C(u8 first, u8 second, u8 third, s32 selection, s16 value);
extern void fn_8004D0F0(void);
extern void fn_800486E0(s32 priority, s8 a, s8 b);
extern void sndFXKeyOff(u32);

void fn_3_97144(void);
void fn_3_972A0(void* owner, s32 idx, s32 track, u32 frame);
void fn_3_972C8(void);
void fn_3_973EC(void);
void fn_3_97800(void);
void fn_3_978DC(void);
void fn_3_97CEC(void);
void fn_3_98028(void);
void fn_3_983B8(void);
void fn_3_98434(void);
void fn_3_9894C(void);
void fn_3_98C20(void);
void fn_3_98DE0(void);
void fn_3_98EA8(void);
void fn_3_99064(void);

#endif
