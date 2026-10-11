#ifndef __MAIN_FILE_800BDEA0_H__
#define __MAIN_FILE_800BDEA0_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "main/file_800BD8C4.h"

// One shadow-casting light camera (0xE0 bytes).
typedef struct ShadowCamera {
    /* 0x00 */ Vec eye;
    /* 0x0C */ Vec up;
    /* 0x18 */ Vec target;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 near;
    /* 0x30 */ f32 far;
    /* 0x34 */ Vec dir;      // light direction
    /* 0x40 */ Mtx view;
    /* 0x70 */ Mtx44 proj;
    /* 0xB0 */ Mtx texMtx;   // light-space texture projection
} ShadowCamera;

typedef void (*ShadowBeginCallback)(void* arg);
typedef void (*ShadowDrawCallback)(ActorObject* obj, Mtx view);
typedef void (*ShadowEndCallback)(Mtx view, s32 arg);

// lbl_803009F8: shadow render state (0x50 bytes).
typedef struct ShadowState {
    /* 0x00 */ u8 enabled;
    /* 0x01 */ u8 numCameras;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ void** images;        // one texture image per camera
    /* 0x08 */ GXTexObj* texObjs;    // one per camera
    /* 0x0C */ GXTlutObj* tlut;
    /* 0x10 */ u16* tlutData;        // 16 IA8 entries
    /* 0x14 */ ShadowCamera* cameras;
    /* 0x18 */ ShadowBeginCallback beginCallback;
    /* 0x1C */ ShadowDrawCallback drawCallback;
    /* 0x20 */ ShadowEndCallback endCallback;
    /* 0x24 */ u16 numPoints;        // points accumulated into the bounds
    /* 0x26 */ u8 pad26[2];
    /* 0x28 */ f32 minX;
    /* 0x2C */ f32 maxX;
    /* 0x30 */ f32 minY;
    /* 0x34 */ f32 maxY;
    /* 0x38 */ f32 minZ;
    /* 0x3C */ f32 maxZ;
    /* 0x40 */ Vec sum;
    /* 0x4C */ u8 flags;             // bits 5-7 set by fn_800BDE8C
    /* 0x4D */ s8 upSign;
    /* 0x4E */ u8 pad4E[2];
} ShadowState;

extern ShadowState lbl_803009F8;

typedef struct SKAccBuffer {
    /* 0x00 */ void* src;
    /* 0x04 */ void* indices;
    /* 0x08 */ void* weights;
} SKAccBuffer;

// Skinning lists (game variant of the charPipeline skinning header).
// vertDst / skBzeroBase are byte offsets into the caller's vertex buffer.
typedef struct SKNBone {
    /* 0x00 */ u8 pad0[0xF0];
    /* 0xF0 */ MtxPtr skinMtx;
} SKNBone;

typedef struct SKN1List {
    /* 0x00 */ Mtx43 m;
    /* 0x30 */ void* vertSrc;
    /* 0x34 */ u32 vertDst;
    /* 0x38 */ u16 boneIndex;
    /* 0x3A */ u16 count;
    /* 0x3C */ u8 vertSrcOffset;
    /* 0x3D */ u8 pad3D[3];
} SKN1List;

typedef struct SKN2List {
    /* 0x00 */ Mtx43 m0;
    /* 0x30 */ Mtx43 m1;
    /* 0x60 */ void* vertSrc;
    /* 0x64 */ void* weights;
    /* 0x68 */ u32 vertDst;
    /* 0x6C */ u16 bone0Index;
    /* 0x6E */ u16 bone1Index;
    /* 0x70 */ u16 count;
    /* 0x72 */ u8 vertSrcOffset;
    /* 0x73 */ u8 pad73;
} SKN2List;

typedef struct SKNAccList {
    /* 0x00 */ Mtx43 m;
    /* 0x30 */ void* vertSrc;
    /* 0x34 */ void* vertIndices;
    /* 0x38 */ u32 vertDst;
    /* 0x3C */ void* weights;
    /* 0x40 */ u16 boneIndex;
    /* 0x42 */ u16 count;
} SKNAccList;

typedef struct SKNHeader {
    /* 0x00 */ u16 numSk1List;
    /* 0x02 */ u16 numSk2List;
    /* 0x04 */ u16 numSkAccList;
    /* 0x06 */ u8 posNrmShift;
    /* 0x07 */ u8 pad7;
    /* 0x08 */ SKN1List* sk1ListArray;
    /* 0x0C */ SKN2List* sk2ListArray;
    /* 0x10 */ SKNAccList* skAccListArray;
    /* 0x14 */ u32 skBzeroBase;
    /* 0x18 */ u32 skBzeroSize;
    /* 0x1C */ u16* flushIndices;
    /* 0x20 */ u32 flushCount;
} SKNHeader;

typedef struct TextureHeaderEntry {
    /* 0x00 */ void* data;     // file offset, relocated by convertTextureHeader
    /* 0x04 */ void* palette;  // file offset, relocated by convertTextureHeader
    /* 0x08 */ u8 pad8[0x14];
    /* 0x1C */ u16 index;
    /* 0x1E */ u8 pad1E[2];
} TextureHeaderEntry;

typedef struct TextureHeader {
    /* 0x00 */ u16 count;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ TextureHeaderEntry entries[1];  // count entries
} TextureHeader;

void fn_800BDEA0(void);
void fn_800BDF70(ActorObject* obj);
void fn_800BDFE0(ActorObjectTable* table);
void fn_800BE09C(void* arg, ShadowCamera* cam);
void fn_800BEA04(Vec point);

void fn_800BEB3C(void);

u8 fn_800BEBA0(void);

u8 GetDrawShadows(void);

MtxPtr fn_800BEB80(u8 index);

void DrawShadows(u8 enable);

void fn_800BEBCC(u8 index, Vec dir);

void fn_800BEC00(s32 reverse);

void fn_800BEC30(u8 numCameras);
void fn_800BF008(void);

void fn_800BF038(ShadowEndCallback callback);

void fn_800BF048(ShadowBeginCallback callback);

void fn_800BF058(ShadowDrawCallback callback);

ShadowState* fn_800BF068(void);

void SKNLoadFile(SKNHeader* hdr);
void SKNFlushByIndex1(u16* indices, u32 count, void* base);
void SKNFlushByIndex2(u16* indices, u32 count, void* base);
void SKNBzero32B(void* base, u32 size);
void SKNInit(void);
void fn_800BF2A8(SKNBone** bones, SKNHeader* hdr, u8* base);
void SKNIt(SKNBone** bones, SKNHeader* hdr, u8* base);
void SKN1Vecs16Norms16(Mtx43 m, f32* src, f32* dst, u32 count);
void fn_800BFF9C(Mtx43 m, s16* src, s16* dst, u32 count);
void SKN2Vecs16Norms16NoTouch(Mtx43 m0, Mtx43 m1, u8* weights, f32* src, f32* dst, u32 count);
void fn_800C02C8(Mtx43 m0, Mtx43 m1, u8* weights, s16* src, s16* dst, u32 count);
void SKNAccVecs16Norms16Iu161(Mtx43 m, u16 count, f32* src, f32* dst, u16* indices, u8* weights);
void SKNAccVecs16Norms16Iu162(Mtx43 m, u16 count, s16* src, s16* dst, u16* indices, u8* weights);
void convertTextureHeader(TextureHeader* hdr);
void fn_800C07BC(void* base, void* tmp, u32 count, u32 size, s32 (*compare)(void*, void*));

#endif
