#ifndef __MAIN_FILE_800527C4_H__
#define __MAIN_FILE_800527C4_H__

#include "mssbTypes.h"

struct CharActor;

struct SceneTask;
struct GameActor;
struct GameBone;
struct SoundLoadTask;
#include "game/UnknownHomes_Game.h"
#include "main/file_8004B284.h"
#include "Dolphin/mtx.h"




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
void fn_80054910(struct SceneTask* task, s32 port);
void fn_80055798(struct SceneTask* task, s32 port);
void fn_8005C5C4(struct SceneTask* task, s32 port);
void fn_80059458(struct SceneTask* task, u8 port, u32 mask);
void fn_8005F734(struct SceneTask* task, s32 port);
void fn_80058394(struct SceneTask* task);
void fn_80058B20(struct SceneTask* task, u8 port);
void fn_8005C2B0(struct SceneTask* task);
void fn_8005AF68(struct SceneTask* task);
void fn_8005BF40(struct SceneTask* task);
void fn_8005BB5C(struct SceneTask* task);
void fn_8005B760(struct SceneTask* task, s32 port);
void fn_80055374(struct SceneTask* task, s32 port);
void someChallengeStarFunction2(struct SceneTask* task);
void fn_800596D4(struct SceneTask* task);
void drawStarProgressionMenu(struct SceneTask* task);
void fn_8005B298(struct SceneTask* task);
void fn_80058644(struct SceneTask* task);
void fn_8005FCA0(struct SceneTask* task, s32 port);
void someChallengeStarFunction(struct SceneTask* task);
void fn_80057CAC(void);
void fn_8005CCE4(struct SceneTask* task, s32 port);
void fn_8005DE14(struct SceneTask* task, s32 port);
void fn_8005E9D8(struct SceneTask* task, s32 port);
void fn_8005EC88(struct SceneTask* task, s32 port);
void fn_8005C830(struct SceneTask* task, s32 port, s32 slot);
void fn_8005F9D0(struct SceneTask* task, s32 port);
void fn_80053810(void);
void fn_800531D0(struct SceneTask* task);
void fn_800559EC(void);
void fn_80060184(void);
void starMissionRelated1(struct SceneTask* task);
void fn_8005A350(struct SceneTask* task, s32 pad);
void fn_80054B00(struct SceneTask* task, s32 port);
void fn_800542C4(u8 cur, u8 target, struct SceneTask* task);
void fn_80058E0C(struct SceneTask* task, u8 port);
void fn_8005F068(struct SceneTask* task, s32 port);
void fn_80056120(void);
void fn_800569C8(void);
void challengeCheckStarsMenuLoading(void);
void starMenu(void);
void fn_80058050(void);
void fn_80061B9C(void);
void SetMenuNumber(void);

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

// lbl_803297E0 (MenuWork), lbl_8034E9A0, lbl_8034E978, lbl_80354720, lbl_803C5EE0,
// lbl_803C5F04 and lbl_803C66B0 are declared in main/file_8004207C.h.



// lbl_8010A768: challenge mission definitions [mission set][mission].
typedef struct ChallengeMission {
    /*0x0*/ s16 msg;
    /*0x2*/ s16 type;
    /*0x4*/ s16 starsNeeded;
    /*0x6*/ s16 _6;
    /*0x8*/ s16 _8;
} ChallengeMission; // size: 0xA




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
void fn_800625A4(s32 index, s32 step);
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
void fn_80062C60(struct CharActor* model, s32 animID, u32 colorIdx, f32 frame);
void fn_80062D94(struct CharActor* model);
void fn_80062E6C(struct CharActor* model, s32 animID, u32 colorIdx, f32 frame);
s32 fn_80062ED4(struct CharActor* player, struct ActorObject* obj);
s32 fn_80062F38(struct GameBone* bone, struct GameBone* target, Mtx m, f32 t);
s32 fn_80063010(struct CharActor* player, struct ActorObject* obj);

// Camera setup (fn_800528AC is defined in this unit).
#include "static/Camera.h"
void fn_800528AC(fn_800528AC_parameter value);
// Not yet decompiled (asm in this unit's range).
u32 fn_80062890(s32 index);
void fn_80062A94(void);

#endif
