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
