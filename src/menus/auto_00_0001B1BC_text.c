#include "menus/auto_00_0001B1BC_text.h"
#include "menus/auto_00_0004B1AC_text.h"
#include "static/UnknownHomes_Static.h"

extern u8* lbl_2_bss_1A8234[];
extern u8* lbl_2_bss_1A824C[];
extern u8* lbl_2_bss_1A8248;
extern u8* lbl_2_bss_1A823C[];
extern u8* lbl_803CC1B8;
extern void fn_2_409CC(void);
extern s32 fn_2_4EB2C(void);
extern s32 fn_2_4EAF4(void);
extern s32 fn_2_4E9A8(void);
extern u8 lbl_800EF808[];
extern u8 lbl_80366B18[];
extern void fn_2_68DAC(s32 index, void* result);
extern void fn_80068720(s32);
extern void fn_8001F228(void);
extern void fn_80021410(void);

// fn_2_1B52C, size:0x94
void fn_2_1B52C(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        if (fn_2_4E970() == 1) {
            o[0x28] = 1;
        }
        break;
    case 1:
        o[0x28] = 6;
        break;
    case 6:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
}

