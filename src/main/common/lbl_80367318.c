// main.dol common .bss 0x80367318-0x8037169C: uninitialised globals, compiled with -common on;
// the linker places all commons after the other .bss, one block per object in link order.
// 3 commons in one object (character manager (file_80011640)): the first one's slot is inflated by the others' size
// (docs/common_bss.md). mwcc lists them in reverse declaration order, so they are
// declared last to first.
#include "main/file_80011640.h"

// Stadium lights. The slot is 0x51E4 = 0x44 + 0x204C + 0x3154 (all 4-aligned), so the
// object is 0x44 bytes: four LightPos and one more word.
typedef struct LightSet {
    /*0x00*/ LightPos pos[4];
    /*0x40*/ u32 _40;
} LightSet;

CharMgr lbl_8036E548;
CharActor lbl_8036C4FC[13];
LightSet lbl_80367318; // viewed as LightPos[4] elsewhere
