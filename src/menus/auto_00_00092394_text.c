#include "menus/auto_00_00092394_text.h"
#include "static/UnknownHomes_Static.h"


extern u8 lbl_800F7478[];
extern void fn_2_8AC84(s32 index, s32 value);

typedef struct MenuState MenuState;
typedef struct MenuObject {
    u8 pad0[0x90];
    s16 phase;
    u8 pad92[0x19];
    u8 state;
    u8 padAC[0x10];
} MenuObject;
extern MenuState* lbl_2_bss_1A8248[];

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

// fn_2_92654, size:0x28
void fn_2_92654(s32 index, u8 state) {
    MenuObject* object = (MenuObject*)((u8*)lbl_2_bss_1A8248[0] + index * 0xBC + 0x21E0);
    object->state = state;
    object->phase = 0;
}

// fn_2_924B0, size:0x54
void fn_2_924B0(u8* object) {
    GXColor color = *(GXColor*)(lbl_800F7478 + 0x28);
    fn_2_8AC84(*(s32*)(object + 0x78), 0);
    color.a = 0xFF;
    fn_800BD2CC(0, color);
}
