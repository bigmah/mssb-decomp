#include "game/rep_2940.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_8036E548[];
extern void fn_3_6A25C(void);
extern void fn_3_6A250(void);

// .text:0x000E11E0 size:0x118 mapped:0x80720274
void fn_3_E11E0(void) {
    return;
}

// .text:0x000E12F8 size:0x78 mapped:0x8072038C
void fn_3_E12F8(void) {
    int i;
    u8* p;
    for (i = 0; i < 4; i++) {
        p = *(u8**)(lbl_8036E548 + i * 4 + 0x2C50);
        if (p != NULL) {
            p[0x25D] = 0;
        }
    }
    fn_3_6A25C();
    fn_3_6A250();
}

// .text:0x000E1370 size:0x108 mapped:0x80720404
void fn_3_E1370(int mode) {
    s8* mg = (s8*)&g_Minigame;
    u8* p;
    int i;
    for (i = 0; i < 4; i++) {
        if (mode == 3) {
            p = *(u8**)(lbl_8036E548 + i * 4 + 0x2C50);
            if (g_d_GameSettings.GameModeSelected == 2) {
                p = *(u8**)(lbl_8036E548 + 0x2C74);
                if (i >= 1) {
                    return;
                }
            }
            if (p != NULL) {
                p[0x25A] = mg[0x19EC + i * 9] / 2;
                p[0x25B] = mg[0x19EC + i * 9] % 2;
            }
        }
    }
}

// .text:0x000E1478 size:0x4EC mapped:0x8072050C
void fn_3_E1478(void) {
    return;
}

