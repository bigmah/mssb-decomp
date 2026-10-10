#include "menus/auto_00_00094854_text.h"

extern void fn_80034E20(void* object, void* data);
extern u8 lbl_2_data_311E4[];
typedef struct { u8* object; s32 pad; } MenuResource;
extern MenuResource lbl_80371C30[];

#include "static/UnknownHomes_Static.h"
extern u8 lbl_2_bss_1033C[];
extern void* lbl_803CC1B8[];

extern u8 lbl_803C66B0[];
extern void fn_80062674(s32 index);

extern u8* lbl_2_bss_1A824C[];


// fn_2_94854, size:0x18
void fn_2_94854(u8 value) {
    lbl_2_bss_1A824C[0][0x197849] = value;
}

// fn_2_95604, size:0x50
void fn_2_95604(void) {
    if ((lbl_803C66B0[0x4F] == 1) ? 1 : 0) {
        fn_80062674(0);
        lbl_803C66B0[0x4F] = 2;
    }
}

// fn_2_95B28, size:0x50
void fn_2_95B28(void) {
    if ((lbl_803C66B0[0x4F] == 1) ? 1 : 0) {
        fn_80062674(0);
        lbl_803C66B0[0x4F] = 2;
    }
}

// fn_2_9486C, size:0x4C
void fn_2_9486C(void) {
    void* object = lbl_803CC1B8[0];
    if (lbl_2_bss_1033C[0xF] != 0) {
        lbl_2_bss_1033C[0xF] = 0;
        fn_80034CEC(object);
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
}

// fn_2_948B8, size:0x84
void fn_2_948B8(void) {
    u8* object = (u8*)lbl_803CC1B8[0];
    lbl_2_bss_1033C[0xF] = 0;
    fn_80034E20(object, lbl_2_data_311E4);
    *(u32*)(lbl_80371C30[*(u16*)(object + 0x14)].object + 0x5C) = 0x280000;
    *(void (**)(void))lbl_803CC1B8[0] = fn_2_9486C;
}

extern u8 lbl_8034E978[];
extern u8 lbl_800FEF70[];
extern void fn_80053FE8(void);
extern void fn_2_96AD4(void);

// fn_2_96D20, size:0x74
void fn_2_96D20(void) {
    fn_800B0A5C_insertQueue(fn_80053FE8, 0x3000);
    lbl_8034E978[0] = 0x5B;
    lbl_8034E978[9] = lbl_8034E978[8];
    lbl_8034E978[8] = *(u16*)(lbl_800FEF70 + 0x5B8);
    fn_800B0A5C_insertQueue(fn_2_948B8, 0x3000);
    fn_800B0A5C_insertQueue(fn_2_96AD4, 0x3000);
}

extern s32 fn_80042DA8(void*, s32, s32);
extern void fn_800626EC(s32);

// fn_2_95E80, size:0xBC
void fn_2_95E80(u8* object) {
    u8 flag;
    if ((lbl_803C66B0[0x4F] == 1) ? 1 : 0) {
        flag = fn_80042DA8(object, 0, 0) != 0;
        if ((*(u32*)(lbl_80371C30[*(u16*)(object + 0x14)].object + 0x5C) >> 16) == 3) {
            changeScene(3, 6);
        }
        if ((s32)flag == 1) {
            lbl_2_bss_1033C[0xE] = 1;
            fn_80062674(0);
            lbl_803C66B0[0x4F] = 2;
        }
    }
}

// fn_2_95F3C, size:0xA4
void fn_2_95F3C(u8* object) {
    if ((lbl_803C66B0[0x4F] == 0) ? 1 : 0) {
        *(u8*)(lbl_80371C30[*(u16*)(object + 0x14)].object + 0x68) = 4;
        *(u8*)(lbl_80371C30[*(u16*)(object + 0x14) + 1].object + 0x68) = 4;
        *(u8*)(lbl_80371C30[*(u16*)(object + 0x14) + 3].object + 0x68) = 4;
        *(u8*)(lbl_80371C30[*(u16*)(object + 0x14) + 4].object + 0x68) = 4;
        fn_800626EC(0);
        lbl_803C66B0[0x4F] = 1;
    }
}

static inline void tally94(u8* o, s32 id, s32 f, s32* total, s32* hits) {
    *total += 1;
    *hits += fn_80042DA8(o, id, f) != 0;
}

// fn_2_95FE0, size:0x138
void fn_2_95FE0(u8* object) {
    s32 hits;
    s32 total;
    s32 i;
    if ((lbl_803C66B0[0x4F] == 1) ? 1 : 0) {
        hits = 0;
        total = 0;
        tally94(object, 0, 0xF, &total, &hits);
        for (i = 0; i < 3; i++) {
            if (i != *(s16*)(lbl_2_bss_1033C + 2)) {
                tally94(object, i + 6, 0xF, &total, &hits);
            }
        }
        if (hits == total) {
            changeScene(1, 6);
            *(u32*)(((u8**)lbl_80371C30)[(*(u16*)(object + 0x14) + 6) * 2] + 0x58) = (*(u32*)(((u8**)lbl_80371C30)[(*(u16*)(object + 0x14) + 6) * 2] + 0x58) & ~0xFFU) | 0xFF;
            *(u32*)(((u8**)lbl_80371C30)[(*(u16*)(object + 0x14) + 7) * 2] + 0x58) = (*(u32*)(((u8**)lbl_80371C30)[(*(u16*)(object + 0x14) + 7) * 2] + 0x58) & ~0xFFU) | 0xFF;
            *(u32*)(((u8**)lbl_80371C30)[(*(u16*)(object + 0x14) + 8) * 2] + 0x58) = (*(u32*)(((u8**)lbl_80371C30)[(*(u16*)(object + 0x14) + 8) * 2] + 0x58) & ~0xFFU) | 0xFF;
            fn_80062674(0);
            lbl_803C66B0[0x4F] = 2;
        }
    }
}

// fn_2_9493C, size:0x150
void fn_2_9493C(u8* object) {
    s32 a;
    s32 b;
    if ((lbl_803C66B0[0x4F] == 1) ? 1 : 0) {
        a = 0;
        b = 0;
        if (*(s8*)(lbl_2_bss_1033C + 6) != 0 && *(s16*)(lbl_2_bss_1033C + 2) == 0 && *(u8*)(lbl_2_bss_1033C + 0xB) == 0) {
            tally94(object, 0x13, 0, &b, &a);
        }
        if (a == b) {
            if (*(s8*)(lbl_2_bss_1033C + 6) != 0 && *(s16*)(lbl_2_bss_1033C + 2) == 0 && *(u8*)(lbl_2_bss_1033C + 0xB) == 0) {
                *(u32*)(((u8**)((u8*)lbl_80371C30 + 0x98))[*(u16*)(object + 0x14) * 2] + 0x5C) = 0;
                *(u32*)(((u8**)((u8*)lbl_80371C30 + 0xB0))[*(u16*)(object + 0x14) * 2] + 0x5C) = 0;
                *(u16*)(((u8**)((u8*)lbl_80371C30 + 0x98))[*(u16*)(object + 0x14) * 2] + 0x64) = 0x1A;
                *(u16*)(((u8**)((u8*)lbl_80371C30 + 0xB0))[*(u16*)(object + 0x14) * 2] + 0x64) = 0x10;
            }
            fn_80062674(0);
            lbl_803C66B0[0x4F] = 2;
        }
    }
}
