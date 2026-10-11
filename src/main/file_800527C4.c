#include "main/file_80069BDC.h"
#include "main/file_800527C4.h"
#include "main/file_8004207C.h"
// UnknownHomes_Static.h declares fn_80021518 with placeholder argument types;
// use the real prototype from file_80021308.h instead.
#define fn_80021518 fn_80021518_placeholder
#include "static/UnknownHomes_Static.h"
#undef fn_80021518
#include "main/file_80021308.h"
#include "main/file_80008E00.h"
#include "C3/control.h"
#include "main/file_8000F150.h"
#include "main/file_8004207C.h"
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

extern camera_803c639c_s lbl_803C639C[4];
extern Unk803C60BC lbl_803C60BC;
extern s32 lbl_803CB880; // number of active cameras
extern MenuDef lbl_800FEF70[0x5D];
extern u8 lbl_80361B20[0xF8];
extern struct SpaniDesc lbl_80108048;
extern struct SpaniDesc lbl_800FEB30;
extern struct SpaniDesc lbl_80107688;
extern struct SpaniDesc lbl_801000A8;
extern struct SpaniDesc lbl_801041C8;
extern struct SpaniDesc lbl_800FF540;
extern u8 lbl_802E4BB0[16];
extern ChallengeMission lbl_8010A768[20][10];
extern s16 lbl_8010B3E8[];
extern s32 determineIfMissionDescriptionIsShown(s16 charID);
extern s32 challengeRelated(s16 team);
extern s32 fn_80064918(s16 charID);
extern void challengeDrawStarsOnMissionMenu(void);
extern u8 lbl_800EFBA4[16]; // sound volumes

extern void fn_80034E20(SceneTask* task, struct SpaniDesc* desc);
extern void fn_8006CF6C(void);
extern void makeLookAtMatrix(Mtx m, Vec* eye, Vec* up, Vec* target);
extern void fn_80011640(Mtx src, Mtx dst);
extern void fn_800369DC(f32 zoom);
extern s16 translateStarPitch(u8 star);
extern s8 translateStarPitchHitIndex(u8 star);
extern s16 translateStarSwing(u8 star);

// Layout object number n of a task's sprite run.
#define TASK_OBJ(task, n) (lbl_80371C30[(task)->u14.objIdx + (n)].obj)

// Pause-menu object index: the in-game layout puts the same object 0x69 earlier.
#define PAUSE_OBJ(n) (g_d_GameSettings._06 == 2 ? (n) - 0x69 : (n))

static inline BOOL ObjFrameReached(SceneTask* task, s32 idx, s32 frame) {
    return fn_80042D68((LayoutOwner*)task, idx, frame) != 0;
}

static inline BOOL ObjAtFrame(SceneTask* task, s32 idx, s32 frame) {
    return fn_80042DA8((LayoutOwner*)task, idx, frame) != 0;
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
// NONMATCHING 97%: only add operand order (objIdx + n) and register swaps differ
#if NONMATCHING
void fn_800531D0(SceneTask* task) {
    s32 i;
    u32 len;

    if (lbl_800FEF70[lbl_8034E978.menu].textStart != 0xFFFF) {
        if (lbl_8034E978.descState == 0) {
            for (i = 0; i < lbl_8034E978.textCount; i++) {
                TASK_OBJ(task, i + 0x16)->flags |= 2;
            }
            TASK_OBJ(task, 9)->flags |= 2;
            if ((TASK_OBJ(task, 9)->_5C >> 16) == 15) {
                if (lbl_8034E978._23 == 0) {
                    len = fn_8000FA9C(lbl_8034E978.text[0]);
                    for (i = 0; i < 10; i++) {
                        lbl_8034E978.textDone[i] = 0xFF;
                    }
                    lbl_8034E978.textCur = 0;
                    TASK_OBJ(task, 10)->_5C = len << 16;
                    TASK_OBJ(task, 10)->_68 = 0;
                    TASK_OBJ(task, 21)->_5C = 0;
                    TASK_OBJ(task, 21)->flags |= 2;
                    if (lbl_800FEF70[lbl_8034E978.menu]._0E != 0) {
                        TASK_OBJ(task, 21)->_68 = 1;
                        lbl_8034E978._23 = 1;
                    } else {
                        TASK_OBJ(task, 21)->_68 = 0;
                    }
                }
                if ((TASK_OBJ(task, 21)->_5C >> 16) > 15 && lbl_8034E978._23 != 0) {
                    lbl_8034E978.descState = 1;
                    lbl_8034E978._23 = 0;
                    return;
                }
            }
        } else if (lbl_8034E978.descState == 1) {
            if ((TASK_OBJ(task, 21)->_5C >> 16) == 0x73) {
                lbl_8034E978.descState = 2;
                TASK_OBJ(task, 10)->_68 = 1;
                return;
            }
        } else if (lbl_8034E978.descState == 2) {
            fn_8000FA9C(lbl_8034E978.text[lbl_8034E978.textCur]);
            if ((TASK_OBJ(task, lbl_8034E978.textCur + 10)->_5C >> 16) > fn_8000FA9C(lbl_8034E978.text[lbl_8034E978.textCur])) {
                lbl_8034E978.textDone[lbl_8034E978.textCur] = lbl_8034E978.textCur;
                if (++lbl_8034E978.textCur == lbl_8034E978.textCount) {
                    lbl_8034E978.textCur = 0;
                }
                TASK_OBJ(task, lbl_8034E978.textCur + 10)->flags |= 2;
                TASK_OBJ(task, lbl_8034E978.textCur + 10)->_5C = 0;
                TASK_OBJ(task, lbl_8034E978.textCur + 10)->_68 = 1;
            }
            for (i = 0; i < 10; i++) {
                if (lbl_8034E978.textDone[i] != 0xFF) {
                    LayoutObj* obj = TASK_OBJ(task, lbl_8034E978.textDone[i] + 10);
                    if ((obj->_5C >> 16) == 0x500) {
                        obj->_5C = 0;
                        TASK_OBJ(task, lbl_8034E978.textDone[i] + 10)->_68 = 0;
                        TASK_OBJ(task, lbl_8034E978.textDone[i] + 10)->flags &= ~2;
                    }
                }
            }
            return;
        }
    } else if (lbl_8034E978.descState != 0) {
        for (i = 0; i < 10; i++) {
            TASK_OBJ(task, i + 0x16)->flags &= ~2;
            TASK_OBJ(task, i + 10)->_5C = 0;
            TASK_OBJ(task, i + 10)->_68 = 0;
        }
        TASK_OBJ(task, 9)->flags &= ~2;
        TASK_OBJ(task, 21)->_5C = 0;
        TASK_OBJ(task, 21)->_68 = 0;
        lbl_8034E978.descState = 0;
    }
}
#endif

// .text:0x80053810 size:0x7D8
// The original inlines fn_80042D68/fn_80042DA8 (frame checks) here.
// NONMATCHING 85%: the original inlines the fn_80042D68/fn_80042DA8 frame checks; ours calls them
#if NONMATCHING
void fn_80053810(void) {
    SceneTask* task = lbl_803CC1B8;
    s32 i;

    if (lbl_8034E978._26 != 0) {
        lbl_8034E978._26 = 0;
    } else {
        switch (lbl_8034E978._06) {
        case 0:
            if (lbl_8034E978._04 == 0) {
                lbl_8034E978._04 = 1;
                TASK_OBJ(task, 0)->_5C = 0;
            }
            if (lbl_8034E978._05 != 0) {
                TASK_OBJ(task, 0)->_68 = 1;
                TASK_OBJ(task, 9)->_68 = 4;
                lbl_8034E978._05 = 0;
                lbl_8034E978._24 = 1;
            }
            if (lbl_8034E978._24 == 0) {
                fn_80042D68((LayoutOwner*)task, 0, 20);
            } else if ((fn_80042D68((LayoutOwner*)task, 0, 40) != 0) + (fn_80042DA8((LayoutOwner*)task, 9, 0) != 0) == 2) {
                lbl_8034E978._24 = 0;
                lbl_8034E978._04 = 0;
                lbl_8034E978._25 = 1;
            }
            if (lbl_8034E978.prevMenu != lbl_8034E978.menu || lbl_8034E978.prev03 != lbl_8034E978._03) {
                TASK_OBJ(task, 6)->_5C = (lbl_8034E978._03 + lbl_800FEF70[lbl_8034E978.menu]._00) << 16;
                fn_800363D8(task, 5, 1, 0xEF, lbl_800FEF70[lbl_8034E978.menu]._02);
                TASK_OBJ(task, 5)->_5C = lbl_800FEF70[lbl_8034E978.menu]._06 << 16;
                TASK_OBJ(task, 6)->_5C = lbl_800FEF70[lbl_8034E978.menu]._04 << 16;
                TASK_OBJ(task, 1)->_5C = 0;
                TASK_OBJ(task, 2)->_5C = 10 << 16;
                TASK_OBJ(task, 1)->_68 = 1;
                TASK_OBJ(task, 2)->_68 = 4;
                TASK_OBJ(task, 7)->_5C = lbl_8034E978.track << 16;
                if (lbl_8034E978._27 != 0) {
                    TASK_OBJ(task, 8)->_5C = lbl_8034E978.track << 16;
                    lbl_8034E978._27 = 0;
                } else {
                    TASK_OBJ(task, 8)->_5C = lbl_8034E978.prevTrack << 16;
                }
                lbl_8034E978.textCount = lbl_800FEF70[lbl_8034E978.menu].textEnd - lbl_800FEF70[lbl_8034E978.menu].textStart;
                if (lbl_8034E978.textCount == 0) {
                    TASK_OBJ(task, 9)->flags &= ~2;
                }
                for (i = 0; i < 10; i++) {
                    if (i < lbl_8034E978.textCount) {
                        TASK_OBJ(task, i + 0x16)->flags |= 2;
                        if (lbl_8034E978.text[i] != -1) {
                            fn_8000FE08(lbl_8034E978.text[i], 0, i + lbl_800FEF70[lbl_8034E978.menu].textStart);
                        } else {
                            lbl_8034E978.text[i] = fn_8000F988((LayoutGroup*)task, i + 0x16, 0, 0, i + lbl_800FEF70[lbl_8034E978.menu].textStart, 0);
                        }
                    } else {
                        TASK_OBJ(task, i + 0x16)->flags &= ~2;
                    }
                    if (i == 0) {
                        TASK_OBJ(task, i + 10)->flags |= 2;
                    }
                    TASK_OBJ(task, i + 10)->_5C = 0;
                    TASK_OBJ(task, i + 10)->_68 = 0;
                    if (i != 0) {
                        TASK_OBJ(task, i + 10)->_5C = 0;
                        TASK_OBJ(task, i + 10)->flags &= ~2;
                        TASK_OBJ(task, i + 0x16)->_5C = 0;
                        TASK_OBJ(task, i + 0x16)->flags &= ~2;
                    }
                }
                lbl_8034E978.descState = 0;
                lbl_8034E978._23 = 0;
            }
            fn_800531D0(task);
            break;
        case 1:
            if (lbl_8034E978._07 == 0) {
                TASK_OBJ(task, 0)->_68 = 4;
                TASK_OBJ(task, 3)->flags &= ~2;
                lbl_8034E978._07 = 1;
            } else if ((fn_80042DA8((LayoutOwner*)task, 0, 0) != 0) == 1) {
                lbl_8034E978._07 = 0;
                lbl_8034E978._06 = 0;
            }
            break;
        case 2:
            if (lbl_8034E978._07 == 0) {
                TASK_OBJ(task, 0)->_68 = 1;
                TASK_OBJ(task, 3)->flags |= 2;
                lbl_8034E978._07 = 1;
            } else if ((fn_80042D68((LayoutOwner*)task, 0, 20) != 0) == 1) {
                lbl_8034E978._07 = 0;
                lbl_8034E978._06 = 0;
            }
            break;
        }
        lbl_8034E978.prevMenu = lbl_8034E978.menu;
        lbl_8034E978.prev03 = lbl_8034E978._03;
        if (lbl_8034E978._25 == 0) {
            return;
        }
    }
    lbl_8034E978.prevMenu = 0;
    lbl_8034E978.menu = 0;
    lbl_8034E978.descState = 0;
    lbl_8034E978._21[0] = 0;
    lbl_8034E978._21[1] = 0;
    lbl_8034E978._03 = 0;
    for (i = 0; i < 10; i++) {
        fn_8000FEE8(lbl_8034E978.text[i]);
    }
    fn_8000F8F4((LayoutGroup*)task);
    fn_800B0A14_removeQueue(fn_80034CEC(task));
}
#endif

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
// NONMATCHING 93%: the i != a tests use a cntlzw/xori boolean in the original; registers differ
#if NONMATCHING
void fn_800542C4(u8 cur, u8 target, SceneTask* task) {
    s8 a = lbl_803C5F04.option[cur];
    s32 i;

    switch (cur) {
    case 1:
        for (i = 0; i < 2; i++) {
            TASK_OBJ(task, i + 0xC)->_64 = 0x106;
            if (i == a) {
                TASK_OBJ(task, i + 0xC)->_68 = 1;
            } else if (cur == target) {
                TASK_OBJ(task, i + 0xC)->_5C = 10 << 16;
                TASK_OBJ(task, i + 0xC)->_68 = 4;
            }
            if (cur == target) {
                if (a != 0) {
                    TASK_OBJ(task, 26)->_5C = 25 << 16;
                    TASK_OBJ(task, 26)->_68 = 4;
                } else {
                    TASK_OBJ(task, 26)->_5C = 5 << 16;
                    TASK_OBJ(task, 26)->_68 = 1;
                }
            }
        }
        return;
    case 2:
        for (i = 0; i < 2; i++) {
            TASK_OBJ(task, i + 0xE)->_64 = 0x106;
            if (i != a) {
                TASK_OBJ(task, i + 0xE)->_68 = 1;
            } else if (cur == target) {
                TASK_OBJ(task, i + 0xE)->_5C = 10 << 16;
                TASK_OBJ(task, i + 0xE)->_68 = 4;
            }
        }
        TASK_OBJ(task, 32)->_5C = 0;
        TASK_OBJ(task, 35)->_5C = 10 << 16;
        fn_800363D8(task, 0x20, 1, 0xF9, lbl_803C5F04.option[2] ^ 1);
        fn_800363D8(task, 0x23, 1, 0xF9, lbl_803C5F04.prevOption[2] ^ 1);
        TASK_OBJ(task, 32)->_68 = 1;
        TASK_OBJ(task, 35)->_68 = 4;
        return;
    case 3:
        for (i = 0; i < 5; i++) {
            if (i == a) {
                TASK_OBJ(task, i + 0x10)->_64 = 0x108;
                TASK_OBJ(task, i + 0x10)->_68 = 1;
            } else if (i == lbl_803C5F04.prevOption[cur] && cur == target) {
                TASK_OBJ(task, i + 0x10)->_64 = 0x108;
                TASK_OBJ(task, i + 0x10)->_5C = 10 << 16;
                TASK_OBJ(task, i + 0x10)->_68 = 4;
            }
        }
        TASK_OBJ(task, 33)->_5C = 0;
        TASK_OBJ(task, 36)->_5C = 10 << 16;
        fn_800363D8(task, 0x21, 1, 0xF9, lbl_803C5F04.option[3] + 2);
        fn_800363D8(task, 0x24, 1, 0xF9, lbl_803C5F04.prevOption[3] + 2);
        TASK_OBJ(task, 33)->_68 = 1;
        TASK_OBJ(task, 36)->_68 = 4;
        return;
    case 4:
        for (i = 0; i < 2; i++) {
            TASK_OBJ(task, i + 0x15)->_64 = 0x106;
            if (i != a) {
                TASK_OBJ(task, i + 0x15)->_68 = 1;
            } else if (cur == target) {
                TASK_OBJ(task, i + 0x15)->_5C = 10 << 16;
                TASK_OBJ(task, i + 0x15)->_68 = 4;
            }
        }
        TASK_OBJ(task, 34)->_5C = 0;
        TASK_OBJ(task, 37)->_5C = 10 << 16;
        fn_800363D8(task, 0x22, 1, 0xF9, lbl_803C5F04.option[4] ^ 1);
        fn_800363D8(task, 0x25, 1, 0xF9, lbl_803C5F04.prevOption[4] ^ 1);
        TASK_OBJ(task, 34)->_68 = 1;
        TASK_OBJ(task, 37)->_68 = 4;
        return;
    }
}
#endif

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
        cur = lbl_803C5F04.cursor[port];
        target = lbl_803C5F04.prevCursor[port];
        if (cur != 0) {
            if (lbl_803C5F04._36 == 0) {
                a = lbl_803C5F04.option[cur];
                b = lbl_803C5F04.prevOption[target];
            } else {
                a = lbl_803C5F04.playerOption[port][cur];
                b = lbl_803C5F04.prevPlayerOption[port][target];
            }
        }
        done = FALSE;
        expected = FALSE;
        if (target == cur && a != b) {
            if (lbl_803C5F04._36 == 0 && cur != 0) {
                switch (cur) {
                case 1:
                    if (a != 0) {
                        done = fn_80042DA8((LayoutOwner*)task, 0x1A, 5) != 0;
                        expected = TRUE;
                    } else {
                        done = fn_80042DA8((LayoutOwner*)task, 0x1A, 0x19) != 0;
                        expected = TRUE;
                    }
                    break;
                }
            } else if (lbl_803C5F04._36 == 1) {
                if (lbl_803C5F04.lastDir[port] == 0) {
                    done = fn_80042DA8((LayoutOwner*)task, cur + port * 4 + 0x33, 0) != 0;
                    expected = TRUE;
                } else {
                    done = fn_80042DA8((LayoutOwner*)task, cur + port * 4 + 0x33, 10) != 0;
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

// Highlights the chosen option of tutorial question n (shared by fn_80054B00).
static inline void ShowTutorialChoice(SceneTask* task, s8 n) {
    s8 a = lbl_803C5F04.option[n];
    switch (n) {
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
}

// .text:0x80054B00 size:0x874
// NONMATCHING 85%: object index sums fold differently; registers differ
#if NONMATCHING
void fn_80054B00(SceneTask* task, s32 port) {
    u8* state = (u8*)&lbl_803C66B0 + port; // becomes &steps[8][port + 1]
    s8 cur;
    s8 target;
    s8 a = 0; // left unset in the original; only compared when set
    s8 b = 0;

    if ((*(state += 0x31) == 0) ? TRUE : FALSE) {
        cur = lbl_803C5F04.cursor[port];
        target = lbl_803C5F04.prevCursor[port];
        if (cur != 0) {
            if (lbl_803C5F04._36 == 0) {
                a = lbl_803C5F04.option[cur];
                b = lbl_803C5F04.prevOption[target];
            } else {
                a = lbl_803C5F04.playerOption[port][cur];
                b = lbl_803C5F04.prevPlayerOption[port][target];
            }
        } else if (lbl_803C5F04._36 == 1) {
            a = lbl_803C5F04.playerOption[port][cur];
            b = lbl_803C5F04.prevPlayerOption[port][target];
        }
        if (cur != target) {
            if (lbl_803C5F04._36 == 0) {
                if (cur == 0) {
                    TASK_OBJ(task, target + 1)->_5C = 0;
                    TASK_OBJ(task, target + 1)->_68 = 0;
                    TASK_OBJ(task, 11)->_5C = 0;
                    TASK_OBJ(task, 11)->_68 = 1;
                    ShowTutorialChoice(task, target);
                } else if (target == 0) {
                    TASK_OBJ(task, cur + 1)->_68 = 1;
                    TASK_OBJ(task, 11)->_5C = 10 << 16;
                    TASK_OBJ(task, 11)->_68 = 4;
                } else {
                    TASK_OBJ(task, cur + 1)->_68 = 1;
                    TASK_OBJ(task, target + 1)->_5C = 0;
                    TASK_OBJ(task, target + 1)->_68 = 0;
                    ShowTutorialChoice(task, target);
                }
            } else {
                if (port == 0) {
                    TASK_OBJ(task, 11)->_5C = 0;
                    TASK_OBJ(task, 11)->_68 = 0;
                }
                TASK_OBJ(task, cur + port * 4 + 0x2B)->_68 = 1;
                TASK_OBJ(task, cur * 2 + port + 0x3F)->_68 = 1;
                TASK_OBJ(task, target + port * 4 + 0x2B)->_5C = 0;
                TASK_OBJ(task, target + port * 4 + 0x2B)->_68 = 0;
                TASK_OBJ(task, target * 2 + port + 0x3F)->_68 = 4;
            }
            if (lbl_803C5F04._36 == 0) {
                fn_800542C4(cur, target, task);
            }
        } else if (target == cur && a != b) {
            if (lbl_803C5F04._36 == 0 && cur != 0) {
                fn_800542C4(cur, target, task);
            } else if (lbl_803C5F04._36 == 1) {
                if (lbl_803C5F04.lastDir[port] == 0) {
                    TASK_OBJ(task, cur + port * 4 + 0x33)->_68 = 4;
                    TASK_OBJ(task, cur * 4 + port + 0x47)->flags &= ~2;
                    TASK_OBJ(task, cur * 4 + port + 0x49)->flags |= 2;
                    TASK_OBJ(task, cur * 4 + port + 0x47)->_68 = 0;
                    TASK_OBJ(task, cur * 4 + port + 0x49)->_68 = 1;
                } else {
                    TASK_OBJ(task, cur + port * 4 + 0x33)->_68 = 1;
                    TASK_OBJ(task, cur * 4 + port + 0x47)->flags |= 2;
                    TASK_OBJ(task, cur * 4 + port + 0x49)->flags &= ~2;
                    TASK_OBJ(task, cur * 4 + port + 0x47)->_68 = 1;
                    TASK_OBJ(task, cur * 4 + port + 0x49)->_68 = 0;
                }
            }
        }
        fn_800626EC(port);
        *state = 1;
    }
}
#endif

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
        target = lbl_803C5F04.prevCursor[port];
        lbl_803C5F04.prevCursor[port] = 0;
        TASK_OBJ(task, target + 1)->_5C = 0;
        TASK_OBJ(task, target + 1)->_68 = 0;
        a = lbl_803C5F04.option[target];
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
                TASK_OBJ(task, lbl_803C5F04.cursor[p] + p * 4 + 0x2B)->_68 = 1;
                TASK_OBJ(task, lbl_803C5F04.cursor[p] * 2 + p + 0x3F)->_68 = 1;
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
        if (lbl_803C5F04._36 == 0) {
            if (lbl_803C5F04.option[1] == 1) {
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
// NONMATCHING 88%: loop registers differ (state pointer kept as step+0x31 offset in the original)
#if NONMATCHING
void fn_800559EC(void) {
    SceneTask* task = lbl_803CC1B8;
    s32 port;
    u8* step;
    s32 done;
    s32 expected;

    for (port = 0, step = lbl_803C66B0.step; port < 2; port++, step++) {
        u8* state = &lbl_803C66B0.steps[8][port + 1];
        switch (*step) {
        case 41:
            fn_80055798(task, port);
            if (*state == 1) {
                done = 0;
                expected = 0;
                if (lbl_803C5F04._36 == 0) {
                    if (lbl_803C5F04.option[1] == 1) {
                        expected = 1;
                        done = fn_80042DA8((LayoutOwner*)task, 0x1A, 5) != 0;
                    } else {
                        expected = 1;
                        done = fn_80042DA8((LayoutOwner*)task, 0x1A, 0x19) != 0;
                    }
                    if (g_d_GameSettings._06 != 2 && g_d_GameSettings.GameModeSelected == 5) {
                        expected = 2;
                        done += fn_80042DA8((LayoutOwner*)task, 0x57, 20) != 0;
                    }
                }
                done += fn_80042DA8((LayoutOwner*)task, 0x1B, 0x21) != 0;
                if (done + (fn_80042DA8((LayoutOwner*)task, 0x58, 10) != 0) == expected + 2) {
                    fn_80062674(port);
                    *state = 2;
                }
            }
            break;
        case 42:
            if (*state == 0) {
                if (lbl_803C5F04._36 == 0) {
                    TASK_OBJ(task, 0)->_68 = 4;
                    if (lbl_803C5F04.option[1] == 1) {
                        TASK_OBJ(task, 26)->_68 = 4;
                    } else {
                        TASK_OBJ(task, 26)->_68 = 1;
                    }
                } else {
                    TASK_OBJ(task, 38)->_68 = 4;
                }
                TASK_OBJ(task, 6)->_68 = 4;
                TASK_OBJ(task, 27)->_68 = 4;
                TASK_OBJ(task, 23)->_68 = 4;
                TASK_OBJ(task, 28)->_68 = 4;
                if (g_d_GameSettings._06 != 2 && g_d_GameSettings.GameModeSelected == 5) {
                    TASK_OBJ(task, 87)->_5C = 20 << 16;
                    TASK_OBJ(task, 87)->_68 = 1;
                }
                fn_800626EC(port);
                *state = 1;
            }
            if (*state == 1) {
                done = 0;
                expected = 0;
                if (lbl_803C5F04._36 == 0) {
                    if (lbl_803C5F04.option[1] == 1) {
                        expected = 1;
                        done = fn_80042DA8((LayoutOwner*)task, 0x1A, 0) != 0;
                    } else {
                        expected = 1;
                        done = fn_80042DA8((LayoutOwner*)task, 0x1A, 30) != 0;
                    }
                }
                expected += 1;
                done += fn_80042DA8((LayoutOwner*)task, 0x1B, 0) != 0;
                if (g_d_GameSettings._06 != 2 && g_d_GameSettings.GameModeSelected == 5) {
                    expected += 1;
                    done += fn_80042DA8((LayoutOwner*)task, 0x57, 30) != 0;
                }
                if (done == expected) {
                    lbl_803C5EE0._15 = 1;
                    fn_80062674(port);
                    *state = 2;
                }
            }
            break;
        case 43:
            fn_80055374(task, port);
            if (*state == 1 && ObjAtFrame(task, 0x58, 20) == 1) {
                fn_80062674(port);
                *state = 2;
            }
            break;
        case 44:
            if (lbl_803C66B0.steps[8][1] == 0) {
                s8 cur0;
                s8 cur1;

                cur1 = lbl_803C5F04.cursor[1];
                lbl_803C5F04.prevCursor[1] = 0;
                cur0 = lbl_803C5F04.cursor[0];
                lbl_803C5F04.cursor[1] = 0;
                lbl_803C5F04.prevCursor[0] = 0;
                lbl_803C5F04.cursor[0] = 0;
                TASK_OBJ(task, 38)->_68 = 4;
                TASK_OBJ(task, 41)->_68 = 4;
                TASK_OBJ(task, 42)->_68 = 4;
                TASK_OBJ(task, 11)->flags |= 2;
                TASK_OBJ(task, 11)->_68 = 1;
                TASK_OBJ(task, cur0 + 0x2B)->_5C = 10 << 16;
                TASK_OBJ(task, cur0 + 0x2B)->_68 = 4;
                TASK_OBJ(task, cur0 * 2 + 0x3F)->_68 = 4;
                if (((u8*)&g_d_GameSettings)[0x10] == 1) { // TODO type
                    TASK_OBJ(task, cur1 + 0x2F)->_5C = 10 << 16;
                    TASK_OBJ(task, cur1 + 0x2F)->_68 = 4;
                    TASK_OBJ(task, cur1 * 2 + 0x40)->_68 = 4;
                }
                TASK_OBJ(task, 0)->_68 = 1;
                TASK_OBJ(task, 88)->_68 = 4;
                fn_800626EC(0);
                lbl_803C66B0.steps[8][1] = 1;
            }
            if (lbl_803C66B0.steps[8][1] == 1 && ObjAtFrame(task, 0x58, 10) == 1) {
                fn_80062674(0);
                lbl_803C66B0.steps[8][1] = 2;
            }
            break;
        case 48:
            fn_80054B00(task, port);
            fn_80054910(task, port);
            break;
        case 49:
            if (*state == 0) {
                TASK_OBJ(task, 0)->_68 = 4;
                TASK_OBJ(task, 6)->_68 = 4;
                TASK_OBJ(task, 11)->_5C = 10 << 16;
                TASK_OBJ(task, 11)->_68 = 4;
                TASK_OBJ(task, 27)->_68 = 1;
                if (lbl_803C5F04._36 == 0) {
                    TASK_OBJ(task, 88)->_68 = 4;
                } else {
                    TASK_OBJ(task, 88)->_68 = 1;
                }
                fn_800626EC(port);
                *state = 1;
            }
            if (*state == 1 && g_d_GameSettings.GameModeSelected != 0) {
                fn_80062674(port);
                *state = 2;
            }
            break;
        }
    }
    if (lbl_803C5EE0._15 != 0) {
        lbl_803C5EE0._15 = 0;
        fn_800B0A14_removeQueue(fn_80034CEC(task));
    }
}
#endif

// .text:0x80056120 size:0x8A8
// NONMATCHING 80%: copy of tblC written as a loop; index sums and registers differ
#if NONMATCHING
void fn_80056120(void) {
    SceneTask* task;
    s32 i;
    s32 p;
    s32 j;
    s8 v;

    lbl_803C5EE0.cursor[0] = lbl_803C5F04.cursor[0];
    for (p = 0; p < 4; p++) {
        for (j = 0; j < 4; j++) {
            lbl_802E4BB0[p * 4 + j] = lbl_803C5F04.playerOption[p][j];
        }
    }
    task = lbl_803CC1B8;
    lbl_802E4BB0[2] = lbl_803C5F04.option[2];
    lbl_802E4BB0[3] = lbl_803C5F04.option[3];
    lbl_802E4BB0[4] = lbl_803C5F04.option[4];
    lbl_803C5EE0.cursor[1] = lbl_803C5F04.cursor[1];
    lbl_803C5EE0.cursor[2] = lbl_803C5F04.cursor[2];
    lbl_803C5EE0.cursor[3] = lbl_803C5F04.cursor[3];
    fn_80034E20(task, &lbl_800FF540);
    for (i = 1; i < 5; i++) {
        fn_800363D8(task, i + 1, 1, 0x110, i - 1);
        if (i > 1) {
            TASK_OBJ(task, i + 0x1B)->_5C = (i - 2) << 16;
            TASK_OBJ(task, i + 0x1B)->flags &= ~2;
        }
    }
    TASK_OBJ(task, lbl_803C5F04.option[1] + 0xC)->_64 = 0x107;
    TASK_OBJ(task, (lbl_803C5F04.option[2] ^ 1) + 0xE)->_64 = 0x107;
    fn_800363D8(task, 0x20, 1, 0xF9, lbl_803C5F04.option[2] ^ 1);
    TASK_OBJ(task, lbl_803C5F04.option[3] + 0x10)->_64 = 0x109;
    fn_800363D8(task, 0x21, 1, 0xF9, lbl_803C5F04.option[3] + 2);
    TASK_OBJ(task, (lbl_803C5F04.option[4] ^ 1) + 0x15)->_64 = 0x107;
    fn_800363D8(task, 0x22, 1, 0xF9, lbl_803C5F04.option[4] ^ 1);
    for (p = 0; p < 2; p++) {
        if (((u8*)&g_d_GameSettings)[0x10] == 0 && p != 0) { // TODO type
            fn_800363D8(task, p + 0xC, 1, 0x116, 0xD);
        } else {
            fn_800363D8(task, p + 0xC, 1, 0x116, lbl_8034E9A0.teamPort[p] + 9);
        }
        fn_800363D8(task, p + 0xE, 1, 0x116, p + 2);
        fn_800363D8(task, p + 0x15, 1, 0x116, p + 2);
    }
    for (i = 0; i < 5; i++) {
        fn_800363D8(task, i + 0x10, 1, 0x116, i + 4);
    }
    TASK_OBJ(task, 0x18)->_5C = lbl_8034E9A0._470D[0] << 16;
    TASK_OBJ(task, 0x19)->_5C = lbl_8034E9A0._470D[1] << 16;
    for (p = 0; p < 2; p++) {
        if (((u8*)&g_d_GameSettings)[0x10] == 0 && p != 0) { // TODO type
            if (lbl_8034E9A0.teamPort[0] == 0) {
                fn_800363D8(task, p + 0x27, 1, 0x46, 5);
            } else {
                fn_800363D8(task, p + 0x27, 1, 0x46, 4);
            }
        } else {
            fn_800363D8(task, p + 0x27, 1, 0x46, lbl_8034E9A0.teamPort[p]);
        }
        if (g_d_GameSettings.GameModeSelected == 5 && p != 0) {
            v = gChallengeState._441F;
        } else {
            v = lbl_8034E9A0._46E0[p][0];
        }
        TASK_OBJ(task, p + 0x3D)->_5C = v << 16;
        fn_800363D8(task, p * 4 + 0x2B, 1, 0x11A, 0);
        fn_800363D8(task, p * 4 + 0x2C, 1, 0x11A, 1);
        fn_800363D8(task, p * 4 + 0x2D, 1, 0x11A, 2);
        fn_800363D8(task, p * 4 + 0x2E, 1, 0x11A, 3);
        for (j = 0; j < 4; j++) {
            s8 c = lbl_803C5F04.playerOption[p][j];
            if (j == 0) {
                fn_800363D8(task, j + p * 4 + 0x33, 1, 0x116, 1);
                fn_800363D8(task, j + p * 4 + 0x33, 2, 0x116, 0);
                TASK_OBJ(task, j + p * 4 + 0x33)->_5C = c * (10 << 16);
            } else if (j == 3) {
                fn_800363D8(task, j + p * 4 + 0x33, 1, 0x116, 2);
                fn_800363D8(task, j + p * 4 + 0x33, 2, 0x116, 3);
                TASK_OBJ(task, j + p * 4 + 0x33)->_5C = (c ^ 1) * (10 << 16);
            } else {
                fn_800363D8(task, j + p * 4 + 0x33, 1, 0x116, 1);
                fn_800363D8(task, j + p * 4 + 0x33, 2, 0x116, 0xE);
                TASK_OBJ(task, j + p * 4 + 0x33)->_5C = c * (10 << 16);
            }
            if (lbl_803C5F04.playerOption[p][j] != 0) {
                if (j != 3) {
                    TASK_OBJ(task, j * 4 + p + 0x47)->flags |= 2;
                    TASK_OBJ(task, j * 4 + p + 0x49)->flags &= ~2;
                } else {
                    TASK_OBJ(task, j * 4 + p + 0x47)->flags &= ~2;
                    TASK_OBJ(task, j * 4 + p + 0x49)->flags |= 2;
                }
            } else if (j != 3) {
                TASK_OBJ(task, j * 4 + p + 0x47)->flags &= ~2;
                TASK_OBJ(task, j * 4 + p + 0x49)->flags |= 2;
            } else {
                TASK_OBJ(task, j * 4 + p + 0x47)->flags |= 2;
                TASK_OBJ(task, j * 4 + p + 0x49)->flags &= ~2;
            }
        }
    }
    if (g_d_GameSettings.GameModeSelected == 5) {
        fn_800363D8(task, 0x57, 1, 0x20, g_d_GameSettings.StadiumID);
    } else {
        TASK_OBJ(task, 87)->flags &= ~2;
    }
    lbl_803C5EE0._15 = 0;
    lbl_803CC1B8->func = fn_800559EC;
}
#endif

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
    CharacterStats* player = &inMemRoster[0][lbl_803297E0.slotCursor];
    s16 charID = player->stats.CharID;
    ChallengeTeamInfo* info = &lbl_800E8558[charID];
    u8 set;
    s8 rank;
    u16 msg;
    s32 i;

    lbl_803297E0._CF9C = info->_0[1];
    set = info->_2;
    rank = gChallengeState.trackers[lbl_803297E0._CF9C].variantClassification;
    switch (rank) {
    case 0:
        rank = 3;
        lbl_803297E0._CF9A = 10;
        break;
    case 1:
        rank = 2;
        lbl_803297E0._CF9A = 8;
        break;
    case 2:
        rank = 1;
        lbl_803297E0._CF9A = 6;
        break;
    case 3:
        rank = 0;
        lbl_803297E0._CF9A = 4;
        break;
    }
    TASK_OBJ(task, 31)->_5C = rank << 16;
    TASK_OBJ(task, 32)->_68 = 1;
    TASK_OBJ(task, 36)->_5C = lbl_8034E9A0.chars[(player->stats.CharID / 9) * 9 + (player->stats.CharID % 9)].stats.CharacterClass << 16;
    TASK_OBJ(task, 37)->_5C = charID << 16;
    TASK_OBJ(task, 38)->_5C = (4 - determineIfMissionDescriptionIsShown(charID)) << 16;
    if ((s8)gChallengeState.trackers[lbl_803297E0._CF9C].inGameMissionTracker[0].shownOnPauseMenu != 0) {
        msg = lbl_8010A768[(s16)set][0].msg;
    } else if (lbl_8010A768[(s16)set][0]._6 <= gChallengeState._4415) {
        msg = 0x1C5;
    } else {
        msg = 0x1C6;
    }
    if (lbl_803297E0._CF92 == 1) {
        lbl_803297E0.nameText = fn_8000F988((LayoutGroup*)task, 0x4F, 0, 0, charID + 8, 0);
        lbl_803297E0.descText = fn_8000F988((LayoutGroup*)task, 0x50, 1, 0, lbl_8010B3E8[info->_2] + challengeRelated(lbl_803297E0._CF9C), 0);
        lbl_803297E0.missionText = fn_8000F988((LayoutGroup*)task, 0x51, 0, 0, msg, 0);
        lbl_80366B18.entries[lbl_803297E0.missionText].hAlign = 1;
    } else {
        fn_8000FE08(lbl_803297E0.nameText, 0, charID + 8);
        fn_8000FE08(lbl_803297E0.descText, 0, lbl_8010B3E8[info->_2] + challengeRelated(lbl_803297E0._CF9C));
        fn_8000FE08(lbl_803297E0.missionText, 0, msg);
    }
    for (i = 0; i < lbl_803297E0._CF9A; i++) {
        if (challengeStarRelatedInd(lbl_803297E0._CF9C, i) != 0) {
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
        set = lbl_800E8558[lbl_803297E0._CF9C]._2;
        TASK_OBJ(task, 1)->_68 = 4;
        TASK_OBJ(task, 0)->_68 = 4;
        for (i = 0; i < lbl_803297E0._CF9A; i++) {
            TASK_OBJ(task, i + 0x31)->flags &= ~2;
            TASK_OBJ(task, i + 0x45)->_5C = 0;
            TASK_OBJ(task, i + 0x45)->flags &= ~2;
        }
        TASK_OBJ(task, 35)->flags &= ~2;
        if (challengeStarRelatedInd(lbl_803297E0._CF9C, lbl_803297E0.starCursor2) != 0) {
            TASK_OBJ(task, 35)->flags |= 2;
            TASK_OBJ(task, 35)->_5C = 0;
            TASK_OBJ(task, 35)->_68 = 1;
            TASK_OBJ(task, lbl_803297E0.starCursor2 + 0x31)->flags |= 2;
            TASK_OBJ(task, lbl_803297E0.starCursor2 + 0x31)->_5C = 0;
            TASK_OBJ(task, lbl_803297E0.starCursor2 + 0x31)->_68 = 1;
            TASK_OBJ(task, lbl_803297E0.starCursor2 + 0x45)->_5C = 1 << 16;
        }
        if (gChallengeState.trackers[lbl_803297E0._CF9C].inGameMissionTracker[lbl_803297E0.starCursor2].shownOnPauseMenu != 0) {
            msg = lbl_8010A768[(s16)set][lbl_803297E0.starCursor2].msg;
        } else if (challengeStarRelatedInd(lbl_803297E0._CF9C, lbl_803297E0.starCursor2) != 0) {
            msg = lbl_8010A768[(s16)set][lbl_803297E0.starCursor2].msg;
        } else if (lbl_8010A768[(s16)set][lbl_803297E0.starCursor2]._6 <= gChallengeState._4415) {
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
        set = lbl_800E8558[lbl_803297E0._CF9C]._2;
        if (challengeStarRelatedInd(lbl_803297E0._CF9C, lbl_803297E0.starCursor2) != 0) {
            TASK_OBJ(task, 35)->flags |= 2;
            TASK_OBJ(task, 35)->_5C = 0;
            TASK_OBJ(task, 35)->_68 = 1;
            TASK_OBJ(task, lbl_803297E0.starCursor2 + 0x31)->flags |= 2;
            TASK_OBJ(task, lbl_803297E0.starCursor2 + 0x31)->_5C = 0;
            TASK_OBJ(task, lbl_803297E0.starCursor2 + 0x31)->_68 = 1;
            TASK_OBJ(task, lbl_803297E0.starCursor2 + 0x45)->_5C = 1 << 16;
        } else {
            TASK_OBJ(task, 35)->flags &= ~2;
            TASK_OBJ(task, lbl_803297E0.starCursor2 + 0x31)->flags &= ~2;
            TASK_OBJ(task, lbl_803297E0.starCursor2 + 0x45)->_5C = 0;
        }
        TASK_OBJ(task, lbl_803297E0.starCursor2 + 0x45)->flags |= 2;
        TASK_OBJ(task, lbl_803297E0.starCursor2 + 0x45)->_68 = 1;
        if (challengeStarRelatedInd(lbl_803297E0._CF9C, lbl_803297E0.prevStarCursor2) != 0) {
            TASK_OBJ(task, lbl_803297E0.prevStarCursor2 + 0x31)->flags &= ~2;
            TASK_OBJ(task, lbl_803297E0.prevStarCursor2 + 0x27)->_5C = 0;
        } else {
            TASK_OBJ(task, lbl_803297E0.prevStarCursor2 + 0x27)->_5C = 0;
        }
        TASK_OBJ(task, lbl_803297E0.prevStarCursor2 + 0x45)->flags &= ~2;
        TASK_OBJ(task, lbl_803297E0.prevStarCursor2 + 0x45)->_68 = 1;
        if (gChallengeState.trackers[lbl_803297E0._CF9C].inGameMissionTracker[lbl_803297E0.starCursor2].shownOnPauseMenu != 0) {
            msg = lbl_8010A768[set][lbl_803297E0.starCursor2].msg;
        } else if (challengeStarRelatedInd(lbl_803297E0._CF9C, lbl_803297E0.starCursor2) != 0) {
            msg = lbl_8010A768[set][lbl_803297E0.starCursor2].msg;
        } else if (lbl_8010A768[set][lbl_803297E0.starCursor2]._6 <= gChallengeState._4415) {
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
            if (challengeStarRelatedInd(lbl_803297E0._CF9C, lbl_803297E0.starCursor2) != 0) {
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
            done = fn_80042DA8((LayoutOwner*)task, 1, 0) != 0;
            if (done + (fn_80042DA8((LayoutOwner*)task, 30, 0) != 0) == 2) {
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
            TASK_OBJ(task, lbl_803297E0.slotCursor + 3)->_5C = 0;
            TASK_OBJ(task, lbl_803297E0.slotCursor + 3)->_68 = 1;
            TASK_OBJ(task, lbl_803297E0.prevSlotCursor + 3)->_5C = 10 << 16;
            TASK_OBJ(task, lbl_803297E0.prevSlotCursor + 3)->_68 = 4;
            drawStarProgressionMenu(task);
            if (challengeStarRelatedInd(lbl_803297E0._CF9C, lbl_803297E0.starCursor2) != 0) {
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

    switch (lbl_803297E0._CF7D) {
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
            lbl_803297E0._CF7D = 2;
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
            lbl_803297E0._CF7D = 0;
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
            lbl_803297E0._CF7D = 0;
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

    if (lbl_803297E0._CF63[lbl_803297E0._CF3B] == 0) {
        TASK_OBJ(task, 302)->flags &= ~2;
        TASK_OBJ(task, 302)->_68 = 0;
        TASK_OBJ(task, 281)->_68 = 4;
        TASK_OBJ(task, 289)->_68 = 4;
        player = &inMemRoster[lbl_803297E0._CF3B][lbl_803297E0.slot[lbl_803297E0._CF3B] - 1];
        row = player->stats.CharID / 9;
        col = player->stats.CharID % 9;
        star = lbl_8034E9A0.chars[(row) * 9 + (col)].stats.CaptainStarHitPitch;
        if (star == 0) {
            swing = lbl_8034E9A0.chars[(row) * 9 + (col)].stats.NonCaptainStarSwing + 11;
            pitch = lbl_8034E9A0.chars[(row) * 9 + (col)].stats.NonCaptainStarPitch + 11;
        } else if (g_d_GameSettings.GameModeSelected != 5) {
            swing = star - 1;
            pitch = swing;
        } else {
            s8 idx;
            pitch = star - 1;
            idx = translateStarPitchHitIndex(pitch);
            if (idx != -1 && ((s8*)&gChallengeState)[0x43C2 + idx] == 0) { // TODO type
                swing = lbl_8034E9A0.chars[(row) * 9 + (col)].stats.NonCaptainStarSwing + 11;
                pitch = lbl_8034E9A0.chars[(row) * 9 + (col)].stats.NonCaptainStarPitch + 11;
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
        lbl_803297E0._CF63[lbl_803297E0._CF3B] = 1;
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

    if (lbl_803297E0._CF63[lbl_803297E0._CF3B] == 0) {
        player = &inMemRoster[lbl_803297E0._CF3B][lbl_803297E0.slot[lbl_803297E0._CF3B] - 1];
        charID = player->stats.CharID;
        fielding = player->stats.FieldingStats;
        pushPull = player->stats.HitTrajectoryPushPull;
        highLow = player->stats.HitTrajectoryHighLow;
        stance = player->stats.BattingStance;
        TASK_OBJ(task, 291)->_5C = charID << 16;
        TASK_OBJ(task, 292)->_5C = fn_80064918(charID) << 16;
        TASK_OBJ(task, 301)->_5C = charID << 16;
        fn_80059458(task, lbl_803297E0._CF3B, fielding);
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
        lbl_803297E0._CF63[lbl_803297E0._CF3B] = 1;
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

    if (lbl_803297E0._CF63[port] == 0) {
        TASK_OBJ(task, port + 0x1C6)->flags &= ~2;
        TASK_OBJ(task, port + 0x1C6)->_68 = 0;
        TASK_OBJ(task, port + 0x19C)->_68 = 4;
        TASK_OBJ(task, port + 0x1AC)->_68 = 4;
        player = &inMemRoster[port][lbl_803297E0.slot[port] - 1];
        row = player->stats.CharID / 9;
        col = player->stats.CharID % 9;
        star = lbl_8034E9A0.chars[(row) * 9 + (col)].stats.CaptainStarHitPitch;
        if (star == 0) {
            swing = lbl_8034E9A0.chars[(row) * 9 + (col)].stats.NonCaptainStarSwing + 11;
            pitch = lbl_8034E9A0.chars[(row) * 9 + (col)].stats.NonCaptainStarPitch + 11;
        } else if (g_d_GameSettings.GameModeSelected != 5) {
            swing = star - 1;
            pitch = swing;
        } else {
            s8 idx;
            pitch = star - 1;
            idx = translateStarPitchHitIndex(pitch);
            if (idx != -1 && ((s8*)&gChallengeState)[0x43C2 + idx] == 0) { // TODO type
                swing = lbl_8034E9A0.chars[(row) * 9 + (col)].stats.NonCaptainStarSwing + 11;
                pitch = lbl_8034E9A0.chars[(row) * 9 + (col)].stats.NonCaptainStarPitch + 11;
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
        lbl_803297E0._CF63[port] = 1;
    }
}
#endif

// .text:0x80058E0C size:0x64C
// NONMATCHING 88%: the port+K object indices are not folded in the original (addi per access)
#if NONMATCHING
void fn_80058E0C(SceneTask* task, u8 port) {
    CharacterStats* player;
    s16 charID;
    u32 fielding;
    u8 pushPull;
    u8 highLow;
    u8 stance;

    if (lbl_803297E0._CF63[port] == 0) {
        player = &inMemRoster[port][lbl_803297E0.slot[port] - 1];
        charID = player->stats.CharID;
        fielding = player->stats.FieldingStats;
        pushPull = player->stats.HitTrajectoryPushPull;
        highLow = player->stats.HitTrajectoryHighLow;
        stance = player->stats.BattingStance;
        TASK_OBJ(task, port + 0x19A)->_68 = 1;
        TASK_OBJ(task, port + 0x1B0)->_5C = charID << 16;
        TASK_OBJ(task, port + 0x1B2)->_5C = fn_80064918(charID) << 16;
        TASK_OBJ(task, port + 0x1AC)->_5C = 0;
        TASK_OBJ(task, port + 0x1C4)->_5C = charID << 16;
        fn_80059458(task, port, fielding);
        TASK_OBJ(task, port + 0x1B8)->_5C = 0;
        TASK_OBJ(task, port + 0x1BA)->_5C = 1 << 16;
        TASK_OBJ(task, port + 0x1BC)->_5C = 2 << 16;
        TASK_OBJ(task, port + 0x1BE)->_5C = 3 << 16;
        TASK_OBJ(task, port + 0x1C0)->_5C = 4 << 16;
        TASK_OBJ(task, port + 0x1C2)->_5C = 5 << 16;
        TASK_OBJ(task, port + 0x1A0)->_5C = 0;
        TASK_OBJ(task, port + 0x1A2)->_5C = 0;
        TASK_OBJ(task, port + 0x1A4)->_5C = 0;
        TASK_OBJ(task, port + 0x1A6)->_5C = 0;
        TASK_OBJ(task, port + 0x1A8)->_5C = 0;
        TASK_OBJ(task, port + 0x1AA)->_5C = 0;
        switch (pushPull) {
        case 0:
            TASK_OBJ(task, port + 0x1A0)->_68 = 1;
            TASK_OBJ(task, port + 0x1A2)->_68 = 0;
            TASK_OBJ(task, port + 0x1A4)->_68 = 0;
            break;
        case 1:
            if (stance == 0) {
                TASK_OBJ(task, port + 0x1A0)->_68 = 0;
                TASK_OBJ(task, port + 0x1A2)->_68 = 1;
                TASK_OBJ(task, port + 0x1A4)->_68 = 0;
            } else {
                TASK_OBJ(task, port + 0x1A0)->_68 = 0;
                TASK_OBJ(task, port + 0x1A2)->_68 = 0;
                TASK_OBJ(task, port + 0x1A4)->_68 = 1;
            }
            break;
        case 2:
            if (stance == 0) {
                TASK_OBJ(task, port + 0x1A0)->_68 = 0;
                TASK_OBJ(task, port + 0x1A2)->_68 = 0;
                TASK_OBJ(task, port + 0x1A4)->_68 = 1;
            } else {
                TASK_OBJ(task, port + 0x1A0)->_68 = 0;
                TASK_OBJ(task, port + 0x1A2)->_68 = 1;
                TASK_OBJ(task, port + 0x1A4)->_68 = 0;
            }
            break;
        }
        switch (highLow) {
        case 0:
            TASK_OBJ(task, port + 0x1A6)->_68 = 1;
            TASK_OBJ(task, port + 0x1A8)->_68 = 0;
            TASK_OBJ(task, port + 0x1AA)->_68 = 0;
            break;
        case 1:
            TASK_OBJ(task, port + 0x1A6)->_68 = 0;
            TASK_OBJ(task, port + 0x1A8)->_68 = 1;
            TASK_OBJ(task, port + 0x1AA)->_68 = 0;
            break;
        case 2:
            TASK_OBJ(task, port + 0x1A6)->_68 = 0;
            TASK_OBJ(task, port + 0x1A8)->_68 = 0;
            TASK_OBJ(task, port + 0x1AA)->_68 = 1;
            break;
        }
        TASK_OBJ(task, port + 0x1C6)->flags |= 2;
        TASK_OBJ(task, port + 0x1C6)->_68 = 1;
        TASK_OBJ(task, port + 0x19C)->_68 = 1;
        TASK_OBJ(task, port + 0x1AC)->_5C = 0;
        TASK_OBJ(task, port + 0x1AC)->_68 = 1;
        TASK_OBJ(task, port + 0x1D0)->flags &= ~2;
        TASK_OBJ(task, port + 0x1D0)->_68 = 0;
        TASK_OBJ(task, port + 0x1C8)->_68 = 4;
        lbl_803297E0._CF63[port] = 1;
    }
}
#endif

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
        if (challengeStarRelatedInd(lbl_803297E0._CF9C, lbl_803297E0.starCursor) != 0) {
            base = 0x1DD;
            TASK_OBJ(task, 473)->flags |= 2;
            TASK_OBJ(task, 473)->_5C = 0;
            TASK_OBJ(task, 473)->_68 = 1;
            TASK_OBJ(task, lbl_803297E0.starCursor + 0x1E7)->flags |= 2;
            TASK_OBJ(task, lbl_803297E0.starCursor + 0x1E7)->_5C = 0;
            TASK_OBJ(task, lbl_803297E0.starCursor + 0x1E7)->_68 = 1;
            if (g_d_GameSettings._06 == 2) {
                base = 0x173;
            }
            TASK_OBJ(task, base + lbl_803297E0.starCursor)->_5C = 1 << 16;
        } else {
            base = 0x1DD;
            TASK_OBJ(task, 473)->flags &= ~2;
            TASK_OBJ(task, lbl_803297E0.starCursor + 0x1E7)->flags &= ~2;
            if (g_d_GameSettings._06 == 2) {
                base = 0x173;
            }
            TASK_OBJ(task, base + lbl_803297E0.starCursor)->_5C = 0;
        }
        TASK_OBJ(task, lbl_803297E0.starCursor + 0x1FB)->flags |= 2;
        TASK_OBJ(task, lbl_803297E0.starCursor + 0x1FB)->_68 = 1;
        if (challengeStarRelatedInd(lbl_803297E0._CF9C, lbl_803297E0.prevStarCursor) != 0) {
            base = 0x1DD;
            TASK_OBJ(task, lbl_803297E0.prevStarCursor + 0x1E7)->flags &= ~2;
            if (g_d_GameSettings._06 == 2) {
                base = 0x173;
            }
            TASK_OBJ(task, base + lbl_803297E0.prevStarCursor)->_5C = 0;
        } else {
            base = 0x1DD;
            if (g_d_GameSettings._06 == 2) {
                base = 0x173;
            }
            TASK_OBJ(task, base + lbl_803297E0.prevStarCursor)->_5C = 0;
        }
        TASK_OBJ(task, lbl_803297E0.prevStarCursor + 0x1FB)->flags &= ~2;
        TASK_OBJ(task, lbl_803297E0.prevStarCursor + 0x1FB)->_68 = 1;
        set = lbl_800E8558[lbl_803297E0._CF9C]._2;
        if ((s8)gChallengeState.trackers[lbl_803297E0._CF9C].inGameMissionTracker[lbl_803297E0.starCursor].shownOnPauseMenu != 0) {
            msg = lbl_8010A768[set][lbl_803297E0.starCursor].msg;
        } else if (lbl_8010A768[set][lbl_803297E0.starCursor]._6 <= gChallengeState._4415) {
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
// NONMATCHING 90%: register numbering differs
#if NONMATCHING
void starMissionRelated1(SceneTask* task) {
    s8 rank;
    s32 count;
    u8 set;
    s16 msg;
    s8 i;
    s32 base;
    s32 idx;

    if (lbl_803297E0.pauseShown == 0) {
        lbl_803297E0._CF9C = lbl_800E8558[lbl_803297E0._CF78]._0[1];
        rank = gChallengeState.trackers[lbl_803297E0._CF9C].variantClassification;
        set = lbl_800E8558[lbl_803297E0._CF78]._2;
        switch (rank) {
        case 0:
            rank = 3;
            count = 10;
            break;
        case 1:
            rank = 2;
            count = 8;
            break;
        case 2:
            rank = 1;
            count = 6;
            break;
        case 3:
            rank = 0;
            count = 4;
            break;
        }
        idx = PAUSE_OBJ(0x1D7);
        TASK_OBJ(task, idx)->flags |= 2;
        idx = PAUSE_OBJ(0x1D7);
        TASK_OBJ(task, idx)->_68 = 1;
        idx = PAUSE_OBJ(0x1D3);
        TASK_OBJ(task, idx)->flags |= 2;
        idx = PAUSE_OBJ(0x1D3);
        TASK_OBJ(task, idx)->_68 = 1;
        idx = PAUSE_OBJ(0x1D4);
        TASK_OBJ(task, idx)->flags |= 2;
        idx = PAUSE_OBJ(0x1D4);
        TASK_OBJ(task, idx)->_5C = rank << 16;
        idx = PAUSE_OBJ(0x1D5);
        TASK_OBJ(task, idx)->flags |= 2;
        idx = PAUSE_OBJ(0x1D5);
        TASK_OBJ(task, idx)->_68 = 1;
        idx = PAUSE_OBJ(0x1D6);
        TASK_OBJ(task, idx)->_68 = 1;
        idx = PAUSE_OBJ(0x1DA);
        TASK_OBJ(task, idx)->_5C = lbl_8034E9A0.chars[(lbl_803297E0._CF78 / 9) * 9 + (lbl_803297E0._CF78 % 9)].stats.CharacterClass << 16;
        idx = PAUSE_OBJ(0x1DB);
        TASK_OBJ(task, idx)->_5C = lbl_803297E0._CF78 << 16;
        lbl_803297E0.nameText = fn_8000F988((LayoutGroup*)task, g_d_GameSettings._06 == 2 ? 0x19B : 0x205, 0, 0, lbl_803297E0._CF9C + 8, 0);
        lbl_803297E0.descText = fn_8000F988((LayoutGroup*)task, g_d_GameSettings._06 == 2 ? 0x19C : 0x206, 1, 0, lbl_8010B3E8[set] + determineIfMissionDescriptionIsShown(lbl_803297E0._CF9C), 0);
        TASK_OBJ(task, 476)->_5C = (4 - determineIfMissionDescriptionIsShown(lbl_803297E0._CF9C)) << 16;
        if ((s8)gChallengeState.trackers[lbl_803297E0._CF9C].inGameMissionTracker[lbl_803297E0.starCursor].shownOnPauseMenu != 0) {
            msg = lbl_8010A768[set][lbl_803297E0.starCursor].msg;
        } else if (lbl_8010A768[set][lbl_803297E0.starCursor]._6 <= gChallengeState._4415) {
            msg = 0x1C5;
        } else {
            msg = 0x1C6;
        }
        lbl_803297E0.missionText = fn_8000F988((LayoutGroup*)task, g_d_GameSettings._06 == 2 ? 0x19D : 0x207, 0, 0, msg, 0);
        lbl_80366B18.entries[lbl_803297E0.missionText].hAlign = 1;
        for (i = 0; i < count; i++) {
            if (challengeStarRelatedInd(lbl_803297E0._CF9C, i) != 0) {
                TASK_OBJ(task, i + 0x1F1)->flags |= 2;
                TASK_OBJ(task, i + 0x1F1)->_68 = 1;
            } else {
                TASK_OBJ(task, i + 0x1F1)->flags &= ~2;
            }
            base = 0x1DD;
            TASK_OBJ(task, i + 0x1FB)->flags &= ~2;
            TASK_OBJ(task, i + 0x1E7)->flags &= ~2;
            if (g_d_GameSettings._06 == 2) {
                base = 0x173;
            }
            TASK_OBJ(task, base + i)->_5C = 0;
        }
        if (challengeStarRelatedInd(lbl_803297E0._CF9C, lbl_803297E0.starCursor) != 0) {
            base = 0x1DD;
            TASK_OBJ(task, 473)->flags |= 2;
            TASK_OBJ(task, 473)->_68 = 1;
            TASK_OBJ(task, lbl_803297E0.starCursor + 0x1E7)->flags |= 2;
            TASK_OBJ(task, lbl_803297E0.starCursor + 0x1E7)->_68 = 1;
            if (g_d_GameSettings._06 == 2) {
                base = 0x173;
            }
            TASK_OBJ(task, base + lbl_803297E0.starCursor)->_5C = 1 << 16;
        } else {
            base = 0x1DD;
            TASK_OBJ(task, 473)->flags &= ~2;
            TASK_OBJ(task, lbl_803297E0.starCursor + 0x1E7)->flags &= ~2;
            if (g_d_GameSettings._06 == 2) {
                base = 0x173;
            }
            TASK_OBJ(task, base + lbl_803297E0.starCursor)->_5C = 0;
        }
        TASK_OBJ(task, lbl_803297E0.starCursor + 0x1FB)->flags |= 2;
        TASK_OBJ(task, lbl_803297E0.starCursor + 0x1FB)->_68 = 1;
        lbl_803297E0.pauseShown = 1;
    }
    if (lbl_803297E0.pauseShown != 0) {
        lbl_803297E0._CF74 = 0;
        lbl_803297E0.pauseShown = 0;
    }
}
#endif

// .text:0x8005A350 size:0xC18
// NONMATCHING 88%: index sums fold differently; registers differ
#if NONMATCHING
void fn_8005A350(SceneTask* task, s32 pad) {
    s32 team = pad;
    u16 pressed;
    s32 sel;
    s32 n;
    CharacterStats* player;

    if (((u8*)&g_d_GameSettings)[0x10] == 0) { // TODO type
        if (pad != 0) {
            return;
        }
        if (lbl_803297E0._CF43 != 0) {
            team = 1;
        } else {
            team = 0;
        }
    }
    if (g_d_GameSettings._06 != 2) {
        pressed = lbl_8034E9A0.input[pad].pressed;
    } else {
        pressed = lbl_803297E0.input[team].pressed;
    }
    if (pressed == 0x400 && lbl_803297E0._CF52[team] == 0 && g_d_GameSettings._06 != 2) {
        if (lbl_803297E0.slot[team] != 0) {
            sel = lbl_803297E0.slot[team] - 1;
            player = &inMemRoster[team][sel];
            n = player->stats.BattingStance + player->stats.FieldingArm * 2 + 1;
            if (n == 4) {
                n = 0;
            }
            player->stats.BattingStance = n % 2;
            player->stats.FieldingArm = n / 2;
            TASK_OBJ(task, sel + team * 9 + 0xAC)->_5C = n << 16;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        lbl_803297E0._CF58[team] = 0;
    }
    if (lbl_803297E0._CF9E[team] != 0) {
        if (g_d_GameSettings._06 != 2) {
            if (lbl_803297E0.slot[team] != 0) {
                transferStatsToInMemRoster(team);
                sndFXRelated(0x40);
            } else {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            }
            if (lbl_803297E0.slot[team] != 0 && g_d_GameSettings.GameModeSelected != 5) {
                s32 slot = lbl_803297E0.slot[team] - 1;
                s8 pos = lbl_80354720[team][slot].slot;
                if (lbl_8034E9A0.boosted[team][slot] != 0) {
                    TASK_OBJ(task, slot + team * 9 + 0x76)->flags |= 2;
                    TASK_OBJ(task, slot + team * 9 + 0x76)->_68 = 1;
                    TASK_OBJ(task, slot + team * 9 + 0x88)->flags |= 2;
                    TASK_OBJ(task, slot + team * 9 + 0x88)->_5C = 0;
                    TASK_OBJ(task, slot + team * 9 + 0x88)->_68 = 1;
                    TASK_OBJ(task, pos + team * 9 + 0x140)->flags |= 2;
                    TASK_OBJ(task, pos + team * 9 + 0x140)->_68 = 1;
                    TASK_OBJ(task, pos + team * 9 + 0x152)->flags |= 2;
                    TASK_OBJ(task, pos + team * 9 + 0x152)->_5C = 0;
                    TASK_OBJ(task, pos + team * 9 + 0x152)->_68 = 1;
                } else {
                    TASK_OBJ(task, slot + team * 9 + 0x88)->flags |= 2;
                    TASK_OBJ(task, slot + team * 9 + 0x88)->_5C = 0;
                    TASK_OBJ(task, slot + team * 9 + 0x88)->_68 = 0;
                    TASK_OBJ(task, pos + team * 9 + 0x152)->flags |= 2;
                    TASK_OBJ(task, pos + team * 9 + 0x152)->_5C = 0;
                    TASK_OBJ(task, pos + team * 9 + 0x152)->_68 = 0;
                }
            }
        }
        lbl_803297E0._CF9E[team] = 0;
    }
    if (lbl_803297E0._CF65[team] != 0) {
        if (g_d_GameSettings._06 != 2) {
            if (lbl_803297E0._CF61[team] != 0) {
                switch (lbl_803297E0._CF67[team]) {
                case 0:
                    fn_80058E0C(task, team);
                    break;
                case 1:
                    fn_80058B20(task, team);
                    break;
                }
            } else {
                if (lbl_803297E0._CF67[team] == 0) {
                    LayoutObj* obj = TASK_OBJ(task, team + 0x19A);
                    if ((obj->_5C >> 16) > 5) {
                        obj->_5C = 5 << 16;
                    }
                    TASK_OBJ(task, team + 0x19A)->_68 = 4;
                    TASK_OBJ(task, team + 0x19C)->_68 = 4;
                    TASK_OBJ(task, team + 0x1AC)->_68 = 4;
                    n = fn_80042DA8((LayoutOwner*)task, team + 0x19A, 0) != 0;
                    n += fn_80042DA8((LayoutOwner*)task, team + 0x19C, 0) != 0;
                    if (n + (fn_80042DA8((LayoutOwner*)task, team + 0x1AC, 0) != 0) == 3) {
                        lbl_803297E0._CF65[team] = 0;
                    }
                } else {
                    LayoutObj* obj = TASK_OBJ(task, team + 0x19A);
                    if ((obj->_5C >> 16) > 5) {
                        obj->_5C = 5 << 16;
                    }
                    TASK_OBJ(task, team + 0x19A)->_68 = 4;
                    TASK_OBJ(task, team + 0x1C8)->_68 = 4;
                    if (ObjAtFrame(task, team + 0x1C8, 0) == 1) {
                        lbl_803297E0._CF65[team] = 0;
                    }
                }
                lbl_803297E0._CF63[team] = 0;
            }
        } else if (lbl_803297E0._CF61[lbl_803297E0._CF3B] != 0) {
            switch (lbl_803297E0._CF67[team]) {
            case 0:
                fn_80058644(task);
                break;
            case 1:
                fn_80058394(task);
                break;
            }
        } else {
            if (lbl_803297E0._CF67[team] == 0) {
                LayoutObj* obj = TASK_OBJ(task, 280);
                if ((obj->_5C >> 16) > 5) {
                    obj->_5C = 5 << 16;
                }
                TASK_OBJ(task, 280)->_68 = 4;
                TASK_OBJ(task, 281)->_68 = 4;
                TASK_OBJ(task, 289)->_68 = 4;
                n = fn_80042DA8((LayoutOwner*)task, 0x118, 0) != 0;
                n += fn_80042DA8((LayoutOwner*)task, 0x119, 0) != 0;
                if (n + (fn_80042DA8((LayoutOwner*)task, 0x121, 0) != 0) == 3) {
                    lbl_803297E0._CF65[team] = 0;
                }
            } else {
                LayoutObj* obj = TASK_OBJ(task, 280);
                if ((obj->_5C >> 16) > 5) {
                    obj->_5C = 5 << 16;
                }
                TASK_OBJ(task, 280)->_68 = 4;
                TASK_OBJ(task, 303)->_68 = 4;
                if (ObjAtFrame(task, 0x12F, 0) == 1) {
                    lbl_803297E0._CF65[lbl_803297E0._CF3B] = 0;
                }
            }
            lbl_803297E0._CF63[lbl_803297E0._CF3B] = 0;
        }
    }
    if (lbl_803297E0._CF71 != 0) {
        if (lbl_803297E0._CF72 != 0) {
            switch (lbl_803297E0._CF74) {
            case 1:
                starMissionRelated1(task);
                return;
            case 2:
                fn_800596D4(task);
                return;
            case 3:
                if (lbl_803297E0.pauseShown == 0) {
                    TASK_OBJ(task, PAUSE_OBJ(0x1D7))->_68 = 4;
                    TASK_OBJ(task, PAUSE_OBJ(0x1D3))->_68 = 4;
                    TASK_OBJ(task, PAUSE_OBJ(0x1D5))->_68 = 4;
                    lbl_803297E0.pauseShown = 1;
                }
                if (lbl_803297E0.pauseShown != 0) {
                    n = fn_80042DA8((LayoutOwner*)task, PAUSE_OBJ(0x1D7), 0) != 0;
                    n += fn_80042DA8((LayoutOwner*)task, PAUSE_OBJ(0x1D3), 0) != 0;
                    if (n + (fn_80042DA8((LayoutOwner*)task, PAUSE_OBJ(0x1D5), 0) != 0) == 3) {
                        TASK_OBJ(task, PAUSE_OBJ(0x1D3))->flags &= ~2;
                        TASK_OBJ(task, PAUSE_OBJ(0x1D4))->flags &= ~2;
                        TASK_OBJ(task, PAUSE_OBJ(0x1D5))->flags &= ~2;
                        TASK_OBJ(task, PAUSE_OBJ(0x1D7))->flags &= ~2;
                        fn_8000FEE8(lbl_803297E0.nameText);
                        fn_8000FEE8(lbl_803297E0.descText);
                        fn_8000FEE8(lbl_803297E0.missionText);
                        fn_8000F8F4((LayoutGroup*)task);
                        lbl_803297E0._CF72 = 0;
                        lbl_803297E0._CF74 = 0;
                        lbl_803297E0.pauseShown = 0;
                        return;
                    }
                }
                break;
            }
        } else {
            n = fn_80042DA8((LayoutOwner*)task, PAUSE_OBJ(0x1D3), 0) != 0;
            if (n + (fn_80042DA8((LayoutOwner*)task, PAUSE_OBJ(0x1D5), 0) != 0) == 2) {
                lbl_803297E0.pauseShown = 0;
                lbl_803297E0._CF71 = 0;
            }
        }
    }
}
#endif

// .text:0x8005AF68 size:0x330
// NONMATCHING 93%: loop registers rotated; pos+0x3E index folded differently
#if NONMATCHING
void fn_8005AF68(SceneTask* task) {
    s32 i;
    s8 team = lbl_803297E0._CF3B;
    OrderEntry* slot = lbl_80354720[team];
    CharacterStats* player = inMemRoster[team];
    u8 flag;

    for (i = 0; i < 9; i++, player++, slot++) {
        if (lbl_803297E0._CFA2[team] != 2) {
            s8 pos = slot->slot;
            fn_800363D8(task, pos + 0x23, 1, 0x83, player->stats.CharID);
            TASK_OBJ(task, i + 0x11)->flags &= ~2;
            if (g_d_GameSettings.GameModeSelected == 5) {
                flag = ((u8*)&gChallengeState)[0x43D6 + player->stats.CharID]; // TODO type
            } else {
                flag = lbl_8034E9A0.boosted[team][i];
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
                TASK_OBJ(task, i + 0x1A)->_64 = (u8)(lbl_8034E9A0.teamPort[0] == 0) + 30;
            } else {
                TASK_OBJ(task, i + 0x1A)->_64 = lbl_8034E9A0.teamPort[team] + 30;
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
    s8 team = lbl_803297E0._CF3B;
    CharacterStats* player = inMemRoster[team];
    u8 flag;

    for (i = 0; i < 9; i++, player++) {
        TASK_OBJ(task, i + 0x5A)->_5C = i << 16;
        TASK_OBJ(task, i + 0x6C)->flags &= ~2;
        if (lbl_803297E0._CFA2[team] == 0) {
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
            flag = lbl_8034E9A0.boosted[team][i];
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
        if (lbl_803297E0.slot[port] != 0) {
            slot = lbl_803297E0.slot[port] - 1;
            pos = lbl_80354720[port][slot].slot;
            for (i = 0; i < 9; i++) {
                TASK_OBJ(task, i + 0x75)->flags &= ~2;
                TASK_OBJ(task, i + 0x35)->flags &= ~2;
            }
            if (lbl_803297E0._CFA2[port] == 0) {
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
                    flag = lbl_8034E9A0.boosted[team][i];
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
    OrderEntry* slot;
    u8 flag;

    for (team = 0, base = 0; team < 2; team++, base += 9) {
        player = inMemRoster[team];
        slot = lbl_80354720[team];
        for (i = 0; i < 9; i++, player++, slot++) {
            fn_800363D8(task, slot->slot + base + 0x10A, 1, 0x83, player->stats.CharID);
            TASK_OBJ(task, i + base + 0xE6)->flags &= ~2;
            if (g_d_GameSettings.GameModeSelected == 5) {
                flag = ((u8*)&gChallengeState)[0x43D6 + player->stats.CharID]; // TODO type
            } else {
                flag = lbl_8034E9A0.boosted[team][i];
            }
            if (flag != 0) {
                TASK_OBJ(task, slot->slot + base + 0x140)->_68 = 1;
                TASK_OBJ(task, slot->slot + base + 0x152)->flags |= 2;
                TASK_OBJ(task, slot->slot + base + 0x152)->_5C = 0;
                TASK_OBJ(task, slot->slot + base + 0x152)->_68 = 1;
            } else if (lbl_80361B20[player->stats.CharID] != 0) {
                TASK_OBJ(task, slot->slot + base + 0x140)->_68 = 1;
                TASK_OBJ(task, slot->slot + base + 0x152)->flags |= 2;
                TASK_OBJ(task, slot->slot + base + 0x152)->_5C = 0;
                TASK_OBJ(task, slot->slot + base + 0x152)->_68 = 0;
            } else {
                TASK_OBJ(task, slot->slot + base + 0x152)->flags &= ~2;
            }
            TASK_OBJ(task, i + base + 0x12E)->flags &= ~2;
            if (((u8*)&g_d_GameSettings)[0x10] == 0 && team != 0) { // TODO type
                TASK_OBJ(task, i + base + 0xF8)->_64 = (s8)(lbl_8034E9A0.teamPort[0] == 0) + 30;
            } else {
                TASK_OBJ(task, i + base + 0xF8)->_64 = lbl_8034E9A0.teamPort[team] + 30;
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
                flag = lbl_8034E9A0.boosted[team][i];
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
    OrderEntry* rs;

    for (j = 0; j < 9; j++) {
        player = inMemRoster[port];
        rs = lbl_80354720[port];
        for (k = 0; k < 9; k++, player++, rs++) {
            if (player->stats.CharID != (s8)lbl_8034E9A0._47F9[port][slot][j]) {
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
                    TASK_OBJ(task, rs->slot + 0x35)->flags |= 2;
                    TASK_OBJ(task, rs->slot + 0x35)->_64 = 0x2B;
                    TASK_OBJ(task, rs->slot + 0x35)->_5C = 0;
                    TASK_OBJ(task, rs->slot + 0x35)->_68 = 1;
                    TASK_OBJ(task, k + 0x6C)->flags |= 2;
                    TASK_OBJ(task, k + 0x6C)->_5C = 0;
                    TASK_OBJ(task, k + 0x6C)->_68 = 1;
                    TASK_OBJ(task, k + 0x75)->flags |= 2;
                    TASK_OBJ(task, k + 0x75)->_64 = 0x2B;
                    TASK_OBJ(task, k + 0x75)->_68 = 1;
                }
            } else if (g_d_GameSettings._06 != 2) {
                TASK_OBJ(task, rs->slot + port * 9 + 0x12E)->flags |= 2;
                TASK_OBJ(task, rs->slot + port * 9 + 0x12E)->_64 = 0x2B;
                TASK_OBJ(task, rs->slot + port * 9 + 0x12E)->_5C = 0;
                TASK_OBJ(task, rs->slot + port * 9 + 0x12E)->_68 = 1;
            } else {
                TASK_OBJ(task, rs->slot + 0x35)->flags |= 2;
                TASK_OBJ(task, rs->slot + 0x35)->_64 = 0x2B;
                TASK_OBJ(task, rs->slot + 0x35)->_5C = 0;
                TASK_OBJ(task, rs->slot + 0x35)->_68 = 1;
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
// NONMATCHING 75%: the original recomputes the _06-dependent object bases per access; index sums fold differently
#if NONMATCHING
void fn_8005CCE4(SceneTask* task, s32 port) {
    u8* state = &lbl_803C66B0.steps[9][port + 1];
    u8 prev;
    s32 slot;
    s8 slotPos;
    s8 prevPos;
    s32 i;
    CharacterStats* players;
    CharacterStats* player;
    OrderEntry* rs;
    u8 flag;
    s32 a;
    s32 b;

    if (*state != 0) {
        return;
    }
    prev = lbl_803297E0._CF3E[port];
    slot = lbl_803297E0.slot[port] - 1;
    slotPos = lbl_80354720[port][slot].slot;
    prevPos = lbl_80354720[port][prev].slot;
    players = inMemRoster[port];
    if (lbl_803297E0._CF52[port] == 0) {
        if (slot != prev) {
            TASK_OBJ(task, prev + port * 9 + 0x1C)->_5C = 10 << 16;
            TASK_OBJ(task, prev + port * 9 + 0x1C)->_68 = 4;
        }
        TASK_OBJ(task, prev + port * 9 + 0x40)->_68 = 4;
        fn_800363D8(task, slot + port * 9 + 0x40, 1, 0x83, players[slot].stats.CharID);
        fn_800363D8(task, prev + port * 9 + 0x40, 1, 0x83, players[prev].stats.CharID);
        TASK_OBJ(task, slot + port * 9 + 0xD0)->_5C = players[slot].stats.CharacterClass << 16;
        TASK_OBJ(task, prev + port * 9 + 0xD0)->_5C = players[prev].stats.CharacterClass << 16;
        TASK_OBJ(task, slot + port * 9 + 0xAC)->_5C = (players[slot].stats.BattingStance + players[slot].stats.FieldingArm * 2) << 16;
        TASK_OBJ(task, prev + port * 9 + 0xAC)->_5C = (players[prev].stats.BattingStance + players[prev].stats.FieldingArm * 2) << 16;
        player = players;
        for (i = 0; i < 9; i++, player++) {
            a = g_d_GameSettings._06 != 2 ? port * 9 + 0x76 : 0x7E;
            b = g_d_GameSettings._06 != 2 ? port * 9 + 0x88 : 0x87;
            if (g_d_GameSettings.GameModeSelected == 5) {
                flag = ((u8*)&gChallengeState)[0x43D6 + player->stats.CharID]; // TODO type
            } else {
                flag = lbl_8034E9A0.boosted[port][i];
            }
            if (flag != 0) {
                TASK_OBJ(task, a + i)->flags |= 2;
                TASK_OBJ(task, a + i)->_68 = 1;
                TASK_OBJ(task, b + i)->flags |= 2;
                TASK_OBJ(task, b + i)->_5C = 15 << 16;
                TASK_OBJ(task, b + i)->_68 = 1;
            } else if (lbl_80361B20[player->stats.CharID] != 0 && g_d_GameSettings.GameModeSelected != 5) {
                TASK_OBJ(task, a + i)->flags |= 2;
                TASK_OBJ(task, a + i)->_68 = 1;
                TASK_OBJ(task, b + i)->flags |= 2;
                TASK_OBJ(task, b + i)->_5C = 0;
                TASK_OBJ(task, b + i)->_68 = 0;
            } else {
                TASK_OBJ(task, a + i)->flags &= ~2;
                TASK_OBJ(task, b + i)->flags &= ~2;
            }
            if (g_d_GameSettings._06 != 2) {
                TASK_OBJ(task, i + port * 9 + 0x64)->flags &= ~2;
            } else {
                TASK_OBJ(task, i + 0x75)->flags &= ~2;
            }
        }
        TASK_OBJ(task, slot + port * 9 + 0x64)->flags |= 2;
        TASK_OBJ(task, slot + port * 9 + 0x64)->_64 = 0x2A;
        TASK_OBJ(task, slot + port * 9 + 0x64)->_68 = 1;
        fn_8005C830(task, port, slot);
    } else {
        if (g_d_GameSettings._06 != 2) {
            fn_800363D8(task, prevPos + port * 9 + 0x10A, 1, 0x83, players[prev].stats.CharID);
            fn_800363D8(task, slotPos + port * 9 + 0x10A, 1, 0x83, players[slot].stats.CharID);
            TASK_OBJ(task, slotPos + port * 9 + 0x10A)->_68 = 4;
            TASK_OBJ(task, slotPos + port * 9 + 0xF8)->_68 = 4;
            TASK_OBJ(task, prevPos + port * 9 + 0x10A)->_68 = 1;
            TASK_OBJ(task, prevPos + port * 9 + 0xF8)->_68 = 1;
            rs = lbl_80354720[port];
            player = players;
            for (i = 0; i < 9; i++, rs++, player++) {
                s8 pos = rs->slot;
                a = g_d_GameSettings._06 != 2 ? port * 9 + 0x140 : 0x3E;
                b = g_d_GameSettings._06 != 2 ? port * 9 + 0x152 : 0x47;
                if (g_d_GameSettings.GameModeSelected == 5) {
                    flag = ((u8*)&gChallengeState)[0x43D6 + player->stats.CharID]; // TODO type
                } else {
                    flag = lbl_8034E9A0.boosted[port][i];
                }
                if (flag != 0) {
                    TASK_OBJ(task, a + pos)->flags |= 2;
                    TASK_OBJ(task, a + pos)->_68 = 1;
                    TASK_OBJ(task, b + pos)->flags |= 2;
                    TASK_OBJ(task, b + pos)->_5C = 15 << 16;
                    TASK_OBJ(task, b + pos)->_68 = 1;
                } else if (lbl_80361B20[player->stats.CharID] != 0 && g_d_GameSettings.GameModeSelected != 5) {
                    TASK_OBJ(task, a + pos)->flags |= 2;
                    TASK_OBJ(task, a + pos)->_68 = 1;
                    TASK_OBJ(task, b + pos)->flags |= 2;
                    TASK_OBJ(task, b + pos)->_5C = 0;
                    TASK_OBJ(task, b + pos)->_68 = 0;
                } else {
                    TASK_OBJ(task, a + pos)->flags &= ~2;
                    TASK_OBJ(task, b + pos)->flags &= ~2;
                }
                TASK_OBJ(task, i + port * 9 + 0x12E)->flags &= ~2;
            }
            TASK_OBJ(task, prevPos + port * 9 + 0x12E)->flags |= 2;
            TASK_OBJ(task, prevPos + port * 9 + 0x12E)->_64 = 0x2A;
            TASK_OBJ(task, prevPos + port * 9 + 0x12E)->_68 = 1;
        } else {
            fn_800363D8(task, prevPos + 0x23, 1, 0x83, players[prev].stats.CharID);
            fn_800363D8(task, slotPos + 0x23, 1, 0x83, players[slot].stats.CharID);
            TASK_OBJ(task, slotPos + 0x23)->_68 = 4;
            TASK_OBJ(task, slotPos + 0x1A)->_68 = 4;
            TASK_OBJ(task, prevPos + 0x23)->_68 = 1;
            TASK_OBJ(task, prevPos + 0x1A)->_68 = 1;
            rs = lbl_80354720[port];
            player = players;
            for (i = 0; i < 9; i++, rs++, player++) {
                s8 pos = rs->slot;
                if (g_d_GameSettings.GameModeSelected == 5) {
                    flag = ((u8*)&gChallengeState)[0x43D6 + player->stats.CharID]; // TODO type
                } else {
                    flag = lbl_8034E9A0.boosted[port][i];
                }
                if (flag != 0 && (port != 1 || g_d_GameSettings.GameModeSelected != 5)) {
                    TASK_OBJ(task, pos + 0x3E)->flags |= 2;
                    TASK_OBJ(task, pos + 0x3E)->_68 = 1;
                    TASK_OBJ(task, pos + 0x47)->flags |= 2;
                    TASK_OBJ(task, pos + 0x47)->_5C = 15 << 16;
                    TASK_OBJ(task, pos + 0x47)->_68 = 1;
                    TASK_OBJ(task, i + 0x7E)->flags |= 2;
                    TASK_OBJ(task, i + 0x7E)->_68 = 1;
                    TASK_OBJ(task, i + 0x87)->flags |= 2;
                    TASK_OBJ(task, i + 0x87)->_5C = 15 << 16;
                    TASK_OBJ(task, i + 0x87)->_68 = 1;
                } else if (lbl_80361B20[player->stats.CharID] != 0 && g_d_GameSettings.GameModeSelected != 5) {
                    TASK_OBJ(task, pos + 0x3E)->flags |= 2;
                    TASK_OBJ(task, pos + 0x3E)->_68 = 1;
                    TASK_OBJ(task, pos + 0x47)->flags |= 2;
                    TASK_OBJ(task, pos + 0x47)->_5C = 0;
                    TASK_OBJ(task, pos + 0x47)->_68 = 0;
                    TASK_OBJ(task, i + 0x7E)->flags |= 2;
                    TASK_OBJ(task, i + 0x7E)->_68 = 1;
                    TASK_OBJ(task, i + 0x87)->flags |= 2;
                    TASK_OBJ(task, i + 0x87)->_5C = 0;
                    TASK_OBJ(task, i + 0x87)->_68 = 0;
                } else {
                    TASK_OBJ(task, pos + 0x3E)->flags &= ~2;
                    TASK_OBJ(task, pos + 0x47)->flags &= ~2;
                    a = g_d_GameSettings._06 != 2 ? port * 9 + 0x76 : 0x7E;
                    TASK_OBJ(task, a + i)->flags &= ~2;
                    b = g_d_GameSettings._06 != 2 ? port * 9 + 0x88 : 0x87;
                    TASK_OBJ(task, b + i)->flags &= ~2;
                }
                TASK_OBJ(task, i + 0x35)->flags &= ~2;
                TASK_OBJ(task, i + 0x75)->flags &= ~2;
            }
            TASK_OBJ(task, prev + 0x75)->flags |= 2;
            TASK_OBJ(task, prev + 0x75)->_64 = 0x2A;
            TASK_OBJ(task, prev + 0x75)->_68 = 1;
            TASK_OBJ(task, prevPos + 0x35)->flags |= 2;
            TASK_OBJ(task, prevPos + 0x35)->_64 = 0x2A;
            TASK_OBJ(task, prevPos + 0x35)->_68 = 1;
        }
        fn_8005C830(task, port, prev);
        lbl_803297E0.slot[port] = fn_80042598(port, lbl_80354720[port][prev].slot);
    }
    lbl_803297E0._CF3E[port] = 0xFF;
    lbl_803C66B0.step[port] = 0;
    *state = 2;
}
#endif

// .text:0x8005DE14 size:0xBC4
// NONMATCHING 85%: object index sums fold differently; registers differ
#if NONMATCHING
void fn_8005DE14(SceneTask* task, s32 port) {
    u8* state = &lbl_803C66B0.steps[9][port + 1];
    s32 i;
    s8 slot;
    s8 prev;
    s8 old;

    if (*state == 0) {
        slot = lbl_803297E0.slot[port] - 1;
        prev = lbl_803297E0._CF3E[port];
        old = lbl_803297E0._CF48[port] - 1;
        if (lbl_803297E0._CF52[port] == 0) {
            if (g_d_GameSettings._06 != 2) {
                for (i = 0; i < 9; i++) {
                    TASK_OBJ(task, i + port * 9 + 0x64)->flags &= ~2;
                }
                TASK_OBJ(task, slot + port * 9 + 0x40)->_5C = 0;
                TASK_OBJ(task, slot + port * 9 + 0x40)->_68 = 1;
                TASK_OBJ(task, slot + port * 9 + 0x1C)->_5C = 0;
                TASK_OBJ(task, slot + port * 9 + 0x1C)->_68 = 1;
                TASK_OBJ(task, slot + port * 9 + 0x52)->_5C = 0;
                TASK_OBJ(task, slot + port * 9 + 0x52)->_68 = 1;
                TASK_OBJ(task, slot + port * 9 + 0x64)->flags |= 2;
                TASK_OBJ(task, slot + port * 9 + 0x64)->_64 = 0x2A;
                TASK_OBJ(task, slot + port * 9 + 0x64)->_68 = 1;
                fn_8005C830(task, port, slot);
                TASK_OBJ(task, old + port * 9 + 0x40)->_5C = 0;
                TASK_OBJ(task, old + port * 9 + 0x40)->_68 = 4;
                TASK_OBJ(task, old + port * 9 + 0x1C)->_5C = 10 << 16;
                TASK_OBJ(task, old + port * 9 + 0x1C)->_68 = 4;
                if (prev != -1) {
                    TASK_OBJ(task, prev + port * 9 + 0x1C)->_5C = 10 << 16;
                    TASK_OBJ(task, prev + port * 9 + 0x1C)->_68 = 0;
                    TASK_OBJ(task, prev + port * 9 + 0x40)->_68 = 1;
                }
            } else {
                s8 pos = lbl_80354720[port][slot].slot;
                for (i = 0; i < 9; i++) {
                    TASK_OBJ(task, i + 0x75)->flags &= ~2;
                    TASK_OBJ(task, i + 0x35)->flags &= ~2;
                }
                TASK_OBJ(task, slot + 0x63)->_5C = 0;
                TASK_OBJ(task, slot + 0x63)->_68 = 1;
                TASK_OBJ(task, slot + 0x51)->_5C = 0;
                TASK_OBJ(task, slot + 0x51)->_68 = 1;
                TASK_OBJ(task, slot + 0x6C)->_5C = 0;
                TASK_OBJ(task, slot + 0x75)->flags |= 2;
                TASK_OBJ(task, slot + 0x75)->_64 = 0x2A;
                TASK_OBJ(task, slot + 0x6C)->_68 = 1;
                TASK_OBJ(task, slot + 0x75)->_68 = 1;
                fn_8005C830(task, port, slot);
                TASK_OBJ(task, old + 0x63)->_5C = 0;
                TASK_OBJ(task, old + 0x63)->_68 = 4;
                TASK_OBJ(task, old + 0x51)->_5C = 10 << 16;
                TASK_OBJ(task, old + 0x51)->_68 = 4;
                TASK_OBJ(task, pos + 0x35)->flags |= 2;
                TASK_OBJ(task, pos + 0x35)->_64 = 0x2A;
                TASK_OBJ(task, pos + 0x35)->_68 = 1;
                if (prev != -1) {
                    TASK_OBJ(task, prev + 0x51)->_5C = 10 << 16;
                    TASK_OBJ(task, prev + 0x51)->_68 = 0;
                    TASK_OBJ(task, prev + 0x63)->_68 = 1;
                }
            }
        } else {
            s8 pos = lbl_80354720[port][slot].slot;
            s8 oldPos = lbl_80354720[port][old].slot;
            s8 prevPos = 0;

            if (prev != -1) { // the original reads it unconditionally
                prevPos = lbl_80354720[port][prev].slot;
            }

            if (g_d_GameSettings._06 != 2) {
                TASK_OBJ(task, pos + port * 9 + 0x10A)->_68 = 1;
                TASK_OBJ(task, pos + port * 9 + 0xF8)->_68 = 1;
                TASK_OBJ(task, pos + port * 9 + 0xE6)->flags |= 2;
                TASK_OBJ(task, oldPos + port * 9 + 0x10A)->_68 = 4;
                TASK_OBJ(task, oldPos + port * 9 + 0xF8)->_68 = 4;
                TASK_OBJ(task, oldPos + port * 9 + 0xE6)->flags &= ~2;
                for (i = 0; i < 9; i++) {
                    TASK_OBJ(task, i + port * 9 + 0x12E)->flags &= ~2;
                }
                TASK_OBJ(task, pos + port * 9 + 0x12E)->flags |= 2;
                TASK_OBJ(task, pos + port * 9 + 0x12E)->_64 = 0x2A;
                TASK_OBJ(task, pos + port * 9 + 0x12E)->_68 = 1;
                fn_8005C830(task, port, slot);
                if (prev != -1) {
                    TASK_OBJ(task, prevPos + port * 9 + 0x10A)->_68 = 1;
                    TASK_OBJ(task, prevPos + port * 9 + 0xF8)->_68 = 1;
                }
            } else {
                TASK_OBJ(task, pos + 0x23)->_68 = 1;
                TASK_OBJ(task, pos + 0x1A)->_68 = 1;
                TASK_OBJ(task, pos + 0x11)->flags |= 2;
                TASK_OBJ(task, oldPos + 0x23)->_68 = 4;
                TASK_OBJ(task, oldPos + 0x1A)->_68 = 4;
                TASK_OBJ(task, oldPos + 0x11)->flags &= ~2;
                for (i = 0; i < 9; i++) {
                    TASK_OBJ(task, i + 0x35)->flags &= ~2;
                    TASK_OBJ(task, i + 0x75)->flags &= ~2;
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
                if (prev != -1) {
                    TASK_OBJ(task, prevPos + 0x23)->_68 = 1;
                    TASK_OBJ(task, prevPos + 0x1A)->_68 = 1;
                }
                fn_8005C830(task, port, slot);
            }
        }
        fn_800626EC(port);
        *state = 1;
    }
}
#endif

// .text:0x8005E9D8 size:0x2B0
void fn_8005E9D8(SceneTask* task, s32 port) {
    u8* state;

    if (lbl_803297E0.slot[port] != lbl_803297E0._CF48[port]) {
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
            s8 pos = lbl_80354720[port][slot].slot;
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
        if (lbl_803297E0.slot[port] != 0) {
            slot = lbl_803297E0.slot[port] - 1;
            pos = lbl_80354720[port][slot].slot;
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
// NONMATCHING 85%: object index sums are folded differently; registers differ
#if NONMATCHING
void fn_8005F068(SceneTask* task, s32 port) {
    u8* state = &lbl_803C66B0.steps[9][port + 1];
    s32 i;
    s8 slot;
    s8 pos;
    s8 prev = 0;
    s8 prevPos = 0;
    u8 prevSlot;

    if (*state == 0) {
        prevSlot = lbl_803297E0._CF3E[port];
        slot = lbl_803297E0.slot[port] - 1;
        pos = lbl_80354720[port][slot].slot;
        if (prevSlot != 0xFF) {
            prev = prevSlot;
            prevPos = lbl_80354720[port][prev].slot;
        }
        switch (lbl_803297E0._CF52[port]) {
        case 0:
            if (lbl_803297E0._CF54[port] == 1) {
                TASK_OBJ(task, port + 0x14)->_5C = 20 << 16;
                TASK_OBJ(task, port + 0x14)->_68 = 4;
                TASK_OBJ(task, port + 0x1A)->_68 = 1;
                TASK_OBJ(task, port + 0xE2)->_68 = 4;
                TASK_OBJ(task, port + 0xE4)->_68 = 4;
                for (i = 0; i < 9; i++) {
                    TASK_OBJ(task, i + port * 9 + 0x64)->flags &= ~2;
                    TASK_OBJ(task, i + port * 9 + 0x1C)->_5C = 0;
                    TASK_OBJ(task, i + port * 9 + 0x1C)->_68 = 0;
                    TASK_OBJ(task, i + port * 9 + 0x40)->_5C = 0;
                    TASK_OBJ(task, i + port * 9 + 0x40)->_68 = 0;
                }
                if (slot >= 0 && slot < 9) {
                    TASK_OBJ(task, slot + port * 9 + 0x1C)->_5C = 0;
                    TASK_OBJ(task, slot + port * 9 + 0x1C)->_68 = 1;
                    TASK_OBJ(task, slot + port * 9 + 0x52)->_5C = 0;
                    TASK_OBJ(task, slot + port * 9 + 0x52)->_68 = 1;
                    TASK_OBJ(task, slot + port * 9 + 0x64)->flags |= 2;
                    TASK_OBJ(task, slot + port * 9 + 0x64)->_64 = 0x2A;
                    TASK_OBJ(task, slot + port * 9 + 0x64)->_68 = 1;
                    fn_8005C830(task, port, slot);
                    TASK_OBJ(task, slot + port * 9 + 0x40)->_5C = 0;
                    TASK_OBJ(task, slot + port * 9 + 0x40)->_68 = 1;
                    if (lbl_803297E0._CF3E[port] != 0xFF) {
                        TASK_OBJ(task, prev + port * 9 + 0x1C)->_5C = 10 << 16;
                        TASK_OBJ(task, prev + port * 9 + 0x1C)->_68 = 0;
                        TASK_OBJ(task, prev + port * 9 + 0x40)->_5C = 0;
                        TASK_OBJ(task, prev + port * 9 + 0x40)->_68 = 1;
                    }
                }
            }
            break;
        case 1:
            if (lbl_803297E0._CF54[port] != 1) {
                for (i = 0; i < 9; i++) {
                    TASK_OBJ(task, i + port * 9 + 0x10A)->_5C = 0;
                    TASK_OBJ(task, i + port * 9 + 0x10A)->_68 = 0;
                    TASK_OBJ(task, i + port * 9 + 0xF8)->_5C = 0;
                    TASK_OBJ(task, i + port * 9 + 0xF8)->_68 = 0;
                    TASK_OBJ(task, i + port * 9 + 0xE6)->flags &= ~2;
                    TASK_OBJ(task, i + port * 9 + 0x12E)->flags &= ~2;
                }
                TASK_OBJ(task, port + 0x14)->_5C = 10 << 16;
                TASK_OBJ(task, port + 0x14)->_68 = 1;
                TASK_OBJ(task, port + 0x1A)->_68 = 4;
                TASK_OBJ(task, port + 0xE2)->_68 = 1;
                TASK_OBJ(task, port + 0xE4)->_68 = 1;
                TASK_OBJ(task, port + 0xE2)->flags |= 2;
                TASK_OBJ(task, port + 0xE4)->flags |= 2;
                if (slot >= 0 && slot < 9) {
                    TASK_OBJ(task, pos + port * 9 + 0x10A)->_68 = 1;
                    TASK_OBJ(task, pos + port * 9 + 0xF8)->_68 = 1;
                    TASK_OBJ(task, pos + port * 9 + 0xE6)->flags |= 2;
                    TASK_OBJ(task, pos + port * 9 + 0x12E)->flags |= 2;
                    TASK_OBJ(task, pos + port * 9 + 0x12E)->_64 = 0x2A;
                    TASK_OBJ(task, pos + port * 9 + 0x12E)->_68 = 1;
                    fn_8005C830(task, port, slot);
                    if (lbl_803297E0._CF3E[port] != 0xFF) {
                        TASK_OBJ(task, prevPos + port * 9 + 0x10A)->_68 = 1;
                        TASK_OBJ(task, prevPos + port * 9 + 0xF8)->_68 = 1;
                    }
                }
            }
            break;
        }
        fn_800626EC(port);
        *state = 1;
    }
}
#endif

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
        done = fn_80042DA8((LayoutOwner*)task, port + 4, 20) != 0;
        if (g_d_GameSettings.GameModeSelected != 5) {
            if (((u8*)&g_d_GameSettings)[0x10] == 0 && port != 0) { // TODO type
                done += fn_80042DA8((LayoutOwner*)task, port, 30) != 0;
                done += fn_80042DA8((LayoutOwner*)task, port + 10, 10) != 0;
                done += fn_80042DA8((LayoutOwner*)task, port + 18, 20) != 0;
                done += fn_80042DA8((LayoutOwner*)task, port + 20, 10) != 0;
            } else {
                done += fn_80042DA8((LayoutOwner*)task, port, 20) != 0;
                done += fn_80042DA8((LayoutOwner*)task, port + 10, 10) != 0;
                done += fn_80042DA8((LayoutOwner*)task, port + 18, 10) != 0;
                done += fn_80042DA8((LayoutOwner*)task, port + 20, 10) != 0;
            }
        } else {
            done += fn_80042DA8((LayoutOwner*)task, port, 20) != 0;
            done += fn_80042DA8((LayoutOwner*)task, port + 10, 10) != 0;
            done += fn_80042DA8((LayoutOwner*)task, 18, 10) != 0;
            done += fn_80042DA8((LayoutOwner*)task, 20, 10) != 0;
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
// NONMATCHING 80%: tutorial step dispatcher; state tests, index sums and registers differ
#if NONMATCHING
void fn_80060184(void) {
    SceneTask* task = lbl_803CC1B8;
    s32 i;
    u8 port;
    u8* st;
    s32 done;
    s32 expected;
    s32 j;
    s32 k;

    for (i = 0; i < 2; i++) {
        port = lbl_803C66B0.portOf[i];
        st = &lbl_803C66B0.steps[9][port + 1];
        switch (lbl_803C66B0.step[i]) {
        case 0x38:
            if (g_d_GameSettings._06 != 2) {
                fn_8005FCA0(task, port);
                fn_8005F9D0(task, port);
            } else {
                if (*st == 0) {
                    TASK_OBJ(task, 0)->_5C = 0;
                    TASK_OBJ(task, 0)->_68 = 1;
                    if (lbl_803297E0._CFA2[port] != 1) {
                        TASK_OBJ(task, 1)->_5C = 0;
                        TASK_OBJ(task, 1)->_68 = 1;
                    }
                    TASK_OBJ(task, 3)->_68 = 1;
                    TASK_OBJ(task, 14)->_5C = 0;
                    TASK_OBJ(task, 14)->_68 = 1;
                    fn_800626EC(port);
                    *st = 1;
                }
                if (*st == 1) {
                    expected = 1;
                    done = fn_80042DA8((LayoutOwner*)task, 0, 20) != 0;
                    if (lbl_803297E0._CFA2[port] != 1) {
                        expected = 2;
                        done += fn_80042DA8((LayoutOwner*)task, 1, 20) != 0;
                    }
                    if (done == expected) {
                        fn_80062674(port);
                        *st = 2;
                    }
                }
            }
            break;
        case 0x39:
            if (g_d_GameSettings._06 != 2) {
                fn_8005F734(task, port);
                if (*st == 1) {
                    done = fn_80042DA8((LayoutOwner*)task, port + 20, 10) != 0;
                    if (((u8*)&g_d_GameSettings)[0x10] == 0 && port == 0) { // TODO type
                        done += fn_80042DA8((LayoutOwner*)task, port, 30) != 0;
                        done += fn_80042DA8((LayoutOwner*)task, port + 18, 20) != 0;
                    } else {
                        done += fn_80042DA8((LayoutOwner*)task, port, 20) != 0;
                        done += fn_80042DA8((LayoutOwner*)task, port + 18, 10) != 0;
                    }
                    done += fn_80042DA8((LayoutOwner*)task, port + 4, 20) != 0;
                    if (done + (fn_80042DA8((LayoutOwner*)task, port + 10, 10) != 0) == 5) {
                        if (((u8*)&g_d_GameSettings)[0x10] == 0) { // TODO type
                            lbl_803297E0.ready[port] = 1;
                            if (lbl_803297E0.ready[0] != 0 && lbl_803297E0.ready[1] != 0) {
                                lbl_803297E0.ready[1] = 0;
                                lbl_803297E0.ready[0] = 0;
                                fn_80062674(0);
                                fn_80062674(1);
                                lbl_803C66B0.steps[9][1] = 2;
                                lbl_803C66B0.steps[9][2] = 2;
                            }
                        } else {
                            fn_80062674(port);
                            *st = 2;
                        }
                    }
                }
            }
            break;
        case 0x3A:
            if (*st == 0) {
                if (g_d_GameSettings.GameModeSelected != 5 && ((u8*)&g_d_GameSettings)[0x10] == 0 && port != 0) { // TODO type
                    TASK_OBJ(task, port)->_5C = 30 << 16;
                    TASK_OBJ(task, port)->_68 = 1;
                } else {
                    TASK_OBJ(task, port)->_5C = 20 << 16;
                    TASK_OBJ(task, port)->_68 = 4;
                }
                fn_800626EC(port);
                *st = 1;
            }
            if (*st == 1) {
                if (g_d_GameSettings.GameModeSelected != 5 && ((u8*)&g_d_GameSettings)[0x10] == 0 && port != 0) { // TODO type
                    done = fn_80042DA8((LayoutOwner*)task, port, 50) != 0;
                } else {
                    done = fn_80042DA8((LayoutOwner*)task, port, 0) != 0;
                }
                if (done == 1) {
                    fn_80062674(port);
                    *st = 2;
                }
            }
            break;
        case 0x3C:
            if (g_d_GameSettings._06 != 2) {
                fn_8005F068(task, port);
                if (*st == 1) {
                    done = 0;
                    expected = 0;
                    switch (lbl_803297E0._CF52[port]) {
                    case 0:
                        if (lbl_803297E0._CF54[port] == 1) {
                            expected = 1;
                            done = fn_80042DA8((LayoutOwner*)task, port + 20, 10) != 0;
                        }
                        break;
                    case 1:
                        if (lbl_803297E0._CF54[port] != 1) {
                            expected = 1;
                            done = fn_80042DA8((LayoutOwner*)task, port + 20, 20) != 0;
                        }
                        break;
                    }
                    if (done == expected) {
                        fn_80062674(port);
                        *st = 2;
                    }
                }
            }
            break;
        case 0x3D:
            if (g_d_GameSettings._06 != 2) {
                fn_8005EC88(task, port);
            } else {
                fn_8005B760(task, port);
            }
            if (*st == 1) {
                fn_80062674(port);
                *st = 2;
            }
            break;
        case 0x3E:
            if (g_d_GameSettings._06 != 2) {
                if (*st == 0) {
                    if (lbl_803297E0.slot[port] == 0) {
                        s32 old = lbl_803297E0._CF48[port] - 1;
                        s8 pos = lbl_80354720[port][old].slot;
                        switch (lbl_803297E0._CF52[port]) {
                        case 0:
                            TASK_OBJ(task, old + port * 9 + 0x40)->_68 = 4;
                            TASK_OBJ(task, old + port * 9 + 0x1C)->_5C = 10 << 16;
                            TASK_OBJ(task, old + port * 9 + 0x1C)->_68 = 4;
                            for (k = 0; k < 9; k++) {
                                TASK_OBJ(task, k + port * 9 + 0x64)->flags &= ~2;
                            }
                            break;
                        case 1:
                            TASK_OBJ(task, pos + port * 9 + 0x10A)->_68 = 4;
                            TASK_OBJ(task, pos + port * 9 + 0xF8)->_68 = 4;
                            TASK_OBJ(task, pos + port * 9 + 0xE6)->flags &= ~2;
                            for (k = 0; k < 9; k++) {
                                TASK_OBJ(task, k + port * 9 + 0x12E)->flags &= ~2;
                            }
                            break;
                        }
                    }
                    TASK_OBJ(task, port + 0x18)->_5C = 0;
                    TASK_OBJ(task, port + 0x18)->_68 = 1;
                    fn_800626EC(port);
                    *st = 1;
                }
            } else if (*st == 0) {
                switch (lbl_803297E0._CF52[port]) {
                case 0: {
                    s32 old = lbl_803297E0._CF48[port] - 1;
                    TASK_OBJ(task, old + 0x63)->_68 = 4;
                    TASK_OBJ(task, old + 0x51)->_5C = 10 << 16;
                    TASK_OBJ(task, old + 0x51)->_68 = 4;
                    for (k = 0; k < 9; k++) {
                        TASK_OBJ(task, k + 0x75)->flags &= ~2;
                        TASK_OBJ(task, k + 0x35)->flags &= ~2;
                    }
                    break;
                }
                case 1: {
                    s8 pos = lbl_80354720[port][lbl_803297E0._CF48[port] - 1].slot;
                    TASK_OBJ(task, pos + 0x23)->_68 = 4;
                    TASK_OBJ(task, pos + 0x1A)->_68 = 4;
                    TASK_OBJ(task, pos + 0x11)->flags &= ~2;
                    for (k = 0; k < 9; k++) {
                        TASK_OBJ(task, k + 0x35)->flags &= ~2;
                        TASK_OBJ(task, k + 0x75)->flags &= ~2;
                    }
                    break;
                }
                }
                TASK_OBJ(task, 14)->_5C = 0;
                TASK_OBJ(task, 14)->_68 = 1;
                fn_800626EC(port);
                *st = 1;
            }
            if (*st == 1) {
                fn_80062674(port);
                *st = 2;
            }
            break;
        case 0x3B:
            fn_8005E9D8(task, port);
            break;
        case 0x3F:
            if (g_d_GameSettings._06 != 2) {
                if (*st == 0) {
                    TASK_OBJ(task, 0)->_5C = 20 << 16;
                    TASK_OBJ(task, 0)->_68 = 1;
                    TASK_OBJ(task, 1)->_5C = 30 << 16;
                    TASK_OBJ(task, 1)->_68 = 4;
                    TASK_OBJ(task, 24)->_5C = 10 << 16;
                    TASK_OBJ(task, 24)->_68 = 4;
                    TASK_OBJ(task, 25)->_5C = 0;
                    TASK_OBJ(task, 25)->_68 = 1;
                    TASK_OBJ(task, 18)->_5C = 10 << 16;
                    TASK_OBJ(task, 18)->_68 = 1;
                    TASK_OBJ(task, 19)->_5C = 20 << 16;
                    TASK_OBJ(task, 19)->_68 = 4;
                    fn_800626EC(port);
                    *st = 1;
                }
                if (*st == 1) {
                    done = fn_80042DA8((LayoutOwner*)task, 0, 30) != 0;
                    done += fn_80042DA8((LayoutOwner*)task, 1, 20) != 0;
                    done += fn_80042DA8((LayoutOwner*)task, 0x12, 20) != 0;
                    if (done + (fn_80042DA8((LayoutOwner*)task, 0x13, 10) != 0) == 4) {
                        fn_80062674(port);
                        *st = 2;
                    }
                }
            }
            break;
        case 0x40:
            if (g_d_GameSettings._06 != 2) {
                if (*st == 0) {
                    TASK_OBJ(task, 0)->_5C = 30 << 16;
                    TASK_OBJ(task, 0)->_68 = 4;
                    TASK_OBJ(task, 1)->_5C = 20 << 16;
                    TASK_OBJ(task, 1)->_68 = 1;
                    TASK_OBJ(task, 24)->_5C = 0;
                    TASK_OBJ(task, 24)->_68 = 1;
                    TASK_OBJ(task, 25)->_5C = 10 << 16;
                    TASK_OBJ(task, 25)->_68 = 4;
                    TASK_OBJ(task, 18)->_5C = 20 << 16;
                    TASK_OBJ(task, 18)->_68 = 4;
                    TASK_OBJ(task, 19)->_5C = 10 << 16;
                    TASK_OBJ(task, 19)->_68 = 1;
                    fn_800626EC(port);
                    *st = 1;
                }
                if (*st == 1) {
                    done = fn_80042DA8((LayoutOwner*)task, 0, 20) != 0;
                    done += fn_80042DA8((LayoutOwner*)task, 1, 30) != 0;
                    done += fn_80042DA8((LayoutOwner*)task, 0x12, 10) != 0;
                    if (done + (fn_80042DA8((LayoutOwner*)task, 0x13, 20) != 0) == 4) {
                        fn_80062674(port);
                        *st = 2;
                    }
                }
            }
            break;
        case 0x41:
            if (*st == 0) {
                TASK_OBJ(task, port)->_5C = 20 << 16;
                TASK_OBJ(task, port)->_68 = 1;
                TASK_OBJ(task, port + 0x18)->_5C = 10 << 16;
                TASK_OBJ(task, port + 0x18)->_68 = 4;
                TASK_OBJ(task, port + 0x12)->_5C = 10 << 16;
                TASK_OBJ(task, port + 0x12)->_68 = 1;
                fn_800626EC(port);
                *st = 1;
            }
            if (*st == 1) {
                done = fn_80042D68((LayoutOwner*)task, port, 30) != 0;
                if (done + (fn_80042D68((LayoutOwner*)task, port + 0x12, 20) != 0) == 2) {
                    lbl_803297E0._CF50[port] = 0;
                    fn_80062674(port);
                    *st = 2;
                }
            }
            break;
        case 0x42:
            if (*st == 0) {
                TASK_OBJ(task, port)->_5C = 30 << 16;
                TASK_OBJ(task, port)->_68 = 4;
                TASK_OBJ(task, port + 0x18)->_5C = 0;
                TASK_OBJ(task, port + 0x18)->_68 = 1;
                TASK_OBJ(task, port + 0x12)->_5C = 20 << 16;
                TASK_OBJ(task, port + 0x12)->_68 = 4;
                fn_800626EC(port);
                *st = 1;
            }
            if (*st == 1) {
                done = fn_80042DA8((LayoutOwner*)task, port, 20) != 0;
                if (done + (fn_80042DA8((LayoutOwner*)task, port + 0x12, 10) != 0) == 2) {
                    fn_80062674(port);
                    *st = 2;
                }
            }
            break;
        case 0x43:
            fn_8005C5C4(task, port);
            if (*st == 1) {
                done = 0;
                expected = 0;
                if (g_d_GameSettings._06 != 2) {
                    if (g_d_GameSettings.GameModeSelected == 5) {
                        done = fn_80042DA8((LayoutOwner*)task, 0, 0) != 0;
                        expected = 2;
                        done += fn_80042DA8((LayoutOwner*)task, 1, 0) != 0;
                    } else if (((u8*)&g_d_GameSettings)[0x10] == 0) { // TODO type
                        if (port != 0) {
                            expected = 1;
                            done = fn_80042DA8((LayoutOwner*)task, port, 0) != 0;
                        } else {
                            expected = 1;
                            done = fn_80042DA8((LayoutOwner*)task, port, 50) != 0;
                        }
                    } else if ((TASK_OBJ(task, port)->_5C >> 16) >= 30) {
                        expected = 1;
                        done = fn_80042DA8((LayoutOwner*)task, port, 50) != 0;
                    } else {
                        expected = 1;
                        done = fn_80042DA8((LayoutOwner*)task, port, 0) != 0;
                    }
                }
                if (done == expected) {
                    fn_80062674(port);
                    *st = 2;
                }
            }
            break;
        case 0x44:
            if (*st == 0) {
                s8 prev = lbl_803297E0._CF3E[port];
                s32 cur = lbl_803297E0.slot[port] - 1;
                if (lbl_803297E0._CF52[port] == 0) {
                    if (prev != -1 && prev != cur) {
                        TASK_OBJ(task, prev + port * 9 + 0x1C)->_5C = 10 << 16;
                        TASK_OBJ(task, prev + port * 9 + 0x1C)->_68 = 4;
                        TASK_OBJ(task, prev + port * 9 + 0x40)->_5C = 10 << 16;
                        TASK_OBJ(task, prev + port * 9 + 0x40)->_68 = 4;
                    }
                } else {
                    s8 curPos = lbl_80354720[port][cur].slot;
                    s8 prevPos = 0;
                    if (prev != -1) { // the original reads it unconditionally
                        prevPos = lbl_80354720[port][prev].slot;
                    }
                    if (g_d_GameSettings._06 != 2) {
                        if (prev != -1 && prevPos != curPos) {
                            TASK_OBJ(task, prevPos + port * 9 + 0x10A)->_68 = 4;
                            TASK_OBJ(task, prevPos + port * 9 + 0xF8)->_68 = 4;
                        }
                    } else if (prev != -1 && prevPos != curPos) {
                        TASK_OBJ(task, prevPos + 0x23)->_68 = 4;
                        TASK_OBJ(task, prevPos + 0x1A)->_68 = 4;
                    }
                }
                lbl_803297E0._CF3E[port] = 0xFF;
                fn_800626EC(port);
                *st = 1;
            }
            if (*st == 1) {
                fn_80062674(port);
                *st = 2;
            }
            break;
        case 0x45: {
            u8 any = FALSE;
            if (lbl_803C66B0.steps[9][1] == 0) {
                for (j = 0; j < 9; j++) {
                    s8 got = gChallengeState.trackers[inMemRoster[1][j].stats.CharID].scoutFlagsAchieved;
                    for (k = 0; k < got; k++) {
                        any = TRUE;
                        TASK_OBJ(task, k + j * 5 + 0x16D)->_68 = 1;
                    }
                }
                if (any) {
                    if (g_d_GameSettings._06 == 2) {
                        sndFXStartEx(0x1B1, 0x7F, 0x3F, 0);
                    } else {
                        sndFXStartEx(0x1E6, 0x7F, 0x3F, 0);
                    }
                }
                fn_800626EC(0);
                lbl_803C66B0.steps[9][1] = 1;
            }
            if (lbl_803C66B0.steps[9][1] == 1) {
                fn_80062674(0);
                lbl_803C66B0.steps[9][1] = 2;
            }
            break;
        }
        case 0x46:
            TASK_OBJ(task, 466)->flags |= 2;
            TASK_OBJ(task, 466)->_68 = 1;
            lbl_803C66B0.step[0] = 0;
            break;
        }
        fn_8005A350(task, port);
    }
    if (lbl_803297E0._CF45 != 0) {
        lbl_803297E0._CF45 = 0;
        fn_800B0A14_removeQueue(fn_80034CEC(task));
    }
}
#endif

// .text:0x80061B9C size:0x7D0
// NONMATCHING 84%: the original keeps dead duplicate condition branches (inlined helpers) and different register use
#if NONMATCHING
void fn_80061B9C(void) {
    SceneTask* task = lbl_803CC1B8;
    s8 team;
    s32 i;
    s8 v;
    BOOL show;
    u8 flag;

    lbl_803297E0._CF45 = 0;
    team = lbl_803297E0._CF3B;
    if (g_d_GameSettings._06 != 2) {
        fn_80034E20(task, &lbl_801000A8);
        TASK_OBJ(task, 16)->_5C = lbl_8034E9A0.teamPort[0] << 16;
        if (((u8*)&g_d_GameSettings)[0x10] == 0) { // TODO type
            TASK_OBJ(task, 17)->_5C = ((s8)(lbl_8034E9A0.teamPort[0] == 0) + 4) << 16;
        } else {
            TASK_OBJ(task, 17)->_5C = lbl_8034E9A0.teamPort[1] << 16;
        }
        if (g_d_GameSettings.GameModeSelected != 5) {
            for (i = 0; i < 9; i++) {
                TASK_OBJ(task, i + 0x164)->flags &= ~2;
            }
            TASK_OBJ(task, 466)->flags &= ~2;
            fn_8005C2B0(task);
            fn_8005BF40(task);
        } else {
            CharacterStats* player = inMemRoster[0];
            OrderEntry* slot = lbl_80354720[0];

            TASK_OBJ(task, 466)->flags &= ~2;
            fn_8005BB5C(task);
            for (i = 0; i < 9; i++, player++, slot++) {
                s8 pos = slot->slot;
                fn_800363D8(task, pos + 0x10A, 1, 0x83, player->stats.CharID);
                TASK_OBJ(task, i + 0xE6)->flags &= ~2;
                if (g_d_GameSettings.GameModeSelected == 5) {
                    flag = ((u8*)&gChallengeState)[0x43D6 + player->stats.CharID]; // TODO type
                } else {
                    flag = lbl_8034E9A0.boosted[0][i];
                }
                if (flag != 0) {
                    TASK_OBJ(task, pos + 0x140)->_68 = 1;
                    TASK_OBJ(task, pos + 0x152)->flags |= 2;
                    TASK_OBJ(task, pos + 0x152)->_5C = 0;
                    TASK_OBJ(task, pos + 0x152)->_68 = 1;
                } else {
                    TASK_OBJ(task, pos + 0x152)->flags &= ~2;
                }
                TASK_OBJ(task, i + 0x12E)->flags &= ~2;
                TASK_OBJ(task, i + 0xF8)->_64 = lbl_8034E9A0.teamPort[0] + 30;
            }
        }
        if (g_d_GameSettings.GameModeSelected == 5) {
            TASK_OBJ(task, 23)->flags &= ~2;
        }
    } else {
        fn_80034E20(task, &lbl_801041C8);
        if (g_d_GameSettings.home_AwaySetting != 0) {
            if (g_d_GameSettings.GameModeSelected == 5 && gChallengeState._441F == 0x13) {
                show = team != 0;
            } else {
                show = team == 0;
            }
        } else {
            show = team != 0;
        }
        if (show) {
            TASK_OBJ(task, 6)->flags &= ~2;
            TASK_OBJ(task, 9)->flags &= ~2;
            TASK_OBJ(task, 7)->_5C = (lbl_8034E9A0._470D[team] % 4) << 16;
            TASK_OBJ(task, 10)->_5C = (lbl_8034E9A0._470D[team] % 4) << 16;
        } else {
            TASK_OBJ(task, 7)->flags &= ~2;
            TASK_OBJ(task, 10)->flags &= ~2;
            TASK_OBJ(task, 6)->_5C = (lbl_8034E9A0._470D[team] % 4) << 16;
            TASK_OBJ(task, 9)->_5C = (lbl_8034E9A0._470D[team] % 4) << 16;
        }
        if (((u8*)&g_d_GameSettings)[0x10] == 0 && team != 0) { // TODO type
            if (lbl_8034E9A0.teamPort[team] == -1) {
                v = (team != 0) + 4;
            } else {
                v = lbl_8034E9A0.teamPort[team] + 4;
            }
        } else {
            v = lbl_8034E9A0.teamPort[team];
        }
        TASK_OBJ(task, 12)->_5C = v << 16;
        TASK_OBJ(task, 2)->_5C = 20 << 16;
        TASK_OBJ(task, 2)->_68 = 0;
        TASK_OBJ(task, 4)->_5C = 20 << 16;
        TASK_OBJ(task, 5)->_5C = 24 << 16;
        TASK_OBJ(task, 4)->_68 = 0;
        TASK_OBJ(task, 5)->_68 = 0;
        TASK_OBJ(task, 8)->_5C = 10 << 16;
        TASK_OBJ(task, 8)->_68 = 0;
        if (lbl_803297E0._CFA2[team] == 1) {
            TASK_OBJ(task, 80)->_64 = 0x28;
            TASK_OBJ(task, 1)->_64 = 0x47;
            TASK_OBJ(task, 1)->_5C = 20 << 16;
            TASK_OBJ(task, 1)->_68 = 0;
        }
        fn_8005B298(task);
        fn_8005AF68(task);
    }
    lbl_803CC1B8->func = fn_80060184;
}
#endif

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
        u8 kind = lbl_803297E0._CFA2[lbl_803297E0._CF3B];
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
void fn_800625A4(s32 index, s32 step) {
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

static inline s32 CharJointSound(CharModel* obj, u16 joint) {
    CharJointMapObj* model = lbl_8036E548.chars[obj->playerIdx];
    if (model != NULL) {
        return model->jointMap[joint];
    }
    return 0xFFFF;
}

static inline void PlayCharJointSound(CharModel* obj) {
    s32 i;

    if (lbl_80366158._28 != 1) {
        for (i = 0; lbl_80108BE0[i] != 0xFFFF && CharJointSound(obj, lbl_80108BE0[i]) == 0xFFFF; i++) {
        }
        if (lbl_80108BE0[i] != 0xFFFF) {
            lbl_80108B90[0] = lbl_803CBD0C;
            fn_800324EC(lbl_80108BE0[i], obj->playerIdx, -1, lbl_80108B90);
        }
    }
}

// .text:0x80062C60 size:0x134
// NONMATCHING 95%: r7/r8 swapped in the inlined joint loop (see docs/patterns/regalloc.md)
#if NONMATCHING
void fn_80062C60(CharModel* model, s32 animID, u32 colorIdx, f32 frame) {
    if (lbl_80366158._28 != 1) {
        if (frame == 0.5f) {
            PlayCharJointSound(model);
        }
        fn_8006C3F8(model, frame, animID, colorIdx);
    }
}
#endif

// .text:0x80062D94 size:0xD8
// NONMATCHING 95%: r7/r9/r10 rotated in the joint loop (see docs/patterns/regalloc.md)
#if NONMATCHING
void fn_80062D94(CharModel* model) {
    PlayCharJointSound(model);
}
#endif

// .text:0x80062E6C size:0x68
void fn_80062E6C(CharModel* model, s32 animID, u32 colorIdx, f32 frame) {
    s32 index = animID - 0x28;
    if (lbl_80366158._28 != 1) {
        fn_8004B1C0(lbl_80108BF0[index][model->charID], model, animID, colorIdx, frame);
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
