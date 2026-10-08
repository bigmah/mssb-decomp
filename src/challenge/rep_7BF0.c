#include "challenge/rep_7BF0.h"
#include "static/UnknownHomes_Static.h"

extern void fn_1_273D8(u8* object);
extern void* lbl_80366158[];
extern ChallengeQueueEntry* lbl_803CC1B8;

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
