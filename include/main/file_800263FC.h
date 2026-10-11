#ifndef __MAIN_FILE_800263FC_H__
#define __MAIN_FILE_800263FC_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "main/file_80024184.h"
#include "main/file_80034F50.h"

// Particle effect system: a pool of 0x1400 particles (lbl_80180040) and
// 16 emitters (lbl_801F8040), each emitter owning a singly linked list of
// particles and sitting in a priority-sorted doubly linked active list
// (head lbl_803CBC84).

// Texture archive: a count followed by 0x20-byte entries; entry[i].index
// selects which entry's image is used for texture i.
typedef struct TexArchiveEntry {
    /* 0x00 */ TexImage img;
    /* 0x1C */ u16 index;
    /* 0x1E */ u8 pad1E[2];
} TexArchiveEntry; // size 0x20

typedef struct TexArchive {
    /* 0x00 */ s32 count;
    /* 0x04 */ TexArchiveEntry entries[1]; // variable length
} TexArchive;

typedef struct Particle {
    /* 0x00 */ struct Particle* next;
    /* 0x04 */ Vec pos;
    /* 0x10 */ union {
        struct {
            /* 0x10 */ Vec vel;
            /* 0x1C */ Vec accel;
            /* 0x28 */ Vec force;
            /* 0x34 */ f32 mass;
        } phys;
        struct {
            /* 0x10 */ f32 unk10;
            /* 0x14 */ f32 unk14;
            /* 0x18 */ s32 unk18;
            /* 0x1C */ s32 unk1C;
            /* 0x20 */ s32 id;
            /* 0x24 */ u8 pad24[0x38 - 0x24];
        } t6;
    } u;
    /* 0x38 */ f32 sizeX;
    /* 0x3C */ f32 sizeY;
    /* 0x40 */ union {
        u32 rgba;
        GXColor c;
        u8 v[4];
    } color;
    /* 0x44 */ union {
        u32 all;
        u8 v[4]; // signed steps added to color every frame
    } colorStep;
    /* 0x48 */ s16 delay;       // frames before the particle appears
    /* 0x4A */ s16 life;        // frames left (0: dead)
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ u8 texIndex;
    /* 0x4E */ u8 uvFrame;
    /* 0x4F */ u8 uvOrder;      // 2 bits per corner: index into lbl_800F78C0
    /* 0x50 */ u8 unk50[0x60 - 0x50];
} Particle; // size 0x60

struct Emitter;
typedef s32 (*EmitterUpdateFn)(struct Emitter* e); // returns nonzero when finished

typedef struct Emitter {
    /* 0x00 */ struct Emitter* prev;
    /* 0x04 */ struct Emitter* next;
    /* 0x08 */ EmitterUpdateFn update; // NULL: emitter is free
    /* 0x0C */ Particle* particles;
    /* 0x10 */ TexArchive* tex;
    /* 0x14 */ u16 unk14 : 4;
    /* 0x14 */ u16 count : 12;
    /* 0x16 */ u8 priority;
    /* 0x17 */ u8 active : 1;
    /* 0x17 */ u8 type : 7;
    /* 0x18 */ union {
        struct {
            /* 0x18 */ Vec pos;       // spawn position
            /* 0x24 */ Vec dir;       // spray direction
            /* 0x30 */ f32 speed;
            /* 0x34 */ s32 spawnLeft; // frames left in which dead particles respawn
            /* 0x38 */ f32 bounce;    // vel.y multiplier at the floor
            /* 0x3C */ f32 floorY;
            /* 0x40 */ u32 color;
            /* 0x44 */ f32 size;
        } t1;
        struct {
            /* 0x18 */ Vec pos;
            /* 0x24 */ Vec prevPos;
            /* 0x30 */ s32 fadeLife; // particles start fading out at this life
        } t9;
        struct {
            /* 0x18 */ Vec start;
            /* 0x24 */ Vec end;
            /* 0x30 */ Vec dir;
            /* 0x3C */ u8 pad3C[4];
            /* 0x40 */ u16 unk40;
        } t10;
        /* 0x18 */ f32 f[0x12]; // per-type parameters, see fn_80027918
        /* 0x18 */ u8 raw[0x48];
    } u;
} Emitter; // size 0x60

// u/v texel coordinates of one quad corner (lbl_800F7860).
typedef struct UVCoord {
    /* 0x0 */ u16 u;
    /* 0x2 */ u16 v;
} UVCoord;

// Spawn parameters of the spark/trail emitter (type 9). Float values are
// stored as fixed point (x100000); angles in degrees.
typedef struct ParticleParams9 {
    /* 0x00 */ TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 life;
    /* 0x10 */ s32 sizeMin;
    /* 0x14 */ s32 sizeMax;
    /* 0x18 */ s32 speed;
    /* 0x1C */ s32 delayRange;
    /* 0x20 */ s32 lifeRange;
    /* 0x24 */ s32 yawMin;
    /* 0x28 */ s32 yawMax;
    /* 0x2C */ s32 pitchMin;
    /* 0x30 */ s32 pitchMax;
    /* 0x34 */ s32 fadeLife;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 angleMin;
    /* 0x44 */ s32 angleMax;
} ParticleParams9;

typedef struct TexCoordF {
    /* 0x0 */ f32 s;
    /* 0x4 */ f32 t;
} TexCoordF;

// Head of the active emitter list; aliases the prev/next of an Emitter.
typedef struct EmitterHead {
    /* 0x0 */ struct Emitter* prev;
    /* 0x4 */ struct Emitter* next;
} EmitterHead;

// Spawn template copied from lbl_800F787C.
typedef struct ParticleParams {
    /* 0x00 */ TexArchive* tex;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 unk18[0x44 - 0x18];
} ParticleParams; // size 0x44

typedef struct ParticleSortEntry {
    /* 0x0 */ Particle* p;
    /* 0x4 */ f32 z;
} ParticleSortEntry;

void fn_8002CDD0(Vec* end);
s32 fn_8002D82C(Emitter* e);
void fn_8002DC68(Vec* pos);
void fn_8002DCE4(Vec* from, Vec* to, ParticleParams9* prm);
s32 fn_8002F1AC(Vec* pos, s32 id);
Particle* fn_80031F34(Particle* list, s32 n);
s32 fn_80032038(const void* a, const void* b);
f32 fn_800335BC(s32 angle);
f32 fn_800335EC(s32 angle);
s32 fn_800328E0(Emitter* e);
void fn_800330CC(s32 n, u32 color, Vec* pos, Vec* dir, s32 spawnFrames, TexArchive* tex, f32 speed, f32 size);
void fn_80033620(Emitter* e);
void fn_80033794(Particle* list);
Emitter* fn_800337CC(Emitter* e, s32 n, s32 strict);
void pitchingMachinePitching(u8 type);
void fn_80033964(Emitter* e);
Emitter* fn_80033A24(EmitterUpdateFn update, u8 priority, s32 unk14, s32 n, s32 strict, u8 type);
s32 fn_80033928(u8 type);
Emitter* fn_800339F0(Emitter* after, u8 type);
void fn_80027918(u8 type, f32 v);
void fn_800332B8(Vec* axis, Vec* out, f32 yawMin, f32 yawMax, f32 pitchMin, f32 pitchMax);
void fn_80033B58(TexArchive* arc, s32 idx, GXTexWrapMode wrapS, GXTexWrapMode wrapT);
void fn_80033CC8(Particle* p, TexArchive* arc);
void fn_80033F64(f32 width, f32 height, f32 angleDeg);
void fn_8003403C(f32 width, f32 height);
void fn_800340F4(Mtx m);
void fn_80034120(Mtx m);
void minigamesSetSomePointers(void);
void minigamesSetSomePointers2(void);
void fn_8003414C(Mtx view);

// Owner of a run of sprites in lbl_80371C30.
typedef struct SpaniGroup {
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ u16 baseIdx;
    /* 0x16 */ u16 count;
} SpaniGroup;

// lbl_80371C30 entries.
typedef struct SpaniSlot {
    /* 0x0 */ SpaniObj* obj;
    /* 0x4 */ SpaniGroup* owner;
} SpaniSlot;

// Something that drives attached sprites (fn_80034BCC).
typedef struct SpaniAttach {
    /* 0x00 */ u8 unk0[0x64];
    /* 0x64 */ MtxPtr mtx;
    /* 0x68 */ u8 color[4];
    /* 0x6C */ s16* key; // [0]: anim id, [1]: tag
} SpaniAttach;

s32 fn_80034BCC(SpaniAttach* a);
void fn_80034CEC(SpaniGroup* g);
void fn_80034E20(SpaniGroup* g, SpaniDesc* descs);

#endif
