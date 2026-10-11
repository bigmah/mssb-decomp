#include "game/auto_00_000B7EF0_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

// Stadium state block; only the RNG seed is used here.
typedef struct StadRandState {
    u8 pad0[0x66];
    s16 seed; // 0x66
} StadRandState;

extern StadRandState lbl_3_common_bss_350E4;

// .text:0x000B7EF0 size:0x28 mapped:0x806F6F84
f32 vecDotProduct(VecXYZ* a, VecXYZ* b) {
    return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

// .text:0x000B7F18 size:0x58 mapped:0x806F6FAC
void vecCrossProduct(VecXYZ* out, VecXYZ* a, VecXYZ* b) {
    out->x = (a->y * b->z) - (a->z * b->y);
    out->y = (a->z * b->x) - (a->x * b->z);
    out->z = (a->x * b->y) - (a->y * b->x);
}

// .text:0x000B7F70 size:0x58 mapped:0x806F7004
s16 fn_3_B7F70(s16 range) {
    return 0;
}

