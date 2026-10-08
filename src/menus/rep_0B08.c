#include "menus/rep_0B08.h"

extern void (*lbl_2_data_2A220[])(u8* object);
extern void (*lbl_2_data_2A210[])(u8* object);
extern void (*lbl_2_data_2A208[])(u8* object);
extern void (*lbl_2_data_2A200[])(u8* object);
extern void (*lbl_2_data_2A1F4[])(u8* object);

// .text:0x71A38 size:0x38
void fn_2_71A38(u8* object) {
    lbl_2_data_2A1F4[*(s16*)(object + 0x94)](object);
}

// .text:0x70588 size:0x38
void fn_2_70588(u8* object) {
    lbl_2_data_2A200[*(s16*)(object + 0x94)](object);
}

// .text:0x704A0 size:0xC
void fn_2_704A0(u8* object) {
    *(s16*)(object + 0x94) = 2;
}

// .text:0x70494 size:0xC
void fn_2_70494(u8* object) {
    *(s16*)(object + 0x94) = 2;
}

// .text:0x7045C size:0x38
void fn_2_7045C(u8* object) {
    lbl_2_data_2A208[*(s16*)(object + 0x94)](object);
}

// .text:0x6FE34 size:0x38
void fn_2_6FE34(u8* object) {
    lbl_2_data_2A210[*(s16*)(object + 0x94)](object);
}

// .text:0x6F6F4 size:0x38
void fn_2_6F6F4(u8* object) {
    lbl_2_data_2A220[*(s16*)(object + 0x94)](object);
}

// .text:0x6E880 size:0xC
void fn_2_6E880(u8* object) {
    *(s16*)(object + 0x94) = 4;
}
