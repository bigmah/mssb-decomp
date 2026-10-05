#include "game/rep_3AE8.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_3_data_2709C[];

typedef struct {
    s16 _0;
    s16 _2;
    s16 _4;
    u8 pad[8];
} T5D6C;
extern T5D6C lbl_3_data_5D6C[];

// .text:0x0015B79C size:0x304 mapped:0x8079A830
void fn_3_15B79C(void) {
    return;
}

// .text:0x0015BAA0 size:0x560 mapped:0x8079AB34
void fn_3_15BAA0(void) {
    return;
}

// .text:0x0015C000 size:0x14 mapped:0x8079B094
void fn_3_15C000(void) {
    *(u32*)(lbl_3_data_2709C + 0x10) = 2;
}

// .text:0x0015C014 size:0x10 mapped:0x8079B0A8
u32 fn_3_15C014(void) {
    return *(u32*)(lbl_3_data_2709C + 0x10);
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
            vel->x = vel->x - vel->x * g_Pitcher.airResistance_veloAdj;
            vel->y = vel->y - vel->y * g_Pitcher.airResistance_veloAdj;
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

