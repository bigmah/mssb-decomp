#include "menus/rep_0DE0.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"
#include <string.h>
#include "Dolphin/OS/OSCache.h"
#include "C3/charPipeline.h"


extern MenuDrawWorld* lbl_2_bss_340140[];
extern const f32 lbl_2_rodata_E88;
extern MenuDrawWorld lbl_8036E548;
extern const f32 lbl_2_rodata_EE0[];
extern const f32 lbl_2_rodata_EE4[];
extern const f32 lbl_2_rodata_EE8[];
extern const f32 lbl_2_rodata_EEC[];
extern const f32 lbl_2_rodata_ED4[];
extern const f32 lbl_2_rodata_EF0[];
extern MenuCamera lbl_2_bss_1A81D4;
extern u8 lbl_803CBBC0[];
extern u8 lbl_2_data_2E9B4[][8];
extern void fn_2_48D54(void);
extern void fn_2_86470(void);
extern void fn_2_85D6C(Mtx);
extern void fn_2_190DC(ActorObjectTable*, Mtx);
extern void fn_800A7D4C(s32, void*);
extern f32 fn_2_4A1E8(f32, f32);
extern const f32 lbl_2_rodata_EAC;
extern Vec lbl_2_data_2E9C4;
extern Vec lbl_2_data_2E9D0;
extern f32 lbl_2_bss_B29C;

// fn_2_868C8, size:0xEC
void fn_2_868C8(void) {
    Vec position;
    Vec difference;
    MenuDrawState* state = lbl_2_bss_340140[0]->states;
    f32 x;
    f32 z;

    memcpy(&position, &state->position, sizeof(Vec));
    PSVECSubtract(&position, &lbl_2_data_2E9D0, &difference);
    x = difference.x * lbl_2_rodata_EAC;
    z = difference.z * lbl_2_rodata_EAC;
    difference.x = x;
    difference.z = z;
    if (0.0f != x || 0.0f != z) {
        lbl_2_bss_B29C = fn_2_4A1E8(difference.z, x);
    }
    memcpy(&lbl_2_data_2E9D0, &state->position, sizeof(Vec));
    state->position.x = position.x;
    state->position.y = position.y;
    state->position.z = position.z;
    state->rotation.x = lbl_2_data_2E9C4.x;
    state->rotation.y = lbl_2_bss_B29C;
    state->rotation.z = lbl_2_data_2E9C4.z;
}

// fn_2_86FEC, size:0xE8
void fn_2_86FEC(void) {
    Mtx44 projection;
    C_MTXFrustum(projection, lbl_2_rodata_EE0[0], lbl_2_rodata_EE4[0],
        lbl_2_rodata_EE8[0], lbl_2_rodata_EEC[0], lbl_2_rodata_ED4[0], lbl_2_rodata_EF0[0]);
    GXSetProjection(projection, GX_PERSPECTIVE);
    fn_2_48D54();
    fn_2_86470();
    fn_2_85D6C(lbl_2_bss_1A81D4.view);
    PSMTXCopy(lbl_2_bss_1A81D4.view, fn_80052768_getCamera(0)->view);
    fn_800A7D4C(0, lbl_2_data_2E9B4[lbl_803CBBC0[0]]);
    fn_2_190DC(lbl_2_bss_340140[0]->table, fn_80052768_getCamera(0)->view);
}

// fn_2_86F40, size:0xAC
void fn_2_86F40(void) {
    ActorObject* object;
    s32 index;
    for (index = 0; index < (s32)lbl_8036E548.table->count; index++) {
        object = &lbl_8036E548.table->objects[index];
        if (object->actor != NULL && lbl_8036E548.table->objects[index].animateBones != 0) {
            if (lbl_8036E548.states[index].draw != NULL) {
                lbl_8036E548.states[index].draw(index);
            }
            fn_800BDA94(object, fn_80052768_getCamera(0)->view);
        }
    }
}

// fn_2_86A0C, size:0x74
void fn_2_86A0C(void) {
    s32 index;
    for (index = 0; index < 3; index++) {
        camera_803c639c_s* camera = fn_80052768_getCamera(0);
        LITXForm(lbl_2_bss_340140[0]->lights[index], camera->view);
    }
}

// fn_2_869B4, size:0x58
void fn_2_869B4(void) {
    s32 index;
    MenuDrawState* state;

    for (index = 0; index < (s32)lbl_2_bss_340140[0]->count; index++) {
        state = &lbl_2_bss_340140[0]->states[index];
        state->position.x = lbl_2_rodata_E88;
        state->position.y = lbl_2_rodata_E88;
        state->position.z = lbl_2_rodata_E88;
        state->rotation.x = lbl_2_rodata_E88;
        state->rotation.y = lbl_2_rodata_E88;
        state->rotation.z = lbl_2_rodata_E88;
    }
}

// .text:0x87114 size:0x4
void fn_2_87114(void) {
}

// fn_2_870D4, size:0x40
void fn_2_870D4(f32 value) {
    if (value) {
        lbl_2_bss_340140[0]->unk307A = 3;
    } else {
        lbl_2_bss_340140[0]->unk307A = 0;
    }
}

extern const Vec lbl_2_rodata_E70;
extern const Vec lbl_2_rodata_E7C;
extern const f32 lbl_2_rodata_E8C[];
extern f32 lbl_2_data_2E944[][6];
extern s8 lbl_2_bss_33FBF5;
extern void makeLookAtMatrix(Mtx m, Vec* camPos, Vec* camUp, Vec* target);

// .text:0x8563C size:0x268
void fn_2_8563C(MenuCamera* camera) {
    Mtx rotX;
    Mtx rotY;
    Mtx combined;
    Vec up = lbl_2_rodata_E70;
    Vec angles;
    Vec offset = lbl_2_rodata_E7C;
    f32 c;
    f32 s;

    camera->yaw = 0xC19F;
    camera->pitch = 0;
    camera->offsetX = 0.0f;
    camera->offsetZ = 0.0f;
    angles.x = camera->yaw;
    angles.y = camera->pitch;
    angles.z = 0.0f;
    PSVECScale(&angles, lbl_2_rodata_E8C[0], &angles);
    PSMTXRotRad(rotX, 'X', angles.x);
    PSMTXRotRad(rotY, 'Y', angles.y);
    s = rotY[0][2];
    c = rotY[0][0];
    PSMTXConcat(rotY, rotX, combined);
    PSMTXMultVec(combined, &offset, &camera->target);
    camera->eye.x += camera->offsetZ * s - camera->offsetX * c;
    camera->eye.z += camera->offsetZ * c + camera->offsetX * s;
    camera->target.x += camera->eye.x;
    camera->target.y += camera->eye.y;
    camera->target.z += camera->eye.z;
    camera->eye.x = lbl_2_data_2E944[lbl_2_bss_33FBF5][0];
    camera->eye.y = lbl_2_data_2E944[lbl_2_bss_33FBF5][1];
    camera->eye.z = lbl_2_data_2E944[lbl_2_bss_33FBF5][2];
    camera->target.x = lbl_2_data_2E944[lbl_2_bss_33FBF5][3];
    camera->target.y = lbl_2_data_2E944[lbl_2_bss_33FBF5][4];
    camera->target.z = lbl_2_data_2E944[lbl_2_bss_33FBF5][5];
    makeLookAtMatrix(camera->view, &camera->eye, &up, &camera->target);
}

extern const f32 lbl_2_rodata_EF4[];
extern const f32 lbl_2_rodata_EF8[];
extern const f32 lbl_2_rodata_EFC[];
extern const f32 lbl_2_rodata_F00[];
extern const f32 lbl_2_rodata_F04[];
extern const f32 lbl_2_rodata_F08[];
extern s8 lbl_2_bss_B2A4;
extern s8 lbl_2_bss_B2A5;

// .text:0x86DCC size:0x174
// NONMATCHING 90%: only register allocation differs (preset base r11 vs r31)
#if NONMATCHING
void fn_2_86DCC(void) {
    Mtx44 projection;

    lbl_2_bss_1A81D4.eye.x = lbl_2_data_2E944[lbl_2_bss_33FBF5][0];
    lbl_2_bss_1A81D4.eye.y = lbl_2_data_2E944[lbl_2_bss_33FBF5][1];
    lbl_2_bss_1A81D4.eye.z = lbl_2_data_2E944[lbl_2_bss_33FBF5][2];
    lbl_2_bss_1A81D4.target.x = lbl_2_data_2E944[lbl_2_bss_33FBF5][3];
    lbl_2_bss_B2A5 = 0;
    lbl_2_bss_B2A4 = 0;
    lbl_2_bss_1A81D4.target.y = lbl_2_data_2E944[lbl_2_bss_33FBF5][4];
    lbl_2_bss_1A81D4.target.z = lbl_2_data_2E944[lbl_2_bss_33FBF5][5];
    C_MTXFrustum(projection, lbl_2_rodata_EE0[0], lbl_2_rodata_EE4[0],
        lbl_2_rodata_EE8[0], lbl_2_rodata_EEC[0], lbl_2_rodata_ED4[0], lbl_2_rodata_EF0[0]);
    GXSetProjection(projection, GX_PERSPECTIVE);
    fn_800B806C(0, lbl_2_rodata_EF4[0], lbl_2_rodata_EF8[0], lbl_2_rodata_EFC[0],
        lbl_2_rodata_F00[0], lbl_2_rodata_F04[0], lbl_2_rodata_EAC, lbl_2_rodata_F08[0]);
    lbl_2_bss_1A81D4.unk54 = 0;
    lbl_2_bss_1A81D4.offsetZ = lbl_2_rodata_E88;
    lbl_2_bss_1A81D4.yaw = 0xC19F;
    lbl_2_bss_1A81D4.pitch = 0;
}
#endif

extern Vec lbl_2_rodata_E58;
extern Vec lbl_2_rodata_E64;
extern const f32 lbl_2_rodata_E98[];
extern const f32 lbl_2_rodata_E9C;

// Debug fly camera: sticks orbit/zoom, triggers move the target up/down.
// .text:0x858A4 size:0x21C
void fn_2_858A4(MenuCamera* camera) {
    Mtx rotX;
    Mtx rotY;
    Mtx combined;
    Vec up = lbl_2_rodata_E58;
    Vec angles;
    Vec offset = lbl_2_rodata_E64;
    MenuDebugPad* pad = g_MenuDebugPad;

    if (!(pad->held & 0x10)) {
        camera->yaw -= pad->substickY;
        camera->pitch += pad->substickX;
        camera->offsetZ += pad->stickY * lbl_2_rodata_E98[0];
        camera->target.y += pad->triggerRight * lbl_2_rodata_E9C;
        camera->target.y -= pad->triggerLeft * lbl_2_rodata_E9C;
    }
    angles.x = camera->yaw;
    angles.y = camera->pitch;
    angles.z = lbl_2_rodata_E88;
    PSVECScale(&angles, lbl_2_rodata_E8C[0], &angles);
    PSMTXRotRad(rotX, 'X', angles.x);
    PSMTXRotRad(rotY, 'Y', angles.y);
    PSMTXConcat(rotX, rotY, combined);
    offset.z = -camera->offsetZ;
    PSMTXMultVec(combined, &offset, &offset);
    PSVECAdd(&offset, &camera->target, &camera->eye);
    PSMTXMultVec(combined, &up, &offset);
    makeLookAtMatrix(camera->view, &camera->eye, &offset, &camera->target);
}

extern Vec lbl_2_rodata_E40;
extern Vec lbl_2_rodata_E4C;
extern const f32 lbl_2_rodata_EA8[];

// Debug walk camera: substick turns, main stick strafes/moves, triggers raise/lower.
// .text:0x85AC0 size:0x2AC
void fn_2_85AC0(MenuCamera* camera) {
    Mtx rotX;
    Mtx rotY;
    Mtx combined;
    Vec up = lbl_2_rodata_E40;
    Vec angles;
    Vec offset = lbl_2_rodata_E4C;
    MenuDebugPad* pad = g_MenuDebugPad;
    f32 c;
    f32 s;

    if (!(pad->held & 0x10)) {
        camera->yaw -= pad->substickY;
        camera->pitch += pad->substickX;
        camera->offsetX = pad->stickX / lbl_2_rodata_EA8[0];
        camera->offsetZ = pad->stickY * lbl_2_rodata_E98[0];
        camera->eye.y += pad->triggerRight * lbl_2_rodata_E9C;
        camera->eye.y -= pad->triggerLeft * lbl_2_rodata_E9C;
    }
    angles.x = camera->yaw;
    angles.y = camera->pitch;
    angles.z = lbl_2_rodata_E88;
    PSVECScale(&angles, lbl_2_rodata_E8C[0], &angles);
    PSMTXRotRad(rotX, 'X', angles.x);
    PSMTXRotRad(rotY, 'Y', angles.y);
    s = rotY[0][2];
    c = rotY[0][0];
    PSMTXConcat(rotY, rotX, combined);
    PSMTXMultVec(combined, &offset, &camera->target);
    camera->eye.x += camera->offsetZ * s - camera->offsetX * c;
    camera->eye.z += camera->offsetZ * c + camera->offsetX * s;
    camera->target.x += camera->eye.x;
    camera->target.y += camera->eye.y;
    camera->target.z += camera->eye.z;
    makeLookAtMatrix(camera->view, &camera->eye, &up, &camera->target);
}

extern MenuStageData lbl_2_data_2E608;
extern const f32 lbl_2_rodata_F0C;
extern void fn_800BD548(ActorObject* entry, u8 numArgs, ...);
extern void CTRLSetTranslation(Control* control, f32 x, f32 y, f32 z);
extern void CTRLSetRotation(Control* control, f32 x, f32 y, f32 z);

// Creates actor objects [start, start + count) for the current stadium's background.
// .text:0x87654 size:0x1D8
// NONMATCHING 74%: the original reaches lbl_2_data_2E608's sub-tables through one anchored .data pool base (file statics), we index a struct
#if NONMATCHING
static void menuStageApplyTexSet(s32 i, s32 model, s32 texSet) {
    s32 j;
    s32 k;
    s16* texIndex;
    for (j = 0; j < lbl_2_data_2E608.boneCount[model]; j++) {
        texIndex = lbl_2_data_2E608.texIndex[texSet];
        for (k = 0; k < lbl_2_data_2E608.texCount[model]; k++) {
            lbl_2_bss_340140[0]->table->objects[i].actor->boneArray[j]->dispObj->textureData
                ->texturePalette->tex[k].texIndex = j + *texIndex++;
        }
    }
}

void fn_2_87654(s32 unused, s32 start, s32 count, void* animBank, s32 arg5) {
    s32 i;
    s32 model;
    s32 texSet;
    s32 hasTexSet;
    MenuStageObject* object;

    for (i = start; i < start + count; i++) {
        object = &lbl_2_data_2E608.objects[lbl_2_bss_33FBF5][i];
        model = object->model;
        texSet = object->texSet;
        hasTexSet = object->hasTexSet;
        fn_800BDC88(lbl_2_bss_340140[0]->table, i, i, lbl_2_bss_340140[0]->models[model].layout, animBank, arg5);
        fn_800BD548(&lbl_2_bss_340140[0]->table->objects[i], 4, lbl_2_bss_340140[0]->lights[0],
            lbl_2_bss_340140[0]->lights[1], lbl_2_bss_340140[0]->lights[2], lbl_2_bss_340140[0]->lights[3]);
        CTRLSetTranslation((Control*)lbl_2_bss_340140[0]->table->objects[i].worldControl, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation((Control*)lbl_2_bss_340140[0]->table->objects[i].worldControl, -90.0f, 0.0f, 0.0f);
        if (hasTexSet != 0) {
            menuStageApplyTexSet(i, model, texSet);
        }
    }
}
#endif

extern void* _OSAllocFromHeap(s32 align, s32 size);

// Allocates the draw states and actor table for the current stadium's background objects.
// .text:0x87118 size:0x238
// NONMATCHING 72%: inlines fn_2_87654; same data-pool anchor difference
#if NONMATCHING
void fn_2_87118(void) {
    lbl_2_bss_340140[0]->count = lbl_2_data_2E608.objectCount[lbl_2_bss_33FBF5];
    lbl_2_bss_340140[0]->states = _OSAllocFromHeap(0x20, lbl_2_bss_340140[0]->count * sizeof(MenuDrawState));
    lbl_2_bss_340140[0]->table = ActorObjectInitTable(lbl_2_bss_340140[0]->count);
    fn_2_87654(0, 0, lbl_2_bss_340140[0]->count, NULL, 0);
}
#endif

// fn_2_87118, then resets every draw state and clears each object's animateBones flag.
// .text:0x87350 size:0x304
// NONMATCHING 79%: inlines fn_2_87118; same data-pool anchor difference
#if NONMATCHING
void fn_2_87350(void) {
    s32 i;

    fn_2_87118();
    for (i = 0; i < lbl_2_bss_340140[0]->count; i++) {
        lbl_2_bss_340140[0]->states[i].position.x = lbl_2_rodata_E88;
        lbl_2_bss_340140[0]->states[i].position.y = lbl_2_rodata_E88;
        lbl_2_bss_340140[0]->states[i].position.z = lbl_2_rodata_E88;
        lbl_2_bss_340140[0]->states[i].rotation.x = lbl_2_rodata_E88;
        lbl_2_bss_340140[0]->states[i].rotation.y = lbl_2_rodata_E88;
        lbl_2_bss_340140[0]->states[i].rotation.z = lbl_2_rodata_E88;
        lbl_2_bss_340140[0]->states[i].unk26 = 0;
        lbl_2_bss_340140[0]->states[i].draw = NULL;
        lbl_2_bss_340140[0]->table->objects[i].animateBones = 0;
    }
}
#endif
