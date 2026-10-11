#ifndef __CHALLENGE_REP_02A8_H__
#define __CHALLENGE_REP_02A8_H__

#include "mssbTypes.h"
#include "challenge/rep_0010.h"
#include "musyx/musyx.h"

// 3D sound test (fn_1_A95C): one listener and one emitter.
typedef struct ChSound3DTest {
    /*0x00*/ SND_LISTENER listener;
    /*0x90*/ SND_EMITTER emitter;
    /*0xDC*/ u8 padDC[4];
    /*0xE0*/ u8 active;
} ChSound3DTest; // size: 0xE4

// sndAddEmitter arguments used by the 3D sound test.
typedef struct ChSoundEmitterParams {
    /*0x00*/ f32 maxDis;
    /*0x04*/ f32 comp;
    /*0x08*/ f32 maxVol;
    /*0x0C*/ f32 minVol;
    /*0x10*/ u16 fxid;
} ChSoundEmitterParams;

// sndAddListener arguments used by the 3D sound test.
typedef struct ChSoundListenerParams {
    /*0x00*/ f32 frontSur;
    /*0x04*/ f32 backSur;
    /*0x08*/ f32 soundSpeed;
    /*0x0C*/ u8 vol;
} ChSoundListenerParams;

// Sound-group load task queued with fn_1_9F04 (same layout as ChSoundLoadTask).
typedef struct ChSoundGroupTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ s32 (*callback)(void);
    /*0x18*/ u8 step;
    /*0x19*/ u8 group;
} ChSoundGroupTask;

void fn_1_A714(void);

s32 fn_1_A7E4(void);

s32 fn_1_A8B4(void);

s32 fn_1_A908(void);

s32 fn_1_A718(void);

void fn_1_A2E4(void);

u32 fn_1_BF34(u32 effect);

void fn_1_A634(void);

void fn_1_B4A4(void);

void fn_1_C188(void);

s32 fn_1_A77C(void);

s32 fn_1_A7B0(void);

s32 fn_1_A880(void);

s32 fn_1_A838(void);

void fn_1_BEF4(s16 voice);

void fn_1_BDD8(void);

void fn_1_A348(void);

void fn_1_A464(void);

void fn_1_BFB0(void);

void fn_1_BC00(void);

void fn_1_BA64(void);

void fn_1_B5B8(void);

void fn_1_A95C(void);

#endif
