#ifndef __MAIN_FILE_80024D2C_H__
#define __MAIN_FILE_80024D2C_H__

#include "mssbTypes.h"

// Shape (vertex morph) animation: keyframed blending between morph targets
// that are written straight into a model's GX vertex arrays.

// One keyframe (4 bytes).
typedef struct ShapeKey {
    /*0x0*/ u16 ease : 1;     // weight comes from `weight` instead of 0/1
    /*0x0*/ u16 hold : 1;     // don't blend toward the next key
    /*0x0*/ u16 override : 1; // target index may be overridden by the caller
    /*0x0*/ u16 unk0_3 : 1;
    /*0x0*/ u16 frame : 12;
    /*0x2*/ u8 weight;        // percent
    /*0x3*/ u8 target;        // morph target index
} ShapeKey;

typedef struct ShapeSeqHdr {
    /*0x0*/ u16 length;
    /*0x2*/ u16 keyCount;
} ShapeSeqHdr;

typedef struct ShapeSeq {
    /*0x0*/ ShapeSeqHdr hdr;
    /*0x4*/ ShapeKey* keys;
} ShapeSeq;

// Sequence as stored in the asset: header followed by the keys.
typedef struct ShapeSeqData {
    /*0x0*/ ShapeSeqHdr hdr;
    /*0x4*/ ShapeKey keys[1];
} ShapeSeqData;

typedef struct ShapeAnimState {
    /*0x00*/ f32 frame;
    /*0x04*/ f32 speed;
    /*0x08*/ u16 unk8;
    /*0x0A*/ u16 seqIdx;
    /*0x0C*/ u16 keyIdx;
    /*0x0E*/ s16 loops; // < 0: forever
    /*0x10*/ u8 unk10;
    /*0x11*/ u8 active : 1;
    /*0x11*/ u8 dirtyA : 2; // per frame buffer (bit = lbl_803CBBC0 != 0)
    /*0x11*/ u8 dirtyB : 2;
    /*0x11*/ u8 unk11_5 : 3;
    /*0x14*/ u32 unk14;
    /*0x18*/ ShapeSeq seqs[1];
} ShapeAnimState;

// Asset header for fn_80025FFC (offsets relocated in place).
typedef struct ShapeAnimSet {
    /*0x0*/ u32 seqCount;
    /*0x4*/ ShapeSeqData** seqs;
    /*0x8*/ s8** tables;
    /*0xC*/ u32 tableCount;
} ShapeAnimSet;

typedef struct ShapeAnimPlayer {
    /*0x00*/ ShapeAnimSet* set;
    /*0x04*/ ShapeSeqData** seqs;
    /*0x08*/ s8** tableList;
    /*0x0C*/ ShapeAnimState state;
    /*0x2C*/ void* model;
    /*0x30*/ s8* tables[10];
    /*0x58*/ s8 curIdx; // -128: none
    /*0x59*/ u8 unk59;
} ShapeAnimPlayer;

// Vertex attribute arrays of a model (0x10 each).
typedef struct VtxArray {
    /*0x0*/ void* data;
    /*0x4*/ u16 count;
    /*0x6*/ u8 unk6[0x10 - 0x6];
} VtxArray;

typedef struct VtxArraySet {
    /*0x0*/ VtxArray* pos;
    /*0x4*/ VtxArray* nrm;
    /*0x8*/ VtxArray* tex; // [type - 4]
    /*0xC*/ VtxArray* clr;
} VtxArraySet;

typedef struct VtxArraySetRef {
    /*0x0*/ VtxArraySet* set;
    /*0x4*/ u32 unk4;
} VtxArraySetRef;

typedef struct ModelVtxDesc {
    /*0x00*/ u8 unk0[0x10];
    /*0x10*/ VtxArraySetRef* sets;
} ModelVtxDesc;

typedef struct ModelGeoArray {
    /*0x00*/ u8 unk0[0x30];
    /*0x30*/ void* data;
    /*0x34*/ u8 unk34[0x42 - 0x34];
    /*0x42*/ u16 count;
} ModelGeoArray;

typedef struct ModelGeoA {
    /*0x00*/ u8 unk0[0x30];
    /*0x30*/ void* data;
} ModelGeoA;

typedef struct ModelGeoB {
    /*0x00*/ u8 unk0[0x60];
    /*0x60*/ void* data;
} ModelGeoB;

typedef struct ModelGeo {
    /*0x00*/ u8 unk0[0x8];
    /*0x08*/ ModelGeoA* a;
    /*0x0C*/ ModelGeoB* b;
    /*0x10*/ ModelGeoArray* arrays; // 0x44 each
} ModelGeo;

typedef struct ShapeModel {
    /*0x00*/ u8 unk0[0x10];
    /*0x10*/ ModelVtxDesc* vtxDesc;
    /*0x14*/ u8 unk14[0x7C - 0x14];
    /*0x7C*/ ModelGeo* geo;
} ShapeModel;

// Morph target: a vertex array of the model that gets written.
typedef struct ShapeTarget {
    /*0x0*/ u16 idx;
    /*0x2*/ u8 useBuf1 : 1;
    /*0x2*/ u8 type : 7;  // 0: geo array, 1: pos, 2: clr, 3: nrm, 4+: tex
    /*0x3*/ u8 fmtHi : 4; // components
    /*0x3*/ u8 fmtLo : 4; // component size
    /*0x4*/ void** dataSlot;
    /*0x8*/ void* buf[2];
} ShapeTarget;

typedef struct ShapeRange {
    /*0x0*/ u16 start;
    /*0x2*/ u16 count; // 0 terminates
} ShapeRange;

// Variable-size (ShapeGroup.entryStride) entry.
typedef struct ShapeEntry {
    /*0x0*/ u8 unk0[4];
    /*0x4*/ u8 id;
    /*0x5*/ u8 copyOnly : 1;
    /*0x5*/ u8 type : 7;
    /*0x6*/ u8 compCount;
    /*0x7*/ u8 compSize;
    /*0x8*/ ShapeRange* ranges;
    /*0xC*/ u8* src[1]; // per morph target
} ShapeEntry;

typedef struct ShapeGroup {
    /*0x0*/ u16 srcCount;
    /*0x2*/ u16 entryCount;
    /*0x4*/ u32 entryStride;
    /*0x8*/ ShapeEntry* entries;
} ShapeGroup;

typedef struct ShapeData {
    /*0x00*/ u16 unk0;
    /*0x02*/ u16 groupCount;
    /*0x04*/ u16 targetCount;
    /*0x06*/ u16 unk6;
    /*0x08*/ ShapeGroup* groups;
    /*0x0C*/ ShapeTarget* targets;
    /*0x10*/ ShapeModel** owner;
} ShapeData;

u32 fn_80024D2C(ShapeAnimState* st);
s32 fn_80024DB0(ShapeAnimState* st);
void fn_80025C58(ShapeData* shape, ShapeModel** model);

void fn_80026130(void);

void fn_80025DDC(u8* h);

#endif
