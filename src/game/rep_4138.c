#include "game/rep_4138.h"
#include "header_rep_data.h"
#include "Dolphin/stl.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"

extern s32 lbl_3_bss_D6F0[];
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

extern u16* lbl_3_bss_D6E4;
extern s32 lbl_3_bss_D6E8;

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
void fn_3_16D810(void) {
    return;
}

extern u16* lbl_3_bss_D6E4;
extern s32 lbl_3_bss_D6E8;
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

extern u8 lbl_3_bss_D6EC;

// .text:0x0016E328 size:0x10
void fn_3_16E328(void) {
    lbl_3_bss_D6EC = 1;
}

extern u8 lbl_3_bss_D6E0[];
extern void fn_3_16E1EC(void);

// .text:0x0016E338 size:0x6C
void fn_3_16E338(u16* p, s32 i) {
    u8* b = lbl_3_bss_D6E0;
    if (p != NULL && p[0] - 1 >= i) {
        *(u16**)(b + 4) = p;
        *(s32*)(b + 8) = i;
        b[0xC] = 0;
        memset(b + 0x10, 0, 0x18);
        fn_800B0A5C_insertQueue(fn_3_16E1EC, 5);
    }
}
