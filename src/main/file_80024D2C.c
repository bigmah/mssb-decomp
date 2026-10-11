#include "main/file_80024D2C.h"
#include "Dolphin/stl.h"

extern u8 lbl_803CBBC0; // current frame buffer (0/1)
extern s32 lbl_803CBC68;
extern ShapeSeqHdr lbl_803CB7F0; // default sequence: {100, 2}
extern ShapeKey* lbl_803CB7F4;   // default sequence keys
extern void DCFlushRangeNoSync(void* addr, u32 nBytes);

static inline s32 shapeDirtyA(ShapeAnimState* st) {
    return st != NULL ? st->dirtyA & (1 << (lbl_803CBBC0 != 0)) : 0;
}

static inline s32 shapeDirtyB(ShapeAnimState* st) {
    return st != NULL ? st->dirtyB & (1 << (lbl_803CBBC0 != 0)) : 0;
}

static inline void shapeSetDirtyA(ShapeAnimState* st) {
    if (st != NULL) {
        st->dirtyA = 3;
    }
}

static inline void shapeSetDirtyB(ShapeAnimState* st) {
    if (st != NULL) {
        st->dirtyB = 3;
    }
}

static inline void shapeStateReset(ShapeAnimState* st) {
    if (st != NULL) {
        st->frame = 0.0f;
        st->speed = 0.5f;
        st->unk8 = 1;
        st->seqIdx = 0;
        st->keyIdx = 0;
        st->loops = -1;
        st->unk10 = 1;
        st->unk14 = 0;
    }
}

// .text:0x80024D2C size:0x84
// Flags (top nibble) of the last key at or before the current frame.
u32 fn_80024D2C(ShapeAnimState* st) {
    ShapeSeq* seq = &st->seqs[st->seqIdx];
    s32 i = seq->hdr.keyCount;

    while (i-- != 0) {
        if ((f32)seq->keys[i].frame <= st->frame) {
            return *(u32*)&seq->keys[i] & 0xF0000000;
        }
    }
    return 0;
}

// .text:0x80024DB0 size:0x1F4
void fn_80024DB0(void) {
    return;
}

// .text:0x80024FA4 size:0xCB4
void fn_80024FA4(void) {
    return;
}

// .text:0x80025C58 size:0x184
void fn_80025C58(void) {
    return;
}

// fn_80026130, size:0x4
void fn_80026130(void) {
}

// fn_80025DDC, size:0x110
void fn_80025DDC(u8* h) {
    u8* q;
    s32 off;
    u8* p;
    u8* e;
    s32 i;
    s32 j;
    s32 k;
    *(u32*)(h + 0x10) = 0;
    if (*(u32*)(h + 0xC) != 0) {
        *(u32*)(h + 0xC) = (u32)h + *(u32*)(h + 0xC);
    }
    if (*(u32*)(h + 8) != 0) {
        *(u32*)(h + 8) = (u32)h + *(u32*)(h + 8);
    }
    if (*(u32*)(h + 8) != 0) {
        i = 0;
        off = 0;
        for (; i < *(u16*)(h + 2); i++) {
            e = *(u8**)(h + 8) + off;
            *(u32*)(e + 8) = (u32)h + *(u32*)(e + 8);
            p = *(u8**)(e + 8);
            for (j = 0; j < *(u16*)(e + 2); j++) {
                *(u32*)(p + 8) = (u32)h + *(u32*)(p + 8);
                q = p;
                for (k = 0; k < *(u16*)(e + 0); k++) {
                    *(u32*)(q + 0xC) = (u32)h + *(u32*)(q + 0xC);
                    q += 4;
                }
                p += *(u32*)(e + 4);
            }
            off += 0xC;
        }
    }
    if (*(u32*)(h + 0xC) != 0) {
        for (i = 0; i < *(u16*)(h + 4); i++) {
            u8* t = *(u8**)(h + 0xC);
            *(u32*)(t + i * 0x10 + 0xC) = (u32)h + *(u32*)(t + i * 0x10 + 0xC);
        }
    }
}

// .text:0x80025EEC size:0x110
void fn_80025EEC(void) {
    return;
}

// .text:0x80025FFC size:0x134
void fn_80025FFC(void) {
    return;
}
