#ifndef __MAIN_PARTICLE_PARAMS5_H__
#define __MAIN_PARTICLE_PARAMS5_H__

// Split out of main/file_800263FC.h for units that can't include that header.

#include "mssbTypes.h"
#include "main/file_80024184.h" // TexArchive

// Spawn parameters of the type-5 emitters (ring/burst variants). Fixed
// point x100000 where floats are meant; the meaning of most words depends
// on the init function.
typedef struct ParticleParams5 {
    /* 0x00 */ TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ u32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
} ParticleParams5;

#endif
