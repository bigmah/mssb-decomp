#ifndef __MENUS_REP_0788_H__
#define __MENUS_REP_0788_H__

#include "mssbTypes.h"
#include "menus/menu_work.h"

// Menu screen tasks are MenuTask (menus/menu_work.h): baseIdx is the first
// sprite in lbl_80371C30, timerA..stateB drive the queued screens.
typedef MenuTask MenuTableContext;
typedef MenuTask MenuQueueState;


void fn_2_24724(void);

void fn_2_20258(void);

void fn_2_1FF10(s32 index);

void fn_2_1FF0C(s32 index);

void fn_2_24EB0(s16 value);

s16 fn_2_24E9C(void);

s16 fn_2_201E4(s16 row, s16 column);

void fn_2_20218(void);

void fn_2_272BC(MenuTableContext* menu, MenuItemState* item);

void fn_2_25D6C(MenuTableContext* menu, MenuItemState* item);

void fn_2_25A1C(MenuTableContext* menu, MenuItemState* item);

void fn_2_25850(MenuTableContext* menu, MenuItemState* item);

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

void fn_2_2B064(MenuTableContext* menu, MenuItemState* item);

void fn_2_2B250(MenuTableContext* menu, MenuItemState* item);

void fn_2_2CF58(MenuTableContext* menu, MenuItemState* item);

void fn_2_272E8(MenuTableContext* menu, MenuItemState* item);

void fn_2_2AD30(MenuTableContext* menu, MenuItemState* item);

void fn_2_2749C(MenuTableContext* menu, MenuItemState* item);

void fn_2_27660(MenuTableContext* menu, MenuItemState* item);

void fn_2_32A78(MenuTableContext* menu, MenuItemState* item);

void fn_2_325E8(MenuTableContext* menu, MenuItemState* item);

void fn_2_27B7C(MenuTableContext* menu, MenuItemState* item);

void fn_2_31880(MenuTableContext* menu, MenuItemState* item);

void fn_2_31D94(MenuTableContext* menu, MenuItemState* item);

void fn_2_31538(MenuTableContext* menu, MenuItemState* item);

void fn_2_27824(MenuTableContext* menu, MenuItemState* item);

void fn_2_320D8(MenuTableContext* menu, MenuItemState* item);

void fn_2_2F8A4(MenuTableContext* menu, MenuItemState* item);

void fn_2_2CBCC(MenuTableContext* menu, MenuItemState* item);

void fn_2_2DCA8(MenuTableContext* menu, MenuItemState* item);

void fn_2_2C1A8(MenuTableContext* menu, MenuItemState* item);

void fn_2_2C698(MenuTableContext* menu, MenuItemState* item);

void fn_2_2C860(MenuTableContext* menu, MenuItemState* item);

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

void fn_2_2CA30(MenuTableContext* menu, MenuItemState* item);

void fn_2_2587C(MenuTableContext* menu, MenuItemState* item);
void fn_2_25050(MenuTableContext* menu, MenuItemState* item);
void fn_2_25200(MenuTableContext* menu, MenuItemState* item);
void fn_2_33720(MenuTableContext* menu, MenuItemState* item);
void fn_2_32D54(MenuTableContext* menu, MenuItemState* item);
void fn_2_328C4(MenuTableContext* menu, MenuItemState* item);
void fn_2_32434(MenuTableContext* menu, MenuItemState* item);
void fn_2_31BE0(MenuTableContext* menu, MenuItemState* item);
void fn_2_31384(MenuTableContext* menu, MenuItemState* item);
void fn_2_3109C(MenuTableContext* menu, MenuItemState* item);
void fn_2_2E298(MenuTableContext* menu, MenuItemState* item);
void fn_2_2DFC8(MenuTableContext* menu, MenuItemState* item);
void fn_2_2CDA4(MenuTableContext* menu, MenuItemState* item);
void fn_2_2C4E4(MenuTableContext* menu, MenuItemState* item);
void fn_2_2A068(MenuTableContext* menu, MenuItemState* item);
void fn_2_28794(MenuTableContext* menu, MenuItemState* item);
void fn_2_27EDC(MenuTableContext* menu, MenuItemState* item);
void fn_2_30C4C(MenuTableContext* menu, MenuItemState* item);
void fn_2_2FBCC(MenuTableContext* menu, MenuItemState* item);
void fn_2_31250(MenuTableContext* menu, MenuItemState* item);
void fn_2_2FA7C(MenuTableContext* menu, MenuItemState* item);
void fn_2_2FD00(MenuTableContext* menu, MenuItemState* item);
void fn_2_30D80(MenuTableContext* menu, MenuItemState* item);
s32 fn_2_20CB0(u32 index);
s32 fn_2_200E4(void);
void fn_2_20D08(void);
void fn_2_1D440(void);
void fn_2_24800(void);
void fn_2_2926C(MenuTableContext* menu, MenuItemState* item);
void fn_2_338D4(MenuTableContext* menu, MenuItemState* item);
void fn_2_207FC(void);
void fn_2_20328(void);
void fn_2_2A338(MenuTableContext* menu, MenuItemState* item);
void fn_2_28EA0(MenuTableContext* menu, MenuItemState* item);
void fn_2_262D0(MenuTableContext* menu, MenuItemState* item);
void fn_2_3039C(MenuTableContext* menu, MenuItemState* item);
void fn_2_25A48(MenuTableContext* menu, MenuItemState* item);
void fn_2_2B884(MenuTableContext* menu, MenuItemState* item);
void fn_2_2BF20(MenuTableContext* menu, MenuItemState* item);
void fn_2_2BB34(MenuTableContext* menu, MenuItemState* item);
void fn_2_2B654(MenuTableContext* menu, MenuItemState* item);
void fn_2_2F544(MenuTableContext* menu, MenuItemState* item);
void fn_2_26AF4(MenuTableContext* menu, MenuItemState* item);

#endif
