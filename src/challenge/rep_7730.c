#include "challenge/rep_7730.h"

#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"
extern void fn_1_20BD8(void);

extern void fn_1_246AC(void);

extern u8* lbl_803CC1B8[];

extern f32 lbl_1_bss_6BE4[4];

extern void (*lbl_1_data_1066C[])(s16);

extern f32 lbl_1_bss_6BF4[];
extern void fn_80037B18(void*, Vec*, f32);

extern u8 lbl_1_data_10674[];
extern void fn_1_1DA54(void);

extern u8 lbl_1_bss_6D48[];
extern const f32 lbl_1_rodata_77E4[];
extern void fn_1_272DC(void*, s32);
extern void fn_1_AF4(s32, s32, f32);
extern void fn_1_1E5D0(void*);

extern void fn_1_21408(void);
extern u8 lbl_803C6CF8[];
extern u8 lbl_1_data_104F4[];
extern const f32 lbl_1_rodata_77D8;
extern const f32 lbl_1_rodata_7804;
extern const f32 lbl_1_rodata_7858;
extern const f32 lbl_1_rodata_785C;
extern const f32 lbl_1_rodata_7860;
extern const f32 lbl_1_rodata_7864;
extern const f32 lbl_1_rodata_7868;
extern const f32 lbl_1_rodata_780C;
extern const f32 lbl_1_rodata_77DC[];
extern const f32 lbl_1_rodata_77E0[];
extern const f32 lbl_1_rodata_7814[];
extern const f32 lbl_1_rodata_7820[];
extern Mtx44 lbl_1_bss_47010;
extern void (*lbl_1_data_104A8[])(void);

// fn_1_246AC, size:0xCC
void fn_1_246AC(void) {
    u8* queue = lbl_803CC1B8[0];
    u16 repeated = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (repeated & 8) {
        if (queue[0x14] == 0) {
            queue[0x14] = 4;
        }
        queue[0x14]--;
    } else if (repeated & 4) {
        queue[0x14]++;
        if (queue[0x14] == 4) {
            queue[0x14] = 0;
        }
    } else {
        u16 pressed = lbl_803C77B8._02;
        if (pressed & 0x100) {
            *(void (**)(void))queue = lbl_1_data_104A8[queue[0x14]];
        } else if (pressed & 0x200) {
            ChallengeTransfer* transfer = *(ChallengeTransfer**)(queue + 0x0C);
            transfer->complete = 1;
            fn_800B0A14_removeQueue(transfer);
        }
    }
}

// fn_1_26A34, size:0xC4
void fn_1_26A34(void) {
    GXSetProjection(lbl_1_bss_47010, GX_PERSPECTIVE);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_NONE);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
}

// fn_1_20890, size:0xC0
void fn_1_20890(void) {
    Mtx identity;
    C_MTXOrtho(lbl_1_bss_47010, lbl_1_rodata_77D8, lbl_1_rodata_77DC[0],
        lbl_1_rodata_77D8, lbl_1_rodata_77E0[0], lbl_1_rodata_7814[0], lbl_1_rodata_7820[0]);
    GXSetProjection(lbl_1_bss_47010, GX_ORTHOGRAPHIC);
    PSMTXIdentity(identity);
    GXLoadPosMtxImm(identity, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadTexMtxImm(identity, GX_TEXMTX0, GX_MTX2x4);
    fn_80048C14(3);
    fn_80048E00(0, 32);
    fn_80048E00(1, 0);
}

// fn_1_207D4, size:0xBC
void fn_1_207D4(void) {
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 8);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
}

// fn_1_1F23C, size:0x9C
void fn_1_1F23C(ChallengeProjectionState* state) {
    fn_800385F0(lbl_1_bss_6BF4,
        *(f32*)(lbl_803CC1B8[0] + 0x14), *(f32*)(lbl_803CC1B8[0] + 0x18),
        *(f32*)(lbl_803CC1B8[0] + 0x1C), *(f32*)(lbl_803CC1B8[0] + 0x20));
    state->depth = -*(f32*)(lbl_803CC1B8[0] + 0x24);
    state->distance += lbl_1_rodata_780C;
    *(u32*)(lbl_803CC1B8[0] + 0x2C) &= ~2U;
    *(u32*)(lbl_803CC1B8[0] + 0x2C) |= 2;
}

// fn_1_23AD8, size:0x7C
void fn_1_23AD8(Mtx44 projection, Vec* camera, Vec* target) {
    camera->x = lbl_1_rodata_77D8;
    camera->y = lbl_1_rodata_77D8;
    camera->z = lbl_1_rodata_7804;
    target->x = lbl_1_rodata_77D8;
    target->y = lbl_1_rodata_77D8;
    target->z = lbl_1_rodata_77D8;
    C_MTXFrustum(projection, lbl_1_rodata_7858, lbl_1_rodata_785C,
        lbl_1_rodata_7860, lbl_1_rodata_7864, lbl_1_rodata_77E4[0], lbl_1_rodata_7868);
}

// fn_1_20F8C, size:0xB4
void fn_1_20F8C(void) {
    s16 phase = *(s16*)(lbl_803CC1B8[0] + 0x10);
    ChallengeTransfer* transfer = *(ChallengeTransfer**)(lbl_803CC1B8[0] + 0x0C);
    switch (phase) {
    case 0:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            transfer->data = (void*)ARAMTransfer(lbl_1_data_104F4, 0, 0, 0);
            (*(s16*)(lbl_803CC1B8[0] + 0x10))++;
        }
        break;
    case 1:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            transfer->complete = 1;
        }
        break;
    }
}

// .text:0x225B8 size:0x8C
void fn_1_225B8(void) {
    u8* queue = lbl_803CC1B8[0];
    switch ((s32)queue[0x25]) {
    case 0:
        fn_1_20DC8();
        queue[0x25]++;
        break;
    case 1:
        if (*(s16*)(queue + 0x10) != 0) {
            *(void (**)(void))queue = fn_1_21408;
        }
        break;
    }
}

// .text:0x1EFF4 size:0x68
void fn_1_1EFF4(void) {
    fn_1_272DC(lbl_1_bss_6D48, 0);
    fn_1_AF4(20, 20, lbl_1_rodata_77E4[0]);
    if (*(u32*)(lbl_803CC1B8[0] + 0x2C) & 2) {
        fn_1_1E5D0(lbl_1_bss_6BF4);
    }
}

// .text:0x1DCE4 size:0x64
void fn_1_1DCE4(void) {
    u8* queue = lbl_803CC1B8[0];
    *(void**)(queue + 0x14) = (void*)ARAMTransfer(lbl_1_data_10674, 0, 0, 0);
    *(void (**)(void))lbl_803CC1B8[0] = fn_1_1DA54;
}

// .text:0x1DD94 size:0x50
void fn_1_1DD94(void) {
    Vec axis;
    axis.x = lbl_1_bss_6BE4[1];
    axis.y = lbl_1_bss_6BE4[2];
    axis.z = lbl_1_bss_6BE4[3];
    fn_80037B18(lbl_1_bss_6BF4, &axis, lbl_1_bss_6BE4[0]);
}

// .text:0x1E8C0 size:0x4C
void fn_1_1E8C0(s32 index) {
    lbl_1_data_1066C[*(s32*)(lbl_803CC1B8[0] + 0x28)]((s16)(index - 8));
}

// .text:0x1DE5C size:0x4
void fn_1_1DE5C(void) {
}

// .text:0x1E28C size:0x4
void fn_1_1E28C(void) {
}

void fn_1_1DDE4(f32 value) {
    lbl_1_bss_6BE4[3] = value;
}

void fn_1_1DDF4(f32 value) {
    lbl_1_bss_6BE4[2] = value;
}

void fn_1_1DE04(f32 value) {
    lbl_1_bss_6BE4[1] = value;
}

void fn_1_1DE14(f32 value) {
    lbl_1_bss_6BE4[0] = value;
}

f32 fn_1_1DE20(void) {
    return lbl_1_bss_6BE4[3];
}

f32 fn_1_1DE30(void) {
    return lbl_1_bss_6BE4[2];
}

f32 fn_1_1DE40(void) {
    return lbl_1_bss_6BE4[1];
}

f32 fn_1_1DE50(void) {
    return lbl_1_bss_6BE4[0];
}

// fn_1_267BC, size:0x38
void fn_1_267BC(void) {
    if (*(s16*)(lbl_803CC1B8[0] + 0x10) != 0) {
        fn_800B0A14_removeQueue(lbl_803CC1B8[0]);
    }
}

// fn_1_24778, size:0x28
void fn_1_24778(void) {
    lbl_803CC1B8[0][0x14] = 0;
    *(void (**)(void))lbl_803CC1B8[0] = fn_1_246AC;
}

// fn_1_20DC8, size:0x38
void fn_1_20DC8(void) {
    u8* object = fn_800B0A5C_insertQueue((void*)fn_1_20BD8, 1);
    object[0x25] = 0;
    *(s16*)(object + 0x10) = 0;
}

// fn_1_1DD48, size:0x4C
f32 fn_1_1DD48(u16 buttons, s32 reverse, f32 value, f32 positive, f32 delta, f32 negative, f32 minimum, f32 maximum) {
    if (buttons & 0x40) delta = positive;
    else if (buttons & 0x20) delta = negative;
    if (reverse) delta = -delta;
    value += delta;
    if (value < minimum) value = minimum;
    if (value > maximum) value = maximum;
    return value;
}
