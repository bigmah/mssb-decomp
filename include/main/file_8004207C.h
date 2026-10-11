#ifndef __MAIN_FILE_8004207C_H__
#define __MAIN_FILE_8004207C_H__

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_8000F150.h"
#include "main/file_8004B284.h"
#include "main/file_8001FE00.h"
#include "main/menu_globals.h"

// Anything that owns a run of layout objects in lbl_80371C30 starting at baseIdx.
typedef struct LayoutOwner {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 baseIdx;
} LayoutOwner;

// Per-character swing effect callback (table lbl_800FBE64).
typedef void (*SwingFxFunc)(CharModel* model, s32 animID, u32 colorIdx, f32 frame);


// Character/team select work area (lbl_8034E9A0, only the fields used here).
typedef struct CharSelWork {
    /*0x0000*/ CharacterStats chars[113]; // base stats, 9 per team slot
    /*0x46A0*/ u8 _46A0[0x46E0 - 0x46A0];
    /*0x46E0*/ s8 _46E0[2][4];
    /*0x46E8*/ u8 _46E8[0x46F8 - 0x46E8];
    /*0x46F8*/ s8 teamPort[2]; // controller port per team
    /*0x46FA*/ u8 _46FA[0x4704 - 0x46FA];
    /*0x4704*/ u8 _4704;
    /*0x4705*/ u8 _4705;
    /*0x4706*/ u8 _4706[0x470D - 0x4706];
    /*0x470D*/ u8 _470D[2];
    /*0x470F*/ u8 _470F[0x4720 - 0x470F];
    /*0x4720*/ s32 _4720[2];
    /*0x4728*/ u8 _4728[0x472C - 0x4728];
    /*0x472C*/ PortInput input[4];
    /*0x4744*/ u8 _4744[0x47F9 - 0x4744];
    /*0x47F9*/ u8 _47F9[2][9][9];
    /*0x489B*/ u8 boosted[2][9]; // per team slot: star boost applied
    /*0x48AD*/ u8 _48AD;
    /*0x48AE*/ u8 _48AE;
    /*0x48AF*/ u8 _48AF;
    /*0x48B0*/ u8 _48B0;
    /*0x48B1*/ u8 _48B1;
    /*0x48B2*/ u8 _48B2;
    /*0x48B3*/ u8 _48B3;
} CharSelWork;

extern CharSelWork lbl_8034E9A0;

// Batting order per team (lbl_80354720).
typedef struct OrderEntry {
    /*0x0*/ u8 _0;
    /*0x1*/ u8 _1;
    /*0x2*/ s8 slot;
    /*0x3*/ u8 _3;
} OrderEntry;

extern OrderEntry lbl_80354720[2][9];

// Match options screen state (lbl_803C5F04).
typedef struct MatchOptions {
    /*0x00*/ u8 _00[0x2C];
    /*0x2C*/ u16 _2C;
    /*0x2E*/ u8 _2E;
    /*0x2F*/ u8 _2F;
    /*0x30*/ u16 state;
    /*0x32*/ u8 _32;
    /*0x33*/ u8 _33;
    /*0x34*/ u8 _34;
    /*0x35*/ u8 _35;
    /*0x36*/ u8 _36;
    /*0x37*/ u8 lastDir[2];
    /*0x39*/ u8 _39[2];
    /*0x3B*/ s8 option[5];
    /*0x40*/ s8 prevOption[5];
    /*0x45*/ s8 playerOption[4][4];
    /*0x55*/ s8 prevPlayerOption[4][4];
    /*0x65*/ s8 cursor[4];
    /*0x69*/ s8 prevCursor[4];
    /*0x6D*/ u8 _6D[3];
} MatchOptions; // size: 0x70

extern MatchOptions lbl_803C5F04;

typedef struct Unk803C5EE0 {
    /*0x00*/ s16 cursor[4]; // copy of MatchOptions.cursor
    /*0x08*/ u8 _08[0xD];
    /*0x15*/ u8 _15;
    /*0x16*/ u8 _16[2];
} Unk803C5EE0; // size: 0x18

extern Unk803C5EE0 lbl_803C5EE0;

typedef struct Unk803C5EF8 {
    /*0x0*/ u8 a[4];
    /*0x4*/ u8 b[4];
    /*0x8*/ u8 _8[4];
} Unk803C5EF8; // size: 0xC

extern Unk803C5EF8 lbl_803C5EF8;

// Saved per-controller match settings (part of lbl_800E8754).
typedef struct PortSettings {
    /*0x0*/ u8 _0;
    /*0x1*/ u8 _1;
    /*0x2*/ u8 _2;
    /*0x3*/ u8 _3;
    /*0x4*/ u8 _4;
    /*0x5*/ u8 _5;
    /*0x6*/ u8 _6;
} PortSettings; // size: 0x7

// Saved match settings (lbl_800E8754).
typedef struct SavedSettings {
    /*0x00*/ u8 innings; // stored doubled
    /*0x01*/ u8 _01[3];
    /*0x04*/ u8 _04;
    /*0x05*/ u8 _05;
    /*0x06*/ u8 _06;
    /*0x07*/ PortSettings port[4];
    /*0x23*/ u8 _23[5];
} SavedSettings; // size: 0x28

extern SavedSettings lbl_800E8754;

// View of the challenge save block (starMissionCompletionTracker, size 0x4508).
typedef struct ChallengeRosterEntry {
    /*0x0*/ s16 charID;
    /*0x2*/ u8 _2;
    /*0x3*/ u8 _3;
    /*0x4*/ s8 _4;
    /*0x5*/ u8 _5;
} ChallengeRosterEntry; // size: 0x6

typedef struct ChallengeSave {
    /*0x0000*/ u8 _0000[0x16C2];
    /*0x16C2*/ s16 _16C2;
    /*0x16C4*/ u8 _16C4[0x40B8 - 0x16C4];
    /*0x40B8*/ ChallengeRosterEntry roster[9];
    /*0x40EE*/ u8 _40EE[0x42EC - 0x40EE];
    /*0x42EC*/ s32 chemistryBonus;
    /*0x42F0*/ u8 _42F0[0x441D - 0x42F0];
    /*0x441D*/ u8 _441D;
    /*0x441E*/ u8 _441E;
    /*0x441F*/ u8 _441F;
    /*0x4420*/ u8 _4420[0x4445 - 0x4420];
    /*0x4445*/ u8 _4445;
} ChallengeSave;

#define gChallengeSave (*(ChallengeSave*)starMissionCompletionTracker)

// lbl_800FB5C0: per-message parameters for fn_8004A34C.
typedef struct MsgDef {
    /*0x0*/ u16 msg;
    /*0x2*/ u8 type;
    /*0x3*/ u8 kind;
    /*0x4*/ u8 _4;
    /*0x5*/ u8 _5;
} MsgDef;

// Process-queue node running a MsgBox (see fn_8004A34C).
typedef struct MsgTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ void* prev;
    /*0x08*/ void* next;
    /*0x0C*/ struct MsgTask* parent;
    /*0x10*/ s16 result16;
    /*0x12*/ u16 priority;
    /*0x14*/ MsgBox* box;
    /*0x18*/ u8 state;
    /*0x19*/ u8 timer;
    /*0x1A*/ u8 result;
    /*0x1B*/ u8 _1B;
} MsgTask;

// Voice/text playback state owned by file_8004C5F8 (only the fields used here).
typedef struct VoiceCtl {
    /*0x00*/ u8 _00[0x1E];
    /*0x1E*/ u8 _1E;
} VoiceCtl;

extern VoiceCtl lbl_803C5F74;

void capApplicationFunction(void);
void transferStatsToInMemRoster(u8 team);
s32 fn_80042598(u8 team, s32 slot);
s32 randRange_FUN_80042bf0(s32 a, s32 b);
void sndFXRelated(u16 button);
void fn_80042D38(u16 scene);
s32 fn_80042D68(LayoutOwner* owner, s32 idx, s32 value);
s32 fn_80042DA8(LayoutOwner* owner, s32 idx, s32 value);
void pauseMenuSelection(void);
void fn_80047CE0(void);
u8 fn_800471F4(u8 mode, u8 team);
void fn_800486E0(s32 priority, s8 a, s8 b);
void fn_80048764(void);

#include "main/debug_menu.h"

s32 fn_80048820(void* menu, u16 held, u16 trig, u16 repeat, u8 holdTime);

void fn_80048BEC(void* menu, u32 a, u32 b);

void fn_80048C14(u32 value);

void fn_80048C1C(void);

void fn_80048C28(void);
void fn_80048D4C(void);
s32 fn_80048E00(s32 index, s32 value);

s32 fn_80048EA8(s32 index);

void possiblyTransferDataBetweenDifferentRels(void);
void fn_80049220(u8 team);
void fn_80049D8C(u8 dir, u8 team);
void fn_800494CC(u8 team);
void startGameRelated(void);
void fn_80049C80(void);
void fn_80049D3C(void);
void fn_8004A0FC(void);
void fn_8004617C(s32 port);
void fn_80043880(u8 dir, u8 team);
void fn_80044C98(u8 dir, u8 team);
void starMenuCursor(void);
void challengeStarMenu(void);
void fn_8004A1BC(void);
void fn_8004A2BC(void);
s32 fn_8004A328(MsgBox* box);
s32 fn_8004A34C(MsgBox* box, s8 a, u8 msgId, s8 b, u8 arg);
void fn_8004A5B8(void);
void fn_8004A7D0(void);
void fn_8004A9E0(void);

void Set_803cb848(s32 value);

s32 fn_8004ABE0(void);

s32 fn_8004ABE8(s32 clear);

s32 fn_8004AD54(u32 stadium, u8 flags);
void fn_8004AE18(s32 idx);
void fn_8004AFA8(s32 idx);

void fn_8004AC00(CharModel* model, s32 animID, u32 colorIdx, f32 frame);

u32 fn_8004ACC4(s32 clear);

u32 fn_8004ACDC(s32 clear);

void fn_8004ACF4(CharModel* model, s32 animID, u32 colorIdx, f32 frame);

void fn_8004B1B8(u32 value);

void fn_8004B1C0(s32 kind, CharModel* model, s32 animID, u32 colorIdx, f32 frame);
void fn_8004B208(CharModel* model, s32 animID, u32 colorIdx, f32 frame);

void fn_8004B270(void);

#endif
