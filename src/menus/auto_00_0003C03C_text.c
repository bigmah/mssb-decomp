#include "menus/auto_00_0003C03C_text.h"
#include "string.h"
#include "Dolphin/vec.h"

extern u8* lbl_2_bss_1A8248[];
extern u8* lbl_2_bss_1A824C[];
extern u8 lbl_803CB8F0[];
extern u32 lbl_803CBD0C[];
extern u32* lbl_2_data_13374[];
extern void fn_80031CA4(Vec*, u32*);
extern u8 lbl_2_bss_15B8[];
extern void* lbl_2_data_12C0C[];
extern void* lbl_2_data_12CE8[];

// fn_2_42474, size:0x1C
void fn_2_42474(void) {
    u8* menu = lbl_2_bss_1A824C[0];
    *(s16*)(menu + 0x1976E4) = 0x78;
}
