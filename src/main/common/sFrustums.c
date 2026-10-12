// main.dol common .bss 0x803CB1FC-0x803CB49C: uninitialised globals, compiled with -common on;
// the linker places all commons after the other .bss, one block per object in link order.
// Owner in the original: C3/control/control.c.
#include "C3/control.h"

CTRLFrustum sFrustums[4];
