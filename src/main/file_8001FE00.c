#include "main/file_8001FE00.h"

// .text:0x8001FE00 size:0x248
void fn_8001FE00(void) {
    return;
}

// .text:0x80020048 size:0x1D0
void calledWhenStartingMatch(void) {
    return;
}

// .text:0x80020218 size:0x34
void fn_80020218(void) {
    return;
}

// .text:0x8002024C size:0x2C
void fn_8002024C(void) {
    return;
}

// .text:0x80020278 size:0x110
void fn_80020278(void) {
    return;
}

// .text:0x80020388 size:0x58
void fn_80020388(void) {
    return;
}

// .text:0x800203E0 size:0xEC
void fn_800203E0(void) {
    return;
}

// .text:0x800204CC size:0xD0
void changeScene(void) {
    return;
}

// .text:0x8002059C size:0x88
void fn_8002059C(void) {
    return;
}

// .text:0x80020624 size:0xD8
void fn_80020624(void) {
    return;
}

// .text:0x800206FC size:0x968
void fn_800206FC(void) {
    return;
}

// .text:0x80021064 size:0x124
void fn_80021064(void) {
    return;
}

// .text:0x80021188 size:0x34
void fn_80021188(void) {
    return;
}

// .text:0x800211BC size:0x34
void fn_800211BC(void) {
    return;
}

extern u8 lbl_800EFBC0[];

extern u8 lbl_800EF808[];
extern u8 lbl_800E8754[];

// fn_80021204, size:0x24
void fn_80021204(void) {
    u8 first = lbl_800EF808[0x398];
    u8 second = lbl_800EF808[0x396];
    lbl_800E8754[0x23] = first;
    lbl_800E8754[0x24] = second;
}

// fn_800211F0, size:0x14
u8 fn_800211F0(void) {
    return *(u32*)(lbl_800EFBC0 + 0x18) & 0xFF;
}

// .text:0x80021228 size:0x64
void fn_80021228(void) {
    return;
}

// .text:0x8002128C size:0x7C
void fn_8002128C(void) {
    return;
}
