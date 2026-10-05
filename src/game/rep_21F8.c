#include "game/rep_21F8.h"
#include "header_rep_data.h"
#include "Dolphin/mtx.h"

extern f32 fn_3_BFDA4(void*, s32, f32, s32, u8, u8*);

// .text:0x000C937C size:0x214 mapped:0x80708410
void fn_3_C937C(void) {
    return;
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
