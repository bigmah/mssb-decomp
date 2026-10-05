#include "game/rep_0.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_1E08.h"


extern void fn_800BF038(int);
extern void fn_3_C0824(void);
extern void fn_3_5AE9C(void);
extern void fn_80036C88(void*, void*);
extern void fn_800B0D28(void*);
extern void fn_8004B270(void);
extern u8 lbl_3_data_118[];

// .text:0x00000464 size:0x38
void _epilog(void) {
    g_d_GameSettings._55 = 0;
    fn_800BF038(0);
    fn_3_BF20C();
}

// .text:0x0000049C size:0x58
void _prolog(void) {
    u8* p;
    fn_800B0A5C_insertQueue(fn_3_5AE9C, 1);
    fn_3_C0824();
    p = lbl_3_data_118 + 0x5C;
    fn_80036C88(lbl_3_data_118, p);
    fn_800B0D28(p);
    fn_8004B270();
}
