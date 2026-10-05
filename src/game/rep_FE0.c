#include "game/rep_FE0.h"
#include "header_rep_data.h"
#include "game/rep_1838.h"

extern u8 g_Fielders[];
extern u8 g_UnkAnimation_31EAC[];

// .text:0x0006AF9C size:0x1A8 mapped:0x806AA030
f32 fn_3_6AF9C(int idx) {
    u8* fielder = g_Fielders + idx * 0x268;
    u8* anim = g_UnkAnimation_31EAC + idx * 0x54;
    f32 base = fn_3_9FEA8(-*(f32*)(fielder + 0x48) - 1.5707964f);
    int a;
    int b;
    int diff;
    if (fielder[0x1FC] != 0) {
        return base;
    }
    a = radToShortAngle(base);
    b = radToShortAngle(*(f32*)(anim + 0x28));
    diff = fn_3_9FCA4(b, a);
    if (diff > 0x800) {
        diff -= 0x1000;
    } else if (diff <= -0x800) {
        diff += 0x1000;
    }
    if (diff > 0x600) {
        if (fielder[0x1C7] == 0) {
            b -= 0x280;
        } else {
            b += 0x280;
        }
    } else if (diff < -0x600) {
        if (fielder[0x1C7] == 0) {
            b -= 0x280;
        } else {
            b += 0x280;
        }
    } else if (diff > 0x200) {
        b -= 0x180;
    } else if (diff < -0x200) {
        b += 0x180;
    } else if (diff > 0x180) {
        b -= 0x100;
    } else if (diff < -0x180) {
        b += 0x100;
    } else if (diff > 0xC0) {
        b -= 0x80;
    } else if (diff < -0xC0) {
        b += 0x80;
    } else if (diff > 0x60) {
        b -= 0x40;
    } else if (diff < -0x60) {
        b += 0x40;
    } else {
        return base;
    }
    return shortAngleToRad(b);
}

// .text:0x0006B144 size:0x384 mapped:0x806AA1D8
void fn_3_6B144(void) {
    return;
}

