// main.dol common .bss 0x803C78C4-0x803C7A24: uninitialised globals, compiled with -common on;
// the linker places all commons after the other .bss, one block per object in link order.
// 4 commons in one object (movie player (file_800ADC40)): the first one's slot is inflated by the others' size
// (docs/common_bss.md). mwcc lists them in reverse declaration order, so they are
// declared last to first.
#include "main/file_800ADC40.h"

MovMramRing lbl_803C7A00;
MovAramRing lbl_803C79D4;
ARQRequest lbl_803C7994[2]; // MRAM -> ARAM
ARQRequest lbl_803C78C4[2]; // ARAM -> MRAM
