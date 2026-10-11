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
    /*0x01*/ u8 _01[7];
    /*0x08*/ u8 track; // from MenuDef.track of the current menu
    /*0x09*/ u8 prevTrack;
    /*0x0A*/ u8 _0A[0x1E];
} MenuState; // size: 0x28

// lbl_800FEF70: per-menu definitions.
typedef struct MenuDef {
    /*0x00*/ u8 _00[8];
    /*0x08*/ u16 track;
    /*0x0A*/ u8 _0A[6];
} MenuDef; // size: 0x10

// lbl_803297E0: menu work area (size 0x24C98), only the fields used here.
typedef struct MenuWork {
    /*0x0000*/ u8 _0000[0xCF3B];
    /*0xCF3B*/ u8 team;
    /*0xCF3C*/ u8 _CF3C[0x34];
    /*0xCF70*/ u8 _CF70;
    /*0xCF71*/ u8 _CF71[0x31];
    /*0xCFA2*/ u8 teamKind[0x36];
} MenuWork;

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
