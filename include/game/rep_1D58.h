#ifndef __GAME_rep_1D58_H_
#define __GAME_rep_1D58_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "C3/control.h"
#include "C3/light.h"
#include "main/file_800BD8C4.h" // ActorObject
#include "main/file_80024D2C.h" // ShapeAnimState, ShapeData

typedef struct SortEnt SortEnt; // {f32 z; s32 idx}, defined in rep_1D58.c

#include "game/sta_ext_list.h" // StaExtList

// Shape (texture) animation attached to a stadium object.
typedef struct StadiumObjShape {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ ShapeAnimState anim;
    /* 0x2C */ ShapeData* shape;
} StadiumObjShape;

// One 0xE8-byte stadium object (lbl_3_common_bss_350E4.objs[]).
typedef struct StadiumObj {
    /* 0x00 */ Control ctrl;
    /* 0x3C */ u8 pad3C[8];
    /* 0x44 */ Mtx mtx;
    /* 0x74 */ ActorObject* actor;
    /* 0x78 */ void* unk78; // collision model
    /* 0x7C */ void (*update)(struct StadiumObj* obj); // run each frame by fn_3_B93CC
    /* 0x80 */ void (*func)(int, int, void*);
    /* 0x84 */ void (*preDraw)(struct StadiumObj* obj);
    /* 0x88 */ void (*postDraw)(struct StadiumObj* obj);
    /* 0x8C */ StadiumObjShape* shapeAnim;
#ifdef TARGET_PC // bitfields in MWCC (big-endian) bit order
    /* 0x90 */ u8 flag01 : 1;
    /* 0x90 */ u8 zUpdate : 1;
    /* 0x90 */ u8 zAlways : 1;   // GX_ALWAYS instead of GX_LEQUAL
    /* 0x90 */ u8 zCompare : 1;
    /* 0x90 */ u8 customZ : 1;   // use the z mode bits below
    /* 0x90 */ u8 depthFade : 1; // sorted by depth; alpha scaled by the sort factor
    /* 0x90 */ u8 flag40 : 1;
    /* 0x90 */ u8 visible : 1;
#else
    /* 0x90 */ u8 visible : 1;
    /* 0x90 */ u8 flag40 : 1;
    /* 0x90 */ u8 depthFade : 1; // sorted by depth; alpha scaled by the sort factor
    /* 0x90 */ u8 customZ : 1;   // use the z mode bits below
    /* 0x90 */ u8 zCompare : 1;
    /* 0x90 */ u8 zAlways : 1;   // GX_ALWAYS instead of GX_LEQUAL
    /* 0x90 */ u8 zUpdate : 1;
    /* 0x90 */ u8 flag01 : 1;
#endif
    /* 0x91 */ u8 pad91;
    /* 0x92 */ u8 alpha;
    /* 0x93 */ u8 viewFlags;     // low 2 bits: fn_800B3C04 result
    /* 0x94 */ u16 attached;
    /* 0x96 */ s16 attachJoint;  // -1: attach to the camera matrix
    /* 0x98 */ u8 layer;
    /* 0x99 */ u8 pad99;
    /* 0x9A */ u8 castShadow;
    /* 0x9B */ u8 pad9B[0xE8 - 0x9B];
#ifdef PORT_LP64
    // All stadium object types share one PC size, 0x128: the generic code
    // (game/rep_1D58.c) indexes them as StadiumObj.
    u8 _lp64pad[0x128 - 0x108];
#endif
} StadiumObj; // size: 0xE8

// lbl_3_common_bss_350E4: the stadium object manager (other units declare
// their own views of it, see StadiumObjList in game/rep_2998.h).
typedef struct StadiumObjMgr {
    /* 0x00 */ StadiumObj* objs;
    /* 0x04 */ StadiumObj* saved;   // copy taken by fn_3_B9124
    /* 0x08 */ StaExtList* anim[2];  // animated texture tiles (fn_3_5C68)
    /* 0x10 */ void* unk10;
    /* 0x14 */ SortEnt* sort;
    /* 0x18 */ void (*draw)(void);
    /* 0x1C */ void (*update)(void);
    /* 0x20 */ Light* lights[4];
    /* 0x30 */ s32 count;
    /* 0x34 */ u32* fileIdx;        // indices into the stadium file table
    /* 0x38 */ void* data;          // the stadium archive
    /* 0x3C */ u32* groupCount;     // per draw group: number of objects
    /* 0x40 */ u16* groupStart;     // per draw group: first entry in groupObjs
    /* 0x44 */ u32* groupObjs;
    /* 0x48 */ Vec* groupBounds;    // per draw group: min and max corner
    /* 0x4C */ Vec noteBlockPos;
    /* 0x58 */ u8 pad58[0x64 - 0x58];
    /* 0x64 */ s16 numGroups;
    /* 0x66 */ s16 seed;            // rand() per game
    /* 0x68 */ s16 savedSeed;
    /* 0x6A */ u8 loading;          // archive transfer queued (fn_3_B9BB4)
    /* 0x6B */ u8 pad6B;
    /* 0x6C */ u8 sortByDepth;
    /* 0x6D */ u8 numActorObjs;     // entries of lbl_8036E548.slots6C
    /* 0x6E */ u8 pad6E[2];
} StadiumObjMgr; // size: 0x70


s32 fn_3_B7FC8(s32 id, s32 kind); // returns fn_3_8BBC4's sound handle
void fn_3_B80D0(void);
void fn_3_B8184(void* pp, void* cam);
struct StadiumObj* fn_3_B827C(void);
void fn_3_B828C(struct StadiumObj* val);
void fn_3_B8298(void);
void fn_3_B8414(void* a, void* b);
void fn_3_B8464(void* mtx, void* obj);
void fn_3_B8574(void);
u32 fn_3_B85A8(int idx, u32** out); // *out: the group's object indices; returns their count
void fn_3_B85DC(s32 i, void* a, void* b);
s32 fn_3_B8658(f32* a, f32* b);
void fn_3_B867C(void* mtx, struct SortEnt* out);
void fn_3_B8828(float (*view)[4], s32 translucent, u32 layer);
void fn_3_B8C08(float (*view)[4]);
void fn_3_B902C(void);
void fn_3_B908C(void);
void fn_3_B9124(void);
void processStadiumObjectFunction(int, void*, int, void*);
void* fn_3_B91C8(s32 type, s32 idx, Mtx m); // the object's collision model, or NULL
void fn_3_B939C(void);
void fn_3_B93C4(void);
void fn_3_B93C8(s32 unused); // empty; rep_1038 passes 1
void fn_3_B93CC(void);
void fn_3_B950C(void);
void fn_3_B9510(s32 i);
void fn_3_B9524(void);
void* fn_3_B9534(u32 w, u32 h, void* tex);
void fn_3_B95EC(void);
void fn_3_B97C8(void* p);
void fn_3_B97DC(struct ActorObject* obj, void* animBank);
void fn_3_B98E8(void* p);
void fn_3_B99E4(void);
s32 fn_3_B9BB4(u32 type);
void fn_3_B9D68(u8* kinds, s32 count, u8* table, s32* outIdx);
void fn_3_B9FB8(u32 type, void* p);

#endif // !__GAME_rep_1D58_H_
