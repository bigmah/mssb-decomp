#include "game/rep_3B70.h"
#include "header_rep_data.h"
#include "Dolphin/mtx.h"
#include "game/auto_00_0015C230_text.h"

// .data lbl_3_data_271A8..273E0: separate statics reached through one pooled base.
// Quads per frame buffer (lbl_803CBBC0), then the quads [count][buffer].
static u8 lbl_3_data_271A8[4] = {0, 0, 0, 0};
static BallQuad lbl_3_data_271AC[2][2] = {
    {{{0}, fn_3_15C230}, {{0}, fn_3_15C230}},
    {{{0}, fn_3_15C230}, {{0}, fn_3_15C230}},
};
// Quad size (x100000) and colour: hit ball / pitch (read by fn_3_15C230).
BallQuadStyle lbl_3_data_273CC = {100000, 0x80};
BallQuadStyle lbl_3_data_273D4 = {190000, 0x80};

extern u8 lbl_803CBBC0;
extern u8 lbl_3_common_bss_35154[];
extern u8 g_Ball[];
extern u8 g_GameLogic[];
extern void* fn_80052734(s32 index);
extern void fn_80024390(f32* a, f32* b, s32 c);
extern void fn_800340F4(void*);
extern void fn_800A7D4C(s32, void*);
extern const f32 lbl_3_rodata_3BC0;
extern const f32 lbl_3_rodata_3BC4;
extern const f32 lbl_3_rodata_3BC8;

// Queues a ball quad (drawn by fn_3_15C230) at the ball position, facing the camera.
// .text:0x0015C3F8 size:0x1FC mapped:0x8079B48C
void fn_3_15C3F8(void) {
    Mtx sp8;
    f32 s;
    f32 t;
    u8* c;
    BallQuad* e;
    s32 sel;
    s32 i;
    c = &lbl_3_data_271A8[lbl_803CBBC0];
    e = &lbl_3_data_271AC[(*c)++][lbl_803CBBC0];
    e->counter = c;
    fn_80024390(fn_80052734(0), e->proj, 0);
    PSMTXTrans(e->m, *(f32*)(lbl_3_common_bss_35154 + 0x440), *(f32*)(lbl_3_common_bss_35154 + 0x444), *(f32*)(lbl_3_common_bss_35154 + 0x448));
    PSMTXConcat((f32(*)[4])((u8*)fn_80052734(0) + 0x40), e->m, e->m);
    if (*(s16*)(g_GameLogic + 0x10A) >= 0) {
        sel = 2;
    } else {
        sel = *(s16*)(g_Ball + 0x1B66) > 0;
    }
    if (sel == 2) {
        t = (f32)lbl_3_data_273D4.size / lbl_3_rodata_3BC0;
        s = t * lbl_3_rodata_3BC4;
    } else {
        t = (f32)lbl_3_data_273CC.size / lbl_3_rodata_3BC0;
        s = t * lbl_3_rodata_3BC4;
    }
    fn_800340F4(sp8);
    e->v[3].x = -s;
    e->v[1].y = -s;
    e->v[0].y = -s;
    e->v[0].x = -s;
    e->v[1].x = s;
    e->v[3].y = s;
    e->v[2].y = s;
    e->v[2].x = s;
    e->v[3].z = lbl_3_rodata_3BC8;
    e->v[2].z = lbl_3_rodata_3BC8;
    e->v[1].z = lbl_3_rodata_3BC8;
    e->v[0].z = lbl_3_rodata_3BC8;
    for (i = 0; i < 4; i++) {
        PSMTXMultVec(sp8, &e->v[i], &e->v[i]);
    }
    fn_800A7D4C(0xB, e);
}
