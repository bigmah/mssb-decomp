#include "challenge/rep_0250.h"

extern void fn_1_973C(void* object);
extern void fn_1_9380(void* object);
#include "static/UnknownHomes_Static.h"
extern void fn_1_8F34(void* object);

// .text:0x96D0 size:0x4
void fn_1_96D0(void) {
}

void fn_1_90B8(void) {
    fn_800B0A5C_insertQueue((void*)fn_1_8F34, 2);
}

void fn_1_96A4(void) {
    fn_800B0A5C_insertQueue((void*)fn_1_9380, 2);
}

void fn_1_97B8(void) {
    fn_800B0A5C_insertQueue((void*)fn_1_973C, 2);
}
