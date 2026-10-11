#ifndef __MAIN_FILE_8003A688_H__
#define __MAIN_FILE_8003A688_H__

#include "mssbTypes.h"
#include "Dolphin/OS/OSUtil.h"
#include "main/file_80069BDC.h"

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

extern OSTime lbl_802D4AE0[4];

// One challenge-mode save in the card image.
typedef struct SaveChallengeBlock {
    /*0x0*/ u16 crc; // CRC-16 of data
    /*0x2*/ u16 _2;
    /*0x4*/ u8 data[0x4508];
} SaveChallengeBlock; // size: 0x450C

// Memory card save image (lbl_802D4B00); starts with the card comment header.
typedef struct SaveImage {
    /*0x000*/ char comment[2][0x20];
    /*0x040*/ u16 cardCrc;
    /*0x042*/ u16 _42;
    /*0x044*/ u16 crc; // CRC-16 of _48 .. _5F4
    /*0x046*/ u16 _46;
    /*0x048*/ u8 _48[0x36];
    /*0x07E*/ u8 _7E[0x10];
    /*0x08E*/ u8 _8E[3];
    /*0x091*/ u8 _91[3];
    /*0x094*/ u8 soundMode;
    /*0x095*/ u8 _95;
    /*0x096*/ u8 _96;
    /*0x097*/ u8 _97[0xF7];
    /*0x18E*/ u8 _18E[2];
    /*0x190*/ u8 _190[0x454];
    /*0x5E4*/ u8 _5E4;
    /*0x5E5*/ u8 _5E5[6];
    /*0x5EB*/ u8 _5EB[6];
    /*0x5F1*/ u8 _5F1[3];
    /*0x5F4*/ s32 _5F4;
    /*0x5F8*/ SaveChallengeBlock challenge[3];
} SaveImage;

extern SaveImage lbl_802D4B00;

// Saved progress (lbl_80354768): three challenge saves plus shared records.
typedef struct SaveProgress {
    /*0x0000*/ u8 challenge[3][0x4508];
    /*0xCF18*/ u8 _CF18[0x36];
    /*0xCF4E*/ u8 _CF4E[0x10];
    /*0xCF5E*/ u8 _CF5E[3];
    /*0xCF61*/ u8 _CF61[3];
} SaveProgress; // size: 0xCF64

extern SaveProgress lbl_80354768;

// Save/load dialog state (lbl_803C50E8), driven by fn_8004A34C.
typedef struct SaveDialog {
    /*0x00*/ u8 _00[0x3E];
    /*0x3E*/ u8 status;
    /*0x3F*/ u8 msg;
    /*0x40*/ u8 port;
    /*0x41*/ u8 mode;
    /*0x42*/ u8 _42[2];
    /*0x44*/ u8 _44;
    /*0x45*/ u8 choice;
    /*0x46*/ u8 _46;
    /*0x47*/ u8 _47;
    /*0x48*/ u8 _48;
    /*0x49*/ u8 _49;
    /*0x4A*/ u16 _4A;
    /*0x4C*/ u8 _4C;
    /*0x4D*/ u8 _4D;
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 _4F;
    /*0x50*/ u16 _50;
    /*0x52*/ u8 _52;
    /*0x53*/ u8 _53;
    /*0x54*/ u32 badMask; // blocks whose CRC failed (bit 0 = shared, 1..3 = challenge saves)
    /*0x58*/ u8 _58[4];
} SaveDialog; // size: 0x5C

extern SaveDialog lbl_803C50E8;
extern s32 lbl_803CBC48;
extern s32 lbl_803CBC4C;
extern s32 lbl_803CBC50;

void fn_8003A688(s32 type, f32 speed, f32 spread);
void fn_8003A6B0(s32 type, TexDesc* desc, f32 speed, f32 spread);
void fn_8003A85C(u8 enabled);
void fn_8003AC90(void);
void fn_8003AD84(TexSet* set);
void fn_8003F23C(void);
void fn_8003F2B8(void);
void fn_8003BF54(u8 a, u8 b, u8 slot, u8 c, u8 d, u8 e, u8 f, u8 g, u8 h);
void fn_8003C00C(void);
s32 fn_80040FE0(SaveImage* img);
u8 fn_80041074(SaveImage* img, s32 length, u32 mask);
void fn_80041150(u8 mask, u8 slot);
s32 fn_80041348(void);
void fn_8004153C(void);

void fn_8003A848(u8 red, u8 green, u8 blue);

u8 fn_8003AE54(void);

void fn_8003AE5C(u8 value);

void fn_8003AE64(void);

u8 fn_8003AE70(s32 selector);

s32 fn_8004157C(void);

void fn_800415A0(u16 value);

#endif
