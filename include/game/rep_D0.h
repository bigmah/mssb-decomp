#ifndef __GAME_rep_D0_H_
#define __GAME_rep_D0_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXTypes.h"

typedef struct _VecSrcDst {
    Vec src, dst;
} VecSrcDst;

typedef struct _CollisionStruct {
    Vec position, normal;
} CollisionStruct;

typedef struct _AABB_Box {
    Vec a, b;
} AABB_Box;

typedef struct _CollisionBox {
    AABB_Box* boundingBox;
} CollisionBox;

struct ActorLayoutFile;

// Sky/backdrop object drawn per camera (two copies, indexed by lbl_803CBBC0).
typedef struct StadiumSkyObj {
    /*0x00*/ u32 link; // draw-list link (fn_800A7D4C)
    /*0x04*/ void (*func)(struct StadiumSkyObj* obj);
    /*0x08*/ Mtx model;
    /*0x38*/ Mtx view;
    /*0x68*/ struct ActorLayoutFile* layout; // actor layout drawn by fn_3_3638
    /*0x6C*/ s32 camera;
} StadiumSkyObj; // size: 0x70

// Per-scene screen effect settings copied into lbl_803C5090.
typedef struct StadiumScreenFx {
    /*0x0*/ f32 scale;
    /*0x4*/ f32 jitterX;
    /*0x8*/ f32 jitterY;
    /*0xC*/ u8 flags;
    /*0xD*/ u8 alpha;
    /*0xE*/ u16 lines;
} StadiumScreenFx; // size: 0x10

// Fog settings (fn_3_5BF0 uses the first entry; color.a is the GX fog type).
typedef struct StadiumFog {
    /*0x0*/ GXColor color;
    /*0x4*/ f32 start;
    /*0x8*/ f32 end;
} StadiumFog; // size: 0xC

// Per-stadium visual settings (fog, screen effects, sky speed); copied from lbl_3_data_23C.
typedef struct StadiumVisual {
    /*0x00*/ StadiumFog fog[3]; // fn_3_5BF0 uses fog[0]
    /*0x24*/ StadiumScreenFx screenFx[3]; // scenes 1, 2, other
    /*0x54*/ f32 skySpeed;
    /*0x58*/ GXColor clearColor; // fn_3_35F0
    /*0x5C*/ u8 _5C;
    /*0x5D*/ u8 _5D; // passed to fn_8003AE5C
    /*0x5E*/ u8 _5E[2];
} StadiumVisual; // size: 0x60

// g_UNK_StadiumDetails: the loaded stadium (collision, sky models, visual settings).
typedef struct _UNK_StadiumCollision {
    /*0x000*/ void* _00; // TexImage entries of the stadium texture archive (rep_1C0)
    /*0x004*/ void* _04; // stadium texture archive; effect textures (fn_3_BC6D8)
    /*0x008*/ StadiumSkyObj sky[7][2]; // per camera view, two frame buffers
    /*0x628*/ u8 _628[0x70A - 0x628];
    /*0x70A*/ s16 numCollisionBoxes;
    /*0x70C*/ CollisionBox* pCollisionBoxes;
    /*0x710*/ f32 skyAngle;
    /*0x714*/ StadiumVisual visual;
    /*0x774*/ u8 _774; // 1 while the live-ball scene is shown (fn_3_1CE90)
    /*0x775*/ u8 _775[3];
    /*0x778*/ CollisionBox* pCollisionBoxes2;
    /*0x77C*/ s16 numCollisionBoxes2;
    /*0x77E*/ u8 _77E[2];
} UNK_StadiumCollision; // size: 0x780

typedef struct _TriangleCollisionStruct {
    /*0x00*/ Mtx mtx1;
    /*0x30*/ Mtx mtx2;
    /*0x60*/ Vec normal;
    /*0x6C*/ f32 distance; // unsure
    /*0x70*/ f32 collisionDistance; // unsure
    /*0x72*/ E(u16, BALL_COLLISION_TYPE) collisionType;
} TriangleCollisionStruct; // size: 0x74

typedef struct _CollisionTriangle{
    /*0x00*/ Vec trianglePoint;
    /*0x0C*/ E(u16, BALL_COLLISION_TYPE) collisionType;
    // pad 2 bytes
} CollisionTriangle; // size:0x10

typedef struct _TriangleGroup {
    /*0x00*/ u8 _0;
    /*0x01*/ bool isTriangleList;
    /*0x02*/ u16 count;
    /*0x04*/ CollisionTriangle tris[];
} TriangleGroup; // size: at least 4, expandable

extern UNK_StadiumCollision g_UNK_StadiumDetails; 

typedef enum _BALL_COLLISION_TYPE {
    BALL_COLLISION_TYPE_NONE,
    BALL_COLLISION_TYPE_GRASS,
    BALL_COLLISION_TYPE_WALL,
    BALL_COLLISION_TYPE_STRUCTURE,
    BALL_COLLISION_TYPE_FOUL_LINE,
    BALL_COLLISION_TYPE_UNCLIMBABLE_WALL,
    BALL_COLLISION_TYPE_DIRT,
    BALL_COLLISION_TYPE_PIT_WALL,
    BALL_COLLISION_TYPE_PIT,
    BALL_COLLISION_TYPE_ROUGH_TERRAIN,
    BALL_COLLISION_TYPE_WATER,
    BALL_COLLISION_TYPE_CHOMP_HAZARD,
    BALL_COLLISION_TYPE_FOUL = 0x80,
} BALL_COLLISION_TYPE;

BALL_COLLISION_TYPE checkCollision(VecSrcDst* inVec, CollisionStruct* outCollision, int collisionCheckType, BOOL useBallCoords);
BALL_COLLISION_TYPE checkStatiumHazardCollisions(VecSrcDst* inVec, CollisionStruct* outCollision, Vec* v);
BALL_COLLISION_TYPE didCollideWithBoundingBoxes(VecSrcDst* inVec, CollisionStruct* outCollision, CollisionBox* boxes,
                                                s16 boxCount);
int checkTriangleCollisions(TriangleCollisionStruct* collisionData, TriangleGroup* TriangleGroup);

#endif // !__GAME_rep_D0_H_
