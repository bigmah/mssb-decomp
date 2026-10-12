#include "game/auto_00_000C1930_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

#include "game/rep_1F58.h"

// Returns the slot index whose id equals `id`, or -1.
// .text:0x000C1930 size:0x34 mapped:0x807009C4
s32 fn_3_C1930(s32 id) {
    s32 k = 1;
    E32_1F58* q = &lbl_3_data_17260[1];
    do {
        if (id == q->id) {
            break;
        }
        q--;
    } while (k-- != 0);
    return k;
}

