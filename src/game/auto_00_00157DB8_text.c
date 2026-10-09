#include "game/auto_00_00157DB8_text.h"
#include "game/rep_1200.h"
#include "game/auto_00_0005985C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern s16 lbl_3_data_FC1C;
extern u8 lbl_3_data_BD90[];
extern u8 lbl_3_data_BD50[];
extern u8 lbl_3_data_B3F4[];
extern u8 lbl_800EF808[];
extern void fn_80034E20(void*, void*);
extern void* fn_80033A24(void*, int, int, int, int, int);
extern void fn_3_6B870(void);
extern u8* lbl_803CC1B8;
extern u32 fn_3_157AC4(u8* o);
extern void fn_3_158FE4(void);
extern void fn_3_15810C(void);
extern void fn_3_157E28(void);
extern void fn_3_159114(void);
typedef struct {
    u8* p;
    s32 pad;
} QEnt;
extern void fn_3_158B64(void);
extern void fn_3_1586B0(void);
extern void fn_3_9669C(void);
extern u8 lbl_3_data_FAF4[];
extern u8 lbl_3_data_B85C[];
extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_3_common_bss_34C90[];
extern u8 lbl_80371C30[];
extern void fn_3_8A350(void);
extern void fn_3_F7B8(void);
extern void fn_3_59338(void);

// fn_3_157DB8, size:0x70
void fn_3_157DB8(s32 arg0) {
    u8* p = fn_80033A24(fn_3_157AC4, 0x80, 0, 1, 1, 0x16);
    if (p != NULL) {
        *(s32*)(p + 0x18) = 0;
        *(s32*)(p + 0x1C) = arg0;
        (*(u8**)(p + 0xC))[0x4D] = 0;
        *(s32*)(*(u8**)(p + 0xC) + 0x40) = -1;
    }
}

