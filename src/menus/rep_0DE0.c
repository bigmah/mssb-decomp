#include "menus/rep_0DE0.h"
#include "static/UnknownHomes_Static.h"


extern u8* lbl_2_bss_1A8248[];
extern MenuDrawWorld* lbl_2_bss_340140[];
extern const f32 lbl_2_rodata_E88;

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
