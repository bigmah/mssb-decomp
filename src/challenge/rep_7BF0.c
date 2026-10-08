#include "challenge/rep_7BF0.h"
#include "static/UnknownHomes_Static.h"

extern void fn_1_273D8(u8* object);
extern void* lbl_80366158[];
extern ChallengeQueueEntry* lbl_803CC1B8;
extern u8 lbl_1_bss_471BC[];
extern u8 lbl_1_bss_471D8[];
extern f32 lbl_1_rodata_7DFC;
extern void fn_1_272DC(void*, u32);
extern void fn_1_AF4(s32, s32, f32);
extern void fn_1_28CE8(u8*);

// fn_1_29414, size:0x78
void fn_1_29414(u8* object) {
    if (object[0x14] != 0) {
        fn_80048BEC(lbl_1_bss_471BC, 0, 0);
    }
    fn_1_272DC(lbl_1_bss_471D8, 0);
    fn_1_AF4(10, 10, lbl_1_rodata_7DFC);
    fn_1_28CE8(object);
}

// fn_1_29A48, size:0x54
void fn_1_29A48(void) {
    ChallengeQueueState* state;

    fn_800AD038(lbl_80366158[2]);
    fn_800A97D0(16, 30);
    state = lbl_803CC1B8->state;
    state->state = 1;
    fn_800B0A14_removeQueue(state);
}


// fn_1_289C0, size:0x20
void fn_1_289C0(u8* object) {
    fn_1_273D8(object);
}
