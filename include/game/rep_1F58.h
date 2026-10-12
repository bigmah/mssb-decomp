#ifndef __GAME_rep_1F58_H_
#define __GAME_rep_1F58_H_

#include "mssbTypes.h"

// Character aura slot (lbl_3_data_17260, two slots); id -1: free.
typedef struct E32_1F58 {
    /*0x00*/ s16 id;
    /*0x02*/ s16 s2; // frames until the next particle burst
    /*0x04*/ f32 v[3];
    /*0x10*/ f32 p[3];
    /*0x1C*/ f32 x;
} E32_1F58;
extern E32_1F58 lbl_3_data_17260[2];

void fn_3_C0854(void);
void fn_3_C095C(u8* a);
void fn_3_C0AD8(void);
void fn_3_C0C4C(s32 idx);
void fn_3_C0CE8(u8 v, f32 x, f32 y, f32 z);
void fn_3_C0D10(s32 i, u8 v1, u8 v2, u8 v3, u8 v4);
void fn_3_C0DD8(s32 unused, s32* stage, s32* coord, s32* map, u8* c1, u8* c2);
void fn_3_C0F8C(void);
void fn_3_C1004(void);
void fn_3_C11CC(s32 who, s32 a);
void fn_3_C1344(s32 who, s32 track, f32 t, f32 t2);
void fn_3_C1770(s32 who);

s32 fn_3_C1930(s32 id);

#endif // !__GAME_rep_1F58_H_
