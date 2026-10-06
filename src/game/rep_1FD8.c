#include "game/rep_1FD8.h"
#include "header_rep_data.h"

#include "static/UnknownHomes_Static.h"
extern void fn_3_C2644(void);
extern void CTRLBuildMatrix(void*);
extern u8* lbl_3_bss_9D98;
extern u8* lbl_3_common_bss_350E4[];
extern void fn_3_B8184(void);
extern void fn_3_B828C(void*);
extern void fn_800BF058(void*);
extern void fn_800BDF70(void*);
extern u32 lbl_3_bss_9D84;
extern u32 fn_80033A24(void*, int, int, int, int, int);

extern u32 lbl_3_bss_9D9C;
extern u32 lbl_3_bss_9D94;
typedef struct DspObj2 DspObj2;
struct DspObj2 {
    u8 pad0[0x14];
    void* w14;
    u8 pad18[0x4C];
    void* w64;
    void* w68;
    u8 pad6C[8];
    DspObj2* child;
    u8 pad78[4];
    void* w7C;
    u8 pad80[0x6C];
    void* wEC;
    u8 padF0[0x10];
    DspObj2* next;
};
extern void DOSetWorldMatrix(void*, void*);
extern void DOVARenderSkin(void*, void*, void*, void*, int, int);
extern void fn_8003A8A0();
extern u32 lbl_3_bss_9D88;
extern u16 lbl_3_data_177F0;

void fn_3_C1964(void) {
    lbl_3_bss_9D9C = 1;
}

void fn_3_C1974(u8* a) {
    u8* p = fn_800B0A5C_insertQueue(fn_3_C2644, 4);
    *(s16*)(p + 0x10) = 0;
    lbl_3_bss_9D98 = a + 0x3C4;
    lbl_3_bss_9D9C = 0;
}

// .text:0x000C19C8 size:0x250 mapped:0x80700A5C
void fn_3_C19C8(void) {
    return;
}

// .text:0x000C1C18 size:0x62C mapped:0x80700CAC
void fn_3_C1C18(void) {
    return;
}

// .text:0x000C2244 size:0xCC mapped:0x807012D8
void fn_3_C2244(void) {
    return;
}

// .text:0x000C2310 size:0xD0 mapped:0x807013A4
void fn_3_C2310(void* pp, void* cam) {
    Mtx m2;
    Mtx m;
    DspObj2* o;
    DspObj2* n;
    ((void (*)(u32, void*))CTRLBuildMatrix)(lbl_3_bss_9D94, m);
    PSMTXConcat((f32 (*)[4])cam, m, m2);
    o = *(DspObj2**)pp;
    n = o->child;
    if (o->w14 != 0) {
        if (o->w7C != 0) {
            fn_8003A8A0(o->w14, m2, 1);
        } else {
            DOVARenderSkin(o->w14, m2, o->w64, o->w68, 0, 0);
        }
    }
    while (n != 0) {
        if (n->w14 != 0) {
            DOSetWorldMatrix(n->w14, n->wEC);
            fn_8003A8A0(n->w14, m2, 0);
        }
        n = n->next;
    }
}

// .text:0x000C23E0 size:0xC0 mapped:0x80701474
void fn_3_C23E0(void) {
    u8* c;
    int i;
    u8** base;
    fn_800BF058(fn_3_B8184);
    base = lbl_3_common_bss_350E4;
    for (i = 0; i < *(int*)((u8*)base + 0x30); i++) {
        c = *base + i * 0xE8;
        fn_3_B828C(c);
        if (i >= 1 && i < 11) {
            if ((c[0x90] >> 7) & 1) {
                if (*(u8**)(c + 0x74) != 0) {
                    (*(u8**)*(u8**)(c + 0x74))[0x98] = c[0x93] | 6;
                    fn_800BDF70(*(u8**)(c + 0x74));
                }
            }
        }
    }
}

// .text:0x000C24A0 size:0x1A4 mapped:0x80701534
void fn_3_C24A0(void) {
    return;
}

// .text:0x000C2644 size:0x330 mapped:0x807016D8
void fn_3_C2644(void) {
    return;
}

// .text:0x000C2974 size:0x18 mapped:0x80701A08
extern u8 lbl_3_bss_9DE7;
extern u8 lbl_3_bss_9D82;

void fn_3_C2974(void) {
    lbl_3_bss_9DE7 = 1;
    lbl_3_bss_9D82 = 1;
}

// .text:0x000C298C size:0x114 mapped:0x80701A20
void fn_3_C298C(void) {
    return;
}

// .text:0x000C2AA0 size:0x1E0 mapped:0x80701B34
void fn_3_C2AA0(void) {
    return;
}

// .text:0x000C2C80 size:0x25C mapped:0x80701D14
void fn_3_C2C80(void) {
    return;
}

// .text:0x000C2EDC size:0x214 mapped:0x80701F70
void fn_3_C2EDC(void) {
    return;
}

// .text:0x000C30F0 size:0x57C mapped:0x80702184
void fn_3_C30F0(void) {
    return;
}

// .text:0x000C366C size:0x35C mapped:0x80702700
#pragma dont_inline on
void fn_3_C366C(u32 a, u8 b) {
    return;
}
#pragma dont_inline reset

// .text:0x000C39C8 size:0x70 mapped:0x80702A5C
void fn_3_C39C8(void) {
    u32 i = 0;
    do {
        u32 r = fn_80033A24(fn_3_C30F0, 0x80, 0, 0x15, 1, 0);
        if (r != 0) {
            fn_3_C366C(r, i);
        }
        i++;
    } while (i < 6);
}

// .text:0x000C3A38 size:0x1F4 mapped:0x80702ACC
void fn_3_C3A38(void) {
    return;
}

// .text:0x000C3C2C size:0x268 mapped:0x80702CC0
void fn_3_C3C2C(void) {
    return;
}

// .text:0x000C3E94 size:0xDC mapped:0x80702F28
void fn_3_C3E94(void) {
    return;
}

// .text:0x000C3F70 size:0xF8 mapped:0x80703004
void fn_3_C3F70(u8* a) {
    u8* t = **(u8***)(a + 0x74);
    u8* q;
    u32 i;
    u32 j;
    u8* e;
    if (lbl_3_bss_9D88++ > 4) {
        if (++lbl_3_data_177F0 > 0x13) {
            lbl_3_data_177F0 = 4;
        }
        lbl_3_bss_9D88 = 0;
    }
    if (lbl_3_bss_9D88 != 0) {
        return;
    }
    for (i = 0; i < *(u16*)(t + 6); i++) {
        e = ((u8**)*(u8**)(t + 0x18))[i];
        e = *(u8**)(e + 0x14);
        if (e != NULL) {
            q = *(u8**)(*(u8**)(e + 0x10) + 4);
            for (j = 0; j < *(u16*)(*(u8**)(e + 0x10) + 8); j++) {
                if (q[0] == 1) {
                    *(u32*)(q + 4) = *(u32*)(q + 4) & ~0x1FFF;
                    *(u32*)(q + 4) = *(u32*)(q + 4) | lbl_3_data_177F0;
                }
                q += 0x10;
            }
        }
    }
}

// .text:0x000C4068 size:0x84 mapped:0x807030FC
void fn_3_C4068(u8* a) {
    u8* p = **(u8***)(a + 0x74);
    u32 n;
    u32 v;
    u16 t;
    p = *(u8**)(p + 0x18);
    p = *(u8**)(p + 4);
    p = *(u8**)(p + 0x14);
    p = *(u8**)(p + 0x10);
    p = *(u8**)(p + 4);
    n = lbl_3_bss_9D84;
    t = *(u32*)(p + 4) & 0x1FFF;
    lbl_3_bss_9D84 = n + 1;
    v = t;
    if (n > 4) {
        v = t + 1;
        if ((u16)v > 0x13) {
            v = 4;
        }
        lbl_3_bss_9D84 = 0;
    }
    *(u32*)(p + 4) = *(u32*)(p + 4) & ~0x1FFF;
    *(u32*)(p + 4) = *(u32*)(p + 4) | (u16)v;
}

// .text:0x000C40EC size:0x60 mapped:0x80703180
void fn_3_C40EC(u8* a) {
    u8* p = **(u8***)(a + 0x74);
    p = *(u8**)(p + 0x18);
    p = *(u8**)(p + 4);
    p = *(u8**)(p + 0x14);
    p = *(u8**)(p + 0x10);
    p = *(u8**)(p + 4);
    if (a[0xA9] != 6) {
        *(u32*)(p + 4) = *(u32*)(p + 4) & ~0x1FFF;
        *(u32*)(p + 4) = *(u32*)(p + 4) | 0x19;
    } else {
        *(u32*)(p + 4) = *(u32*)(p + 4) & ~0x1FFF;
        *(u32*)(p + 4) = *(u32*)(p + 4) | 0x1A;
    }
}

// .text:0x000C414C size:0x158 mapped:0x807031E0
void fn_3_C414C(void) {
    return;
}

// .text:0x000C42A4 size:0x1A8 mapped:0x80703338
void fn_3_C42A4(void) {
    return;
}

// .text:0x000C444C size:0x2D8 mapped:0x807034E0
void fn_3_C444C(void) {
    return;
}

// .text:0x000C4724 size:0x1AC mapped:0x807037B8
void fn_3_C4724(void) {
    return;
}

// .text:0x000C48D0 size:0x2B0 mapped:0x80703964
void fn_3_C48D0(void) {
    return;
}

// .text:0x000C4B80 size:0x174 mapped:0x80703C14
void fn_3_C4B80(void) {
    return;
}

// .text:0x000C4CF4 size:0x20C mapped:0x80703D88
void fn_3_C4CF4(void) {
    return;
}

// .text:0x000C4F00 size:0x404 mapped:0x80703F94
void fn_3_C4F00(void) {
    return;
}

// .text:0x000C5304 size:0x1CC mapped:0x80704398
void fn_3_C5304(void) {
    return;
}

// .text:0x000C54D0 size:0x218 mapped:0x80704564
void fn_3_C54D0(void) {
    return;
}

// .text:0x000C56E8 size:0x294 mapped:0x8070477C
void fn_3_C56E8(void) {
    return;
}

// .text:0x000C597C size:0x364 mapped:0x80704A10
void fn_3_C597C(void) {
    return;
}

// .text:0x000C5CE0 size:0xFC mapped:0x80704D74
void fn_3_C5CE0(void) {
    return;
}

// .text:0x000C5DDC size:0x480 mapped:0x80704E70
void fn_3_C5DDC(void) {
    return;
}

// .text:0x000C625C size:0x174 mapped:0x807052F0
void fn_3_C625C(void) {
    return;
}

// .text:0x000C63D0 size:0xDFC mapped:0x80705464
void fn_3_C63D0(void) {
    return;
}

// .text:0x000C71CC size:0x278 mapped:0x80706260
void fn_3_C71CC(void) {
    return;
}

// .text:0x000C7444 size:0x58 mapped:0x807064D8
void fn_3_C7444(u8* a) {
    u8* p = **(u8***)(a + 0x74);
    p = *(u8**)(p + 0x18);
    p = *(u8**)(p + 0x34);
    p = *(u8**)(p + 0x14);
    p = *(u8**)(p + 0x10);
    p = *(u8**)(p + 4);
    switch (*(s8*)(a + 0xB0)) {
    case 0:
        *(u32*)(p + 4) = *(u32*)(p + 4) & ~0x1FFF;
        *(u32*)(p + 4) = *(u32*)(p + 4) | 2;
        break;
    default:
        *(u32*)(p + 4) = *(u32*)(p + 4) & ~0x1FFF;
        break;
    }
}

// .text:0x000C749C size:0x11C mapped:0x80706530
void fn_3_C749C(void) {
    return;
}

// .text:0x000C75B8 size:0x1F4 mapped:0x8070664C
void fn_3_C75B8(void) {
    return;
}

// .text:0x000C77AC size:0x260 mapped:0x80706840
void fn_3_C77AC(void) {
    return;
}

// .text:0x000C7A0C size:0x650 mapped:0x80706AA0
void fn_3_C7A0C(void) {
    return;
}

// .text:0x000C805C size:0x1E0 mapped:0x807070F0
void fn_3_C805C(void) {
    return;
}

// .text:0x000C823C size:0x78 mapped:0x807072D0
typedef struct { u8 _0[0x78]; s32 f78; u8 _7C[0xA9 - 0x7C]; u8 fA9; u8 _AA[0xE8 - 0xAA]; } C823CEnt;
s32 fn_3_C823C(s32 idx, f32* out) {
    C823CEnt* p = *(C823CEnt**)&lbl_3_common_bss_350E4 + idx;
    CTRLBuildMatrix(p);
    if (p->fA9 == 5) {
        out[7] = -0.002f;
    }
    return (*(C823CEnt**)&lbl_3_common_bss_350E4 + idx)->f78;
}

// .text:0x000C82B4 size:0x39C mapped:0x80707348
void fn_3_C82B4(void) {
    return;
}

// .text:0x000C8650 size:0xD2C mapped:0x807076E4
void fn_3_C8650(void) {
    return;
}

