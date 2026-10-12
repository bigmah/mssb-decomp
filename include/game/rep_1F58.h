#ifndef __GAME_rep_1F58_H_
#define __GAME_rep_1F58_H_

#include "mssbTypes.h"
#include "main/scene_task.h" // SCENE_TASK_VIEW_HEAD
#include "Dolphin/mtx.h"
#include "game/rep_3F60.h" // EffectAnim

struct DODisplayObj;

// Character aura slot (lbl_3_data_17260, two slots); id -1: free.
typedef struct E32_1F58 {
    /*0x00*/ s16 id;
    /*0x02*/ s16 s2; // frames until the next particle burst
    /*0x04*/ f32 v[3];
    /*0x10*/ f32 p[3];
    /*0x1C*/ f32 x;
} E32_1F58;
extern E32_1F58 lbl_3_data_17260[2];

// Display-list node for fn_800A7D4C that draws the aura model (two per slot, indexed by lbl_803CBBC0).
typedef struct E18_1F58 {
    /*0x00*/ void* next;                       // draw-list link
    /*0x04*/ void (*draw)(struct E18_1F58* a); // fn_3_C095C
    /*0x08*/ Vec pos;
    /*0x14*/ u32 frame;
} E18_1F58; // size: 0x18

typedef struct E30_1F58 {
    E18_1F58 e[2];
} E30_1F58;

// Scene task that feeds an E18_1F58 each frame (fn_3_C0AD8; lbl_803CC1B8 while it runs).
typedef struct Rep1F58Track {
    /*0x00*/ SCENE_TASK_VIEW_HEAD // SceneTask head (main/scene_task.h)
    /*0x14*/ u32 frame;
    /*0x18*/ s32 slot;  // index into lbl_3_data_174A0 / lbl_3_data_174A8
    /*0x1C*/ s32 actor; // index into lbl_8036E548.active
    /*0x20*/ u8 done;
} Rep1F58Track;

// Scene task that fades an aura out (fn_3_C1004).
typedef struct Rep1F58Fade {
    /*0x00*/ SCENE_TASK_VIEW_HEAD // SceneTask head (main/scene_task.h)
    /*0x14*/ u8 who; // index into lbl_8036E548.active
    /*0x15*/ u8 alpha;
    /*0x16*/ u8 count; // frames left (from 10)
} Rep1F58Fade;

// View of lbl_3_common_bss_35154, only the fields used here.
typedef struct Rep1F58Bss35154 {
    union {
        /*0x000*/ EffectAnim anim[2]; // anim[0].table: models, anim[0..1]: the aura's shape animations
        struct {
            /*0x000*/ u8 _000[0x4];
            /*0x004*/ void* tex; // particle texture
        };
    };
    /*0x0B8*/ u8 _0B8[0x3AC - 0xB8];
    /*0x3AC*/ u32 flags;
    /*0x3B0*/ u8 _3B0[0x434 - 0x3B0];
    /*0x434*/ Vec pos434;
    /*0x440*/ u8 _440[0x467 - 0x440];
    /*0x467*/ u8 _467;
    /*0x468*/ u8 _468[0x477 - 0x468];
    /*0x477*/ u8 tracking[2]; // per slot: a fn_3_C0AD8 task was started
} Rep1F58Bss35154;

void fn_3_C0854(void);
void fn_3_C095C(E18_1F58* a);
void fn_3_C0AD8(void);
void fn_3_C0C4C(s32 idx);
void fn_3_C0CE8(u8 v, f32 x, f32 y, f32 z);
void fn_3_C0D10(s32 i, u8 v1, u8 v2, u8 v3, u8 v4);
void fn_3_C0DD8(struct DODisplayObj* unused, s32* stage, s32* coord, s32* map, u8* c1, u8* c2, MtxPtr camera); // DOTevHook
void fn_3_C0F8C(void);
void fn_3_C1004(void);
void fn_3_C11CC(s32 who, s32 a);
void fn_3_C1344(s32 who, s32 track, f32 t, f32 t2);
void fn_3_C1770(s32 who);

s32 fn_3_C1930(s32 id);

#endif // !__GAME_rep_1F58_H_
