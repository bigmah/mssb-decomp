#include "game/rep_1CB8.h"
#include "header_rep_data.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/math_api.h"

extern f32 lbl_3_data_4444[];
extern f32 lbl_3_rodata_1D3C;
extern f32 lbl_3_rodata_1D08;
extern f32 lbl_3_rodata_1D38;

extern f64 lbl_3_rodata_1D10;
extern f64 lbl_3_rodata_1D18;
extern f64 lbl_3_rodata_1D20;
extern f32 lbl_3_rodata_1D2C;
extern f32 lbl_3_rodata_1D30;

extern int __float_nan[];
#define NAN (*(f32*)__float_nan)
f64 __frsqrte(f64);

#define SQRT_L(x)                                                                                  \
    do {                                                                                           \
        if ((x) > lbl_3_rodata_1D08) {                                                             \
            f64 xd = (f64)(x);                                                                     \
            f64 guess = __frsqrte(xd);                                                             \
            guess = lbl_3_rodata_1D10 * guess * (lbl_3_rodata_1D18 - guess * guess * xd);          \
            guess = lbl_3_rodata_1D10 * guess * (lbl_3_rodata_1D18 - guess * guess * xd);          \
            guess = lbl_3_rodata_1D10 * guess * (lbl_3_rodata_1D18 - guess * guess * xd);          \
            (x) = (f32)(xd * guess);                                                               \
        } else if ((x) < lbl_3_rodata_1D20) {                                                      \
            (x) = NAN;                                                                             \
        } else if (isnan(x)) {                                                                     \
            (x) = NAN;                                                                             \
        }                                                                                          \
    } while (0)

// .text:0x000B79AC size:0x280 mapped:0x806F6A40
f32 fn_3_B79AC(f32 x, f32 z) {
    VecSrcDst p;
    CollisionStruct c;
    f32 len;
    f32 s;
    f32 e;
    f32 m;
    len = x * x + z * z;
    SQRT_L(len);
    if (lbl_3_rodata_1D08 == len) {
        return 0.0f;
    }
    s = lbl_3_rodata_1D2C / len;
    m = -0.5f;
    p.src.y = m;
    p.dst.y = m;
    p.dst.x = x * s;
    p.dst.z = z * s;
    p.src.x = lbl_3_rodata_1D08;
    p.src.z = lbl_3_rodata_1D08;
    checkCollision(&p, &c, 0, 0);
    e = c.position.x * c.position.x + c.position.z * c.position.z;
    SQRT_L(e);
    return e - len;
}

// .text:0x000B7C2C size:0xB0 mapped:0x806F6CC0
int fn_3_B7C2C(Vec* a, Vec* b) {
    VecSrcDst p;
    CollisionStruct c;
    u32 t;
    p.src.x = a->x;
    p.src.y = -a->y;
    p.src.z = a->z;
    p.dst.x = b->x;
    p.dst.y = -b->y;
    p.dst.z = b->z;
    t = checkCollision(&p, &c, 0, 0);
    t &= 0x7F;
    if (t == 2 || t == 3 || t == 4 || t == 5 || t == 7 || t == 8 || t == 11) {
        return 1;
    } else {
        return 0;
    }
}

// .text:0x000B7CDC size:0x90 mapped:0x806F6D70
void fn_3_B7CDC(void) {
    return;
}

// .text:0x000B7D6C size:0x6C mapped:0x806F6E00
int fn_3_B7D6C(f32 a, f32 b) {
    if (a > lbl_3_rodata_1D08) {
        if (b > a - lbl_3_rodata_1D38 && b < lbl_3_rodata_1D38 + a) {
            return 1;
        }
    } else if (b > -a - lbl_3_rodata_1D38 && b < lbl_3_rodata_1D38 - a) {
        return 1;
    }
    return 0;
}

// .text:0x000B7DD8 size:0x38 mapped:0x806F6E6C
int fn_3_B7DD8(f32 a, f32 b) {
    return b > a + lbl_3_data_4444[5] ? 1 : (b > -a + lbl_3_data_4444[5]);
}

// .text:0x000B7E10 size:0x34 mapped:0x806F6EA4
int fn_3_B7E10(f32 a, f32 b) {
    return b < a - lbl_3_rodata_1D3C ? 1 : (b < -a - lbl_3_rodata_1D3C);
}

// .text:0x000B7E44 size:0xAC mapped:0x806F6ED8
void fn_3_B7E44(void) {
    return;
}

