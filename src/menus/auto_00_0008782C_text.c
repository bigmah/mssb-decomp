#include "menus/auto_00_0008782C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_8000F150.h"
#include "main/file_8003A688.h"
#include "menus/auto_00_00013BA4_text.h"
#include "string.h"

// main.dol headers that declare these can't be included next to the ones above.
extern void LoadActorLayout(void* layout);
extern void convertGeometryAndSknHeader(void* geometry, void* sknHeader);
extern s32 fn_80042DA8(void* owner, s32 idx, s32 value);
extern void fn_80034E20(void* group, void* descs);
extern u8 lbl_8034E978[]; // TODO type: MenuState (main/file_8004207C.h)
extern UnlockFlags lbl_80361B20;

extern SlotSelectState lbl_2_bss_33FBCC;
extern SlotSelectInfo lbl_2_bss_F410;
extern MenuSceneWork* lbl_2_bss_340140;
extern MenuSceneTex lbl_2_bss_34009C;
extern Unk3401BC* lbl_2_bss_3401BC;
extern u8 lbl_2_data_2F964[8]; // team ids, indexed by logo frame
extern u8 lbl_2_data_2ECE4[];  // SpaniDesc list
// TODO: data split; the button layouts fn_2_89F70 uses live at +0xBAC/+0xCCC/+0xDCC.
extern u8 lbl_2_data_2E9F8[];

// Layout object k + x of the task's run (constant first, as the original adds it last).
#define SLOT_OBJ(task, x, k) (lbl_80371C30[(k) + (task)->u14.objIdx + x].obj) // x: a sum, unparenthesised on purpose
#define CHALLENGE_SAVE(i) ((ChallengeState*)lbl_80354768.challenge[i])

// .text:0x0008782C size:0x16C
void fn_2_8782C(void) {
    u32* file;
    s32 i;
    void* actor;
    void* geometry;
    void* textures;

    lbl_2_bss_340140->entryCount = 0;
    file = lbl_2_bss_340140->resFile;
    for (i = 0; i < 15; i += 5) {
        lbl_2_bss_340140->res[i + 0] = (u8*)file + file[i + 0];
        lbl_2_bss_340140->res[i + 1] = (u8*)file + file[i + 1];
        lbl_2_bss_340140->res[i + 2] = (u8*)file + file[i + 2];
        lbl_2_bss_340140->res[i + 3] = (u8*)file + file[i + 3];
        lbl_2_bss_340140->res[i + 4] = (u8*)file + file[i + 4];
    }
    i++;
    lbl_2_bss_34009C.tex64 = (u8*)file + file[i];
    i++;
    lbl_2_bss_34009C.tex68 = (u8*)file + file[i];
    for (i = 0; i < 5; i++) {
        actor = lbl_2_bss_340140->res[i * 3 + 0];
        geometry = lbl_2_bss_340140->res[i * 3 + 1];
        textures = lbl_2_bss_340140->res[i * 3 + 2];
        LoadActorLayout(actor);
        convertGeometryAndSknHeader(geometry, NULL);
        haveActLayoutPointToGeoHeader(actor, geometry);
        convertTextureHeader(textures);
        fn_800BD190(geometry, (s32)textures); // TODO type: UnknownHomes_Static.h takes s32
    }
    convertTextureHeader(lbl_2_bss_34009C.tex64);
    convertTextureHeader(lbl_2_bss_34009C.tex68);
}

// .text:0x00087998 size:0x618
void fn_2_87998(SceneTask* task) {
    s32 done;
    s32 total;
    s32 i;
    s32 j;
    ChallengeState* save;
    u8 digits[3];

    if ((lbl_2_bss_33FBCC.animStarted == 0) ? TRUE : FALSE) {
        fn_2_8A008(task);
        for (i = 0; i < 3; i++) {
            if (lbl_80354768._CF5E[i] != 0) {
                save = CHALLENGE_SAVE(i);
                if (lbl_2_bss_F410.slot == i) {
                    SLOT_OBJ(task, i, 0x38)->flags |= 2;
                    fn_800363D8(task, i + 0x38, 1, 5, i);
                    digits[0] = save->_43BC / 100;
                    digits[1] = (save->_43BC - digits[0] * 100) / 10;
                    digits[2] = (save->_43BC - digits[0] * 100) - digits[1] * 10;
                    for (j = 0; j < 3; j++) {
                        SLOT_OBJ(task, i * 3 + j, 0xE)->flags |= 2;
                        SLOT_OBJ(task, i * 3 + j, 0xE)->_5C = 0;
                        fn_800363D8(task, i * 3 + 0xE + j, 1, 0xD, digits[j]);
                        SLOT_OBJ(task, i * 3 + j, 0xE)->_68 = 1;
                    }
                    SLOT_OBJ(task, i, 0xB)->_5C = 0;
                    SLOT_OBJ(task, i, 0xB)->_68 = 1;
                    SLOT_OBJ(task, i, 4)->_68 = 1;
                    SLOT_OBJ(task, i, 7)->_64 = 0x13;
                    SLOT_OBJ(task, i, 7)->_5C = 0;
                    SLOT_OBJ(task, i, 7)->_68 = 1;
                } else {
                    SLOT_OBJ(task, i, 4)->_68 = 1;
                    SLOT_OBJ(task, i, 7)->_64 = 0x12;
                    SLOT_OBJ(task, i, 7)->_68 = 1;
                    SLOT_OBJ(task, i, 0xB)->_5C = 0x1A0000;
                    SLOT_OBJ(task, i, 0xB)->_68 = 0;
                }
                if ((save->_444B == -1 && save->_1606 == 0) ||
                    (save->_444B == -1 && save->_1606 != 0 && save->_441B != 0)) {
                    SLOT_OBJ(task, i, 0x35)->_5C = 0;
                    SLOT_OBJ(task, i, 0x35)->_68 = 1;
                }
            }
        }
        SLOT_OBJ(task, lbl_2_bss_33FBCC._10, 7)->flags |= 2;
        SLOT_OBJ(task, lbl_2_bss_33FBCC._10, 7)->_5C = 0;
        SLOT_OBJ(task, lbl_2_bss_33FBCC._10, 7)->_68 = 1;
        SLOT_OBJ(task, lbl_2_bss_33FBCC._10, 4)->flags |= 2;
        SLOT_OBJ(task, lbl_2_bss_33FBCC._10, 0x42)->flags &= ~2;
        lbl_2_bss_33FBCC._10 = -1;
        lbl_2_bss_33FBCC.animStarted = 1;
        lbl_2_bss_33FBCC.animRunning = 1;
    }
    if ((lbl_2_bss_33FBCC.animRunning == 1) ? TRUE : FALSE) {
        done = 0;
        total = 0;
        for (i = 0; i < 3; i++) {
            if (lbl_80354768._CF5E[i] != 0) {
                save = CHALLENGE_SAVE(i);
                if (lbl_2_bss_F410.slot == i) {
                    if (save->_1606 == 0 || (save->_1606 != 0 && save->_441B != 0)) {
                        total++;
                        done += fn_80042DA8(task, i + 0xB, 0x15) != 0;
                    }
                    for (j = 0; j < 3; j++) {
                        total++;
                        done += fn_80042DA8(task, i * 3 + 0xE + j, 0x15) != 0;
                    }
                }
                if (save->_444B != -1) {
                    total++;
                    done += fn_80042DA8(task, i + 0x32, 0xA) != 0;
                }
                if ((save->_444B == -1 && save->_1606 == 0) ||
                    (save->_444B == -1 && save->_1606 != 0 && save->_441B != 0)) {
                    total++;
                    done += fn_80042DA8(task, i + 0x35, 0xE) != 0;
                }
            }
        }
        if (done == total) {
            lbl_2_bss_33FBCC.animStarted = 0;
            lbl_2_bss_33FBCC.anim = 0;
            lbl_2_bss_33FBCC.animRunning = 0;
        }
    }
}

// .text:0x00087FB0 size:0x2A0
void fn_2_87FB0(SceneTask* task) {
    s32 i;
    s32 done;
    s32 total;
    ChallengeState* save;

    if ((lbl_2_bss_33FBCC.animStarted == 0) ? TRUE : FALSE) {
        fn_2_8A008(task);
        SLOT_OBJ(task, lbl_2_bss_33FBCC._10, 7)->_64 = 0x12;
        SLOT_OBJ(task, lbl_2_bss_33FBCC._10, 7)->_5C = 0;
        SLOT_OBJ(task, lbl_2_bss_33FBCC._10, 7)->_68 = 1;
        SLOT_OBJ(task, lbl_2_bss_F410.slot, 7)->_64 = 0x12;
        SLOT_OBJ(task, lbl_2_bss_F410.slot, 7)->_68 = 1;
        SLOT_OBJ(task, lbl_2_bss_33FBCC._10, 4)->flags |= 2;
        SLOT_OBJ(task, lbl_2_bss_33FBCC._10, 0x42)->flags &= ~2;
        lbl_2_bss_33FBCC.animStarted = 1;
        lbl_2_bss_33FBCC.prevSlot = lbl_2_bss_33FBCC._10;
        lbl_2_bss_F410.slot = lbl_2_bss_33FBCC._10;
        lbl_2_bss_33FBCC._10 = -1;
        lbl_2_bss_33FBCC.animRunning = 1;
    }
    if ((lbl_2_bss_33FBCC.animRunning == 1) ? TRUE : FALSE) {
        done = 0;
        total = 0;
        for (i = 0; i < 3; i++) {
            if (lbl_80354768._CF5E[i] != 0) {
                save = CHALLENGE_SAVE(i);
                if (save->_444B != -1) {
                    total++;
                    done += fn_80042DA8(task, i + 0x32, 0xA) != 0;
                } else if (save->_1606 == 0) {
                    total++;
                    done += fn_80042DA8(task, i + 0x35, 0xE) != 0;
                }
            }
        }
        if (done == total) {
            SLOT_OBJ(task, lbl_2_bss_F410.slot, 7)->_64 = 0x13;
            SLOT_OBJ(task, lbl_2_bss_F410.slot, 7)->_68 = 1;
            lbl_2_bss_33FBCC.anim = 0;
            lbl_2_bss_33FBCC.animStarted = 0;
            lbl_2_bss_33FBCC.animRunning = 0;
        }
    }
}

// .text:0x00088250 size:0x178
void fn_2_88250(SceneTask* task) {
    if ((lbl_2_bss_33FBCC.animStarted == 0) ? TRUE : FALSE) {
        SLOT_OBJ(task, lbl_2_bss_33FBCC._0F, 7)->_64 = 0x14;
        SLOT_OBJ(task, lbl_2_bss_33FBCC._0F, 7)->flags |= 2;
        SLOT_OBJ(task, lbl_2_bss_33FBCC._0F, 7)->_5C = 0;
        SLOT_OBJ(task, lbl_2_bss_33FBCC._0F, 7)->_68 = 1;
        SLOT_OBJ(task, lbl_2_bss_F410.slot, 7)->_64 = 0x13;
        SLOT_OBJ(task, lbl_2_bss_F410.slot, 7)->_68 = 1;
        SLOT_OBJ(task, lbl_2_bss_33FBCC._0F, 0x42)->flags |= 2;
        SLOT_OBJ(task, lbl_2_bss_33FBCC._0F, 0x42)->_68 = 1;
        lbl_2_bss_33FBCC.animStarted = 1;
        lbl_2_bss_33FBCC.animRunning = 1;
    }
    if ((lbl_2_bss_33FBCC.animRunning == 1) ? TRUE : FALSE) {
        lbl_2_bss_33FBCC.anim = 0;
        lbl_2_bss_33FBCC.animStarted = 0;
        lbl_2_bss_33FBCC.animRunning = 0;
    }
}

// .text:0x000883C8 size:0x430
void fn_2_883C8(SceneTask* task) {
    s32 i;
    s32 done;
    s32 total;
    ChallengeState* save;

    if (((lbl_2_bss_33FBCC.animStarted == 0) ? TRUE : FALSE) && lbl_2_bss_33FBCC.prevSlot != lbl_2_bss_F410.slot) {
        for (i = 0; i < 3; i++) {
            if (lbl_80354768._CF5E[i] != 0) {
                save = CHALLENGE_SAVE(i);
                if (lbl_2_bss_F410.slot == i) {
                    SLOT_OBJ(task, i, 4)->_68 = 1;
                    SLOT_OBJ(task, i, 7)->_64 = 0x13;
                    SLOT_OBJ(task, i, 7)->_68 = 1;
                    if (save->_1606 == 0 || (save->_1606 != 0 && save->_441B != 0)) {
                        SLOT_OBJ(task, i, 0xB)->_5C = 0x1A0000;
                        SLOT_OBJ(task, i, 0xB)->_68 = 4;
                    }
                } else if (lbl_2_bss_33FBCC.prevSlot == i && i != lbl_2_bss_33FBCC._0F) {
                    SLOT_OBJ(task, i, 4)->_68 = 1;
                    SLOT_OBJ(task, i, 7)->_64 = 0x12;
                    SLOT_OBJ(task, i, 7)->_68 = 1;
                    if (save->_1606 == 0 || (save->_1606 != 0 && save->_441B != 0)) {
                        SLOT_OBJ(task, i, 0xB)->_5C = 0x160000;
                        SLOT_OBJ(task, i, 0xB)->_68 = 1;
                    }
                }
            } else if (lbl_2_bss_F410.slot == i) {
                SLOT_OBJ(task, i, 7)->_64 = 0x13;
                SLOT_OBJ(task, i, 7)->_68 = 1;
            } else {
                SLOT_OBJ(task, i, 7)->_64 = 0x12;
                SLOT_OBJ(task, i, 7)->_68 = 1;
            }
        }
        lbl_2_bss_33FBCC.animStarted = 1;
        lbl_2_bss_33FBCC.animRunning = 1;
    }
    if (((lbl_2_bss_33FBCC.animRunning == 1) ? TRUE : FALSE) && lbl_2_bss_33FBCC.prevSlot != lbl_2_bss_F410.slot) {
        done = 0;
        total = 0;
        for (i = 0; i < 3; i++) {
            if (lbl_80354768._CF5E[i] != 0) {
                save = CHALLENGE_SAVE(i);
                if (lbl_2_bss_F410.slot == i) {
                    if (save->_1606 == 0 || (save->_1606 != 0 && save->_441B != 0)) {
                        total++;
                        done += fn_80042DA8(task, i + 0xB, 0x16) != 0;
                    }
                } else if (lbl_2_bss_33FBCC.prevSlot == i && i != lbl_2_bss_33FBCC._0F) {
                    if (save->_1606 == 0 || (save->_1606 != 0 && save->_441B != 0)) {
                        total++;
                        done += fn_80042DA8(task, i + 0xB, 0x1A) != 0;
                    }
                }
            }
        }
        if (done == total) {
            lbl_2_bss_33FBCC.prevSlot = lbl_2_bss_F410.slot;
            lbl_2_bss_33FBCC.anim = 0;
            lbl_2_bss_33FBCC.animStarted = 0;
            lbl_2_bss_33FBCC.animRunning = 0;
        }
    }
}

// .text:0x000887F8 size:0x598
void fn_2_887F8(SceneTask* task) {
    s32 i;
    s32 j;
    s32 done;
    s32 total;
    ChallengeState* save;
    s32 digits[3];
    s32 rem;

    if ((lbl_2_bss_33FBCC.animStarted == 0) ? TRUE : FALSE) {
        fn_2_8A008(task);
        for (i = 0; i < 3; i++) {
            if (lbl_80354768._CF5E[i] != 0) {
                save = CHALLENGE_SAVE(i);
                if (lbl_2_bss_F410.slot == i) {
                    digits[0] = save->_43BC / 100;
                    digits[1] = (save->_43BC - digits[0] * 100) / 10;
                    digits[2] = (save->_43BC - digits[0] * 100) - digits[1] * 10;
                    for (j = 0; j < 3; j++) {
                        SLOT_OBJ(task, i * 3 + j, 0xE)->flags |= 2;
                        SLOT_OBJ(task, i * 3 + j, 0xE)->_5C = 0;
                        fn_800363D8(task, i * 3 + 0xE + j, 1, 0xD, digits[j]);
                        SLOT_OBJ(task, i * 3 + j, 0xE)->_68 = 1;
                    }
                    SLOT_OBJ(task, i, 4)->_68 = 1;
                    SLOT_OBJ(task, i, 7)->_64 = 0x13;
                    SLOT_OBJ(task, i, 7)->_5C = 0;
                    SLOT_OBJ(task, i, 7)->_68 = 1;
                } else {
                    SLOT_OBJ(task, i, 4)->_68 = 1;
                    SLOT_OBJ(task, i, 7)->_64 = 0x12;
                    SLOT_OBJ(task, i, 7)->_68 = 1;
                    SLOT_OBJ(task, i, 0xB)->_5C = 0x1A0000;
                    SLOT_OBJ(task, i, 0xB)->_68 = 0;
                }
                if (save->_444B != -1) {
                    SLOT_OBJ(task, i, 0x32)->flags |= 2;
                    SLOT_OBJ(task, i, 0x32)->_5C = 0;
                    fn_800363D8(task, i + 0x32, 4, 0x64, save->_444B);
                    SLOT_OBJ(task, i, 0x32)->_68 = 1;
                } else {
                    SLOT_OBJ(task, i, 0x35)->flags &= ~2;
                    SLOT_OBJ(task, i, 0x35)->_68 = 0;
                    SLOT_OBJ(task, i, 0x35)->flags |= 2;
                    SLOT_OBJ(task, i, 0x35)->_68 = 1;
                    SLOT_OBJ(task, i, 0x32)->flags &= ~2;
                }
            }
        }
        SLOT_OBJ(task, lbl_2_bss_F410.slot, 7)->flags |= 2;
        SLOT_OBJ(task, lbl_2_bss_F410.slot, 7)->_5C = 0;
        SLOT_OBJ(task, lbl_2_bss_F410.slot, 7)->_68 = 1;
        SLOT_OBJ(task, lbl_2_bss_F410.slot, 4)->flags |= 2;
        lbl_2_bss_33FBCC.animStarted = 1;
        lbl_2_bss_33FBCC.animRunning = 1;
    }
    if ((lbl_2_bss_33FBCC.animRunning == 1) ? TRUE : FALSE) {
        done = 0;
        total = 0;
        for (i = 0; i < 3; i++) {
            if (lbl_80354768._CF5E[i] != 0) {
                if (lbl_2_bss_F410.slot == i) {
                    for (j = 0; j < 3; j++) {
                        total++;
                        done += fn_80042DA8(task, i * 3 + 0xE + j, 0x15) != 0;
                    }
                }
                save = CHALLENGE_SAVE(i);
                if (save->_444B != -1) {
                    total++;
                    done += fn_80042DA8(task, i + 0x32, 0xA) != 0;
                } else {
                    total++;
                    done += fn_80042DA8(task, i + 0x35, 0xE) != 0;
                }
            }
        }
        if (done == total) {
            lbl_2_bss_33FBCC.animStarted = 0;
            lbl_2_bss_33FBCC.anim = 0;
            lbl_2_bss_33FBCC.animRunning = 0;
        }
    }
}

// .text:0x00088D90 size:0x2A8
void fn_2_88D90(SceneTask* task) {
    s32 i;
    s32 finished;
    ChallengeState* save;

    if ((lbl_2_bss_33FBCC.animStarted == 0) ? TRUE : FALSE) {
        SLOT_OBJ(task, 0, 0)->_5C = 0x190000;
        SLOT_OBJ(task, 0, 0)->_68 = 4;
        for (i = 0; i < 3; i++) {
            SLOT_OBJ(task, i, 4)->_68 = 4;
            if (lbl_80354768._CF5E[i] != 0) {
                SLOT_OBJ(task, i * 3, 0xE)->_68 = 4;
                SLOT_OBJ(task, i * 3, 0xF)->_68 = 4;
                SLOT_OBJ(task, i * 3, 0x10)->_68 = 4;
                SLOT_OBJ(task, i, 0x38)->_68 = 4;
                save = CHALLENGE_SAVE(i);
                if (save->_1606 != 0 && save->_441B == 0) {
                    SLOT_OBJ(task, i, 0x3B)->_68 = 4;
                } else {
                    SLOT_OBJ(task, i, 0x17)->_68 = 4;
                    SLOT_OBJ(task, i, 0xB)->_5C = 0x160000;
                    SLOT_OBJ(task, i, 0xB)->_68 = 4;
                    if (save->_444B != -1) {
                        SLOT_OBJ(task, i, 0x32)->_68 = 4;
                    }
                }
            }
        }
        lbl_2_bss_33FBCC.animStarted = 1;
        lbl_2_bss_33FBCC.animRunning = 1;
    }
    if ((lbl_2_bss_33FBCC.animRunning == 1) ? TRUE : FALSE) {
        finished = fn_80042DA8(task, 0, 0) != 0;
        if ((SLOT_OBJ(task, 0, 0)->_5C >> 16) == 3) {
            changeScene(3, 6);
        }
        if (finished == 1) {
            lbl_8034E9A0._48AF = 1;
            lbl_2_bss_33FBCC.done = 1;
            lbl_2_bss_33FBCC.anim = 0;
            lbl_2_bss_33FBCC.animStarted = 0;
            lbl_2_bss_33FBCC.animRunning = 0;
        }
    }
}

// .text:0x00089038 size:0x5C0
void fn_2_89038(SceneTask* task) {
    s32 i;
    s32 j;
    s32 done;
    s32 total;
    ChallengeState* save;
    s8 digits[3];

    if ((lbl_2_bss_33FBCC.animStarted == 0) ? TRUE : FALSE) {
        for (i = 0; i < 3; i++) {
            if (lbl_80354768._CF5E[i] != 0) {
                save = CHALLENGE_SAVE(i);
                digits[0] = save->_43BC / 100;
                digits[1] = (save->_43BC - digits[0] * 100) / 10;
                digits[2] = save->_43BC - digits[0] * 100 - digits[1] * 10;
                for (j = 0; j < 3; j++) {
                    SLOT_OBJ(task, i * 3 + j, 0xE)->flags |= 2;
                    SLOT_OBJ(task, i * 3 + j, 0xE)->_5C = 0;
                    fn_800363D8(task, i * 3 + 0xE + j, 1, 0xD, digits[j]);
                    SLOT_OBJ(task, i * 3 + j, 0xE)->_68 = 1;
                }
                if (lbl_2_bss_F410.slot == i) {
                    SLOT_OBJ(task, i, 4)->_68 = 1;
                    SLOT_OBJ(task, i, 7)->_64 = 0x13;
                    SLOT_OBJ(task, i, 7)->_5C = 0;
                    SLOT_OBJ(task, i, 7)->_68 = 1;
                } else {
                    SLOT_OBJ(task, i, 4)->_68 = 1;
                    SLOT_OBJ(task, i, 7)->_64 = 0x12;
                    SLOT_OBJ(task, i, 7)->_68 = 1;
                    if (save->_1606 == 0 || (save->_1606 != 0 && save->_441B != 0)) {
                        SLOT_OBJ(task, i, 0xB)->_5C = 0x1A0000;
                        SLOT_OBJ(task, i, 0xB)->_68 = 0;
                        if (save->_444B != -1) {
                            SLOT_OBJ(task, i, 0x32)->flags |= 2;
                            SLOT_OBJ(task, i, 0x32)->_5C = 0;
                            fn_800363D8(task, i + 0x32, 4, 0x64, save->_444B);
                            SLOT_OBJ(task, i, 0x32)->_68 = 1;
                        } else {
                            SLOT_OBJ(task, i, 0x35)->flags &= ~2;
                            SLOT_OBJ(task, i, 0x35)->_68 = 0;
                            SLOT_OBJ(task, i, 0x35)->flags |= 2;
                            SLOT_OBJ(task, i, 0x35)->_68 = 1;
                            SLOT_OBJ(task, i, 0x32)->flags &= ~2;
                        }
                    }
                }
            } else if (lbl_2_bss_F410.slot == i) {
                SLOT_OBJ(task, i, 7)->_64 = 0x13;
                SLOT_OBJ(task, i, 7)->_68 = 1;
            }
        }
        lbl_2_bss_33FBCC.animStarted = 1;
        lbl_2_bss_33FBCC.animRunning = 1;
    }
    if ((lbl_2_bss_33FBCC.animRunning == 1) ? TRUE : FALSE) {
        done = 0;
        total = 0;
        for (i = 0; i < 3; i++) {
            if (lbl_80354768._CF5E[i] != 0) {
                for (j = 0; j < 3; j++) {
                    total++;
                    done += fn_80042DA8(task, i * 3 + 0xE + j, 0x15) != 0;
                }
                save = CHALLENGE_SAVE(i);
                if (save->_1606 == 0 || (save->_1606 != 0 && save->_441B != 0)) {
                    if (lbl_2_bss_F410.slot == i) {
                        total++;
                        done += fn_80042DA8(task, i + 0xB, 0x15) != 0;
                    }
                    if (save->_444B != -1) {
                        total++;
                        done += fn_80042DA8(task, i + 0x32, 0xA) != 0;
                    } else {
                        total++;
                        done += fn_80042DA8(task, i + 0x35, 0xE) != 0;
                    }
                }
            }
        }
        if (done == total) {
            lbl_2_bss_33FBCC.animStarted = 0;
            lbl_2_bss_33FBCC.anim = 0;
            lbl_2_bss_33FBCC.animRunning = 0;
        }
    }
}

// .text:0x000895F8 size:0x164
// Maps a button id to its position in the current button layout.
// NONMATCHING 95%: `li r3, 0` for pos is scheduled before the loads, not after them
#if NONMATCHING
s32 fn_2_895F8(u8 alt) {
    s32 button = lbl_2_bss_F410._54;
    s32 altButton = lbl_2_bss_33FBCC._1C;
    s32 pos;

    pos = 0;
    if (alt) {
        button = altButton;
    }
    switch (lbl_2_bss_33FBCC.mode) {
    case 0:
        switch (button) {
        case 0:
            pos = 0;
            break;
        case 5:
            pos = 1;
            break;
        }
        break;
    case 1:
        switch (button) {
        case 1:
            pos = 0;
            break;
        case 3:
            pos = 1;
            break;
        case 4:
            pos = 2;
            break;
        case 5:
            pos = 3;
            break;
        }
        break;
    case 2:
        switch (button) {
        case 2:
            pos = 0;
            break;
        case 3:
            pos = 1;
            break;
        case 4:
            pos = 2;
            break;
        case 5:
            pos = 3;
            break;
        }
        break;
    case 3:
        switch (button) {
        case 1:
            pos = 0;
            break;
        case 2:
            pos = 1;
            break;
        case 3:
            pos = 2;
            break;
        case 4:
            pos = 3;
            break;
        case 5:
            pos = 4;
            break;
        }
        break;
    }
    return pos;
}
#endif

// .text:0x0008975C size:0x814
void fn_2_8975C(void) {
    SceneTask* task = lbl_803CC1B8;
    s32 count;
    s32 i;
    s32 done;
    s32 total;
    s32 pos;
    s32 altPos;

    switch (lbl_2_bss_33FBCC.mode) {
    case 0:
        count = 2;
        break;
    case 1:
    case 2:
        count = 4;
        break;
    case 3:
        count = 5;
        break;
    }

    switch (lbl_2_bss_33FBCC.btnAnim) {
    case 0x51:
        if (lbl_2_bss_33FBCC.btnStarted == 0) {
            SLOT_OBJ(task, 0, 1)->_68 = 1;
            switch (lbl_2_bss_33FBCC.mode) {
            case 0:
                fn_800363D8(task, 3, 1, 0xCF, 0x13);
                fn_800363D8(task, 4, 1, 0xCF, 0x18);
                break;
            case 1:
                fn_800363D8(task, 3, 1, 0xCF, 0x14);
                fn_800363D8(task, 4, 1, 0xCF, 0x16);
                fn_800363D8(task, 5, 1, 0xCF, 0x17);
                fn_800363D8(task, 6, 1, 0xCF, 0x18);
                break;
            case 2:
                fn_800363D8(task, 3, 1, 0xCF, 0x15);
                fn_800363D8(task, 4, 1, 0xCF, 0x16);
                fn_800363D8(task, 5, 1, 0xCF, 0x17);
                fn_800363D8(task, 6, 1, 0xCF, 0x18);
                break;
            case 3:
                fn_800363D8(task, 3, 1, 0xCF, 0x14);
                fn_800363D8(task, 4, 1, 0xCF, 0x15);
                fn_800363D8(task, 5, 1, 0xCF, 0x16);
                fn_800363D8(task, 6, 1, 0xCF, 0x17);
                fn_800363D8(task, 7, 1, 0xCF, 0x18);
                break;
            }
            for (i = 0; i < count; i++) {
                SLOT_OBJ(task, i, 3)->_68 = 1;
            }
            lbl_2_bss_33FBCC.btnStarted = 1;
            lbl_2_bss_33FBCC.btnRunning = 1;
        }
        if (lbl_2_bss_33FBCC.btnRunning != 0) {
            done = 0;
            total = 0;
            for (i = 0; i < count; i++) {
                if (i == 0) {
                    total++;
                    done += fn_80042DA8(task, i + 3, 8) != 0;
                } else {
                    total++;
                    done += fn_80042DA8(task, i + 3, 3) != 0;
                }
            }
            if (done == total) {
                lbl_2_bss_33FBCC.btnStarted = 0;
                lbl_2_bss_33FBCC.btnRunning = 0;
                lbl_2_bss_33FBCC.btnAnim = 0;
            }
        }
        break;
    case 0x52:
        if (lbl_2_bss_33FBCC.btnStarted == 0) {
            SLOT_OBJ(task, 0, 0)->_68 = 4;
            SLOT_OBJ(task, 0, 1)->_68 = 4;
            for (i = 0; i < count; i++) {
                SLOT_OBJ(task, i, 3)->_5C = 0x30000;
                SLOT_OBJ(task, i, 3)->_68 = 4;
            }
            lbl_2_bss_33FBCC.btnStarted = 1;
            lbl_2_bss_33FBCC.btnRunning = 1;
        }
        if (lbl_2_bss_33FBCC.btnRunning != 0) {
            done = 0;
            total = 0;
            total++;
            done += fn_80042DA8(task, 1, 0) != 0;
            if (done == total) {
                lbl_2_bss_33FBCC.btnStarted = 0;
                lbl_2_bss_33FBCC.btnRunning = 0;
                lbl_2_bss_33FBCC.btnAnim = 0;
            }
        }
        break;
    case 0x53:
        if (lbl_2_bss_33FBCC.btnStarted == 0) {
            pos = fn_2_895F8(0);
            altPos = fn_2_895F8(1);
            SLOT_OBJ(task, pos, 3)->_5C = 0x80000;
            SLOT_OBJ(task, pos, 3)->_68 = 0;
            SLOT_OBJ(task, altPos, 3)->_5C = 0x30000;
            SLOT_OBJ(task, altPos, 3)->_68 = 0;
            lbl_2_bss_33FBCC.btnStarted = 1;
            lbl_2_bss_33FBCC.btnRunning = 1;
        }
        if (lbl_2_bss_33FBCC.btnRunning != 0) {
            fn_2_895F8(0);
            fn_2_895F8(1);
            lbl_2_bss_33FBCC.btnStarted = 0;
            lbl_2_bss_33FBCC.btnRunning = 0;
            lbl_2_bss_33FBCC.btnAnim = 0;
        }
        break;
    }

    if (lbl_2_bss_33FBCC.closing != 0 && lbl_2_bss_33FBCC.btnRunning == 0) {
        lbl_2_bss_33FBCC.closing = 0;
        fn_800B0A14_removeQueue(fn_80034CEC(task));
    }
}

// .text:0x00089F70 size:0x98
void fn_2_89F70(void) {
    u8* data = lbl_2_data_2E9F8;
    SceneTask* task = lbl_803CC1B8;
    u8* descs;

    switch (lbl_2_bss_33FBCC.mode) {
    case 0:
        descs = data + 0xDCC;
        break;
    case 1:
    case 2:
        descs = data + 0xCCC;
        break;
    case 3:
        descs = data + 0xBAC;
        break;
    }
    fn_80034E20(task, descs);
    lbl_2_bss_33FBCC.closing = 0;
    lbl_803CC1B8->func = fn_2_8975C;
}

// .text:0x0008A008 size:0x81C
// NONMATCHING 98%: register allocation in the logo-table scan and the slot-header block
// (team id in r5 not r3); comparing the roster ids against `((u8*)save)[0x441D]` gets the
// roster loop's `addi rN, save, 0x441D` base but not the rest.
#if NONMATCHING
void fn_2_8A008(SceneTask* task) {
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 logo;
    u8 team;
    ChallengeState* save;
    u8 unused[3]; // cleared but never read (the original frame has 0x18 bytes of locals)

    memset(unused, 0, 3);
    for (i = 0; i < 3; i++) {
        if (lbl_80354768._CF5E[i] != 0) {
            save = CHALLENGE_SAVE(i);
            SLOT_OBJ(task, i, 4)->_64 = 0x11;
            fn_800363D8(task, i + 0x38, 1, 5, i);
            if (save->_1606 != 0 && save->_441B == 0) {
                SLOT_OBJ(task, i, 0x3B)->flags |= 2;
                fn_800363D8(task, i + 0x3B, 1, 4, save->_4416);
                SLOT_OBJ(task, i, 0x3B)->_5C = 0;
                SLOT_OBJ(task, i, 0x3B)->_68 = 1;
                fn_800363D8(task, i + 4, 1, 6, save->_4416);
                SLOT_OBJ(task, i, 0xB)->flags &= ~2;
                SLOT_OBJ(task, i, 0x17)->flags &= ~2;
                SLOT_OBJ(task, i, 0x32)->flags &= ~2;
                SLOT_OBJ(task, i, 0x35)->flags &= ~2;
            } else {
                SLOT_OBJ(task, i, 0x3B)->flags &= ~2;
                SLOT_OBJ(task, i, 0xB)->flags |= 2;
                SLOT_OBJ(task, i, 0x17)->flags |= 2;
                SLOT_OBJ(task, i, 0x38)->flags |= 2;
                SLOT_OBJ(task, i, 0x32)->flags |= 2;
                SLOT_OBJ(task, i, 0x35)->flags |= 2;
                SLOT_OBJ(task, i * 3, 0xE)->flags |= 2;
                SLOT_OBJ(task, i * 3, 0xF)->flags |= 2;
                SLOT_OBJ(task, i * 3, 0x10)->flags |= 2;
                team = save->_441D;
                for (k = 0; k < 6; k++) {
                    if (lbl_2_data_2F964[k] == team) {
                        logo = k;
                    }
                }
                save->_441D = team;
                SLOT_OBJ(task, i, 0xB)->_5C = 0;
                fn_800363D8(task, i + 0xB, 1, 0x54, logo);
                SLOT_OBJ(task, i, 0xB)->color = (SLOT_OBJ(task, i, 0xB)->color & ~0xFF) | 0xFF;
                SLOT_OBJ(task, i, 0xB)->_68 = 1;
                if (save->_444B != -1) {
                    SLOT_OBJ(task, i, 0x32)->flags |= 2;
                    SLOT_OBJ(task, i, 0x32)->_5C = 0;
                    fn_800363D8(task, i + 0x32, 4, 0x64, save->_444B);
                    SLOT_OBJ(task, i, 0x32)->_68 = 1;
                    SLOT_OBJ(task, i, 0x35)->flags &= ~2;
                    SLOT_OBJ(task, i, 0x35)->_68 = 0;
                } else {
                    SLOT_OBJ(task, i, 0x35)->flags |= 2;
                    SLOT_OBJ(task, i, 0x35)->_68 = 1;
                    SLOT_OBJ(task, i, 0x32)->flags &= ~2;
                }
                fn_800363D8(task, i + 4, 1, 6, save->_4415);
                n = 0;
                for (j = 0; j < 9; j++) {
                    if (save->teams[j].id != save->_441D) {
                        SLOT_OBJ(task, i * 8 + n++, 0x1A)->_5C = save->teams[j].id << 16;
                    }
                }
            }
        } else {
            SLOT_OBJ(task, i, 4)->_64 = 1;
            SLOT_OBJ(task, i, 4)->_5C = 0;
            SLOT_OBJ(task, i, 4)->_68 = 1;
            fn_800363D8(task, i + 4, 1, 6, 4);
            SLOT_OBJ(task, i, 0xB)->flags &= ~2;
            SLOT_OBJ(task, i, 0x17)->flags &= ~2;
            SLOT_OBJ(task, i, 0x38)->flags &= ~2;
            SLOT_OBJ(task, i, 0x32)->flags &= ~2;
            SLOT_OBJ(task, i, 0x35)->flags &= ~2;
            SLOT_OBJ(task, i, 0x3B)->flags &= ~2;
            SLOT_OBJ(task, i * 3, 0xE)->flags &= ~2;
            SLOT_OBJ(task, i * 3, 0xF)->flags &= ~2;
            SLOT_OBJ(task, i * 3, 0x10)->flags &= ~2;
        }
        if (lbl_2_bss_F410.slot == i) {
            SLOT_OBJ(task, i, 0x3F)->flags |= 2;
        } else {
            SLOT_OBJ(task, i, 0x3F)->flags &= ~2;
        }
    }
}
#endif

// .text:0x0008A824 size:0x3D8
void fn_2_8A824(void) {
    return;
}

// .text:0x0008ABFC size:0x88
void fn_2_8ABFC(void) {
    return;
}

// .text:0x0008AC84 size:0x2C
void fn_2_8AC84(s32 index, s32 value) {
    return;
}

// .text:0x0008ACB0 size:0x2C
void fn_2_8ACB0(s32 index, s32 value) {
    return;
}

// .text:0x0008ACDC size:0x4
void fn_2_8ACDC(void) {
    return;
}

