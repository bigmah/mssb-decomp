#include "game/rep_3AE8.h"
#define REP_HEADER_FN repHeader_3AE8
#include "header_rep_inline.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/stl.h"
#include "main/file_800263FC.h"
#include "Dolphin/rand.h"

// Pitch / hit ball trail effects (lbl_3_data_26F78).
typedef struct BallTrailFx {
    /*0x000*/ ParticleParams9 pitch[2]; // unk38: z where the pitch trail ends (x100000)
    /*0x090*/ ParticleParams9 hit[2];   // unk38/unk3C: min/max trail length, percent of the hang time (x100000)
    /*0x120*/ s32 minHitHeight;         // x100000
} BallTrailFx;
extern BallTrailFx lbl_3_data_26F78;
// Hit / pitch line effects (lbl_3_data_2709C).
typedef struct BallLineFx {
    /*0x000*/ ParticleParamsA hit;
    /*0x084*/ ParticleParamsA pitch;
} BallLineFx;
extern BallLineFx lbl_3_data_2709C;
// Stadium effect state (lbl_3_common_bss_35154); only the fields used here.
extern struct {
    /*0x000*/ u8 _000[0x4];
    /*0x004*/ TexArchive* tex;
    /*0x008*/ u8 _008[0x464 - 0x8];
    /*0x464*/ s16 _464;
} lbl_3_common_bss_35154;

typedef struct {
    s16 _0;
    s16 _2;
    s16 _4;
    u8 pad[8];
} T5D6C;
extern T5D6C lbl_3_data_5D6C[];


void fn_3_15C024(VecXYZ* pos, VecXYZ* vel, VecXYZ* add, int flag);

// .text:0x0015B79C size:0x304 mapped:0x8079A830
void fn_3_15B79C(int flag) {
    VecXYZ pos;
    VecXYZ vel;
    VecXYZ add;
    f32 limit = (f32)lbl_3_data_26F78.pitch[flag].unk38 / 100000.0f;
    memcpy(&pos, &g_Pitcher, sizeof(VecXYZ));
    memcpy(&vel, &g_Pitcher.ballVelocity, sizeof(VecXYZ));
    memcpy(&add, &g_Pitcher.pitchCurveVeloV1, sizeof(VecXYZ));
    while (pos.z > limit) {
        fn_3_15C024(&pos, &vel, &add, 1);
    }
    pos.y = -pos.y;
    if (flag) {
        fn_8002CDD0(&pos);
    } else {
        fn_8002DC68(&pos);
    }
}

// Spawns the ball trail: flag 0 the ground trail, 1 the line trail.
// NONMATCHING 73%: the original reaches lbl_3_data_2709C through the lbl_3_data_26F78 base (+0x124/+0x1A8,
// same-TU data pooling), so every address computation and the register allocation differ
// nmverify: lbl_3_data_2709C is reached via the pooled lbl_3_data_26F78 base in the original
// .text:0x0015BAA0 size:0x560 mapped:0x8079AB34
#if NONMATCHING
void fn_3_15BAA0(s32 flag) {
    VecXYZ pos;
    VecXYZ end;
    VecXYZ add;
    s32 state;
    s32 i;
    f32 limit;
    f32 minLen;
    f32 lenRange;
    ParticleParams9* trail;

    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        state = 2;
    } else {
        state = g_Ball.framesSinceHit > 0;
    }

    switch (state) {
    case 0:
        // Pitch: simulate the pitch from the release point to the plate.
        if (lbl_3_common_bss_35154._464 == 0) {
            limit = (f32)lbl_3_data_26F78.pitch[flag].unk38 / 100000.0f;
            memcpy(&pos, &g_Pitcher.ballCurrentPosition, sizeof(VecXYZ));
            memcpy(&end, &g_Pitcher.ballVelocity, sizeof(VecXYZ));
            memcpy(&add, &g_Pitcher.pitchCurveVeloV1, sizeof(VecXYZ));
            trail = &lbl_3_data_26F78.pitch[flag];
            trail->life = 0;
            while (pos.z > limit) {
                fn_3_15C024(&pos, &end, &add, 0);
                trail->life++;
            }
            pos.y = -pos.y;
            end.x = g_Pitcher.ballCurrentPosition.x;
            end.y = -g_Pitcher.ballCurrentPosition.y;
            end.z = g_Pitcher.ballCurrentPosition.z;
            if (flag) {
                lbl_3_data_2709C.pitch.unk10 = trail->life;
                lbl_3_data_2709C.pitch.tex = lbl_3_common_bss_35154.tex;
                fn_8002CE4C(&end, &pos, &lbl_3_data_2709C.pitch);
            } else {
                trail->tex = lbl_3_common_bss_35154.tex;
                fn_8002DCE4(&end, &pos, trail);
            }
        }
        break;
    case 1:
    case 2:
        // Hit: trail along the predicted flight path.
        if (flag) {
            lbl_3_data_2709C.hit.tex = lbl_3_common_bss_35154.tex;
            memcpy(&pos, &g_Ball, sizeof(VecXYZ));
            i = 0;
            while (g_Ball.physicsSubstruct.futureCoordsAndDist[i + 1].pos.y >= g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y) {
                i++;
            }
            limit = (f32)lbl_3_data_26F78.minHitHeight / 100000.0f;
            while (g_Ball.physicsSubstruct.futureCoordsAndDist[i + 1].pos.y >= limit) {
                i++;
            }
            lbl_3_data_2709C.hit.unk10 = i;
            memcpy(&end, &g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos, sizeof(VecXYZ));
            pos.y = -pos.y;
            end.y = -end.y;
            fn_8002CE4C(&pos, &end, &lbl_3_data_2709C.hit);
        } else {
            trail = &lbl_3_data_26F78.hit[flag];
            trail->tex = lbl_3_common_bss_35154.tex;
            minLen = ((f32)trail->unk38 / 100000.0f) / 100.0f;
            lenRange = ((f32)trail->unk3C / 100000.0f) / 100.0f - minLen;
            i = 0;
            while (g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y < g_Ball.physicsSubstruct.futureCoordsAndDist[i + 1].pos.y) {
                i++;
            }
            trail->life = (minLen + (lenRange * rand()) / 32767.0f) * (f32)(g_Ball.hangtimeOfHit - i) + (f32)i;
            memcpy(&pos, &g_Ball, sizeof(VecXYZ));
            memcpy(&end, &g_Ball.physicsSubstruct.futureCoordsAndDist[trail->life].pos, sizeof(VecXYZ));
            pos.y = -pos.y;
            end.y = -end.y;
            fn_8002DCE4(&pos, &end, trail);
        }
        break;
    }
}
#endif

// .text:0x0015C000 size:0x14 mapped:0x8079B094
void fn_3_15C000(void) {
    lbl_3_data_2709C.hit.unk10 = 2;
}

// .text:0x0015C014 size:0x10 mapped:0x8079B0A8
u32 fn_3_15C014(void) {
    return lbl_3_data_2709C.hit.unk10;
}

// .text:0x0015C024 size:0x20C mapped:0x8079B0B8
void fn_3_15C024(VecXYZ* pos, VecXYZ* vel, VecXYZ* add, int flag) {
    f32 dir = 0.0f;
    f32 v;
    f32 t;
    T5D6C* e = &lbl_3_data_5D6C[g_Pitcher.specialPitchTypeCode];
    if (pos->z <= g_Pitcher.pitchZ_whenAirResistanceStarts) {
        t = vel->z - vel->z * g_Pitcher.airResistance_veloAdj;
        if (t < -0.05f) {
            vel->x -= vel->x * g_Pitcher.airResistance_veloAdj;
            vel->y -= vel->y * g_Pitcher.airResistance_veloAdj;
            vel->z = t;
        }
    }
    vel->x = vel->x * g_Pitcher.decelerationFactor;
    vel->y = vel->y * g_Pitcher.decelerationFactor;
    vel->z = vel->z * g_Pitcher.decelerationFactor;
    vel->x = vel->x + add->x;
    pos->x = pos->x + vel->x;
    pos->y = pos->y + vel->y;
    pos->z = pos->z + vel->z;
    if (flag) {
        u16 b;
        v = 0.00005f * LinearInterpolateToNewRange(g_Pitcher.calced_curve, 1.0f, 100.0f, e->_2, e->_4);
        b = g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]].buttonInput;
        if (b & 1) {
            dir = -1.0f;
        } else if (b & 2) {
            dir = 1.0f;
        }
        if (dir) {
            vel->x = v * dir;
        }
    }
}


// .data 0x00026F78..0x000271A8
BallTrailFx lbl_3_data_26F78 = {
    {
        {NULL, 22, 128, 0, 50000, 100000, 10, 32, 32, -3000000, 6000000, -4500000, 4500000, 128, -100000, 0, 0, 0},
        {
            NULL,
            40,
            128,
            0,
            70000,
            90000,
            10,
            32,
            32,
            -3000000,
            6000000,
            -4500000,
            4500000,
            128,
            -100000,
            0,
            -4500000,
            4500000,
        },
    },
    {
        {
            NULL,
            22,
            256,
            0,
            80000,
            150000,
            50,
            32,
            32,
            -6000000,
            6000000,
            -4500000,
            4500000,
            32,
            6000000,
            9000000,
            0,
            0,
        },
        {
            NULL,
            40,
            256,
            0,
            80000,
            150000,
            50,
            32,
            32,
            -6000000,
            6000000,
            -4500000,
            4500000,
            32,
            6000000,
            9000000,
            -4500000,
            4500000,
        },
    },
    200000,
};
BallLineFx lbl_3_data_2709C = {
    {
        NULL,
        40,
        256,
        30,
        10000,
        90000,
        100000,
        60000,
        70000,
        30,
        40,
        32,
        32,
        80000,
        150000,
        -6000000,
        6000000,
        -4500000,
        4500000,
        2000000,
        3000000,
        -4500000,
        4500000,
        400000,
        800000,
        70000,
        80000,
        -100000,
        -120000,
        25000,
        50000,
        0,
        25000,
    },
    {
        NULL,
        40,
        128,
        30,
        10000,
        90000,
        100000,
        80000,
        90000,
        20,
        30,
        128,
        128,
        70000,
        90000,
        -3000000,
        6000000,
        -4500000,
        4500000,
        1500000,
        2000000,
        -4500000,
        4500000,
        400000,
        800000,
        70000,
        80000,
        -100000,
        -120000,
        25000,
        50000,
        0,
        25000,
    },
};

