#ifndef _DOLPHIN_CP_UNKTYPES_H_
#define _DOLPHIN_CP_UNKTYPES_H_

// uncategorized types go in here.

#include "Dolphin/gx.h"

#include "charPipeline/texPalette.h"

typedef struct {
    /* 0x00 */ char *positionArray;
    /* 0x04 */ u16 numPositions;
    /* 0x06 */ u8 quantizeInfo;
    /* 0x07 */ u8 compCount;
} PositionData;

typedef struct {
    /* 0x00 */ char * colorArray;
    /* 0x04 */ u16 numColors;
    /* 0x06 */ u8 quantizeInfo;
    /* 0x07 */ u8 compCount;
} ColorData;

typedef struct {
    /* 0x00 */ u32 versionNumber;
    /* 0x04 */ u32 userDataSize;
    /* 0x08 */ void *userData;
    /* 0x0C */ u32 numDescriptors;
    /* 0x10 */ TEXDescriptorPtr descriptorArray;
} TEXPaletteData, *TEXPaletteDataPtr;

// MSSB texture bank (same layout as the sprite banks): a u32 header then 0x20-byte texture records.
typedef struct DOTexInfo {
    /* 0x00 */ void * image;
    /* 0x04 */ void * tlut; // NULL unless colour-indexed
    /* 0x08 */ u16 height;
    /* 0x0A */ u16 width;
    /* 0x0C */ u8 pad0C[2];
    /* 0x0E */ u8 minFilter;
    /* 0x0F */ u8 magFilter;
    /* 0x10 */ f32 lodBias;
    /* 0x14 */ u8 pad14;
    /* 0x15 */ u8 minLOD;
    /* 0x16 */ u8 maxLOD;
    /* 0x17 */ u8 format;
    /* 0x18 */ u16 tlutEntries;
    /* 0x1A */ u8 tlutFormat;
    /* 0x1B */ u8 pad1B;
    /* 0x1C */ u16 texIndex; // index of the record holding the image
    /* 0x1E */ u16 pad1E;
} DOTexInfo;

typedef struct DOTexBank {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ DOTexInfo tex[1]; // variable length
} DOTexBank;

typedef struct {
    /* 0x00 */ char * textureCoordArray;
    /* 0x04 */ u16 numTextureCoords;
    /* 0x06 */ u8 quantizeInfo;
    /* 0x07 */ u8 compCount;
    /* 0x08 */ char * texturePaletteName;
    /* 0x0C */ DOTexBank * texturePalette;
} TextureData;

typedef struct {
    /* 0x00 */ char * normalArray;
    /* 0x04 */ u16 numNormals;
    /* 0x06 */ u8 quantizeInfo;
    /* 0x07 */ u8 compCount;
    /* 0x08 */ f32 ambientPercentage;
} LightingData;

typedef struct {
    /* 0x00 */ u8 id;
    /* 0x01 */ u8 pad8;
    /* 0x02 */ u16 pad16;
    /* 0x04 */ u32 setting;
    /* 0x08 */ char * primitiveList;
    /* 0x0C */ u32 listSize;
} DisplayStateList;

typedef struct {
    /* 0x00 */ char * primitiveBank;
    /* 0x04 */ DisplayStateList * displayStateList;
    /* 0x08 */ u16 numStateEntries;
    /* 0x0A */ u16 pad16;
} DisplayData;

typedef struct KeyFrame {
    /* 0x00 */ f32 time;
    /* 0x04 */ char * setting;
    /* 0x08 */ char * interpolation;
} KeyFrame;

typedef struct {
    /* 0x00 */ char * Prev;
    /* 0x04 */ char * Next;
    /* 0x08 */ char * Parent;
    /* 0x0C */ char * Children;
} Branch;

#endif // _DOLPHIN_CP_UNKTYPES_H_
