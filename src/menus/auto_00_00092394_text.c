#include "menus/auto_00_00092394_text.h"


extern void (*lbl_2_data_308B4[])(u8* object);

extern void (*lbl_2_data_307F0[])(u8* object);

extern void (*lbl_2_data_307F8[])(u8* object);

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

// fn_2_9246C, size:0x38
void fn_2_9246C(u8* object) {
    lbl_2_data_307F8[*(s16*)(object + 0x90)](object);
}

// fn_2_92504, size:0x38
void fn_2_92504(u8* object) {
    lbl_2_data_307F0[*(s16*)(object + 0x90)](object);
}

// fn_2_9253C, size:0x40
void fn_2_9253C(u8* object) {
    *(void (**)(u8*))(object + 0xB8) = lbl_2_data_308B4[object[0xAB]];
    (*(void (**)(u8*))(object + 0xB8))(object);
}
