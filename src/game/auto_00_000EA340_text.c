#include "game/auto_00_000EA340_text.h"

typedef struct {
    u8* p;
    s32 pad;
} QEnt;

extern u8 lbl_3_common_bss_32724[];
extern u8 g_GameLogic[];
extern u8 lbl_80371C30[];
extern u8* lbl_803CC1B8;
extern u8 lbl_3_data_8FCC[];
extern void* fn_80034CEC(void*);
extern void fn_800B0A14_removeQueue(void*);
extern void fn_80034E20(void*, void*, void*);

// fn_3_EBFD4, size:0x40
s32 fn_3_EBFD4(void) {
    if (lbl_3_common_bss_32724[0x96] != 0 || g_GameLogic[0x11E] == 2 || g_GameLogic[0x11E] == 8) {
        return 1;
    }
    return 0;
}

// fn_3_EB684, size:0x5C
s32 fn_3_EB684(void) {
    if (lbl_3_common_bss_32724[0x96] != 0 || lbl_3_common_bss_32724[0xB7] != 0) {
        return 1;
    }
    if (g_GameLogic[0x11E] != 1 && g_GameLogic[0x11E] != 2 && g_GameLogic[0x11E] != 0xB) {
        return 1;
    }
    return 0;
}

// fn_3_ED244, size:0x64
void fn_3_ED244(void) {
    u8* p = lbl_803CC1B8;
    if (lbl_3_common_bss_32724[0x96] != 0 || ((QEnt*)lbl_80371C30)[*(u16*)(p + 0x14)].p[0x69] == 2) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// fn_3_ED2A8, size:0x4C
void fn_3_ED2A8(void) {
    fn_80034E20(lbl_803CC1B8, lbl_3_data_8FCC, &lbl_803CC1B8);
    *(void**)lbl_803CC1B8 = fn_3_ED244;
}
