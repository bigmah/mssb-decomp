#ifndef __GAME_rep_16B8_H_
#define __GAME_rep_16B8_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_8000F150.h" // LayoutSlot lbl_80371C30


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

// g_Fielders entry (0x268 bytes); only the fields used here.
typedef struct RepFielderView {
    /*0x000*/ f32 x;
    /*0x004*/ f32 _004;
    /*0x008*/ f32 z;
    /*0x00C*/ f32 _00C;
    /*0x010*/ u8 _010[0x268 - 0x10];
} RepFielderView; // size: 0x268


// Sprite descriptor handed to fn_80034E20 (same layout as SpaniDesc).
typedef struct RepSpriteDesc {
    /*0x00*/ u16 type;
    /*0x02*/ s16 animId;
    /*0x04*/ f32 x;
    /*0x08*/ f32 y;
    /*0x0C*/ s32 unkC;
    /*0x10*/ u8 playMode;
    /*0x11*/ u8 layer;
    /*0x12*/ u8 unk12[2];
    /*0x14*/ u8 texId;
    /*0x15*/ u8 unk15[3];
    /*0x18*/ f32 scale;
    /*0x1C*/ u8 is3D;
    /*0x1D*/ u8 unk1D;
    /*0x1E*/ s16 unk1E;
} RepSpriteDesc; // size: 0x20

// Line-score sprite data (lbl_3_data_EC1C, 0x5E4 bytes).
typedef struct RepLineScoreData {
    /*0x000*/ RepSpriteDesc scoreDescs[18]; // fn_3_93544
    /*0x240*/ RepSpriteDesc lineDescs[29];  // fn_3_91FC4; [0]/[1] animIds depend on the inning count
    /*0x5E0*/ u16 blankDigitAnim;
    /*0x5E2*/ u16 _5E2;
} RepLineScoreData; // size: 0x5E4

// Event-banner data (lbl_3_data_BE50, 0x11C bytes).
typedef struct RepBannerData {
    /*0x00*/ s16 kinds[25][4];    // per banner kind: animId, frame that ends the intro, hold frames, minigame y
    /*0xC8*/ u16 runsAnim[10];    // [runs scored - 1]; [4..8] walk-off / tying / go-ahead variants
    /*0xDC*/ RepSpriteDesc desc[2];
} RepBannerData; // size: 0x11C


// g_RunningLogic (0x20 bytes); only the fields used here.
typedef struct RepRunningLogic {
    /*0x00*/ u8 _00[0x12];
    /*0x12*/ u8 runsScored;
    /*0x13*/ u8 _13[0x20 - 0x13];
} RepRunningLogic;


// Crowd sound settings: lbl_3_data_8404[stadium * 15 + sound], lbl_3_data_84B8[sound] for GameModeSelected 6.
typedef struct RepSoundParams {
    /*0x0*/ u8 vol;
    /*0x1*/ u8 ctrl;
} RepSoundParams;



// Score-tally task (fn_3_93544 / fn_3_933CC / fn_3_92CD8): counts each team's shown score up to its target.
typedef struct RepScoreTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 _04[0x14 - 0x4];
    /*0x14*/ u16 baseIdx; // first slot in lbl_80371C30
    /*0x16*/ u16 _16;
    /*0x18*/ u16 timer;
    /*0x1A*/ u16 _1A;
    /*0x1C*/ u16 score[2][2]; // [0][team]: score shown, [1][team]: target score
} RepScoreTask;

// Field-HUD task (fn_3_9669C / fn_3_959BC); only the fields used here.
typedef struct RepFieldHudTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 _04[0x14 - 0x4];
    /*0x14*/ u16 baseIdx; // first slot in lbl_80371C30
    /*0x16*/ u16 _16;
    /*0x18*/ u16 timer;
    /*0x1A*/ u16 blinkTimer; // minigame: frames since a panel was hit (0 = idle)
    /*0x1C*/ u16 progress[4]; // minigame: per player, shown panel count (+10 once complete, 14 = done)
} RepFieldHudTask;

// View of lbl_3_common_bss_34C90 (pause state), only the fields used here.
typedef struct RepPauseView {
    /*0x000*/ u8 _000[0xC];
    /*0x00C*/ s16 _00C;
    /*0x00E*/ u8 _00E[0x1D5 - 0xE];
    /*0x1D5*/ u8 _1D5;
} RepPauseView;

// 5-byte entries at lbl_3_common_bss_37400 + 0x12 (9 of them), read by fn_3_94BC4.
typedef struct RepGaugeEntry {
    /*0x0*/ s8 full;
    /*0x1*/ s8 total;
    /*0x2*/ s8 partial;
    /*0x3*/ s8 active;
    /*0x4*/ s8 value;
} RepGaugeEntry;

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
void fn_3_92CD8(RepScoreTask* task);
void fn_3_933CC(void);
void fn_3_93544(void);
void fn_3_93688(RepTask* task);
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
