#ifndef __MAIN_FILE_800263FC_H__
#define __MAIN_FILE_800263FC_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// Particle effect system: a pool of 0x1400 particles (lbl_80180040) and
// 16 emitters (lbl_801F8040), each emitter owning a singly linked list of
// particles and sitting in a priority-sorted doubly linked active list
// (head lbl_803CBC84).

typedef struct Particle {
    /* 0x00 */ struct Particle* next;
    /* 0x04 */ Vec pos;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 unk24[0x38 - 0x24];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8 unk44[0x48 - 0x44];
    /* 0x48 */ s16 unk48;  // start delay (> 0: not yet visible)
    /* 0x4A */ s16 unk4A;  // life
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ s8 unk4D;
    /* 0x4E */ u8 unk4E[0x60 - 0x4E];
} Particle; // size 0x60

struct Emitter;
typedef s32 (*EmitterUpdateFn)(struct Emitter* e); // returns nonzero when finished

typedef struct Emitter {
    /* 0x00 */ struct Emitter* prev;
    /* 0x04 */ struct Emitter* next;
    /* 0x08 */ EmitterUpdateFn update; // NULL: emitter is free
    /* 0x0C */ Particle* particles;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u16 unk14 : 4;
    /* 0x14 */ u16 count : 12;
    /* 0x16 */ u8 priority;
    /* 0x17 */ u8 active : 1;
    /* 0x17 */ u8 type : 7;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ Vec unk24;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ u8 unk48[0x60 - 0x48];
} Emitter; // size 0x60

// Head of the active emitter list; aliases the prev/next of an Emitter.
typedef struct EmitterHead {
    /* 0x0 */ struct Emitter* prev;
    /* 0x4 */ struct Emitter* next;
} EmitterHead;

// Spawn template copied from lbl_800F787C.
typedef struct ParticleParams {
    /* 0x00 */ s32 unk0;
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

s32 fn_80032038(const void* a, const void* b);
f32 fn_800335BC(s32 angle);
f32 fn_800335EC(s32 angle);
void fn_80033794(Particle* list);
Emitter* fn_800337CC(Emitter* e, s32 n, s32 strict);
void pitchingMachinePitching(u8 type);
void fn_80033964(Emitter* e);
Emitter* fn_80033A24(EmitterUpdateFn update, u8 priority, s32 unk14, s32 n, s32 strict, u8 type);
s32 fn_80033928(u8 type);
Emitter* fn_800339F0(Emitter* after, u8 type);
void fn_80027918(u8 type, f32 v);
void fn_800340F4(Mtx m);
void fn_80034120(Mtx m);

#endif
