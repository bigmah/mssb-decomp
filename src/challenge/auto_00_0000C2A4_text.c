#include "challenge/auto_00_0000C2A4_text.h"
#include "challenge/rep_0010.h"
#include "static/UnknownHomes_Static.h"

// .text:0x0000C2A4 size:0x38
void fn_1_C2A4(void) {
    ChTaskHeader* parent = ((ChTaskHeader*)lbl_803CC1B8)->parent;

    parent->result = 1;
    fn_800B0A14_removeQueue(parent);
}

