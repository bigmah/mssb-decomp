#ifndef __MAIN_FILE_8004B284_H__
#define __MAIN_FILE_8004B284_H__

#include "mssbTypes.h"
#include "main/file_80063028.h"

typedef struct AnimSlot {
    /*0x00*/ u8 pad00[0x4D];
    /*0x4D*/ u8 active;
    /*0x4E*/ u8 pad4E[0x16];
} AnimSlot; // size 0x64

typedef struct AnimSlotPair {
    /*0x00*/ u8 pad00[0x10];
    /*0x10*/ AnimSlot slots[2];
} AnimSlotPair;

// Character model object (one per player on the field).
typedef struct CharModel {
    /*0x000*/ u8 pad000[0x2C];
    /*0x02C*/ AnimSlotPair* anim;
    /*0x030*/ AnimSlotPair* anim2;
    /*0x034*/ Vec pos;
    /*0x040*/ Vec rot;
    /*0x04C*/ u8 pad04C[0x16];
    /*0x062*/ s16 animID;
    /*0x064*/ u8 pad064[0x126];
    /*0x18A*/ u16 bone18A;
    /*0x18C*/ u8 pad18C[0xA];
    /*0x196*/ u16 bone196;
    /*0x198*/ u8 pad198[0x42];
    /*0x1DA*/ u16 bone1DA;
    /*0x1DC*/ u16 bone1DC;
    /*0x1DE*/ u8 pad1DE[0x18];
    /*0x1F6*/ u16 bone1F6;
    /*0x1F8*/ u16 bone1F8;
    /*0x1FA*/ u16 bone1FA;
    /*0x1FC*/ u8 pad1FC[0x56];
    /*0x252*/ s8 charID;
    /*0x253*/ u8 pad253;
    /*0x254*/ s8 playerIdx;
    /*0x255*/ u8 pad255[5];
    /*0x25A*/ u8 unk25A;
    /*0x25B*/ u8 unk25B;
    /*0x25C*/ u8 unk25C;
    /*0x25D*/ u8 unk25D;
    /*0x25E*/ u8 pad25E[0x16];
    /*0x274*/ u8 unk274;
    /*0x275*/ u8 pad275[3];
    /*0x278*/ u8 unk278;
} CharModel;

// Effect spawn parameters (templates in .data, copied and tweaked before use).
typedef struct EffectParams {
    /*0x00*/ s32 stamp;
    /*0x04*/ u8 pad04[0x8];
    /*0x0C*/ s32 unk0C;
    /*0x10*/ s32 unk10;
    /*0x14*/ u8 pad14[0x2C];
    /*0x40*/ u32 rgb; // r << 24 | g << 16 | b << 8
    /*0x44*/ u8 pad44[0xC];
} EffectParams; // size 0x50

typedef struct EffectParamsB {
    /*0x00*/ s32 stamp;
    /*0x04*/ u8 pad04[0x50];
} EffectParamsB; // size 0x54

typedef struct RGB8 {
    u8 r, g, b;
} RGB8;

typedef struct BatFxParams { // lbl_800FBF10
    /*0x000*/ EffectParams params[3];
    /*0x0F0*/ EffectParamsB paramsB[3];
} BatFxParams;

typedef struct BatFxTables { // lbl_800FC0FC
    /*0x000*/ RGB8 colors[13];
    /*0x027*/ u8 pad27;
    /*0x028*/ u16 animIDs[32][7];
} BatFxTables;

u32 fn_80024D2C(AnimSlot* slot);
s32 fn_8001B728(s32 playerIdx, s32 kind, Vec* out);
void fn_80030D88(Vec* pos, Vec* dir, void* params, int kind);
void fn_8001D180(s32 playerIdx, u32 part, s32 alt);
void fn_800B2B74(GameActor* actor, u16 bone);
struct DODisplayObj* fn_800B2BA8(GameActor* actor, u16 bone, GameActor* src, u16 srcBone);
void fn_800B2BE4(GameActor* actor, u16 bone);

// Per-character swing effect callbacks (table lbl_800FBE64) share this signature.
void fn_8004B284(CharModel* model, s32 animID, u32 colorIdx, f32 frame);
void fn_8004B6EC(CharModel* model, GameActor** actor);
s32 fn_8004B7B4(CharModel* model, GameActor** actor);
void fn_8004B7F4(CharModel* model);
void fn_8004BAEC(CharModel* model);
s32 fn_8004BD6C(CharModel* model, GameActor** actor);

#endif
