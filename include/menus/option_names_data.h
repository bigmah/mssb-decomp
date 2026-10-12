#ifndef __MENUS_OPTION_NAMES_DATA_H__
#define __MENUS_OPTION_NAMES_DATA_H__

#include "mssbTypes.h"

// Options menu item names. File-scope statics of a header: each including unit has
// its own (unreferenced) copy in .data, as in the original (3 copies in menus.rel).
static char optionMenuNames[8][0x20] = {
    "MUSIC", "SOUND", "VIBRATION", "MONAURAL", "STEREO", "SURROUND", "ON", "OFF",
};

#endif
