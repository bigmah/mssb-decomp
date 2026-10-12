// main.dol common .bss 0x803C5144-0x803C5EA4: uninitialised globals, compiled with -common on;
// the linker places all commons after the other .bss, one block per object in link order.
#include "types.h"

u8 lbl_803C5144[0xD60]; // starts with the picked-up player per team (CharacterStats[2])
