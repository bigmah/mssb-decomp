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

