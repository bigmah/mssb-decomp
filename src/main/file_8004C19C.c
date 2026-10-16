#include "main/file_8004C19C.h"
#include "main/file_80011640.h"
#include "static/GameSettings.h"
#include "static/Camera.h"
#include "static/Pad.h"
#include "main/file_800263FC.h"

extern BatFxTables lbl_800FC0FC;
extern EffectParams* lbl_803CB860;
extern void* lbl_803CBD0C; // TexArchive* of the effect particles (set by fn_8004B1B8)
extern s16 lbl_800FBD80[]; // per-character effect frame

// .data 0x800FC720..0x800FC890: separate objects reached through one pooled base.
EffectParams lbl_800FC720 = {
    NULL,
    4,
    20,
    80000,
    30000,
    {78000, 60, 10, 109000, 101000, 0, 40, 12800000, 0, 0, 0},
    0xFFFFFF00,
    {0, 75000, 0},
};
s32 lbl_800FC770[3] = {500000, 2050000, 200000}; // first frame
s32 lbl_800FC77C[3] = {1100000, 2300000, 500000}; // end frame
s32 lbl_800FC788[3] = {450000, 400000, 400000}; // interval
s32 lbl_800FC794[3] = {1100000, 2400000, 600000}; // flag window
EffectParams lbl_800FC7A0[3] = {
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
};

// Fires the effect at firstFrame, firstFrame + interval, ... while frame < endFrame.
// .text:0x8004C19C size:0x374
void fn_8004C19C(CharActor* model, s32 animID, u32 colorIdx, f32 frame) {
    f32 interval;
    f32 end;
    f32 first;
    f32 t;
    s32 i;
    Vec pos;

    if (CHAR_KIND(model->kind) != 0x12) {
        return;
    }

    if (animID == 0x48) {
        if (frame < lbl_800FC794[2] / 100000.0f) {
            model->mode[0] = 2;
        }
        end = lbl_800FC77C[2] / 100000.0f;
        first = lbl_800FC770[2] / 100000.0f;
        interval = lbl_800FC788[2] / 100000.0f;
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
                    lbl_800FC7A0[2].stamp = lbl_803CBD0C;
                    lbl_800FC7A0[2].rgb = (lbl_800FC0FC.colors[colorIdx].r << 24) |
                                        ((lbl_800FC0FC.colors[colorIdx].g & 0xFF) << 16) |
                                        (lbl_800FC0FC.colors[colorIdx].b << 8);
                    fn_80031CA4(&pos, (ParticleParams5 *)&lbl_800FC7A0[2]);
                }
            }
        }
        return;
    }

    if (frame >= lbl_800FC794[0] / 100000.0f && frame < lbl_800FC794[1] / 100000.0f) {
        model->mode[0] = 2;
    }

    for (i = 0; i < 2; i++) {
        first = lbl_800FC770[i] / 100000.0f;
        interval = lbl_800FC788[i] / 100000.0f;
        end = lbl_800FC77C[i] / 100000.0f;
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
            lbl_800FC7A0[i].stamp = lbl_803CBD0C;
            lbl_800FC7A0[i].rgb = (lbl_800FC0FC.colors[colorIdx].r << 24) | ((lbl_800FC0FC.colors[colorIdx].g & 0xFF) << 16) | (lbl_800FC0FC.colors[colorIdx].b << 8);
            fn_80031CA4(&pos, (ParticleParams5 *)&lbl_800FC7A0[i]);
        }
    }
}

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
        fn_80031CA4(&pos, (ParticleParams5 *)lbl_803CB860);
    }
}
