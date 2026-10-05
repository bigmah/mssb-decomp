#include "game/rep_21F8.h"
#include "header_rep_data.h"
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXPixel.h"

extern f32 fn_3_BFDA4(void*, s32, f32, s32, u8, u8*);

typedef struct {
    f32 f[12];
} M12;
typedef struct {
    u8 pad0[4];
    void* p4;
    u8 pad8[0xC];
    f32 f14;
} E21F8;
extern const M12 lbl_3_rodata_2248;
extern f32 lbl_3_rodata_2278;
extern f32 lbl_3_rodata_227C;
extern f32 lbl_3_rodata_2280;
extern u8 lbl_3_bss_9F20[];
typedef struct {
    u8 pad0[0x26C];
    E21F8 ents[2];
    u8 pad2[0x2E8 - 0x26C - 0x30];
    u8 flag;
    u8 pad3[3];
    f32 tab[4];
} G21F8;
extern G21F8 lbl_3_data_17898;
extern u8 lbl_3_common_bss_35154[];
extern void fn_80034120(Mtx);
extern void fn_3_BF8F8(void*, Mtx, void*, void*);
extern void fn_3_C9590(u8*, s32, f32*, f32);

// .text:0x000C937C size:0x214 mapped:0x80708410
// ~92%: orig keeps (data_17898+0x26C)/(+0x2EC) as separate addi before the index add; we fold the offset into the final add/lfs. Also first base regs/r28 copy loop order differ.
int fn_3_C937C(void) {
    G21F8* d = &lbl_3_data_17898;
    E21F8* e;
    u8* b = lbl_3_bss_9F20;
    Mtx sm;
    M12 id = lbl_3_rodata_2248;
    Mtx a;
    f32 sc;
    f32 t;
    switch (b[0x14]) {
    case 0:
        b[0x14] = 1;
        *(f32*)(b + 0x10) = lbl_3_rodata_2278;
    case 1:
        t = *(f32*)(b + 0x10) + lbl_3_rodata_227C;
        *(f32*)(b + 0x10) = t;
        if (t >= lbl_3_rodata_2280) {
            b[0x14] = 2;
        }
        break;
    }
    fn_80034120(a);
    PSMTXConcat(a, (f32(*)[4])&id, a);
    sc = d->tab[b[0]];
    PSMTXScale(sm, sc, sc, sc);
    PSMTXConcat(a, sm, a);
    e = &d->ents[b[0]];
    e->f14 = *(f32*)(b + 0x10);
    e->p4 = lbl_3_common_bss_35154 + 4;
    if (d->flag != 0) {
        GXSetZMode(1, 7, 1);
    }
    GXSetBlendMode(1, 4, 6, 0);
    fn_3_BF8F8(&d->ents[b[0]], a, b + 4, fn_3_C9590);
    if (d->flag != 0) {
        GXSetZMode(1, 3, 1);
    }
    GXSetBlendMode(1, 4, 5, 0);
    return b[0x14] == 2;
}

// .text:0x000C9590 size:0x1A4 mapped:0x80708624
void fn_3_C9590(u8* o, s32 k, f32* m, f32 t) {
    Mtx tmp;
    f32 v;
    PSMTXIdentity((f32(*)[4])m);
    m[0] = fn_3_BFDA4(*(void**)(o + 0x14), o[0x34], t, k, o[0x3C], o + 0x3C);
    m[5] = fn_3_BFDA4(*(void**)(o + 0x18), o[0x35], t, k, o[0x3D], o + 0x3D);
    if (*(void**)(o + 0x1C) != NULL) {
        v = fn_3_BFDA4(*(void**)(o + 0x1C), o[0x36], t, k, o[0x3E], o + 0x3E);
    } else {
        v = 0.0f;
    }
    m[3] = v;
    if (*(void**)(o + 0x28) != NULL) {
        v = fn_3_BFDA4(*(void**)(o + 0x28), o[0x39], t, k, o[0x41], o + 0x41);
    } else {
        v = 0.0f;
    }
    if (v) {
        PSMTXRotRad(tmp, 'Y', v);
        PSMTXConcat(tmp, (f32(*)[4])m, (f32(*)[4])m);
    }
    if (*(void**)(o + 0x2C) != NULL) {
        v = fn_3_BFDA4(*(void**)(o + 0x2C), o[0x3A], t, k, o[0x42], o + 0x42);
    } else {
        v = 0.0f;
    }
    if (v) {
        PSMTXRotRad(tmp, 'Z', v);
        PSMTXConcat(tmp, (f32(*)[4])m, (f32(*)[4])m);
    }
    fn_3_BFDA4(*(void**)(o + 0x30), o[0x3B], t, k, o[0x43], o + 0x43);
}

extern u8 lbl_3_bss_9F34;

// .text:0x000C9734 size:0x10
void fn_3_C9734(void) {
    lbl_3_bss_9F34 = 2;
}
