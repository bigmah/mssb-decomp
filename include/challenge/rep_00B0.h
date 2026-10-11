#ifndef __CHALLENGE_REP_00B0_H_
#define __CHALLENGE_REP_00B0_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "main/file_800A1A70.h"

// Debug drawing / ray casting against the challenge stage collision mesh.

// One collision vertex (size 0x10).
typedef struct ChalColVtx {
    /* 0x0 */ Vec pos;
    /* 0xC */ u16 id; // surface id, also selects the debug color
    /* 0xE */ u16 pad;
} ChalColVtx;

// A block of collision geometry. Blocks follow each other in memory; a header
// word of 0 ends the list. isStrip == 0: count triangles (count * 3 vertices),
// otherwise a triangle strip of count + 2 vertices.
typedef struct ChalColBlock {
    union {
        struct {
            /* 0x0 */ u8 unk0;
            /* 0x1 */ u8 isStrip;
            /* 0x2 */ u16 count;
        } h;
        u32 word;
    } hdr;
    /* 0x4 */ ChalColVtx v[1]; // variable length
} ChalColBlock;

// Axis-aligned bounding box of a collision block (size 0x18).
typedef struct ChalColBox {
    /* 0x00 */ Vec min;
    /* 0x0C */ Vec max;
} ChalColBox;

typedef struct ChalColModel {
    /* 0x0 */ ChalColBox* boxes;
    /* 0x4 */ ChalColBlock* blocks[1]; // variable length
} ChalColModel;

// Ray cast state (ray along +z in the space of mtx).
typedef struct ChalRayCast {
    /* 0x00 */ Mtx mtx;
    /* 0x30 */ u8 unk30[0x30];
    /* 0x60 */ Vec normal;
    /* 0x6C */ f32 length;
    /* 0x70 */ f32 dist;
    /* 0x74 */ u16 hitId;
} ChalRayCast;

void fn_1_19AC(void);
void fn_1_1BF8(ChalColBox* boxes, s32 index);
void fn_1_1DBC(s32 a, s32 b, s32 c, s32 d, s8 color);
void fn_1_25BC(ChalColBlock* block);
void fn_1_3E38(Vec* pos, u32 id);
void fn_1_4074(Vec* pos);
void fn_1_4290(Vec* line);
u32 fn_1_4728(Vec* ray, Vec* out);
void fn_1_4A24(ChalRayCast* ray, ChalColBlock* block);

#endif
