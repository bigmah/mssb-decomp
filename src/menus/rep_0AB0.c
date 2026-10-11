#include "menus/rep_0AB0.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_8000F150.h"
#include "main/file_8004207C.h"
#include "main/file_800527C4.h"
#include "menus/auto_00_0004B1AC_text.h"
#include "menus/rep_0788.h"

extern u8* lbl_2_bss_1A8234[]; // menu layout work area (byte offsets, as elsewhere in menus)
extern void* lbl_803CC1B8;
extern InitEntry lbl_2_data_20C68[];
extern InitEntry lbl_2_data_268A8[];

// .text:0x0005979C size:0x55C
void fn_2_5979C(void) {
    return;
}

// .text:0x00059CF8 size:0x52C
void fn_2_59CF8(void) {
    return;
}

// .text:0x0005A224 size:0xC30
void fn_2_5A224(void) {
    return;
}

// .text:0x0005AE54 size:0xD0
void fn_2_5AE54(void) {
    MenuQueueState* queue = lbl_803CC1B8;
    switch ((s32)queue->stateA) {
    case 1:
        break;
    case 0:
        fn_2_4E878(queue, lbl_2_data_20C68);
        queue->stateA = 1;
        queue->timerA = 0;
        break;
    }
    fn_2_53F88((s32)queue);
    fn_2_54120();
    if (lbl_2_bss_1A8234[0][0x162992] != 0) {
        fn_2_53DF8((u8*)queue);
        fn_8000F8F4((LayoutGroup*)queue);
        fn_8000FE54();
        fn_800B0A14_removeQueue(fn_2_4E858(queue));
        queue->stateA = 0;
        queue->stateB = 0;
        lbl_2_bss_1A8234[0][0x162992] = 0;
    }
}

// .text:0x0005AF24 size:0x8C
void fn_2_5AF24(void) {
    MenuQueueState* queue;
    lbl_8034E978.menu = 0x53;
    fn_800B0A5C_insertQueue(fn_80053FE8, 0);
    queue = fn_800B0A5C_insertQueue(fn_2_5AE54, 0);
    queue->stateA = 0;
    queue->stateB = 0;
    fn_2_54354(lbl_2_data_268A8, 0x2E0);
    lbl_2_bss_1A8234[0][0x162604] = 1;
    lbl_2_bss_1A8234[0][0x162605] = 1;
}

// .text:0x0005AFB0 size:0x82C
void fn_2_5AFB0(void) {
    return;
}

// .text:0x0005B7DC size:0xDDC
void fn_2_5B7DC(void) {
    return;
}

// .text:0x0005C5B8 size:0x5A4
void fn_2_5C5B8(void) {
    return;
}

// .text:0x0005CB5C size:0x710
void fn_2_5CB5C(void) {
    return;
}

// .text:0x0005D26C size:0x9F0
void fn_2_5D26C(void) {
    return;
}

// .text:0x0005DC5C size:0x4A8
void fn_2_5DC5C(void) {
    return;
}

// .text:0x0005E104 size:0x748
void fn_2_5E104(void) {
    return;
}
