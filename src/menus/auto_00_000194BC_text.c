#include "menus/auto_00_000194BC_text.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_2_bss_1033C[];
extern u8 lbl_800EF808[];
extern u8 lbl_80366158[];
extern u8 lbl_800E8754[];
extern void fn_80021204(void);
extern s32 fn_8003AE70(s32 selector);

// fn_2_194BC, size:0x2C
void fn_2_194BC(u8* object) {
    void* p = *(void**)(object + 0x70);
    if (p != NULL) {
        fn_800B9AA8(p);
    }
}

// fn_2_194E8, size:0x38
void fn_2_194E8(void) {
    fn_80021204();
    lbl_800E8754[0x25] = lbl_80366158[0x1F];
}

// fn_2_19554, size:0x84
s8 fn_2_19554(void) {
    s32 result = 0;
    if (lbl_800EF808[0x398] != fn_8003AE70(0) || lbl_800EF808[0x397] != fn_8003AE70(1) || lbl_80366158[0x1F] != fn_8003AE70(2)) {
        result = 1;
    }
    return result;
}
