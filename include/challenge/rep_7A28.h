#ifndef __CHALLENGE_REP_7A28_H__
#define __CHALLENGE_REP_7A28_H__

#include "mssbTypes.h"
#include "challenge/rep_0010.h"
#include "challenge/rep_7978.h"
#include "main/debug_menu.h"

// Particle test task (lbl_803CC1B8 while fn_1_27E98 runs).
typedef struct ChParticleTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ ChallengeDebugCamera* camera;
    /*0x18*/ void* texture;
    /*0x1C*/ DebugMenu* menu;
    /*0x20*/ Vec pos;
    /*0x2C*/ f32 length;
    /*0x30*/ f32 scale;
    /*0x34*/ u16 flags; // 1: menu/emitter mode, 2: respawn, 4: ?, 8: menu open
    /*0x36*/ s8 mode;
    /*0x37*/ s8 cursor; // 0..6
} ChParticleTask;

void fn_1_27AD0(void);

void fn_1_27E50(void);

void fn_1_27560(s32 value);

void fn_1_27AD4(void);

void fn_1_27D6C(void);

void fn_1_28118(void);

void fn_1_28200(void);

void fn_1_27594(void);

void fn_1_27BB8(void);

void fn_1_27E98(void);

void fn_1_276CC(void);

#endif
