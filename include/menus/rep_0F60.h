#ifndef __REP_0F60_MENUS_H__
#define __REP_0F60_MENUS_H__

#include "mssbTypes.h"
#include "main/file_80024D2C.h"
#include "Dolphin/mtx.h"

struct GameActor;

// Views of main.dol character types (main/file_80011640.h: CharModel, CharSlot,
// CharActor); that header can't be included next to this unit's declarations.
typedef struct MenuJoint {
    /*0x000*/ u16 id;
    /*0x002*/ u8 _002[0x136 - 0x2];
    /*0x136*/ u8 _136;
} MenuJoint;

// A GameActor (main/file_80063028.h), only the fields used here.
typedef struct MenuModel {
    /*0x00*/ u8 _00[0x6];
    /*0x06*/ u16 jointCount;
    /*0x08*/ u8 _08[0x18 - 0x8];
    /*0x18*/ MenuJoint** joints;
    /*0x1C*/ u8 _1C[0x8C - 0x1C];
    /*0x8C*/ f32 blend;
    /*0x90*/ u8 _90[0x99 - 0x90];
    /*0x99*/ u8 _99;
} MenuModel;

// Animation bank of a character model (ANIMBank, C3/anim.h; only the count is used here).
typedef struct MenuAnimBank {
    /*0x00*/ u8 _00[0xA];
    /*0x0A*/ u16 count;
} MenuAnimBank;

// A model file plus its shape (face) animation player.
typedef struct MenuFacePart {
    /*0x00*/ void** files;
    /*0x04*/ ShapeAnimPlayer anim;
    /*0x60*/ u8 _60[0x64 - 0x60];
} MenuFacePart; // size: 0x64

// Face/shape animation block hanging off a character (MenuActor.face/faceSub);
// lbl_2_bss_340140 + 0x140 holds one per actor.
typedef struct MenuFaceAnim {
    /*0x00*/ MenuFacePart main;
    /*0x64*/ MenuFacePart sub;
    /*0xC8*/ u8 _C8[0xCC - 0xC8];
    /*0xCC*/ u8 hasSub;
    /*0xCD*/ u8 _CD[0xD4 - 0xCD];
} MenuFaceAnim; // size: 0xD4

// One 0x90-byte actor object slot (cf. ActorObject in main/file_800BD8C4.h,
// CharSlot in main/file_80011640.h); fn_800111D8 returns a pointer to one.
typedef struct MenuAnimObject {
    /*0x00*/ struct GameActor* actor;
    /*0x04*/ MenuAnimBank* animBank;
    /*0x08*/ void (*callback)(u8* object);
    /*0x0C*/ u8 _0C[0xE - 0xC];
    /*0x0E*/ s16 seqNum;
    /*0x10*/ u8 ctrl[0x44]; // Control
    /*0x54*/ f32 _54;
    /*0x58*/ u8 setAnimation;
    /*0x59*/ u8 setTime;
    /*0x5A*/ u8 setSpeed;
    /*0x5B*/ u8 visFlags; // 3: loop, 2: play once
    /*0x5C*/ f32 time;
    /*0x60*/ f32 speed;
} MenuAnimObject;

// View of a character actor in lbl_8036E548 (+0xC04, stride 0x27C;
// cf. CharActor in main/file_80011640.h). Only the fields used here.
typedef struct MenuActor {
    /*0x000*/ struct GameActor* actor;
    /*0x004*/ u8 _004[0x8 - 0x4];
    /*0x008*/ void** files; // file offsets, relocated in place
    /*0x00C*/ u8 _00C[0x10 - 0xC];
    /*0x010*/ MenuAnimBank* animBank;
    /*0x014*/ u8 _014[0x2C - 0x14];
    /*0x02C*/ MenuFaceAnim* face;
    /*0x030*/ MenuFaceAnim* faceSub;
    /*0x034*/ u8 _034[0x40 - 0x34];
    /*0x040*/ Vec rot;
    /*0x04C*/ f32 animFrames; // frames per unit of animation time
    /*0x050*/ u8 _050[0x5C - 0x50];
    /*0x05C*/ s32 _05C;
    /*0x060*/ s16 anims[8]; // prev/cur/next/queued anim and their frames
    /*0x070*/ u8 _070[0x162 - 0x70];
    /*0x162*/ u16 joints[0x78];
    /*0x252*/ s8 kind;
    /*0x253*/ u8 _253[0x255 - 0x253];
    /*0x255*/ s8 modelIndex;
    /*0x256*/ u8 _256[0x25D - 0x256];
    /*0x25D*/ u8 _25D[0x268 - 0x25D];
    /*0x268*/ u8 faceMode;
    /*0x269*/ u8 _269[0x26C - 0x269];
    /*0x26C*/ u8 blend;
    /*0x26D*/ u8 _26D[0x26F - 0x26D];
    /*0x26F*/ u8 _26F;
    /*0x270*/ u8 _270[0x277 - 0x270];
    /*0x277*/ u8 _277;
} MenuActor; // size: 0x278 (0x27C stride)

void fn_2_8D24C(u8* object);

void fn_2_8B118(f32 value);

s32 fn_2_8CC88(s32 index);

void fn_2_8CCAC(s32 index, u8 value);

void fn_2_8CCCC(s32 index, s32 a, s32 b, u8 mode, s32 c, s32 d, s32 e, s32 f);

void fn_2_8DC00(void);

void fn_2_8C724(void);

void fn_2_8DB14(void);

void fn_2_8C80C(s32 a, s32 b, s32 c, s32 d, s32 e);

void fn_2_8D9DC(s32 mode);

void fn_2_8B2C0(void);

void fn_2_8E478(void);

void fn_2_8DCD8(void);

void fn_2_8CD58(s32 index, s32 anim, u8 loop, u8 face, s16 time, u8 eyes, u8 frames);

void fn_2_8C910(void);

void fn_2_8DFB0(void);

void fn_2_8B158(void);

void fn_2_8D270(u8 index);

#endif
