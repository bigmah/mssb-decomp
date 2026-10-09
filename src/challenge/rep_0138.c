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

extern const f32 lbl_1_rodata_21C[];
extern const f32 lbl_1_rodata_220[];
extern const f32 lbl_1_rodata_224[];
extern const f32 lbl_1_rodata_228[];
extern const f32 lbl_1_rodata_22C[];
extern const f32 lbl_1_rodata_230[];
extern const f32 lbl_1_rodata_234[];
extern const f32 lbl_1_rodata_238[];
extern const f32 lbl_1_rodata_23C;
extern const f32 lbl_1_rodata_240;
extern const f32 lbl_1_rodata_244;

// fn_1_7E04, size:0xF4
void fn_1_7E04(f32 scale) {
    Mtx44 projection;
    f32 inverse = lbl_1_rodata_1D8 / scale;
    C_MTXFrustum(projection, lbl_1_rodata_21C[0] * inverse, lbl_1_rodata_220[0] * inverse,
                 lbl_1_rodata_224[0] * inverse, lbl_1_rodata_228[0] * inverse,
                 lbl_1_rodata_1D8, lbl_1_rodata_208);
    GXSetProjection(projection, GX_PERSPECTIVE);
    fn_800B806C(0, lbl_1_rodata_22C[0] * inverse, lbl_1_rodata_230[0] * inverse,
               lbl_1_rodata_234[0] * inverse, lbl_1_rodata_238[0] * inverse,
               lbl_1_rodata_23C, lbl_1_rodata_240, lbl_1_rodata_244);
}

extern s32 lbl_1_bss_C4;

extern u8 lbl_1_bss_C2[];
extern u8 lbl_1_data_85C[];

extern u8 lbl_1_common_bss_472B4[];
extern void fn_1_4DD8(u16* effects);
extern u8 lbl_803CBBC0;
extern void fn_800A7D4C(int, void*);
extern const f32 lbl_1_rodata_204;
typedef struct { u8 b[8]; } Chal8;
static u8 sPad[0x5E4] = {1};
static Chal8 sTabA[3] = {{{1}}};
static Chal8 sTabB[2] = {{{1}}};
static Chal8 sTabC[2] = {{{1}}};

// fn_1_717C, size:0x104
void fn_1_717C(ChallengeModelOffsets* model) {
    u8* geometry;
    u8* actor;
    u8* textures;
    actor = (u8*)model + model->mainActor;
    geometry = (u8*)model + model->mainGeometry;
    textures = (u8*)model + model->textures;
    fn_1_4DD8((u16*)((u8*)model + model->effects));
    fn_800B49E4(actor);
    fn_800BCE38(geometry);
    convertTextureHeader(textures);
    *(u8**)(lbl_1_common_bss_472B4 + 0x58) = textures + 4;
    fn_800BD190((struct GQRValueGroups*)geometry, (s32)textures);
    haveActLayoutPointToGeoHeader(actor, geometry);
    *(u16*)(lbl_1_common_bss_472B4 + 0x22A) = *(u16*)(actor + 6);
    *(u8**)(lbl_1_common_bss_472B4 + 0x130) = actor;
    *(u8**)(lbl_1_common_bss_472B4 + 0xC4) = actor;
    actor = (u8*)model + model->secondaryActor;
    geometry = (u8*)model + model->secondaryGeometry;
    fn_800B49E4(actor);
    fn_800BCE38(geometry);
    fn_800BD190((struct GQRValueGroups*)geometry, (s32)textures);
    haveActLayoutPointToGeoHeader(actor, geometry);
    *(u8**)(lbl_1_common_bss_472B4 + 0x208) = actor;
    *(u8**)(lbl_1_common_bss_472B4 + 0x19C) = actor;
}

// fn_1_7EF8, size:0x100
void fn_1_7EF8(void) {
    switch ((s32)*(u16*)((u8*)&lbl_803C77B8 + 4)) {
    case 4:
    case 8:
        lbl_1_bss_C2[0] = !lbl_1_bss_C2[0];
        break;
    case 1: {
        s32 value = (s32)fn_80048EA8(lbl_1_bss_C2[0]);
        fn_80048E00(lbl_1_bss_C2[0], value - 1);
        break;
    }
    case 2: {
        s32 value = (s32)fn_80048EA8(lbl_1_bss_C2[0]);
        fn_80048E00(lbl_1_bss_C2[0], value + 1);
        break;
    }
    case 0x100: {
        u8 enabled = !lbl_1_data_85C[0];
        lbl_1_data_85C[0] = enabled;
        if (enabled != 0) {
            fn_80048C14(0x3F);
        } else {
            fn_80048C14(0);
        }
        break;
    }
    }
}

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

// fn_1_7280, size:0x138
void fn_1_7280(void) {
    u8* p;
    u8* q;
    p = lbl_1_common_bss_472B4 + lbl_803CBBC0 * 0x6C + 0x5C;
    PSMTXCopy((f32(*)[4])lbl_1_common_bss_472B4, (f32(*)[4])(p + 0x38));
    fn_800A7D4C(0, &sTabC[lbl_803CBBC0]);
    fn_800A7D4C(0, p);
    fn_800A7D4C(0, &sTabB[lbl_803CBBC0]);
    q = lbl_1_common_bss_472B4 + lbl_803CBBC0 * 0x6C + 0x134;
    PSMTXRotRad((f32(*)[4])(q + 8), 0x59, lbl_1_rodata_204 * (f32)*(u16*)(lbl_1_common_bss_472B4 + 0x23A));
    PSMTXCopy((f32(*)[4])lbl_1_common_bss_472B4, (f32(*)[4])(q + 0x38));
    fn_800A7D4C(0, q);
    fn_800A7D4C(0, &sTabA[lbl_803CBBC0]);
}
