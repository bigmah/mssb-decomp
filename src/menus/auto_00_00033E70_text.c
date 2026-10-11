#include "menus/auto_00_00033E70_text.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"
#include "menus/auto_00_0003C03C_text.h"
#include "menus/auto_00_0004B1AC_text.h"
#include "menus/rep_0788.h"
extern s32 fn_8000FF04(s32 table, s32 msg, s16 x, s16 y, u8 layer, u32 color, u8 fontSize);

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
    u8 skipped;
    u8 pad1[3];
    s32 size;
    void* alt;
    void* buf;
    void* heap;
} Fn37460Data;

extern Fn37460Data lbl_2_bss_15A0;
extern u8 lbl_2_data_12180[];
extern u8 lbl_2_data_12170[];
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

#define FN353FC_ENT(a, b) lbl_80371C30[(*(u16*)((a) + 0x14) + *(s16*)((b) + 0xE)) * 2]

// fn_2_353FC, size:0x358
void fn_2_353FC(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = FN353FC_ENT(a, b);
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2:
        *(u32*)(FN353FC_ENT(a, b) + 0x54) |= 2;
        *(u32*)(FN353FC_ENT(a, b) + 0x5C) = 0;
        FN353FC_ENT(a, b)[0x68] = 1;
        *(s16*)(b + 4) = 3;
        break;
    case 3:
        if ((*(u32*)(FN353FC_ENT(a, b) + 0x5C) >> 16) >= 5) {
            *(s16*)(b + 4) = 0x25;
        }
        break;
    case 0x25:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976DA) == 0) {
            u8* p = FN353FC_ENT(a, b);
            if ((*(u32*)(p + 0x5C) >> 16) <= 5) {
                *(u32*)(p + 0x5C) = 0x50000;
                FN353FC_ENT(a, b)[0x68] = 0;
            } else {
                p[0x68] = 4;
            }
        } else {
            u8* p = FN353FC_ENT(a, b);
            if ((*(u32*)(p + 0x5C) >> 16) >= 0xA) {
                *(u32*)(p + 0x5C) = 0xA0000;
                FN353FC_ENT(a, b)[0x68] = 0;
            } else {
                p[0x68] = 1;
            }
        }
        break;
    case 5:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976DA) == 0) {
            FN353FC_ENT(a, b)[0x68] = 4;
        } else {
            FN353FC_ENT(a, b)[0x68] = 1;
        }
        *(s16*)(b + 4) = 6;
        break;
    case 6:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976DA) == 0) {
            u8* p = FN353FC_ENT(a, b);
            if ((*(u32*)(p + 0x5C) >> 16) == 0) {
                p[0x68] = 0;
                *(s16*)(b + 4) = 7;
            }
        } else {
            u8* p = FN353FC_ENT(a, b);
            if ((*(u32*)(p + 0x5C) >> 16) >= 0xF) {
                p[0x68] = 0;
                *(s16*)(b + 4) = 7;
            }
        }
        break;
    case 7:
        *(u32*)(FN353FC_ENT(a, b) + 0x54) &= ~2;
        break;
    }
}

// fn_2_35A14, size:0x3A0
void fn_2_35A14(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* p = FN353FC_ENT(a, b);
        *(u32*)(p + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2:
        fn_800363D8(a, *(s16*)(b + 0xE), 1, 0xCF, *(s16*)(b + 0x10));
        *(u32*)(FN353FC_ENT(a, b) + 0x54) |= 2;
        *(u32*)(FN353FC_ENT(a, b) + 0x5C) = 0;
        FN353FC_ENT(a, b)[0x68] = 1;
        *(s16*)(b + 4) = 3;
        break;
    case 3: {
        u8* p = FN353FC_ENT(a, b);
        if ((*(u32*)(p + 0x5C) >> 16) >= 3) {
            *(u32*)(p + 0x5C) = 0x30000;
            FN353FC_ENT(a, b)[0x68] = 0;
            *(s16*)(b + 4) = 0x25;
        }
        break;
    }
    case 0x25:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976D8) == *(s16*)(b + 0xA)) {
            u8* p = FN353FC_ENT(a, b);
            if ((*(u32*)(p + 0x5C) >> 16) >= 8) {
                *(u32*)(p + 0x5C) = 0x80000;
                FN353FC_ENT(a, b)[0x68] = 0;
            } else {
                p[0x68] = 1;
            }
        } else {
            u8* p = FN353FC_ENT(a, b);
            if ((*(u32*)(p + 0x5C) >> 16) <= 3) {
                *(u32*)(p + 0x5C) = 0x30000;
                FN353FC_ENT(a, b)[0x68] = 0;
            } else {
                p[0x68] = 4;
            }
        }
        break;
    case 5:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976D8) == *(s16*)(b + 0xA)) {
            FN353FC_ENT(a, b)[0x68] = 1;
        } else {
            FN353FC_ENT(a, b)[0x68] = 4;
        }
        *(s16*)(b + 4) = 6;
        break;
    case 6:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976D8) == *(s16*)(b + 0xA)) {
            u8* p = FN353FC_ENT(a, b);
            if ((*(u32*)(p + 0x5C) >> 16) >= 0xB) {
                p[0x68] = 0;
                *(s16*)(b + 4) = 7;
            }
        } else {
            u8* p = FN353FC_ENT(a, b);
            if ((*(u32*)(p + 0x5C) >> 16) == 0) {
                p[0x68] = 0;
                *(s16*)(b + 4) = 7;
            }
        }
        break;
    case 7:
        *(u32*)(FN353FC_ENT(a, b) + 0x54) &= ~2;
        break;
    }
}

// fn_2_38F48, size:0x26C
void fn_2_38F48(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    u8* e;
    s32 last;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        last = 0;
        if (lbl_2_bss_1A8244[0][0xE4 + lbl_2_bss_1A8248[0][0x4415]] == 0 && lbl_2_bss_1A8248[0][0x4415] < 3) {
            last = 1;
        }
        fn_2_38EA8();
        if (last) {
            *(s16*)(p + 0x14) = 0x12;
            lbl_2_bss_1A8234[0][0x160000 + 0x264F] = 1;
            fn_80062890(0x38);
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
        e = (u8*)&lbl_803C77B8;
        e += *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20;
        if (*(u16*)(e + 2) & 0x100) {
            *(s16*)(p + 0x14) = 0x12;
            lbl_2_bss_1A8234[0][0x160000 + 0x2839] = 1;
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

// fn_2_391B4, size:0x254
void fn_2_391B4(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    u16 btn;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        *(s16*)(p + 0x14) = 0x1E;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x1976E0) = 0;
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
        btn = ((u16*)((u8*)&lbl_803C77B8 + 4))[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x10];
        if ((btn & 1) && *(s16*)(lbl_2_bss_1A824C[0] + 0x1976E0) == 1) {
            *(s16*)(lbl_2_bss_1A824C[0] + 0x1976E0) = 0;
        } else if ((btn & 2) && *(s16*)(lbl_2_bss_1A824C[0] + 0x1976E0) == 0) {
            *(s16*)(lbl_2_bss_1A824C[0] + 0x1976E0) = 1;
        }
        btn = ((u16*)((u8*)&lbl_803C77B8 + 2))[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x10];
        if (btn & 0x100) {
            p[0x28] = 3;
        } else if (btn & 0x200) {
            if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976E0) == 0) {
                *(s16*)(lbl_2_bss_1A824C[0] + 0x1976E0) = 1;
            } else {
                p[0x28] = 3;
            }
        }
        if (*(s16*)(p + 0x16) == 0) {
            fn_8000FF04(4, 0x2E0, 0x64, 0xC8, 9, -1, 0);
        } else {
            fn_8000FF04(4, lbl_2_bss_1A8248[0][0x4420] + 0x2ED, 0x64, 0xC8, 9, -1, 0);
        }
        break;
    case 3:
        *(s16*)(p + 0x14) = 0x10;
        p[0x28] = 4;
        break;
    case 4: {
        if ((*(s16*)(p + 0x14))-- == 0) {
            if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976E0) == 0) {
                q = *(u8**)(lbl_803CC1B8 + 0xC);
                *(s16*)(q + 0x10) = 1;
            } else {
                q = *(u8**)(lbl_803CC1B8 + 0xC);
                *(s16*)(q + 0x10) = 2;
            }
            fn_800B0A14_removeQueue(q);
            p[0x28] = 0;
        }
        break;
    }
    }
}

// fn_2_397AC, size:0x214
void fn_2_397AC(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    u16 btn;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        *(s16*)(p + 0x14) = 0x1E;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x1976DC) = 0;
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
        btn = ((u16*)((u8*)&lbl_803C77B8 + 4))[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x10];
        if ((btn & 1) && *(s16*)(lbl_2_bss_1A824C[0] + 0x1976DC) == 1) {
            *(s16*)(lbl_2_bss_1A824C[0] + 0x1976DC) = 0;
        } else if ((btn & 2) && *(s16*)(lbl_2_bss_1A824C[0] + 0x1976DC) == 0) {
            *(s16*)(lbl_2_bss_1A824C[0] + 0x1976DC) = 1;
        }
        btn = ((u16*)((u8*)&lbl_803C77B8 + 2))[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x10];
        if (btn & 0x100) {
            p[0x28] = 3;
        } else if (btn & 0x200) {
            if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976DC) == 0) {
                *(s16*)(lbl_2_bss_1A824C[0] + 0x1976DC) = 1;
            } else {
                p[0x28] = 3;
            }
        }
        fn_8000FF04(4, 0x2DF, 0x64, 0xC8, 9, -1, 0);
        break;
    case 3:
        *(s16*)(p + 0x14) = 0x10;
        p[0x28] = 4;
        break;
    case 4: {
        if ((*(s16*)(p + 0x14))-- == 0) {
            if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976DC) == 0) {
                q = *(u8**)(lbl_803CC1B8 + 0xC);
                *(s16*)(q + 0x10) = 1;
            } else {
                q = *(u8**)(lbl_803CC1B8 + 0xC);
                *(s16*)(q + 0x10) = 2;
            }
            fn_800B0A14_removeQueue(q);
            p[0x28] = 0;
        }
        break;
    }
    }
}

// Subtitle cue: shown from frame `start` until frame `end`.
typedef struct MovieCue {
    s32 start;
    s32 end;
    s32 text;
} MovieCue;

extern MovieCue lbl_2_data_34E0[2][8];
extern void fn_800AD830(void*);
extern s32 fn_800AED24(void);

#define MOVIE_FRAME (*(s32*)(lbl_2_bss_1A824C[0] + 0x1976B0))
#define MOVIE_TICK (*(s32*)(lbl_2_bss_1A824C[0] + 0x1976B4))
#define MOVIE_CUE (*(s32*)(lbl_2_bss_1A824C[0] + 0x1976B8))
#define MOVIE_CUE_ON (*(s32*)(lbl_2_bss_1A824C[0] + 0x1976BC))

// fn_2_37630, size:0x3A0
void fn_2_37630(void) {
    Fn37460Data* d = &lbl_2_bss_15A0;
    u8* o = lbl_803CC1B8;
    void* p;
    s32 sz;
    switch ((s8)o[0x28]) {
    case 0:
        MOVIE_FRAME = 0;
        MOVIE_TICK = 0;
        MOVIE_CUE = 0;
        MOVIE_CUE_ON = 0;
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
        if (fn_800ADB04(lbl_2_data_12170, d->heap, 1, 0) != 0) {
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
    case 3: {
        u8* e = (u8*)&lbl_803C77B8;
        e += *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20;
        if (*(u16*)(e + 2) & 0x1000) {
            d->skipped = 1;
            fn_800AD830(d->heap);
            o[0x28]++;
            return;
        }
        MOVIE_TICK++;
        fn_800AD070();
        if (fn_800AED24() == 1) {
            s32 sel;
            MOVIE_FRAME++;
            sel = lbl_2_bss_1A8248[0][0x441C] == 5;
            if (MOVIE_FRAME == lbl_2_data_34E0[sel][MOVIE_CUE].start && MOVIE_CUE_ON == 0 &&
                lbl_2_data_34E0[sel][MOVIE_CUE].start != -1) {
                *(s16*)(lbl_2_bss_1A824C[0] + 0x19774C) = lbl_2_data_34E0[sel][MOVIE_CUE].text;
                MOVIE_CUE_ON = 1;
                lbl_2_bss_1A8234[0][0x160000 + 0x264E] = 1;
            } else if (MOVIE_FRAME == lbl_2_data_34E0[sel][MOVIE_CUE].end && MOVIE_CUE_ON == 1 &&
                       lbl_2_data_34E0[sel][MOVIE_CUE].start != -1) {
                lbl_2_bss_1A8234[0][0x160000 + 0x2838] = 1;
                MOVIE_CUE++;
                MOVIE_CUE_ON = 0;
            }
        }
        if (fn_800AD780(d->heap) != 0) {
            o[0x28]++;
            return;
        }
        break;
    }
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

extern u8* lbl_2_bss_1A8230[];
extern GXColor lbl_2_data_12270;
extern void fn_2_54474(void);
extern BOOL fn_80068514(u32 frames, u8 target);
extern void fn_8006877C(u8 track);
extern void fn_800A86B4(s32 cmd);

// fn_2_379D0, size:0x3A0
void fn_2_379D0(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        if (fn_2_4EABC() == 1) {
            o[0x28] = 1;
        }
        break;
    case 1: {
        GXColor clear = lbl_2_data_12270;
        GXSetCopyClear(clear, 0xFFFFFF);
        changeScene(1, 6);
        fn_2_515DC(4);
        lbl_2_bss_1A8234[0][0x160000 + 0x2992] = 0;
        lbl_2_bss_1A8230[0][0x32A86] = 0;
        fn_2_54474();
        fn_2_245C8();
        *(s16*)(lbl_2_bss_1A824C[0] + 0x1976E4) = 0x168;
        lbl_2_bss_15A0.skipped = 0;
        o[0x28] = 2;
        break;
    }
    case 2:
        o[0x28] = 3;
        break;
    case 3:
        if (lbl_8037169C[0x12] != 0) {
            q = fn_800B0A5C_insertQueue(fn_2_37630, 2);
            q[0x28] = 0;
            *(s16*)(o + 0x10) = 0;
            o[0x28] = 4;
        }
        break;
    case 4:
        if (*(s16*)(o + 0x10) != 0) {
            if (lbl_2_bss_15A0.skipped) {
                changeScene(3, 6);
                lbl_2_bss_1A8234[0][0x160000 + 0x2838] = 1;
                lbl_2_bss_1A8234[0][0x160000 + 0x2839] = 1;
                lbl_2_bss_1A8234[0][0x160000 + 0x2835] = 1;
                lbl_2_bss_1A8234[0][0x160000 + 0x2837] = 1;
                o[0x28] = 7;
            } else {
                fn_8006877C(0xB);
                if (lbl_2_bss_1A8248[0][0x441C] == 5) {
                    fn_2_422FC(1);
                } else {
                    fn_2_422FC(0);
                }
                q = fn_800B0A5C_insertQueue(fn_2_42388, 2);
                q[0x28] = 0;
                *(s16*)(o + 0x10) = 0;
                o[0x28] = 5;
            }
        }
        break;
    case 5: {
        BOOL fading = fn_80068514(0x78, 0x7F);
        if (*(s16*)(o + 0x10) == 1) {
            lbl_2_bss_1A824C[0][0x19783F] = 0;
            changeScene(3, 6);
            lbl_2_bss_1A8234[0][0x160000 + 0x2838] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2839] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2835] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2837] = 1;
            o[0x28] = 6;
        }
        if ((((u16*)((u8*)&lbl_803C77B8 + 2))[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x10] & 0x1000) && (u8)fading == 0) {
            lbl_2_bss_1A824C[0][0x19783F] = 1;
        }
        break;
    }
    case 6:
        if (fn_8006862C(0x78, 0) == 0) {
            o[0x28] = 7;
        }
        break;
    case 7:
        if (lbl_8037169C[0x13] != 0) {
            GXColor clear;
            fn_800A86B4(3);
            clear = lbl_2_data_12270;
            GXSetCopyClear(clear, 0xFFFFFF);
            lbl_2_bss_1A8234[0][0x160000 + 0x2992] = 1;
            lbl_2_bss_1A8230[0][0x32A86] = 1;
            o[0x28] = 8;
        }
        break;
    case 8:
        fn_2_4E8E0();
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
}

extern u8 lbl_800EFBA4[];
extern int sndFXStartEx(int, int, int, int);

// fn_2_39408, size:0x3A4
void fn_2_39408(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    u16 btn;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        switch (lbl_2_bss_1A824C[0][0x1972B6]) {
        case 0:
            lbl_2_bss_1A8234[0][0x160000 + 0x266E] = 1;
            break;
        case 1:
            lbl_2_bss_1A8234[0][0x160000 + 0x266F] = 1;
            break;
        case 2:
            lbl_2_bss_1A8234[0][0x160000 + 0x2670] = 1;
            break;
        }
        *(s16*)(p + 0x14) = 0xA;
        *(s16*)(p + 0x16) = 0;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x1976DE) = lbl_2_bss_1A824C[0][0x1972B7];
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
        btn = ((u16*)((u8*)&lbl_803C77B8 + 4))[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x10];
        if ((btn & 1) && *(s16*)(lbl_2_bss_1A824C[0] + 0x1976DE) == 1) {
            *(s16*)(lbl_2_bss_1A824C[0] + 0x1976DE) = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if ((btn & 2) && *(s16*)(lbl_2_bss_1A824C[0] + 0x1976DE) == 0) {
            *(s16*)(lbl_2_bss_1A824C[0] + 0x1976DE) = 1;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        btn = ((u16*)((u8*)&lbl_803C77B8 + 2))[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x10];
        if (btn & 0x100) {
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            p[0x28] = 3;
        } else if (btn & 0x200) {
            if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976DE) == 0) {
                *(s16*)(lbl_2_bss_1A824C[0] + 0x1976DE) = 1;
            } else {
                *(s16*)(p + 0x16) = 1;
                p[0x28] = 3;
            }
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    case 3:
        switch (lbl_2_bss_1A824C[0][0x1972B6]) {
        case 0:
            lbl_2_bss_1A8234[0][0x160000 + 0x2858] = 1;
            break;
        case 1:
            lbl_2_bss_1A8234[0][0x160000 + 0x2859] = 1;
            break;
        case 2:
            lbl_2_bss_1A8234[0][0x160000 + 0x285A] = 1;
            break;
        }
        *(s16*)(p + 0x14) = 0xA;
        p[0x28] = 4;
        break;
    case 4:
        if ((*(s16*)(p + 0x14))-- == 0) {
            if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976DE) == 0) {
                q = *(u8**)(lbl_803CC1B8 + 0xC);
                *(s16*)(q + 0x10) = 1;
            } else if (*(s16*)(p + 0x16) == 0) {
                q = *(u8**)(lbl_803CC1B8 + 0xC);
                *(s16*)(q + 0x10) = 2;
            } else {
                q = *(u8**)(lbl_803CC1B8 + 0xC);
                *(s16*)(q + 0x10) = 3;
            }
            fn_800B0A14_removeQueue(q);
            p[0x28] = 0;
        }
        break;
    }
}

// Grid layouts for the selection cursor: highest column and row index.
typedef struct GridSize {
    s16 maxCol;
    s16 maxRow;
} GridSize;

extern GridSize lbl_2_data_122A8[4];

#define GRID_COL (*(s16*)(lbl_2_bss_1A824C[0] + 0x19770C))
#define GRID_ROW (*(s16*)(lbl_2_bss_1A824C[0] + 0x19770E))
#define GRID_SEL (*(s16*)(lbl_2_bss_1A824C[0] + 0x197710))
#define GRID_PREV (*(s16*)(lbl_2_bss_1A824C[0] + 0x197712))
#define GRID_LAYOUT (*(s16*)(lbl_2_bss_1A824C[0] + 0x197714))

// fn_2_3A8FC, size:0x60C
// NONMATCHING 99.7%: r30/r31 swapped between the task pointer and the pad pointer (see docs/patterns/regalloc.md)
#if NONMATCHING
void fn_2_3A8FC(void) {
    u8* repeat;
    u8* p = lbl_803CC1B8;
    u8* q;
    u16 btn;
    s32 pad;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        if (*(s8*)(lbl_2_bss_1A8248[0] + 0x44F4) == 0) {
            lbl_2_bss_1A8234[0][0x160000 + 0x267F] = 1;
        } else {
            lbl_2_bss_1A8234[0][0x160000 + 0x2651] = 1;
        }
        *(s16*)(p + 0x14) = 0xC;
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
        repeat = (u8*)&lbl_803C77B8 + 4;
        btn = *(u16*)(repeat + *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20);
        if (btn & 1) {
            GRID_PREV = GRID_SEL;
            GRID_COL--;
            if (GRID_COL < 0) {
                GRID_COL = lbl_2_data_122A8[GRID_LAYOUT].maxCol;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (btn & 2) {
            GRID_PREV = GRID_SEL;
            GRID_COL++;
            if (GRID_COL > lbl_2_data_122A8[GRID_LAYOUT].maxCol) {
                GRID_COL = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        btn = *(u16*)(repeat + *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20);
        if (btn & 8) {
            if (lbl_2_data_122A8[GRID_LAYOUT].maxRow != 0) {
                GRID_PREV = GRID_SEL;
                GRID_ROW--;
                if (GRID_ROW < 0) {
                    GRID_ROW = lbl_2_data_122A8[GRID_LAYOUT].maxRow;
                }
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (btn & 4) {
            if (lbl_2_data_122A8[GRID_LAYOUT].maxRow != 0) {
                GRID_PREV = GRID_SEL;
                GRID_ROW++;
                if (GRID_ROW > lbl_2_data_122A8[GRID_LAYOUT].maxRow) {
                    GRID_ROW = 0;
                }
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
        GRID_SEL = GRID_COL + GRID_ROW * (lbl_2_data_122A8[GRID_LAYOUT].maxCol + 1);
        pad = *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20;
        btn = *(u16*)(repeat + pad);
        if ((btn & 8) || (btn & 4)) {
            if (lbl_2_data_122A8[GRID_LAYOUT].maxRow == 0) {
                goto check_confirm;
            }
            if (*(s8*)(lbl_2_bss_1A8248[0] + 0x44F4) == 0) {
                lbl_2_bss_1A8234[0][0x160000 + 0x270B] = 1;
            } else {
                lbl_2_bss_1A8234[0][0x160000 + 0x26DD] = 1;
            }
            p[0x28] = 3;
        } else if ((btn & 1) || (btn & 2)) {
            if (*(s8*)(lbl_2_bss_1A8248[0] + 0x44F4) == 0) {
                lbl_2_bss_1A8234[0][0x160000 + 0x270B] = 1;
            } else {
                lbl_2_bss_1A8234[0][0x160000 + 0x26DD] = 1;
            }
            p[0x28] = 3;
        } else {
        check_confirm:
            btn = *(u16*)((u8*)&lbl_803C77B8 + pad + 2);
            if (btn & 0x100) {
                if (*(s8*)(lbl_2_bss_1A8248[0] + 0x44F4) == 0) {
                    lbl_2_bss_1A8234[0][0x160000 + 0x2869] = 1;
                } else {
                    lbl_2_bss_1A8234[0][0x160000 + 0x283B] = 1;
                }
                *(s16*)(p + 0x14) = 0xC;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                p[0x28] = 4;
            } else if (btn & 0x200) {
                if (*(s8*)(lbl_2_bss_1A8248[0] + 0x44F4) == 0) {
                    lbl_2_bss_1A8234[0][0x160000 + 0x2869] = 1;
                } else {
                    lbl_2_bss_1A8234[0][0x160000 + 0x283B] = 1;
                }
                *(s16*)(p + 0x14) = 0xC;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                p[0x28] = 4;
            }
        }
        break;
    case 3:
        p[0x28] = 2;
        break;
    case 4: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            p[0x28] = 5;
        }
        break;
    }
    case 5:
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
#endif

extern s16 lbl_2_data_373C[20];
extern s16 lbl_2_data_296B8[36];
extern u8 lbl_800E869C[];
typedef struct Unk8010B42C {
    u8 _00[0xC];
    s16 gridLayout[1]; // TODO type: indexed by fn_2_44F14
} Unk8010B42C;
extern Unk8010B42C lbl_8010B42C;
extern u8 lbl_8034E978[];
extern u8 lbl_800FEF70[];
extern void fn_80053FE8(void);
extern s32 fn_8006C79C(u8);

#define PICK_ID (*(s16*)(lbl_2_bss_1A824C[0] + 0x197706))
#define PICK_COL (*(s16*)(lbl_2_bss_1A824C[0] + 0x197708))
#define PICK_ROW (*(s16*)(lbl_2_bss_1A824C[0] + 0x19770A))

// fn_2_3AF08, size:0xB38
// NONMATCHING 98%: r30/r31 swapped (task vs pad pointer), dead `cmpwi 0x14` before the loop, lbl_8010B42C+0xC lhax folded
#if NONMATCHING
void fn_2_3AF08(void) {
    u8* repeat;
    u8* p = lbl_803CC1B8;
    u8* q;
    u16 btn;
    s32 i;
    s32 n;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        n = 0;
        for (i = 0; i < 20; i++) {
            if (*(s8*)(lbl_2_bss_1A8248[0] + 0x43C2 + i) == 1 && lbl_2_data_373C[i] == 0) {
                lbl_2_bss_1A824C[0][0x1978B3 + n++] = 1;
            }
        }
        changeScene(3, 6);
        p[0x28] = 1;
        break;
    case 1:
        if (lbl_8037169C[0x13] != 0) {
            p[0x28] = 2;
        }
        break;
    case 2:
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197730) = 6;
        lbl_2_bss_1A8248[0][0x44F2] = 2;
        PICK_ID = 0;
        PICK_COL = 1;
        PICK_ROW = 0;
        lbl_2_bss_1A8234[0][0x160000 + 0x267B] = 1;
        lbl_2_bss_1A8234[0][0x160000 + 0x267E] = 1;
        lbl_8034E978[3] = lbl_2_bss_1A8248[0][0x4415];
        fn_800B0A5C_insertQueue(fn_80053FE8, 0);
        lbl_8034E978[0] = 0xE;
        lbl_8034E978[0] = 0xE;
        lbl_8034E978[9] = lbl_8034E978[8];
        lbl_8034E978[8] = *(u16*)(lbl_800FEF70 + 0xE * 0x10 + 8);
        changeScene(1, 6);
        p[0x28] = 3;
        break;
    case 3:
        (*(s16*)(p + 0x14))--;
        if (lbl_8037169C[0x12] != 0) {
            p[0x28] = 4;
        }
        break;
    case 4:
        *(s16*)(p + 0x14) = 0x28;
        lbl_2_bss_1A8234[0][0x160000 + 0x267C] = 1;
        p[0x28] = 5;
        break;
    case 5: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t <= 0) {
            p[0x28] = 6;
        }
        break;
    }
    case 6:
        repeat = (u8*)&lbl_803C77B8 + 4;
        btn = *(u16*)(repeat + *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20);
        if (btn & 1) {
            PICK_COL--;
            if (PICK_COL == 0 && (PICK_ROW == 0 || PICK_ROW == 5)) {
                PICK_COL = 4;
            } else if (PICK_COL < 0) {
                PICK_COL = 5;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (btn & 2) {
            PICK_COL++;
            if (PICK_COL == 5 && (PICK_ROW == 0 || PICK_ROW == 5)) {
                PICK_COL = 1;
            } else if (PICK_COL > 5) {
                PICK_COL = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        btn = *(u16*)(repeat + *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20);
        if (btn & 8) {
            PICK_ROW--;
            if (PICK_ROW == 0 && (PICK_COL == 0 || PICK_COL == 5)) {
                PICK_ROW = 4;
            } else if (PICK_ROW < 0) {
                PICK_ROW = 5;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (btn & 4) {
            PICK_ROW++;
            if (PICK_ROW == 5 && (PICK_COL == 0 || PICK_COL == 5)) {
                PICK_ROW = 1;
            } else if (PICK_ROW > 5) {
                PICK_ROW = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        PICK_ID = lbl_2_data_296B8[PICK_COL + PICK_ROW * 6];
        btn = ((u16*)((u8*)&lbl_803C77B8 + 2))[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x10];
        if (btn & 0x40) {
            *(s16*)(lbl_2_bss_1A824C[0] + 0x197730) = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x293A] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2866] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            *(s16*)(p + 0x14) = 0x32;
            p[0x28] = 7;
        } else if (btn & 0x20) {
            *(s16*)(lbl_2_bss_1A824C[0] + 0x197730) = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2980] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2866] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            *(s16*)(p + 0x14) = 0x32;
            p[0x28] = 7;
        } else if (btn & 0x100) {
            if (fn_8006C79C(lbl_800E869C[PICK_ID]) == 1) {
                GRID_PREV = 0;
                GRID_SEL = 0;
                GRID_COL = 0;
                GRID_ROW = 0;
                GRID_LAYOUT = lbl_8010B42C.gridLayout[fn_2_44F14(lbl_800E869C[PICK_ID])];
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                p[0x28] = 8;
            } else {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            }
        } else if (btn & 0x200) {
            lbl_2_bss_1A8234[0][0x160000 + 0x2866] = 1;
            *(s16*)(p + 0x14) = 0x28;
            p[0x28] = 0xE;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    case 7: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            p[0x28] = 0xA;
        }
        break;
    }
    case 8:
        q = fn_800B0A5C_insertQueue(fn_2_3A8FC, 2);
        q[0x28] = 0;
        *(s16*)(p + 0x10) = 0;
        p[0x28] = 9;
        break;
    case 9:
        if (*(s16*)(p + 0x10) == 1) {
            p[0x28] = 6;
        }
        break;
    case 10:
        *(s16*)(p + 0x14) = 0x1E;
        lbl_8034E978[0] = 0xF;
        lbl_8034E978[9] = lbl_8034E978[8];
        lbl_8034E978[8] = *(u16*)(lbl_800FEF70 + 0xF * 0x10 + 8);
        lbl_2_bss_1A8234[0][0x160000 + 0x267D] = 1;
        p[0x28] = 0xB;
        break;
    case 11: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t <= 0) {
            p[0x28] = 0xC;
        }
        break;
    }
    case 12:
        btn = ((u16*)((u8*)&lbl_803C77B8 + 2))[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x10];
        if (btn & 0x40) {
            *(s16*)(lbl_2_bss_1A824C[0] + 0x197730) = 6;
            lbl_2_bss_1A8234[0][0x160000 + 0x293A] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2867] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            *(s16*)(p + 0x14) = 0x1E;
            lbl_8034E978[0] = 0xE;
            lbl_8034E978[9] = lbl_8034E978[8];
            lbl_8034E978[8] = *(u16*)(lbl_800FEF70 + 0xE * 0x10 + 8);
            p[0x28] = 0xD;
        } else if (btn & 0x20) {
            *(s16*)(lbl_2_bss_1A824C[0] + 0x197730) = 6;
            lbl_2_bss_1A8234[0][0x160000 + 0x2980] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2867] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            *(s16*)(p + 0x14) = 0x1E;
            lbl_8034E978[0] = 0xE;
            lbl_8034E978[9] = lbl_8034E978[8];
            lbl_8034E978[8] = *(u16*)(lbl_800FEF70 + 0xE * 0x10 + 8);
            p[0x28] = 0xD;
        } else if (btn & 0x200) {
            lbl_2_bss_1A8234[0][0x160000 + 0x2867] = 1;
            *(s16*)(p + 0x14) = 0x1E;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            p[0x28] = 0xE;
        }
        break;
    case 13: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            p[0x28] = 4;
        }
        break;
    }
    case 14: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            changeScene(3, 6);
            p[0x28] = 0xF;
        }
        break;
    }
    case 15:
        if (lbl_8037169C[0x13] != 0) {
            p[0x28] = 0x10;
        }
        break;
    case 16:
        lbl_2_bss_1A8248[0][0x44F2] = 0;
        lbl_8034E978[0x26] = 1;
        lbl_2_bss_1A8234[0][0x160000 + 0x2865] = 1;
        lbl_2_bss_1A8234[0][0x160000 + 0x2868] = 1;
        *(s16*)(p + 0x14) = 0x32;
        changeScene(1, 6);
        p[0x28] = 0x11;
        break;
    case 17:
        (*(s16*)(p + 0x14))--;
        if (lbl_8037169C[0x12] != 0) {
            p[0x28] = 0x12;
        }
        break;
    case 18:
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
#endif

extern s16 lbl_2_data_29700[36];
extern void fn_2_72054(s32 index, s8 value);

// Switch the menu screen: remember the current track and take the new menu's track.
#define SET_MENU_SCREEN(m)                                         \
    do {                                                           \
        lbl_8034E978[0] = (m);                                     \
        lbl_8034E978[9] = lbl_8034E978[8];                         \
        lbl_8034E978[8] = *(u16*)(lbl_800FEF70 + (m) * 0x10 + 8); \
    } while (0)

// fn_2_399C0, size:0xF3C
// NONMATCHING 98%: r30/r31 swapped, &g_d_GameSettings hoisted to r31 in the original, lbl_8010B42C+0xC lhax folded
#if NONMATCHING
void fn_2_399C0(void) {
    u8* repeat;
    u8* p = lbl_803CC1B8;
    u8* q;
    u16 btn;
    s32 pad;
    s32 i;
    switch (*(s8*)(p + 0x28)) {
    case 0:
        fn_2_45204();
        fn_2_45A84();
        for (i = 0; i < 54; i++) {
            if (*(s8*)(lbl_2_bss_1A8248[0] + 0x444D + i) == 1) {
                lbl_2_bss_1A824C[0][0x1978F8] = 1;
            }
            if (*(s8*)(lbl_2_bss_1A8248[0] + 0x44B9 + i) == 1) {
                lbl_2_bss_1A824C[0][0x1978F9] = 1;
            }
        }
        if (lbl_2_bss_1A824C[0][0x1978F7] == 2) {
            p[0x28] = 0x11;
        } else {
            changeScene(3, 6);
            p[0x28] = 1;
        }
        break;
    case 1:
        if (lbl_8037169C[0x13] != 0) {
            p[0x28] = 2;
        }
        break;
    case 2:
        lbl_2_bss_1A8248[0][0x44F2] = 2;
        lbl_2_bss_1A824C[0][0x1978F6] = 0;
        PICK_ID = 0;
        PICK_COL = 1;
        PICK_ROW = 0;
        if (*(s8*)(lbl_2_bss_1A8248[0] + 0x44F4) == 0) {
            lbl_2_bss_1A8234[0][0x160000 + 0x2681] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2682] = 1;
        } else {
            lbl_2_bss_1A8234[0][0x160000 + 0x2652] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x2653] = 1;
        }
        if (lbl_2_bss_1A824C[0][0x1978F7] == 0) {
            lbl_2_bss_1A824C[0][0x1978F6] = 0;
        } else {
            lbl_2_bss_1A824C[0][0x1978F6] = 1;
        }
        changeScene(1, 6);
        p[0x28] = 3;
        break;
    case 3:
        (*(s16*)(p + 0x14))--;
        if (lbl_8037169C[0x12] != 0) {
            p[0x28] = 4;
        }
        break;
    case 4:
        *(s16*)(p + 0x14) = 0x28;
        if (lbl_2_bss_1A824C[0][0x1978F7] == 0) {
            lbl_8034E978[3] = lbl_2_bss_1A8248[0][0x4415];
            fn_800B0A5C_insertQueue(fn_80053FE8, 0);
            if (lbl_2_bss_1A824C[0][0x1978F8] == 1) {
                if (*(s8*)(lbl_2_bss_1A824C[0] + 0x197843) == 0) {
                    if (g_d_GameSettings.someChallengeModeFlag == 1) {
                        SET_MENU_SCREEN(0x28);
                    } else {
                        SET_MENU_SCREEN(0x27);
                    }
                }
                fn_80062890(0x39);
            } else if (*(s8*)(lbl_2_bss_1A824C[0] + 0x197843) == 0) {
                SET_MENU_SCREEN(0x29);
            } else if (*(s8*)(lbl_2_bss_1A824C[0] + 0x197843) == 1) {
                SET_MENU_SCREEN(0x2A);
            } else {
                SET_MENU_SCREEN(0x2A);
            }
            lbl_2_bss_1A824C[0][0x1978F6] = 0;
        } else {
            lbl_8034E978[3] = lbl_2_bss_1A8248[0][0x4415];
            fn_800B0A5C_insertQueue(fn_80053FE8, 0);
            if (lbl_2_bss_1A824C[0][0x1978F9] == 1) {
                SET_MENU_SCREEN(0x2B);
                fn_80062890(0x3F);
            } else {
                SET_MENU_SCREEN(0x2C);
            }
            if (*(s8*)(lbl_2_bss_1A8248[0] + 0x44F4) == 0) {
                lbl_2_bss_1A8234[0][0x160000 + 0x2685] = 1;
                lbl_2_bss_1A8234[0][0x160000 + 0x270E] = 1;
            } else {
                lbl_2_bss_1A8234[0][0x160000 + 0x2656] = 1;
                lbl_2_bss_1A8234[0][0x160000 + 0x26DF] = 1;
            }
            lbl_2_bss_1A824C[0][0x1978F6] = 1;
        }
        if (*(s8*)(lbl_2_bss_1A8248[0] + 0x44F4) == 0) {
            lbl_2_bss_1A8234[0][0x160000 + 0x2684] = 1;
        } else {
            lbl_2_bss_1A8234[0][0x160000 + 0x2655] = 1;
        }
        p[0x28] = 5;
        break;
    case 5: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t <= 0) {
            if (lbl_2_bss_1A824C[0][0x1978F7] == 0) {
                p[0x28] = 6;
            } else {
                p[0x28] = 8;
            }
        }
        break;
    }
    case 6:
        if (((u16*)((u8*)&lbl_803C77B8 + 2))[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x10] & 0x100) {
            *(s16*)(p + 0x14) = 0xA;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            p[0x28] = 7;
        }
        break;
    case 7: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            lbl_2_bss_1A824C[0][0x1978F6] = 1;
            if (lbl_2_bss_1A824C[0][0x1978F9] == 1) {
                SET_MENU_SCREEN(0x2B);
                fn_80062890(0x3F);
            } else {
                SET_MENU_SCREEN(0x2C);
            }
            if (*(s8*)(lbl_2_bss_1A8248[0] + 0x44F4) == 0) {
                lbl_2_bss_1A8234[0][0x160000 + 0x2685] = 1;
                lbl_2_bss_1A8234[0][0x160000 + 0x270E] = 1;
                lbl_2_bss_1A8234[0][0x160000 + 0x2710] = 1;
            } else {
                lbl_2_bss_1A8234[0][0x160000 + 0x2656] = 1;
                lbl_2_bss_1A8234[0][0x160000 + 0x26DF] = 1;
                lbl_2_bss_1A8234[0][0x160000 + 0x26E1] = 1;
            }
            p[0x28] = 8;
        }
        break;
    }
    case 8:
        repeat = (u8*)&lbl_803C77B8 + 4;
        btn = *(u16*)(repeat + *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20);
        if (btn & 1) {
            PICK_COL--;
            if (PICK_COL == 0 && PICK_ROW == 0) {
                PICK_COL = 5;
            } else if (PICK_COL == 0 && PICK_ROW == 5) {
                PICK_COL = 4;
            } else if (PICK_COL < 0) {
                PICK_COL = 5;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (btn & 2) {
            PICK_COL++;
            if (PICK_COL == 6 && PICK_ROW == 0) {
                PICK_COL = 1;
            } else if (PICK_COL == 5 && PICK_ROW == 5) {
                PICK_COL = 1;
            } else if (PICK_COL > 5) {
                PICK_COL = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        btn = *(u16*)(repeat + *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20);
        if (btn & 8) {
            PICK_ROW--;
            if (PICK_ROW == 0 && PICK_COL == 0) {
                PICK_ROW = 4;
            } else if (PICK_ROW < 0 && PICK_COL == 5) {
                PICK_ROW = 4;
            } else if (PICK_ROW < 0) {
                PICK_ROW = 5;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (btn & 4) {
            PICK_ROW++;
            if (PICK_ROW == 5 && PICK_COL == 0) {
                PICK_ROW = 1;
            } else if (PICK_ROW == 5 && PICK_COL == 5) {
                PICK_ROW = 0;
            } else if (PICK_ROW > 5) {
                PICK_ROW = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        PICK_ID = lbl_2_data_29700[PICK_COL + PICK_ROW * 6];
        pad = *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20;
        btn = *(u16*)(repeat + pad);
        if ((btn & 8) || (btn & 4) || (btn & 1) || (btn & 2)) {
            if (*(s8*)(lbl_2_bss_1A8248[0] + 0x44F4) == 0) {
                lbl_2_bss_1A8234[0][0x160000 + 0x27E3] = 1;
            } else {
                lbl_2_bss_1A8234[0][0x160000 + 0x27B4] = 1;
            }
            p[0x28] = 9;
        } else {
            btn = *(u16*)((u8*)&lbl_803C77B8 + pad + 2);
            if (btn & 0x100) {
                if (PICK_ROW == 0 && PICK_COL == 5) {
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                    p[0x28] = 0xC;
                } else if (fn_8006C79C(lbl_800E869C[PICK_ID]) == 1) {
                    GRID_PREV = 0;
                    GRID_SEL = 0;
                    GRID_COL = 0;
                    GRID_ROW = 0;
                    GRID_LAYOUT = lbl_8010B42C.gridLayout[fn_2_44F14(lbl_800E869C[PICK_ID])];
                    sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                    p[0x28] = 0xA;
                } else {
                    sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                }
            } else if ((btn & 0x200) && (PICK_ROW != 0 || PICK_COL != 5)) {
                PICK_ROW = 0;
                PICK_COL = 5;
                PICK_ID = lbl_2_data_29700[PICK_COL + PICK_ROW * 6];
                if (*(s8*)(lbl_2_bss_1A8248[0] + 0x44F4) == 0) {
                    lbl_2_bss_1A8234[0][0x160000 + 0x27E3] = 1;
                } else {
                    lbl_2_bss_1A8234[0][0x160000 + 0x27B4] = 1;
                }
                p[0x28] = 9;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            }
        }
        break;
    case 9:
        p[0x28] = 8;
        break;
    case 10:
        q = fn_800B0A5C_insertQueue(fn_2_3A8FC, 2);
        q[0x28] = 0;
        *(s16*)(p + 0x10) = 0;
        p[0x28] = 0xB;
        break;
    case 11:
        if (*(s16*)(p + 0x10) == 1) {
            p[0x28] = 8;
        }
        break;
    case 12:
        if (*(s8*)(lbl_2_bss_1A8248[0] + 0x44F4) == 0) {
            lbl_2_bss_1A8234[0][0x160000 + 0x286F] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x286E] = 1;
            *(s16*)(p + 0x14) = 0x28;
            p[0x28] = 0xD;
        } else {
            *(s16*)(p + 0x14) = 0xA;
            p[0x28] = 0x12;
        }
        break;
    case 13: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            changeScene(3, 6);
            p[0x28] = 0xE;
        }
        break;
    }
    case 14:
        if (lbl_8037169C[0x13] != 0) {
            p[0x28] = 0xF;
        }
        break;
    case 15:
        lbl_8034E978[0x26] = 1;
        lbl_2_bss_1A8248[0][0x44F2] = 0;
        if (*(s8*)(lbl_2_bss_1A8248[0] + 0x44F4) == 0) {
            lbl_2_bss_1A8234[0][0x160000 + 0x286B] = 1;
            lbl_2_bss_1A8234[0][0x160000 + 0x286C] = 1;
            *(s16*)(p + 0x14) = 0x32;
        } else {
            *(s16*)(p + 0x14) = 1;
        }
        changeScene(1, 6);
        fn_2_72054(0, 4);
        p[0x28] = 0x10;
        break;
    case 16:
        (*(s16*)(p + 0x14))--;
        if (lbl_8037169C[0x12] != 0) {
            p[0x28] = 0x11;
        }
        break;
    case 17:
        q = *(u8**)(p + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        p[0x28] = 0;
        break;
    case 18: {
        s16 t = *(s16*)(p + 0x14);
        *(s16*)(p + 0x14) = t - 1;
        if (t == 0) {
            p[0x28] = 0x11;
        }
        break;
    }
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        p[0x28] = 0;
    }
}
#endif
