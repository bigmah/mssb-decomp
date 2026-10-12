#ifndef __CHALLENGE_CH_DATA_H__
#define __CHALLENGE_CH_DATA_H__

#include "mssbTypes.h"

// Data layouts shared by several challenge.rel files. They copy main.dol types
// whose headers can't be included next to static/UnknownHomes_Static.h
// (conflicting prototypes); the layouts are the same.

// AssetLoadInstructions (Unknown/File_0x800a64e0.h): one ARAM file table
// entry, as plain words because its anonymous unions can't be initialised.
typedef struct ChFileEntry {
    /* 0x0 */ u32 compressionConstants;
    /* 0x4 */ u32 sizeFlags; // top 2 bits: compression flag, low 28: size
    /* 0x8 */ u32 aramOffset;
    /* 0xC */ u32 compressedSize;
} ChFileEntry; // size: 0x10

// SpaniDesc (main/file_80034F50.h): one sprite of a layout handed to
// fn_80034E20; a list ends with type 3.
typedef struct ChSpaniDesc {
    /* 0x00 */ u16 type;
    /* 0x02 */ u16 animId;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 playMode;
    /* 0x11 */ u8 layer;
    /* 0x12 */ u8 unk12[2];
    /* 0x14 */ u8 texId;
    /* 0x15 */ u8 unk15[3];
    /* 0x18 */ f32 scale;
    /* 0x1C */ u8 is3D;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s16 unk1E;
} ChSpaniDesc; // size: 0x20

// A 2D sprite with the usual defaults, and the list terminator.
#define CH_SPANI(anim, tex) { 0, anim, 0.0f, 0.0f, -1, 1, 5, { 0, 0xFF }, tex, { 0, 0, 0 }, 0.0f, 0, 1, 0 }
#define CH_SPANI_END { 3, 0, 0.0f, 0.0f, 0, 0, 0, { 0, 0 }, 0, { 0, 0, 0 }, 0.0f, 0, 0, 0 }

struct TexArchive;

// Texture archive after convertTextureHeader: a count followed by 0x20-byte image records.
typedef struct ChTexArchive {
    /*0x0*/ u32 count;
    /*0x4*/ u8 images[1][0x20]; // struct TexImage records
} ChTexArchive;

// ParticleParams5 (main/file_800263FC.h): spawn parameters of the type-5
// emitters (fn_80030D88, fn_80031CA4). Fixed point x100000.
typedef struct ChParticleParams5 {
    /* 0x00 */ struct TexArchive* tex;
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
} ChParticleParams5; // size: 0x50

// ParticleParamsC (main/file_800263FC.h): spawn parameters of fn_8002955C.
typedef struct ChParticleParamsC {
    /* 0x00 */ struct TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 unk8[(0x54 - 0x08) / 4];
} ChParticleParamsC; // size: 0x54

// ParticleParams (main/file_800263FC.h): trail spawn template (fn_8002F258).
typedef struct ChParticleParams {
    /* 0x00 */ struct TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 size;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 life;
    /* 0x18 */ s32 unk18[(0x44 - 0x18) / 4];
} ChParticleParams; // size: 0x44

// ParticleParamsB (main/file_800263FC.h): spawn template of fn_800324EC.
typedef struct ChParticleParamsB {
    /* 0x00 */ struct TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 unk8[(0x50 - 0x08) / 4];
} ChParticleParamsB; // size: 0x50

#endif
