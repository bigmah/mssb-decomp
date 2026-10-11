#include "main/file_8004C5F8.h"

// .text:0x8004C5F8 size:0x404
void fn_8004C5F8(void) {
    return;
}

extern u32 lbl_803CB878;

extern u32 lbl_803CB874;

// fn_8004C9FC, size:0xC
void fn_8004C9FC(void) {
    lbl_803CB874 = lbl_803CB878;
}

// fn_8004CA08, size:0xC
void fn_8004CA08(u32 value) {
    lbl_803CB878 = value;
    lbl_803CB874 = value;
}

// .text:0x8004CA14 size:0x34
void fn_8004CA14(void) {
    return;
}

// .text:0x8004CA48 size:0x24
void fn_8004CA48(void) {
    return;
}

// .text:0x8004CA6C size:0x1AC
void fn_8004CA6C(void) {
    return;
}

extern u8 lbl_803C5F74[];

// fn_8004CC18, size:0x14
void fn_8004CC18(void) {
    *(u8*)(lbl_803C5F74 + 0x3) = 0x4;
}

// fn_8004CC2C, size:0x20
void fn_8004CC2C(void) {
    if (lbl_803C5F74[3] != 4) {
        lbl_803C5F74[3] = 3;
    }
}

// fn_8004CC4C, size:0x74
void fn_8004CC4C(u8 first, u8 second, u8 third, s32 selection, s16 value) {
    u8* state = lbl_803C5F74;
    if (state[0] == 0) {
        state[1] = first;
        state[2] = third;
        state[3] = 0;
        state[4] = second;
        state[0x1E] = 0;
        *(s16*)(state + 6) = 0;
        *(s16*)(state + 0xE) = -1;
        *(s16*)(state + 8) = 0;
        *(s16*)(state + 0x10) = -1;
        *(s16*)(state + 0xA) = 0;
        *(s16*)(state + 0x12) = -1;
        *(s16*)(state + 0xC) = 0;
        *(s16*)(state + 0x14) = -1;
        state[0x1B] = 0;
        state[0x1C] = 0;
        if (selection >= 0) {
            state[0x1A] = selection;
            *(s16*)(state + 0x18) = value;
            return;
        }
        *(s8*)(state + 0x1A) = -1;
    }
}

// .text:0x8004CCC0 size:0x430
void fn_8004CCC0(void) {
    return;
}

// .text:0x8004D0F0 size:0x370
void fn_8004D0F0(void) {
    return;
}

// .text:0x8004D460 size:0x90
void fn_8004D460(void) {
    return;
}

// .text:0x8004D4F0 size:0x8C
void fn_8004D4F0(void) {
    return;
}

// .text:0x8004D57C size:0x3C0
void fn_8004D57C(void) {
    return;
}

// .text:0x8004D93C size:0x54
void fn_8004D93C(void) {
    return;
}

// .text:0x8004D990 size:0x200
void fn_8004D990(void) {
    return;
}

// .text:0x8004DB90 size:0x75C
void fn_8004DB90(void) {
    return;
}

// .text:0x8004E2EC size:0x218
void fn_8004E2EC(void) {
    return;
}

// .text:0x8004E504 size:0xB0
void fn_8004E504(void) {
    return;
}

// .text:0x8004E5B4 size:0x78
void fn_8004E5B4(void) {
    return;
}

// .text:0x8004E62C size:0x858
void fn_8004E62C(void) {
    return;
}

// .text:0x8004EE84 size:0x70
void fn_8004EE84(void) {
    return;
}

// .text:0x8004EEF4 size:0x218
void fn_8004EEF4(void) {
    return;
}

// .text:0x8004F10C size:0x858
void fn_8004F10C(void) {
    return;
}

// .text:0x8004F964 size:0x400
void fn_8004F964(void) {
    return;
}

// .text:0x8004FD64 size:0x3C
void fn_8004FD64(void) {
    return;
}

// .text:0x8004FDA0 size:0x48
void fn_8004FDA0(void) {
    return;
}

// .text:0x8004FDE8 size:0x350
void fn_8004FDE8(void) {
    return;
}

// .text:0x80050138 size:0x5B0
void fn_80050138(void) {
    return;
}

// .text:0x800506E8 size:0x78
void fn_800506E8(void) {
    return;
}

// .text:0x80050760 size:0x818
void fn_80050760(void) {
    return;
}

// .text:0x80050F78 size:0x70
void fn_80050F78(void) {
    return;
}

// .text:0x80050FE8 size:0x3A4
void fn_80050FE8(void) {
    return;
}

// .text:0x8005138C size:0x974
void fn_8005138C(void) {
    return;
}

// .text:0x80051D00 size:0x488
void fn_80051D00(void) {
    return;
}

// .text:0x80052188 size:0x28
void fn_80052188(void) {
    return;
}

// .text:0x800521B0 size:0x25C
void fn_800521B0(void) {
    return;
}

// .text:0x8005240C size:0x228
void fn_8005240C(void) {
    return;
}

// .text:0x80052634 size:0x58
void fn_80052634(void) {
    return;
}

extern u32 lbl_803CBD14;

// fn_8005268C, size:0x8
u32 fn_8005268C(void) {
    return lbl_803CBD14;
}

// .text:0x80052694 size:0xA0
void fn_80052694(void) {
    return;
}

extern u32 lbl_803CB880;

extern u8 lbl_803C639C[];

// fn_80052734, size:0x34
void* fn_80052734(s32 index) {
    u8* camera;
    if (index < 0) {
        index = 0;
    } else if (index >= 2) {
        index = 1;
    }
    camera = lbl_803C639C + index * 0xA8;
    return camera + 0x150;
}

// fn_80052768_getCamera, size:0x30
camera_803c639c_s* fn_80052768_getCamera(int index) {
    if (index < 0) {
        index = 0;
    } else if (index >= 2) {
        index = 1;
    }
    return (camera_803c639c_s*)(lbl_803C639C + index * 0xA8);
}

// fn_800527BC, size:0x8
u32 fn_800527BC(void) {
    return lbl_803CB880;
}

// fn_80052798, size:0x24
void fn_80052798(s32 count) {
    if (count < 1) {
        count = 1;
    } else if (count > 2) {
        count = 2;
    }
    lbl_803CB880 = count;
}
