#include "challenge/rep_0138.h"


#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"

extern GXCullMode lbl_1_data_8C4[];
extern void* lbl_1_data_848[3];
extern void fn_1_73B8(void* context, s32 count, ...);

// fn_1_54E0, size:0x60
void fn_1_54E0(void* matrix) {
    s32 i;
    for (i = 0; i < 3; i++) {
        LITXForm(lbl_1_data_848[i], matrix);
    }
}

// fn_1_77EC, size:0x5C
void fn_1_77EC(void* context) {
    GXSetCullMode(lbl_1_data_8C4[0]);
    fn_1_73B8(context, 3, lbl_1_data_848[0], lbl_1_data_848[1], lbl_1_data_848[2]);
}

// .text:0x5540 size:0x4
void fn_1_5540(void) {
}

// fn_1_7848, size:0x24
void fn_1_7848(void) {
    fn_80048C28();
    fn_80048C1C();
}
