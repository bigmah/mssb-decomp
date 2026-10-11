#ifndef __MAIN_FILE_80039AC0_H__
#define __MAIN_FILE_80039AC0_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// Full-screen copy / blur effect state (lbl_803C5090).
typedef struct ScreenFx {
    /*0x00*/ f32 scale;
    /*0x04*/ f32 unk4;
    /*0x08*/ f32 jitterX;
    /*0x0C*/ f32 jitterY;
    /*0x10*/ u16 width;    // copy size
    /*0x12*/ u16 height;
    /*0x14*/ u16 lines;    // visible height (0x1C0)
    /*0x16*/ u8 _16;
    /*0x17*/ u8 alpha;
    /*0x18*/ u8 unk18;
    /*0x19*/ u8 repeat;
    /*0x1A*/ u8 r;
    /*0x1B*/ u8 g;
    /*0x1C*/ u8 b;
    /*0x1D*/ u8 flags;
    /*0x1E*/ u8 _1E[2];
} ScreenFx; // size 0x20

typedef struct ScreenFxNode {
    /*0x00*/ u32 link;
    /*0x04*/ void (*func)(struct ScreenFxNode* node);
    /*0x08*/ ScreenFx fx;
} ScreenFxNode; // size 0x28

// Texture descriptor used by DrawSprite_TexObj / SetDisplayStateTexture.
typedef struct TexDesc {
    /*0x00*/ void* image;
    /*0x04*/ u32 _04;
    /*0x08*/ u16 height;
    /*0x0A*/ u16 width;
    /*0x0C*/ u8 _0C[0x20 - 0x0C];
} TexDesc; // size 0x20

typedef struct SpriteVertex {
    /*0x00*/ f32 x;
    /*0x04*/ f32 y;
    /*0x08*/ f32 z;
    /*0x0C*/ u32 color;
    /*0x10*/ u16 s;
    /*0x12*/ u16 t;
} SpriteVertex; // size 0x14

typedef struct TrailEntry {
    /*0x00*/ Vec pos;
    /*0x0C*/ Vec dir;
    /*0x18*/ Vec vel;
    /*0x24*/ u8 alpha;
    /*0x25*/ u8 type;
    /*0x26*/ u8 flag;
    /*0x27*/ u8 _27;
} TrailEntry; // size 0x28

typedef struct TrailParams {
    /*0x0*/ f32 speed;
    /*0x4*/ f32 spread;
} TrailParams;

// lbl_802D3D80
typedef struct TrailSystem {
    /*0x000*/ TrailEntry entries[64];
    /*0xA00*/ u16 head;
    /*0xA02*/ u16 tail;
    /*0xA04*/ u8 _A04[0xCC0 - 0xA04];
    /*0xCC0*/ u8 texMode[13]; // 0 none, 1 direct, 2 color-indexed
    /*0xCCD*/ u8 _CCD[3];
    /*0xCD0*/ TrailParams params[13];
    /*0xD38*/ u8 enabled;
    /*0xD39*/ u8 _D39[7];
} TrailSystem; // size 0xD40

void fn_80039AC0(void);
void fn_80039FF8(ScreenFxNode* node);
void fn_8003A090(void);
void fn_8003A144(void);
void fn_8003A1D0(void);
void fn_8003A2C0(void);
void fn_8003A2EC(void);
void fn_8003A37C(Mtx mtx, s32* stage, s32* coord, s32* map, u8* count, u8* texMtx);
void fn_8003A4C8(void);

u32 fn_8003A538(void);

void fn_8003A540(u32 value);

void fn_8003A548(u32 value);

void fn_8003A550(s32 type, Vec* pos, Vec* dir, u8 flag);

#endif
