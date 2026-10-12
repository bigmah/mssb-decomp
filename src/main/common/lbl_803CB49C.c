// main.dol common .bss 0x803CB49C-0x803CB6FC: uninitialised globals, compiled with -common on;
// the linker places all commons after the other .bss, one block per object in link order.
// 2 commons in one object (file_800B9974): the first one's slot is inflated by the others' size
// (docs/common_bss.md). mwcc lists them in reverse declaration order, so they are
// declared last to first.
#include "Dolphin/gx.h"

GXTexObj lbl_803CB5FC[8];
GXTlutObj lbl_803CB49C[8]; // one per texture map
