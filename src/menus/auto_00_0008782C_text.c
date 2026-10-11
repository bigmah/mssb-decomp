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
    return;
}

// .text:0x00087FB0 size:0x2A0
void fn_2_87FB0(SceneTask* task) {
    return;
}

// .text:0x00088250 size:0x178
void fn_2_88250(SceneTask* task) {
    return;
}

// .text:0x000883C8 size:0x430
void fn_2_883C8(SceneTask* task) {
    return;
}

// .text:0x000887F8 size:0x598
void fn_2_887F8(SceneTask* task) {
    return;
}

// .text:0x00088D90 size:0x2A8
void fn_2_88D90(SceneTask* task) {
    return;
}

// .text:0x00089038 size:0x5C0
void fn_2_89038(SceneTask* task) {
    return;
}

// .text:0x000895F8 size:0x164
s32 fn_2_895F8(u8 alt) {
    return 0;
}

// .text:0x0008975C size:0x814
void fn_2_8975C(void) {
    return;
}

// .text:0x00089F70 size:0x98
void fn_2_89F70(void) {
    return;
}

// .text:0x0008A008 size:0x81C
void fn_2_8A008(SceneTask* task) {
    return;
}

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

