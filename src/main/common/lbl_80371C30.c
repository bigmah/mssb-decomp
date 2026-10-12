// main.dol common .bss 0x80371C30-0x803C5090: uninitialised globals, compiled with -common on;
// the linker places all commons after the other .bss, one block per object in link order.
// 3 commons in one object (sprite animation (file_80034F50)): the first one's slot is inflated by the others' size
// (docs/common_bss.md). mwcc lists them in reverse declaration order, so they are
// declared last to first.
#include "main/file_80034F50.h"
#include "main/file_8000F150.h"

SpaniTexSlot lbl_803C4BE0[SPANI_TEX_SLOT_COUNT];
SpaniObj lbl_8039C3E0[SPANI_OBJ_COUNT];
LayoutSlot lbl_80371C30[SPANI_OBJ_COUNT];
