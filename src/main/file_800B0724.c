#include "main/file_800B0724.h"

// .text:0x800B0724 size:0xD8
void makeLookAtMatrix(void) {
    return;
}

// .text:0x800B07FC size:0x38
void soundQuit(void) {
    return;
}

// .text:0x800B0834 size:0x100
void initSound(void) {
    return;
}

// fn_800B0934, size:0x4
void fn_800B0934(void) {
}

// .text:0x800B0938 size:0x64
void SndFree(void) {
    return;
}

// .text:0x800B099C size:0x78
void SndAlloc(void) {
    return;
}

extern u16 lbl_803CC1B0;
extern u16 lbl_803CC1B2;
extern u16 lbl_803CC1B4;
extern u8 lbl_80111300[];
extern u8* lbl_803CC1B8;

extern u8 lbl_803C7A24[];

// fn_800B0A14_removeQueue, size:0x48
void fn_800B0A14_removeQueue(void* unused) {
    if (lbl_803CC1B2 != 0) {
        u8* previous = *(u8**)(lbl_803CC1B8 + 4);
        *(u8**)(previous + 8) = *(u8**)(lbl_803CC1B8 + 8);
        previous = *(u8**)(lbl_803CC1B8 + 8);
        *(u8**)(previous + 4) = *(u8**)(lbl_803CC1B8 + 4);
        *(u32*)lbl_803CC1B8 = 0;
        lbl_803CC1B2--;
    }
}

// nop_function, size:0x4
void nop_function(void) {
}

// fn_800B0C80, size:0x34
void fn_800B0C80(void (*draw)(void)) {
    u8* node;
    s32 remaining;
    if (draw == NULL) {
        draw = nop_function;
    }
    remaining = 3;
    node = lbl_803C7A24;
    do {
        remaining--;
        *(void (**)(void))node = draw;
        node += 0x80;
    } while (remaining != 0);
}

// resetAllDrawingStructs, size:0x98
void resetAllDrawingStructs(void) {
    s32 remaining;
    u8* node;
    u32* slot;
    s32 count;
    node = lbl_803C7A24;
    remaining = 3;
    do {
        *(s32*)(node + 4) = 0;
        *(u8**)(node + 8) = node + 0x40;
        *(u8**)(node + 0xC) = lbl_80111300;
        *(u16*)(node + 0x10) = 0;
        *(u16*)(node + 0x12) = 0;
        *(u8**)(node + 0x44) = node;
        *(s32*)(node + 0x48) = 0;
        *(u8**)(node + 0x4C) = lbl_80111300;
        *(u16*)(node + 0x50) = 0;
        *(u16*)(node + 0x52) = 0xFFFF;
        node += 0x80;
    } while (--remaining != 0);
    slot = (u32*)(lbl_803C7A24 + 0x180);
    count = 0x3A;
    do {
        *slot = 0;
        slot += 0x10;
    } while (--count != 0);
    lbl_803CC1B2 = 0;
    lbl_803CC1B0 = 0;
    lbl_803CC1B4 = 5;
}

// fn_800B0A5C_insertQueue, size:0xD0
void* fn_800B0A5C_insertQueue(void* draw, u16 priority) {
    u8* node;
    u8* prev;
    u8* entry;
    u16 idx;
    s32 i;
    do {
        lbl_803CC1B4++;
        idx = lbl_803CC1B4 & 0x3F;
        lbl_803CC1B4 = idx;
    } while (*(u32*)(lbl_803C7A24 + idx * 0x40) != 0);
    node = lbl_803C7A24 + (lbl_803CC1B0 << 7);
    do {
        node = *(u8**)(node + 8);
    } while (*(u16*)(node + 0x12) < priority);
    prev = *(u8**)(node + 4);
    entry = lbl_803C7A24 + (idx << 6);
    *(u8**)(node + 4) = entry;
    *(u8**)(prev + 8) = entry;
    *(void**)entry = draw;
    *(u8**)(entry + 4) = prev;
    *(u8**)(entry + 8) = node;
    *(u8**)(entry + 0xC) = lbl_803CC1B8;
    *(u16*)(entry + 0x10) = 0;
    *(u16*)(entry + 0x12) = priority;
    *(s32*)(entry + 0x14) = 0;
    lbl_803CC1B2++;
    for (i = 0; i < 5; i++) {
        *(s32*)(entry + 0x1C + i * 8) = 0;
        *(s32*)(entry + 0x18 + i * 8) = 0;
    }
    return entry;
}

// .text:0x800B0B2C size:0xBC
void resetAllDrawingStructs_tonop(void) {
    return;
}

// .text:0x800B0CB8 size:0x70
void RunDrawScripts_with_stack_variables(void) {
    return;
}

extern void* lbl_803CC1D8[2];

extern s32 lbl_803CBB30;
extern u8 lbl_80111340[];

// fn_800B0D38, size:0x30
void fn_800B0D38(s32 index, s32 value) {
    if (index >= 0 && index < lbl_803CBB30) {
        u8* entry = lbl_80111340 + index * 0xC;
        *(s32*)(entry + 0x120) = value;
        ((s32*)lbl_80111340)[index * 3] = value;
    }
}

// fn_800B0D28, size:0x10
void fn_800B0D28(void* value) {
    lbl_803CC1D8[0] = value;
    lbl_803CC1D8[1] = value;
}

// .text:0x800B0D68 size:0x414
void AllocateSprite(void) {
    return;
}

extern u8* lbl_803CBB34;

// fn_800B117C, size:0xC
void fn_800B117C(u8 value) {
    lbl_803CBB34[0x8C] = value;
}

// .text:0x800B1188 size:0x11C
void fn_800B1188(void) {
    return;
}

// .text:0x800B12A4 size:0x38
void DrawNullSprite(void) {
    return;
}

// .text:0x800B12DC size:0x38
void fn_800B12DC(void) {
    return;
}

// .text:0x800B1314 size:0x3C
void fn_800B1314(void) {
    return;
}

// .text:0x800B1350 size:0x38
void DrawSprite_TexObj(void) {
    return;
}

// .text:0x800B1388 size:0x38
void fn_800B1388(void) {
    return;
}

// .text:0x800B13C0 size:0xA8
void fn_800B13C0(void) {
    return;
}

// .text:0x800B1468 size:0x98
void fn_800B1468(void) {
    return;
}

// .text:0x800B1500 size:0x9BC
void DrawSprite(void) {
    return;
}

// .text:0x800B1EBC size:0x2A4
void fn_800B1EBC(void) {
    return;
}

extern u8* lbl_803CBB34;

// fn_800B2160, size:0xC
void fn_800B2160(u8 value) {
    lbl_803CBB34[0x8A] = value;
}

// fn_800B216C, size:0x3C
s32 fn_800B216C(u8 flag, u32 mode, u8 index) {
    u32 value = ((u32)index << 4) | (flag | (mode << 1)) | 0x40000000;
    if (*(u32*)(lbl_803CBB34 + 0x78) == value) {
        return 0;
    }
    *(u32*)(lbl_803CBB34 + 0x78) = value;
    return 1;
}

// fn_800B21A8, size:0x98
void fn_800B21A8(s32 mode) {
    if (mode == 2) {
        s32 changed;
        u32 old = *(u32*)(lbl_803CBB34 + 0x78);
        if (old == 0x40000013) {
            changed = 0;
        } else {
            *(u32*)(lbl_803CBB34 + 0x78) = 0x40000013;
            changed = 1;
        }
        if (changed != 0) {
            *(u32*)(lbl_803CBB34 + 0x7C) = old;
        }
    } else if (mode != 0) {
        if (*(u32*)(lbl_803CBB34 + 0x78) != 0x40000017) {
            *(u32*)(lbl_803CBB34 + 0x78) = 0x40000017;
        }
    } else {
        if (*(u32*)(lbl_803CBB34 + 0x78) != 0x4000001F) {
            *(u32*)(lbl_803CBB34 + 0x78) = 0x4000001F;
        }
    }
}

// .text:0x800B2240 size:0x294
void fn_800B2240(void) {
    return;
}

// .text:0x800B24D4 size:0x48
void fn_800B24D4(void) {
    return;
}

// .text:0x800B251C size:0x288
void fn_800B251C(void) {
    return;
}

// .text:0x800B27A4 size:0x38
void fn_800B27A4(void) {
    return;
}

// .text:0x800B27DC size:0x78
void fn_800B27DC(void) {
    return;
}

// .text:0x800B2854 size:0x274
void fn_800B2854(void) {
    return;
}

// .text:0x800B2AC8 size:0x84
void fn_800B2AC8(void) {
    return;
}

// .text:0x800B2B4C size:0x8
void fn_800B2B4C(GameActor* actor, f32 value) {
    actor->unk90 = value;
}

// .text:0x800B2B54 size:0x18
void fn_800B2B54(void) {
    return;
}

// .text:0x800B2B6C size:0x8
void Set_FUN_800b2b6c(void) {
    return;
}

// .text:0x800B2B74 size:0x34
void fn_800B2B74(void) {
    return;
}

// .text:0x800B2BA8 size:0x3C
void fn_800B2BA8(void) {
    return;
}

// .text:0x800B2BE4 size:0x18
void fn_800B2BE4(void) {
    return;
}

// .text:0x800B2BFC size:0xC
void fn_800B2BFC(void) {
    return;
}

// .text:0x800B2C08 size:0x8
void fn_800B2C08(void) {
    return;
}

// .text:0x800B2C10 size:0x34
void fn_800B2C10(void) {
    return;
}
