#include "main/file_8004C19C.h"
#include "main/file_80011640.h"
#include "static/GameSettings.h"
#include "static/Camera.h"
#include "static/Pad.h"
#include "main/file_800263FC.h"

extern RepeatFxData lbl_800FC720;
extern BatFxTables lbl_800FC0FC;
extern EffectParams* lbl_803CB860;
extern void* lbl_803CBD0C; // TexArchive* of the effect particles (set by fn_8004B1B8)
extern s16 lbl_800FBD80[]; // per-character effect frame

// Fires the effect at firstFrame, firstFrame + interval, ... while frame < endFrame.
// .text:0x8004C19C size:0x374
// NONMATCHING 95%: the original reaches fx's arrays via unfolded `addi base, 0x5C; lwz 8(base)` and
// keeps separate induction pointers per array; register allocation differs
#if NONMATCHING
void fn_8004C19C(CharActor* model, s32 animID, u32 colorIdx, f32 frame) {
    RepeatFxData* fx = &lbl_800FC720;
    u8* r;
    u8* g;
    u8* b;
    s32 i;
    f32 end;
    f32 first;
    f32 interval;
    f32 t;
    Vec pos;
    s32* pFirst;
    s32* pInterval;
    s32* pEnd;
    EffectParams* params;

    if (model->kind != 0x12) {
        return;
    }

    if (animID == 0x48) {
        if (frame < fx->flagWindow[2] / 100000.0f) {
            model->mode[0] = 2;
        }
        end = fx->endFrame[2] / 100000.0f;
        first = fx->firstFrame[2] / 100000.0f;
        interval = fx->interval[2] / 100000.0f;
        if (frame < end) {
            t = frame - first;
            if (t >= 0.0f) {
                while (t >= interval) {
                    t -= interval;
                }
                if (0.0f == t) {
                    pos.x = 0.0f;
                    pos.y = 0.0f;
                    pos.z = 0.0f;
                    fn_8001B728(model->index, 4, &pos);
                    pos.y = 0.0f;
                    fx->params[2].stamp = lbl_803CBD0C;
                    fx->params[2].rgb = (lbl_800FC0FC.colors[colorIdx].r << 24) |
                                        ((lbl_800FC0FC.colors[colorIdx].g & 0xFF) << 16) |
                                        (lbl_800FC0FC.colors[colorIdx].b << 8);
                    fn_80031CA4(&pos, (ParticleParams5 *)(u32*)&fx->params[2]); // TODO type
                }
            }
        }
        return;
    }

    if (frame >= fx->flagWindow[0] / 100000.0f && frame < fx->flagWindow[1] / 100000.0f) {
        model->mode[0] = 2;
    }
    r = &lbl_800FC0FC.colors[colorIdx].r;
    g = &lbl_800FC0FC.colors[colorIdx].g;
    b = &lbl_800FC0FC.colors[colorIdx].b;
    pFirst = fx->firstFrame;
    pInterval = fx->interval;
    pEnd = fx->endFrame;
    params = fx->params;
    for (i = 0; i < 2; i++, pFirst++, pInterval++, pEnd++, params++) {
        end = *pEnd / 100000.0f;
        first = *pFirst / 100000.0f;
        interval = *pInterval / 100000.0f;
        if (frame >= end) {
            continue;
        }
        t = frame - first;
        if (!(t >= 0.0f)) {
            continue;
        }
        while (t >= interval) {
            t -= interval;
        }
        if (0.0f == t) {
            pos.x = 0.0f;
            pos.y = 0.0f;
            pos.z = 0.0f;
            fn_8001B728(model->index, 4, &pos);
            pos.y = 0.0f;
            params->stamp = lbl_803CBD0C;
            params->rgb = (*r << 24) | ((*g & 0xFF) << 16) | (*b << 8);
            fn_80031CA4(&pos, (ParticleParams5 *)(u32*)params); // TODO type
        }
    }
}
#endif

// .text:0x8004C510 size:0xE8
void fn_8004C510(CharActor* model, s32 animID, u32 colorIdx, f32 frame) {
    Vec pos;

    if (0.0f == frame) {
        fn_80062D94(model, animID, colorIdx, frame);
        return;
    }
    if (frame == lbl_800FBD80[model->kind]) {
        pos.x = 0.0f;
        pos.y = 0.0f;
        pos.z = 0.0f;
        fn_8001B728(model->index, 4, &pos);
        pos.y = 0.0f;
        lbl_803CB860->stamp = lbl_803CBD0C;
        lbl_803CB860->rgb = (lbl_800FC0FC.colors[colorIdx].r << 24) |
                            ((lbl_800FC0FC.colors[colorIdx].g & 0xFF) << 16) |
                            (lbl_800FC0FC.colors[colorIdx].b << 8);
        fn_80031CA4(&pos, (ParticleParams5 *)(u32*)lbl_803CB860); // TODO type
    }
}

// ---- Data (initialisers generated from the original DOL) ----

// .data 0x800FC720..0x800FC890
RepeatFxData lbl_800FC720 = {
    {
        NULL,
        4,
        20,
        80000,
        30000,
        {78000, 60, 10, 109000, 101000, 0, 40, 12800000, 0, 0, 0},
        0xFFFFFF00,
        {0, 75000, 0},
    },
    {500000, 2050000, 200000},
    {1100000, 2300000, 500000},
    {450000, 400000, 400000},
    {1100000, 2400000, 600000},
    {
        {
            NULL,
            4,
            20,
            60000,
            20000,
            {88000, 28, 4, 109000, 101000, 0, 128, 10100000, 0, 0, 0},
            0xFFFFFF00,
            {0, 75000, 0},
        },
        {
            NULL,
            4,
            20,
            60000,
            20000,
            {88000, 28, 4, 109000, 101000, 0, 128, 10100000, 0, 0, 0},
            0xFFFFFF00,
            {0, 75000, 0},
        },
        {
            NULL,
            4,
            20,
            60000,
            20000,
            {88000, 28, 4, 109000, 101000, 0, 128, 10100000, 0, 0, 0},
            0xFFFFFF00,
            {0, 75000, 0},
        },
    },
};

