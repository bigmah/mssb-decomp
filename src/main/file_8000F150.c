#include "main/file_8000F150.h"

// .text:0x8000F150 size:0x298
void fn_8000F150(void) {
    return;
}

// .text:0x8000F3E8 size:0xA4
void fn_8000F3E8(void) {
    return;
}

// .text:0x8000F48C size:0x2C
void somethingSetTexturePointer(void) {
    return;
}

// .text:0x8000F4B8 size:0x7C
void fn_8000F4B8(void) {
    return;
}

// .text:0x8000F534 size:0x3C0
void fn_8000F534(void) {
    return;
}

// .text:0x8000F8F4 size:0x94
void fn_8000F8F4(void) {
    return;
}

// .text:0x8000F988 size:0x114
void fn_8000F988(void) {
    return;
}

// .text:0x8000FA9C size:0x2B8
void fn_8000FA9C(void) {
    return;
}

// .text:0x8000FD54 size:0x24
void fn_8000FD54(void) {
    return;
}

// .text:0x8000FD78 size:0x24
void fn_8000FD78(void) {
    return;
}

// .text:0x8000FD9C size:0x6C
void fn_8000FD9C(void) {
    return;
}

// .text:0x8000FE08 size:0x4C
void fn_8000FE08(void) {
    return;
}

// .text:0x8000FE54 size:0x94
void fn_8000FE54(void) {
    return;
}

// .text:0x8000FEE8 size:0x1C
void fn_8000FEE8(void) {
    return;
}

// .text:0x8000FF04 size:0x1A0
void fn_8000FF04(void) {
    return;
}

// .text:0x800100A4 size:0x3F4
void fn_800100A4(void) {
    return;
}

// .text:0x80010498 size:0xA94
void DrawText(void) {
    return;
}

// .text:0x80010F2C size:0x74
void DrawTextOnCondition(void) {
    return;
}

// .text:0x80010FA0 size:0x60
void fn_80010FA0(void) {
    return;
}

// .text:0x80011000 size:0x140
void fn_80011000(void) {
    return;
}

// .text:0x80011140 size:0x74
void fn_80011140(void) {
    return;
}

// .text:0x800111B4 size:0x24
void fn_800111B4(void) {
    return;
}

// .text:0x800111D8 size:0x24
void fn_800111D8(void) {
    return;
}

// .text:0x800111FC size:0x15C
void fn_800111FC(void) {
    return;
}

// .text:0x80011358 size:0x110
void fn_80011358(void) {
    return;
}

// .text:0x80011468 size:0x108
void fn_80011468(void) {
    return;
}

extern u32 lbl_803CBC18;

extern u8 lbl_8036E548[];

// fn_80011578, size:0x50
void fn_80011578(void) {
    s8 i = 0;
    s32 n;
    for (n = 13; n != 0; n--) {
        if (i >= 0 && i < 13) {
            u8* object = *(u8**)(lbl_8036E548 + ((s8)i << 2) + 0x2C50);
            if (object != NULL) {
                *(u32*)(object + 0x5C) = 0;
            }
        }
        i++;
    }
}

// fn_800115C8, size:0x3C
void fn_800115C8(s8 index) {
    if (index >= 0 && index < 13) {
        u8* base = lbl_8036E548;
        u8* object;
        base += index * 4;
        object = *(u8**)(base + 0x2C50);
        if (object != NULL) {
            *(u32*)(object + 0x5C) = 0;
        }
    }
}

// fn_80011570, size:0x8
u32 fn_80011570(void) {
    return lbl_803CBC18;
}

// fn_80011604, size:0x3C
void fn_80011604(s8 index, u32 value) {
    u8* base;
    u8* object;
    if (index < 0 || index >= 13) {
        return;
    }
    base = lbl_8036E548;
    base += index * 4;
    object = *(u8**)(base + 0x2C50);
    if (object != NULL) {
        *(u32*)(object + 0x5C) = value;
    }
}
