#include "game/rep_F80.h"
#include "header_rep_data.h"

extern u8 g_Batter[];
extern u8 lbl_3_common_bss_32220[];
extern void fn_3_C07A0(void);
extern void fn_3_C0770(void);
extern void fn_3_C07B0(void);
extern void fn_3_BF1AC(void);
extern void fn_3_CABB4(void);
extern void fn_80011578(void);

extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_8036E548[];

// .text:0x0006A2A4 size:0x5C mapped:0x806A9338
void fn_3_6A2A4(s8 idx) {
    u8* e = *(u8**)(lbl_8036E548 + 0x64) + (idx - 0x1F) * 0x90 + 0x34;
    lbl_3_common_bss_32724[0xD4] = 1;
    e[0x5B] = 2;
    *(f32*)(e + 0x5C) = 0.0f;
    e[0x59] = 1;
    *(f32*)(e + 0x54) = 1.0f;
    e[0x5A] = 1;
}

// .text:0x0006A300 size:0x100 mapped:0x806A9394
void fn_3_6A300(void) {
    return;
}

// .text:0x0006A400 size:0x14 mapped:0x806A9494

void fn_3_6A400(void) {
    lbl_3_common_bss_32724[0xD4] = 0;
}

// .text:0x0006A414 size:0x428 mapped:0x806A94A8
void fn_3_6A414(void) {
    return;
}

// .text:0x0006A83C size:0x174 mapped:0x806A98D0
void fn_3_6A83C(void) {
    return;
}

// .text:0x0006A9B0 size:0xE8 mapped:0x806A9A44
void fn_3_6A9B0(void) {
    return;
}

// .text:0x0006AA98 size:0x98 mapped:0x806A9B2C
void fn_3_6AA98(void) {
    if (*(s16*)(g_Batter + 0x62) == 2 || *(s16*)(g_Batter + 0x62) == 3 || *(s16*)(g_Batter + 0x62) == 6) {
        return;
    }
    {
        u8 t = lbl_3_common_bss_32220[0xA];
        if (t == 0) {
            return;
        }
        if (t == 3 || t == 4) {
            fn_3_C07A0();
        } else if (t == 9) {
            fn_3_C0770();
        } else if (*(s16*)(lbl_3_common_bss_32220 + 2) == 2 && t == 2) {
            fn_3_C07B0();
        }
    }
}

// .text:0x0006AB30 size:0x28 mapped:0x806A9BC4
void fn_3_6AB30(void) {
    fn_3_BF1AC();
    fn_3_CABB4();
    fn_80011578();
}

// .text:0x0006AB58 size:0x368 mapped:0x806A9BEC
void fn_3_6AB58(void) {
    return;
}

