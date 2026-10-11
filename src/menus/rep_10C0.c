#include "header_rep_data.h"
#include "menus/rep_10C0.h"
#include "Dolphin/vec.h"
#include "Dolphin/GX/GXTransform.h"
#include "main/file_800A7C08.h"
#include "string.h"

extern MenuCameraWork* lbl_2_bss_1A824C[];
extern MenuCamera lbl_2_bss_1A81D4;
extern MenuCameraPreset lbl_2_data_38E0[];
extern MenuCameraSpring lbl_2_data_3BB0[][2];
extern PadState lbl_803C77B8[4];

extern f32 fn_2_4A18C(f32 angle);
extern void fn_2_68DE8(s32 index, Vec* result);
extern void makeLookAtMatrix(Mtx m, Vec* camPos, Vec* camUp, Vec* target);
extern void fn_80011640(MenuCamera* a, MenuCamera* b);
extern void fn_800B806C(s32 index, f32 bottom, f32 top, f32 left, f32 right,
                      f32 near, f32 far, f32 focalLength);

// Constants of this unit's .rodata, referenced by name so CW doesn't pool them.
extern const Vec lbl_2_rodata_1110; // {0, 1, 0}
extern const Vec lbl_2_rodata_111C; // {0, 0, 1}
extern const Vec lbl_2_rodata_1128; // {0, 1, 0}
extern const Vec lbl_2_rodata_1134; // {0, 0, 1}
extern const f32 lbl_2_rodata_1140; // 0.01f
extern const f32 lbl_2_rodata_1148; // -256.0f
extern const f32 lbl_2_rodata_114C; // 1/256
extern const f32 lbl_2_rodata_1150; // 1/1024
extern const f32 lbl_2_rodata_1154; // 2*pi / 0x10000
extern const f32 lbl_2_rodata_1144; // 0.0f
extern const f32 lbl_2_rodata_1168; // -10.0f
extern const f32 lbl_2_rodata_116C; // 11.0f
extern const f32 lbl_2_rodata_1170; // -50.0f
extern const f32 lbl_2_rodata_1174; // -22.0f
extern const f32 lbl_2_rodata_1178; // -24.0f
extern const f32 lbl_2_rodata_117C; // 8.0f
extern const f32 lbl_2_rodata_1180; // 0.00001f
extern const f32 lbl_2_rodata_1184; // 0.00002f
extern const f32 lbl_2_rodata_1188; // -0.175f
extern const f32 lbl_2_rodata_118C; // 0.175f
extern const f32 lbl_2_rodata_1190; // 0.25f
extern const f32 lbl_2_rodata_1194; // -0.25f
extern const f32 lbl_2_rodata_1198; // 1.0f
extern const f32 lbl_2_rodata_119C; // 512.0f
extern const f32 lbl_2_rodata_11A0; // -240.0f
extern const f32 lbl_2_rodata_11A4; // 240.0f
extern const f32 lbl_2_rodata_11A8; // -320.0f
extern const f32 lbl_2_rodata_11AC; // 320.0f
extern const f32 lbl_2_rodata_11B0; // -512.0f
extern const f32 lbl_2_rodata_11B4; // -1.0f
extern const f32 lbl_2_rodata_11B8; // 1280.0f

#define WORK (lbl_2_bss_1A824C[0])

// One step of a damped spring: moves `cur` towards `goal`, damped by how far
// the goal moved since last frame (`prevGoal`).
static inline Vec CameraSpringStep(Vec cur, Vec goal, Vec prevGoal, f32 stiffness, f32 damping, f32 rest) {
    Vec dir;
    Vec vel;
    Vec goalMove;
    f32 dist;
    f32 force;

    PSVECSubtract(&cur, &goal, &dir);
    dist = PSVECDistance(&cur, &goal);
    PSVECSubtract(&prevGoal, &goal, &goalMove);
    PSVECScale(&goalMove, lbl_2_rodata_1140, &vel);
    force = stiffness * (rest - dist) + damping * (PSVECDotProduct(&vel, &dir) / dist);
    PSVECNormalize(&dir, &dir);
    PSVECScale(&dir, force * lbl_2_rodata_1140, &dir);
    PSVECAdd(&cur, &dir, &cur);
    return cur;
}

// fn_2_927C8, size:0x26C
void fn_2_927C8(MenuCamera* cam, Vec* goal) {
    if (WORK->springOn) {
        Vec res;
        Vec cur;
        Vec next;
        Vec prev;
        Vec unused;
        f32 stiffness;
        f32 damping;
        f32 rest;

        memcpy(&unused, goal, sizeof(Vec));
        cur.x = WORK->targetSpring.x;
        cur.y = WORK->targetSpring.y;
        cur.z = WORK->targetSpring.z;
        memcpy(&next, goal, sizeof(Vec));
        prev.x = WORK->targetPrev.x;
        prev.y = WORK->targetPrev.y;
        prev.z = WORK->targetPrev.z;
        rest = WORK->targetParams.rest;
        damping = WORK->targetParams.damping;
        stiffness = WORK->targetParams.stiffness;
        res = CameraSpringStep(cur, next, prev, stiffness, damping, rest);
        WORK->targetPrev.x = goal->x;
        WORK->targetPrev.y = goal->y;
        WORK->targetPrev.z = goal->z;
        WORK->targetSpring.x = res.x;
        WORK->targetSpring.y = res.y;
        WORK->targetSpring.z = res.z;
        goal->x = res.x;
        goal->y = res.y;
        goal->z = res.z;
    }
}

// fn_2_92A34, size:0x27C
void fn_2_92A34(MenuCamera* cam, Vec* goal) {
    if (WORK->springOn) {
        Vec res;
        Vec cur;
        Vec next;
        Vec prev;
        f32 stiffness;
        f32 damping;
        f32 rest;

        goal->x = fn_2_4A18C(goal->x);
        goal->y = fn_2_4A18C(goal->y);
        cur.x = WORK->targetSpring.x;
        cur.y = WORK->targetSpring.y;
        cur.z = WORK->targetSpring.z;
        next.x = goal->x;
        next.y = goal->y;
        next.z = lbl_2_rodata_1144;
        prev.x = WORK->targetPrev.x;
        prev.y = WORK->targetPrev.y;
        prev.z = WORK->targetPrev.z;
        rest = WORK->targetParams.rest;
        damping = WORK->targetParams.damping;
        stiffness = WORK->targetParams.stiffness;
        res = CameraSpringStep(cur, next, prev, stiffness, damping, rest);
        WORK->targetPrev.x = goal->x;
        WORK->targetPrev.y = goal->y;
        WORK->targetPrev.z = lbl_2_rodata_1144;
        WORK->targetSpring.x = res.x;
        WORK->targetSpring.y = res.y;
        WORK->targetSpring.z = res.z;
        goal->x = res.x;
        goal->y = res.y;
    }
}

// fn_2_92CB0, size:0x27C
void fn_2_92CB0(MenuCamera* cam) {
    if (WORK->springOn) {
        Vec res;
        Vec cur;
        Vec next;
        Vec prev;
        f32 stiffness;
        f32 damping;
        f32 rest;
        f32 x, y, z;

        x = WORK->pos.x;
        y = WORK->pos.y;
        z = WORK->pos.z;
        cur.x = WORK->posSpring.x;
        cur.y = WORK->posSpring.y;
        cur.z = WORK->posSpring.z;
        next.x = x;
        next.y = y;
        next.z = z;
        prev.x = WORK->posPrev.x;
        prev.y = WORK->posPrev.y;
        prev.z = WORK->posPrev.z;
        rest = WORK->posParams.rest;
        damping = WORK->posParams.damping;
        stiffness = WORK->posParams.stiffness;
        res = CameraSpringStep(cur, next, prev, stiffness, damping, rest);
        WORK->pos.x = res.x;
        WORK->pos.y = res.y;
        WORK->pos.z = res.z;
        WORK->posSpring.x = res.x;
        WORK->posSpring.y = res.y;
        WORK->posSpring.z = res.z;
        WORK->posPrev.x = x;
        WORK->posPrev.y = y;
        WORK->posPrev.z = z;
    }
}

// fn_2_92F2C, size:0x3B0
// NONMATCHING 97%: float constant loads (-256, 1/256, 1/1024, u8->f32 bias) get swapped f-regs and one addi/@l addressing difference
#if NONMATCHING
void fn_2_92F2C(MenuCamera* cam) {
    Vec up = lbl_2_rodata_1128;
    Vec angles;
    Vec offset = lbl_2_rodata_1134;
    Mtx rotX;
    Mtx rotY;
    Mtx rot;
    f32 c;
    f32 s;

    if (!(lbl_803C77B8[WORK->padIndex].held & 0x10)) {
        cam->rotX -= lbl_803C77B8[WORK->padIndex].sticks.substickY;
        cam->rotY += lbl_803C77B8[WORK->padIndex].sticks.substickX;
        cam->strafe = lbl_803C77B8[WORK->padIndex].sticks.stickX / lbl_2_rodata_1148;
        cam->advance = lbl_803C77B8[WORK->padIndex].sticks.stickY * lbl_2_rodata_114C;
        cam->pos.y += lbl_803C77B8[WORK->padIndex].analog.triggerRight * lbl_2_rodata_1150;
        cam->pos.y -= lbl_803C77B8[WORK->padIndex].analog.triggerLeft * lbl_2_rodata_1150;
    }
    if (lbl_803C77B8[WORK->padIndex].repeat & 0x800) {
        cam->fov -= lbl_2_rodata_1140;
    } else if (lbl_803C77B8[WORK->padIndex].repeat & 0x400) {
        cam->fov += lbl_2_rodata_1140;
    }
    angles.x = cam->rotX;
    angles.y = cam->rotY;
    angles.z = lbl_2_rodata_1144;
    PSVECScale(&angles, lbl_2_rodata_1154, &angles);
    PSMTXRotRad(rotX, 'X', angles.x);
    PSMTXRotRad(rotY, 'Y', angles.y);
    s = rotY[0][2];
    c = rotY[0][0];
    PSMTXConcat(rotY, rotX, rot);
    PSMTXMultVec(rot, &offset, &cam->target);
    cam->pos.x += cam->advance * s - cam->strafe * c;
    cam->pos.z += cam->advance * c + cam->strafe * s;
    cam->target.x += cam->pos.x;
    cam->target.y += cam->pos.y;
    cam->target.z += cam->pos.z;
    makeLookAtMatrix(cam->view, &cam->pos, &up, &cam->target);
}
#endif

// fn_2_932DC, size:0x91C
// NONMATCHING 99.6%: f0/f1 swapped in the cam->pos clamps and f28-f31 rotated in the inlined fn_2_927C8 spring
#if NONMATCHING
void fn_2_932DC(MenuCamera* cam) {
    Mtx rotX;
    Mtx rotY;
    Mtx rot;
    Vec up = lbl_2_rodata_1110;
    Vec offset = lbl_2_rodata_111C;
    Vec angles;
    Vec focus;
    Vec target;
    s32 preset = WORK->presetIndex;
    f32 c;
    f32 s;

    cam->rotX = lbl_2_data_38E0[preset].rotX;
    cam->rotY = lbl_2_data_38E0[preset].rotY;
    cam->strafe = lbl_2_rodata_1144;
    cam->advance = lbl_2_rodata_1144;
    angles.x = cam->rotX;
    angles.y = cam->rotY;
    angles.z = lbl_2_rodata_1144;
    PSVECScale(&angles, lbl_2_rodata_1154, &angles);
    PSMTXRotRad(rotX, 'X', angles.x);
    PSMTXRotRad(rotY, 'Y', angles.y);
    s = rotY[0][2];
    c = rotY[0][0];
    PSMTXConcat(rotY, rotX, rot);
    PSMTXMultVec(rot, &offset, &cam->target);
    cam->pos.x += cam->advance * s - cam->strafe * c;
    cam->pos.z += cam->advance * c + cam->strafe * s;
    cam->target.x += cam->pos.x;
    cam->target.y += cam->pos.y;
    cam->target.z += cam->pos.z;

    if (WORK->focusMode == 1) {
        memcpy(&angles, &lbl_2_data_38E0[preset].pos, sizeof(Vec));
        fn_2_68DE8(WORK->focusIndex, &focus);
        PSVECAdd(&focus, &angles, &angles);
        memcpy(&cam->pos, &angles, sizeof(Vec));
    } else {
        memcpy(&angles, &lbl_2_data_38E0[preset].pos, sizeof(Vec));
        memcpy(&cam->pos, &angles, sizeof(Vec));
    }
    if (WORK->noClamp == 0) {
        if (cam->pos.x <= lbl_2_rodata_1168) {
            cam->pos.x = lbl_2_rodata_1168;
        }
        if (cam->pos.x >= lbl_2_rodata_116C) {
            cam->pos.x = lbl_2_rodata_116C;
        }
        if (cam->pos.z <= lbl_2_rodata_1170) {
            cam->pos.z = lbl_2_rodata_1170;
        }
        if (cam->pos.z >= lbl_2_rodata_1174) {
            cam->pos.z = lbl_2_rodata_1174;
        }
    }
    memcpy(&WORK->pos, &cam->pos, sizeof(Vec));

    if (WORK->focusIndex != -1) {
        fn_2_68DE8(WORK->focusIndex, &target);
    } else {
        memcpy(&target, &lbl_2_data_38E0[preset].target, sizeof(Vec));
    }
    if (WORK->noClamp == 0) {
        if (target.x <= lbl_2_rodata_1168) {
            target.x = lbl_2_rodata_1168;
        } else if (target.x >= lbl_2_rodata_116C) {
            target.x = lbl_2_rodata_116C;
        } else {
            WORK->targetClamped.x = target.x;
        }
        if (target.z <= lbl_2_rodata_1178) {
            target.z = lbl_2_rodata_1178;
        } else if (target.z >= lbl_2_rodata_117C) {
            target.z = lbl_2_rodata_117C;
        } else {
            WORK->targetClamped.z = target.z;
        }
    }
    memcpy(&WORK->target, &target, sizeof(Vec));
    fn_2_927C8(cam, &target);
    memcpy(&WORK->target, &target, sizeof(Vec));
    fn_2_92CB0(cam);
    memcpy(&cam->pos, &WORK->pos, sizeof(Vec));
    memcpy(&cam->target, &WORK->target, sizeof(Vec));
    cam->fov = lbl_2_data_38E0[preset].fov;
    makeLookAtMatrix(cam->view, &cam->pos, &up, &cam->target);
}
#endif

// fn_2_93BF8, size:0x6C
void fn_2_93BF8(MenuCamera* cam) {
    switch (WORK->cameraMode) {
    case 0:
        fn_2_932DC(cam);
        break;
    case 1:
        fn_2_92F2C(cam);
        break;
    }
    fn_80011640(cam, cam);
}

// fn_2_94604, size:0x18
void fn_2_94604(u8 value) {
    WORK->focusMode = value;
}

// fn_2_9461C, size:0x18
void fn_2_9461C(s16 value) {
    WORK->focusIndex = value;
}

// fn_2_94634, size:0xA8
void fn_2_94634(s32 i) {
    WORK->posParams.stiffness = lbl_2_data_3BB0[i][0].stiffness;
    WORK->posParams.damping = lbl_2_data_3BB0[i][0].damping;
    WORK->posParams.rest = lbl_2_data_3BB0[i][0].rest;
    WORK->targetParams.stiffness = lbl_2_data_3BB0[i][1].stiffness;
    WORK->targetParams.damping = lbl_2_data_3BB0[i][1].damping;
    WORK->targetParams.rest = lbl_2_data_3BB0[i][1].rest;
    if (i == 0) {
        WORK->springOn = 0;
        return;
    }
    WORK->springOn = 1;
}

// fn_2_946DC, size:0x178
void fn_2_946DC(s32 i) {
    WORK->posParams.stiffness = lbl_2_data_3BB0[i][0].stiffness;
    WORK->posParams.damping = lbl_2_data_3BB0[i][0].damping;
    WORK->posParams.rest = lbl_2_data_3BB0[i][0].rest;
    WORK->targetParams.stiffness = lbl_2_data_3BB0[i][1].stiffness;
    WORK->targetParams.damping = lbl_2_data_3BB0[i][1].damping;
    WORK->targetParams.rest = lbl_2_data_3BB0[i][1].rest;
    WORK->posPrev.x = lbl_2_bss_1A81D4.pos.x;
    WORK->posPrev.y = lbl_2_bss_1A81D4.pos.y;
    WORK->posPrev.z = lbl_2_bss_1A81D4.pos.z;
    WORK->posSpring.x = lbl_2_rodata_1180 + lbl_2_bss_1A81D4.pos.x;
    WORK->posSpring.y = lbl_2_rodata_1180 + lbl_2_bss_1A81D4.pos.y;
    WORK->posSpring.z = lbl_2_rodata_1180 + lbl_2_bss_1A81D4.pos.z;
    WORK->targetPrev.x = lbl_2_rodata_1180 + lbl_2_bss_1A81D4.target.x;
    WORK->targetPrev.y = lbl_2_rodata_1180 + lbl_2_bss_1A81D4.target.y;
    WORK->targetPrev.z = lbl_2_rodata_1180 + lbl_2_bss_1A81D4.target.z;
    WORK->targetSpring.x = lbl_2_rodata_1184 + lbl_2_bss_1A81D4.target.x;
    WORK->targetSpring.y = lbl_2_rodata_1184 + lbl_2_bss_1A81D4.target.y;
    WORK->targetSpring.z = lbl_2_rodata_1184 + lbl_2_bss_1A81D4.target.z;
}
