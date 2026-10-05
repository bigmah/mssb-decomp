#include "game/rep_D0.h"
#include "header_rep_data.h"
#include "Dolphin/stl.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_1D58.h"



#pragma dont_inline on
Vec lbl_3_data_1F8 = {0.0f, 1.0f, 0.0f};
Vec lbl_3_data_204 = {0.0f, 0.0f, 0.0f};
extern void makeLookAtMatrix(TriangleCollisionStruct*, VecSrcDst*, Vec*, Vec*);

// .text:0x000008D4 size:0x40
BALL_COLLISION_TYPE fn_3_8D4(VecSrcDst* inVec, CollisionStruct* outCollision) {
    if (g_UNK_StadiumDetails.pCollisionBoxes2 != NULL) {
        return didCollideWithBoundingBoxes(inVec, outCollision, g_UNK_StadiumDetails.pCollisionBoxes2,
                                           g_UNK_StadiumDetails.numCollisionBoxes2);
    }
    return BALL_COLLISION_TYPE_NONE;
}

// .text:0x00000914 size:0x158 mapped:0x8063F9A8
BALL_COLLISION_TYPE checkCollision(VecSrcDst* inVec, CollisionStruct* outCollision, int collisionCheckType,
                                   BOOL useBallCoords) {
    VecSrcDst p;
    int* v;
    BALL_COLLISION_TYPE ret = 0;
    if (collisionCheckType) {
        if (useBallCoords && (g_d_GameSettings.StadiumID == STADIUM_ID_WARIO_PALACE ||
                              g_d_GameSettings.StadiumID == STADIUM_ID_YOHSI_PARK ||
                              g_d_GameSettings.StadiumID == STADIUM_ID_DK_JUNGLE)) {
            memcpy(&p.dst, &g_Ball.AtBat_Contact_BallPos, sizeof(p.dst));
            memcpy(&p.src, &g_Ball.pastCoordinates[4], sizeof(p.src));
            p.src.y *= -1.f;
            p.dst.y *= -1.f;
        } else {
            memcpy(&p, inVec, sizeof(p));
        }
        ret = checkStatiumHazardCollisions(&p, outCollision, (Vec*)&v);
        if (ret) {
            if (collisionCheckType == 2 && (ret & BALL_COLLISION_TYPE_FOUL)) {
                ret = BALL_COLLISION_TYPE_NONE;
            } else {
                processStadiumObjectFunction(g_d_GameSettings.StadiumID, v, ret, outCollision);
            }
        }
    }
    if (collisionCheckType != 3) {
        ret = didCollideWithBoundingBoxes(inVec, outCollision, g_UNK_StadiumDetails.pCollisionBoxes,
                                          g_UNK_StadiumDetails.numCollisionBoxes);
    }
    return ret;
}

// .text:0x00000A6C size:0x384 mapped:0x8063FB00
BALL_COLLISION_TYPE checkStatiumHazardCollisions(VecSrcDst* inVec, CollisionStruct* outCollision, Vec* v) {
    return;
}

#pragma dont_inline off
extern f32 lbl_3_rodata_124;
extern f64 lbl_3_rodata_128;
extern f64 lbl_3_rodata_130;
extern f64 lbl_3_rodata_138;

static inline f32 sqrtLocal(f32 x) {
    if (x > lbl_3_rodata_124) {
        f64 xd = (f64)x;
        f64 guess = __frsqrte(xd);
        guess = lbl_3_rodata_128 * guess * (lbl_3_rodata_130 - guess * guess * xd);
        guess = lbl_3_rodata_128 * guess * (lbl_3_rodata_130 - guess * guess * xd);
        guess = lbl_3_rodata_128 * guess * (lbl_3_rodata_130 - guess * guess * xd);
        return (f32)(xd * guess);
    } else if (x < lbl_3_rodata_138) {
        return NAN;
    } else if (isnan(x)) {
        return NAN;
    } else {
        return x;
    }
}

// .text:0x00000DF0 size:0x2F0 mapped:0x8063FE84
BALL_COLLISION_TYPE didCollideWithBoundingBoxes(VecSrcDst* inVec, CollisionStruct* outCollision, CollisionBox* boxes,
                                                s16 boxCount) {
    u8 flags[256];
    TriangleCollisionStruct tc;
    Vec d[4];
    Mtx m;
    int n;
    int i;
    u32 allOut;
    AABB_Box* bb;
    u8* fp;
    CollisionBox* cb;
    f32 dist;
    n = boxCount;
    bb = boxes->boundingBox;
    memset(flags, 1, n);
    i = n;
    fp = flags;
    allOut = 1;
    do {
        PSVECSubtract(&inVec->src, &bb->a, &d[0]);
        PSVECSubtract(&bb->b, &inVec->src, &d[1]);
        PSVECSubtract(&inVec->dst, &bb->a, &d[2]);
        PSVECSubtract(&bb->b, &inVec->dst, &d[3]);
        if (!((((*(s32*)&d[0].x & *(s32*)&d[2].x) | (*(s32*)&d[1].x & *(s32*)&d[3].x)) & 0x80000000)) &&
            !((((*(s32*)&d[0].y & *(s32*)&d[2].y) | (*(s32*)&d[1].y & *(s32*)&d[3].y)) & 0x80000000)) &&
            !((((*(s32*)&d[0].z & *(s32*)&d[2].z) | (*(s32*)&d[1].z & *(s32*)&d[3].z)) & 0x80000000))) {
            allOut = 0;
            *fp = 0;
        }
        fp++;
        i--;
        bb++;
    } while (i != 0);
    if (allOut != 0) {
        return BALL_COLLISION_TYPE_NONE;
    }
    makeLookAtMatrix(&tc, inVec, &lbl_3_data_1F8, &inVec->dst);
    dist = sqrtLocal(PSVECSquareDistance(&inVec->dst, &inVec->src));
    tc.distance = dist;
    fp = flags;
    cb = boxes + 1;
    tc.collisionDistance = dist;
    tc.collisionType = 0;
    do {
        if (*fp++ == 0) {
            checkTriangleCollisions(&tc, (TriangleGroup*)cb->boundingBox);
        }
        n--;
        cb++;
    } while (n != 0);
    if (tc.collisionType != 0) {
        PSMTXInverse((f32(*)[4])&tc, m);
        lbl_3_data_204.z = -tc.collisionDistance;
        PSMTXMultVec(m, &lbl_3_data_204, &outCollision->position);
        PSMTXTranspose((f32(*)[4])&tc, m);
        PSMTXMultVec(m, &tc.normal, &outCollision->normal);
        PSVECNormalize(&outCollision->normal, &outCollision->normal);
        return tc.collisionType;
    }
    return BALL_COLLISION_TYPE_NONE;
}

// .text:0x000010E0 size:0x3C4 mapped:0x80640174
bool checkTriangleCollisions(TriangleCollisionStruct* collisionData, TriangleGroup* _triangleGroup) {
#define O_GROUP ((TriangleGroup*)_triangleGroup)
#define O_TRI ((CollisionTriangle*)_triangleGroup)

    Vec tri[3];
    Vec dist[3];
    u32 remainingTriangles;
    u32 didVecPassTriangle;
    u32 isBackwardsTriangle;

    bool ret = false;
    f32 d;
    while (true) {
        bool isList;
        remainingTriangles = O_GROUP->count;
        if (remainingTriangles == 0)
            break;

        isList = O_GROUP->isTriangleList;
        // this should be reassigned to r24? but they're different types?
        // i hope it's not a union
        O_TRI = O_GROUP->tris;
        if (!isList) {
            // grou of 3 verts to make up a triangle
            do {
                MTXMultVec(collisionData->mtx1, &O_TRI[0].trianglePoint, &tri[00]);
                MTXMultVec(collisionData->mtx1, &O_TRI[1].trianglePoint, &tri[01]);
                MTXMultVec(collisionData->mtx1, &O_TRI[2].trianglePoint, &tri[02]);
                didVecPassTriangle = tri[00].x * tri[01].y - tri[01].x * tri[00].y >= 0;
                didVecPassTriangle &= tri[01].x * tri[02].y - tri[02].x * tri[01].y >= 0;
                didVecPassTriangle &= tri[02].x * tri[00].y - tri[00].x * tri[02].y >= 0;
                if (didVecPassTriangle) {
                    VECSubtract(&tri[01], &tri[00], &dist[0]);
                    VECSubtract(&tri[02], &tri[01], &dist[1]);
                    VECCrossProduct(&dist[0], &dist[1], &dist[2]);
                    d = -VECDotProduct(&dist[2], &tri[00]) / dist[2].z;
                    if (d >= 0.f && collisionData->collisionDistance > d) {
                        collisionData->collisionDistance = d;
                        ret = true;
                        collisionData->collisionType = O_TRI[2].collisionType;
                        collisionData->normal = dist[2];
                    }
                }
                O_TRI += 3;
            } while (--remainingTriangles);
        } else {
            // the first 3 verts describe a triangle, after that each new vert replaces the oldest vert to make a
            // triangle fan
            isBackwardsTriangle = false;
            MTXMultVec(collisionData->mtx1, &O_TRI[0].trianglePoint, &tri[00]);
            MTXMultVec(collisionData->mtx1, &O_TRI[1].trianglePoint, &tri[01]);
            O_TRI += 2;
            do {
                MTXMultVec(collisionData->mtx1, &O_TRI->trianglePoint, &tri[02]);
                dist[0].x = tri[00].x * tri[01].y - tri[01].x * tri[00].y;
                dist[0].y = tri[01].x * tri[02].y - tri[02].x * tri[01].y;
                dist[0].z = tri[02].x * tri[00].y - tri[00].x * tri[02].y;

                if (isBackwardsTriangle) {
                    didVecPassTriangle = dist[0].x <= 0.f & dist[0].y <= 0.f & dist[0].z <= 0.f;
                } else {
                    didVecPassTriangle = dist[0].x >= 0.f & dist[0].y >= 0.f & dist[0].z >= 0.f;
                }

                if (didVecPassTriangle) {
                    VECSubtract(&tri[01], &tri[00], &dist[0]);
                    VECSubtract(&tri[02], &tri[01], &dist[1]);
                    VECCrossProduct(&dist[0], &dist[1], &dist[2]);
                    d = -VECDotProduct(&dist[2], &tri[00]) / dist[2].z;
                    if (d >= 0.f && collisionData->collisionDistance > d) {
                        collisionData->collisionDistance = d;
                        collisionData->collisionType = O_TRI[0].collisionType;
                        if (!isBackwardsTriangle) {
                            collisionData->normal = dist[2];
                        } else {
                            collisionData->normal.x = -dist[2].x;
                            collisionData->normal.y = -dist[2].y;
                            collisionData->normal.z = -dist[2].z;
                        }
                        ret = true;
                    }
                }
                tri[00] = tri[01];
                tri[01] = *&tri[02];
                isBackwardsTriangle ^= 1;
                O_TRI++;
            } while (--remainingTriangles);
        }
    }

    return ret;
}
