#include "main/file_80069BDC.h"
#include "main/file_800527C4.h"
// UnknownHomes_Static.h declares fn_80021518 with placeholder argument types;
// use the real prototype from file_80021308.h instead.
#define fn_80021518 fn_80021518_placeholder
#include "static/UnknownHomes_Static.h"
#undef fn_80021518
#include "main/file_80021308.h"
#include "main/file_80008E00.h"
#include "C3/control.h"
#include "main/file_8000F150.h"
#include "musyx/musyx.h"
#include "dolphin/os.h"
#include "Dolphin/mtxext.h"
#include "stl/math.h"
#include "stl/string.h"

extern SoundManager lbl_800EF808;
extern SoundGroupRequest lbl_80108B84;
extern u8 lbl_80108B18[0x24];
extern u8 lbl_80108B3C[0x48];
extern s32 lbl_80108B90[0x14];
extern u16 lbl_80108BE0[8];
extern s8 lbl_80108BF0[][0x36];
extern u16 lbl_80108DF4[0x22];
extern u16 lbl_80108E38[0x46];
extern u32 lbl_803C663C[4];
extern TutorialSteps lbl_803C66B0;
extern LoopSfxState lbl_803C6714;
extern u8 lbl_803CB888;
extern u8 lbl_803CB889;
extern char lbl_800E6970[]; // "...(%d) Step No %d \n"
extern char lbl_800E69A8[]; // "sound end \n"
extern s32 lbl_803CBD0C;
extern CharModelTable lbl_8036E548;

extern s32 fn_800698F8(s32 kind);
extern void fn_80032064(Vec* pos, s32* params);
extern void fn_80032284(Vec* pos);
extern void fn_800324EC(u16 id, s32 charIndex, s32 c, s32* params);
extern void fn_8004B1C0(s32 sound, CharSoundObj* obj, s32 kind, s32 c);

extern camera_803c639c_s lbl_803C639C[4];
extern Unk803C60BC lbl_803C60BC;
extern s32 lbl_803CB880; // number of active cameras
extern MenuState lbl_8034E978;
extern MenuDef lbl_800FEF70[0x5D];
extern MenuWork lbl_803297E0;
extern u8 lbl_80361B20[0xF8];
extern struct SpaniDesc lbl_80108048;
extern struct SpaniDesc lbl_800FEB30;
extern struct SpaniDesc lbl_80107688;
extern ChallengeMission lbl_8010A768[20][10];
extern s16 lbl_8010B3E8[];
extern s32 determineIfMissionDescriptionIsShown(s16 charID);
extern s32 challengeRelated(s16 team);
extern s32 fn_80064918(s16 charID);
extern void challengeDrawStarsOnMissionMenu(void);

extern void fn_80034E20(SceneTask* task, struct SpaniDesc* desc);
extern void fn_8006CF6C(void);
extern void makeLookAtMatrix(Mtx m, Vec* eye, Vec* up, Vec* target);
extern void fn_80011640(Mtx src, Mtx dst);
extern void fn_800369DC(f32 zoom);
extern BOOL fn_80042D68(SceneTask* owner, s32 idx, s32 frame);
extern BOOL fn_80042DA8(SceneTask* owner, s32 idx, s32 frame);
extern TutorialInput lbl_803C5F04;
extern RosterData lbl_8034E9A0;
extern RosterSlot lbl_80354720[2][9];
extern s16 translateStarPitch(u8 star);
extern s8 translateStarPitchHitIndex(u8 star);
extern s16 translateStarSwing(u8 star);

// Layout object number n of a task's sprite run.
#define TASK_OBJ(task, n) (lbl_80371C30[(task)->u14.objIdx + (n)].obj)

static inline BOOL ObjFrameReached(SceneTask* task, s32 idx, s32 frame) {
    return fn_80042D68(task, idx, frame) != 0;
}

static inline BOOL ObjAtFrame(SceneTask* task, s32 idx, s32 frame) {
    return fn_80042DA8(task, idx, frame) != 0;
}

static inline void SetMenu(s16 menu) {
    lbl_8034E978.menu = menu;
    lbl_8034E978.prevTrack = lbl_8034E978.track;
    lbl_8034E978.track = lbl_800FEF70[menu].track;
}

// .text:0x800527C4 size:0xE8
// TRUE when the point (with y folded below the ground plane) lands inside camera 0's view volume.
BOOL fn_800527C4(Vec* pos) {
    Vec v;

    v.x = pos->x;
    v.y = -__fabs(pos->y);
    v.z = pos->z;
    PSMTXMultVec(lbl_803C639C[0].view, &v, &v);
    PSMTX44MultVec(lbl_803C639C[0].proj, &v, &v);
    return !((v.z < -1.0f) | ((v.z > 0.0f) | ((v.y < -1.0f) | ((v.y > 1.0f) | ((v.x > 1.0f) | (v.x < -1.0f))))));
}

extern fn_800528AC_parameter lbl_803CBD10;

// fn_800528AC, size:0x8
void fn_800528AC(fn_800528AC_parameter value) {
    lbl_803CBD10 = value;
}

// fn_800528B4, size:0xC
void fn_800528B4(void) {
    lbl_803CBD10 = 0;
}

// .text:0x800528C0 size:0xA8
void fn_800528C0(s16* screenX, s16* screenY, f32 x, f32 y, f32 z) {
    Vec v;
    f32 w = 320.0f;
    f32 h = 224.0f;

    v.x = x;
    v.y = y;
    v.z = z;
    PSMTXMultVec(lbl_803C639C[0].view, &v, &v);
    PSMTX44MultVec(lbl_803C639C[0].proj, &v, &v);
    *screenX = v.x * w + w;
    *screenY = -v.y * h + h;
}

// .text:0x80052968 size:0x408
// NONMATCHING 99%: r29/r30 swapped for the view matrix pointer in the two-camera branch
#if NONMATCHING
void fn_80052968(void) {
    MtxPtr view;
    camera_803c639c_s* cam;
    MtxPtr view2;
    f32 scale;

    if (lbl_803CB880 == 1) {
        if (lbl_803CBD10 != NULL) {
            lbl_803CBD10(&lbl_803C639C[0]);
        }
        view = lbl_803C639C[0].view;
        makeLookAtMatrix(view, &lbl_803C639C[0].eye, &lbl_803C639C[0].Up, &lbl_803C639C[0].target);
        scale = 1.0f / lbl_803C639C[0].zoom;
        C_MTXFrustum(lbl_803C639C[0].proj, -0.175f * scale, 0.175f * scale, 0.25f * scale, -0.25f * scale, 1.0f, 512.0f);
        fn_800B806C(0, -240.0f * scale, 240.0f * scale, -320.0f * scale, 320.0f * scale, -512.0f, -1.0f, 1280.0f);
        fn_80011640(view, view);
        scale = 1.0f / lbl_803C639C[0].zoom;
        C_MTXFrustum(lbl_803C639C[0].proj, -0.175f * scale, 0.175f * scale, 0.25f * scale, -0.25f * scale, 1.0f, 512.0f);
        fn_800B806C(0, -240.0f * scale, 240.0f * scale, -320.0f * scale, 320.0f * scale, -512.0f, -1.0f, 1280.0f);
    } else if (lbl_803CB880 == 2) {
        if (lbl_803CBD10 != NULL) {
            lbl_803CBD10(&lbl_803C639C[1]);
        }
        cam = &lbl_803C639C[1];
        view2 = cam->view;
        makeLookAtMatrix(view2, &cam->eye, &cam->Up, &cam->target);
        scale = 1.0f / lbl_803C639C[1].zoom;
        C_MTXFrustum(cam->proj, -0.175f * scale, 0.175f * scale, 0.25f * scale, -0.25f * scale, 1.0f, 512.0f);
        fn_800B806C(0, -240.0f * scale, 240.0f * scale, -320.0f * scale, 320.0f * scale, -512.0f, -1.0f, 1280.0f);
        fn_80011640(view2, view2);
        scale = 1.0f / lbl_803C639C[1].zoom;
        C_MTXFrustum(cam->proj, -0.175f * scale, 0.175f * scale, 0.375f * scale, -0.125f * scale, 1.0f, 512.0f);
        fn_800B806C(1, -240.0f * scale, 240.0f * scale, -160.0f * scale, 160.0f * scale, -512.0f, -1.0f, 1280.0f);

        if (lbl_803CBD10 != NULL) {
            lbl_803CBD10(&lbl_803C639C[0]);
        }
        cam = &lbl_803C639C[0];
        view = cam->view;
        makeLookAtMatrix(view, &cam->eye, &cam->Up, &cam->target);
        scale = 1.0f / lbl_803C639C[0].zoom;
        C_MTXFrustum(lbl_803C639C[0].proj, -0.175f * scale, 0.175f * scale, 0.25f * scale, -0.25f * scale, 1.0f, 512.0f);
        fn_800B806C(0, -240.0f * scale, 240.0f * scale, -320.0f * scale, 320.0f * scale, -512.0f, -1.0f, 1280.0f);
        fn_80011640(view, view);
        scale = 1.0f / lbl_803C639C[0].zoom;
        C_MTXFrustum(lbl_803C639C[0].proj, -0.175f * scale, 0.175f * scale, 0.125f * scale, -0.375f * scale, 1.0f, 512.0f);
        fn_800B806C(0, -240.0f * scale, 240.0f * scale, -160.0f * scale, 160.0f * scale, -512.0f, -1.0f, 1280.0f);
    }
    memcpy(&lbl_803C639C[2], &lbl_803C639C[0], sizeof(camera_803c639c_s) * 2);
    fn_800369DC(lbl_803C639C[0].zoom);
}
#endif

static inline void InitCameras(void) {
    s32 i;
    camera_803c639c_s* cam;
    f32 scale;

    lbl_803CB880 = 1;
    cam = lbl_803C639C;
    for (i = 0; i < 2; i++, cam++) {
        cam->eye.x = 0.0f;
        cam->eye.y = -1.0f;
        cam->eye.z = -5.0f;
        cam->target.x = 0.0f;
        cam->target.y = -1.0f;
        cam->target.z = -4.0f;
        cam->Up.x = 0.0f;
        cam->Up.y = 1.0f;
        cam->Up.z = 0.0f;
        cam->zoom = 1.0f;
        scale = 1.0f / cam->zoom;
        C_MTXFrustum(cam->proj, -0.175f * scale, 0.175f * scale, 0.25f * scale, -0.25f * scale, 1.0f, 512.0f);
        fn_800B806C(0, -240.0f * scale, 240.0f * scale, -320.0f * scale, 320.0f * scale, -512.0f, -1.0f, 1280.0f);
    }
    lbl_803C60BC.dir.x = 0.0f;
    lbl_803C60BC.dir.y = -1.0f;
    lbl_803C60BC.dir.z = 0.0f;
    lbl_803C60BC.dir2.x = 0.0f;
    lbl_803C60BC.dir2.y = -1.0f;
    lbl_803C60BC.dir2.z = 1.0f;
    lbl_803C60BC.angle = -3.1415927f;
    lbl_803C60BC._28 = 0.0f;
    lbl_803C60BC._2C = 0.0f;
    lbl_803C60BC._3C = 1;
    lbl_803C60BC._3D = 0;
    lbl_803CBD10 = NULL;
}

// .text:0x80052D70 size:0x228
void fn_80052D70(void) {
    InitCameras();
}

// .text:0x80052F98 size:0x238
void possiblyTransitionBlackScreen(void) {
    InitCameras();
    lbl_803CC1B8->func = fn_80052968;
}

// .text:0x800531D0 size:0x640
void fn_800531D0(void) {
    return;
}

// .text:0x80053810 size:0x7D8
void fn_80053810(void) {
    return;
}

// .text:0x80053FE8 size:0x2DC
// NONMATCHING 97%: r28/r29 swapped and the loop's zero init scheduled differently
#if NONMATCHING
void fn_80053FE8(void) {
    s32 i;
    SceneTask* task = lbl_803CC1B8;
    u16 first;

    lbl_8034E978._25 = 0;
    lbl_8034E978._24 = 0;
    lbl_8034E978._05 = 0;
    lbl_8034E978._04 = 0;
    for (i = 0; i < 10; i++) {
        lbl_8034E978.text[i] = -1;
    }
    fn_80034E20(task, &lbl_800FEB30);
    TASK_OBJ(task, 6)->_5C = (lbl_8034E978._03 + lbl_800FEF70[lbl_8034E978.menu]._00) << 16;
    TASK_OBJ(task, 5)->_5C = lbl_800FEF70[lbl_8034E978.menu]._06 << 16;
    fn_800363D8(task, 5, 1, 0xEF, lbl_800FEF70[lbl_8034E978.menu]._02);
    TASK_OBJ(task, 4)->_5C = lbl_800FEF70[lbl_8034E978.menu]._04 << 16;
    TASK_OBJ(task, 3)->_5C = lbl_800FEF70[lbl_8034E978.menu]._06 << 16;
    lbl_8034E978._27 = 1;
    TASK_OBJ(task, 7)->_5C = lbl_8034E978.track << 16;
    TASK_OBJ(task, 8)->_5C = lbl_8034E978.prevTrack << 16;
    first = lbl_800FEF70[lbl_8034E978.menu].textStart;
    if (first != 0xFFFF) {
        lbl_8034E978.textCount = lbl_800FEF70[lbl_8034E978.menu].textEnd - first;
        for (i = 0; i < 10; i++) {
            if (i < lbl_8034E978.textCount) {
                lbl_8034E978.text[i] = fn_8000F988((LayoutGroup*)task, i + 0x16, 0, 0, i + lbl_800FEF70[lbl_8034E978.menu].textStart, 0);
            } else {
                lbl_8034E978.text[i] = fn_8000F988((LayoutGroup*)task, i + 0x16, 0, 0, lbl_800FEF70[lbl_8034E978.menu].textStart, 0);
            }
        }
    } else {
        TASK_OBJ(task, 9)->flags &= ~2;
    }
    lbl_8034E978._26 = 0;
    lbl_803CC1B8->func = fn_80053810;
}
#endif

// .text:0x800542C4 size:0x64C
void fn_800542C4(void) {
    return;
}

// .text:0x80054910 size:0x1F0
// NONMATCHING 96%: expected=TRUE scheduled before the call args and a missing mr for done
#if NONMATCHING
void fn_80054910(SceneTask* task, s32 port) {
    u8* state = (u8*)&lbl_803C66B0 + port; // becomes &steps[8][port + 1]
    s8 cur;
    s8 target;
    s8 a;
    s8 b;
    u8 done;
    BOOL expected;

    if ((*(state += 0x31) == 1) ? TRUE : FALSE) {
        cur = lbl_803C5F04.cur[port];
        target = lbl_803C5F04.target[port];
        if (cur != 0) {
            if (lbl_803C5F04.mode == 0) {
                a = lbl_803C5F04.tblA[cur];
                b = lbl_803C5F04.tblB[target];
            } else {
                a = lbl_803C5F04.tblC[port][cur];
                b = lbl_803C5F04.tblD[port][target];
            }
        }
        done = FALSE;
        expected = FALSE;
        if (target == cur && a != b) {
            if (lbl_803C5F04.mode == 0 && cur != 0) {
                switch (cur) {
                case 1:
                    if (a != 0) {
                        done = fn_80042DA8(task, 0x1A, 5) != 0;
                        expected = TRUE;
                    } else {
                        done = fn_80042DA8(task, 0x1A, 0x19) != 0;
                        expected = TRUE;
                    }
                    break;
                }
            } else if (lbl_803C5F04.mode == 1) {
                if (lbl_803C5F04._37[port] == 0) {
                    done = fn_80042DA8(task, cur + port * 4 + 0x33, 0) != 0;
                    expected = TRUE;
                } else {
                    done = fn_80042DA8(task, cur + port * 4 + 0x33, 10) != 0;
                    expected = TRUE;
                }
            }
        }
        if (done == expected) {
            fn_80062674(port);
            *state = 2;
        }
    }
}
#endif

// .text:0x80054B00 size:0x874
void fn_80054B00(void) {
    return;
}

// .text:0x80055374 size:0x424
// NONMATCHING 88%: index sums fold differently and registers differ
#if NONMATCHING
void fn_80055374(SceneTask* task, s32 port) {
    u8* state = (u8*)&lbl_803C66B0 + port; // becomes &steps[8][port + 1]
    s8 menu;
    s8 target;
    s8 a;
    s32 p;

    if ((*(state += 0x31) == 0) ? TRUE : FALSE) {
        menu = 0x15;
        if (g_d_GameSettings.GameModeSelected != 5) {
            menu = 7;
        }
        SetMenu(menu);
        TASK_OBJ(task, 38)->_68 = 1;
        TASK_OBJ(task, 41)->_68 = 1;
        TASK_OBJ(task, 42)->_68 = 1;
        target = lbl_803C5F04.target[port];
        lbl_803C5F04.target[port] = 0;
        TASK_OBJ(task, target + 1)->_5C = 0;
        TASK_OBJ(task, target + 1)->_68 = 0;
        a = lbl_803C5F04.tblA[target];
        switch (target) {
        case 1:
            TASK_OBJ(task, a + 0xC)->_64 = 0x107;
            TASK_OBJ(task, a + 0xC)->_5C = 10 << 16;
            TASK_OBJ(task, a + 0xC)->_68 = 4;
            break;
        case 2:
            TASK_OBJ(task, (a ^ 1) + 0xE)->_64 = 0x107;
            TASK_OBJ(task, (a ^ 1) + 0xE)->_5C = 10 << 16;
            TASK_OBJ(task, (a ^ 1) + 0xE)->_68 = 4;
            break;
        case 3:
            TASK_OBJ(task, a + 0x10)->_64 = 0x109;
            TASK_OBJ(task, a + 0x10)->_5C = 10 << 16;
            TASK_OBJ(task, a + 0x10)->_68 = 4;
            break;
        case 4:
            TASK_OBJ(task, (a ^ 1) + 0x15)->_64 = 0x107;
            TASK_OBJ(task, (a ^ 1) + 0x15)->_5C = 10 << 16;
            TASK_OBJ(task, (a ^ 1) + 0x15)->_68 = 4;
            break;
        }
        TASK_OBJ(task, 0)->_5C = 10 << 16;
        TASK_OBJ(task, 0)->_68 = 4;
        for (p = 0; p < 2; p++) {
            if (((u8*)&g_d_GameSettings)[0x10] != 0 || p == 0) { // TODO type
                TASK_OBJ(task, lbl_803C5F04.cur[p] + p * 4 + 0x2B)->_68 = 1;
                TASK_OBJ(task, lbl_803C5F04.cur[p] * 2 + p + 0x3F)->_68 = 1;
            }
        }
        TASK_OBJ(task, 11)->flags &= ~2;
        TASK_OBJ(task, 88)->_68 = 1;
        fn_800626EC(port);
        *state = 1;
    }
}
#endif

// .text:0x80055798 size:0x254
void fn_80055798(SceneTask* task, s32 port) {
    u8* state = (u8*)&lbl_803C66B0 + port; // becomes &steps[8][port + 1]
    s32 i;

    if ((*(state += 0x31) == 0) ? TRUE : FALSE) {
        if (lbl_803C5F04.mode == 0) {
            if (lbl_803C5F04.tblA[1] == 1) {
                TASK_OBJ(task, 26)->_68 = 1;
            } else {
                TASK_OBJ(task, 26)->_5C = 30 << 16;
                TASK_OBJ(task, 26)->_68 = 4;
            }
            TASK_OBJ(task, 6)->_68 = 1;
            TASK_OBJ(task, 11)->_68 = 1;
            TASK_OBJ(task, 27)->_68 = 1;
            TASK_OBJ(task, 28)->_68 = 1;
            for (i = 0; i < 3; i++) {
                TASK_OBJ(task, i + 0x20)->_68 = 1;
            }
            if (g_d_GameSettings._06 != 2 && g_d_GameSettings.GameModeSelected == 5) {
                TASK_OBJ(task, 87)->_5C = 30 << 16;
                TASK_OBJ(task, 87)->_68 = 4;
            }
        } else {
            TASK_OBJ(task, 38)->_68 = 1;
            TASK_OBJ(task, 41)->_68 = 1;
            TASK_OBJ(task, 42)->_68 = 1;
            TASK_OBJ(task, 6)->_68 = 1;
            TASK_OBJ(task, 11)->_68 = 1;
            TASK_OBJ(task, 27)->_68 = 1;
        }
        TASK_OBJ(task, 88)->_68 = 1;
        fn_800626EC(port);
        *state = 1;
    }
}

// .text:0x800559EC size:0x734
void fn_800559EC(void) {
    return;
}

// .text:0x80056120 size:0x8A8
void fn_80056120(void) {
    return;
}

// .text:0x800569C8 size:0x11C
void fn_800569C8(void) {
    if (g_d_GameSettings._06 == 2) {
        fn_800B0A5C_insertQueue(fn_80053FE8, 0);
        if (g_d_GameSettings.GameModeSelected == 5) {
            SetMenu(0x15);
        } else {
            SetMenu(7);
        }
    } else if (g_d_GameSettings.GameModeSelected == 5) {
        SetMenu(0x14);
    } else {
        SetMenu(6);
    }
    fn_800B0A5C_insertQueue(fn_80056120, 0x3000);
}

// .text:0x80056AE4 size:0x48C
// NONMATCHING 93%: register numbering and some sign-extension placement differ
#if NONMATCHING
void drawStarProgressionMenu(SceneTask* task) {
    CharacterStats* player = &inMemRoster[0][lbl_803297E0.charSel];
    s16 charID = player->stats.CharID;
    ChallengeTeamInfo* info = &lbl_800E8558[charID];
    u8 set;
    s8 rank;
    u16 msg;
    s32 i;

    lbl_803297E0.challengeTeam = info->_0[1];
    set = info->_2;
    rank = gChallengeState.trackers[lbl_803297E0.challengeTeam].variantClassification;
    switch (rank) {
    case 0:
        rank = 3;
        lbl_803297E0.missionCount = 10;
        break;
    case 1:
        rank = 2;
        lbl_803297E0.missionCount = 8;
        break;
    case 2:
        rank = 1;
        lbl_803297E0.missionCount = 6;
        break;
    case 3:
        rank = 0;
        lbl_803297E0.missionCount = 4;
        break;
    }
    TASK_OBJ(task, 31)->_5C = rank << 16;
    TASK_OBJ(task, 32)->_68 = 1;
    TASK_OBJ(task, 36)->_5C = lbl_8034E9A0.chars[player->stats.CharID / 9][player->stats.CharID % 9].stats.CharacterClass << 16;
    TASK_OBJ(task, 37)->_5C = charID << 16;
    TASK_OBJ(task, 38)->_5C = (4 - determineIfMissionDescriptionIsShown(charID)) << 16;
    if ((s8)gChallengeState.trackers[lbl_803297E0.challengeTeam].inGameMissionTracker[0].shownOnPauseMenu != 0) {
        msg = lbl_8010A768[(s16)set][0].msg;
    } else if (lbl_8010A768[(s16)set][0]._6 <= gChallengeState._4415) {
        msg = 0x1C5;
    } else {
        msg = 0x1C6;
    }
    if (lbl_803297E0._CF92 == 1) {
        lbl_803297E0.nameText = fn_8000F988((LayoutGroup*)task, 0x4F, 0, 0, charID + 8, 0);
        lbl_803297E0.descText = fn_8000F988((LayoutGroup*)task, 0x50, 1, 0, lbl_8010B3E8[info->_2] + challengeRelated(lbl_803297E0.challengeTeam), 0);
        lbl_803297E0.missionText = fn_8000F988((LayoutGroup*)task, 0x51, 0, 0, msg, 0);
        lbl_80366B18.entries[lbl_803297E0.missionText].hAlign = 1;
    } else {
        fn_8000FE08(lbl_803297E0.nameText, 0, charID + 8);
        fn_8000FE08(lbl_803297E0.descText, 0, lbl_8010B3E8[info->_2] + challengeRelated(lbl_803297E0.challengeTeam));
        fn_8000FE08(lbl_803297E0.missionText, 0, msg);
    }
    for (i = 0; i < lbl_803297E0.missionCount; i++) {
        if (challengeStarRelatedInd(lbl_803297E0.challengeTeam, i) != 0) {
            TASK_OBJ(task, i + 0x3B)->flags |= 2;
            TASK_OBJ(task, i + 0x3B)->_68 = 1;
        } else {
            TASK_OBJ(task, i + 0x3B)->flags &= ~2;
        }
        TASK_OBJ(task, i + 0x45)->flags &= ~2;
        TASK_OBJ(task, i + 0x31)->flags &= ~2;
        TASK_OBJ(task, i + 0x45)->_5C = 0;
    }
}
#endif

// .text:0x80056F70 size:0x350
// NONMATCHING 94%: shownOnPauseMenu read as s8 and (fn != 0) == 1 kept unfolded in the original
#if NONMATCHING
void someChallengeStarFunction(SceneTask* task) {
    s32 i;
    u8 set;
    s16 msg;

    if (lbl_803297E0.missionShown == 0) {
        set = lbl_800E8558[lbl_803297E0.challengeTeam]._2;
        TASK_OBJ(task, 1)->_68 = 4;
        TASK_OBJ(task, 0)->_68 = 4;
        for (i = 0; i < lbl_803297E0.missionCount; i++) {
            TASK_OBJ(task, i + 0x31)->flags &= ~2;
            TASK_OBJ(task, i + 0x45)->_5C = 0;
            TASK_OBJ(task, i + 0x45)->flags &= ~2;
        }
        TASK_OBJ(task, 35)->flags &= ~2;
        if (challengeStarRelatedInd(lbl_803297E0.challengeTeam, lbl_803297E0.mission) != 0) {
            TASK_OBJ(task, 35)->flags |= 2;
            TASK_OBJ(task, 35)->_5C = 0;
            TASK_OBJ(task, 35)->_68 = 1;
            TASK_OBJ(task, lbl_803297E0.mission + 0x31)->flags |= 2;
            TASK_OBJ(task, lbl_803297E0.mission + 0x31)->_5C = 0;
            TASK_OBJ(task, lbl_803297E0.mission + 0x31)->_68 = 1;
            TASK_OBJ(task, lbl_803297E0.mission + 0x45)->_5C = 1 << 16;
        }
        if (gChallengeState.trackers[lbl_803297E0.challengeTeam].inGameMissionTracker[lbl_803297E0.mission].shownOnPauseMenu != 0) {
            msg = lbl_8010A768[(s16)set][lbl_803297E0.mission].msg;
        } else if (challengeStarRelatedInd(lbl_803297E0.challengeTeam, lbl_803297E0.mission) != 0) {
            msg = lbl_8010A768[(s16)set][lbl_803297E0.mission].msg;
        } else if (lbl_8010A768[(s16)set][lbl_803297E0.mission]._6 <= gChallengeState._4415) {
            msg = 0x1C5;
        } else {
            msg = 0x1C6;
        }
        fn_8000FE08(lbl_803297E0.missionText, 0, msg);
        lbl_803297E0.missionShown = 1;
    }
    if (lbl_803297E0.missionShown != 0 && ObjAtFrame(task, 1, 10) == 1) {
        lbl_803297E0.missionShown = 0;
        lbl_803297E0._CF92 = 0;
    }
}
#endif

// .text:0x800572C0 size:0x430
// NONMATCHING 95%: shownOnPauseMenu read as s8 in the original; register numbering differs
#if NONMATCHING
void someChallengeStarFunction2(SceneTask* task) {
    u8 set;
    s16 msg;

    if (lbl_803297E0.missionShown == 0) {
        set = lbl_800E8558[lbl_803297E0.challengeTeam]._2;
        if (challengeStarRelatedInd(lbl_803297E0.challengeTeam, lbl_803297E0.mission) != 0) {
            TASK_OBJ(task, 35)->flags |= 2;
            TASK_OBJ(task, 35)->_5C = 0;
            TASK_OBJ(task, 35)->_68 = 1;
            TASK_OBJ(task, lbl_803297E0.mission + 0x31)->flags |= 2;
            TASK_OBJ(task, lbl_803297E0.mission + 0x31)->_5C = 0;
            TASK_OBJ(task, lbl_803297E0.mission + 0x31)->_68 = 1;
            TASK_OBJ(task, lbl_803297E0.mission + 0x45)->_5C = 1 << 16;
        } else {
            TASK_OBJ(task, 35)->flags &= ~2;
            TASK_OBJ(task, lbl_803297E0.mission + 0x31)->flags &= ~2;
            TASK_OBJ(task, lbl_803297E0.mission + 0x45)->_5C = 0;
        }
        TASK_OBJ(task, lbl_803297E0.mission + 0x45)->flags |= 2;
        TASK_OBJ(task, lbl_803297E0.mission + 0x45)->_68 = 1;
        if (challengeStarRelatedInd(lbl_803297E0.challengeTeam, lbl_803297E0.prevMission) != 0) {
            TASK_OBJ(task, lbl_803297E0.prevMission + 0x31)->flags &= ~2;
            TASK_OBJ(task, lbl_803297E0.prevMission + 0x27)->_5C = 0;
        } else {
            TASK_OBJ(task, lbl_803297E0.prevMission + 0x27)->_5C = 0;
        }
        TASK_OBJ(task, lbl_803297E0.prevMission + 0x45)->flags &= ~2;
        TASK_OBJ(task, lbl_803297E0.prevMission + 0x45)->_68 = 1;
        if (gChallengeState.trackers[lbl_803297E0.challengeTeam].inGameMissionTracker[lbl_803297E0.mission].shownOnPauseMenu != 0) {
            msg = lbl_8010A768[set][lbl_803297E0.mission].msg;
        } else if (challengeStarRelatedInd(lbl_803297E0.challengeTeam, lbl_803297E0.mission) != 0) {
            msg = lbl_8010A768[set][lbl_803297E0.mission].msg;
        } else if (lbl_8010A768[set][lbl_803297E0.mission]._6 <= gChallengeState._4415) {
            msg = 0x1C5;
        } else {
            msg = 0x1C6;
        }
        fn_8000FE08(lbl_803297E0.missionText, 0, (u16)msg);
        lbl_803297E0.missionShown = 1;
    }
    if (lbl_803297E0.missionShown != 0) {
        lbl_803297E0.missionShown = 0;
        lbl_803297E0._CF92 = 0;
    }
}
#endif

// .text:0x800576F0 size:0x518
// NONMATCHING 97%: register swaps; text release written as three calls (original is a 3-iteration loop)
#if NONMATCHING
void challengeCheckStarsMenuLoading(void) {
    SceneTask* task = lbl_803CC1B8;
    BOOL done;

    switch (lbl_803297E0._CF92) {
    case 1:
        if (lbl_803297E0.missionShown == 0) {
            TASK_OBJ(task, 1)->_68 = 1;
            TASK_OBJ(task, 30)->_68 = 1;
            TASK_OBJ(task, 3)->_68 = 1;
            challengeDrawStarsOnMissionMenu();
            drawStarProgressionMenu(task);
            if (challengeStarRelatedInd(lbl_803297E0.challengeTeam, lbl_803297E0.mission) != 0) {
                TASK_OBJ(task, 35)->flags |= 2;
                TASK_OBJ(task, 35)->_5C = 0;
                TASK_OBJ(task, 35)->_68 = 1;
                TASK_OBJ(task, 69)->_5C = 1 << 16;
            }
            lbl_803297E0.missionShown = 1;
        }
        if (lbl_803297E0.missionShown != 0 && ObjAtFrame(task, 1, 10) == 1) {
            lbl_803297E0.missionShown = 0;
            lbl_803297E0._CF92 = 0;
        }
        break;
    case 2:
        if (lbl_803297E0.missionShown == 0) {
            TASK_OBJ(task, 1)->_68 = 4;
            TASK_OBJ(task, 30)->_68 = 4;
            lbl_803297E0.missionShown = 1;
        }
        if (lbl_803297E0.missionShown != 0) {
            done = fn_80042DA8(task, 1, 0) != 0;
            if (done + (fn_80042DA8(task, 30, 0) != 0) == 2) {
                lbl_803297E0.menuDone = 1;
                lbl_803297E0.missionShown = 0;
                lbl_803297E0._CF92 = 0;
                fn_8000FEE8(lbl_803297E0.nameText);
                fn_8000FEE8(lbl_803297E0.descText);
                fn_8000FEE8(lbl_803297E0.missionText);
                fn_8000F8F4((LayoutGroup*)task);
            }
        }
        break;
    case 3:
        if (lbl_803297E0.missionShown == 0) {
            TASK_OBJ(task, lbl_803297E0.charSel + 3)->_5C = 0;
            TASK_OBJ(task, lbl_803297E0.charSel + 3)->_68 = 1;
            TASK_OBJ(task, lbl_803297E0.prevCharSel + 3)->_5C = 10 << 16;
            TASK_OBJ(task, lbl_803297E0.prevCharSel + 3)->_68 = 4;
            drawStarProgressionMenu(task);
            if (challengeStarRelatedInd(lbl_803297E0.challengeTeam, lbl_803297E0.mission) != 0) {
                TASK_OBJ(task, 35)->flags |= 2;
                TASK_OBJ(task, 35)->_5C = 0;
                TASK_OBJ(task, 35)->_68 = 1;
                TASK_OBJ(task, 69)->_5C = 1 << 16;
            } else {
                TASK_OBJ(task, 35)->flags &= ~2;
                TASK_OBJ(task, 69)->_5C = 0;
            }
            lbl_803297E0.missionShown = 1;
        }
        if (lbl_803297E0.missionShown != 0) {
            lbl_803297E0.missionShown = 0;
            lbl_803297E0._CF92 = 0;
        }
        break;
    case 4:
        someChallengeStarFunction2(task);
        break;
    case 6:
        someChallengeStarFunction(task);
        break;
    case 5:
        if (lbl_803297E0.missionShown == 0) {
            TASK_OBJ(task, 1)->_68 = 1;
            TASK_OBJ(task, 0)->_68 = 1;
            TASK_OBJ(task, 69)->flags |= 2;
            TASK_OBJ(task, 69)->_68 = 1;
            lbl_803297E0.missionShown = 1;
        }
        if (lbl_803297E0.missionShown != 0 && ObjAtFrame(task, 1, 20) == 1) {
            lbl_803297E0.missionShown = 0;
            lbl_803297E0._CF92 = 0;
        }
        break;
    }
    if (lbl_803297E0.menuDone != 0) {
        lbl_803297E0.menuDone = 0;
        fn_800B0A14_removeQueue(fn_80034CEC(task));
    }
}
#endif

// .text:0x80057C08 size:0xA4
void starMenu(void) {
    SceneTask* task;
    s32 i;

    fn_80034E20(task = lbl_803CC1B8, &lbl_80108048);
    for (i = 0; i < 9; i++) {
        lbl_80371C30[12 + task->u14.objIdx + i].obj->_5C = i << 16;
        fn_800363D8(task, i + 0x15, 1, 0x83, inMemRoster[0][i].stats.CharID);
    }
    lbl_803CC1B8->func = challengeCheckStarsMenuLoading;
}

// .text:0x80057CAC size:0x3A4
// NONMATCHING 96%: the scout-flag loop counters start from the any-flag register; loop registers differ
#if NONMATCHING
void fn_80057CAC(void) {
    SceneTask* task = lbl_803CC1B8;
    s32 i;
    s32 j;
    s32 base;
    u8 any;

    switch (lbl_803297E0.scoutState) {
    case 1:
        if (lbl_803297E0.scoutSub == 0) {
            TASK_OBJ(task, 0)->_68 = 1;
            TASK_OBJ(task, 1)->_68 = 1;
            for (i = 0; i < 9; i++) {
                TASK_OBJ(task, i + 0x17)->_68 = 1;
            }
            lbl_803297E0.scoutSub = 1;
        }
        if (lbl_803297E0.scoutSub != 0 && ObjFrameReached(task, 0, 10) == 1) {
            lbl_803297E0.scoutSub = 0;
            lbl_803297E0.scoutState = 2;
        }
        break;
    case 2:
        any = FALSE;
        if (lbl_803297E0.scoutSub == 0) {
            for (i = 0, base = 0; i < 9; i++, base += 5) {
                for (j = 0; j < lbl_803297E0.scoutGot[i]; j++) {
                    any = TRUE;
                    TASK_OBJ(task, j + base + 0x20)->_68 = 1;
                }
            }
            if (any) {
                sndFXStartEx(0x1B1, 0x7F, 0x3F, 0);
            }
            lbl_803297E0.scoutSub = 1;
        }
        if (lbl_803297E0.scoutSub != 0) {
            lbl_803297E0.scoutSub = 0;
            lbl_803297E0.scoutState = 0;
        }
        break;
    case 3:
        if (lbl_803297E0.scoutSub == 0) {
            TASK_OBJ(task, 0)->_68 = 4;
            lbl_803297E0.scoutSub = 1;
        }
        if (lbl_803297E0.scoutSub != 0 && ObjAtFrame(task, 0, 0) == 1) {
            lbl_803297E0.scoutDone = 1;
            lbl_803297E0.scoutSub = 0;
            lbl_803297E0.scoutState = 0;
        }
        break;
    }
    if (lbl_803297E0.scoutDone != 0) {
        lbl_803297E0.scoutDone = 0;
        fn_800B0A14_removeQueue(fn_80034CEC(task));
    }
}
#endif

// .text:0x80058050 size:0x344
// NONMATCHING 92%: scout-flag loop registers and compare shapes differ
#if NONMATCHING
void fn_80058050(void) {
    SceneTask* task = lbl_803CC1B8;
    CharacterStats* player;
    s32 i;
    s32 j;
    s32 base;
    ChallengeTrackingStruct* tracker;

    fn_80034E20(task, &lbl_80107688);
    for (i = 0, base = 0, player = inMemRoster[1]; i < 9; i++, player++, base += 5) {
        tracker = &gChallengeState.trackers[player->stats.CharID];
        lbl_803297E0.scoutTotal[i] = ((ScoutFlagTable*)tracker->scoutFlagPointer)->flags[gChallengeState._4415][gChallengeState._441C];
        lbl_803297E0.scoutGot[i] = gChallengeState.trackers[player->stats.CharID].scoutFlagsAchieved;
        for (j = 0; j < 5; j++) {
            if (j < lbl_803297E0.scoutTotal[i] && lbl_803297E0.scoutTotal[i] - lbl_803297E0.scoutGot[i] > j) {
                TASK_OBJ(task, j + base + 0x20)->_5C = 0;
            } else if (j >= lbl_803297E0.scoutTotal[i]) {
                TASK_OBJ(task, j + base + 0x20)->flags &= ~2;
            }
        }
        TASK_OBJ(task, i + 5)->_5C = i << 16;
        fn_800363D8(task, i + 0xE, 1, 0x83, player->stats.CharID);
    }
    TASK_OBJ(task, 4)->_5C = 5 << 16;
    if (gChallengeState._441F == 0x13) {
        if ((g_d_GameSettings.home_AwaySetting ^ 1) != 0) {
            TASK_OBJ(task, 2)->flags |= 2;
            TASK_OBJ(task, 2)->_5C = (lbl_8034E9A0._470D[1] % 4) << 16;
        } else {
            TASK_OBJ(task, 3)->flags |= 2;
            TASK_OBJ(task, 3)->_5C = (lbl_8034E9A0._470D[1] % 4) << 16;
        }
    } else if (g_d_GameSettings.home_AwaySetting != 0) {
        TASK_OBJ(task, 2)->flags |= 2;
        TASK_OBJ(task, 2)->_5C = (lbl_8034E9A0._470D[1] % 4) << 16;
    } else {
        TASK_OBJ(task, 3)->flags |= 2;
        TASK_OBJ(task, 3)->_5C = (lbl_8034E9A0._470D[1] % 4) << 16;
    }
    lbl_803CC1B8->func = fn_80057CAC;
}
#endif

// .text:0x80058394 size:0x2B0
// NONMATCHING 97%: star-1 kept untruncated in r26 in the challenge branch; ours truncates early
#if NONMATCHING
void fn_80058394(SceneTask* task) {
    CharacterStats* player;
    s8 row;
    s8 col;
    u8 star;
    u8 swing;
    u8 pitch;
    s16 swingAnim;
    s16 pitchAnim;

    if (lbl_803297E0.starShown[lbl_803297E0.team] == 0) {
        TASK_OBJ(task, 302)->flags &= ~2;
        TASK_OBJ(task, 302)->_68 = 0;
        TASK_OBJ(task, 281)->_68 = 4;
        TASK_OBJ(task, 289)->_68 = 4;
        player = &inMemRoster[lbl_803297E0.team][lbl_803297E0.selected[lbl_803297E0.team] - 1];
        row = player->stats.CharID / 9;
        col = player->stats.CharID % 9;
        star = lbl_8034E9A0.chars[row][col].stats.CaptainStarHitPitch;
        if (star == 0) {
            swing = lbl_8034E9A0.chars[row][col].stats.NonCaptainStarSwing + 11;
            pitch = lbl_8034E9A0.chars[row][col].stats.NonCaptainStarPitch + 11;
        } else if (g_d_GameSettings.GameModeSelected != 5) {
            swing = star - 1;
            pitch = swing;
        } else {
            s8 idx;
            pitch = star - 1;
            idx = translateStarPitchHitIndex(pitch);
            if (idx != -1 && ((s8*)&gChallengeState)[0x43C2 + idx] == 0) { // TODO type
                swing = lbl_8034E9A0.chars[row][col].stats.NonCaptainStarSwing + 11;
                pitch = lbl_8034E9A0.chars[row][col].stats.NonCaptainStarPitch + 11;
            } else {
                swing = pitch;
                pitch = (u8)(star - 1);
            }
        }
        swingAnim = translateStarSwing(swing);
        pitchAnim = translateStarPitch(pitch);
        TASK_OBJ(task, 305)->_64 = swingAnim;
        TASK_OBJ(task, 305)->_5C = 0;
        TASK_OBJ(task, 305)->_68 = 1;
        TASK_OBJ(task, 306)->_64 = pitchAnim;
        TASK_OBJ(task, 306)->_5C = 0;
        TASK_OBJ(task, 306)->_68 = 1;
        TASK_OBJ(task, 307)->flags |= 2;
        TASK_OBJ(task, 307)->_68 = 1;
        TASK_OBJ(task, 303)->_68 = 1;
        lbl_803297E0.starShown[lbl_803297E0.team] = 1;
    }
}
#endif

// .text:0x80058644 size:0x4DC
// NONMATCHING 99%: the roster address adds are scheduled in a different order
#if NONMATCHING
void fn_80058644(SceneTask* task) {
    CharacterStats* player;
    s16 charID;
    u32 fielding;
    u8 pushPull;
    u8 highLow;
    u8 stance;

    if (lbl_803297E0.starShown[lbl_803297E0.team] == 0) {
        player = &inMemRoster[lbl_803297E0.team][lbl_803297E0.selected[lbl_803297E0.team] - 1];
        charID = player->stats.CharID;
        fielding = player->stats.FieldingStats;
        pushPull = player->stats.HitTrajectoryPushPull;
        highLow = player->stats.HitTrajectoryHighLow;
        stance = player->stats.BattingStance;
        TASK_OBJ(task, 291)->_5C = charID << 16;
        TASK_OBJ(task, 292)->_5C = fn_80064918(charID) << 16;
        TASK_OBJ(task, 301)->_5C = charID << 16;
        fn_80059458(task, lbl_803297E0.team, fielding);
        TASK_OBJ(task, 295)->_5C = 0;
        TASK_OBJ(task, 296)->_5C = 1 << 16;
        TASK_OBJ(task, 297)->_5C = 2 << 16;
        TASK_OBJ(task, 298)->_5C = 3 << 16;
        TASK_OBJ(task, 299)->_5C = 4 << 16;
        TASK_OBJ(task, 300)->_5C = 5 << 16;
        TASK_OBJ(task, 283)->_5C = 0;
        TASK_OBJ(task, 284)->_5C = 0;
        TASK_OBJ(task, 285)->_5C = 0;
        TASK_OBJ(task, 286)->_5C = 0;
        TASK_OBJ(task, 287)->_5C = 0;
        TASK_OBJ(task, 288)->_5C = 0;
        switch (pushPull) {
        case 0:
            TASK_OBJ(task, 283)->_68 = 1;
            TASK_OBJ(task, 284)->_68 = 0;
            TASK_OBJ(task, 285)->_68 = 0;
            break;
        case 1:
            if (stance == 0) {
                TASK_OBJ(task, 283)->_68 = 0;
                TASK_OBJ(task, 284)->_68 = 1;
                TASK_OBJ(task, 285)->_68 = 0;
            } else {
                TASK_OBJ(task, 283)->_68 = 0;
                TASK_OBJ(task, 284)->_68 = 0;
                TASK_OBJ(task, 285)->_68 = 1;
            }
            break;
        case 2:
            if (stance == 0) {
                TASK_OBJ(task, 283)->_68 = 0;
                TASK_OBJ(task, 284)->_68 = 0;
                TASK_OBJ(task, 285)->_68 = 1;
            } else {
                TASK_OBJ(task, 283)->_68 = 0;
                TASK_OBJ(task, 284)->_68 = 1;
                TASK_OBJ(task, 285)->_68 = 0;
            }
            break;
        }
        switch (highLow) {
        case 0:
            TASK_OBJ(task, 286)->_68 = 1;
            TASK_OBJ(task, 287)->_68 = 0;
            TASK_OBJ(task, 288)->_68 = 0;
            break;
        case 1:
            TASK_OBJ(task, 286)->_68 = 0;
            TASK_OBJ(task, 287)->_68 = 1;
            TASK_OBJ(task, 288)->_68 = 0;
            break;
        case 2:
            TASK_OBJ(task, 286)->_68 = 0;
            TASK_OBJ(task, 287)->_68 = 0;
            TASK_OBJ(task, 288)->_68 = 1;
            break;
        }
        TASK_OBJ(task, 302)->flags |= 2;
        TASK_OBJ(task, 302)->_68 = 1;
        TASK_OBJ(task, 281)->_68 = 1;
        TASK_OBJ(task, 289)->_5C = 0;
        TASK_OBJ(task, 289)->_68 = 1;
        TASK_OBJ(task, 307)->flags &= ~2;
        TASK_OBJ(task, 307)->_68 = 0;
        TASK_OBJ(task, 303)->_68 = 4;
        lbl_803297E0.starShown[lbl_803297E0.team] = 1;
    }
}
#endif

// .text:0x80058B20 size:0x2EC
// NONMATCHING 95%: same star-select register differences as fn_80058394
#if NONMATCHING
void fn_80058B20(SceneTask* task, u8 port) {
    CharacterStats* player;
    s8 row;
    s8 col;
    u8 star;
    u8 swing;
    u8 pitch;
    s16 swingAnim;
    s16 pitchAnim;

    if (lbl_803297E0.starShown[port] == 0) {
        TASK_OBJ(task, port + 0x1C6)->flags &= ~2;
        TASK_OBJ(task, port + 0x1C6)->_68 = 0;
        TASK_OBJ(task, port + 0x19C)->_68 = 4;
        TASK_OBJ(task, port + 0x1AC)->_68 = 4;
        player = &inMemRoster[port][lbl_803297E0.selected[port] - 1];
        row = player->stats.CharID / 9;
        col = player->stats.CharID % 9;
        star = lbl_8034E9A0.chars[row][col].stats.CaptainStarHitPitch;
        if (star == 0) {
            swing = lbl_8034E9A0.chars[row][col].stats.NonCaptainStarSwing + 11;
            pitch = lbl_8034E9A0.chars[row][col].stats.NonCaptainStarPitch + 11;
        } else if (g_d_GameSettings.GameModeSelected != 5) {
            swing = star - 1;
            pitch = swing;
        } else {
            s8 idx;
            pitch = star - 1;
            idx = translateStarPitchHitIndex(pitch);
            if (idx != -1 && ((s8*)&gChallengeState)[0x43C2 + idx] == 0) { // TODO type
                swing = lbl_8034E9A0.chars[row][col].stats.NonCaptainStarSwing + 11;
                pitch = lbl_8034E9A0.chars[row][col].stats.NonCaptainStarPitch + 11;
            } else {
                swing = pitch;
                pitch = (u8)(star - 1);
            }
        }
        swingAnim = translateStarSwing(swing);
        pitchAnim = translateStarPitch(pitch);
        TASK_OBJ(task, port + 0x1CC)->_64 = swingAnim;
        TASK_OBJ(task, port + 0x1CC)->_5C = 0;
        TASK_OBJ(task, port + 0x1CC)->_68 = 1;
        TASK_OBJ(task, port + 0x1CE)->_64 = pitchAnim;
        TASK_OBJ(task, port + 0x1CE)->_5C = 0;
        TASK_OBJ(task, port + 0x1CE)->_68 = 1;
        TASK_OBJ(task, port + 0x1D0)->flags |= 2;
        TASK_OBJ(task, port + 0x1D0)->_68 = 1;
        TASK_OBJ(task, port + 0x1C8)->_68 = 1;
        lbl_803297E0.starShown[port] = 1;
    }
}
#endif

// .text:0x80058E0C size:0x64C
void fn_80058E0C(void) {
    return;
}

// .text:0x80059458 size:0x27C
// Shows the two set bits of mask (bit 0 also skips bit 1) as frames on two objects.
// NONMATCHING 98%: li r0,12 hoisted above the first compare in the original; register swaps in the store tail
#if NONMATCHING
void fn_80059458(SceneTask* task, u8 port, u32 mask) {
    s32 digits[2];
    s32 i;
    s32 n;

    memset(digits, -1, 2);
    for (i = 0, n = 0; i < 14; i++) {
        if (mask & (1 << i)) {
            switch (i) {
            case 0:
                i++;
                break;
            case 1:
                digits[n++] = 1;
                break;
            case 2:
                digits[n++] = 2;
                break;
            case 3:
                digits[n++] = 3;
                break;
            case 4:
                digits[n++] = 4;
                break;
            case 5:
                digits[n++] = 5;
                break;
            case 6:
                digits[n++] = 6;
                break;
            case 7:
                digits[n++] = 7;
                break;
            case 8:
                digits[n++] = 8;
                break;
            case 9:
                digits[n++] = 9;
                break;
            case 10:
                digits[n++] = 10;
                break;
            case 11:
                digits[n++] = 11;
                break;
            case 12:
                digits[n++] = 12;
                break;
            default:
                digits[n++] = 13;
                break;
            }
        }
    }
    digits[0]--;
    digits[1]--;
    if (digits[0] < 0) {
        digits[0] = 12;
    }
    if (digits[1] < 0) {
        digits[1] = 12;
    }
    if (g_d_GameSettings._06 != 2) {
        TASK_OBJ(task, port + 0x1B4)->_5C = digits[0] << 16;
        TASK_OBJ(task, port + 0x1B6)->_5C = digits[1] << 16;
    } else {
        TASK_OBJ(task, 0x125)->_5C = digits[0] << 16;
        TASK_OBJ(task, 0x126)->_5C = digits[1] << 16;
    }
}
#endif

// .text:0x800596D4 size:0x464
// NONMATCHING 92%: register numbering and index-sum order differ
#if NONMATCHING
void fn_800596D4(SceneTask* task) {
    s32 base;
    s16 msg;
    u8 set;

    if (lbl_803297E0.pauseShown == 0) {
        if (challengeStarRelatedInd(lbl_803297E0.challengeTeam, lbl_803297E0.pauseMission) != 0) {
            base = 0x1DD;
            TASK_OBJ(task, 473)->flags |= 2;
            TASK_OBJ(task, 473)->_5C = 0;
            TASK_OBJ(task, 473)->_68 = 1;
            TASK_OBJ(task, lbl_803297E0.pauseMission + 0x1E7)->flags |= 2;
            TASK_OBJ(task, lbl_803297E0.pauseMission + 0x1E7)->_5C = 0;
            TASK_OBJ(task, lbl_803297E0.pauseMission + 0x1E7)->_68 = 1;
            if (g_d_GameSettings._06 == 2) {
                base = 0x173;
            }
            TASK_OBJ(task, base + lbl_803297E0.pauseMission)->_5C = 1 << 16;
        } else {
            base = 0x1DD;
            TASK_OBJ(task, 473)->flags &= ~2;
            TASK_OBJ(task, lbl_803297E0.pauseMission + 0x1E7)->flags &= ~2;
            if (g_d_GameSettings._06 == 2) {
                base = 0x173;
            }
            TASK_OBJ(task, base + lbl_803297E0.pauseMission)->_5C = 0;
        }
        TASK_OBJ(task, lbl_803297E0.pauseMission + 0x1FB)->flags |= 2;
        TASK_OBJ(task, lbl_803297E0.pauseMission + 0x1FB)->_68 = 1;
        if (challengeStarRelatedInd(lbl_803297E0.challengeTeam, lbl_803297E0.pausePrevMission) != 0) {
            base = 0x1DD;
            TASK_OBJ(task, lbl_803297E0.pausePrevMission + 0x1E7)->flags &= ~2;
            if (g_d_GameSettings._06 == 2) {
                base = 0x173;
            }
            TASK_OBJ(task, base + lbl_803297E0.pausePrevMission)->_5C = 0;
        } else {
            base = 0x1DD;
            if (g_d_GameSettings._06 == 2) {
                base = 0x173;
            }
            TASK_OBJ(task, base + lbl_803297E0.pausePrevMission)->_5C = 0;
        }
        TASK_OBJ(task, lbl_803297E0.pausePrevMission + 0x1FB)->flags &= ~2;
        TASK_OBJ(task, lbl_803297E0.pausePrevMission + 0x1FB)->_68 = 1;
        set = lbl_800E8558[lbl_803297E0.challengeTeam]._2;
        if ((s8)gChallengeState.trackers[lbl_803297E0.challengeTeam].inGameMissionTracker[lbl_803297E0.pauseMission].shownOnPauseMenu != 0) {
            msg = lbl_8010A768[set][lbl_803297E0.pauseMission].msg;
        } else if (lbl_8010A768[set][lbl_803297E0.pauseMission]._6 <= gChallengeState._4415) {
            msg = 0x1C5;
        } else {
            msg = 0x1C6;
        }
        fn_8000FE08(lbl_803297E0.missionText, 0, msg);
        lbl_803297E0.pauseShown = 1;
    }
    if (lbl_803297E0.pauseShown != 0) {
        lbl_803297E0._CF74 = 0;
        lbl_803297E0.pauseShown = 0;
    }
}
#endif

// .text:0x80059B38 size:0x818
void starMissionRelated1(void) {
    return;
}

// .text:0x8005A350 size:0xC18
void fn_8005A350(void) {
    return;
}

// .text:0x8005AF68 size:0x330
// NONMATCHING 93%: loop registers rotated; pos+0x3E index folded differently
#if NONMATCHING
void fn_8005AF68(SceneTask* task) {
    s32 i;
    s8 team = lbl_803297E0.team;
    RosterSlot* slot = lbl_80354720[team];
    CharacterStats* player = inMemRoster[team];
    u8 flag;

    for (i = 0; i < 9; i++, player++, slot++) {
        if (lbl_803297E0.teamKind[team] != 2) {
            s8 pos = slot->pos;
            fn_800363D8(task, pos + 0x23, 1, 0x83, player->stats.CharID);
            TASK_OBJ(task, i + 0x11)->flags &= ~2;
            if (g_d_GameSettings.GameModeSelected == 5) {
                flag = ((u8*)&gChallengeState)[0x43D6 + player->stats.CharID]; // TODO type
            } else {
                flag = lbl_8034E9A0._489B[team][i];
            }
            if (flag != 0 && (team != 1 || g_d_GameSettings.GameModeSelected != 5)) {
                TASK_OBJ(task, pos + 0x3E)->_68 = 1;
                TASK_OBJ(task, pos + 0x47)->flags |= 2;
                TASK_OBJ(task, pos + 0x47)->_5C = 0;
                TASK_OBJ(task, pos + 0x47)->_68 = 1;
            } else if (lbl_80361B20[player->stats.CharID] != 0 && g_d_GameSettings.GameModeSelected != 5) {
                TASK_OBJ(task, pos + 0x3E)->_68 = 1;
                TASK_OBJ(task, pos + 0x47)->flags |= 2;
                TASK_OBJ(task, pos + 0x47)->_5C = 0;
                TASK_OBJ(task, pos + 0x47)->_68 = 0;
            } else {
                TASK_OBJ(task, pos + 0x3E)->flags &= ~2;
                TASK_OBJ(task, pos + 0x47)->flags &= ~2;
            }
            TASK_OBJ(task, i + 0x35)->flags &= ~2;
            if (((u8*)&g_d_GameSettings)[0x10] == 0 && team != 0) { // TODO type
                TASK_OBJ(task, i + 0x1A)->_64 = (u8)(lbl_8034E9A0._46F8[0] == 0) + 30;
            } else {
                TASK_OBJ(task, i + 0x1A)->_64 = lbl_8034E9A0._46F8[team] + 30;
            }
        }
    }
}
#endif

// .text:0x8005B298 size:0x4C8
// NONMATCHING 92%: loop registers differ
#if NONMATCHING
void fn_8005B298(SceneTask* task) {
    s32 i;
    s32 j;
    s8 team = lbl_803297E0.team;
    CharacterStats* player = inMemRoster[team];
    u8 flag;

    for (i = 0; i < 9; i++, player++) {
        TASK_OBJ(task, i + 0x5A)->_5C = i << 16;
        TASK_OBJ(task, i + 0x6C)->flags &= ~2;
        if (lbl_803297E0.teamKind[team] == 0) {
            fn_800363D8(task, i + 0x63, 1, 0x83, player->stats.CharID);
            TASK_OBJ(task, i + 0xAB)->_5C = player->stats.CharacterClass << 16;
            TASK_OBJ(task, i + 0x99)->_5C = (player->stats.BattingStance + player->stats.FieldingArm * 2) << 16;
            TASK_OBJ(task, i + 0x134)->flags &= ~2;
        } else {
            ChallengeTrackingStruct* tracker;
            s8 total;
            s32 left;

            fn_800363D8(task, i + 0x63, 1, 0x83, inMemRoster[1][i].stats.CharID);
            tracker = &gChallengeState.trackers[inMemRoster[1][i].stats.CharID];
            total = ((ScoutFlagTable*)tracker->scoutFlagPointer)->flags[gChallengeState._4415][gChallengeState._441C];
            left = total - (s8)tracker->scoutFlagsAchieved;
            for (j = 0; j < 5; j++) {
                if (j < total && left > j) {
                    TASK_OBJ(task, j + i * 5 + 0x13D)->_5C = 0;
                } else if (j < total) {
                    TASK_OBJ(task, j + i * 5 + 0x13D)->_68 = 1;
                    if (g_d_GameSettings._06 == 2) {
                        sndFXStartEx(0x1B1, 0x7F, 0x3F, 0);
                    } else {
                        sndFXStartEx(0x1E6, 0x7F, 0x3F, 0);
                    }
                } else {
                    TASK_OBJ(task, j + i * 5 + 0x13D)->flags &= ~2;
                }
            }
            TASK_OBJ(task, i + 0xAB)->flags &= ~2;
            TASK_OBJ(task, i + 0x99)->flags &= ~2;
        }
        if (g_d_GameSettings.GameModeSelected == 5) {
            flag = ((u8*)&gChallengeState)[0x43D6 + player->stats.CharID]; // TODO type
        } else {
            flag = lbl_8034E9A0._489B[team][i];
        }
        if (flag != 0 && (team != 1 || g_d_GameSettings.GameModeSelected != 5)) {
            TASK_OBJ(task, i + 0x7E)->_68 = 1;
            TASK_OBJ(task, i + 0x87)->flags |= 2;
            TASK_OBJ(task, i + 0x87)->_5C = 0;
            TASK_OBJ(task, i + 0x87)->_68 = 1;
        } else if (lbl_80361B20[player->stats.CharID] != 0 && g_d_GameSettings.GameModeSelected != 5) {
            TASK_OBJ(task, i + 0x7E)->_68 = 1;
            TASK_OBJ(task, i + 0x87)->flags |= 2;
            TASK_OBJ(task, i + 0x87)->_5C = 0;
            TASK_OBJ(task, i + 0x87)->_68 = 0;
        } else {
            TASK_OBJ(task, i + 0x7E)->flags &= ~2;
            TASK_OBJ(task, i + 0x87)->flags &= ~2;
        }
        TASK_OBJ(task, i + 0x75)->flags &= ~2;
    }
}
#endif

// .text:0x8005B760 size:0x3FC
// NONMATCHING 93%: state test shape and register numbering differ
#if NONMATCHING
void fn_8005B760(SceneTask* task, s32 port) {
    u8* state = &lbl_803C66B0.steps[9][port + 1];
    s32 i;
    s32 slot;
    s8 pos;

    if (*state == 0) {
        if (lbl_803297E0.selected[port] != 0) {
            slot = lbl_803297E0.selected[port] - 1;
            pos = lbl_80354720[port][slot].pos;
            for (i = 0; i < 9; i++) {
                TASK_OBJ(task, i + 0x75)->flags &= ~2;
                TASK_OBJ(task, i + 0x35)->flags &= ~2;
            }
            if (lbl_803297E0.teamKind[port] == 0) {
                TASK_OBJ(task, pos + 0x23)->_68 = 1;
                TASK_OBJ(task, pos + 0x1A)->_68 = 1;
            } else {
                TASK_OBJ(task, slot + 0x63)->_68 = 1;
                TASK_OBJ(task, slot + 0x51)->flags |= 2;
                TASK_OBJ(task, slot + 0x51)->_5C = 0;
                TASK_OBJ(task, slot + 0x51)->_68 = 1;
                TASK_OBJ(task, slot + 0x6C)->flags |= 2;
                TASK_OBJ(task, slot + 0x6C)->_5C = 0;
                TASK_OBJ(task, slot + 0x6C)->_68 = 1;
            }
            TASK_OBJ(task, slot + 0x6C)->flags |= 2;
            TASK_OBJ(task, slot + 0x6C)->_5C = 0;
            TASK_OBJ(task, slot + 0x6C)->_68 = 1;
            TASK_OBJ(task, slot + 0x75)->flags |= 2;
            TASK_OBJ(task, slot + 0x75)->_64 = 0x2A;
            TASK_OBJ(task, slot + 0x75)->_68 = 1;
            TASK_OBJ(task, pos + 0x35)->flags |= 2;
            TASK_OBJ(task, pos + 0x35)->_64 = 0x2A;
            TASK_OBJ(task, pos + 0x35)->_68 = 1;
            fn_8005C830(task, port, slot);
            TASK_OBJ(task, 14)->_5C = 0;
            TASK_OBJ(task, 14)->_68 = 0;
        }
        fn_800626EC(port);
        *state = 1;
    }
}
#endif

// .text:0x8005BB5C size:0x3E4
// NONMATCHING 90%: loop registers and index sums differ
#if NONMATCHING
void fn_8005BB5C(SceneTask* task) {
    s32 team;
    s32 base;
    s32 i;
    s32 j;
    CharacterStats* player;
    u8 flag;

    for (team = 0, base = 0; team < 2; team++, base += 9) {
        for (i = 0; i < 9; i++) {
            player = &inMemRoster[team][i];
            fn_800363D8(task, i + base + 0x40, 1, 0x83, player->stats.CharID);
            TASK_OBJ(task, i + base + 0x2E)->_5C = i << 16;
            if (team == 0) {
                TASK_OBJ(task, i + 0xD0)->_5C = inMemRoster[0][i].stats.CharacterClass << 16;
                TASK_OBJ(task, i + 0xAC)->_5C = (inMemRoster[0][i].stats.BattingStance + inMemRoster[0][i].stats.FieldingArm * 2) << 16;
                TASK_OBJ(task, i + 0x64)->flags &= ~2;
                if (g_d_GameSettings.GameModeSelected == 5) {
                    flag = ((u8*)&gChallengeState)[0x43D6 + player->stats.CharID]; // TODO type
                } else {
                    flag = lbl_8034E9A0._489B[team][i];
                }
                if (flag != 0 && team == 0) {
                    TASK_OBJ(task, i + 0x76)->_68 = 1;
                    TASK_OBJ(task, i + 0x88)->flags |= 2;
                    TASK_OBJ(task, i + 0x88)->_5C = 0;
                    TASK_OBJ(task, i + 0x88)->_68 = 1;
                } else {
                    TASK_OBJ(task, i + 0x88)->flags &= ~2;
                }
            } else {
                ChallengeTrackingStruct* tracker;
                TASK_OBJ(task, i + base + 0xD0)->flags &= ~2;
                TASK_OBJ(task, i + base + 0xAC)->flags &= ~2;
                TASK_OBJ(task, i + base + 0x88)->flags &= ~2;
                TASK_OBJ(task, i + base + 0x64)->flags &= ~2;
                for (j = 0; j < 5; j++) {
                    tracker = &gChallengeState.trackers[inMemRoster[1][i].stats.CharID];
                    if (j < ((ScoutFlagTable*)tracker->scoutFlagPointer)->flags[gChallengeState._4415][gChallengeState._441C]) {
                        TASK_OBJ(task, j + i * 5 + 0x16D)->_5C = 0;
                        TASK_OBJ(task, j + i * 5 + 0x16D)->_68 = 0;
                    } else {
                        TASK_OBJ(task, j + i * 5 + 0x16D)->flags &= ~2;
                    }
                }
            }
        }
        TASK_OBJ(task, team + 8)->_5C = lbl_8034E9A0._470D[team] << 16;
        TASK_OBJ(task, team + 0xC)->_5C = lbl_8034E9A0._470D[team] << 16;
    }
}
#endif

// .text:0x8005BF40 size:0x370
// NONMATCHING 90%: loop registers and index sums differ
#if NONMATCHING
void fn_8005BF40(SceneTask* task) {
    s32 team;
    s32 base;
    s32 i;
    CharacterStats* player;
    RosterSlot* slot;
    u8 flag;

    for (team = 0, base = 0; team < 2; team++, base += 9) {
        player = inMemRoster[team];
        slot = lbl_80354720[team];
        for (i = 0; i < 9; i++, player++, slot++) {
            fn_800363D8(task, slot->pos + base + 0x10A, 1, 0x83, player->stats.CharID);
            TASK_OBJ(task, i + base + 0xE6)->flags &= ~2;
            if (g_d_GameSettings.GameModeSelected == 5) {
                flag = ((u8*)&gChallengeState)[0x43D6 + player->stats.CharID]; // TODO type
            } else {
                flag = lbl_8034E9A0._489B[team][i];
            }
            if (flag != 0) {
                TASK_OBJ(task, slot->pos + base + 0x140)->_68 = 1;
                TASK_OBJ(task, slot->pos + base + 0x152)->flags |= 2;
                TASK_OBJ(task, slot->pos + base + 0x152)->_5C = 0;
                TASK_OBJ(task, slot->pos + base + 0x152)->_68 = 1;
            } else if (lbl_80361B20[player->stats.CharID] != 0) {
                TASK_OBJ(task, slot->pos + base + 0x140)->_68 = 1;
                TASK_OBJ(task, slot->pos + base + 0x152)->flags |= 2;
                TASK_OBJ(task, slot->pos + base + 0x152)->_5C = 0;
                TASK_OBJ(task, slot->pos + base + 0x152)->_68 = 0;
            } else {
                TASK_OBJ(task, slot->pos + base + 0x152)->flags &= ~2;
            }
            TASK_OBJ(task, i + base + 0x12E)->flags &= ~2;
            if (((u8*)&g_d_GameSettings)[0x10] == 0 && team != 0) { // TODO type
                TASK_OBJ(task, i + base + 0xF8)->_64 = (s8)(lbl_8034E9A0._46F8[0] == 0) + 30;
            } else {
                TASK_OBJ(task, i + base + 0xF8)->_64 = lbl_8034E9A0._46F8[team] + 30;
            }
        }
    }
}
#endif

// .text:0x8005C2B0 size:0x314
// NONMATCHING 90%: index sums associate differently (objIdx+i+base+K) and loop registers differ
#if NONMATCHING
void fn_8005C2B0(SceneTask* task) {
    s32 team;
    s32 base;
    s32 i;
    CharacterStats* player;
    u8 flag;

    for (team = 0, base = 0; team < 2; team++, base += 9) {
        for (i = 0; i < 9; i++) {
            player = &inMemRoster[team][i];
            fn_800363D8(task, i + base + 0x40, 1, 0x83, player->stats.CharID);
            TASK_OBJ(task, i + base + 0x2E)->_5C = i << 16;
            TASK_OBJ(task, i + base + 0xD0)->_5C = player->stats.CharacterClass << 16;
            TASK_OBJ(task, i + base + 0xAC)->_5C = (player->stats.BattingStance + player->stats.FieldingArm * 2) << 16;
            if (g_d_GameSettings.GameModeSelected == 5) {
                flag = ((u8*)&gChallengeState)[0x43D6 + player->stats.CharID]; // TODO type
            } else {
                flag = lbl_8034E9A0._489B[team][i];
            }
            if (flag != 0) {
                TASK_OBJ(task, i + base + 0x76)->_68 = 1;
                TASK_OBJ(task, i + base + 0x88)->flags |= 2;
                TASK_OBJ(task, i + base + 0x88)->_5C = 0;
                TASK_OBJ(task, i + base + 0x88)->_68 = 1;
            } else if (lbl_80361B20[player->stats.CharID] != 0) {
                TASK_OBJ(task, i + base + 0x76)->_68 = 1;
                TASK_OBJ(task, i + base + 0x88)->flags |= 2;
                TASK_OBJ(task, i + base + 0x88)->_5C = 0;
                TASK_OBJ(task, i + base + 0x88)->_68 = 0;
            } else {
                TASK_OBJ(task, i + base + 0x88)->flags &= ~2;
            }
            TASK_OBJ(task, i + base + 0x64)->flags &= ~2;
        }
        TASK_OBJ(task, team + 8)->_5C = lbl_8034E9A0._470D[team] << 16;
        TASK_OBJ(task, team + 0xC)->_5C = lbl_8034E9A0._470D[team] << 16;
    }
}
#endif

// .text:0x8005C5C4 size:0x26C
// NONMATCHING 97%: r5/r7 and r0/r4 swapped in the frame-30 branch
#if NONMATCHING
void fn_8005C5C4(SceneTask* task, s32 port) {
    u8* state = (u8*)&lbl_803C66B0 + port; // becomes &steps[9][port + 1]

    if ((*(state += 0x37) == 0) ? TRUE : FALSE) {
        if (g_d_GameSettings._06 == 2) {
            TASK_OBJ(task, 0)->_5C = 20 << 16;
            TASK_OBJ(task, 0)->_68 = 4;
        } else if (g_d_GameSettings.GameModeSelected == 5) {
            TASK_OBJ(task, 0)->_5C = 20 << 16;
            TASK_OBJ(task, 1)->_5C = 20 << 16;
            TASK_OBJ(task, 0)->_68 = 4;
            TASK_OBJ(task, 1)->_68 = 4;
        } else if (((u8*)&g_d_GameSettings)[0x10] == 0) { // TODO type
            if (port != 0) {
                TASK_OBJ(task, port)->_5C = 20 << 16;
                TASK_OBJ(task, port)->_68 = 4;
            } else {
                TASK_OBJ(task, port)->_5C = 30 << 16;
                TASK_OBJ(task, port)->_68 = 1;
            }
        } else {
            LayoutSlot* slots = lbl_80371C30;
            LayoutObj* obj = slots[task->u14.objIdx + port].obj;
            if ((obj->_5C >> 16) == 30) {
                obj->_5C = 30 << 16;
                slots[task->u14.objIdx + port].obj->_68 = 1;
            } else {
                obj->_5C = 20 << 16;
                slots[task->u14.objIdx + port].obj->_68 = 4;
            }
        }
        TASK_OBJ(task, port + 0x16)->_5C = 10 << 16;
        TASK_OBJ(task, port + 0x18)->_68 = 4;
        TASK_OBJ(task, port + 0x12)->_5C = 20 << 16;
        TASK_OBJ(task, port + 0x12)->_68 = 1;
        fn_800626EC(port);
        *state = 1;
    }
}
#endif

// .text:0x8005C830 size:0x4B4
// NONMATCHING 88%: index sums associate differently and loop registers differ
#if NONMATCHING
void fn_8005C830(SceneTask* task, s32 port, s32 slot) {
    s32 j;
    s32 k;
    CharacterStats* player;
    RosterSlot* rs;

    for (j = 0; j < 9; j++) {
        player = inMemRoster[port];
        rs = lbl_80354720[port];
        for (k = 0; k < 9; k++, player++, rs++) {
            if (player->stats.CharID != lbl_8034E9A0.chemPartner[port][slot][j]) {
                continue;
            }
            if (lbl_803297E0._CF52[port] == 0) {
                if (g_d_GameSettings._06 != 2) {
                    TASK_OBJ(task, k + port * 9 + 0x52)->_5C = 0;
                    TASK_OBJ(task, k + port * 9 + 0x52)->_68 = 1;
                    TASK_OBJ(task, k + port * 9 + 0x64)->flags |= 2;
                    TASK_OBJ(task, k + port * 9 + 0x64)->_64 = 0x2B;
                    TASK_OBJ(task, k + port * 9 + 0x64)->_68 = 1;
                } else {
                    TASK_OBJ(task, rs->pos + 0x35)->flags |= 2;
                    TASK_OBJ(task, rs->pos + 0x35)->_64 = 0x2B;
                    TASK_OBJ(task, rs->pos + 0x35)->_5C = 0;
                    TASK_OBJ(task, rs->pos + 0x35)->_68 = 1;
                    TASK_OBJ(task, k + 0x6C)->flags |= 2;
                    TASK_OBJ(task, k + 0x6C)->_5C = 0;
                    TASK_OBJ(task, k + 0x6C)->_68 = 1;
                    TASK_OBJ(task, k + 0x75)->flags |= 2;
                    TASK_OBJ(task, k + 0x75)->_64 = 0x2B;
                    TASK_OBJ(task, k + 0x75)->_68 = 1;
                }
            } else if (g_d_GameSettings._06 != 2) {
                TASK_OBJ(task, rs->pos + port * 9 + 0x12E)->flags |= 2;
                TASK_OBJ(task, rs->pos + port * 9 + 0x12E)->_64 = 0x2B;
                TASK_OBJ(task, rs->pos + port * 9 + 0x12E)->_5C = 0;
                TASK_OBJ(task, rs->pos + port * 9 + 0x12E)->_68 = 1;
            } else {
                TASK_OBJ(task, rs->pos + 0x35)->flags |= 2;
                TASK_OBJ(task, rs->pos + 0x35)->_64 = 0x2B;
                TASK_OBJ(task, rs->pos + 0x35)->_5C = 0;
                TASK_OBJ(task, rs->pos + 0x35)->_68 = 1;
                TASK_OBJ(task, k + 0x6C)->flags |= 2;
                TASK_OBJ(task, k + 0x6C)->_5C = 0;
                TASK_OBJ(task, k + 0x6C)->_68 = 1;
                TASK_OBJ(task, k + 0x75)->flags |= 2;
                TASK_OBJ(task, k + 0x75)->_64 = 0x2B;
                TASK_OBJ(task, k + 0x75)->_68 = 1;
            }
        }
    }
}
#endif

// .text:0x8005CCE4 size:0x1130
void fn_8005CCE4(SceneTask* task, s32 port) {
    return;
}

// .text:0x8005DE14 size:0xBC4
void fn_8005DE14(SceneTask* task, s32 port) {
    return;
}

// .text:0x8005E9D8 size:0x2B0
void fn_8005E9D8(SceneTask* task, s32 port) {
    u8* state;

    if (lbl_803297E0.selected[port] != lbl_803297E0.selected2[port]) {
        fn_8005DE14(task, port);
        state = (u8*)&lbl_803C66B0 + port; // becomes &steps[9][port + 1]
        if ((*(state += 0x37) == 1) ? TRUE : FALSE) {
            fn_80062674(port);
            *state = 2;
        }
    } else if (lbl_803297E0._CF3C[port] != 0) {
        state = &lbl_803C66B0.steps[9][port + 1];
        if (*state == 0) {
            u8 slot = lbl_803297E0._CF3E[port];
            s8 pos = lbl_80354720[port][slot].pos;
            if (lbl_803297E0._CF52[port] == 0) {
                TASK_OBJ(task, slot + port * 9 + 0x1C)->_5C = 10 << 16;
                TASK_OBJ(task, slot + port * 9 + 0x1C)->_68 = 0;
                TASK_OBJ(task, slot + port * 9 + 0x40)->_5C = 0;
                TASK_OBJ(task, slot + port * 9 + 0x40)->_68 = 1;
            } else if (g_d_GameSettings._06 != 2) {
                TASK_OBJ(task, pos + port * 9 + 0x10A)->_5C = 0;
                TASK_OBJ(task, pos + port * 9 + 0x10A)->_68 = 1;
                TASK_OBJ(task, pos + port * 9 + 0xF8)->_5C = 0;
                TASK_OBJ(task, pos + port * 9 + 0xF8)->_68 = 1;
            } else {
                TASK_OBJ(task, pos + 0x23)->_5C = 0;
                TASK_OBJ(task, pos + 0x23)->_68 = 1;
                TASK_OBJ(task, pos + 0x1A)->_5C = 0;
                TASK_OBJ(task, pos + 0x1A)->_68 = 1;
            }
            lbl_803C66B0.step[port] = 0;
            *state = 2;
        }
    } else {
        fn_8005CCE4(task, port);
    }
}

// .text:0x8005EC88 size:0x3E0
// NONMATCHING 90%: index sums (objIdx+i+port*9+K) associate differently; state test shape
#if NONMATCHING
void fn_8005EC88(SceneTask* task, s32 port) {
    u8* state = &lbl_803C66B0.steps[9][port + 1];
    s32 i;
    s32 slot;
    s8 pos;

    if (*state == 0) {
        if (lbl_803297E0.selected[port] != 0) {
            slot = lbl_803297E0.selected[port] - 1;
            pos = lbl_80354720[port][slot].pos;
            for (i = 0; i < 9; i++) {
                TASK_OBJ(task, i + port * 9 + 0x64)->flags &= ~2;
                TASK_OBJ(task, i + port * 9 + 0x12E)->flags &= ~2;
            }
            switch (lbl_803297E0._CF52[port]) {
            case 0:
                TASK_OBJ(task, slot + port * 9 + 0x40)->_68 = 1;
                TASK_OBJ(task, slot + port * 9 + 0x1C)->_5C = 0;
                TASK_OBJ(task, slot + port * 9 + 0x1C)->_68 = 1;
                TASK_OBJ(task, slot + port * 9 + 0x52)->_5C = 0;
                TASK_OBJ(task, slot + port * 9 + 0x52)->_68 = 1;
                TASK_OBJ(task, slot + port * 9 + 0x64)->flags |= 2;
                TASK_OBJ(task, slot + port * 9 + 0x64)->_64 = 0x2A;
                TASK_OBJ(task, slot + port * 9 + 0x64)->_68 = 1;
                fn_8005C830(task, port, slot);
                break;
            case 1:
                TASK_OBJ(task, pos + port * 9 + 0x10A)->_68 = 1;
                TASK_OBJ(task, pos + port * 9 + 0xF8)->_68 = 1;
                TASK_OBJ(task, pos + port * 9 + 0x12E)->flags |= 2;
                TASK_OBJ(task, pos + port * 9 + 0x12E)->_64 = 0x2A;
                TASK_OBJ(task, pos + port * 9 + 0x12E)->_68 = 1;
                fn_8005C830(task, port, slot);
                break;
            }
        }
        TASK_OBJ(task, port + 0x18)->_5C = 10 << 16;
        TASK_OBJ(task, port + 0x18)->_68 = 4;
        fn_800626EC(port);
        *state = 1;
    }
}
#endif

// .text:0x8005F068 size:0x6CC
void fn_8005F068(void) {
    return;
}

// .text:0x8005F734 size:0x29C
// NONMATCHING 95%: add operand order objIdx+port and r4/r8 swapped throughout
#if NONMATCHING
void fn_8005F734(SceneTask* task, s32 port) {
    u8* state = (u8*)&lbl_803C66B0 + port; // becomes &steps[9][port + 1]

    if ((*(state += 0x37) == 0) ? TRUE : FALSE) {
        TASK_OBJ(task, port)->_64 = 0x49;
        TASK_OBJ(task, port)->_5C = 50 << 16;
        TASK_OBJ(task, port)->_68 = 4;
        TASK_OBJ(task, port + 2)->_64 = 0x52;
        TASK_OBJ(task, port + 2)->_5C = 0;
        TASK_OBJ(task, port + 2)->_68 = 1;
        TASK_OBJ(task, port + 4)->_5C = 0;
        TASK_OBJ(task, port + 4)->_68 = 1;
        TASK_OBJ(task, port + 6)->_5C = 14 << 16;
        TASK_OBJ(task, port + 6)->_68 = 1;
        TASK_OBJ(task, port + 10)->flags |= 2;
        TASK_OBJ(task, port + 10)->_5C = 0;
        TASK_OBJ(task, port + 10)->_68 = 1;
        TASK_OBJ(task, port + 20)->_5C = 0;
        TASK_OBJ(task, port + 20)->_68 = 1;
        if (((u8*)&g_d_GameSettings)[0x10] == 0 && port == 0) { // TODO type
            TASK_OBJ(task, port + 18)->_5C = 30 << 16;
            TASK_OBJ(task, port + 18)->_68 = 4;
            TASK_OBJ(task, port + 24)->_5C = 0;
            TASK_OBJ(task, port + 24)->_68 = 0;
        } else {
            TASK_OBJ(task, port + 18)->_5C = 0;
            TASK_OBJ(task, port + 18)->_68 = 1;
        }
        fn_800626EC(port);
        *state = 1;
    }
}
#endif

// .text:0x8005F9D0 size:0x2D0
// NONMATCHING 96%: the original keeps the constant 5 in r27 (set in each branch) and tests ready[] with bne/b
#if NONMATCHING
void fn_8005F9D0(SceneTask* task, s32 port) {
    u8* states = &lbl_803C66B0.steps[9][1];
    s32 done;

    if ((states[port] == 1) ? TRUE : FALSE) {
        done = fn_80042DA8(task, port + 4, 20) != 0;
        if (g_d_GameSettings.GameModeSelected != 5) {
            if (((u8*)&g_d_GameSettings)[0x10] == 0 && port != 0) { // TODO type
                done += fn_80042DA8(task, port, 30) != 0;
                done += fn_80042DA8(task, port + 10, 10) != 0;
                done += fn_80042DA8(task, port + 18, 20) != 0;
                done += fn_80042DA8(task, port + 20, 10) != 0;
            } else {
                done += fn_80042DA8(task, port, 20) != 0;
                done += fn_80042DA8(task, port + 10, 10) != 0;
                done += fn_80042DA8(task, port + 18, 10) != 0;
                done += fn_80042DA8(task, port + 20, 10) != 0;
            }
        } else {
            done += fn_80042DA8(task, port, 20) != 0;
            done += fn_80042DA8(task, port + 10, 10) != 0;
            done += fn_80042DA8(task, 18, 10) != 0;
            done += fn_80042DA8(task, 20, 10) != 0;
        }
        if (done == 5) {
            if (((u8*)&g_d_GameSettings)[0x10] == 0) { // TODO type
                lbl_803297E0.ready[port] = 1;
                if (lbl_803297E0.ready[0] != 0) {
                    if (lbl_803297E0.ready[1] == 0) {
                        return;
                    }
                    lbl_803297E0.ready[1] = 0;
                    lbl_803297E0.ready[0] = 0;
                    fn_80062674(0);
                    fn_80062674(1);
                    lbl_803C66B0.steps[9][1] = 2;
                    lbl_803C66B0.steps[9][2] = 2;
                    if (g_d_GameSettings.GameModeSelected == 5) {
                        fn_800625A4(0, 0x45);
                    }
                }
            } else {
                fn_80062674(port);
                states[port] = 2;
            }
        }
    }
}
#endif

// .text:0x8005FCA0 size:0x4E4
// NONMATCHING 97%: r4/r7 swapped (objIdx+port operand order), as in fn_8005F734
#if NONMATCHING
void fn_8005FCA0(SceneTask* task, s32 port) {
    u8* state = (u8*)&lbl_803C66B0 + port; // becomes &steps[9][port + 1]

    if ((*(state += 0x37) == 0) ? TRUE : FALSE) {
        TASK_OBJ(task, port + 4)->_5C = 0;
        TASK_OBJ(task, port + 4)->_68 = 1;
        TASK_OBJ(task, port + 6)->_5C = 14 << 16;
        TASK_OBJ(task, port + 6)->_68 = 1;
        if (g_d_GameSettings.GameModeSelected != 5) {
            if (((u8*)&g_d_GameSettings)[0x10] == 0 && port != 0) { // TODO type
                TASK_OBJ(task, port)->_5C = 0;
                TASK_OBJ(task, port)->_68 = 1;
                TASK_OBJ(task, port + 2)->_5C = 0;
                TASK_OBJ(task, port + 2)->_68 = 1;
                TASK_OBJ(task, port + 18)->_5C = 30 << 16;
                TASK_OBJ(task, port + 18)->_68 = 4;
                TASK_OBJ(task, port + 20)->_5C = 0;
                TASK_OBJ(task, port + 20)->_68 = 1;
                TASK_OBJ(task, port + 24)->_5C = 0;
                TASK_OBJ(task, port + 24)->_68 = 0;
                TASK_OBJ(task, port + 10)->flags |= 2;
                TASK_OBJ(task, port + 10)->_5C = 0;
                TASK_OBJ(task, port + 10)->_68 = 1;
            } else {
                TASK_OBJ(task, port)->_5C = 0;
                TASK_OBJ(task, port)->_68 = 1;
                TASK_OBJ(task, port + 2)->_5C = 0;
                TASK_OBJ(task, port + 2)->_68 = 1;
                TASK_OBJ(task, port + 10)->flags |= 2;
                TASK_OBJ(task, port + 10)->_5C = 0;
                TASK_OBJ(task, port + 10)->_68 = 1;
                TASK_OBJ(task, port + 2)->_5C = 0;
                TASK_OBJ(task, port + 2)->_68 = 1;
                TASK_OBJ(task, port + 18)->_5C = 0;
                TASK_OBJ(task, port + 18)->_68 = 1;
                TASK_OBJ(task, port + 20)->_5C = 0;
                TASK_OBJ(task, port + 20)->_68 = 1;
            }
        } else {
            TASK_OBJ(task, port)->_5C = 0;
            TASK_OBJ(task, port)->_68 = 1;
            TASK_OBJ(task, port + 10)->flags |= 2;
            TASK_OBJ(task, port + 10)->_5C = 0;
            TASK_OBJ(task, port + 10)->_68 = 1;
            TASK_OBJ(task, 18)->_5C = 0;
            TASK_OBJ(task, 18)->_68 = 1;
            TASK_OBJ(task, 20)->_5C = 0;
            TASK_OBJ(task, 20)->_68 = 1;
            TASK_OBJ(task, 2)->_5C = 0;
            TASK_OBJ(task, 2)->_68 = 1;
            TASK_OBJ(task, 3)->_5C = 0;
            TASK_OBJ(task, 3)->_68 = 1;
            if (lbl_803297E0._CF70 == 0) {
                TASK_OBJ(task, 466)->flags |= 2;
                TASK_OBJ(task, 466)->_5C = 10 << 16;
                TASK_OBJ(task, 466)->_68 = 1;
            }
        }
        fn_800626EC(port);
        *state = 1;
    }
}
#endif

// .text:0x80060184 size:0x1A18
void fn_80060184(void) {
    return;
}

// .text:0x80061B9C size:0x7D0
void fn_80061B9C(void) {
    return;
}

// .text:0x8006236C size:0x20C
void SetMenuNumber(void) {
    s32 i;
    u8 any = FALSE;
    s16 menu;

    if (g_d_GameSettings._06 != 2) {
        if (g_d_GameSettings.GameModeSelected == 5) {
            menu = 0x16;
        } else {
            for (i = 0; i < 0x36; i++) {
                if (lbl_80361B20[i] != 0) {
                    any = TRUE;
                    break;
                }
            }
            if (any) {
                menu = 4;
            } else {
                menu = 3;
            }
        }
        SetMenu(menu);
    }
    {
        u8 kind = lbl_803297E0.teamKind[lbl_803297E0.team];
        if (kind != 2 && kind != 3) {
            if (g_d_GameSettings.GameModeSelected == 5 && lbl_803297E0._CF70 != 0 && lbl_80361B20[0xE4] == 0) {
                fn_800B0A5C_insertQueue(fn_8006CF6C, 0x3000);
            }
            fn_800B0A5C_insertQueue(fn_80061B9C, 0x3000);
        } else if (kind == 2) {
            fn_800B0A5C_insertQueue(fn_80058050, 0x3000);
        } else {
            fn_800B0A5C_insertQueue(starMenu, 0x3000);
        }
    }
}

// .text:0x80062578 size:0x2C
BOOL fn_80062578(void) {
    BOOL ret = FALSE;
    if (lbl_803C66B0.step[0] == 0 && lbl_803C66B0.step[1] == 0) {
        ret = TRUE;
    }
    return ret;
}

// .text:0x800625A4 size:0xD0
// NONMATCHING 98%: the unrolled clear stores the loop counter's zero register (r4) instead of a fresh li r0,0
#if NONMATCHING
void fn_800625A4(s32 index, s8 step) {
    s32 i;
    s32 port = ((u8*)&g_d_GameSettings)[0x10] == 0 ? 0 : index; // TODO type

    if (lbl_803C66B0.active[port] != 0) {
        OSReport(lbl_800E6970, port, lbl_803C66B0.step[port]);
    }
    lbl_803C66B0.step[index] = step;
    for (i = 0; i < 14; i++) {
        lbl_803C66B0.steps[i][index + 1] = 0;
    }
}
#endif


// fn_800626EC, size:0x58
void fn_800626EC(s32 index) {
    if (((u8*)&g_d_GameSettings)[0x10] == 0) {
        lbl_803C66B0.active[0] = 1;
    } else {
        lbl_803C66B0.active[index] = 1;
    }
    lbl_803C663C[index]++;
}

// fn_80062674, size:0x78
void fn_80062674(s32 index) {
    lbl_803C663C[index]--;
    if ((s32)lbl_803C663C[index] == 0) {
        if (((u8*)&g_d_GameSettings)[0x10] == 0) {
            lbl_803C66B0.active[0] = 0;
        } else {
            lbl_803C66B0.active[index] = 0;
        }
        lbl_803C66B0.step[index] = 0;
    }
}

// fn_80062744, size:0x20
void fn_80062744(void) {
    lbl_803C663C[3] = 0;
    lbl_803C663C[2] = 0;
    lbl_803C663C[1] = 0;
    lbl_803C663C[0] = 0;
}

// .text:0x80062764 size:0x30
void fn_80062764(SoundLoadTask* task) {
    lbl_80108B84.task = task;
    fn_800215F8(&lbl_80108B84);
}

// .text:0x80062794 size:0x30
BOOL fn_80062794(s32 voice) {
    return sndFXCheck(voice) != SND_ID_ERROR;
}

// .text:0x800627C4 size:0x34
s32 fn_800627C4(void) {
    fn_80021518(0, lbl_800EF808.groups[4]);
    return 0;
}

// .text:0x800627F8 size:0x34
s32 fn_800627F8(void) {
    fn_80021518(0x31, lbl_800EF808.groups[38]);
    return 0;
}

// .text:0x8006282C size:0x30
void fn_8006282C(void) {
    fn_80021518(0x20, lbl_800EF808.groups[37]);
}

// .text:0x8006285C size:0x34
s32 fn_8006285C(void) {
    fn_80021518(0x20, lbl_800EF808.groups[37]);
    return 0;
}

// .text:0x80062890 size:0x44
u32 fn_80062890(s32 index) {
    return sndFXStartEx(lbl_80108E38[index], lbl_80108B3C[index], 0x3F, 0);
}

// .text:0x800628D4 size:0x74
// NONMATCHING 90%: lis/addi of lbl_80108B18 and lbl_80108DF4 scheduled in a different order
#if NONMATCHING
u32 fn_800628D4(s32 kind) {
    u32 voice;

    lbl_8034E9A0._48AE = 1;
    voice = sndFXStartEx(lbl_80108DF4[fn_800698F8(kind)], lbl_80108B18[0], 0x3F, 0);
    sndFXCtrl(voice, 0x5B, 0);
    return voice;
}
#endif

// fn_80062948, size:0x14
void fn_80062948(void) {
    lbl_803C6714.stopB = 1;
}

// .text:0x8006295C size:0xF4
void fn_8006295C(void) {
    if (lbl_800EF808.unk398 != 0) {
        if (lbl_803C6714.activeB == 0) {
            lbl_803C6714.voiceB = sndFXStartEx(0, lbl_803CB889, 0x3F, 0);
            lbl_803C6714.activeB = 1;
            lbl_803C6714.stopB = 0;
        }
        if (lbl_803C6714.stopB != 0) {
            sndFXKeyOff(lbl_803C6714.voiceB);
            lbl_803C6714.voiceB = 0;
            lbl_803C6714.stopB = 0;
            lbl_803C6714.activeB = 0;
            ((void (*)(void))fn_800B0A14_removeQueue)(); // removes the running task
        }
    } else {
        sndFXKeyOff(lbl_803C6714.voiceB);
        lbl_803C6714.voiceB = 0;
        lbl_803C6714.stopB = 0;
        lbl_803C6714.activeB = 0;
        OSReport(lbl_800E69A8);
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
}


// initializeUnknown, size:0x24
void initializeUnknown(void) {
    lbl_8034E9A0._48B3 = 0;
    lbl_803C6714.voiceA = 0;
    lbl_803C6714.stopA = 0;
    lbl_803C6714.activeA = 0;
}

// fn_80062A74, size:0x20
void fn_80062A74(void) {
    lbl_803C6714.stopA = 1;
    lbl_8034E9A0._48B3 = 1;
}

// .text:0x80062A94 size:0x150
void fn_80062A94(void) {
    if (lbl_800EF808.unk398 != 0) {
        if (lbl_803C6714.activeA == 0) {
            lbl_803C6714.voiceA = sndFXStartEx(0x1E4, lbl_803CB888, 0x3F, 0);
            lbl_803C6714.activeA = 1;
            lbl_803C6714.stopA = 0;
            lbl_803C6714.fadeLen = 0;
            lbl_803C6714.fadeCount = 0;
        }
        if (lbl_803C6714.fadeLen != 0) {
            lbl_803C6714.fadeCount++;
            if (lbl_803C6714.fadeCount >= lbl_803C6714.fadeLen) {
                lbl_803C6714.stopA = 1;
            } else {
                sndFXCtrl(lbl_803C6714.voiceA, 7, lbl_803CB888 - lbl_803CB888 * lbl_803C6714.fadeCount / lbl_803C6714.fadeLen);
            }
        }
        if (lbl_803C6714.stopA != 0) {
            sndFXKeyOff(lbl_803C6714.voiceA);
            lbl_803C6714.stopA = 0;
            lbl_803C6714.voiceA = 0;
            lbl_803C6714.activeA = 0;
            ((void (*)(void))fn_800B0A14_removeQueue)(); // removes the running task
        }
    } else {
        sndFXKeyOff(lbl_803C6714.voiceA);
        lbl_803C6714.voiceA = 0;
        lbl_803C6714.stopA = 0;
        lbl_803C6714.activeA = 0;
        OSReport(lbl_800E69A8);
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
}

// .text:0x80062BE4 size:0x40
void fn_80062BE4(Vec* pos) {
    if (lbl_80366158._28 != 1) {
        lbl_80108B90[0] = lbl_803CBD0C;
        fn_80032064(pos, lbl_80108B90);
    }
}

// .text:0x80062C24 size:0x3C
void fn_80062C24(Vec* pos) {
    if (lbl_80366158._28 != 1 && pos != NULL) {
        fn_80032284(pos);
    }
}

static inline s32 CharJointSound(CharSoundObj* obj, u16 joint) {
    CharJointMapObj* model = lbl_8036E548.chars[obj->charIndex];
    if (model != NULL) {
        return model->jointMap[joint];
    }
    return 0xFFFF;
}

static inline void PlayCharJointSound(CharSoundObj* obj) {
    s32 i;

    if (lbl_80366158._28 != 1) {
        for (i = 0; lbl_80108BE0[i] != 0xFFFF && CharJointSound(obj, lbl_80108BE0[i]) == 0xFFFF; i++) {
        }
        if (lbl_80108BE0[i] != 0xFFFF) {
            lbl_80108B90[0] = lbl_803CBD0C;
            fn_800324EC(lbl_80108BE0[i], obj->charIndex, -1, lbl_80108B90);
        }
    }
}

// .text:0x80062C60 size:0x134
// NONMATCHING 95%: r7/r8 swapped in the inlined joint loop (see docs/patterns/regalloc.md)
#if NONMATCHING
void fn_80062C60(CharSoundObj* obj, s32 a, s32 b, f32 frame) {
    if (lbl_80366158._28 != 1) {
        if (frame == 0.5f) {
            PlayCharJointSound(obj);
        }
        fn_8006C3F8(obj, frame, a, b);
    }
}
#endif

// .text:0x80062D94 size:0xD8
// NONMATCHING 95%: r7/r9/r10 rotated in the joint loop (see docs/patterns/regalloc.md)
#if NONMATCHING
void fn_80062D94(CharSoundObj* obj) {
    PlayCharJointSound(obj);
}
#endif

// .text:0x80062E6C size:0x68
void fn_80062E6C(CharSoundObj* obj, s32 kind, s32 c) {
    s32 index = kind - 0x28;
    if (lbl_80366158._28 != 1) {
        fn_8004B1C0(lbl_80108BF0[index][obj->_252], obj, kind, c);
    }
}

// .text:0x80062ED4 size:0x64
// NONMATCHING 90%: r8/r9 swapped; jump table is in another unit's .data
#if NONMATCHING
s32 fn_80062ED4(void* player, GameActor** actorp) {
    GameBone* bone;
    s32 i;
    GameActor* actor = *actorp;

    for (i = 0; i < actor->totalBones; i++) {
        bone = actor->boneArray[i];
        switch (bone->boneID) {
        case 0x41:
        case 0x43:
        case 0x45:
        case 0x47:
        case 0x49:
        case 0x4B:
            bone->rotAxis = 2;
            break;
        }
    }
    return 0;
}
#endif

// .text:0x80062F38 size:0xD8
s32 fn_80062F38(GameBone* bone, GameBone* target, Mtx m, f32 t) {
    switch (bone->boneID) {
    case 0x46:
        fn_800B84AC(&target->animCtrl, &target->blendCtrl, &target->animCtrl, t);
        CTRLBuildMatrix_Flip(&target->animCtrl, m, 0);
        return 1;
    case 0x4A:
        fn_800B84AC(&target->animCtrl, &target->blendCtrl, &target->animCtrl, t);
        CTRLBuildMatrix_Flip(&target->animCtrl, m, 0);
        return 1;
    case 0x4C:
        fn_800B84AC(&target->animCtrl, &target->blendCtrl, &target->animCtrl, t);
        CTRLBuildMatrix_Flip(&target->animCtrl, m, 0);
        return 1;
    }
    return 0;
}

// .text:0x80063010 size:0x18
s32 fn_80063010(void* player, GameActor** actor) {
    (*actor)->boneCallback = fn_80062F38;
    return 0;
}
