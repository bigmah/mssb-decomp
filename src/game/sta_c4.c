#include "game/sta_c4.h"
#define REP_HEADER_FN repHeader_sta_c4
#include "header_rep_inline.h"
#include "main/file_800263FC.h"
#include "main/file_80011640.h"
#include "C3/anim.h"
#include "main/file_80024D2C.h"
#include "main/file_800BD3EC.h"
#include "game/sta_c0.h"
#include "game/rep_1C0.h"
#include "game/auto_00_000FBCD0_text.h"
#include "game/rep_D0.h"
#include "main/file_8004207C.h"
#include "game/rep_23E8.h"
#include "main/file_800B4A44.h"
#include "main/file_80039AC0.h"
#include "main/file_80037054.h"
#include "main/file_800A7C08.h"
#include "static/Camera.h"
#include "main/file_8004C5F8.h"
#include "C3/geoPalette.h" // DODisplayObj, DisplayStateList
#pragma dont_inline on
extern void fn_800B0A14_removeQueue(void*);

// fn_800B0A14_removeQueue ignores its argument. Some callers pass nothing: r3 is
// whatever the previous call left (e.g. right after fn_80034CEC). The matching
// build calls it through a (void) cast there; the port passes NULL.
#ifndef REMOVE_QUEUE_NOARG
#if NONMATCHING
#define REMOVE_QUEUE_NOARG() fn_800B0A14_removeQueue(NULL)
#else
#define REMOVE_QUEUE_NOARG() ((void (*)(void))fn_800B0A14_removeQueue)()
#endif
#endif

// Same prototype as main/file_800527C4.h. The original callers evaluate the floats first,
// as do sta_c2 and rep_1FD8 (see fn_800528C0_xyz below).
extern void fn_800528C0(s16* sx, s16* sy, f32 x, f32 y, f32 z);
// A few matched callers evaluate the floats before the out pointers. On PPC the
// argument order makes no difference to the call, so the matching build calls
// through a float-first cast there; the port uses the real prototype.
#if NONMATCHING
#define fn_800528C0_xyz(x, y, z, sx, sy) fn_800528C0(sx, sy, x, y, z)
#else
#define fn_800528C0_xyz(x, y, z, sx, sy) ((void (*)(f32, f32, f32, s16*, s16*))fn_800528C0)(x, y, z, sx, sy)
#endif

#include "Dolphin/GX/GXBump.h"
#include "Dolphin/GX/GXTexture.h"
extern void fn_3_B9510(s32);
#include "Dolphin/GX/GXPixel.h"

extern u8 lbl_3_data_81DC[];
extern const f32 lbl_3_rodata_3064;
extern void fn_3_8B890(s32);
extern void fn_3_8BA60(s32 handle, f32* pos, f32* vel);
extern s32 fn_3_8BBC4(s32 id, f32* pos, f32* vel, s32 kind);
extern const f32 lbl_3_rodata_2FB8[3];
extern const f32 lbl_3_rodata_2FC4;
extern const f64 lbl_3_rodata_2FC8;
extern const f32 lbl_3_rodata_2FD0;
extern const f32 lbl_3_rodata_2FD4;
extern const f64 lbl_3_rodata_2FD8;
extern const f64 lbl_3_rodata_2FE0;
extern const f64 lbl_3_rodata_2FE8;
extern const f32 lbl_3_rodata_2FF0;
extern const f64 lbl_3_rodata_2FF8;
extern const f64 lbl_3_rodata_3000;
extern const f32 lbl_3_rodata_3028;
extern const f32 lbl_3_rodata_302C;
extern const char lbl_3_rodata_3030[];
extern const char lbl_3_rodata_303C[];
extern void* fn_3_B9534(u32, u32, void*);
extern s32 fn_800247E4(s32, s32, s32, s32);
extern void OSPanic(const char*, int, const char*, ...);
extern int rand(void);
typedef struct {
    StaObj* objs;
    StaObj* objsBackup;
    StaExtList* ext08;
    StaExtList* ext0C;
    StaExt10* ext10;
    u8 pad14[4];
    void (*draw)(void);   // 0x18
    void (*update)(void); // 0x1C
    void* lights[4];      // 0x20
    s32 n;                // 0x30
    u32* fileIdx;         // 0x34: indices into the stadium file list (fn_3_B9D68)
    u8 pad38[4];
    u32* a3C;
    u16* a40;
    u32* a44;
    Vec* a48; // per draw group: min and max corner
    Vec pos; // 0x4C
    Vec vel; // 0x58
    s16 cnt;
    u8 pad66[5];
    u8 b6B;
    u8 pad6C;
    u8 numActorObjs; // 0x6D
} StaCommon;
extern StaCommon lbl_3_common_bss_350E4;
extern f64 cos(f64);
extern f64 sin(f64);
extern const f32 lbl_3_rodata_2FC4;
extern const f64 lbl_3_rodata_3008;
extern const f32 lbl_3_rodata_3010;
extern const f32 lbl_3_rodata_3014;
extern const f32 lbl_3_rodata_3018;
extern const f64 lbl_3_rodata_3020;
extern u32 sndFXStartEx(int, u8, u8, u8);
extern void sndFXCtrl(int, int, u8);
extern u8 lbl_3_data_8404[];
extern u8 lbl_3_data_84B8[];
// This unit's .bss, declared in reverse address order (CW lays statics out last-declared-first).
static u8 lbl_3_bss_B664[0x14];
static TexArchive* lbl_3_bss_B660;
static GXTexObj lbl_3_bss_B640;
static u8* lbl_3_bss_B63C;
static u8 lbl_3_bss_B630[0xC];
static u16 lbl_3_bss_B62C;
static SpaniGroup* lbl_3_bss_B628[1];
static u8 lbl_3_bss_B620[8];
static Vec lbl_3_bss_B5D8[6];
static u8 lbl_3_bss_B5D4;
static ShapeAnimPlayer lbl_3_bss_B578;
static s32 lbl_3_bss_B574[1];
static u8 lbl_3_bss_B570;
extern void (*lbl_3_data_1BA88[])(s32, s32, CollisionStruct*);
extern void fn_3_F92FC(void);
extern const f32 lbl_3_rodata_3060;
extern const f32 lbl_3_rodata_3078;
extern const f32 lbl_3_rodata_3068;
extern const f32 lbl_3_rodata_306C;
extern const f64 lbl_3_rodata_3070;
extern SpaniDesc lbl_3_data_10E9C[];
// Byte tables defined in rep_1D58.c, stored in StaExtList.pC / .p8.
extern u8 lbl_3_data_10F7C[8];
extern u8 lbl_3_data_10F84[4];
extern u8 lbl_3_data_10F88[0x80]; // 64 (x, y) byte pairs
extern u8 lbl_3_data_11008[0x40]; // 32 (x, y) byte pairs
extern const u8 lbl_3_data_110A8[]; // 32 x 3 initial entries for ext08
extern const u8 lbl_3_data_11138[]; // 16 x 3 initial entries for ext0C
// rep_1D58 (stadium objects); not from rep_1D58.h, where these are still (u8*, u32) / u8* tables (as in rep_2998).
void fn_3_B97C8(void* p);
void fn_3_B97DC(ActorObject* obj, void* animBank);
void fn_3_B9D68(void* names, s32 n, void** files, u32* out);
extern const f32 lbl_3_rodata_307C;
extern const f32 lbl_3_rodata_3080;
extern const f32 lbl_3_rodata_3084;
extern const f32 lbl_3_rodata_3088;
extern const f32 lbl_3_rodata_308C;
extern Vec lbl_3_data_1BF6C[21]; // haze fan: 20 rim points, then the center
extern u8 lbl_3_data_1C068[20][3]; // per strip: tip point, then the two spokes
extern const f32 lbl_3_rodata_3050;
extern const f64 lbl_3_rodata_3058;
extern f64 __fabs(f64);
extern StaObjDef lbl_3_data_1BA98[];
extern void* fn_800B0A5C_insertQueue(void*, s32);
extern void* memcpy(void*, const void*, size_t);
extern void* memset(void*, int, size_t);
extern void DCFlushRange(void*, u32);

// .text:0x000F8444 size:0x10
void fn_3_F8444(void) {
    lbl_3_bss_B5D4 = 1;
}

// .text:0x000F8454 size:0xD0
void fn_3_F8454(void) {
    if (g_GameLogic.gameStatus == 0xB) {
        if (lbl_3_bss_B664[0] == 0) {
            fn_3_8B890(lbl_3_bss_B574[0]);
            lbl_3_bss_B664[0] = 1;
        }
    } else if (lbl_3_bss_B664[0] != 0) {
        lbl_3_bss_B574[0] = fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings.StadiumID] + 3, NULL, NULL, 2);
        lbl_3_bss_B664[0] = 0;
    } else {
        fn_3_8BA60(lbl_3_bss_B574[0], NULL, NULL);
    }
}

// .text:0x000F8524 size:0x8C mapped:0x807375B8
#pragma dont_inline off
void fn_3_F8524(Particle* p) {
    if (p->uvOrder < 0x2A) {
        p->u.phys.vel.y = lbl_3_rodata_2FC4;
        p->pos.x = lbl_3_rodata_2FB8[0];
        p->pos.y = lbl_3_rodata_2FB8[1] - lbl_3_rodata_2FC8;
        p->pos.z = lbl_3_rodata_2FB8[2];
        p->sizeX = lbl_3_rodata_2FD0;
        p->sizeY = lbl_3_rodata_2FD4;
    }
    p->color.v[2] = 0xFF;
    p->color.v[1] = 0xFF;
    p->color.v[0] = 0xFF;
    p->color.v[3] = 0xFF;
    p->life = 0x80;
    p->delay = 0;
}
#pragma dont_inline on

// .text:0x000F85B0 size:0x2C8 mapped:0x80737644
#pragma dont_inline off
s32 fn_3_F85B0(Emitter* e) {
    Particle* p = e->particles;
    if (g_GameLogic.gameStatus >= 0x1B && g_GameLogic.gameStatus <= 0x21) {
        return 0;
    }
    fn_80033620(e);
    GXSetZMode(1, GX_LEQUAL, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    do {
        if (p->delay <= 0 && p->life != 0) {
            fn_8003403C(p->sizeX, p->sizeY);
            fn_80033CC8(p, e->tex);
            if (-p->delay < 0x40) {
                p->color.v[3] = p->color.v[3] + lbl_3_rodata_2FD8;
                p->sizeX = p->sizeX + lbl_3_rodata_2FE0;
            } else {
                p->sizeX = p->sizeX + lbl_3_rodata_2FE8;
                p->color.v[3] = p->color.v[3] + lbl_3_rodata_2FF0;
                if (p->color.v[3] > lbl_3_rodata_2FF8) {
                    p->color.v[3] = 0;
                }
            }
            p->pos.x += p->u.phys.vel.x;
            p->pos.y -= p->u.phys.vel.y;
            p->pos.z += p->u.phys.vel.z;
            p->u.phys.vel.y = p->u.phys.vel.y - lbl_3_rodata_3000;
            p->life--;
        }
        p->delay--;
        if (p->life == 0) {
            fn_3_F8524(p);
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}
#pragma dont_inline on

// .text:0x000F8878 size:0x244 mapped:0x8073790C
// NONMATCHING 99%: only the stfs of 0.123f (n+0x14) is emitted after the fmuls instead of at loop top (orig keeps it at top yet gives it the lowest f-reg f23; moving it to the top flips f-reg order)
#if NONMATCHING
void fn_3_F8878(Emitter* e) {
    s16 delay;
    Particle* p;
    u32 i;
    f32 prev;
    f32 f;
    f32 ang;
    p = e->particles;
    i = 0;
    delay = 0;
    e->tex = lbl_3_bss_B660;
    for (; p != NULL; p = p->next) {
        if ((i & 1) == 0) {
            f = (f32)((i % 6) * 0x3C);
            if (((i / 6) & 1) == 1) {
                f += lbl_3_rodata_3010;
            }
        } else {
            f = lbl_3_rodata_3014 + prev;
        }
        prev = f;
        p->u.phys.vel.y = lbl_3_rodata_2FC4;
        ang = lbl_3_rodata_3018 * f;
        p->u.phys.vel.x = lbl_3_rodata_3020 * (f32)cos(ang);
        p->u.phys.vel.z = lbl_3_rodata_3020 * (f32)sin(ang);
        p->delay = delay;
        delay += 3;
        p->uvOrder = i;
        i++;
        p->pos.x = lbl_3_rodata_2FB8[0];
        p->pos.y = lbl_3_rodata_2FB8[1] - lbl_3_rodata_2FC8;
        p->pos.z = lbl_3_rodata_2FB8[2];
        p->sizeX = lbl_3_rodata_2FD0;
        p->sizeY = lbl_3_rodata_2FD4;
        p->color.v[2] = 0xFF;
        p->color.v[1] = 0xFF;
        p->color.v[0] = 0xFF;
        p->color.v[3] = 0xFF;
        p->life = 0x80;
        p->texIndex = 0x1B;
        p->uvFrame = 0;
    }
}
#endif

// .text:0x000F8ABC size:0x48 mapped:0x80737B50
void fn_3_F8ABC(void) {
    Emitter* e = fn_80033A24(fn_3_F85B0, 0xF0, 0xD, 0x2A, 1, 0x7F);
    if (e != NULL) {
        fn_3_F8878(e);
    }
}

// .text:0x000F8B04 size:0x2C mapped:0x80737B98
void fn_3_F8B04(void) {
    GXSetZMode(1, 3, 0);
}

// .text:0x000F8B30 size:0x4 mapped:0x80737BC4
void fn_3_F8B30(void) {
    return;
}

// .text:0x000F8B34 size:0x74 mapped:0x80737BC8
void fn_3_F8B34(StaObj* o) {
    fn_3_B9510(0);
    GXLoadTexObj(&lbl_3_bss_B640, 7);
    GXSetIndTexOrder(0, 0, 7);
    GXSetNumIndStages(1);
    GXSetIndTexCoordScale(0, 0, 0);
    GXSetTevIndWarp(0, 0, 0, 0, 1);
}

// .text:0x000F8BA8 size:0x158 mapped:0x80737C3C
void fn_3_F8BA8(StaObj* o) {
    // first display state of bone 0 (its setting holds the haze texture frame)
    DisplayStateList* r = o->actorObj->actor->boneArray[0]->dispObj->displayData->displayStateList;
    s8 prev;
    u32 i, j;
    if (o->frame != 0 && o->frame % 3 == 0) {
        o->state++;
        if (o->state > 0x19) {
            o->state = 0xA;
            o->frame = 0;
        }
        r->setting &= ~0x1FFF;
        r->setting |= o->state;
        for (i = 0; i < 0x80; i++) {
            for (j = 0; j < 0x80; j++) {
                if (j == 0) {
                    prev = lbl_3_bss_B63C[fn_800247E4(i, 0x7F, 0x80, 2)];
                }
                {
                    s32 idx = fn_800247E4(i, j, 0x80, 2);
                    s8 t = lbl_3_bss_B63C[idx];
                    lbl_3_bss_B63C[idx] = prev;
                    prev = t;
                }
            }
        }
        DCFlushRange(lbl_3_bss_B63C, 0x8000);
    }
    o->frame++;
}

// .text:0x000F8D00 size:0x120 mapped:0x80737D94
#pragma dont_inline off
void fn_3_F8D00(void) {
    f32 m[2][3];
    u32 i, j;
    m[0][0] = lbl_3_rodata_3028;
    m[0][1] = lbl_3_rodata_302C;
    m[0][2] = lbl_3_rodata_302C;
    m[1][0] = lbl_3_rodata_302C;
    m[1][1] = lbl_3_rodata_3028;
    m[1][2] = lbl_3_rodata_302C;
    GXSetIndTexMtx(GX_ITM_0, m, 2);
    lbl_3_bss_B63C = (u8*)fn_3_B9534(0x80, 0x80, &lbl_3_bss_B640);
    if (lbl_3_bss_B63C == NULL) {
        OSPanic(lbl_3_rodata_3030, 0x6DF, lbl_3_rodata_303C);
    }
    for (i = 0; i < 0x80; i++) {
        for (j = 0; j < 0x80; j++) {
            s32 idx = fn_800247E4(j, i, 0x80, 2);
            lbl_3_bss_B63C[idx] = (u8)(rand() % 4) + 0x7E;
        }
    }
}
#pragma dont_inline on

// .text:0x000F8E20 size:0x268 mapped:0x80737EB4
#pragma dont_inline off
void fn_3_F8E20(void) {
    u8* state = lbl_3_bss_B620;
    Vec* pos = lbl_3_bss_B5D8;
    SpaniGroup* st = (SpaniGroup*)lbl_803CC1B8;
    s32 i;
    for (i = 0; i < 6; i++, state++, pos++) {
        switch (*state) {
            case 1:
                fn_3_F9088(pos, i);
                lbl_80371C30[st->u14.objIdx + i].obj->_5C = 0;
                lbl_80371C30[st->u14.objIdx + i].obj->flags |= 2;
                *state = 2;
                break;
            case 2: {
                LayoutObj* o;
                fn_3_F9088(pos, i);
                o = lbl_80371C30[st->u14.objIdx + i].obj;
                if ((u32)__cntlzw(2 - o->_69) >> 5) {
                    o->flags &= ~2;
                    *state = 0;
                }
                break;
            }
        }
    }
    if (lbl_3_bss_B5D4 != 0) {
        REMOVE_QUEUE_NOARG();
        fn_80034CEC(lbl_3_bss_B628[0]);
        lbl_3_bss_B5D4 = 0;
    }
}

// .text:0x000F9088 size:0xDC mapped:0x8073811C
#pragma dont_inline off
void fn_3_F9088(Vec* pos, s32 idx) {
    s16 x;
    s16 y;
    fn_800528C0_xyz(pos->x, pos->y, pos->z, &x, &y);
    lbl_80371C30[lbl_3_bss_B628[0]->u14.objIdx + idx].obj->x = x;
    lbl_80371C30[lbl_3_bss_B628[0]->u14.objIdx + idx].obj->y = y;
    lbl_80371C30[lbl_3_bss_B628[0]->u14.objIdx + idx].obj->z = 0.0f;
}
#pragma dont_inline on

// .text:0x000F9164 size:0x198 mapped:0x807381F8
void fn_3_F9164(StaObj* o) {
    s32 stad;
    s32 slot;
    s32 snd;
    u32 h;
    u8 v;
    Vec* d;
    switch (o->state) {
        case 0:
            snd = 2;
            slot = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy;
            break;
        case 1:
            snd = 1;
            slot = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy + 2;
            break;
        case 2:
            snd = 0;
            slot = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy + 4;
            break;
    }
    stad = g_d_GameSettings.StadiumID;
    if (g_d_GameSettings.GameModeSelected == 6) {
        v = lbl_3_data_84B8[snd * 2];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + snd * 2];
    }
    h = sndFXStartEx((u16)(snd + ((u16*)lbl_3_data_81DC)[stad]), v, 0x3F, 0);
    if (g_d_GameSettings.GameModeSelected == 6) {
        v = lbl_3_data_84B8[snd * 2 + 1];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + snd * 2 + 1];
    }
    sndFXCtrl(h, 0x5B, v);
    lbl_3_bss_B620[slot] = 1;
    lbl_3_bss_B5D8[slot].x = g_Ball.AtBat_Contact_BallPos.x;
    lbl_3_bss_B5D8[slot].y = -g_Ball.AtBat_Contact_BallPos.y;
    lbl_3_bss_B5D8[slot].z = g_Ball.AtBat_Contact_BallPos.z;
}

// .text:0x000F92FC size:0x50 mapped:0x80738390
void fn_3_F92FC(void) {
    StaTimerTask* st = (StaTimerTask*)lbl_803CC1B8;
    if (st->timer-- == 0) {
        StaObj* o = st->obj;
        o->bit5 = 1;
        fn_800B0A14_removeQueue(o);
    }
}

// .data 0x0001BA88..0x0001C0A8
void (*lbl_3_data_1BA88[4])(s32, s32, CollisionStruct*) = {fn_3_F9E78, (void (*)(s32, s32, CollisionStruct*))fn_3_F99F0, fn_3_F976C, fn_3_F9B9C}; // onHit per object state
StaObjDef lbl_3_data_1BA98[51] = {
    {{-12.0f, -12.0f, 55.0f}, 350.0f, 3, 1, 1, 8},
    {{12.0f, -12.0f, 55.0f}, 10.0f, 3, 1, 1, 8},
    {{-20.0f, -9.0f, 73.0f}, 350.0f, 3, 1, 1, 8},
    {{20.0f, -9.0f, 73.0f}, 10.0f, 3, 1, 1, 8},
    {{-25.0f, -9.0f, 45.0f}, 320.0f, 3, 1, 2, 8},
    {{-51.0f, -9.0f, 65.0f}, 315.0f, 2, 1, 2, 8},
    {{-39.0f, -10.0f, 52.0f}, 315.0f, 2, 1, 3, 8},
    {{-30.0f, -12.0f, 62.0f}, 325.0f, 1, 1, 3, 8},
    {{25.0f, -9.0f, 45.0f}, 40.0f, 3, 1, 4, 8},
    {{51.0f, -9.0f, 65.0f}, 45.0f, 2, 1, 4, 8},
    {{39.0f, -10.0f, 52.0f}, 45.0f, 2, 1, 5, 8},
    {{30.0f, -12.0f, 62.0f}, 35.0f, 1, 1, 5, 8},
    {{-29.0f, -9.0f, 26.0f}, 265.0f, 1, 1, 6, 8},
    {{-39.0f, -10.0f, 36.0f}, 265.0f, 0, 1, 6, 8},
    {{29.0f, -9.0f, 26.0f}, 85.0f, 1, 1, 7, 8},
    {{39.0f, -10.0f, 36.0f}, 85.0f, 0, 1, 7, 8},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 5, 1, 9, 8},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 5, 1, 9, 8},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 5, 1, 9, 8},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 5, 1, 9, 8},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 5, 1, 9, 8},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 5, 1, 9, 8},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 5, 1, 9, 8},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 5, 1, 9, 8},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 5, 1, 9, 8},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 4, 1, 9, 8},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
    {{2.3880104e-38f, 9.551468e-38f, 9.846494e-38f}, 2.558537e-35f, 0, 0, 0, 0},
};
StaHazeNode lbl_3_data_1BE94[2] = {{2, fn_3_FB3D8}, {2, fn_3_FB3D8}};
Vec lbl_3_data_1BF6C[21] = {
    {1.2209f, -0.1f, 67.7082f},
    {-1.2209f, -0.1f, 67.7082f},
    {-3.5431f, -0.1f, 66.9536f},
    {-5.5184f, -0.1f, 65.5184f},
    {-6.9536f, -0.1f, 63.5431f},
    {-7.7082f, -0.1f, 61.2209f},
    {-7.7082f, -0.1f, 58.7791f},
    {-6.9536f, -0.1f, 56.4569f},
    {-5.5184f, -0.1f, 54.4816f},
    {-3.5431f, -0.1f, 53.0464f},
    {-1.2209f, -0.1f, 52.2918f},
    {1.2209f, -0.1f, 52.2918f},
    {3.5431f, -0.1f, 53.0464f},
    {5.5184f, -0.1f, 54.4816f},
    {6.9536f, -0.1f, 56.4569f},
    {7.7082f, -0.1f, 58.7791f},
    {7.7082f, -0.1f, 61.2209f},
    {6.9536f, -0.1f, 63.5431f},
    {5.5184f, -0.1f, 65.5184f},
    {3.5431f, -0.1f, 66.9536f},
    {0.0f, -0.1f, 60.0f},
};
u8 lbl_3_data_1C068[20][3] = {
    {20, 19, 0},
    {20, 1, 2},
    {20, 16, 17},
    {20, 12, 13},
    {20, 5, 6},
    {20, 18, 19},
    {20, 3, 4},
    {20, 14, 15},
    {20, 10, 11},
    {20, 7, 8},
    {20, 17, 18},
    {20, 8, 9},
    {20, 2, 3},
    {20, 11, 12},
    {20, 0, 1},
    {20, 9, 10},
    {20, 15, 16},
    {20, 6, 7},
    {20, 4, 5},
    {20, 13, 14},
}; // NOTE: type size 0x3C != symbol size 0x40

// .text:0x000F934C size:0x2F0 mapped:0x807383E0
// NONMATCHING 98%: lbl_3_bss_B62C is read as addi+lhz 0 and added before task->idx in the original (pooled bss statics, see docs/patterns/regalloc.md); ours reassociates the index sum
#if NONMATCHING
void fn_3_F934C(void) {
    StaBounceTask* task = (StaBounceTask*)lbl_803CC1B8;
    Vec* vel = &lbl_3_common_bss_350E4.vel;
    Vec* pos = &lbl_3_common_bss_350E4.pos;
    Vec tmp;
    Vec nv;
    f32 mag;
    f32 speed;
    s32 k;
    memcpy(&tmp, vel, 0xC);
    PSVECScale(&task->normal, PSVECDotProduct(&task->normal, &tmp), &tmp);
    PSVECAdd(&task->vel, &tmp, &nv);
    mag = PSVECMag(&nv);
    PSVECAdd(pos, vel, &tmp);
    if (task->bounced) {
        speed = PSVECMag(vel) + lbl_3_rodata_3050 * mag;
    } else {
        speed = PSVECMag(vel) - lbl_3_rodata_3050 * mag;
    }
    memcpy(&task->vel, &nv, 0xC);
    memcpy(pos, &tmp, 0xC);
    if (task->bounced &&
        (__fabs(PSVECMag(&nv)) <= lbl_3_rodata_3058 ||
         (!(task->normal.x * nv.x < lbl_3_rodata_302C) && !(task->normal.y * nv.y < lbl_3_rodata_302C) &&
          !(task->normal.z * nv.z < lbl_3_rodata_302C)))) {
        memset(&task->vel, 0, 0xC);
        lbl_3_common_bss_350E4.b6B = 0;
        fn_800B0A14_removeQueue(&lbl_3_common_bss_350E4);
    } else if (speed <= lbl_3_rodata_302C) {
        task->bounced = 1;
        PSVECScale(&task->normal, lbl_3_rodata_3060, &task->normal);
        PSVECScale(&task->normal, lbl_3_rodata_3050 * mag, vel);
    } else {
        PSVECNormalize(vel, &tmp);
        PSVECScale(&tmp, speed, vel);
    }
    CTRLSetTranslation(&lbl_3_common_bss_350E4.objs[task->idx].ctrl.base, task->vel.x + lbl_3_data_1BA98[task->idx].pos.x,
                       task->vel.y + lbl_3_data_1BA98[task->idx].pos.y, task->vel.z + lbl_3_data_1BA98[task->idx].pos.z);
    k = task->idx + (lbl_3_bss_B62C + 9);
    CTRLGetTranslation(&lbl_3_common_bss_350E4.objs[k].ctrl.base, &tmp.x, &tmp.y, &tmp.z);
    CTRLSetTranslation(&lbl_3_common_bss_350E4.objs[k].ctrl.base, task->vel.x + lbl_3_data_1BA98[task->idx].pos.x, tmp.y,
                       task->vel.z + lbl_3_data_1BA98[task->idx].pos.z);
}
#endif

#pragma dont_inline off
static inline void F9164_inl(StaObj* o) {
    s32 stad;
    s32 slot;
    s32 snd;
    u32 h;
    u8 v;
    Vec* d;
    switch (o->state) {
        case 0:
            snd = 2;
            slot = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy;
            break;
        case 1:
            snd = 1;
            slot = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy + 2;
            break;
        case 2:
            snd = 0;
            slot = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy + 4;
            break;
    }
    stad = g_d_GameSettings.StadiumID;
    if (g_d_GameSettings.GameModeSelected == 6) {
        v = lbl_3_data_84B8[snd * 2];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + snd * 2];
    }
    h = sndFXStartEx((u16)(snd + ((u16*)lbl_3_data_81DC)[stad]), v, 0x3F, 0);
    if (g_d_GameSettings.GameModeSelected == 6) {
        v = lbl_3_data_84B8[snd * 2 + 1];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + snd * 2 + 1];
    }
    sndFXCtrl(h, 0x5B, v);
    lbl_3_bss_B620[slot] = 1;
    lbl_3_bss_B5D8[slot].x = g_Ball.AtBat_Contact_BallPos.x;
    lbl_3_bss_B5D8[slot].y = -g_Ball.AtBat_Contact_BallPos.y;
    lbl_3_bss_B5D8[slot].z = g_Ball.AtBat_Contact_BallPos.z;
}
#pragma dont_inline on

// .text:0x000F963C size:0x130 mapped:0x807386D0
#pragma dont_inline off
void fn_3_F963C(s32 idx, CollisionStruct* v) {
    StaBounceTask* p;
    lbl_3_common_bss_350E4.b6B = 1;
    p = fn_800B0A5C_insertQueue(fn_3_F934C, (u16)(((StaBounceTask*)lbl_803CC1B8)->priority + 1));
    memcpy(&lbl_3_common_bss_350E4.pos, &g_Ball.AtBat_Contact_BallPos, 0xC);
    memcpy(&lbl_3_common_bss_350E4.vel, &g_Ball.physicsSubstruct.velocity, 0xC);
    lbl_3_common_bss_350E4.pos.y = -lbl_3_common_bss_350E4.pos.y;
    lbl_3_common_bss_350E4.vel.y = -lbl_3_common_bss_350E4.vel.y;
    if (v != NULL) {
        PSVECScale(&v->normal, lbl_3_rodata_3060, &p->normal);
    }
    memset(&p->vel, 0, 0xC);
    p->idx = idx;
    p->bounced = 0;
    lbl_3_common_bss_350E4.objs[p->idx].hasShadow = 0;
}
#pragma dont_inline on

// .text:0x000F976C size:0x284 mapped:0x80738800
void fn_3_F976C(s32 idx, s32 b, CollisionStruct* c) {
    F9164_inl(&lbl_3_common_bss_350E4.objs[idx]);
    fn_3_F963C(idx, c);
}

// .text:0x000F99F0 size:0x1AC mapped:0x80738A84
#pragma dont_inline off
void fn_3_F99F0(s32 idx) {
    s32 snd;
    s32 slot;
    s32 stad;
    u32 h;
    u8 v;
    Vec* d;
    // objs[idx].state, written as a byte offset for the original addressing
    switch (((u8*)lbl_3_common_bss_350E4.objs)[idx * sizeof(StaObj) + OFFSET_OF(StaObj, state)]) {
        case 0:
            snd = 2;
            slot = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy;
            break;
        case 1:
            snd = 1;
            slot = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy + 2;
            break;
        case 2:
            snd = 0;
            slot = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy + 4;
            break;
    }
    stad = g_d_GameSettings.StadiumID;
    if (g_d_GameSettings.GameModeSelected == 6) {
        v = lbl_3_data_84B8[snd * 2];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + snd * 2];
    }
    h = sndFXStartEx((u16)(snd + ((u16*)lbl_3_data_81DC)[stad]), v, 0x3F, 0);
    if (g_d_GameSettings.GameModeSelected == 6) {
        v = lbl_3_data_84B8[snd * 2 + 1];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + snd * 2 + 1];
    }
    sndFXCtrl(h, 0x5B, v);
    lbl_3_bss_B620[slot] = 1;
    lbl_3_bss_B5D8[slot].x = g_Ball.AtBat_Contact_BallPos.x;
    lbl_3_bss_B5D8[slot].y = -g_Ball.AtBat_Contact_BallPos.y;
    lbl_3_bss_B5D8[slot].z = g_Ball.AtBat_Contact_BallPos.z;
}

#pragma dont_inline on

// .text:0x000F9B9C size:0x1F8 mapped:0x80738C30
// partial: F963C inlined OK; only prologue reg order (lis r6/addi r7 base vs ours r3/r6) differs
void fn_3_F9B9C(s32 idx, s32 b, CollisionStruct* c) {
    StaObj* o = &lbl_3_common_bss_350E4.objs[idx];
    StaTimerTask* q;
    u32 t;
    o->prevState = o->state;
    if (o->prevState == 0) {
        fn_3_F9E78(idx, b, c);
        return;
    }
    if (o->prevState == 2) {
        fn_3_F963C(idx, c);
    }
    o->actorObj = &lbl_8036E548.slots6C->objects[o->state];
    o->onHit = lbl_3_data_1BA88[o->state];
    t = 0;
    if (o->visible && o->shadow != NULL) {
        t = 1;
    }
    o->hasShadow = t;
    o->onHit(idx, b, c);
    o->bit5 = 0;
    q = fn_800B0A5C_insertQueue(fn_3_F92FC, 0);
    q->timer = 0x5A;
    q->obj = o;
}

// .text:0x000F9D94 size:0xE4 mapped:0x80738E28
void fn_3_F9D94(StaObj* o) {
    ActorObject* anim = o->actorObj;
    s32 i;
    if (o->animTime >= ((ANIMBank*)anim->animBank)->animSequences->trackArray[anim->seqNum].animTime) {
        o->visible = 0;
        o->actorObj = NULL;
        o->shadow = NULL;
        o->update = NULL;
        o->onHit = NULL;
        o->hasShadow = 0;
        for (i = 0; i < 9; i++) {
            if (lbl_3_bss_B630[i] == o->id) {
                lbl_3_bss_B630[i] = 0xFF;
                break;
            }
        }
    } else {
        AnimateActorBones(anim->actor);
        o->animTime = o->animTime + lbl_3_rodata_3064;
    }
}

// .text:0x000F9E78 size:0x548 mapped:0x80738F0C
#pragma dont_inline off
void fn_3_F9E78(s32 idx, s32 b, CollisionStruct* c) {
    StaObj* o = &lbl_3_common_bss_350E4.objs[idx];
    StaTimerTask* q;
    u32 t;
    s32 i;
    F9164_inl(o);
    if (o->state == 0) {
        for (i = 0; i < 9; i++) {
            if (lbl_3_bss_B630[i] == 0xFF) {
                StaObj* d = &lbl_3_common_bss_350E4.objs[lbl_3_bss_B62C + i];
                ActorObject* a;
                d->actorObj = &lbl_8036E548.slots6C->objects[i + 5];
                d->shadow = NULL;
                d->update = fn_3_F9D94;
                d->onHit = NULL;
                d->hasShadow = 0;
                d->visible = 1;
                d->actorObj->visFlags = 2;
                a = d->actorObj;
                a->time = lbl_3_rodata_302C;
                a->setTime = 1;
                a = d->actorObj;
                a->unk54 = lbl_3_rodata_3064;
                a->setSpeed = 1;
                d->actorObj->boneRemap = NULL;
                a = d->actorObj;
                ACTSetAnimation(a->actor, a->animBank, NULL, a->seqNum, lbl_3_rodata_302C, a->speed);
                fn_800B4CA0(a->actor, a->time);
                fn_800B4C04(a->actor, a->unk54);
                fn_800B4AFC(a->actor, a->visFlags & 1);
                d->animTime = lbl_3_rodata_302C;
                d->ctrl.base.type = 0;
                CTRLSetTranslation(&d->ctrl.base, lbl_3_data_1BA98[idx].pos.x, lbl_3_data_1BA98[idx].pos.y, lbl_3_data_1BA98[idx].pos.z);
                CTRLSetRotation(&d->ctrl.base, 0.0f, lbl_3_data_1BA98[idx].rotY, 0.0f);
                lbl_3_bss_B630[i] = d->id;
                break;
            }
        }
        o = &lbl_3_common_bss_350E4.objs[idx];
        o->actorObj = NULL;
        o->shadow = NULL;
        o->update = NULL;
        o->onHit = NULL;
        o->visible = 0;
        o->hasShadow = 0;
        if (lbl_800E8754._04 != 0) {
            Vec v;
            CTRLGetTranslation(&o->ctrl.base, &v.x, &v.y, &v.z);
            fn_3_CB7E8(v.x, v.y, v.z);
        }
        lbl_3_common_bss_350E4.objs[lbl_3_bss_B62C + 9 + idx].visible = 0;
        return;
    }
    if (o->state == 2) {
        fn_3_F963C(idx, c);
    }
    o->actorObj = &lbl_8036E548.slots6C->objects[o->state];
    o->onHit = lbl_3_data_1BA88[o->state];
    t = 0;
    if (o->visible && o->shadow != NULL) {
        t = 1;
    }
    o->hasShadow = t;
    o->bit5 = 0;
    q = fn_800B0A5C_insertQueue(fn_3_F92FC, 0);
    q->timer = 0x5A;
    q->obj = o;
}
#pragma dont_inline on

// .text:0x000FA3C0 size:0x1CC mapped:0x80739454
// NONMATCHING 97%: idx assigned directly (no j temp). Remaining: saved-reg ranking (orig: offC<cnt<j<i<off18<off2<off4; ours: i<cnt<j<off18<offC) and the orig IV zero-inits are `mr` copies of i (ours li). Explicit offset vars + decl order fix regs but give li inits.
extern void* _OSAllocFromHeap(s32, s32);
extern void* memset(void*, int, size_t);
extern void fn_3_B8414(void*, void*);
extern void fn_3_B8464(void*, void*);
extern void fn_3_B8574(void);
#if NONMATCHING
void fn_3_FA3C0(void) {
    Mtx m;
    s32 j;
    s32 cnt;
    s32 i;
    s32 size;
    s32 idx;
    StaObj* o;
    size = (lbl_3_common_bss_350E4.n << 2) + (lbl_3_common_bss_350E4.n << 1) + (lbl_3_common_bss_350E4.n << 2) + lbl_3_common_bss_350E4.n * 0x18;
    if (lbl_3_common_bss_350E4.a48 == NULL) {
        lbl_3_common_bss_350E4.a48 = _OSAllocFromHeap(4, size);
        lbl_3_common_bss_350E4.a3C = (u32*)(lbl_3_common_bss_350E4.a48 + lbl_3_common_bss_350E4.n * 2);
        lbl_3_common_bss_350E4.a44 = lbl_3_common_bss_350E4.a3C + lbl_3_common_bss_350E4.n;
        lbl_3_common_bss_350E4.a40 = (u16*)(lbl_3_common_bss_350E4.a44 + lbl_3_common_bss_350E4.n);
    }
    memset(lbl_3_common_bss_350E4.a48, 0, size);
    cnt = 0;
    for (i = 0; i < 10; i++) {
        idx = (u16)(lbl_3_common_bss_350E4.a40[cnt - 1] + lbl_3_common_bss_350E4.a3C[cnt - 1]);
        lbl_3_common_bss_350E4.a40[cnt] = idx;
        fn_3_B8574();
        for (j = 0; j < lbl_3_common_bss_350E4.n; j++) {
            if (i == lbl_3_data_1BA98[j].group && lbl_3_common_bss_350E4.objs[j].hasShadow) {
                lbl_3_common_bss_350E4.a44[idx] = j;
                idx++;
                lbl_3_common_bss_350E4.a3C[cnt]++;
                o = &lbl_3_common_bss_350E4.objs[j];
                CTRLBuildMatrix(&o->ctrl.base, m);
                fn_3_B8464(m, o->shadow);
            }
        }
        if (lbl_3_common_bss_350E4.a3C[cnt] != 0) {
            fn_3_B8414(&lbl_3_common_bss_350E4.a48[cnt * 2], &lbl_3_common_bss_350E4.a48[cnt * 2 + 1]);
            cnt++;
        }
    }
    lbl_3_common_bss_350E4.cnt = cnt;
}
#endif

// .text:0x000FA58C size:0xE4C mapped:0x80739620
static inline void sta_initObjTail(StaObj* p) {
    p->_92 = 0xFF;
    p->preDraw = NULL;
    p->anim = NULL;
    p->_94 = 0;
    p->_96 = -1;
    p->_98 = 1;
}

static inline u8 sta_hasShadow(StaObj* p) {
    u8 t = 0;
    if (p->visible && p->shadow != NULL) {
        t = 1;
    }
    return t;
}

// NONMATCHING 87%: same structure and calls; the original reaches lbl_3_data_1BA88/1BA98 and this unit's .bss through
// pooled base registers and keeps 0.0f in memory (ours hoists it into f31), so most remaining lines are register numbering
#if NONMATCHING
void fn_3_FA58C(void** files) {
    void (*draw)(void);
    u32* idx;
    ActorObjectTable* tbl;
    StaObj* p;
    StaObj* q;
    StaObj* o;
    StaObjDef* def;
    StaExtList* ext;
    const u8* src;
    u8* slot;
    s32 last;
    s32 dup;
    s32 i;
    s32 k;
    s32 n;
    s32 size;

    last = 0;
    draw = fn_3_FBCD0;
    if (g_d_GameSettings.GameModeSelected == 7) {
        draw = NULL;
    }
    lbl_3_common_bss_350E4.draw = draw;
    lbl_3_common_bss_350E4.update = fn_3_F8454;
    lbl_3_bss_B664[0] = 1;
    idx = _OSAllocFromHeap(4, 0x44);
    lbl_3_common_bss_350E4.fileIdx = idx;
    fn_3_B9D68(&lbl_3_data_1BA98[50], 0x11, files, idx); // the file kinds follow the 50 object spots
    lbl_3_bss_B660 = files[0];
    fn_80035750(files[idx[16]], files[idx[15]], 5);
    lbl_3_bss_B628[0] = fn_800B0A5C_insertQueue(fn_3_F8E20, 2);
    fn_80034E20(lbl_3_bss_B628[0], lbl_3_data_10E9C);

    tbl = ActorObjectInitTable(0x10);
    lbl_8036E548.slots6C = tbl;
    fn_800BDC88(tbl, 0, 0, files[idx[1]], NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 1, 1, files[idx[3]], NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 2, 2, files[idx[4]], NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 3, 3, files[idx[5]], NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 4, 4, files[idx[6]], NULL, NULL);
    for (k = 0; k < 9; k++) {
        fn_800BDC88(lbl_8036E548.slots6C, k + 5, k + 5, files[idx[2]], files[idx[2] + 2], NULL);
        fn_3_B97DC(&lbl_8036E548.slots6C->objects[k + 5], files[idx[2] + 2]);
        lbl_8036E548.slots6C->objects[k + 5].setAnimation = 0;
    }
    fn_800BDC88(lbl_8036E548.slots6C, 14, 14, files[idx[7]], NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 15, 15, files[idx[8]], NULL, NULL);
    lbl_3_common_bss_350E4.numActorObjs = 0x10;
    for (k = 0; k < 16; k++) {
        fn_800BD548(&lbl_8036E548.slots6C->objects[k], 4, lbl_3_common_bss_350E4.lights[0], lbl_3_common_bss_350E4.lights[1],
                    lbl_3_common_bss_350E4.lights[2], lbl_3_common_bss_350E4.lights[3]);
    }
    if (files[idx[13]] != NULL) {
        fn_80025DDC(files[idx[13]]);
        // ShapeModel is fn_80025C58's view of the GameActor in the actor slot.
        fn_80025C58(files[idx[13]], (ShapeModel**)&lbl_8036E548.slots6C->objects[15].actor);
        lbl_3_bss_B578.set = files[idx[14]];
        fn_80025FFC(files[idx[13]], &lbl_3_bss_B578);
        fn_80025EEC(&lbl_3_bss_B578, 0, 0);
    }

    lbl_3_common_bss_350E4.n = 0x34;
    size = (g_d_GameSettings.miniGameStadiumIndicator == 0 ? 2 * sizeof(StaExtList) + 32 * 3 + 16 * 3 + sizeof(StaExt10) : 0) + 0x34 * sizeof(StaObj);
    lbl_3_common_bss_350E4.objs = _OSAllocFromHeap(0x20, size);
    memset(lbl_3_common_bss_350E4.objs, 0, size);
    lbl_3_common_bss_350E4.objsBackup = _OSAllocFromHeap(0x20, size);
    memset(lbl_3_common_bss_350E4.objsBackup, 0, size);
    if (g_d_GameSettings.miniGameStadiumIndicator == 0) {
        // the extra bytes behind the backup objects: two lists, their entries and ext10
        u8* extra = (u8*)&lbl_3_common_bss_350E4.objsBackup[0x34];
        lbl_3_common_bss_350E4.ext08 = (StaExtList*)extra;
        lbl_3_common_bss_350E4.ext0C = (StaExtList*)(extra + sizeof(StaExtList));
        lbl_3_common_bss_350E4.ext08->entries = (u8*)lbl_3_common_bss_350E4.ext0C + sizeof(StaExtList);
        lbl_3_common_bss_350E4.ext0C->entries = lbl_3_common_bss_350E4.ext08->entries + 32 * 3;
        lbl_3_common_bss_350E4.ext10 = (StaExt10*)(lbl_3_common_bss_350E4.ext0C->entries + 16 * 3);
    } else {
        lbl_3_common_bss_350E4.ext08 = NULL;
        lbl_3_common_bss_350E4.ext0C = NULL;
        lbl_3_common_bss_350E4.ext10 = NULL;
    }

    p = lbl_3_common_bss_350E4.objs;
    q = p;
    if (g_d_GameSettings.GameModeSelected != 7) {
        slot = lbl_3_bss_B630;
        dup = 0;
        lbl_3_bss_B62C = 0xFFFF;
        for (i = 0; i < 0x34; i++, p++, q = p) {
            def = &lbl_3_data_1BA98[i];
            q->id = i;
            if (def->kind == 5) {
                // free slot for a knocked-off object (fn_3_F9E78)
                q->prevState = 5;
                if (lbl_3_bss_B62C == 0xFFFF) {
                    lbl_3_bss_B62C = i;
                }
                *slot++ = 0xFF;
                p->actorObj = &lbl_8036E548.slots6C->objects[i + 5];
                p->shadow = NULL;
                p->update = NULL;
                p->onHit = NULL;
                p->visible = 0;
                p->hasShadow = 0;
                p->bit5 = 0;
                p->ctrl.base.type = 0;
            } else if (dup != 0) {
                q->prevState = 0;
                q->state = 0;
                p->actorObj = &lbl_8036E548.slots6C->objects[0];
                p->shadow = files[idx[9]];
                p->update = NULL;
                p->onHit = NULL;
                p->visible = 0;
                p->hasShadow = 0;
                p->bit5 = 1;
                p->ctrl.base.type = 0;
                CTRLSetTranslation(&p->ctrl.base, lbl_3_rodata_302C, lbl_3_rodata_302C, lbl_3_rodata_302C);
                CTRLSetRotation(&p->ctrl.base, lbl_3_rodata_302C, lbl_3_rodata_302C, lbl_3_rodata_302C);
            } else if ((dup = (def->kind == 4)) != 0) {
                // copies of the first B62C spots, sunk into the ground
                StaObjDef* d = lbl_3_data_1BA98;
                for (k = 0; k < lbl_3_bss_B62C; k++, d++, i++, p++, q = p) {
                    q->prevState = 0;
                    q->state = 0;
                    p->actorObj = &lbl_8036E548.slots6C->objects[4];
                    p->shadow = NULL;
                    p->update = NULL;
                    p->onHit = NULL;
                    p->visible = d->visible;
                    p->hasShadow = 0;
                    p->ctrl.base.type = 0;
                    CTRLSetTranslation(&p->ctrl.base, d->pos.x, lbl_3_rodata_3068, d->pos.z);
                    CTRLSetRotation(&p->ctrl.base, lbl_3_rodata_302C, d->rotY, lbl_3_rodata_302C);
                    p->bit5 = 0;
                    sta_initObjTail(p);
                }
                last = i;
                i--;
                p--;
            } else {
                q->prevState = def->kind;
                q->state = def->state;
                if (q->prevState == 3) {
                    if (q->state == 8) {
                        q->state = rand() % 3;
                    }
                } else if (q->prevState == 0 && q->state == 8) {
                    q->state = rand() % 3;
                } else {
                    q->state = q->prevState;
                }
                p->actorObj = &lbl_8036E548.slots6C->objects[q->prevState];
                p->shadow = files[idx[9 + q->state]];
                p->update = NULL;
                p->onHit = lbl_3_data_1BA88[q->prevState];
                p->visible = def->visible;
                p->hasShadow = sta_hasShadow(p);
                p->ctrl.base.type = 0;
                CTRLSetTranslation(&p->ctrl.base, def->pos.x, def->pos.y, def->pos.z);
                CTRLSetRotation(&p->ctrl.base, lbl_3_rodata_302C, def->rotY, lbl_3_rodata_302C);
                p->bit5 = 1;
            }
            sta_initObjTail(p);
        }
    }

    // the haze object (fn_3_FB3D8) and its particles
    o = &lbl_3_common_bss_350E4.objs[last];
    o->id = 0x33;
    o->prevState = 6;
    o->state = 10;
    {
        Emitter* e = fn_80033A24(fn_3_F85B0, 0xF0, 0xD, 0x2A, 1, 0x7F); // fn_3_F8ABC
        if (e != NULL) {
            fn_3_F8878(e);
        }
    }
    o->actorObj = &lbl_8036E548.slots6C->objects[14];
    o->shadow = NULL;
    o->update = fn_3_F8BA8;
    o->onHit = NULL;
    o->visible = 1;
    o->hasShadow = sta_hasShadow(o);
    o->ctrl.base.type = 0;
    CTRLSetTranslation(&o->ctrl.base, lbl_3_rodata_302C, lbl_3_rodata_302C, lbl_3_rodata_302C);
    CTRLSetRotation(&o->ctrl.base, lbl_3_rodata_302C, lbl_3_rodata_302C, lbl_3_rodata_302C);
    o->bit5 = 1;
    sta_initObjTail(o);
    o->preDraw = fn_3_F8B34;
    fn_3_F8D00();

    // the shape-animated object
    o++;
    o->id = 0x33;
    o->prevState = 7;
    o->actorObj = &lbl_8036E548.slots6C->objects[15];
    o->shadow = NULL;
    o->update = NULL;
    o->onHit = NULL;
    o->visible = 1;
    o->hasShadow = sta_hasShadow(o);
    o->ctrl.base.type = 0;
    CTRLSetTranslation(&o->ctrl.base, lbl_3_rodata_302C, lbl_3_rodata_306C, lbl_3_rodata_302C);
    CTRLSetRotation(&o->ctrl.base, lbl_3_rodata_302C, lbl_3_rodata_302C, lbl_3_rodata_302C);
    o->bit5 = 1;
    sta_initObjTail(o);
    o->anim = &lbl_3_bss_B578;

    if (g_d_GameSettings.miniGameStadiumIndicator == 0) {
        ext = lbl_3_common_bss_350E4.ext08;
        ext->pC = lbl_3_data_10F7C;
        ext->p8 = lbl_3_data_10F88;
        ext->p0 = (StaC0Panel*)g_UNK_StadiumDetails._00 + 3;
        ext->p4 = (StaC0Panel*)g_UNK_StadiumDetails._00 + 2;
        ext->count = 0x20;
        ext->n18 = 6;
        ext->nChoices = 5;
        src = lbl_3_data_110A8;
        for (k = 0, n = 0; k < 0x20; k++, n += 3, src += 3) {
            ext->entries[n] = src[0];
            if (src[1] < 6) {
                ext->entries[n + 1] = src[1];
            } else {
                ext->entries[n + 1] = rand() % 6;
            }
            if (src[2] < 5) {
                ext->entries[n + 2] = src[2];
            } else {
                ext->entries[n + 2] = rand() % ext->nChoices;
            }
        }

        ext = lbl_3_common_bss_350E4.ext0C;
        ext->pC = lbl_3_data_10F84;
        ext->p8 = lbl_3_data_11008;
        ext->p0 = (StaC0Panel*)g_UNK_StadiumDetails._00 + 5;
        ext->p4 = (StaC0Panel*)g_UNK_StadiumDetails._00 + 4;
        ext->count = 0x10;
        ext->n18 = 2;
        ext->nChoices = 8;
        src = lbl_3_data_11138;
        for (k = 0, n = 0; k < 0x10; k++, n += 3, src += 3) {
            ext->entries[n] = src[0];
            if (src[1] >= 2) {
                ext->entries[n + 1] = src[1];
            } else {
                ext->entries[n + 1] = rand() % 6;
            }
            if (src[2] >= 8) {
                ext->entries[n + 2] = src[2];
            } else {
                ext->entries[n + 2] = rand() % ext->nChoices;
            }
        }

        fn_3_35E4(fn_3_C9878);
        {
            StaExt10* e = lbl_3_common_bss_350E4.ext10;
            e->file = g_UNK_StadiumDetails._00;
            e->n20 = 2;
            e->cosAngle = cos(lbl_3_rodata_3070);
            e->b[0] = 8;
            e->b[1] = 2;
            e->b[2] = 7;
            e->b[3] = 4;
            e->b[4] = 7;
            e->b[5] = 4;
            e->b[6] = 9;
            e->b[7] = 2;
            e->b[8] = 7;
            e->b[9] = 10;
            e->b[10] = 7;
            e->b[11] = 4;
            e->b[12] = 8;
            e->b[13] = 2;
            e->b[14] = 7;
            e->b[15] = 4;
            e->b[16] = 7;
            e->b[17] = 4;
            e->b[18] = 9;
            e->b[19] = 2;
            e->b[20] = 7;
            e->b[21] = 10;
            e->b[22] = 7;
            e->b[23] = 4;
        }
    }
    lbl_3_common_bss_350E4.a48 = NULL;
    if (g_d_GameSettings.GameModeSelected != 7) {
        fn_3_FA3C0();
    }
    fn_3_B97C8(fn_3_F8444);
}
#endif

// .text:0x000FB3D8 size:0x7C8 mapped:0x8073A46C
// NONMATCHING 96%: register allocation only (min/max floats f0-f3 vs ours f1-f4, saved gprs rotated)
#pragma dont_inline off
#if NONMATCHING
void fn_3_FB3D8(StaHazeNode* node) {
    f32 base2d[21][2];
    Vec d;
    Vec step;
    f32* scr;
    Vec* pts;
    Vec* out;
    Vec* src;
    Vec* o;
    const u8* tri;
    s32 i;
    s32 k;
    s32 b;
    s32 c;
    f32 minX;
    f32 maxX;
    f32 minY;
    f32 maxY;
    f32 rx;
    f32 ry;

    fn_8003A144();
    scr = _OSAllocFromHeap(4, 0x20D0);
    pts = (Vec*)(scr + 420 * 2); // 420 screen positions (f32[2]), then 420 Vecs
    src = lbl_3_data_1BF6C;
    out = pts;
    for (i = 0; i < 21; i++, src++) {
        if (i != 20) {
            PSVECSubtract(src, &lbl_3_data_1BF6C[20], &d);
            o = out;
            for (k = 1; k <= 20; k++) {
                PSVECScale(&d, (f32)k / lbl_3_rodata_3078, &step);
                PSVECAdd(&lbl_3_data_1BF6C[20], &step, o);
                out++;
                o++;
            }
        }
    }
    fn_800245EC(fn_80052768_getCamera(0)->proj, node->view, lbl_3_data_1BF6C, &base2d[0][0], 21, 1);
    fn_800245EC(fn_80052768_getCamera(0)->proj, node->view, pts, scr, 400, 1);

    minX = lbl_3_rodata_307C;
    maxX = -minX;
    minY = minX;
    maxY = maxX;
    for (i = 0; i < 400; i++) {
        if (minX > scr[i * 2]) {
            minX = scr[i * 2];
        }
        if (maxX < scr[i * 2]) {
            maxX = scr[i * 2];
        }
        if (minY > scr[i * 2 + 1]) {
            minY = scr[i * 2 + 1];
        }
        if (maxY < scr[i * 2 + 1]) {
            maxY = scr[i * 2 + 1];
        }
    }
    rx = lbl_3_rodata_3080 * (maxX - minX);
    ry = lbl_3_rodata_3080 * (maxY - minY);
    for (i = 0; i < 800; i += 2) {
        scr[i] += rx * (f32)(rand() % 256) * lbl_3_rodata_3084 - lbl_3_rodata_3088;
        scr[i + 1] += ry * (f32)(rand() % 256) * lbl_3_rodata_3084 - lbl_3_rodata_3088;
    }

    fn_3_FBBA0(fn_80039AB4());
    GXSetZMode(1, GX_LEQUAL, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, 0, GX_PTIDENTITY);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, 0, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, 0, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    GXLoadPosMtxImm(node->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    for (i = 0, tri = lbl_3_data_1C068[0]; i < 20; i++, tri += 3) {
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 43);
        GXWGFifo.f32 = lbl_3_data_1BF6C[tri[0]].x;
        GXWGFifo.f32 = lbl_3_rodata_308C + lbl_3_data_1BF6C[tri[0]].y;
        GXWGFifo.f32 = lbl_3_data_1BF6C[tri[0]].z;
        GXWGFifo.u32 = 0xFFFFFFFF;
        GXWGFifo.f32 = base2d[tri[0]][0];
        GXWGFifo.f32 = base2d[tri[0]][1];
        b = tri[1];
        c = tri[2];
        for (k = 0; k < 20; k++) {
            GXPosition3f32(pts[b * 20 + k].x, lbl_3_rodata_308C + pts[b * 20 + k].y, pts[b * 20 + k].z);
            GXColor1u32(0xFFFFFFFF);
            GXTexCoord2f32(scr[(b * 20 + k) * 2], scr[(b * 20 + k) * 2 + 1]);
            GXPosition3f32(pts[c * 20 + k].x, lbl_3_rodata_308C + pts[c * 20 + k].y, pts[c * 20 + k].z);
            GXColor1u32(0xFFFFFFFF);
            GXTexCoord2f32(scr[(c * 20 + k) * 2], scr[(c * 20 + k) * 2 + 1]);
        }
        GXWGFifo.f32 = lbl_3_data_1BF6C[b].x;
        GXWGFifo.f32 = lbl_3_rodata_308C + lbl_3_data_1BF6C[b].y;
        GXWGFifo.f32 = lbl_3_data_1BF6C[b].z;
        GXWGFifo.u32 = 0xFFFFFFFF;
        GXWGFifo.f32 = base2d[b][0];
        GXWGFifo.f32 = base2d[b][1];
        GXWGFifo.f32 = lbl_3_data_1BF6C[c].x;
        GXWGFifo.f32 = lbl_3_rodata_308C + lbl_3_data_1BF6C[c].y;
        GXWGFifo.f32 = lbl_3_data_1BF6C[c].z;
        GXWGFifo.u32 = 0xFFFFFFFF;
        GXWGFifo.f32 = base2d[c][0];
        GXWGFifo.f32 = base2d[c][1];
    }
    fn_800ACFB0(scr);
}
#endif
#pragma dont_inline on

// .text:0x000FBBA0 size:0x130 mapped:0x8073AC34
#pragma dont_inline off
void fn_3_FBBA0(TexImage* t) {
    GXTexObj tex;
    GXTlutObj tlut;
    if (t->tlut != NULL) {
        GXInitTexObjCI(&tex, t->data, t->width, t->height, (GXCITexFmt)t->format, (GXTexWrapMode)t->wrapS, (GXTexWrapMode)t->wrapT,
                       t->minLOD != t->maxLOD, 0);
        GXInitTlutObj(&tlut, t->tlut, (GXTlutFmt)t->tlutFormat, t->tlutEntries);
        GXLoadTlut(&tlut, 0);
    } else {
        GXInitTexObj(&tex, t->data, t->width, t->height, (GXTexFmt)t->format, (GXTexWrapMode)t->wrapS, (GXTexWrapMode)t->wrapT,
                     t->minLOD != t->maxLOD);
    }
    GXInitTexObjLOD(&tex, (GXTexFilter)t->minFilter, (GXTexFilter)t->magFilter, (f32)t->minLOD, (f32)t->maxLOD, t->lodBias, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&tex, GX_TEXMAP0);
}


#pragma dont_inline off

