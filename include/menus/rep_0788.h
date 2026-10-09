#ifndef __MENUS_REP_0788_H__
#define __MENUS_REP_0788_H__

#include "mssbTypes.h"

typedef struct {
    u8 padding[0x1976A0];
    s32 selection;
    s32 secondarySelection;
    u8 padding1976A8[0xFA];
    s16 frameSetA[5];
    u8 padding1977AC[0x62];
    s16 frameSetB[5];
    s16 frameSetC[5];
    u8 padding197822[0x41];
    s8 port;
} MenuInputContext;

typedef struct {
    u8 padding[0x18];
    u16 timerA;
    u16 timerB;
    u16 stateA;
    u16 stateB;
} MenuQueueState;

typedef struct {
    u8 padding[0x14];
    u16 firstIndex;
} MenuTableContext;

typedef struct {
    u8 padding[4];
    s16 state;
    s16 timer;
    u8 padding08[2];
    s16 index;
    u8 padding0C[2];
    s16 offset;
} MenuItemState;

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

void fn_2_1FF14(s32 count);

void fn_2_242FC(void);

void fn_2_24238(void);

void fn_2_243BC(void);

void fn_2_2416C(void);

void fn_2_2025C(void);

void fn_2_32C64(MenuTableContext* menu, MenuItemState* item);

void fn_2_327D4(MenuTableContext* menu, MenuItemState* item);

void fn_2_26774(MenuTableContext* menu, MenuItemState* item);

void fn_2_26684(MenuTableContext* menu, MenuItemState* item);

s32 fn_2_24728(s32 character);

void fn_2_33614(MenuTableContext* menu, MenuItemState* item);

void fn_2_25D98(MenuTableContext* menu, MenuItemState* item);

void fn_2_2E17C(MenuTableContext* menu, MenuItemState* item);

void fn_2_2A21C(MenuTableContext* menu, MenuItemState* item);

void fn_2_2D508(MenuTableContext* menu, MenuItemState* item);

void fn_2_24488(void);

void fn_2_322E4(MenuTableContext* menu, MenuItemState* item);

void fn_2_31A90(MenuTableContext* menu, MenuItemState* item);

void fn_2_27D8C(MenuTableContext* menu, MenuItemState* item);

void fn_2_2DE78(MenuTableContext* menu, MenuItemState* item);

void fn_2_29F18(MenuTableContext* menu, MenuItemState* item);

void fn_2_2C378(MenuTableContext* menu, MenuItemState* item);

void fn_2_2835C(MenuTableContext* menu, MenuItemState* item);

void fn_2_26170(MenuTableContext* menu, MenuItemState* item);

void fn_2_26010(MenuTableContext* menu, MenuItemState* item);

void fn_2_25EB0(MenuTableContext* menu, MenuItemState* item);

void fn_2_28224(MenuTableContext* menu, MenuItemState* item);

void fn_2_26F80(MenuTableContext* menu, MenuItemState* item);

void fn_2_253B0(MenuTableContext* menu, MenuItemState* item);

void fn_2_2E44C(MenuTableContext* menu, MenuItemState* item);

void fn_2_31F50(MenuTableContext* menu, MenuItemState* item);

void fn_2_316F8(MenuTableContext* menu, MenuItemState* item);

void fn_2_279F4(MenuTableContext* menu, MenuItemState* item);

void fn_2_28D24(MenuTableContext* menu, MenuItemState* item);

void fn_2_2BDA4(MenuTableContext* menu, MenuItemState* item);

void fn_2_2AEDC(MenuTableContext* menu, MenuItemState* item);

void fn_2_24EC4(MenuTableContext* menu, MenuItemState* item);

void fn_2_28090(MenuTableContext* menu, MenuItemState* item);

#endif
