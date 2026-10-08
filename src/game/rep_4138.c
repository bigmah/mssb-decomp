#include "game/rep_4138.h"
#include "header_rep_data.h"
#include "Dolphin/stl.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"

extern u8 lbl_8036E548[];
extern u8 lbl_803CBBC0[];
extern u8 g_GameLogic[];
extern u8 lbl_3_data_2A498[];
extern void fn_800A7D4C(int, void*);
static s32 lbl_3_bss_D6F0[9];
static u8 lbl_3_bss_D6EC;
static s32 lbl_3_bss_D6E8;
static u16* lbl_3_bss_D6E4;
static u32 lbl_3_bss_D6E0;
extern f32 lbl_3_data_2A448[];
extern f32 lbl_3_data_2A478[];
extern GXColor lbl_3_rodata_4188;
extern f32 lbl_3_rodata_418C;
extern f32 lbl_3_rodata_4190;
extern u8 g_Scores[];
extern u8 g_Strikes[];

void fn_3_16E1A0(void) {
    s32* o = lbl_3_bss_D6F0;
    o[0] = *(s16*)(g_Scores + 0x2A);
    o[1] = *(s16*)(g_Scores + 4);
    o[2] = *(s32*)g_Scores;
    o[3] = *(s32*)g_Strikes;
    o[4] = *(s32*)(g_Strikes + 4);
    o[5] = *(s32*)(g_Strikes + 8);
}

typedef struct { s32 a, b; } Ent;

// .text:0x0016E1EC size:0x110
void fn_3_16E1EC(void) {
    s32 x;
    u32 idx;
    if (((u32)lbl_3_bss_D6E4 == 0) | (lbl_3_bss_D6EC | (lbl_8036E548[0x3088] == 0))) {
        lbl_3_bss_D6E4 = NULL;
        lbl_3_bss_D6E8 = -1;
        lbl_3_bss_D6EC = 0;
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
    x = g_GameLogic[0x11E];
    if ((x != 0x13) & (x != 0x14)) {
        fn_3_16E1A0();
    }
    idx = lbl_803CBBC0[0];
    fn_800A7D4C(1, lbl_3_data_2A498 + idx * 8);
}

void fn_3_16E2FC(u16* p, s32 i) {
    if (p == NULL) {
        return;
    }
    if (p[0] - 1 < i) {
        return;
    }
    lbl_3_bss_D6E4 = p;
    lbl_3_bss_D6E8 = i;
}

// .text:0x0016D810 size:0x1A0 mapped:0x807AC8A4
void fn_3_16D810(s32 n, f32 x, f32 y) {
    s32 i;
    GXColor col = lbl_3_rodata_4188;
    f32 t = lbl_3_rodata_418C * (f32)n;
    f32 u = t * lbl_3_rodata_4190;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(x + lbl_3_data_2A448[i * 3], y + lbl_3_data_2A448[i * 3 + 1], lbl_3_data_2A448[i * 3 + 2]);
        GXColor1u32(*(u32*)&col);
        GXTexCoord2f32(u + lbl_3_data_2A478[i * 2], lbl_3_data_2A478[i * 2 + 1]);
    }
}

extern s32 fn_8005268C(void);
extern void fn_80033B58(void*, s32, s32, s32);

// .text:0x0016D9B0 size:0x1BC mapped:0x807ACA44
void fn_3_16D9B0(void) {
    GXSetZMode(1, 3, 0);
    GXSetCullMode(0);
    GXSetBlendMode(1, 4, 1, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 1, 1, 4);
    GXSetTevColorIn(0, 8, 0xA, 0xF, 0xF);
    GXSetTevAlphaIn(0, 4, 5, 7, 7);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXLoadPosMtxImm(fn_80052768_getCamera(fn_8005268C())->view, 0);
    GXSetCurrentMtx(0);
    GXSetProjection(fn_80052768_getCamera(fn_8005268C())->proj, 0);
    fn_80033B58(lbl_3_bss_D6E4, lbl_3_bss_D6E8, 0, 0);
}

// .text:0x0016DB6C size:0x458 mapped:0x807ACC00
#pragma dont_inline on
void fn_3_16DB6C(u8 i) {
    return;
}
#pragma dont_inline reset

// .text:0x0016DFC4 size:0x1DC
void fn_3_16DFC4(void) {
    u32 i;
    GXSetZMode(1, 3, 0);
    GXSetCullMode(0);
    GXSetBlendMode(1, 4, 1, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 1, 1, 4);
    GXSetTevColorIn(0, 8, 0xA, 0xF, 0xF);
    GXSetTevAlphaIn(0, 4, 5, 7, 7);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXLoadPosMtxImm(fn_80052768_getCamera(fn_8005268C())->view, 0);
    GXSetCurrentMtx(0);
    GXSetProjection(fn_80052768_getCamera(fn_8005268C())->proj, 0);
    fn_80033B58(lbl_3_bss_D6E4, lbl_3_bss_D6E8, 0, 0);
    i = 0;
    do {
        fn_3_16DB6C(i);
        i += 1;
    } while (i < 6U);
}


// .text:0x0016E328 size:0x10
void fn_3_16E328(void) {
    lbl_3_bss_D6EC = 1;
}

extern void fn_3_16E1EC(void);

// .text:0x0016E338 size:0x6C
void fn_3_16E338(u16* p, s32 i) {
    if (p != NULL && p[0] - 1 >= i) {
        lbl_3_bss_D6E4 = p;
        lbl_3_bss_D6E8 = i;
        lbl_3_bss_D6EC = 0;
        memset(lbl_3_bss_D6F0, 0, 0x18);
        fn_800B0A5C_insertQueue(fn_3_16E1EC, 5);
    }
}
