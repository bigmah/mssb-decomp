#include "game/rep_10E8.h"
#include "header_rep_data.h"

#pragma dont_inline on

typedef struct _Ctl {
    u16 stick;
    u16 mag;
    u16 held;
    u16 pressed;
    u16 x8;
    u8 a;
    u8 b;
    u8 trigR;
    u8 trigL;
    u8 pad;
} Ctl;

typedef struct _RawPad {
    u16 s0, s2, s4;
    u8 pad6[10];
    u8 b10, b11;
    u8 pad12[2];
    u8 b14, b15;
    u8 pad16[10];
} RawPad;

extern Ctl g_Controls[];
extern RawPad lbl_803C77B8[];

// .text:0x0006CD88 size:0x57C mapped:0x806ABE1C
void fn_3_6CD88(int i) {
    return;
}

// .text:0x0006D304 size:0x19C mapped:0x806AC398
void fn_3_6D304(void) {
    int i;
    for (i = 0; i < 4; i++) {
        Ctl* c = &g_Controls[i];
        RawPad* r = &lbl_803C77B8[i];
        u16 prev;
        c->pad = 0;
        prev = c->held;
        c->held = r->s0;
        c->pressed = r->s2;
        c->x8 = r->s4;
        c->a = r->b10;
        c->b = r->b11;
        c->trigL = r->b14;
        c->trigR = r->b15;
        if ((c->pressed & 0x40) && (prev & 0x40)) {
            c->pressed = c->pressed & 0xFFBF;
        }
        if ((f32)c->trigL >= 120.0f) {
            if (!(prev & 0x40)) {
                c->pressed |= 0x40;
            }
            c->held |= 0x40;
        }
        if ((c->pressed & 0x20) && (prev & 0x20)) {
            c->pressed = c->pressed & 0xFFDF;
        }
        if ((f32)c->trigR >= 120.0f) {
            if (!(prev & 0x20)) {
                c->pressed |= 0x20;
            }
            c->held |= 0x20;
        }
        fn_3_6CD88(i);
    }
}
