#include "game/auto_00_000CABB4_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

typedef struct CABB4Obj {
    u8 pad0[0x34];
    u8 flag34; // 0x34
} CABB4Obj;

extern CABB4Obj* lbl_3_data_17D10[2];

// .text:0x000CABB4 size:0x3C mapped:0x80709C48
void fn_3_CABB4(void) {
    if (lbl_3_data_17D10[0] != NULL) {
        lbl_3_data_17D10[0]->flag34 = 1;
    }
    if (lbl_3_data_17D10[1] != NULL) {
        lbl_3_data_17D10[1]->flag34 = 1;
    }
}
