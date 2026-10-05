#include "game/rep_1038.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"

// .text:0x0006BEA4 size:0x15C mapped:0x806AAF38
void fn_3_6BEA4(void) {
    return;
}

// .text:0x0006C000 size:0xE0 mapped:0x806AB094
void fn_3_6C000(void) {
    return;
}

// .text:0x0006C0E0 size:0x28 mapped:0x806AB174
extern u8 lbl_3_common_bss_32724[];

void fn_3_6C0E0(void) {
    *(s16*)(lbl_3_common_bss_32724 + 0x90) = -1;
    *(s16*)(lbl_3_common_bss_32724 + 0x92) = 0;
    lbl_3_common_bss_32724[0xA9] = 0;
    lbl_3_common_bss_32724[0xD3] = 0;
    lbl_3_common_bss_32724[0xB5] = 0;
}

// .text:0x0006C108 size:0x34 mapped:0x806AB19C
extern void fn_3_B93C8(s32);

void fn_3_6C108(void) {
    fn_3_B93C8(1);
    lbl_3_common_bss_32724[0xAE] = 0;
}

// .text:0x0006C13C size:0x14 mapped:0x806AB1D0
extern u8 g_Scores[];

void fn_3_6C13C(void) {
    g_Scores[0xC3] = 0;
}

// .text:0x0006C150 size:0x88 mapped:0x806AB1E4
extern void fn_3_6916C(void*);
extern void fn_3_674E0(void);
extern void fn_3_97800(void);
extern u8 lbl_8036E548[];

void fn_3_6C150(void) {
    *(s16*)(lbl_3_common_bss_32724 + 0x9E) = -1;
    *(s16*)(lbl_3_common_bss_32724 + 0xA0) = -1;
    *(s16*)(lbl_3_common_bss_32724 + 0xA2) = -1;
    fn_3_6916C(lbl_3_common_bss_32724);
    fn_3_674E0();
    fn_3_97800();
    if (((u8*)&g_d_GameSettings)[0x11] != 0) {
        lbl_8036E548[0x307E] = 0;
        return;
    }
    if (((u8*)&g_d_GameSettings)[7] != 2) {
        lbl_8036E548[0x307A] = 1;
        lbl_8036E548[0x307E] = 1;
    }
}

// .text:0x0006C1D8 size:0x238 mapped:0x806AB26C
void fn_3_6C1D8(void) {
    return;
}

