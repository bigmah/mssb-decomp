#include "menus/auto_00_0004B1AC_text.h"

#include "static/UnknownHomes_Static.h"

extern u8 lbl_2_data_1323C[];

extern u8 lbl_2_data_1324C[];

extern u8 lbl_2_data_1325C[];

extern u8 lbl_2_data_1326C[];

extern u8 lbl_2_data_132DC[];

extern s16 lbl_2_data_3EC8[];

extern s16 lbl_2_data_3ED4[];


// fn_2_4C3C4, size:0x14
s16 fn_2_4C3C4(s32 index) {
    return lbl_2_data_3ED4[index];
}

// fn_2_4C3D8, size:0x14
s16 fn_2_4C3D8(s32 index) {
    return lbl_2_data_3EC8[index];
}

// fn_2_4E898, size:0x24
void fn_2_4E898(void) {
    fn_80035B50(0x17);
}

// fn_2_4E8BC, size:0x24
void fn_2_4E8BC(void) {
    fn_80035B50(0x18);
}

// fn_2_4E8E0, size:0x24
void fn_2_4E8E0(void) {
    fn_80035B50(0x17);
}

// fn_2_4E904, size:0x24
void fn_2_4E904(void) {
    fn_80035B50(0xC);
}

// fn_2_4E928, size:0x24
void fn_2_4E928(void) {
    fn_80035B50(0x15);
}

// fn_2_4E94C, size:0x24
void fn_2_4E94C(void) {
    fn_80035B50(0x8);
}

// fn_2_4E970, size:0x38
s32 fn_2_4E970(void) {
    return fn_80035838(lbl_2_data_132DC, 0x17) != 0;
}

// fn_2_4EABC, size:0x38
s32 fn_2_4EABC(void) {
    return fn_80035838(lbl_2_data_1326C, 0x17) != 0;
}

// fn_2_4EAF4, size:0x38
s32 fn_2_4EAF4(void) {
    return fn_80035838(lbl_2_data_1325C, 0xC) != 0;
}

// fn_2_4EB2C, size:0x38
s32 fn_2_4EB2C(void) {
    return fn_80035838(lbl_2_data_1324C, 0x15) != 0;
}

// fn_2_4EB64, size:0x38
s32 fn_2_4EB64(void) {
    return fn_80035838(lbl_2_data_1323C, 0x8) != 0;
}

// fn_2_4E858, size:0x20
void* fn_2_4E858(void* object) {
    return fn_80034CEC(object);
}

// fn_2_512B8, size:0x8
s32 fn_2_512B8(void) {
    return 0;
}
