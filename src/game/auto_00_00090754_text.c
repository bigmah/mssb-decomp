#include "game/auto_00_00090754_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern s32 fn_800698F8(void);
extern u32 lbl_800EF808[];
extern u8* lbl_803CC1B8;
extern u8 lbl_3_data_81D4[];
extern void fn_800216F8(u8, void*);
extern void fn_8006285C(void);

// fn_3_90754, size:0x10
void fn_3_90754(u8* p, s8 a, s8 b) {
    p[0x11820] = a;
    p[0x11821] = b;
}

// fn_3_90764, size:0x34
s32 fn_3_90764(void) {
    fn_80021518(0x33, lbl_800EF808[0xBC / 4]);
    return 0;
}

