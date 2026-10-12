// game.rel common .bss (0xDE94, size 0x2AF4): defined uninitialised and compiled with -common on,
// one global per unit as in the original link (the linker puts all commons after the other .bss).
// Only its first word is known (lbl_3_common_bss_DE94_s: a pointer to the scene state).
#include "types.h"

u32 lbl_3_common_bss_DE94[0x2AF4 / 4]; // TODO type
