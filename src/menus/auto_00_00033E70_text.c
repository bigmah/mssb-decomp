#include "menus/auto_00_00033E70_text.h"
#include "static/UnknownHomes_Static.h"

extern void fn_2_4E7EC(void);
extern void fn_2_4E824(void);
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
extern void fn_80036134(void*, s32, s32, s32);
extern s16 fn_8000F988(void*, s16, u16, s32, s32, s32);
extern u8 lbl_80366B18[];
extern u8 lbl_2_data_C924[];
extern u8 lbl_2_data_C8F8[];
extern u8 lbl_2_data_C904[];
extern void fn_8000FE08(s16, s32, s32);

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

// fn_2_34BCC, size:0x1E0
void fn_2_34BCC(u8* a, u8* b) {
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
        u8* p;
        *(u32*)(lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2] + 0x5C) = 0;
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5:
        *(s16*)(b + 6) = 3;
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

// fn_2_349F8, size:0x1D4
void fn_2_349F8(u8* a, u8* b) {
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
        u8* p;
        *(u32*)(lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2] + 0x5C) = 0;
        fn_800363D8(a, *(s16*)(b + 0xE), 1, 0xCD, lbl_2_bss_1A8248[0][0x4415] - 1);
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5:
        *(s16*)(b + 6) = 3;
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

// fn_2_36074, size:0x190
void fn_2_36074(u8* a, u8* b) {
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
        u8* p;
        *(u32*)(lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2] + 0x5C) = 0;
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 0;
        *(s16*)(b + 4) = 6;
        break;
    case 6:
        *(u32*)(lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2] + 0x54) &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}


// fn_2_36204, size:0x1C4
void fn_2_36204(u8* a, u8* b) {
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
        if (((s16*)(lbl_2_bss_1A824C[0] + 0x1972AC))[*(s16*)(b + 0xA)] == 3) {
            u8* p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
            *(u32*)(p + 0x54) |= 2;
            lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        }
        *(s16*)(b + 4) = 0x25;
        break;
    case 5:
        if (((s16*)(lbl_2_bss_1A824C[0] + 0x1972AC))[*(s16*)(b + 0xA)] == 3) {
            lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 0;
        }
        *(s16*)(b + 4) = 6;
        break;
    case 6:
        *(u32*)(lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2] + 0x54) &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}


// fn_2_36590, size:0x1C0
void fn_2_36590(u8* a, u8* b) {
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
        fn_80036134(a, 0x12, *(s16*)(lbl_2_bss_1A824C[0] + 0x1972B0), *(s16*)(b + 0xE));
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 0x25:
        fn_80036134(a, 0x12, *(s16*)(lbl_2_bss_1A824C[0] + 0x1972B0), *(s16*)(b + 0xE));
        break;
    case 5:
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 0;
        *(s16*)(b + 4) = 6;
        break;
    case 6:
        *(u32*)(lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2] + 0x54) &= ~2;
        break;
    case 1:
        break;
    }
}


// fn_2_363C8, size:0x1C8
void fn_2_363C8(u8* a, u8* b) {
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
        fn_80036134(a, 0x293, *(s16*)(lbl_2_bss_1A824C[0] + 0x1972B0) + 1, *(s16*)(b + 0xE));
        *(s16*)(b + 4) = 0x25;
        break;
    }
    case 0x25:
        fn_80036134(a, 0x293, *(s16*)(lbl_2_bss_1A824C[0] + 0x1972B0) + 1, *(s16*)(b + 0xE));
        break;
    case 5:
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 0;
        *(s16*)(b + 4) = 6;
        break;
    case 6:
        *(u32*)(lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2] + 0x54) &= ~2;
        break;
    case 1:
        break;
    }
}


// fn_2_36B30, size:0x1E4
void fn_2_36B30(u8* a, u8* b) {
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
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 0x25;
        break;
    case 0x25:
        if (((s16*)(lbl_2_bss_1A824C[0] + 0x197298))[*(s16*)(b + 0xA)] != 0) {
            *(u32*)(lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2] + 0x54) |= 2;
        } else {
            *(u32*)(lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2] + 0x54) &= ~2;
        }
        break;
    case 5:
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 0;
        *(s16*)(b + 4) = 6;
        break;
    case 6:
        *(u32*)(lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2] + 0x54) &= ~2;
        break;
    case 1:
        break;
    }
}



// fn_2_3523C, size:0x1C0
void fn_2_3523C(u8* a, u8* b) {
    u8* p;
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 0x12) = 0xFF;
        *(s16*)(b + 0x14) = fn_8000F988(a, *(s16*)(b + 0xE), *(s16*)(b + 0x10), 4, 0x312, 0);
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80366B18[*(s16*)(b + 0x14) * 0x38 + 0x2F] = 1;
        *(s16*)(b + 4) = 3;
        break;
    }
    case 3:
        *(s16*)(b + 4) = 0x25;
        break;
    case 0x25:
        *(s16*)(b + 4) = 0x25;
        break;
    case 5: {
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    }
    p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
    *(u32*)(p + 0x58) = *(s16*)(b + 0x12) | (*(u32*)(p + 0x58) & 0xFFFFFF00);
}

// fn_2_34D70, size:0x1FC
void fn_2_34D70(u8* a, u8* b) {
    u8* p;
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 0x12) = 0xFF;
        *(s16*)(b + 0x14) = fn_8000F988(a, *(s16*)(b + 0xE), *(s16*)(b + 0x10), 4, 0x306, 0);
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2: {
        fn_8000FE08(*(s16*)(b + 0x14), 4, lbl_2_bss_1A8248[0][0x4415] + 0x305);
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80366B18[*(s16*)(b + 0x14) * 0x38 + 0x2F] = 1;
        *(s16*)(b + 4) = 3;
        break;
    }
    case 3:
        *(s16*)(b + 4) = 0x25;
        break;
    case 0x25:
        *(s16*)(b + 4) = 0x25;
        break;
    case 5: {
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    }
    lbl_80366B18[*(s16*)(b + 0x14) * 0x38 + 0x2F] = 1;
    p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
    *(u32*)(p + 0x58) = *(s16*)(b + 0x12) | (*(u32*)(p + 0x58) & 0xFFFFFF00);
}

// fn_2_33E70, size:0x1F0
void fn_2_33E70(u8* a, u8* b) {
    u8* p;
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0:
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    case 2:
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        fn_800363D8(a, *(s16*)(b + 0xE), 1, 0x2E, ((s16*)(lbl_2_data_C924 + *(s16*)(b + 0xA) * 0x18))[lbl_2_bss_1A824C[0][0x19785B]]);
        break;
    case 5:
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 4;
        *(s16*)(b + 4) = 6;
        break;
    case 6:
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        if ((*(u32*)(p + 0x5C) >> 16) == 0) {
            p[0x68] = 0;
            *(s16*)(b + 4) = 7;
        }
        break;
    case 7:
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_36D04, size:0x240
void fn_2_36D04(u8* a, u8* b) {
    u8* p;
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0:
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    case 2:
        *(u32*)(lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2] + 0x5C) = 0xF0000;
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 3;
        break;
    case 3:
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        if ((*(u32*)(p + 0x5C) >> 16) >= ((s16*)lbl_2_data_C8F8)[*(s16*)(b + 0x10)]) {
            p[0x68] = 0;
            *(s16*)(b + 4) = 0x25;
        }
        break;
    case 5:
        *(u32*)(lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2] + 0x5C) = ((s16*)lbl_2_data_C8F8)[*(s16*)(b + 0x10)] << 16;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 6;
        break;
    case 6:
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        if ((*(u32*)(p + 0x5C) >> 16) >= ((s16*)lbl_2_data_C904)[*(s16*)(b + 0x10)]) {
            p[0x68] = 0;
            *(s16*)(b + 4) = 7;
        }
        break;
    case 7:
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        break;
    case 1:
    case 4:
    case 0x25:
        break;
    }
}

// fn_2_36750, size:0x22C
void fn_2_36750(u8* a, u8* b) {
    u8* p;
    s16 v;
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0:
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    case 2:
        if (*(s16*)(b + 0xA) == 0) {
            v = *(s16*)(lbl_2_bss_1A824C[0] + 0x1972AA);
            if (v != 0xA) {
                fn_800363D8(a, *(s16*)(b + 0xE), 1, 0x54, v);
            }
        } else {
            fn_800363D8(a, *(s16*)(b + 0xE), 1, 0x54, lbl_2_bss_1A8248[0][0x441C]);
        }
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) |= 2;
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 1;
        *(s16*)(b + 4) = 3;
        break;
    case 3:
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        if ((*(u32*)(p + 0x5C) >> 16) >= 0x15) {
            p[0x68] = 0;
            *(s16*)(b + 4) = 0x25;
        }
        break;
    case 5:
        lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2][0x68] = 4;
        *(s16*)(b + 4) = 6;
        break;
    case 6:
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        if ((*(u32*)(p + 0x5C) >> 16) == 0) {
            p[0x68] = 0;
            *(s16*)(b + 4) = 7;
        }
        break;
    case 7:
        p = lbl_80371C30[(*(u16*)(a + 0x14) + *(s16*)(b + 0xE)) * 2];
        *(u32*)(p + 0x54) &= ~2;
        break;
    case 1:
    case 4:
    case 0x25:
        break;
    }
}

typedef struct Fn37460Data {
    u8 pad0[4];
    s32 size;
    void* alt;
    void* buf;
    void* heap;
} Fn37460Data;

extern Fn37460Data lbl_2_bss_15A0;
extern u8 lbl_2_data_12180[];
extern void* _OSAllocFromHeap(s32, s32);
extern void* memset(void*, int, u32);
extern void fn_80009018(void*);
extern void fn_800AD070(void);
extern void fn_800AD500(void*, void*);
extern s32 fn_800AD6BC(void*);
extern s32 fn_800AD780(void*);
extern void fn_800AD95C(void*, s32);
extern void fn_800AD9F4(void*);
extern s32 fn_800ADAFC(void);
extern s32 fn_800ADB04(void*, void*, s32, s32);
extern void fn_800ADBFC(void);
extern void fn_800ADC40(void*, s32);

// fn_2_37460, size:0x1D0
void fn_2_37460(void) {
    Fn37460Data* d = &lbl_2_bss_15A0;
    u8* o = lbl_803CC1B8;
    void* p;
    s32 sz;
    switch ((s8)o[0x28]) {
    case 0:
        fn_2_4E824();
        p = _OSAllocFromHeap(0x20, 0x1C0);
        d->heap = p;
        memset(p, 0, 0x1C0);
        d->size = 0x400000;
        p = _OSAllocFromHeap(0x20, 0x400000);
        d->alt = p;
        fn_800ADC40(p, d->size);
        o[0x28]++;
        return;
    case 1:
        if (fn_800ADB04(lbl_2_data_12180, d->heap, 1, 0) != 0) {
            fn_80009018(d->heap);
            o[0x28]++;
        }
        break;
    case 2:
        if (fn_800ADAFC() != 0) {
            sz = fn_800AD6BC(d->heap);
            p = _OSAllocFromHeap(0x20, sz);
            d->buf = p;
            fn_800AD500(d->heap, p);
            fn_800AD95C(d->heap, 1);
            o[0x28]++;
            return;
        }
        break;
    case 3:
        fn_800AD070();
        if (fn_800AD780(d->heap) != 0) {
            o[0x28]++;
            return;
        }
        break;
    case 4:
        if (fn_800AD780(d->heap) != 0) {
            fn_80009018(0);
            fn_800AD9F4(d->heap);
            fn_800ADBFC();
            o[0x28]++;
            return;
        }
        break;
    case 5:
        fn_2_4E7EC();
        p = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)((u8*)p + 0x10) = 1;
        fn_800B0A14_removeQueue(p);
        o[0x28] = 0;
        return;
    }
}

// fn_2_38A40, size:0x1D4
void fn_2_38A40(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        lbl_2_bss_1A8248[0][0x44F2] = 3;
        *(s16*)(p + 0x14) = 0xF;
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x19729C) != 0) {
            lbl_2_bss_1A8234[0][0x160000 + 0x264C] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x264D] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x264E] = 1;
        }
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x19729E) != 0) {
            lbl_2_bss_1A8234[0][0x160000 + 0x2652] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2653] = 1;
        }
        if ((s8)lbl_2_bss_1A824C[0][0x1978FA] == 0) {
            *(u32*)(lbl_2_bss_1A824C[0] + 0x1976A8) = fn_80062890(0x11);
        }
        lbl_2_bss_1A824C[0][0x1978FA] = 0;
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

extern void fn_2_4A6E8(void);

// fn_2_3BA40, size:0x1E4
void fn_2_3BA40(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    u8* e;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        *(s16*)(p + 0x14) = 0x3C;
        fn_2_4A6E8();
        lbl_2_bss_1A8234[0][0x160000 + 0x2669] = 1;
        lbl_2_bss_1A8234[0][0x160000 + 0x266A] = 1;
        lbl_2_bss_1A8234[0][0x160000 + 0x266B] = 1;
        lbl_2_bss_1A8234[0][0x160000 + 0x266C] = 1;
        lbl_2_bss_1A8234[0][0x160000 + 0x266D] = 1;
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
        e = (u8*)&lbl_803C77B8;
        e += *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20;
        if (*(u16*)(e + 2) & 0x300) {
            *(s16*)(p + 0x14) = 0x32;
            lbl_2_bss_1A8234[0][0x160000 + 0x2853] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2854] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2855] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2856] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2857] = 1;
            p[0x28] = 3;
        }
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

// fn_2_38824, size:0x21C
void fn_2_38824(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        *(s16*)(p + 0x14) = 0xA;
        if (*(s16*)(p + 0x18) == 1) {
            *(s16*)(p + 0x18) = 0;
            switch (*(s16*)(lbl_2_bss_1A824C[0] + 0x1972AC)) {
            case 0:
                lbl_2_bss_1A8234[0][0x160000 + 0x264F] = 1;
                break;
            case 1:
                lbl_2_bss_1A8234[0][0x160000 + 0x2650] = 1;
                break;
            case 2:
            case 3:
                lbl_2_bss_1A8234[0][0x160000 + 0x2651] = 1;
                break;
            }
        }
        if (*(s16*)(p + 0x1A) == 1) {
            *(s16*)(p + 0x1A) = 0;
            switch (*(s16*)(lbl_2_bss_1A824C[0] + 0x1972AE)) {
            case 0:
                lbl_2_bss_1A8234[0][0x160000 + 0x2654] = 1;
                break;
            case 1:
                lbl_2_bss_1A8234[0][0x160000 + 0x2655] = 1;
                break;
            case 2:
            case 3:
                lbl_2_bss_1A8234[0][0x160000 + 0x2656] = 1;
                break;
            }
        }
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

// fn_2_382A0, size:0x298
void fn_2_382A0(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    s16 m;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        *(s16*)(p + 0x14) = 5;
        m = *(s16*)(p + 0x16);
        if ((m == 0 || m == 2) && *(s16*)(lbl_2_bss_1A824C[0] + 0x1972A4) != 0) {
            switch (*(s16*)(lbl_2_bss_1A824C[0] + 0x1972AC)) {
            case 0:
                lbl_2_bss_1A8234[0][0x160000 + 0x2839] = 1;
                break;
            case 1:
                lbl_2_bss_1A8234[0][0x160000 + 0x283A] = 1;
                break;
            case 2:
            case 3:
                lbl_2_bss_1A8234[0][0x160000 + 0x283B] = 1;
                break;
            }
        }
        m = *(s16*)(p + 0x16);
        if ((m == 1 || m == 2) && *(s16*)(lbl_2_bss_1A824C[0] + 0x1972A6) != 0) {
            switch (*(s16*)(lbl_2_bss_1A824C[0] + 0x1972AE)) {
            case 0:
                lbl_2_bss_1A8234[0][0x160000 + 0x283E] = 1;
                break;
            case 1:
                lbl_2_bss_1A8234[0][0x160000 + 0x283F] = 1;
                break;
            case 2:
            case 3:
                lbl_2_bss_1A8234[0][0x160000 + 0x2840] = 1;
                break;
            }
        }
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
        m = *(s16*)(p + 0x16);
        if (m == 0 || m == 2) {
            *(s16*)(lbl_2_bss_1A824C[0] + 0x1972A4) = 0;
        }
        m = *(s16*)(p + 0x16);
        if (m == 1 || m == 2) {
            *(s16*)(lbl_2_bss_1A824C[0] + 0x1972A6) = 0;
        }
        q = *(u8**)(lbl_803CC1B8 + 0xC);
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

// fn_2_38538, size:0x2EC
void fn_2_38538(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        *(s16*)(p + 0x14) = 0x1E;
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x19729C) != 0) {
            lbl_2_bss_1A8234[0][0x160000 + 0x2836] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2837] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2838] = 1;
        }
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1972A4) != 0) {
            switch (*(s16*)(lbl_2_bss_1A824C[0] + 0x1972AC)) {
            case 0:
                lbl_2_bss_1A8234[0][0x160000 + 0x2839] = 1;
                break;
            case 1:
                lbl_2_bss_1A8234[0][0x160000 + 0x283A] = 1;
                break;
            case 2:
            case 3:
                lbl_2_bss_1A8234[0][0x160000 + 0x283B] = 1;
                break;
            }
        }
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x19729E) != 0) {
            lbl_2_bss_1A8234[0][0x160000 + 0x283C] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x283D] = 1;
        }
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1972A6) != 0) {
            switch (*(s16*)(lbl_2_bss_1A824C[0] + 0x1972AE)) {
            case 0:
                lbl_2_bss_1A8234[0][0x160000 + 0x283E] = 1;
                break;
            case 1:
                lbl_2_bss_1A8234[0][0x160000 + 0x283F] = 1;
                break;
            case 2:
            case 3:
                lbl_2_bss_1A8234[0][0x160000 + 0x2840] = 1;
                break;
            }
        }
        *(u32*)(lbl_2_bss_1A824C[0] + 0x1976A8) = fn_80062890(0x11);
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
        lbl_2_bss_1A8248[0][0x44F2] = 0;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x1972A6) = 0;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x1972A4) = 0;
        q = *(u8**)(lbl_803CC1B8 + 0xC);
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
