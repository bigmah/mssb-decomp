#ifndef __GAME_rep_1C0_H_
#define __GAME_rep_1C0_H_

#include "mssbTypes.h"
#include "Dolphin/GX/GXTypes.h"
#include "Dolphin/mtx.h"

struct TexImage;

// lbl_3_data_228 (0x14 bytes, defined in rep_1C0.c): frame counter / random seed.
typedef struct RandSeedView {
    /*0x00*/ u32 counter;     // frames the game logic actually ran
    /*0x04*/ s32 totalFrames;
    /*0x08*/ s32 randomInt1;    // copy of g_Ball.StaticRandomInt1
    /*0x0C*/ s32 randomInt2;    // copy of g_Ball.StaticRandomInt2
    /*0x10*/ u8 _10;
    /*0x11*/ u8 _11[3];
} RandSeedView; // size: 0x14

struct StadiumArchive;

// Per-frame stadium draw callback: (view matrix, translucent pass, layer).
typedef void (*StadiumDrawFn)(float (*view)[4], s32 translucent, u32 layer);

void (*setFanObjPtr(void))(void);
void fn_3_35E4(void (*val)(void));
void fn_3_35F0(Mtx view, s32 arg);
struct StadiumSkyObj;
void fn_3_3638(struct StadiumSkyObj* obj);
void fn_3_3818(void);
void fn_3_38E8(StadiumDrawFn a);
void fn_3_3904(s16 x, s16 y, s32 msg, GXColor color0, GXColor color1, u8 flags);
void fn_3_3BE8(struct TexImage* img, s16 x0, s16 y0, s16 x1, s16 y1, s16 u, s16 v, s16 uw, s16 vh);
void fn_3_3EE8(struct TexImage* img, s16 x0, s16 y0, s16 x1, s16 y1, s16 u, s16 v, s16 uw, s16 vh);
void fn_3_42CC(GXTexObj* tex, s16 x0, s16 y0, s16 x1, s16 y1, s16 sx, s16 sy, s16 sw, s16 sh,
               GXColor color0, GXColor color1, u8 flags);
void fn_3_4984(void);
void fn_3_4A38(u8 a);
void fn_3_4F90(GXTexObj* tex, s16 x, s16 y, s16 value, u8 width, GXColor color0, GXColor color1, u8 boxed);
void fn_3_53E0(u16* in, s16* a, s16* b, s16* c, s16* d, s16* e);
void fn_3_5518(void);
void fn_3_567C(void);
void fn_3_5BAC(void);
struct StadiumCameraNode;
void fn_3_5BCC(struct StadiumCameraNode* p);
void fn_3_5BF0(void);
struct StadiumAnimNode;
void fn_3_5C68(struct StadiumAnimNode* obj);
void fn_3_5E60(void);
void fn_3_5EC0(struct StadiumArchive* arc);
void fn_3_64DC(void);
struct _CollisionBox;
s16 fn_3_6424(u8* base, struct _CollisionBox** out);

#endif // !__GAME_rep_1C0_H_
