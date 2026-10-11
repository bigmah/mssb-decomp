#ifndef __CHALLENGE_REP_7978_H_
#define __CHALLENGE_REP_7978_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// Analog part of a PADStatus (starts at stickX).
typedef struct ChallengeDebugPad {
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
    u8 triggerL;
    u8 triggerR;
} ChallengeDebugPad;

struct ChallengeDebugCamera;
typedef void (*ChallengeDebugCameraFunc)(struct ChallengeDebugCamera* camera, u16 held, u16 pressed, u16 repeated,
                                         ChallengeDebugPad* pad);

// Free-fly debug camera.
typedef struct ChallengeDebugCamera {
    Mtx view;            // 0x00
    Mtx44 projection;    // 0x30
    Vec position;        // 0x70
    Vec direction;       // 0x7C
    Vec up;              // 0x88
    u8 pad94[0xA4 - 0x94];
    f32 yaw;             // 0xA4
    f32 pitch;           // 0xA8
    f32 moveSpeed;       // 0xAC
    f32 turnSpeed;       // 0xB0, degrees per second
    f32 zoomSpeed;       // 0xB4
    f32 zoom;            // 0xB8
    f32 invZoom;         // 0xBC
    f32 near;            // 0xC0
    f32 far;             // 0xC4
    f32 top;             // 0xC8
    f32 bottom;          // 0xCC
    f32 left;            // 0xD0
    f32 right;           // 0xD4
    ChallengeDebugCameraFunc update; // 0xD8
} ChallengeDebugCamera;

void fn_1_26D28(ChallengeDebugCamera* camera, u16 held, u16 pressed, u16 repeated, ChallengeDebugPad* pad);
void fn_1_272DC(ChallengeDebugCamera* camera, u32 matrixId);
void fn_1_27330(ChallengeDebugCamera* camera);
void fn_1_273D8(ChallengeDebugCamera* camera);

#endif
