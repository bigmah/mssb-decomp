#include "game/auto_00_000C1930_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

// 2-entry slot table (0x20 bytes per slot), first field is the owner id.
typedef struct C1930Slot {
    s16 id;
    u8 pad2[0x20 - 0x2];
} C1930Slot;

extern C1930Slot lbl_3_data_17260[2];

// .text:0x000C1930 size:0x34 mapped:0x807009C4
// Returns the slot index whose id equals `id`, or -1.
s32 fn_3_C1930(s32 id) {
    s32 k = 1;
    C1930Slot* q = &lbl_3_data_17260[1];
    do {
        if (id == q->id) {
            break;
        }
        q--;
    } while (k-- != 0);
    return k;
}
