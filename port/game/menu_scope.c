// What the PC port offers: Exhibition at Mario Stadium (plus Practice, Records
// and Options). Challenge, Toy Field, Minigames and the other stadiums aren't
// supported yet; the menus skip them unless `allmodes = true` in user.ini (or
// MSSB_ALLMODES=1 in the environment, for the test scripts).
//
//   main menu (fn_2_1800 / fn_2_1DC8, auto_00_00001254_text.c): entries
//     0 Exhibition, 1 Challenge, 2 Toy Field, 3 Minigames, 4 Practice,
//     5 Records, 6 Options; the draw task (fn_2_747FC) hides 1-3 and moves
//     4-6 up (port_menu_row)
//   stadium select (fn_2_11340): the cursor stays on Mario Stadium (0)
#include "mssbTypes.h"

#include <stdlib.h>

const char* port_user_ini_get(const char* key);
int port_user_ini_bool(const char* key);

static s32 all_modes(void) {
    static s32 s_all = -1;
    if (s_all < 0) {
        const char* env = getenv("MSSB_ALLMODES");
        s_all = (port_user_ini_get("allmodes") != NULL && port_user_ini_bool("allmodes")) ||
                (env != NULL && env[0] == '1');
    }
    return s_all;
}

// Main menu entry `entry` can be picked.
s32 port_menu_mode_enabled(s32 entry) {
    return all_modes() || entry == 0 || entry >= 4;
}

// The row the main menu draws entry `entry` in (-1: hidden).
s32 port_menu_row(s32 entry) {
    if (all_modes()) {
        return entry;
    }
    if (entry == 0) {
        return 0;
    }
    return entry >= 4 ? entry - 3 : -1;
}

// Stadium select can move off Mario Stadium.
s32 port_stadium_select_enabled(void) {
    return all_modes();
}
