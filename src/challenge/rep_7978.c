#include "challenge/rep_7978.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"


static inline void updateView(ChallengeDebugCamera* camera) {
    Vec target;
    PSVECAdd(&camera->position, &camera->direction, &target);
    C_MTXLookAt(camera->view, &camera->position, &camera->up, &target);
}

// .text:0x00026D28 size:0x5B4
void fn_1_26D28(ChallengeDebugCamera* camera, u16 held, u16 pressed, u16 repeated, ChallengeDebugPad* pad) {
    return;
}

// .text:0x000272DC size:0x54
void fn_1_272DC(ChallengeDebugCamera* camera, u32 matrixId) {
    GXSetProjection(camera->projection, GX_PERSPECTIVE);
    GXLoadPosMtxImm(camera->view, matrixId);
    GXSetCurrentMtx(matrixId);
}

static inline void updateProjection(ChallengeDebugCamera* camera) {
    C_MTXFrustum(camera->projection, (camera->invZoom * (camera->top * camera->near)) / 1280.0f,
                 (camera->invZoom * (camera->bottom * camera->near)) / 1280.0f,
                 (camera->invZoom * (camera->left * camera->near)) / 1280.0f,
                 (camera->invZoom * (camera->right * camera->near)) / 1280.0f, camera->near, camera->far);
}

// .text:0x00027330 size:0xA8
void fn_1_27330(ChallengeDebugCamera* camera) {
    return;
}

// .text:0x000273D8 size:0x188
void fn_1_273D8(ChallengeDebugCamera* camera) {
    return;
}
