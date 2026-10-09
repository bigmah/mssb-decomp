#include "menus/auto_00_00071EC4_text.h"

#include "static/UnknownHomes_Static.h"

extern u8* lbl_2_bss_1A8248[];
extern u8 lbl_803C66B0[];
extern u8 lbl_8034E978[];
extern void* lbl_2_data_2A1E8[];
extern void* lbl_2_data_2A2EC[];
extern s32 lbl_2_bss_A840;
extern void fn_80062674(s32 index);
extern void fn_800626EC(s32 index);
extern void fn_800625A4(s32 a, s32 b);
extern u8* lbl_803CC1B8;
extern u8 lbl_800FEF70[];
#include "menus/auto_00_00001254_text.h"

// fn_2_73028, size:0x4
void fn_2_73028(void) {
}

// fn_2_71EC4, size:0x38
void fn_2_71EC4(u8* obj) {
    ((void (*)(u8*))lbl_2_data_2A1E8[*(s16*)(obj + 0x94)])(obj);
}

// fn_2_71EFC, size:0x24
void fn_2_71EFC(u8* obj) {
    s32 i = *(s32*)(obj + 0x80);
    u8* b = lbl_2_bss_1A8248[0];
    *(u8*)(b + i * 0xD8 + 0x16D0) = 0;
}

