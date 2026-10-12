#ifdef TARGET_PC
// PC build: use the host/aurora headers instead.
#include <stdlib.h>
#else
#ifndef _MSL_RAND_H
#define _MSL_RAND_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

int rand();
void srand(u32 seed);

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
#endif // TARGET_PC
