#ifndef __AUTO_00_0004B1AC_TEXT_MENUS_H__
#define __AUTO_00_0004B1AC_TEXT_MENUS_H__

#include "mssbTypes.h"

struct MenuTask;
#include "menus/menu_asset.h" // InitEntry


void fn_2_4C314(void);

void fn_2_4C9C4(void);

void fn_2_4D194(void);

void fn_2_4C36C(void);

void fn_2_54B38(void);

void fn_2_53F88(void* context); // the running task, passed to each draw entry

void fn_2_53F04(void* context);

s16 fn_2_4C3C4(s32 index);

s32 fn_2_4C3D8(s32 index);

void fn_2_4E898(void);

void fn_2_4E8BC(void);

void fn_2_4E8E0(void);

void fn_2_4E904(void);

void fn_2_4E928(void);

void fn_2_4E94C(void);

s32 fn_2_4E970(void);

s32 fn_2_4EABC(void);

s32 fn_2_4EAF4(void);

s32 fn_2_4EB2C(void);

s32 fn_2_4EB64(void);

void fn_2_4E858(void* object); // fn_80034CEC wrapper

s32 fn_2_512B8(void);

void* fn_2_519F0(void);

void fn_2_54874(void);

void fn_2_54848(void);

void fn_2_4E7EC(void);

void fn_2_4E824(void);

void fn_2_54BAC(void);

void fn_2_54844(void);

void fn_2_5268C(void);

void fn_2_51568(void);

void fn_2_5146C(void);

void fn_2_513E4(void);

void fn_2_513E0(void* buffer, s32 x, s32 y, s32 option, s32 style, s32 first, s32 second, s32 third); // empty

void fn_2_513DC(void);

void fn_2_51358(void);

void fn_2_512B4(void);

void fn_2_5118C(void);

void fn_2_4E878(void* object, void* data);

void fn_2_52648(s32 priority);

void fn_2_4E7A4(void);

void fn_2_515DC(u8 mode);

u16* fn_2_5156C(s32 index, u16 font);

void fn_2_50E5C(s32 channel);

void fn_2_50CC0(s16 value);

void fn_2_52198(void);

void fn_2_50BF4(s16 id);

void fn_2_510A8(void);

s32 fn_2_4E9A8(void);

void fn_2_54890(void);

void fn_2_5400C(void);

void fn_2_51190(s32 a, s32 b);

void fn_2_50898(s32 a);

void fn_2_54120(void);

void fn_2_54234(InitEntry* entries, s32 count);

void fn_2_54354(InitEntry* entries, s32 count);

void fn_2_53CEC(struct MenuTask* menu);

void fn_2_53DF8(struct MenuTask* menu);

void fn_2_4B1AC(void);

void fn_2_520A4(void);

void fn_2_51890(void);

void fn_2_512C0(s32 index);

s32 fn_2_513E8(u16* str, u16 font);

s32 fn_2_51470(s32 index, u16 font);

void fn_2_4D378(void);

void fn_2_4D67C(void);

void fn_2_4D960(void);

void fn_2_4DC24(void);

void fn_2_4DEE8(void);

void fn_2_4E1C0(void);

void fn_2_535B0(void);

void fn_2_54474(void);

void fn_2_52260(void);

void fn_2_51C58(void);

void fn_2_52690(void);

void fn_2_4B2D0(void);

s16 fn_2_4EB9C(void);
void fn_2_53408(void);

#endif
