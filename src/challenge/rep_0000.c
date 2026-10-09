#include "challenge/rep_0000.h"
#include "static/UnknownHomes_Static.h"

extern u8* lbl_803CC1B8[];
extern void fn_1_16A0(void);
extern void fn_1_1E0(void);
extern void ANIMGet(void* bank, char* name);

void fn_1_0(void* bank, char* name) {
    ANIMGet(bank, name);
}

void fn_1_1B0(u32* table, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) {
        if (table[i] != 0) {
            table[i] += (u32)table;
        }
    }
}

