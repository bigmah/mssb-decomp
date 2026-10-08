#include "menus/rep_0788.h"

extern s16 lbl_2_data_3D30[][4];
extern u8* lbl_803CC1B8[];

// .text:0x24724 size:0x4
void fn_2_24724(void) {
}

// .text:0x20258 size:0x4
void fn_2_20258(void) {
}

// .text:0x1FF10 size:0x4
void fn_2_1FF10(void) {
}

// .text:0x1FF0C size:0x4
void fn_2_1FF0C(void) {
}

void fn_2_24EB0(s16 value) {
    *(s16*)(lbl_803CC1B8[0] + 0x10) = value;
}

s16 fn_2_24E9C(void) {
    return *(s16*)(lbl_803CC1B8[0] + 0x10);
}

s16 fn_2_201E4(s16 row, s16 column) {
    if (column < 0) return -1;
    return lbl_2_data_3D30[row][column];
}
