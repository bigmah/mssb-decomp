#include "game/rep_4138.h"
#define REP_HEADER_FN repHeader_4138
#include "header_rep_inline.h"
#include "Dolphin/stl.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_80011640.h" // CharMgr

// Scoreboard overlay: two-digit counters (score, outs, ...) drawn as textured quads.
// Functions are written in reverse address order (-inline deferred emits them last-first).

extern u8 lbl_803CBBC0[];
extern GameScores g_Scores;
extern void fn_800A7D4C(int, void*);
extern s32 fn_8005268C(void);
extern void fn_80033B58(void*, s32, s32, s32);

// Draw-list node queued with fn_800A7D4C (one per frame buffer, indexed by lbl_803CBBC0).
typedef struct ScoreDrawNode {
    /* 0x0 */ void* next; // draw-list link, set by fn_800A7D4C
    /* 0x4 */ void (*draw)(void* node); // draw-list callbacks get their node
} ScoreDrawNode;

// Digit quad: x, y, z of the four corners.
static f32 lbl_3_data_2A448[12] = {
    0.0f, 0.0f, 101.785f,
    1.8f, 0.0f, 101.785f,
    1.8f, 2.28f, 101.785f,
    0.0f, 2.28f, 101.785f,
};
// Digit quad: u, v of the four corners (u is offset by digit * 0.0977).
static f32 lbl_3_data_2A478[8] = {
    0.0f, 0.0f,
    0.09765625f, 0.0f,
    0.09765625f, 1.0f,
    0.0f, 1.0f,
};
static ScoreDrawNode lbl_3_data_2A498[2] = {
    { NULL, fn_3_16DFC4 },
    { NULL, fn_3_16DFC4 },
};

// fn_3_16D810 constants. As one-element arrays they stay real objects: where fn_3_16D810 is
// inlined into fn_3_16DB6C the original loads them through addi+lfs 0, which literals do not give.
static const GXColor lbl_3_rodata_4188[1] = { { 0xFF, 0xFF, 0xFF, 0xFF } };
static const f32 lbl_3_rodata_418C[1] = { 50.0f };
static const f32 lbl_3_rodata_4190[1] = { 0.001953125f };

static s32 lbl_3_bss_D6F0[9];
static u8 lbl_3_bss_D6EC;
static s32 lbl_3_bss_D6E8;
static u16* lbl_3_bss_D6E4;
static u32 lbl_3_bss_D6E0;

void fn_3_16E1EC(void);

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

// .text:0x0016E328 size:0x10
void fn_3_16E328(void) {
    lbl_3_bss_D6EC = 1;
}

// .text:0x0016E2FC
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

// .text:0x0016E1EC size:0x110
void fn_3_16E1EC(void) {
    s32 x;
    u32 idx;
    if ((lbl_3_bss_D6E4 == 0) | (lbl_3_bss_D6EC | (lbl_8036E548._3088 == 0))) {
        lbl_3_bss_D6E4 = NULL;
        lbl_3_bss_D6E8 = -1;
        lbl_3_bss_D6EC = 0;
        REMOVE_QUEUE_NOARG();
    }
    x = g_GameLogic.gameStatus;
    if ((x != 0x13) & (x != 0x14)) {
        fn_3_16E1A0();
    }
    idx = lbl_803CBBC0[0];
    fn_800A7D4C(1, &lbl_3_data_2A498[idx]);
}

// .text:0x0016E1A0
void fn_3_16E1A0(void) {
    s32* o = lbl_3_bss_D6F0;
    o[0] = g_Scores.team[1].runs[0];
    o[1] = g_Scores.team[0].runs[0];
    o[2] = g_Scores.inning;
    o[3] = g_Strikes.strikes;
    o[4] = g_Strikes.balls;
    o[5] = g_Strikes.outs;
}

// .text:0x0016DFC4 size:0x1DC
void fn_3_16DFC4(void* node) {
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

// .text:0x0016DB6C size:0x458 mapped:0x807ACC00
// Draws two-digit counter i (0-5, see fn_3_16E1A0) of the scoreboard overlay.
void fn_3_16DB6C(u8 i) {
    f32 x;
    f32 y;
    s32 value;
    s32 tens;

    switch (i) {
    case 0:
        x = -15.438f;
        y = -12.96f;
        value = lbl_3_bss_D6F0[0];
        break;
    case 1:
        x = -10.878f;
        y = -12.96f;
        value = lbl_3_bss_D6F0[2];
        break;
    case 2:
        x = -6.318f;
        y = -12.96f;
        value = lbl_3_bss_D6F0[1];
        break;
    case 3:
        x = -15.438f;
        y = -9.0f;
        value = lbl_3_bss_D6F0[4];
        break;
    case 4:
        x = -10.878f;
        y = -9.0f;
        value = lbl_3_bss_D6F0[3];
        break;
    case 5:
        x = -6.318f;
        y = -9.0f;
        value = lbl_3_bss_D6F0[5];
        break;
    default:
        return;
    }
    tens = (value % 100) / 10;
    if (tens != 0) {
        fn_3_16D810(tens, x, y);
    }
    x += 1.8f;
    fn_3_16D810(value % 10, x, y);
}


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

// .text:0x0016D810 size:0x1A0 mapped:0x807AC8A4
// Draws digit n as a quad at (x, y).
void fn_3_16D810(s32 n, f32 x, f32 y) {
    s32 i;
    GXColor col = lbl_3_rodata_4188[0];
    f32 t = lbl_3_rodata_418C[0] * (f32)n;
    f32 u = t * lbl_3_rodata_4190[0];
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(x + lbl_3_data_2A448[i * 3], y + lbl_3_data_2A448[i * 3 + 1], lbl_3_data_2A448[i * 3 + 2]);
        GXColor1u32(*(u32*)&col);
        GXTexCoord2f32(u + lbl_3_data_2A478[i * 2], lbl_3_data_2A478[i * 2 + 1]);
    }
}
