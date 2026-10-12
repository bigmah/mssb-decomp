#ifndef __GAME_rep_1E08_H_
#define __GAME_rep_1E08_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// Lens-flare element (16 bytes); a list ends with size == 0.
typedef struct BD434E {
    /* 0x0 */ f32 x;     // distance along the flare axis
    /* 0x4 */ f32 y;     // alpha slope (types 2/3)
    /* 0x8 */ f32 z;     // size
    /* 0xC */ s16 tex;   // index into the texture table
    /* 0xE */ u8 type;   // 0/1 spinning quad, 2 square, 3 rotated starburst, 4+ sun
    /* 0xF */ u8 occl;   // drawn even when occluded; also the fn_800B21A8 mode
} BD434E;

typedef struct { f32 x, y; } V2f;

// Ring-burst effect instance (one per frame buffer, filled by fn_3_BDCA4, drawn by fn_3_BD8FC).
typedef struct BDCA4E {
    /* 0x00 */ void* next; // draw-list link
    /* 0x04 */ void (*draw)(struct BDCA4E* e); // fn_3_BD8FC
    /* 0x08 */ Mtx m;
    /* 0x38 */ f32 x, y, z;
    /* 0x44 */ s32 n;
    /* 0x48 */ f32 s;
    /* 0x4C */ V2f pts[0x60];
} BDCA4E; // size 0x34C

// Scene-queue task slots (SceneTask, main/file_80069BDC.h) as this unit's tasks use them.
typedef struct Rep1E08TaskHead {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ void* prev;
    /* 0x08 */ void* next;
    /* 0x0C */ void* parent;
} Rep1E08TaskHead;

// Ring-burst task (fn_3_BDE14 / fn_3_BDF74, drawn by fn_3_BDCA4).
typedef struct RingBurstTask {
    /* 0x00 */ Rep1E08TaskHead head;
    /* 0x10 */ s16 delay;
    /* 0x12 */ u16 priority;
#ifdef TARGET_PC
    void* _u14align[0]; // SceneTask.u14 is 8-byte aligned
#endif
    /* 0x14 */ Vec pos;
    /* 0x20 */ s32 n;
    /* 0x24 */ BDCA4E* ring;
} RingBurstTask;

// Asset-load task (fn_3_BD758).
typedef struct LoadTask1E08 {
    /* 0x00 */ Rep1E08TaskHead head;
    /* 0x10 */ s16 _10;
    /* 0x12 */ u16 priority;
#ifdef TARGET_PC
    void* _u14align[0]; // SceneTask.u14 is 8-byte aligned
#endif
    /* 0x14 */ u16 loader; // lbl_3_data_11390 index
    /* 0x16 */ u16 slot;   // StadiumFxState._40C index
} LoadTask1E08;

// Layout-sprite effect task (fn_3_BEFF8 / fn_3_BE1D4).
typedef struct LayoutFxTask {
    /* 0x00 */ Rep1E08TaskHead head;
    /* 0x10 */ s16 _10;
    /* 0x12 */ u16 priority;
#ifdef TARGET_PC
    void* _u14align[0]; // SceneTask.u14 is 8-byte aligned
#endif
    /* 0x14 */ u16 objIdx; // first slot in lbl_80371C30
    /* 0x16 */ u16 _16;
    /* 0x18 */ s16 _18;
} LayoutFxTask;

// Sprite animation set drawn by fn_3_BF8F8 (elements of 0x44 bytes).
typedef struct SprAnimElem {
    /* 0x00 */ f32 x, y, w, h;
    /* 0x10 */ u16 tex;
    /* 0x12 */ u16 texIdx;
    /* 0x14 */ void* ch[8];   // keyframe tracks (fn_3_BFDA4), NULL: constant
    /* 0x34 */ u8 chMode[8];
    /* 0x3C */ u8 chState[8];
} SprAnimElem; // size: 0x44

typedef struct SprAnim {
    /* 0x00 */ SprAnimElem* elems;
    /* 0x04 */ void** textures;
    /* 0x08 */ s32 count;
    /* 0x0C */ u8 _0C[4];
    /* 0x10 */ f32 _10;
    /* 0x14 */ f32 _14;
} SprAnim;

struct CharActor;
struct Particle;
struct Emitter;

void fn_3_BA538(struct Particle* p);
void fn_3_BA7F4(struct Emitter* a);
void fn_3_BB07C(f32*, f32);
void fn_3_BB15C(struct Particle* p);
void fn_3_BB454(struct Emitter* a);
void fn_3_BB7F4(void);
void fn_3_BBBC4(void);
void fn_3_BBF94(void);
void fn_3_BC224(void);
void fn_3_BC25C(void);
s32 fn_3_BC274(struct CharActor* a, Vec* b, Vec* c);
void fn_3_BC2DC(void);
void fn_3_BC6D8(Vec* from, Vec* to, int idx, int c);
void fn_3_BC850(int a, int i);
void fn_3_BC888(void);
void fn_3_BCA20(void);
void fn_3_BD1D4(void);
void fn_3_BD1D8(f32 (*m)[4]);
void fn_3_BD434(int, int);
void fn_3_BD4F0(void);
void fn_3_BD504(int a, f32 x, f32 y, f32 z);
void fn_3_BD6AC(int, f32, f32, f32);
void fn_3_BD758(void);
s32 fn_3_BD7D0(void);
void fn_3_BD7D8(void);
void fn_3_BD7DC(MtxPtr view);
void fn_3_BD80C(MtxPtr a);
void fn_3_BD8D8(void);
void fn_3_BD8FC(BDCA4E* e);
void fn_3_BDCA4(void);
void fn_3_BDE14(void);
void fn_3_BDF74(void);
void fn_3_BE140(void);
void fn_3_BE174(s32 a, f32 x, f32 y, f32 z);
void fn_3_BE1D4(void);
void fn_3_BEFF8(void);
void fn_3_BF070(void);
void fn_3_BF158(void);
void fn_3_BF1AC(void);
void fn_3_BF20C(void);
void fn_3_BF238(void);
void fn_3_BF6C0(void);
int fn_3_BF878(void);
void fn_3_BF8F8(SprAnim* a, f32 (*in)[4], f32* pos, f32 (*cb)(SprAnimElem*, s32, f32 (*)[4], f32));
f32 fn_3_BFB3C(SprAnimElem* e, s32 x, f32 (*m)[4], f32 t);
f32 fn_3_BFDA4(void* k, s32 n, f32 t, s32 len, u8 idx, u8* out);
s32 fn_3_C0134(void);

void fn_3_C07A0(void);
void fn_3_C07B0(void);

void fn_3_C0770(void);

#endif // !__GAME_rep_1E08_H_
