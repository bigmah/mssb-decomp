#ifndef __AUTO_00_000194BC_TEXT_MENUS_H__
#define __AUTO_00_000194BC_TEXT_MENUS_H__

#include "mssbTypes.h"

// Options menu state (lbl_2_bss_1033C): rumble / sound mode / third option.
typedef struct OptionsMenu {
    /*0x00*/ u16 state;
    /*0x02*/ s16 cursor;     // row 0..2
    /*0x04*/ s16 prevCursor;
    /*0x06*/ s8 rumble;      // mirrors lbl_800EF808[0x398]
    /*0x07*/ s8 sound;       // mirrors lbl_800EF808[0x396] (0..2)
    /*0x08*/ s8 option2;     // mirrors lbl_80366158._1F
    /*0x09*/ s8 prevSound;
    /*0x0A*/ s8 _0A;
    /*0x0B*/ u8 editing;     // a row is selected for editing
    /*0x0C*/ u8 _0C;
    /*0x0D*/ u8 _0D;
    /*0x0E*/ u8 _0E;
    /*0x0F*/ u8 _0F;
} OptionsMenu;

void fn_2_194BC(u8* object);
void fn_2_194E8(void);
void fn_2_19520(void);
s8 fn_2_19554(void);
void fn_2_195D8(void);
void fn_2_195DC(void);
void fn_2_19778(void);
void fn_2_197AC(u8 port);
void fn_2_19D04(void);

#endif
