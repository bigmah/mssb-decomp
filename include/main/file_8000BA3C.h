#ifndef __MAIN_FILE_8000BA3C_H__
#define __MAIN_FILE_8000BA3C_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

typedef struct Vec2f {
    f32 x;
    f32 y;
} Vec2f;

// A 2D quad: four corner points given as x/y pairs, transformed in place into
// 3D points (stride 0x10).
typedef struct QuadPoint {
    Vec pos;
    f32 pad;
} QuadPoint;

typedef union SpriteQuad {
    f32 xy[4][2];
    QuadPoint pt[4];
} SpriteQuad;

// Per-draw parameters: integer offsets for the four corners, then their colors.
typedef struct SpriteDrawParams {
    /* 0x00 */ s32 ofs[4][2];
    /* 0x20 */ u32 color[4];
    /* 0x30 */ f32 radius2; // second ring radius
    /* 0x34 */ u16 segments; // circle segment count
    /* 0x36 */ u8 arcSegments; // when non-zero, only draw this many segments
} SpriteDrawParams;

// One vertex of the quad being built in lbl_80366188.
typedef struct QuadVtx {
    /* 0x00 */ Vec pos;
    /* 0x0C */ u32 color;
    /* 0x10 */ s16 s;
    /* 0x12 */ s16 t;
} QuadVtx; // size 0x14

// Texture info record in a sprite bank (0x20 bytes, starting at bank + 4).
typedef struct SpriteTexInfo {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ u16 height;
    /* 0x0A */ u16 width;
    /* 0x0C */ u8 padC[0x10];
    /* 0x1C */ u16 texIndex; // index of the record holding the image
    /* 0x1E */ u8 pad1E[2];
} SpriteTexInfo;

typedef struct SpriteBank {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ SpriteTexInfo tex[1]; // variable length
} SpriteBank;

// Generic sprite element header.
typedef struct SpriteElem {
    /* 0x00 */ u8 unk0_b0 : 4;
    /* 0x00 */ u8 type : 4;
    /* 0x01 */ u8 flipX : 1;
    /* 0x01 */ u8 flipY : 1;
    /* 0x01 */ u8 unk1_b2 : 1;
    /* 0x01 */ u8 perCorner : 1; // per-corner vertex colors
    /* 0x01 */ u8 unk1_b4 : 4;
    /* 0x02 */ u16 texIdx;
} SpriteElem;

// Sprite rectangle element.
typedef struct SpriteRectElem {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ u16 texIdx;
    /* 0x08 */ u8 flipX : 1;
    /* 0x08 */ u8 flipY : 1;
    /* 0x08 */ u8 perCorner : 1; // per-corner vertex colors
    /* 0x08 */ u8 unk8_b4 : 5;
} SpriteRectElem;

// Filled circle element.
typedef struct CircleElem {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 z;
    /* 0x1C */ u8 pad1C[0xD];
    /* 0x29 */ u8 hidden : 1;
    /* 0x29 */ u8 unk29_b1 : 7;
} CircleElem;

// Circle element (screen-space variant).
typedef struct Circle2DElem {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ s16 x;
    /* 0x16 */ s16 y;
    /* 0x18 */ u8 pad18[0xD];
    /* 0x25 */ u8 hidden : 1;
    /* 0x25 */ u8 unk25_b1 : 7;
} Circle2DElem;

// Keyframe animation data.
typedef enum AnimEntryType {
    ANIM_ENTRY_FULL = 0,   // full parameter block (block->size bytes, starting at the block's first entry)
    ANIM_ENTRY_RAW = 1,    // anim->paramCount words
    ANIM_ENTRY_SPARSE = 2, // indexed words patched over the base entry
    ANIM_ENTRY_SPANS = 3,  // byte spans patched over the base entry
} AnimEntryType;

typedef struct AnimEntry {
    /* 0x00 */ u16 type; // bit 15: flag, low 15 bits: AnimEntryType
    /* 0x02 */ u16 time;
    /* 0x04 */ u16 count; // SPARSE/SPANS: number of patches
    /* 0x06 */ u16 size;  // SPARSE/SPANS: entry size in words
    /* 0x08 */ u16 data[1]; // SPARSE: word indices; SPANS: (byte offset, length) pairs
} AnimEntry;

typedef struct AnimBlock {
    /* 0x00 */ u16 count; // number of entries
    /* 0x02 */ u16 size;  // size of a FULL entry in bytes
    /* 0x04 */ AnimEntry entries[1];
} AnimBlock;

typedef struct AnimTrack {
    /* 0x00 */ u32 count; // bit 31: flag, low 31 bits: number of blocks (including loops)
    /* 0x04 */ u32 unk4;
    /* 0x08 */ u16* loops;
    /* 0x0C */ AnimBlock* blocks[1];
} AnimTrack;

typedef struct AnimTrackTable {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ AnimTrack* tracks[1];
} AnimTrackTable;

typedef struct Anim {
    /* 0x00 */ u8 pad0[5];
    /* 0x05 */ u8 paramCount; // words per decoded frame
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ AnimTrackTable* table;
} Anim;

// Quad being assembled for drawing.
typedef struct QuadState {
    /* 0x00 */ QuadVtx v[4];
    /* 0x50 */ u8 pad50[0x14];
    /* 0x64 */ void* unk64;
    /* 0x68 */ void* unk68;
    /* 0x6C */ void* unk6C;
    /* 0x70 */ SpriteBank* bank;
    /* 0x74 */ u8 pad74[4];
    /* 0x78 */ void* elem;
    /* 0x7C */ u16 perCornerColor;
    /* 0x7E */ u8 unk7E;
    /* 0x7F */ u8 unk7F;
    /* 0x80 */ u8 pad80[8];
    /* 0x88 */ void (*callback)(struct QuadState*, Mtx);
    /* 0x8C */ u8 pad8C[4];
} QuadState; // size 0x90

extern QuadState lbl_80366188;
extern SpriteTexInfo* lbl_803CBBD8;

void fn_8000E7BC(SpriteElem* elem, Mtx mtx, SpriteDrawParams* params, s32 perCorner);
void SetSpriteRect(SpriteRectElem* elem, SpriteBank* bank, Mtx mtx, SpriteDrawParams* params, s32 perCorner);
void fn_8000EC0C(SpriteElem* elem, SpriteBank* bank, Mtx mtx, SpriteDrawParams* params, s32 perCorner);
void fn_8000E030(CircleElem* elem, Mtx mtx, SpriteDrawParams* params);
void fn_8000E2D4(Circle2DElem* elem, Mtx mtx, SpriteDrawParams* params);
void fn_8000DC9C(Circle2DElem* elem, Mtx mtx, SpriteDrawParams* params);
void fn_8000D8A4(CircleElem* elem, Mtx mtx, SpriteDrawParams* params);
BOOL fn_8000CEF0(Anim* anim, s32 trackIdx, u32 blockIdx, s32 entryIdx, u32* out);
void fn_8000CC4C(Anim* anim, AnimBlock* block, u8* src, u32 ofs, u32 len);
void fn_8000E764(f32 angle, Vec2f* out);
void AddVec2iToQuad(SpriteQuad* quad, Mtx mtx, SpriteDrawParams* params);

#endif
