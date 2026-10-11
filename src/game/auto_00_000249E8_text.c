#include "game/auto_00_000249E8_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_E08.h"
#include "game/rep_1838.h"
#include "Dolphin/stl.h"

// main.dol (main/file_80011640.h)
void QueueCharacterAnimation(s32 index, s32 anim, s32 a, s32 b, s32 c, s32 d, s32 e);
void AnimateCharacter(s32 index, s32 anim, s32 a, u8 mode, s32 b, s32 c, s32 d, s32 e);

extern SceneActorSetup lbl_3_data_1D28[];
extern SceneActorSetup lbl_3_data_1E434[];
extern SceneActorSetup lbl_3_data_1F090[];
extern u8* lbl_3_data_1F40[13]; // per mode: actor-setup script

typedef struct Unk2398Entry {
    /*0x00*/ u8 _00[0x34];
    /*0x34*/ s32 _34[3];
} Unk2398Entry; // size: 0x40
extern Unk2398Entry lbl_3_data_2398[];

// .text:0x000249E8 size:0xF4 mapped:0x80663A7C
void fn_3_249E8(s32 idx) {
    SceneActorSetup* e = &lbl_3_data_1F090[idx];
    s32 i;
    u8 key = e->actor;

    for (i = 0; i < 9; i++) {
        if (key == g_Fielders[i].opponentIdx) {
            lbl_3_common_bss_1323C->actorSetup[i] = idx;
            if (!e->keepPos) {
                memcpy(&g_Fielders[i], e, 0xC);
            }
            g_Fielders[i].rotY = lbl_3_common_bss_1323C->actors[i].rotY = e->rotY;
            lbl_3_common_bss_1323C->animSet[i] = 1;
            AnimateCharacter(i, e->anim, e->animA, e->animMode, e->animB, e->animArg, 0, 0);
        }
    }
}

// .text:0x00024ADC size:0x2E0 mapped:0x80663B70
void fn_3_24ADC(void) {
    return;
}

// .text:0x00024DBC size:0xE4 mapped:0x80663E50
void fn_3_24DBC(void) {
    return;
}

// .text:0x00024EA0 size:0x80 mapped:0x80663F34
void fn_3_24EA0(void) {
    return;
}

// .text:0x00024F20 size:0x4 mapped:0x80663FB4
void fn_3_24F20(void) {
    return;
}

// .text:0x00024F24 size:0x1D8 mapped:0x80663FB8
void fn_3_24F24(void) {
    return;
}

// .text:0x000250FC size:0xE8 mapped:0x80664190
void fn_3_250FC(void) {
    return;
}
