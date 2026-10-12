#include "game/rep_3B70.h"
#define REP_HEADER_FN repHeader_3B70
#include "header_rep_inline.h"
#include "Dolphin/mtx.h"
#include "game/auto_00_0015C230_text.h"

typedef struct {
    void* next;                 // draw-list link
    void (*draw)(BallQuad* q);  // fn_3_15C230
    Mtx m;
    u8 pad38[0x1C];
    Vec q[4];
    u8* cp;
} Ent3B70;

typedef struct {
    u8 cnt[4];
    Ent3B70 e[2][2];
} Dat3B70;

extern u8 lbl_803CBBC0;
extern Dat3B70 lbl_3_data_271A8;
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

// 94%: saved regs swapped (orig data base r31 / entry r30; ours r30 / r31), float temp regs rotated in the sel==2 branches
// .text:0x0015C3F8 size:0x1FC mapped:0x8079B48C
void fn_3_15C3F8(void) {
    Mtx sp8;
    f32 s;
    u8* c;
    Ent3B70* e;
    u8* q;
    Vec* t;
    s32 sel;
    s32 i;
    q = (u8*)&lbl_3_data_271A8;
    c = q;
    c += lbl_803CBBC0;
    e = (Ent3B70*)(q + 4);
    e = (Ent3B70*)((u8*)e + (*c * 0x110 + lbl_803CBBC0 * 0x88));
    *c += 1;
    e->cp = c;
    fn_80024390(fn_80052734(0), (f32*)((u8*)e + 0x38), 0);
    PSMTXTrans(e->m, *(f32*)(lbl_3_common_bss_35154 + 0x440), *(f32*)(lbl_3_common_bss_35154 + 0x444), *(f32*)(lbl_3_common_bss_35154 + 0x448));
    PSMTXConcat((f32(*)[4])((u8*)fn_80052734(0) + 0x40), e->m, e->m);
    if (*(s16*)(g_GameLogic + 0x10A) >= 0) {
        sel = 2;
    } else {
        sel = *(s16*)(g_Ball + 0x1B66) > 0;
    }
    if (sel == 2) {
        s = lbl_3_rodata_3BC4 * ((f32)*(s32*)(q + 0x22C) / lbl_3_rodata_3BC0);
    } else {
        s = lbl_3_rodata_3BC4 * ((f32)*(s32*)(q + 0x224) / lbl_3_rodata_3BC0);
    }
    fn_800340F4(sp8);
    e->q[3].x = -s;
    *(f32*)((u8*)e + 0x64) = -s;
    *(f32*)((u8*)e + 0x58) = -s;
    *(f32*)((u8*)e + 0x54) = -s;
    *(f32*)((u8*)e + 0x60) = s;
    *(f32*)((u8*)e + 0x7C) = s;
    *(f32*)((u8*)e + 0x70) = s;
    *(f32*)((u8*)e + 0x6C) = s;
    *(f32*)((u8*)e + 0x80) = lbl_3_rodata_3BC8;
    *(f32*)((u8*)e + 0x74) = lbl_3_rodata_3BC8;
    *(f32*)((u8*)e + 0x68) = lbl_3_rodata_3BC8;
    *(f32*)((u8*)e + 0x5C) = lbl_3_rodata_3BC8;
    q = (u8*)e;
    i = 0;
    do {
        t = (Vec*)(q + 0x54);
        PSMTXMultVec(sp8, t, t);
        i++;
        q += 0xC;
    } while (i < 4);
    fn_800A7D4C(0xB, e);
}

// .data 0x000271A8..0x000273E0
Dat3B70 lbl_3_data_271A8 = {
    {0, 0, 0, 0},
    {
        {
            {
                NULL,
                fn_3_15C230,
                {{0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
                NULL,
            },
            {
                NULL,
                fn_3_15C230,
                {{0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
                NULL,
            },
        },
        {
            {
                NULL,
                fn_3_15C230,
                {{0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
                NULL,
            },
            {
                NULL,
                fn_3_15C230,
                {{0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
                NULL,
            },
        },
    },
};
QuadColor lbl_3_data_273CC = {100000, 128};
QuadColor2 lbl_3_data_273D4 = {190000, 128, 0};

