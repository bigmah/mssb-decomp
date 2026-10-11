#include "challenge/rep_7A28.h"
#include "static/UnknownHomes_Static.h"
#include <string.h>
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#define REP_HEADER_FN repHeader_7A28
#include "header_rep_inline.h"

extern void GXDrawSphere1(u8);
extern void minigamesGXStuff(void);
extern u8 lbl_803C6CF8[];
extern void* _OSAllocFromHeap(s32, s32);
extern void PSVECNormalize(const Vec*, Vec*);
extern void* lbl_80366158[];

// ParticleParams5 / ParticleParams8 from main/file_800263FC.h, which can't be
// included next to UnknownHomes_Static.h (conflicting prototypes). Same layout.
typedef struct ChParticleParams5 {
    /* 0x00 */ struct TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ u32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
} ChParticleParams5;

// Beam emitter parameters with its 8 texture frames (ParticleParams8 ends in a
// count-sized array).
typedef struct ChBeamParams {
    /* 0x00 */ struct TexArchive* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 taper;
    /* 0x10 */ s32 sizeMax;
    /* 0x14 */ s32 sizeMin;
    /* 0x18 */ s32 length;
    /* 0x1C */ s32 offset;
    /* 0x20 */ u32 gray;
    /* 0x24 */ s32 texIndex2[8];
} ChBeamParams;

// Same layout as AssetLoadInstructions (Unknown/File_0x800a64e0.h).
typedef struct ChFileEntry {
    /* 0x0 */ u32 compressionConstants;
    /* 0x4 */ u32 sizeFlags;
    /* 0x8 */ u32 aramOffset;
    /* 0xC */ u32 compressedSize;
} ChFileEntry;

extern void fn_8003414C(void*);
extern void fn_8002F5F4(Vec* pos, Vec* dir, ChBeamParams* prm);
extern void fn_80030470(Vec* pos, Vec* dir, Vec* velScale, ChParticleParams5* prm, u8 type);
extern void fn_80030D88(Vec* pos, Vec* dir, ChParticleParams5* prm, u8 type);

// Per-mode input handlers; the caller passes the table itself as a (stale) argument.
static void (*lbl_1_data_108E8[2])(void*) = {
    (void (*)(void*))fn_1_27AD4,
    (void (*)(void*))fn_1_276CC,
};
// Per-mode draw callbacks.
static void (*lbl_1_data_108F0[2])(void) = { fn_1_27AD0, fn_1_27594 };
// Particle texture archive, an AssetLoadInstructions entry (its anonymous unions
// can't be initialised here, hence the plain words).
static ChFileEntry lbl_1_data_108F8 = { 0x40B, 0x40046100, 0x0E641000, 0x24B48 };
// Emitter parameters: fire 0, fire 1, smoke (fixed point x100000).
static ChParticleParams5 lbl_1_data_10908[3] = {
    { NULL, 0, 5, 280000, 0, 0, 4, 2, 120000, 90000, 0, 128, 1000000, 1000000, -500000, 500000, 0xFFFFFF00, 0, -28000, 1 },
    { NULL, 0, 10, 78000, 60000, 50000, 12, 6, 109000, 101000, 0, 40, 4500000, 9500000, -1000000, 4500000, 0xFFFFFF00, 0, 0, 0 },
    { NULL, 0, 3, 90000, 100000, 10000, 20, 10, 103000, 105999, 0, 60, 10000000, 18000000, 1000000, -1000000, 0x3C3C3C00, 0, 0, 0 },
};
// Fireball beam.
static ChBeamParams lbl_1_data_109F8 = {
    NULL, 20, 8, 7, 250000, 50000, 550000, 0, 255, { 12, 13, 14, 15, 16, 17, 18, 19 },
};

#define ITEM_COUNT(label, value) { 0, label, 1, 100, { 1, 10, 20 }, value, 0, 0, NULL }
#define ITEM_FIXED(label, min, value) { 1, label, min, 10000000, { 100, 10, 1000 }, value, 0, 0, NULL }
#define ITEM_ANGLE(label, min, value) { 1, label, min, 18000000, { 100000, 10000, 1000000 }, value, 0, 0, NULL }
#define ITEM_END { 0, NULL, 0, 0, { 0, 0, 0 }, NULL, 0, 0, NULL }

// Edit menus for the three emitters and the beam.
static DebugMenuItem lbl_1_data_10A3C[15] = {
    ITEM_COUNT("NUM     ", &lbl_1_data_10908[0].count),
    ITEM_FIXED("SIZE    ", 10, &lbl_1_data_10908[0].unkC),
    ITEM_FIXED("SPEED   ", 0, &lbl_1_data_10908[0].unk10),
    ITEM_FIXED("SLOWDOWN", 0, &lbl_1_data_10908[0].unk14),
    ITEM_COUNT("LIFE    ", &lbl_1_data_10908[0].unk18),
    ITEM_COUNT("LIFETURN", &lbl_1_data_10908[0].unk1C),
    ITEM_FIXED("SCALE UP", 0, &lbl_1_data_10908[0].unk20),
    ITEM_FIXED("SCALE DN", 0, &lbl_1_data_10908[0].unk24),
    { 0, "MAXALPHA", 0, 255, { 1, 10, 20 }, &lbl_1_data_10908[0].unk2C, 0, 0, NULL },
    ITEM_FIXED("SP ANGLE", 0, &lbl_1_data_10908[0].unk30),
    ITEM_ANGLE("HANG MAX", 0, &lbl_1_data_10908[0].unk34),
    ITEM_ANGLE("VANG MIN", -18000000, &lbl_1_data_10908[0].unk38),
    ITEM_ANGLE("VANG MAX", -18000000, &lbl_1_data_10908[0].unk3C),
    { 1, "BIAS    ", -10000000, 10000000, { 100, 10, 1000 }, &lbl_1_data_10908[0].unk48, 0, 0, NULL },
    ITEM_END,
};
static DebugMenuItem lbl_1_data_10CD0[14] = {
    ITEM_COUNT("NUM     ", &lbl_1_data_10908[1].count),
    ITEM_FIXED("SIZE    ", 10, &lbl_1_data_10908[1].unkC),
    ITEM_FIXED("SPEED   ", 0, &lbl_1_data_10908[1].unk10),
    ITEM_FIXED("SLOWDOWN", 0, &lbl_1_data_10908[1].unk14),
    ITEM_COUNT("LIFE    ", &lbl_1_data_10908[1].unk18),
    ITEM_COUNT("LIFETURN", &lbl_1_data_10908[1].unk1C),
    ITEM_FIXED("SCALE UP", 0, &lbl_1_data_10908[1].unk20),
    ITEM_FIXED("SCALE DN", 0, &lbl_1_data_10908[1].unk24),
    { 0, "MAXALPHA", 0, 255, { 1, 10, 20 }, &lbl_1_data_10908[1].unk2C, 0, 0, NULL },
    ITEM_FIXED("SP ANGLE", 0, &lbl_1_data_10908[1].unk30),
    ITEM_ANGLE("HANG MAX", 0, &lbl_1_data_10908[1].unk34),
    ITEM_ANGLE("VANG MIN", -18000000, &lbl_1_data_10908[1].unk38),
    ITEM_ANGLE("VANG MAX", -18000000, &lbl_1_data_10908[1].unk3C),
    ITEM_END,
};
static DebugMenuItem lbl_1_data_10F38[14] = {
    ITEM_COUNT("NUM     ", &lbl_1_data_10908[2].count),
    ITEM_FIXED("SIZE    ", 10, &lbl_1_data_10908[2].unkC),
    ITEM_FIXED("SPEED   ", 0, &lbl_1_data_10908[2].unk10),
    ITEM_FIXED("SLOWDOWN", 0, &lbl_1_data_10908[2].unk14),
    ITEM_COUNT("LIFE    ", &lbl_1_data_10908[2].unk18),
    ITEM_COUNT("LIFETURN", &lbl_1_data_10908[2].unk1C),
    ITEM_FIXED("SCALE UP", 0, &lbl_1_data_10908[2].unk20),
    ITEM_FIXED("SCALE DN", 0, &lbl_1_data_10908[2].unk24),
    { 0, "MAXALPHA", 0, 255, { 1, 10, 20 }, &lbl_1_data_10908[2].unk2C, 0, 0, NULL },
    ITEM_FIXED("SP ANGLE", 0, &lbl_1_data_10908[2].unk30),
    ITEM_ANGLE("HANG MAX", 0, &lbl_1_data_10908[2].unk34),
    ITEM_ANGLE("VANG MIN", -18000000, &lbl_1_data_10908[2].unk38),
    ITEM_ANGLE("VANG MAX", -18000000, &lbl_1_data_10908[2].unk3C),
    ITEM_END,
};
static DebugMenuItem lbl_1_data_111A0[7] = {
    { 0, "NUM     ", 2, 8, { 1, 1, 1 }, &lbl_1_data_109F8.count, 0, 0, NULL },
    { 0, "TAILNUM ", 1, 7, { 1, 1, 1 }, &lbl_1_data_109F8.taper, 0, 0, NULL },
    ITEM_FIXED("SIZE    ", 10, &lbl_1_data_109F8.sizeMax),
    ITEM_FIXED("TAILSIZE", 10, &lbl_1_data_109F8.sizeMin),
    ITEM_FIXED("LENGTH  ", 10, &lbl_1_data_109F8.length),
    { 0, "CENTER  ", 0, 7, { 1, 1, 1 }, &lbl_1_data_109F8.offset, 0, 0, NULL },
    ITEM_END,
};

#define CUR_TASK ((ChParticleTask*)lbl_803CC1B8)

// .text:0x00028200 size:0xF4
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
    *(f32*)(camera + 0x8C) *= -1.0f;
    *(f32*)(object + 0x20) = 0.0f;
    *(f32*)(object + 0x24) = -1.0f;
    *(f32*)(object + 0x28) = 0.0f;
    *(f32*)(object + 0x2C) = 1.0f;
    *(f32*)(object + 0x30) = 1.0f;
    object[0x36] = 0;
    object[0x37] = 0;
    *(u16*)(object + 0x34) = 0;
    *(void**)((u8*)lbl_803CC1B8) = fn_1_28118;
}

// .text:0x00028118 size:0xE8
void fn_1_28118(void) {
    u8* object = ((u8*)lbl_803CC1B8);
    s16 state = *(s16*)(object + 0x10);
    s32 ready;
    switch (state) {
    case 0:
        *(s16*)(object + 0x10) = state + 1;
        *(void**)(object + 0x18) = ARAMTransfer(&lbl_1_data_108F8, 0, 0, 0);
    case 1:
        ready = lbl_803C6CF8[0x715];
        if (ready == 1) {
            *(s32*)(object + 0x18) = *(s32*)(object + 0x18) + **(s32**)(object + 0x18);
            convertTextureHeader(*(void**)(object + 0x18));
            fn_1_27560(*(struct TexArchive**)(object + 0x18));
            *(void**)((u8*)lbl_803CC1B8) = fn_1_27E98;
        }
    }
}

// .text:0x00027E98 size:0x280
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
    fn_1_AF4(20, 20, 1.0f);
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
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = *(f32*)(object + 0x2C);
    PSVECAdd((Vec*)(object + 0x20), &v, &v);
    GXWGFifo.f32 = v.x;
    GXWGFifo.f32 = v.y;
    GXWGFifo.f32 = v.z;
    GXWGFifo.u32 = 0xFF0000FF;
    lbl_1_data_108F0[*(s8*)(object + 0x36)]();
    minigamesGXStuff();
}

// .text:0x00027E50 size:0x48
void fn_1_27E50(void) {
    u8* parent;
    fn_800AD038(lbl_80366158[2]);
    parent = *(u8**)(((u8*)lbl_803CC1B8) + 0xC);
    *(s16*)(parent + 0x10) = 1;
    fn_800B0A14_removeQueue(parent);
}

// .text:0x00027D6C size:0xE4
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

// .text:0x00027BB8 size:0x1B4
void fn_1_27BB8(void) {
    Mtx m;
    Vec v;
    f32 x; f32 y; f32 z;
    u8* object = ((u8*)lbl_803CC1B8);
    fn_8003414C(*(void**)(object + 0x14));
    fn_1_272DC(*(void**)(object + 0x14), 0);
    fn_1_AF4(20, 20, 1.0f);
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
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = *(f32*)(object + 0x2C);
    PSVECAdd((Vec*)(object + 0x20), &v, &v);
    GXWGFifo.f32 = v.x;
    GXWGFifo.f32 = v.y;
    GXWGFifo.f32 = v.z;
    GXWGFifo.u32 = 0xFF0000FF;
    lbl_1_data_108F0[*(s8*)(object + 0x36)]();
    minigamesGXStuff();
}

// .text:0x00027AD4 size:0xE4
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

// .text:0x00027AD0 size:0x4
void fn_1_27AD0(void) {
}

// .text:0x000276CC size:0x404
void fn_1_276CC(void) {
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
            task->scale *= 0.5f;
            break;
        case 2:
            task->length -= (f32)(task->length > 1.0f);
            break;
        }
    } else if (repeat & 2) {
        switch (task->cursor) {
        case 0:
            task->flags = flags ^ 4;
            break;
        case 1:
            task->scale *= 2.0f;
            break;
        case 2:
            task->length += 1.0f;
            break;
        }
    } else if (lbl_803C77B8._00 & 0x100) {
        task->menu->top = 0;
        task->menu->cursor = 0;
        task->menu->count = 0;
        switch (task->cursor) {
        case 3:
            task->menu->title = "Fire 0";
            task->menu->items = lbl_1_data_10A3C;
            CUR_TASK->flags ^= 8;
            break;
        case 4:
            task->menu->title = "Fire 1";
            task->menu->items = lbl_1_data_10CD0;
            CUR_TASK->flags ^= 8;
            break;
        case 5:
            task->menu->title = "Smoke";
            task->menu->items = lbl_1_data_10F38;
            CUR_TASK->flags ^= 8;
            break;
        case 6:
            task->menu->title = "Fireball";
            task->menu->items = lbl_1_data_111A0;
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

// .text:0x00027594 size:0x138
void fn_1_27594(void) {
    Vec dir;
    u8* object = ((u8*)lbl_803CC1B8);
    Vec rest = { 0.0f, 0.0f, 0.0f };
    s32 i;
    u16 flags;
    flags = *(u16*)(object + 0x34);
    if ((flags & 2) || (flags & 4)) {
        i = 1;
        dir.x = 0.0f;
        dir.y = 0.0f;
        dir.z = *(f32*)(object + 0x2C);
        do {
            fn_80030D88((Vec*)(object + 0x20), &dir, &lbl_1_data_10908[i], 5);
            i++;
        } while (i < 3);
        fn_8002F5F4((Vec*)(object + 0x20), &dir, &lbl_1_data_109F8);
        PSVECNormalize(&dir, &dir);
        fn_80030470((Vec*)(object + 0x20), &dir, &rest, lbl_1_data_10908, 5);
        *(u16*)(((u8*)lbl_803CC1B8) + 0x34) ^= 2;
    }
    if (*(u16*)(((u8*)lbl_803CC1B8) + 0x34) & 8) {
        fn_80048BEC(*(void**)(object + 0x1C), 1, 1);
    }
}

// .text:0x00027560 size:0x34
// Points every emitter at the particle texture archive.
void fn_1_27560(struct TexArchive* tex) {
    lbl_1_data_10908[2].tex = tex;
    lbl_1_data_10908[1].tex = tex;
    lbl_1_data_10908[0].tex = tex;
    lbl_1_data_10908[0].texIndex = 7;
    lbl_1_data_10908[1].texIndex = 7;
    lbl_1_data_10908[2].texIndex = 4;
    lbl_1_data_109F8.tex = tex;
}
