#include "challenge/auto_00_00009EA0_text.h"
#include "challenge/rep_0010.h"
#include "challenge/rep_02A8.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_80008E00.h"
#include "Unknown/File_0x800a64e0.h"

struct SoundGroupData;

// Start of the sound manager (SoundManager in main/file_80021308.h).
typedef struct ChSoundManager {
    /*0x000*/ u32 _0;
    /*0x004*/ struct SoundGroupData* groups[48];
} ChSoundManager;

extern ChSoundManager lbl_800EF808;
extern AssetLoadInstructions lbl_1_data_196C[]; // challenge sound groups

extern void fn_80021954(struct SoundGroupData** data);
extern void fn_80021980(struct SoundGroupData* data);

// Copy of the main-module sound group loader task (SoundLoadTask, fn_80021758).
typedef struct ChSoundLoadTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ s32 (*callback)(u8* state);
    /*0x18*/ u8 step;
    /*0x19*/ u8 group;
    /*0x1A*/ u8 callbackState;
} ChSoundLoadTask;

// lbl_1_common_bss_49A78 (also used by rep_02A8 as a byte array).
typedef struct ChFileMenu {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ s32 _0C;
    /*0x10*/ u8 _10[0x24 - 0x10];
    /*0x24*/ s32 _24[11];
} ChFileMenu;

extern ChFileMenu lbl_1_common_bss_49A78;

// .text:0x0000A1F4 size:0x1C
void fn_1_A1F4(ChListCursor* list, ChListItem* items, s32 count, s32 visible) {
    list->items = items;
    list->count = count;
    list->visible = visible;
    list->top = 0;
    list->cursor = 0;
}

