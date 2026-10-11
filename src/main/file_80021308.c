#include "main/file_80021308.h"

// .text:0x80021308 size:0xEC
void fn_80021308(void) {
    return;
}

extern u8* lbl_803CBC40;

// fn_800213F4, size:0x4
void fn_800213F4(void) {
}

// fn_800213F8, size:0x18
void* fn_800213F8(u32 size) {
    void* result = lbl_803CBC40;
    lbl_803CBC40 += (size + 31) & ~31;
    return result;
}

// .text:0x80021410 size:0x8C
void fn_80021410(void) {
    return;
}

// .text:0x8002149C size:0x34
void fn_8002149C(void) {
    return;
}

// .text:0x800214D0 size:0x48
void fn_800214D0(void) {
    return;
}

// .text:0x80021518 size:0x74
void fn_80021518(void) {
    return;
}

// .text:0x8002158C size:0x6C
void fn_8002158C(void) {
    return;
}

// .text:0x800215F8 size:0x58
void fn_800215F8(void) {
    return;
}

// .text:0x80021650 size:0xA8
void fn_80021650(void) {
    return;
}

// .text:0x800216F8 size:0x60
void fn_800216F8(void) {
    return;
}

// .text:0x80021758 size:0x1FC
void fn_80021758(void) {
    return;
}

// .text:0x80021954 size:0x2C
void fn_80021954(void) {
    return;
}

// .text:0x80021980 size:0x34
void fn_80021980(void) {
    return;
}

// .text:0x800219B4 size:0xEC
void f_initSound(void) {
    return;
}

// .text:0x80021AA0 size:0x20
void fn_80021AA0(void) {
    return;
}

extern u8 lbl_803716B8[];

// fn_80021AC0, size:0x4
void fn_80021AC0(void) {
}

// fn_80021AC4, size:0x4
void fn_80021AC4(void) {
}

// fn_80021AC8, size:0x14
void fn_80021AC8(void) {
    *(u32*)(lbl_803716B8 + 0x55c) = 0x0;
}

// .text:0x80021ADC size:0xE0
void fn_80021ADC(void) {
    return;
}

// .text:0x80021BBC size:0xE8
void fn_80021BBC(void) {
    return;
}

// .text:0x80021CA4 size:0x3A8
void fn_80021CA4(void) {
    return;
}

// .text:0x8002204C size:0x400
void fn_8002204C(void) {
    return;
}

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

// .text:0x8002254C size:0xD4
void fn_8002254C(void) {
    return;
}

// .text:0x80022634 size:0x16C
void fn_80022634(void) {
    return;
}

// .text:0x800227A0 size:0x44
void fn_800227A0(void) {
    return;
}

// .text:0x800227E4 size:0x1E8
void fn_800227E4(void) {
    return;
}

// .text:0x800229CC size:0x58
void fn_800229CC(void) {
    return;
}

// .text:0x80022A24 size:0xF0
void fn_80022A24(void) {
    return;
}

// .text:0x80022B14 size:0x54
void fn_80022B14(void) {
    return;
}

// .text:0x80022B68 size:0x14C
void fn_80022B68(void) {
    return;
}

// .text:0x80022CB4 size:0xA4
void fn_80022CB4(void) {
    return;
}

// .text:0x80022D58 size:0x54
void fn_80022D58(void) {
    return;
}
