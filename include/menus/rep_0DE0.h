#ifndef __MENUS_REP_0DE0_H__
#define __MENUS_REP_0DE0_H__

#include "mssbTypes.h"
#include "Dolphin/vec.h"

typedef struct {
    void (*draw)(s32);
    Vec position;
    Vec rotation;
    u8 padding1C[0x0C];
} MenuDrawState;

typedef struct {
    void* actor;
    u8 padding[8];
} MenuDrawDescriptor;

typedef struct {
    MenuDrawDescriptor descriptor;
    u8 padding0C[0x60];
    u8 visible;
    u8 padding6D[0x23];
} MenuDrawRow;

typedef struct {
    u16 count;
    u8 padding[0x32];
    MenuDrawRow rows[1];
} MenuDrawCollection;

typedef struct {
    u8 padding[0x68];
    MenuDrawCollection* collection;
    u8 padding6C[0x40];
    void* lights[3];
    u8 paddingB8[0x2CDC];
    MenuDrawState* states;
    u8 padding2D98[0x2E0];
    u16 count;
} MenuDrawWorld;

typedef struct {
    u8 pad00[0x30];
    u16 yaw;
    u16 pitch;
    f32 offsetX;
    f32 offsetZ;
    Vec target;
    Vec eye;
} MenuCamera;

void fn_2_8563C(MenuCamera* camera);

void fn_2_87114(void);

void fn_2_870D4(f32 value);

void fn_2_869B4(void);

void fn_2_86A0C(void);

void fn_2_86F40(void);

void fn_2_86FEC(void);

void fn_2_868C8(void);

#endif
