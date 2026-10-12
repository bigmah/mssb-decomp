// Translation unit 0x05F0: the options menu. .text 0x194BC..0x19F2C, .data 0x2798..0x2B78,
// common .bss lbl_2_bss_1033C (formerly part of the auto_00_000194BC_text split).
// The .data (a debug-menu header copy, the option names, fn_2_19D04's jump table) and
// the common block (separate from rep_0568's lbl_2_bss_101AC block) place this code in
// its own unit after rep_0568; whether fn_2_194BC belongs here or ends rep_0568 is unknown.
// Functions in reverse address order (-inline deferred).
#define REP_HEADER_FN repHeader_menus_05F0
#include "header_rep_inline.h"
#include "menus/rep_05F0.h"
#include "menus/menu_work.h"
#include "main/file_800BD8C4.h"
#include "main/file_80021308.h"
#include "main/file_80008E00.h"
#include "main/menu_globals.h"  // lbl_803C66B0, lbl_8034E978, lbl_803C50E8, SavedSettings
#include "main/file_8001FE00.h" // SceneFade lbl_8037169C
extern SavedSettings lbl_800E8754;
extern SoundManager lbl_800EF808;
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"
#include "musyx/musyx.h"
#include "menus/auto_00_00000D08_text.h"

// .data: header statics (unreferenced copies), then fn_2_19D04's jump table.
#include "menus/debug_menu_data.h"
#include "menus/option_names_data.h"

OptionsMenu lbl_2_bss_1033C;

extern void fn_80021204(void);
extern s32 fn_8003AE70(s32 selector);
extern s32 lbl_2_bss_1598;
extern u8* lbl_803CC1B8[];
extern void initializeUnknown(void);
extern void fn_80021228(u8);
extern void fn_80062A74(void);
extern void fn_800A97EC(s32, u32, u8);
extern u8 lbl_800EFBA4[]; // menu sound-effect volumes
extern MenuSelVars lbl_2_bss_F410;
extern void fn_800625A4(s32 port, s32 sound);
extern void fn_8003BF54(u8 a, u8 b, u8 slot, u8 c, u8 d, u8 e, u8 f, u8 g, u8 h);
extern void fn_2_96D20(void);
extern void* memset(void*, int, size_t);

// Buttons latched by the menus, one per port.
typedef struct MenuPadState {
    u16 held;
    u16 pressed;
    u16 repeat;
} MenuPadState;

// Character select work area (lbl_8034E9A0; see CharSelWork in main/file_8004207C.h).
typedef struct CharSelPads {
    /*0x0000*/ u8 _0000[0x46E8];
    /*0x46E8*/ u8* _46E8[4]; // heap marks (CharSelectState, main/charsel_state_type.h)
    /*0x46F8*/ s8 teamPort[2];
    /*0x46FA*/ u8 _46FA[0x472C - 0x46FA];
    /*0x472C*/ MenuPadState input[4];
} CharSelPads;
extern CharSelPads lbl_8034E9A0;

// Same test as fn_2_19554 (settings differ from the saved ones), with an int result.
static inline s32 settingsChanged(void) {
    s32 result = 0;
    if (lbl_800EF808.unk398 != fn_8003AE70(0) || lbl_800EF808.outputMode != fn_8003AE70(1) || lbl_80366158._1F != fn_8003AE70(2)) {
        result = 1;
    }
    return result;
}

// fn_2_19D04, size:0x228
// Options menu scene state machine.
void fn_2_19D04(void) {
    OptionsMenu* menu = &lbl_2_bss_1033C;
    switch (menu->state) {
    case 0:
        if (lbl_8037169C._13 == 0) {
            break;
        }
        menu->state = 1;
    case 1:
        changeScene(1, 6);
        lbl_2_bss_F410._08 = 0;
        lbl_2_bss_F410._0C = 0;
        fn_2_96D20();
        fn_800625A4(0, 0x59);
        lbl_2_bss_1033C.prevCursor = 0;
        lbl_2_bss_1033C.cursor = 0;
        lbl_2_bss_1033C.editing = 0;
        fn_2_19778();
        lbl_2_bss_1033C._0D = lbl_2_bss_1033C.rumble != 0;
        lbl_2_bss_1033C.state = 2;
        break;
    case 2:
        if (lbl_803C66B0.step[0] == 0) {
            menu->state = 3;
        }
        break;
    case 3:
        fn_2_197AC(lbl_8034E9A0.teamPort[0]);
        break;
    case 5:
        fn_2_194E8();
        fn_8003BF54(0, 0, 0, 0, 1, 4, 1, 0, 4);
        ((MenuTask*)lbl_803CC1B8[0])->_10 = 0;
        lbl_2_bss_1033C.state = 6;
        break;
    case 6: {
        s16 result = ((MenuTask*)lbl_803CC1B8[0])->_10;
        if (result != 0) {
            switch (result) {
            case 1:
            case 11:
                fn_800625A4(0, 0x5A);
                lbl_2_bss_1033C.state = 4;
                break;
            default:
                lbl_2_bss_1033C.state = 5;
                break;
            }
        }
        break;
    }
    case 4:
        if (lbl_803C66B0.active[0] == 0) {
            menu->_0F = 1;
            menu->state = 0;
            lbl_8034E978._26 = 1;
            fn_2_11A0(5);
        }
        break;
    }
}

// fn_2_197AC, size:0x558
// Options menu input for one controller port.
void fn_2_197AC(u8 port) {
    MenuPadState in;
    u8 changed = 0;
    u8 old;

    if (lbl_8034E9A0.teamPort[port] == -1) {
        return;
    }
    memset(&in, 0, sizeof(in));
    in.held = lbl_8034E9A0.input[port].held;
    in.pressed = lbl_8034E9A0.input[port].pressed;
    in.repeat = lbl_8034E9A0.input[port].repeat;

    if (in.pressed & 0x100) {
        if (lbl_2_bss_1033C.editing) {
            fn_2_195DC();
        } else {
            lbl_2_bss_1033C.editing = 1;
        }
        fn_800625A4(0, 0x5C);
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (in.pressed & 0x200) {
        if (lbl_2_bss_1033C.editing) {
            lbl_2_bss_1033C.editing = 0;
            fn_800625A4(0, 0x5C);
            fn_2_19778();
        } else if (lbl_803C50E8._47 != 0) {
            fn_2_194E8();
            fn_800625A4(0, 0x5A);
            lbl_2_bss_1033C.state = 4;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        } else {
            if (settingsChanged()) {
                lbl_2_bss_1033C.state = 5;
            } else {
                fn_800625A4(0, 0x5A);
                lbl_2_bss_1033C.state = 4;
            }
        }
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    } else if (in.repeat & 8) {
        if (!lbl_2_bss_1033C.editing) {
            lbl_2_bss_1033C.prevCursor = lbl_2_bss_1033C.cursor;
            lbl_2_bss_1033C.cursor--;
            if (lbl_2_bss_1033C.cursor < 0) {
                lbl_2_bss_1033C.cursor = 2;
            } else if (lbl_2_bss_1033C.rumble == 0 && lbl_2_bss_1033C.cursor == 1) {
                lbl_2_bss_1033C.cursor--;
            }
            fn_800625A4(0, 0x5B);
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (in.repeat & 4) {
        if (!lbl_2_bss_1033C.editing) {
            lbl_2_bss_1033C.prevCursor = lbl_2_bss_1033C.cursor;
            lbl_2_bss_1033C.cursor++;
            if (lbl_2_bss_1033C.cursor == 3) {
                lbl_2_bss_1033C.cursor = 0;
            } else if (lbl_2_bss_1033C.rumble == 0 && lbl_2_bss_1033C.cursor == 1) {
                lbl_2_bss_1033C.cursor++;
            }
            fn_800625A4(0, 0x5B);
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (in.pressed & 1) {
        if (lbl_2_bss_1033C.editing) {
            switch (lbl_2_bss_1033C.cursor) {
            case 0: {
                changed = lbl_2_bss_1033C.rumble == 0;
                lbl_2_bss_1033C.rumble = 1;
                lbl_2_bss_1033C._0A = 0;
                break;
            }
            case 1:
                lbl_2_bss_1033C.prevSound = lbl_2_bss_1033C.sound;
                if (lbl_2_bss_1033C.sound > 0) {
                    lbl_2_bss_1033C.sound--;
                    changed = 1;
                }
                break;
            case 2: {
                changed = lbl_2_bss_1033C.option2 == 0;
                lbl_2_bss_1033C.option2 = 1;
                break;
            }
            }
            if (changed) {
                fn_800625A4(0, 0x5B);
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (in.pressed & 2) {
        if (lbl_2_bss_1033C.editing) {
            switch (lbl_2_bss_1033C.cursor) {
            case 0:
                old = lbl_2_bss_1033C.rumble;
                lbl_2_bss_1033C.rumble = 0;
                if (lbl_2_bss_1033C.rumble == 0) {
                    lbl_2_bss_1033C._0A = 0;
                } else {
                    lbl_2_bss_1033C._0A = 1;
                }
                if (old != lbl_2_bss_1033C.rumble) {
                    changed = 1;
                }
                break;
            case 1:
                old = lbl_2_bss_1033C.sound;
                lbl_2_bss_1033C.prevSound = old;
                lbl_2_bss_1033C.sound++;
                if (lbl_2_bss_1033C.sound == 3) {
                    lbl_2_bss_1033C.sound = 2;
                }
                if (old != lbl_2_bss_1033C.sound) {
                    changed = 1;
                }
                break;
            case 2:
                old = lbl_2_bss_1033C.option2;
                lbl_2_bss_1033C.option2 = 0;
                if (old != lbl_2_bss_1033C.option2) {
                    changed = 1;
                }
                break;
            }
            if (changed) {
                fn_800625A4(0, 0x5B);
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    }
}

// fn_2_19778, size:0x34
void fn_2_19778(void) {
    s8 x = lbl_800EF808.unk398;
    s8 y = lbl_80366158._1F;
    s8 z = lbl_800EF808.soundMode;
    lbl_2_bss_1033C.rumble = x;
    lbl_2_bss_1033C.option2 = y;
    lbl_2_bss_1033C.sound = z;
}

// fn_2_195DC, size:0x19C
void fn_2_195DC(void) {
    OptionsMenu* menu = &lbl_2_bss_1033C;
    switch (menu->cursor) {
    case 0:
        if (menu->rumble != 0 && lbl_800EF808.unk398 == 0) {
            initializeUnknown();
            fn_800B0A5C_insertQueue(fn_80062A94, 0x1000);
        } else if (menu->rumble == 0 && lbl_800EF808.unk398 != 0) {
            fn_80062A74();
        }
        lbl_800EF808.unk398 = menu->rumble;
        lbl_2_bss_1033C._0D = menu->rumble;
        break;
    case 1:
        if (menu->sound != lbl_800EF808.soundMode) {
            fn_80062A74();
            if (menu->sound == 1) {
                lbl_800EF808.soundMode = 1;
            } else if (menu->sound == 0) {
                lbl_800EF808.soundMode = 0;
            } else {
                lbl_800EF808.soundMode = 2;
            }
            fn_80021228(lbl_800EF808.soundMode);
            fn_800B0A5C_insertQueue(fn_80062A94, 0x1000);
            lbl_800EF808.soundMode = menu->sound;
        }
        break;
    case 2:
        if (menu->option2 != 0) {
            lbl_80366158._1F = 1;
            fn_800A97EC(0, 0x32, 1);
        } else {
            lbl_80366158._1F = 0;
        }
        break;
    }
    lbl_2_bss_1033C.editing = 0;
}

// fn_2_195D8, size:0x4
void fn_2_195D8(void) {
}

// fn_2_19554, size:0x84
s8 fn_2_19554(void) {
    s32 result = 0;
    if (lbl_800EF808.unk398 != fn_8003AE70(0) || lbl_800EF808.outputMode != fn_8003AE70(1) || lbl_80366158._1F != fn_8003AE70(2)) {
        result = 1;
    }
    return result;
}

// fn_2_19520, size:0x34
void fn_2_19520(void) {
    s8 x = lbl_800EF808.unk398;
    s8 y = lbl_80366158._1F;
    s8 z = lbl_800EF808.soundMode;
    lbl_2_bss_1033C.rumble = x;
    lbl_2_bss_1033C.option2 = y;
    lbl_2_bss_1033C.sound = z;
}

// fn_2_194E8, size:0x38
void fn_2_194E8(void) {
    fn_80021204();
    lbl_800E8754._23[2] = lbl_80366158._1F;
}

// fn_2_194BC, size:0x2C
void fn_2_194BC(struct ActorObject* object) {
    void* p = object->lights[0];
    if (p != NULL) {
        fn_800B9AA8(p);
    }
}
