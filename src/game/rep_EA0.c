#include "game/rep_EA0.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#include "static/GameSettings.h"
#include "static/Camera.h"
#include "game/rep_D0.h"                // checkCollision
#include "game/rep_1838.h"              // angle helpers
#include "game/rep_3F60.h"              // fn_3_168FA0
#include "main/file_80008E00.h"         // lbl_80366158
#include "main/file_80011640.h"         // lbl_8036E548 (CharMgr), fn_8001D148
#include "main/file_8004207C.h"         // lbl_800E8754
#include "main/file_8004C5F8.h"         // fn_80052694, fn_80052734
#include "main/file_80069BDC.h"         // lbl_803CC1B8
#include "Dolphin/gx.h"
#include "Dolphin/OS/OSCache.h"
#include "stl/mem.h"
#include "stl/math.h"

extern u8 lbl_803CBBC0; // frame buffer in use (0/1)
extern void fn_800A7D4C(s32 layer, void* node);

// The original keeps these as separate statics that the compiler addresses through one
// pooled base, so they are modelled as one struct here. The ones that are also
// accessed through their own symbol are kept separate.
extern RepTrailWork lbl_3_bss_200;
extern TexImage* lbl_3_bss_204; // trail texture (NULL: untextured)
extern s32 lbl_3_bss_169C;      // never read in this file
extern u8 lbl_3_data_6820[16]; // lbl_8036E548.trail index per lbl_3_common_bss_32724.trailType
extern f32 lbl_3_data_6830[2];
extern f32 lbl_3_data_6838[2];
extern f32 lbl_3_data_6840[2];
extern TrailShadowData lbl_3_data_6848;
extern BallTrailParams lbl_3_data_6880[12];
extern TrailCharData lbl_3_data_6940;
extern TrailNode lbl_3_data_69A0[2];
extern f32 lbl_803CB740[];
extern TrailHudView lbl_3_common_bss_32724;
extern TrailPauseView lbl_3_common_bss_34C90;
extern TrailFadeView lbl_3_common_bss_35154;
extern TrailStadiumView lbl_3_common_bss_350E4;
extern TrailFielder g_Fielders[9];

#define TRAIL_TASK ((TrailTask*)lbl_803CC1B8)

// Ball/shadow model scales by trail type, stored right after charSizeMultipliers in main.dol.
#define TRAIL_SCALES ((f32(*)[3])charSizeMultipliers[NUM_CHOOSABLE_CHARACTERS]) // TODO type

// .text:0x0006750C size:0xAC mapped:0x806A65A0
void fn_3_6750C(TexArchive* archive) {
    BallTrailParams* p = &lbl_3_data_6880[1];
    s32 i;
    for (i = 0; i < 11; i++, p++) {
        p->tex.image = &archive->entries[p->tex.index];
        if (0.0f == p->widthRatio) {
            p->widthRatio = 1.0f;
        } else {
            p->widthRatio = p->widthRatio / p->width;
        }
        p->length = p->length * 60 / 100;
        if (p->length < 2) {
            p->length = 2;
        }
    }
    lbl_3_bss_169C = 0;
}

// .text:0x000675B8 size:0x68 mapped:0x806A664C
void fn_3_675B8(u16 frames) {
    RepTrailWork* w = &lbl_3_bss_200;
    if (frames == 0) {
        lbl_3_common_bss_32724.trailActive = 0;
        w->alpha = 0.0f;
        return;
    }
    w->delay = frames;
    w->alphaStep = w->alpha / (f32)frames;
}

// .text:0x00067620 size:0x298 mapped:0x806A66B4
void fn_3_67620(s32 type, u16 frames) {
    return;
}

// .text:0x000678B8 size:0x190 mapped:0x806A694C
void fn_3_678B8(void) {
    return;
}

// .text:0x00067A48 size:0x1EC mapped:0x806A6ADC
void fn_3_67A48(void) {
    return;
}

// .text:0x00067C34 size:0x2BC mapped:0x806A6CC8
void fn_3_67C34(TrailNode* node) {
    return;
}

// Builds the trail vertices from the position history. Returns which way the trail
// faces the camera (-1/1), which picks the strip draw order.
// .text:0x00067EF0 size:0x700 mapped:0x806A6F84
s32 fn_3_67EF0(VecQueue* queue, s32 maxPoints, Vec* positions, u32* colors, u32 color, Vec* capPositions,
               u32* capColors, Vec* dir, f32 width) {
    return 0;
}

// Picks the trail type for the current pitch / hit.
// .text:0x000685F0 size:0x5C4 mapped:0x806A7684
void fn_3_685F0(void) {
    return;
}

// Spins the ball model.
// .text:0x00068BB4 size:0x548 mapped:0x806A7C48
void fn_3_68BB4(void) {
    if (lbl_80366158._28 != 0 && lbl_3_common_bss_32724.trailType != 7 && lbl_3_common_bss_32724.trailType != 8) {
        return;
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
        if (g_Minigame.GameMode_MiniGame == 1) {
            if (g_Pitcher.pitcherActionState == 3) {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw += 50;
            } else {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
            }
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        } else if (lbl_3_common_bss_32724.trailType == 9 || lbl_3_common_bss_32724.trailType == 10) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw += 300;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch += 100;
        } else if (lbl_3_common_bss_32724.trailType == 7 || lbl_3_common_bss_32724.trailType == 8) {
            if (g_Pitcher.bulletPitchStageCode == 1) {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw =
                    radToShortAngle(3.1415927f + (6.2831855f - g_Pitcher.bulletPitchLoopAngleRadians));
            } else {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
            }
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        } else if (lbl_3_common_bss_32724.trailType == 5 || lbl_3_common_bss_32724.trailType == 6) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
            if (g_Pitcher.handedness) {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch += 200;
            } else {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch -= 200;
            }
        } else if (lbl_3_common_bss_32724.trailType == 11 || lbl_3_common_bss_32724.trailType == 12) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        } else {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw -= 600;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
        if (g_Minigame.GameMode_MiniGame == 1) {
            if (g_Ball.AtBat_ContactResult == 0) {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw += (s32)(400.0f * g_Ball.ballVelocity);
            } else {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw -= (s32)(400.0f * g_Ball.ballVelocity);
            }
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        } else if (g_Ball.fielderWBallIndex >= 0) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
        } else if (lbl_3_common_bss_32724.trailType == 9 || lbl_3_common_bss_32724.trailType == 10) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = -(g_Ball.ballTravelAngle - 0x400);
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw += (s32)(200.0f * g_Ball.ballVelocity);
        } else if (lbl_3_common_bss_32724.trailType == 7 || lbl_3_common_bss_32724.trailType == 8) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = fn_3_9FE6C_normalizeAngle(0xC00 - g_Ball.Hit_HorizontalAngle);
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        } else if (lbl_3_common_bss_32724.trailType == 5 || lbl_3_common_bss_32724.trailType == 6) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
            if (g_Batter.batterHand) {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch -= 200;
            } else {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch += 200;
            }
        } else if (lbl_3_common_bss_32724.trailType == 11 || lbl_3_common_bss_32724.trailType == 12) {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        } else {
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
            g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0x800 - g_Ball.ballTravelAngle;
            if (g_Ball.AtBat_ContactResult == 0) {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw += (s32)(400.0f * g_Ball.ballVelocity);
            } else if (g_Ball.ballState == 2 && !g_Ball.thrownBallHasHitGround) {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw += (s32)(800.0f * g_Ball.ballVelocity);
            } else {
                g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw -= (s32)(400.0f * g_Ball.ballVelocity);
            }
        }
    } else {
        g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll = 0;
        g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch = 0;
        g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw = 0;
    }
    g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw =
        fn_3_9FE6C_normalizeAngle(g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw);
    g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch =
        fn_3_9FE6C_normalizeAngle(g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch);
    g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll =
        fn_3_9FE6C_normalizeAngle(g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll);
}

// .text:0x000690FC size:0x70 mapped:0x806A8190
void fn_3_690FC(void) {
    lbl_8036E548.trail[0]._26 = 0;
    lbl_8036E548.trail[1]._26 = 0;
    lbl_8036E548.trail[2]._26 = 0;
    lbl_8036E548.trail[3]._26 = 0;
    lbl_8036E548.trail[5]._26 = 0;
    lbl_8036E548.trail[6]._26 = 0;
    lbl_8036E548.trail[7]._26 = 0;
    lbl_8036E548.trail[8]._26 = 0;
    lbl_8036E548.trail[9]._26 = 0;
    lbl_8036E548.trail[10]._26 = 0;
    lbl_8036E548.trail[12]._26 = 0;
    lbl_8036E548.trail[13]._26 = 0;
}

// .text:0x0006916C size:0x18 mapped:0x806A8200
void fn_3_6916C(void) {
    lbl_3_common_bss_32724.trailType = 0;
    lbl_3_common_bss_32724.trailActive = 0;
}

// Bat shadow.
// .text:0x00069184 size:0x15C mapped:0x806A8218
void fn_3_69184(void) {
    CharTrail* p;
    if (g_Batter.trimmedBat == 1) {
        p = &lbl_8036E548.trail[6];
    } else {
        p = &lbl_8036E548.trail[5];
    }
    p->_26 = 0;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU) {
            return;
        }
        if (g_Practice.practiceLevel != 4 && g_Practice.practiceType_2 != 1) {
            return;
        }
    } else if (g_Batter.easyBatting == 0) {
        return;
    }
    if (g_Stats.replayInd != 0) {
        return;
    }
    if (g_GameLogic.gameStatus != GAME_STATUS_DEFAULT && g_GameLogic.gameStatus != GAME_STATUS_AT_BAT) {
        return;
    }
    if (g_GameLogic.sceneID != SCENE_ID_AT_BAT) {
        return;
    }
    p->_26 = 1;
    if (g_Batter.batterHand != 0) {
        p->_04[0] = -g_Batter.batPosition2.x;
        p->_04[4] = 3.1415927f;
    } else {
        p->_04[0] = g_Batter.batPosition2.x;
        p->_04[4] = 0.0f;
    }
    p->_04[2] = g_Batter.batPosition2.z + lbl_3_data_6848.shadowOffset[1];
    p->_04[1] = lbl_3_data_6848.shadowOffset[0];
}

// Ball landing marker.
// .text:0x000692E0 size:0x318 mapped:0x806A8374
void fn_3_692E0(void) {
    VecSrcDst ray;
    CollisionStruct coll;
    CharTrail* marker;
    s32 idx;
    u32 hit;
    f32 height;
    f32 rot;
    f32 scale;

    lbl_8036E548.trail[2]._26 = 0;
    lbl_8036E548.trail[3]._26 = 0;
    if (g_Stats.replayInd != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        return;
    }
    if (g_Minigame.GameMode_MiniGame != 0) {
        return;
    }
    if (g_Ball.pauseBallMovementWhenInPlant != 0 || g_Ball.frameCountdownAfterLeavingPlant != 0) {
        return;
    }
    if (g_Ball.deadBallReason != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE &&
        lbl_800E8754.port[g_GameLogic.teams[g_GameLogic.teamFielding]]._4 == 0) {
        return;
    }
    if (g_GameLogic.sceneID != SCENE_ID_LIVE_BALL) {
        return;
    }
    if (g_FieldingLogic._107 != 0) {
        return;
    }
    if (g_Ball.AtBat_ContactResult != 0) {
        return;
    }
    if (g_Ball.maxYOfHit < 2.0f) {
        return;
    }
    if (g_Ball.currentStarSwing2 == 11 || g_Ball.currentStarSwing2 == 12) {
        return;
    }
    if (g_Ball.warioWaluGarlicIsActive != 0) {
        return;
    }

    if (g_FieldingLogic._144 != 0) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE &&
            (g_Practice.practiceType_2 == 1 || g_Practice.practiceLevel == 4)) {
            idx = 2;
        } else {
            idx = 3;
        }
    } else {
        idx = 2;
    }
    marker = &lbl_8036E548.trail[idx];
    marker->_26 = 1;
    ray.src.x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    ray.src.y = -1.0f;
    ray.src.z = g_Ball.physicsSubstruct.hitLandingSpotDistFromHome;
    ray.dst.x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    ray.dst.y = 1.0f;
    ray.dst.z = g_Ball.physicsSubstruct.hitLandingSpotDistFromHome;
    hit = checkCollision(&ray, &coll, 0, FALSE);
    if (hit == BALL_COLLISION_TYPE_GRASS || hit == BALL_COLLISION_TYPE_DIRT ||
        (u32)(hit - BALL_COLLISION_TYPE_ROUGH_TERRAIN) <= 1 || hit == 0x32) {
        marker->_04[1] = coll.position.y - 0.06f;
    } else {
        marker->_04[1] = -0.06f;
    }
    marker->_04[0] = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    marker->_04[2] = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
    rot = marker->_04[4];
    height = 30.0f - g_Ball.AtBat_Contact_BallPos.y;
    if (height < 1.0f) {
        height = 1.0f;
    }
    height *= 0.003f;
    marker->_04[4] = fn_3_9FEA8(rot + height);
    scale = LinearInterpolateToNewRange((f32)g_Ball.framesUntilBallHitsGround, 0.0f, 120.0f, lbl_3_data_6840[0],
                                        lbl_3_data_6840[1]);
    fn_8001D148(idx, scale, scale, scale);
}

// Ball shadow.
// .text:0x000695F8 size:0x1D4 mapped:0x806A868C
void fn_3_695F8(s32 flag) {
    CharTrail* p = lbl_8036E548.trail;
    s32 t;
    p[1]._26 = 0;
    p[1]._04[0] = g_Ball.AtBat_Contact_BallPos.x;
    p[1]._04[1] = -g_Ball.physicsSubstruct.twoFrameLookback[1] - 0.04f;
    p[1]._04[2] = g_Ball.AtBat_Contact_BallPos.z;
    if (g_Ball.warioWaluGarlicIsActive != 0) {
        if (g_Ball.framesSinceHit & 1) {
            p[1]._04[0] = g_Ball.warioStarHitCoords[2].x;
            p[1]._04[2] = g_Ball.warioStarHitCoords[2].z;
        }
    } else if (g_Pitcher.warioWaluStarAnimationStage == 1 && (g_Pitcher.pitchTotalTimeCounter & 1)) {
        p[1]._04[0] = g_Pitcher.ballCurrentPosition.x + g_Pitcher.pitchX_parabolicAdjustment -
                      g_Pitcher.starPitchPositionAdjustment.x;
    }
    if (g_Ball.fielderActionOccuring != 0) {
        p[1]._04[0] = g_Ball.fielderActionCatchCoords.x;
        p[1]._04[1] = -g_Ball.fielderActionCatchCoords.y;
        p[1]._04[2] = g_Ball.fielderActionCatchCoords.z;
    }
    if (g_Ball.hitNoteBlockInd != 0) {
        p[1]._04[0] = lbl_3_common_bss_350E4.noteBlockPos.x;
        p[1]._04[2] = lbl_3_common_bss_350E4.noteBlockPos.z;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        fn_8001D148(1, lbl_3_data_6830[1], 1.0f, lbl_3_data_6830[1]);
    } else {
        fn_8001D148(1, lbl_3_data_6830[0], 1.0f, lbl_3_data_6830[0]);
    }
    if (flag != 0) {
        t = g_Ball.collisionCode & 0x7F;
        if (t == 1 || t == 6 || (u32)(t - 9) <= 1 || (t >= 0x70 && t < 0x79)) {
            p[1]._26 = 1;
        }
    }
}

// Updates the ball model, its trail and the shadows each frame.
// .text:0x000697CC size:0x994 mapped:0x806A8860
void fn_3_697CC(void) {
    return;
}
