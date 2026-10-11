#ifndef __GAME_rep_16B8_H_
#define __GAME_rep_16B8_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_8000F150.h" // LayoutSlot lbl_80371C30

extern GameScores g_Scores;

// Sprite-layout task (lbl_803CC1B8[0] while one of this unit's tasks runs); only the fields used here.
typedef struct RepTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 _04[0x14 - 0x4];
    /*0x14*/ u16 baseIdx; // first slot in lbl_80371C30
    /*0x16*/ u16 _16;
    /*0x18*/ u16 timer;
    /*0x1A*/ u16 _1A;
    /*0x1C*/ u16 _1C;
    /*0x1E*/ u16 _1E;
    /*0x20*/ u16 _20;
    /*0x22*/ u16 _22;
} RepTask;

#define REP_OBJ(task, i) (lbl_80371C30[(task)->baseIdx + (i)].obj)

void fn_3_91520(void);
void fn_3_91A60(void);
void fn_3_91AC8(void);
void fn_3_91B50(void);
void fn_3_91B9C(void);
void fn_3_91C70(void);
void fn_3_91CCC(void);
void fn_3_91D1C(void);
void fn_3_91E4C(void);
void fn_3_91FC4(void);
void fn_3_92CD8(void);
void fn_3_933CC(void);
void fn_3_93544(void);
void fn_3_93688(void);
void fn_3_93960(void);
void fn_3_93D5C(void);
void fn_3_9413C(void);
void fn_3_94194(void);
void fn_3_94708(void);
void fn_3_94760(void);
void fn_3_948B8(void);
void fn_3_94930(void);
void fn_3_9497C(void);
void fn_3_94BC4(void);
void fn_3_94E68(void);
void fn_3_95000(void);
void fn_3_95098(void);
void fn_3_95124(void);
void fn_3_951B4(void);
void fn_3_952DC(void);
void fn_3_9538C(void);
void fn_3_953FC(void);
void fn_3_954C4(void);
void fn_3_9551C(void);
void fn_3_95568(void);
void fn_3_955CC(void);
void fn_3_95620(void);
void fn_3_95970(void);
void fn_3_959BC(void);
void fn_3_9669C(void);
void fn_3_96914(void);
void fn_3_9698C(void);
void fn_3_96CA4(void);

#endif // !__GAME_rep_16B8_H_
