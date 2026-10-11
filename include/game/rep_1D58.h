#ifndef __GAME_rep_1D58_H_
#define __GAME_rep_1D58_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

struct StadiumObj;
struct SortEnt;

s32 fn_3_B7FC8(s32 id, s32 kind); // returns fn_3_8BBC4's sound handle
void fn_3_B80D0(void);
void fn_3_B8184(void* pp, void* cam);
struct StadiumObj* fn_3_B827C(void);
void fn_3_B828C(struct StadiumObj* val);
void fn_3_B8298(void);
void fn_3_B8414(void* a, void* b);
void fn_3_B8464(void* mtx, void* obj);
void fn_3_B8574(void);
u32 fn_3_B85A8(int idx, u32** out); // *out: the group's object indices; returns their count
void fn_3_B85DC(s32 i, void* a, void* b);
s32 fn_3_B8658(f32* a, f32* b);
void fn_3_B867C(void* mtx, struct SortEnt* out);
void fn_3_B8828(float (*view)[4], s32 translucent, u32 layer);
void fn_3_B8C08(float (*view)[4]);
void fn_3_B902C(void);
void fn_3_B908C(void);
void fn_3_B9124(void);
void processStadiumObjectFunction(int, void*, int, void*);
void* fn_3_B91C8(s32 type, s32 idx, Mtx m); // the object's collision model, or NULL
void fn_3_B939C(void);
void fn_3_B93C4(void);
void fn_3_B93C8(s32 unused); // empty; rep_1038 passes 1
void fn_3_B93CC(void);
void fn_3_B950C(void);
void fn_3_B9510(s32 i);
void fn_3_B9524(void);
void* fn_3_B9534(u32 w, u32 h, void* tex);
void fn_3_B95EC(void);
void fn_3_B97C8(void* p);
void fn_3_B97DC(u8* obj, void* animBank); // obj: ActorObject*
void fn_3_B98E8(void* p);
void fn_3_B99E4(void);
s32 fn_3_B9BB4(u32 type);
void fn_3_B9D68(u8* kinds, s32 count, u8* table, s32* outIdx);
void fn_3_B9FB8(u32 type, void* p);

#endif // !__GAME_rep_1D58_H_
