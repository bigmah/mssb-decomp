#include "mssbTypes.h"

// .text:0x00091B7C size:0x4
void fn_2_91B7C(void) {}

// .text:0x00091B28 size:0x4
void fn_2_91B28(void) {}

// .text:0x00091C40 size:0xC
void fn_2_91C40(u8* object) {
    *(s16*)(object + 0x90) = 2;
}

// .text:0x00091B70 size:0xC
void fn_2_91B70(u8* object) {
    *(s16*)(object + 0x90) = 2;
}
