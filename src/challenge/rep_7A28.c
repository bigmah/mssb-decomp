#include "challenge/rep_7A28.h"


#include "static/UnknownHomes_Static.h"
extern u8 lbl_1_data_10908[];
extern s32 lbl_1_data_109F8;

extern void* lbl_80366158[];
extern u8* lbl_803CC1B8[];

// .text:0x27AD0 size:0x4
void fn_1_27AD0(void) {
}

// fn_1_27E50, size:0x48
void fn_1_27E50(void) {
    u8* parent;
    fn_800AD038(lbl_80366158[2]);
    parent = *(u8**)(lbl_803CC1B8[0] + 0xC);
    *(s16*)(parent + 0x10) = 1;
    fn_800B0A14_removeQueue(parent);
}

// fn_1_27560, size:0x34
void fn_1_27560(s32 value) {
    *(s32*)(lbl_1_data_10908 + 0xA0) = value;
    *(s32*)(lbl_1_data_10908 + 0x50) = value;
    *(s32*)(lbl_1_data_10908 + 0x00) = value;
    *(s32*)(lbl_1_data_10908 + 0x04) = 7;
    *(s32*)(lbl_1_data_10908 + 0x54) = 7;
    *(s32*)(lbl_1_data_10908 + 0xA4) = 4;
    lbl_1_data_109F8 = value;
}

// fn_1_27AD4, size:0xE4
void fn_1_27AD4(void) {
    u16 repeated = *(u16*)((u8*)&lbl_803C77B8 + 4);
    u8* object = lbl_803CC1B8[0];
    if (repeated & 8) {
        *(s8*)(object + 0x37) = (*(s8*)(object + 0x37) + 1) % 2;
        return;
    }
    if (repeated & 4) {
        *(s8*)(object + 0x37) = (*(s8*)(object + 0x37) + 1) % 2;
        return;
    }
    if (lbl_803C77B8._02 & 0x100) {
        object[0x36] = object[0x37] + 1;
        object[0x37] = 0;
        return;
    }
    if (lbl_803C77B8._02 & 0x200) {
        fn_1_27E50();
    }
}
