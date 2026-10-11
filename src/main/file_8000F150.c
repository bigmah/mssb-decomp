#include "main/file_8000F150.h"
#include "static/UnknownHomes_Static.h"

extern u16 lbl_80366218[];
extern void* lbl_803CBBE8;
extern u8 lbl_800E9920[];

typedef struct FogSetting {
    /*0x0*/ u8 _00[0x8];
    /*0x8*/ s32 value;
} FogSetting;
extern FogSetting lbl_800E9908[];
extern u8 lbl_803CBBC0;
extern u8 lbl_803CB760[5];
extern void fn_800A7D4C(s32, void*);

// .text:0x8000F150 size:0x298
void fn_8000F150(void* arg) {
    return;
}

// .text:0x8000F3E8 size:0xA4
void fn_8000F3E8(s32 arg) {
    FogSetting* f = &lbl_800E9908[lbl_803CBBC0];
    switch (arg) {
    case -1:
        f->value = lbl_803CB760[4];
        break;
    case 4:
        f->value = lbl_803CB760[1];
        break;
    case 5:
        f->value = lbl_803CB760[0];
        break;
    case 6:
        f->value = lbl_803CB760[2];
        break;
    case 11:
        f->value = lbl_803CB760[3];
        break;
    }
    fn_800A7D4C(0, f);
}

// .text:0x8000F48C size:0x2C
void somethingSetTexturePointer(void) {
    lbl_803CBBE8 = lbl_800E9920;
    convertTextureHeader(lbl_800E9920);
}

// .text:0x8000F4B8 size:0x7C
void fn_8000F4B8(s32 a, s32 b, s32 c, s32 d) {
    lbl_80366B18.padMask = 0;
    if (a >= 0) {
        lbl_80366B18.padMask = 1 << a;
    }
    if (b >= 0) {
        lbl_80366B18.padMask |= 1 << b;
    }
    if (c >= 0) {
        lbl_80366B18.padMask |= 1 << c;
    }
    if (d >= 0) {
        lbl_80366B18.padMask |= 1 << d;
    }
}

// .text:0x8000F534 size:0x3C0
void fn_8000F534(void* object, s32 visible) {
    return;
}

// .text:0x8000F8F4 size:0x94
void fn_8000F8F4(LayoutGroup* group) {
    s32 i;
    s32 j;
    u16 start = group->start;
    for (i = 0; i < group->count; i++) {
        LayoutObj* obj = lbl_80371C30[start + (u32)i].obj;
        if (obj != NULL && (obj->flags & 4)) {
            for (j = 0; j < 30; j++) {
                if (lbl_80366B18.owners[j].object == lbl_80371C30[start + (u32)i].obj) {
                    lbl_80366B18.owners[j].object = NULL;
                    break;
                }
            }
        }
    }
}

// .text:0x8000F988 size:0x114
s32 fn_8000F988(LayoutGroup* group, s32 index, u16 arg2, s32 table, s32 msg, s32 shadow) {
    s32 i;
    LayoutObj* obj = lbl_80371C30[group->start + index].obj;
    obj->flags |= 4;
    if (shadow != 0) {
        obj->flags |= 8;
    }
    for (i = 0; i < 30; i++) {
        if (lbl_80366B18.owners[i].object == NULL) {
            lbl_80366B18.owners[i].object = obj;
            lbl_80366B18.owners[i]._06 = arg2;
            lbl_80366B18.owners[i].entry = fn_8000FF04(table, msg, 0, 0, obj->layer, -1, 0);
            if (obj->_00 != NULL) {
                lbl_80366B18.entries[lbl_80366B18.owners[i].entry].mtx = obj->mtx;
            } else {
                lbl_80366B18.entries[lbl_80366B18.owners[i].entry].mtx = NULL;
            }
            return lbl_80366B18.owners[i].entry;
        }
    }
    return -1;
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
    s32 i;
    for (i = 0; i < 30; i++) {
        lbl_80366B18.entries[i].state = 0;
    }
}

// .text:0x8000FEE8 size:0x1C
void fn_8000FEE8(s32 index) {
    lbl_80366B18.entries[index].state = 0;
}

// NONMATCHING 99%: two address computations (table/msg slwi) scheduled in the other order
// .text:0x8000FF04 size:0x1A0
#if NONMATCHING
s32 fn_8000FF04(s32 table, s32 msg, s16 x, s16 y, u8 layer, u32 color, u8 fontSize) {
    s32 i;
    TextEntry* e;
    for (i = 0; i < 30; i++) {
        if (lbl_80366B18.entries[i].state == 0) {
            break;
        }
    }
    if (i >= 30) {
        return 0;
    }
    e = &lbl_80366B18.entries[i];
    e->text = lbl_80366B18.tables[table]->msgs[msg];
    e->x = x;
    e->y = y;
    e->layer = layer;
    e->state = 2;
    e->fontSize = fontSize;
    e->color = color;
    e->numbers[0] = 0;
    e->numbers[1] = 0;
    e->numbers[2] = 0;
    e->numbers[3] = 0;
    e->charSpacing = 0;
    e->lineSpacing = 2;
    e->hAlign = 0;
    e->vAlign = 0;
    e->mtx = NULL;
    e->charLimit = -1;
    e->typeSpeed = 0;
    e->typeTimer = 0;
    e->finished = 0;
    e->_33 = 0;
    e->_35 = 0;
    e->_36 = 0;
    return i;
}
#endif

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
    s32 i;
    for (i = 0; i < 30; i++) {
        if (lbl_80366B18.entries[i].state == 2 && layer == lbl_80366B18.entries[i].layer) {
            DrawText(i);
        }
    }
}

// NONMATCHING 96%: extra `mr` when setting up dst before the copy loop
// .text:0x80010FA0 size:0x60
#if NONMATCHING
void fn_80010FA0(void) {
    MsgTable* t = lbl_80366B18.tables[0];
    u16* dst = lbl_80366218;
    u16* src;
    lbl_80366B18.msgs = t->msgs;
    lbl_80366B18._7EC = t->msgs[1];
    lbl_80366B18._7F0 = t->msgs[2];
    lbl_80366B18._7F8 = t->msgs[6];
    lbl_80366B18._7F4 = t->msgs[5];
    src = lbl_80366B18.msgs[7];
    for (;;) {
        u16 c = *src;
        if (c == 0x4001) {
            return;
        }
        *dst = c;
        src++;
        dst++;
    }
}
#endif

// NONMATCHING 96%: saved regs r30/r31 swapped (loop counter vs. lbl_80366B18 base)
// .text:0x80011000 size:0x140
#if NONMATCHING
void fn_80011000(void) {
    s32 i;
    lbl_80366B18.fontTex[0] = (TexArchive*)((u8*)lbl_80366B18.fontArchive + lbl_80366B18.fontArchive[0]);
    lbl_80366B18.fontTex[1] = (TexArchive*)((u8*)lbl_80366B18.fontArchive + lbl_80366B18.fontArchive[1]);
    lbl_80366B18.fontTex[2] = (TexArchive*)((u8*)lbl_80366B18.fontArchive + lbl_80366B18.fontArchive[2]);
    lbl_80366B18.fontTex[3] = (TexArchive*)((u8*)lbl_80366B18.fontArchive + lbl_80366B18.fontArchive[3]);
    for (i = 0; i < 4; i++) {
        convertTextureHeader(lbl_80366B18.fontTex[i]);
        lbl_80366B18.fontTexObj[i] = TEX_ARCHIVE_OBJ(lbl_80366B18.fontTex[i], 0);
    }
    convertTextureHeader(lbl_80366B18.iconArchive);
    for (i = 0; i < 9; i++) {
        lbl_80366B18.iconTexObj[i] = TEX_ARCHIVE_OBJ(lbl_80366B18.iconArchive, i);
    }
    lbl_80366B18.scaleX = 1;
    lbl_80366B18.scaleY = 1;
}
#endif

// .text:0x80011140 size:0x74
void fn_80011140(void) {
    s32 i;
    for (i = 0; i < 30; i++) {
        lbl_80366B18.entries[i].state = 0;
        lbl_80366B18.owners[i].object = NULL;
    }
    lbl_80366B18.padMask = 0;
}

// .text:0x800111B4 size:0x24
void fn_800111B4(MsgTable* table) {
    s32 n = table->count;
    u16** p = table->msgs;
    do {
        *p = (u16*)((u32)*p + (u32)table); // file offset -> pointer (32-bit data)
        p++;
    } while (--n);
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
