#ifndef __GAME_sta_c4_H_
#define __GAME_sta_c4_H_

#include "mssbTypes.h"
#include "main/file_800263FC.h"
#include "main/file_80063028.h"
#include "main/file_800BD8C4.h"
#include "game/rep_D0.h" // CollisionStruct
#include "game/sta_ext_list.h" // StaExtList

// One 0xE8-byte entry of lbl_3_common_bss_350E4.objs (stadium object of this stadium).
typedef struct StaObj {
    /*0x00*/ GameControl ctrl;
    /*0x44*/ u8 _44[0x74 - 0x44];
    /*0x74*/ ActorObject* actorObj;
    /*0x78*/ void* shadow; // passed to fn_3_B8464
    /*0x7C*/ void (*update)(struct StaObj* o);
    /*0x80*/ void (*onHit)(s32 idx, s32 b, CollisionStruct* c); // c: where the ball hit
    /*0x84*/ void (*preDraw)(struct StaObj* o);
    /*0x88*/ u8 _88[4];
    /*0x8C*/ void* anim; // ShapeAnimPlayer* (lbl_3_bss_B578) for the shape-animated object

#ifdef TARGET_PC // bitfields in MWCC (big-endian) bit order
    /*0x90*/ u8 bits : 5;
    /*0x90*/ u8 bit5 : 1;
    /*0x90*/ u8 hasShadow : 1;
    /*0x90*/ u8 visible : 1;
#else
    /*0x90*/ u8 visible : 1;
    /*0x90*/ u8 hasShadow : 1;
    /*0x90*/ u8 bit5 : 1;
    /*0x90*/ u8 bits : 5;
#endif
    /*0x91*/ u8 _91;
    /*0x92*/ u8 _92;
    /*0x93*/ u8 _93;
    /*0x94*/ s16 _94;
    /*0x96*/ s16 _96;
    /*0x98*/ u8 _98;
    /*0x99*/ u8 _99[0x9C - 0x99];
    /*0x9C*/ f32 animTime;
    /*0xA0*/ u8 id;
    /*0xA1*/ u8 prevState;
    /*0xA2*/ u8 state;
    /*0xA3*/ u8 frame;
    /*0xA4*/ u8 _A4[0xE8 - 0xA4];
} StaObj; // size: 0xE8

// Queue task (lbl_803CC1B8) that sets obj->bit5 after `timer` frames (fn_3_F92FC).
typedef struct StaTimerTask {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ void* prev;
    /* 0x08 */ void* next;
    /* 0x0C */ void* parent;
    /* 0x10 */ s16 timer;
    /* 0x12 */ u16 priority;
    /* 0x14 */ StaObj* obj;
} StaTimerTask;

// Draw node (lbl_3_data_1BE94[2], queued with fn_800A7D4C) whose callback is fn_3_FB3D8.
typedef struct StaHazeNode {
    /* 0x00 */ u32 link;
    /* 0x04 */ void (*draw)(struct StaHazeNode* node);
    /* 0x08 */ u8 _08[0x38 - 0x08];
    /* 0x38 */ Mtx view; // camera view matrix for this frame
    /* 0x68 */ u8 _68[4];
} StaHazeNode; // size: 0x6C

// StaExtList (lbl_3_common_bss_350E4 + 0x08 / + 0x0C): game/sta_ext_list.h.

// lbl_3_common_bss_350E4 + 0x10, set up by fn_3_FA58C.
typedef struct StaExt10 {
    /*0x00*/ u8 b[0x18];
    /*0x18*/ void* file;    // stadium file
    /*0x1C*/ f32 cosAngle;
    /*0x20*/ u8 n20;
} StaExt10; // size: 0x24

// lbl_3_data_1BA98: where each object stands.
typedef struct StaObjDef {
    /*0x00*/ Vec pos;
    /*0x0C*/ f32 rotY;
    /*0x10*/ u8 kind;    // initial StaObj.prevState; 4: copies, 5: free slot
    /*0x11*/ u8 visible;
    /*0x12*/ u8 group;
    /*0x13*/ u8 state;   // initial StaObj.state; 8: random 0-2
} StaObjDef; // size: 0x14

// Queue task (lbl_803CC1B8) that moves a knocked object along with the ball (fn_3_F934C).
typedef struct StaBounceTask {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ void* prev;
    /* 0x08 */ void* next;
    /* 0x0C */ void* parent;
    /* 0x10 */ s16 result;
    /* 0x12 */ u16 priority;
    /* 0x14 */ Vec normal;
    /* 0x20 */ Vec vel;
    /* 0x2C */ s32 idx;
    /* 0x30 */ u8 bounced;
} StaBounceTask;

void fn_3_F8524(Particle* p);
s32 fn_3_F85B0(Emitter* e);
void fn_3_F8878(Emitter* e);
void fn_3_F8ABC(void);
void fn_3_F8B04(void);
void fn_3_F8B30(void);
void fn_3_F8B34(StaObj* o);
void fn_3_F8BA8(StaObj* o);
void fn_3_F8D00(void);
void fn_3_F8E20(void);
void fn_3_F9088(Vec* pos, s32 idx);
void fn_3_F9164(StaObj* o);
void fn_3_F92FC(void);
void fn_3_F934C(void);
void fn_3_F963C(s32 idx, CollisionStruct* v);
void fn_3_F976C(s32 idx, s32 b, CollisionStruct* c);
void fn_3_F99F0(s32 idx);
void fn_3_F9B9C(s32 idx, s32 b, CollisionStruct* c);
void fn_3_F9D94(StaObj* o);
void fn_3_F9E78(s32 idx, s32 b, CollisionStruct* c);
void fn_3_FA3C0(void);
void fn_3_FA58C(void** files);
void fn_3_FB3D8(StaHazeNode* node);
void fn_3_FBBA0(TexImage* t);
void fn_3_F8444(void);
void fn_3_F8454(void);

#endif // !__GAME_sta_c4_H_
