#ifndef __MAIN_FILE_8003A688_H__
#define __MAIN_FILE_8003A688_H__

#include "mssbTypes.h"
#include "Dolphin/OS/OSUtil.h"

// Process-queue task used by the memory-card save/load state machines.
typedef struct SaveTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 _04[0x10 - 0x04];
    /*0x10*/ s16 result; // set by child tasks
    /*0x12*/ u16 priority;
    /*0x14*/ u8 state;
    /*0x15*/ u8 _15;
    /*0x16*/ u8 _16;
    /*0x17*/ u8 slot;
    /*0x18*/ u8 _18;
    /*0x19*/ u8 _19;
    /*0x1A*/ u8 _1A;
    /*0x1B*/ u8 _1B;
    /*0x1C*/ u8 _1C;
    /*0x1D*/ u8 _1D;
    /*0x1E*/ u8 _1E;
    /*0x1F*/ u8 _1F;
    /*0x20*/ u8 _20;
    /*0x21*/ u8 _21;
} SaveTask;

// Texture description passed to fn_8003A6B0.
typedef struct TrailTexDesc {
    /*0x00*/ void* image;
    /*0x04*/ void* tlut; // NULL for direct-color textures
    /*0x08*/ u16 height;
    /*0x0A*/ u16 width;
    /*0x0C*/ u8 wrapS;
    /*0x0D*/ u8 wrapT;
    /*0x0E*/ u8 minFilter;
    /*0x0F*/ u8 magFilter;
    /*0x10*/ f32 lodBias;
    /*0x14*/ u8 _14;
    /*0x15*/ u8 minLod;
    /*0x16*/ u8 maxLod;
    /*0x17*/ u8 format;
    /*0x18*/ u16 tlutCount;
    /*0x1A*/ u8 tlutFormat;
} TrailTexDesc;

extern OSTime lbl_802D4AE0[4];
extern s32 lbl_803CBC48;
extern s32 lbl_803CBC4C;
extern s32 lbl_803CBC50;

void fn_8003A688(s32 type, f32 speed, f32 spread);
void fn_8003A6B0(s32 type, TrailTexDesc* desc, f32 speed, f32 spread);
void fn_8003A85C(u8 enabled);
void fn_8003F23C(void);
void fn_8003F2B8(void);
void fn_8004153C(void);

void fn_8003A848(u8 red, u8 green, u8 blue);

u8 fn_8003AE54(void);

void fn_8003AE5C(u8 value);

void fn_8003AE64(void);

u8 fn_8003AE70(s32 selector);

s32 fn_8004157C(void);

void fn_800415A0(u16 value);

#endif
