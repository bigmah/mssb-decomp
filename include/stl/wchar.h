#ifdef TARGET_PC
// PC build: use the host/aurora headers instead.
#include <wchar.h>
#else
#ifndef _WCHAR_H
#define _WCHAR_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "PowerPC_EABI_Support/MSL_C/MSL_Common/wchar_io.h"

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
#endif // TARGET_PC
