#include "Unknown/auto_03_8002244C_text.h"

extern u8 lbl_803716B8[];
extern u8 lbl_800EFD38[];

typedef struct {
    void* a;
    void* end;
    s32 mode;
    s32 v;
    void (*cb)(void);
    s32 z;
} QEntry8002;

// fn_80022620, size:0x14
void fn_80022620(void) {
    *(u8*)(lbl_803716B8 + 0x1e8) = 0x0;
}

// fn_8002244C, size:0x100
void fn_8002244C(s32 unused, s32* hdr, s32 arg) {
    s32 v;
    s8 next;
    s32 h;
    s32 len = (*(u32*)(lbl_800EFD38 + ((arg >> 16) + 0x36) * 16 + 4) & 0x0FFFFFFF);
    len = (len + 0x1F) & ~0x1F;
    hdr[3] = len;
    hdr = (s32*)(len + (u32)hdr);
    v = *(s32*)(*(u8**)(lbl_803716B8 + 0x1DC) + (u16)arg * 4);
    h = (s8)lbl_803716B8[0x1C8];
    next = (h + 1) % 18;
    if (next == (s8)lbl_803716B8[0x1C9]) {
        return;
    }
    if (hdr == NULL && fn_80022620 == NULL) {
        return;
    }
    {
        QEntry8002* e;
        lbl_803716B8[0x1CA] = 1;
        e = (QEntry8002*)(lbl_803716B8 + (s8)lbl_803716B8[0x1C8] * 0x18) + 1;
        e->a = lbl_800EFD38 + ((u16)arg + 0x36) * 16;
        e->end = hdr;
        e->mode = 3;
        e->v = v;
        e->cb = fn_80022620;
        e->z = 0;
        lbl_803716B8[0x1C8] = next;
    }
}
