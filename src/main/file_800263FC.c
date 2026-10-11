#include "main/file_800263FC.h"
#include "main/file_80008E00.h"
#include "Dolphin/os.h"
#include "stl/math.h"
#include "stl/mem.h"

// Particle / emitter system.

int __abs(int);
int rand(void);
// TODO: these belong in their own units' headers.
void SetFogNone(void);
u32 fn_8005268C(void);       // file_8004C5F8
void* fn_80052734(s32 index); // file_8004C5F8: projection matrix
extern u8 lbl_800F7840[]; // 4x4 RGB565 texture
void* _OSAllocFromHeap(s32 heap, s32 size);
void fn_800ACFB0(void* p); // free
void fn_800C07BC(void* base, void* tmp, s32 n, s32 size, s32 (*cmp)(const void*, const void*)); // merge sort
void fn_800118AC(Mtx in, Mtx out); // TODO: belongs in file_80011640.h

extern f32 lbl_8017ED68[]; // cosine table, 0x800 steps per turn
extern Mtx lbl_8017FF78[2]; // [0]: billboard rotation (inverse view, no translation), [1]: inverse view
extern Mtx lbl_8017FFE0;
extern Vec lbl_80180010[4];     // billboard quad corners
extern Particle lbl_80180040[0x1400]; // particle pool
extern Emitter lbl_801F8040[0x10];    // emitter pool
extern UVCoord lbl_800F7860[];
extern TexCoordF lbl_800F78C0[4]; // quad corner texcoords
extern const Vec lbl_800E6778;    // (1, 0, 0)
typedef struct MtxBox {
    Mtx m;
} MtxBox;
extern const MtxBox lbl_800E67C0; // identity
extern const Vec lbl_800E6784;    // (0, -1, 0)
extern s32 lbl_803CB7F8;          // respawn delay mask
extern f32 lbl_803CB7FC;          // respawn angle spread (0..1)
extern ParticleParams lbl_800F787C; // default spawn parameters
extern TexArchive* lbl_803CBD0C;
extern SpaniSlot lbl_80371C30[0x360];
extern SpaniObj* lbl_803CBC9C;
extern Particle* lbl_803CBC74; // free particle list
extern u8 lbl_803CBC78;        // nonzero: clear all emitters on next draw
extern s32 lbl_803CBC7C;
extern Emitter* lbl_803CBC80;  // free emitter list (linked through next)
extern EmitterHead lbl_803CBC84; // active list head
#define EMITTER_HEAD ((Emitter*)&lbl_803CBC84)

static inline f32 CosIdx(s32 angle) {
    s32 i = __abs(angle) & 0x7FF;
    if (i >= 0x401) {
        i = 0x800 - i;
    }
    return lbl_8017ED68[i];
}

#define SinIdx(angle) CosIdx((angle) + 0x600)

static inline Emitter* FindEmitter(Emitter* e, u8 type) {
    if (e == NULL) {
        e = EMITTER_HEAD;
    }
    while ((e = e->next) != NULL) {
        if (e->type == type) {
            break;
        }
    }
    return e;
}

static inline void FreeParticles(Particle* list) {
    Particle* last = list;
    while (last != NULL && last->next != NULL) {
        last = last->next;
    }
    if (last != NULL) {
        last->next = lbl_803CBC74;
        lbl_803CBC74 = list;
    }
}

static inline Emitter* AllocParticles(Emitter* e, s32 n, s32 strict) {
    s32 count;
    Particle* p;
    Particle* last;
    count = 0;
    last = NULL;
    p = lbl_803CBC74;
    if (e != NULL) {
        while (p != NULL && n != 0) {
            last = p;
            p = p->next;
            count++;
            n--;
        }
        if (strict && n != 0) {
            return NULL;
        }
        e->count = count;
        if (count != 0) {
            e->particles = lbl_803CBC74;
            lbl_803CBC74 = p;
            if (last != NULL) {
                last->next = NULL;
            }
        } else {
            e->particles = NULL;
        }
    }
    return e;
}

static inline void FreeEmitter(Emitter* e) {
    if (e->update != NULL) {
        if (e->prev != NULL) {
            e->prev->next = e->next;
        }
        if (e->next != NULL) {
            e->next->prev = e->prev;
        }
        e->update = NULL;
        FreeParticles(e->particles);
        e->prev = NULL;
        e->next = lbl_803CBC80;
        lbl_803CBC80 = e;
    }
}

static inline Emitter* NewEmitter(EmitterUpdateFn update, u8 priority, s32 unk14, s32 n, s32 strict, u8 type) {
    Emitter* e = AllocParticles(lbl_803CBC80, n, strict);
    Emitter* at;
    if (e == NULL) {
        return NULL;
    }
    lbl_803CBC80 = lbl_803CBC80->next;
    e->update = update;
    e->priority = priority;
    e->type = type;
    e->active = 1;
    e->unk14 = unk14;
    e->next = NULL;
    e->prev = NULL;
    at = EMITTER_HEAD;
    while (at->next != NULL && at->next->priority < e->priority) {
        at = at->next;
    }
    e->next = at->next;
    if (e->next != NULL) {
        e->next->prev = e;
    }
    e->prev = at;
    at->next = e;
    return e;
}

static inline void LoadParticleTex(TexArchive* arc, s32 idx, GXTexWrapMode wrapS, GXTexWrapMode wrapT) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    TexImage* img;

    if (arc == NULL) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        return;
    }
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
    img = &arc->entries[arc->entries[idx].index].img;
    if (img->tlut != NULL) {
        GXInitTexObjCI(&texObj, img->data, img->width, img->height, img->format, wrapS, wrapT, GX_FALSE, 0);
        GXInitTlutObj(&tlutObj, img->tlut, img->tlutFormat, img->tlutEntries);
        GXLoadTlut(&tlutObj, GX_TLUT0);
    } else {
        GXInitTexObj(&texObj, img->data, img->width, img->height, img->format, wrapS, wrapT, GX_FALSE);
    }
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, (f32)img->minLOD, (f32)img->maxLOD, img->lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP1);
}

static inline void DrawParticleQuad(Particle* p, TexArchive* arc) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    TexImage* img;
    s32 tex = p->texIndex;
    Vec* corner;
    s32 i;

    if (arc == NULL) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    } else {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
        img = &arc->entries[arc->entries[tex].index].img;
        if (img->tlut != NULL) {
            GXInitTexObjCI(&texObj, img->data, img->width, img->height, img->format, GX_CLAMP, GX_CLAMP, GX_FALSE, 0);
            GXInitTlutObj(&tlutObj, img->tlut, img->tlutFormat, img->tlutEntries);
            GXLoadTlut(&tlutObj, GX_TLUT0);
        } else {
            GXInitTexObj(&texObj, img->data, img->width, img->height, img->format, GX_CLAMP, GX_CLAMP, GX_FALSE);
        }
        GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, (f32)img->minLOD, (f32)img->maxLOD, img->lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&texObj, GX_TEXMAP1);
    }
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    corner = lbl_80180010;
    for (i = 0; i < 4; i++) {
        GXPosition3f32(p->pos.x + corner[i].x, p->pos.y + corner[i].y, p->pos.z + corner[i].z);
        GXColor1u32(p->color.rgba);
        GXTexCoord2f32(lbl_800F7860[p->uvFrame + i].u, lbl_800F7860[p->uvFrame + i].v);
    }
}

s32 fn_8002E3DC(Emitter* e);
s32 fn_8002E828(Emitter* e);
s32 fn_80029CC8(Emitter* e);

// .text:0x800263FC size:0x59C
void fn_800263FC(void) {
    return;
}

// .text:0x80026998 size:0x4C0
void fn_80026998(void) {
    return;
}

// .text:0x80026E58 size:0x4A8
void fn_80026E58(void) {
    return;
}

// .text:0x80027300 size:0x374
void fn_80027300(void) {
    return;
}

// .text:0x80027674 size:0x2A4
void fn_80027674(void) {
    return;
}

// .text:0x80027918 size:0x50
// NONMATCHING 96%: the store goes through r4 instead of the copied r3
#if NONMATCHING
void fn_80027918(u8 type, f32 v) {
    Emitter* e;
    Emitter* f = NULL;
    while (e = FindEmitter(f, type), f = e, e != NULL) {
        f->u.f[1] = v;
    }
}
#endif

// .text:0x80027968 size:0xBC4
void fn_80027968(void) {
    return;
}

// .text:0x8002852C size:0xFC
void fn_8002852C(void) {
    return;
}

// .text:0x80028628 size:0x920
void fn_80028628(void) {
    return;
}

// .text:0x80028F48 size:0x614
void fn_80028F48(void) {
    return;
}

// .text:0x8002955C size:0x294
void fn_8002955C(void) {
    return;
}

// .text:0x800297F0 size:0x4D8
void fn_800297F0(void) {
    return;
}

// .text:0x80029CC8 size:0x504
// NONMATCHING 62%: register allocation; the original copies the identity matrix word by word
#if NONMATCHING
s32 fn_80029CC8(Emitter* e) {
    MtxBox ident;
    Vec c;
    Vec q;
    Vec t;
    Vec perp;
    Vec v0;
    Vec v1;
    Vec v2;
    Vec v3;
    f32 sx;
    f32 sy;
    s32 count;
    Particle* p;

    ident = lbl_800E67C0;
    count = e->count;
    GXLoadPosMtxImm(ident.m, GX_PNMTX0);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    PSMTXMultVec(lbl_8017FFE0, &e->u.t9.pos, &c);
    p = e->particles;
    LoadParticleTex(e->tex, p->texIndex, GX_CLAMP, GX_CLAMP);
    for (; p != NULL; p = p->next) {
        if (p->delay != 0) {
            p->delay--;
        } else if (p->life != 0) {
            PSVECAdd(&p->u.tB.dir, &p->u.tB.vel, &p->u.tB.dir);
            PSVECAdd(&p->pos, &p->u.tB.dir, &p->pos);
            p->color.c.a = (p->colorStep.tB.alpha0 * p->life) / p->colorStep.tB.maxLife;
            if (c.z <= -1.0f) {
                PSMTXMultVec(lbl_8017FFE0, &p->pos, &q);
                t.x = (c.x * q.z) / c.z;
                t.y = (c.y * q.z) / c.z;
                t.z = q.z;
                PSVECSubtract(&q, &t, &t);
                t.z = 0.0f;
                perp.x = -t.y;
                perp.y = t.x;
                perp.z = 0.0f;
                sx = p->u.tB.sizeX + (p->u.tB.sizeXDelta * (f32)(p->colorStep.tB.maxLife - p->life)) / (f32)p->colorStep.tB.maxLife;
                sy = p->u.tB.sizeY + (p->u.tB.sizeYDelta * (f32)(p->colorStep.tB.maxLife - p->life)) / (f32)p->colorStep.tB.maxLife;
                PSVECScale(&t, sy, &t);
                PSVECScale(&perp, sx * 0.5f, &perp);
                PSVECAdd(&q, &perp, &v0);
                PSVECSubtract(&q, &perp, &v1);
                PSVECSubtract(&v1, &t, &v2);
                PSVECSubtract(&v0, &t, &v3);
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition3f32(v0.x, v0.y, v0.z);
                GXColor1u32(p->color.rgba);
                GXTexCoord2f32(0.0f, 1.0f);
                GXPosition3f32(v1.x, v1.y, v1.z);
                GXColor1u32(p->color.rgba);
                GXTexCoord2f32(0.0f, 0.0f);
                GXPosition3f32(v2.x, v2.y, v2.z);
                GXColor1u32(p->color.rgba);
                GXTexCoord2f32(1.0f, 0.0f);
                GXPosition3f32(v3.x, v3.y, v3.z);
                GXColor1u32(p->color.rgba);
                GXTexCoord2f32(1.0f, 1.0f);
            }
            p->life--;
        } else {
            count--;
        }
    }
    GXLoadPosMtxImm(lbl_8017FFE0, GX_PNMTX0);
    return count == 0;
}
#endif

// .text:0x8002A1CC size:0x690
// NONMATCHING 44%: float register allocation/scheduling of the 14 parameter conversions
#if NONMATCHING
void fn_8002A1CC(Vec* pos, ParticleParamsB* prm) {
    Emitter* e;
    Particle* p;
    f32 speedMin = (f32)prm->speedMin / 100000.0f;
    f32 speedRange = (f32)prm->speedMax / 100000.0f - speedMin;
    f32 velMin = (f32)prm->velMin / 100000.0f;
    f32 velRange = (f32)prm->velMax / 100000.0f - velMin;
    f32 sizeXMin = (f32)prm->sizeXMin / 100000.0f;
    f32 sizeXRange = (f32)prm->sizeXMax / 100000.0f - sizeXMin;
    f32 sizeYMin = (f32)prm->sizeYMin / 100000.0f;
    f32 sizeYRange = (f32)prm->sizeYMax / 100000.0f - sizeYMin;
    f32 endXMin = (f32)prm->endXMin / 100000.0f;
    f32 endXRange = (f32)prm->endXMax / 100000.0f - endXMin;
    f32 endYMin;
    f32 endYRange;
    s32 lifeRange;
    s32 instant;
    f32 step;
    f32 yaw;
    f32 pitch;

    e = NewEmitter(fn_80029CC8, 0x80, 0, prm->count, 1, 11);
    if (e == NULL) {
        return;
    }
    e->tex = prm->tex;
    memcpy(&e->u.t9.pos, pos, sizeof(Vec));
    instant = prm->instant;
    lifeRange = prm->lifeMax - prm->lifeMin;
    endYMin = (f32)prm->endYMin / 100000.0f;
    endYRange = (f32)prm->endYMax / 100000.0f - endYMin;
    step = 360.0f / (f32)(s32)(f32)sqrt(prm->instant);
    pitch = -180.0f;
    yaw = -180.0f;
    p = e->particles;
    do {
        p->texIndex = prm->texIndex;
        if (instant-- != 0) {
            p->delay = 0;
        } else {
            p->delay = (prm->delayMax * rand()) / 32767;
        }
        p->life = p->colorStep.tB.maxLife = prm->lifeMin + (lifeRange * rand()) / 32767;
        memcpy(&p->pos, pos, sizeof(Vec));
        fn_800332B8(NULL, &p->u.tB.dir, yaw, yaw + step, pitch, pitch + step);
        yaw += step;
        if (yaw >= 180.0f) {
            pitch += step;
            yaw -= 360.0f;
            if (pitch >= 180.0f) {
                pitch -= 360.0f;
            }
        }
        PSVECScale(&p->u.tB.dir, velMin + (velRange * (f32)rand()) / 32767.0f, &p->u.tB.vel);
        PSVECScale(&p->u.tB.dir, speedMin + (speedRange * (f32)rand()) / 32767.0f, &p->u.tB.dir);
        p->u.tB.sizeX = sizeXMin + (sizeXRange * (f32)rand()) / 32767.0f;
        p->u.tB.sizeY = sizeYMin + (sizeYRange * (f32)rand()) / 32767.0f;
        p->u.tB.sizeXDelta = (endXMin + (endXRange * (f32)rand()) / 32767.0f) - p->u.tB.sizeX;
        p->u.tB.sizeYDelta = (endYMin + (endYRange * (f32)rand()) / 32767.0f) - p->u.tB.sizeY;
        p->color.rgba = prm->color;
        p->colorStep.tB.alpha0 = p->color.c.a;
        p = p->next;
    } while (p != NULL);
}
#endif

// .text:0x8002A85C size:0x40C
void fn_8002A85C(void) {
    return;
}

// .text:0x8002AC68 size:0x3AC
void fn_8002AC68(void) {
    return;
}

// .text:0x8002B014 size:0x3EC
void fn_8002B014(void) {
    return;
}

// .text:0x8002B400 size:0x3F8
void fn_8002B400(void) {
    return;
}

// .text:0x8002B7F8 size:0x48C
void fn_8002B7F8(void) {
    return;
}

// .text:0x8002BC84 size:0x64C
void fn_8002BC84(void) {
    return;
}

// .text:0x8002C2D0 size:0x29C
void fn_8002C2D0(void) {
    return;
}

// .text:0x8002C56C size:0x864
void fn_8002C56C(void) {
    return;
}

// .text:0x8002CDD0 size:0x7C
void fn_8002CDD0(Vec* end) {
    Emitter* e = FindEmitter(NULL, 10);
    if (e != NULL && e->u.t10.unk40 != 0) {
        e->u.t10.end.x = end->x;
        e->u.t10.end.y = end->y;
        e->u.t10.end.z = end->z;
        PSVECSubtract(&e->u.t10.end, &e->u.t10.start, &e->u.t10.dir);
    }
}

// .text:0x8002CE4C size:0x9E0
void fn_8002CE4C(void) {
    return;
}

// .text:0x8002D82C size:0x43C
// NONMATCHING 94%: register allocation of the color/physics loop walkers (r4/r5) differs
#if NONMATCHING
s32 fn_8002D82C(Emitter* e) {
    Mtx ident;
    Vec v;
    TexCoordF* uv = lbl_800F78C0;
    Particle* p = e->particles;
    s32 alive = 0;
    TexArchive* arc = e->tex;
    s32 tex = p->texIndex;
    TexImage* img;
    GXTexObj texObj;
    GXTlutObj tlutObj;
    s32 k;
    s32 c;

    if (arc == NULL) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    } else {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
        img = &arc->entries[arc->entries[tex].index].img;
        if (img->tlut != NULL) {
            GXInitTexObjCI(&texObj, img->data, img->width, img->height, img->format, GX_CLAMP, GX_CLAMP, GX_FALSE, 0);
            GXInitTlutObj(&tlutObj, img->tlut, img->tlutFormat, img->tlutEntries);
            GXLoadTlut(&tlutObj, GX_TLUT0);
        } else {
            GXInitTexObj(&texObj, img->data, img->width, img->height, img->format, GX_CLAMP, GX_CLAMP, GX_FALSE);
        }
        GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, (f32)img->minLOD, (f32)img->maxLOD, img->lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&texObj, GX_TEXMAP1);
    }
    PSMTXIdentity(ident);
    GXLoadPosMtxImm(ident, GX_PNMTX0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    do {
        if (p->life != 0) {
            alive++;
            if (p->delay != 0) {
                p->delay -= (lbl_80366158._28 == 0);
            } else {
                PSMTXMultVec(lbl_8017FFE0, &p->pos, &v);
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition3f32(v.x - p->sizeX, v.y - p->sizeY, v.z);
                GXColor1u32(p->color.rgba);
                GXTexCoord2f32(uv[p->uvOrder & 3].s, uv[p->uvOrder & 3].t);
                GXPosition3f32(v.x + p->sizeY, v.y - p->sizeX, v.z);
                GXColor1u32(p->color.rgba);
                GXTexCoord2f32(uv[(p->uvOrder >> 2) & 3].s, uv[(p->uvOrder >> 2) & 3].t);
                GXPosition3f32(v.x + p->sizeX, v.y + p->sizeY, v.z);
                GXColor1u32(p->color.rgba);
                GXTexCoord2f32(uv[(p->uvOrder >> 4) & 3].s, uv[(p->uvOrder >> 4) & 3].t);
                GXPosition3f32(v.x - p->sizeY, v.y + p->sizeX, v.z);
                GXColor1u32(p->color.rgba);
                GXTexCoord2f32(uv[(p->uvOrder >> 6) & 3].s, uv[(p->uvOrder >> 6) & 3].t);
                if (lbl_80366158._28 == 0) {
                    p->life--;
                    for (k = 0; k < 3; k++) {
                        c = p->color.v[k] + (s8)p->colorStep.v[k];
                        if (c < 0) {
                            c = 0;
                        } else if (c > 0xFF) {
                            c = 0xFF;
                        }
                        p->color.v[k] = c;
                        (&p->u.phys.accel.x)[k] = (&p->u.phys.force.x)[k] / p->u.phys.mass;
                        (&p->u.phys.vel.x)[k] += (&p->u.phys.accel.x)[k];
                        (&p->pos.x)[k] += (&p->u.phys.vel.x)[k];
                    }
                    c = p->color.v[k] + (s8)p->colorStep.v[k];
                    if (c < 0) {
                        c = 0;
                    } else if (c > 0xFF) {
                        c = 0xFF;
                    }
                    p->color.v[k] = c;
                    if (p->life <= e->u.t9.fadeLife && p->colorStep.v[3] == 0) {
                        p->colorStep.v[3] = -0x100 / p->life;
                    }
                }
            }
        }
        p = p->next;
    } while (p != NULL);
    GXLoadPosMtxImm(lbl_8017FFE0, GX_PNMTX0);
    return alive == 0;
}
#endif

// .text:0x8002DC68 size:0x7C
void fn_8002DC68(Vec* pos) {
    Emitter* e = FindEmitter(NULL, 9);
    if (e != NULL) {
        memcpy(&e->u.t9.prevPos, &e->u.t9.pos, sizeof(Vec));
        memcpy(&e->u.t9.pos, pos, sizeof(Vec));
    }
}

// .text:0x8002DCE4 size:0x6F8
// NONMATCHING 73%: float load scheduling/registers; the cos index uses a branchy abs in the original
#if NONMATCHING
void fn_8002DCE4(Vec* from, Vec* to, ParticleParams9* prm) {
    Vec d;
    s32 sign = 1;
    f32 sizeMin = (f32)prm->sizeMin / 100000.0f;
    f32 yawMin = (f32)prm->yawMin / 100000.0f;
    f32 yawMax = (f32)prm->yawMax / 100000.0f;
    f32 pitchMin = (f32)prm->pitchMin / 100000.0f;
    f32 pitchMax = (f32)prm->pitchMax / 100000.0f;
    f32 angleRange = (f32)(prm->angleMax - prm->angleMin) / 100000.0f;
    f32 sizeRange = (f32)prm->sizeMax / 100000.0f - sizeMin;
    f32 angleBase = 45.0f + (f32)prm->angleMin / 100000.0f;
    f32 speed;
    f32 r;
    s32 ang;
    Emitter* e;
    Particle* p;

    PSVECSubtract(to, from, &d);
    speed = (f32)prm->speed / 100000.0f;
    e = NewEmitter(fn_8002D82C, 0x80, 0, prm->count, 1, 9);
    if (e == NULL) {
        return;
    }
    e->tex = prm->tex;
    e->u.t9.fadeLife = prm->fadeLife;
    memcpy(&e->u.t9.pos, to, sizeof(Vec));
    memcpy(&e->u.t9.prevPos, to, sizeof(Vec));
    p = e->particles;
    do {
        p->delay = rand() % prm->delayRange;
        p->life = prm->life - p->delay - rand() % prm->lifeRange;
        p->pos.x = from->x;
        p->pos.y = from->y;
        p->pos.z = from->z;
        p->u.phys.vel.x = d.x / (f32)(p->life - 1);
        p->u.phys.vel.y = d.y / (f32)(p->life - 1);
        p->u.phys.vel.z = d.z / (f32)(p->life - 1);
        fn_800332B8(NULL, &p->u.phys.force, yawMin, yawMax, pitchMin, pitchMax);
        PSVECScale(&p->u.phys.force, speed * (0.5f * (f32)(rand() % 256) + 0.75f), &p->u.phys.force);
        p->u.phys.force.x = p->u.phys.force.x * (f32)sign;
        sign = -sign;
        PSVECScale(&p->u.phys.force, 0.5f * (f32)-p->life, &p->u.phys.accel);
        PSVECAdd(&p->u.phys.vel, &p->u.phys.accel, &p->u.phys.vel);
        p->u.phys.mass = 1.0f;
        if (angleRange != 0.0f) {
            ang = (s32)(0.5f + (2048.0f * (angleBase + (angleRange * (f32)rand()) / 32767.0f)) / 360.0f);
            r = 1.4142135f * ((sizeMin + (sizeRange * (f32)rand()) / 32767.0f) * 0.5f);
            p->sizeX = r * CosIdx(ang);
            p->sizeY = r * SinIdx(ang);
            p->uvOrder = (rand() & 1) ? 0x1B : 0xE4;
        } else {
            r = (sizeMin + (sizeRange * (f32)rand()) / 32767.0f) * 0.5f;
            p->sizeX = r;
            p->sizeY = r;
            p->uvOrder = 0xB1;
        }
        p->color.rgba = 0xFFFFFFFF;
        p->colorStep.all = 0;
        p->texIndex = prm->texIndex;
        p = p->next;
    } while (p != NULL);
}
#endif

// .text:0x8002E3DC size:0x44C
void fn_8002E3DC(void) {
    return;
}

// .text:0x8002E828 size:0x478
void fn_8002E828(void) {
    return;
}

// .text:0x8002ECA0 size:0x50C
void fn_8002ECA0(void) {
    return;
}

// .text:0x8002F1AC size:0xAC
s32 fn_8002F1AC(Vec* pos, s32 id) {
    Emitter* e = FindEmitter(NULL, 6);
    Particle* p;
    if (e != NULL && lbl_80366158._28 == 0) {
        for (p = e->particles; p != NULL; p = p->next) {
            if (p->u.t6.id == id) {
                memcpy(&p->pos, pos, sizeof(Vec));
                p->life++;
                return 1;
            }
        }
    }
    return 0;
}

// .text:0x8002F258 size:0x39C
void fn_8002F258(void) {
    return;
}

// .text:0x8002F5F4 size:0x408
void fn_8002F5F4(void) {
    return;
}

// .text:0x8002F9FC size:0x3BC
void fn_8002F9FC(void) {
    return;
}

// .text:0x8002FDB8 size:0x6B8
void fn_8002FDB8(void) {
    return;
}

// .text:0x80030470 size:0x2B0
void fn_80030470(void) {
    return;
}

// .text:0x80030720 size:0x668
void fn_80030720(void) {
    return;
}

// .text:0x80030D88 size:0x2AC
void fn_80030D88(void) {
    return;
}

// .text:0x80031034 size:0x790
void fn_80031034(void) {
    return;
}

// .text:0x800317C4 size:0x4E0
void fn_800317C4(void) {
    return;
}

// .text:0x80031CA4 size:0x290
void fn_80031CA4(void) {
    return;
}

// .text:0x80031F34 size:0x104
// NONMATCHING 62%: the original keeps n and the countdown copy in separate saved regs
#if NONMATCHING
Particle* fn_80031F34(Particle* list, s32 n) {
    Vec v;
    s32 i = 0;
    s32 left = n;
    ParticleSortEntry* buf;
    ParticleSortEntry* ent;
    Particle* p;

    if (n != 0) {
        buf = _OSAllocFromHeap(0x20, n * 2 * sizeof(ParticleSortEntry));
        for (p = list, ent = buf; p != NULL; p = p->next) {
            if (i >= n) {
                OSReport("zsort particle err.\n");
                break;
            }
            ent->p = p;
            PSMTXMultVec(lbl_8017FFE0, &p->pos, &v);
            i++;
            ent->z = v.z;
            ent++;
        }
        fn_800C07BC(buf, buf + n, n, sizeof(ParticleSortEntry), fn_80032038);
        list = buf[0].p;
        ent = buf;
        while (--left != 0) {
            ent->p->next = ent[1].p;
            ent++;
        }
        ent->p->next = NULL;
        fn_800ACFB0(buf);
    }
    return list;
}
#endif

// .text:0x80032038 size:0x2C
s32 fn_80032038(const void* a, const void* b) {
    if (((const ParticleSortEntry*)a)->z > ((const ParticleSortEntry*)b)->z) {
        return 1;
    }
    if (((const ParticleSortEntry*)a)->z < ((const ParticleSortEntry*)b)->z) {
        return -1;
    }
    return 0;
}

// .text:0x80032064 size:0x220
void fn_80032064(void) {
    return;
}

// .text:0x80032284 size:0x268
void fn_80032284(void) {
    return;
}

// .text:0x800324EC size:0x3F4
void fn_800324EC(void) {
    return;
}

// .text:0x800328E0 size:0x7EC
// NONMATCHING 59%: the original inlines fn_8003403C with the file-static bss base (lbl_8017EC00 + offset); calls fn_8003403C here
#if NONMATCHING
s32 fn_800328E0(Emitter* e) {
    Mtx rotM;
    Quaternion q;
    Vec ref;
    Vec dir;
    Vec axis;
    Vec v;
    f32 angle;
    f32 s;
    f32 spread;
    f32 cosA;
    f32 sinA;
    f32 spd;
    f32 h;
    s32 ang;
    s32 r;
    s32 k;
    s32 c;
    s32 count = 0;
    Particle* p = e->particles;

    ref = lbl_800E6784;
    fn_8003403C(p->sizeX, p->sizeY);
    memcpy(&dir, &e->u.t1.dir, sizeof(Vec));
    angle = acos(PSVECDotProduct(&ref, &dir));
    PSVECCrossProduct(&ref, &dir, &axis);
    angle = angle * 0.5f;
    s = sin(angle);
    q.w = cos(angle);
    q.x = axis.x * s;
    q.y = axis.y * s;
    q.z = axis.z * s;
    PSMTXQuat(rotM, &q);
    do {
        if (p->delay > 0) {
            p->delay -= (lbl_80366158._28 == 0);
            count++;
        } else if (p->life != 0) {
            if (lbl_80366158._28 == 0) {
                p->u.phys.force.z = 0.0f;
                p->u.phys.force.x = 0.0f;
                p->u.phys.force.y = 0.16344418f * p->u.phys.mass;
                p->u.phys.force.x = 0.001f * (-p->u.phys.vel.x * p->u.phys.mass) + p->u.phys.force.x;
                p->u.phys.force.y = 0.001f * (-p->u.phys.vel.y * p->u.phys.mass) + p->u.phys.force.y;
                p->u.phys.force.z = 0.001f * (-p->u.phys.vel.z * p->u.phys.mass) + p->u.phys.force.z;
                for (k = 0; k < 3; k++) {
                    c = p->color.v[k] + (s8)p->colorStep.v[k];
                    if (c < 0) {
                        c = 0;
                    } else if (c > 0xFF) {
                        c = 0xFF;
                    }
                    p->color.v[k] = c;
                    (&p->u.phys.accel.x)[k] = (&p->u.phys.force.x)[k] / p->u.phys.mass;
                    (&p->u.phys.vel.x)[k] += (&p->u.phys.accel.x)[k];
                    (&p->pos.x)[k] += (&p->u.phys.vel.x)[k];
                }
                c = p->color.v[k] + (s8)p->colorStep.v[k];
                if (c < 0) {
                    c = 0;
                } else if (c > 0xFF) {
                    c = 0xFF;
                }
                p->color.v[k] = c;
                if (p->u.phys.vel.y > 0.0f && p->pos.y >= e->u.t1.floorY) {
                    p->u.phys.vel.y = p->u.phys.vel.y * e->u.t1.bounce;
                    p->life--;
                }
                if (fabs(p->pos.x) > 300.0 || fabs(p->pos.z) > 300.0) {
                    p->life = 0;
                }
            }
            DrawParticleQuad(p, e->tex);
            count++;
        } else if (e->u.t1.spawnLeft != 0) {
            spread = lbl_803CB7FC;
            ang = (s32)(512.0f * (1.0f - spread) + (512.0f * spread * (f32)rand()) / 32767.0f);
            cosA = CosIdx(ang);
            sinA = SinIdx(ang);
            r = rand();
            k = (rand() & 0xF) + 0x5A;
            p->u.phys.mass = 0.001f;
            p->pos.x = e->u.t1.pos.x;
            p->pos.y = e->u.t1.pos.y;
            p->pos.z = e->u.t1.pos.z;
            spd = (((e->u.t1.speed / 60.0f) * (f32)k) / 100.0f) / 0.001f;
            h = spd * cosA;
            v.y = -spd * sinA;
            v.x = h * CosIdx(r);
            v.z = h * SinIdx(r);
            v.y = v.y + 0.16344418f;
            PSMTXMultVec(rotM, &v, &v);
            p->u.phys.vel.x = v.x;
            p->u.phys.vel.y = v.y;
            p->u.phys.vel.z = v.z;
            p->sizeX = e->u.t1.size;
            p->sizeY = e->u.t1.size;
            p->color.rgba = e->u.t1.color;
            p->colorStep.all = 0;
            p->life = 2;
            p->delay = r & lbl_803CB7F8;
            p->texIndex = 0xFF;
            count++;
        }
        p = p->next;
    } while (p != NULL);
    if (e->u.t1.spawnLeft > 0) {
        e->u.t1.spawnLeft--;
    }
    return count == 0;
}
#endif

// .text:0x800330CC size:0x1EC
void fn_800330CC(s32 n, u32 color, Vec* pos, Vec* dir, s32 spawnFrames, TexArchive* tex, f32 speed, f32 size) {
    Emitter* e = NewEmitter(fn_800328E0, 0x80, 0, n, 1, 1);
    if (e != NULL) {
        e->tex = tex;
        memcpy(&e->u.t1.pos, pos, sizeof(Vec));
        memcpy(&e->u.t1.dir, dir, sizeof(Vec));
        e->u.t1.speed = speed;
        e->u.t1.spawnLeft = spawnFrames;
        e->u.t1.bounce = -0.4f;
        e->u.t1.floorY = -0.0001f;
        e->u.t1.color = color;
        e->u.t1.size = size;
    }
}

// .text:0x800332B8 size:0x304
// NONMATCHING 80%: float register allocation; the original also stores yawMin/360*360 into out->x first (dead store)
#if NONMATCHING
void fn_800332B8(Vec* axis, Vec* out, f32 yawMin, f32 yawMax, f32 pitchMin, f32 pitchMax) {
    Mtx m;
    Vec cross;
    Vec ref;
    Vec axisCopy;
    f32 angle;
    Quaternion q;
    s32 yaw;
    s32 pitch;

    ref = lbl_800E6778;
    if (axis != NULL) {
        memcpy(&axisCopy, axis, sizeof(Vec));
        axis = &axisCopy;
    }
    yaw = (s32)(2048.0f * (yawMin / 360.0f) + 0.5f);
    if (yawMax != yawMin) {
        yaw += rand() % (s32)(2048.0f * ((yawMax - yawMin) / 360.0f) + 0.5f);
    }
    out->x = CosIdx(yaw);
    out->y = SinIdx(yaw);
    pitch = (s32)(2048.0f * (pitchMin / 360.0f) + 0.5f);
    if (pitchMax != pitchMin) {
        pitch += rand() % (s32)(2048.0f * ((pitchMax - pitchMin) / 360.0f) + 0.5f);
    }
    out->z = out->x * SinIdx(pitch);
    out->x = out->x * CosIdx(pitch);
    if (axis != NULL && PSVECMag(axis) != 0.0f) {
        angle = acos(PSVECDotProduct(&ref, axis));
        PSVECCrossProduct(&ref, axis, &cross);
        if (PSVECMag(&cross) != 0.0f) {
            C_QUATRotAxisRad(&q, &cross, angle);
            PSMTXQuat(m, &q);
            PSMTXMultVec(m, out, out);
        } else {
            PSVECScale(out, PSVECMag(axis), out);
        }
    }
}
#endif

// .text:0x800335BC size:0x30
f32 fn_800335BC(s32 angle) {
    s32 i = __abs(angle) & 0x7FF;
    if (i >= 0x401) {
        i = 0x800 - i;
    }
    return lbl_8017ED68[i];
}

// .text:0x800335EC size:0x34
f32 fn_800335EC(s32 angle) {
    s32 i = __abs(angle + 0x600) & 0x7FF;
    if (i >= 0x401) {
        i = 0x800 - i;
    }
    return lbl_8017ED68[i];
}

// .text:0x80033620 size:0x174
void fn_80033620(Emitter* e) {
    Vec v;
    Vec w;
    Particle tmp;
    Particle* p;
    Particle* q;
    Particle* best;
    Particle* pNext;
    Particle* bestNext;
    f32 bestZ;
    u32 i = 0;

    for (p = e->particles; p != NULL && e->count > i; p = p->next, i++) {
        q = p->next;
        if (p->delay <= 0 && p->life != 0) {
            PSMTXMultVec(lbl_8017FFE0, &p->pos, &v);
            bestZ = v.z;
            best = NULL;
            for (; q != NULL; q = q->next) {
                if (q->delay <= 0 && q->life != 0) {
                    PSMTXMultVec(lbl_8017FFE0, &q->pos, &w);
                    if (bestZ > w.z) {
                        best = q;
                        bestZ = w.z;
                    }
                }
            }
            if (best != NULL) {
                pNext = p->next;
                bestNext = best->next;
                tmp = *p;
                *p = *best;
                *best = tmp;
                p->next = pNext;
                best->next = bestNext;
            }
        }
    }
}

// .text:0x80033794 size:0x38
void fn_80033794(Particle* list) {
    FreeParticles(list);
}

// .text:0x800337CC size:0x90
Emitter* fn_800337CC(Emitter* e, s32 n, s32 strict) {
    s32 count = 0;
    Particle* p = lbl_803CBC74;
    Particle* last = NULL;
    if (e != NULL) {
        while (p != NULL && n != 0) {
            last = p;
            p = p->next;
            count++;
            n--;
        }
        if (strict && n != 0) {
            return NULL;
        }
        e->count = count;
        if (count != 0) {
            e->particles = lbl_803CBC74;
            lbl_803CBC74 = p;
            if (last != NULL) {
                last->next = NULL;
            }
        } else {
            e->particles = NULL;
        }
    }
    return e;
}

// .text:0x8003385C size:0xCC
void pitchingMachinePitching(u8 type) {
    Emitter* e = EMITTER_HEAD->next;
    while (e != NULL) {
        Emitter* found = e->type == type ? e : NULL;
        e = e->next;
        if (found != NULL) {
            FreeEmitter(found);
        }
    }
}

// .text:0x80033928 size:0x3C
s32 fn_80033928(u8 type) {
    Emitter* e;
    for (e = EMITTER_HEAD->next; e != NULL; e = e->next) {
        if (e->type == type) {
            return 1;
        }
    }
    return 0;
}

// .text:0x80033964 size:0x8C
void fn_80033964(Emitter* e) {
    FreeEmitter(e);
}

// .text:0x800339F0 size:0x34
Emitter* fn_800339F0(Emitter* after, u8 type) {
    return FindEmitter(after, type);
}

// .text:0x80033A24 size:0x134
Emitter* fn_80033A24(EmitterUpdateFn update, u8 priority, s32 unk14, s32 n, s32 strict, u8 type) {
    Emitter* e = fn_800337CC(lbl_803CBC80, n, strict);
    Emitter* at;
    if (e == NULL) {
        return NULL;
    }
    lbl_803CBC80 = lbl_803CBC80->next;
    e->update = update;
    e->priority = priority;
    e->type = type;
    e->active = 1;
    e->unk14 = unk14;
    e->next = NULL;
    e->prev = NULL;
    at = EMITTER_HEAD;
    while (at->next != NULL && at->next->priority < e->priority) {
        at = at->next;
    }
    e->next = at->next;
    if (e->next != NULL) {
        e->next->prev = e;
    }
    e->prev = at;
    at->next = e;
    return e;
}

// .text:0x80033B58 size:0x170
void fn_80033B58(TexArchive* arc, s32 idx, GXTexWrapMode wrapS, GXTexWrapMode wrapT) {
    LoadParticleTex(arc, idx, wrapS, wrapT);
}

// .text:0x80033CC8 size:0x29C
void fn_80033CC8(Particle* p, TexArchive* arc) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    TexImage* img;
    s32 tex = p->texIndex;
    Vec* corner;
    s32 i;

    if (arc == NULL) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    } else {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
        img = &arc->entries[arc->entries[tex].index].img;
        if (img->tlut != NULL) {
            GXInitTexObjCI(&texObj, img->data, img->width, img->height, img->format, GX_CLAMP, GX_CLAMP, GX_FALSE, 0);
            GXInitTlutObj(&tlutObj, img->tlut, img->tlutFormat, img->tlutEntries);
            GXLoadTlut(&tlutObj, GX_TLUT0);
        } else {
            GXInitTexObj(&texObj, img->data, img->width, img->height, img->format, GX_CLAMP, GX_CLAMP, GX_FALSE);
        }
        GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, (f32)img->minLOD, (f32)img->maxLOD, img->lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&texObj, GX_TEXMAP1);
    }
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    corner = lbl_80180010;
    for (i = 0; i < 4; i++) {
        GXPosition3f32(p->pos.x + corner[i].x, p->pos.y + corner[i].y, p->pos.z + corner[i].z);
        GXColor1u32(p->color.rgba);
        GXTexCoord2f32(lbl_800F7860[p->uvFrame + i].u, lbl_800F7860[p->uvFrame + i].v);
    }
}

// .text:0x80033F64 size:0xD8
void fn_80033F64(f32 width, f32 height, f32 angleDeg) {
    Mtx m;
    Mtx rot;
    s32 i;
    f32 x1;
    f32 y0;
    f32 x0;
    f32 y1;

    x1 = 0.5f * width;
    x0 = 0.5f * -width;
    y0 = 0.5f * -height;
    y1 = 0.5f * height;
    lbl_80180010[0].z = 0.0f;
    lbl_80180010[0].x = x0;
    lbl_80180010[0].y = y0;
    lbl_80180010[1].x = x1;
    lbl_80180010[1].y = y0;
    lbl_80180010[1].z = 0.0f;
    lbl_80180010[2].x = x1;
    lbl_80180010[2].y = y1;
    lbl_80180010[2].z = 0.0f;
    lbl_80180010[3].x = x0;
    lbl_80180010[3].y = y1;
    lbl_80180010[3].z = 0.0f;
    PSMTXRotRad(rot, 'z', 0.017453292f * angleDeg);
    PSMTXConcat(lbl_8017FF78[0], rot, m);
    for (i = 0; i < 4; i++) {
        PSMTXMultVec(m, &lbl_80180010[i], &lbl_80180010[i]);
    }
}

// .text:0x8003403C size:0xB8
void fn_8003403C(f32 width, f32 height) {
    s32 i;
    f32 x1;
    f32 x0;
    f32 y0;
    f32 y1;

    x1 = 0.5f * width;
    x0 = 0.5f * -width;
    y0 = 0.5f * -height;
    y1 = 0.5f * height;
    lbl_80180010[0].z = 0.0f;
    lbl_80180010[0].x = x0;
    lbl_80180010[0].y = y0;
    lbl_80180010[1].x = x1;
    lbl_80180010[1].y = y0;
    lbl_80180010[1].z = 0.0f;
    lbl_80180010[2].x = x1;
    lbl_80180010[2].y = y1;
    lbl_80180010[2].z = 0.0f;
    lbl_80180010[3].x = x0;
    lbl_80180010[3].y = y1;
    lbl_80180010[3].z = 0.0f;
    for (i = 0; i < 4; i++) {
        PSMTXMultVec(lbl_8017FF78[0], &lbl_80180010[i], &lbl_80180010[i]);
    }
}

// .text:0x800340F4 size:0x2C
void fn_800340F4(Mtx m) {
    PSMTXCopy(lbl_8017FF78[0], m);
}

// .text:0x80034120 size:0x2C
void fn_80034120(Mtx m) {
    PSMTXCopy(lbl_8017FFE0, m);
}

// .text:0x8003414C size:0xD4
// NONMATCHING 43%: the original addresses these file-static bss objects off one base (lbl_8017EC00 + offset); needs the .bss split into this unit
#if NONMATCHING
void fn_8003414C(Mtx view) {
    s32 i;

    PSMTXCopy(view, lbl_8017FFE0);
    fn_800118AC(view, lbl_8017FF78[1]);
    PSMTXCopy(lbl_8017FF78[1], lbl_8017FF78[0]);
    lbl_8017FF78[0][2][3] = 0.0f;
    lbl_8017FF78[0][1][3] = 0.0f;
    lbl_8017FF78[0][0][3] = 0.0f;
    lbl_80180010[0].x = -0.5f;
    lbl_80180010[0].y = -0.5f;
    lbl_80180010[0].z = 0.0f;
    lbl_80180010[1].x = 0.5f;
    lbl_80180010[1].y = -0.5f;
    lbl_80180010[1].z = 0.0f;
    lbl_80180010[2].x = 0.5f;
    lbl_80180010[2].y = 0.5f;
    lbl_80180010[2].z = 0.0f;
    lbl_80180010[3].x = -0.5f;
    lbl_80180010[3].y = 0.5f;
    lbl_80180010[3].z = 0.0f;
    for (i = 0; i < 4; i++) {
        PSMTXMultVec(lbl_8017FF78[0], &lbl_80180010[i], &lbl_80180010[i]);
    }
}
#endif

// .text:0x80034220 size:0x30C
// NONMATCHING 82%: r3/r4 swapped in the pool-link loop, mr before the cos loop
#if NONMATCHING
void minigamesSetSomePointers(void) {
    s32 i;
    f32* t;

    lbl_803CBC78 = 1;
    memset(lbl_80180040, 0, sizeof(lbl_80180040));
    for (i = 0; i < 0x13FF; i++) {
        lbl_80180040[i].next = &lbl_80180040[i + 1];
    }
    lbl_803CBC74 = lbl_80180040;
    lbl_803CBC78 = 0;
    lbl_803CBC84.prev = NULL;
    lbl_803CBC84.next = NULL;
    memset(lbl_801F8040, 0, sizeof(lbl_801F8040));
    for (i = 0; i < 0xF; i++) {
        lbl_801F8040[i].next = &lbl_801F8040[i + 1];
    }
    lbl_803CBC80 = lbl_801F8040;
    t = lbl_8017ED68;
    i = 0;
    do {
        *t = cos((3.141592654 * i) / 1025.0);
        i++;
        t++;
    } while (i < 0x401);
    lbl_803CBC7C = 0;
}
#endif

// .text:0x8003452C size:0x39C
void minigamesGXStuff(void) {
    GXTexObj texObj;
    Emitter* e;
    Emitter* dead;
    s32 done;

    if (lbl_803CBC78 != 0) {
        lbl_803CBC78 = 0;
        e = lbl_803CBC84.next;
        while (e != NULL) {
            dead = e;
            e = e->next;
            FreeEmitter(dead);
        }
        lbl_803CBC84.next = NULL;
        return;
    }
    if (lbl_803CBC84.next == NULL) {
        return;
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    // 1 is the SDK GX_TG_MTX2x4 (GXEnum.h has the 2x4/3x4 names swapped)
    GXSetTexCoordGen2(GX_TEXCOORD0, (GXTexGenType)1, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetCullMode(GX_CULL_NONE);
    GXInitTexObj(&texObj, lbl_800F7840, 4, 4, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetProjection(fn_80052734(fn_8005268C()), GX_PERSPECTIVE);
    GXLoadPosMtxImm(lbl_8017FFE0, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    SetFogNone();
    // done/dead deliberately carry over between iterations (as in the original)
    for (e = lbl_803CBC84.next; e != NULL;) {
        if (e->update != NULL) {
            done = e->update(e);
            if (done) {
                dead = e;
            }
        }
        e = e->next;
        if (done) {
            FreeEmitter(dead);
        }
    }
}

// .text:0x800348C8 size:0x304
// NONMATCHING 98%: extra mr for the cos table pointer
#if NONMATCHING
void minigamesSetSomePointers2(void) {
    s32 i;
    f32* t;

    memset(lbl_80180040, 0, sizeof(lbl_80180040));
    for (i = 0; i < 0x13FF; i++) {
        lbl_80180040[i].next = &lbl_80180040[i + 1];
    }
    lbl_803CBC74 = lbl_80180040;
    lbl_803CBC78 = 0;
    lbl_803CBC84.prev = NULL;
    lbl_803CBC84.next = NULL;
    memset(lbl_801F8040, 0, sizeof(lbl_801F8040));
    for (i = 0; i < 0xF; i++) {
        lbl_801F8040[i].next = &lbl_801F8040[i + 1];
    }
    lbl_803CBC80 = lbl_801F8040;
    t = lbl_8017ED68;
    i = 0;
    do {
        *t = cos((3.141592654 * i) / 1025.0);
        i++;
        t++;
    } while (i < 0x401);
    lbl_803CBC7C = 0;
}
#endif

// .text:0x80034BCC size:0x120
s32 fn_80034BCC(SpaniAttach* a) {
    SpaniObj* o;
    u8* col;

    for (o = lbl_803CBC9C->unk8; o != NULL; o = o->unk4) {
        if (((SpaniObj*)o->parent)->animId == a->key[0] && o->unk72 == a->key[1]) {
            PSMTXCopy(a->mtx, o->mtx2);
            // TODO type: unk58/unk74 are RGBA colors in SpaniObj
            col = (u8*)&o->unk74;
            col[0] = (a->color[0] * ((u8*)&o->unk58)[0]) / 255;
            col[1] = (a->color[1] * ((u8*)&o->unk58)[1]) / 255;
            col[2] = (a->color[2] * ((u8*)&o->unk58)[2]) / 255;
            col[3] = (a->color[3] * ((u8*)&o->unk58)[3]) / 255;
            o->unkA8 = 1;
        }
    }
    return 0;
}

// .text:0x80034CEC size:0x134
void fn_80034CEC(SpaniGroup* g) {
    s32 base = g->baseIdx;
    s32 i;
    s32 dst;

    for (i = 0; i < g->count; i++) {
        if (lbl_80371C30[base + i].obj != NULL) {
            lbl_80371C30[base + i].obj->flags = 0;
        }
    }
    dst = base;
    for (i += base; i < 0x360; i++, dst++) {
        lbl_80371C30[dst].obj = lbl_80371C30[i].obj;
        lbl_80371C30[dst].owner = lbl_80371C30[i].owner;
        if (lbl_80371C30[dst].owner != NULL) {
            lbl_80371C30[dst].owner->baseIdx = dst;
        }
    }
    for (i = dst; i < 0x360; i++) {
        lbl_80371C30[i].obj = NULL;
        lbl_80371C30[i].owner = NULL;
    }
}

// .text:0x80034E20 size:0x130
void fn_80034E20(SpaniGroup* g, SpaniDesc* descs) {
    SpaniDesc* d;
    SpaniSlot* base;
    s32 n = 0;
    s32 i;
    s32 k;
    SpaniObj* obj;
    s32 idx;

    for (i = 0; i < 0x360; i++) {
        if (lbl_80371C30[i].obj == NULL) {
            g->baseIdx = i;
            base = &lbl_80371C30[i];
            base->owner = g;
            break;
        }
    }
    d = descs;
    for (;;) {
        idx = n + i;
        if (d->type == 3) {
            break;
        }
        lbl_80371C30[idx].obj = fn_80034F50(d);
        obj = lbl_80371C30[idx].obj;
        // TODO type: SpaniDesc.unk12 is the parent's index within the group (0xFF: none)
        if (*(s16*)d->unk12 == 0xFF || n == 0) {
            obj->parent = NULL;
        } else {
            obj->parent = base[*(s16*)d->unk12].obj;
            obj->unk4 = ((SpaniObj*)obj->parent)->unk8;
            ((SpaniObj*)obj->parent)->unk8 = obj;
        }
        for (k = 0; k < SPANI_TEX_OVERRIDE_COUNT; k++) {
            obj->texOverride[k] = 0xFFFF;
        }
        d++;
        n++;
    }
    g->count = n;
}
