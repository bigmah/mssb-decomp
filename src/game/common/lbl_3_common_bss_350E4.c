// game.rel common .bss (0x350E4, size 0x70): defined uninitialised and compiled with -common on,
// one global per unit as in the original link (the linker puts all commons after the other .bss).
#include "types.h"

#ifdef TARGET_PC
#include "game/rep_1D58.h"
StadiumObjMgr lbl_3_common_bss_350E4; // holds pointers: bigger than 0x70 on PC
#else
u32 lbl_3_common_bss_350E4[0x1C]; // TODO type: StadiumObjMgr (0x70), still defined inside rep_1D58.c; needs moving to a header
#endif
