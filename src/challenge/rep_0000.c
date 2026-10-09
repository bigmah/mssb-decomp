#include "challenge/rep_0000.h"
#include "static/UnknownHomes_Static.h"

extern u8* lbl_803CC1B8[];
extern void fn_1_16A0(void);
extern void fn_1_1E0(void);
extern void ANIMGet(void* bank, char* name);
extern void LoadActorLayout(void* actor);
extern void convertGeometryAndSknHeader(void* geometry, void* skin);
extern void fn_80025DDC(void* object);
extern u8 lbl_1_data_AC[];
extern u8 lbl_1_bss_4[];
extern u8 lbl_803C6CF8[];
extern u8 lbl_800F1D78[];
extern void LoadFile(void*, void*, s32, s32, s32);
extern s32 fn_800A8518(s32);
extern u32 fn_800A88C8(void);
extern void fn_800A8B78(void*);

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

void fn_1_1E0(void) {
    u8* queue = lbl_803CC1B8[0];
    switch (*(s16*)(queue + 0x10)) {
    case 0:
        LoadFile(lbl_1_data_AC, lbl_1_bss_4, 0, 0, 1);
        *(s16*)(lbl_803CC1B8[0] + 0x10) += 1;
    case 1:
        if (fn_800A8518(1) != 0) {
            *(s16*)(lbl_803CC1B8[0] + 0x10) += 1;
        }
        break;
    case 2:
        if (*(u16*)((u8*)&lbl_803C77B8 + 4) & 0x100) {
            *(s32*)(queue + 0x14) = ARAMTransfer(lbl_800F1D78 + queue[0x18] * 16, 0, 0, 0);
            *(s16*)(lbl_803CC1B8[0] + 0x10) += 1;
        }
        break;
    case 3:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            s32 v = queue[0x18] % 19;
            switch (v) {
            case 0:
                fn_1_20(*(ChallengeModelHeader**)(queue + 0x14));
                break;
            case 1:
                fn_1_E8(*(ChallengeModelHeader**)(queue + 0x14));
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
                ((void (*)(void*))ANIMGet)(*(void**)(queue + 0x14));
                break;
            }
            fn_800ACFB0(*(void**)(queue + 0x14));
            if (*(u16*)&lbl_803C77B8 & 0x200) {
                *(s16*)(lbl_803CC1B8[0] + 0x10) += 1;
            } else {
                s32 n = queue[0x18] + 1;
                queue[0x18] = n;
                *(s32*)(queue + 0x14) = ARAMTransfer(lbl_800F1D78 + (u8)n * 16, 0, 0, 0);
            }
        }
        break;
    case 4:
        if (fn_800A8518(3) != 0) {
            *(s16*)(lbl_803CC1B8[0] + 0x10) += 1;
        }
        break;
    case 5:
        if (fn_800A88C8() == 0) {
            fn_800A8B78(lbl_1_bss_4);
            *(s16*)(lbl_803CC1B8[0] + 0x10) += 1;
        }
        break;
    case 6: {
        u8* object = *(u8**)(queue + 4);
        *(s16*)(object + 0x10) = 1;
        fn_800B0A14_removeQueue(object);
        break;
    }
    }
}
