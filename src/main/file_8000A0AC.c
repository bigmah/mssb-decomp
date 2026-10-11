#include "main/file_8000A0AC.h"

extern const f32 lbl_803CC428; // 1.0f
extern const f32 lbl_803CC42C; // 0.0f
extern const f32 lbl_803CC430; // 1.0f / 1024
extern const f32 lbl_803CC434; // 4096.0f
extern const f32 lbl_803CC438; // 2 * pi
extern const f32 lbl_803CC448; // 360.0f
extern const f32 lbl_803CC44C; // 0.5f
extern const f32 lbl_803CC450; // pi / 2
extern const f32 lbl_803CC454; // pi / 180

void fn_8000E764(f32* sinCos, f32 angle);

// .text:0x8000A0AC size:0x13C
void fn_8000A0AC(void) {
    return;
}

// .text:0x8000A1E8 size:0x204
void interpolatePointsBezier_Vec2s(void) {
    return;
}

// .text:0x8000A3EC size:0xB30
void fn_8000A3EC(void) {
    return;
}

// .text:0x8000AF1C size:0xAAC
void fn_8000AF1C(void) {
    return;
}

// .text:0x8000B9C8 size:0x74
void fn_8000B9C8(void* file) {
    // TODO port: converts 32-bit file offsets into pointers in place
    u32* header = (u32*)file;
    u32* entry;
    u32* item;
    u32 count;
    u32 n;
    u32* group;
    u32* table;

    header[2] += (u32)header;
    if (((u16*)header)[3] == 0) {
        header[3] += (u32)header;
    }
    table = (u32*)header[2];
    count = table[0];
    entry = table;
    do {
        entry[2] += (u32)table;
        group = (u32*)entry[2];
        n = group[0] & 0x7FFFFFFF;
        item = group;
        do {
            item[2] += (u32)group;
            item++;
        } while (--n != 0);
        entry++;
    } while (--count != 0);
}
