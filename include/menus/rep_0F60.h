#ifndef __REP_0F60_MENUS_H__
#define __REP_0F60_MENUS_H__

#include "mssbTypes.h"
#include "main/file_80024D2C.h"

struct GameActor;

// The blend field of a GameActor (main/file_80063028.h), which can't be included here.
typedef struct MenuModelBlend {
    /*0x00*/ u8 _00[0x8C];
    /*0x8C*/ f32 blend;
} MenuModelBlend;

// Animation bank of a character model (only the count is used here).
typedef struct MenuAnimBank {
    /*0x00*/ u8 _00[0xA];
    /*0x0A*/ u16 count;
} MenuAnimBank;

// Face/shape animation block hanging off a character (MenuActor.face/faceSub).
typedef struct MenuFaceAnim {
    /*0x00*/ u8 _00[0x4];
    /*0x04*/ ShapeAnimPlayer main;
    /*0x60*/ u8 _60[0x68 - 0x60];
    /*0x68*/ ShapeAnimPlayer sub;
    /*0xC4*/ u8 _C4[0xCC - 0xC4];
    /*0xCC*/ u8 hasSub;
} MenuFaceAnim;

// One 0x90-byte actor object slot (cf. ActorObject in main/file_800BD8C4.h);
// fn_800111D8 returns a pointer to one.
typedef struct MenuAnimObject {
    /*0x00*/ struct GameActor* actor;
    /*0x04*/ MenuAnimBank* animBank;
    /*0x08*/ u8 _08[0xE - 0x8];
    /*0x0E*/ s16 seqNum;
    /*0x10*/ u8 _10[0x58 - 0x10];
    /*0x58*/ u8 setAnimation;
    /*0x59*/ u8 setTime;
    /*0x5A*/ u8 setSpeed;
    /*0x5B*/ u8 visFlags; // 3: loop, 2: play once
    /*0x5C*/ f32 time;
    /*0x60*/ f32 speed;
} MenuAnimObject;

// View of a character actor in lbl_8036E548 (+0xC04, stride 0x27C;
// cf. ActorMgrActor in main/file_8000F150.h). Only the fields used here.
typedef struct MenuActor {
    /*0x000*/ struct GameActor* actor;
    /*0x004*/ u8 _004[0x10 - 0x4];
    /*0x010*/ MenuAnimBank* animBank;
    /*0x014*/ u8 _014[0x2C - 0x14];
    /*0x02C*/ MenuFaceAnim* face;
    /*0x030*/ MenuFaceAnim* faceSub;
    /*0x034*/ u8 _034[0x4C - 0x34];
    /*0x04C*/ f32 animFrames; // frames per unit of animation time
    /*0x050*/ u8 _050[0x162 - 0x50];
    /*0x162*/ u16 joints[8];
    /*0x172*/ u8 _172[0x268 - 0x172];
    /*0x268*/ u8 faceMode;
    /*0x269*/ u8 _269[0x26C - 0x269];
    /*0x26C*/ u8 blend;
} MenuActor;

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

#endif
