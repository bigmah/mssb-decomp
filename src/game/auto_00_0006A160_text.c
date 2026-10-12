#include "game/auto_00_0006A160_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_000249E8_text.h"
#include "game/rep_1E08.h"

// Views declared in the unit headers (kept out of them: other units have their own views).
extern ActorMgrView lbl_8036E548;
extern Unk32724 lbl_3_common_bss_32724;

typedef struct Unk35154 {
    /*0x000*/ u8 _000[0x3AC];
    /*0x3AC*/ u32 _3AC;
    /*0x3B0*/ u8 _3B0[0x480 - 0x3B0];
} Unk35154; // size: 0x480
extern Unk35154 lbl_3_common_bss_35154;

// .text:0x0006A25C size:0x48 mapped:0x806A92F0
void fn_3_6A25C(void) {
    s32 i;

    if (lbl_8036E548.stadium != NULL) {
        for (i = 0; i < 4; i++) {
            lbl_8036E548.stadium->parts[i].active = 0;
        }
    }
    lbl_3_common_bss_32724._D4 = 0;
}

// .text:0x0006A258 size:0x4 mapped:0x806A92EC
void fn_3_6A258(void) {
    return;
}

// .text:0x0006A254 size:0x4 mapped:0x806A92E8
void fn_3_6A254(void) {
    return;
}

// .text:0x0006A250 size:0x4 mapped:0x806A92E4
void fn_3_6A250(void) {
    return;
}

// .text:0x0006A160 size:0xF0 mapped:0x806A91F4
void fn_3_6A160(void) {
    s32 kind;

    if (g_Ball.framesSinceHit == 0 && (lbl_3_common_bss_35154._3AC & 3) == 0) {
        if (g_Batter.captainStarSwingActivated != 0 || g_Batter.didNonCaptainStarSwingConnect) {
            kind = 4;
        } else if (g_Batter.hitGeneralType == 3) {
            kind = 0;
        } else if (g_Batter.displayContactSprite != 0) {
            kind = 3;
        } else if (g_Batter.contactType == 2) {
            kind = 2;
        } else {
            kind = 1;
        }
        if (g_Batter.batterHand == 0) {
            fn_3_BE174(kind, g_Batter.hitContactPos.x, -g_Batter.hitContactPos.y, g_Batter.hitContactPos.z);
        } else {
            fn_3_BE174(kind, -g_Batter.hitContactPos.x, -g_Batter.hitContactPos.y, g_Batter.hitContactPos.z);
        }
    }
}

