#include "game/auto_00_0006AEC0_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_000249E8_text.h"

// Views declared in the unit headers (kept out of them: other units have their own views).
extern ActorMgrView lbl_8036E548;
extern Unk32724 lbl_3_common_bss_32724;

// .text:0x0006AEC0 size:0x20 mapped:0x806A9F54
void fn_3_6AEC0(void) {
    lbl_3_common_bss_32724._C8 = 0;
    lbl_3_common_bss_32724._C9 = 0;
    lbl_3_common_bss_32724._CA = 0;
    lbl_3_common_bss_32724._D4 = 0;
}

// .text:0x0006AEE0 size:0xBC mapped:0x806A9F74
void fn_3_6AEE0(void) {
    s32 i;

    for (i = 0; i < 9; i++) {
        if (lbl_8036E548.actors[i] != NULL) {
            lbl_8036E548.actors[i]->_25D = 0;
        }
    }
}
