#ifndef __GAME_rep_3310_H_
#define __GAME_rep_3310_H_

#include "mssbTypes.h"
#include "main/file_800BD8C4.h" // ActorObjectTable

// One minigame sprite/model slot in lbl_8036E548.sprites (CharTrail in main/file_80011640.h).
typedef struct Rep3310Sprite {
    /*0x00*/ void (*draw)(s32 index);
    /*0x04*/ f32 pos[3];
    /*0x10*/ f32 rot[3];
    /*0x1C*/ u8 _1C[0x26 - 0x1C];
    /*0x26*/ u8 visible;
    /*0x27*/ u8 _27;
} Rep3310Sprite; // size: 0x28

// Relocated model data for one object kind (lbl_8036E548 + 0x2DA0).
typedef struct Rep3310ObjData {
    /*0x0*/ struct ActorLayout* layout;
    /*0x4*/ void* geometry;
    /*0x8*/ void* textures;
} Rep3310ObjData; // size: 0xC

// lbl_3_data_2265C: per-state ball texture records, then the ball scales.
typedef struct Rep3310BallCfg {
    /*0x00*/ u8 tex[4];
    /*0x04*/ f32 scale;
    /*0x08*/ f32 shadowScale;
    /*0x0C*/ f32 minScale; // squash target while bouncing (state 2)
    /*0x10*/ s32 squashFrames;
} Rep3310BallCfg;

// One bonus item in g_Minigame + 0x72C (7 entries).
typedef struct Rep3310Item {
    /*0x00*/ f32 pos[3];
    /*0x0C*/ u8 _0C[0x18 - 0xC];
    /*0x18*/ f32 spin;
    /*0x1C*/ u8 _1C[0x24 - 0x1C];
    /*0x24*/ s16 timer;
    /*0x26*/ u8 _26[2];
    /*0x28*/ u8 state; // 0: none, 4: picked up, 5: pickup animation playing
    /*0x29*/ u8 kind;
    /*0x2A*/ u8 _2A[2];
} Rep3310Item; // size: 0x2C

// View of g_Ball (InMemBallType in game/UnknownHomes_Game.h), only the fields used here.
typedef struct Rep3310BallView {
    /*0x00*/ Vec contactPos;
} Rep3310BallView;

// View of lbl_8036E548 (CharMgr in main/file_80011640.h), only the fields used here.
typedef struct Rep3310CharMgr {
    /*0x0000*/ u8 _0000[0x68];
    /*0x0068*/ ActorObjectTable* objs;
    /*0x006C*/ u8 _006C[0xAC - 0x6C];
    /*0x00AC*/ void* lights[4];
    /*0x00BC*/ u8 _00BC[0x2D94 - 0xBC];
    /*0x2D94*/ Rep3310Sprite* sprites;
    /*0x2D98*/ u8 _2D98[0x2DA0 - 0x2D98];
    /*0x2DA0*/ Rep3310ObjData data[27];
    /*0x2EE4*/ u8 _2EE4[0x3078 - 0x2EE4];
    /*0x3078*/ u16 count; // sprites / objs entries
    /*0x307A*/ u8 _307A[0x307E - 0x307A];
    /*0x307E*/ u8 _307E;
} Rep3310CharMgr;

void fn_3_116840(void);
void fn_3_1169D0(void);
void fn_3_116B38(void);
void fn_3_116B74(void);
void fn_3_11741C(s32 i);
void fn_3_117494(void);
void fn_3_117588(s32 idx);
void fn_3_1179EC(void);
void fn_3_117AE4(void);
void fn_3_117B78(s32 idx);
void fn_3_117FC8(void);
void fn_3_1180A4(void);
void fn_3_118164(void);
void fn_3_118358(s32 i, f32* v);
void fn_3_1183FC(void);
void fn_3_118508(void);
void fn_3_118614(void);
void fn_3_11874C(void);
void fn_3_11881C(s32 i);
void fn_3_11887C(void);
void fn_3_11897C(s32 i);
void fn_3_1189C8(s32 i, s32 a, s32 b, s32 d, u8 flag);
void fn_3_118B18(void);
void fn_3_1192B8(void);
void fn_3_119468(s32 i);
void fn_3_1194AC(s32 i);
void fn_3_1194FC(void);
f32 fn_3_119854(u8 i);
void fn_3_119878(void);
void fn_3_119934(void);
void fn_3_119C34(void);
void fn_3_119CA8(s32 i);
f32 fn_3_119D28(void);
void fn_3_119D34(void);
void fn_3_119E30(s32 i);
void fn_3_119EE0(s32 i);
void fn_3_119F6C(void);
void fn_3_11A20C(void);
void fn_3_11A210(void);
u32 fn_3_11A350(int i);
void fn_3_11A38C(s32 i, s16 h);
void fn_3_11A408(void);
void fn_3_11A92C(u8* q, s32 n);
void fn_3_11AB2C(void);
void fn_3_11AC6C(void);
void fn_3_11B75C(void);
void fn_3_11BBA4(void);
void fn_3_11C02C(void);
void fn_3_11C2CC(void);
void fn_3_11C5F8(void);
void fn_3_11CD00(void);
void fn_3_11CF04(void);
void fn_3_11CF84(void);
void fn_3_11D1B0(void);
void fn_3_11D2C8(s32 idx, s32 start, s32 count, void* animBank, struct sHdr* skHeader);

#endif // !__GAME_rep_3310_H_
