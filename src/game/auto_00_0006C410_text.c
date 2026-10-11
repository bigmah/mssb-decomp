#include "game/auto_00_0006C410_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_000249E8_text.h"
#include "game/auto_00_0006A160_text.h"

// Views declared in the unit headers (kept out of them: other units have their own views).
extern ActorMgrView lbl_8036E548;
extern Unk32724 lbl_3_common_bss_32724;

// .text:0x0006C410 size:0x18 mapped:0x806AB4A4
void fn_3_6C410(void) {
    lbl_8036E548.stadium->_0C6 = 0;
}

// .text:0x0006C428 size:0x4 mapped:0x806AB4BC
void fn_3_6C428(void) {
    return;
}

// .text:0x0006C42C size:0x28 mapped:0x806AB4C0
void fn_3_6C42C(void) {
    lbl_8036E548.stadium->_0C6 = 0;
    lbl_3_common_bss_32724._90 = -1;
}

// .text:0x0006C454 size:0x78 mapped:0x806AB4E8
void fn_3_6C454(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (lbl_8036E548.actors[i + 9] != NULL) {
            lbl_8036E548.actors[i + 9]->_25D = 0;
        }
    }
    fn_3_6A25C();
    fn_3_6A250();
}

// .text:0x0006C4CC size:0x4 mapped:0x806AB560
void fn_3_6C4CC(void) {
    return;
}
