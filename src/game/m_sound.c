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
extern u32 sndCheckEmitter(void*);
extern void sndRemoveEmitter(void*);

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
void fn_3_8B718(void) {
    return;
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
void fn_3_8B890(void) {
    return;
}

// .text:0x0008B964 size:0x58 mapped:0x806CA9F8
void fn_3_8B964(void* a, void* b, void* c) {
    if (*(u32*)(lbl_3_common_bss_32B20 + 8) != 0) {
        sndUpdateListener(lbl_3_common_bss_32B20, a, b, c, lbl_3_data_8D70, 0x7F, 0);
    }
}

// .text:0x0008B9BC size:0xA4 mapped:0x806CAA50
void fn_3_8B9BC(void) {
    return;
}

// .text:0x0008BA60 size:0x164 mapped:0x806CAAF4
void fn_3_8BA60(void) {
    return;
}

// .text:0x0008BBC4 size:0x230 mapped:0x806CAC58
void fn_3_8BBC4(void) {
    return;
}

// .text:0x0008BDF4 size:0x98 mapped:0x806CAE88
void fn_3_8BDF4(void) {
    return;
}

// .text:0x0008BE8C size:0x1F0 mapped:0x806CAF20
void fn_3_8BE8C(void) {
    return;
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
void fn_3_8C104(void) {
    return;
}

// .text:0x0008C2DC size:0x214 mapped:0x806CB370
void fn_3_8C2DC(void) {
    return;
}

// .text:0x0008C4F0 size:0xD8 mapped:0x806CB584
void fn_3_8C4F0(void) {
    return;
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
    return;
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
void fn_3_8FC80(void) {
    return;
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
void fn_3_8FF5C(void) {
    return;
}

// .text:0x00090064 size:0xEC mapped:0x806CF0F8
void fn_3_90064(void) {
    return;
}

// .text:0x00090150 size:0xD0 mapped:0x806CF1E4
void fn_3_90150(void) {
    return;
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
    u8* tbl = lbl_3_data_8530;
    u8 ctrl = tbl[off + 0x180];
    u32 vid = sndFXStartEx(off + lbl_3_data_8168[idx], tbl[off], 0x3F, 0);
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
