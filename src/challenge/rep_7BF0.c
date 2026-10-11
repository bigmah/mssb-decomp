#include "challenge/rep_7BF0.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "main/file_800A7C08.h"
#include "main/file_800B0724.h"
#include "main/file_8004207C.h"
#include "main/file_80024184.h"
#include "main/file_80037054.h"

extern PadState lbl_803C77B8[4];
extern void fn_800B806C(s32 index, f32 bottom, f32 top, f32 left, f32 right, f32 near, f32 far, f32 focalLength);
extern void fn_1_AF4(s32 rows, s32 cols, f32 spacing);

extern void* lbl_80366158[];
extern ChallengeQueueEntry* lbl_803CC1B8;
// POOL BEGIN (high-to-low; memory order is the reverse)
static ChallengeDebugCamera lbl_1_bss_471D8;
static ChallengeSimulationMenu lbl_1_bss_471BC;
static RigidBody lbl_1_bss_47068;
// POOL END
extern f32 lbl_1_rodata_7DFC;
extern const char* lbl_1_data_11424[];

static ChallengeSimulationSettings lbl_1_data_11300 = {
    { 150000, 50000, 6250, 12500 }, // len, frac, radius, mass
    5000,                           // unk50
    500000,                         // height
    2000000,                        // angle
    { 0, 0, 0 },                    // vel
    { 0, 0, 0 },                    // angVel
    19,                             // steps
    0,                              // simulationState
    0,                              // stepRequested
};
static RigidBodyParams sSimParams = { 100000000, 100, 100, 980665, 100, 100, 1000, 314000, 0 };
// Unit cube drawn by fn_1_28CE8.
static f32 sBoxVerts[8][3] = {
    { -0.5f, -0.5f, -0.5f },
    { 0.5f, -0.5f, -0.5f },
    { 0.5f, 0.5f, -0.5f },
    { -0.5f, 0.5f, -0.5f },
    { -0.5f, -0.5f, 0.5f },
    { 0.5f, -0.5f, 0.5f },
    { 0.5f, 0.5f, 0.5f },
    { -0.5f, 0.5f, 0.5f },
};
static GXColor sBoxColors[8] = {
    { 0xFF, 0x00, 0x00, 0xFF },
    { 0x00, 0xFF, 0x00, 0xFF },
    { 0x00, 0x00, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0x00, 0xFF },
    { 0xFF, 0x00, 0xFF, 0xFF },
    { 0x00, 0xFF, 0xFF, 0xFF },
    { 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00 },
};
// GX_QUADS, 24 vertices of (position index, color index): one quad per face
static u8 sBoxDisplayList[0x40] = {
    0x80, 0x00, 0x18, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04, 0x01, 0x07, 0x01, 0x06,
    0x01, 0x05, 0x01, 0x00, 0x02, 0x04, 0x02, 0x05, 0x02, 0x01, 0x02, 0x01, 0x03, 0x05, 0x03, 0x06,
    0x03, 0x02, 0x03, 0x02, 0x04, 0x06, 0x04, 0x07, 0x04, 0x03, 0x04, 0x03, 0x05, 0x07, 0x05, 0x04,
    0x05, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static u32 sB = 1;
static u32 sC[36] = {0};
static struct { u8 pad0[0x30]; u32 v; u8 pad1[0x444]; } sD = {{0}};
static ChallengeMenuItem* sE[2] = {0};

// fn_1_2948C, size:0x15C
static inline u8 NavigationMask(u16 held) {
    return (held & 0x800) ? 0x91 : ((held & 0x400) ? 0x50 : 0);
}
void fn_1_2948C(ChallengeQueueEntry* task) {
    u16 held;
    u16 pressed;
    u16 repeated;

    repeated = lbl_803C77B8[0].repeat;
    held = lbl_803C77B8[0].held;
    pressed = lbl_803C77B8[0].down;
    if (lbl_803C77B8[0].down & 0x1000) {
        task->menuOpen ^= 1;
        if (task->menuOpen != 0) {
            fn_800A97D0(32, 0);
        } else {
            fn_800A97D0(16, 30);
        }
    } else if (task->menuOpen != 0) {
        fn_80048820(&lbl_1_bss_471BC, held, pressed, repeated,
            NavigationMask(lbl_803C77B8[0].held));
        held &= 0xFFFFF3FF;
        pressed &= 0xFFFFF3FF;
        repeated &= 0xFFFFF3FF;
    } else if (lbl_803C77B8[0].down & 0x200) {
        fn_1_29A48();
    }
    fn_1_26D28(&lbl_1_bss_471D8, held, pressed, repeated, (ChallengeDebugPad*)&lbl_803C77B8[0].sticks);
    fn_1_27330(&lbl_1_bss_471D8);
}


// fn_1_289E0, size:0x100
s32 fn_1_289E0(ChallengeSimulationMenu* menu, u16 buttons) {
    switch (lbl_1_data_11300.simulationState) {
    case 0:
        if (buttons & 0x100) {
            lbl_1_data_11300.simulationState = 2;
        } else if (buttons & 0x400) {
            lbl_1_data_11300.stepRequested = 1;
            lbl_1_data_11300.simulationState = 1;
        }
        break;
    case 1:
        if (buttons & 0x100) {
            lbl_1_data_11300.simulationState = 2;
        } else if (buttons & 0x200) {
            lbl_1_data_11300.simulationState = 0;
        } else if (buttons & 0x400) {
            lbl_1_data_11300.stepRequested = 1;
        }
        break;
    case 2:
        if (buttons & 0x100) {
            lbl_1_data_11300.simulationState = 1;
        } else if (buttons & 0x200) {
            lbl_1_data_11300.simulationState = 0;
        }
        break;
    }
    menu->items[menu->selected].text = lbl_1_data_11424[lbl_1_data_11300.simulationState];
    return 0;
}

// fn_1_2935C, size:0xB8
void fn_1_2935C(RigidBody* body) {
    fn_80037768(body, 2, lbl_1_data_11300.cameraFlags,
        (f32)lbl_1_data_11300.scaledCamera[0] / 100000.0f,
        (f32)lbl_1_data_11300.scaledCamera[1] / 100000.0f,
        (f32)lbl_1_data_11300.scaledCamera[2] / 100000.0f,
        (f32)lbl_1_data_11300.scaledCamera[3] / 100000.0f);
}

// fn_1_29414, size:0x78
void fn_1_29414(ChallengeQueueEntry* task) {
    if (task->menuOpen != 0) {
        fn_80048BEC(&lbl_1_bss_471BC, 0, 0);
    }
    fn_1_272DC(&lbl_1_bss_471D8, 0);
    fn_1_AF4(10, 10, lbl_1_rodata_7DFC);
    fn_1_28CE8(task);
}

// fn_1_29A48, size:0x54
void fn_1_29A48(void) {
    ChallengeQueueState* state;

    fn_800AD038(lbl_80366158[2]);
    fn_800A97D0(16, 30);
    state = lbl_803CC1B8->state;
    state->state = 1;
    fn_800B0A14_removeQueue(state);
}


// fn_1_289C0, size:0x20
void fn_1_289C0(ChallengeDebugCamera* camera) {
    fn_1_273D8(camera);
}

// fn_1_28C34, size:0xB4
void fn_1_28C34(ChallengeSimulationMenu* menu, s32 which, void* data) {
    menu->data = data ? data : (void*)sB;
    menu->capacity = 0x10;
    menu->cursor = 0;
    menu->selected = 0;
    menu->flags = 1;
    menu->items = sE[which];
    if (which == 1) {
        if (sD.v == 0) {
            sD.v = sC[lbl_1_data_11300.simulationState];
        }
    }
    menu->count = 0;
    while (menu->items[menu->count].text != NULL) {
        menu->count++;
    }
}

// fn_1_28AE0, size:0x154
s32 fn_1_28AE0(ChallengeSimulationMenu* menu) {
    ChallengeQueueEntry* entry = lbl_803CC1B8;
    entry->selection = menu->items[menu->selected].selection;
    if (entry->selection < 0) {
        fn_800AD038(lbl_80366158[2]);
        fn_800A97D0(16, 30);
        {
            ChallengeQueueState* state = lbl_803CC1B8->state;
            state->state = 1;
            fn_800B0A14_removeQueue(state);
        }
    } else {
        fn_1_28C34(menu, entry->selection, (void*)menu->items[menu->selected].text);
    }
    return 0;
}

// .text:0x0002858C size:0x434
// Orbit-camera update (same as fn_1_26D28 without the callback, pitch and height inverted).
void fn_1_2858C(ChallengeDebugCamera* camera, u16 held, u16 pressed, u16 repeated, ChallengeDebugPad* pad) {
    Mtx rot;
    Quaternion q;
    Vec v;

    if (pressed & 0x10) {
        fn_1_273D8(camera);
        return;
    }

    camera->yaw = camera->yaw - (((3.1415927f * camera->turnSpeed) / 180.0f) * (f32)pad->substickX /
                                 128.0f) / 60.0f;
    camera->pitch = camera->pitch + (((3.1415927f * camera->turnSpeed) / 180.0f) *
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

    v.x = (camera->moveSpeed * (f32)-pad->stickX / 128.0f) / 60.0f;
    v.z = (camera->moveSpeed * (f32)pad->stickY / 128.0f) / 60.0f;
    v.y -= ((camera->moveSpeed * (f32)pad->triggerL) / 150.0f) / 60.0f;
    v.y += ((camera->moveSpeed * (f32)pad->triggerR) / 150.0f) / 60.0f;
    PSMTXMultVec(rot, &v, &v);
    PSVECAdd(&camera->position, &v, &camera->position);

    camera->zoom = camera->zoom + (camera->zoomSpeed * (f32)(s32)((held >> 10) & 1)) / 60.0f;
    camera->zoom = camera->zoom - (camera->zoomSpeed * (f32)(s32)((held >> 11) & 1)) / 60.0f;
    camera->zoom = 0.1f * (f32)(0.0f == camera->zoom) + camera->zoom * (f32)(0.0f != camera->zoom);
    camera->invZoom = 1.0f / camera->zoom;
}

// .text:0x00028CE8 size:0x374
// Draws the rigid body as a box plus a set of axes; the vectors computed at the end are unused.
void fn_1_28CE8(ChallengeQueueEntry* task) {
    return;
}

// .text:0x0002905C size:0x300
// Steps the rigid-body simulation according to lbl_1_data_11300.simulationState.
void fn_1_2905C(void) {
    Mtx m;

    switch (lbl_1_data_11300.simulationState) {
    case 0:
        fn_1_2935C(&lbl_1_bss_47068);
        lbl_1_bss_47068.pos.x = 0.0f;
        lbl_1_bss_47068.pos.y = (f32)lbl_1_data_11300.height / 100000.0f;
        lbl_1_bss_47068.pos.z = 0.0f;
        lbl_1_bss_47068.vel.x = (f32)lbl_1_data_11300.vel[0] / 100000.0f;
        lbl_1_bss_47068.vel.y = (f32)lbl_1_data_11300.vel[1] / 100000.0f;
        lbl_1_bss_47068.vel.z = (f32)lbl_1_data_11300.vel[2] / 100000.0f;
        PSMTXMultVec(lbl_1_bss_47068.invRot, &lbl_1_bss_47068.vel, &lbl_1_bss_47068.velLocal);
        lbl_1_bss_47068.angVel.x = (f32)lbl_1_data_11300.angVel[0] / 100000.0f;
        lbl_1_bss_47068.angVel.y = (f32)lbl_1_data_11300.angVel[1] / 100000.0f;
        lbl_1_bss_47068.angVel.z = (f32)lbl_1_data_11300.angVel[2] / 100000.0f;
        PSMTXRotRad(m, 'X', 0.017453292f * ((f32)lbl_1_data_11300.angle / 100000.0f));
        C_QUATMtx(&lbl_1_bss_47068.quat, m);
        fn_800383BC(&lbl_1_bss_47068);
        break;
    case 1:
        if (lbl_1_data_11300.stepRequested == 0) {
            break;
        }
        lbl_1_data_11300.stepRequested = 0;
    case 2:
        lbl_1_bss_47068.unk50 = (f32)lbl_1_data_11300.unk50 / 100000.0f;
        fn_80037054(&lbl_1_bss_47068, &sSimParams);
        break;
    }
}

// .text:0x000295E8 size:0x460
void fn_1_295E8(void) {
    return;
}

// .text:0x00029A9C size:0x1C0
void fn_1_29A9C(void) {
    return;
}
