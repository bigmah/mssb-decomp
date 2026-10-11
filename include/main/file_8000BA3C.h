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
    /* 0x00 */ void* image;
    /* 0x04 */ void* tlut;      // palette, NULL if none
    /* 0x08 */ u16 height;
    /* 0x0A */ u16 width;
    /* 0x0C */ u8 wrapS;        // GXTexWrapMode
    /* 0x0D */ u8 wrapT;
    /* 0x0E */ u8 minFilter;    // GXTexFilter
    /* 0x0F */ u8 magFilter;
    /* 0x10 */ f32 lodBias;
    /* 0x14 */ u8 pad14;
    /* 0x15 */ u8 minLod;
    /* 0x16 */ u8 maxLod;
    /* 0x17 */ u8 format;       // GXTexFmt
    /* 0x18 */ u16 tlutCount;   // palette entries
    /* 0x1A */ u8 tlutFormat;   // GXTlutFmt
    /* 0x1B */ u8 pad1B;
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

// Loop marker in a track's loop table (count at +0, markers from +4).
typedef struct AnimLoop {
    /* 0x00 */ u16 end;
    /* 0x02 */ u16 mode; // 0: wrap to 0, 2: wrap to start
    /* 0x04 */ u16 start;
    /* 0x06 */ u8 pad6[6];
} AnimLoop;

// A decoded animation frame (anim->paramCount words).
typedef struct AnimFrame {
    /* 0x00 */ u16 type;
    /* 0x02 */ u16 time;
    /* 0x04 */ u8 kind; // what to draw; 3: nested track
    /* 0x05 */ u8 blend; // 0..2: blend mode 1..3
    /* 0x06 */ u16 subTrack; // nested track, or texture index for sprites
    /* 0x08 */ u8 flags; // bit 0: perspective scale, bit 3: draw callback, bit 4: curved path, bit 5: per-corner colors
    /* 0x09 */ u8 flags2; // bit 7: fn_800B1188
    /* 0x0A */ u8 padA[6];
    /* 0x10 */ s16 x;
    /* 0x12 */ s16 y;
    /* 0x14 */ u8 pad14[4];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8 pad1A[0x36];
} AnimFrame; // size 0x50

typedef struct AnimTrackTable {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ AnimTrack* tracks[1];
} AnimTrackTable;

typedef struct Anim {
    /* 0x00 */ u8 pad0[5];
    /* 0x05 */ u8 paramCount; // words per decoded frame
    /* 0x06 */ u16 unk6; // 0: old format (fn_8000D164)
    /* 0x08 */ AnimTrackTable* table;
    /* 0x0C */ void* unkC; // passed to fn_8000AF1C
} Anim;

// Old-format (anim->unk6 == 0) keyframe: an uncompressed sprite element.
typedef struct AnimKeyV0 {
    /* 0x00 */ u8 blend : 4; // 0..2: blend mode 1..3
    /* 0x00 */ u8 kind : 4;  // 1, 2: quad, 3: circle, 4: sprite, 5: nested track
    /* 0x01 */ u8 flipX : 1;
    /* 0x01 */ u8 flipY : 1;
    /* 0x01 */ u8 linked : 1; // continues the previous key's segment
    /* 0x01 */ u8 perCorner : 1;
    /* 0x01 */ u8 curved : 1;
    /* 0x01 */ u8 useCallback : 1;
    /* 0x01 */ u8 unk1_b6 : 2;
    /* 0x02 */ u16 subTrack; // nested track, or texture index for sprites
    /* 0x04 */ u8 pad4[8];
    /* 0x0C */ u16 time;
    /* 0x0E */ u8 padE[0x1A];
} AnimKeyV0; // size 0x28

typedef struct AnimBlockV0 {
    /* 0x00 */ u16 count;
    /* 0x02 */ u16 pad2;
    /* 0x04 */ AnimKeyV0 keys[1];
} AnimBlockV0;

// Quad being assembled for drawing.
// Circle parameters handed to the draw callback instead of vertices.
typedef struct QuadCircle {
    /* 0x00 */ Mtx mtx;
    /* 0x30 */ u8 pad30[0x10];
    /* 0x40 */ f32 radius;
    /* 0x44 */ f32 radius2;
    /* 0x48 */ u32 color0;
    /* 0x4C */ u32 color1;
    /* 0x50 */ s16 x;
    /* 0x52 */ s16 y;
    /* 0x54 */ u8 segments;
    /* 0x55 */ u8 arcSegments;
} QuadCircle;

typedef struct QuadState {
    /* 0x00 */ union {
        QuadVtx v[4];
        QuadCircle circle;
    } u;
    /* 0x58 */ u8 pad58[0xC];
    /* 0x64 */ f32 (*mtx)[4];
    /* 0x68 */ u32 color;
    /* 0x6C */ s16* path;
    /* 0x70 */ SpriteBank* bank;
    /* 0x74 */ u8 pad74[4];
    /* 0x78 */ void* elem;
    /* 0x7C */ u16 perCornerColor;
    /* 0x7E */ u8 unk7E;
    /* 0x7F */ u8 unk7F;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ s32 (*drawCallback)(struct QuadState*); // returns whether to draw
    /* 0x88 */ void (*callback)(struct QuadState*, Mtx);
    /* 0x8C */ u8 pad8C[4];
} QuadState; // size 0x90

extern QuadState lbl_80366188;

typedef struct MtxBox {
    Mtx m;
} MtxBox;
extern const MtxBox lbl_800E65D0; // zero matrix
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
s32 fn_8000BA3C(u32* time, Anim* anim, s32 trackIdx, Mtx mtx, s32 flags, u32 color, u16** outLoop, s16* path);
s32 fn_8000C194(u32* time, Anim* anim, s32 trackIdx, Mtx mtx, s32 flags, u32 color, u16** outLoop, SpriteBank* bank);
s32 fn_8000D164(u32* time, Anim* anim, s32 trackIdx, Mtx mtx, s32 flags, u32 color, u16** outLoop, SpriteBank* bank);
s32 fn_8000D838(u32* time, Anim* anim, s32 trackIdx, Mtx mtx, s32 flags, u32 color, u16** outLoop, SpriteBank* bank);
void fn_8000E764(f32 angle, Vec2f* out);
void AddVec2iToQuad(SpriteQuad* quad, Mtx mtx, SpriteDrawParams* params);

#endif
