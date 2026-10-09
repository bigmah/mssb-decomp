#include "menus/rep_0F60.h"

#include "static/UnknownHomes_Static.h"


extern u8* lbl_2_bss_1A8248[];
extern u8 lbl_8036E548[];
extern u8* lbl_2_bss_340140;
typedef struct {
    u8 pad0[0x25D];
    u8 enabled;
    u8 pad25E[0x1E];
} MenuEntry;

// fn_2_8D24C, size:0x24
void fn_2_8D24C(u8* object) {
    fn_800B9AA8(*(void**)(object + 0x70));
}

// fn_2_8B118, size:0x40
void fn_2_8B118(f32 value) {
    if (value) {
        lbl_2_bss_1A8248[0][0x307A] = 3;
    } else {
        lbl_2_bss_1A8248[0][0x307A] = 0;
    }
}

// fn_2_8CC88, size:0x24
s32 fn_2_8CC88(s32 index) {
    u8* base = lbl_8036E548;
    u8* object;
    base += index * 4;
    object = *(u8**)(base + 0x2C50);
    return !*(s16*)(object + 0x68);
}

// fn_2_8CCAC, size:0x20
void fn_2_8CCAC(s32 index, u8 value) {
    MenuEntry* entry = (MenuEntry*)(lbl_2_bss_340140 + index * 0x27C + 0xC04);
    if (entry != NULL) {
        entry->enabled = value;
    }
}

// fn_2_8CCCC, size:0x8C
void fn_2_8CCCC(s32 index, s32 a, s32 b, u8 mode, s32 c, s32 d, s32 e, s32 f) {
    u8* p;
    { u8* base = lbl_2_bss_340140; base += index * 4; p = *(u8**)(base + 0x2C50); }
    if (p == NULL) return;
    if (mode == 1 && *(s16*)(p + 0x62) == a) return;
    if (mode == 3) mode = 1;
    *(s16*)(p + 0x64) = a;
    *(s16*)(p + 0x6C) = d;
    p[0x260] = b;
    p[0x25E] = mode;
    p[0x263] = c;
    p[0x266] = e;
    p[0x26D] = 0;
    if (f == -1) {
        p[0x26A] = 5;
    } else {
        p[0x26A] = f;
    }
    *(s16*)(p + 0x66) = -1;
}
