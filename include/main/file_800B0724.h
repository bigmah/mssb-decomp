#ifndef __MAIN_FILE_800B0724_H__
#define __MAIN_FILE_800B0724_H__

#include "mssbTypes.h"
#include "main/file_80063028.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gd.h"

struct QuadVtx;
struct QuadState;
struct SpriteTexInfo;
struct DrawNode;

// GXSetProjectionv-style projection: type, then the six used terms of the 4x4 matrix.
typedef struct SpriteProj {
    /*0x00*/ f32 type;
    /*0x04*/ f32 p[6];
} SpriteProj; // size 0x1C

// GX state of a sprite layer. lbl_803CBB34 is the wanted state, lbl_803CBB38 the state
// already written into the layer's display list; DrawSprite emits only the differences.
typedef struct SpriteState {
    /*0x00*/ Mtx mtx;
    /*0x30*/ SpriteProj proj;
    /*0x4C*/ struct SpriteTexInfo* tex[7]; // texture loaded into each map
    /*0x68*/ u16 texSerial[8];
    /*0x78*/ u32 zMode;      // BP register 0x40 (GX_BP_REG_ZMODE) value
    /*0x7C*/ u32 savedZMode;
    /*0x80*/ s32 primOffset; // display-list offset of the last primitive header, -1 if none
    /*0x84*/ u16 serial;
    /*0x86*/ u16 texWidth;
    /*0x88*/ u16 texHeight;
    /*0x8A*/ u8 blendMode;
    /*0x8B*/ u8 textured;
    /*0x8C*/ u8 noAlphaTest;
    /*0x8D*/ u8 alphaTest;
    /*0x8E*/ u8 pad8E[2];
} SpriteState; // size 0x90

#define SPRITE_MAX_LAYERS 24

// A geometry palette entry (8 bytes) as seen by fn_800B2AC8.
typedef struct LoadedGeoEntry {
    /*0x0*/ u8* obj; // display object
    /*0x4*/ u8 pad4[4];
} LoadedGeoEntry;

typedef struct LoadedGeoPalette {
    /*0x00*/ u8 pad00[0x10];
    /*0x10*/ LoadedGeoEntry* entries;
} LoadedGeoPalette;

// C3 ActorBone (0x1C) as stored after the actor layout header.
typedef struct LoadedActorBone {
    /*0x00*/ u8 pad00[0x14];
    /*0x14*/ u16 geoFileID; // 0xFFFF: no geometry
    /*0x16*/ u16 boneID;
    /*0x18*/ u8 inheritanceFlag;
    /*0x19*/ u8 drawingPriority;
    /*0x1A*/ u16 flags;
} LoadedActorBone;

// C3 ActorLayout header (0x20) followed by its bones, with the palette resolved.
typedef struct LoadedActorLayout {
    /*0x00*/ u8 pad00[6];
    /*0x06*/ u16 totalBones;
    /*0x08*/ u8 pad08[8];
    /*0x10*/ LoadedGeoPalette* pal;
    /*0x14*/ u8 pad14[0xC];
    /*0x20*/ LoadedActorBone bones[1]; // totalBones entries
} LoadedActorLayout;

// Object returned by fn_800BF068 (lbl_803009F8).
typedef struct SkinState {
    /*0x0*/ u8 pad0[8];
    /*0x8*/ void* unk8;
} SkinState;

// Per-layer display-list draw command handed to fn_800A7D4C.
typedef struct SpriteDrawCmd {
    /*0x0*/ u32 link; // low two bits: flags (fn_800B0D38); the rest is set by fn_800A7D4C
    /*0x4*/ void (*draw)(struct SpriteDrawCmd* cmd);
    /*0x8*/ GDCurrentDL* dl;
} SpriteDrawCmd; // size 0xC

// Sprite system work area (lbl_802FE8B8).
typedef struct SpriteWork {
    /*0x0000*/ s32 layerIds[SPRITE_MAX_LAYERS];
    /*0x0060*/ SpriteProj proj[SPRITE_MAX_LAYERS];
    /*0x0300*/ u8 pad300[0x40];
    /*0x0340*/ SpriteState wanted[SPRITE_MAX_LAYERS];
    /*0x10C0*/ SpriteState committed[SPRITE_MAX_LAYERS];
    /*0x1E40*/ GDCurrentDL dl[2][SPRITE_MAX_LAYERS]; // double-buffered
} SpriteWork;

// Arguments to sndInit (default: lbl_801112F0).
typedef struct SoundConfig {
    /*0x0*/ u8 voices;
    /*0x1*/ u8 music;
    /*0x2*/ u8 sfx;
    /*0x3*/ u8 studios;
    /*0x4*/ u32 flags;
    /*0x8*/ u32 aramSize;
} SoundConfig;

// Stack-like heap that the sound library allocates from (SndAlloc/SndFree).
typedef struct SndHeap {
    /*0x0*/ s32 free;
    /*0x4*/ u8* cur;
    /*0x8*/ u8* end;
} SndHeap;

// Header placed just before every SndAlloc block.
typedef struct SndBlockHdr {
    /*0x0*/ u8* prevCur; // heap->cur before the allocation
    /*0x4*/ u32 size;    // bytes taken from the heap, including alignment
} SndBlockHdr;

void makeLookAtMatrix(Mtx m, Vec* camPos, Vec* camUp, Vec* target);
void soundQuit(void);
void initSound(SoundConfig* config, u8* aiStack, u8* heapStart, u32 heapSize);
void SndFree(void* ptr);
void* SndAlloc(u32 size);

void DrawSprite(s32 prim, struct QuadVtx* verts, s32 count, struct SpriteTexInfo* tex, u16 width, u16 height);
void DrawNullSprite(struct QuadVtx* verts, s32 count); // triangle strip
void fn_800B12DC(struct QuadVtx* verts, s32 count); // triangle fan
void fn_800B1314(struct QuadVtx* verts, struct SpriteTexInfo* tex, u16 width, u16 height); // textured quad
void DrawSprite_TexObj(struct QuadState* quad, struct SpriteTexInfo* tex); // textured quad
void fn_800B1388(struct QuadState* quad); // untextured quad
void fn_800B1188(void);
void fn_800B13C0(Vec* pos, u32* colors, s32 count); // triangle fan
s32 AllocateSprite(s32 layer, s32 needed);
void fn_800B1468(Vec* pos, u32 color, struct SpriteTexInfo* tex); // textured quad
void fn_800B24D4(s32 layer);
void fn_800B2AC8(LoadedActorLayout* layout);
void fn_800B2854(u8* buf, s32 bufSize, Mtx44 proj, s32 projType, s32 numLayers, s32* layerIds, s32* layerSizes);
void fn_800B27A4(s32 fracBits);
void fn_800B27DC(Mtx44 m, s32 type); // set projection (GXSetProjection)
s32 fn_800B1EBC(struct SpriteTexInfo* tex, s32 map, u32 width, u32 height);

void fn_800B0934(void);

typedef struct DrawingQueueNode {
    void (*draw)(void);
    struct DrawingQueueNode* previous;
    struct DrawingQueueNode* next;
} DrawingQueueNode;

void fn_800B0A14_removeQueue(void* unused);

void nop_function(void);

void fn_800B0C80(void (*draw)(void));

void resetAllDrawingStructs(void);

struct SceneTask* fn_800B0A5C_insertQueue(void* draw, u16 priority);

void fn_800B0D28(s32* layerSizes);

void fn_800B0D38(s32 index, s32 value);

void fn_800B117C(u8 value);

void fn_800B2160(u8 value);

s32 fn_800B216C(u8 flag, u32 mode, u8 index);

void fn_800B21A8(s32 mode);

void fn_800B2B4C(GameActor* actor, f32 value);
void fn_800B2B54(GameActor* actor, u16 bone, u8 value);
void Set_FUN_800b2b6c(GameActor* actor, s32 value);
void fn_800B2B74(GameActor* actor, u16 bone);
struct DODisplayObj* fn_800B2BA8(GameActor* actor, u16 bone, GameActor* src, u16 srcBone);
void fn_800B2BE4(GameActor* actor, u16 bone);
void fn_800B2BFC(GameActor* actor, s16 a, s16 b);
void fn_800B2C08(GameActor* actor, s16 value);
void fn_800B2C10(GameActor* actor, u16 index, Vec* v);

#endif
