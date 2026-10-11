#include "main/file_8003A688.h"
#include "main/file_80039AC0.h"
#include "main/file_800A7C08.h"
#include "main/file_800B0724.h"
#include "stl/string.h"

extern TrailSystem lbl_802D3D80;
// Current process-queue task (typed per caller, see SceneTask in file_80069BDC.h).
extern SaveTask* lbl_803CC1B8;

// .text:0x8003A688 size:0x28
void fn_8003A688(s32 type, f32 speed, f32 spread) {
    lbl_802D3D80.params[type].speed = speed / 2;
    lbl_802D3D80.params[type].spread = spread / 2;
}

// .text:0x8003A6B0 size:0x198
void fn_8003A6B0(void) {
    return;
}

extern u8 lbl_803CB828[3];

// fn_8003A848, size:0x14
void fn_8003A848(u8 red, u8 green, u8 blue) {
    lbl_803CB828[0] = red;
    lbl_803CB828[1] = green;
    lbl_803CB828[2] = blue;
}

// .text:0x8003A85C size:0x44
void fn_8003A85C(u8 enabled) {
    lbl_802D3D80.enabled = enabled;
    lbl_802D3D80.head = 0;
    lbl_802D3D80.tail = 0;
    memset(lbl_802D3D80.texMode, 0, sizeof(lbl_802D3D80.texMode));
}

// .text:0x8003A8A0 size:0x3F0
void fn_8003A8A0(void) {
    return;
}

// .text:0x8003AC90 size:0xF4
void fn_8003AC90(void) {
    return;
}

// .text:0x8003AD84 size:0xD0
void fn_8003AD84(void) {
    return;
}

extern u32 lbl_803CBCB8;

extern u8 lbl_803CBCB4;

extern u8 lbl_802D4B00[];

// fn_8003AE70, size:0x5C
u8 fn_8003AE70(s32 selector) {
    u8 value = 0;
    switch (selector) {
    case 0:
        value = lbl_802D4B00[0x95];
        break;
    case 1:
        value = lbl_802D4B00[0x94];
        break;
    case 2:
        value = lbl_802D4B00[0x96];
        break;
    }
    return value;
}

// fn_8003AE54, size:0x8
u8 fn_8003AE54(void) {
    return lbl_803CBCB4;
}

// fn_8003AE5C, size:0x8
void fn_8003AE5C(u8 value) {
    lbl_803CBCB4 = value;
}

// fn_8003AE64, size:0xC
void fn_8003AE64(void) {
    lbl_803CBCB8 = 0x0;
}

// .text:0x8003AECC size:0x6E4
void fn_8003AECC(void) {
    return;
}

// .text:0x8003B5B0 size:0x5E0
void fn_8003B5B0(void) {
    return;
}

// .text:0x8003BB90 size:0x3C4
void fn_8003BB90(void) {
    return;
}

// .text:0x8003BF54 size:0xB8
void fn_8003BF54(void) {
    return;
}

// .text:0x8003C00C size:0x28CC
void fn_8003C00C(void) {
    return;
}

// .text:0x8003E8D8 size:0x964
void fn_8003E8D8(void) {
    return;
}

// .text:0x8003F23C size:0x7C
void fn_8003F23C(void) {
    return;
}

// .text:0x8003F2B8 size:0x1284
void fn_8003F2B8(void) {
    return;
}

// .text:0x8004053C size:0x6D8
void fn_8004053C(void) {
    return;
}

// .text:0x80040C14 size:0x3CC
void fn_80040C14(void) {
    return;
}

// .text:0x80040FE0 size:0x94
void fn_80040FE0(void) {
    return;
}

// .text:0x80041074 size:0xDC
void fn_80041074(void) {
    return;
}

// .text:0x80041150 size:0x1F8
void fn_80041150(void) {
    return;
}

// .text:0x80041348 size:0x1F4
void fn_80041348(void) {
    return;
}

// .text:0x8004153C size:0x40
void fn_8004153C(void) {
    return;
}

extern u16 lbl_803CBCC0;

// fn_8004157C, size:0x24
s32 fn_8004157C(void) {
    if (lbl_803CBCC0 != 0) {
        lbl_803CBCC0--;
        return 1;
    }
    return 0;
}

// fn_800415A0, size:0x8
void fn_800415A0(u16 value) {
    lbl_803CBCC0 = value;
}

// .text:0x800415A8 size:0xAD4
void fn_800415A8(void) {
    return;
}
