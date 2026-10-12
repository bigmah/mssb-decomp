// game.rel common .bss (0x31ACC, size 0x3E0): defined uninitialised and compiled with -common on,
// one global per unit as in the original link (the linker puts all commons after the other .bss).
#include "types.h"

// Starts with a ThrowState (UnknownHomes_Game.h, 0x14 bytes; rep_E08 declares ThrowState[]); nothing
// reads the other 0x3CC bytes, and no ThrowState array is 0x3E0 bytes long.
u32 g_UnkThrowing_31ACC[0xF8]; // TODO type: ThrowState + 0x3CC unknown bytes
