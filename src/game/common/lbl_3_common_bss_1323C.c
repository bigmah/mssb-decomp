// game.rel common .bss (0x1323C, size 0x288): defined uninitialised and compiled with -common on,
// one global per unit as in the original link (the linker puts all commons after the other .bss).
#include "types.h"

// The first word is the SceneWork* other units declare (extern SceneWork* lbl_3_common_bss_1323C); the
// other 0x284 bytes are SceneWork-sized but have no symbol of their own (a split needs symbols.txt).
u32 lbl_3_common_bss_1323C[0xA2]; // TODO type: SceneWork* followed by an unnamed 0x284-byte SceneWork
