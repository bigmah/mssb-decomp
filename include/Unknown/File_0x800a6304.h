#ifndef __UNKNOWN_FILE_0x800A6304_H__
#define __UNKNOWN_FILE_0x800A6304_H__

#include "types.h"

// ARAM stack allocator state: free byte count and two stacks of (address, size) entries.
typedef struct AramStackEntry
{
    u32 _00; // 00
    u32 _04; // 04
} AramStackEntry;

typedef struct AramStack
{
    u32 tempValue;  // 000: free ARAM bytes
    u32 count1;     // 004
    u32 count2;     // 008
    AramStackEntry values1[0x20]; // 00C
    AramStackEntry values2[0x20]; // 10C
} AramStack; // size: 0x20C

extern AramStack data_803C6780;

// ARAM stack allocator
void fn_800A63C8(void);
u32 fn_800A6418(u32 size);
void fn_800A64AC(void);

#endif
