#include "challenge/auto_00_000085A8_text.h"
#include "challenge/auto_00_00004DD8_text.h"
#include "challenge/rep_0010.h"
#include "static/UnknownHomes_Static.h"

extern void fn_80035CA4(s32 id);
extern void fn_1_9AB0(void);
extern u8 lbl_1_data_B70[]; // TODO type: ARAM data for fn_80035838

typedef struct ChAnimObj {
    /*0x00*/ u8 _00[0x5C];
    /*0x5C*/ u32 frame; // 16.16
} ChAnimObj;

typedef struct ChAnimSlot {
    /*0x0*/ ChAnimObj* obj;
    /*0x4*/ u32 _4;
} ChAnimSlot;

extern ChAnimSlot lbl_80371C30[];

// Animation preview task (fn_1_86BC -> fn_1_8624).
typedef struct ChAnimTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ u16 objIdx; // lbl_80371C30 index
    /*0x16*/ u8 _16[2];
    /*0x18*/ u16 timer;
} ChAnimTask;

// .text:0x000085A8 size:0x7C
// Left/right picks the viewer animation (-1 = none).
void fn_1_85A8(void) {
    if (lbl_803C77B8._04 & 1) {
        if (--lbl_1_common_bss_472B4.anim < -1) {
            lbl_1_common_bss_472B4.anim = lbl_1_common_bss_472B4.animCount - 1;
        }
    } else if (lbl_803C77B8._04 & 2) {
        if (++lbl_1_common_bss_472B4.anim >= lbl_1_common_bss_472B4.animCount) {
            lbl_1_common_bss_472B4.anim = -1;
        }
    }
}

// .text:0x000088CC size:0x4
void fn_1_88CC(void) {
    return;
}

// .text:0x00008B8C size:0x4
void fn_1_8B8C(void) {
    return;
}

