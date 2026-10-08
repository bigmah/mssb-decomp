#include "challenge/rep_0138.h"


#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"

extern GXCullMode lbl_1_data_8C4[];
extern void* lbl_1_data_848[3];
extern void fn_1_73B8(void* context, s32 count, ...);

typedef union ChallengeColor {
    GXColor color;
    s32 word;
} ChallengeColor;

typedef struct ChallengeFog {
    ChallengeColor color;
    f32 start;
    f32 end;
} ChallengeFog;

extern ChallengeColor lbl_1_data_858[];
extern ChallengeFog* lbl_1_bss_4E0[];
extern const f32 lbl_1_rodata_1D8;
extern const f32 lbl_1_rodata_208;

extern s32 lbl_1_bss_C4;

// fn_1_78E4, size:0x7C
void fn_1_78E4(void) {
    GXColor clear = lbl_1_data_858[0].color;
    GXSetCopyClear(clear, 0xFFFFFF);
    if (lbl_1_bss_C4 != 0) {
        GXSetCullMode(GX_CULL_NONE);
    } else {
        GXSetCullMode(GX_CULL_BACK);
    }
    SetFogNoneAgain();
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
}

// fn_1_786C, size:0x78
void fn_1_786C(void) {
    GXColor clear;
    GXColor color;
    ChallengeFog* fog;
    fn_80048D4C();
    clear = lbl_1_data_858[0].color;
    GXSetCopyClear(clear, 0xFFFFFF);
    fog = lbl_1_bss_4E0[0];
    color = fog->color.color;
    // This call passes the packed colour through the GXColor value ABI.
    ((void (*)(u8, GXColor, f32, f32, f32, f32))SetFog)(fog->color.color.a, color, fog->start, fog->end, lbl_1_rodata_1D8, lbl_1_rodata_208);
}

// fn_1_54E0, size:0x60
void fn_1_54E0(void* matrix) {
    s32 i;
    for (i = 0; i < 3; i++) {
        LITXForm(lbl_1_data_848[i], matrix);
    }
}

// fn_1_77EC, size:0x5C
void fn_1_77EC(void* context) {
    GXSetCullMode(lbl_1_data_8C4[0]);
    fn_1_73B8(context, 3, lbl_1_data_848[0], lbl_1_data_848[1], lbl_1_data_848[2]);
}

// .text:0x5540 size:0x4
void fn_1_5540(void) {
}

// fn_1_7848, size:0x24
void fn_1_7848(void) {
    fn_80048C28();
    fn_80048C1C();
}
