#include "game/auto_00_0007976C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_803535C8[];

#pragma dont_inline on

// fn_3_7AEE8, size:0x4
void fn_3_7AEE8(void) {
    return;
}

// fn_3_7BBC0, size:0x38
u8* fn_3_7BBC0(void) {
    return lbl_803535C8 + *(s32*)((u8*)&g_GameLogic + 0x8) * 0x10E + ((s32*)((u8*)&g_GameLogic + *(s32*)((u8*)&g_GameLogic + 0x10) * 0x50))[0xF] * 0x1E;
}

// fn_3_7BBF8, size:0x14
void fn_3_7BBF8(void) {
    ((u8*)&g_Stats)[0x39] = 1;
}

// fn_3_7BC0C, size:0x14
void fn_3_7BC0C(void) {
    ((u8*)&g_Stats)[0x39] = 1;
}

// fn_3_7C190, size:0x4
void fn_3_7C190(void) {
    return;
}
