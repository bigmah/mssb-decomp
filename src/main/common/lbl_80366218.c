// main.dol common .bss 0x80366218-0x80367318: uninitialised globals, compiled with -common on;
// the linker places all commons after the other .bss, one block per object in link order.
// 2 commons in one object (text system (file_8000F150)): the first one's slot is inflated by the others' size
// (docs/common_bss.md). mwcc lists them in reverse declaration order, so they are
// declared last to first.
#include "main/file_8000F150.h"

TextSystem lbl_80366B18;
u16 lbl_80366218[0x80]; // character code -> glyph map
