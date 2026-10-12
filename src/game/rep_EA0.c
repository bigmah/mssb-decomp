#include "game/rep_EA0.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#include "static/GameSettings.h"
#include "static/Camera.h"
#include "game/rep_D0.h"                // checkCollision
#include "game/rep_1838.h"              // angle helpers
#include "game/rep_3F60.h"              // fn_3_168FA0
#include "main/file_80008E00.h"         // lbl_80366158
#include "main/file_80011640.h"         // lbl_8036E548 (CharMgr), fn_8001D148
#include "main/file_8004207C.h"         // lbl_800E8754
#include "main/file_8004C5F8.h"         // fn_80052694, fn_80052734
#include "main/file_80069BDC.h"         // lbl_803CC1B8
#include "Dolphin/gx.h"
#include "Dolphin/OS/OSCache.h"
#include "stl/mem.h"
#include "stl/math.h"

extern u8 lbl_803CBBC0; // frame buffer in use (0/1)
extern void fn_800A7D4C(s32 layer, void* node);

// The original keeps these as separate statics that the compiler addresses through one
// pooled base, so they are modelled as one struct here. The ones that are also
// accessed through their own symbol are kept separate.
// The unit's .bss (0x200-0x16AC): ball trail state. The original addresses these through one pooled
// base, so they are file statics (CW lays .bss statics out in reverse declaration order).
static f32 sTrailAlpha;           // lbl_3_bss_16A8
static f32 sTrailAlphaStep;       // lbl_3_bss_16A4
static s32 sTrailType;            // lbl_3_bss_16A0
static s32 lbl_3_bss_169C;        // never read in this file
static TrailMesh sTrailMeshes[2]; // lbl_3_bss_164C
static VecQueue sTrailQueue;      // lbl_3_bss_1630
static Vec sTrailHistory[60];     // lbl_3_bss_1360
static u8 sTrailDisplayList[0x180];         // lbl_3_bss_11E0
static u8 sTrailDisplayListReversed[0x180]; // lbl_3_bss_1060
static Vec sTrailPositions[2][120];         // lbl_3_bss_520
static u32 sTrailColors[2][64];             // lbl_3_bss_320
static Vec sTrailCapPositions[2][8];        // lbl_3_bss_260
static u32 sTrailCapColors[2][8];           // lbl_3_bss_220
static u8 lbl_3_bss_210[0x10];
static s32 sTrailDelay;           // lbl_3_bss_20C: frames before the fade starts (-1: never)
static s32 sTrailFadeFrames;      // lbl_3_bss_208
static TexImage* lbl_3_bss_204;   // trail texture (NULL: untextured)
static s32 lbl_3_bss_200;
// The unit's .data (0x6820-0x69C0). The original addresses these through one pooled base, so they
// are file statics with their real contents, in address order (initialized statics keep declaration order).
static u8 lbl_3_data_6820[16] = { 0, 0, 0, 12, 13, 7, 7, 10, 11, 8, 9, 0, 0, 0, 0, 0 }; // lbl_8036E548.trail index per trailType
static f32 lbl_3_data_6830[2] = { 2.5f, 5.0f };
static f32 lbl_3_data_6838[2] = { 0.6f, 0.6f };
static f32 lbl_3_data_6840[2] = { 0.3f, 1.0f };
static TrailShadowData lbl_3_data_6848 = {
    { -0.1f, 1.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
};
// Trail texture coordinates (GX_U16, 14 fractional bits).
static u16 lbl_3_data_6860[8][2] = {
    { 0, 0x4000 }, { 0x4000, 0x4000 }, { 0, 0x2000 }, { 0x4000, 0x2000 },
    { 0, 0x1000 }, { 0x4000, 0x1000 }, { 0, 0x800 },  { 0x4000, 0x800 },
};
static BallTrailParams lbl_3_data_6880[12] = {
    { 0, 0.1f, 0.1f, 60 },   { 10, 0.2f, 0.2f, 30 },  { 11, 0.4f, 0.4f, 60 },  { 10, 0.3f, 0.3f, 50 },
    { 11, 0.5f, 0.5f, 100 }, { 11, 1.0f, 1.0f, 100 }, { 23, 0.4f, 0.4f, 100 }, { 23, 1.0f, 1.0f, 100 },
    { 30, 0.3f, 0.3f, 50 },  { 31, 0.3f, 0.3f, 50 },  { 33, 0.4f, 0.4f, 60 },  { 33, 0.4f, 0.4f, 60 },
};
// Per character id: trail texture (+0x21 in the archive).
static u8 lbl_3_data_6940[0x40] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x05, 0x00,
    0x00, 0x03, 0x06, 0x03, 0x00, 0x01, 0x00, 0x02, 0x01, 0x00, 0x03, 0x03, 0x06, 0x01, 0x02, 0x03,
    0x04, 0x01, 0x00, 0x03, 0x02, 0x05, 0x00, 0x06, 0x06, 0x06, 0x00, 0x03, 0x01, 0x02, 0x03, 0x06,
    0x05, 0x03, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// Display list of the trail's head cap (fn_3_67C34).
static u8 lbl_3_data_6980[0x20] = {
    0x80, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x03, 0x00, 0x03, 0x02, 0x00, 0x02, 0x02,
    0x01, 0x02, 0x03, 0x01, 0x03, 0x05, 0x02, 0x01, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static TrailNode lbl_3_data_69A0[2] = {
    { 0, fn_3_67C34, { NULL, NULL } },
    { 0, fn_3_67C34, { NULL, NULL } },
};
extern f32 lbl_803CB740[];
extern TrailHudView lbl_3_common_bss_32724;
extern TrailPauseView lbl_3_common_bss_34C90;
extern TrailFadeView lbl_3_common_bss_35154;
extern TrailStadiumView lbl_3_common_bss_350E4;
extern TrailFielder g_Fielders[9];

#define TRAIL_TASK ((TrailTask*)lbl_803CC1B8)


// .text:0x0006750C size:0xAC mapped:0x806A65A0
void fn_3_6750C(TexArchive* archive) {
    BallTrailParams* p = &lbl_3_data_6880[1];
    s32 i;
    for (i = 0; i < 11; i++, p++) {
        p->tex.image = &archive->entries[p->tex.index];
        if (0.0f == p->widthRatio) {
            p->widthRatio = 1.0f;
        } else {
            p->widthRatio = p->widthRatio / p->width;
        }
        p->length = p->length * 60 / 100;
        if (p->length < 2) {
            p->length = 2;
        }
    }
    lbl_3_bss_169C = 0;
}

// .text:0x000675B8 size:0x68 mapped:0x806A664C
void fn_3_675B8(u16 frames) {
    if (frames == 0) {
        lbl_3_common_bss_32724.trailActive = 0;
        sTrailAlpha = 0.0f;
        return;
    }
    sTrailDelay = frames;
    sTrailAlphaStep = sTrailAlpha / (f32)frames;
}

// .text:0x00067620 size:0x298 mapped:0x806A66B4
// NONMATCHING 94%: the display list header bytes do not reuse the loop induction registers (posA/i/posB)
#if NONMATCHING
void fn_3_67620(s32 type, u16 frames) {
    u8* start;
    u8* dl;
    u8* src;
    u8* dst;
    s32 i;
    s32 posA;
    s32 posB;

    sTrailType = type;
    if (type == 10) {
        lbl_3_data_6880[type].tex.image =
            &lbl_3_common_bss_35154.archive->entries[lbl_3_data_6940[g_Pitcher.charID] + 0x21];
    } else if (type == 11) {
        lbl_3_data_6880[type].tex.image =
            &lbl_3_common_bss_35154.archive->entries[lbl_3_data_6940[g_Batter.charID] + 0x21];
    }
    sTrailAlpha = 255.0f;
    if (frames == 0) {
        sTrailDelay = -1;
        sTrailAlphaStep = 0.0f;
    } else if (lbl_3_data_6880[type].tex.image != NULL) {
        sTrailDelay = frames - 8;
        sTrailFadeFrames = 8;
        sTrailAlphaStep = 31.875f;
    } else {
        sTrailDelay = 0;
        sTrailFadeFrames = frames;
        sTrailAlphaStep = 255.0f / (f32)(s32)frames;
    }
    lbl_3_bss_204 = lbl_3_data_6880[type].tex.image;
    fn_80023EEC(&sTrailQueue, sTrailHistory, lbl_3_data_6880[type].length);

    // Triangle strip over the 60 point pairs: (pos, color, texcoord) index8 triples.
    start = dl = sTrailDisplayList;
    i = 1;
    posA = 2;
    posB = 3;
    dl[0] = GX_TRIANGLESTRIP | GX_VTXFMT0;
    dl[1] = 0;
    dl[2] = 120;
    dl[3] = 0;
    dl[4] = 0;
    dl[5] = posA;
    dl[6] = i;
    dl[7] = 0;
    dl[8] = posB;
    dl += 9;
    do {
        dl[0] = posA;
        dl[1] = i;
        dl[2] = 6 - ((i & 1) << 1);
        dl[3] = posB;
        posA += 2;
        dl[4] = i;
        posB += 2;
        dl[5] = 7 - ((i & 1) << 1);
        dl += 6;
        i++;
    } while (i < 60);
    DCStoreRangeNoSync(start, dl - start);

    // Same strip with the vertices in reverse order.
    memcpy(sTrailDisplayListReversed, sTrailDisplayList, 3);
    src = sTrailDisplayList + 3;
    dst = sTrailDisplayListReversed + 3 + 120 * 3;
    i = 119;
    do {
        dst -= 3;
        memcpy(dst, src, 3);
        src += 3;
    } while (i-- != 0);
    DCStoreRangeNoSync(sTrailDisplayListReversed, 3 + 120 * 3);
    lbl_3_common_bss_32724.trailActive = 1;
}
#endif

// .text:0x000678B8 size:0x190 mapped:0x806A694C
// NONMATCHING 83%: scheduling of the argument setup before fn_3_67EF0 (the original loads lbl_803CC1B8
// with addi + lwz 0 and the trail type after it) and register numbering after the call
#if NONMATCHING
void fn_3_678B8(void) {
    s32 buf = lbl_803CBBC0;
    s32 side;
    TrailMesh* mesh;
    TrailNode* node;

    side = fn_3_67EF0(&sTrailQueue, 60, sTrailPositions[buf], sTrailColors[buf], (u32)sTrailAlpha | 0xFFFFFF00,
                      sTrailCapPositions[buf], sTrailCapColors[buf], TRAIL_TASK->dir, lbl_3_data_6880[sTrailType].width);
    side = (side + 1) >> 1;
    buf = lbl_803CBBC0;
    sTrailMeshes[buf].body.positions = sTrailPositions[buf];
    sTrailMeshes[buf].body.texCoords = lbl_3_data_6860;
    sTrailMeshes[buf].body.colors = sTrailColors[buf];
    sTrailMeshes[buf].cap.positions = sTrailCapPositions[buf];
    sTrailMeshes[buf].cap.texCoords = lbl_3_data_6860;
    sTrailMeshes[buf].cap.colors = sTrailCapColors[buf];
    sTrailMeshes[buf].cap.displayListSize = sizeof(lbl_3_data_6980);
    sTrailMeshes[buf].cap.displayList = lbl_3_data_6980;
    mesh = &sTrailMeshes[buf];
    if (side) {
        mesh->body.displayListSize = sizeof(sTrailDisplayListReversed);
        node = &lbl_3_data_69A0[buf];
        node->strips[0] = &mesh->cap;
        mesh->body.displayList = sTrailDisplayListReversed;
        node->strips[1] = &mesh->body;
    } else {
        mesh->body.displayListSize = sizeof(sTrailDisplayList);
        node = &lbl_3_data_69A0[buf];
        node->strips[0] = &mesh->body;
        mesh->body.displayList = sTrailDisplayList;
        node->strips[1] = &mesh->cap;
    }
    fn_800B0A14_removeQueue(node);
}
#endif

// .text:0x00067A48 size:0x1EC mapped:0x806A6ADC
void fn_3_67A48(void) {
    Vec pos;
    Vec last;
    s32 push;
    TrailTask* task;

    if (sTrailAlpha > 0.0f) {
        if (lbl_80366158._28 == 0) {
            push = 1;
            if (g_Ball.fielderActionOccuring) {
                pos.x = g_Ball.fielderActionCatchCoords.x;
                pos.y = -g_Ball.fielderActionCatchCoords.y;
                pos.z = g_Ball.fielderActionCatchCoords.z;
            } else {
                pos.x = g_Ball.AtBat_Contact_BallPos.x;
                pos.y = -g_Ball.AtBat_Contact_BallPos.y;
                pos.z = g_Ball.AtBat_Contact_BallPos.z;
            }
            if (sTrailQueue.count != 0) {
                fn_80023D4C(&sTrailQueue, &last);
                if (memcmp(&pos, &last, sizeof(Vec)) == 0) {
                    push = 0;
                }
            }
            if (push) {
                fn_80023E48(&sTrailQueue, &pos);
            }
        }
        if (sTrailQueue.count >= 2) {
            task = fn_800B0A5C_insertQueue(fn_3_678B8, 1000);
            if (sTrailType == 6 || sTrailType == 7) {
                task->dir = &task->dirBuf;
                task->dirBuf.x = 1.0f;
                task->dirBuf.y = 0.0f;
                task->dirBuf.z = 0.0f;
            } else {
                task->dir = NULL;
            }
            fn_800A7D4C(0, &lbl_3_data_69A0[lbl_803CBBC0]);
            if (lbl_80366158._28 == 0) {
                if (sTrailDelay != 0) {
                    sTrailDelay -= (sTrailDelay > 0);
                } else if (--sTrailFadeFrames != 0) {
                    sTrailAlpha -= sTrailAlphaStep;
                } else {
                    sTrailAlpha = 0.0f;
                }
            }
        }
    }
}

// .text:0x00067C34 size:0x2BC mapped:0x806A6CC8
// NONMATCHING 98%: the original moves node through r0 and schedules li r3,0 before saving r31
#if NONMATCHING
void fn_3_67C34(TrailNode* node) {
    Mtx m = { { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 0.0f } };
    s32 i;

    fn_80052694(0);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 14);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_MTX2x4, GX_TG_TEXCOORD0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    if (lbl_3_bss_204 != NULL) {
        lbl_3_bss_204->wrapT = GX_CLAMP;
        SetDisplayStateTexture(lbl_3_bss_204, 0, 0);
    }
    if (lbl_3_bss_204 != NULL) {
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    } else {
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    }
    GXSetZCompLoc(GX_FALSE);
    GXInvalidateVtxCache();
    for (i = 0; i < 2; i++) {
        GXSetArray(GX_VA_POS, node->strips[i]->positions, sizeof(Vec));
        GXSetArray(GX_VA_CLR0, node->strips[i]->colors, sizeof(u32));
        GXSetArray(GX_VA_TEX0, node->strips[i]->texCoords, 2 * sizeof(u16));
        GXCallDisplayList(node->strips[i]->displayList, node->strips[i]->displayListSize);
    }
}
#endif

// Builds the trail vertices from the position history. Returns which way the trail
// faces the camera (-1/1), which picks the strip draw order.
// .text:0x00067EF0 size:0x700 mapped:0x806A6F84
// NONMATCHING 85%: stack slot order and register allocation differ; same calls and math
#if NONMATCHING
s32 fn_3_67EF0(VecQueue* queue, s32 maxPoints, Vec* positions, u32* colors, u32 color, Vec* capPositions,
               u32* capColors, Vec* dir, f32 width) {
    Vec side;     // 0x08
    Vec offset;   // 0x14
    Vec pt[2];    // 0x20
    Vec near;     // 0x38
    Vec far;      // 0x44
    Mtx view;     // 0x50
    s32 cur;
    s32 count;
    s32 alpha;
    s32 segs;
    s32 i;
    s32 facing;
    u32 rgb;
    u32 headAlpha;
    s32 capAlpha;
    f32 angle;
    Vec* p;
    Vec* prev;
    Vec* out;

    colors[0] = color;
    alpha = color & 0xFF;
    PSMTXCopy(((camera_803c639c_s*)fn_80052734(0))->view, view);
    cur = 1;
    count = 0;
    fn_80023DFC(queue, &pt[0]);
    PSMTXMultVec(view, &pt[0], &pt[0]);
    out = positions;
    while (p = &pt[cur], fn_80023D98(queue, p) != 0) {
        PSMTXMultVec(view, p, p);
        prev = &pt[cur == 0];
        if (p->z == prev->z) {
            memcpy(&near, prev, sizeof(Vec));
            memcpy(&far, p, sizeof(Vec));
        } else if (0.0f != prev->z) {
            near.x = prev->x * p->z / prev->z;
            near.y = prev->y * p->z / prev->z;
            near.z = prev->z;
            memcpy(&far, p, sizeof(Vec));
        } else {
            memcpy(&near, prev, sizeof(Vec));
            far.x = p->x * prev->z / p->z;
            far.y = p->y * prev->z / p->z;
            far.z = p->z;
        }
        PSVECSubtract(&near, &far, &side);
        side.z = 0.0f;
        if (PSVECMag(&side) != 0.0f) {
            PSVECNormalize(&side, &offset);
            memcpy(out, prev, sizeof(Vec));
            PSVECScale(&offset, width, &positions[count * 2 + 1]);
            cur ^= 1;
            out += 2;
            count++;
        }
    }
    prev = &pt[cur == 0];
    memcpy(&positions[count * 2], prev, sizeof(Vec));
    memcpy(&positions[count * 2 + 1], prev, sizeof(Vec));
    segs = count * alpha / 255;
    colors[count] = 0xFFFFFF00;
    PSVECNormalize(&positions[1], &side);
    PSVECSubtract(&positions[0], &positions[2], &pt[0]);
    if (PSVECMag(&pt[0]) != 0.0f) {
        PSVECNormalize(&pt[0], &pt[0]);
    }
    angle = acos(PSVECDotProduct(&pt[0], &side));
    side.z = -side.y;
    side.y = side.x;
    side.x = side.z;
    side.z = 0.0f;

    // Turn each center point + offset pair into the two edge vertices.
    rgb = color & 0xFFFFFF00;
    for (i = 0; i < segs; i++) {
        memcpy(&pt[0], &positions[i * 2], sizeof(Vec));
        if (dir != NULL) {
            PSVECScale(dir, width * (f32)(segs - i) / (f32)segs, &offset);
        } else {
            PSVECScale(&positions[i * 2 + 1], (f32)(segs - i) / (f32)segs, &offset);
            offset.z = -offset.y;
            offset.y = offset.x;
            offset.x = offset.z;
            offset.z = 0.0f;
        }
        PSVECAdd(&pt[0], &offset, &positions[i * 2]);
        PSVECSubtract(&pt[0], &offset, &positions[i * 2 + 1]);
        colors[i] = rgb | (u8)(alpha * (segs - i) / segs);
    }

    if (positions[0].z >= positions[(segs - 1) * 2].z) {
        facing = -1;
    } else {
        facing = 1;
    }
    PSMTXRotAxisRad(view, &side, angle * (f32)-facing);

    // Head cap: a fan of 3 x 2 vertices around the first two edge vertices.
    for (i = 0; i < 2; i++) {
        if (dir != NULL) {
            f32 t;
            PSVECScale(dir, width, &side);
            t = side.y;
            side.y = side.x;
            side.x = -t;
        } else {
            PSVECSubtract(&positions[i], &positions[i + 2], &side);
            if (PSVECMag(&side) != 0.0f) {
                PSVECNormalize(&side, &side);
            } else {
                side.y = 0.0f;
                side.z = 0.0f;
                side.x = 1.0f;
            }
            PSVECScale(&side, width, &side);
        }
        PSMTXMultVec(view, &side, &side);
        PSVECAdd(&positions[i], &side, &capPositions[i]);
        memcpy(&capPositions[i + 2], &positions[i], sizeof(Vec));
        PSVECSubtract(&positions[i], &side, &capPositions[i + 4]);
    }

    capColors[0] = colors[0];
    capColors[1] = colors[0];
    capColors[2] = colors[0];
    if (angle > 1.5707964f) {
        angle = 3.1415927f - angle;
    }
    angle = angle / 1.5707964f;
    headAlpha = colors[0] & 0xFF;
    capColors[1] &= 0xFFFFFF00;
    capColors[2] &= 0xFFFFFF00;
    colors[0] &= 0xFFFFFF00;
    capAlpha = (f32)headAlpha * angle;
    capColors[1] |= (u8)capAlpha;
    capColors[2] |= (u8)capAlpha;
    colors[0] |= (u8)(headAlpha - capAlpha);

    memset(&positions[segs * 2], 0, (maxPoints - segs) * 2 * sizeof(Vec));
    memset(&colors[segs], 0, (maxPoints - segs) * sizeof(u32));
    DCStoreRangeNoSync(positions, maxPoints * 2 * sizeof(Vec));
    DCStoreRangeNoSync(colors, maxPoints * sizeof(u32));
    DCStoreRangeNoSync(capPositions, 6 * sizeof(Vec));
    DCStoreRangeNoSync(capColors, 6 * sizeof(u32));
    return facing;
}
#endif

// Picks the trail type for the current pitch / hit.
// .text:0x000685F0 size:0x5C4 mapped:0x806A7684
void fn_3_685F0(void) {
    if (g_Minigame.GameMode_MiniGame == 4 || g_Minigame.GameMode_MiniGame == 5 ||
        g_Minigame.GameMode_MiniGame == 6) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU) {
            fn_3_675B8(0);
            return;
        }
        if (g_Practice.tutorialState == 2) {
            fn_3_675B8(0);
            return;
        }
        if (g_Practice._19F != 0) {
            if (lbl_3_common_bss_34C90.state == 7 || lbl_3_common_bss_34C90.state == 9 ||
                lbl_3_common_bss_34C90.state == 11) {
                fn_3_675B8(0);
                return;
            }
        }
    }

    if (g_Ball.pitchHangtimeCounter == 1) {
        if (g_Pitcher.starPitchType != 0) {
            if (g_Pitcher.starPitchType == 5 || g_Pitcher.starPitchType == 6) {
                fn_3_67620(5, 45);
            } else if (g_Pitcher.starPitchType == 9 || g_Pitcher.starPitchType == 10) {
                fn_3_67620(6, 120);
            } else {
                fn_3_675B8(0);
            }
        } else if (g_Pitcher.starPitchType == 0 && g_Pitcher.ballHaloTrainInd_unused) {
            fn_3_67620(10, 45);
        } else if (g_Pitcher.ChargePitchType == 3) {
            fn_3_67620(2, 45);
        } else if (g_Pitcher.ChargePitchType != 0) {
            fn_3_67620(1, 45);
        } else {
            fn_3_67620(1, 45);
        }
    } else if (g_Ball.pitchHangtimeCounter >= 1 && g_Ball.framesSinceHit <= 0) {
        if (lbl_3_common_bss_32724.trailActive && g_Pitcher.pitcherActionState == 4) {
            fn_3_675B8(0);
        }
    } else if (g_Ball.framesSinceHit == 1) {
        fn_3_675B8(0);
    } else if (g_Ball.framesSinceHit == 2) {
        if (g_Minigame.GameMode_MiniGame == 1) {
            if (g_Ball.bODQualifyingHitInd) {
                fn_3_67620(3, 180);
            } else {
                fn_3_675B8(0);
            }
        } else if (g_Ball.currentStarSwing != 0) {
            if (g_Ball.currentStarSwing == 5 || g_Ball.currentStarSwing == 6) {
                fn_3_67620(5, 90);
            } else if (g_Ball.currentStarSwing == 9 || g_Ball.currentStarSwing == 10) {
                fn_3_67620(7, 180);
            } else {
                fn_3_675B8(0);
            }
        } else if (!g_Batter.captainStarSwingActivated && g_Batter.didNonCaptainStarSwingConnect) {
            fn_3_67620(11, 90);
        } else if (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy) {
            fn_3_67620(4, 90);
        } else {
            fn_3_67620(3, 90);
        }
    } else if (g_Ball.framesSinceHit > 0) {
        if (lbl_3_common_bss_32724.trailActive) {
            if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
                fn_3_675B8(0);
            }
            if (g_Minigame.GameMode_MiniGame == 3) {
                if (g_Minigame.barrelBatter_scoreCalculatedInd) {
                    fn_3_675B8(0);
                }
            } else if (g_Ball.timeSinceBallPickedUp == 0) {
                fn_3_675B8(0);
            } else if (g_Ball.numFieldersWhoHandledBallDuringPlay == 1 && g_Ball.numberOfThrowsDuringPlay == 0) {
                fn_3_675B8(0);
            } else if (0.0f == g_Ball.ballVelocity) {
                fn_3_675B8(0);
            }
        }
        if (g_Ball.framesSinceThrowStarted == 1) {
            if (g_FieldingLogic._13E) {
                fn_3_168FA0(g_Ball.fielderBeingThrownTo, 0);
                fn_3_168FA0(g_Ball.throwingFielder, 0);
                fn_3_67620(8, 90);
            } else if (g_Ball.IsAntichemistryThrow) {
                fn_3_168FA0(g_Ball.fielderBeingThrownTo, 1);
                fn_3_168FA0(g_Ball.throwingFielder, 1);
                fn_3_67620(9, 90);
            } else if (g_FieldingLogic._140) {
                fn_3_67620(2, 90);
            } else if (g_FieldingLogic._13D || g_FieldingLogic.throwSpeedType == 1) {
                fn_3_67620(1, 90);
            }
        }
    }
}

// Spins the ball model.
// .text:0x00068BB4 size:0x548 mapped:0x806A7C48
void fn_3_68BB4(void) {
    if (lbl_80366158._28 != 0 && lbl_3_common_bss_32724.trailType != 7 && lbl_3_common_bss_32724.trailType != 8) {
        return;
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
        if (g_Minigame.GameMode_MiniGame == 1) {
            if (g_Pitcher.pitcherActionState == 3) {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw += 50;
            } else {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
            }
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        } else if (lbl_3_common_bss_32724.trailType == 9 || lbl_3_common_bss_32724.trailType == 10) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw += 300;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch += 100;
        } else if (lbl_3_common_bss_32724.trailType == 7 || lbl_3_common_bss_32724.trailType == 8) {
            if (g_Pitcher.bulletPitchStageCode == 1) {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw =
                    radToShortAngle(3.1415927f + (6.2831855f - g_Pitcher.bulletPitchLoopAngleRadians));
            } else {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
            }
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        } else if (lbl_3_common_bss_32724.trailType == 5 || lbl_3_common_bss_32724.trailType == 6) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
            if (g_Pitcher.handedness) {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch += 200;
            } else {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch -= 200;
            }
        } else if (lbl_3_common_bss_32724.trailType == 11 || lbl_3_common_bss_32724.trailType == 12) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        } else {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw -= 600;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
        if (g_Minigame.GameMode_MiniGame == 1) {
            if (g_Ball.AtBat_ContactResult == 0) {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw += (s32)(400.0f * g_Ball.ballVelocity);
            } else {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw -= (s32)(400.0f * g_Ball.ballVelocity);
            }
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        } else if (g_Ball.fielderWBallIndex >= 0) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
        } else if (lbl_3_common_bss_32724.trailType == 9 || lbl_3_common_bss_32724.trailType == 10) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = -(g_Ball.ballTravelAngle - 0x400);
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw += (s32)(200.0f * g_Ball.ballVelocity);
        } else if (lbl_3_common_bss_32724.trailType == 7 || lbl_3_common_bss_32724.trailType == 8) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = fn_3_9FE6C_normalizeAngle(0xC00 - g_Ball.Hit_HorizontalAngle);
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        } else if (lbl_3_common_bss_32724.trailType == 5 || lbl_3_common_bss_32724.trailType == 6) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
            if (g_Batter.batterHand) {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch -= 200;
            } else {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch += 200;
            }
        } else if (lbl_3_common_bss_32724.trailType == 11 || lbl_3_common_bss_32724.trailType == 12) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        } else {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0x800 - g_Ball.ballTravelAngle;
            if (g_Ball.AtBat_ContactResult == 0) {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw += (s32)(400.0f * g_Ball.ballVelocity);
            } else if (g_Ball.ballState == 2 && !g_Ball.thrownBallHasHitGround) {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw += (s32)(800.0f * g_Ball.ballVelocity);
            } else {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw -= (s32)(400.0f * g_Ball.ballVelocity);
            }
        }
    } else {
        g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
        g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
    }
    g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw =
        fn_3_9FE6C_normalizeAngle(g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw);
    g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch =
        fn_3_9FE6C_normalizeAngle(g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch);
    g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll =
        fn_3_9FE6C_normalizeAngle(g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll);
}

// .text:0x000690FC size:0x70 mapped:0x806A8190
void fn_3_690FC(void) {
    lbl_8036E548.trail[0]._26 = 0;
    lbl_8036E548.trail[1]._26 = 0;
    lbl_8036E548.trail[2]._26 = 0;
    lbl_8036E548.trail[3]._26 = 0;
    lbl_8036E548.trail[5]._26 = 0;
    lbl_8036E548.trail[6]._26 = 0;
    lbl_8036E548.trail[7]._26 = 0;
    lbl_8036E548.trail[8]._26 = 0;
    lbl_8036E548.trail[9]._26 = 0;
    lbl_8036E548.trail[10]._26 = 0;
    lbl_8036E548.trail[12]._26 = 0;
    lbl_8036E548.trail[13]._26 = 0;
}

// .text:0x0006916C size:0x18 mapped:0x806A8200
void fn_3_6916C(void) {
    lbl_3_common_bss_32724.trailType = 0;
    lbl_3_common_bss_32724.trailActive = 0;
}

// Bat shadow.
// .text:0x00069184 size:0x15C mapped:0x806A8218
void fn_3_69184(void) {
    CharTrail* p;
    if (g_Batter.trimmedBat == 1) {
        p = &lbl_8036E548.trail[6];
    } else {
        p = &lbl_8036E548.trail[5];
    }
    p->_26 = 0;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU) {
            return;
        }
        if (g_Practice.practiceLevel != 4 && g_Practice.practiceType_2 != 1) {
            return;
        }
    } else if (g_Batter.easyBatting == 0) {
        return;
    }
    if (g_Stats.replayInd != 0) {
        return;
    }
    if (g_GameLogic.gameStatus != GAME_STATUS_DEFAULT && g_GameLogic.gameStatus != GAME_STATUS_AT_BAT) {
        return;
    }
    if (g_GameLogic.sceneID != SCENE_ID_AT_BAT) {
        return;
    }
    p->_26 = 1;
    if (g_Batter.batterHand != 0) {
        p->_04[0] = -g_Batter.batPosition2.x;
        p->_04[4] = 3.1415927f;
    } else {
        p->_04[0] = g_Batter.batPosition2.x;
        p->_04[4] = 0.0f;
    }
    p->_04[2] = g_Batter.batPosition2.z + lbl_3_data_6848.shadowOffset[1];
    p->_04[1] = lbl_3_data_6848.shadowOffset[0];
}

// Ball landing marker.
// .text:0x000692E0 size:0x318 mapped:0x806A8374
void fn_3_692E0(void) {
    VecSrcDst ray;
    CollisionStruct coll;
    CharTrail* marker;
    s32 idx;
    u32 hit;
    f32 height;
    f32 rot;
    f32 scale;

    lbl_8036E548.trail[2]._26 = 0;
    lbl_8036E548.trail[3]._26 = 0;
    if (g_Stats.replayInd != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        return;
    }
    if (g_Minigame.GameMode_MiniGame != 0) {
        return;
    }
    if (g_Ball.pauseBallMovementWhenInPlant != 0 || g_Ball.frameCountdownAfterLeavingPlant != 0) {
        return;
    }
    if (g_Ball.deadBallReason != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE &&
        lbl_800E8754.port[g_GameLogic.teams[g_GameLogic.teamFielding]]._4 == 0) {
        return;
    }
    if (g_GameLogic.sceneID != SCENE_ID_LIVE_BALL) {
        return;
    }
    if (g_FieldingLogic._107 != 0) {
        return;
    }
    if (g_Ball.AtBat_ContactResult != 0) {
        return;
    }
    if (g_Ball.maxYOfHit < 2.0f) {
        return;
    }
    if (g_Ball.currentStarSwing2 == 11 || g_Ball.currentStarSwing2 == 12) {
        return;
    }
    if (g_Ball.warioWaluGarlicIsActive != 0) {
        return;
    }

    if (g_FieldingLogic._144 != 0) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE &&
            (g_Practice.practiceType_2 == 1 || g_Practice.practiceLevel == 4)) {
            idx = 2;
        } else {
            idx = 3;
        }
    } else {
        idx = 2;
    }
    marker = &lbl_8036E548.trail[idx];
    marker->_26 = 1;
    ray.src.x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    ray.src.y = -1.0f;
    ray.src.z = g_Ball.physicsSubstruct.hitLandingSpotDistFromHome;
    ray.dst.x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    ray.dst.y = 1.0f;
    ray.dst.z = g_Ball.physicsSubstruct.hitLandingSpotDistFromHome;
    hit = checkCollision(&ray, &coll, 0, FALSE);
    if (hit == BALL_COLLISION_TYPE_GRASS || hit == BALL_COLLISION_TYPE_DIRT ||
        (u32)(hit - BALL_COLLISION_TYPE_ROUGH_TERRAIN) <= 1 || hit == 0x32) {
        marker->_04[1] = coll.position.y - 0.06f;
    } else {
        marker->_04[1] = -0.06f;
    }
    marker->_04[0] = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    marker->_04[2] = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
    rot = marker->_04[4];
    height = 30.0f - g_Ball.AtBat_Contact_BallPos.y;
    if (height < 1.0f) {
        height = 1.0f;
    }
    height *= 0.003f;
    marker->_04[4] = fn_3_9FEA8(rot + height);
    scale = LinearInterpolateToNewRange((f32)g_Ball.framesUntilBallHitsGround, 0.0f, 120.0f, lbl_3_data_6840[0],
                                        lbl_3_data_6840[1]);
    fn_8001D148(idx, scale, scale, scale);
}

// Ball shadow.
// .text:0x000695F8 size:0x1D4 mapped:0x806A868C
void fn_3_695F8(s32 flag) {
    CharTrail* p = lbl_8036E548.trail;
    s32 t;
    p[1]._26 = 0;
    p[1]._04[0] = g_Ball.AtBat_Contact_BallPos.x;
    p[1]._04[1] = -g_Ball.physicsSubstruct.twoFrameLookback[1] - 0.04f;
    p[1]._04[2] = g_Ball.AtBat_Contact_BallPos.z;
    if (g_Ball.warioWaluGarlicIsActive != 0) {
        if (g_Ball.framesSinceHit & 1) {
            p[1]._04[0] = g_Ball.warioStarHitCoords[2].x;
            p[1]._04[2] = g_Ball.warioStarHitCoords[2].z;
        }
    } else if (g_Pitcher.warioWaluStarAnimationStage == 1 && (g_Pitcher.pitchTotalTimeCounter & 1)) {
        p[1]._04[0] = g_Pitcher.ballCurrentPosition.x + g_Pitcher.pitchX_parabolicAdjustment -
                      g_Pitcher.starPitchPositionAdjustment.x;
    }
    if (g_Ball.fielderActionOccuring != 0) {
        p[1]._04[0] = g_Ball.fielderActionCatchCoords.x;
        p[1]._04[1] = -g_Ball.fielderActionCatchCoords.y;
        p[1]._04[2] = g_Ball.fielderActionCatchCoords.z;
    }
    if (g_Ball.hitNoteBlockInd != 0) {
        p[1]._04[0] = lbl_3_common_bss_350E4.noteBlockPos.x;
        p[1]._04[2] = lbl_3_common_bss_350E4.noteBlockPos.z;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        fn_8001D148(1, lbl_3_data_6830[1], 1.0f, lbl_3_data_6830[1]);
    } else {
        fn_8001D148(1, lbl_3_data_6830[0], 1.0f, lbl_3_data_6830[0]);
    }
    if (flag != 0) {
        t = g_Ball.collisionCode & 0x7F;
        if (t == 1 || t == 6 || (u32)(t - 9) <= 1 || (t >= 0x70 && t < 0x79)) {
            p[1]._26 = 1;
        }
    }
}

// Updates the ball model, its trail and the shadows each frame.
// .text:0x000697CC size:0x994 mapped:0x806A8860
// NONMATCHING 97%: register allocation; the original reads the scale table lbl_800E84B0 with lfsx
#if NONMATCHING
void fn_3_697CC(void) {
    CharTrail* trail;
    CharTrail* extra;
    s32 extraIdx;
    s32 scaleIdx;
    s32 row;
    s32 held;
    u8 status;
    u8 st;
    f32 scale;
    Vec avg;

    extra = NULL;
    lbl_8036E548.trail[0]._26 = 0;
    lbl_8036E548.trail[7]._26 = 0;
    lbl_8036E548.trail[8]._26 = 0;
    lbl_8036E548.trail[9]._26 = 0;
    lbl_8036E548.trail[10]._26 = 0;
    lbl_8036E548.trail[11]._26 = 0;
    lbl_8036E548.trail[12]._26 = 0;
    lbl_8036E548.trail[13]._26 = 0;
    lbl_8036E548.trail[14]._26 = 0;
    lbl_8036E548.trail[15]._26 = 0;
    lbl_8036E548.trail[16]._26 = 0;
    lbl_8036E548.trail[1]._26 = 0;
    lbl_8036E548.trail[2]._26 = 0;
    lbl_8036E548.trail[3]._26 = 0;
    lbl_3_common_bss_32724.trailType = 0;
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT ||
        g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PIRANHA_PANIC ||
        g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_STAR_DASH) {
        return;
    }
    if (g_Minigame.GameMode_MiniGame == 3 && g_Minigame.barrelBatter_scoreCalculatedInd) {
        return;
    }
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_BASERUNNING) {
        return;
    }

    status = g_GameLogic.gameStatus;
    if ((status == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == 3) ||
        (!g_Ball.warioWaluGarlicIsActive && status == GAME_STATUS_LIVE_BALL && g_Ball.currentStarSwing == 3)) {
        lbl_3_common_bss_32724.trailType = 3;
    }
    if ((status == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == 4) ||
        (!g_Ball.warioWaluGarlicIsActive && status == GAME_STATUS_LIVE_BALL && g_Ball.currentStarSwing == 4)) {
        lbl_3_common_bss_32724.trailType = 4;
    }
    if ((status == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == 5) ||
        (status == GAME_STATUS_LIVE_BALL && g_Ball.currentStarSwing == 5)) {
        lbl_3_common_bss_32724.trailType = 5;
    }
    if ((status == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == 6) ||
        (status == GAME_STATUS_LIVE_BALL && g_Ball.currentStarSwing == 6)) {
        lbl_3_common_bss_32724.trailType = 6;
    }
    if ((status == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == 7) ||
        (status == GAME_STATUS_LIVE_BALL && g_Ball.currentStarSwing == 7)) {
        lbl_3_common_bss_32724.trailType = 7;
    }
    if ((status == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == 8) ||
        (status == GAME_STATUS_LIVE_BALL && g_Ball.currentStarSwing == 8)) {
        lbl_3_common_bss_32724.trailType = 8;
    }
    if ((status == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == 9) ||
        (status == GAME_STATUS_LIVE_BALL && g_Ball.currentStarSwing == 9)) {
        lbl_3_common_bss_32724.trailType = 9;
    }
    if ((status == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == 10) ||
        (status == GAME_STATUS_LIVE_BALL && g_Ball.currentStarSwing == 10)) {
        lbl_3_common_bss_32724.trailType = 10;
    }

    trail = &lbl_8036E548.trail[lbl_3_data_6820[lbl_3_common_bss_32724.trailType]];
    if (g_Minigame.GameMode_MiniGame == 1) {
        if (g_Minigame.bOD_KingBombInd) {
            trail = &lbl_8036E548.trail2[1];
        } else {
            trail = &lbl_8036E548.trail2[0];
        }
        lbl_8036E548.trail2[0]._26 = 0;
        lbl_8036E548.trail2[1]._26 = 0;
    }

    fn_3_68BB4();
    trail->_04[0] = g_Ball.AtBat_Contact_BallPos.x;
    trail->_04[1] = -g_Ball.AtBat_Contact_BallPos.y;
    trail->_04[2] = g_Ball.AtBat_Contact_BallPos.z;
    trail->_04[3] = shortAngleToRad_Capped(g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw);
    trail->_04[4] = shortAngleToRad_Capped(g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch);
    trail->_04[5] = shortAngleToRad_Capped(g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll);

    if (g_Ball.warioWaluGarlicIsActive) {
        // Garlic ball: a second ball model.
        s32 swing = g_Ball.currentStarSwing != 3;
        extraIdx = 14;
        if (g_Ball.framesUntilBallHitsGround <= lbl_3_common_bss_35154.garlicFrames[swing]) {
            extraIdx = swing + 15;
        }
        extra = &lbl_8036E548.trail[extraIdx];
        extra->_04[0] = g_Ball.warioStarHitCoords[2].x;
        extra->_04[1] = -g_Ball.warioStarHitCoords[2].y;
        extra->_04[2] = g_Ball.warioStarHitCoords[2].z;
        extra->_26 = 1;
        extra->_04[3] = trail->_04[3];
        extra->_04[4] = trail->_04[4];
        extra->_04[5] = trail->_04[5];
    } else if (g_Pitcher.warioWaluStarAnimationStage == 1 && (g_Pitcher.pitchTotalTimeCounter & 1)) {
        trail->_04[0] = g_Pitcher.ballCurrentPosition.x + g_Pitcher.pitchX_parabolicAdjustment -
                        g_Pitcher.starPitchPositionAdjustment.x;
    }
    if (g_Ball.fielderActionOccuring) {
        trail->_04[0] = g_Ball.fielderActionCatchCoords.x;
        trail->_04[1] = -g_Ball.fielderActionCatchCoords.y;
        trail->_04[2] = g_Ball.fielderActionCatchCoords.z;
    }
    if (g_Ball.hitNoteBlockInd) {
        trail->_04[0] = lbl_3_common_bss_350E4.noteBlockPos.x;
        trail->_04[1] = lbl_3_common_bss_350E4.noteBlockPos.y;
        trail->_04[2] = lbl_3_common_bss_350E4.noteBlockPos.z;
    }

    held = 0;
    if (g_Ball.ballState != 1) {
        held = 1;
    } else if (g_Ball.fielderWBallIndex >= 0 &&
               lbl_800E8558[g_Fielders[g_Ball.fielderWBallIndex].charID]._0[1] == 0x21) {
        held = 2;
        avg.x = (g_Ball.offsetWhilePickedUpHistory[1].x + g_Ball.offsetWhilePickedUpHistory[2].x +
                 g_Ball.offsetWhilePickedUpHistory[3].x) / 3.0f;
        avg.y = (g_Ball.offsetWhilePickedUpHistory[1].y + g_Ball.offsetWhilePickedUpHistory[2].y +
                 g_Ball.offsetWhilePickedUpHistory[3].y) / 3.0f;
        avg.z = (g_Ball.offsetWhilePickedUpHistory[1].z + g_Ball.offsetWhilePickedUpHistory[2].z +
                 g_Ball.offsetWhilePickedUpHistory[3].z) / 3.0f;
        trail->_04[0] = g_Ball.AtBat_Contact_BallPos.x + avg.x;
        trail->_04[1] = g_Ball.AtBat_Contact_BallPos.y + avg.y;
        trail->_04[2] = g_Ball.AtBat_Contact_BallPos.z + avg.z;
        trail->_04[1] = -trail->_04[1];
    }

    if ((g_GameLogic.gameStatus == GAME_STATUS_AT_BAT && g_Ball.pitchHangtimeCounter >= 0) ||
        (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && held != 0)) {
        st = g_Pitcher.pitcherActionState;
        if (!(st == 4 && g_Pitcher.currentStateFrameCounter >= 1 && !g_FieldingLogic._107) &&
            !(st == 4 && !g_FieldingLogic._107 && g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) &&
            !((st == 5 || st == 6) && g_Pitcher.currentStateFrameCounter >= 1 && !g_FieldingLogic._107) &&
            g_Ball.collisionRelated < 2 && !g_Batter.hitByPitch && !g_Pitcher.peachDaisyStarAnimationOn &&
            !g_Batter.invisibleBallForPeachStarHit &&
            !(g_d_GameSettings.StadiumID == 3 && g_Ball.pauseBallMovementWhenInPlant) &&
            !(((u8)(st - 4) <= 1 || st == 6) && g_Minigame.GameMode_MiniGame == 1)) {
            trail->_26 = 1;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            if (g_Minigame.TF_ballDespawnedInd) {
                trail->_26 = 0;
            } else if (g_Minigame.TF_framesSinceHittingPanel > 0 && g_Minigame.TF_framesSinceHittingPanel % 3 == 0) {
                trail->_26 = 0;
            }
        }
        if (g_Minigame.GameMode_MiniGame == 1 && g_Minigame.bODRelated3) {
            trail->_26 = 0;
            fn_3_675B8(0);
        }
    }

    scaleIdx = 0;
    if (g_GameLogic.sceneID == SCENE_ID_LIVE_BALL) {
        scaleIdx = 1;
    }
    if (g_Stats.replayInd) {
        scaleIdx = 2;
    }
    if (g_Minigame.GameMode_MiniGame == 1) {
        fn_8001D0D0(0, lbl_3_data_6838[g_Minigame.bOD_KingBombInd]);
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        scale = lbl_803CB740[scaleIdx];
        fn_8001D148(lbl_3_data_6820[lbl_3_common_bss_32724.trailType], scale, scale, scale);
    } else {
        scale = lbl_800E84B0[lbl_3_common_bss_32724.trailType][scaleIdx];
        fn_8001D148(lbl_3_data_6820[lbl_3_common_bss_32724.trailType], scale, scale, scale);
    }
    if (extra != NULL) {
        switch (extraIdx) {
        case 14:
            row = 0;
            break;
        case 15:
            row = 3;
            break;
        case 16:
            row = 4;
            break;
        }
        scale = lbl_800E84B0[row][scaleIdx];
        fn_8001D148(extraIdx, scale, scale, scale);
        extra->_26 = trail->_26;
    }
    fn_3_695F8(trail->_26);
    fn_3_692E0();
    fn_3_69184();
    fn_3_67A48();
}
#endif
