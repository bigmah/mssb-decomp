#include "game/rep_23E8.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1E08.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_3_common_bss_35154[];
extern f32 lbl_3_rodata_2438;
extern f32 lbl_3_rodata_243C;

// .text:0x000CB738 size:0x9C mapped:0x8070A7CC
void fn_3_CB738(void) {
    u8* b = lbl_3_common_bss_35154;
    if (*(u8*)((u8*)&g_d_GameSettings + 0x55) != 0 || b[0x479] != 0 || (*(s16*)(b + 0x404))-- == 0) {
        b[0x40A] = 0;
        ((void (*)(void))fn_800B0A14_removeQueue)();
    } else {
        fn_3_BD8D8();
        *(f32*)(b + 0x3EC) = *(f32*)(b + 0x3EC) + lbl_3_rodata_2438;
        *(f32*)(b + 0x3F8) = *(f32*)(b + 0x3F8) + lbl_3_rodata_243C;
    }
}

// .text:0x000CB7D4 size:0x14 mapped:0x8070A868
void fn_3_CB7D4(void) {
    *(s16*)(lbl_3_common_bss_35154 + 0x404) = 0;
}

// .text:0x000CB7E8 size:0xC0 mapped:0x8070A87C
void fn_3_CB7E8(void) {
    return;
}

