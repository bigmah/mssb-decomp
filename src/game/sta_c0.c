#include "game/sta_c0.h"
#include "header_rep_data.h"

extern u8 g_GameLogic[];
extern void AnimateActorBones(void*);
typedef struct { u8 pad[0x90]; u8 f : 1; } BF90;
#include "Dolphin/GX/GXBump.h"
#include "Dolphin/GX/GXTexture.h"
extern GXTexObj lbl_3_bss_9F4C;
extern void fn_3_B9510(s32);

// .text:0x000C9878 size:0x180 mapped:0x8070890C
void fn_3_C9878(void) {
    return;
}

// .text:0x000C99F8 size:0x68 mapped:0x80708A8C
void fn_3_C99F8(void* a_) {
    BF90* a = a_;
    if (g_GameLogic[0x11E] == 1 || g_GameLogic[0x11E] == 0) {
        a->f = 0;
    } else {
        a->f = 1;
        AnimateActorBones(**(void***)((u8*)a + 0x74));
    }
}

// .text:0x000C9A60 size:0x68 mapped:0x80708AF4
void fn_3_C9A60(void* a_) {
    BF90* a = a_;
    if (g_GameLogic[0x11E] == 1 || g_GameLogic[0x11E] == 0) {
        a->f = 0;
    } else {
        a->f = 1;
        AnimateActorBones(**(void***)((u8*)a + 0x74));
    }
}

// .text:0x000C9AC8 size:0x94 mapped:0x80708B5C
void fn_3_C9AC8(void) {
    fn_3_B9510(0);
    fn_3_B9510(1);
    GXLoadTexObj(&lbl_3_bss_9F4C, 7);
    GXSetIndTexOrder(0, 0, 7);
    GXSetNumIndStages(1);
    GXSetIndTexCoordScale(0, 0, 0);
    GXSetTevIndWarp(0, 0, 0, 0, 1);
    GXSetTevIndWarp(1, 0, 0, 0, 1);
}

// .text:0x000C9B5C size:0x138 mapped:0x80708BF0
void fn_3_C9B5C(void) {
    return;
}

// .text:0x000C9C94 size:0x120 mapped:0x80708D28
void fn_3_C9C94(void) {
    return;
}

// .text:0x000C9DB4 size:0xE00 mapped:0x80708E48
void fn_3_C9DB4(void) {
    return;
}

