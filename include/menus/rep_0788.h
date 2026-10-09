#ifndef __MENUS_REP_0788_H__
#define __MENUS_REP_0788_H__

#include "mssbTypes.h"

typedef struct {
    u8 padding[0x1976A0];
    s32 selection;
    u8 padding1976A4[0x1BF];
    s8 port;
} MenuInputContext;

void fn_2_24724(void);

void fn_2_20258(void);

void fn_2_1FF10(void);

void fn_2_1FF0C(void);

void fn_2_24EB0(s16 value);

s16 fn_2_24E9C(void);

s16 fn_2_201E4(s16 row, s16 column);

void fn_2_20218(void);

void fn_2_272BC(u8* menu, u8* item);

void fn_2_25D6C(u8* menu, u8* item);

void fn_2_25A1C(u8* menu, u8* item);

void fn_2_25850(u8* menu, u8* item);

void fn_2_246E0(void);

void fn_2_2469C(void);

void fn_2_2460C(void);

void fn_2_245C8(void);

void fn_2_24650(void);

void fn_2_1FFC4(s32 count);

#endif
