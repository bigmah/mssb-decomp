#include "menus/rep_0840.h"
#define REP_HEADER_FN repHeader_menus_0840
#include "header_rep_inline.h"
// math.h first with dolsqrtf2 static: UnknownHomes_Game.h makes it extern inline,
// which would emit its _half/_three statics into this unit's .rodata.
#include "math.h"
#undef SQRT2_LINKAGE

#include <string.h>
#include "Dolphin/vec.h"
#include "main/file_800A7C08.h"
#include "menus/rep_0B08.h"
#include "menus/auto_00_00071EC4_text.h"
#include "menus/auto_00_00092394_text.h"

extern void fn_800B0A14_removeQueue(void* unused);

// fn_800B0A14_removeQueue ignores its argument. Some callers pass nothing: r3 is
// whatever the previous call left (e.g. right after fn_80034CEC). The matching
// build calls it through a (void) cast there; the port passes NULL.
#ifndef REMOVE_QUEUE_NOARG
#if NONMATCHING
#define REMOVE_QUEUE_NOARG() fn_800B0A14_removeQueue(NULL)
#else
#define REMOVE_QUEUE_NOARG() ((void (*)(void))fn_800B0A14_removeQueue)()
#endif
#endif
extern u32 fn_80062890(s32 index);

// Menu world state (lbl_2_bss_1A8248[0]), only the fields used here.
typedef struct MenuWorld0840 {
    /*0x0000*/ u8 _0000[0x16C0];
    /*0x16C0*/ s16 location;
    /*0x16C2*/ s16 prevLocation;
} MenuWorld0840;

// Menu work buffer (lbl_2_bss_1A824C[0]), only the fields used here.
typedef struct MenuWork0840 {
    /*0x000000*/ u8 _000000[0x19783F];
    /*0x19783F*/ u8 abort;
} MenuWork0840;

extern MenuWorld0840* lbl_2_bss_1A8248[];
extern MenuWork0840* lbl_2_bss_1A824C[];
extern MenuSceneTask0840* lbl_803CC1B8;
extern MenuSpot lbl_2_data_3198[];

// .text:0x0003BD88 size:0x2B4
// Scripted menu scene: walks the cursor character to the stadium entrance.
void fn_2_3BD88(void) {
    MenuSceneTask0840* task = lbl_803CC1B8;
    Vec pos;

    switch (task->state) {
    case 0:
        task->timer = 1;
        task->state = 1;
        break;
    case 1:
        if (task->timer-- == 0) {
            fn_2_72054(0, 0x13);
            task->timer = 50;
            task->state = 2;
        }
        break;
    case 2:
        if (task->timer == 12) {
            if (lbl_2_bss_1A8248[0]->prevLocation == 0x12) {
                fn_2_92654(0x19, 9);
            } else {
                fn_2_92654(0x1A, 9);
            }
        }
        if (task->timer-- == 0) {
            fn_80062890(0xB);
        }
        if (fn_2_6AF9C(0) == 1) {
            fn_2_6AF80(0, 0);
            task->state = 3;
        }
        break;
    case 3:
        task->state = 4;
        break;
    case 4:
        if (lbl_2_bss_1A8248[0]->location == 0x30) {
            memcpy(&pos, &lbl_2_data_3198[26].position, sizeof(Vec));
            PSVECScale(&pos, 0.5f, &pos);
            fn_2_6AABC(0, &pos);
            fn_2_92654(0x1A, 9);
        } else {
            memcpy(&pos, &lbl_2_data_3198[25].position, sizeof(Vec));
            PSVECScale(&pos, 0.5f, &pos);
            fn_2_6AABC(0, &pos);
            fn_2_92654(0x19, 9);
        }
        task->state = 5;
        break;
    case 5:
        fn_2_72054(0, 0x14);
        task->state = 6;
        break;
    case 6:
        if (fn_2_6AF9C(0) == 1) {
            fn_2_6AF80(0, 0);
            fn_2_72054(0, 4);
            if (lbl_2_bss_1A8248[0]->location == 0x30) {
                lbl_2_bss_1A8248[0]->prevLocation = 0x32;
                lbl_2_bss_1A8248[0]->location = 0x32;
            } else {
                lbl_2_bss_1A8248[0]->prevLocation = 0x12;
                lbl_2_bss_1A8248[0]->location = 0x12;
            }
            task->state = 7;
        }
        break;
    case 7:
        task->parent->result = 1;
        REMOVE_QUEUE_NOARG(); // arg unused
        task->state = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->abort == 1) {
        lbl_803CC1B8->parent->result = 1;
        REMOVE_QUEUE_NOARG(); // arg unused
        task->state = 0;
    }
}
