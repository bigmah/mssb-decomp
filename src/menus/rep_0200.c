#include "menus/rep_0200.h"
#define REP_HEADER_FN repHeader_menus_0200
#include "header_rep_inline.h"
// math.h first with dolsqrtf2 static: UnknownHomes_Game.h makes it extern inline,
// which would emit its _half/_three statics into this unit's .rodata.
#include "math.h"
#undef SQRT2_LINKAGE

#include "Dolphin/os.h"


// fn_2_121C, size:0x38
void fn_2_121C(void) {
    OSPanic("yd_step.c", 0x4C, "Removed step was called.\n");
}
