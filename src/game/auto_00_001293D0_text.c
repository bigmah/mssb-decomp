#include "game/auto_00_001293D0_text.h"
#include "static/UnknownHomes_Static.h"

extern u8 g_Minigame[];
extern void* memset(void*, s32, u32);

// fn_3_12DB54, size:0x2C
void fn_3_12DB54(void) {
    s8 i;
    i = 0;
    do {
        g_Minigame[i + 0x1DBC] = 0;
        i++;
    } while (i < 4);
}

// fn_3_12E808, size:0x34
void fn_3_12E808(void) {
    memset(g_Minigame + 0x1D7C, 0, 0x78);
}

// fn_3_12DD88, size:0x44
u32 fn_3_12DD88(void) {
    u32 i = 0;
    do {
        if (g_Minigame[i * 0x34 + 0x890] != 2) {
            break;
        }
        i++;
    } while (i < 0xF);
    return i >= 0xF;
}
