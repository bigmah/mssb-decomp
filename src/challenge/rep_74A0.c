#include "challenge/rep_74A0.h"


#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"
#include <math.h>

extern void fn_1_1CBE4(u8* object);
extern ChallengeRosterQueue* lbl_803CC1B8;
extern u8 lbl_1_bss_69FC[];
extern void fn_1_19D60(struct DODisplayObj*, s32);
extern s32 lbl_1_data_FB24[];
extern const f32 lbl_1_rodata_7578;
extern const f32 lbl_1_rodata_757C;
extern const f32 lbl_1_rodata_7520;

// fn_1_1A290, size:0x124
void fn_1_1A290(ChallengeDrawCollection* collection, s32 mode) {
    u16 index;

    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (index = 0; index < collection->count; index++) {
        ChallengeActorDrawing* drawing = &collection->nodes[index].drawing;
        if (drawing->actor != NULL && collection->nodes[index].visible != 0) {
            fn_1_1A1EC(drawing, mode);
        }
    }
}

// fn_1_18E04, size:0xE0
void fn_1_18E04(ChallengeOrbitPosition* position, f32 degrees) {
    f32 sine;
    f32 radians;
    f32 cosine;
    radians = lbl_1_rodata_7578 * degrees;
    sine = (f32)sin(radians);
    cosine = (f32)cos(radians);
    position->x = sine * (f32)lbl_1_data_FB24[1] / lbl_1_rodata_757C;
    position->y = cosine * (f32)lbl_1_data_FB24[1] / lbl_1_rodata_757C;
    position->z = lbl_1_rodata_7520;
}

// fn_1_1A1EC, size:0xA4
void fn_1_1A1EC(ChallengeActorDrawing* drawing, s32 mode) {
    ChallengeDrawActor* actor = drawing->actor;
    if (drawing->prepare != NULL) {
        drawing->prepare(drawing);
    }
    if (actor->display != NULL) {
        fn_800B2D5C(actor);
        GXInvalidateVtxCache();
        fn_1_19D60(actor->display, mode);
    } else {
        for (actor = actor->children; actor != NULL; actor = actor->next) {
            if (actor->display != NULL) {
                DOSetWorldMatrix(actor->display, actor->worldMatrix);
            }
            fn_1_19D60(actor->display, mode);
        }
    }
}

// fn_1_1D470, size:0xA4
void fn_1_1D470(void) {
    ChallengeRosterQueue* queue = lbl_803CC1B8;
    s32 index;
    for (index = 0; index < 24; index++) {
        lbl_1_bss_69FC[0x40 + index] = 0;
    }
    queue->menu = 0;
    lbl_803CC1B8->update = fn_1_1D450;
}


// .text:0x1D10C size:0x4
void fn_1_1D10C(void) {
}

// fn_1_1D0E8, size:0x24
void fn_1_1D0E8(u8* object) {
    fn_800B9AA8(*(void**)(object + 0x70));
}

// fn_1_1D450, size:0x20
void fn_1_1D450(u8* object) {
    fn_1_1CBE4(object);
}

// fn_1_19D1C, size:0x44
s32 fn_1_19D1C(u8 value) {
    switch ((value >> 4) & 0xF) {
    case 0:
    case 1: return 1;
    case 2:
    case 3: return 2;
    case 4: return 4;
    default: return 0;
    }
}
