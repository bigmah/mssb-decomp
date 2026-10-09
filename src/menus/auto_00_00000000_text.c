#include "menus/auto_00_00000000_text.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXTev.h"

extern void fn_800A7D4C(s32, void*);
extern void* fn_800B0A5C_insertQueue(void*, s32);
extern void fn_800B0A14_removeQueue(void);

extern void fn_8001F228(void);
extern void fn_80062744(void);
extern void fn_8001E474(void);
extern void fn_80036C88(void*, void*);
extern void fn_800B0D28(void*);
extern struct {
    u8 pad[0x28];
    u16 menu[0x10];
} lbl_800E8754;
extern u8 lbl_2_data_0[];
extern u8 lbl_2_data_C0[];
extern u8* lbl_2_bss_4;

typedef struct {
    u8 pad0[2];
    u16 held;
    u8 pad4[0x1C];
} PadEntry;
extern u8* lbl_803CBBCC[];
extern PadEntry lbl_803C77B8[];

// fn_2_0, size:0x3C
void fn_2_0(void) {
    GXSetZCompLoc(0);
    GXSetAlphaCompare(4, 0, 0, 7, 0);
}

// fn_2_3C, size:0x2C
void fn_2_3C(void) {
    fn_800A7D4C(0, lbl_2_data_C0);
}

// NOTE fn_2_110: 6 diff lines (sthx r4,r7,r0 with addi r0,r3,0xc index; ours folds to sth 0xC(r3))

// fn_2_160, size:0x48
void fn_2_160(void) {
    *(u16*)(lbl_803CBBCC[0] + 0xC) |= *(u16*)((u8*)lbl_803C77B8 + 2);
    *(u16*)(lbl_803CBBCC[0] + 0xE) |= *(u16*)((u8*)lbl_803C77B8 + 0x22);
    lbl_803CBBCC[0][0x10] = 0;
}

// fn_2_2D8, size:0x4
void fn_2_2D8(void) {
}

// fn_2_2DC, size:0x4C
void fn_2_2DC(void) {
    u8* q = lbl_2_bss_4;
    u8 n = (q[0x15] + 1) % 32;
    if (n != q[0x16]) {
        q[0x15] = n;
        q[q[0x15] + 0x17] = 2;
    }
}

// fn_2_328, size:0x4C
void fn_2_328(void) {
    u8* q = lbl_2_bss_4;
    u8 n = (q[0x15] + 1) % 32;
    if (n != q[0x16]) {
        q[0x15] = n;
        q[q[0x15] + 0x17] = 1;
    }
}

// fn_2_4C4, size:0x4C
s32 fn_2_4C4(u8* q, s8 value) {
    u8 n = (q[0x15] + 1) % 32;
    if (n == q[0x16]) {
        return 0;
    }
    q[0x15] = n;
    q[q[0x15] + 0x17] = value;
    return 1;
}

// fn_2_510, size:0x44
u8 fn_2_510(u8* q) {
    if (q[0x16] == q[0x15]) {
        return 0;
    }
    q[0x16] = (q[0x16] + 1) % 32;
    return q[q[0x16] + 0x17];
}

