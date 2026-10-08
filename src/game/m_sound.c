#include "game/m_sound.h"
#include "header_rep_data.h"

typedef struct SndState34C58 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad20[8];
    u8 unk28;
    u8 pad29[6];
    u8 unk2F;
    u8 pad30[3];
    u8 unk33;
} SndState34C58;
extern SndState34C58 lbl_3_common_bss_34C58;
#define S34C58 lbl_3_common_bss_34C58
#define B34C58 ((u8*)&lbl_3_common_bss_34C58)
extern s32 lbl_3_bss_1780[];
extern u8 lbl_3_common_bss_32B20[];
extern u8 lbl_3_data_8D70[];
extern void sndUpdateListener(void*, void*, void*, void*, void*, s32, s32);
extern u8 lbl_3_common_bss_32B20[];
extern void sndRemoveListener(void*);
extern void fn_800A86B4(int);
extern void fn_800A88C0(void);
extern void fn_800A8B78(void);
extern void OSPanic(const char*, int, const char*, ...);
extern char lbl_3_rodata_1590[];
extern char lbl_3_rodata_15DC[];
extern char lbl_3_rodata_15EC[];
extern u16 lbl_3_data_81FC[];
extern u8 lbl_3_data_84F4[];
extern void* fn_80052734(int);
#include "Dolphin/mtx.h"
extern Vec lbl_3_rodata_1558;
extern Vec lbl_3_rodata_1564;
extern Vec lbl_3_rodata_1570;
extern void sndUpdateEmitter(void*, Vec*, Vec*, u8, void*);
extern u32 sndAddListener(void*, void*, void*, void*, void*, f32, f32, f32, u32, u8, void*);
extern f32 lbl_3_data_88AC;
extern u32 sndCheckEmitter(void*);
extern void sndRemoveEmitter(void*);
extern u8 lbl_3_bss_1760[];
typedef struct Snd1760 { u8 pad0; u8 on; u8 pad2[0xE]; u8 lo; u8 hi; } Snd1760;
extern u16 fn_800A8864(void);
extern void fn_800A8878(u8, u8);
extern s32 fn_3_1650C(int* outX, int* outY, s32 r5, f32 pX, f32 pY, f32 pZ);
extern u8 lbl_3_data_8338[];
extern u8 lbl_800EF808[];

#include "static/UnknownHomes_Static.h"
extern void* lbl_3_bss_1768;
extern void fn_3_8B094(void);
#include "musyx/musyx.h"

void fn_3_902FC(void) {
    sndVolume(0, 10, 0xFF);
}

// .text:0x0008B258 size:0x8C
s32 fn_3_8B258(u8 a, u8 b, u8 c) {
    u8 w;
    if (((u8**)&lbl_3_bss_1768)[0] == NULL || (w = ((u8**)&lbl_3_bss_1768)[0][0x14], ((u8**)&lbl_3_bss_1768)[0][0x15] == (u32)(u8)((w + 1) % 14))) {
        return 0;
    }
    ((u8**)&lbl_3_bss_1768)[0][0x14] = (u32)(u8)((w + 1) % 14);
    ((u8**)&lbl_3_bss_1768)[0][w * 3 + 0x16] = b;
    ((u8**)&lbl_3_bss_1768)[0][w * 3 + 0x17] = a;
    ((u8**)&lbl_3_bss_1768)[0][w * 3 + 0x18] = c;
    return 1;
}

void fn_3_8B2E4(void) {
    lbl_3_bss_1768 = fn_800B0A5C_insertQueue(fn_3_8B094, 0);
}

// .text:0x0008B718 size:0xC4 mapped:0x806CA7AC
void fn_3_8B718(f32* a, f32* b, f32* c) {
    u8* cam = fn_80052734(0);
    if (a != NULL) {
        a[0] = *(f32*)(cam + 0x70);
        a[1] = *(f32*)(cam + 0x74);
        a[2] = *(f32*)(cam + 0x78);
    }
    if (b != NULL) {
        b[0] = 0.0f;
        b[1] = 0.0f;
        b[2] = 0.0f;
    }
    if (c != NULL) {
        PSVECSubtract((Vec*)(cam + 0x7C), (Vec*)(cam + 0x70), (Vec*)c);
        if (PSVECMag((Vec*)c)) {
            PSVECNormalize((Vec*)c, (Vec*)c);
        }
    }
}

// .text:0x0008B7DC size:0x28 mapped:0x806CA870
void fn_3_8B7DC(void) {
    sndRemoveListener(lbl_3_common_bss_32B20);
}

// .text:0x0008B804 size:0x8C mapped:0x806CA898
void fn_3_8B804(void) {
    s32 i;
    for (i = 0; i < 100; i++) {
        if (lbl_3_common_bss_32B20[0x2034 + i] != 0) {
            if (sndCheckEmitter(lbl_3_common_bss_32B20 + 0x90 + i * 0x50) != 0) {
                sndRemoveEmitter(lbl_3_common_bss_32B20 + 0x90 + i * 0x50);
            }
            lbl_3_common_bss_32B20[0x2034 + i] = 0;
        }
    }
}

// .text:0x0008B890 size:0xD4 mapped:0x806CA924
void fn_3_8B890(s32 i) {
    u8* em;
    if (i < 0 || i >= 100 || lbl_3_common_bss_32B20[0x2034 + i] == 0) {
        return;
    }
    em = lbl_3_common_bss_32B20 + 0x90 + i * 0x50;
    if (sndCheckEmitter(em) != 0) {
        Vec pos = lbl_3_rodata_1564;
        Vec dir = lbl_3_rodata_1570;
        sndUpdateEmitter(em, &pos, &dir, 0, 0);
        sndRemoveEmitter(em);
    }
}

// .text:0x0008B964 size:0x58 mapped:0x806CA9F8
void fn_3_8B964(void* a, void* b, void* c) {
    if (*(u32*)(lbl_3_common_bss_32B20 + 8) != 0) {
        sndUpdateListener(lbl_3_common_bss_32B20, a, b, c, lbl_3_data_8D70, 0x7F, 0);
    }
}

// .text:0x0008B9BC size:0xA4 mapped:0x806CAA50
void fn_3_8B9BC(void* pos) {
    f32 head[3];
    f32 dir[3];
    head[0] = 0.0f;
    head[1] = 0.0f;
    head[2] = -1.0f;
    dir[0] = 0.0f;
    dir[1] = 0.0f;
    dir[2] = 0.0f;
    sndRemoveListener(lbl_3_common_bss_32B20);
    sndAddListener(lbl_3_common_bss_32B20, pos, dir, head, lbl_3_data_8D70, lbl_3_data_88AC, lbl_3_data_88AC, lbl_3_data_88AC, 1, 0x7F, 0);
}

// .text:0x0008BA60 size:0x164 mapped:0x806CAAF4
typedef struct SndEm3C { s32 x, y, z; s32 maxd, comp; u32 f14, f18; u32 fl[7]; u32 f38; } SndEm3C;
extern SndEm3C lbl_3_data_8974[];
extern Vec lbl_3_data_8D7C;
void fn_3_8BA60(s32 i, f32* pos, f32* dir) {
    f32 tmp[3];
    u8* em;
    u8 type;
    if (i < 0 || i >= 100 || lbl_3_common_bss_32B20[0x2034 + i] == 0) {
        return;
    }
    em = lbl_3_common_bss_32B20 + i * 0x50 + 0x90;
    if (sndCheckEmitter(em) == 0) {
        lbl_3_common_bss_32B20[0x2034 + i] = 0;
        return;
    }
    type = lbl_3_common_bss_32B20[0x1FD0 + i];
    if (pos == NULL) {
        tmp[0] = lbl_3_data_8974[type].x / 100000.0f;
        tmp[1] = lbl_3_data_8974[type].y / 100000.0f;
        tmp[2] = lbl_3_data_8974[type].z / 100000.0f;
        pos = tmp;
    }
    if (dir == NULL) {
        dir = (f32*)&lbl_3_data_8D7C;
    }
    sndUpdateEmitter(em, (Vec*)pos, (Vec*)dir, lbl_3_data_8974[type].f14, 0);
}

// .text:0x0008BBC4 size:0x230 mapped:0x806CAC58
extern char lbl_3_rodata_159C[];
extern u32 sndAddEmitter(void*, void*, void*, f32, f32, u32, u16, u8, u8, void*);
s32 fn_3_8BBC4(s32 id, f32* pos, f32* dir, s32 type) {
    f32 tmp[3];
    s32 i;
    for (i = 0; i < 100; i++) {
        if (lbl_3_common_bss_32B20[0x2034 + i] == 0 || sndCheckEmitter(lbl_3_common_bss_32B20 + i * 0x50 + 0x90) == 0) {
            lbl_3_common_bss_32B20[0x1FD0 + i] = type;
            lbl_3_common_bss_32B20[0x2034 + i] = 1;
            lbl_3_common_bss_32B20[0x2098 + i] = 0;
            if (pos == NULL) {
                tmp[0] = lbl_3_data_8974[type].x / 100000.0f;
                tmp[1] = lbl_3_data_8974[type].y / 100000.0f;
                tmp[2] = lbl_3_data_8974[type].z / 100000.0f;
                pos = tmp;
            }
            if (dir == NULL) {
                dir = (f32*)&lbl_3_data_8D7C;
            }
            sndAddEmitter(lbl_3_common_bss_32B20 + i * 0x50 + 0x90, pos, dir,
                          lbl_3_data_8974[type].maxd / 100000.0f, lbl_3_data_8974[type].comp / 100000.0f,
                          lbl_3_data_8974[type].fl[0] | lbl_3_data_8974[type].fl[1] | lbl_3_data_8974[type].fl[2] |
                              lbl_3_data_8974[type].fl[3] | lbl_3_data_8974[type].fl[4] | lbl_3_data_8974[type].fl[5] |
                              lbl_3_data_8974[type].fl[6],
                          (u16)id, lbl_3_data_8974[type].f14, lbl_3_data_8974[type].f18, 0);
            return i;
        }
    }
    if (i == 100) {
        OSPanic(lbl_3_rodata_1590, 0xE4C, lbl_3_rodata_159C);
    }
    return -1;
}

// .text:0x0008BDF4 size:0x98 mapped:0x806CAE88
void fn_3_8BDF4(void) {
    fn_3_8B804();
    fn_3_8B7DC();
}

// .text:0x0008BE8C size:0x1F0 mapped:0x806CAF20
void fn_3_8BE8C(void) {
    Vec pos = lbl_3_rodata_1558;
    s32 i;
    for (i = 0; i < 100; i++) {
        lbl_3_common_bss_32B20[0x1FD0 + i] = 0xFF;
        lbl_3_common_bss_32B20[0x2034 + i] = 0;
        lbl_3_common_bss_32B20[0x2098 + i] = 0;
    }
    lbl_3_common_bss_32B20[0x20FC] = 0xFF;
    lbl_3_common_bss_32B20[0x20FD] = 0;
    fn_3_8B9BC(&pos);
    fn_3_8B804();
}

// .text:0x0008C07C size:0x88 mapped:0x806CB110
typedef struct SndQ1768 {
    u8 pad[0x14];
    u8 head;
    u8 tail;
    struct { u8 a, b, c; } e[14];
} SndQ1768;
void fn_3_8C07C(void) {
    SndQ1768** pp = (SndQ1768**)&lbl_3_bss_1768;
    u8 cur;
    u8 next;
    if (*pp != NULL) {
        cur = (*pp)->head;
        if ((*pp)->tail != (next = (cur + 1) % 14)) {
            (*pp)->head = next;
            (*pp)->e[cur].a = 0;
            (*pp)->e[cur].b = 4;
            (*pp)->e[cur].c = 0;
        }
    }
}

// .text:0x0008C104 size:0x1D8 mapped:0x806CB198
extern u8 lbl_800E88A4[][2];
extern u8 g_GameLogic[];
void fn_3_8C104(s32 v) {
    u8 b;
    u32 a;
    u32 j = 0;
    if (lbl_800EF808[0x398] == 0) {
        return;
    }
    if (v == -2) {
        j = 1;
    }
    if (g_d_GameSettings.GameModeSelected == 6) {
        a = 9;
        b = lbl_800E88A4[9][j];
    } else if (g_GameLogic[0x11E] == 0x24) {
        a = 7;
        b = lbl_800E88A4[7][j];
    } else if (*(s16*)(B34C58 + 0x20) == 0x16) {
        a = 6;
        b = lbl_800E88A4[6][j];
    } else if (*(s16*)(B34C58 + 0x20) == 0x17) {
        a = 0xE;
        b = lbl_800E88A4[0xE][j];
    } else if (g_GameLogic[0x11E] == 0xE) {
        a = 7;
        b = lbl_800E88A4[7][j];
    } else if (g_GameLogic[0x11E] == 0x17) {
        a = 8;
        b = lbl_800E88A4[8][j];
    } else {
        a = g_d_GameSettings.StadiumID;
        b = lbl_800E88A4[a][j];
    }
    if (v >= 0) {
        b = v;
    }
    {
        SndQ1768** pp = (SndQ1768**)&lbl_3_bss_1768;
        u8 cur;
        u8 next;
        if (*pp != NULL) {
            cur = (*pp)->head;
            if ((*pp)->tail != (next = (cur + 1) % 14)) {
                (*pp)->head = next;
                (*pp)->e[cur].a = a;
                (*pp)->e[cur].b = 0;
                (*pp)->e[cur].c = b;
            }
        }
    }
    if ((u8)b == 0) {
        fn_800A8878(b, b);
    }
}

// .text:0x0008C2DC size:0x214 mapped:0x806CB370
extern f32 lbl_3_bss_1764;
extern f32 lbl_3_bss_176C;
s32 fn_3_8C2DC(u32 div, u8 k) {
    u16 v;
    f32 hi;
    v = fn_800A8864();
    if (g_d_GameSettings.GameModeSelected == 6) {
        k = lbl_800E88A4[9][k];
    } else if (*(s16*)(B34C58 + 0x20) == 0x16) {
        k = lbl_800E88A4[6][k];
    } else if (g_GameLogic[0x11E] == 0xE) {
        k = lbl_800E88A4[7][k];
    } else if (g_GameLogic[0x11E] == 0x17) {
        k = lbl_800E88A4[8][k];
    } else {
        k = lbl_800E88A4[g_d_GameSettings.StadiumID][k];
    }
    hi = (s32)((v >> 8) & 0xFF);
    if (hi > lbl_3_bss_1764) {
        lbl_3_bss_1764 = hi;
    }
    if (S34C58.unk2F == 0) {
        lbl_3_bss_176C = (f32)k / (f32)div;
        S34C58.unk2F = 1;
        lbl_3_bss_1764 = hi;
    }
    lbl_3_bss_1764 += lbl_3_bss_176C;
    fn_800A8878((u8)lbl_3_bss_1764, (u8)lbl_3_bss_1764);
    if (lbl_3_bss_1764 >= (f32)k) {
        S34C58.unk2F = 0;
        return 0;
    }
    return 1;
}

// .text:0x0008C4F0 size:0xD8 mapped:0x806CB584
s32 fn_3_8C4F0(u32 div, u8 lim) {
    Snd1760* st = (Snd1760*)lbl_3_bss_1760;
    u16 v;
    u8 hi;
    u8 lo;
    v = fn_800A8864();
    S34C58.unk2F = 0;
    hi = (v >> 8) & 0xFF;
    lo = v & 0xFF;
    if (st->on == 0) {
        st->on = 1;
        st->hi = hi / div;
        st->lo = lo / div;
    }
    if ((s16)(hi - st->hi) <= lim || div == 1) {
        st->on = 0;
        fn_800A8878(lim, lim);
        return 0;
    }
    fn_800A8878(hi - st->hi, lo - st->lo);
    return 1;
}

// .text:0x0008C5C8 size:0x7AC mapped:0x806CB65C
void fn_3_8C5C8(void) {
    return;
}

// .text:0x0008CD74 size:0xC4C mapped:0x806CBE08
void fn_3_8CD74(void) {
    return;
}

// .text:0x0008D9C0 size:0xC0 mapped:0x806CCA54
void fn_3_8D9C0(void) {
    f32 pos[3];
    f32 up[3];
    Vec dir;
    u8* cam;
    ((void (*)(void))fn_3_8CD74)();
    cam = fn_80052734(0);
    pos[0] = *(f32*)(cam + 0x70);
    pos[1] = *(f32*)(cam + 0x74);
    pos[2] = *(f32*)(cam + 0x78);
    up[0] = 0.0f;
    up[1] = 0.0f;
    up[2] = 0.0f;
    PSVECSubtract((Vec*)(cam + 0x7C), (Vec*)(cam + 0x70), &dir);
    if (PSVECMag(&dir)) {
        PSVECNormalize(&dir, &dir);
    }
    if (*(u32*)(lbl_3_common_bss_32B20 + 8) != 0) {
        sndUpdateListener(lbl_3_common_bss_32B20, pos, up, &dir, lbl_3_data_8D70, 0x7F, 0);
    }
}

// .text:0x0008DA80 size:0x1748 mapped:0x806CCB14
void fn_3_8DA80(void) {
    return;
}

// .text:0x0008F1C8 size:0x54 mapped:0x806CE25C
void fn_3_8F1C8(void) {
    *(s16*)(B34C58 + 0x20) = -1;
    *(s16*)(B34C58 + 0x22) = -1;
    B34C58[0x29] = 0;
    B34C58[0x2A] = 0;
    lbl_3_bss_1768 = fn_800B0A5C_insertQueue(fn_3_8B094, 0);
}

// .text:0x0008F21C size:0x9F0 mapped:0x806CE2B0
void fn_3_8F21C(void) {
    return;
}

// .text:0x0008FC0C size:0x74 mapped:0x806CECA0
void fn_3_8FC0C(void) {
    B34C58[0x26] = 0;
    if (*(u32*)(B34C58 + 0x10) != 0xFFFFFFFF) {
        sndFXKeyOff(*(u32*)(B34C58 + 0x10));
        *(s32*)(B34C58 + 0x10) = -1;
    }
    if (*(u32*)(B34C58 + 0x14) != 0xFFFFFFFF) {
        sndFXKeyOff(*(u32*)(B34C58 + 0x14));
        *(s32*)(B34C58 + 0x14) = -1;
    }
}

// .text:0x0008FC80 size:0x298 mapped:0x806CED14
extern u8 g_Ball[];
extern u8 g_Practice[];
extern s16 lbl_3_data_88B8[];
extern f32 lbl_3_rodata_1604;
extern f32 lbl_3_rodata_1608;
extern f32 lbl_3_rodata_160C;
extern f32 lbl_3_rodata_157C;
void fn_3_8FC80(void) {
    u8 st = g_GameLogic[0x121];
    if ((st == 0 || (u8)(st - 0xB) <= 4 || st == 0x10)
        && (g_d_GameSettings.GameModeSelected != 2 || (g_Practice[0x19F] == 0 && g_Practice[0x196] != 0))
        && g_GameLogic[0x11E] == 2
        && *(f32*)(g_Ball + 0x4) > lbl_3_rodata_1604
        && *(f32*)(g_Ball + 0x19D4) > lbl_3_rodata_1608
        && (!(*(f32*)(g_Ball + 0x4) < lbl_3_rodata_160C) || !(*(f32*)(g_Ball + 0x31C) < lbl_3_rodata_157C))
        && *(s16*)(g_Ball + 0x1B96) == 0
        && g_Ball[0x1BF4] == 0
        && g_Ball[0x1BD1] == 0
        && *(s16*)(g_Ball + 0x1B7A) != 1
        && !(*(s16*)(g_Ball + 0x1B7A) == 2 || *(s16*)(g_Ball + 0x1B7A) == 3)) {
        s32 v;
        s32 r;
        f32 f;
        if ((u32)S34C58.unk18 == 0xFFFFFFFF) {
            u32 vid = playSoundEffect(0x17F);
            S34C58.unk18 = vid;
            sndFXCtrl(vid, 7, lbl_3_data_88B8[4]);
        }
        r = *(f32*)(g_Ball + 0x4);
        v = r;
        if (r > lbl_3_data_88B8[3]) {
            v = lbl_3_data_88B8[3];
        }
        v -= lbl_3_data_88B8[2];
        f = (f32)v / (f32)(lbl_3_data_88B8[3] - lbl_3_data_88B8[2]);
        sndFXCtrl14(S34C58.unk18, 0x80, lbl_3_data_88B8[0] + (s32)(f * (f32)(lbl_3_data_88B8[1] - lbl_3_data_88B8[0])));
    } else {
        if ((u32)S34C58.unk18 != 0xFFFFFFFF) {
            sndFXKeyOff(S34C58.unk18);
            S34C58.unk18 = -1;
        }
    }
}

// .text:0x0008FF18 size:0x44 mapped:0x806CEFAC
void fn_3_8FF18(void) {
    S34C58.unkC = -1;
    S34C58.unk10 = -1;
    S34C58.unk14 = -1;
    S34C58.unk18 = -1;
    S34C58.unk1C = -1;
    S34C58.unk28 = 0;
    lbl_3_bss_1780[0] = -1;
    S34C58.unk4 = -1;
    S34C58.unk8 = -1;
    S34C58.unk2F = 0;
    S34C58.unk33 = 0;
}

// .text:0x0008FF5C size:0x108 mapped:0x806CEFF0
u32 fn_3_8FF5C(s32 id, f32 x, f32 y, f32 z) {
    int sx;
    int sy;
    u32 pan = 0x3F;
    u32 vid;
    if (lbl_800EF808[0x396] == 1) {
        fn_3_1650C(&sx, &sy, 1, x, -y, z);
        if (sx < 0) {
            pan = 0;
        } else if (sx > 640) {
            pan = 0x7F;
        } else {
            pan = (s32)(127.0f * ((f32)sx / 640.0f));
        }
    }
    vid = sndFXStartEx(id, lbl_3_data_8338[id * 2 - 0x2A2], pan, 0);
    sndFXCtrl(vid, 0x5B, lbl_3_data_8338[id * 2 - 0x2A1]);
    return vid;
}

// .text:0x00090064 size:0xEC mapped:0x806CF0F8
void fn_3_90064(s32 id) {
    s32 i;
    if (g_d_GameSettings.GameModeSelected != 7) {
        OSPanic(lbl_3_rodata_1590, 0x402, lbl_3_rodata_15DC);
    }
    for (i = 0; i < 0x39; i++) {
        if (id == lbl_3_data_81FC[i]) {
            break;
        }
    }
    if (i == 0x39) {
        OSPanic(lbl_3_rodata_1590, 0x40D, lbl_3_rodata_15EC);
    }
    sndFXStartEx((u16)id, lbl_3_data_84F4[i], 0x3F, 0);
}

// .text:0x00090150 size:0xD0 mapped:0x806CF1E4
extern u8 lbl_3_data_8148[];
u32 fn_3_90150(s32 a, s32 b) {
    u8* d = lbl_3_data_8148;
    u8* t = d + 0x3E8;
    u8 v1 = (s32)((f32)t[b] * *(f32*)(d + 0x6E8));
    u8 v2 = (s32)((f32)t[b + 0x180] * *(f32*)(d + 0x6E8));
    u32 h = sndFXStartEx((u16)(b + ((u16*)(d + 0x20))[a]), v1, 0x3F, 0);
    sndFXCtrl(h, 0x5B, v2);
    return h;
}


extern u16 lbl_3_data_8168[];
extern u8 lbl_3_data_8530[];
extern u8 lbl_3_data_8338[];
extern u32 sndSeqGetValid(u32);
extern u32 sndSeqPlayEx(u16 sgid, u16 sid, void* arrfile, void* para, u8 studio);
extern u32* lbl_3_bss_1774;
extern u8 lbl_3_data_88E0[];
extern u8 lbl_3_data_830C[];
extern u8 lbl_3_data_8148[];
extern u8 lbl_800EF808[];
extern void sndSeqVolume(u8 volume, u16 time, u32 seqId, u8 mode);

// .text:0x00090220 size:0x74 mapped:0x806CF2B4
u32 fn_3_90220(s32 idx, s32 off) {
    u32 id = off + lbl_3_data_8168[idx];
    u32 vol = lbl_3_data_8530[off];
    u32 ctrl = lbl_3_data_8530[off + 0x180];
    u32 vid = sndFXStartEx(id, vol, 0x3F, 0);
    sndFXCtrl(vid, 0x5B, ctrl);
    return vid;
}

// .text:0x00090294 size:0x68 mapped:0x806CF328
u32 playSoundEffect(s32 id) {
    u32 vid = sndFXStartEx(id, lbl_3_data_8338[id * 2 - 0x2A2], 0x3F, 0);
    sndFXCtrl(vid, 0x5B, lbl_3_data_8338[id * 2 - 0x2A1]);
    return vid;
}

// .text:0x00090328 size:0x90 mapped:0x806CF3BC
void fn_3_90328(s32 vol) {
    if (vol < 0) {
        vol = 3000;
    }
    {
        SndState34C58* s = &S34C58;
        if (sndSeqGetValid(s->unk4)) {
            sndSeqVolume(0, vol, s->unk4, 1);
        }
    }
    {
        SndState34C58* s = &S34C58;
        if (sndSeqGetValid(s->unk8)) {
            sndSeqVolume(0, vol, s->unk8, 1);
        }
    }
}

// .text:0x000903B8 size:0x7C mapped:0x806CF44C
void fn_3_903B8(void) {
    SndState34C58* s = &S34C58;
    if (sndSeqGetValid(s->unk4)) {
        sndSeqVolume(0, 0xA0, s->unk4, 1);
    }
    s = &S34C58;
    if (sndSeqGetValid(s->unk8)) {
        sndSeqVolume(0, 0xA0, s->unk8, 1);
    }
}

// .text:0x00090434 size:0x138
void fn_3_90434(void) {
    SndState34C58* s;
    s32 i;
    fn_800A86B4(3);
    fn_800A88C0();
    fn_800A8B78();
    s = &S34C58;
    if (sndSeqGetValid(s->unk4)) {
        sndSeqVolume(0, 0, s->unk4, 1);
    }
    s = &S34C58;
    if (sndSeqGetValid(s->unk8)) {
        sndSeqVolume(0, 0, s->unk8, 1);
    }
    for (i = 0; i < 3; i++) {
        if (*(u32*)(B34C58 + 0xC + i * 4) != 0xFFFFFFFF) {
            sndFXKeyOff(*(u32*)(B34C58 + 0xC + i * 4));
            *(s32*)(B34C58 + 0xC + i * 4) = -1;
        }
    }
    fn_3_8BDF4();
}

// .text:0x00090674 size:0x88 mapped:0x806CF708
void fn_3_90674(s32 idx) {
    u16* e = (u16*)(lbl_3_data_88E0 + idx * 6);
    S34C58.unk4 = sndSeqPlayEx(e[0], e[1], (void*)lbl_3_bss_1774[idx], 0, 0);
    sndSeqVolume(lbl_3_data_830C[idx * 2], 0, S34C58.unk4, 0);
}

// .text:0x000906FC size:0x58 mapped:0x806CF790
void fn_3_906FC(void) {
    u32* p;
    u32 base;
    s32 i;
    base = S34C58.unk0;
    p = (u32*)base;
    for (i = 0; i < (g_d_GameSettings.GameModeSelected == 2 ? 1 : 0x14); i++) {
        *p += base;
        p++;
    }
    lbl_3_bss_1774 = (u32*)base;
}

// .text:0x0009056C size:0x108 mapped:0x806CF600
typedef struct { u16 a, b, c; } SeqEnt6;
typedef struct { u8 v, pad; } SeqVol2;
u32 fn_3_9056C(s32 idx) {
    u8* d = lbl_3_data_8148;
    SeqEnt6* e;
    SndState34C58* s;
    u8 vol;
    u32 seq;
    if (g_d_GameSettings.GameModeSelected != 2) {
        e = &((SeqEnt6*)(d + 0x798))[idx];
    } else {
        e = &((SeqEnt6*)(d + 0x80C))[idx];
    }
    s = &S34C58;
    if (sndSeqGetValid(s->unk8)) {
        sndSeqVolume(0, 0, s->unk8, 1);
        return 0;
    }
    seq = sndSeqPlayEx(e->a, e->b, (void*)lbl_3_bss_1774[idx], 0, 0);
    vol = ((SeqVol2*)(d + 0x1C4))[idx].v;
    s->unk8 = seq;
    lbl_800EF808[0x391] = vol;
    sndSeqVolume(vol, 0, seq, 0);
    return 1;
}
