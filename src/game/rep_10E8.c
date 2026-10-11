#include "game/rep_10E8.h"
#include "header_rep_data.h"
#include "static/Pad.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1838.h"
#include "stl/math.h"
extern PadState lbl_803C77B8[4];

#pragma dont_inline on

// .text:0x0006CD88 size:0x57C mapped:0x806ABE1C
// Converts the raw stick of controller i into angle + magnitude (with a dead
// zone of 16 and full tilt at 72), falling back to the D-pad when the stick is
// inside the dead zone. Diagonals are stretched slightly toward the corners.
// NONMATCHING 79%: the original addresses each float constant as its own .rodata symbol
// (lbl_3_rodata_1138..1170, not yet split; 79% measured with externs, 75% with literals) and
// re-derives &g_Controls[i] for the stores (sthx) instead of reusing c
#if NONMATCHING
void fn_3_6CD88(int i) {
    InputStruct* c = &g_Controls[i];
    s8* pX = &c->right_left;
    s8* pY = &c->up_down;
    f32 y = c->up_down;
    f32 x = c->right_left;
    sAng angle = -1;
    s16 mag;
    f32 m;

    m = dolsqrtf2(x * x + y * y) - 16.0f;
    if (m <= 0.0f) {
        u16 b = g_Controls[i].buttonInput;
        if ((b & INPUT_BUTTON_UP) && (b & INPUT_BUTTON_RIGHT)) {
            g_Controls[i].controlStickAngle = 0x200;
            g_Controls[i].controlStickMagnitude = 0x40;
        } else if ((b & INPUT_BUTTON_UP) && (b & INPUT_BUTTON_LEFT)) {
            g_Controls[i].controlStickAngle = 0x600;
            g_Controls[i].controlStickMagnitude = 0x40;
        } else if ((b & INPUT_BUTTON_DOWN) && (b & INPUT_BUTTON_RIGHT)) {
            g_Controls[i].controlStickAngle = 0xE00;
            g_Controls[i].controlStickMagnitude = 0x40;
        } else if ((b & INPUT_BUTTON_DOWN) && (b & INPUT_BUTTON_LEFT)) {
            g_Controls[i].controlStickAngle = 0xA00;
            g_Controls[i].controlStickMagnitude = 0x40;
        } else if (b & INPUT_BUTTON_UP) {
            g_Controls[i].controlStickAngle = 0x400;
            g_Controls[i].controlStickMagnitude = 0x40;
        } else if (b & INPUT_BUTTON_RIGHT) {
            g_Controls[i].controlStickAngle = 0;
            g_Controls[i].controlStickMagnitude = 0x40;
        } else if (b & INPUT_BUTTON_DOWN) {
            g_Controls[i].controlStickAngle = 0xC00;
            g_Controls[i].controlStickMagnitude = 0x40;
        } else if (b & INPUT_BUTTON_LEFT) {
            g_Controls[i].controlStickAngle = 0x800;
            g_Controls[i].controlStickMagnitude = 0x40;
        } else {
            g_Controls[i].controlStickAngle = -1;
            g_Controls[i].controlStickMagnitude = 0;
        }
        return;
    }
    if (m > 56.0f) {
        m = 56.0f;
    }
    mag = 64.0f * m / 56.0f;
    if (mag != 0) {
        s32 a;
        f32 k;
        angle = radToShortAngle(atan2(y, x));
        a = angle % 0x400;
        if (a > 0x200) {
            a = 0x400 - a;
        }
        k = (f32)a * (1.0f / 512.0f) * 0.27208483f;
        x = x * k + x;
        y = y * k + y;
        *pX = x;
        *pY = y;
        m = dolsqrtf2(x * x + y * y) - 16.0f;
        if (m > 56.0f) {
            m = 56.0f;
        }
        mag = 64.0f * m / 56.0f;
    }
    g_Controls[i].controlStickAngle = angle;
    g_Controls[i].controlStickMagnitude = mag;
}
#endif

// .text:0x0006D304 size:0x19C mapped:0x806AC398
void fn_3_6D304(void) {
    int i;
    for (i = 0; i < 4; i++) {
        InputStruct* c = &g_Controls[i];
        PadState* r = &lbl_803C77B8[i];
        u16 prev;
        c->_0E = 0;
        prev = c->buttonInput;
        c->buttonInput = r->held;
        c->newButtonInput = r->down;
        c->_08 = r->repeat;
        c->right_left = r->sticks.stickX;
        c->up_down = r->sticks.stickY;
        c->leftTriggerDistance = r->analog.triggerLeft;
        c->rightTriggerDistance = r->analog.triggerRight;
        if ((c->newButtonInput & 0x40) && (prev & 0x40)) {
            c->newButtonInput = c->newButtonInput & 0xFFBF;
        }
        if ((f32)c->leftTriggerDistance >= 120.0f) {
            if (!(prev & 0x40)) {
                c->newButtonInput |= 0x40;
            }
            c->buttonInput |= 0x40;
        }
        if ((c->newButtonInput & 0x20) && (prev & 0x20)) {
            c->newButtonInput = c->newButtonInput & 0xFFDF;
        }
        if ((f32)c->rightTriggerDistance >= 120.0f) {
            if (!(prev & 0x20)) {
                c->newButtonInput |= 0x20;
            }
            c->buttonInput |= 0x20;
        }
        fn_3_6CD88(i);
    }
}

#pragma dont_inline off
