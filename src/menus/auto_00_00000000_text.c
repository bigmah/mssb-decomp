#include "menus/auto_00_00000000_text.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXTev.h"

extern void fn_800A7D4C(s32, void*);
extern void* fn_800B0A5C_insertQueue(void*, s32);
extern void fn_800B0A14_removeQueue(void);

extern u8 lbl_2_data_C0[];
extern u8* lbl_2_bss_4;

typedef struct {
    u8 pad0[2];
    u16 held;
    u8 pad4[0x1C];
} PadEntry;
extern u8* lbl_803CBBCC[];
extern PadEntry lbl_803C77B8[];

// fn_2_0, size:0x3C
void fn_2_0(void) {
    GXSetZCompLoc(0);
    GXSetAlphaCompare(4, 0, 0, 7, 0);
}

