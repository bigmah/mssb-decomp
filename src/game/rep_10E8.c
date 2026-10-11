#include "game/rep_10E8.h"
#include "header_rep_data.h"
#include "static/Pad.h"
extern PadState lbl_803C77B8[4];

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

extern Ctl g_Controls[];

// .text:0x0006CD88 size:0x57C mapped:0x806ABE1C
void fn_3_6CD88(int i) {
    return;
}

// .text:0x0006D304 size:0x19C mapped:0x806AC398
void fn_3_6D304(void) {
    int i;
    for (i = 0; i < 4; i++) {
        Ctl* c = &g_Controls[i];
        PadState* r = &lbl_803C77B8[i];
        u16 prev;
        c->pad = 0;
        prev = c->held;
        c->held = r->held;
        c->pressed = r->down;
        c->x8 = r->repeat;
        c->a = r->sticks.stickX;
        c->b = r->sticks.stickY;
        c->trigL = r->analog.triggerLeft;
        c->trigR = r->analog.triggerRight;
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
