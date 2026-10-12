#ifndef __GAME_rep_3520_H_
#define __GAME_rep_3520_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "game/UnknownHomes_Game.h"
#include "static/Camera.h"

struct DODisplayObj;

// This minigame's use of the shared minigame area (g_Minigame, as MiniGameStruct for the
// common fields). Reached through MG3520.
typedef struct Mg3520Ent {
    /*0x00*/ Vec pos;
    /*0x0C*/ u8 _0C[0x22 - 0xC];
    /*0x22*/ s16 _22;
    /*0x24*/ u8 _24[2];
    /*0x26*/ u8 _26; // drawn
    /*0x27*/ u8 _27;
} Mg3520Ent; // size: 0x28

// One obstacle (fn_3_137B10 and its helpers).
typedef struct Mg3520Obj {
    /*0x00*/ Vec pos;
    /*0x0C*/ Vec _0C;
    /*0x18*/ Vec _18;
    /*0x24*/ Vec _24;
    /*0x30*/ f32 _30;
    /*0x34*/ f32 _34;
    /*0x38*/ s16 _38;
    /*0x3A*/ s16 _3A;
    /*0x3C*/ u8 _3C;
    /*0x3D*/ u8 state;
    /*0x3E*/ u8 _3E;
    /*0x3F*/ u8 _3F;
} Mg3520Obj; // size: 0x40

// The bouncing item (fn_3_13688C).
typedef struct Obj136 {
    /*0x00*/ Vec pos;
    /*0x0C*/ Vec vel;
    /*0x18*/ u8 pad[4];
    /*0x1C*/ s16 timer;
    /*0x1E*/ u8 state;
    /*0x1F*/ u8 _1F;
} Obj136; // size: 0x20

// Per-player CPU state, 8 bytes at g_Minigame+0x1DCC (see fn_3_1356F8).
typedef struct CpuSlot3520 {
    /*0x0*/ f32 radius;   // extra keep-out radius around the arena
    /*0x4*/ s16 lastStick; // stick angle last frame (-1: none)
    /*0x6*/ u8 state;     // 0 roam, 1 start dash, 2 dashing, 3 wait for landing
    /*0x7*/ s8 timer;
} CpuSlot3520;
typedef struct CpuState3520 {
    /*0x00*/ CpuSlot3520 slot[4];
    /*0x20*/ f32 rotSin; // sin/cos of the arena rotation (-_1D64)
    /*0x24*/ f32 rotCos;
} CpuState3520;

typedef struct Mg3520 {
    /*0x0000*/ u8 _0000[0xA8];
    /*0x00A8*/ Mg3520Ent ents[40];
    /*0x06E8*/ u8 _06E8[0xBAC - 0x6E8];
    /*0x0BAC*/ u8 _BAC;
    /*0x0BAD*/ u8 _BAD[3];
    /*0x0BB0*/ Mg3520Obj objs[4];
    /*0x0CB0*/ Obj136 item;
    /*0x0CD0*/ Vec coinPos[100];
    /*0x1180*/ Vec coinVel[100];
    /*0x1630*/ u8 _1630[0x17C0 - 0x1630];
    /*0x17C0*/ u32 timer;
    /*0x17C4*/ u32 _17C4;
    /*0x17C8*/ s16 coinTimer[100];
    /*0x1890*/ u8 _1890[0x193A - 0x1890];
    /*0x193A*/ u8 coinState[100];
    /*0x199E*/ u8 _199E[0x1CB8 - 0x199E];
    /*0x1CB8*/ Vec knockVel[4];
    /*0x1CE8*/ struct {
        Vec a;
        Vec b;
    } spokes[4];
    /*0x1D48*/ f32 _1D48;
    /*0x1D4C*/ u8 _1D4C[0x1D5A - 0x1D4C];
    /*0x1D5A*/ s16 stunTimer[4];
    /*0x1D62*/ s16 _1D62;
    /*0x1D64*/ s16 spokeAng[4];
    /*0x1D6C*/ u8 _1D6C[0x1DCC - 0x1D6C];
    /*0x1DCC*/ CpuState3520 cpu;
    /*0x1DF4*/ u8 _1DF4[4];
    /*0x1DF8*/ u8 _1DF8[0x1E2C - 0x1DF8];
} Mg3520; // size: 0x1E2C

// g_Minigame seen both ways.
typedef union Mg3520U {
    MiniGameStruct mg;
    Mg3520 x;
} Mg3520U;

void fn_3_132EDC(struct DODisplayObj* dispObj, s32* stage, s32* coord, s32* map, u8* c1, u8* c2, MtxPtr camera);
void fn_3_1330E4(void);
void fn_3_133200(void);
void fn_3_133320(void);
void fn_3_13334C(void);
int fn_3_1344BC(int a, int b);
s16 fn_3_1345AC(s16 a, s16 b, s32 c);
void fn_3_134658(int a, f32* ox, f32* oz, s32* out);
s32 fn_3_134908(s16* a, s16* b);
s32 fn_3_134918(f32* a, f32* b);
int fn_3_13493C(u32 idx, f32* ox, f32* oz, u32 depth);
int fn_3_134C80(u32 a, u32 b, u32 c, f32 x, f32 y);
u32 fn_3_134D4C(f32 ax, f32 az, f32 r, f32 bx, f32 bz, f32 x, f32 y);
typedef struct CoinCand {
    /*0x00*/ f32 score; // lower is better (squared distance plus penalties)
    /*0x04*/ s32 coin;  // index into the coin pool
    /*0x08*/ f32 x;     // coin position rotated into the field frame
    /*0x0C*/ f32 z;
    /*0x10*/ u8 quad;   // quadrant of (x, z)
    /*0x11*/ u8 valid;
    /*0x12*/ u8 pad[2];
} CoinCand; // size: 0x14
CoinCand* fn_3_1350BC(u32 player, u32 quad, u32 n, CoinCand* cands);
int fn_3_1354BC(int idx, f32 x, f32 y);
u32 fn_3_135520(f32 x, f32 y, f32 r);
void fn_3_135600(f32* outX, f32* outY, f32 x, f32 y);
int fn_3_13564C(f32 x, f32 y);
int fn_3_135698(CoinCand* a, CoinCand* b);
void fn_3_1356F8(void);
void fn_3_1357A4(f32* out, Vec* dir);
void fn_3_13583C(f32* out);
void fn_3_135924(void);
void fn_3_135A64(void);
void fn_3_135C18(void);
void fn_3_135E38(void);
void fn_3_135E98(void);
void fn_3_135F4C(void);
void fn_3_135FF4(void);
void fn_3_136048(void);
void fn_3_1360BC(int p);
void fn_3_136220(void);
struct Obj136;
void fn_3_13688C(Obj136* o);
void fn_3_136CF4(Obj136* o);
void fn_3_136EA4(void);
void fn_3_1370A0(camera_803c639c_s* o);
void fn_3_1371E8(void);
void fn_3_137224(Mg3520Obj* o);
struct _VecSrcDst;
struct _CollisionStruct;
u8 fn_3_1373E0(struct _VecSrcDst* seg, Vec* vel, struct _CollisionStruct* col, f32 r);
u8 fn_3_1379A0(s32 idx);
u8 fn_3_137B10(Mg3520Obj* o);
void fn_3_137CF8(Mg3520Obj* o);
void fn_3_137DE4(Mg3520Obj* o);
void fn_3_137F14(Mg3520Obj* o);
void fn_3_13802C(Mg3520Obj* o);
void fn_3_1382E0(Mg3520Obj* o);
void fn_3_138448(Mg3520Obj* a);
void fn_3_1384B4(Mg3520Obj* o);
void fn_3_138AA4(void);
void fn_3_1391C0(void);
void fn_3_139700(void);
void fn_3_13974C(void);
void fn_3_139808(void);
void fn_3_139CA0(void);
void fn_3_139F84(void);
void fn_3_13A048(int i, int j);
void fn_3_13A0AC(void);
void fn_3_13A724(void);
void fn_3_13A89C(void);
void fn_3_13AA78(void);
void fn_3_13ACB4(struct _CollisionStruct* c);
void fn_3_13ADC0(f32* out, f32* a, f32* b);
void fn_3_13AE1C(void);
void fn_3_13AFE4(void);
void fn_3_13B284(void);
void fn_3_13B9C4(void);
void fn_3_13BB30(void);
void fn_3_13BBF4(void);
void fn_3_13BCB8(void);
void fn_3_13C464(void);
void fn_3_13C468(void);

#endif // !__GAME_rep_3520_H_
