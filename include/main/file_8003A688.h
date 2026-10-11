#ifndef __MAIN_FILE_8003A688_H__
#define __MAIN_FILE_8003A688_H__

#include "mssbTypes.h"
#include "main/file_80069BDC.h"
#include "main/file_8000F150.h"
#include "main/file_80024184.h"

// Vertex attribute array of a display-list model.
typedef struct ModelArray {
    /*0x00*/ void* data;
    /*0x04*/ u8 _04[2];
    /*0x06*/ u8 fmt;   // high nibble: GXCompType, low nibble: fraction bits
    /*0x07*/ u8 count; // components per vertex
    /*0x08*/ u8 _08[4];
    /*0x0C*/ TexArchive* textures; // texture coordinate arrays only
} ModelArray; // size: 0x10

enum {
    MODEL_CMD_TEXTURE = 1, // param: bits 0-12 texture index, bits 13-15 texcoord array / texmap
    MODEL_CMD_VTXDESC = 2, // param: 2-bit GXAttrType per attribute, PNMTXIDX then POS..TEX7, 21
    MODEL_CMD_CALLBACK = 3
};

typedef struct ModelCmd {
    /*0x00*/ u8 type;
    /*0x04*/ u32 param;
    /*0x08*/ void* displayList;
    /*0x0C*/ u32 displayListSize;
} ModelCmd; // size: 0x10

typedef struct ModelCmdList {
    /*0x00*/ u8 _00[4];
    /*0x04*/ ModelCmd* cmds;
    /*0x08*/ u16 count;
} ModelCmdList;

typedef struct Model {
    /*0x00*/ ModelArray* pos;
    /*0x04*/ u8 _04[4];
    /*0x08*/ ModelArray* texCoords;
    /*0x0C*/ u8 _0C[4];
    /*0x10*/ ModelCmdList* cmdList;
    /*0x14*/ u8 numTexCoords;
    /*0x15*/ u8 _15[3];
    /*0x18*/ Mtx mtx;
} Model;

// Memory card banner, icon and comment data (lbl_800F7B00).
typedef struct SaveBannerData {
    /*0x0000*/ u8 _0000[0x40];
    /*0x0040*/ u8 iconTpl[0x2380];
    /*0x23C0*/ u8 bannerTpl[0xE60];
    /*0x3220*/ char text[2][2][0x20];
} SaveBannerData; // size: 0x32A0

extern SaveBannerData lbl_800F7B00;

#define ROSTER_EMPTY 0x36 // no character

// Challenge-mode character records (lbl_8034E9A0).
typedef struct ChallengeRoster {
    /*0x0000*/ CharacterStats teams[6][9];
    /*0x21C0*/ u8 _21C0[0x4756 - 0x21C0];
    /*0x4756*/ u8 _4756;
    /*0x4757*/ u8 recruited[54];
    /*0x478D*/ u8 _478D[0x48AF - 0x478D];
    /*0x48AF*/ u8 _48AF;
    /*0x48B0*/ u8 _48B0[0x4C28 - 0x48B0];
} ChallengeRoster;

extern ChallengeRoster lbl_8034E9A0;

// Challenge-mode team being assembled (lbl_803C6724).
typedef struct ChallengeTeam {
    /*0x00*/ u8 _00[0xB];
    /*0x0B*/ s8 roster[9]; // character ids, ROSTER_EMPTY if free
    /*0x14*/ u8 _14[0x5C - 0x14];
} ChallengeTeam;

extern ChallengeTeam lbl_803C6724;

typedef struct ChallengeFreeAgent {
    /*0x0*/ s8 charId;
    /*0x1*/ u8 _1[4];
} ChallengeFreeAgent;

extern ChallengeFreeAgent lbl_80108FF8[10];
extern s16 lbl_80108EDC[][5]; // character variant groups

// Process-queue task used by the memory-card save/load state machines.
typedef struct SaveTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 _04[0x10 - 0x04];
    /*0x10*/ s16 result; // set by child tasks
    /*0x12*/ u16 priority;
    /*0x14*/ u8 state;
    /*0x15*/ u8 port; // controller that owns the dialog
    /*0x16*/ u8 _16;
    /*0x17*/ u8 slot; // memory card channel
    /*0x18*/ u8 mode;
    /*0x19*/ u8 _19;
    /*0x1A*/ u8 _1A;
    /*0x1B*/ u8 saveFlags; // bit 1: challenge save, 7: everything
    /*0x1C*/ u8 outcome; // result handed to the parent task
    /*0x1D*/ u8 noCard;
    /*0x1E*/ u8 cardReady;
    /*0x1F*/ u8 _1F;
    /*0x20*/ u8 challengeSlot; // 3: all
    /*0x21*/ u8 _21;
} SaveTask;

// Serial number of the memory card each save slot was last read from / written to.
extern u64 lbl_802D4AE0[4];

// Same layout as CardSlot/CardSystem in main/file_800A7C08.h, which can't be included
// next to UnknownHomes_Static.h (conflicting prototypes). TODO: unify.
typedef struct SaveCardSlot {
    /*0x00*/ u64 serial;
    /*0x08*/ s32 probeResult;
    /*0x0C*/ u8 _0C[0x28 - 0x0C];
} SaveCardSlot;

typedef struct SaveCardSystem {
    /*0x00*/ SaveCardSlot slots[2];
    /*0x50*/ s32 lastResult;
    /*0x54*/ u8 status; // CARD_STATUS_* or an error code
    /*0x55*/ u8 op;
    /*0x56*/ u8 _56[0x60 - 0x56];
} SaveCardSystem;

extern SaveCardSystem lbl_803C7838;

// Same layout as CardRequest in main/file_800A7C08.h (see SaveCardSystem).
typedef struct SaveCardRequest {
    /*0x00*/ char* fileName;
    /*0x04*/ void* buffer;
    /*0x08*/ s32 length;
    /*0x0C*/ u8 chan;
    /*0x0D*/ u8 mode;
    /*0x0E*/ u8 permissions;
    /*0x0F*/ u8 _0F;
    /*0x10*/ u8 (*verify)(void* buffer, s32 length, u32 arg);
    /*0x14*/ u32 verifyArg;
    /*0x18*/ u32 flags;
} SaveCardRequest;

// One challenge-mode save in the card image.
typedef struct SaveChallengeBlock {
    /*0x0*/ u16 crc; // CRC-16 of data
    /*0x2*/ u16 size; // 0x450C
    /*0x4*/ u8 data[0x4508];
} SaveChallengeBlock; // size: 0x450C

// Memory card save image (lbl_802D4B00); starts with the card comment header.
typedef struct SaveImage {
    /*0x000*/ char comment[2][0x20];
    /*0x040*/ u16 cardCrc;
    /*0x042*/ u16 _42;
    /*0x044*/ u16 crc;  // CRC-16 of _48 .. _5F4
    /*0x046*/ u16 size; // 0x5B4
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
    /*0xD51C*/ u8 _D51C[0x10000 - 0xD51C]; // filled with 0xEE
} SaveImage; // size: 0x10000

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
    /*0x00*/ u8 _00;
    /*0x01*/ u8 _01[0x9 - 0x1];
    /*0x09*/ u8 _09;
    /*0x0A*/ u8 _0A[0x3E - 0xA];
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
void fn_8003A6B0(s32 type, TexImage* tex, f32 speed, f32 spread);
void fn_8003A85C(u8 enabled);
void fn_8003A8A0(Model* model, Mtx viewMtx, s32 unused);
void fn_8003AC90(void);
void fn_8003AD84(TexArchive* arc);
void fn_8003E8D8(void);
void fn_8003F23C(void);
void fn_8003F2B8(void);

void fn_8003AECC(void);
void fn_8003B5B0(void);
void fn_8003BB90(void);
void fn_8003BF54(u8 a, u8 b, u8 slot, u8 c, u8 d, u8 e, u8 f, u8 g, u8 h);
void fn_8003C00C(void);
u8 fn_80040FE0(void* buffer, s32 length, u32 mask);
void fn_8004053C(void);
void fn_80040C14(void);
u8 fn_80041074(void* buffer, s32 length, u32 mask);
void fn_80041150(u8 mask, u8 slot);
s32 fn_80041348(void);
void fn_8004153C(void);
void fn_800415A8(void);

void fn_8003A848(u8 red, u8 green, u8 blue);

u8 fn_8003AE54(void);

void fn_8003AE5C(u8 value);

void fn_8003AE64(void);

u8 fn_8003AE70(s32 selector);

u16 fn_8004157C(void);

void fn_800415A0(u16 value);

#endif
