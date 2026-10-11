#include "main/file_80026134.h"
#include "Dolphin/stl.h"
#include "stl/math.h"

extern ActorManager lbl_8036E548;
extern void fn_800B2DD0(Model* model, ModelJoint* joint);

// .text:0x80026134 size:0x2C8
// Turns actor idx's head joint toward the target position (pitch first, then full rotation).
void fn_80026134(s32 idx, Vec* target) {
    JointCtrl ctrl;
    Mtx m;
    Vec fwd = { 0.0f, 0.0f, 1.0f };
    Vec dir;
    Vec axis;
    Quaternion q1;
    Quaternion q2;
    LookActor* actor;
    LookActor* override;
    Model** pm;
    Model* model;
    ModelJoint* joint;
    ModelJoint* parent;
    s32 j;
    f32 angle;
    f32 s;
    f32 c;

    override = lbl_8036E548.actorOverride[idx];
    if (override != NULL) {
        actor = override;
        pm = &lbl_8036E548.modelSlots[override->modelIdx].model;
    } else {
        actor = &lbl_8036E548.actors[idx];
        pm = &lbl_8036E548.modelSlots[idx].model;
    }
    model = *pm;
    j = actor->headJoint;
    if (j == 0xFFFF) {
        return;
    }
    joint = model->joints[j];
    memcpy(&ctrl, &joint->ctrl, sizeof(JointCtrl));
    parent = joint->parent;

    PSMTXInverse(joint->worldMtx, m);
    PSMTXMultVec(m, target, &dir);
    dir.x = 0.0f;
    PSVECNormalize(&dir, &dir);
    angle = acos(PSVECDotProduct(&fwd, &dir));
    if (angle < 0.000001f) {
        axis.x = 1.0f;
    } else {
        PSVECCrossProduct(&fwd, &dir, &axis);
    }
    if (angle > 1.256637f) {
        angle = 1.256637f;
    }
    angle *= 0.5f;
    q1.x = axis.x * sin(angle);
    q1.y = 0.0f;
    q1.z = 0.0f;
    q1.w = cos(angle);
    CTRLSetQuat(&ctrl.c, q1.x, q1.y, q1.z, q1.w);
    CTRLBuildMatrix(&ctrl.c, m);
    PSMTXConcat(parent->worldMtx, m, m);
    PSMTXInverse(m, m);
    PSMTXMultVec(m, target, &dir);
    PSVECNormalize(&dir, &dir);
    PSVECCrossProduct(&fwd, &dir, &axis);
    c = acos(PSVECDotProduct(&fwd, &dir));
    if (c > 0.94247776f) {
        c = 0.94247776f;
    }
    angle = c;
    angle *= 0.5f;
    s = sin(angle);
    c = cos(angle);
    q2.x = axis.x * s;
    q2.y = axis.y * s;
    q2.z = axis.z * s;
    q2.w = c;
    PSQUATMultiply(&q1, &q2, &q1);
    CTRLSetQuat(&joint->ctrl.c, q1.x, q1.y, q1.z, q1.w);
    fn_800B2DD0(model, joint);
}
