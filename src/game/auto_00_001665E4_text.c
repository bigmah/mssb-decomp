#include "game/auto_00_001665E4_text.h"
#include "game/auto_00_00097144_text.h"
#include "game/rep_3E00.h"
#include "main/file_800A6870.h"
#include "main/file_80011640.h"

extern AssetLoadInstructions lbl_3_data_284E8[2];

// Steps the trail-file load; returns 1 once it is done.
// .text:0x001665E4 size:0xCC mapped:0x807A5678
s32 fn_3_1665E4(void) {
    GameHudFlags* hud = &lbl_3_common_bss_32724;

    switch (hud->loadStep) {
    case 0:
        lbl_8036E548.trailFile = ARAMTransfer(&lbl_3_data_284E8[1], NULL, 0, 0);
        hud->loadStep++;
        break;
    case 1:
        if (lbl_803C6CF8.idle == 1) {
            hud->loadStep++;
        }
        break;
    case 2:
        fn_3_166448();
        hud->loadStep++;
        break;
    default:
        return 1;
    }
    return 0;
}

