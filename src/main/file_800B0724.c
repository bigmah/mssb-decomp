#include "main/file_800B0724.h"
#include "main/file_80069BDC.h"
#include "Dolphin/os.h"
#include "Dolphin/ai.h"
#include "Dolphin/ar.h"
#include "musyx/musyx.h"
#include "main/file_8000BA3C.h"
#include "stl/mem.h"
#include "main/file_800B9974.h"
#include "main/file_800BDEA0.h"

extern const f32 lbl_803CCF08; // -1.0f
extern const f32 lbl_803CCF0C; // 0.0f
extern const f32 lbl_803CCF10; // 1.0f
extern SoundConfig lbl_801112F0;
extern SndHeap* lbl_803CBB10;

// .text:0x800B0724 size:0xD8
// Like C_MTXLookAt, but handles a camera looking straight up or down.
void makeLookAtMatrix(Mtx m, Vec* camPos, Vec* camUp, Vec* target) {
    if (camPos->x == target->x && camPos->z == target->z) {
        m[0][0] = lbl_803CCF08;
        m[0][1] = lbl_803CCF0C;
        m[0][2] = lbl_803CCF0C;
        m[0][3] = camPos->x;
        if (camPos->y - target->y <= lbl_803CCF0C) {
            m[1][0] = lbl_803CCF0C;
            m[1][1] = lbl_803CCF0C;
            m[1][2] = lbl_803CCF08;
            m[1][3] = camPos->z;
            m[2][0] = lbl_803CCF0C;
            m[2][1] = lbl_803CCF08;
            m[2][2] = lbl_803CCF0C;
            m[2][3] = camPos->y;
        } else {
            m[1][0] = lbl_803CCF0C;
            m[1][1] = lbl_803CCF0C;
            m[1][2] = lbl_803CCF10;
            m[1][3] = -camPos->z;
            m[2][0] = lbl_803CCF0C;
            m[2][1] = lbl_803CCF10;
            m[2][2] = lbl_803CCF0C;
            m[2][3] = -camPos->y;
        }
    } else {
        C_MTXLookAt(m, camPos, camUp, target);
    }
}

// .text:0x800B07FC size:0x38
void soundQuit(void) {
    SND_HOOKS hooks = {SndAlloc, SndFree};
    sndSetHooks(&hooks);
    sndQuit();
}

// .text:0x800B0834 size:0x100
void initSound(SoundConfig* config, u8* aiStack, u8* heapStart, u32 heapSize) {
    SND_HOOKS hooks = {SndAlloc, SndFree};
    u8* heapEnd;
    AIInit(aiStack);
    ARInit(NULL, 0);
    ARQInit();
    if (config == NULL) {
        config = &lbl_801112F0;
    }
    heapEnd = heapStart + heapSize;
    lbl_803CBB10->cur = heapStart;
    lbl_803CBB10->end = heapEnd;
    lbl_803CBB10->free = heapEnd - heapStart;
    sndSetHooks(&hooks);
    if (sndInit(config->voices, config->music, config->sfx, config->studios, config->flags, config->aramSize) != 0) {
        OSPanic("sound.c", 0x116, "gYd_MusyXInit()::Failed to sndInit().");
    }
    if (OSGetSoundMode() == 0) {
        sndOutputMode(SND_OUTPUTMODE_MONO);
    } else {
        sndOutputMode(SND_OUTPUTMODE_STEREO);
    }
}

// fn_800B0934, size:0x4
void fn_800B0934(void) {
}

// .text:0x800B0938 size:0x64
void SndFree(void* ptr) {
    SndBlockHdr* hdr = (SndBlockHdr*)ptr - 1;
    u8* prevCur = hdr->prevCur;
    if (prevCur + hdr->size != lbl_803CBB10->cur) {
        OSReport("sNp_SndFree err\n");
        while (TRUE) {
        }
    }
    lbl_803CBB10->cur = prevCur;
    lbl_803CBB10->free = lbl_803CBB10->end - lbl_803CBB10->cur;
}

// .text:0x800B099C size:0x78
// NONMATCHING 95%: block-cur temp lands in r4 instead of r6 (matches only if `size` is reused to hold newCur as an integer)
#if NONMATCHING
void* SndAlloc(u32 size) {
    u8* cur;
    u8* hdrEnd;
    u8* block;
    u8* newCur;
    u32 taken;
    s32 remaining;
    size = (size + 3) & ~3;
    cur = lbl_803CBB10->cur;
    // Round cur + header up to 32 bytes (only the low address bits matter).
    hdrEnd = cur + sizeof(SndBlockHdr);
    block = hdrEnd + (-(u32)(size_t)hdrEnd & 0x1F);
    taken = block - cur;
    taken += size;
    newCur = block + size;
    remaining = lbl_803CBB10->end - newCur;
    if (remaining < 0) {
        OSReport("sNp_SndAlloc:: no enough space:%d\n", remaining);
        while (TRUE) {
        }
    }
    ((SndBlockHdr*)block)[-1].prevCur = cur;
    ((SndBlockHdr*)block)[-1].size = taken;
    lbl_803CBB10->free = remaining;
    lbl_803CBB10->cur = newCur;
    return block;
}
#endif

// Draw queue: lbl_803C7A24 holds 64 task slots. Slots 0-5 are the sentinels of three
// priority-sorted lists (head = slot 2n, tail = slot 2n+1); lbl_803CC1B0 picks the list.
extern u16 lbl_803CC1B0; // active list
extern u16 lbl_803CC1B2; // queued task count
extern u16 lbl_803CC1B4; // last slot handed out
extern SceneTask lbl_80111300; // root task (parent of the sentinels)
extern SceneTask lbl_803C7A24[64];

// fn_800B0A14_removeQueue, size:0x48
// Unlinks the running task (lbl_803CC1B8) and frees its slot.
void fn_800B0A14_removeQueue(void* unused) {
    if (lbl_803CC1B2 != 0) {
        SceneTask* neighbor = lbl_803CC1B8->prev;
        neighbor->next = lbl_803CC1B8->next;
        neighbor = lbl_803CC1B8->next;
        neighbor->prev = lbl_803CC1B8->prev;
        lbl_803CC1B8->func = NULL;
        lbl_803CC1B2--;
    }
}

// nop_function, size:0x4
void nop_function(void) {
}

// fn_800B0C80, size:0x34
// Sets the function run by each list's head sentinel.
void fn_800B0C80(void (*draw)(void)) {
    SceneTask* head;
    s32 remaining;
    if (draw == NULL) {
        draw = nop_function;
    }
    remaining = 3;
    head = lbl_803C7A24;
    do {
        remaining--;
        head->func = draw;
        head += 2;
    } while (remaining != 0);
}

// resetAllDrawingStructs, size:0x98
void resetAllDrawingStructs(void) {
    s32 remaining;
    SceneTask* head;
    SceneTask* slot;
    s32 count;
    head = lbl_803C7A24;
    remaining = 3;
    do {
        head[0].prev = NULL;
        head[0].next = &head[1];
        head[0].parent = &lbl_80111300;
        head[0]._10 = 0;
        head[0].priority = 0;
        head[1].prev = &head[0];
        head[1].next = NULL;
        head[1].parent = &lbl_80111300;
        head[1]._10 = 0;
        head[1].priority = 0xFFFF;
        head += 2;
    } while (--remaining != 0);
    slot = &lbl_803C7A24[6];
    count = 64 - 6;
    do {
        slot->func = NULL;
        slot++;
    } while (--count != 0);
    lbl_803CC1B2 = 0;
    lbl_803CC1B0 = 0;
    lbl_803CC1B4 = 5;
}

// fn_800B0A5C_insertQueue, size:0xD0
// Queues draw in the first free slot, before the first task with a higher priority.
SceneTask* fn_800B0A5C_insertQueue(void* draw, u16 priority) {
    SceneTask* node;
    SceneTask* prev;
    SceneTask* entry;
    s32* args;
    u16 idx;
    s32 i;
    do {
        lbl_803CC1B4++;
        idx = lbl_803CC1B4 & 0x3F;
        lbl_803CC1B4 = idx;
    } while (*(void**)&lbl_803C7A24[idx] != NULL); // read as a plain word: lbl_803CC1B4 is reloaded each pass
    node = &lbl_803C7A24[lbl_803CC1B0 * 2];
    do {
        node = node->next;
    } while (node->priority < priority);
    prev = node->prev;
    entry = &lbl_803C7A24[idx];
    node->prev = entry;
    prev->next = entry;
    entry->func = (void (*)(void))draw;
    entry->prev = prev;
    entry->next = node;
    entry->parent = lbl_803CC1B8;
    entry->_10 = 0;
    entry->priority = priority;
    entry->u14.res = NULL;
    lbl_803CC1B2++;
    args = (s32*)&entry->nodes; // TODO type: clears the task's 0x18-0x3F user words
    for (i = 0; i < 5; i++) {
        args[i * 2 + 1] = 0;
        args[i * 2] = 0;
    }
    return entry;
}

// .text:0x800B0B2C size:0xBC
// NONMATCHING 90%: register allocation only (inlined resetAllDrawingStructs uses r6/r7/r5 instead of r5/r6/r3)
#if NONMATCHING
// resetAllDrawingStructs, then points every list's sentinels at nop_function.
void resetAllDrawingStructs_tonop(void) {
    SceneTask* slot;
    s32 count;
    resetAllDrawingStructs();
    slot = lbl_803C7A24;
    count = 6;
    do {
        slot->func = nop_function;
        slot++;
    } while (--count != 0);
}
#endif

// .text:0x800B0CB8 size:0x70
// Task functions are called with a pointer to caller-stack scratch space.
typedef void (*DrawScriptFunc)(void* scratch);

// Runs the root task, then every task of the active list in order.
void RunDrawScripts_with_stack_variables(void) {
    u8 rootScratch[0x1C];
    u8 listScratch[0x14];
    SceneTask* task;
    lbl_803CC1B8 = &lbl_80111300;
    ((DrawScriptFunc)lbl_80111300.func)(rootScratch);
    task = &lbl_803C7A24[lbl_803CC1B0 * 2];
    do {
        lbl_803CC1B8 = task;
        ((DrawScriptFunc)task->func)(listScratch);
        task = task->next;
    } while (task != NULL);
}

// Sprite system globals (see SpriteWork / SpriteState).
extern SpriteWork lbl_802FE8B8;
// The same memory as lbl_802FE8B8.wanted/.committed and .proj; fn_800B24D4 addresses them by these names.
extern SpriteState lbl_802FEBF8[SPRITE_MAX_LAYERS * 2]; // TODO port: alias of lbl_802FE8B8.wanted
extern SpriteProj lbl_802FE918[SPRITE_MAX_LAYERS];      // TODO port: alias of lbl_802FE8B8.proj
extern SpriteDrawCmd lbl_80111340[2][SPRITE_MAX_LAYERS]; // per buffer, per layer
extern GDCurrentDL* lbl_803CC0F0;  // __GDCurrentDL
extern GDCurrentDL* lbl_803CC1C0;  // current layer's display list
extern s32 lbl_803CC1C4;           // display-list buffer being filled (0/1)
extern s32 lbl_803CC1C8;           // texcoord fraction bits
extern s32 lbl_803CC1CC;           // scissor x
extern s32 lbl_803CC1D0;           // scissor y
extern s32 lbl_803CC1D4;           // current layer
extern s32* lbl_803CC1D8[2];       // per buffer: optional per-layer display-list sizes
extern s32 lbl_803CC1E0;           // size of one display-list buffer
extern GDCurrentDL* lbl_803CC1E4;  // display lists of the buffer being filled
extern s32 lbl_803CBB28;           // scissor width
extern s32 lbl_803CBB2C;           // scissor height
extern s32 lbl_803CBB30;           // layer count
extern SpriteState* lbl_803CBB34;  // wanted state of the current layer
extern SpriteState* lbl_803CBB38;  // committed state of the current layer
extern s32 lbl_803CBB3C;           // display-list growth granularity
extern SpriteProj* lbl_803CBB40;   // default projection of the current layer
extern u8 lbl_803CBB18[8];         // BP commands: untextured TEV order
extern u8 lbl_803CBB20[8];         // BP commands: textured TEV order
extern s16 lbl_801115A0[4][2];     // quad texcoords (scaled by fn_800B27A4)
extern Mtx44 lbl_801115B0;         // screen projection for fn_800B1188
extern QuadVtx lbl_801115F0[4];    // full-screen quad
extern QuadVtx lbl_803C8A24[510];  // fn_800B13C0 vertex scratch

extern u8 lbl_80111580[]; // 4x4 white RGB5A3 texture
void fn_800A7D4C(s32 layer, DrawNode* node); // queue a draw node on a layer

// GD (display-list) functions; they write to lbl_803CC0F0.
void fn_800A1A70(GDCurrentDL* dl, u8* start, s32 length); // GDInitGDLObj
void fn_800A1BB0(GXBlendMode type, GXBlendFactor src, GXBlendFactor dst, GXLogicOp op); // GDSetBlendMode
void fn_800A1E3C(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1); // GDSetAlphaCompare
void fn_800A1F40(GXTexMapID id, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter minFilt, GXTexFilter magFilt,
                 f32 minLod, f32 maxLod, f32 lodBias, GXBool biasClamp, GXBool edgeLod, GXAnisotropy maxAniso); // GDSetTexLookupMode
void fn_800A2194(GXTexMapID id, u16 width, u16 height, GXTexFmt format); // GDSetTexImgAttr
void fn_800A2294(GXTexMapID id, void* image); // GDSetTexImgPtr
void fn_800A237C(GXTexMapID id, u32 tmemAddr, GXTlutFmt format); // GDSetTexTlut
void fn_800A246C(GXTexCoordID coord, u16 sScale, GXBool sBias, GXBool sWrap, u16 tScale, GXBool tBias, GXBool tWrap); // GDSetTexCoordScaleAndTOEs
void fn_800A26FC(void* tlut, u32 tmemAddr, GXTlutSize size); // GDLoadTlut

// Fills a projection from a 4x4 matrix, like GXSetProjection.
static inline void SpriteProjFromMtx(SpriteProj* proj, Mtx44 m, s32 type) {
    s32 col = (type == GX_ORTHOGRAPHIC) + 2;
    proj->type = type;
    proj->p[0] = m[0][0];
    proj->p[1] = m[0][col];
    proj->p[2] = m[1][1];
    proj->p[3] = m[1][col];
    proj->p[4] = m[2][2];
    proj->p[5] = m[2][3];
}

// Sets the wanted projection of the current layer.
static inline void SpriteSetProjection(Mtx44 m, s32 type) {
    SpriteProjFromMtx(&lbl_803CBB34->proj, m, type);
}

// Makes sure the current layer's display list has room for size more bytes.
static inline void SpriteReserve(s32 size) {
    s32 needed = size;
    needed -= lbl_803CC1C0->end - lbl_803CC1C0->pDisplayListData;
    if (needed > 0 && AllocateSprite(lbl_803CC1D4, needed) > 0) {
        OSPanic("sprt.c", 0x19F, "SPRITE BUFFER OVERFLOW\n");
    }
}

// Writes the BP Z-mode command; returns whether the committed Z mode changed.
static inline BOOL SpriteSyncZMode(void) {
    if (lbl_803CBB38->zMode != lbl_803CBB34->zMode) {
        lbl_803CBB38->zMode = lbl_803CBB34->zMode;
        SpriteReserve(5);
        *lbl_803CC1C0->pDisplayListData = 0x61;
        *(u32*)(lbl_803CC1C0->pDisplayListData + 1) = lbl_803CBB38->zMode;
        lbl_803CC1C0->pDisplayListData += 5;
        return TRUE;
    }
    return FALSE;
}

// fn_800B0D38, size:0x30
void fn_800B0D38(s32 index, s32 value) {
    if (index >= 0 && index < lbl_803CBB30) {
        lbl_80111340[1][index].link = value;
        lbl_80111340[0][index].link = value;
    }
}

// fn_800B0D28, size:0x10
void fn_800B0D28(s32* layerSizes) {
    lbl_803CC1D8[0] = layerSizes;
    lbl_803CC1D8[1] = layerSizes;
}

// .text:0x800B0D68 size:0x414
// NONMATCHING 90%: same instructions; register allocation and some scheduling differ
#if NONMATCHING
// Grows layer's display list by at least needed bytes, taking unused space from the
// neighbouring layers (moving the lists in between). Returns how many bytes are still missing.
s32 AllocateSprite(s32 layer, s32 needed) {
    s32 below;
    s32 above;
    s32 last;
    u8* flushStart;
    u8* flushEnd;
    s32 remaining;
    s32 take;
    s32 avail;
    s32 moved;
    s32 i;
    u8* src;

    if (needed <= 0) {
        return 0;
    }
    // Round up to the growth granularity (small requests) or to 32 bytes.
    remaining = (needed < lbl_803CBB3C) ? lbl_803CBB3C * ((lbl_803CBB3C + needed - 1) / lbl_803CBB3C)
                                        : (needed + 0x1F) / 32 * 32;
    below = layer;
    last = lbl_803CBB30 - 1;
    above = layer;
    flushEnd = lbl_803CC1E4[0].begin;
    flushStart = lbl_803CC1E4[last].end;
    do {
        // Take free space from the end of a lower layer: shift the layers in between down.
        below -= (below > 0);
        avail = lbl_803CC1E4[below].length -
                ((lbl_803CC1E4[below].pDisplayListData - lbl_803CC1E4[below].begin + 0x1F) & ~0x1F);
        if (remaining <= avail) {
            avail = remaining;
        }
        take = (below != layer) * avail;
        if (take != 0) {
            lbl_803CC1E4[below].length -= take;
            lbl_803CC1E4[below].end -= take;
            src = lbl_803CC1E4[below + 1].begin;
            moved = 0;
            i = below;
            do {
                i++;
                moved += lbl_803CC1E4[i].length;
                lbl_803CC1E4[i].begin -= take;
                lbl_803CC1E4[i].end -= take;
                lbl_803CC1E4[i].pDisplayListData -= take;
            } while (i < layer);
            if (moved != 0) {
                memmove(src - take, src, moved);
                if (flushStart > src - take) {
                    flushStart = src - take;
                }
                if (flushEnd < src) {
                    flushEnd = src;
                }
            }
            remaining -= take;
            lbl_803CC1E4[layer].length += take;
            lbl_803CC1E4[layer].end += take;
        }

        // Take free space from the end of a higher layer: shift the layers in between up.
        above += (above < last);
        avail = lbl_803CC1E4[above].length -
                ((lbl_803CC1E4[above].pDisplayListData - lbl_803CC1E4[above].begin + 0x1F) & ~0x1F);
        if (remaining <= avail) {
            avail = remaining;
        }
        take = (above != layer) * avail;
        if (take != 0) {
            lbl_803CC1E4[above].length -= take;
            lbl_803CC1E4[above].end -= take;
            src = lbl_803CC1E4[layer + 1].begin;
            moved = 0;
            for (i = layer + 1; i <= above; i++) {
                moved += lbl_803CC1E4[i].length;
                lbl_803CC1E4[i].begin += take;
                lbl_803CC1E4[i].end += take;
                lbl_803CC1E4[i].pDisplayListData += take;
            }
            if (moved != 0) {
                memmove(src + take, src, moved);
                if (flushEnd < src + take) {
                    flushEnd = src + take;
                }
                if (flushStart > src) {
                    flushStart = src;
                }
            }
            remaining -= take;
            lbl_803CC1E4[layer].length += take;
            lbl_803CC1E4[layer].end += take;
        }
    } while (remaining > 0 && (below != 0 || last - above != 0));

    if (flushStart < flushEnd) {
        DCStoreRange(flushStart, flushEnd - flushStart);
    }
    if (remaining > 0) {
        return remaining;
    }
    return 0;
}
#endif

// fn_800B117C, size:0xC
void fn_800B117C(u8 value) {
    lbl_803CBB34->noAlphaTest = value;
}

// .text:0x800B1188 size:0x11C
void fn_800B1188(void) {
    return;
}

// .text:0x800B12A4 size:0x38
void DrawNullSprite(QuadVtx* verts, s32 count) {
    DrawSprite(GX_TRIANGLESTRIP, verts, count, NULL, 0, 0);
}

// .text:0x800B12DC size:0x38
void fn_800B12DC(QuadVtx* verts, s32 count) {
    DrawSprite(GX_TRIANGLEFAN, verts, count, NULL, 0, 0);
}

// .text:0x800B1314 size:0x3C
void fn_800B1314(QuadVtx* verts, SpriteTexInfo* tex, u16 width, u16 height) {
    DrawSprite(GX_QUADS, verts, 4, tex, width, height);
}

// .text:0x800B1350 size:0x38
void DrawSprite_TexObj(QuadState* quad, SpriteTexInfo* tex) {
    DrawSprite(GX_QUADS, quad->u.v, 4, tex, tex->width, tex->height);
}

// .text:0x800B1388 size:0x38
void fn_800B1388(void) {
    return;
}

// .text:0x800B13C0 size:0xA8
void fn_800B13C0(void) {
    return;
}

// .text:0x800B1468 size:0x98
void fn_800B1468(void) {
    return;
}

// .text:0x800B1500 size:0x9BC
// NONMATCHING 94%: register allocation (verts/tex/dirty) differs, and the original evaluates an unused
// "all corners degenerate?" float check on verts (no effect, omitted here)
#if NONMATCHING
// Appends a primitive to the current layer's display list, first writing any state
// (projection, matrix, blend, alpha test, Z mode, texture) that differs from what the
// list already has. Consecutive quads with no state change are merged into one draw.
void DrawSprite(s32 prim, QuadVtx* verts, s32 count, SpriteTexInfo* tex, u16 width, u16 height) {
    BOOL dirty = FALSE;
    BOOL changed;
    s32 alphaTest;

    if (tex != NULL) {
        lbl_803CC0F0 = lbl_803CC1C0;
        dirty = fn_800B1EBC(tex, 0, width, height);
        lbl_803CC0F0 = NULL;
    }

    if (memcmp(&lbl_803CBB38->proj, &lbl_803CBB34->proj, sizeof(SpriteProj)) != 0) {
        memcpy(&lbl_803CBB38->proj, &lbl_803CBB34->proj, sizeof(SpriteProj));
        SpriteReserve(0x21);
        // XF load: 7 projection registers at 0x1020
        *lbl_803CC1C0->pDisplayListData = 0x10;
        *(u16*)(lbl_803CC1C0->pDisplayListData + 1) = 6;
        *(u16*)(lbl_803CC1C0->pDisplayListData + 3) = 0x1020;
        lbl_803CC1C0->pDisplayListData += 5;
        *(u32*)lbl_803CC1C0->pDisplayListData = *(u32*)&lbl_803CBB34->proj.p[0];
        lbl_803CC1C0->pDisplayListData += 4;
        *(u32*)lbl_803CC1C0->pDisplayListData = *(u32*)&lbl_803CBB34->proj.p[1];
        lbl_803CC1C0->pDisplayListData += 4;
        *(u32*)lbl_803CC1C0->pDisplayListData = *(u32*)&lbl_803CBB34->proj.p[2];
        lbl_803CC1C0->pDisplayListData += 4;
        *(u32*)lbl_803CC1C0->pDisplayListData = *(u32*)&lbl_803CBB34->proj.p[3];
        lbl_803CC1C0->pDisplayListData += 4;
        *(u32*)lbl_803CC1C0->pDisplayListData = *(u32*)&lbl_803CBB34->proj.p[4];
        lbl_803CC1C0->pDisplayListData += 4;
        *(u32*)lbl_803CC1C0->pDisplayListData = *(u32*)&lbl_803CBB34->proj.p[5];
        lbl_803CC1C0->pDisplayListData += 4;
        *(u32*)lbl_803CC1C0->pDisplayListData = lbl_803CBB34->proj.type;
        lbl_803CC1C0->pDisplayListData += 4;
        changed = TRUE;
    } else {
        changed = FALSE;
    }
    dirty |= changed;

    if (memcmp(lbl_803CBB38->mtx, lbl_803CBB34->mtx, sizeof(Mtx)) != 0) {
        PSMTXCopy(lbl_803CBB34->mtx, lbl_803CBB38->mtx);
        SpriteReserve(0x35);
        // XF load: position matrix 0 (12 registers at 0)
        *lbl_803CC1C0->pDisplayListData = 0x10;
        *(u16*)(lbl_803CC1C0->pDisplayListData + 1) = 0xB;
        *(u16*)(lbl_803CC1C0->pDisplayListData + 3) = 0;
        lbl_803CC1C0->pDisplayListData += 5;
        memcpy(lbl_803CC1C0->pDisplayListData, lbl_803CBB34->mtx, sizeof(Mtx));
        changed = TRUE;
        lbl_803CC1C0->pDisplayListData += sizeof(Mtx);
    } else {
        changed = FALSE;
    }
    dirty |= changed;

    if (lbl_803CBB38->blendMode != lbl_803CBB34->blendMode) {
        lbl_803CBB38->blendMode = lbl_803CBB34->blendMode;
        SpriteReserve(0xA);
        lbl_803CC0F0 = lbl_803CC1C0;
        switch (lbl_803CBB34->blendMode) {
        case 0:
            fn_800A1BB0(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_CLEAR);
            break;
        case 1:
            fn_800A1BB0(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
            break;
        case 2:
            fn_800A1BB0(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
            break;
        case 3:
            fn_800A1BB0(GX_BM_SUBTRACT, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
            break;
        }
        changed = TRUE;
    } else {
        changed = FALSE;
    }
    dirty |= changed;

    alphaTest = 0;
    if (lbl_803CBB34->noAlphaTest) {
        alphaTest = 2;
    }
    if (lbl_803CBB38->alphaTest == alphaTest) {
        changed = FALSE;
    } else {
        lbl_803CBB38->alphaTest = alphaTest;
        if (alphaTest != 0) {
            if (lbl_803CBB38->zMode != 0x40000013) {
                lbl_803CBB38->zMode = 0x40000013;
                SpriteReserve(5);
                *lbl_803CC1C0->pDisplayListData = 0x61;
                *(u32*)(lbl_803CC1C0->pDisplayListData + 1) = 0x40000013;
                lbl_803CC1C0->pDisplayListData += 5;
            }
            SpriteReserve(5);
            lbl_803CC0F0 = lbl_803CC1C0;
            fn_800A1E3C(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
            lbl_803CC0F0 = NULL;
        } else {
            if (lbl_803CBB38->zMode != lbl_803CBB34->zMode) {
                lbl_803CBB38->zMode = lbl_803CBB34->zMode;
                SpriteReserve(5);
                *lbl_803CC1C0->pDisplayListData = 0x61;
                *(u32*)(lbl_803CC1C0->pDisplayListData + 1) = lbl_803CBB34->zMode;
                lbl_803CC1C0->pDisplayListData += 5;
            }
            SpriteReserve(5);
            lbl_803CC0F0 = lbl_803CC1C0;
            fn_800A1E3C(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
            lbl_803CC0F0 = NULL;
        }
        changed = TRUE;
    }
    {
        BOOL zChanged = changed;
        if (!changed) {
            zChanged = SpriteSyncZMode();
        }
        dirty |= zChanged;
    }

    if ((lbl_803CBB34->textured == 1) == !tex) {
        u8* cmd = lbl_803CBB20;
        if (tex == NULL) {
            cmd = lbl_803CBB18;
        }
        SpriteReserve(5);
        memcpy(lbl_803CC1C0->pDisplayListData, cmd, 5);
        dirty = TRUE;
        lbl_803CC1C0->pDisplayListData += 5;
        lbl_803CBB34->textured = (tex != NULL);
    }

    if (lbl_803CBB34->primOffset >= 0 && !dirty) {
        u8* hdr = lbl_803CC1C0->begin + lbl_803CBB34->primOffset;
        u16 n = *(u16*)(hdr + 1);
        if (hdr[0] == GX_QUADS && prim == GX_QUADS &&
            lbl_803CC1C0->pDisplayListData == hdr + n * sizeof(QuadVtx) + 3 && n < 0xFFFF - count) {
            s32 size = count * sizeof(QuadVtx);
            SpriteReserve(size);
            hdr = lbl_803CC1C0->begin + lbl_803CBB34->primOffset;
            memcpy(lbl_803CC1C0->pDisplayListData, verts, size);
            lbl_803CC1C0->pDisplayListData += size;
            *(u16*)(hdr + 1) += count;
            return;
        }
    }
    {
        s32 size = count * sizeof(QuadVtx);
        lbl_803CBB34->primOffset = lbl_803CC1C0->pDisplayListData - lbl_803CC1C0->begin;
        SpriteReserve(size + 3);
        *lbl_803CC1C0->pDisplayListData = prim;
        *(u16*)(lbl_803CC1C0->pDisplayListData + 1) = count;
        lbl_803CC1C0->pDisplayListData += 3;
        memcpy(lbl_803CC1C0->pDisplayListData, verts, size);
        lbl_803CC1C0->pDisplayListData += size;
    }
}
#endif

// .text:0x800B1EBC size:0x2A4
// NONMATCHING 99%: map/width/height parameters get different saved registers
#if NONMATCHING
// Loads tex into texture map `map` of the current display list (if it isn't already)
// and sets the texcoord scale. Returns whether anything was written.
s32 fn_800B1EBC(SpriteTexInfo* tex, s32 map, u32 width, u32 height) {
    s32 id = map + 1;
    s32 written;
    lbl_803CBB34->texSerial[map] = lbl_803CBB34->serial;
    written = FALSE;
    lbl_803CBB34->serial++;
    if (lbl_803CBB34->tex[map] != tex) {
        lbl_803CBB34->tex[map] = tex;
        SpriteReserve(((tex->tlut != NULL) * 7 + 4) * 5);
        if (tex->tlut != NULL) {
            u32 tmem;
            u32 tlutSize = GX_TLUT_16;
            while (tlutSize * 16 < tex->tlutCount) {
                tlutSize *= 2;
            }
            tmem = (map << 13) + 0xC0000;
            fn_800A26FC(tex->tlut, tmem, tlutSize);
            fn_800A237C(id, tmem, tex->tlutFormat);
        }
        {
            s32 wrapS = tex->wrapS;
            s32 wrapT;
            // Only power-of-two dimensions can repeat/mirror.
            if (wrapS != GX_CLAMP) {
                u16 n = tex->width;
                u16 bits = 0;
                while (n != 0) {
                    bits += n & 1;
                    n >>= 1;
                }
                if (bits > 1) {
                    wrapS = GX_CLAMP;
                }
            }
            wrapT = tex->wrapT;
            if (wrapT != GX_CLAMP) {
                u16 n = tex->height;
                u16 bits = 0;
                while (n != 0) {
                    bits += n & 1;
                    n >>= 1;
                }
                if (bits > 1) {
                    wrapT = GX_CLAMP;
                }
            }
            fn_800A1F40(id, wrapS, wrapT, tex->minFilter, tex->magFilter, tex->minLod, tex->maxLod, tex->lodBias,
                        GX_FALSE, GX_FALSE, GX_ANISO_1);
        }
        fn_800A2194(id, tex->width, tex->height, tex->format);
        fn_800A2294(id, tex->image);
        written = TRUE;
    }
    if (lbl_803CBB34->texWidth != width || lbl_803CBB34->texHeight != height) {
        lbl_803CBB34->texWidth = width;
        lbl_803CBB34->texHeight = height;
        SpriteReserve(0xF);
        fn_800A246C(map, width, GX_FALSE, GX_FALSE, height, GX_FALSE, GX_FALSE);
        written = TRUE;
    }
    return written;
}
#endif

// fn_800B2160, size:0xC
void fn_800B2160(u8 value) {
    lbl_803CBB34->blendMode = value;
}

// fn_800B216C, size:0x3C
// Sets the wanted Z mode (enable, compare func, update enable); returns whether it changed.
s32 fn_800B216C(u8 flag, u32 mode, u8 index) {
    u32 value = ((u32)index << 4) | (flag | (mode << 1)) | 0x40000000;
    if (lbl_803CBB34->zMode == value) {
        return 0;
    }
    lbl_803CBB34->zMode = value;
    return 1;
}

// fn_800B21A8, size:0x98
void fn_800B21A8(s32 mode) {
    if (mode == 2) {
        s32 changed;
        u32 old = lbl_803CBB34->zMode;
        if (old == 0x40000013) {
            changed = 0;
        } else {
            lbl_803CBB34->zMode = 0x40000013;
            changed = 1;
        }
        if (changed != 0) {
            lbl_803CBB34->savedZMode = old;
        }
    } else if (mode != 0) {
        if (lbl_803CBB34->zMode != 0x40000017) {
            lbl_803CBB34->zMode = 0x40000017;
        }
    } else {
        if (lbl_803CBB34->zMode != 0x4000001F) {
            lbl_803CBB34->zMode = 0x4000001F;
        }
    }
}

// .text:0x800B2240 size:0x294
void fn_800B2240(void) {
    return;
}

// .text:0x800B24D4 size:0x48
void fn_800B24D4(void) {
    return;
}

// .text:0x800B251C size:0x288
void fn_800B251C(void) {
    return;
}

// .text:0x800B27A4 size:0x38
void fn_800B27A4(void) {
    return;
}

// .text:0x800B27DC size:0x78
void fn_800B27DC(void) {
    return;
}

// .text:0x800B2854 size:0x274
void fn_800B2854(void) {
    return;
}

// .text:0x800B2AC8 size:0x84
void fn_800B2AC8(void) {
    return;
}

// .text:0x800B2B4C size:0x8
void fn_800B2B4C(GameActor* actor, f32 value) {
    actor->unk90 = value;
}

// .text:0x800B2B54 size:0x18
void fn_800B2B54(GameActor* actor, u16 bone, u8 value) {
    actor->boneArray[bone]->unk134 = value;
}

// .text:0x800B2B6C size:0x8
void Set_FUN_800b2b6c(GameActor* actor, s32 value) {
    actor->unk88 = value;
}

// .text:0x800B2B74 size:0x34
// Moves a bone to the end of the actor's draw-priority list.
void fn_800B2B74(GameActor* actor, u16 bone) {
    DSInsertListObject(&actor->drawPriorityList, actor->drawPriorityList.Tail, (Ptr)actor->boneArray[bone]);
}

// .text:0x800B2BA8 size:0x3C
// Gives a bone another actor's bone's display object (or none); returns the old one.
struct DODisplayObj* fn_800B2BA8(GameActor* actor, u16 bone, GameActor* src, u16 srcBone) {
    GameBone* dst = actor->boneArray[bone];
    struct DODisplayObj* old = dst->dispObj;
    if (src != NULL) {
        dst->dispObj = src->boneArray[srcBone]->dispObj;
    } else {
        dst->dispObj = NULL;
    }
    return old;
}

// .text:0x800B2BE4 size:0x18
// Restores a bone's original display object.
void fn_800B2BE4(GameActor* actor, u16 bone) {
    GameBone* b = actor->boneArray[bone];
    b->dispObj = b->defaultDispObj;
}

// .text:0x800B2BFC size:0xC
void fn_800B2BFC(GameActor* actor, s16 a, s16 b) {
    actor->unk80 = a;
    actor->unk82 = b;
}

// .text:0x800B2C08 size:0x8
void fn_800B2C08(GameActor* actor, s16 value) {
    actor->unk84 = value;
}

// .text:0x800B2C10 size:0x34
// Transforms v in place by the actor's matrix at index.
void fn_800B2C10(GameActor* actor, u16 index, Vec* v) {
    PSMTXMultVec(actor->mtxArray[index], v, v);
}
