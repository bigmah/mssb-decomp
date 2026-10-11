#ifndef __GAME_rep_1C0_H_
#define __GAME_rep_1C0_H_

#include "mssbTypes.h"
#include "Dolphin/GX/GXTypes.h"

// Per-frame stadium draw callback: (view matrix, translucent pass, layer).
typedef void (*StadiumDrawFn)(float (*view)[4], s32 translucent, u32 layer);

u32 setFanObjPtr(void);
void fn_3_35E4(u32 val);
void fn_3_35F0(void);
void fn_3_3638(u8* obj);
void fn_3_3818(void);
void fn_3_38E8(StadiumDrawFn a);
void fn_3_3904(s16 x, s16 y, s32 msg, GXColor color0, GXColor color1, u8 flags);
void fn_3_3BE8(void);
void fn_3_3EE8(void);
void fn_3_42CC(struct _GXTexObj* tex, s16 x0, s16 y0, s16 x1, s16 y1, s16 sx, s16 sy, s16 sw, s16 sh,
               GXColor color0, GXColor color1, u8 flags);
void fn_3_4984(void);
void fn_3_4A38(u8 a);
void fn_3_4F90(struct _GXTexObj* tex, s16 x, s16 y, s16 value, u8 width, GXColor color0, GXColor color1, u8 boxed);
void fn_3_53E0(u16* in, s16* a, s16* b, s16* c, s16* d, s16* e);
void fn_3_5518(void);
void fn_3_567C(void);
void fn_3_5BAC(void);
void fn_3_5BCC(u8* p);
void fn_3_5BF0(void);
void fn_3_5C68(u8* obj);
void fn_3_5E60(void);
void fn_3_64DC(void);
s16 fn_3_6424(u8* base, u8** out);

#endif // !__GAME_rep_1C0_H_
