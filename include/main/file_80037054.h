#ifndef __MAIN_FILE_80037054_H__
#define __MAIN_FILE_80037054_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// Rigid body (bat / stick) simulated with a fixed sub-step.
typedef struct RigidBody {
    /*0x000*/ Vec p0;         // end point A (body space)
    /*0x00C*/ Vec p1;         // end point B (body space)
    /*0x018*/ Vec d;          // p0 - p1
    /*0x024*/ f32 mass;
    /*0x028*/ f32 invMass;
    /*0x02C*/ f32 radius;
    /*0x030*/ Vec inertia;    // diagonal inertia tensor
    /*0x03C*/ Vec invInertia;
    /*0x048*/ f32 dt;         // (1/60) / steps
    /*0x04C*/ s32 steps;
    /*0x050*/ f32 unk50;
    /*0x054*/ f32 unk54;
    /*0x058*/ Mtx world;      // body -> world
    /*0x088*/ Mtx rot;        // from quat
    /*0x0B8*/ Mtx invRot;
    /*0x0E8*/ Vec pos;
    /*0x0F4*/ Quaternion quat;
    /*0x104*/ Vec force;
    /*0x110*/ Vec forceLocal;
    /*0x11C*/ Vec vel;
    /*0x128*/ Vec velLocal;
    /*0x134*/ Vec torque;
    /*0x140*/ Vec angVel;
    /*0x14C*/ u8 unk14C;
    /*0x14D*/ u8 unk14D;
    /*0x14E*/ s8 axis;
    /*0x14F*/ u8 _14F;
    /*0x150*/ f32 unk150;
} RigidBody; // size 0x154

// Parameters passed to the rigid body integrators.
typedef struct RigidBodyParams {
    /*0x00*/ s32 unk0;
    /*0x04*/ s32 unk4;
    /*0x08*/ s32 unk8;
    /*0x0C*/ s32 unkC;
    /*0x10*/ s32 unk10;
    /*0x14*/ s32 unk14;
    /*0x18*/ s32 unk18;
    /*0x1C*/ s32 unk1C;
    /*0x20*/ s32 unk20;
} RigidBodyParams;

// One mass point of a verlet rope.
typedef struct RopeNode {
    /*0x00*/ f32 mass;
    /*0x04*/ f32 invMass;
    /*0x08*/ f32 floorY;
    /*0x0C*/ Vec pos;
    /*0x18*/ Vec prevPos;
    /*0x24*/ Vec vel;
    /*0x30*/ Vec force;
    /*0x3C*/ u32 fixed;
} RopeNode; // size 0x40

typedef struct RopeParams {
    /*0x00*/ f32 restLen;
    /*0x04*/ f32 bounce;
    /*0x08*/ f32 springK;
    /*0x0C*/ f32 damping;
    /*0x10*/ f32 friction;
    /*0x14*/ f32 drag;
    /*0x18*/ f32 dt;
    /*0x1C*/ f32 dtSq;
    /*0x20*/ s32 iterations;
    /*0x24*/ f32 invTwoDt;
} RopeParams;

// Bat swing simulation state (lbl_800F79B8).
typedef struct BatSim {
    /*0x00*/ Mtx mtx;
    /*0x30*/ Vec angVel;
    /*0x3C*/ Vec vel;
    /*0x48*/ Vec tip;
    /*0x54*/ Vec ends[2];
    /*0x6C*/ Vec inertia;
    /*0x78*/ s32 state;
    /*0x7C*/ s32 jointBase;
    /*0x80*/ s32 joint;
    /*0x84*/ u32 _84;
} BatSim;

typedef struct ModelJoint {
    /*0x00*/ u8 _00[0xEC];
    /*0xEC*/ MtxPtr mtx;
} ModelJoint;

typedef struct Model {
    /*0x00*/ u8 _00[0x18];
    /*0x18*/ ModelJoint** joints;
} Model;

typedef struct CharModelObj {
    /*0x000*/ u8 _000[0x162];
    /*0x162*/ u16 jointMap[0x79];
    /*0x254*/ u8 _254;
    /*0x255*/ s8 slot;
} CharModelObj;

// Task queued by fn_80037AA0 to attach a rigid body to a character joint.
typedef struct JointAttachTask {
    /*0x00*/ void (*func)(struct JointAttachTask*);
    /*0x04*/ struct JointAttachTask* prev;
    /*0x08*/ struct JointAttachTask* next;
    /*0x0C*/ u8 _0C[0x14 - 0x0C];
    /*0x14*/ void (*callback)(void);
    /*0x18*/ RigidBody* body;
    /*0x1C*/ void* anim;
    /*0x20*/ Vec pos;
    /*0x2C*/ Quaternion quat;
    /*0x3C*/ u16 joint;
    /*0x3E*/ u8 charIdx;
} JointAttachTask;


void fn_80037054(RigidBody* rb, RigidBodyParams* params);
void fn_8003731C(RigidBody* rb, RigidBodyParams* params);
void fn_80037768(RigidBody* rb, s8 axis, s32 steps, f32 len, f32 frac, f32 radius, f32 mass);
void fn_80037964(JointAttachTask* task);
void fn_80037984(JointAttachTask* task);
void fn_80037AA0(RigidBody* body, s32 charIdx, void (*callback)(void), u16 joint, void* anim);
void fn_80037B18(RigidBody* rb, Vec* force);
void fn_80037BAC(RigidBody* rb);
void fn_8003819C(RigidBody* rb);
MtxPtr fn_800383BC(RigidBody* rb);
void fn_80038418(RigidBody* rb, Vec* pos, Quaternion* quat, Vec* prevPos, Quaternion* prevQuat);
void fn_800385F0(RigidBody* rb, f32 len, f32 frac, f32 radius, f32 mass);
void fn_800387B0(RopeParams* p, RopeNode* nodes, s32 count, Vec* gravity);
void fn_80038B48(RopeParams* p, RopeNode* nodes, s32 count, Vec* gravity);
RopeNode* fn_80038CD0(s32 count, f32* spacing, RopeNode* nodes, f32 floorY, f32 mass);
void fn_80038E2C(RopeParams* p);
void fn_80038EC4(CharModelObj* obj, Model** model, s32 joint);
void fn_80038F08(CharModelObj* obj, Model* model, u8 joint);
void fn_80039310(BatSim* bat, f32 floorY, f32 minEnergy);
void fn_80039A4C(void);

void* GetUITexture(void);

void* fn_80039AB4(void);

#endif
