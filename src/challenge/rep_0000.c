#include "challenge/rep_0000.h"
#include "static/UnknownHomes_Static.h"

extern u8* lbl_803CC1B8[];
extern void fn_1_16A0(void);
extern void fn_1_1E0(void);
extern void ANIMGet(void* bank, char* name);
extern void LoadActorLayout(void* actor);
extern void convertGeometryAndSknHeader(void* geometry, void* skin);
extern void fn_80025DDC(void* object);

void fn_1_0(void* bank, char* name) {
    ANIMGet(bank, name);
}

void fn_1_1B0(u32* table, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) {
        if (table[i] != 0) {
            table[i] += (u32)table;
        }
    }
}

void fn_1_568(void) {
    u8* queue = lbl_803CC1B8[0];
    if (*(s16*)(queue + 0x10) == 1) {
        *(void**)queue = (void*)fn_1_16A0;
    }
}

void fn_1_5E8(void) {
}


void fn_1_20(ChallengeModelHeader* model) {
    s32 i;
    u32* p = (u32*)model;
    for (i = 0; i < 5; i++) {
        if (p[i] != 0) p[i] += (u32)model;
    }
    convertTextureHeader((void*)model->textures);
    LoadActorLayout((void*)model->actor);
    convertGeometryAndSknHeader((void*)model->geometry, (void*)model->skin);
    haveActLayoutPointToGeoHeader((void*)model->actor, (void*)model->geometry);
    if (model->extra != 0) fn_80025DDC((void*)model->extra);
}

void fn_1_E8(ChallengeModelHeader* model) {
    s32 i;
    u32* p = (u32*)model;
    for (i = 0; i < 5; i++) {
        if (p[i] != 0) p[i] += (u32)model;
    }
    convertTextureHeader((void*)model->textures);
    LoadActorLayout((void*)model->actor);
    convertGeometryAndSknHeader((void*)model->geometry, (void*)model->skin);
    haveActLayoutPointToGeoHeader((void*)model->actor, (void*)model->geometry);
    if (model->extra != 0) fn_80025DDC((void*)model->extra);
}
