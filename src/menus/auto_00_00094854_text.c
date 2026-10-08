#include "menus/auto_00_00094854_text.h"

extern void fn_80034E20(void* object, void* data);
extern u8 lbl_2_data_311E4[];
typedef struct { u8* object; s32 pad; } MenuResource;
extern MenuResource lbl_80371C30[];

#include "static/UnknownHomes_Static.h"
extern u8 lbl_2_bss_1033C[];
extern void* lbl_803CC1B8[];

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

// fn_2_9486C, size:0x4C
void fn_2_9486C(void) {
    void* object = lbl_803CC1B8[0];
    if (lbl_2_bss_1033C[0xF] != 0) {
        lbl_2_bss_1033C[0xF] = 0;
        fn_80034CEC(object);
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
}

// fn_2_948B8, size:0x84
void fn_2_948B8(void) {
    u8* object = (u8*)lbl_803CC1B8[0];
    lbl_2_bss_1033C[0xF] = 0;
    fn_80034E20(object, lbl_2_data_311E4);
    *(u32*)(lbl_80371C30[*(u16*)(object + 0x14)].object + 0x5C) = 0x280000;
    *(void (**)(void))lbl_803CC1B8[0] = fn_2_9486C;
}
