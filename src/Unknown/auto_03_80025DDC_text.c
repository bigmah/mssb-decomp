#include "Unknown/auto_03_80025DDC_text.h"

// fn_80026130, size:0x4
void fn_80026130(void) {
}

// fn_80025DDC, size:0x110
void fn_80025DDC(u8* h) {
    u8* q;
    s32 off;
    u8* p;
    u8* e;
    s32 i;
    s32 j;
    s32 k;
    *(u32*)(h + 0x10) = 0;
    if (*(u32*)(h + 0xC) != 0) {
        *(u32*)(h + 0xC) = (u32)h + *(u32*)(h + 0xC);
    }
    if (*(u32*)(h + 8) != 0) {
        *(u32*)(h + 8) = (u32)h + *(u32*)(h + 8);
    }
    if (*(u32*)(h + 8) != 0) {
        i = 0;
        off = 0;
        for (; i < *(u16*)(h + 2); i++) {
            e = *(u8**)(h + 8) + off;
            *(u32*)(e + 8) = (u32)h + *(u32*)(e + 8);
            p = *(u8**)(e + 8);
            for (j = 0; j < *(u16*)(e + 2); j++) {
                *(u32*)(p + 8) = (u32)h + *(u32*)(p + 8);
                q = p;
                for (k = 0; k < *(u16*)(e + 0); k++) {
                    *(u32*)(q + 0xC) = (u32)h + *(u32*)(q + 0xC);
                    q += 4;
                }
                p += *(u32*)(e + 4);
            }
            off += 0xC;
        }
    }
    if (*(u32*)(h + 0xC) != 0) {
        for (i = 0; i < *(u16*)(h + 4); i++) {
            u8* t = *(u8**)(h + 0xC);
            *(u32*)(t + i * 0x10 + 0xC) = (u32)h + *(u32*)(t + i * 0x10 + 0xC);
        }
    }
}
