#ifndef __GAME_rep_3F60_H_
#define __GAME_rep_3F60_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "main/file_80011640.h"  // CharActor
#include "main/file_80024D2C.h"  // ShapeAnimState, ShapeData
#include "main/file_800BD8C4.h"  // ActorObjectTable

// Character effect models (animated shape models drawn at a character's joint).

// Display-list node for fn_800A7D4C that draws one effect model (two per actor, indexed by lbl_803CBBC0).
typedef struct EffectNode {
    /*0x00*/ void* next; // draw-list link, set by fn_800A7D4C
    /*0x04*/ void (*draw)(struct EffectNode* node);
    /*0x08*/ Vec pos;
    /*0x14*/ f32 scale;
    /*0x18*/ u32 frame;
    /*0x1C*/ u8 objIdx;  // ActorObject in lbl_3_common_bss_35154.anim[0].table
    /*0x1D*/ u8 ofsIdx;  // model offset in lbl_3_data_28680
    /*0x1E*/ u8 animIdx; // shape animations in lbl_3_common_bss_35154.anim
    /*0x1F*/ u8 animIdx2;
} EffectNode; // size: 0x20

// Scene task that feeds an EffectNode each frame (lbl_803CC1B8 while it runs).
typedef struct EffectTask {
    /*0x00*/ u8 _00[0x12];
    /*0x12*/ u16 priority;
    /*0x14*/ Vec pos;
    /*0x20*/ f32 scale;
    /*0x24*/ u16 frame;
    /*0x26*/ s16 _26;
    /*0x28*/ u8 objIdx;
    /*0x29*/ u8 actor; // index into lbl_8036E548.active
    /*0x2A*/ u8 ofsIdx;
    /*0x2B*/ u8 animIdx;
    /*0x2C*/ u8 animIdx2;
} EffectTask;

// One shape animation of an effect model.
typedef struct EffectAnim {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ ActorObjectTable* table; // only anim[0].table is used
    /*0x14*/ u8 _14[0xC];
    /*0x20*/ ShapeAnimState state; // state.seqs[0].hdr.length: frames to show the effect
    /*0x40*/ ShapeData* shape;
    /*0x44*/ u8 _44[0x18];
} EffectAnim; // size: 0x5C

// View of lbl_3_common_bss_35154, only the fields used here.
typedef struct EffectAnims {
    /*0x000*/ EffectAnim anim[12];
    /*0x450*/ u8 _450[0x29];
    /*0x479*/ u8 _479;
} EffectAnims;

void fn_3_168414(EffectNode* node);
void fn_3_168704(void);
void fn_3_16892C(CharActor* actor, f32 frame, s32 b, s32 unused); // AnimEventCallback (fn_8006C3F0)
void fn_3_168A6C(EffectNode* node);
void fn_3_168CD8(CharActor* actor, f32 frame, s32 unused0, s32 unused1); // AnimEventCallback (fn_8006C43C)
void fn_3_168DFC(void);
void fn_3_168FA0(s32 actor, s32 b);

#endif // !__GAME_rep_3F60_H_
