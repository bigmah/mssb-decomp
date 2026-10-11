#include "challenge/auto_00_00009EA0_text.h"
#include "challenge/rep_0010.h"
#include "challenge/rep_02A8.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_80008E00.h"
#include "Unknown/File_0x800a64e0.h"
extern u8 lbl_803C6CF8[]; // TODO type: ARAMLoader (main/file_800A6870.h); idle at 0x715

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

// .text:0x00009EA0 size:0x64
// Same as fn_800216F8: queues fn_1_9F04 to load sound group `group` from lbl_1_data_196C.
void fn_1_9EA0(u8 group, s32 (*callback)(u8* state)) {
    ChSoundLoadTask* task = fn_800B0A5C_insertQueue(fn_1_9F04, 1);
    task->step = 0;
    task->group = group;
    task->callback = callback;
    ((ChTaskHeader*)lbl_803CC1B8)->result = 0;
}

// .text:0x00009F04 size:0x120
void fn_1_9F04(void) {
    ChSoundLoadTask* task = lbl_803CC1B8;
    ChTaskHeader* parent;

    switch (task->step) {
    case 0:
        // TODO port: ARAMTransfer returns the destination pointer (declared s32 in UnknownHomes_Static.h)
        lbl_800EF808.groups[task->group] = (struct SoundGroupData*)ARAMTransfer(&lbl_1_data_196C[task->group], 0, 1, 0);
        task->step = 1;
        break;
    case 1:
        if ((s32)lbl_803C6CF8[0x715] != 1) {
            break;
        }
        fn_80021980(lbl_800EF808.groups[task->group]);
        task->step = 2;
        task->callbackState = 0;
    case 2:
        if (task->callback(&task->callbackState) == 0) {
            fn_80021954(&lbl_800EF808.groups[task->group]);
            parent = task->h.parent;
            parent->result = 1;
            fn_800B0A14_removeQueue(parent);
        }
        break;
    }
}

// .text:0x0000A024 size:0x160
// Moves the list cursor one row or one page, scrolling the window as needed.
void fn_1_A024(ChListCursor* list, s32 dir) {
    s32 top = list->top;
    s32 visible = list->visible;
    s32 count = list->count;
    s32 cursor = list->cursor;
    s32 row = cursor - top;
    s32 rows;

    if (top + visible < count) {
        rows = visible;
    } else if (count < visible) {
        rows = count;
    } else {
        rows = count - top;
    }

    switch (dir) {
    case CH_LIST_UP:
        if (row != 0) {
            list->cursor--;
        } else if (top != 0) {
            list->top--;
            list->cursor--;
        }
        break;
    case CH_LIST_DOWN:
        if (row + 1 == rows) {
            if (cursor + 1 < count) {
                list->top++;
                list->cursor++;
            }
        } else {
            list->cursor++;
        }
        break;
    case CH_LIST_PAGE_UP:
        if (top < visible) {
            list->top = 0;
            list->cursor = 0;
        } else {
            list->top -= visible;
            list->cursor -= list->visible;
        }
        break;
    case CH_LIST_PAGE_DOWN:
        if (cursor + rows >= count) {
            list->top = count - rows;
            list->cursor = list->count - 1;
        } else {
            list->top += visible;
            list->cursor += list->visible;
        }
        break;
    }
}

// .text:0x0000A184 size:0x70
// Walks the visible item names (the debug print that used them is compiled out).
static inline s32 ch_strlen(const char* s) {
    s32 n = 0;
    while (*s++ != '\0') {
        n++;
    }
    return n;
}

void fn_1_A184(ChListCursor* list) {
    s32 rows;
    ChListItem* item;
    s32 i;

    if (list->top + list->visible < list->count) {
        rows = list->visible;
    } else if (list->count < list->visible) {
        rows = list->count;
    } else {
        rows = list->count - list->top;
    }

    item = &list->items[list->top];
    for (i = 0; i < rows; i++, item++) {
        if (item->name != NULL) {
            ch_strlen(item->name);
        }
    }
}

// .text:0x0000A1F4 size:0x1C
void fn_1_A1F4(ChListCursor* list, ChListItem* items, s32 count, s32 visible) {
    list->items = items;
    list->count = count;
    list->visible = visible;
    list->top = 0;
    list->cursor = 0;
}

// .text:0x0000A210 size:0x40
// Returns the part of `path` after the last '/'.
char* fn_1_A210(char* path) {
    char c;
    char* name = path;

    if (path == NULL) {
        return NULL;
    }
    while ((c = *path++) != '\0') {
        if (c == '/') {
            name = path;
        }
    }
    return name;
}

// .text:0x0000A250 size:0x94
void fn_1_A250(void) {
    s32 i;

    for (i = 0; i < 11; i++) {
        lbl_1_common_bss_49A78._24[i] = -1;
    }
    lbl_1_common_bss_49A78._0C = -1;
    ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_A348;
}
