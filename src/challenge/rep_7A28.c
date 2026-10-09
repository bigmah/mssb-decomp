#include "challenge/rep_7A28.h"


#include "static/UnknownHomes_Static.h"
#include <string.h>
extern u8 lbl_1_data_10908[];
extern s32 lbl_1_data_109F8;
extern void (*lbl_1_data_108E8[])(void*);
extern void fn_1_26D28(s32, u16, u16, u16, void*);
extern void fn_1_276CC(void*);
extern void fn_1_27E98(void*);
extern u8 lbl_803C6CF8[];
extern void* _OSAllocFromHeap(s32, s32);
extern void fn_1_273D8(void*);
extern const f32 lbl_1_rodata_7B5C;
extern const f32 lbl_1_rodata_7B64;
extern const f32 lbl_1_rodata_7B98;

static void* sTable[4] = { (void*)fn_1_27AD4, (void*)fn_1_276CC, 0, 0 };
static u8 sXfer[0x10] = {1};
static u8 sArr[0xF0] = {1};
static s32 sLast = 1;


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

// fn_1_27D6C, size:0xE4
void fn_1_27D6C(void) {
    u8 buf[6];
    if (*(u16*)(lbl_803CC1B8[0] + 0x34) & 1) {
        lbl_1_data_108E8[*(s8*)(lbl_803CC1B8[0] + 0x36)](lbl_1_data_108E8);
    } else {
        memcpy(buf, (u8*)&lbl_803C77B8 + 0x10, 6);
        buf[0] = -buf[0];
        buf[4] = ((u8*)&lbl_803C77B8)[0x15];
        buf[5] = ((u8*)&lbl_803C77B8)[0x14];
        fn_1_26D28(*(s32*)(lbl_803CC1B8[0] + 0x14), lbl_803C77B8._00, lbl_803C77B8._02, *(u16*)((u8*)&lbl_803C77B8 + 4), buf);
    }
    if (lbl_803C77B8._02 & 0x1000) {
        *(u16*)(lbl_803CC1B8[0] + 0x34) ^= 1;
    }
}

// fn_1_28118, size:0xE8
void fn_1_28118(void) {
    u8* object = lbl_803CC1B8[0];
    s16 state = *(s16*)(object + 0x10);
    s32 ready;
    switch (state) {
    case 0:
        *(s16*)(object + 0x10) = state + 1;
        *(s32*)(object + 0x18) = ARAMTransfer(sXfer, 0, 0, 0);
    case 1:
        ready = lbl_803C6CF8[0x715];
        if (ready == 1) {
            s32 tex;
            *(s32*)(object + 0x18) = *(s32*)(object + 0x18) + **(s32**)(object + 0x18);
            convertTextureHeader(*(void**)(object + 0x18));
            tex = *(s32*)(object + 0x18);
            *(s32*)(sArr + 0xA0) = tex;
            *(s32*)(sArr + 0x50) = tex;
            *(s32*)(sArr + 0x00) = tex;
            *(s32*)(sArr + 0x04) = 7;
            *(s32*)(sArr + 0x54) = 7;
            *(s32*)(sArr + 0xA4) = 4;
            sLast = tex;
            *(void**)lbl_803CC1B8[0] = fn_1_27E98;
        }
    }
}

// fn_1_28200, size:0xF4
void fn_1_28200(void) {
    u8* object = lbl_803CC1B8[0];
    u8* camera;
    *(s16*)(object + 0x10) = 0;
    fn_800AD038(lbl_80366158[2]);
    *(void**)(object + 0x14) = _OSAllocFromHeap(0x20, 0xDC);
    fn_1_273D8(*(void**)(object + 0x14));
    *(void**)(object + 0x1C) = _OSAllocFromHeap(0x20, 0x1C);
    *(s32*)(*(u8**)(object + 0x1C) + 8) = 0x10;
    *(s32*)(*(u8**)(object + 0x1C) + 0x14) = 1;
    camera = *(u8**)(object + 0x14);
    *(f32*)(camera + 0x8C) = *(f32*)(camera + 0x8C) * lbl_1_rodata_7B98;
    *(f32*)(object + 0x20) = lbl_1_rodata_7B5C;
    *(f32*)(object + 0x24) = lbl_1_rodata_7B98;
    *(f32*)(object + 0x28) = lbl_1_rodata_7B5C;
    *(f32*)(object + 0x2C) = lbl_1_rodata_7B64;
    *(f32*)(object + 0x30) = lbl_1_rodata_7B64;
    object[0x36] = 0;
    object[0x37] = 0;
    *(u16*)(object + 0x34) = 0;
    *(void**)lbl_803CC1B8[0] = fn_1_28118;
}
