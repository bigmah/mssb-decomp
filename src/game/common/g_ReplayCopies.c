// game.rel common .bss (0x13748, size 0x114BC): defined uninitialised and compiled with -common on,
// one global per unit as in the original link (the linker puts all commons after the other .bss).
#include "types.h"

u8 g_ReplayCopies[0x114BC]; // replay snapshot: the game state globals packed at fixed offsets (rep_1330)
// TODO port: the snapshot copies 32-bit-layout structs byte for byte at fixed offsets; needs the port layout
