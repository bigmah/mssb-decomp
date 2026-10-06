#include "game/rep_3F60.h"
#include "header_rep_data.h"

// .text:0x00168414 size:0x2F0 mapped:0x807A74A8
void fn_3_168414(void) {
    return;
}

// .text:0x00168704 size:0x228 mapped:0x807A7798
void fn_3_168704(void) {
    return;
}

// .text:0x0016892C size:0x140 mapped:0x807A79C0
void fn_3_16892C(void) {
    return;
}

// .text:0x00168A6C size:0x26C mapped:0x807A7B00
void fn_3_168A6C(void) {
    return;
}

extern u8 lbl_8036E548[];
extern u8* lbl_803CC1B8;
extern s32 lbl_3_data_28680[];
extern u16 lbl_3_data_28920;
extern void* fn_800B0A5C_insertQueue(void*, s32);
extern void getAnimRelatedCoordinates(s32, s32, void*);

// .text:0x00168CD8 size:0x124 mapped:0x807A7D6C
void fn_3_168CD8(u8* p, f32 f) {
    s32 a = *(s8*)(p + 0x254);
    u8* q;
    if (f == (f32)lbl_3_data_28680[0x38 / 4] / 100000.0f && p != NULL) {
        q = fn_800B0A5C_insertQueue(fn_3_168DFC, (u16)(*(u16*)(lbl_803CC1B8 + 0x12) + 1));
        q[0x29] = a;
        *(s16*)(q + 0x24) = 0;
        *(f32*)(q + 0x20) = (f32)lbl_3_data_28680[0x3C / 4] / 100000.0f;
        getAnimRelatedCoordinates(a, lbl_3_data_28920, q + 0x14);
        q[0x2A] = 2;
        q[0x28] = 4;
        q[0x2B] = 7;
    }
}

// .text:0x00168DFC size:0x1A4 mapped:0x807A7E90
void fn_3_168DFC(void) {
    return;
}

extern u16 lbl_3_data_2891E;

// .text:0x00168FA0 size:0x120 mapped:0x807A8034
void fn_3_168FA0(s32 a, s32 b) {
    u8* q;
    if (((u32*)(lbl_8036E548 + 0x2C50))[a] != 0) {
        q = fn_800B0A5C_insertQueue(fn_3_168DFC, (u16)(*(u16*)(lbl_803CC1B8 + 0x12) + 1));
        q[0x29] = a;
        *(s16*)(q + 0x24) = 0;
        *(f32*)(q + 0x20) = (f32)lbl_3_data_28680[0x34 / 4] / 100000.0f;
        getAnimRelatedCoordinates(a, lbl_3_data_2891E, q + 0x14);
        if (b != 0) {
            q[0x2A] = 1;
            q[0x28] = 3;
            q[0x2B] = 6;
        } else {
            q[0x2A] = 0;
            q[0x28] = 2;
            q[0x2B] = 5;
        }
    }
}

