#include "game/rep_1C0.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"
#include "Dolphin/mtx.h"
#pragma dont_inline on

typedef struct { u8 b[14]; } Tbl14;
extern u8 lbl_3_rodata_214[];
extern void CTRLBuildMatrix(void*, void*);
extern void DOVARender(void*, void*, int, int);
extern s32 fn_800B7D3C(void*, f32*, void*);
extern u8 lbl_803CBBC0;
extern u32 lbl_3_data_A10[];

extern u32 lbl_3_bss_18[];
extern f32 lbl_3_rodata_504;
extern f32 lbl_3_rodata_524;
extern f32 lbl_3_rodata_528;
extern f32 lbl_3_rodata_52C;
extern f32 lbl_3_rodata_530;
extern f32 lbl_3_rodata_520[];
extern f32 lbl_3_rodata_538[];
extern u8 g_UNK_StadiumDetails[];
extern u32 fn_80009028(void);
extern s32 fn_800527BC(void);
extern void fn_80052694(void*);
extern s32 fn_80052734(s32);
extern void SetFog(u8, s32*, f32, f32, f32, f32);

// .text:0x000035D4 size:0x10
u32 setFanObjPtr(void) {
    return lbl_3_bss_18[0];
}

// .text:0x000035E4 size:0xC
void fn_3_35E4(u32 val) {
    lbl_3_bss_18[0] = val;
}

// .text:0x000035F0 size:0x48
void fn_3_35F0(void) {
    if (fn_80009028() == 0) {
        GXSetCopyClear(*(GXColor*)(g_UNK_StadiumDetails + 0x76C), 0xFFFFFF);
    }
}

// .text:0x00003638 size:0x1E0
// near-match (16 lines): saved regs e/tbl swapped
void fn_3_3638(u8* obj) {
    u8* e;
    u8* pA;
    u8* pB;
    u8* tbl;
    s32 i;
    u8* m26;
    u8* hdr;
    Mtx m;
    f32 pts[24];
    i = 0;
    pA = obj + 8;
    pB = obj + 0x38;
    hdr = *(u8**)(obj + 0x68);
    tbl = *(u8**)(hdr + 0x10);
    e = hdr;
    for (i = 0; i < *(u16*)(hdr + 6); i++, e += 0x1C) {
        u16 idx = *(u16*)(e + 0x34);
        if (idx != 0xFFFF) {
            m26 = *(u8**)(*(u8**)(tbl + 0x10) + idx * 8);
            CTRLBuildMatrix(*(void**)(e + 0x20), m26 + 0x18);
            PSMTXConcat((void*)pA, (void*)(m26 + 0x18), (void*)(m26 + 0x18));
            PSMTXConcat((void*)pB, (void*)(m26 + 0x18), m);
#define F(o) (*(f32*)(m26 + o))
            pts[0] = F(0x58); pts[1] = F(0x60); pts[2] = F(0x64);
            pts[3] = F(0x54); pts[4] = F(0x60); pts[5] = F(0x64);
            pts[6] = F(0x54); pts[7] = F(0x60); pts[8] = F(0x68);
            pts[9] = F(0x58); pts[10] = F(0x60); pts[11] = F(0x68);
            pts[12] = F(0x58); pts[13] = F(0x5C); pts[14] = F(0x64);
            pts[15] = F(0x54); pts[16] = F(0x5C); pts[17] = F(0x64);
            pts[18] = F(0x54); pts[19] = F(0x5C); pts[20] = F(0x68);
            pts[21] = F(0x58); pts[22] = F(0x5C); pts[23] = F(0x68);
            if (fn_800B7D3C(*(void**)(obj + 0x6C), pts, m)) {
                if (*(u16*)(e + 0x3A) & 1) {
                    GXSetZMode(1, 7, 1);
                } else {
                    GXSetZMode(1, 3, 1);
                }
                switch (*(u16*)(e + 0x3A) & 6) {
                case 2:
                    GXSetBlendMode(1, 1, 1, 0);
                    break;
                case 4:
                    GXSetBlendMode(1, 2, 0, 0);
                    break;
                default:
                    GXSetBlendMode(1, 4, 5, 0);
                    break;
                }
                DOVARender(m26, (void*)pB, 0, 0);
            }
        }
    }
}

// .text:0x00003818 size:0xD0
void fn_3_3818(void) {
    s32 i;
    if (lbl_3_data_A10[lbl_803CBBC0 == 0] != 0) {
        i = fn_800527BC() - 1;
        do {
            fn_80052694((void*)i);
            ((void (*)(s32, s32, s32))lbl_3_data_A10[lbl_803CBBC0 == 0])(fn_80052734(i) + 0x40, 0, 0);
        } while (i-- != 0);
        lbl_3_data_A10[lbl_803CBBC0 == 0] = 0;
    }
}

// .text:0x000038E8 size:0x1C
void fn_3_38E8(u32 a) {
    lbl_3_data_A10[lbl_803CBBC0] = a;
}

// .text:0x00003904 size:0x2E4 mapped:0x80642998
void fn_3_3904(void) {
    return;
}

// .text:0x00003BE8 size:0x300 mapped:0x80642C7C
void fn_3_3BE8(void) {
    return;
}

// .text:0x00003EE8 size:0x3E4 mapped:0x80642F7C
void fn_3_3EE8(void) {
    return;
}

// .text:0x000042CC size:0x6B8 mapped:0x80643360
void fn_3_42CC(void) {
    return;
}

// .text:0x00004984 size:0xB4 mapped:0x80643A18
void fn_3_4984(void) {
    Mtx mtx;
    Mtx44 proj;
    GXSetZMode(1, 7, 1);
    GXSetScissor(0, 0, 0x280, 0x1C0);
    C_MTXOrtho(proj, lbl_3_rodata_504, lbl_3_rodata_524, lbl_3_rodata_504, lbl_3_rodata_528, lbl_3_rodata_52C, lbl_3_rodata_530);
    GXSetProjection(proj, 1);
    GXSetCullMode(0);
    PSMTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, 0);
    GXSetCurrentMtx(0);
}

// .text:0x00004A38 size:0x558 mapped:0x80643ACC
void fn_3_4A38(u8 a) {
    return;
}

// .text:0x00004F90 size:0x450 mapped:0x80644024
void fn_3_4F90(void) {
    return;
}

// .text:0x000053E0 size:0x138 mapped:0x80644474
void fn_3_53E0(u16* in, s16* a, s16* b, s16* c, s16* d, s16* e) {
    u16 v = *in;
    if (!(v & 0x4000)) {
        if (v & 0x8000) {
            u16 w = v & 0x7FFF;
            *e = w / 2116;
            w = w % 2116;
            *a = w % 46;
            *b = (w / 46) * 22;
            *a = *a * 22;
            *c = 22;
            *d = 22;
        } else {
            *a = v % 92;
            *b = (v / 92) * 22;
            *a = (*a % 2 + (*a / 2) * 2) * 11;
            *c = 11;
            *d = 22;
            *e = 0;
        }
    }
}

// .text:0x00005518 size:0x164 mapped:0x806445AC
// near-match (6 lines): saved reg assignment sd/off swapped
void fn_3_5518(void) {
    u8* sd;
    s16 tbl[7];
    Mtx44 proj;
    Mtx mtx;
    s32 off;
    void* tex;
    *(Tbl14*)tbl = *(Tbl14*)lbl_3_rodata_214;
    sd = *(u8**)g_UNK_StadiumDetails;
    off = tbl[g_d_GameSettings.StadiumID] << 5;
    GXSetZMode(1, 7, 1);
    GXSetScissor(0, 0, 0x280, 0x1C0);
    C_MTXOrtho(proj, lbl_3_rodata_504, lbl_3_rodata_524, lbl_3_rodata_504, lbl_3_rodata_528, lbl_3_rodata_52C, lbl_3_rodata_530);
    GXSetProjection(proj, 1);
    GXSetCullMode(0);
    PSMTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, 0);
    GXSetCurrentMtx(0);
    GXSetTexCopySrc(0, 0, 0x200, 0x1E0);
    GXSetTexCopyDst(0x200, 0x1E0, 0x20, 0);
    fn_3_4A38(g_d_GameSettings.StadiumID);
    tex = *(void**)(sd + off);
    GXDrawDone();
    GXCopyTex(tex, 1);
    GXPixModeSync();
}

// .text:0x0000567C size:0x530 mapped:0x80644710
void fn_3_567C(void) {
    return;
}

// .text:0x00005BAC size:0x20 mapped:0x80644C40
void fn_3_5BAC(void) {
    fn_3_567C();
}

// .text:0x00005BCC size:0x24 mapped:0x80644C60

void fn_3_5BCC(u8* p) {
    fn_80052694(*(void**)(p + 8));
}

// .text:0x00005BF0 size:0x78 mapped:0x80644C84
void fn_3_5BF0(void) {
    s32 col;
    u8* d = g_UNK_StadiumDetails;
    if (lbl_3_bss_18[0] != 0) {
        ((void (*)(void))lbl_3_bss_18[0])();
    }
    col = *(s32*)(d + 0x714);
    SetFog(d[0x717], &col, *(f32*)(d + 0x718), *(f32*)(d + 0x71C), lbl_3_rodata_520[0], lbl_3_rodata_538[0]);
}

// .text:0x00005C68 size:0x1F8 mapped:0x80644CFC
void fn_3_5C68(void) {
    return;
}


extern u8 lbl_8036E548[];
extern void fn_80035CA4(int);
extern void fn_800BCDBC(void*);
extern void fn_800ACFB0(void*);

// .text:0x00005E60 size:0x60
void fn_3_5E60(void) {
    u8* b = lbl_8036E548;
    u8* p = *(u8**)(b + 4);
    fn_80035CA4(5);
    fn_800BCDBC(p + *(s32*)(p + 0x10));
    fn_800BCDBC(p + *(s32*)(p + 0xC));
    fn_800ACFB0(*(void**)(b + 4));
}

extern u8 lbl_3_data_7EC[];
extern s32 ARAMTransfer(void*, int, int, int);
// .text:0x000064DC size:0x54
void fn_3_64DC(void) {
    ARAMTransfer(lbl_3_data_7EC + (g_d_GameSettings.miniGameStadiumIndicator + g_d_GameSettings.StadiumID * 3) * 16, 0, 0, 0);
}

// .text:0x00006424 size:0xB8
s16 fn_3_6424(u8* base, u8** out) {
    s16 n = *(u16*)base;
    s32 i;
    u32* p;
    *out = base + 4;
    p = (u32*)(base + 4);
    for (i = n; i >= 0; i--) {
        *p += (u32)base;
        p++;
    }
    return n;
}
