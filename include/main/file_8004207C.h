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

// Controller input as latched by the menus (one per port).
typedef struct PortInput {
    /*0x0*/ u16 held;
    /*0x2*/ u16 pressed;
    /*0x4*/ u16 repeat;
} PortInput;

// Pause/star menu work area inside lbl_803297E0 (only the fields used here).
typedef struct MenuWork {
    /*0x0000*/ PortInput input[4]; // used instead of lbl_8034E9A0.input while paused in game
    /*0x0018*/ u8 swap[2][2];        // per team: last swapped slots (from, to)
    /*0x001C*/ u8 _001C[0xCF38 - 0x1C];
    /*0xCF38*/ u16 _CF38;
    /*0xCF3A*/ s8 _CF3A;
    /*0xCF3B*/ u8 _CF3B;
    /*0xCF3C*/ u8 _CF3C[2];
    /*0xCF3E*/ u8 _CF3E[2];
    /*0xCF40*/ u8 _CF40;
    /*0xCF41*/ u8 _CF41;
    /*0xCF42*/ u8 _CF42;
    /*0xCF43*/ u8 _CF43;
    /*0xCF44*/ u8 _CF44;
    /*0xCF45*/ u8 _CF45;
    /*0xCF46*/ s8 slot[2]; // selected batting order slot (1-based) per team
    /*0xCF48*/ s8 _CF48[2];
    /*0xCF4A*/ s8 _CF4A[2];
    /*0xCF4C*/ u8 _CF4C[2];
    /*0xCF4E*/ u8 _CF4E[2];
    /*0xCF50*/ u8 _CF50[2];
    /*0xCF52*/ u8 _CF52[2];
    /*0xCF54*/ u8 _CF54[2];
    /*0xCF56*/ u8 _CF56[2];
    /*0xCF58*/ u8 _CF58[2];
    /*0xCF5A*/ u8 _CF5A;
    /*0xCF5B*/ u8 ready[2]; // per port, two-player tutorial sync
    /*0xCF5D*/ u8 _CF5D;
    /*0xCF5E*/ u8 _CF5E;
    /*0xCF5F*/ u8 _CF5F;
    /*0xCF60*/ u8 _CF60;
    /*0xCF61*/ u8 _CF61[2];
    /*0xCF63*/ u8 _CF63[2];
    /*0xCF65*/ u8 _CF65[2];
    /*0xCF67*/ u8 _CF67[2];
    /*0xCF69*/ u8 _CF69;
    /*0xCF6A*/ u8 _CF6A;
    /*0xCF6B*/ u8 _CF6B;
    /*0xCF6C*/ u8 _CF6C;
    /*0xCF6D*/ u8 _CF6D;
    /*0xCF6E*/ u8 _CF6E;
    /*0xCF6F*/ u8 _CF6F;
    /*0xCF70*/ u8 _CF70;
    /*0xCF71*/ u8 _CF71;
    /*0xCF72*/ u8 _CF72;
    /*0xCF73*/ u8 pauseShown;
    /*0xCF74*/ u8 _CF74;
    /*0xCF75*/ s8 starCursor;
    /*0xCF76*/ s8 prevStarCursor;
    /*0xCF77*/ u8 _CF77;
    /*0xCF78*/ u16 _CF78;
    /*0xCF7A*/ u8 nameText; // text entries of the star/mission panel
    /*0xCF7B*/ u8 descText;
    /*0xCF7C*/ u8 missionText;
    /*0xCF7D*/ u8 _CF7D;
    /*0xCF7E*/ u8 scoutSub;
    /*0xCF7F*/ u8 scoutDone;
    /*0xCF80*/ s8 scoutTotal[9]; // scout flags per player
    /*0xCF89*/ s8 scoutGot[9];
    /*0xCF92*/ u8 _CF92;
    /*0xCF93*/ u8 missionShown;
    /*0xCF94*/ u8 menuDone;
    /*0xCF95*/ s8 prevSlotCursor;
    /*0xCF96*/ s8 slotCursor;
    /*0xCF97*/ s8 prevStarCursor2;
    /*0xCF98*/ s8 starCursor2;
    /*0xCF99*/ u8 _CF99;
    /*0xCF9A*/ u8 _CF9A;
    /*0xCF9B*/ u8 _CF9B;
    /*0xCF9C*/ s16 _CF9C;
    /*0xCF9E*/ u8 _CF9E[2];
    /*0xCFA0*/ u8 _CFA0;
    /*0xCFA1*/ u8 _CFA1;
    /*0xCFA2*/ u8 _CFA2[2];
} MenuWork;


extern MenuWork lbl_803297E0;


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

// lbl_8034E978: current menu screen.
typedef struct MenuState {
    /*0x00*/ u8 menu;
    /*0x01*/ u8 prevMenu;
    /*0x02*/ u8 prev03;
    /*0x03*/ u8 _03;
    /*0x04*/ u8 _04;
    /*0x05*/ u8 _05;
    /*0x06*/ u8 _06;
    /*0x07*/ u8 _07;
    /*0x08*/ u8 track; // from MenuDef.track of the current menu
    /*0x09*/ u8 prevTrack;
    /*0x0A*/ s8 text[10]; // text entries for the menu description
    /*0x14*/ u8 textCount;
    /*0x15*/ u8 textCur;
    /*0x16*/ u8 textDone[10]; // 0xFF: free
    /*0x20*/ u8 descState;
    /*0x21*/ u8 _21[2];
    /*0x23*/ u8 _23;
    /*0x24*/ u8 _24;
    /*0x25*/ u8 _25;
    /*0x26*/ u8 _26;
    /*0x27*/ u8 _27;
} MenuState; // size: 0x28

extern MenuState lbl_8034E978;

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

// Message box with optional voice (lbl_803C50E8 is the shared one).
typedef struct MsgBox {
    /*0x00*/ u8 _00[3];
    /*0x03*/ u8 port;
    /*0x04*/ u8 _04;
    /*0x05*/ u8 _05[0x3E - 0x05];
    /*0x3E*/ u8 state;
    /*0x3F*/ u8 msgId;
    /*0x40*/ s8 _40;
    /*0x41*/ s8 _41;
    /*0x42*/ u8 _42[2];
    /*0x44*/ u8 done;
    /*0x45*/ u8 result;
    /*0x46*/ u8 cancel;
    /*0x47*/ u8 _47;
    /*0x48*/ u8 loopStop;
    /*0x49*/ u8 looping;
    /*0x4A*/ u16 loopMsg;
    /*0x4C*/ u8 kind;
    /*0x4D*/ u8 arg;
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 _4F;
    /*0x50*/ u16 msg;
    /*0x52*/ u8 _52;
    /*0x53*/ u8 _53[0x5C - 0x53];
} MsgBox; // size: 0x5C

extern MsgBox lbl_803C50E8;

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
