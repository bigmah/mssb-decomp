// main.dol common .bss 0x803C50B0-0x803C50E8: uninitialised globals, compiled with -common on;
// the linker places all commons after the other .bss, one block per object in link order.
// 2 commons in one object (file_8003A688): the first one's slot is inflated by the others' size
// (docs/common_bss.md). mwcc lists them in reverse declaration order, so they are
// declared last to first.
#include "Dolphin/gx.h"

GXTlutObj lbl_803C50DC;
GXTexObj lbl_803C50B0;
