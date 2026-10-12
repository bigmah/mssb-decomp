#include "game/rep_1CB8.h"
#define REP_HEADER_FN repHeader_1CB8
#include "header_rep_inline.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/math_api.h"

extern f32 lbl_3_data_4444[];

extern int __float_nan[];
#define NAN (*(f32*)__float_nan)
f64 __frsqrte(f64);

#define SQRT_L(x)                                                                                  \
    do {                                                                                           \
        if ((x) > 0.0f) {                                                             \
            f64 xd = (f64)(x);                                                                     \
            f64 guess = __frsqrte(xd);                                                             \
            guess = 0.5 * guess * (3.0 - guess * guess * xd);          \
            guess = 0.5 * guess * (3.0 - guess * guess * xd);          \
            guess = 0.5 * guess * (3.0 - guess * guess * xd);          \
            (x) = (f32)(xd * guess);                                                               \
        } else if ((x) < 0.0) {                                                      \
            (x) = NAN;                                                                             \
        } else if (isnan(x)) {                                                                     \
            (x) = NAN;                                                                             \
        }                                                                                          \
    } while (0)

// .text:0x000B7E44 size:0xAC mapped:0x806F6ED8
int fn_3_B7E44(s16 a, f32 y) {
    f32 t;
    s16 d;
    if (a < 0x1E0 || a > 0x620) {
        return 0;
    }
    d = 0x200 - __abs(a - 0x400);
    t = 0.06 * d;
    if (63.0f + t < y) {
        return 2;
    }
    if (55.0f + t < y) {
        return 1;
    }
    return 0;
}

// .text:0x000B7E10 size:0x34 mapped:0x806F6EA4
int fn_3_B7E10(f32 a, f32 b) {
    return b < a - 0.15f ? 1 : (b < -a - 0.15f);
}

// .text:0x000B7DD8 size:0x38 mapped:0x806F6E6C
int fn_3_B7DD8(f32 a, f32 b) {
    return b > a + lbl_3_data_4444[5] ? 1 : (b > -a + lbl_3_data_4444[5]);
}

// .text:0x000B7D6C size:0x6C mapped:0x806F6E00
int fn_3_B7D6C(f32 a, f32 b) {
    if (a > 0.0f) {
        if (b > a - 3.0f && b < 3.0f + a) {
            return 1;
        }
    } else if (b > -a - 3.0f && b < 3.0f - a) {
        return 1;
    }
    return 0;
}

// .text:0x000B7CDC size:0x90 mapped:0x806F6D70
int fn_3_B7CDC(f32 a, f32 b) {
    VecSrcDst p;
    CollisionStruct c;
    u32 t;
    p.src.x = a;
    p.src.y = -100.0f;
    p.src.z = b;
    p.dst.x = a;
    p.dst.y = 100.0f;
    p.dst.z = b;
    t = checkCollision(&p, &c, 0, 0);
    t &= 0x7F;
    if (t == 1 || t == 6 || t == 9 || t == 10 || t == 50) {
        return 0;
    }
    return 1;
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
    if (0.0f == len) {
        return 100.0f;
    }
    s = 200.0f / len;
    m = -0.5f;
    p.src.y = m;
    p.dst.y = m;
    p.dst.x = x * s;
    p.dst.z = z * s;
    p.src.x = 0.0f;
    p.src.z = 0.0f;
    checkCollision(&p, &c, 0, 0);
    e = c.position.x * c.position.x + c.position.z * c.position.z;
    SQRT_L(e);
    return e - len;
}

