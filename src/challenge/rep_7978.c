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
    Mtx rot;
    Quaternion q;
    Vec v;

    if (camera->update == NULL || camera->update == fn_1_26D28) {
        if (pressed & 0x10) {
            fn_1_273D8(camera);
            return;
        }

        camera->yaw = camera->yaw - (((3.1415927f * camera->turnSpeed) / 180.0f) * (f32)pad->substickX /
                                     128.0f) / 60.0f;
        camera->pitch = camera->pitch - (((3.1415927f * camera->turnSpeed) / 180.0f) *
                                         (f32)pad->substickY / 128.0f) / 60.0f;
        while (camera->yaw < -3.1415927f) {
            camera->yaw += 6.2831855f;
        }
        while (camera->yaw >= 3.1415927f) {
            camera->yaw -= 6.2831855f;
        }
        if (camera->pitch < -3.1385248f) {
            camera->pitch = -3.1385248f;
        } else if (camera->pitch > 3.1385248f) {
            camera->pitch = 3.1385248f;
        }

        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 1.0f;
        PSVECCrossProduct(&v, &camera->up, &camera->direction);
        PSVECNormalize(&camera->direction, &camera->direction);
        C_QUATRotAxisRad(&q, &camera->direction, camera->pitch);
        PSMTXQuat(rot, &q);
        PSMTXMultVec(rot, &v, &camera->direction);
        C_QUATRotAxisRad(&q, &camera->up, camera->yaw);
        PSMTXQuat(rot, &q);
        PSMTXMultVec(rot, &camera->direction, &camera->direction);

        v.x = (-camera->moveSpeed * (f32)pad->stickX / 128.0f) / 60.0f;
        v.z = (camera->moveSpeed * (f32)pad->stickY / 128.0f) / 60.0f;
        v.y = ((camera->moveSpeed * (f32)pad->triggerL) / 150.0f) / 60.0f;
        v.y = v.y - ((camera->moveSpeed * (f32)pad->triggerR) / 150.0f) / 60.0f;
        PSMTXMultVec(rot, &v, &v);
        PSVECAdd(&camera->position, &v, &camera->position);

        camera->zoom = camera->zoom + (camera->zoomSpeed * (f32)(s32)((held >> 10) & 1)) / 60.0f;
        camera->zoom = camera->zoom - (camera->zoomSpeed * (f32)(s32)((held >> 11) & 1)) / 60.0f;
        camera->zoom = 0.1f * (f32)(0.0f == camera->zoom) +
                       camera->zoom * (f32)(0.0f != camera->zoom);
        camera->invZoom = 1.0f / camera->zoom;
    } else {
        camera->update(camera, held, pressed, repeated, pad);
    }
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
    updateView(camera);
    updateProjection(camera);
}

// .text:0x000273D8 size:0x188
void fn_1_273D8(ChallengeDebugCamera* camera) {
    camera->moveSpeed = 5.0f;
    camera->turnSpeed = 120.0f;
    camera->update = NULL;
    camera->pitch = camera->yaw = 0.0f;
    camera->position.x = camera->position.y = camera->position.z = 0.0f;
    camera->direction.x = camera->direction.y = 0.0f;
    camera->direction.z = 1.0f;
    camera->up.x = 0.0f;
    camera->up.y = 1.0f;
    camera->up.z = 0.0f;
    updateView(camera);
    camera->zoomSpeed = 1.0f;
    camera->zoom = 1.0f;
    camera->invZoom = 1.0f / camera->zoom;
    camera->near = 1.0f;
    camera->far = 512.0f;
    camera->top = 240.0f;
    camera->bottom = -240.0f;
    camera->left = -320.0f;
    camera->right = 320.0f;
    updateProjection(camera);
}
