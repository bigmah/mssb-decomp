#include "game/auto_00_0006B4C8_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_0001D86C_text.h"
#include "game/auto_00_000249E8_text.h"
#include "main/file_800639BC.h"
#include "main/file_8000F150.h"
#include "main/file_800BD8C4.h"

// main.dol (main/file_80011640.h, which declares a conflicting view of lbl_8036E548)
void fn_8001196C(void);
void fn_80011A60(void);
void fn_80011BE4(s32 index);
s32 fn_8001594C(s32 team);
// game.rel calls pass kind unextended (lwz) or sign-extended (s8): it was built against an s32 kind
s32 fn_80016344(s32 kind, s32 index, s32 arg2, s32 roster);
s32 fn_8001500C(s32 team, s32 roster, s32 index);

typedef struct Unk80353A90 {
    /*0x000*/ u8 _000[0x103];
    /*0x103*/ s8 _103; // character id
    /*0x104*/ u8 _104[0x108 - 0x104];
} Unk80353A90; // size: 0x108
extern Unk80353A90 lbl_80353A90;


extern u8 lbl_3_data_FAA8[0x1C]; // practice roster id -> character id

// .text:0x0006B4C8 size:0x110 mapped:0x806AA55C
s32 fn_3_6B4C8(void) {
    s32 i;

    if (lbl_3_common_bss_32724._9A == 0) {
        fn_80011A60();
        lbl_8036E548._2D77 = 0;
        lbl_3_common_bss_32724._9A = 1;
    }
    if (fn_80016344(lbl_8034E9A0.captain[g_d_GameSettings.humanTeamNumber], 0xC, 1,
                    ((u8*)lbl_8034E9A0.captainSlot)[g_d_GameSettings.humanTeamNumber])) {
        for (i = 0; i < 9; i++) {
            if (lbl_8036E548.actors[i]->kind == lbl_8034E9A0.captain[g_d_GameSettings.humanTeamNumber]) {
                lbl_8036E548.actors[i] = &lbl_8036E548.storage[12];
                lbl_8036E548.actors[12] = NULL;
                break;
            }
        }
        return 1;
    }
    return 0;
}

// .text:0x0006B5D8 size:0x9C mapped:0x806AA66C
s32 fn_3_6B5D8(void) {
    switch (lbl_3_common_bss_32724._9A) {
    case 0:
        lbl_8036E548._2D77 = 0;
        lbl_3_common_bss_34C58._2C = 0;
        lbl_3_common_bss_32724._9A++;
        break;
    case 1:
        if (fn_80016344(lbl_80353A90._103, 9, 0, 0)) {
            return 1;
        }
        break;
    }
    return 0;
}

// .text:0x0006B674 size:0x1FC mapped:0x806AA708
void fn_3_6B674(void) {
    return;
}

// .text:0x0006B870 size:0x1F4 mapped:0x806AA904
void fn_3_6B870(void) {
    return;
}

// .text:0x0006BA64 size:0x308 mapped:0x806AAAF8
void fn_3_6BA64(void) {
    return;
}

// .text:0x0006BD6C size:0x138 mapped:0x806AAE00
void fn_3_6BD6C(void) {
    return;
}
