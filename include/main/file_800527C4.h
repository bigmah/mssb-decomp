#ifndef __MAIN_FILE_800527C4_H__
#define __MAIN_FILE_800527C4_H__

#include "mssbTypes.h"
#include "main/file_80069BDC.h"
#include "Dolphin/mtx.h"
#include "main/file_80063028.h"

// Character actor as seen by the sound helpers here (only the fields used).
typedef struct CharSoundObj {
    /*0x000*/ u8 _000[0x252];
    /*0x252*/ s8 _252;
    /*0x253*/ u8 _253;
    /*0x254*/ s8 charIndex;
} CharSoundObj;

// Per-character model object: maps game joint ids to model joints.
typedef struct CharJointMapObj {
    /*0x000*/ u8 _000[0x162];
    /*0x162*/ u16 jointMap[0x79];
} CharJointMapObj;

// lbl_8036E548 (character actors and models), only the fields used here.
typedef struct CharModelTable {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ CharJointMapObj* chars[13];
} CharModelTable;

// lbl_803C66B0: tutorial step state per player.
typedef struct TutorialSteps {
    /*0x00*/ u8 steps[14][6];
    /*0x54*/ u8 _54;
    /*0x55*/ u8 active[8];
    /*0x5D*/ u8 step[7];
} TutorialSteps; // size: 0x64

// lbl_803C6714: two looping sound effects driven by queue tasks.
typedef struct LoopSfxState {
    /*0x00*/ u32 voiceA;
    /*0x04*/ u8 activeA;
    /*0x05*/ u8 stopA;
    /*0x06*/ u8 fadeLen;   // frames to fade out over (0: no fade)
    /*0x07*/ u8 fadeCount;
    /*0x08*/ u32 voiceB;
    /*0x0C*/ u8 activeB;
    /*0x0D*/ u8 stopB;
    /*0x0E*/ u8 _0E[2];
} LoopSfxState; // size: 0x10

BOOL fn_800527C4(Vec* pos);
void fn_80052968(void);
void fn_80052D70(void);
void possiblyTransitionBlackScreen(void);
void fn_80053FE8(void);
void fn_80054910(SceneTask* task, s32 port);
void fn_80055798(SceneTask* task, s32 port);
void fn_8005C5C4(SceneTask* task, s32 port);
void fn_80059458(SceneTask* task, u8 port, u32 mask);
void fn_8005F734(SceneTask* task, s32 port);
void fn_80058394(SceneTask* task);
void fn_80058B20(SceneTask* task, u8 port);
void fn_8005C2B0(SceneTask* task);
void fn_8005AF68(SceneTask* task);
void fn_8005BF40(SceneTask* task);
void fn_8005BB5C(SceneTask* task);
void fn_8005B760(SceneTask* task, s32 port);
void fn_80055374(SceneTask* task, s32 port);
void someChallengeStarFunction2(SceneTask* task);
void fn_800596D4(SceneTask* task);
void drawStarProgressionMenu(SceneTask* task);
void fn_8005B298(SceneTask* task);
void fn_80058644(SceneTask* task);
void fn_8005FCA0(SceneTask* task, s32 port);
void someChallengeStarFunction(SceneTask* task);
void fn_80057CAC(void);
void fn_8005CCE4(SceneTask* task, s32 port);
void fn_8005DE14(SceneTask* task, s32 port);
void fn_8005E9D8(SceneTask* task, s32 port);
void fn_8005EC88(SceneTask* task, s32 port);
void fn_8005C830(SceneTask* task, s32 port, s32 slot);
void fn_8005F9D0(SceneTask* task, s32 port);
void fn_80053810(void);
void fn_800531D0(SceneTask* task);
void fn_80056120(void);
void fn_800569C8(void);
void challengeCheckStarsMenuLoading(void);
void starMenu(void);
void fn_80058050(void);
void fn_80061B9C(void);
void SetMenuNumber(void);
// lbl_8034E978: current menu screen.
typedef struct MenuState {
    /*0x00*/ u8 menu;
    /*0x01*/ u8 _01[2];
    /*0x03*/ u8 _03;
    /*0x04*/ u8 _04;
    /*0x05*/ u8 _05;
    /*0x06*/ u8 _06[2];
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

// lbl_800FEF70: per-menu definitions.
typedef struct MenuDef {
    /*0x00*/ u16 _00;
    /*0x02*/ u16 _02;
    /*0x04*/ u16 _04;
    /*0x06*/ u16 _06;
    /*0x08*/ u16 track;
    /*0x0A*/ u16 textStart; // 0xFFFF: no description text
    /*0x0C*/ u16 textEnd;
    /*0x0E*/ u16 _0E;
} MenuDef; // size: 0x10

// lbl_803297E0: menu work area (size 0x24C98), only the fields used here.
typedef struct MenuWork {
    /*0x0000*/ u8 _0000[0xCF3B];
    /*0xCF3B*/ u8 team;
    /*0xCF3C*/ u8 _CF3C[2];
    /*0xCF3E*/ u8 _CF3E[2]; // roster slot per port
    /*0xCF40*/ u8 _CF40[6];
    /*0xCF46*/ s8 selected[2]; // 1-based roster index per team
    /*0xCF48*/ s8 selected2[2];
    /*0xCF4A*/ u8 _CF4A[8];
    /*0xCF52*/ u8 _CF52[2];
    /*0xCF54*/ u8 _CF54[7];
    /*0xCF5B*/ u8 ready[2]; // per port, two-player tutorial sync
    /*0xCF5D*/ u8 _CF5D[6];
    /*0xCF63*/ u8 starShown[2];
    /*0xCF65*/ u8 _CF65[0xB];
    /*0xCF70*/ u8 _CF70;
    /*0xCF71*/ u8 _CF71[2];
    /*0xCF73*/ u8 pauseShown;
    /*0xCF74*/ u8 _CF74;
    /*0xCF75*/ s8 pauseMission;
    /*0xCF76*/ s8 pausePrevMission;
    /*0xCF77*/ u8 _CF77[3];
    /*0xCF7A*/ u8 nameText;
    /*0xCF7B*/ u8 descText;
    /*0xCF7C*/ u8 missionText; // text entry index
    /*0xCF7D*/ u8 scoutState;
    /*0xCF7E*/ u8 scoutSub;
    /*0xCF7F*/ u8 scoutDone;
    /*0xCF80*/ s8 scoutTotal[9];
    /*0xCF89*/ s8 scoutGot[9];
    /*0xCF92*/ u8 _CF92;
    /*0xCF93*/ u8 missionShown;
    /*0xCF94*/ u8 menuDone;
    /*0xCF95*/ s8 prevCharSel;
    /*0xCF96*/ s8 charSel;
    /*0xCF97*/ s8 prevMission;
    /*0xCF98*/ s8 mission;
    /*0xCF99*/ u8 _CF99;
    /*0xCF9A*/ u8 missionCount;
    /*0xCF9B*/ u8 _CF9B;
    /*0xCF9C*/ s16 challengeTeam;
    /*0xCF9E*/ u8 _CF9E[4];
    /*0xCFA2*/ u8 teamKind[0x36];
} MenuWork;

// lbl_8034E9A0 (size 0x4C28): base character stats by CharID, plus other state.
typedef struct RosterData {
    /*0x0000*/ CharacterStats chars[6][9];
    /*0x21C0*/ u8 _21C0[0x46F8 - 0x21C0];
    /*0x46F8*/ s8 _46F8[2];
    /*0x46FA*/ u8 _46FA[0x470D - 0x46FA];
    /*0x470D*/ u8 _470D[2];
    /*0x470F*/ u8 _470F[0x47F9 - 0x470F];
    /*0x47F9*/ s8 chemPartner[2][9][9]; // CharIDs linked to each roster slot
    /*0x489B*/ u8 _489B[2][9];
    /*0x48AD*/ u8 _48AD;
    /*0x48AE*/ u8 _48AE;
    /*0x48AF*/ u8 _48AF[4];
    /*0x48B3*/ u8 _48B3;
    /*0x48B4*/ u8 _48B4[0x4C28 - 0x48B4];
} RosterData; // size: 0x4C28

// lbl_8010A768: challenge mission definitions [mission set][mission].
typedef struct ChallengeMission {
    /*0x0*/ s16 msg;
    /*0x2*/ s16 type;
    /*0x4*/ s16 starsNeeded;
    /*0x6*/ s16 _6;
    /*0x8*/ s16 _8;
} ChallengeMission; // size: 0xA

// lbl_80354720: per-port roster slots.
typedef struct RosterSlot {
    /*0x0*/ u8 _0[2];
    /*0x2*/ s8 pos;
    /*0x3*/ u8 _3;
} RosterSlot; // size: 0x4

// lbl_803C5F04: input state for the tutorial step checks (size 0x70).
typedef struct TutorialInput {
    /*0x00*/ u8 _00[0x36];
    /*0x36*/ u8 mode;
    /*0x37*/ u8 _37[4];
    /*0x3B*/ s8 tblA[5];
    /*0x40*/ s8 tblB[5];
    /*0x45*/ s8 tblC[4][4];
    /*0x55*/ s8 tblD[4][4];
    /*0x65*/ s8 cur[4];
    /*0x69*/ s8 target[4];
    /*0x6D*/ u8 _6D[3];
} TutorialInput; // size: 0x70

// lbl_803C60BC (size 0x2E0, directly before the cameras), only the fields used here.
typedef struct Unk803C60BC {
    /*0x00*/ Vec dir;
    /*0x0C*/ Vec dir2;
    /*0x18*/ u8 _18[0xC];
    /*0x24*/ f32 angle;
    /*0x28*/ f32 _28;
    /*0x2C*/ f32 _2C;
    /*0x30*/ u8 _30[0xC];
    /*0x3C*/ u8 _3C;
    /*0x3D*/ u8 _3D;
    /*0x3E*/ u8 _3E[0x2E0 - 0x3E];
} Unk803C60BC; // size: 0x2E0

void fn_800528B4(void);
void fn_800528C0(s16* screenX, s16* screenY, f32 x, f32 y, f32 z);

BOOL fn_80062578(void);
void fn_800625A4(s32 index, s8 step);
void fn_800626EC(s32 index);
void fn_80062674(s32 index);
void fn_80062744(void);
void fn_80062764(struct SoundLoadTask* task);
BOOL fn_80062794(s32 voice);
s32 fn_800627C4(void);
s32 fn_800627F8(void);
void fn_8006282C(void);
s32 fn_8006285C(void);
u32 fn_800628D4(s32 kind);
void fn_80062948(void);
void fn_8006295C(void);
void initializeUnknown(void);
void fn_80062A74(void);
void fn_80062BE4(Vec* pos);
void fn_80062C24(Vec* pos);
void fn_80062C60(CharSoundObj* obj, s32 a, s32 b, f32 frame);
void fn_80062D94(CharSoundObj* obj);
void fn_80062E6C(CharSoundObj* obj, s32 kind, s32 c);
s32 fn_80062ED4(void* player, GameActor** actor);
s32 fn_80062F38(GameBone* bone, GameBone* target, Mtx m, f32 t);
s32 fn_80063010(void* player, GameActor** actor);

#endif
