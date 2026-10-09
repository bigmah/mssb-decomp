#include "menus/auto_00_00033E70_text.h"
#include "static/UnknownHomes_Static.h"

extern u8* lbl_80371C30[];
extern u8* lbl_2_bss_1A8244[];
extern u8* lbl_2_bss_1A8248[];
extern s16 fn_2_53BC8(void*);
extern u8* lbl_2_bss_1A8234[];
extern u8* lbl_2_bss_1A824C[];
extern u8* lbl_803CC1B8;
extern void fn_800B0A14_removeQueue(void*);
extern s32 fn_2_45A84();
extern void fn_2_90428(s32);
extern void fn_2_92654(s32, u8);
extern u8 fn_8006862C(s32, s32);
extern u8 lbl_8037169C[];

// fn_2_37430, size:0x2C
void fn_2_37430(u8* a, u8* b) {
    u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
    *(u32*)(p + 0x54) &= ~2;
}

// fn_2_3745C, size:0x4
void fn_2_3745C(void) {
}

// fn_2_37D70, size:0x4
void fn_2_37D70(void) {
}

// fn_2_37D74, size:0x4
void fn_2_37D74(void) {
}

// fn_2_37D78, size:0x4
void fn_2_37D78(void) {
}

// fn_2_37D7C, size:0x4
void fn_2_37D7C(void) {
}

// fn_2_37D80, size:0x4
void fn_2_37D80(void) {
}

// fn_2_37D84, size:0x4
void fn_2_37D84(void) {
}

// fn_2_37D88, size:0x4
void fn_2_37D88(void) {
}

// fn_2_37D8C, size:0x4
void fn_2_37D8C(void) {
}

// fn_2_37D90, size:0x4
void fn_2_37D90(void) {
}

// fn_2_37D94, size:0x4
void fn_2_37D94(void) {
}

// fn_2_38EA8, size:0xA0
void fn_2_38EA8(void) {
    lbl_2_bss_1A8248[0][0x4416] = lbl_2_bss_1A8248[0][0x4415];
    lbl_2_bss_1A8244[0][0xE4 + lbl_2_bss_1A8248[0][0x4415]] = 1;
    if (lbl_2_bss_1A8248[0][0x4415] < 3) {
        u8* e = lbl_2_bss_1A8244[0] + lbl_2_bss_1A8248[0][0x441C];
        if (e[0xE8] == 0) {
            e[0xE8] = 1;
        }
        lbl_2_bss_1A8248[0][0x4415] = lbl_2_bss_1A8248[0][0x4415] + 1;
        e = lbl_2_bss_1A8244[0] + lbl_2_bss_1A8248[0][0x441C];
        e[0xDE] = e[0xDE] + 1;
    }
}

// fn_2_372AC, size:0xB0
void fn_2_372AC(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0:
        *(s16*)(b + 4) = 0x26;
        break;
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 0x25:
        break;
    }
}

