#include "game/rep_8C8.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1838.h"
#pragma dont_inline on
extern s32 fn_3_B0CF4(void);
extern u8 lbl_3_data_1AAC[];
extern u8 lbl_3_data_1AB0[];

// .text:0x0001E4B8 size:0x26C mapped:0x8065D54C
void fn_3_1E4B8(void) {
    return;
}

// .text:0x0001E724 size:0xD0 mapped:0x8065D7B8
s32 fn_3_1E724(void) {
    if (*((u8*)&g_GameLogic + 0x121) == 0xD) {
        return fn_3_B0CF4() != 0;
    }
    if (*((u8*)&g_AiLogic + 0x58) != 1) {
        return 0;
    }
    if (*((u8*)&g_AiLogic + 0x65) != 0) {
        return 0;
    }
    if (*(s16*)((u8*)&g_Ball + 0x1B68) <= 0) {
        return 1;
    }
    if (*(s16*)((u8*)&g_Pitcher + 0x132) == *((u8*)&g_AiLogic + 0x5D)) {
        if (fn_3_1E7F4() == 0) {
            *((u8*)&g_AiLogic + 0x65) = 1;
            return 0;
        }
    }
    return 1;
}

// .text:0x0001E7F4 size:0x2B4 mapped:0x8065D888
s32 fn_3_1E7F4(void) {
    return 0;
}

// .text:0x0001EAA8 size:0x53C mapped:0x8065DB3C
void fn_3_1EAA8(void) {
    return;
}

// .text:0x0001EFE4 size:0x1E8 mapped:0x8065E078
void fn_3_1EFE4(void) {
    return;
}

// .text:0x0001F1CC size:0x184 mapped:0x8065E260
void fn_3_1F1CC(void) {
    return;
}

// .text:0x0001F350 size:0x128 mapped:0x8065E3E4
void fn_3_1F350(void) {
    return;
}

// .text:0x0001F478 size:0x520 mapped:0x8065E50C
void fn_3_1F478(void) {
    return;
}

// .text:0x0001F998 size:0x3F4 mapped:0x8065EA2C
void fn_3_1F998(void) {
    return;
}

// .text:0x0001FD8C size:0x1BC mapped:0x8065EE20
void batterAIControlled(void) {
    return;
}

// .text:0x0001FF48 size:0x11C mapped:0x8065EFDC
void fn_3_1FF48(void) {
    return;
}

// .text:0x00020064 size:0x124 mapped:0x8065F0F8
void fn_3_20064(void) {
    return;
}

// .text:0x00020188 size:0x9C mapped:0x8065F21C
void fn_3_20188(void) {
    if (*(u8*)((u8*)&g_AiLogic + 0x6D) != 0xFF && RandomInt_Game(0x64) < (s32)lbl_3_data_1AAC[*(u8*)((u8*)&g_AiLogic + 0x55)]) {
        *(u8*)((u8*)&g_AiLogic + 0x5E) = *(u8*)((u8*)&g_AiLogic + 0x6D);
        return;
    }
    *(u8*)((u8*)&g_AiLogic + 0x5E) = RandomIndexFromWeights(lbl_3_data_1AB0 + *(u8*)((u8*)&g_Pitcher + 0x149) * 3, 3);
}

// .text:0x00020224 size:0x83C mapped:0x8065F2B8
void fn_3_20224(void) {
    return;
}
