#include "menus/rep_08E8.h"
#include "string.h"

extern void LITXForm(void* light, void* matrix);

#include "Dolphin/vec.h"
extern s32 fn_2_68690(s32 index);
extern void fn_2_68DAC(s32 index, void* result);
extern u32 lbl_803CBD0C[];
extern u32* lbl_2_data_13374[];
extern void fn_80031CA4(Vec*, u32*);

extern u16 lbl_2_data_13238[];

extern u8 lbl_803CBBC0[];
extern u8 lbl_2_data_13228[];
extern void fn_800A7D4C(s32, void*, u8);

extern const f32 lbl_2_rodata_9B0;

#include "static/UnknownHomes_Static.h"
#include "math.h"

extern const f32 lbl_2_rodata_94C;
extern const f32 lbl_2_rodata_9A8;
extern const f32 lbl_2_rodata_9AC;
extern const f32 lbl_2_rodata_9B4;
extern const f32 lbl_2_rodata_9A0;

extern u8 lbl_8036E548[];
extern u8* lbl_2_bss_1A8248[];

extern u8* lbl_2_bss_1A824C[];

extern void* _OSAllocFromHeap(s32 alignment, s32 size);
extern void* fn_2_4917C(void*, s32, s32, s32, s32);
extern void fn_2_513E0(void*, s32, s32, s32, s32, s32, s32, s32);

extern f32 lbl_2_bss_55B8;
extern Vec lbl_2_data_132EC;
extern Vec lbl_2_data_132F8;

// .text:0x48BE0 size:0x128
void fn_2_48BE0(void) {
    f32 x;
    f32 z;
    Vec position;
    Vec direction;
    u8* menu = lbl_2_bss_1A824C[0];
    u8* parameters = lbl_8036E548 + *(s32*)(menu + 0x19769C) * 0x27C + 0xC04;
    memcpy(&position, parameters + 0x34, sizeof(Vec));
    PSVECSubtract(&position, &lbl_2_data_132F8, &direction);
    z = direction.z * lbl_2_rodata_9A0;
    x = direction.x * lbl_2_rodata_9A0;
    direction.x = x;
    direction.z = z;
    if (lbl_2_rodata_94C != x || lbl_2_rodata_94C != z) {
        lbl_2_bss_55B8 = fn_2_4A1E8(direction.z, x);
    }
    memcpy(&lbl_2_data_132F8, parameters + 0x34, sizeof(Vec));
    *(f32*)(parameters + 0x34) = position.x;
    *(f32*)(parameters + 0x38) = position.y;
    *(f32*)(parameters + 0x3C) = position.z;
    *(f32*)(parameters + 0x40) = lbl_2_data_132EC.x;
    *(f32*)(parameters + 0x44) = lbl_2_bss_55B8;
    *(f32*)(parameters + 0x48) = lbl_2_data_132EC.z;
}

// .text:0x49DB8 size:0xA4
void fn_2_49DB8(s32 x, s32 y, s32 number, s32 flags, s32 option, s32 digits,
                s32 style, s32 first, s32 second, s32 third) {
    void* buffer = _OSAllocFromHeap(16, 64);
    fn_2_4917C(buffer, number, flags, digits, style);
    fn_2_513E0(buffer, x, y, option, style, first, second, third);
    if (buffer != NULL) {
        fn_800ACFB0(buffer);
    }
}

// .text:0x49E5C size:0xA0
void fn_2_49E5C(s32 x, s32 y, s32 number, s32 flags, s32 digits, s32 style,
                s32 first, s32 second, s32 third) {
    void* buffer = _OSAllocFromHeap(16, 64);
    fn_2_4917C(buffer, number, flags, digits, style);
    fn_2_513E0(buffer, x, y, 0, style, first, second, third);
    if (buffer != NULL) {
        fn_800ACFB0(buffer);
    }
}

// .text:0x4A234 size:0x90
s16 fn_2_4A234(f32 x, f32 y) {
    s16 angle;
    if (lbl_2_rodata_94C == x) {
        if (y >= lbl_2_rodata_94C) {
            return 0x400;
        }
        return 0xC00;
    }
    angle = (s16)((lbl_2_rodata_9B4 * (f32)atan2(y, x)) / lbl_2_rodata_9A8);
    if (angle < 0) {
        angle += 0x1000;
    }
    return angle;
}

// .text:0x48D08 size:0x4C
void fn_2_48D08(void) {
    u8* menu = lbl_2_bss_1A824C[0];
    s32 index = *(s32*)(menu + 0x19769C);
    f32* parameters = (f32*)(lbl_8036E548 + index * 0x27C + 0xC04);
    parameters[13] = lbl_2_rodata_94C;
    parameters[14] = lbl_2_rodata_94C;
    parameters[15] = lbl_2_rodata_94C;
    parameters[16] = lbl_2_rodata_94C;
    parameters[17] = lbl_2_rodata_94C;
    parameters[18] = lbl_2_rodata_94C;
}

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

// fn_2_489DC, size:0x40
void fn_2_489DC(void) {
    s32 index = lbl_803CBBC0[0];
    fn_800A7D4C(0xC, lbl_2_data_13228 + index * 8, index);
}

// fn_2_49EFC, size:0x80
s32 fn_2_49EFC(const u16* string, u16 style) {
    u32 character;
    s32 width = 0;
    while ((character = *string) != 0x4000) {
        if (character == 0x4003) {
            width += lbl_2_data_13238[style];
        } else if (character == 0x4002) {
            width += (u32)lbl_2_data_13238[style] >> 1;
        } else if (!(character & 0x4000)) {
            if (character & 0x8000) {
                width += lbl_2_data_13238[style];
            } else {
                width += (u32)lbl_2_data_13238[style] >> 1;
            }
        }
        string++;
    }
    return width;
}

// fn_2_46C88, size:0x78
void fn_2_46C88(s32 index) {
    Vec position;
    fn_2_68690(0);
    fn_2_68DAC(index, &position);
    PSVECScale(&position, 2.0f, &position);
    *lbl_2_data_13374[0] = lbl_803CBD0C[0];
    fn_80031CA4(&position, lbl_2_data_13374[0]);
}

// fn_2_48D54, size:0x60
void fn_2_48D54(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        u8* camera = (u8*)fn_80052768_getCamera(0);
        LITXForm(*(void**)(lbl_8036E548 + i * 4 + 0xAC), camera + 0x40);
    }
}
