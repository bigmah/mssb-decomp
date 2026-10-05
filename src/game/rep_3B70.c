#include "game/rep_3B70.h"
#include "header_rep_data.h"

// TODO: struct layout figured out (data_271A8: u8 counter[4]; Entry[2][2] stride 0x110/0x88; Entry: Mtx@8, Vec quad[4]@0x54, counter ptr@0x84)
// but mwcc pools the float consts via a rodata base reg here, orig loads each with its own lis. Not matched.
// .text:0x0015C3F8 size:0x1FC mapped:0x8079B48C
void fn_3_15C3F8(void) {
    return;
}

