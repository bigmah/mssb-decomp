#include "menus/rep_10C0.h"

extern u8* lbl_2_bss_1A8248[];


// fn_2_9461C, size:0x18
void fn_2_9461C(s16 value) {
    *(s16*)(lbl_2_bss_1A8248[0] + 0x19774A) = value;
}

// fn_2_94604, size:0x18
void fn_2_94604(u8 value) {
    *(u8*)(lbl_2_bss_1A8248[0] + 0x197856) = value;
}

extern u8* lbl_2_bss_1A824C[];
typedef struct {
    f32 f[6];
} F6;
extern F6 lbl_2_data_3BB0[];

// fn_2_94634, size:0xA8
void fn_2_94634(s32 i) {
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197668) = lbl_2_data_3BB0[i].f[0];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x19766C) = lbl_2_data_3BB0[i].f[1];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197670) = lbl_2_data_3BB0[i].f[2];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197674) = lbl_2_data_3BB0[i].f[3];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197678) = lbl_2_data_3BB0[i].f[4];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x19767C) = lbl_2_data_3BB0[i].f[5];
    if (i == 0) {
        *(u8*)(lbl_2_bss_1A824C[0] + 0x197855) = 0;
        return;
    }
    *(u8*)(lbl_2_bss_1A824C[0] + 0x197855) = 1;
}

extern const f32 lbl_2_rodata_1180;
extern const f32 lbl_2_rodata_1184;
extern f32 lbl_2_bss_1A81D4[];

// fn_2_946DC, size:0x178
void fn_2_946DC(s32 i) {
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197668) = lbl_2_data_3BB0[i].f[0];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x19766C) = lbl_2_data_3BB0[i].f[1];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197670) = lbl_2_data_3BB0[i].f[2];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197674) = lbl_2_data_3BB0[i].f[3];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197678) = lbl_2_data_3BB0[i].f[4];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x19767C) = lbl_2_data_3BB0[i].f[5];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197620) = lbl_2_bss_1A81D4[0x13];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197624) = lbl_2_bss_1A81D4[0x14];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197628) = lbl_2_bss_1A81D4[0x15];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x19762C) = lbl_2_rodata_1180 + lbl_2_bss_1A81D4[0x13];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197630) = lbl_2_rodata_1180 + lbl_2_bss_1A81D4[0x14];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197634) = lbl_2_rodata_1180 + lbl_2_bss_1A81D4[0x15];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197638) = lbl_2_rodata_1180 + lbl_2_bss_1A81D4[0x10];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x19763C) = lbl_2_rodata_1180 + lbl_2_bss_1A81D4[0x11];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197640) = lbl_2_rodata_1180 + lbl_2_bss_1A81D4[0x12];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197644) = lbl_2_rodata_1184 + lbl_2_bss_1A81D4[0x10];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x197648) = lbl_2_rodata_1184 + lbl_2_bss_1A81D4[0x11];
    *(f32*)(lbl_2_bss_1A824C[0] + 0x19764C) = lbl_2_rodata_1184 + lbl_2_bss_1A81D4[0x12];
}
