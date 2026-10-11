#include "main/file_80008E00.h"

extern u32 lbl_803CBBB8;

// fn_80008E00, size:0x8
void fn_80008E00(u32 value) {
    lbl_803CBBB8 = value;
}

// .text:0x80008E08 size:0x1C8
void fn_80008E08(void) {
    return;
}

// .text:0x80008FD0 size:0x3C
void PostRetraceCallback(void) {
    return;
}

extern u32 lbl_803CBBBC;

extern u32 lbl_803CBBAC;

extern u8 lbl_803C6CF8[];
extern s32 lbl_803CBBA0;
extern u8 lbl_803CBBA4;

// fn_80009028, size:0x6C
u8 fn_80009028(void) {
    switch (*(s8*)(lbl_803C6CF8 + 0x722)) {
    case 0:
        lbl_803CBBA4 = 0;
        break;
    case -1:
    case 4:
    case 5:
    case 6:
    case 11:
        lbl_803CBBA0 = *(s8*)(lbl_803C6CF8 + 0x722);
        lbl_803CBBA4 = 1;
        break;
    }
    return lbl_803CBBA4;
}

// fn_8000900C, size:0xC
void fn_8000900C(void) {
    lbl_803CBBAC = 0x1;
}

// fn_80009018, size:0x10
u32 fn_80009018(u32 value) {
    u32 previous = lbl_803CBBBC;
    lbl_803CBBBC = value;
    return previous;
}

// .text:0x80009094 size:0x20
void fn_80009094(void) {
    return;
}

// .text:0x800090B4 size:0x90
void fn_800090B4(void) {
    return;
}

// .text:0x80009144 size:0x3C
void fn_80009144(void) {
    return;
}

// .text:0x80009180 size:0x55C
void main(void) {
    return;
}

// .text:0x800096DC size:0xC4
void PrepFilesToBeLoaded(void) {
    return;
}

// .text:0x800097A0 size:0x6F4
void fn_800097A0(void) {
    return;
}

// .text:0x80009E94 size:0x178
void interpolatePointsUnknown(void) {
    return;
}

// .text:0x8000A00C size:0x88
void BezierInterpolate(void) {
    return;
}

// .text:0x8000A094 size:0x18
void fn_8000A094(void) {
    return;
}
