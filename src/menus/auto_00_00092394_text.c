#include "menus/auto_00_00092394_text.h"


extern void (*lbl_2_data_30804[])(u8* object);

// fn_2_923CC, size:0xC
void fn_2_923CC(u8* object) {
    *(s16*)(object + 0x90) = 2;
}

// fn_2_923D8, size:0xC
void fn_2_923D8(u8* object) {
    *(s16*)(object + 0x90) = 2;
}

// fn_2_924A4, size:0xC
void fn_2_924A4(u8* object) {
    *(s16*)(object + 0x90) = 1;
}

// fn_2_92394, size:0x38
void fn_2_92394(u8* object) {
    lbl_2_data_30804[*(s16*)(object + 0x90)](object);
}
