#ifndef __MAIN_FILE_80034F50_H__
#define __MAIN_FILE_80034F50_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// spani_default.c: 2D sprite animation ("Spani") system.

#define SPANI_OBJ_COUNT 0x360
#define SPANI_TEX_SLOT_COUNT 20
#define SPANI_TEX_OVERRIDE_COUNT 10

// One key of an animation track (0x50 bytes).
typedef struct SpaniKey {
    /*0x00*/ u16 type; // low 15 bits
    /*0x02*/ u16 unk2;
    /*0x04*/ u8 enabled;
    /*0x05*/ u8 unk5;
    /*0x06*/ u16 texIdx;
    /*0x08*/ u8 unk8[0x14 - 0x08];
    /*0x14*/ s16 x;
    /*0x16*/ s16 y;
    /*0x18*/ u8 unk18[0x1C - 0x18];
    /*0x1C*/ s32 unk1C;
    /*0x20*/ u8 unk20[0x50 - 0x20];
} SpaniKey;

typedef struct SpaniTrack {
    /*0x0*/ u16 keyCount;
    /*0x2*/ u16 unk2;
    /*0x4*/ SpaniKey keys[1]; // keyCount entries
} SpaniTrack;

typedef struct SpaniSeq {
    /*0x0*/ u32 trackCount; // bit 31 is a flag
    /*0x4*/ u32 unk4;
    /*0x8*/ SpaniTrack* tracks[1]; // trackCount entries
} SpaniSeq;

typedef struct SpaniSeqList {
    /*0x0*/ u32 count;
    /*0x4*/ u32 unk4;
    /*0x8*/ SpaniSeq* seqs[1]; // count entries
} SpaniSeqList;

typedef struct SpaniAnim {
    /*0x0*/ u16 width;
    /*0x2*/ u16 height;
    /*0x4*/ u8 unk4;
    /*0x5*/ u8 unk5;
    /*0x6*/ u16 unk6;
    /*0x8*/ SpaniSeqList* seqList;
    /*0xC*/ void* unkC;
} SpaniAnim;

// A loaded texture + animation bank (0x3C bytes).
typedef struct SpaniTexSlot {
    /*0x00*/ Mtx mtx;
    /*0x30*/ void* data;
    /*0x34*/ void* tex;
    /*0x38*/ SpaniAnim* anim;
} SpaniTexSlot;

// One sprite instance (0xC0 bytes).
typedef struct SpaniObj {
    /*0x00*/ void* parent;
    /*0x04*/ s32 unk4;
    /*0x08*/ s32 unk8;
    /*0x0C*/ Mtx mtx;
    /*0x3C*/ f32 posX;
    /*0x40*/ f32 posY;
    /*0x44*/ f32 posZ;
    /*0x48*/ f32 baseX;
    /*0x4C*/ f32 baseY;
    /*0x50*/ f32 baseZ;
    /*0x54*/ u32 flags;
    /*0x58*/ s32 unk58;
    /*0x5C*/ u32 frame; // 16.16 fixed point
    /*0x60*/ u32 frameStep;
    /*0x64*/ u16 animId;
    /*0x66*/ u8 texSlot;
    /*0x67*/ u8 layer;
    /*0x68*/ u8 playMode;
    /*0x69*/ u8 animResult;
    /*0x6A*/ u8 unk6A[2];
    /*0x6C*/ f32 scale;
    /*0x70*/ u8 is3D;
    /*0x71*/ u8 unk71;
    /*0x72*/ s16 unk72;
    /*0x74*/ s32 unk74;
    /*0x78*/ Mtx mtx2;
    /*0xA8*/ u8 unkA8;
    /*0xA9*/ u8 unkA9[3];
    /*0xAC*/ u16 texOverride[SPANI_TEX_OVERRIDE_COUNT];
} SpaniObj;

typedef struct SpaniRef {
    /*0x0*/ SpaniObj* obj;
    /*0x4*/ s32 unk4;
} SpaniRef;

// Creation parameters for fn_80034F50.
typedef struct SpaniDesc {
    /*0x00*/ u16 type;
    /*0x02*/ u16 animId;
    /*0x04*/ f32 x;
    /*0x08*/ f32 y;
    /*0x0C*/ s32 unkC;
    /*0x10*/ u8 playMode;
    /*0x11*/ u8 layer;
    /*0x12*/ u8 unk12[2];
    /*0x14*/ u8 texId;
    /*0x15*/ u8 unk15[3];
    /*0x18*/ f32 scale;
    /*0x1C*/ u8 is3D;
    /*0x1D*/ u8 unk1D;
    /*0x1E*/ s16 unk1E;
} SpaniDesc;

// Anything that owns a run of sprites in lbl_80371C30 starting at baseIdx.
typedef struct SpaniOwner {
    /*0x00*/ u8 unk0[0x14];
    /*0x14*/ u16 baseIdx;
} SpaniOwner;

SpaniObj* fn_80034F50(SpaniDesc* desc);
void fn_800356B8(void);
void fn_80035A00(void);
void fn_80035B50(int id);
void fn_80035CA4(s32 id);
s32 fn_80035DD4(s32 id);
void fn_80035ED0(s32 idx);
void fn_80035EEC(u16 frame, s32 idx);
void fn_80036134(SpaniOwner* owner, s32 srcIdx, u32 track, s32 dstIdx);
s32 fn_80036214(SpaniOwner* owner, s32 idx, u32 track, u32 frame);
void fn_80036270(SpaniOwner* owner, s32 idx, u32 track, u32 frame, s16* outX, s16* outY);
void fn_800362F0(SpaniOwner* owner, s32 idx);
void fn_800363D8(SpaniOwner* owner, s32 idx, u32 slot, u16 animId, u32 frame);
void fn_800369DC(f32 zoom);
void fn_80036A3C(void);
s32 fn_80036C88(s32* src, s32* dst);

#endif
