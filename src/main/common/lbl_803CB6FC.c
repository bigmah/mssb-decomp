// main.dol common .bss 0x803CB6FC-0x803CB734: uninitialised globals, compiled with -common on;
// the linker places all commons after the other .bss, one block per object in link order.
// 2 commons in one object (skinning (file_800BDEA0)): the first one's slot is inflated by the others' size
// (docs/common_bss.md). mwcc lists them in reverse declaration order, so they are
// declared last to first.
#include "main/file_800BDEA0.h"

void* lbl_803CB724[4]; // locked-cache work buffers
SKAccBuffer lbl_803CB6FC[2];
