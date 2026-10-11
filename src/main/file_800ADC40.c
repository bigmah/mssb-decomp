#include "main/file_800ADC40.h"

// .text:0x800ADC40 size:0x130
void fn_800ADC40(void) {
    return;
}

// .text:0x800ADD70 size:0x1F0
void fn_800ADD70(void) {
    return;
}

// .text:0x800ADF60 size:0x338
void YUV2RGB(void) {
    return;
}

// .text:0x800AE298 size:0x320
void YUV2RGB_(void) {
    return;
}

// .text:0x800AE5B8 size:0x300
void fn_800AE5B8(void) {
    return;
}

// .text:0x800AE8B8 size:0x260
void fn_800AE8B8(void) {
    return;
}

// .text:0x800AEB18 size:0x20C
void MovStreamThread(void) {
    return;
}

extern u32 lbl_803CC19C;

// fn_800AED24, size:0x10
s32 fn_800AED24(void) {
    return !lbl_803CC19C;
}

// .text:0x800AED34 size:0x474
void MovDecodeThread(void) {
    return;
}

// .text:0x800AF1A8 size:0x454
void fn_800AF1A8(void) {
    return;
}

// .text:0x800AF5FC size:0x3B8
void fn_800AF5FC(void) {
    return;
}

// .text:0x800AF9B4 size:0x23C
void fn_800AF9B4(void) {
    return;
}

// .text:0x800AFBF0 size:0x20
void fn_800AFBF0(void) {
    return;
}

// .text:0x800AFC10 size:0x13C
void fn_800AFC10(void) {
    return;
}

// .text:0x800AFD4C size:0x264
void fn_800AFD4C(void) {
    return;
}

extern u8 lbl_803C79D4[];

extern u32 lbl_803C7A00[9];

// fn_800AFFC0, size:0x48
void fn_800AFFC0(u32 count) {
    u32* state = lbl_803C7A00;
    u32 position = state[4] + count;
    state[4] = position;
    if (position >= state[3]) {
        state[4] = position - state[6];
    }
    state[7] -= count;
    state[8] += count;
}

// fn_800AFFB0, size:0x10
u8 fn_800AFFB0(void) {
    return *(u8*)(lbl_803C79D4 + 0x28);
}

// .text:0x800B0008 size:0x12C
void fn_800B0008(void) {
    return;
}

// .text:0x800B0134 size:0xFC
void fn_800B0134(void) {
    return;
}

// .text:0x800B0230 size:0x160
void fn_800B0230(void) {
    return;
}

// .text:0x800B0390 size:0x64
void fn_800B0390(void) {
    return;
}

// .text:0x800B03F4 size:0x18C
void fn_800B03F4(void) {
    return;
}

// .text:0x800B0580 size:0x64
void fn_800B0580(void) {
    return;
}

// .text:0x800B05E4 size:0x140
void fn_800B05E4(void) {
    return;
}
