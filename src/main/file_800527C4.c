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
extern u8 lbl_8034E9A0[];
extern CharModelTable lbl_8036E548;

extern s32 fn_800698F8(s32 kind);
extern void fn_80032064(Vec* pos, s32* params);
extern void fn_80032284(Vec* pos);
extern void fn_800324EC(u16 id, s32 charIndex, s32 c, s32* params);
extern void fn_8004B1C0(s32 sound, CharSoundObj* obj, s32 kind, s32 c);

extern camera_803c639c_s lbl_803C639C[4];
extern Unk803C60BC lbl_803C60BC;
extern u32 lbl_803CB880;
extern MenuState lbl_8034E978;
extern MenuDef lbl_800FEF70[0x5D];
extern MenuWork lbl_803297E0;
extern u8 lbl_80361B20[0xF8];
extern struct SpaniDesc lbl_80108048;

extern void fn_80034E20(SceneTask* task, struct SpaniDesc* desc);
extern void fn_8006CF6C(void);
extern BOOL fn_80042D68(SceneTask* owner, s32 idx, s32 frame);
extern BOOL fn_80042DA8(SceneTask* owner, s32 idx, s32 frame);
extern TutorialInput lbl_803C5F04;

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
void fn_80052968(void) {
    return;
}

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
void fn_80053FE8(void) {
    return;
}

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
void fn_80055374(void) {
    return;
}

// .text:0x80055798 size:0x254
void fn_80055798(void) {
    return;
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
void drawStarProgressionMenu(void) {
    return;
}

// .text:0x80056F70 size:0x350
void someChallengeStarFunction(void) {
    return;
}

// .text:0x800572C0 size:0x430
void someChallengeStarFunction2(void) {
    return;
}

// .text:0x800576F0 size:0x518
void challengeCheckStarsMenuLoading(void) {
    return;
}

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
void fn_80057CAC(void) {
    return;
}

// .text:0x80058050 size:0x344
void fn_80058050(void) {
    return;
}

// .text:0x80058394 size:0x2B0
void fn_80058394(void) {
    return;
}

// .text:0x80058644 size:0x4DC
void fn_80058644(void) {
    return;
}

// .text:0x80058B20 size:0x2EC
void fn_80058B20(void) {
    return;
}

// .text:0x80058E0C size:0x64C
void fn_80058E0C(void) {
    return;
}

// .text:0x80059458 size:0x27C
void fn_80059458(void) {
    return;
}

// .text:0x800596D4 size:0x464
void fn_800596D4(void) {
    return;
}

// .text:0x80059B38 size:0x818
void starMissionRelated1(void) {
    return;
}

// .text:0x8005A350 size:0xC18
void fn_8005A350(void) {
    return;
}

// .text:0x8005AF68 size:0x330
void fn_8005AF68(void) {
    return;
}

// .text:0x8005B298 size:0x4C8
void fn_8005B298(void) {
    return;
}

// .text:0x8005B760 size:0x3FC
void fn_8005B760(void) {
    return;
}

// .text:0x8005BB5C size:0x3E4
void fn_8005BB5C(void) {
    return;
}

// .text:0x8005BF40 size:0x370
void fn_8005BF40(void) {
    return;
}

// .text:0x8005C2B0 size:0x314
void fn_8005C2B0(void) {
    return;
}

// .text:0x8005C5C4 size:0x26C
void fn_8005C5C4(void) {
    return;
}

// .text:0x8005C830 size:0x4B4
void fn_8005C830(void) {
    return;
}

// .text:0x8005CCE4 size:0x1130
void fn_8005CCE4(void) {
    return;
}

// .text:0x8005DE14 size:0xBC4
void fn_8005DE14(void) {
    return;
}

// .text:0x8005E9D8 size:0x2B0
void fn_8005E9D8(void) {
    return;
}

// .text:0x8005EC88 size:0x3E0
void fn_8005EC88(void) {
    return;
}

// .text:0x8005F068 size:0x6CC
void fn_8005F068(void) {
    return;
}

// .text:0x8005F734 size:0x29C
void fn_8005F734(void) {
    return;
}

// .text:0x8005F9D0 size:0x2D0
void fn_8005F9D0(void) {
    return;
}

// .text:0x8005FCA0 size:0x4E4
void fn_8005FCA0(void) {
    return;
}

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

    lbl_8034E9A0[0x48AE] = 1;
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
    lbl_8034E9A0[0x48B3] = 0;
    lbl_803C6714.voiceA = 0;
    lbl_803C6714.stopA = 0;
    lbl_803C6714.activeA = 0;
}

// fn_80062A74, size:0x20
void fn_80062A74(void) {
    lbl_803C6714.stopA = 1;
    lbl_8034E9A0[0x48B3] = 1;
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
