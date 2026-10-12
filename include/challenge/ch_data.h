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

#endif
