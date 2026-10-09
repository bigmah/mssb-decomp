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

