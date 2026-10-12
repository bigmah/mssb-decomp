#include "game/rep_F80.h"
#define REP_HEADER_FN repHeader_F80
#include "header_rep_inline.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#include "main/file_80011640.h" // lbl_8036E548 (CharMgr), getAnimRelatedCoordinates

extern f32 game_atan2(f32 x, f32 y);
extern void fn_3_BE174(s32 a, f32 x, f32 y, f32 z);
extern void fn_3_CB344(int who, u8 a);
extern void fn_3_CB234(int who, int a);
extern void fn_3_CB284(int who, s16 a, f32 f);
extern void fn_3_C07A0(void);
extern void fn_3_C1770(int who);
extern void fn_3_C11CC(int who, int a);
extern void fn_3_C1344(s32 who, s32 track, f32 t, f32 t2);
// The original passes a fifth float (k) that fn_3_C1344 ignores; only the matching
// build reproduces that through a cast.
#if NONMATCHING
#define fn_3_C1344_k(who, track, t, t2, k) fn_3_C1344(who, track, t, t2)
#else
#define fn_3_C1344_k(who, track, t, t2, k) ((void (*)(s32, s32, f32, f32, f32))fn_3_C1344)(who, track, t, t2, k)
#endif
extern void fn_3_C0770(void);
extern void fn_3_C07B0(void);
extern void fn_3_BF1AC(void);
extern void fn_3_CABB4(void);
extern void fn_80011578(void);
extern void fn_3_BD4F0(void);
extern void fn_3_BD504(int a, f32 x, f32 y, f32 z);
extern void fn_3_BD6AC(int a, f32 x, f32 y, f32 z);
extern void fn_3_CB1B0(int a, u8 b, int c);

extern RepF80HudView lbl_3_common_bss_32724;
extern RepF80Bss32220 lbl_3_common_bss_32220;
extern RepF80Bss3223C lbl_3_common_bss_3223C;
extern RepF80Bss35154 lbl_3_common_bss_35154;

// .text:0x0006A2A4 size:0x5C mapped:0x806A9338
void fn_3_6A2A4(s8 idx) {
    ActorObject* e = &lbl_8036E548.slots64->objects[idx - 0x1F];
    lbl_3_common_bss_32724.starEffect = 1;
    e->visFlags = 2;
    e->time = 0.0f;
    e->setTime = 1;
    e->unk54 = 1.0f;
    e->setSpeed = 1;
}

// .text:0x0006A300 size:0x100 mapped:0x806A9394
void fn_3_6A300(void) {
    CharActor* actor;
    CharTrail* d;
    if (lbl_3_common_bss_32724.starEffect == 0) {
        return;
    }
    actor = lbl_8036E548.active[9];
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        actor = lbl_8036E548.active[g_Minigame.rosterID];
    }
    {
        s8 t = actor->kind;
        if (t == 0x30) {
            d = &lbl_8036E548.trail[17];
        } else if (t == 0x31) {
            d = &lbl_8036E548.trail[18];
        } else if (t == 0x32) {
            d = &lbl_8036E548.trail[19];
        } else {
            d = &lbl_8036E548.trail[20];
        }
    }
    d->_26 = 1;
    d->_04[0] = actor->pos.x;
    d->_04[1] = -actor->pos.y;
    d->_04[2] = actor->pos.z;
    d->_04[3] = actor->rot.x;
    d->_04[4] = -actor->rot.y;
    d->_04[5] = actor->rot.z;
}

// .text:0x0006A400 size:0x14 mapped:0x806A9494

void fn_3_6A400(void) {
    lbl_3_common_bss_32724.starEffect = 0;
}

// Ball effect while a star pitch / star swing is under way.
// .text:0x0006A414 size:0x428 mapped:0x806A94A8
// NONMATCHING 95%: the framesSinceHit >= 1 argument of fn_3_BD504 is scheduled before the ball
// position loads instead of between them
#if NONMATCHING
void fn_3_6A414(void) {
    if (g_Pitcher.pitchTotalTimeCounter <= 0) {
        if (lbl_3_common_bss_32724.ballEffect != 0) {
            fn_3_BD4F0();
            lbl_3_common_bss_32724.ballEffect = 0;
        }
        return;
    }
    if (g_Pitcher.starPitchType != 0 || g_Pitcher.nonCaptainStarPitchTriggeredType != 0) {
        fn_3_CB1B0(0, g_Pitcher.starPitchType, g_Pitcher.windupCountdownUntilBallReleased);
    }
    if (g_Ball.pitchHangtimeCounter == 1) {
        fn_3_BD6AC(0, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y,
                   g_Ball.AtBat_Contact_BallPos.z);
        switch (g_Pitcher.starPitchType) {
        case 1:
        case 2:
            lbl_3_common_bss_32724.ballEffect = 1;
            break;
        case 11:
        case 12:
            lbl_3_common_bss_32724.ballEffect = 2;
            break;
        case 9:
        case 10:
            lbl_3_common_bss_32724.ballEffect = 3;
            break;
        case 7:
        case 8:
            lbl_3_common_bss_32724.ballEffect = 4;
            break;
        }
        return;
    }

    if (lbl_3_common_bss_32724.ballEffect == 1) {
        fn_3_BD504(g_Ball.framesSinceHit >= 1, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y,
                   g_Ball.AtBat_Contact_BallPos.z);
        if ((g_Ball.framesSinceHit >= 0 || g_Ball.postPitchResultCounter >= 0 ||
             g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) &&
            g_Ball.currentStarSwing != 1 && g_Ball.currentStarSwing != 2) {
            fn_3_BD4F0();
            lbl_3_common_bss_32724.ballEffect = 0;
            return;
        }
    }
    if (lbl_3_common_bss_32724.ballEffect == 3) {
        fn_3_BD504(g_Ball.framesSinceHit >= 1, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y,
                   g_Ball.AtBat_Contact_BallPos.z);
        if ((g_Ball.framesSinceHit >= 0 || g_Ball.postPitchResultCounter >= 0 ||
             g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) &&
            g_Ball.currentStarSwing != 9 && g_Ball.currentStarSwing != 10) {
            fn_3_BD4F0();
            lbl_3_common_bss_32724.ballEffect = 0;
            return;
        }
    }
    if (g_Ball.framesSinceHit == 1) {
        switch (g_Ball.currentStarSwing) {
        case 1:
        case 2:
            fn_3_BD6AC(1, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y,
                       g_Ball.AtBat_Contact_BallPos.z);
            lbl_3_common_bss_32724.ballEffect = 1;
            break;
        case 11:
        case 12:
            fn_3_BD6AC(1, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y,
                       g_Ball.AtBat_Contact_BallPos.z);
            break;
        case 9:
        case 10:
            fn_3_BD6AC(1, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y,
                       g_Ball.AtBat_Contact_BallPos.z);
            lbl_3_common_bss_32724.ballEffect = 3;
            break;
        case 7:
        case 8:
            fn_3_BD6AC(1, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y,
                       g_Ball.AtBat_Contact_BallPos.z);
            lbl_3_common_bss_32724.ballEffect = 4;
            break;
        case 3:
        case 4:
            fn_3_BD6AC(1, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y,
                       g_Ball.AtBat_Contact_BallPos.z);
            lbl_3_common_bss_32724.ballEffect = 5;
            break;
        }
    }
    if (lbl_3_common_bss_32724.ballEffect != 0) {
        fn_3_BD504(g_Ball.framesSinceHit >= 1, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y,
                   g_Ball.AtBat_Contact_BallPos.z);
        if ((g_Ball.framesSinceHit >= 0 || g_Ball.postPitchResultCounter >= 0 ||
             g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) &&
            g_Ball.currentStarSwing == 0) {
            fn_3_BD4F0();
            lbl_3_common_bss_32724.ballEffect = 0;
        }
    }
}
#endif

#pragma dont_inline on
// .text:0x0006A83C size:0x174 mapped:0x806A98D0
void fn_3_6A83C(void) {
    Vec v;
    s32 who = 0;
    if (g_Pitcher.pitchTotalTimeCounter <= 0) {
        lbl_3_common_bss_32724.pitchEffect = 0;
        return;
    }
    if (lbl_3_common_bss_32724.pitchEffect < 2) {
        if (g_d_GameSettings.minigamesEnabled) {
            who = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        }
        if (g_Pitcher.pitchTotalTimeCounter >= 0 && (g_Pitcher.TypeOfPitch != 0 || g_Pitcher.ChargePitchType != 0)) {
            if (lbl_3_common_bss_32724.pitchEffect == 0) {
                fn_3_CB344(who, g_Pitcher.starPitchType);
                lbl_3_common_bss_32724.pitchEffect = 1;
            }
            if (lbl_3_common_bss_32724.pitchEffect == 1) {
                if (g_Ball.pitchHangtimeCounter == 1 || g_GameLogic.gameStatus != GAME_STATUS_AT_BAT) {
                    fn_3_CB234(who, 1);
                    lbl_3_common_bss_32724.pitchEffect = 2;
                    return;
                }
                // TODO type: called through the old (int, int, void*) prototype, which keeps the original scheduling
                ((int (*)(int, int, void*))getAnimRelatedCoordinates)(who, g_Pitcher.handedness != 0 ? 0x14 : 0x1A, &v);
                fn_3_CB284(who, g_Pitcher.windupCountdownUntilBallReleased, g_Pitcher.pitchChargeUpAnimationProportion);
            }
        }
    }
}
#pragma dont_inline reset

// .text:0x0006A9B0 size:0xE8 mapped:0x806A9A44
void fn_3_6A9B0(void) {
    s32 who;
    if (g_d_GameSettings.minigamesEnabled) {
        who = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID];
    } else {
        who = 9;
    }
    if (g_Batter.chargeStatus == 1) {
        if (g_Batter.chargeFrames == 1) {
            fn_3_C1770(who);
            lbl_3_common_bss_32724.chargeEffect = 1;
            return;
        }
        {
            f32 k = 100.0f;
            f32 y = g_Batter.chargeDown;
            f32 x = g_Batter.chargeUp;
            x = k * x;
            y = k * y;
            fn_3_C1344_k(who, x >= k, x, y, k);
        }
        return;
    }
    if (lbl_3_common_bss_32724.chargeEffect != 0) {
        fn_3_C11CC(who, 1);
        lbl_3_common_bss_32724.chargeEffect = 0;
    }
}

// .text:0x0006AA98 size:0x98 mapped:0x806A9B2C
void fn_3_6AA98(void) {
    if (g_Batter.charID == 2 || g_Batter.charID == 3 || g_Batter.charID == 6) {
        return;
    }
    {
        u8 t = lbl_3_common_bss_32220.state;
        if (t == 0) {
            return;
        }
        if (t == 3 || t == 4) {
            fn_3_C07A0();
        } else if (t == 9) {
            fn_3_C0770();
        } else if (lbl_3_common_bss_32220._02 == 2 && t == 2) {
            fn_3_C07B0();
        }
    }
}

// .text:0x0006AB30 size:0x28 mapped:0x806A9BC4
void fn_3_6AB30(void) {
    fn_3_BF1AC();
    fn_3_CABB4();
    fn_80011578();
}

static inline void fn_3_6A9B0_i(void) {
    s32 who;
    if (g_d_GameSettings.minigamesEnabled) {
        who = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID];
    } else {
        who = 9;
    }
    if (g_Batter.chargeStatus == 1) {
        if (g_Batter.chargeFrames == 1) {
            fn_3_C1770(who);
            lbl_3_common_bss_32724.chargeEffect = 1;
            return;
        }
        {
            f32 k = 100.0f;
            f32 x = g_Batter.chargeUp;
            f32 y = g_Batter.chargeDown;
            x = k * x;
            y = k * y;
            fn_3_C1344_k(who, x >= k, x, y, k);
        }
        return;
    }
    if (lbl_3_common_bss_32724.chargeEffect != 0) {
        fn_3_C11CC(who, 1);
        lbl_3_common_bss_32724.chargeEffect = 0;
    }
}

// .text:0x0006AB58 size:0x368 mapped:0x806A9BEC
void fn_3_6AB58(void) {
    s32 mode;
    lbl_3_common_bss_3223C.cameraYaw =
        game_atan2(g_Camera._284C.z - g_Camera._2840.z, g_Camera._284C.x - g_Camera._2840.x);
    fn_3_6AA98();
    fn_3_6A9B0_i();
    fn_3_6A83C();
    ((void (*)(void))fn_3_6A414)();
    fn_3_6A300();
    if (g_Ball.framesSinceHit == 0 && (lbl_3_common_bss_35154._3AC & 3) == 0) {
        if (g_Batter.captainStarSwingActivated != 0 || g_Batter.didNonCaptainStarSwingConnect != 0) {
            mode = 4;
        } else if (g_Batter.hitGeneralType == 3) {
            mode = 0;
        } else if (g_Batter.displayContactSprite != 0) {
            mode = 3;
        } else if (g_Batter.contactType == 2) {
            mode = 2;
        } else {
            mode = 1;
        }
        if (g_Batter.batterHand == 0) {
            fn_3_BE174(mode, g_Batter.hitContactPos.x, -g_Batter.hitContactPos.y, g_Batter.hitContactPos.z);
        } else {
            fn_3_BE174(mode, -g_Batter.hitContactPos.x, -g_Batter.hitContactPos.y, g_Batter.hitContactPos.z);
        }
    }
}
