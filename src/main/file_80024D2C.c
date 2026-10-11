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
// Advances the animation; returns whether the end of the sequence was reached.
s32 fn_80024DB0(ShapeAnimState* st) {
    ShapeSeq* seq = &st->seqs[st->seqIdx];
    u32 atStart;
    u16 oldKey;
    s32 ended;

    if (st->loops == 0) {
        return 0;
    }
    if (!st->active) {
        return 0;
    }
    atStart = (0.0f == st->frame);
    oldKey = st->keyIdx;
    st->frame += st->speed;
    shapeSetDirtyA(st);
    ended = (st->frame >= (f32)seq->hdr.length);
    if (ended) {
        if (st->loops > 0) {
            st->loops--;
        }
        if (st->loops != 0) {
            st->frame -= (f32)seq->hdr.length;
            st->keyIdx = seq->hdr.keyCount;
            do {
                st->keyIdx--;
            } while ((f32)seq->keys[st->keyIdx].frame > st->frame);
        } else {
            st->frame = (f32)seq->hdr.length;
        }
    } else if (st->keyIdx < seq->hdr.keyCount - 1) {
        while (st->frame >= (f32)seq->keys[st->keyIdx + 1].frame) {
            st->keyIdx++;
        }
    }
    if (atStart || oldKey != st->keyIdx) {
        shapeSetDirtyB(st);
    }
    return ended;
}

// .text:0x80024FA4 size:0xCB4
// Writes the current blend of the two active morph targets into the model's vertex arrays.
// NONMATCHING 89%: blend loops pick different registers; original re-reads s0/s1 with lhzx and keeps hold/mode on the stack
#if NONMATCHING
void fn_80024FA4(ShapeModel** model, ShapeData* shape, ShapeAnimState* st, s32 forceTarget) {
    ShapeSeq* seq = &st->seqs[st->seqIdx];
    u8 hold = 0;
    ShapeModel* m;
    ModelGeo* geo;
    ModelVtxDesc* vd;
    void* posData;
    ModelGeoArray* arrays;
    ShapeKey* keys;
    u32 k;
    u32 n;
    f32 frame0;
    f32 frame1;
    f32 w0;
    f32 w1;
    f32 blend;
    f32 inv;
    s32 mode;
    s32 mul8;
    s32 mul8Inv;
    s32 mul16;
    s32 mul16Inv;
    s32 src0;
    s32 src1;
    s32 g;
    void* flushAddr;
    u32 flushSize;

    if (shape == NULL || shape->targets == NULL) {
        return;
    }
    if (!shapeDirtyA(st) && !shapeDirtyB(st)) {
        return;
    }
    k = st->keyIdx;
    n = seq->hdr.keyCount;
    if (k == n || (hold = seq->keys[k + 1].hold) != 0) {
        if (!shapeDirtyB(st)) {
            return;
        }
    }

    m = *model;
    geo = m->geo;
    vd = m->vtxDesc;
    if (geo == NULL) {
        posData = NULL;
        arrays = NULL;
    } else {
        if (geo->a != NULL) {
            posData = geo->a->data;
        } else if (geo->b != NULL) {
            posData = geo->b->data;
        } else {
            posData = NULL;
        }
        arrays = geo->arrays;
    }

    keys = seq->keys;
    frame0 = keys[(u16)k].frame;
    if ((s32)(k + 1) == (s32)n) {
        frame1 = 0.0f;
        hold = 1;
    } else {
        frame1 = keys[k + 1].frame;
    }
    if (hold) {
        mode = 0;
    } else {
        if (keys[(u16)k].ease) {
            w0 = 1.0f - keys[(u16)k].weight / 100.0f;
        } else {
            w0 = 0.0f;
        }
        if (keys[k + 1].ease) {
            w1 = keys[k + 1].weight / 100.0f;
        } else {
            w1 = 1.0f;
        }
        if (st->frame == frame0) {
            blend = w0;
            mode = 0;
        } else if (st->frame == frame1) {
            blend = w1;
            mode = 1;
        } else {
            mode = 2;
            blend = (st->frame - frame0) / (frame1 - frame0) * (w1 - w0) + w0;
        }
        if (1.0f != blend && 0.0f != blend) {
            mode = 2;
        }
        inv = 1.0f - blend;
        mul8Inv = 16777216.0f * inv;
        mul16Inv = 65536.0f * inv;
        mul8 = 0x1000000 - mul8Inv;
        mul16 = 0x10000 - mul16Inv;
    }
    if (keys[(u16)k].override && forceTarget != -1) {
        src0 = forceTarget;
    } else {
        src0 = keys[(u16)k].target;
    }
    if (hold) {
        src1 = src0;
    } else if (keys[k + 1].override && forceTarget != -1) {
        src1 = forceTarget;
    } else {
        src1 = keys[k + 1].target;
    }
    inv = 1.0f - blend;

    for (g = 0; g < shape->groupCount; g++) {
        ShapeGroup* grp = &shape->groups[g];
        ShapeEntry* e = grp->entries;
        s32 ti = 0;
        s32 ei;

        for (ei = 0; ei < grp->entryCount; ei++) {
            ShapeTarget* tgt;
            u32 copyOnly;
            u8* dst;
            u8* s0;
            u8* s1;
            s32 off;
            s32 compCount;
            s32 compSize;
            s32 ri;
            s32 v;
            s32 count;

            if (!shapeDirtyA(st)) {
                e = (ShapeEntry*)((u8*)e + grp->entryStride);
                continue;
            }
            copyOnly = e->copyOnly;
            if (copyOnly && !shapeDirtyB(st)) {
                e = (ShapeEntry*)((u8*)e + grp->entryStride);
                continue;
            }

            tgt = NULL;
            do {
                if (e->id == shape->targets[ti].idx && e->type == shape->targets[ti].type) {
                    tgt = &shape->targets[ti];
                    break;
                }
                ti++;
            } while (ti < shape->targetCount);
            if (tgt == NULL) {
                break;
            }

            compCount = e->compCount;
            compSize = e->compSize;
            dst = tgt->buf[tgt->useBuf1];
            off = 0;
            s0 = e->src[src0];
            s1 = e->src[src1];
            if (copyOnly || hold || mode == 0) {
                s32 stride = compSize * compCount;
                for (ri = 0; e->ranges[ri].count != 0; ri++) {
                    count = e->ranges[ri].count * stride;
                    memcpy(dst + e->ranges[ri].start * stride, s0 + off, count);
                    off += count;
                }
            } else {
                switch (mode) {
                case 1: {
                s32 stride = compSize * compCount;
                for (ri = 0; e->ranges[ri].count != 0; ri++) {
                    count = e->ranges[ri].count * stride;
                    memcpy(dst + e->ranges[ri].start * stride, s1 + off, count);
                    off += count;
                }
                break;
                }
                case 2:
                if (e->type == 3) {
                    // packed 4:4:4:4 values
                    u32 stride = compSize * compCount;
                    for (ri = 0; e->ranges[ri].count != 0; ri++) {
                        u16 start = e->ranges[ri].start;
                        for (v = 0; v < e->ranges[ri].count; v++) {
                            u16* d = (u16*)dst + compCount * (start + v);
                            *d = (s32)((s32)(*(u16*)(s0 + off) & 0xF) * inv + (s32)(*(u16*)(s1 + off) & 0xF) * blend) & 0xF;
                            *d |= (s32)((s32)(*(u16*)(s0 + off) & 0xF0) * inv + (s32)(*(u16*)(s1 + off) & 0xF0) * blend) & 0xF0;
                            *d |= (s32)((s32)(*(u16*)(s0 + off) & 0xF00) * inv + (s32)(*(u16*)(s1 + off) & 0xF00) * blend) & 0xF00;
                            {
                                u16 a = *(u16*)(s0 + off);
                                u16 b = *(u16*)(s1 + off);
                                off += stride;
                                *d |= (s32)((s32)(a & 0xF000) * inv + (s32)(b & 0xF000) * blend) & 0xF000;
                            }
                        }
                    }
                } else if (compSize == 1) {
                    u32 stride = compCount * compSize;
                    for (ri = 0; e->ranges[ri].count != 0; ri++) {
                        u16 start = e->ranges[ri].start;
                        for (v = 0; v < e->ranges[ri].count; v++) {
                            s8* d = (s8*)(dst + (start + v) * stride);
                            s32 c;
                            for (c = compCount; c > 0; c--) {
                                u8 b = s1[off];
                                u8 a = s0[off];
                                off += compSize;
                                *d++ = (mul8Inv * a + (mul8 * b + (lbl_803CBC68 << 24))) / 0x1000000;
                            }
                        }
                    }
                } else if (compSize == 2) {
                    for (ri = 0; e->ranges[ri].count != 0; ri++) {
                        u16 start = e->ranges[ri].start;
                        for (v = 0; v < e->ranges[ri].count; v++) {
                            s32 di = compCount * (start + v);
                            s16* a = (s16*)(s1 + off);
                            s16* b = (s16*)(s0 + off);
                            s32 c;
                            for (c = compCount; c > 0; c--) {
                                s16 av = *a++;
                                s16 bv;
                                off += compSize;
                                bv = *b++;
                                ((s16*)dst)[di++] = (mul16Inv * bv + (mul16 * av + (lbl_803CBC68 << 16))) / 0x10000;
                            }
                        }
                    }
                }
                break;
                }
            }

            {
                u32 elemSize = tgt->fmtHi * tgt->fmtLo;
                e = (ShapeEntry*)((u8*)e + grp->entryStride);
                switch (tgt->type) {
                case 0:
                    flushAddr = arrays[tgt->idx].data;
                    flushSize = elemSize * arrays[tgt->idx].count;
                    break;
                case 1:
                    if (tgt->fmtHi == 6) {
                        flushAddr = posData;
                    } else {
                        flushAddr = vd->sets[tgt->idx].set->pos->data;
                    }
                    flushSize = elemSize * vd->sets[tgt->idx].set->pos->count;
                    break;
                case 2:
                    flushAddr = vd->sets[tgt->idx].set->clr->data;
                    flushSize = elemSize * vd->sets[tgt->idx].set->clr->count;
                    break;
                case 3:
                    flushAddr = vd->sets[tgt->idx].set->nrm->data;
                    flushSize = elemSize * vd->sets[tgt->idx].set->nrm->count;
                    break;
                case 4:
                case 5:
                case 6:
                case 7: {
                    VtxArray* arr = &vd->sets[tgt->idx].set->tex[tgt->type - 4];
                    flushAddr = arr->data;
                    flushSize = elemSize * arr->count;
                    break;
                }
                }
                DCFlushRangeNoSync(flushAddr, flushSize);
            }
        }
    }
    if (st != NULL) {
        st->dirtyA = st->dirtyA & (1 << (lbl_803CBBC0 == 0));
    }
    if (st != NULL) {
        st->dirtyB = st->dirtyB & (1 << (lbl_803CBBC0 == 0));
    }
}
#endif

// .text:0x80025C58 size:0x184
// Binds the shape data to a model: caches each target's vertex array slot and data pointer.
// NONMATCHING 96%: r5/r6 swapped for geo/arrays vs posSlot; original copies the zero with mr
#if NONMATCHING
void fn_80025C58(ShapeData* shape, ShapeModel** model) {
    ShapeModel* m;
    ModelGeo* geo;
    ModelVtxDesc* vd;
    void** posSlot;
    void* posData;
    ModelGeoArray* arrays;
    ShapeTarget* t;
    s32 i;
    void** slot;
    void* data;

    if (shape->targets == NULL) {
        return;
    }
    shape->owner = model;
    m = *model;
    geo = m->geo;
    vd = m->vtxDesc;
    if (geo == NULL) {
        posData = NULL;
        arrays = NULL;
    } else {
        if (geo->a != NULL) {
            posSlot = &geo->a->data;
            posData = *posSlot;
        } else if (geo->b != NULL) {
            posSlot = &geo->b->data;
            posData = *posSlot;
        } else {
            posSlot = NULL;
            posData = NULL;
        }
        arrays = geo->arrays;
    }
    t = shape->targets;
    for (i = 0; i < shape->targetCount; i++, t++) {
        u32 type = t->type;
        u32 fmt = t->fmtHi;
        switch (type) {
        case 0:
            slot = &arrays[t->idx].data;
            data = *slot;
            break;
        case 1:
            if (fmt == 6) {
                slot = posSlot;
                data = posData;
            } else {
                slot = &vd->sets[t->idx].set->pos->data;
                data = *slot;
            }
            break;
        case 2:
            slot = &vd->sets[t->idx].set->clr->data;
            data = *slot;
            break;
        case 3:
            slot = &vd->sets[t->idx].set->nrm->data;
            data = *slot;
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            slot = &vd->sets[t->idx].set->tex[type - 4].data;
            data = *slot;
            break;
        }
        t->dataSlot = slot;
        t->buf[0] = data;
    }
}
#endif

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
// Starts the sequence selected by tables[table][entry] (negative: none).
// NONMATCHING 93%: original tests `active` from the merged byte instead of reloading it; default seq loads both words before storing
#if NONMATCHING
void fn_80025EEC(ShapeAnimPlayer* p, s32 table, s32 entry) {
    ShapeAnimState* st = &p->state;
    s8 idx = p->tables[table][entry];

    if (p->curIdx != -128 && idx == p->curIdx) {
        return;
    }
    st->active = (idx > -1);
    if (st->active) {
        ShapeSeqData* d = p->seqs[idx];
        st->seqIdx = 0;
        st->seqs[0].hdr.length = d->hdr.length;
        st->seqs[0].hdr.keyCount = d->hdr.keyCount;
        st->seqs[0].keys = d->keys;
    } else {
        st->seqs[0].hdr = lbl_803CB7F0;
        st->seqs[0].keys = lbl_803CB7F4;
    }
    shapeStateReset(st);
    shapeSetDirtyA(st);
    shapeSetDirtyB(st);
    p->curIdx = idx;
}
#endif

// .text:0x80025FFC size:0x134
// Relocates the player's animation set and binds it to model.
// NONMATCHING 95%: `p == NULL` early return emitted as bne/blr; st in r7 instead of r6
#if NONMATCHING
void fn_80025FFC(void* model, ShapeAnimPlayer* p) {
    ShapeAnimState* st;
    u32 i;
    if (model == NULL) {
        return;
    }
    if (p == NULL) {
        return;
    }
    if (p->set == NULL) {
        return;
    }
    p->model = model;
    p->set->seqs = (ShapeSeqData**)((u8*)p->set + (size_t)p->set->seqs);
    p->set->tables = (s8**)((u8*)p->set + (size_t)p->set->tables);
    p->seqs = p->set->seqs;
    for (i = 0; i < p->set->seqCount; i++) {
        p->seqs[i] = (ShapeSeqData*)((u8*)p->set + (size_t)p->seqs[i]);
    }
    p->tableList = p->set->tables;
    for (i = 0; i < p->set->tableCount; i++) {
        p->tableList[i] = (s8*)((u8*)p->set + (size_t)p->tableList[i]);
        p->tables[i] = p->tableList[i];
    }
    st = &p->state;
    shapeStateReset(st);
    st->seqs[0].hdr = lbl_803CB7F0;
    st->seqs[0].keys = lbl_803CB7F4;
    p->curIdx = -128;
    p->unk59 = 1;
}
#endif
