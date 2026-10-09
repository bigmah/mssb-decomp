#include "menus/rep_0568.h"

#include <string.h>
#include "Dolphin/GX.h"
#include "Dolphin/mtx.h"
extern u8 lbl_8036E548[];
extern u8 lbl_2_bss_100B8[];

extern u8 lbl_8036E548[];
extern u8 lbl_2_bss_100B8[];
extern u8* lbl_2_bss_1224;
extern void fn_2_18398(void);
extern void fn_2_188EC(void);
extern const f32 lbl_2_rodata_5BC;
extern const f32 lbl_2_rodata_5D4;
extern const f32 lbl_2_rodata_5D8;
extern const f32 lbl_2_rodata_5DC;
extern const f32 lbl_2_rodata_5E0;
extern const f32 lbl_2_rodata_5E4;
extern const f32 lbl_2_rodata_5E8;
extern void fn_800BDA94(void*, s32);
extern u8 lbl_8034E9A0[];

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

// fn_2_18650, size:0xF8
s32 fn_2_18650(s32 a) {
    s32 next = (*(s8*)&lbl_2_bss_100B8[0] + 1) % 10;
    if (next != *(s8*)&lbl_2_bss_100B8[1]) {
        if (lbl_2_bss_1224 == NULL) {
            lbl_2_bss_1224 = fn_800B0A5C_insertQueue(fn_2_18398, 0xFFFF);
            if (lbl_2_bss_1224 != NULL) {
                lbl_2_bss_1224[0x1C] = 0;
                lbl_2_bss_1224[0x1D] = 0;
            } else {
                return 0;
            }
        }
        lbl_2_bss_100B8[*(s8*)&lbl_2_bss_100B8[0] + 2] = a;
        lbl_2_bss_100B8[0] = next;
        lbl_2_bss_100B8[a + 0x42] = 1;
        return 1;
    }
    return 0;
}

// fn_2_18FBC, size:0xFC
void fn_2_18FBC(void) {
    u8* q;
    s32 i;
    q = fn_800B0A5C_insertQueue(fn_2_188EC, 0x6000);
    lbl_2_bss_100B8[0x19] = 0;
    lbl_2_bss_100B8[0x1B] = 1;
    if (lbl_8034E9A0[0x4701] == 0) {
        for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
            ((s8*)lbl_2_bss_100B8)[i + 0x27] = -1;
        }
        q[0x1C] = 0;
    } else {
        for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
            lbl_2_bss_100B8[i + 0x14] = 0;
        }
        q[0x1C] = 0;
    }
    lbl_2_bss_100B8[0] = i = 0;
    lbl_2_bss_100B8[1] = 0;
    for (; i < 10; i++) {
        ((s8*)lbl_2_bss_100B8)[i + 2] = -1;
    }
}
