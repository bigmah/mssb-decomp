#include "main/file_8000F150.h"
#include "static/UnknownHomes_Static.h"

extern u16 lbl_80366218[];
extern void* lbl_803CBBE8;
extern u8 lbl_800E9920[];

// .text:0x8000F150 size:0x298
void fn_8000F150(void* arg) {
    return;
}

// .text:0x8000F3E8 size:0xA4
void fn_8000F3E8(s32 arg) {
    return;
}

// .text:0x8000F48C size:0x2C
void somethingSetTexturePointer(void) {
    return;
}

// .text:0x8000F4B8 size:0x7C
void fn_8000F4B8(s32 a, s32 b, s32 c, s32 d) {
    return;
}

// .text:0x8000F534 size:0x3C0
void fn_8000F534(void* object, s32 visible) {
    return;
}

// .text:0x8000F8F4 size:0x94
void fn_8000F8F4(LayoutGroup* group) {
    return;
}

// .text:0x8000F988 size:0x114
s32 fn_8000F988(LayoutGroup* group, s32 index, u16 arg2, s32 table, s32 msg, s32 shadow) {
    return 0;
}

// .text:0x8000FA9C size:0x2B8
s32 fn_8000FA9C(s32 index) {
    return 0;
}

// .text:0x8000FD54 size:0x24
void fn_8000FD54(s32 index, s16 a, s16 b, s16 c, s16 d) {
    TextEntry* e = &lbl_80366B18.entries[index];
    e->strings[0] = a;
    e->strings[1] = b;
    e->strings[2] = c;
    e->strings[3] = d;
}

// .text:0x8000FD78 size:0x24
void fn_8000FD78(s32 index, s16 a, s16 b, s16 c, s16 d) {
    TextEntry* e = &lbl_80366B18.entries[index];
    e->numbers[0] = a;
    e->numbers[1] = b;
    e->numbers[2] = c;
    e->numbers[3] = d;
}

// .text:0x8000FD9C size:0x6C
void fn_8000FD9C(s32 index, s32 speed, s32 limit) {
    if (speed == 0) {
        lbl_80366B18.entries[index].charLimit = -1;
        lbl_80366B18.entries[index].typeSpeed = 0;
        lbl_80366B18.entries[index].typeTimer = 0;
        return;
    }
    if (limit >= 0) {
        lbl_80366B18.entries[index].charLimit = limit;
    }
    lbl_80366B18.entries[index].typeSpeed = speed;
    lbl_80366B18.entries[index].typeTimer = 0;
}

// .text:0x8000FE08 size:0x4C
void fn_8000FE08(s32 index, s32 table, s32 msg) {
    TextEntry* e;
    u16* text = lbl_80366B18.tables[table]->msgs[msg];
    e = &lbl_80366B18.entries[index];
    e->text = text;
    if (e->charLimit >= 0) {
        e->charLimit = 0;
        e->finished = 0;
        e->_35 = 0;
    }
}

// .text:0x8000FE54 size:0x94
void fn_8000FE54(void) {
    return;
}

// .text:0x8000FEE8 size:0x1C
void fn_8000FEE8(s32 index) {
    lbl_80366B18.entries[index].state = 0;
}

// .text:0x8000FF04 size:0x1A0
s32 fn_8000FF04(s32 table, s32 msg, s16 x, s16 y, u8 layer, u32 color, u8 fontSize) {
    return 0;
}

// .text:0x800100A4 size:0x3F4
void fn_800100A4(s32 x, s32 y, u16 s, u16 t, u16 w, u32 color, s32 kind, MtxPtr mtx) {
    return;
}

// .text:0x80010498 size:0xA94
#if NONMATCHING
void DrawText(s32 index) {
    return;
}
#endif

// .text:0x80010F2C size:0x74
void DrawTextOnCondition(s32 layer) {
    return;
}

// .text:0x80010FA0 size:0x60
void fn_80010FA0(void) {
    return;
}

// .text:0x80011000 size:0x140
void fn_80011000(void) {
    return;
}

// .text:0x80011140 size:0x74
void fn_80011140(void) {
    return;
}

// .text:0x800111B4 size:0x24
void fn_800111B4(MsgTable* table) {
    return;
}

// .text:0x800111D8 size:0x24
void** fn_800111D8(void* actor) {
    return 0;
}

// .text:0x800111FC size:0x15C
void* fn_800111FC(void* actor, s32 second) {
    return 0;
}

// .text:0x80011358 size:0x110
void fn_80011358(s8 index, s32 kind) {
    return;
}

// .text:0x80011468 size:0x108
void fn_80011468(void) {
    return;
}

extern u32 lbl_803CBC18;

extern u8 lbl_8036E548[];

// fn_80011578, size:0x50
void fn_80011578(void) {
    s8 i = 0;
    s32 n;
    for (n = 13; n != 0; n--) {
        if (i >= 0 && i < 13) {
            u8* object = *(u8**)(lbl_8036E548 + ((s8)i << 2) + 0x2C50);
            if (object != NULL) {
                *(u32*)(object + 0x5C) = 0;
            }
        }
        i++;
    }
}

// fn_800115C8, size:0x3C
void fn_800115C8(s8 index) {
    if (index >= 0 && index < 13) {
        u8* base = lbl_8036E548;
        u8* object;
        base += index * 4;
        object = *(u8**)(base + 0x2C50);
        if (object != NULL) {
            *(u32*)(object + 0x5C) = 0;
        }
    }
}

// fn_80011570, size:0x8
u32 fn_80011570(void) {
    return lbl_803CBC18;
}

// fn_80011604, size:0x3C
void fn_80011604(s8 index, u32 value) {
    u8* base;
    u8* object;
    if (index < 0 || index >= 13) {
        return;
    }
    base = lbl_8036E548;
    base += index * 4;
    object = *(u8**)(base + 0x2C50);
    if (object != NULL) {
        *(u32*)(object + 0x5C) = value;
    }
}
