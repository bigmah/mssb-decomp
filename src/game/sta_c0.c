#include "game/sta_c0.h"
#define REP_HEADER_FN repHeader_sta_c0
#include "header_rep_inline.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#include "static/Camera.h"
#include "game/rep_D0.h"        // g_UNK_StadiumDetails
#include "main/file_80011640.h" // lbl_8036E548 (CharMgr)
#include "main/file_800B4A44.h" // AnimateActorBones
#include "main/file_800BD3EC.h" // fn_800BD548
#include "C3/control.h"
#include "Dolphin/GX/GXBump.h"
#include "Dolphin/GX/GXTexture.h"
#include "Dolphin/OS/OSError.h"
#include <string.h>
#include <math.h>

extern void* _OSAllocFromHeap(s32 align, s32 size);
extern void GXSetZCompLoc(u8);
extern s32 fn_8005268C(void);
extern void* fn_80052734(s32 index);
extern void PSVECSubtract(const Vec*, const Vec*, Vec*);
extern f32 PSVECMag(const Vec*);
extern f32 PSVECDotProduct(const Vec*, const Vec*);
extern void DCFlushRange(void*, u32);
extern s32 fn_800247E4(s32 x, s32 y, s32 width, s32 bytesPerTexel);
extern int rand(void);

// rep_1D58 (stadium objects), typed as in game/rep_2998.c.
extern void fn_3_B939C(void);
extern void fn_3_B9510(s32);
extern u8* fn_3_B9534(s32 width, s32 height, GXTexObj* obj);
extern void fn_3_B97DC(ActorObject* obj, void* animBank);
extern void fn_3_B9D68(void* names, s32 n, void** files, u32* out);
extern s32 fn_3_B7FC8(s32 id, s32 type);
extern void fn_3_35E4(void (*val)(void));
extern void fn_3_16E338(u16* p, s32 i);
// m_sound
extern void fn_3_8B890(s32);
extern void fn_3_8BA60(s32 handle, f32* pos, f32* vel);
extern s32 fn_3_8BBC4(s32 id, f32* pos, f32* vel, s32 kind);

// lbl_3_bss_9F38.._9FDC are separate statics in the original, addressed through one
// pooled base; the ones also used through their own symbol are declared on their own.
extern StaC0Work lbl_3_bss_9F38;
extern u32 lbl_3_bss_9F3C;    // water scroll frame counter
extern u8* lbl_3_bss_9F48;    // water indirect texture (I8, 128 x 64)
extern GXTexObj lbl_3_bss_9F4C;

extern StaC0ObjList lbl_3_common_bss_350E4;
extern StaC0Part lbl_3_data_17B98[11];
extern u8 lbl_3_data_17CF8[]; // TODO type: file name table for fn_3_B9D68
extern u16 lbl_3_data_81DC[]; // per stadium: crowd sound id base
extern u8 lbl_3_data_10F7C[];
extern u8 lbl_3_data_10F84[];
extern u8 lbl_3_data_10F88[];
extern u8 lbl_3_data_11008[];
extern u8 lbl_3_data_11048[32][3];
extern u8 lbl_3_data_11108[16][3];
extern Vec lbl_3_rodata_22D8;
extern char lbl_3_rodata_22EC[]; // "sta_c0.c"
extern char lbl_3_rodata_22F8[]; // "error\n"

// .text:0x000C9744 size:0x134
// Crowd sound.
void fn_3_C9744(void) {
    StaC0Work* s = &lbl_3_bss_9F38;
    GameInitVariables* gs = &g_d_GameSettings;
    if (gs->GameModeSelected != GAME_TYPE_PRACTICE && g_GameLogic.gameStatus != 0x21) {
        if (g_GameLogic.gameStatus == 0xB) {
            if (s->flag == 0) {
                fn_3_8B890(s->h0);
                if (gs->GameModeSelected != GAME_TYPE_MINIGAMES) {
                    fn_3_8B890(s->h1);
                }
                s->flag = 1;
            }
        } else {
            if (s->flag != 0) {
                s->h0 = fn_3_8BBC4(lbl_3_data_81DC[gs->StadiumID] + 1, NULL, NULL, 1);
                if (gs->GameModeSelected != GAME_TYPE_MINIGAMES) {
                    s->h1 = fn_3_B7FC8(lbl_3_data_81DC[gs->StadiumID], 0);
                }
                s->flag = 0;
            } else {
                fn_3_8BA60(s->h0, NULL, NULL);
                if (gs->GameModeSelected != GAME_TYPE_MINIGAMES) {
                    fn_3_8BA60(s->h1, NULL, NULL);
                }
            }
        }
    }
}

// Light panels: switch the panel frames depending on whether the camera faces them.
// .text:0x000C9878 size:0x180 mapped:0x8070890C
void fn_3_C9878(void) {
    StaC0Lights* p = lbl_3_common_bss_350E4.lights;
    Vec diff;
    Vec dir = lbl_3_rodata_22D8;
    s32 idx;
    u8 flag;
    u8* r;
    u8* q;
    s32 i;
    s32 gl;
    f32 lim;
    if (p != NULL) {
        GXSetZCompLoc(0);
        idx = fn_8005268C();
        gl = g_GameLogic.gameStatus;
        if (gl != 0xB) {
            if (gl < 0xB) {
                if (gl == 3) {
                    goto zero;
                }
                goto check;
            }
            if (gl >= 0x18 || gl < 0x13) {
            check:
                if (g_Stats.replayInd == 0) {
                    camera_803c639c_s* t = fn_80052734(idx);
                    PSVECSubtract(&t->target, &t->eye, &diff);
                    diff.y = 0.0f;
                    lim = p->cosLimit * PSVECMag(&diff);
                    flag = PSVECDotProduct(&diff, &dir) > lim;
                } else {
                    goto zero;
                }
            } else {
                goto zero;
            }
        } else {
        zero:
            flag = 0;
        }
        q = p->frames[idx][0];
        r = q + flag;
        for (i = 0; i < p->count; i++) {
            p->panels[q[0]].frame = r[1];
            p->panels[q[3]].frame = r[4];
            q += 6;
            r += 6;
        }
    }
}

// .text:0x000C99F8 size:0x68 mapped:0x80708A8C
void fn_3_C99F8(StaC0Obj* o) {
    if (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 0) {
        o->visible = 0;
    } else {
        o->visible = 1;
        AnimateActorBones(o->actorObj->actor);
    }
}

// .text:0x000C9A60 size:0x68 mapped:0x80708AF4
void fn_3_C9A60(StaC0Obj* o) {
    if (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 0) {
        o->visible = 0;
    } else {
        o->visible = 1;
        AnimateActorBones(o->actorObj->actor);
    }
}

// Water: indirect texture warp.
// .text:0x000C9AC8 size:0x94 mapped:0x80708B5C
void fn_3_C9AC8(StaC0Obj* o) {
    fn_3_B9510(0);
    fn_3_B9510(1);
    GXLoadTexObj(&lbl_3_bss_9F4C, 7);
    GXSetIndTexOrder(0, 0, 7);
    GXSetNumIndStages(1);
    GXSetIndTexCoordScale(0, 0, 0);
    GXSetTevIndWarp(0, 0, 0, 0, 1);
    GXSetTevIndWarp(1, 0, 0, 0, 1);
}

// Water: scroll the indirect texture one texel every 4 frames.
// .text:0x000C9B5C size:0x138 mapped:0x80708BF0
void fn_3_C9B5C(StaC0Obj* o) {
    u32 y;
    u32 x;
    s8 prev;
    if (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 0) {
        o->visible = 0;
        return;
    }
    o->visible = 1;
    if (lbl_3_bss_9F3C < 3) {
        lbl_3_bss_9F3C++;
        return;
    }
    for (y = 0; y < 0x80; y++) {
        for (x = 0; x < 0x40; x++) {
            if (x == 0) {
                prev = (s8)lbl_3_bss_9F48[fn_800247E4(y, 0x3F, 0x80, 2)];
            }
            {
                s32 off = fn_800247E4(y, x, 0x80, 2);
                s32 t = (s8)lbl_3_bss_9F48[off];
                lbl_3_bss_9F48[off] = prev;
                prev = t;
            }
        }
    }
    lbl_3_bss_9F3C = 0;
    DCFlushRange(lbl_3_bss_9F48, 0x4000);
}

// Water: create the random indirect texture.
// .text:0x000C9C94 size:0x120 mapped:0x80708D28
void fn_3_C9C94(void) {
    f32 m[6];
    s32 off;
    u32 y;
    u32 x;
    m[0] = 0.5f;
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 0.0f;
    m[4] = 0.0f;
    m[5] = 0.0f;
    GXSetIndTexMtx(GX_ITM_0, (f32(*)[3])m, 2);
    lbl_3_bss_9F48 = fn_3_B9534(0x80, 0x40, &lbl_3_bss_9F4C);
    if (lbl_3_bss_9F48 == NULL) {
        OSPanic(lbl_3_rodata_22EC, 0x29F, lbl_3_rodata_22F8);
    }
    for (y = 0; y < 0x40; y++) {
        for (x = 0; x < 0x80; x++) {
            off = fn_800247E4(x, y, 0x80, 2);
            lbl_3_bss_9F48[off] = (u8)((s32)rand() % 4) + 0x7E;
        }
    }
}

// Sets up the stadium objects. files: the stadium's file table.
// .text:0x000C9DB4 size:0xE00 mapped:0x80708E48
// NONMATCHING 89%: register allocation and the inlined fn_3_C9C94 reaching lbl_3_bss_9F48/9F4C through
// the pooled lbl_3_bss_9F38 base (expected nmverify difference); same calls, stores and control flow
#if NONMATCHING
void fn_3_C9DB4(void** files) {
    StaC0ObjList* list = &lbl_3_common_bss_350E4;
    u32* idx;
    StaC0Obj* o;
    StaC0Part* e;
    StaC0Seq* seq;
    StaC0Lights* lights;
    u8* extra;
    u32 nParts;
    u32 i;
    s32 k;
    s32 n;
    s32 j;
    s32 size;
    u8 done;
    u8 sh;
    u8 v;

    done = 0;
    list->draw = fn_3_B939C;
    list->update = fn_3_C9744;
    lbl_3_bss_9F38.flag = 1;
    idx = _OSAllocFromHeap(4, 0x24);
    lbl_3_common_bss_350E4.fileIdx = idx;
    fn_3_B9D68(lbl_3_data_17CF8, 9, files, idx);
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES &&
        g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
        fn_3_16E338(files[0], 11);
    }

    // count the placed parts
    for (nParts = 0; nParts < 10; nParts++) {
        if (lbl_3_data_17B98[nParts].kind == 4) {
            break;
        }
    }
    lbl_3_common_bss_350E4.numActorObjs = nParts + 3;
    lbl_8036E548.slots6C = ActorObjectInitTable(nParts + 3);
    fn_800BDC88(lbl_8036E548.slots6C, 0, 0, files[idx[1]], NULL, NULL);
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        fn_800BDC88(lbl_8036E548.slots6C, 1, 1, files[idx[4]], files[idx[4] + 2], NULL);
        fn_3_B97DC(&lbl_8036E548.slots6C->objects[1], files[idx[4] + 2]);
    } else {
        fn_800BDC88(lbl_8036E548.slots6C, 1, 1, files[idx[2]], files[idx[2] + 2], NULL);
        fn_3_B97DC(&lbl_8036E548.slots6C->objects[1], files[idx[2] + 2]);
    }
    for (k = 2, i = 0; i < nParts; i++, k++) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
            fn_800BDC88(lbl_8036E548.slots6C, (u16)k, (u16)k, files[idx[5]], files[idx[5] + 2], NULL);
            fn_3_B97DC(&lbl_8036E548.slots6C->objects[k], files[idx[5] + 2]);
        } else {
            fn_800BDC88(lbl_8036E548.slots6C, (u16)k, (u16)k, files[idx[3]], files[idx[3] + 2], NULL);
            fn_3_B97DC(&lbl_8036E548.slots6C->objects[k], files[idx[3] + 2]);
        }
    }
    fn_800BDC88(lbl_8036E548.slots6C, (u16)k, (u16)k, files[idx[6]], NULL, NULL);
    for (j = 0; j < lbl_3_common_bss_350E4.numActorObjs; j++) {
        fn_800BD548(&lbl_8036E548.slots6C->objects[j], 4, lbl_3_common_bss_350E4.lightObjs[0],
                    lbl_3_common_bss_350E4.lightObjs[1], lbl_3_common_bss_350E4.lightObjs[2],
                    lbl_3_common_bss_350E4.lightObjs[3]);
    }
    if (files[idx[7]] != NULL) {
        fn_80025DDC(files[idx[7]]);
        fn_80025C58(files[idx[7]], (ShapeModel**)&lbl_8036E548.slots6C->objects[0]);
        lbl_3_bss_9F38.anim.set = files[idx[8]];
        fn_80025FFC(files[idx[7]], &lbl_3_bss_9F38.anim);
        fn_80025EEC(&lbl_3_bss_9F38.anim, 0, 0);
    }

    // 20 objects, followed by the panel sequences and light data outside practice
    lbl_3_common_bss_350E4.count = 20;
    size = 20 * sizeof(StaC0Obj) +
           (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE
                ? 2 * sizeof(StaC0Seq) + 32 * 3 + 16 * 3 + sizeof(StaC0Lights)
                : 0);
    lbl_3_common_bss_350E4.objs = _OSAllocFromHeap(0x20, size);
    memset(lbl_3_common_bss_350E4.objs, 0, size);
    lbl_3_common_bss_350E4.objsBackup = _OSAllocFromHeap(0x20, size);
    memset(lbl_3_common_bss_350E4.objsBackup, 0, size);
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
        extra = (u8*)lbl_3_common_bss_350E4.objsBackup + 20 * sizeof(StaC0Obj);
        lbl_3_common_bss_350E4.seqA = (StaC0Seq*)extra;
        lbl_3_common_bss_350E4.seqB = (StaC0Seq*)(extra + sizeof(StaC0Seq));
        ((StaC0Seq*)extra)->steps = extra + 2 * sizeof(StaC0Seq);
        lbl_3_common_bss_350E4.seqB->steps = lbl_3_common_bss_350E4.seqA->steps + 32 * 3;
        lbl_3_common_bss_350E4.lights = (StaC0Lights*)(lbl_3_common_bss_350E4.seqB->steps + 16 * 3);
    } else {
        lbl_3_common_bss_350E4.seqA = NULL;
        lbl_3_common_bss_350E4.seqB = NULL;
        lbl_3_common_bss_350E4.lights = NULL;
    }

    // object 0: the stadium
    o = lbl_3_common_bss_350E4.objs;
    o->kind = 1;
    o->_A2 = 1;
    o->actorObj = &lbl_8036E548.slots6C->objects[1];
    o->shadow = NULL;
    o->update = fn_3_C9A60;
    o->onHit = NULL;
    o->visible = 1;
    sh = 0;
    if (o->visible && o->shadow != NULL) {
        sh = 1;
    }
    o->hasShadow = sh;
    o->ctrl.base.type = 0;
    CTRLSetTranslation(&o->ctrl.base, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation(&o->ctrl.base, 0.0f, 0.0f, 0.0f);
    o->bit5 = 1;
    o->_92 = 0xFF;
    o->shapeAnim = NULL;
    o->preDraw = NULL;
    o->_94 = 0;
    o->_96 = -1;
    o->_98 = 1;

    // object 1: the water
    o[1].kind = 0;
    o[1]._A2 = 0;
    o[1].actorObj = &lbl_8036E548.slots6C->objects[0];
    o[1].shadow = NULL;
    o[1].update = fn_3_C9B5C;
    o[1].onHit = NULL;
    o[1].visible = 1;
    sh = 0;
    if (o[1].visible && o[1].shadow != NULL) {
        sh = 1;
    }
    o[1].hasShadow = sh;
    o[1].ctrl.base.type = 0;
    CTRLSetTranslation(&o[1].ctrl.base, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation(&o[1].ctrl.base, 0.0f, 0.0f, 0.0f);
    o[1].bit5 = 1;
    o[1]._92 = 0xFF;
    o[1].preDraw = fn_3_C9AC8;
    o[1].shapeAnim = &lbl_3_bss_9F38.anim;
    o[1]._94 = 0;
    o[1]._96 = -1;
    o[1]._98 = 1;
    o += 2;

    // the placed parts
    n = 2;
    e = lbl_3_data_17B98;
    for (j = 0; j < 10; j++, e++) {
        if (e->kind == 4) {
            done = 1;
        }
        if (done) {
            // mark the rest of the list unused
            for (; j < 10; j++) {
                lbl_3_data_17B98[j].kind = 4;
            }
            break;
        }
        o->kind = 2;
        o->_A2 = 2;
        o->phase = j * 100;
        o->actorObj = &lbl_8036E548.slots6C->objects[j + 2];
        o->shadow = NULL;
        o->update = fn_3_C99F8;
        o->onHit = NULL;
        o->visible = 1;
        sh = 0;
        if (o->visible && o->shadow != NULL) {
            sh = 1;
        }
        o->hasShadow = sh;
        o->ctrl.base.type = 0;
        CTRLSetScale(&o->ctrl.base, e->scale.x, e->scale.y, e->scale.z);
        CTRLSetTranslation(&o->ctrl.base, e->pos.x, e->pos.y, e->pos.z);
        CTRLSetRotation(&o->ctrl.base, 0.0f, e->rotY, 0.0f);
        o->bit5 = 0;
        o->_92 = 0xFF;
        o->shapeAnim = NULL;
        o->preDraw = NULL;
        o->_94 = 0;
        o->_96 = -1;
        o->_98 = 1;
        n++;
        o++;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        o->kind = 3;
        o->actorObj = &lbl_8036E548.slots6C->objects[k];
        o->shadow = NULL;
        o->update = NULL;
        o->onHit = NULL;
        o->visible = 1;
        sh = 0;
        if (o->visible && o->shadow != NULL) {
            sh = 1;
        }
        o->hasShadow = sh;
        o->ctrl.base.type = 0;
        CTRLSetTranslation(&o->ctrl.base, 0.0f, 0.0f, 0.0f);
        o->bit5 = 0;
        o->_92 = 0xFF;
        o->shapeAnim = NULL;
        o->preDraw = NULL;
        o->_94 = 0;
        o->_96 = -1;
        o->_98 = 1;
        n++;
        o++;
    }

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
        seq = lbl_3_common_bss_350E4.seqA;
        seq->_0C = lbl_3_data_10F7C;
        lbl_3_common_bss_350E4.seqA->_08 = lbl_3_data_10F88;
        lbl_3_common_bss_350E4.seqA->panelA = (StaC0Panel*)g_UNK_StadiumDetails._00 + 3;
        lbl_3_common_bss_350E4.seqA->panelB = (StaC0Panel*)g_UNK_StadiumDetails._00 + 2;
        lbl_3_common_bss_350E4.seqA->count = 32;
        lbl_3_common_bss_350E4.seqA->_18 = 6;
        lbl_3_common_bss_350E4.seqA->range2 = 5;
        for (j = 0; j < 32; j++) {
            lbl_3_common_bss_350E4.seqA->steps[j * 3] = lbl_3_data_11048[j][0];
            v = lbl_3_data_11048[j][1];
            if (v < 6) {
                lbl_3_common_bss_350E4.seqA->steps[j * 3 + 1] = v;
            } else {
                lbl_3_common_bss_350E4.seqA->steps[j * 3 + 1] = rand() % 6;
            }
            v = lbl_3_data_11048[j][2];
            if (v < 5) {
                lbl_3_common_bss_350E4.seqA->steps[j * 3 + 2] = v;
            } else {
                lbl_3_common_bss_350E4.seqA->steps[j * 3 + 2] = rand() % lbl_3_common_bss_350E4.seqA->range2;
            }
        }

        seq = lbl_3_common_bss_350E4.seqB;
        seq->_0C = lbl_3_data_10F84;
        lbl_3_common_bss_350E4.seqB->_08 = lbl_3_data_11008;
        lbl_3_common_bss_350E4.seqB->panelA = (StaC0Panel*)g_UNK_StadiumDetails._00 + 5;
        lbl_3_common_bss_350E4.seqB->panelB = (StaC0Panel*)g_UNK_StadiumDetails._00 + 4;
        lbl_3_common_bss_350E4.seqB->count = 16;
        lbl_3_common_bss_350E4.seqB->_18 = 2;
        lbl_3_common_bss_350E4.seqB->range2 = 8;
        for (j = 0; j < 16; j++) {
            lbl_3_common_bss_350E4.seqB->steps[j * 3] = lbl_3_data_11108[j][0];
            v = lbl_3_data_11108[j][1];
            if (v < 2) {
                lbl_3_common_bss_350E4.seqB->steps[j * 3 + 1] = v;
            } else {
                lbl_3_common_bss_350E4.seqB->steps[j * 3 + 1] = rand() % 6;
            }
            v = lbl_3_data_11108[j][2];
            if (v < 8) {
                lbl_3_common_bss_350E4.seqB->steps[j * 3 + 2] = v;
            } else {
                lbl_3_common_bss_350E4.seqB->steps[j * 3 + 2] = rand() % lbl_3_common_bss_350E4.seqB->range2;
            }
        }

        fn_3_35E4(fn_3_C9878);
        lights = lbl_3_common_bss_350E4.lights;
        lights->panels = g_UNK_StadiumDetails._00;
        lights->count = 2;
        lights->cosLimit = cos(1.3962634801864624); // 80 degrees
        lights->frames[0][0][0] = 8;
        lights->frames[0][0][1] = 2;
        lights->frames[0][0][2] = 7;
        lights->frames[0][0][3] = 4;
        lights->frames[0][0][4] = 7;
        lights->frames[0][0][5] = 4;
        lights->frames[0][1][0] = 9;
        lights->frames[0][1][1] = 2;
        lights->frames[0][1][2] = 7;
        lights->frames[0][1][3] = 10;
        lights->frames[0][1][4] = 7;
        lights->frames[0][1][5] = 4;
        lights->frames[1][0][0] = 8;
        lights->frames[1][0][1] = 2;
        lights->frames[1][0][2] = 7;
        lights->frames[1][0][3] = 4;
        lights->frames[1][0][4] = 7;
        lights->frames[1][0][5] = 4;
        lights->frames[1][1][0] = 9;
        lights->frames[1][1][1] = 2;
        lights->frames[1][1][2] = 7;
        lights->frames[1][1][3] = 10;
        lights->frames[1][1][4] = 7;
        lights->frames[1][1][5] = 4;
        o++;
    }

    // clear the unused objects
    for (j = n; j < lbl_3_common_bss_350E4.count; j++, o++) {
        o->kind = 0;
        o->_A2 = 0;
        o->actorObj = NULL;
        o->shadow = NULL;
        o->update = NULL;
        o->onHit = NULL;
        o->visible = 0;
        o->hasShadow = 0;
        o->bit5 = 0;
        o->ctrl.base.type = 0;
        CTRLSetTranslation(&o->ctrl.base, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(&o->ctrl.base, 0.0f, 0.0f, 0.0f);
        o->_92 = 0;
        o->shapeAnim = NULL;
        o->_94 = 0;
        o->_96 = -1;
    }

    lbl_3_common_bss_350E4._48 = 0;
    fn_3_C9C94();
}
#endif

// .data 0x00017B98..0x00017D08
StaC0Part lbl_3_data_17B98[11] = {
    {{24.4f, 0.0f, 117.2f}, {1.0f, 1.0f, 1.0f}, -16.0f, 2, {1, 0, 0}},
    {{5.549f, 0.0f, 111.0f}, {1.0f, 1.0f, 1.0f}, 0.0f, 2, {1, 0, 0}},
    {{-22.0f, 0.0f, 109.8f}, {0.9f, 0.9f, 0.9f}, 32.0f, 2, {1, 0, 0}},
    {{98.0f, 0.0f, 73.0f}, {1.0f, 1.0f, 1.0f}, 75.0f, 2, {1, 0, 0}},
    {{-112.0f, 0.0f, 66.0f}, {1.0f, 1.0f, 1.0f}, -25.0f, 2, {1, 0, 0}},
    {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f, 4, {0, 0, 0}},
    {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f, 0, {0, 0, 0}},
    {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f, 0, {0, 0, 0}},
    {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f, 0, {0, 0, 0}},
    {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f, 0, {0, 0, 0}},
}; // NOTE: type size 0x140 != symbol size 0x160
u8 lbl_3_data_17CF8[16] = {1, 2, 4, 4, 4, 4, 2, 8, 9, 0, 0, 0, 0, 0, 0, 0};

