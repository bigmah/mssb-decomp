#include "main/file_800BDEA0.h"
#include "main/file_800B9974.h" // GQRSetup5-7
#include "Dolphin/os.h"
#include "Dolphin/stl.h"

extern const f32 lbl_803CBB68; // 20.0f
extern const f32 lbl_803CD068; // 1e8f
extern const f32 lbl_803CD06C; // -1e8f
extern const f32 lbl_803CD070; // 0.0f
extern const f32 lbl_803CD074; // 640.0f
extern const f32 lbl_803CD078; // 480.0f
extern const f32 lbl_803CD07C; // 1.0f
extern const f32 lbl_803CD080; // 448.0f
extern const f32 lbl_803CD084; // 512.0f
extern const f32 lbl_803CD088; // 1280.0f
extern const f32 lbl_803CD08C; // 100.0f
extern const f32 lbl_803CD090; // 1.4f
extern const f32 lbl_803CD094; // 15.0f
extern const f32 lbl_803CD098; // 0.5f
extern const f32 lbl_803CD09C; // 10.0f
extern const f32 lbl_803CD0A0; // 23.0f
extern const f32 lbl_803CD0A4; // 2.5f
extern const f32 lbl_803CD0A8; // 2.0f
extern const f32 lbl_803CD0AC; // -20.0f
extern const f32 lbl_803CD0B0; // -1.0f
extern const f32 lbl_803CD0B4; // 12.0f
extern const f32 lbl_803CD0C0; // 10000.0f
extern const f32 lbl_803CD0C4; // -10000.0f
extern const f32 lbl_803CD0C8; // -68.0f
extern const f32 lbl_803CD0CC; // 68.0f
extern const f32 lbl_803CD0D0; // -36.0f
extern const f32 lbl_803CD0D4; // 0.175f
extern const f32 lbl_803CD0D8; // 0.25f
extern const f32 lbl_803CD0DC; // 50.0f

extern void* lbl_803CB724[4];          // SKBuffers: locked-cache work buffers
extern SKAccBuffer lbl_803CB6FC[2];    // SKAccBuffers


// Bump allocator state (see fn_800AD054 / file_80008E00.c).
typedef struct ShadowArena {
    /* 0x00 */ u32 remaining;
    /* 0x04 */ u8* cur;
    /* 0x08 */ u8* end;
} ShadowArena;
extern ShadowArena lbl_803C7898;

typedef struct ShadowHeapInfo {
    /* 0x00 */ u8 pad0[0x50];
    /* 0x50 */ void* arenaStart;
    /* 0x54 */ void* arenaEnd;
    /* 0x58 */ u32 arenaSize;
} ShadowHeapInfo;
extern ShadowHeapInfo lbl_803C7420;

typedef struct ShadowDirTable {
    Vec dirs[4];
} ShadowDirTable;
extern const ShadowDirTable lbl_800E8030;

void fn_800AD054(void* start, void* end);

#if NONMATCHING
static u8 sSKNPosNrmShift; // GQR6 scale used by the portable s16 skinning kernels
#endif

#ifdef __MWERKS__
#define ABS(x) __abs(x)
#else
#define ABS(x) ((x) < 0 ? -(x) : (x))
#endif

void fn_800BE158(ShadowCamera* shadow, ShadowCamera* cam);
void fn_800BE498(Mtx view, f32 width, f32 height, f32 near, f32 far, f32 depth);

// .text:0x800BDEA0 size:0xD0
void fn_800BDEA0(void) {
    ShadowState* state = &lbl_803009F8;

    if (state->enabled) {
        if (state->endCallback != NULL) {
            state->endCallback(state->cameras->view, 0);
        }
        GXSetTexCopySrc(0, 0, 640, 448);
        GXSetTexCopyDst(640, 480, GX_CTF_R4, GX_FALSE);
        GXCopyTex(lbl_803009F8.images[0], GX_TRUE);
        GXPixModeSync();
        lbl_803009F8.numPoints = 0;
        lbl_803009F8.minX = lbl_803009F8.minY = lbl_803009F8.minZ = lbl_803CD068;
        lbl_803009F8.maxX = lbl_803009F8.maxY = lbl_803009F8.maxZ = lbl_803CD06C;
        lbl_803009F8.sum.x = lbl_803009F8.sum.y = lbl_803009F8.sum.z = lbl_803CD070;
    }
}

// .text:0x800BDF70 size:0x70
void fn_800BDF70(ActorObject* obj) {
    ShadowState* state = &lbl_803009F8;
    u8 flags;

    if (state->enabled && state->drawCallback != NULL && obj->animateBones) {
        flags = obj->actor->flags98;
        if ((flags & 0x24) && (flags & 0x12)) {
            state->drawCallback(obj, state->cameras->view);
        }
    }
}

// .text:0x800BDFE0 size:0xBC
// NONMATCHING 95%: table/index saved registers swapped (r28/r29)
#if NONMATCHING
void fn_800BDFE0(ActorObjectTable* table) {
    ShadowState* state = &lbl_803009F8;
    s32 i;
    u8 flags;

    if (state->enabled && state->drawCallback != NULL) {
        for (i = 0; i < table->count; i++) {
            if (table->objects[i].animateBones) {
                flags = table->objects[i].actor->flags98;
                if ((flags & 0x24) && (flags & 0x12)) {
                    state->drawCallback(&table->objects[i], state->cameras->view);
                }
            }
        }
    }
}
#endif

// .text:0x800BE09C size:0xBC
// NONMATCHING 99.8%: shadow-state address lands in r3 instead of r4 before the begin callback
#if NONMATCHING
void fn_800BE09C(void* arg, ShadowCamera* cam) {
    if (lbl_803009F8.enabled) {
        GXSetScissor(2, 2, 636, 476);
        GXSetViewport(lbl_803CD070, lbl_803CD070, lbl_803CD074, lbl_803CD078, lbl_803CD070, lbl_803CD07C);
        if (lbl_803009F8.beginCallback != NULL) {
            lbl_803009F8.beginCallback(&arg);
        }
        fn_800BE498(cam->view, lbl_803CD074, lbl_803CD080, lbl_803CD07C, lbl_803CD084, lbl_803CD088);
        fn_800BE158(lbl_803009F8.cameras, cam);
    }
}
#endif

// .text:0x800BE158 size:0x340
// NONMATCHING 99%: f-register allocation; int->float magic constant is DATA (no .sdata2 split)
#if NONMATCHING
void fn_800BE158(ShadowCamera* shadow, ShadowCamera* cam) {
    Vec ground;
    f32 t;
    f32 dist;
    f32 size;
    f32 height;
    f32 w;
    f32 h;
    f32 neg;

    // Point where the view ray from the camera eye to its target hits y = 0.
    t = cam->eye.y / (cam->eye.y - cam->target.y);
    PSVECSubtract(&cam->target, &cam->eye, &ground);
    PSVECScale(&ground, t, &ground);
    dist = PSVECMag(&ground);
    PSVECAdd(&cam->eye, &ground, &ground);

    height = lbl_803CD08C;
    if (lbl_803009F8.numPoints != 0) {
        w = ABS((s32)(lbl_803009F8.maxX - lbl_803009F8.minX));
        h = ABS((s32)(lbl_803009F8.maxZ - lbl_803009F8.minZ));
        if (w >= h) {
            size = w;
        } else {
            size = h;
        }
        size /= lbl_803CD090;
        if (size < lbl_803CD094) {
            size = lbl_803CD094;
        }
        shadow->target.x = (lbl_803009F8.minX + lbl_803009F8.maxX) * lbl_803CD098;
        shadow->target.y = lbl_803CD070;
        shadow->target.z = (lbl_803009F8.minZ + lbl_803009F8.maxZ) * lbl_803CD098;
    } else {
        size = lbl_803CD09C;
        shadow->target.x = lbl_803CD070;
        shadow->target.y = lbl_803CD070;
        shadow->target.z = lbl_803CD070;
    }

    if (size < lbl_803CBB68 || dist > lbl_803CD0A0) {
        neg = -size;
        C_MTXOrtho(shadow->proj, neg, size, size, neg, shadow->near, shadow->far);
        GXSetProjection(shadow->proj, GX_ORTHOGRAPHIC);
        C_MTXLightOrtho(shadow->texMtx, size, neg, size, neg, lbl_803CD098, lbl_803CD098, lbl_803CD098, lbl_803CD098);
    } else {
        t = lbl_803CD0A4 * (cam->eye.y - lbl_803CD0A8);
        height = t;
        if (t > lbl_803CD0AC) {
            height = lbl_803CD0AC;
        }
        shadow->target.x = ground.x;
        shadow->target.y = lbl_803CD070;
        shadow->target.z = ground.z;
        neg = -lbl_803CD0B4;
        height *= lbl_803CD0B0;
        C_MTXOrtho(shadow->proj, neg, lbl_803CD0B4, lbl_803CD0B4, neg, shadow->near, shadow->far);
        GXSetProjection(shadow->proj, GX_ORTHOGRAPHIC);
        C_MTXLightOrtho(shadow->texMtx, lbl_803CD0B4, neg, lbl_803CD0B4, neg, lbl_803CD098, lbl_803CD098, lbl_803CD098,
                        lbl_803CD098);
    }
    PSVECScale(&shadow->dir, height, &ground);
    PSVECAdd(&shadow->target, &ground, &shadow->eye);
    shadow->up.y = lbl_803009F8.upSign;
    C_MTXLookAt(shadow->view, &shadow->eye, &shadow->up, &shadow->target);
    PSMTXConcat(shadow->texMtx, shadow->view, shadow->texMtx);
}
#endif

// .text:0x800BE498 size:0x56C
// NONMATCHING 90%: original reuses param f-regs (one fewer saved FPR), stray frsp on -far
#if NONMATCHING
void fn_800BE498(Mtx view, f32 width, f32 height, f32 near, f32 far, f32 depth) {
    Mtx inv;
    Vec dir[4];    // frustum edge directions; reused as the bounds min (dir[0]) / max (dir[1])
    Vec pos[4];    // frustum edge origins, then the ground hit points
    Vec down;
    Vec origin;
    f32 t[4];
    f32 dot;
    f32 hwNear;
    f32 hhNear;
    f32 hwFar;
    f32 hhFar;
    f32 zNear;
    f32 zFar;
    s32 i;

    if (lbl_803009F8.flags & 0x40) {
        return;
    }
    origin.x = lbl_803CD070;
    origin.y = lbl_803CD070;
    origin.z = lbl_803CD070;
    down.x = lbl_803CD070;
    down.y = lbl_803CD0B0;
    down.z = lbl_803CD070;
    PSMTXMultVec(view, &origin, &origin);
    PSMTXMultVec(view, &down, &down);
    PSVECSubtract(&down, &origin, &down);
    if (lbl_803CD070 == PSVECMag(&down)) {
        return;
    }
    PSVECNormalize(&down, &down);
    dot = PSVECDotProduct(&down, &origin);

    zFar = -far;
    hhNear = ((height * near) / depth) * lbl_803CD098;
    hhFar = ((height * far) / depth) * lbl_803CD098;
    hwNear = ((width * near) / depth) * lbl_803CD098;
    hwFar = ((width * far) / depth) * lbl_803CD098;
    zNear = -near;
    pos[0].x = hwNear;
    pos[0].y = lbl_803CD070;
    pos[0].z = zNear;
    pos[1].x = hwFar;
    pos[1].y = lbl_803CD070;
    pos[1].z = zFar;
    pos[2].x = hwFar;
    pos[2].y = hhFar;
    pos[2].z = zFar;
    pos[3].x = hwFar;
    pos[3].y = -hhFar;
    pos[3].z = zFar;
    dir[0].x = lbl_803CD070;
    dir[0].y = hhNear;
    dir[0].z = lbl_803CD070;
    dir[1].x = lbl_803CD070;
    dir[1].y = hhFar;
    dir[1].z = lbl_803CD070;
    dir[2].x = hwNear - hwFar;
    dir[2].y = hhNear - hhFar;
    dir[2].z = zNear - zFar;
    dir[3].x = hwNear - hwFar;
    dir[3].y = -(hhNear - hhFar);
    dir[3].z = zNear - zFar;

    for (i = 0; i < 4; i++) {
        t[i] = PSVECDotProduct(&down, &dir[i]);
        if (lbl_803CD070 == t[i]) {
            dir[i].z = lbl_803CD070;
        } else {
            t[i] = -(-dot + PSVECDotProduct(&down, &pos[i])) / t[i];
            PSVECScale(&dir[i], t[i], &dir[i]);
            PSVECAdd(&pos[i], &dir[i], &dir[i]);
        }
        if (t[i] < lbl_803CD070) {
            t[i] = -t[i];
        }
    }

    if (dir[2].z <= zNear && dir[2].z >= zFar && dir[3].z <= zNear && dir[3].z >= zFar) {
        memcpy(&dir[0], &dir[2], sizeof(Vec));
        memcpy(&dir[1], &dir[3], sizeof(Vec));
    } else if (!(t[0] <= lbl_803CD07C && t[1] <= lbl_803CD07C)) {
        if (t[0] <= lbl_803CD07C || t[1] <= lbl_803CD07C) {
            if (dir[2].z <= zNear && dir[2].z >= zFar) {
                memcpy(&dir[3], &dir[2], sizeof(Vec));
            }
            if (t[0] < lbl_803CD07C) {
                memcpy(&dir[1], &dir[3], sizeof(Vec));
            } else {
                memcpy(&dir[0], &dir[3], sizeof(Vec));
            }
        } else {
            return;
        }
    }

    PSMTXInverse(view, inv);
    PSMTXMultVec(inv, &dir[1], &pos[3]);
    dir[2].x = -dir[1].x;
    dir[2].y = dir[1].y;
    dir[2].z = dir[1].z;
    PSMTXMultVec(inv, &dir[2], &pos[0]);
    PSMTXMultVec(inv, &dir[0], &pos[2]);
    dir[2].x = -dir[0].x;
    dir[2].y = dir[0].y;
    dir[2].z = dir[0].z;
    PSMTXMultVec(inv, &dir[2], &pos[1]);

    dir[0].x = lbl_803CD0C0;
    dir[0].z = lbl_803CD0C0;
    dir[1].x = lbl_803CD0C4;
    dir[1].z = lbl_803CD0C4;
    for (i = 0; i < 4; i++) {
        if (pos[i].x < dir[0].x) {
            dir[0].x = pos[i].x;
        }
        if (pos[i].x > dir[1].x) {
            dir[1].x = pos[i].x;
        }
        if (pos[i].z < dir[0].z) {
            dir[0].z = pos[i].z;
        }
        if (pos[i].z > dir[1].z) {
            dir[1].z = pos[i].z;
        }
    }
    lbl_803009F8.minX = dir[0].x;
    lbl_803009F8.maxX = dir[1].x;
    lbl_803009F8.minZ = dir[0].z;
    lbl_803009F8.maxZ = dir[1].z;
    if (lbl_803009F8.minX < lbl_803CD0C8) {
        lbl_803009F8.minX = lbl_803CD0C8;
    }
    if (lbl_803009F8.maxX > lbl_803CD0CC) {
        lbl_803009F8.maxX = lbl_803CD0CC;
    }
    if (lbl_803009F8.minZ < lbl_803CD0D0) {
        lbl_803009F8.minZ = lbl_803CD0D0;
    }
    if (lbl_803009F8.maxZ > lbl_803CD08C) {
        lbl_803009F8.maxZ = lbl_803CD08C;
    }
}
#endif

// .text:0x800BEA04 size:0x138
void fn_800BEA04(Vec point) {
    lbl_803009F8.minX = (lbl_803009F8.minX <= point.x) ? lbl_803009F8.minX : point.x;
    lbl_803009F8.maxX = (lbl_803009F8.maxX >= point.x) ? lbl_803009F8.maxX : point.x;
    lbl_803009F8.minY = (lbl_803009F8.minY <= point.y) ? lbl_803009F8.minY : point.y;
    lbl_803009F8.maxY = (lbl_803009F8.maxY >= point.y) ? lbl_803009F8.maxY : point.y;
    lbl_803009F8.minZ = (lbl_803009F8.minZ <= point.z) ? lbl_803009F8.minZ : point.z;
    lbl_803009F8.maxZ = (lbl_803009F8.maxZ >= point.z) ? lbl_803009F8.maxZ : point.z;
    PSVECAdd(&lbl_803009F8.sum, &point, &lbl_803009F8.sum);
    lbl_803009F8.numPoints++;
}

// fn_800BEB3C, size:0x44
void fn_800BEB3C(void) {
    lbl_803009F8.numPoints = 0;
    lbl_803009F8.minX = lbl_803009F8.minY = lbl_803009F8.minZ = lbl_803CD068;
    lbl_803009F8.maxX = lbl_803009F8.maxY = lbl_803009F8.maxZ = lbl_803CD06C;
    lbl_803009F8.sum.x = lbl_803009F8.sum.y = lbl_803009F8.sum.z = lbl_803CD070;
}

// fn_800BEBA0, size:0x10
u8 fn_800BEBA0(void) {
    return lbl_803009F8.enabled;
}

// GetDrawShadows, size:0x10
u8 GetDrawShadows(void) {
    return lbl_803009F8.enabled;
}

// fn_800BEB80, size:0x20
MtxPtr fn_800BEB80(u8 index) {
    return lbl_803009F8.cameras[index].texMtx;
}

// DrawShadows, size:0xC
void DrawShadows(u8 enable) {
    lbl_803009F8.enabled = enable;
}

// fn_800BEC00, size:0x30
void fn_800BEC00(s32 reverse) {
    if (reverse != 0) {
        lbl_803009F8.upSign = -1;
        return;
    }
    lbl_803009F8.upSign = 1;
}

// .text:0x800BEBCC size:0x34
void fn_800BEBCC(u8 index, Vec dir) {
    lbl_803009F8.cameras[index].dir = dir;
}

// .text:0x800BEC30 size:0x3D8
// NONMATCHING 99%: register allocation of the arena pointers and the rodata Vec copy
#if NONMATCHING
void fn_800BEC30(u8 numCameras) {
    ShadowDirTable dirs = lbl_800E8030;
    u8* arenaEnd;
    u8* cur;
    u8* end;
    u32 size;
    s32 v;
    s32 i;

    arenaEnd = lbl_803C7898.end;
    cur = (u8*)OSRoundUp32B(lbl_803C7898.cur);
    lbl_803009F8.images = (void**)cur;
    cur = (u8*)OSRoundUp32B(cur + numCameras * sizeof(void*));
    size = GXGetTexBufferSize(640, 480, GX_TF_I4, GX_FALSE, 0);
    lbl_803009F8.images[0] = (void*)OSRoundUp32B(cur);
    cur = (u8*)OSRoundUp32B(size + (u32)lbl_803009F8.images[0]);
    lbl_803009F8.texObjs = (GXTexObj*)OSRoundUp32B(cur);
    cur = (u8*)OSRoundUp32B((u8*)lbl_803009F8.texObjs + numCameras * sizeof(GXTexObj));
    lbl_803009F8.tlut = (GXTlutObj*)OSRoundUp32B(cur);
    cur = (u8*)OSRoundUp32B((u8*)lbl_803009F8.tlut + sizeof(GXTlutObj));
    lbl_803009F8.tlutData = (u16*)OSRoundUp32B(cur);
    cur = (u8*)OSRoundUp32B((u8*)lbl_803009F8.tlutData + 16 * sizeof(u16));
    v = 0x11110;
    do {
        v -= 0x1111;
        lbl_803009F8.tlutData[v & 0xF] = v;
    } while (v != 0);
    lbl_803009F8.cameras = (ShadowCamera*)OSRoundUp32B(cur);
    end = (u8*)OSRoundUp32B((u8*)lbl_803009F8.cameras + numCameras * sizeof(ShadowCamera));
    fn_800AD054(end, arenaEnd);
    lbl_803C7420.arenaStart = end;
    lbl_803C7420.arenaEnd = arenaEnd;
    lbl_803C7420.arenaSize = OSRoundUp32B(arenaEnd - end);
    OSSetArenaLo(arenaEnd);

    for (i = 0; i < numCameras; i++) {
        GXInitTexObjCI(&lbl_803009F8.texObjs[i], lbl_803009F8.images[i], 640, 480, GX_TF_C4, GX_CLAMP, GX_CLAMP,
                       GX_FALSE, GX_TLUT15);
        GXInitTlutObj(lbl_803009F8.tlut, lbl_803009F8.tlutData, GX_TL_IA8, 16);
        GXInitTexObjLOD(&lbl_803009F8.texObjs[i], GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f,
                        GX_FALSE, GX_FALSE, GX_ANISO_1);
        lbl_803009F8.cameras[i].unk28 = lbl_803CD0D4;
        lbl_803009F8.cameras[i].unk24 = lbl_803CD0D8;
        lbl_803009F8.cameras[i].near = lbl_803CD07C;
        lbl_803009F8.cameras[i].far = lbl_803CD084;
        lbl_803009F8.cameras[i].eye.x = lbl_803CD08C;
        lbl_803009F8.cameras[i].eye.y = lbl_803CD08C;
        lbl_803009F8.cameras[i].eye.z = lbl_803CD08C;
        lbl_803009F8.cameras[i].up.x = lbl_803CD070;
        lbl_803009F8.cameras[i].up.y = lbl_803CD07C;
        lbl_803009F8.cameras[i].up.z = lbl_803CD070;
        lbl_803009F8.cameras[i].target.x = lbl_803CD070;
        lbl_803009F8.cameras[i].target.y = lbl_803CD070;
        lbl_803009F8.cameras[i].target.z = lbl_803CD0DC;
        lbl_803009F8.cameras[i].dir = dirs.dirs[i];
    }
    lbl_803009F8.numCameras = numCameras;
    lbl_803009F8.enabled = 0;
    lbl_803009F8.beginCallback = NULL;
    lbl_803009F8.drawCallback = NULL;
    lbl_803009F8.upSign = 1;
}
#endif

// .text:0x800BF008 size:0x30
void fn_800BF008(void) {
    GXLoadTlut(lbl_803009F8.tlut, GX_TLUT15);
}

// fn_800BF038, size:0x10
void fn_800BF038(ShadowEndCallback callback) {
    lbl_803009F8.endCallback = callback;
}

// fn_800BF048, size:0x10
void fn_800BF048(ShadowBeginCallback callback) {
    lbl_803009F8.beginCallback = callback;
}

// fn_800BF058, size:0x10
void fn_800BF058(ShadowDrawCallback callback) {
    lbl_803009F8.drawCallback = callback;
}

// fn_800BF068, size:0xC
ShadowState* fn_800BF068(void) {
    return &lbl_803009F8;
}

// .text:0x800BF074 size:0x130
void SKNLoadFile(SKNHeader* hdr) {
    SKN1List* l1;
    u32 i;
    SKN2List* l2;
    SKNAccList* la;

    if (hdr->sk1ListArray != NULL) {
        hdr->sk1ListArray = (SKN1List*)((u8*)hdr->sk1ListArray + (u32)hdr);
    }
    if (hdr->sk2ListArray != NULL) {
        hdr->sk2ListArray = (SKN2List*)((u8*)hdr->sk2ListArray + (u32)hdr);
    }
    if (hdr->skAccListArray != NULL) {
        hdr->skAccListArray = (SKNAccList*)((u8*)hdr->skAccListArray + (u32)hdr);
    }
    if (hdr->flushIndices != NULL) {
        hdr->flushIndices = (u16*)((u8*)hdr->flushIndices + (u32)hdr);
    }
    for (i = 0; i < hdr->numSk1List; i++) {
        l1 = &hdr->sk1ListArray[i];
        l1->vertSrc = (u8*)l1->vertSrc + (u32)hdr;
    }
    for (i = 0; i < hdr->numSk2List; i++) {
        l2 = &hdr->sk2ListArray[i];
        l2->vertSrc = (u8*)l2->vertSrc + (u32)hdr;
        l2->weights = (u8*)l2->weights + (u32)hdr;
    }
    for (i = 0; i < hdr->numSkAccList; i++) {
        la = &hdr->skAccListArray[i];
        la->vertSrc = (u8*)la->vertSrc + (u32)hdr;
        la->weights = (u8*)la->weights + (u32)hdr;
        la->vertIndices = (u8*)la->vertIndices + (u32)hdr;
    }
    SKNInit();
}

// .text:0x800BF1A4 size:0x1C
#if NONMATCHING
void SKNFlushByIndex1(u16* indices, u32 count, void* base) {
    do {
        DCFlushRange((u8*)base + *indices++ * 0x18, 1);
    } while (--count);
}
#else
asm void SKNFlushByIndex1(register u16* indices, register u32 count, register void* base) {
    nofralloc
    mtctr r4
    subi r3, r3, 0x2
L_800BF1AC:
    lhzu r6, 0x2(r3)
    mulli r7, r6, 0x18
    dcbf r7, r5
    bdnz L_800BF1AC
    blr
}
#endif

// .text:0x800BF1C0 size:0x28
#if NONMATCHING
void SKNFlushByIndex2(u16* indices, u32 count, void* base) {
    do {
        DCFlushRange((u8*)base + *indices++ * 0xC, 1);
    } while (--count);
}
#else
asm void SKNFlushByIndex2(register u16* indices, register u32 count, register void* base) {
    nofralloc
    mtctr r4
    subi r3, r3, 0x2
L_800BF1C8:
    lhzu r6, 0x2(r3)
    add r7, r6, r6
    add r6, r7, r6
    add r6, r6, r6
    add r6, r6, r6
    dcbf r6, r5
    bdnz L_800BF1C8
    blr
}
#endif

// .text:0x800BF1E8 size:0x1C
#if NONMATCHING
void SKNBzero32B(void* base, u32 size) {
    u32 n = size >> 5;

    do {
        memset(base, 0, 32);
        base = (u8*)base + 32;
    } while (--n);
}
#else
asm void SKNBzero32B(register void* base, register u32 size) {
    nofralloc
    li r0, 0x0
    srwi r4, r4, 5
    mtctr r4
L_800BF1F4:
    dcbz r0, r3
    addi r3, r3, 0x20
    bdnz L_800BF1F4
    blr
}
#endif

// .text:0x800BF204 size:0xA4
void SKNInit(void) {
    if (!(PPCMfhid2() & 0x10000000)) {
        DCInvalidateRange((void*)0xE0000000, 0x4000);
        LCEnable();
    }
    lbl_803CB724[0] = (void*)0xE0000000;
    lbl_803CB724[1] = (void*)0xE0001000;
    lbl_803CB724[2] = (void*)0xE0002000;
    lbl_803CB724[3] = (void*)0xE0003000;
    lbl_803CB6FC[0].src = (void*)0xE0000000;
    lbl_803CB6FC[0].indices = (void*)0xE0001000;
    lbl_803CB6FC[0].weights = (void*)0xE0001800;
    lbl_803CB6FC[1].src = (void*)0xE0002000;
    lbl_803CB6FC[1].indices = (void*)0xE0003000;
    lbl_803CB6FC[1].weights = (void*)0xE0003800;
    GQRSetup5(8, 4, 8, 4);
}

// Locked-cache helpers (charPipeline skinning.h); vertex size is 0x18 (f32) or 0xC (s16).
static inline u32 SKNLCTouchData(u8 buffer, void* data, u32 size) {
    LCLoadData(lbl_803CB724[buffer], data, size);
    return size;
}

static inline u32 SKNLC2TouchData(u8 buffer, void* data, u32 size) {
    size = (size + 0x1F) >> 5;
    LCLoadBlocks(lbl_803CB724[buffer], data, size);
    return size;
}

static inline void SKNLCAccTouchData(u8 buffer, void* src, void* indices, void* weights, u32 count, u32 vtxSize) {
    u32 size = (count * vtxSize + 0x1F) >> 5;

    LCLoadBlocks(lbl_803CB6FC[buffer].src, src, size);
    size = (count * 2 + 0x1F) >> 5;
    LCLoadBlocks(lbl_803CB6FC[buffer].indices, indices, size);
    LCLoadBlocks(lbl_803CB6FC[buffer].weights, weights, (count + 0x1F) >> 5);
}

// .text:0x800BF2A8 size:0x5F4
// NONMATCHING 90.6%: scheduling/regalloc in the sk2 and acc double-buffer loops
#if NONMATCHING
void fn_800BF2A8(SKNBone** bones, SKNHeader* hdr, u8* base) {
    u16 sizes[2];
    u32 i;
    SKN1List* l1;
    SKN2List* l2;
    SKNAccList* la;

    GQRSetup6(hdr->posNrmShift, 7, hdr->posNrmShift, 7);
    sSKNPosNrmShift = hdr->posNrmShift;

    if (hdr->numSk1List != 0) {
        sizes[0] = SKNLCTouchData(0, hdr->sk1ListArray[0].vertSrc,
                                  hdr->sk1ListArray[0].count * 0xC + hdr->sk1ListArray[0].vertSrcOffset);
        for (i = 0; i < hdr->numSk1List - 1; i++) {
            sizes[(i + 1) & 1] = SKNLCTouchData(((i + 1) & 1) * 2, hdr->sk1ListArray[i + 1].vertSrc,
                                                hdr->sk1ListArray[i + 1].count * 0xC + hdr->sk1ListArray[i + 1].vertSrcOffset);
            l1 = &hdr->sk1ListArray[i];
            PSMTXReorder(bones[l1->boneIndex]->skinMtx, l1->m);
            LCQueueWait(1);
            fn_800BFF9C(l1->m, (s16*)((u8*)lbl_803CB724[(i & 1) * 2] + l1->vertSrcOffset),
                          (s16*)((u8*)lbl_803CB724[(i & 1) * 2] + l1->vertSrcOffset), l1->count);
        LCStoreData(l1->vertDst + base, lbl_803CB724[(i & 1) * 2], sizes[i & 1]);
        }
        l1 = &hdr->sk1ListArray[i];
        PSMTXReorder(bones[l1->boneIndex]->skinMtx, l1->m);
        fn_800BFF9C(l1->m, (s16*)((u8*)lbl_803CB724[(i & 1) * 2] + l1->vertSrcOffset),
                          (s16*)((u8*)lbl_803CB724[(i & 1) * 2] + l1->vertSrcOffset), l1->count);
        LCStoreData(l1->vertDst + base, lbl_803CB724[(i & 1) * 2], sizes[i & 1]);
    }

    if (hdr->numSk2List != 0) {
        sizes[0] = SKNLC2TouchData(0, hdr->sk2ListArray[0].vertSrc,
                                   hdr->sk2ListArray[0].count * 0xC + hdr->sk2ListArray[0].vertSrcOffset);
        SKNLC2TouchData(1, hdr->sk2ListArray[0].weights, hdr->sk2ListArray[0].count * 2);
        for (i = 0; i < hdr->numSk2List - 1; i++) {
            l2 = &hdr->sk2ListArray[i];
            sizes[(i + 1) & 1] = SKNLC2TouchData(((i + 1) & 1) * 2, l2[1].vertSrc, l2[1].vertSrcOffset + l2[1].count * 0xC);
            SKNLC2TouchData(((i + 1) & 1) * 2 + 1, hdr->sk2ListArray[i + 1].weights, hdr->sk2ListArray[i + 1].count * 2);
            PSMTXReorder(bones[l2->bone0Index]->skinMtx, l2->m0);
            PSMTXReorder(bones[l2->bone1Index]->skinMtx, l2->m1);
            LCQueueWait(2);
            fn_800C02C8(l2->m0, l2->m1, lbl_803CB724[(i & 1) * 2 + 1],
                                 (s16*)((u8*)lbl_803CB724[(i & 1) * 2] + l2->vertSrcOffset),
                                 (s16*)((u8*)lbl_803CB724[(i & 1) * 2] + l2->vertSrcOffset), l2->count);
        LCStoreBlocks(l2->vertDst + base, lbl_803CB724[(i & 1) * 2], sizes[i & 1]);
        }
        l2 = &hdr->sk2ListArray[i];
        PSMTXReorder(bones[l2->bone0Index]->skinMtx, l2->m0);
        PSMTXReorder(bones[l2->bone1Index]->skinMtx, l2->m1);
        LCQueueWait(0);
        fn_800C02C8(l2->m0, l2->m1, lbl_803CB724[(i & 1) * 2 + 1],
                                 (s16*)((u8*)lbl_803CB724[(i & 1) * 2] + l2->vertSrcOffset),
                                 (s16*)((u8*)lbl_803CB724[(i & 1) * 2] + l2->vertSrcOffset), l2->count);
        LCStoreBlocks(l2->vertDst + base, lbl_803CB724[(i & 1) * 2], sizes[i & 1]);
    }

    if (hdr->numSkAccList != 0) {
        if (hdr->skBzeroSize != 0) {
            SKNBzero32B(base + hdr->skBzeroBase, (hdr->skBzeroSize + 0x1F) & 0x07FFFFFF);
        }
        SKNLCAccTouchData(0, hdr->skAccListArray[0].vertSrc, hdr->skAccListArray[0].vertIndices,
                          hdr->skAccListArray[0].weights, hdr->skAccListArray[0].count, 0xC);
        LCQueueWait(0);
        for (i = 0; i < hdr->numSkAccList - 1; i++) {
            SKNLCAccTouchData((i + 1) & 1, hdr->skAccListArray[i + 1].vertSrc, hdr->skAccListArray[i + 1].vertIndices,
                              hdr->skAccListArray[i + 1].weights, hdr->skAccListArray[i + 1].count, 0xC);
            la = &hdr->skAccListArray[i];
            PSMTXReorder(bones[la->boneIndex]->skinMtx, la->m);
            SKNAccVecs16Norms16Iu162(la->m, la->count, lbl_803CB6FC[i & 1].src, (s16*)(la->vertDst + base),
                                     lbl_803CB6FC[i & 1].indices, lbl_803CB6FC[i & 1].weights);
        }
        la = &hdr->skAccListArray[i];
        PSMTXReorder(bones[la->boneIndex]->skinMtx, la->m);
        SKNAccVecs16Norms16Iu162(la->m, la->count, lbl_803CB6FC[i & 1].src, (s16*)(la->vertDst + base),
                                 lbl_803CB6FC[i & 1].indices, lbl_803CB6FC[i & 1].weights);
        DCStoreRange(base + hdr->skBzeroBase, (hdr->skBzeroSize + 0x1F) & 0x07FFFFFF);
        if (hdr->flushCount != 0) {
            SKNFlushByIndex2(hdr->flushIndices, hdr->flushCount, base + hdr->skAccListArray[0].vertDst);
        }
    }
}
#endif

// .text:0x800BF89C size:0x5F4
// NONMATCHING 90.6%: scheduling/regalloc in the sk2 and acc double-buffer loops
#if NONMATCHING
void SKNIt(SKNBone** bones, SKNHeader* hdr, u8* base) {
    u16 sizes[2];
    u32 i;
    SKN1List* l1;
    SKN2List* l2;
    SKNAccList* la;

    GQRSetup7(hdr->posNrmShift, 0, hdr->posNrmShift, 0);

    if (hdr->numSk1List != 0) {
        sizes[0] = SKNLCTouchData(0, hdr->sk1ListArray[0].vertSrc,
                                  hdr->sk1ListArray[0].count * 0x18 + hdr->sk1ListArray[0].vertSrcOffset);
        for (i = 0; i < hdr->numSk1List - 1; i++) {
            sizes[(i + 1) & 1] = SKNLCTouchData(((i + 1) & 1) * 2, hdr->sk1ListArray[i + 1].vertSrc,
                                                hdr->sk1ListArray[i + 1].count * 0x18 + hdr->sk1ListArray[i + 1].vertSrcOffset);
            l1 = &hdr->sk1ListArray[i];
            PSMTXReorder(bones[l1->boneIndex]->skinMtx, l1->m);
            LCQueueWait(1);
            SKN1Vecs16Norms16(l1->m, (f32*)((u8*)lbl_803CB724[(i & 1) * 2] + l1->vertSrcOffset),
                          (f32*)((u8*)lbl_803CB724[(i & 1) * 2] + l1->vertSrcOffset), l1->count);
        LCStoreData(l1->vertDst + base, lbl_803CB724[(i & 1) * 2], sizes[i & 1]);
        }
        l1 = &hdr->sk1ListArray[i];
        PSMTXReorder(bones[l1->boneIndex]->skinMtx, l1->m);
        SKN1Vecs16Norms16(l1->m, (f32*)((u8*)lbl_803CB724[(i & 1) * 2] + l1->vertSrcOffset),
                          (f32*)((u8*)lbl_803CB724[(i & 1) * 2] + l1->vertSrcOffset), l1->count);
        LCStoreData(l1->vertDst + base, lbl_803CB724[(i & 1) * 2], sizes[i & 1]);
    }

    if (hdr->numSk2List != 0) {
        sizes[0] = SKNLC2TouchData(0, hdr->sk2ListArray[0].vertSrc,
                                   hdr->sk2ListArray[0].count * 0x18 + hdr->sk2ListArray[0].vertSrcOffset);
        SKNLC2TouchData(1, hdr->sk2ListArray[0].weights, hdr->sk2ListArray[0].count * 2);
        for (i = 0; i < hdr->numSk2List - 1; i++) {
            l2 = &hdr->sk2ListArray[i];
            sizes[(i + 1) & 1] = SKNLC2TouchData(((i + 1) & 1) * 2, l2[1].vertSrc, l2[1].vertSrcOffset + l2[1].count * 0x18);
            SKNLC2TouchData(((i + 1) & 1) * 2 + 1, hdr->sk2ListArray[i + 1].weights, hdr->sk2ListArray[i + 1].count * 2);
            PSMTXReorder(bones[l2->bone0Index]->skinMtx, l2->m0);
            PSMTXReorder(bones[l2->bone1Index]->skinMtx, l2->m1);
            LCQueueWait(2);
            SKN2Vecs16Norms16NoTouch(l2->m0, l2->m1, lbl_803CB724[(i & 1) * 2 + 1],
                                 (f32*)((u8*)lbl_803CB724[(i & 1) * 2] + l2->vertSrcOffset),
                                 (f32*)((u8*)lbl_803CB724[(i & 1) * 2] + l2->vertSrcOffset), l2->count);
        LCStoreBlocks(l2->vertDst + base, lbl_803CB724[(i & 1) * 2], sizes[i & 1]);
        }
        l2 = &hdr->sk2ListArray[i];
        PSMTXReorder(bones[l2->bone0Index]->skinMtx, l2->m0);
        PSMTXReorder(bones[l2->bone1Index]->skinMtx, l2->m1);
        LCQueueWait(0);
        SKN2Vecs16Norms16NoTouch(l2->m0, l2->m1, lbl_803CB724[(i & 1) * 2 + 1],
                                 (f32*)((u8*)lbl_803CB724[(i & 1) * 2] + l2->vertSrcOffset),
                                 (f32*)((u8*)lbl_803CB724[(i & 1) * 2] + l2->vertSrcOffset), l2->count);
        LCStoreBlocks(l2->vertDst + base, lbl_803CB724[(i & 1) * 2], sizes[i & 1]);
    }

    if (hdr->numSkAccList != 0) {
        if (hdr->skBzeroSize != 0) {
            SKNBzero32B(base + hdr->skBzeroBase, (hdr->skBzeroSize + 0x1F) & 0x07FFFFFF);
        }
        SKNLCAccTouchData(0, hdr->skAccListArray[0].vertSrc, hdr->skAccListArray[0].vertIndices,
                          hdr->skAccListArray[0].weights, hdr->skAccListArray[0].count, 0x18);
        LCQueueWait(0);
        for (i = 0; i < hdr->numSkAccList - 1; i++) {
            SKNLCAccTouchData((i + 1) & 1, hdr->skAccListArray[i + 1].vertSrc, hdr->skAccListArray[i + 1].vertIndices,
                              hdr->skAccListArray[i + 1].weights, hdr->skAccListArray[i + 1].count, 0x18);
            la = &hdr->skAccListArray[i];
            PSMTXReorder(bones[la->boneIndex]->skinMtx, la->m);
            SKNAccVecs16Norms16Iu161(la->m, la->count, lbl_803CB6FC[i & 1].src, (f32*)(la->vertDst + base),
                                     lbl_803CB6FC[i & 1].indices, lbl_803CB6FC[i & 1].weights);
        }
        la = &hdr->skAccListArray[i];
        PSMTXReorder(bones[la->boneIndex]->skinMtx, la->m);
        SKNAccVecs16Norms16Iu161(la->m, la->count, lbl_803CB6FC[i & 1].src, (f32*)(la->vertDst + base),
                                 lbl_803CB6FC[i & 1].indices, lbl_803CB6FC[i & 1].weights);
        DCStoreRange(base + hdr->skBzeroBase, (hdr->skBzeroSize + 0x1F) & 0x07FFFFFF);
        if (hdr->flushCount != 0) {
            SKNFlushByIndex1(hdr->flushIndices, hdr->flushCount, base + hdr->skAccListArray[0].vertDst);
        }
    }
}
#endif

#if NONMATCHING
// Portable versions of the paired-single skinning kernels. The f32 kernels match
// GQR7 = f32 (set by SKNIt); the s16 kernels match GQR6 = s16 scaled by
// 2^posNrmShift (set by fn_800BF2A8). Each vertex is a position and a normal.
static void SKNXformVtx(Mtx43 m, const f32* in, f32* out) {
    s32 k;

    for (k = 0; k < 3; k++) {
        out[k] = m[0][k] * in[0] + m[1][k] * in[1] + m[2][k] * in[2] + m[3][k];
        out[k + 3] = m[0][k] * in[3] + m[1][k] * in[4] + m[2][k] * in[5];
    }
}

static void SKNLoadS16(const s16* src, f32* v) {
    f32 scale = 1.0f / (f32)(1 << sSKNPosNrmShift);
    s32 k;

    for (k = 0; k < 6; k++) {
        v[k] = src[k] * scale;
    }
}

static void SKNStoreS16(s16* dst, const f32* v) {
    f32 scale = (f32)(1 << sSKNPosNrmShift);
    f32 t;
    s32 k;

    for (k = 0; k < 6; k++) {
        t = v[k] * scale;
        if (t > 32767.0f) {
            t = 32767.0f;
        } else if (t < -32768.0f) {
            t = -32768.0f;
        }
        dst[k] = (s16)t;
    }
}

static void SKNBlend2(Mtx43 m0, Mtx43 m1, const u8* w, const f32* in, f32* out) {
    f32 a[6];
    f32 b[6];
    f32 w0 = w[0] / 256.0f;
    f32 w1 = w[1] / 256.0f;
    s32 k;

    SKNXformVtx(m0, in, a);
    SKNXformVtx(m1, in, b);
    for (k = 0; k < 6; k++) {
        out[k] = b[k] * w1 + a[k] * w0;
    }
}
#endif

// .text:0x800BFE90 size:0x10C
#if NONMATCHING
void SKN1Vecs16Norms16(Mtx43 m, f32* src, f32* dst, u32 count) {
    f32 v[6];
    s32 k;

    do {
        SKNXformVtx(m, src, v);
        for (k = 0; k < 6; k++) {
            dst[k] = v[k];
        }
        src += 6;
        dst += 6;
    } while (--count);
}
#else
asm void SKN1Vecs16Norms16(register Mtx43 m, register f32* src, register f32* dst, register u32 count) {
    nofralloc
    stwu r1, -0x40(r1)
    stfd f14, 0x8(r1)
    stfd f15, 0x10(r1)
    subi r6, r6, 0x1
    stfd f16, 0x18(r1)
    stfd f17, 0x20(r1)
    stfd f18, 0x28(r1)
    mtctr r6
    psq_l f0, 0x0(r3), 0, 0
    subi r4, r4, 0x8
    psq_l f1, 0x8(r3), 1, 0
    subi r5, r5, 0x4
    psq_l f6, 0x24(r3), 0, 0
    psq_lu f8, 0x8(r4), 0, 7
    psq_l f7, 0x2c(r3), 1, 0
    psq_lu f9, 0x8(r4), 0, 7
    ps_madds0 f11, f0, f8, f6
    psq_l f2, 0xc(r3), 0, 0
    ps_madds0 f12, f1, f8, f7
    psq_l f3, 0x14(r3), 1, 0
    ps_muls1 f13, f0, f9
    psq_lu f10, 0x8(r4), 0, 7
    ps_muls1 f14, f1, f9
    psq_l f5, 0x20(r3), 1, 0
    ps_madds1 f11, f2, f8, f11
    ps_madds1 f12, f3, f8, f12
    psq_l f4, 0x18(r3), 0, 0
    ps_madds0 f13, f2, f10, f13
    psq_lu f8, 0x8(r4), 0, 7
    ps_madds0 f14, f3, f10, f14
    ps_madds0 f15, f4, f9, f11
    ps_madds0 f16, f5, f9, f12
    psq_lu f9, 0x8(r4), 0, 7
    ps_madds1 f17, f4, f10, f13
    ps_madds1 f18, f5, f10, f14
    psq_lu f10, 0x8(r4), 0, 7
L_800BFF20:
    ps_madds0 f11, f0, f8, f6
    psq_stu f15, 0x4(r5), 0, 7
    ps_madds0 f12, f1, f8, f7
    psq_stu f16, 0x8(r5), 1, 7
    ps_muls1 f13, f0, f9
    psq_stu f17, 0x4(r5), 0, 7
    ps_muls1 f14, f1, f9
    psq_stu f18, 0x8(r5), 1, 7
    ps_madds1 f11, f2, f8, f11
    ps_madds1 f12, f3, f8, f12
    psq_lu f8, 0x8(r4), 0, 7
    ps_madds0 f13, f2, f10, f13
    ps_madds0 f14, f3, f10, f14
    ps_madds0 f15, f4, f9, f11
    ps_madds0 f16, f5, f9, f12
    psq_lu f9, 0x8(r4), 0, 7
    ps_madds1 f17, f4, f10, f13
    ps_madds1 f18, f5, f10, f14
    psq_lu f10, 0x8(r4), 0, 7
    bdnz L_800BFF20
    psq_stu f15, 0x4(r5), 0, 7
    psq_stu f16, 0x8(r5), 1, 7
    psq_stu f17, 0x4(r5), 0, 7
    psq_stu f18, 0x8(r5), 1, 7
    lfd f14, 0x8(r1)
    lfd f15, 0x10(r1)
    lfd f16, 0x18(r1)
    lfd f17, 0x20(r1)
    lfd f18, 0x28(r1)
    addi r1, r1, 0x40
    blr
}
#endif

// .text:0x800BFF9C size:0x10C
#if NONMATCHING
void fn_800BFF9C(Mtx43 m, s16* src, s16* dst, u32 count) {
    f32 in[6];
    f32 v[6];

    do {
        SKNLoadS16(src, in);
        SKNXformVtx(m, in, v);
        SKNStoreS16(dst, v);
        src += 6;
        dst += 6;
    } while (--count);
}
#else
asm void fn_800BFF9C(register Mtx43 m, register s16* src, register s16* dst, register u32 count) {
    nofralloc
    stwu r1, -0x40(r1)
    stfd f14, 0x8(r1)
    stfd f15, 0x10(r1)
    subi r6, r6, 0x1
    stfd f16, 0x18(r1)
    stfd f17, 0x20(r1)
    stfd f18, 0x28(r1)
    mtctr r6
    psq_l f0, 0x0(r3), 0, 0
    subi r4, r4, 0x4
    psq_l f1, 0x8(r3), 1, 0
    subi r5, r5, 0x2
    psq_l f6, 0x24(r3), 0, 0
    psq_lu f8, 0x4(r4), 0, 6
    psq_l f7, 0x2c(r3), 1, 0
    psq_lu f9, 0x4(r4), 0, 6
    ps_madds0 f11, f0, f8, f6
    psq_l f2, 0xc(r3), 0, 0
    ps_madds0 f12, f1, f8, f7
    psq_l f3, 0x14(r3), 1, 0
    ps_muls1 f13, f0, f9
    psq_lu f10, 0x4(r4), 0, 6
    ps_muls1 f14, f1, f9
    psq_l f5, 0x20(r3), 1, 0
    ps_madds1 f11, f2, f8, f11
    ps_madds1 f12, f3, f8, f12
    psq_l f4, 0x18(r3), 0, 0
    ps_madds0 f13, f2, f10, f13
    psq_lu f8, 0x4(r4), 0, 6
    ps_madds0 f14, f3, f10, f14
    ps_madds0 f15, f4, f9, f11
    ps_madds0 f16, f5, f9, f12
    psq_lu f9, 0x4(r4), 0, 6
    ps_madds1 f17, f4, f10, f13
    ps_madds1 f18, f5, f10, f14
    psq_lu f10, 0x4(r4), 0, 6
L_800C002C:
    ps_madds0 f11, f0, f8, f6
    psq_stu f15, 0x2(r5), 0, 6
    ps_madds0 f12, f1, f8, f7
    psq_stu f16, 0x4(r5), 1, 6
    ps_muls1 f13, f0, f9
    psq_stu f17, 0x2(r5), 0, 6
    ps_muls1 f14, f1, f9
    psq_stu f18, 0x4(r5), 1, 6
    ps_madds1 f11, f2, f8, f11
    ps_madds1 f12, f3, f8, f12
    psq_lu f8, 0x4(r4), 0, 6
    ps_madds0 f13, f2, f10, f13
    ps_madds0 f14, f3, f10, f14
    ps_madds0 f15, f4, f9, f11
    ps_madds0 f16, f5, f9, f12
    psq_lu f9, 0x4(r4), 0, 6
    ps_madds1 f17, f4, f10, f13
    ps_madds1 f18, f5, f10, f14
    psq_lu f10, 0x4(r4), 0, 6
    bdnz L_800C002C
    psq_stu f15, 0x2(r5), 0, 6
    psq_stu f16, 0x4(r5), 1, 6
    psq_stu f17, 0x2(r5), 0, 6
    psq_stu f18, 0x4(r5), 1, 6
    lfd f14, 0x8(r1)
    lfd f15, 0x10(r1)
    lfd f16, 0x18(r1)
    lfd f17, 0x20(r1)
    lfd f18, 0x28(r1)
    addi r1, r1, 0x40
    blr
}
#endif

// .text:0x800C00A8 size:0x220
#if NONMATCHING
void SKN2Vecs16Norms16NoTouch(Mtx43 m0, Mtx43 m1, u8* weights, f32* src, f32* dst, u32 count) {
    f32 v[6];
    s32 k;

    do {
        SKNBlend2(m0, m1, weights, src, v);
        for (k = 0; k < 6; k++) {
            dst[k] = v[k];
        }
        weights += 2;
        src += 6;
        dst += 6;
    } while (--count);
}
#else
asm void SKN2Vecs16Norms16NoTouch(register Mtx43 m0, register Mtx43 m1, register u8* weights, register f32* src, register f32* dst, register u32 count) {
    nofralloc
    stwu r1, -0xa0(r1)
    stfd f14, 0x8(r1)
    subi r9, r8, 0x1
    stfd f15, 0x10(r1)
    stfd f16, 0x18(r1)
    stfd f17, 0x20(r1)
    stfd f18, 0x28(r1)
    stfd f19, 0x30(r1)
    stfd f20, 0x38(r1)
    stfd f21, 0x40(r1)
    stfd f22, 0x48(r1)
    stfd f23, 0x50(r1)
    stfd f24, 0x58(r1)
    stfd f25, 0x60(r1)
    stfd f26, 0x68(r1)
    stfd f27, 0x70(r1)
    mtctr r9
    psq_l f0, 0x0(r3), 0, 0
    subi r6, r6, 0x8
    psq_l f1, 0x8(r3), 1, 0
    subi r7, r7, 0x4
    psq_l f6, 0x24(r3), 0, 0
    subi r5, r5, 0x2
    psq_lu f8, 0x8(r6), 0, 7
    psq_l f7, 0x2c(r3), 1, 0
    psq_lu f9, 0x8(r6), 0, 7
    psq_lu f27, 0x2(r5), 0, 5
    ps_madds0 f15, f0, f8, f6
    psq_l f2, 0xc(r3), 0, 0
    ps_madds0 f16, f1, f8, f7
    psq_l f3, 0x14(r3), 1, 0
    ps_muls1 f17, f0, f9
    psq_lu f10, 0x8(r6), 0, 7
    ps_muls1 f18, f1, f9
    psq_l f5, 0x20(r3), 1, 0
    ps_madds1 f15, f2, f8, f15
    psq_l f19, 0x0(r4), 0, 0
    ps_madds1 f16, f3, f8, f16
    psq_l f4, 0x18(r3), 0, 0
    ps_madds0 f17, f2, f10, f17
    psq_l f20, 0x8(r4), 1, 0
    ps_madds0 f18, f3, f10, f18
    psq_l f21, 0xc(r4), 0, 0
    ps_madds0 f15, f4, f9, f15
    psq_l f22, 0x14(r4), 1, 0
    ps_madds0 f16, f5, f9, f16
    psq_l f23, 0x18(r4), 0, 0
    ps_madds1 f17, f4, f10, f17
    psq_l f24, 0x20(r4), 1, 0
    ps_madds1 f18, f5, f10, f18
    psq_l f25, 0x24(r4), 0, 0
    ps_muls0 f15, f15, f27
    psq_l f26, 0x2c(r4), 1, 0
    ps_muls0 f16, f16, f27
    ps_muls0 f17, f17, f27
    ps_muls0 f18, f18, f27
    ps_madds0 f11, f19, f8, f25
    ps_madds0 f12, f20, f8, f26
    ps_muls1 f13, f19, f9
    ps_muls1 f14, f20, f9
    ps_madds1 f11, f21, f8, f11
    ps_madds1 f12, f22, f8, f12
    ps_madds0 f13, f21, f10, f13
    psq_lu f8, 0x8(r6), 0, 7
    ps_madds0 f14, f22, f10, f14
    ps_madds0 f11, f23, f9, f11
    ps_madds0 f12, f24, f9, f12
    ps_madds1 f13, f23, f10, f13
    ps_madds1 f14, f24, f10, f14
    psq_lu f9, 0x8(r6), 0, 7
    ps_madds1 f11, f11, f27, f15
    ps_madds1 f12, f12, f27, f16
    ps_madds1 f13, f13, f27, f17
    psq_lu f10, 0x8(r6), 0, 7
    ps_madds1 f14, f14, f27, f18
L_800C01D4:
    ps_madds0 f15, f0, f8, f6
    psq_stu f11, 0x4(r7), 0, 7
    ps_madds0 f16, f1, f8, f7
    psq_stu f12, 0x8(r7), 1, 7
    ps_muls1 f17, f0, f9
    psq_stu f13, 0x4(r7), 0, 7
    ps_muls1 f18, f1, f9
    psq_stu f14, 0x8(r7), 1, 7
    ps_madds1 f15, f2, f8, f15
    ps_madds1 f16, f3, f8, f16
    ps_madds0 f17, f2, f10, f17
    ps_madds0 f18, f3, f10, f18
    ps_madds0 f15, f4, f9, f15
    ps_madds0 f16, f5, f9, f16
    psq_lu f27, 0x2(r5), 0, 5
    ps_madds1 f17, f4, f10, f17
    ps_madds1 f18, f5, f10, f18
    ps_muls0 f15, f15, f27
    ps_muls0 f16, f16, f27
    ps_muls0 f17, f17, f27
    ps_muls0 f18, f18, f27
    ps_madds0 f11, f19, f8, f25
    ps_madds0 f12, f20, f8, f26
    ps_muls1 f13, f19, f9
    ps_muls1 f14, f20, f9
    ps_madds1 f11, f21, f8, f11
    ps_madds1 f12, f22, f8, f12
    ps_madds0 f13, f21, f10, f13
    psq_lu f8, 0x8(r6), 0, 7
    ps_madds0 f14, f22, f10, f14
    ps_madds0 f11, f23, f9, f11
    ps_madds0 f12, f24, f9, f12
    ps_madds1 f13, f23, f10, f13
    ps_madds1 f14, f24, f10, f14
    psq_lu f9, 0x8(r6), 0, 7
    ps_madds1 f11, f11, f27, f15
    ps_madds1 f12, f12, f27, f16
    ps_madds1 f13, f13, f27, f17
    psq_lu f10, 0x8(r6), 0, 7
    ps_madds1 f14, f14, f27, f18
    bdnz L_800C01D4
    psq_stu f11, 0x4(r7), 0, 7
    psq_stu f12, 0x8(r7), 1, 7
    psq_stu f13, 0x4(r7), 0, 7
    psq_stu f14, 0x8(r7), 1, 7
    lfd f14, 0x8(r1)
    lfd f15, 0x10(r1)
    lfd f16, 0x18(r1)
    lfd f17, 0x20(r1)
    lfd f18, 0x28(r1)
    lfd f19, 0x30(r1)
    lfd f20, 0x38(r1)
    lfd f21, 0x40(r1)
    lfd f22, 0x48(r1)
    lfd f23, 0x50(r1)
    lfd f24, 0x58(r1)
    lfd f25, 0x60(r1)
    lfd f26, 0x68(r1)
    lfd f27, 0x70(r1)
    addi r1, r1, 0xa0
    blr
}
#endif

// .text:0x800C02C8 size:0x220
#if NONMATCHING
void fn_800C02C8(Mtx43 m0, Mtx43 m1, u8* weights, s16* src, s16* dst, u32 count) {
    f32 in[6];
    f32 v[6];

    do {
        SKNLoadS16(src, in);
        SKNBlend2(m0, m1, weights, in, v);
        SKNStoreS16(dst, v);
        weights += 2;
        src += 6;
        dst += 6;
    } while (--count);
}
#else
asm void fn_800C02C8(register Mtx43 m0, register Mtx43 m1, register u8* weights, register s16* src, register s16* dst, register u32 count) {
    nofralloc
    stwu r1, -0xa0(r1)
    stfd f14, 0x8(r1)
    subi r9, r8, 0x1
    stfd f15, 0x10(r1)
    stfd f16, 0x18(r1)
    stfd f17, 0x20(r1)
    stfd f18, 0x28(r1)
    stfd f19, 0x30(r1)
    stfd f20, 0x38(r1)
    stfd f21, 0x40(r1)
    stfd f22, 0x48(r1)
    stfd f23, 0x50(r1)
    stfd f24, 0x58(r1)
    stfd f25, 0x60(r1)
    stfd f26, 0x68(r1)
    stfd f27, 0x70(r1)
    mtctr r9
    psq_l f0, 0x0(r3), 0, 0
    subi r6, r6, 0x4
    psq_l f1, 0x8(r3), 1, 0
    subi r7, r7, 0x2
    psq_l f6, 0x24(r3), 0, 0
    subi r5, r5, 0x2
    psq_lu f8, 0x4(r6), 0, 6
    psq_l f7, 0x2c(r3), 1, 0
    psq_lu f9, 0x4(r6), 0, 6
    psq_lu f27, 0x2(r5), 0, 5
    ps_madds0 f15, f0, f8, f6
    psq_l f2, 0xc(r3), 0, 0
    ps_madds0 f16, f1, f8, f7
    psq_l f3, 0x14(r3), 1, 0
    ps_muls1 f17, f0, f9
    psq_lu f10, 0x4(r6), 0, 6
    ps_muls1 f18, f1, f9
    psq_l f5, 0x20(r3), 1, 0
    ps_madds1 f15, f2, f8, f15
    psq_l f19, 0x0(r4), 0, 0
    ps_madds1 f16, f3, f8, f16
    psq_l f4, 0x18(r3), 0, 0
    ps_madds0 f17, f2, f10, f17
    psq_l f20, 0x8(r4), 1, 0
    ps_madds0 f18, f3, f10, f18
    psq_l f21, 0xc(r4), 0, 0
    ps_madds0 f15, f4, f9, f15
    psq_l f22, 0x14(r4), 1, 0
    ps_madds0 f16, f5, f9, f16
    psq_l f23, 0x18(r4), 0, 0
    ps_madds1 f17, f4, f10, f17
    psq_l f24, 0x20(r4), 1, 0
    ps_madds1 f18, f5, f10, f18
    psq_l f25, 0x24(r4), 0, 0
    ps_muls0 f15, f15, f27
    psq_l f26, 0x2c(r4), 1, 0
    ps_muls0 f16, f16, f27
    ps_muls0 f17, f17, f27
    ps_muls0 f18, f18, f27
    ps_madds0 f11, f19, f8, f25
    ps_madds0 f12, f20, f8, f26
    ps_muls1 f13, f19, f9
    ps_muls1 f14, f20, f9
    ps_madds1 f11, f21, f8, f11
    ps_madds1 f12, f22, f8, f12
    ps_madds0 f13, f21, f10, f13
    psq_lu f8, 0x4(r6), 0, 6
    ps_madds0 f14, f22, f10, f14
    ps_madds0 f11, f23, f9, f11
    ps_madds0 f12, f24, f9, f12
    ps_madds1 f13, f23, f10, f13
    ps_madds1 f14, f24, f10, f14
    psq_lu f9, 0x4(r6), 0, 6
    ps_madds1 f11, f11, f27, f15
    ps_madds1 f12, f12, f27, f16
    ps_madds1 f13, f13, f27, f17
    psq_lu f10, 0x4(r6), 0, 6
    ps_madds1 f14, f14, f27, f18
L_800C03F4:
    ps_madds0 f15, f0, f8, f6
    psq_stu f11, 0x2(r7), 0, 6
    ps_madds0 f16, f1, f8, f7
    psq_stu f12, 0x4(r7), 1, 6
    ps_muls1 f17, f0, f9
    psq_stu f13, 0x2(r7), 0, 6
    ps_muls1 f18, f1, f9
    psq_stu f14, 0x4(r7), 1, 6
    ps_madds1 f15, f2, f8, f15
    ps_madds1 f16, f3, f8, f16
    ps_madds0 f17, f2, f10, f17
    ps_madds0 f18, f3, f10, f18
    ps_madds0 f15, f4, f9, f15
    ps_madds0 f16, f5, f9, f16
    psq_lu f27, 0x2(r5), 0, 5
    ps_madds1 f17, f4, f10, f17
    ps_madds1 f18, f5, f10, f18
    ps_muls0 f15, f15, f27
    ps_muls0 f16, f16, f27
    ps_muls0 f17, f17, f27
    ps_muls0 f18, f18, f27
    ps_madds0 f11, f19, f8, f25
    ps_madds0 f12, f20, f8, f26
    ps_muls1 f13, f19, f9
    ps_muls1 f14, f20, f9
    ps_madds1 f11, f21, f8, f11
    ps_madds1 f12, f22, f8, f12
    ps_madds0 f13, f21, f10, f13
    psq_lu f8, 0x4(r6), 0, 6
    ps_madds0 f14, f22, f10, f14
    ps_madds0 f11, f23, f9, f11
    ps_madds0 f12, f24, f9, f12
    ps_madds1 f13, f23, f10, f13
    ps_madds1 f14, f24, f10, f14
    psq_lu f9, 0x4(r6), 0, 6
    ps_madds1 f11, f11, f27, f15
    ps_madds1 f12, f12, f27, f16
    ps_madds1 f13, f13, f27, f17
    psq_lu f10, 0x4(r6), 0, 6
    ps_madds1 f14, f14, f27, f18
    bdnz L_800C03F4
    psq_stu f11, 0x2(r7), 0, 6
    psq_stu f12, 0x4(r7), 1, 6
    psq_stu f13, 0x2(r7), 0, 6
    psq_stu f14, 0x4(r7), 1, 6
    lfd f14, 0x8(r1)
    lfd f15, 0x10(r1)
    lfd f16, 0x18(r1)
    lfd f17, 0x20(r1)
    lfd f18, 0x28(r1)
    lfd f19, 0x30(r1)
    lfd f20, 0x38(r1)
    lfd f21, 0x40(r1)
    lfd f22, 0x48(r1)
    lfd f23, 0x50(r1)
    lfd f24, 0x58(r1)
    lfd f25, 0x60(r1)
    lfd f26, 0x68(r1)
    lfd f27, 0x70(r1)
    addi r1, r1, 0xa0
    blr
}
#endif

// .text:0x800C04E8 size:0x148
#if NONMATCHING
void SKNAccVecs16Norms16Iu161(Mtx43 m, u16 count, f32* src, f32* dst, u16* indices, u8* weights) {
    f32 v[6];
    f32* out;
    f32 w;
    s32 k;

    do {
        out = dst + *indices++ * 6;
        w = *weights++ / 256.0f;
        SKNXformVtx(m, src, v);
        for (k = 0; k < 6; k++) {
            out[k] = v[k] * w + out[k];
        }
        DCStoreRange(out, 6 * sizeof(f32));
        src += 6;
    } while (--count);
}
#else
asm void SKNAccVecs16Norms16Iu161(register Mtx43 m, register u16 count, register f32* src, register f32* dst, register u16* indices, register u8* weights) {
    nofralloc
    stwu r1, -0xa0(r1)
    subi r7, r7, 0x2
    stfd f14, 0x8(r1)
    lhzu r9, 0x2(r7)
    stfd f15, 0x10(r1)
    stfd f16, 0x18(r1)
    add r11, r9, r9
    stfd f17, 0x20(r1)
    add r9, r9, r11
    stfd f18, 0x28(r1)
    add r9, r9, r9
    stfd f19, 0x30(r1)
    add r9, r9, r9
    stfd f20, 0x38(r1)
    add r9, r9, r9
    stfd f21, 0x40(r1)
    add r10, r9, r6
    stfd f22, 0x48(r1)
    subi r8, r8, 0x1
    stfd f23, 0x50(r1)
    mtctr r4
    psq_l f0, 0x0(r3), 0, 0
    subi r5, r5, 0x8
    psq_l f1, 0x8(r3), 1, 0
    psq_l f6, 0x24(r3), 0, 0
    psq_l f7, 0x2c(r3), 1, 0
    psq_lu f8, 0x8(r5), 0, 7
    psq_lu f9, 0x8(r5), 0, 7
    psq_l f2, 0xc(r3), 0, 0
    psq_l f3, 0x14(r3), 1, 0
    psq_lu f10, 0x8(r5), 0, 7
    psq_l f5, 0x20(r3), 1, 0
    psq_l f4, 0x18(r3), 0, 0
L_800C056C:
    ps_madds0 f11, f0, f8, f6
    psq_lu f23, 0x1(r8), 1, 5
    ps_madds0 f12, f1, f8, f7
    ps_muls1 f13, f0, f9
    psq_l f19, 0x0(r10), 0, 7
    ps_muls1 f14, f1, f9
    ps_madds1 f11, f2, f8, f11
    ps_madds1 f12, f3, f8, f12
    psq_l f20, 0x8(r10), 1, 7
    ps_madds0 f13, f2, f10, f13
    ps_madds0 f14, f3, f10, f14
    psq_l f21, 0xc(r10), 0, 7
    ps_madds0 f15, f4, f9, f11
    ps_madds0 f16, f5, f9, f12
    lhzu r9, 0x2(r7)
    ps_madds1 f17, f4, f10, f13
    ps_madds1 f18, f5, f10, f14
    psq_l f22, 0x14(r10), 1, 7
    ps_madds0 f19, f15, f23, f19
    psq_lu f8, 0x8(r5), 0, 7
    ps_madds0 f20, f16, f23, f20
    psq_lu f9, 0x8(r5), 0, 7
    ps_madds0 f21, f17, f23, f21
    psq_lu f10, 0x8(r5), 0, 7
    ps_madds0 f22, f18, f23, f22
    add r11, r9, r9
    psq_st f19, 0x0(r10), 0, 7
    add r9, r9, r11
    psq_st f20, 0x8(r10), 1, 7
    add r9, r9, r9
    psq_st f21, 0xc(r10), 0, 7
    add r9, r9, r9
    psq_st f22, 0x14(r10), 1, 7
    add r9, r9, r9
    dcbst r0, r10
    add r10, r9, r6
    bdnz L_800C056C
    lfd f14, 0x8(r1)
    lfd f15, 0x10(r1)
    lfd f16, 0x18(r1)
    lfd f17, 0x20(r1)
    lfd f18, 0x28(r1)
    lfd f19, 0x30(r1)
    lfd f20, 0x38(r1)
    lfd f21, 0x40(r1)
    lfd f22, 0x48(r1)
    lfd f23, 0x50(r1)
    addi r1, r1, 0xa0
    blr
}
#endif

// .text:0x800C0630 size:0x140
#if NONMATCHING
void SKNAccVecs16Norms16Iu162(Mtx43 m, u16 count, s16* src, s16* dst, u16* indices, u8* weights) {
    f32 in[6];
    f32 v[6];
    f32 acc[6];
    s16* out;
    f32 w;
    s32 k;

    do {
        out = dst + *indices++ * 6;
        w = *weights++ / 256.0f;
        SKNLoadS16(src, in);
        SKNXformVtx(m, in, v);
        SKNLoadS16(out, acc);
        for (k = 0; k < 6; k++) {
            acc[k] = v[k] * w + acc[k];
        }
        SKNStoreS16(out, acc);
        DCStoreRange(out, 6 * sizeof(s16));
        src += 6;
    } while (--count);
}
#else
asm void SKNAccVecs16Norms16Iu162(register Mtx43 m, register u16 count, register s16* src, register s16* dst, register u16* indices, register u8* weights) {
    nofralloc
    stwu r1, -0xa0(r1)
    subi r7, r7, 0x2
    stfd f14, 0x8(r1)
    lhzu r9, 0x2(r7)
    stfd f15, 0x10(r1)
    stfd f16, 0x18(r1)
    add r11, r9, r9
    stfd f17, 0x20(r1)
    add r9, r9, r11
    stfd f18, 0x28(r1)
    add r9, r9, r9
    stfd f19, 0x30(r1)
    add r9, r9, r9
    stfd f20, 0x38(r1)
    add r10, r9, r6
    stfd f21, 0x40(r1)
    subi r8, r8, 0x1
    stfd f22, 0x48(r1)
    stfd f23, 0x50(r1)
    mtctr r4
    psq_l f0, 0x0(r3), 0, 0
    subi r5, r5, 0x4
    psq_l f1, 0x8(r3), 1, 0
    psq_l f6, 0x24(r3), 0, 0
    psq_l f7, 0x2c(r3), 1, 0
    psq_lu f8, 0x4(r5), 0, 6
    psq_lu f9, 0x4(r5), 0, 6
    psq_l f2, 0xc(r3), 0, 0
    psq_l f3, 0x14(r3), 1, 0
    psq_lu f10, 0x4(r5), 0, 6
    psq_l f5, 0x20(r3), 1, 0
    psq_l f4, 0x18(r3), 0, 0
L_800C06B0:
    ps_madds0 f11, f0, f8, f6
    psq_lu f23, 0x1(r8), 1, 5
    ps_madds0 f12, f1, f8, f7
    ps_muls1 f13, f0, f9
    psq_l f19, 0x0(r10), 0, 6
    ps_muls1 f14, f1, f9
    ps_madds1 f11, f2, f8, f11
    ps_madds1 f12, f3, f8, f12
    psq_l f20, 0x4(r10), 1, 6
    ps_madds0 f13, f2, f10, f13
    ps_madds0 f14, f3, f10, f14
    psq_l f21, 0x6(r10), 0, 6
    ps_madds0 f15, f4, f9, f11
    ps_madds0 f16, f5, f9, f12
    lhzu r9, 0x2(r7)
    ps_madds1 f17, f4, f10, f13
    ps_madds1 f18, f5, f10, f14
    psq_l f22, 0xa(r10), 1, 6
    ps_madds0 f19, f15, f23, f19
    psq_lu f8, 0x4(r5), 0, 6
    ps_madds0 f20, f16, f23, f20
    psq_lu f9, 0x4(r5), 0, 6
    ps_madds0 f21, f17, f23, f21
    psq_lu f10, 0x4(r5), 0, 6
    ps_madds0 f22, f18, f23, f22
    add r11, r9, r9
    psq_st f19, 0x0(r10), 0, 6
    add r9, r9, r11
    psq_st f20, 0x4(r10), 1, 6
    add r9, r9, r9
    psq_st f21, 0x6(r10), 0, 6
    add r9, r9, r9
    psq_st f22, 0xa(r10), 1, 6
    dcbst r0, r10
    add r10, r9, r6
    bdnz L_800C06B0
    lfd f14, 0x8(r1)
    lfd f15, 0x10(r1)
    lfd f16, 0x18(r1)
    lfd f17, 0x20(r1)
    lfd f18, 0x28(r1)
    lfd f19, 0x30(r1)
    lfd f20, 0x38(r1)
    lfd f21, 0x40(r1)
    lfd f22, 0x48(r1)
    lfd f23, 0x50(r1)
    addi r1, r1, 0xa0
    blr
}
#endif

// .text:0x800C0770 size:0x4C
void convertTextureHeader(TextureHeader* hdr) {
    s32 i;

    for (i = 0; i < hdr->count; i++) {
        if (hdr->entries[i].data != NULL) {
            hdr->entries[i].data = (u8*)hdr + (u32)hdr->entries[i].data;
        }
        if (hdr->entries[i].palette != NULL) {
            hdr->entries[i].palette = (u8*)hdr + (u32)hdr->entries[i].palette;
        }
        hdr->entries[i].index = i;
    }
}

// .text:0x800C07BC size:0x2D0
// NONMATCHING 61%: original keeps half*size and the second-half pointers live across the self-inlined recursion
#if NONMATCHING
void fn_800C07BC(void* base, void* tmp, u32 count, u32 size, s32 (*compare)(void*, void*)) {
    u32 half;
    u32 i;
    u32 j;
    u32 k;
    void* src;

    if (count > 1) {
        half = count >> 1;
        fn_800C07BC(base, tmp, half, size, compare);
        fn_800C07BC((u8*)base + half * size, (u8*)tmp + half * size, count - half, size, compare);
        memcpy(tmp, base, half * size);
        k = 0;
        j = half;
        i = 0;
        while (i < half && j < count) {
            if (compare((u8*)tmp + i * size, (u8*)base + j * size) <= 0) {
                src = (u8*)tmp + i * size;
                i++;
            } else {
                src = (u8*)base + j * size;
                j++;
            }
            memcpy((u8*)base + k * size, src, size);
            k++;
        }
        if (i < half) {
            memcpy((u8*)base + k * size, (u8*)tmp + i * size, size * (half - i));
        }
    }
}
#endif
