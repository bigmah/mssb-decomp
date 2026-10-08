#include "menus/rep_0B08.h"

extern void (*lbl_2_data_2A1F4[])(u8* object);

// .text:0x71A38 size:0x38
void fn_2_71A38(u8* object) {
    lbl_2_data_2A1F4[*(s16*)(object + 0x94)](object);
}
