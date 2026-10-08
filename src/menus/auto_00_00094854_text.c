#include "menus/auto_00_00094854_text.h"

extern u8 lbl_803C66B0[];
extern void fn_80062674(s32 index);

extern u8* lbl_2_bss_1A824C[];


// fn_2_94854, size:0x18
void fn_2_94854(u8 value) {
    lbl_2_bss_1A824C[0][0x197849] = value;
}

// fn_2_95604, size:0x50
void fn_2_95604(void) {
    if ((lbl_803C66B0[0x4F] == 1) ? 1 : 0) {
        fn_80062674(0);
        lbl_803C66B0[0x4F] = 2;
    }
}

// fn_2_95B28, size:0x50
void fn_2_95B28(void) {
    if ((lbl_803C66B0[0x4F] == 1) ? 1 : 0) {
        fn_80062674(0);
        lbl_803C66B0[0x4F] = 2;
    }
}
