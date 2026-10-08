#include "menus/rep_08E8.h"

extern const f32 lbl_2_rodata_9B0;

#include "static/UnknownHomes_Static.h"
#include "math.h"

extern const f32 lbl_2_rodata_94C;
extern const f32 lbl_2_rodata_9A8;
extern const f32 lbl_2_rodata_9AC;
extern const f32 lbl_2_rodata_9B4;

extern u8 lbl_8036E548[];
extern u8* lbl_2_bss_1A8248[];

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

s16 fn_2_4A310(s16 a, s16 b) {
    int difference = a - b;
    difference = (s16)((difference < 0) ? -difference : difference);
    if (difference > 0x800) return 0x1000 - difference;
    return difference;
}

u16* fn_2_4A094(u16* destination, const u16* source) {
    u16* result = destination;
    while (*source != 0x4000) *destination++ = *source++;
    *destination = *source;
    return result;
}

s32 fn_2_4A068(const u16* string) {
    const u16* end = string;
    while (*end != 0x4000) end++;
    return end - string;
}

s32 fn_2_46D00(void) {
    u8* menu = lbl_2_bss_1A8248[0];
    if (menu[0x441C] == 5 && menu[0x4422] >= 6) return 1;
    return 0;
}

void fn_2_481B8(void) {
    u8* camera = (u8*)fn_80052768_getCamera(0);
    fn_800BD670(*(void**)(lbl_8036E548 + 0x60), (u32)(camera + 0x40));
}

// fn_2_474FC, size:0x44
void fn_2_474FC(void) {
    if (*(void**)(lbl_8036E548 + 0x2C88) != 0) {
        fn_800ACFB0(*(void**)(lbl_8036E548 + 0x2C88));
        *(void**)(lbl_8036E548 + 0x2C88) = 0;
    }
}

// fn_2_4777C, size:0x44
void fn_2_4777C(void) {
    if (*(void**)(lbl_8036E548 + 0x2C8C) != 0) {
        fn_800ACFB0(*(void**)(lbl_8036E548 + 0x2C8C));
        *(void**)(lbl_8036E548 + 0x2C8C) = 0;
    }
}

// fn_2_4A1E8, size:0x4C
f32 fn_2_4A1E8(f32 x, f32 y) {
    if (x == 0.0f && y == 0.0f) return 0.0f;
    return (f32)atan2(y, x);
}

// fn_2_4A2C4, size:0x4C
s32 fn_2_4A2C4(f32 angle) {
    if (angle < lbl_2_rodata_94C) angle = lbl_2_rodata_9A8 + angle;
    return (s32)((lbl_2_rodata_9B4 * angle) / lbl_2_rodata_9AC);
}

// fn_2_47AFC, size:0x28
void fn_2_47AFC(void) {
    s32 i;
    for (i = 0; i < 13; i++) {}
}

// fn_2_4A18C, size:0x5C
f32 fn_2_4A18C(f32 angle) {
    if (angle >= lbl_2_rodata_9A8) {
        while (angle >= lbl_2_rodata_9A8) angle -= lbl_2_rodata_9AC;
    }
    if (angle < lbl_2_rodata_9B0) {
        while (angle < lbl_2_rodata_9B0) angle = lbl_2_rodata_9AC + angle;
    }
    return angle;
}

// fn_2_46D34, size:0x60
void fn_2_46D34(s32 delta) {
    *(s16*)(lbl_2_bss_1A8248[0] + 0x43BE) = *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC);
    *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) += delta;
    if (*(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) > 999) {
        *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) = 999;
    }
    if (*(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) < 0) {
        *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) = 0;
    }
}
