#ifndef __GAME_rep_2998_H_
#define __GAME_rep_2998_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "main/file_80063028.h"
#include "main/file_800BD8C4.h"

// Stadium Piranha Plants. They rise out of the ground when a batted ball comes
// near, snap it out of the air, hold it in the mouth and spit it out again, and
// knock back fielders that run into them.

// lbl_3_data_18ED0: where each plant stands.
typedef struct PiranhaSpot {
    /*0x00*/ Vec pos;
    /*0x0C*/ f32 rotY;      // degrees
    /*0x10*/ u8 state;      // 2 = end of the list
    /*0x11*/ u8 _11;
    /*0x12*/ u8 group;      // fn_3_E4CB0 draws the plants by group (0-9)
    /*0x13*/ u8 _13;
    /*0x14*/ f32 spitAngle;  // degrees
    /*0x18*/ f32 spitSpread; // random +- spitSpread / 2 degrees
} PiranhaSpot; // size: 0x1C

// One 0xE8-byte entry of lbl_3_common_bss_350E4.objs (stadium object).
typedef struct PiranhaPlant {
    /*0x00*/ GameControl ctrl;
    /*0x44*/ u8 _44[0x74 - 0x44];
    /*0x74*/ ActorObject* actorObj;
    /*0x78*/ void* shadow;          // passed to fn_3_B8464
    /*0x7C*/ void (*update)(struct PiranhaPlant* p);
    /*0x80*/ void (*onHit)(s32 idx);
    /*0x84*/ void (*preDraw)(struct PiranhaPlant* p);
    /*0x88*/ u8 _88[4];
    /*0x8C*/ s32 _8C;
    /*0x90*/ u8 visible : 1;
    /*0x90*/ u8 hasShadow : 1;
    /*0x90*/ u8 bit5 : 1;
    /*0x90*/ u8 bits : 5;
    /*0x91*/ u8 _91;
    /*0x92*/ u8 _92;
    /*0x93*/ u8 _93;
    /*0x94*/ s16 _94;
    /*0x96*/ s16 _96;
    /*0x98*/ u8 _98;
    /*0x99*/ u8 _99;
    /*0x9A*/ u8 _9A;
    /*0x9B*/ u8 _9B;
    /*0x9C*/ u8 spot;               // index into lbl_3_data_18ED0
    /*0x9D*/ u8 isDummy;
    /*0x9E*/ u8 group;
    /*0x9F*/ u8 _9F;
    /*0xA0*/ Vec pos;
    /*0xAC*/ void* animBank;
    /*0xB0*/ f32 rotY;              // degrees
    /*0xB4*/ f32 scale;
    /*0xB8*/ f32 animTime;
    /*0xBC*/ f32 spitAngle;         // degrees
    /*0xC0*/ f32 spinSpeed;         // degrees per frame while holding the ball
    /*0xC4*/ u8 state;              // 0 hidden, 1 rising, 2 up, 3 holding the ball, 4 spitting, 5 sinking
    /*0xC5*/ u8 timer;
    /*0xC6*/ u8 riseFrames;
    /*0xC7*/ u8 active;
    /*0xC8*/ u8 sleepy;             // nonzero: does not bite (fn_3_E2B70)
    /*0xC9*/ u8 wasHit;
    /*0xCA*/ u8 holdingBall;
    /*0xCB*/ s8 anim;               // index into the animation bank table
    /*0xCC*/ u8 _CC[0xE8 - 0xCC];
} PiranhaPlant; // size: 0xE8

// lbl_3_common_bss_350E4: the stadium object list.
typedef struct StadiumObjList {
    /*0x00*/ PiranhaPlant* objs;
    /*0x04*/ PiranhaPlant* objsBackup;
    /*0x08*/ u8 _08[0x18 - 0x08];
    /*0x18*/ void (*draw)(void);
    /*0x1C*/ void (*update)(void);
    /*0x20*/ void* lights[4];
    /*0x30*/ s32 count;
    /*0x34*/ u32* fileIdx;          // indices into the stadium file table
    /*0x38*/ u8 _38[0x3C - 0x38];
    /*0x3C*/ u32* groupCount;       // per draw group: number of objects
    /*0x40*/ u16* groupStart;       // per draw group: first entry in groupObjs
    /*0x44*/ s32* groupObjs;
    /*0x48*/ Vec* groupBounds;      // per draw group: min and max corner
    /*0x4C*/ u8 _4C[0x64 - 0x4C];
    /*0x64*/ s16 numGroups;
    /*0x66*/ u8 _66[0x6D - 0x66];
    /*0x6D*/ u8 numActorObjs;
} StadiumObjList;

// g_Fielders entry (0x268 bytes), only the fields used here.
typedef struct PiranhaFielder {
    /*0x000*/ Vec pos;
    /*0x00C*/ u8 _00C[0x210 - 0x00C];
    /*0x210*/ u8 knockback; // nonzero while knocked back (fn_3_253A4)
    /*0x211*/ u8 _211[0x268 - 0x211];
} PiranhaFielder; // size: 0x268

void fn_3_E1DB8(void);
void fn_3_E1FA8(PiranhaPlant* p);
void fn_3_E2034(PiranhaPlant* p);
void fn_3_E2118(s32 idx);
void fn_3_E22A4(PiranhaPlant* p);
void fn_3_E2324(PiranhaPlant* p);
void fn_3_E25D0(PiranhaPlant* p, u32 anim);
void fn_3_E266C(PiranhaPlant* p);
u8 fn_3_E28DC(PiranhaPlant* p);
u8 fn_3_E29B4(PiranhaPlant* p);
u8 fn_3_E2B70(PiranhaPlant* p);
void fn_3_E2E78(PiranhaPlant* p);
void fn_3_E2F4C(PiranhaPlant* p);
void fn_3_E3044(PiranhaPlant* p);
u8 fn_3_E3284(PiranhaPlant* p);
void fn_3_E3668(PiranhaPlant* p);
void fn_3_E3764(PiranhaPlant* p);
void fn_3_E3914(PiranhaPlant* p);
void fn_3_E3B88(PiranhaPlant* p);
void fn_3_E4554(PiranhaPlant* p);
void fn_3_E45A8(PiranhaPlant* p);
void fn_3_E45F0(PiranhaPlant* p);
void fn_3_E4658(PiranhaPlant* p);
void fn_3_E4760(PiranhaPlant* p);
void fn_3_E48D0(PiranhaPlant* p);
void fn_3_E4A38(Mtx m, u8* b);
void* fn_3_E4BE8(s32 idx, Mtx m);
void fn_3_E4CB0(s32* group, s32* obj);
void fn_3_E4EF4(void);
void fn_3_E4FC4(void** files);

#endif // !__GAME_rep_2998_H_
