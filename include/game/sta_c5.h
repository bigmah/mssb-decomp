#ifndef __GAME_sta_c5_H_
#define __GAME_sta_c5_H_

#include "mssbTypes.h"

struct StaC5Obj;
struct StadCtlA;
struct StadObjB;
struct StadObjHdr;
struct DODisplayObj;
#include "Dolphin/mtx.h"

void fn_3_EE100(struct DODisplayObj* obj, f32 (*mtx)[4]);
void fn_3_EE388(void);
void fn_3_EE67C(struct DODisplayObj* a, f32 (*m)[4]);
void fn_3_EE96C(u8* pos);
void fn_3_EEB94(void);
void fn_3_EECF4(void);
void fn_3_EEE3C(void);
void fn_3_EEF24(void);
void fn_3_EEFA4(void);
void fn_3_EEFD0(void);
void fn_3_EEFD4(s32 idx);
void fn_3_EF218(void);
void fn_3_EF21C(struct StaC5Obj* p);
void fn_3_EF3D4(struct StaC5Obj* p, u8 idx);
void fn_3_EF408(struct StaC5Obj* p);
#include "Dolphin/vec.h"
u32 fn_3_EF55C(Vec p, u8 idx);
typedef struct { s32 a, b, c; } V3i;
u32 fn_3_EF7B4(V3i v, s32 x);
void fn_3_EF800(struct StaC5Obj* p);
void fn_3_EF890(struct StaC5Obj* p);
void fn_3_EF930(struct StaC5Obj* p);
struct StadCtlA;
void fn_3_EFB54(struct StadCtlA* p);
void fn_3_F0184(void);
struct StadCtlA;
void fn_3_F0224(struct StadCtlA* p);
void fn_3_F082C(struct StadCtlA* p);
void fn_3_F0FA4(struct StadCtlA* p);
void fn_3_F13F8(struct StaC5Obj* p);
void fn_3_F1448(struct StaC5Obj* p);
struct StadCtlA;
void fn_3_F1518(struct StadCtlA* p);
void fn_3_F1674(void);
void fn_3_F1750(struct StadCtlA* p);
void fn_3_F18A4(struct StaC5Obj* p);
void fn_3_F193C(struct StadCtlA* p);
void fn_3_F1E2C(struct StadCtlA* p);
void fn_3_F22FC(struct StaC5Obj* p, s32 idx);
s32 fn_3_F2448(struct StaC5Obj* p);
void fn_3_F2724(struct StaC5Obj* p, struct StaC5Obj* q);
void fn_3_F2938(struct StadCtlA* p);
void fn_3_F2FFC(struct StadCtlA* p, f32 x, f32 z);
void fn_3_F31E0(struct StadCtlA* p, f32 x, f32 z);
u32 fn_3_F37BC(u32 n, u32 k);
void fn_3_F38D4(void);
void fn_3_F3A04(struct StaC5Obj* p);
void fn_3_F3A5C(struct StaC5Obj* p, f32 x, f32 y, f32 z, f32 r);
void fn_3_F3AE0(struct StaC5Obj* p);
void fn_3_F3BB0(struct StaC5Obj* p);
struct Emitter;
s32 fn_3_F3CD0(struct Emitter* em);
void fn_3_F3EFC(struct Emitter* em);
void fn_3_F42A0(void);
void fn_3_F466C(void);
void fn_3_F469C(void);
struct StadObjB;
void fn_3_F46A0(struct StadObjB* p);
void fn_3_F4BA0(struct StaC5Obj* p);
void fn_3_F4C4C(struct StaC5Obj* p);
void fn_3_F4D00(struct StaC5Obj* p);
void fn_3_F4DAC(void);
void fn_3_F4FBC(struct StadObjB* p);
void fn_3_F56CC(struct StadObjB* p);
void fn_3_F5C30(struct StaC5Obj* p);
s32 fn_3_F5E78(u8 id);
s32 fn_3_F5EFC(u32* a, u32* b);
s32 fn_3_F5F28(f32* a, f32* b);
void fn_3_F5F4C(Mtx m);
struct SortEnt;
void fn_3_F6084(MtxPtr view, struct SortEnt* out);
void* fn_3_F6504(s32 idx, Mtx arg); // collision model, or NULL
void fn_3_F65C8(s32* n);
void fn_3_F66C8(s32* n);
void fn_3_F6938(s32* n);
void fn_3_F6A94(s32* n);
void fn_3_F6C60(void);
void fn_3_F6FCC(void);
void fn_3_F6FDC(void** files);

s32 fn_3_EE0BC(u32 v);

#endif // !__GAME_sta_c5_H_
