#include "main/file_80063028.h"

// .text:0x80063028 size:0x384
void fn_80063028(void) {
    return;
}

// .text:0x800633AC size:0x36C
void fn_800633AC(void) {
    return;
}

// .text:0x80063718 size:0xA4
void fn_80063718(void) {
    return;
}

extern void fn_80063718(void);

// fn_800637BC, size:0x18
s32 fn_800637BC(s32 unused, void** object) {
    *(void (**)(void))((u8*)*object + 0x94) = fn_80063718;
    return 0;
}

// fn_800637D4, size:0x8
s32 fn_800637D4(void) {
    return 0;
}

// .text:0x800637DC size:0xD8
void fn_800637DC(void) {
    return;
}

// .text:0x800638B4 size:0x18
void fn_800638B4(void) {
    return;
}

// .text:0x800638CC size:0x8C
void fn_800638CC(void) {
    return;
}

// .text:0x80063958 size:0x64
void fn_80063958(void) {
    return;
}
