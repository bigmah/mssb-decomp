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
void fn_80037054(RigidBody* rb, RigidBodyParams* params) {
    return;
}

// .text:0x8003731C size:0x44C
void fn_8003731C(RigidBody* rb, RigidBodyParams* params) {
    return;
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
void fn_80037BAC(RigidBody* rb) {
    return;
}

// .text:0x8003819C size:0x220
void fn_8003819C(RigidBody* rb) {
    return;
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
    return;
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
    inertia = mass * (radius * radius * lbl_803CC740 + len * len / lbl_803CC744);
    rb->inertia.z = inertia;
    rb->inertia.x = inertia;
    rb->inertia.y = lbl_803CC72C * (radius * (mass * radius));
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
void fn_800387B0(RopeParams* p, RopeNode* nodes, s32 count, Vec* gravity) {
    return;
}

// .text:0x80038B48 size:0x188
void fn_80038B48(RopeParams* p, RopeNode* nodes, s32 count, Vec* gravity) {
    Vec accel;
    Vec g;
    Vec step;
    Vec next;
    RopeNode* node;
    s32 iter;
    s32 i;
    f32 dtSq;
    f32 damp;
    f32 under;

    PSVECScale(gravity, p->dt, &g);
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
                    node->prevPos.y = node->prevPos.y - (node->prevPos.y - node->floorY) * p->bounce;
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
void fn_80038F08(CharModelObj* obj, Model* model, u8 joint) {
    return;
}

// .text:0x80039310 size:0x73C
void fn_80039310(BatSim* bat, f32 floorY, f32 minEnergy) {
    return;
}

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
