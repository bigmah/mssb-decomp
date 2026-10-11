#ifndef __GAME_AUTO_00_000E1964_TEXT_H_
#define __GAME_AUTO_00_000E1964_TEXT_H_

#include "mssbTypes.h"

// lbl_3_data_18ED0: stadium object placement table (stride 0x1C).
typedef struct StadObjPlace {
    /*0x00*/ f32 pos[4];
    /*0x10*/ u8 kind; // 2 terminates the list
    /*0x11*/ u8 _11[3];
    /*0x14*/ f32 _14[2];
} StadObjPlace; // size: 0x1C

void fn_3_E1964(void);
void fn_3_E19E8(void);
void fn_3_E1C60(void);
void fn_3_E1D00(void);

#endif
