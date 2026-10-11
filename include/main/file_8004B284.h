#ifndef __MAIN_FILE_8004B284_H__
#define __MAIN_FILE_8004B284_H__

#include "mssbTypes.h"
#include "main/file_80063028.h"
#include "main/file_80011640.h" // CharActor


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

void fn_800B2B74(GameActor* actor, u16 bone);
struct DODisplayObj* fn_800B2BA8(GameActor* actor, u16 bone, GameActor* src, u16 srcBone);
void fn_800B2BE4(GameActor* actor, u16 bone);

// Per-character swing effect callbacks (table lbl_800FBE64) share this signature.
void fn_8004B284(CharActor* model, s32 animID, u32 colorIdx, f32 frame);
void fn_8004B6EC(CharActor* model, ActorObject* obj);
s32 fn_8004B7B4(CharActor* model, ActorObject* obj);
void fn_8004B7F4(CharActor* model, ActorObject* obj);
void fn_8004BAEC(CharActor* model, ActorObject* obj);
s32 fn_8004BD6C(CharActor* model, ActorObject* obj);

#endif
