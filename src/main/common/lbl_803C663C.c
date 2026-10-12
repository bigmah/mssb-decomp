// main.dol common .bss 0x803C663C-0x803C6714: uninitialised globals, compiled with -common on;
// the linker places all commons after the other .bss, one block per object in link order.
// 2 commons in one object (file_800527C4): the first one's slot is inflated by the others' size
// (docs/common_bss.md). mwcc lists them in reverse declaration order, so they are
// declared last to first.
#include "main/menu_globals.h"

TutorialSteps lbl_803C66B0;
u32 lbl_803C663C[4];
