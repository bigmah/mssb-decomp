#ifndef __GAME_sta_c0_H_
#define __GAME_sta_c0_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "main/file_80063028.h" // GameControl
#include "main/file_800BD8C4.h" // ActorObject
#include "main/file_80024D2C.h" // ShapeAnimPlayer

// Stadium 0 (Mario Stadium) objects: the stadium model, the animated parts, the
// light panels that turn towards the camera and the indirect-texture water.

// One 0xE8-byte entry of lbl_3_common_bss_350E4.objs, as set up by fn_3_C9DB4
// (same layout as PiranhaPlant in game/rep_2998.h up to 0x98).
typedef struct StaC0Obj {
    /*0x00*/ GameControl ctrl;
    /*0x44*/ u8 _44[0x74 - 0x44];
    /*0x74*/ ActorObject* actorObj;
    /*0x78*/ void* shadow;
    /*0x7C*/ void (*update)(struct StaC0Obj* o);
    /*0x80*/ void (*onHit)(s32 idx);
    /*0x84*/ void (*preDraw)(struct StaC0Obj* o);
    /*0x88*/ u8 _88[4];
    /*0x8C*/ ShapeAnimPlayer* shapeAnim;
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
    /*0x99*/ u8 _99[0xA1 - 0x99];
    /*0xA1*/ u8 kind; // set by fn_3_C9DB4: 1, 0 (water), 2 (placed parts), 3 (minigames extra)
    /*0xA2*/ u8 _A2;
    /*0xA3*/ u8 _A3;
    /*0xA4*/ s32 phase; // placed parts: index * 100
    /*0xA8*/ u8 _A8[0xE8 - 0xA8];
} StaC0Obj; // size: 0xE8

// lbl_3_data_17B98: where the placed stadium parts stand (up to 10, kind 4 ends the list).
typedef struct StaC0Part {
    /*0x00*/ Vec pos;
    /*0x0C*/ Vec scale;
    /*0x18*/ f32 rotY;
    /*0x1C*/ u8 kind; // 4: end of the list
    /*0x1D*/ u8 _1D[3];
} StaC0Part; // size: 0x20

// A g_UNK_StadiumDetails._00 entry (0x20 bytes); only the field set here.
typedef struct StaC0Panel {
    /*0x00*/ u8 _00[0x1C];
    /*0x1C*/ s16 frame;
    /*0x1E*/ u8 _1E[2];
} StaC0Panel;

// Animated panel sequence (two of them follow the objects in objsBackup).
typedef struct StaC0Seq {
    /*0x00*/ StaC0Panel* panelA;
    /*0x04*/ StaC0Panel* panelB;
    /*0x08*/ void* _08;
    /*0x0C*/ void* _0C;
    /*0x10*/ u8* steps; // count x {u8, u8, u8}
    /*0x14*/ u16 count;
    /*0x16*/ u16 range2; // random range for the third byte
    /*0x18*/ u16 _18;
    /*0x1A*/ u8 _1A[2];
} StaC0Seq; // size: 0x1C

// Light panels that face the camera (fn_3_C9878).
typedef struct StaC0Lights {
    /*0x00*/ u8 frames[2][2][6]; // [camera][panel pair]: {panelA, frame off, frame on, panelB, off, on}
    /*0x18*/ StaC0Panel* panels;
    /*0x1C*/ f32 cosLimit;
    /*0x20*/ u8 count;
    /*0x21*/ u8 _21[3];
} StaC0Lights; // size: 0x24

// lbl_3_common_bss_350E4 (StadiumObjList in game/rep_2998.h), as used here.
typedef struct StaC0ObjList {
    /*0x00*/ StaC0Obj* objs;
    /*0x04*/ StaC0Obj* objsBackup;
    /*0x08*/ StaC0Seq* seqA;
    /*0x0C*/ StaC0Seq* seqB;
    /*0x10*/ StaC0Lights* lights;
    /*0x14*/ u8 _14[0x18 - 0x14];
    /*0x18*/ void (*draw)(void);
    /*0x1C*/ void (*update)(void);
    /*0x20*/ void* lightObjs[4];
    /*0x30*/ s32 count;
    /*0x34*/ u32* fileIdx; // indices into the stadium file table
    /*0x38*/ u8 _38[0x48 - 0x38];
    /*0x48*/ s32 _48;
    /*0x4C*/ u8 _4C[0x6D - 0x4C];
    /*0x6D*/ u8 numActorObjs;
} StaC0ObjList;

void fn_3_C9744(void);
void fn_3_C9878(void);
void fn_3_C99F8(StaC0Obj* o);
void fn_3_C9A60(StaC0Obj* o);
void fn_3_C9AC8(StaC0Obj* o);
void fn_3_C9B5C(StaC0Obj* o);
void fn_3_C9C94(void);
void fn_3_C9DB4(void** files);

#endif // !__GAME_sta_c0_H_
