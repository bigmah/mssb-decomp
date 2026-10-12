// Translation unit 0x0FD8: .text 0x8ED4C..0x8F0F4 (split off auto_00_0008E6A4_text;
// fn_2_8EEC8 drives fn_2_8EDC4/fn_2_8ED4C). Functions in reverse address order (-inline deferred).
#include "header_rep_data.h"
// math.h before UnknownHomes_Game.h keeps dolsqrtf2 static: its unused extern-inline
// copy would emit _half/_three into this unit's .rodata.
#include "math.h"
#undef SQRT2_LINKAGE
#include "game/UnknownHomes_Game.h"
#include "menus/auto_00_0008E6A4_text.h"
#include "main/file_800527C4.h"
#include "menus/auto_00_00000D08_text.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_8004207C.h"
#include "main/file_80069BDC.h"
#include "main/file_80008E00.h"
#include "Dolphin/os.h"

extern void fn_2_2FC0(u8, s32, s32);
extern void fn_8003F23C(void); // main/file_8003A688.h

extern MenuScreenState lbl_2_bss_340234;
static SceneTask* lbl_2_bss_B2C0; // confirm dialog task (fn_8006C0D0)

// .text:0x0008EEC8 size:0x22C
void fn_2_8EEC8(void) {
    switch (lbl_2_bss_340234.state) {
    case 0:
        if (lbl_803CBBCC->prevScene != 5) {
            fn_80062764((struct SoundLoadTask*)lbl_803CC1B8);
        }
        lbl_2_bss_B2C0 = fn_8006C0D0();
        lbl_2_bss_340234.state = 1;
        break;
    case 1:
        switch (lbl_2_bss_B2C0->_3B) {
        case 1:
            break;
        case 2:
            lbl_2_bss_B2C0->_3B = 0;
            lbl_2_bss_340234.state = 2;
            break;
        case 3:
            lbl_2_bss_B2C0->_3B = 0;
            lbl_2_bss_340234.state = 3;
            break;
        }
        break;
    case 2:
        fn_2_8EDC4();
        break;
    case 3:
        fn_2_8ED4C();
        changeScene(4, 6);
        fn_2_11A0(4);
        break;
    }
}
// .text:0x0008EDC4 size:0x104
void fn_2_8EDC4(void) {
    s16 result;

    switch (lbl_2_bss_340234.subState) {
    case 0:
        if (lbl_803C50E8._00[0] == 0) {
            lbl_80366158._1F = 1;
            fn_8003F23C();
            lbl_2_bss_340234.subState++;
            break;
        }
        // fallthrough
    case 1:
        if (lbl_803C50E8._00[0] == 0) {
            result = lbl_803CC1B8->_10;
            if (result == 1 || result == 11) {
                if (result != 1) {
                    fn_80021228(OSGetSoundMode());
                }
                lbl_803C50E8._00[0] = 1;
                lbl_2_bss_340234.subState++;
            }
            break;
        }
        // fallthrough
    case 2:
        lbl_2_bss_340234.subState = 0;
        lbl_2_bss_340234.state = 0;
        fn_2_11A0(5);
        break;
    }
}
// .text:0x0008ED4C size:0x78
void fn_2_8ED4C(void) {
    g_d_GameSettings._10 = 2;
    g_d_GameSettings.home_AwaySetting = 0;
    fn_2_2FC0(9, 0, 1);
    fn_8004A0FC();
    lbl_803C5F04.option[3] = 0;
    fn_8004A0FC();
    lbl_800E8754.innings = 3;
    g_d_GameSettings.GameModeSelected = 4;
}
