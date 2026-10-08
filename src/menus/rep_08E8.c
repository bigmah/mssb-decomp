#include "menus/rep_08E8.h"


// .text:0x4A064 size:0x4
void fn_2_4A064(void) {
}

// .text:0x474F8 size:0x4
void fn_2_474F8(void) {
}

s16 fn_2_4A150(s16 angle) {
    if (angle < 0) {
        while (angle < 0) angle += 0x1000;
    }
    if (angle >= 0x1000) {
        while (angle >= 0x1000) angle -= 0x1000;
    }
    return angle;
}
