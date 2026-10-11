#ifndef __GAME_sta_c4_H_
#define __GAME_sta_c4_H_

#include "mssbTypes.h"
#include "main/file_800263FC.h"

// Queue task (lbl_803CC1B8) that moves a knocked object along with the ball (fn_3_F934C).
typedef struct StaBounceTask {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ void* prev;
    /* 0x08 */ void* next;
    /* 0x0C */ void* parent;
    /* 0x10 */ s16 result;
    /* 0x12 */ u16 priority;
    /* 0x14 */ Vec normal;
    /* 0x20 */ Vec vel;
    /* 0x2C */ s32 idx;
    /* 0x30 */ u8 bounced;
} StaBounceTask;

void fn_3_F8524(Particle* p);
s32 fn_3_F85B0(Emitter* e);
void fn_3_F8878(Emitter* e);
void fn_3_F8ABC(void);
void fn_3_F8B04(void);
void fn_3_F8B30(void);
void fn_3_F8B34(void);
void fn_3_F8BA8(u8* o);
void fn_3_F8D00(void);
void fn_3_F8E20(void);
void fn_3_F9088(f32* pos, s32 idx);
void fn_3_F9164(u8* o);
void fn_3_F92FC(void);
void fn_3_F934C(void);
void fn_3_F963C(s32 idx, u8* v);
void fn_3_F976C(s32 idx, s32 b, u8* c);
void fn_3_F99F0(s32 idx);
void fn_3_F9B9C(s32 idx, s32 b, u8* c);
void fn_3_F9D94(u8* o);
void fn_3_F9E78(void);
void fn_3_FA3C0(void);
void fn_3_FA58C(void);
void fn_3_FB3D8(void);
void fn_3_FBBA0(u8* t);
void fn_3_F8444(void);
void fn_3_F8454(void);

#endif // !__GAME_sta_c4_H_
