#include "challenge/rep_7A28.h"


#include "static/UnknownHomes_Static.h"
extern void* lbl_80366158[];
extern u8* lbl_803CC1B8[];

// .text:0x27AD0 size:0x4
void fn_1_27AD0(void) {
}

// fn_1_27E50, size:0x48
void fn_1_27E50(void) {
    u8* parent;
    fn_800AD038(lbl_80366158[2]);
    parent = *(u8**)(lbl_803CC1B8[0] + 0xC);
    *(s16*)(parent + 0x10) = 1;
    fn_800B0A14_removeQueue(parent);
}
