#include "Unknown/auto_03_8001B200_text.h"

extern u8 lbl_8036E548[];

// fn_8001B200, size:0x14
void fn_8001B200(void) {
    *(u32*)(lbl_8036E548 + 0x308c) = 0x0;
}

// fn_8001B214, size:0x10
void fn_8001B214(u32 value) {
    *(u32*)(lbl_8036E548 + 0x308c) = value;
}
