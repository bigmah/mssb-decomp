#ifndef _DOLPHIN_RAND_H
#define _DOLPHIN_RAND_H

#include "types.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/rand.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

#ifdef TARGET_PC
#undef RAND_MAX // host stdlib's; the game's rand() is MSL's (port/src/msl.c)
#endif
#define RAND_MAX         (32768.0f)
#define RAND_EBISAWA_MAX (32767.0f)

#ifdef TARGET_PC
#define inline static inline
#endif
inline f32 randEbisawaFloat() { return (f32)rand() / RAND_EBISAWA_MAX; }
inline f32 randFloat() { return (f32)rand() / RAND_MAX; }
inline int randInt(int multiplier) { return multiplier * randFloat(); }
inline f32 randWeightFloat(f32 range) { return (range * (f32)rand()) / RAND_MAX; }
#ifdef TARGET_PC
#undef inline
#endif

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
