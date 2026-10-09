#include "menus/rep_0DE0.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"


extern u8* lbl_2_bss_1A8248[];
extern MenuDrawWorld* lbl_2_bss_340140[];
extern const f32 lbl_2_rodata_E88;
extern MenuDrawWorld lbl_8036E548;
extern void fn_800BDA94(void*, void*);
extern const f32 lbl_2_rodata_EE0[];
extern const f32 lbl_2_rodata_EE4[];
extern const f32 lbl_2_rodata_EE8[];
extern const f32 lbl_2_rodata_EEC[];
extern const f32 lbl_2_rodata_ED4[];
extern const f32 lbl_2_rodata_EF0[];
extern Mtx lbl_2_bss_1A81D4;
extern u8 lbl_803CBBC0[];
extern u8 lbl_2_data_2E9B4[][8];
extern void fn_2_48D54(void);
extern void fn_2_86470(void);
extern void fn_2_85D6C(Mtx);
extern void fn_2_190DC(MenuDrawCollection*, Mtx);
extern void fn_800A7D4C(s32, void*);

// fn_2_86FEC, size:0xE8
void fn_2_86FEC(void) {
    Mtx44 projection;
    C_MTXFrustum(projection, lbl_2_rodata_EE0[0], lbl_2_rodata_EE4[0],
        lbl_2_rodata_EE8[0], lbl_2_rodata_EEC[0], lbl_2_rodata_ED4[0], lbl_2_rodata_EF0[0]);
    GXSetProjection(projection, GX_PERSPECTIVE);
    fn_2_48D54();
    fn_2_86470();
    fn_2_85D6C(lbl_2_bss_1A81D4);
    PSMTXCopy(lbl_2_bss_1A81D4, fn_80052768_getCamera(0)->view);
    fn_800A7D4C(0, lbl_2_data_2E9B4[lbl_803CBBC0[0]]);
    fn_2_190DC(lbl_2_bss_340140[0]->collection, fn_80052768_getCamera(0)->view);
}

// fn_2_86F40, size:0xAC
void fn_2_86F40(void) {
    MenuDrawDescriptor* descriptor;
    s32 index;
    for (index = 0; index < (s32)lbl_8036E548.collection->count; index++) {
        descriptor = &lbl_8036E548.collection->rows[index].descriptor;
        if (descriptor->actor != NULL && lbl_8036E548.collection->rows[index].visible != 0) {
            if (lbl_8036E548.states[index].draw != NULL) {
                lbl_8036E548.states[index].draw(index);
            }
            fn_800BDA94(descriptor, fn_80052768_getCamera(0)->view);
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
        lbl_2_bss_1A8248[0][0x307A] = 3;
    } else {
        lbl_2_bss_1A8248[0][0x307A] = 0;
    }
}
