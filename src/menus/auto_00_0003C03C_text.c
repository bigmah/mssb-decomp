#include "menus/auto_00_0003C03C_text.h"
#include "string.h"
#include "Dolphin/vec.h"
#include "static/UnknownHomes_Static.h"

extern u8* lbl_2_bss_1A8248[];
extern u8* lbl_2_bss_1A824C[];
extern u8 lbl_803CB8F0[];
extern u32 lbl_803CBD0C[];
extern u32* lbl_2_data_13374[];
extern void fn_80031CA4(Vec*, u32*);
extern u8 lbl_2_bss_15B8[];
extern void* lbl_2_data_12C0C[];
extern void* lbl_2_data_12CE8[];
extern u8* lbl_803CC1B8;
extern u8 lbl_80366B18[];
extern u8 lbl_803C6CF8[];
extern u8 lbl_2_data_12298[];
extern void fn_800111B4(s32);
extern void fn_2_94854(u8);
extern void fn_2_9461C(s16);
extern void fn_2_94604(u8);
extern void fn_2_94634(u8);
extern u8 lbl_8036E548[];
extern u8* lbl_2_bss_1A8234[];
extern u8* lbl_2_bss_1A8230[];
extern void fn_2_20218(void*);
extern void fn_2_1BF50(void);
extern s32 fn_8006CDC0(s32);
extern u8 lbl_800E8558[];
extern u8 lbl_80109AE8[];
extern u8 lbl_8010A768[];
extern s32 fn_2_40CB8(void);
extern void fn_2_90428(s32);
extern void fn_2_92654(s32, u8);
extern u8 lbl_2_data_3198[];
extern void fn_2_1BFD0(void);
extern u8 lbl_8034E978[];
extern void fn_2_72054(s32, s8);
extern s32 fn_2_8CC88(s32);

typedef struct {
    s32 k;
    s32 v;
} SortEnt;

// fn_2_42474, size:0x1C
void fn_2_42474(void) {
    u8* menu = lbl_2_bss_1A824C[0];
    *(s16*)(menu + 0x1976E4) = 0x78;
}

// fn_2_44F14, size:0x20
s32 fn_2_44F14(s32 index) {
    u8* menu = lbl_2_bss_1A8248[0];
    u8* entry = menu + index * 0x34;
    return *(s8*)(entry + 5);
}

// fn_2_44F34, size:0x30
s32 fn_2_44F34(s32 index) {
    return *(s8*)(lbl_2_bss_1A8248[0] + index * 0x34 + 5) <= 3;
}

// fn_2_4668C, size:0x20
void fn_2_4668C(s32 index) {
    u8* menu = lbl_2_bss_1A8248[0];
    u8* entry = menu + index * 0x34;
    entry[0x31] = 1;
}

// fn_2_45938, size:0x40
s32 fn_2_45938(s32 index) {
    u8* menu = lbl_2_bss_1A8248[0];
    return *(s8*)(menu + lbl_803CB8F0[menu[index * 10 + 0x40F3]] * 0x34 + 0x31) == 0;
}

// fn_2_460EC, size:0x4
void fn_2_460EC(void) {
    return;
}

// fn_2_460F0, size:0x4
void fn_2_460F0(void) {
    return;
}

// fn_2_460F4, size:0x4
void fn_2_460F4(void) {
    return;
}

// fn_2_46C24, size:0x8
s32 fn_2_46C24(void) {
    return 0;
}

// fn_2_46C2C, size:0x5C
void fn_2_46C2C(s32 unused, Vec* src) {
    Vec position;
    position.x = src->x;
    position.y = src->y;
    position.z = src->z;
    *lbl_2_data_13374[0] = lbl_803CBD0C[0];
    fn_80031CA4(&position, lbl_2_data_13374[0]);
}

// fn_2_422FC, size:0x8C
void fn_2_422FC(s32 index) {
    *(s32*)(lbl_2_bss_1A824C[0] + 0x197694) = 0;
    *(s32*)(lbl_2_bss_1A824C[0] + 0x19768C) = 0;
    *(s32*)(lbl_2_bss_1A824C[0] + 0x197690) = 0;
    memcpy(lbl_2_bss_15B8, lbl_2_data_12C0C[index], 0x4000);
    *(u8**)(lbl_2_bss_1A824C[0] + 0x197684) = lbl_2_bss_15B8;
}

// fn_2_42270, size:0x8C
void fn_2_42270(s32 index) {
    *(s32*)(lbl_2_bss_1A824C[0] + 0x197694) = 0;
    *(s32*)(lbl_2_bss_1A824C[0] + 0x19768C) = 0;
    *(s32*)(lbl_2_bss_1A824C[0] + 0x197690) = 0;
    memcpy(lbl_2_bss_15B8, lbl_2_data_12CE8[index], 0x4000);
    *(u8**)(lbl_2_bss_1A824C[0] + 0x197684) = lbl_2_bss_15B8;
}

// fn_2_44238, size:0xB0
s32 fn_2_44238(s32 value) {
    s32 count = 0;
    s32 i;
    u8* menu = lbl_2_bss_1A8248[0];
    for (i = 0; i < 9; i++) {
        if (*(s16*)(menu + 0x40B8 + i * 6) == value) count++;
    }
    return count != 0;
}

// fn_2_44184, size:0xB4
void fn_2_44184(void) {
    s32 count = 0;
    s32 i;
    u8* menu = lbl_2_bss_1A8248[0];
    for (i = 0; i < 9; i++) {
        if (*(s16*)(menu + 0x40B8 + i * 6) == 12) count++;
    }
    if (count == 0) {
        menu[0x44F7] = 1;
    }
}

// fn_2_442E8, size:0x80
s32 fn_2_442E8(void) {
    s32 i;
    s32 count = 0;
    u8* menu = lbl_2_bss_1A8248[0];
    for (i = 0; i < 9; i++) {
        s32 a = *(s16*)(menu + 0x40B8 + i * 6);
        if (a == 0 || a == 1) count++;
    }
    return count == 2;
}

// fn_2_44368, size:0xAC
s32 fn_2_44368(void) {
    s32 i;
    s32 count = 0;
    u8* menu = lbl_2_bss_1A8248[0];
    for (i = 0; i < 9; i++) {
        s32 a = *(s16*)(menu + 0x40B8 + i * 6);
        if (a == 13 || a == 29 || a == 30 || a == 31 || a == 32) count++;
    }
    return count >= 5;
}

// fn_2_42638, size:0xD0
void fn_2_42638(void) {
    s32 i;
    u8* d;
    u8* s;
    for (i = 0; i < 20; i++) {
        d = lbl_2_bss_1A824C[0] + 0x1978C7;
        s = lbl_2_bss_1A8248[0] + 0x43C2;
        d[i] = s[i];
    }
}

// fn_2_467FC, size:0xE0
void fn_2_467FC(void) {
    u8* entry;
    s32 i;
    for (i = 0; i < 54; i++) {
        entry = lbl_2_bss_1A8248[0] + i * 0x34;
        if (*(s8*)(entry + 4) == (s32)lbl_2_bss_1A8248[0][0x441C] && *(s8*)(entry + 5) <= 3) {
            entry[0x31] = 1;
        } else {
            entry[0x31] = 0;
        }
    }
}

// fn_2_45978, size:0x10C
void fn_2_45978(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 54; i++) {
        u8* entry = lbl_2_bss_1A8248[0] + i * 0x34;
        entry[7] = entry[6];
        for (j = 0; j < 10; j++) {
            entry[0x1D + j * 2] = entry[9 + j * 2];
            entry[0x1E + j * 2] = entry[10 + j * 2];
        }
        lbl_2_bss_1A8248[0][i + 0x444D] = 0;
        lbl_2_bss_1A8248[0][i + 0x4483] = 0;
        lbl_2_bss_1A8248[0][i + 0x44B9] = 0;
    }
}

// fn_2_409CC, size:0xD0
void fn_2_409CC(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        *(s32*)(lbl_80366B18 + 0x7A8) = ARAMTransfer(lbl_2_data_12298, 0, 1, 0);
        o[0x28] = 1;
        break;
    case 1:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            fn_800111B4(*(s32*)(lbl_80366B18 + 0x7A8));
            o[0x28] = 2;
        }
        break;
    case 2:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
}

// fn_2_3C03C, size:0x12C
void fn_2_3C03C(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(o + 0x14) = 1;
        o[0x28] = 1;
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            fn_2_94854(0xB);
            fn_2_9461C(0);
            fn_2_94604(1);
            fn_2_94634(1);
            *(s16*)(o + 0x14) = 0x14;
            o[0x28] = 2;
        }
        break;
    case 2:
        if ((*(s16*)(o + 0x14))-- == 0) {
            o[0x28] = 3;
        }
        break;
    case 3:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_3E7EC, size:0x12C
void fn_2_3E7EC(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(o + 0x14) = 1;
        o[0x28] = 1;
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            *(s16*)(o + 0x14) = 0x3C;
            fn_2_72054(0, 0xA);
            fn_2_72054(lbl_2_bss_1A8248[0][0x441E], 9);
            o[0x28] = 2;
        }
        break;
    case 2:
        if (fn_2_8CC88(0) != 0) {
            o[0x28] = 3;
        }
        break;
    case 3:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_3E918, size:0x12C
void fn_2_3E918(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(o + 0x14) = 1;
        o[0x28] = 1;
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            *(s16*)(o + 0x14) = 0x3C;
            fn_2_72054(0, 0xB);
            fn_2_72054(lbl_2_bss_1A8248[0][0x441E], 0xB);
            o[0x28] = 2;
        }
        break;
    case 2:
        if (fn_2_8CC88(0) != 0) {
            o[0x28] = 3;
        }
        break;
    case 3:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_3EBA8, size:0x118
void fn_2_3EBA8(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(o + 0x14) = 1;
        o[0x28] = 1;
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            *(s16*)(o + 0x14) = 0x3C;
            fn_2_72054(0, 0xA);
            o[0x28] = 2;
        }
        break;
    case 2:
        if ((*(s16*)(o + 0x14))-- == 0) {
            o[0x28] = 3;
        }
        break;
    case 3:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_3ECC0, size:0x118
void fn_2_3ECC0(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(o + 0x14) = 1;
        o[0x28] = 1;
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            *(s16*)(o + 0x14) = 0x3C;
            fn_2_72054(0, 0xA);
            o[0x28] = 2;
        }
        break;
    case 2:
        if ((*(s16*)(o + 0x14))-- == 0) {
            o[0x28] = 3;
        }
        break;
    case 3:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_3EDD8, size:0x118
void fn_2_3EDD8(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(o + 0x14) = 1;
        o[0x28] = 1;
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            *(s16*)(o + 0x14) = 0x3C;
            fn_2_72054(0, 9);
            o[0x28] = 2;
        }
        break;
    case 2:
        if ((*(s16*)(o + 0x14))-- == 0) {
            o[0x28] = 3;
        }
        break;
    case 3:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_3EEF0, size:0x114
void fn_2_3EEF0(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(o + 0x14) = 1;
        o[0x28] = 1;
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            *(s16*)(o + 0x14) = 0x3C;
            fn_2_72054(0, 0xB);
            o[0x28] = 2;
        }
        break;
    case 2:
        if (fn_2_8CC88(0) != 0) {
            o[0x28] = 3;
        }
        break;
    case 3:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_3F188, size:0x114
void fn_2_3F188(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(o + 0x14) = 1;
        o[0x28] = 1;
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            *(s16*)(o + 0x14) = 0x3C;
            fn_2_72054(0, 9);
            o[0x28] = 2;
        }
        break;
    case 2:
        if (fn_2_8CC88(0) != 0) {
            o[0x28] = 3;
        }
        break;
    case 3:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_3F44C, size:0x110
void fn_2_3F44C(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(o + 0x14) = 0x28;
        if (lbl_2_bss_1A8248[0][0x4418] != 0) {
            fn_80062890(8);
            o[0x28] = 1;
        } else {
            o[0x28] = 2;
        }
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            o[0x28] = 2;
        }
        break;
    case 2:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_3F55C, size:0x110
void fn_2_3F55C(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(o + 0x14) = 0x28;
        if (lbl_2_bss_1A8248[0][0x4418] < 5) {
            fn_80062890(7);
            o[0x28] = 1;
        } else {
            o[0x28] = 2;
        }
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            o[0x28] = 2;
        }
        break;
    case 2:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_4078C, size:0x130
void fn_2_4078C(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    u8* p;
    switch ((s8)o[0x28]) {
    case 0:
        lbl_2_bss_1A824C[0][0x19783E] = 0;
        o[0x28] = 1;
        break;
    case 1:
        p = (u8*)&lbl_803C77B8;
        p += *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20;
        if (*(u16*)(p + 2) & 0x100) {
            o[0x28] = 2;
        }
        break;
    case 2:
        lbl_2_bss_1A824C[0][0x19783E] = 1;
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_408BC, size:0x110
void fn_2_408BC(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(o + 0x14) = 0x3C;
        lbl_2_bss_1A824C[0][0x19782C] = 1;
        fn_2_72054(1, 0xD);
        fn_80062890(9);
        o[0x28] = 1;
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            o[0x28] = 2;
        }
        break;
    case 2:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_40A9C, size:0xF4
void fn_2_40A9C(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        lbl_2_bss_1A824C[0][0x1978F3] = 0;
        o[0x28] = 1;
        break;
    case 1:
        lbl_8036E548[0x307A] = 0;
        fn_2_20218(lbl_8036E548);
        lbl_2_bss_1A8234[0][0x162992] = 1;
        lbl_2_bss_1A8230[0][0x32A86] = 1;
        o[0x28] = 2;
        break;
    case 2:
        fn_2_1BF50();
        o[0x28] = 3;
        break;
    case 3:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
}

// fn_2_40B90, size:0x128
void fn_2_40B90(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        lbl_2_bss_1A824C[0][0x1978F3] = 0;
        o[0x28] = 1;
        break;
    case 1:
        lbl_8036E548[0x307A] = 0;
        fn_2_20218(lbl_8036E548);
        lbl_2_bss_1A8234[0][0x162992] = 1;
        lbl_2_bss_1A8230[0][0x32A86] = 1;
        o[0x28] = 2;
        break;
    case 2:
        o[0x28] = 3;
        break;
    case 3:
        fn_2_1BFD0();
        o[0x28] = 4;
        break;
    case 4:
        lbl_8034E978[0x26] = 1;
        o[0x28] = 5;
        break;
    case 5:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
}

// fn_2_3DF28, size:0x130
void fn_2_3DF28(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    u8* p;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(o + 0x14) = 0x14;
        o[0x28] = 1;
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            o[0x28] = 2;
        }
        break;
    case 2:
        p = (u8*)&lbl_803C77B8;
        p += *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20;
        if (*(u16*)(p + 2) & 0x300) {
            *(s16*)(o + 0x14) = 0x32;
            o[0x28] = 3;
        }
        break;
    case 3:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_3DC60, size:0x164
void fn_2_3DC60(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    u8* p;
    switch ((s8)o[0x28]) {
    case 0:
        lbl_2_bss_1A8234[0][0x16264B] = 1;
        *(s16*)(o + 0x14) = 0x10;
        fn_80062890(0x38);
        o[0x28] = 1;
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            o[0x28] = 2;
        }
        break;
    case 2:
        p = (u8*)&lbl_803C77B8;
        p += *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20;
        if (*(u16*)(p + 2) & 0x300) {
            lbl_2_bss_1A8234[0][0x162835] = 1;
            *(s16*)(o + 0x14) = 0x10;
            o[0x28] = 3;
        }
        break;
    case 3:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_3DDC4, size:0x164
void fn_2_3DDC4(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    u8* p;
    switch ((s8)o[0x28]) {
    case 0:
        lbl_2_bss_1A8234[0][0x16264C] = 1;
        *(s16*)(o + 0x14) = 0x10;
        fn_80062890(0x38);
        o[0x28] = 1;
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            o[0x28] = 2;
        }
        break;
    case 2:
        p = (u8*)&lbl_803C77B8;
        p += *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20;
        if (*(u16*)(p + 2) & 0x300) {
            lbl_2_bss_1A8234[0][0x162836] = 1;
            *(s16*)(o + 0x14) = 0x10;
            o[0x28] = 3;
        }
        break;
    case 3:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_3EA44, size:0x164
void fn_2_3EA44(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    u8* m;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(o + 0x14) = 1;
        o[0x28] = 1;
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            *(s16*)(o + 0x14) = 0x168;
            fn_2_72054(0, 9);
            fn_2_72054(lbl_2_bss_1A8248[0][0x441E], 0xA);
            o[0x28] = 2;
        }
        break;
    case 2:
        if (fn_2_8CC88(0) != 0) {
            o[0x28] = 3;
        }
        break;
    case 3:
        m = lbl_2_bss_1A8248[0];
        if (m[0x441C] == 5) {
            m[*(s16*)(m + 0x16C2) * 10 + 0x40F1] = 3;
        }
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_3F004, size:0x184
void fn_2_3F004(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    u8* m;
    u8 k;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(o + 0x14) = 1;
        o[0x28] = 1;
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            *(s16*)(o + 0x14) = 0x50;
            fn_2_72054(0, 0xA);
            o[0x28] = 2;
        }
        break;
    case 2:
        m = lbl_2_bss_1A8248[0];
        k = m[0x441C];
        if ((k == 3 && m[0x441E] == 1 && *(s16*)(m + 0x16C2) == 0xB) ||
            (k == 3 && m[0x441E] == 5 && *(s16*)(m + 0x16C2) == 0x2A)) {
            if ((*(s16*)(o + 0x14))-- == 0) {
                o[0x28] = 3;
            }
        } else if (fn_2_8CC88(0) != 0) {
            o[0x28] = 3;
        }
        break;
    case 3:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_3F29C, size:0x1B0
void fn_2_3F29C(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        lbl_2_bss_1A8234[0][0x1627B9] = 1;
        *(s16*)(o + 0x14) = 0xA;
        o[0x28] = 1;
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            lbl_2_bss_1A8248[0][0x4439] = 0;
            fn_2_92654(8, 0);
            fn_2_90428(9);
            fn_2_92654(9, 0xB);
            ((void (*)(s32, Vec*))fn_2_46C2C)(0, (Vec*)(lbl_2_data_3198 + 0xB4));
            lbl_2_bss_1A8248[0][0x441A] = 0;
            lbl_2_bss_1A8248[0][0x428E] = 0;
            fn_80062890(5);
            *(s16*)(o + 0x14) = 0x50;
            o[0x28] = 2;
        }
        break;
    case 2:
        if (*(s16*)(o + 0x14) == 0x46) {
            ((void (*)(s32, Vec*))fn_2_46C2C)(0, (Vec*)(lbl_2_data_3198 + 0xB4));
        }
        if ((*(s16*)(o + 0x14))-- == 0) {
            o[0x28] = 3;
        }
        break;
    case 3:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_4041C, size:0x198
// ~97%: only scheduling of the three lis DATA@ha in case 0 differs
void fn_2_4041C(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        if (((s32 (*)(s32))fn_2_45938)(*(s16*)(lbl_2_bss_1A8248[0] + 0x16C2)) == 0) {
            *(s16*)(o + 0x14) = 0xB4;
            lbl_2_bss_1A8248[0][*(s16*)(lbl_2_bss_1A8248[0] + 0x16C2) * 10 + 0x40F1] = 2;
            lbl_2_bss_1A824C[0][0x197854] = lbl_2_bss_1A8248[0][*(s16*)(lbl_2_bss_1A8248[0] + 0x16C2) * 10 + 0x40F3];
            lbl_2_bss_1A8234[0][0x1627C1] = 1;
            fn_80062890(3);
            o[0x28] = 1;
        } else {
            o[0x28] = 2;
        }
        break;
    case 1:
        if ((*(s16*)(o + 0x14))-- == 0) {
            o[0x28] = 2;
        }
        break;
    case 2:
        lbl_2_bss_1A8248[0][*(s16*)(lbl_2_bss_1A8248[0] + 0x16C2) * 10 + 0x40F1] = 3;
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_405B4, size:0x1D8
void fn_2_405B4(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        if (((s32 (*)(s32))fn_2_45938)(*(s16*)(lbl_2_bss_1A8248[0] + 0x16C2)) == 0) {
            *(s16*)(o + 0x14) = 0xB4;
            lbl_2_bss_1A8248[0][*(s16*)(lbl_2_bss_1A8248[0] + 0x16C2) * 10 + 0x40F1] = 2;
            lbl_2_bss_1A824C[0][0x197854] = lbl_2_bss_1A8248[0][*(s16*)(lbl_2_bss_1A8248[0] + 0x16C2) * 10 + 0x40F3];
            fn_2_90428(*(s8*)(lbl_2_bss_1A824C[0] + 0x197854) + 0xA);
            fn_2_90428(*(s8*)(lbl_2_bss_1A824C[0] + 0x197854) + 0x10);
            fn_2_92654(*(s8*)(lbl_2_bss_1A824C[0] + 0x197854) + 0xA, 0xC);
            lbl_2_bss_1A8234[0][0x1627C1] = 1;
            o[0x28] = 1;
        } else {
            o[0x28] = 2;
        }
        break;
    case 1:
        if (*(s16*)(o + 0x14) == 0x96) {
            fn_80062890(0x41);
        }
        if ((*(s16*)(o + 0x14))-- == 0) {
            o[0x28] = 2;
        }
        break;
    case 2:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_42388, size:0xEC
void fn_2_42388(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(lbl_2_bss_1A824C[0] + 0x1976E4) = 0x78;
        o[0x28] = 1;
        break;
    case 1:
        if (fn_2_40CB8() != 0) {
            o[0x28] = 2;
        }
        break;
    case 2:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

// fn_2_42EB0, size:0x118
// ~99%: li r0,0xa / addi r11 scheduling before the inner loop
void fn_2_42EB0(void) {
    s32 i;
    s32 j;
    u8* e;
    u8* m;
    for (i = 0; i < 54; i++) {
        if (lbl_800E8558[i * 6 + 3] == 1) {
            e = lbl_2_bss_1A8248[0] + i * 0x34;
            if (*(s8*)(e + 0x31) == 1) {
                for (j = 0; j < 10; j++) {
                    s32 row;
                    s16 v;
                    s16 t;
                    s16 a;
                    row = lbl_800E8558[i * 6 + 2] * 0x64;
                    v = *(s16*)(lbl_80109AE8 + row + j * 10);
                    t = *(s16*)(lbl_8010A768 + row + j * 10 + 2);
                    a = *(s16*)(lbl_8010A768 + row + j * 10 + 4);
                    if (t != -1 && *(s8*)(e + j * 2 + 0xA) == 0 && t == 0x12 &&
                        lbl_2_bss_1A8248[0][0x4415] >= a && lbl_2_bss_1A8248[0][0x442A] == 1) {
                        e[j * 2 + 0xA] = 1;
                    }
                    if (v != -1 && *(s8*)(e + j * 2 + 9) < 0) {
                        e[j * 2 + 0xA] = 1;
                    }
                }
            }
        }
    }
}

// fn_2_432EC, size:0x118
// not matching: lis order / r30,r31 swapped for the two tables
void fn_2_432EC(void) {
    s32 i;
    s32 j;
    s32 row;
    s16 v;
    s16 t;
    s16 a;
    s16 b;
    u8* e;
    for (i = 0; i < 54; i++) {
        if (lbl_800E8558[i * 6 + 3] == 1) {
            e = lbl_2_bss_1A8248[0] + i * 0x34;
            if (*(s8*)(e + 0x31) == 1) {
                for (j = 0; j < 10; j++) {
                    row = lbl_800E8558[i * 6 + 2] * 0x64;
                    v = *(s16*)(lbl_80109AE8 + row + j * 10);
                    t = *(s16*)(lbl_8010A768 + row + j * 10 + 2);
                    a = *(s16*)(lbl_8010A768 + row + j * 10 + 4);
                    b = *(s16*)(lbl_8010A768 + row + j * 10 + 6);
                    if (v != -1 && *(s8*)(e + j * 2 + 9) < 0) {
                        e[j * 2 + 0xA] = 1;
                    }
                    if (t == 1 && fn_8006CDC0(i) >= a && lbl_2_bss_1A8248[0][0x4415] >= b) {
                        e[j * 2 + 0xA] = 1;
                    }
                }
            }
        }
    }
}

// fn_2_44E2C, size:0xE8
s32 fn_2_44E2C(s32 ch) {
    s32 n;
    s32 j;
    u8* mi = lbl_800E8558 + ch * 6;
    u8 row;
    u8* p;
    if (mi[3] == 1) {
        n = 0;
        p = mi + 2;
        row = *p;
        for (j = 0; j < 10; j++) {
            if (*(s16*)(lbl_80109AE8 + row * 0x64 + j * 10) != -1) {
                n++;
            }
        }
        *p = row;
        return n;
    }
    return 0;
}

// fn_2_44414, size:0xF0
void fn_2_44414(void* arr) {
    SortEnt* a = arr;
    SortEnt tmp;
    s32 i;
    s32 j;
    for (i = 1; i < 55; i++) {
        tmp = a[i];
        a[0] = tmp;
        j = i - 1;
        while (tmp.k < a[j].k) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = tmp;
    }
}
