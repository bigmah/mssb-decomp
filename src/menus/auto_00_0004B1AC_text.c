#include "menus/auto_00_0004B1AC_text.h"

#include "static/UnknownHomes_Static.h"

extern u32 lbl_803C7898[];

extern u8* lbl_2_bss_1A824C[];

extern void fn_2_89F70(void);

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

// fn_2_519F0, size:0x2C
void* fn_2_519F0(void) {
    return fn_800B0A5C_insertQueue((void*)fn_2_89F70, 0x3000);
}

// fn_2_54874, size:0x1C
void fn_2_54874(void) {
    *(s16*)(lbl_2_bss_1A824C[0] + 0x197754) = 0;
}

// fn_2_54848, size:0x2C
void fn_2_54848(void) {
    *(s16*)(lbl_2_bss_1A824C[0] + 0x197754) = 1;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x197752) = 10;
}

// fn_2_4E7EC, size:0x38
void fn_2_4E7EC(void) {
    u8* data = lbl_2_bss_1A824C[0];
    fn_800AD054(*(void**)(data + 0x195424), *(void**)(data + 0x195428));
}

// fn_2_4E824, size:0x34
void fn_2_4E824(void) {
    *(u32*)(lbl_2_bss_1A824C[0] + 0x195424) = lbl_803C7898[1];
    *(u32*)(lbl_2_bss_1A824C[0] + 0x195428) = lbl_803C7898[2];
}

// fn_2_54BAC, size:0x4
void fn_2_54BAC(void) {
    return;
}

// fn_2_54844, size:0x4
void fn_2_54844(void) {
    return;
}

// fn_2_5268C, size:0x4
void fn_2_5268C(void) {
    return;
}
