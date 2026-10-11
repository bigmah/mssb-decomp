#include "challenge/rep_7A28.h"


#include "static/UnknownHomes_Static.h"
#include <string.h>
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
extern u8 lbl_1_data_10908[];
extern s32 lbl_1_data_109F8;
extern void (*lbl_1_data_108E8[])(void*);
extern void fn_8003414C(void*);
extern void GXDrawSphere1(u8);
extern void minigamesGXStuff(void);
extern void (*lbl_1_data_108F0[])(void);
extern u8 lbl_803C6CF8[];
extern void* _OSAllocFromHeap(s32, s32);
extern const f32 lbl_1_rodata_7B5C;
typedef struct { u32 a, b, c; } V3U;
extern V3U lbl_1_rodata_7B50;
extern void fn_80030D88(void*, f32*, void*, s32);
extern void fn_8002F5F4(void*, f32*, void*);
extern void fn_80030470(void*, f32*, V3U*, void*, s32);
extern void PSVECNormalize(const Vec*, Vec*);
extern const f32 lbl_1_rodata_7B64;
extern const f32 lbl_1_rodata_7B98;

static void* sTable[4] = { (void*)fn_1_27AD4, (void*)fn_1_276CC, 0, 0 };
static u8 sXfer[0x10] = {1};
static u8 sArr[0xF0] = {1};
static s32 sLast = 1;


extern void* lbl_80366158[];

// .text:0x27AD0 size:0x4
void fn_1_27AD0(void) {
}

// fn_1_27E50, size:0x48
void fn_1_27E50(void) {
    u8* parent;
    fn_800AD038(lbl_80366158[2]);
    parent = *(u8**)(((u8*)lbl_803CC1B8) + 0xC);
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
    u8* object = ((u8*)lbl_803CC1B8);
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
    if (*(u16*)(((u8*)lbl_803CC1B8) + 0x34) & 1) {
        lbl_1_data_108E8[*(s8*)(((u8*)lbl_803CC1B8) + 0x36)](lbl_1_data_108E8);
    } else {
        memcpy(buf, (u8*)&lbl_803C77B8 + 0x10, 6);
        buf[0] = -buf[0];
        buf[4] = ((u8*)&lbl_803C77B8)[0x15];
        buf[5] = ((u8*)&lbl_803C77B8)[0x14];
        fn_1_26D28(((ChParticleTask*)lbl_803CC1B8)->camera, lbl_803C77B8._00, lbl_803C77B8._02, lbl_803C77B8._04, (ChallengeDebugPad*)buf);
    }
    if (lbl_803C77B8._02 & 0x1000) {
        *(u16*)(((u8*)lbl_803CC1B8) + 0x34) ^= 1;
    }
}

// fn_1_28118, size:0xE8
void fn_1_28118(void) {
    u8* object = ((u8*)lbl_803CC1B8);
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
            *(void**)((u8*)lbl_803CC1B8) = fn_1_27E98;
        }
    }
}

// fn_1_28200, size:0xF4
void fn_1_28200(void) {
    u8* object = ((u8*)lbl_803CC1B8);
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
    *(void**)((u8*)lbl_803CC1B8) = fn_1_28118;
}

// fn_1_27594, size:0x138
void fn_1_27594(void) {
    Vec dir;
    V3U rest;
    u8* object;
    s32 i;
    u16 flags;
    object = ((u8*)lbl_803CC1B8);
    rest = lbl_1_rodata_7B50;
    flags = *(u16*)(object + 0x34);
    if ((flags & 2) || (flags & 4)) {
        i = 1;
        dir.x = lbl_1_rodata_7B5C;
        dir.y = lbl_1_rodata_7B5C;
        dir.z = *(f32*)(object + 0x2C);
        do {
            fn_80030D88(object + 0x20, &dir.x, lbl_1_data_10908 + i * 0x50, 5);
            i++;
        } while (i < 3);
        fn_8002F5F4(object + 0x20, &dir.x, &lbl_1_data_109F8);
        PSVECNormalize(&dir, &dir);
        fn_80030470(object + 0x20, &dir.x, &rest, lbl_1_data_10908, 5);
        *(u16*)(((u8*)lbl_803CC1B8) + 0x34) ^= 2;
    }
    if (*(u16*)(((u8*)lbl_803CC1B8) + 0x34) & 8) {
        fn_80048BEC(*(void**)(object + 0x1C), 1, 1);
    }
}

// fn_1_27BB8, size:0x1B4
void fn_1_27BB8(void) {
    Mtx m;
    Vec v;
    f32 x; f32 y; f32 z;
    u8* object = ((u8*)lbl_803CC1B8);
    fn_8003414C(*(void**)(object + 0x14));
    fn_1_272DC(*(void**)(object + 0x14), 0);
    fn_1_AF4(20, 20, lbl_1_rodata_7B64);
    PSMTXScale(m, *(f32*)(object + 0x30), *(f32*)(object + 0x30), *(f32*)(object + 0x30));
    PSMTXTransApply(m, m, *(f32*)(object + 0x20), *(f32*)(object + 0x24), *(f32*)(object + 0x28));
    PSMTXConcat(*(void**)(object + 0x14), m, *(void**)(object + 0x14));
    fn_1_272DC(*(void**)(object + 0x14), 0);
    fn_1_F2C(4, 0, 0);
    GXSetZMode(1, GX_LEQUAL, 1);
    GXDrawSphere1(2);
    PSMTXTrans(m, *(f32*)(object + 0x20), *(f32*)(object + 0x24), *(f32*)(object + 0x28));
    PSMTXConcat(*(void**)(object + 0x14), m, *(void**)(object + 0x14));
    fn_1_272DC(*(void**)(object + 0x14), 0);
    fn_1_F2C(4, 0, 0);
    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    z = *(f32*)(object + 0x28);
    y = *(f32*)(object + 0x24);
    x = *(f32*)(object + 0x20);
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
    GXWGFifo.u32 = 0xFF0000FF;
    v.x = lbl_1_rodata_7B5C;
    v.y = lbl_1_rodata_7B5C;
    v.z = *(f32*)(object + 0x2C);
    PSVECAdd((Vec*)(object + 0x20), &v, &v);
    GXWGFifo.f32 = v.x;
    GXWGFifo.f32 = v.y;
    GXWGFifo.f32 = v.z;
    GXWGFifo.u32 = 0xFF0000FF;
    lbl_1_data_108F0[*(s8*)(object + 0x36)]();
    minigamesGXStuff();
}

// fn_1_27E98, size:0x280
void fn_1_27E98(void) {
    Mtx m;
    Vec v;
    f32 x; f32 y; f32 z;
    u8* object = ((u8*)lbl_803CC1B8);
    fn_1_27D6C();
    fn_1_27330(*(void**)(object + 0x14));
    object = ((u8*)lbl_803CC1B8);
    fn_8003414C(*(void**)(object + 0x14));
    fn_1_272DC(*(void**)(object + 0x14), 0);
    fn_1_AF4(20, 20, lbl_1_rodata_7B64);
    PSMTXScale(m, *(f32*)(object + 0x30), *(f32*)(object + 0x30), *(f32*)(object + 0x30));
    PSMTXTransApply(m, m, *(f32*)(object + 0x20), *(f32*)(object + 0x24), *(f32*)(object + 0x28));
    PSMTXConcat(*(void**)(object + 0x14), m, *(void**)(object + 0x14));
    fn_1_272DC(*(void**)(object + 0x14), 0);
    fn_1_F2C(4, 0, 0);
    GXSetZMode(1, GX_LEQUAL, 1);
    GXDrawSphere1(2);
    PSMTXTrans(m, *(f32*)(object + 0x20), *(f32*)(object + 0x24), *(f32*)(object + 0x28));
    PSMTXConcat(*(void**)(object + 0x14), m, *(void**)(object + 0x14));
    fn_1_272DC(*(void**)(object + 0x14), 0);
    fn_1_F2C(4, 0, 0);
    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    z = *(f32*)(object + 0x28);
    y = *(f32*)(object + 0x24);
    x = *(f32*)(object + 0x20);
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
    GXWGFifo.u32 = 0xFF0000FF;
    v.x = lbl_1_rodata_7B5C;
    v.y = lbl_1_rodata_7B5C;
    v.z = *(f32*)(object + 0x2C);
    PSVECAdd((Vec*)(object + 0x20), &v, &v);
    GXWGFifo.f32 = v.x;
    GXWGFifo.f32 = v.y;
    GXWGFifo.f32 = v.z;
    GXWGFifo.u32 = 0xFF0000FF;
    lbl_1_data_108F0[*(s8*)(object + 0x36)]();
    minigamesGXStuff();
}

extern const f32 lbl_1_rodata_7B60; // 0.5f
extern const f32 lbl_1_rodata_7B68; // 2.0f
extern const char lbl_1_rodata_7B6C[]; // "Fire 0"
extern const char lbl_1_rodata_7B74[]; // "Fire 1"
extern const char lbl_1_rodata_7B7C[]; // "Smoke"
extern const char lbl_1_rodata_7B84[]; // "Fireball"

#define CUR_TASK ((ChParticleTask*)lbl_803CC1B8)

// .text:0x000276CC size:0x404
void fn_1_276CC(void) {
    u8* pool = (u8*)lbl_1_data_108E8; // TODO type: menu item tables live in this data pool
    ChParticleTask* task = CUR_TASK;
    u16 flags = task->flags;
    u16 repeat;

    if (flags & 8) {
        // TODO type: lbl_803C77B8 byte 0x15 (PadState.analog.triggerRight)
        fn_80048820(task->menu, lbl_803C77B8._00, lbl_803C77B8._02, lbl_803C77B8._04,
                    ((u8*)&lbl_803C77B8)[0x15]);
        if (lbl_803C77B8._00 & 0x100) {
            CUR_TASK->flags &= ~2;
            CUR_TASK->flags |= 2;
        } else if (lbl_803C77B8._02 & 0x200) {
            CUR_TASK->flags ^= 8;
        }
    } else if ((repeat = lbl_803C77B8._04) & 8) {
        task->cursor = (task->cursor + 6) % 7;
    } else if (repeat & 4) {
        task->cursor = (task->cursor + 1) % 7;
    } else if (repeat & 1) {
        switch (task->cursor) {
        case 0:
            task->flags = flags ^ 4;
            break;
        case 1:
            task->scale *= lbl_1_rodata_7B60;
            break;
        case 2:
            task->length -= (f32)(task->length > lbl_1_rodata_7B64);
            break;
        }
    } else if (repeat & 2) {
        switch (task->cursor) {
        case 0:
            task->flags = flags ^ 4;
            break;
        case 1:
            task->scale *= lbl_1_rodata_7B68;
            break;
        case 2:
            task->length += lbl_1_rodata_7B64;
            break;
        }
    } else if (lbl_803C77B8._00 & 0x100) {
        task->menu->top = 0;
        task->menu->cursor = 0;
        task->menu->count = 0;
        switch (task->cursor) {
        case 3:
            task->menu->title = lbl_1_rodata_7B6C;
            task->menu->items = (DebugMenuItem*)(pool + 0x154);
            CUR_TASK->flags ^= 8;
            break;
        case 4:
            task->menu->title = lbl_1_rodata_7B74;
            task->menu->items = (DebugMenuItem*)(pool + 0x3E8);
            CUR_TASK->flags ^= 8;
            break;
        case 5:
            task->menu->title = lbl_1_rodata_7B7C;
            task->menu->items = (DebugMenuItem*)(pool + 0x650);
            CUR_TASK->flags ^= 8;
            break;
        case 6:
            task->menu->title = lbl_1_rodata_7B84;
            task->menu->items = (DebugMenuItem*)(pool + 0x8B8);
            CUR_TASK->flags ^= 8;
            break;
        default:
            task->menu->items = NULL;
            CUR_TASK->flags &= ~2;
            CUR_TASK->flags |= 2;
            break;
        }
        if (task->menu->items != NULL) {
            while (task->menu->items[task->menu->count].label != NULL) {
                task->menu->count++;
            }
        }
    } else if (lbl_803C77B8._02 & 0x200) {
        task->mode = 0;
        task->cursor = 0;
    }
}
