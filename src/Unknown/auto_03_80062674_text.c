#include "Unknown/auto_03_80062674_text.h"
#include "static/UnknownHomes_Static.h"

extern u32 lbl_803C663C[4];

extern u8 lbl_803C66B0[];

// fn_800626EC, size:0x58
void fn_800626EC(s32 index) {
    if (((u8*)&g_d_GameSettings)[0x10] == 0) {
        lbl_803C66B0[0x55] = 1;
    } else {
        u8* entry = lbl_803C66B0 + index;
        entry[0x55] = 1;
    }
    lbl_803C663C[index]++;
}

// fn_80062744, size:0x20
void fn_80062744(void) {
    lbl_803C663C[3] = 0;
    lbl_803C663C[2] = 0;
    lbl_803C663C[1] = 0;
    lbl_803C663C[0] = 0;
}
