#include "main/file_80037054.h"
#include "main/file_800B0724.h"
#include "stl/string.h"
#include "stl/math.h"

typedef struct CharSlot {
    /*0x00*/ u8 _00[0x34];
    /*0x34*/ Model* model;
    /*0x38*/ u8 _38[0x90 - 0x38];
} CharSlot; // size 0x90

typedef struct Unk8036E548 {
    /*0x0000*/ u8 _0000[0x60];
    /*0x0060*/ CharSlot* slots;
    /*0x0064*/ u8 _0064[0xC38 - 0x64];
    /*0x0C38*/ Vec unkC38;
    /*0x0C44*/ u8 _0C44[0x2C50 - 0xC44];
    /*0x2C50*/ CharModelObj* chars[1]; // TODO size
} Unk8036E548;

extern Unk8036E548 lbl_8036E548;
extern JointAttachTask* lbl_803CC1B8;
extern u32 fn_80024D2C(void* anim);
extern BOOL getAnimRelatedCoordinates(int charIdx, int joint, Vec* out);

extern const f32 lbl_803CC720; // 1/60
extern const f32 lbl_803CC724; // 100000
extern const f32 lbl_803CC728; // 0
extern const f32 lbl_803CC72C; // 0.5
extern const f32 lbl_803CC738; // -9.80665
extern const f32 lbl_803CC73C; // 1
extern const f32 lbl_803CC740; // 0.25
extern const f32 lbl_803CC744; // 12
extern const f32 lbl_803CC748; // 9.80665
extern const f32 lbl_803CC74C; // 10
extern const f32 lbl_803CC750; // 20
extern const f32 lbl_803CC754; // 2
extern const f32 lbl_803CC758; // 60
extern const f32 lbl_803CC75C; // -1
extern const f32 lbl_803CC760; // 0.8
extern const f32 lbl_803CC764; // 100
extern const f32 lbl_803CC768; // 5
extern const f32 lbl_803CC76C; // 1.5
extern const f32 lbl_803CC770; // 0.001
extern const f32 lbl_803CC774; // -0.12675
extern const f32 lbl_803CC778; // 1.8
extern const f32 lbl_803CC77C; // 50
extern const f32 lbl_803CC780; // 0.2
extern const f32 lbl_803CC784; // 1/6
extern const f32 lbl_803CC788; // 0.0001
extern const f32 lbl_803CC78C; // 1.3
extern const f32 lbl_803CC790; // 0.2962963
extern const f32 lbl_803CC794; // -0.1
extern const f32 lbl_803CC798; // 3.375

extern Vec lbl_800F79A0[2];
extern BatSim lbl_800F79B8;
extern s16 lbl_803CB818;
extern f32 lbl_803CB81C;
extern s32 lbl_803CB820;
extern f32 lbl_803CB824;
extern u8 lbl_803CBCA0;
extern u8 lbl_803CBCA1;
extern u8 lbl_803CBCA2[6];

// .text:0x80037054 size:0x2C8
s32 fn_80037054(RigidBody* rb, RigidBodyParams* params) {
    RigidBody b;
    Vec dpos;
    Vec dvel;
    Vec w;
    Quaternion q;
    f32 maxAngVel;
    f32 time;

    time = lbl_803CC720;
    rb->unk150 = rb->dt;
    memcpy(&b, rb, sizeof(RigidBody));
    do {
        fn_8003731C(&b, params);
        PSVECScale(&b.force, b.invMass * b.unk150, &dvel);
        PSVECAdd(&b.vel, &dvel, &b.vel);
        PSVECScale(&b.vel, b.unk150, &dpos);
        PSVECAdd(&b.pos, &dpos, &b.pos);
        maxAngVel = params->maxAngVel / lbl_803CC724;
        w.x = b.inertia.x * b.angVel.x;
        w.y = b.inertia.y * b.angVel.y;
        w.z = b.inertia.z * b.angVel.z;
        PSVECCrossProduct(&b.angVel, &w, &w);
        PSVECSubtract(&b.torque, &w, &w);
        w.x = w.x * b.invInertia.x;
        w.y = w.y * b.invInertia.y;
        w.z = w.z * b.invInertia.z;
        PSVECScale(&w, b.unk150, &w);
        PSVECAdd(&b.angVel, &w, &b.angVel);
        if (maxAngVel != lbl_803CC728) {
            f32 mag = PSVECMag(&b.angVel);
            if (mag > maxAngVel) {
                PSVECScale(&b.angVel, maxAngVel / mag, &b.angVel);
            }
        }
        memcpy(&q, &b.angVel, sizeof(Vec));
        q.w = lbl_803CC728;
        PSQUATMultiply(&b.quat, &q, &q);
        PSQUATScale(&q, lbl_803CC72C * b.unk150, &q);
        PSQUATAdd(&b.quat, &q, &b.quat);
        PSMTXQuat(b.rot, &b.quat);
        PSMTXInverse(b.rot, b.invRot);
        PSMTXTransApply(b.rot, b.world, b.pos.x, b.pos.y, b.pos.z);
        PSMTXMultVec(b.invRot, &b.vel, &b.velLocal);
        time -= b.unk150;
    } while (time > lbl_803CC728);
    memcpy(rb, &b, sizeof(RigidBody));
    return 0;
}

// .text:0x8003731C size:0x44C
s32 fn_8003731C(RigidBody* rb, RigidBodyParams* params) {
    Vec world[2];
    Vec local[2];
    Vec v;
    Vec f;
    Vec fric;
    Vec saved;
    Vec t;
    Vec off;
    f32 spring = params->spring / 100000.0f;
    f32 damping = params->damping / 100000.0f;
    f32 maxForce = params->maxForce / 100000.0f;
    f32 minForce = params->minForce / 100000.0f;
    f32 torqueEps = params->torqueEps / 100000.0f;
    f32 maxDepth = params->maxDepth / 100000.0f;
    f32 friction = params->friction / 100000.0f;
    f32 depth;
    f32 mag;
    s32 i;

    memcpy(&saved, &rb->force, sizeof(Vec));
    memset(&rb->force, 0, sizeof(Vec));
    memset(&rb->forceLocal, 0, sizeof(Vec));
    memset(&rb->torque, 0, sizeof(Vec));
    off.x = off.z = lbl_803CC728;
    off.y = -rb->radius;
    PSMTXMultVec(rb->invRot, &off, &off);
    PSVECScale(&rb->vel, -rb->unk50, &f);
    PSVECAdd(&rb->force, &f, &rb->force);
    PSVECScale(&rb->angVel, -rb->unk50, &t);
    (&t.x)[rb->axis] = lbl_803CC728;
    PSVECAdd(&rb->torque, &t, &rb->torque);

    // ground contact at both end points
    i = 2;
    while (i-- != 0) {
        PSVECAdd(i == 1 ? &rb->p1 : &rb->p0, &off, &local[i]);
        PSMTXMultVec(rb->world, &local[i], &world[i]);
        memset(&f, 0, sizeof(Vec));
        f.y = -world[i].y;
        depth = f.y;
        if (depth >= lbl_803CC728) {
            if (maxDepth != lbl_803CC728 && depth > maxDepth) {
                f.y = maxDepth;
            }
            PSVECCrossProduct(&local[i], &rb->angVel, &v);
            PSMTXMultVec(rb->rot, &v, &v);
            PSVECAdd(&rb->vel, &v, &v);
            f.y = spring * f.y + damping * -v.y;
            mag = fabs(f.y);
            if (maxForce != lbl_803CC728 && mag > maxForce) {
                f.y = maxForce * (f.y / mag);
            } else if (mag < minForce) {
                continue;
            }
            if (friction != lbl_803CC728) {
                fric.x = -v.x;
                fric.y = lbl_803CC728;
                fric.z = -v.z;
                PSVECScale(&fric, friction, &fric);
                f.x += fric.x;
                f.z += fric.z;
            }
            PSVECAdd(&rb->force, &f, &rb->force);
            PSMTXMultVec(rb->invRot, &f, &f);
            PSVECCrossProduct(&local[i], &f, &t);
            PSVECAdd(&rb->torque, &t, &rb->torque);
        }
    }

    // gravity
    f.x = lbl_803CC728;
    f.y = lbl_803CC738 * rb->mass;
    f.z = lbl_803CC728;
    PSVECAdd(&rb->force, &f, &rb->force);
    if (PSVECMag(&rb->torque) < torqueEps) {
        memset(&rb->torque, 0, sizeof(Vec));
    }
    return 0;
}

// .text:0x80037768 size:0x1FC
void fn_80037768(RigidBody* rb, s32 axis, s32 steps, f32 len, f32 frac, f32 radius, f32 mass) {
    f32 inertia;

    rb->axis = axis;
    rb->p1.x = lbl_803CC728;
    rb->p1.y = lbl_803CC728;
    rb->p1.z = lbl_803CC728;
    (&rb->p1.x)[axis] = -len * frac;
    rb->p0.x = lbl_803CC728;
    rb->p0.y = lbl_803CC728;
    rb->p0.z = lbl_803CC728;
    (&rb->p0.x)[axis] = len + (&rb->p1.x)[axis];
    PSVECSubtract(&rb->p0, &rb->p1, &rb->d);
    rb->mass = mass;
    rb->invMass = lbl_803CC73C / mass;
    rb->radius = radius;
    {
        f32 r2 = radius * radius;
        f32 l2 = len * len;
        inertia = mass * (r2 * lbl_803CC740 + l2 / lbl_803CC744);
    }
    rb->inertia.z = inertia;
    rb->inertia.y = inertia;
    rb->inertia.x = inertia;
    {
        f32 axial = radius * (mass * radius);
        (&rb->inertia.x)[axis] = axial * lbl_803CC72C;
    }
    rb->invInertia.x = lbl_803CC73C / rb->inertia.x;
    rb->invInertia.y = lbl_803CC73C / rb->inertia.y;
    rb->invInertia.z = lbl_803CC73C / rb->inertia.z;
    rb->steps = steps;
    rb->dt = lbl_803CC720 / rb->steps;
    rb->unk50 = lbl_803CC728;
    rb->unk54 = lbl_803CC72C;
    PSMTXIdentity(rb->rot);
    PSMTXIdentity(rb->invRot);
    PSMTXIdentity(rb->world);
    rb->pos.x = rb->pos.y = rb->pos.z = lbl_803CC728;
    rb->quat.x = rb->quat.y = rb->quat.z = lbl_803CC728;
    rb->quat.w = lbl_803CC73C;
    rb->forceLocal.x = rb->forceLocal.y = rb->forceLocal.z = lbl_803CC728;
    rb->vel.x = rb->vel.y = rb->vel.z = lbl_803CC728;
    rb->velLocal.x = rb->velLocal.y = rb->velLocal.z = lbl_803CC728;
    rb->torque.x = rb->torque.y = rb->torque.z = lbl_803CC728;
    rb->angVel.x = rb->angVel.y = rb->angVel.z = lbl_803CC728;
    rb->unk14D = 0;
    rb->unk14C = 0;
}

// .text:0x80037964 size:0x20
void fn_80037964(JointAttachTask* task) {
    fn_800B0A14_removeQueue(task);
}

// .text:0x80037984 size:0x11C
static inline MtxPtr getJointMtx(JointAttachTask* task) {
    CharModelObj* obj = lbl_8036E548.chars[task->charIdx];
    ModelJoint** joints = lbl_8036E548.slots[obj->slot].model->joints;
    u16 joint;
    if (obj != NULL) {
        joint = obj->jointMap[task->joint];
    } else {
        joint = 0xFFFF;
    }
    return joints[joint]->mtx;
}

void fn_80037984(void) {
    JointAttachTask* task = lbl_803CC1B8;
    Mtx m;
    Vec pos;
    Quaternion q;

    PSMTXCopy(getJointMtx(task), m);
    m[2][3] = lbl_803CC728;
    m[1][3] = lbl_803CC728;
    m[0][3] = lbl_803CC728;
    C_QUATMtx(&q, m);
    getAnimRelatedCoordinates(task->charIdx, task->joint, &pos);
    if (fn_80024D2C(task->anim) & 0x10000000) {
        fn_80038418(task->body, &pos, &q, &task->pos, &task->quat);
        lbl_803CC1B8->func = fn_80037964;
    } else {
        memcpy(&task->pos, &pos, sizeof(Vec));
        memcpy(&task->quat, &q, sizeof(Quaternion));
    }
}

// .text:0x80037AA0 size:0x78
void fn_80037AA0(RigidBody* body, s32 charIdx, void (*callback)(void), u16 joint, void* anim) {
    JointAttachTask* task;

    if (lbl_8036E548.chars[charIdx] != NULL) {
        task = fn_800B0A5C_insertQueue((void*)fn_80037984, 0x6001);
        task->body = body;
        task->charIdx = charIdx;
        task->joint = joint;
        task->anim = anim;
        task->callback = callback;
    }
}

// .text:0x80037B18 size:0x94
void fn_80037B18(RigidBody* rb, Vec* force) {
    Vec f;
    Vec arm;
    Vec t;

    PSVECScale(&rb->d, lbl_803CC73C, &arm);
    PSVECAdd(&arm, &rb->p1, &arm);
    PSMTXMultVec(rb->invRot, force, &f);
    PSVECAdd(&rb->forceLocal, &f, &rb->forceLocal);
    PSVECCrossProduct(&arm, &f, &t);
    PSVECAdd(&rb->torque, &t, &rb->torque);
}

// .text:0x80037BAC size:0x5F0
s32 fn_80037BAC(RigidBody* rb) {
    RigidBody b;
    RigidBody* orig;
    Vec world[2];
    Vec t;
    Vec n;
    Vec vel;
    Vec angVel;
    Vec r;
    Quaternion q;
    Vec* pts[2];
    s32 side[2];
    f32 time;
    f32 denom;
    s32 j;

    orig = rb;
    time = rb->dt;
    rb = &b;
    memcpy(rb, orig, 0x150);
    pts[0] = &rb->p1;
    pts[1] = &rb->p0;
    PSMTXMultVec(rb->world, &rb->p1, &world[0]);
    PSMTXMultVec(rb->world, &rb->p0, &world[1]);
    rb->unk150 = rb->dt;
    do {
        PSMTXMultVec(rb->invRot, &rb->vel, &rb->velLocal);
        fn_8003819C(rb);
        PSVECScale(&rb->forceLocal, rb->invMass * rb->unk150, &t);
        PSMTXMultVec(rb->rot, &t, &t);
        PSVECAdd(&rb->vel, &t, &rb->vel);
        PSVECScale(&rb->vel, rb->unk150, &t);
        PSVECAdd(&rb->pos, &t, &rb->pos);
        t.x = rb->inertia.x * rb->angVel.x;
        t.y = rb->inertia.y * rb->angVel.y;
        t.z = rb->inertia.z * rb->angVel.z;
        PSVECCrossProduct(&rb->angVel, &t, &t);
        PSVECSubtract(&rb->torque, &t, &t);
        PSVECScale(&t, rb->unk150, &t);
        rb->angVel.x = t.x * rb->invInertia.x + rb->angVel.x;
        rb->angVel.y = t.y * rb->invInertia.y + rb->angVel.y;
        rb->angVel.z = t.z * rb->invInertia.z + rb->angVel.z;
        PSVECScale(&rb->angVel, rb->unk150, (Vec*)&q);
        q.w = lbl_803CC728;
        PSQUATMultiply(&rb->quat, &q, &q);
        PSQUATScale(&q, lbl_803CC72C * rb->unk150, &q);
        PSQUATAdd(&rb->quat, &q, &q);
        if (q.x != lbl_803CC728 || q.y != lbl_803CC728 || q.z != lbl_803CC728 || q.w != lbl_803CC728) {
            PSQUATNormalize(&q, &rb->quat);
        } else {
            memcpy(&rb->quat, &q, sizeof(Quaternion));
        }
        rb->torque.x = rb->torque.y = rb->torque.z = lbl_803CC728;
        rb->forceLocal.x = rb->forceLocal.y = rb->forceLocal.z = lbl_803CC728;
        PSMTXQuat(rb->rot, &rb->quat);
        PSMTXInverse(rb->rot, rb->invRot);
        PSMTXTransApply(rb->rot, rb->world, rb->pos.x, rb->pos.y, rb->pos.z);
        PSMTXMultVec(rb->world, &rb->p1, &world[0]);
        PSMTXMultVec(rb->world, &rb->p0, &world[1]);

        // which end points touch the ground (1), are above it (0) or went through it (-1)
        side[0] = (world[0].y < -rb->radius) ? 0 : ((world[0].y > rb->radius) ? -1 : 1);
        side[1] = (world[1].y < -rb->radius) ? 0 : ((world[1].y > rb->radius) ? -1 : 1);
        if (side[0] == 0) {
            rb->unk14D = 0;
        } else if (rb->unk14D != 0) {
            side[0] = 0;
        }
        if (side[1] == 0) {
            rb->unk14C = 0;
        } else if (rb->unk14C != 0) {
            side[1] = 0;
        }

        if (side[0] != -1 && side[1] != -1) {
            PSMTXMultVec(rb->invRot, &rb->vel, &rb->velLocal);
            memcpy(&vel, &rb->velLocal, sizeof(Vec));
            memcpy(&angVel, &rb->angVel, sizeof(Vec));
            n.x = lbl_803CC728;
            n.y = lbl_803CC73C;
            n.z = lbl_803CC728;
            PSMTXMultVec(rb->invRot, &n, &n);
            j = 1;
            do {
                if (side[j] != 0) {
                    PSVECCrossProduct(&angVel, pts[j], &t);
                    PSVECAdd(&vel, &t, &t);
                    PSMTXMultVec(rb->rot, &t, &r);
                    if (r.y > lbl_803CC728) {
                        // collision impulse
                        PSVECCrossProduct(pts[j], &n, &r);
                        r.x = r.x * rb->invInertia.x;
                        r.y = r.y * rb->invInertia.y;
                        r.z = r.z * rb->invInertia.z;
                        PSVECCrossProduct(&r, pts[j], &r);
                        denom = rb->invMass + PSVECDotProduct(&n, &r);
                        PSVECScale(&n, (lbl_803CC73C + rb->unk54) * -PSVECDotProduct(&t, &n) / denom, &t);
                        PSVECScale(&t, rb->invMass, &r);
                        PSVECAdd(&rb->velLocal, &r, &rb->velLocal);
                        PSVECCrossProduct(pts[j], &t, &t);
                        t.x = t.x * rb->invInertia.x;
                        t.y = t.y * rb->invInertia.y;
                        t.z = t.z * rb->invInertia.z;
                        PSVECAdd(&rb->angVel, &t, &rb->angVel);
                    }
                    if (j != 0) {
                        rb->unk14C = 1;
                    } else {
                        rb->unk14D = 1;
                    }
                }
            } while (j-- != 0);
            PSMTXMultVec(rb->rot, &rb->velLocal, &rb->vel);
            time -= rb->unk150;
            if (rb->unk150 < time) {
                rb->unk150 = time;
            }
            memcpy(orig, rb, 0x150);
        } else {
            // went through the ground: retry with half the step
            memcpy(rb, orig, 0x150);
            rb->unk150 *= lbl_803CC72C;
        }
    } while (time > lbl_803CC728);
    return 0;
}

// .text:0x8003819C size:0x220
void fn_8003819C(RigidBody* rb) {
    Vec pt;
    Vec f;
    Vec v;
    Vec g;
    Vec t;
    s32 i;

    f.x = lbl_803CC728;
    f.y = lbl_803CC748 * rb->mass;
    f.z = lbl_803CC728;
    PSMTXMultVec(rb->invRot, &f, &f);
    PSVECAdd(&rb->forceLocal, &f, &rb->forceLocal);
    for (i = 0; i <= 10; i++) {
        PSVECScale(&rb->d, i / lbl_803CC74C, &pt);
        PSVECAdd(&rb->p1, &pt, &pt);
        PSVECCrossProduct(&rb->angVel, &pt, &v);
        PSVECAdd(&v, &rb->velLocal, &v);
        PSVECScale(&v, rb->unk50, &f);
        if (rb->unk14D != 0 && rb->unk14C != 0) {
            g.x = lbl_803CC728;
            g.y = lbl_803CC738 * rb->mass / lbl_803CC750;
            g.z = lbl_803CC728;
            if (i > 0 && i < 10) {
                g.y = g.y * lbl_803CC754;
            }
            PSMTXMultVec(rb->invRot, &g, &g);
            PSVECAdd(&f, &g, &f);
        } else if ((rb->unk14D != 0 && i == 0) || (rb->unk14C != 0 && i == 10)) {
            g.x = lbl_803CC728;
            g.y = lbl_803CC738 * rb->mass;
            g.z = lbl_803CC728;
            PSMTXMultVec(rb->invRot, &g, &g);
            PSVECAdd(&f, &g, &f);
        }
        PSVECAdd(&rb->forceLocal, &f, &rb->forceLocal);
        PSVECCrossProduct(&pt, &f, &t);
        PSVECAdd(&rb->torque, &t, &rb->torque);
    }
}

// .text:0x800383BC size:0x5C
MtxPtr fn_800383BC(RigidBody* rb) {
    PSMTXQuat(rb->rot, &rb->quat);
    PSMTXInverse(rb->rot, rb->invRot);
    PSMTXTransApply(rb->rot, rb->world, rb->pos.x, rb->pos.y, rb->pos.z);
    return rb->world;
}

// .text:0x80038418 size:0x1D8
void fn_80038418(RigidBody* rb, Vec* pos, Quaternion* quat, Vec* prevPos, Quaternion* prevQuat) {
    Mtx m1;
    Mtx m2;
    Vec v;
    Quaternion q;
    f32 angle;

    v.x = -rb->p1.x;
    v.y = -rb->p1.y;
    v.z = -rb->p1.z;
    PSMTXQuat(rb->rot, quat);
    PSMTXInverse(rb->rot, rb->invRot);
    PSMTXTransApply(rb->rot, rb->world, pos->x, pos->y, pos->z);
    PSMTXMultVec(rb->world, &v, &rb->pos);
    memcpy(&rb->quat, quat, sizeof(Quaternion));

    // linear velocity from the previous pose
    PSMTXQuat(m2, prevQuat);
    PSMTXTransApply(m2, m1, prevPos->x, prevPos->y, prevPos->z);
    PSMTXMultVec(m1, &v, &v);
    PSVECSubtract(&rb->pos, &v, &v);
    PSVECScale(&v, lbl_803CC758, &rb->vel);
    PSMTXMultVec(rb->invRot, &rb->vel, &rb->velLocal);
    memset(&rb->vel, 0, sizeof(Vec));
    memset(&rb->velLocal, 0, sizeof(Vec));

    // angular velocity from the rotation delta
    PSMTXQuat(m1, quat);
    PSMTXQuat(m2, prevQuat);
    PSMTXInverse(m2, m2);
    PSMTXConcat(m1, m2, m1);
    C_QUATMtx(&q, m1);
    q.w = acos(q.w);
    angle = lbl_803CC758 * (lbl_803CC754 * q.w);
    q.w = sin(q.w);
    if (q.w != lbl_803CC728) {
        PSVECScale((Vec*)&q, angle / q.w, &rb->angVel);
    } else {
        rb->angVel.x = angle;
        rb->angVel.y = lbl_803CC728;
        rb->angVel.z = lbl_803CC728;
    }
}

// .text:0x800385F0 size:0x1C0
void fn_800385F0(RigidBody* rb, f32 len, f32 frac, f32 radius, f32 mass) {
    f32 inertia;

    rb->p1.x = lbl_803CC728;
    rb->p1.y = -len * frac;
    rb->p1.z = lbl_803CC728;
    rb->p0.x = lbl_803CC728;
    rb->p0.y = len + rb->p1.y;
    rb->p0.z = lbl_803CC728;
    PSVECSubtract(&rb->p0, &rb->p1, &rb->d);
    rb->mass = mass;
    rb->invMass = lbl_803CC73C / mass;
    rb->radius = radius;
    {
        f32 r2 = radius * radius;
        f32 l2 = len * len;
        inertia = mass * (r2 * lbl_803CC740 + l2 / lbl_803CC744);
    }
    rb->inertia.z = inertia;
    rb->inertia.x = inertia;
    {
        f32 axial = radius * (mass * radius);
        rb->inertia.y = axial * lbl_803CC72C;
    }
    rb->invInertia.x = rb->invInertia.z = lbl_803CC73C / rb->inertia.x;
    rb->invInertia.y = lbl_803CC73C / rb->inertia.y;
    rb->steps = 1;
    rb->dt = lbl_803CC720 / rb->steps;
    rb->unk50 = lbl_803CC728;
    rb->unk54 = lbl_803CC72C;
    PSMTXIdentity(rb->rot);
    PSMTXIdentity(rb->world);
    rb->pos.x = rb->pos.y = rb->pos.z = lbl_803CC728;
    rb->quat.x = rb->quat.y = rb->quat.z = lbl_803CC728;
    rb->quat.w = lbl_803CC73C;
    rb->forceLocal.x = rb->forceLocal.y = rb->forceLocal.z = lbl_803CC728;
    rb->vel.x = rb->vel.y = rb->vel.z = lbl_803CC728;
    rb->velLocal.x = rb->velLocal.y = rb->velLocal.z = lbl_803CC728;
    rb->torque.x = rb->torque.y = rb->torque.z = lbl_803CC728;
    rb->angVel.x = rb->angVel.y = rb->angVel.z = lbl_803CC728;
    rb->unk14D = 0;
    rb->unk14C = 0;
}

// .text:0x800387B0 size:0x398
void fn_800387B0(RopeParams* p, RopeNode* nodes, s32 count, Vec* force) {
    Vec dv;
    Vec d;
    Vec acc;
    RopeNode* node;
    RopeNode* prev;
    s32 i;
    s32 j;
    f32 stretch;
    f32 damp;
    f32 speed;
    f32 len;
    f32 fmag;
    f32 vmag;

    // gravity and external force on the last node
    for (i = 0; i < count; i++) {
        node = &nodes[i];
        memset(&node->force, 0, sizeof(Vec));
        if (node->fixed == 0) {
            node->force.y = lbl_803CC738 * node->mass;
        }
        if (i == count - 1) {
            PSVECAdd(&node->force, force, &node->force);
        }
    }

    // springs between neighbours
    j = count;
    while (--j != 0) {
        node = &nodes[j];
        prev = &nodes[j - 1];
        PSVECSubtract(&node->pos, &prev->pos, &d);
        PSVECSubtract(&node->vel, &prev->vel, &dv);
        len = PSVECMag(&d);
        if (lbl_803CC728 != len) {
            stretch = p->springK * (len - p->restLen);
            damp = p->damping * (PSVECDotProduct(&dv, &d) / len);
            PSVECNormalize(&d, &d);
            PSVECScale(&d, -(stretch + damp), &d);
            if (node->fixed == 0) {
                PSVECAdd(&node->force, &d, &node->force);
            }
            PSVECScale(&d, lbl_803CC75C, &d);
            if (prev->fixed == 0) {
                PSVECAdd(&prev->force, &d, &prev->force);
            }
        }
    }

    // air drag and ground friction
    for (i = 0; i < count; i++) {
        node = &nodes[i];
        if (node->fixed == 0) {
            memcpy(&dv, &node->vel, sizeof(Vec));
            memcpy(&d, &node->force, sizeof(Vec));
            PSVECScale(&d, node->invMass, &d);
            PSVECScale(&d, p->dt, &d);
            PSVECAdd(&dv, &d, &dv);
            memset(&acc, 0, sizeof(Vec));
            speed = PSVECMag(&dv);
            if (speed != lbl_803CC728) {
                PSVECScale(&dv, lbl_803CC75C, &d);
                PSVECNormalize(&d, &d);
                PSVECScale(&d, p->drag * (speed * speed), &d);
                PSVECAdd(&acc, &d, &acc);
            }
            if (node->pos.y <= node->floorY && node->force.y < lbl_803CC728) {
                len = node->force.y * p->friction;
                if (len < lbl_803CC728) {
                    len = -len;
                }
                memcpy(&d, &node->force, sizeof(Vec));
                d.y = lbl_803CC728;
                fmag = PSVECMag(&d);
                dv.y = lbl_803CC728;
                vmag = PSVECMag(&dv);
                if (vmag != lbl_803CC728 || fmag > len) {
                    if (vmag != lbl_803CC728) {
                        PSVECNormalize(&dv, &d);
                    } else {
                        PSVECNormalize(&d, &d);
                    }
                    PSVECScale(&d, -len, &d);
                    PSVECAdd(&acc, &d, &acc);
                } else {
                    PSVECScale(&node->force, lbl_803CC75C, &d);
                    PSVECAdd(&acc, &d, &acc);
                }
            }
            PSVECAdd(&node->force, &acc, &node->force);
        }
    }
}

// .text:0x80038B48 size:0x188
void fn_80038B48(RopeParams* p, RopeNode* nodes, s32 count, Vec* force) {
    Vec accel;
    Vec g;
    Vec step;
    Vec next;
    RopeNode* node;
    s32 i;
    s32 iter;
    f32 dtSq;
    f32 damp;
    f32 under;

    PSVECScale(force, p->dt, &g);
    for (iter = 0; iter < p->iterations; iter++) {
        fn_800387B0(p, nodes, count, &g);
        node = nodes;
        for (i = 0; i < count; i++) {
            PSVECScale(&node->force, node->invMass, &accel);
            damp = p->invTwoDt;
            dtSq = p->dtSq;
            PSVECScale(&node->pos, lbl_803CC754, &next);
            PSVECSubtract(&next, &node->prevPos, &next);
            PSVECScale(&accel, dtSq, &step);
            PSVECAdd(&next, &step, &next);
            PSVECSubtract(&next, &node->prevPos, &node->vel);
            PSVECScale(&node->vel, damp, &node->vel);
            memcpy(&node->prevPos, &node->pos, sizeof(Vec));
            memcpy(&node->pos, &next, sizeof(Vec));
            if (node->fixed == 0) {
                under = node->pos.y - node->floorY;
                if (under < lbl_803CC728) {
                    node->pos.y = node->pos.y - under * p->bounce;
                    under = node->prevPos.y - node->floorY;
                    node->prevPos.y = node->prevPos.y - under * p->bounce;
                }
            }
            node++;
        }
    }
}

// .text:0x80038CD0 size:0x15C
RopeNode* fn_80038CD0(s32 count, f32* spacing, RopeNode* nodes, f32 floorY, f32 mass) {
    RopeNode* node;
    s32 i;
    f32 midMass;

    memset(nodes, 0, count * sizeof(RopeNode));
    node = nodes;
    midMass = lbl_803CC754 * mass;
    for (i = 0; i < count; i++) {
        if (i == 0) {
            node->mass = mass;
        } else if (i == count - 1) {
            node->mass = mass;
        } else {
            node->mass = midMass;
        }
        node->floorY = floorY;
        node->invMass = lbl_803CC73C / node->mass;
        node->pos.x = lbl_803CC728;
        node->pos.y = *spacing * i + floorY;
        node->pos.z = lbl_803CC728;
        memcpy(&node->prevPos, &node->pos, sizeof(Vec));
        node->fixed = (i == 0);
        node++;
    }
    return nodes;
}

// .text:0x80038E2C size:0x98
void fn_80038E2C(RopeParams* p) {
    p->restLen = lbl_803CC760;
    p->bounce = lbl_803CC72C;
    p->springK = lbl_803CC764;
    p->damping = lbl_803CC768;
    p->friction = lbl_803CC76C;
    p->drag = lbl_803CC770;
    p->iterations = 8;
    p->dt = (lbl_803CC73C / p->iterations) / lbl_803CC758;
    p->dtSq = p->dt * p->dt;
    p->invTwoDt = lbl_803CC73C / (lbl_803CC754 * p->dt);
}

// .text:0x80038EC4 size:0x44
void fn_80038EC4(CharModelObj* obj, Model** model, s32 joint) {
    if (lbl_800F79B8.state < 0) {
        lbl_800F79B8.state = 0;
    }
    fn_80038F08(obj, *model, joint);
}

// .text:0x80038F08 size:0x408
// NONMATCHING 92%: the original addresses lbl_800F79A0 and lbl_800F79B8 (= lbl_800F79A0 + 0x18)
// through one base register; with two separate symbols we load each address separately.
#if NONMATCHING
void fn_80038F08(CharModelObj* obj, Model* model, u8 joint) {
    Mtx dm;
    Mtx m;
    Vec v;
    Vec prev;
    BatSim* bat = &lbl_800F79B8;
    f32 frameDt = lbl_803CC720 * lbl_803CB81C;
    ModelJoint* hand = model->joints[obj->jointMap[bat->jointBase + joint]];
    ModelJoint* batJoint;
    s32 i;

    if (bat->state < 0) {
        return;
    }
    if (bat->state == 0) {
        PSMTXCopy(hand->mtx, bat->mtx);
        PSMTXMultVec(hand->mtx, &bat->tip, &v);
        bat->mtx[0][3] = v.x;
        bat->mtx[1][3] = v.y;
        bat->mtx[2][3] = v.z;
        batJoint = model->joints[obj->jointMap[bat->joint]];
        PSMTXCopy(bat->mtx, batJoint->mtx);
        PSVECScale(&bat->tip, lbl_803CC75C, &v);
        PSMTXMultVec(bat->mtx, &v, &v);
        batJoint->mtx[0][3] = v.x;
        batJoint->mtx[1][3] = v.y;
        batJoint->mtx[2][3] = v.z;
        bat->state++;
    } else if (bat->state == 1) {
        // derive the swing velocity from the hand motion
        PSMTXMultVec(hand->mtx, &bat->tip, &v);
        prev.x = bat->mtx[0][3];
        prev.y = bat->mtx[1][3];
        prev.z = bat->mtx[2][3];
        PSVECSubtract(&v, &prev, &bat->vel);
        if (lbl_803CBCA0 != 0) {
            memcpy(&bat->vel, &lbl_800F79A0[1], sizeof(Vec));
        } else {
            PSVECAdd(&bat->vel, &lbl_800F79A0[0], &bat->vel);
        }
        PSVECScale(&bat->vel, lbl_803CB824, &bat->vel);
        PSVECScale(&bat->vel, lbl_803CC73C / frameDt, &bat->vel);
        for (i = 0; i < 3; i++) {
            dm[i][0] = (hand->mtx[i][0] - bat->mtx[i][0]) / frameDt;
            dm[i][1] = (hand->mtx[i][1] - bat->mtx[i][1]) / frameDt;
            dm[i][2] = (hand->mtx[i][2] - bat->mtx[i][2]) / frameDt;
        }
        dm[2][3] = lbl_803CC728;
        dm[1][3] = lbl_803CC728;
        dm[0][3] = lbl_803CC728;
        PSMTXTranspose(hand->mtx, m);
        PSMTXConcat(dm, m, dm);
        bat->angVel.x = dm[2][1];
        bat->angVel.y = dm[0][2];
        bat->angVel.z = dm[1][0];
        PSMTXMultVec(m, &bat->angVel, &bat->angVel);
        PSMTXCopy(hand->mtx, bat->mtx);
        bat->mtx[0][3] = v.x;
        bat->mtx[1][3] = v.y;
        bat->mtx[2][3] = v.z;
        PSVECScale(&bat->angVel, lbl_803CC72C * lbl_803CB824, &bat->angVel);
        batJoint = model->joints[obj->jointMap[bat->joint]];
        PSMTXCopy(bat->mtx, batJoint->mtx);
        PSVECScale(&bat->tip, lbl_803CC75C, &v);
        PSMTXMultVec(bat->mtx, &v, &v);
        batJoint->mtx[0][3] = v.x;
        batJoint->mtx[1][3] = v.y;
        batJoint->mtx[2][3] = v.z;
        bat->state++;
    } else {
        PSMTXTrans(m, lbl_8036E548.unkC38.x, lbl_8036E548.unkC38.y, lbl_8036E548.unkC38.z);
        PSMTXInverse(m, m);
        fn_80039310(bat, lbl_803CC774, lbl_803CC778);
        batJoint = model->joints[obj->jointMap[bat->joint]];
        PSMTXCopy(bat->mtx, batJoint->mtx);
        PSVECScale(&bat->tip, lbl_803CC75C, &v);
        PSMTXMultVec(bat->mtx, &v, &v);
        batJoint->mtx[0][3] = v.x;
        batJoint->mtx[1][3] = v.y;
        batJoint->mtx[2][3] = v.z;
        bat->state += (bat->state == 2);
    }
}
#endif

// .text:0x80039310 size:0x73C
// NONMATCHING 98%: float register allocation differs (the original keeps one more callee-saved FPR, f24)
#if NONMATCHING
void fn_80039310(BatSim* bat, f32 floorY, f32 minEnergy) {
    Mtx rotM;
    Mtx m2;
    Mtx m3;
    Quaternion q;
    Vec t;
    Vec acc;
    Vec w;
    Vec k;
    Vec imp;
    Quaternion q2;
    Vec up;
    Vec b;
    Vec a;
    f32 invIx = lbl_803CC73C / bat->inertia.x;
    f32 invIy = lbl_803CC73C / bat->inertia.y;
    f32 invIz = lbl_803CC73C / bat->inertia.z;
    f32 dt = lbl_803CC720 * lbl_803CB81C;
    f32 mag;
    f32 half;
    f32 inv;
    f32 y;
    f32 energy;
    f32 sn;
    f32 cs;
    s32 i;

    mag = PSVECMag(&bat->angVel);
    if (mag >= lbl_803CC77C) {
        PSVECScale(&bat->angVel, lbl_803CC77C / mag, &bat->angVel);
    }

    // linear motion (midpoint step with gravity)
    half = lbl_803CC72C * dt;
    PSVECScale(&bat->vel, half, &t);
    PSMTXTransApply(bat->mtx, bat->mtx, t.x, t.y, t.z);
    PSVECScale(&bat->vel, lbl_803CC72C * -dt, &t);
    PSVECAdd(&bat->vel, &t, &bat->vel);
    bat->vel.y = lbl_803CC750 * dt + bat->vel.y;
    PSVECScale(&bat->vel, half, &t);
    PSMTXTransApply(bat->mtx, bat->mtx, t.x, t.y, t.z);

    // angular motion (Euler equations, 4 sub-steps)
    memcpy(&w, &bat->angVel, sizeof(Vec));
    memset(&acc, 0, sizeof(Vec));
    k.x = invIx * (bat->inertia.y - bat->inertia.z);
    k.y = invIy * (bat->inertia.z - bat->inertia.x);
    k.z = invIz * (bat->inertia.x - bat->inertia.y);
    PSVECScale(&k, dt, &k);
    for (i = 0; i < 4; i++) {
        t.y = k.y * (w.z * w.x - lbl_803CC780 * w.y);
        t.x = k.x * (w.y * w.z - lbl_803CC780 * w.x);
        t.z = k.z * (w.x * w.y - lbl_803CC780 * w.z);
        if (i == 1 || i == 2) {
            PSVECScale(&t, lbl_803CC754, &t);
        }
        PSVECAdd(&acc, &t, &acc);
        PSVECScale(&t, lbl_803CC72C, &w);
    }
    PSVECScale(&acc, lbl_803CC784, &t);
    PSVECAdd(&bat->angVel, &t, &bat->angVel);

    mag = PSVECMag(&bat->angVel);
    inv = lbl_803CC73C / mag;
    if (mag > lbl_803CC788) {
        half = lbl_803CC72C * (-mag * dt);
        acc.x = sin(half);
        acc.y = cos(half);
        PSVECScale(&bat->angVel, inv * acc.x, (Vec*)&q);
        q.w = acc.y;
    } else {
        q.w = lbl_803CC73C;
        q.z = lbl_803CC728;
        q.y = lbl_803CC728;
        q.x = lbl_803CC728;
    }
    PSMTXQuat(rotM, &q);
    PSMTXConcat(bat->mtx, rotM, bat->mtx);

    // collision of both ends with the ground
    for (i = 0; i < 2; i++) {
        PSMTXMultVec(bat->mtx, &bat->ends[i], &t);
        y = t.y;
        if (y > floorY) {
            PSMTXCopy(bat->mtx, m2);
            m2[2][3] = lbl_803CC728;
            m2[1][3] = lbl_803CC728;
            m2[0][3] = lbl_803CC728;
            PSVECCrossProduct(&bat->angVel, &bat->ends[i], &t);
            PSMTXMultVec(m2, &t, &t);
            PSVECAdd(&bat->vel, &t, &t);
            imp.x = t.x;
            imp.y = lbl_803CC78C * -t.y;
            imp.z = t.z;
            acc.x = lbl_803CC728;
            acc.y = lbl_803CC75C;
            acc.z = lbl_803CC728;
            PSMTXMultVec(m2, &bat->ends[i], &w);
            PSMTXScale(m2, invIx, invIy, invIz);
            PSMTXConcat(bat->mtx, m2, m2);
            PSMTXTranspose(bat->mtx, rotM);
            PSMTXConcat(m2, rotM, m2);
            PSVECCrossProduct(&w, &acc, &t);
            PSMTXMultVec(m2, &t, &t);
            PSVECCrossProduct(&t, &w, &t);
            imp.y = imp.y / (lbl_803CC790 + PSVECDotProduct(&t, &acc));
            imp.x = imp.x * lbl_803CC794;
            imp.z = imp.z * lbl_803CC794;
            bat->vel.y = bat->vel.y + imp.y / lbl_803CC798;
            bat->vel.x = bat->vel.x + imp.x;
            bat->vel.z = bat->vel.z + imp.z;
            PSMTXTranspose(bat->mtx, rotM);
            rotM[2][3] = lbl_803CC728;
            rotM[1][3] = lbl_803CC728;
            rotM[0][3] = lbl_803CC728;
            PSMTXMultVec(rotM, &imp, &t);
            PSVECCrossProduct(&bat->ends[i], &t, &t);
            acc.x = bat->angVel.x * bat->inertia.x;
            acc.y = bat->angVel.y * bat->inertia.y;
            acc.z = bat->angVel.z * bat->inertia.z;
            PSVECAdd(&acc, &t, &t);
            bat->angVel.x = t.x * invIx;
            bat->angVel.y = t.y * invIy;
            bat->angVel.z = t.z * invIz;
            bat->mtx[1][3] = bat->mtx[1][3] - (y - floorY);
            lbl_803CBCA1 = 1;
        }
    }

    // come to rest when the energy is low enough
    energy = lbl_803CC72C * (bat->vel.x * bat->vel.x + bat->vel.y * bat->vel.y + bat->vel.z * bat->vel.z) +
             lbl_803CC72C * (bat->angVel.x * (bat->inertia.x * bat->angVel.x) + bat->angVel.y * (bat->inertia.y * bat->angVel.y) +
                             bat->angVel.z * (bat->inertia.z * bat->angVel.z));
    if (bat->mtx[1][3] > lbl_803CC728) {
        energy = bat->mtx[1][3] * lbl_803CC750 + energy;
    } else {
        energy = energy - bat->mtx[1][3] * lbl_803CC750;
    }
    if (energy <= minEnergy) {
        bat->mtx[1][3] = floorY;
        bat->angVel.x = bat->angVel.y = bat->angVel.z = bat->vel.x = bat->vel.y = bat->vel.z = lbl_803CC728;
        PSMTXMultVec(bat->mtx, &bat->ends[0], &a);
        PSMTXMultVec(bat->mtx, &bat->ends[1], &b);
        PSVECSubtract(&a, &b, &a);
        half = lbl_803CC72C * (f32)sin(a.y / PSVECMag(&a));
        sn = sin(half);
        cs = cos(half);
        up.x = lbl_803CC728;
        up.y = lbl_803CC75C;
        up.z = lbl_803CC728;
        PSVECCrossProduct(&up, &a, &a);
        PSVECScale(&a, sn / PSVECMag(&a), (Vec*)&q2);
        q2.w = cs;
        PSMTXQuat(m3, &q2);
        PSMTXConcat(m3, bat->mtx, m3);
        PSMTXCopy(m3, bat->mtx);
    }
}
#endif

// .text:0x80039A4C size:0x5C
void fn_80039A4C(void) {
    lbl_800F79B8.state = -1;
    lbl_803CBCA2[0] = 0;
    memset(lbl_800F79A0, 0, sizeof(Vec));
    lbl_803CB818 = -1;
    lbl_803CB820 = -1;
    lbl_803CBCA1 = 0;
}

extern u8 lbl_800F7A40[];

extern u8 lbl_8023DD80[];

// GetUITexture, size:0xC
void* GetUITexture(void) {
    return lbl_8023DD80;
}

// fn_80039AB4, size:0xC
void* fn_80039AB4(void) {
    return lbl_800F7A40;
}
