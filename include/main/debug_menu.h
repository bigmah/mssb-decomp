#ifndef __MAIN_DEBUG_MENU_H_
#define __MAIN_DEBUG_MENU_H_

#include "mssbTypes.h"

// Debug menu (see fn_80048820).
struct DebugMenu;

typedef struct DebugMenuItem {
    /*0x00*/ s32 type; // 2: s8, 3-5: u8, 6-8: button action, else s32
    /*0x04*/ const char* label; // NULL ends the item list
    /*0x08*/ s32 min;
    /*0x0C*/ s32 max;
    /*0x10*/ s32 step[3]; // by how long the direction has been held
    /*0x1C*/ void* value;
    /*0x20*/ u32 mask;
    /*0x24*/ s32 _24;
    /*0x28*/ s32 (*func)(struct DebugMenu* menu, u16 buttons);
} DebugMenuItem; // size: 0x2C

typedef struct DebugMenu {
    /*0x00*/ const char* title;
    /*0x04*/ s32 count;
    /*0x08*/ s32 visible;
    /*0x0C*/ s32 top;
    /*0x10*/ s32 cursor;
    /*0x14*/ s32 wrap;
    /*0x18*/ DebugMenuItem* items;
} DebugMenu;

#endif
