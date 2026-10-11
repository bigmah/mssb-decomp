#include "game/auto_00_000E1964_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "static/GameSettings.h"
#include "main/file_800BD8C4.h"
#include "main/file_80039AC0.h"
#include "Dolphin/gx.h"
#include "game/rep_1838.h"
#include "game/rep_1D58.h"
#include "game/rep_2940.h"
#include "game/rep_3310.h"
#include "game/rep_EA0.h"
#include "game/rep_F80.h"
#include "game/auto_00_0006A160_text.h"
#include "game/auto_00_0006B4C8_text.h"
#include "game/auto_00_000DEB90_text.h"
#include "game/auto_00_000EA340_text.h"

// View of lbl_8036E548 (CharMgr in main/file_80011640.h; that header can't be
// included next to the game headers).
typedef struct GameCharActor {
    /*0x000*/ u8 _000[0x25D];
    /*0x25D*/ u8 mode[2];
} GameCharActor;

typedef struct GameCharTrail {
    /*0x00*/ void (*draw)(void);
    /*0x04*/ Vec pos;
    /*0x10*/ f32 _10;
    /*0x14*/ f32 angle;
    /*0x18*/ f32 _18;
    /*0x1C*/ u8 _1C[0xA];
    /*0x26*/ u8 visible;
    /*0x27*/ u8 _27;
} GameCharTrail; // size: 0x28

typedef struct GameCharMgr {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ GameCharActor* active[13];
    /*0x2C84*/ u8 _2C84[0x2D94 - 0x2C84];
    /*0x2D94*/ GameCharTrail* trail2; // [30]
    /*0x2D98*/ u8 _2D98[0x307A - 0x2D98];
    /*0x307A*/ u8 _307A;
    /*0x307B*/ u8 _307B[0x3087 - 0x307B];
    /*0x3087*/ u8 _3087;
} GameCharMgr;

extern GameCharMgr lbl_8036E548;
extern void fn_8001D0D0(s32 index, f32 scale);
extern int rand(void);
typedef void (*ShadowDrawCallback)(ActorObject* obj, Mtx view);
extern void fn_800BDF70(ActorObject* obj);
extern void fn_800BF058(ShadowDrawCallback callback);
extern void fn_3_12D1F4(void);

extern f32 lbl_3_data_18D98[14];
extern f32 lbl_3_data_18DD0;
extern s16 lbl_3_data_18BB0[2][2];
extern StadObjPlace lbl_3_data_18ED0[11];

// lbl_3_common_bss_350E4: stadium object list.
typedef struct StadObjE8 {
    /*0x00*/ u8 _00[0x74];
    /*0x74*/ ActorObject* actor;
    /*0x78*/ u8 _78[0x93 - 0x78];
    /*0x93*/ u8 flags93;
    /*0x94*/ u8 _94[0xE8 - 0x94];
} StadObjE8; // size: 0xE8

typedef struct StadObjListE8 {
    /*0x00*/ StadObjE8* objs;
    /*0x04*/ u8 _04[0x2C];
    /*0x30*/ s32 count;
} StadObjListE8;

extern StadObjListE8 lbl_3_common_bss_350E4;

// .text:0x000E1964 size:0x84 mapped:0x807209F8
// NONMATCHING 89%: trail offset induction is li'd instead of copied from i (mr r27,r29); regalloc
#if NONMATCHING
void fn_3_E1964(void) {
    GameCharTrail* trail;
    s32 i;

    for (i = 0; i < 30; i++) {
        trail = &lbl_8036E548.trail2[i];
        fn_8001D0D0(i, lbl_3_data_18D98[0]);
        trail->angle = shortAngleToRad_Capped(rand() % 4096);
    }
}
#endif

// .text:0x000E19E8 size:0x278 mapped:0x80720A7C
void fn_3_E19E8(void) {
    return;
}

// .text:0x000E1C60 size:0xA0 mapped:0x80720CF4
void fn_3_E1C60(void) {
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_A2, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}

// .text:0x000E1D00 size:0xB8 mapped:0x80720D94
void fn_3_E1D00(void) {
    StadObjE8* obj;
    s32 i;

    fn_800BF058((ShadowDrawCallback)fn_3_B8184);
    fn_8003A548((u32)fn_3_E1C60); // TODO type: callback stored as u32
    for (i = 0; i < lbl_3_common_bss_350E4.count; i++) {
        if (lbl_3_data_18ED0[i].kind == 2) {
            break;
        }
        obj = &lbl_3_common_bss_350E4.objs[i];
        fn_3_B828C((u32)obj); // TODO type
        if (obj->actor != NULL) {
            obj->actor->actor->flags98 = obj->flags93 | 6;
            fn_800BDF70(obj->actor);
        }
    }
    fn_8003A548(0);
}
