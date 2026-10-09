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
extern void fn_800363D8(void*, s32, s32, s32, s32);

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

// fn_2_3735C, size:0xD4
void fn_2_3735C(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2:
        *(s16*)(b + 4) = 0x25;
        break;
    case 1:
    case 5:
    case 8:
    case 0x24:
    case 0x25:
        break;
    }
}

// fn_2_380B0, size:0xF8
void fn_2_380B0(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        *(s16*)(p + 0x14) = 0x15;
        lbl_2_bss_1A8234[0][0x160000 + 0x264E] = 1;
        p[0x28] = 1;
        break;
    case 1: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            p[0x28] = 2;
        }
        break;
    }
    case 2:
        q = *(u8**)(p + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        p[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        p[0x28] = 0;
    }
}

// fn_2_381A8, size:0xF8
void fn_2_381A8(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        *(s16*)(p + 0x14) = 0x15;
        lbl_2_bss_1A8234[0][0x160000 + 0x2838] = 1;
        p[0x28] = 1;
        break;
    case 1: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            p[0x28] = 2;
        }
        break;
    }
    case 2:
        q = *(u8**)(p + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        p[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        p[0x28] = 0;
    }
}

// fn_2_35754, size:0x10C
void fn_2_35754(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 0;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 1:
    case 5:
    case 0x25:
        break;
    }
}

// fn_2_35DB4, size:0x10C
void fn_2_35DB4(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 0;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 1:
    case 5:
    case 0x25:
        break;
    }
}

// fn_2_34F6C, size:0x11C
void fn_2_34F6C(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_38C14, size:0x130
void fn_2_38C14(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        *(s16*)(p + 0x14) = 0x14;
        p[0x28] = 2;
        break;
    case 1: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            lbl_2_bss_1A824C[0][0x19782C] = 1;
            *(s16*)(p + 0x14) = 0x14;
            p[0x28] = 2;
        }
        break;
    }
    case 2: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            *(s16*)(p + 0x14) = 0x14;
            p[0x28] = 3;
        }
        break;
    }
    case 3:
        q = *(u8**)(p + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        p[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        p[0x28] = 0;
    }
}

// fn_2_38D44, size:0x164
void fn_2_38D44(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        if (fn_2_45A84() == 1) {
            *(s16*)(p + 0x14) = 1;
            p[0x28] = 1;
        } else {
            p[0x28] = 4;
        }
        break;
    case 1: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            p[0x28] = 2;
        }
        break;
    }
    case 2:
        lbl_2_bss_1A8234[0][0x160000 + 0x2680] = 1;
        *(s16*)(p + 0x14) = 0x5A;
        p[0x28] = 3;
        break;
    case 3: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            lbl_2_bss_1A8234[0][0x160000 + 0x286A] = 1;
            p[0x28] = 4;
        }
        break;
    }
    case 4:
        q = *(u8**)(p + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        p[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        p[0x28] = 0;
    }
}

// fn_2_37D98, size:0x16C
void fn_2_37D98(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        changeScene(1, 6);
        *(s16*)(p + 0x14) = 0x26AE;
        *(s16*)(p + 0x16) = 0;
        lbl_2_bss_1A8234[0][0x160000 + 0x264B] = 1;
        p[0x28] = 1;
        break;
    case 1: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            p[0x28] = 2;
        }
        *(s16*)(p + 0x16) = *(s16*)(p + 0x16) + 1;
        break;
    }
    case 2:
        if (fn_8006862C(0x1A4, 0) == 0) {
            p[0x28] = 3;
        }
        break;
    case 3:
        changeScene(3, 6);
        p[0x28] = 4;
        break;
    case 4:
        if (lbl_8037169C[0x13] != 0) {
            q = *(u8**)(p + 0xC);
            *(s16*)(q + 0x10) = 1;
            fn_800B0A14_removeQueue(q);
            p[0x28] = 0;
        }
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        p[0x28] = 0;
    }
}

// fn_2_37F04, size:0x1AC
void fn_2_37F04(void) {
    u8* p = lbl_803CC1B8;
    u8* gs = (u8*)&g_d_GameSettings;
    u8* q;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        if (*(s8*)&lbl_2_bss_1A8248[0][0x444B] != -1) {
            *(s16*)(p + 0x14) = 0x14;
            p[0x28] = 1;
        } else {
            p[0x28] = 4;
        }
        break;
    case 1: {
        s16 t;
        if (*(s16*)(p + 0x14) == 4) {
            fn_80062890(0x43);
        }
        t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            p[0x28] = 2;
        }
        break;
    }
    case 2:
        gs[*(s8*)&lbl_2_bss_1A8248[0][0x444B] + 0x3C] = 0;
        *(s8*)&lbl_2_bss_1A8248[0][0x444C] = -1;
        *(s8*)&lbl_2_bss_1A8248[0][0x444B] = -1;
        lbl_2_bss_1A8234[0][0x160000 + 0x281C] = 1;
        *(s16*)(p + 0x14) = 0x3C;
        p[0x28] = 3;
        break;
    case 3: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            p[0x28] = 4;
        }
        break;
    }
    case 4:
        q = *(u8**)(p + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        p[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        p[0x28] = 0;
    }
}

// fn_2_3BC24, size:0x164
void fn_2_3BC24(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        lbl_2_bss_1A8248[0][0x442A] = 1;
        *(s16*)(p + 0x14) = 0x3C;
        p[0x28] = 1;
        break;
    case 1: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            fn_2_90428(0x19);
            fn_2_92654(0x19, 8);
            fn_2_90428(0x1A);
            fn_2_92654(0x1A, 1);
            fn_2_90428(0x1B);
            fn_2_92654(0x1B, 2);
            fn_80062890(0x42);
            *(s16*)(p + 0x14) = 0xB4;
            p[0x28] = 2;
        }
        break;
    }
    case 2: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            p[0x28] = 3;
        }
        break;
    }
    case 3:
        q = *(u8**)(p + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        p[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        p[0x28] = 0;
    }
}

// fn_2_35088, size:0x1B4
void fn_2_35088(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 4;
        *(s16*)(b + 4) = 6;
        break;
    case 6: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        if ((*(u32*)(p + 0x5C) >> 16) == 0) {
            p[0x68] = 0;
            *(s16*)(b + 4) = 7;
        }
        break;
    }
    case 7: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_34060, size:0x1B4
void fn_2_34060(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 4;
        *(s16*)(b + 4) = 6;
        break;
    case 6: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        if ((*(u32*)(p + 0x5C) >> 16) == 0) {
            p[0x68] = 0;
            *(s16*)(b + 4) = 7;
        }
        break;
    }
    case 7: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_34524, size:0x1B4
void fn_2_34524(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 4;
        *(s16*)(b + 4) = 6;
        break;
    case 6: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        if ((*(u32*)(p + 0x5C) >> 16) == 0) {
            p[0x68] = 0;
            *(s16*)(b + 4) = 7;
        }
        break;
    }
    case 7: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_34844, size:0x1B4
void fn_2_34844(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 4;
        *(s16*)(b + 4) = 6;
        break;
    case 6: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        if ((*(u32*)(p + 0x5C) >> 16) == 0) {
            p[0x68] = 0;
            *(s16*)(b + 4) = 7;
        }
        break;
    }
    case 7: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_35860, size:0x1B4
void fn_2_35860(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 4;
        *(s16*)(b + 4) = 6;
        break;
    case 6: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        if ((*(u32*)(p + 0x5C) >> 16) == 0) {
            p[0x68] = 0;
            *(s16*)(b + 4) = 7;
        }
        break;
    }
    case 7: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_35EC0, size:0x1B4
void fn_2_35EC0(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 4;
        *(s16*)(b + 4) = 6;
        break;
    case 6: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        if ((*(u32*)(p + 0x5C) >> 16) == 0) {
            p[0x68] = 0;
            *(s16*)(b + 4) = 7;
        }
        break;
    }
    case 7: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_3697C, size:0x1B4
void fn_2_3697C(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 4;
        *(s16*)(b + 4) = 6;
        break;
    case 6: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        if ((*(u32*)(p + 0x5C) >> 16) == 0) {
            p[0x68] = 0;
            *(s16*)(b + 4) = 7;
        }
        break;
    }
    case 7: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_36F44, size:0x1B4
void fn_2_36F44(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 4;
        *(s16*)(b + 4) = 6;
        break;
    case 6: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        if ((*(u32*)(p + 0x5C) >> 16) == 0) {
            p[0x68] = 0;
            *(s16*)(b + 4) = 7;
        }
        break;
    }
    case 7: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_370F8, size:0x1B4
void fn_2_370F8(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 4;
        *(s16*)(b + 4) = 6;
        break;
    case 6: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        if ((*(u32*)(p + 0x5C) >> 16) == 0) {
            p[0x68] = 0;
            *(s16*)(b + 4) = 7;
        }
        break;
    }
    case 7: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_346D8, size:0x16C
void fn_2_346D8(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5:
        *(s16*)(b + 6) = 0x29;
        *(s16*)(b + 4) = 6;
        break;
    case 6:
        if ((*(s16*)(b + 6))-- <= 0) {
            lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 0;
            *(u32*)(lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2] + 0x54) &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_34214, size:0x188
void fn_2_34214(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5:
        *(s16*)(b + 6) = 0x29;
        *(s16*)(b + 4) = 6;
        break;
    case 6:
        if ((*(s16*)(b + 6))-- <= 0) {
            lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 0;
            *(u32*)(lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2] + 0x54) &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_3439C, size:0x188
void fn_2_3439C(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5:
        *(s16*)(b + 6) = 0x29;
        *(s16*)(b + 4) = 6;
        break;
    case 6:
        if ((*(s16*)(b + 6))-- <= 0) {
            lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 0;
            *(u32*)(lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2] + 0x54) &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

