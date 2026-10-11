#include "game/auto_00_0015F874_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_80024184.h"
#include "main/file_80069BDC.h"
#include "Dolphin/gx.h"

// .text:0x0015F874 size:0x124 mapped:0x8079E908
void fn_3_15F874(s32 useB) {
    FadeDrawData* d = &lbl_3_data_27EC0;
    Mtx m;

    GXSetProjection(d->proj, GX_ORTHOGRAPHIC);
    PSMTXIdentity(m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetColorUpdate(GX_FALSE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    gOz_GXSetTexture(GX_PASSCLR, 0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA4, 0);
    if (useB) {
        GXSetArray(GX_VA_POS, d->posB, 0xC);
    } else {
        GXSetArray(GX_VA_POS, d->posA, 0xC);
    }
    GXCallDisplayList(d->displayList, 0x20);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
}

// .text:0x0015F998 size:0x14 mapped:0x8079EA2C
void fn_3_15F998(void) {
    lbl_3_common_bss_35154.active = 0;
}

// .text:0x0015F9AC size:0x14 mapped:0x8079EA40
void fn_3_15F9AC(void) {
    return;
}

// .text:0x0015F9C0 size:0x98 mapped:0x8079EA54
void fn_3_15F9C0(void) {
    return;
}

// .text:0x0015FA58 size:0x12C mapped:0x8079EAEC
void fn_3_15FA58(void) {
    return;
}
