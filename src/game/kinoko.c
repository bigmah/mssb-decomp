#include "game/kinoko.h"
#include "header_rep_data.h"
#pragma dont_inline on

typedef struct {
    u8* buf;
    void* tex;
    s32 cnt;
} KinokoCtl;
extern KinokoCtl lbl_3_bss_BA00;
extern s32 lbl_3_bss_BA08[];
extern u8 lbl_80366158[];
extern s8 lbl_3_data_2A330;
extern s32 fn_800247E4(s32, s32, s32, s32);
extern void DCFlushRange(void*, u32);

extern void GXLoadTexObj(void*, s32);
extern void GXSetTexCoordGen2(s32, s32, s32, s32, s32, s32);
extern void GXSetTevOrder(s32, s32, s32, s32);
extern void GXSetTevColorIn(s32, s32, s32, s32, s32);
extern void GXSetTevColorOp(s32, s32, s32, s32, s32, s32);
extern void GXSetTevAlphaIn(s32, s32, s32, s32, s32);
extern void GXSetTevAlphaOp(s32, s32, s32, s32, s32, s32);

// .text:0x0016917C size:0x2C0
void fn_3_16917C(s32 unused, s32* stage, s32* coord, s32* map, u8* c1, u8* c2) {
    KinokoCtl* c = &lbl_3_bss_BA00;
    s32 v;
    s32 i;
    s32 t;
    c->cnt += (lbl_80366158[0x28] == 0);
    if ((c->cnt & 1) == 0) {
        v = c->buf[fn_800247E4(0, 0, 4, 4)];
        v += lbl_3_data_2A330 * 2;
        if (v > 0xFF) {
            v = 0xFF;
        } else if (v < 0) {
            v = 0;
        }
        for (i = 0; i < 32; i += 2) {
            c->buf[i] = v;
        }
        DCFlushRange(c->buf, 4);
        t = v + lbl_3_data_2A330 * 2;
        if (t > 0xFF || t < 0) {
            lbl_3_data_2A330 *= -1;
        }
    }
    GXLoadTexObj(c->tex, *map);
    GXSetTexCoordGen2(*coord, 1, 4, 0x3C, 0, 0x7D);
    GXSetTevOrder(*stage, *coord, *map, 0xFF);
    if (c->buf == (u8*)c + 0xA0) {
        GXSetTevColorIn(*stage, 0, 8, 9, 0xF);
        GXSetTevColorOp(*stage, 0, 0, 0, 1, 0);
        GXSetTevAlphaIn(*stage, 7, 7, 7, 0);
        GXSetTevAlphaOp(*stage, 0, 0, 0, 1, 0);
    } else {
        GXSetTevColorIn(*stage, 0xF, 8, 9, 0);
        GXSetTevColorOp(*stage, 0, 0, 0, 1, 0);
        GXSetTevAlphaIn(*stage, 7, 7, 7, 0);
        GXSetTevAlphaOp(*stage, 0, 0, 0, 1, 0);
    }
    *stage += 1;
    *coord += 1;
    *map += 1;
    *c1 += 1;
    *c2 += 1;
}

// .text:0x0016943C size:0x164
void fn_3_16943C(void) {
    s32 v;
    s32 i;
    s32 t;
    lbl_3_bss_BA08[0] += (lbl_80366158[0x28] == 0);
    if ((lbl_3_bss_BA08[0] & 1) == 0) {
        v = lbl_3_bss_BA00.buf[fn_800247E4(0, 0, 4, 4)];
        v += lbl_3_data_2A330 * 2;
        if (v > 0xFF) {
            v = 0xFF;
        } else if (v < 0) {
            v = 0;
        }
        for (i = 0; i < 32; i += 2) {
            lbl_3_bss_BA00.buf[i] = v;
        }
        DCFlushRange(lbl_3_bss_BA00.buf, 4);
        t = v + lbl_3_data_2A330 * 2;
        if (t > 0xFF || t < 0) {
            lbl_3_data_2A330 *= -1;
        }
    }
}

// .text:0x001695A0 size:0x4
void fn_3_1695A0(void) {
}

extern void fn_80011604(s32, void*);

// .text:0x001695A4 size:0x5C
void fn_3_1695A4(s32 a, u8 flag) {
    u8* p = (u8*)&lbl_3_bss_BA00;
    if (flag == 0) {
        *(u8**)p = p + 0xA0;
        *(u8**)(p + 4) = p + 0x2C;
    } else {
        *(u8**)p = p + 0x60;
        *(u8**)(p + 4) = p + 0xC;
    }
    fn_80011604(a, fn_3_16917C);
}

extern u8 lbl_3_data_28928[];
extern u8 lbl_3_bss_BAE0[];
extern void fn_3_16A07C(void);
extern void* memset(void*, s32, u32);
extern void* fn_800B0A5C_insertQueue(void*, s32);

// .text:0x0016C394 size:0x7C
void fn_3_16C394(s8 a) {
    memset(lbl_3_data_28928, 0, 0x19E0);
    memset(lbl_3_bss_BAE0, 0, 0x1BF0);
    lbl_3_data_28928[0x19DC] = a;
    lbl_3_data_28928[0x19DD] = 1;
    *(s32*)(lbl_3_data_28928 + 0x19D4) = 1;
    fn_3_16B884();
    fn_800B0A5C_insertQueue(fn_3_16A07C, 0);
}

extern char lbl_3_rodata_4050[];
extern char lbl_3_rodata_405C[];
extern s32 fn_8001B728(s32, s32, void*);
extern void OSPanic(const char*, int, const char*, ...);

// .text:0x0016B488 size:0x12C
void fn_3_16B488(void* out, s8 id) {
    if (out == NULL) {
        OSPanic(lbl_3_rodata_4050, 0x11C, lbl_3_rodata_405C);
    }
    memset(out, 0, 0xC);
    if (fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], id, out) == 0) {
        switch (id) {
        case 28:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x1E, out);
            break;
        case 32:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x22, out);
            break;
        case 7:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 5, out);
            break;
        case 18:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x13, out);
            break;
        case 24:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x19, out);
            break;
        }
    }
}

// .text:0x00169600 size:0x204 mapped:0x807A8694
void fn_3_169600(void) {
    return;
}

// .text:0x00169804 size:0x180 mapped:0x807A8898
void fn_3_169804(void) {
    return;
}

// .text:0x00169984 size:0x37C mapped:0x807A8A18
void fn_3_169984(void) {
    return;
}

// .text:0x00169D00 size:0x170 mapped:0x807A8D94
void fn_3_169D00(void) {
    return;
}

// .text:0x00169E70 size:0x20C mapped:0x807A8F04
void fn_3_169E70(void) {
    return;
}

// .text:0x0016A07C size:0x140C mapped:0x807A9110
void fn_3_16A07C(void) {
    return;
}

// .text:0x0016B5B4 size:0x2D0 mapped:0x807AA648
void fn_3_16B5B4(void) {
    return;
}

// .text:0x0016B884 size:0xB10 mapped:0x807AA918
void fn_3_16B884(void) {
    return;
}

