#include "game/rep_4138.h"
#include "header_rep_data.h"

extern s32 lbl_3_bss_D6F0[];
extern u8 g_Scores[];
extern u8 g_Strikes[];

void fn_3_16E1A0(void) {
    s32* o = lbl_3_bss_D6F0;
    o[0] = *(s16*)(g_Scores + 0x2A);
    o[1] = *(s16*)(g_Scores + 4);
    o[2] = *(s32*)g_Scores;
    o[3] = *(s32*)g_Strikes;
    o[4] = *(s32*)(g_Strikes + 4);
    o[5] = *(s32*)(g_Strikes + 8);
}

extern u16* lbl_3_bss_D6E4;
extern s32 lbl_3_bss_D6E8;

void fn_3_16E2FC(u16* p, s32 i) {
    if (p == NULL) {
        return;
    }
    if (p[0] - 1 < i) {
        return;
    }
    lbl_3_bss_D6E4 = p;
    lbl_3_bss_D6E8 = i;
}

// .text:0x0016D810 size:0x1A0 mapped:0x807AC8A4
void fn_3_16D810(void) {
    return;
}

// .text:0x0016D9B0 size:0x1BC mapped:0x807ACA44
void fn_3_16D9B0(void) {
    return;
}

// .text:0x0016DB6C size:0x458 mapped:0x807ACC00
void fn_3_16DB6C(void) {
    return;
}

extern u8 lbl_3_bss_D6EC;

// .text:0x0016E328 size:0x10
void fn_3_16E328(void) {
    lbl_3_bss_D6EC = 1;
}
