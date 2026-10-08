#include "menus/rep_1028.h"

extern MenuStateCallback lbl_2_data_30810[3];
extern MenuStateCallback lbl_2_data_3081C[3];
extern MenuStateCallback lbl_2_data_30828[3];
extern MenuStateCallback lbl_2_data_30834[3];
extern MenuStateCallback lbl_2_data_30840[3];
extern MenuStateCallback lbl_2_data_3084C[3];

// .text:0x00091B7C size:0x4
void fn_2_91B7C(void) {}

// .text:0x00091B28 size:0x4
void fn_2_91B28(void) {}

// .text:0x00091C40 size:0xC
void fn_2_91C40(u8* object) {
    *(s16*)(object + 0x90) = 2;
}

// .text:0x00091B70 size:0xC
void fn_2_91B70(u8* object) {
    *(s16*)(object + 0x90) = 2;
}

// .text:0x00091B2C size:0xC
void fn_2_91B2C(u8* object) {
    *(s16*)(object + 0x90) = 1;
}

// .text:0x00091B1C size:0xC
void fn_2_91B1C(u8* object) {
    *(s16*)(object + 0x90) = 2;
}

// .text:0x000919C0 size:0xC
void fn_2_919C0(u8* object) {
    *(s16*)(object + 0x90) = 2;
}

// .text:0x000919B4 size:0xC
void fn_2_919B4(u8* object) {
    *(s16*)(object + 0x90) = 2;
}

// .text:0x000918E8 size:0xC
void fn_2_918E8(u8* object) {
    *(s16*)(object + 0x90) = 2;
}

// .text:0x00091C08 size:0x38
void fn_2_91C08(MenuStateObject* object) {
    lbl_2_data_30810[object->state](object);
}

// .text:0x00091B38 size:0x38
void fn_2_91B38(MenuStateObject* object) {
    lbl_2_data_3081C[object->state](object);
}

// .text:0x00091AE4 size:0x38
void fn_2_91AE4(MenuStateObject* object) {
    lbl_2_data_30828[object->state](object);
}

// .text:0x0009197C size:0x38
void fn_2_9197C(MenuStateObject* object) {
    lbl_2_data_30834[object->state](object);
}

// .text:0x000918A4 size:0x38
void fn_2_918A4(MenuStateObject* object) {
    lbl_2_data_30840[object->state](object);
}

// .text:0x000916C0 size:0x38
void fn_2_916C0(MenuStateObject* object) {
    lbl_2_data_3084C[object->state](object);
}
