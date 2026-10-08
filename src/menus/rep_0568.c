#include "menus/rep_0568.h"

#include <string.h>
extern u8 lbl_8036E548[];
extern u8 lbl_2_bss_100B8[];

extern u8 lbl_8036E548[];
extern u8 lbl_2_bss_100B8[];

#include "static/UnknownHomes_Static.h"


// fn_2_190B8, size:0x24
void fn_2_190B8(u8* object) {
    fn_800B9AA8(*(void**)(object + 0x70));
}

// fn_2_16CE0, size:0x58
void fn_2_16CE0(void) {
    u8* resource;
    s32 i;
    for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
        resource = *(u8**)(lbl_8036E548 + i * 4 + 0x2C50);
        if (resource != NULL && *(s16*)(resource + 0x62) == 0x6B) {
            lbl_2_bss_100B8[i + 0x40] = 1;
        }
    }
}

// fn_2_16D38, size:0x70
void fn_2_16D38(void) {
    s32 i;
    for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
        memset(*(void**)(lbl_8036E548 + i * 0x27C + 0xC0C), 0, 0x5C);
    }
}
