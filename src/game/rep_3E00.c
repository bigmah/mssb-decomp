#include "game/rep_3E00.h"
#include "header_rep_data.h"

extern u8 lbl_8036E548[];
extern u8 lbl_3_common_bss_32724[];
extern void LoadActorLayout(void*);
extern void convertGeometryAndSknHeader(void*, int);
extern void haveActLayoutPointToGeoHeader(void*, void*);
extern void convertTextureHeader(void*);
extern void fn_800BD190(void*, void*);
extern void fn_80025DDC(void*);
extern void fn_80025FFC(void*, void*);
extern void fn_80025EEC(void*, int, int);
extern void* _OSAllocFromHeap(int, int);
extern void* memset(void*, int, u32);
extern void* ActorObjectInitTable(u16);
extern void fn_3_11D2C8(s32 idx, s32 start, s32 count, s32 a, s32 b);
extern void fn_80025C58(void*, void*);
extern f32 lbl_3_rodata_3E50;

// 91%: only register allocation differs. Original has b=r31, bss=r30, a=r29, c=r28, zero=r29, one=r31;
// ours ranks the bss pointer (r31) above b (r30) as soon as the unit has any branch (zero check).
// Recipe so far: `#pragma opt_propagation off` keeps the idx/zero/one/cnt constants unfolded, and
// volatile field accesses force the reloads of fields 2DA0/2DA4/2DA8 after the stores.
// A static inline helper taking `u8* bss` as a parameter gave the right mapping when zero was a literal.
// Also tried (no gain): all 5040 local-declaration orders, ~2500 statement orders of the first block, `register`,
// int/ptr/u8 types for zero/one, reusing a/b as zero/one, inline helpers (bss param). An inline helper with
// literal zero folded gets bss=r30/b=r31 right (30 diff lines) but then the cmpwi/bne is dropped.
// .text:0x00166448 size:0x19C mapped:0x807A54DC
#pragma opt_propagation off
void fn_3_166448(void) {
    u8* b;
    u8* bss = lbl_3_common_bss_32724;
    u8* a;
    u8* c;
    u8* hdr = *(u8**)(lbl_8036E548 + 0x2D9C);
    int idx = 3;
    u8* p = hdr + idx * 4;
    *(u8* volatile*)(lbl_8036E548 + 0x2DA0) = hdr + *(u32*)(hdr + 0);
    *(u8* volatile*)(lbl_8036E548 + 0x2DA4) = hdr + *(u32*)(hdr + 4);
    *(u8* volatile*)(lbl_8036E548 + 0x2DA8) = hdr + *(u32*)(hdr + 8);
    a = *(u8* volatile*)(lbl_8036E548 + 0x2DA0);
    b = *(u8* volatile*)(lbl_8036E548 + 0x2DA4);
    *(u8**)(bss + 0) = hdr + *(u32*)(p + 0);
    c = *(u8* volatile*)(lbl_8036E548 + 0x2DA8);
    *(u8**)(bss + 4) = hdr + *(u32*)(p + 4);
    LoadActorLayout(a);
    convertGeometryAndSknHeader(b, 0);
    haveActLayoutPointToGeoHeader(a, b);
    convertTextureHeader(c);
    fn_800BD190(b, c);
    {
    int one = 1;
    int zero = 0;
    fn_80025DDC(*(u8**)bss);
    fn_80025FFC(*(u8**)bss, bss + 4);
    fn_80025EEC(bss + 4, 0, 0);
    if (zero == 0) {
        *(u16*)(bss + 0x1E) = one;
    }
    {
    int cnt = 1;
    *(u16*)(lbl_8036E548 + 0x3078) = cnt;
    *(void**)(lbl_8036E548 + 0x2D94) = _OSAllocFromHeap(0x20, cnt * 0x28);
    memset(*(void**)(lbl_8036E548 + 0x2D94), 0, *(u16*)(lbl_8036E548 + 0x3078) * 0x28);
    *(void**)(lbl_8036E548 + 0x68) = ActorObjectInitTable(*(u16*)(lbl_8036E548 + 0x3078));
    }
    fn_3_11D2C8(0, 0, 1, 0, 0);
    *(f32*)(lbl_3_common_bss_32724 + 0x14) = lbl_3_rodata_3E50;
    fn_80025C58(*(void**)lbl_3_common_bss_32724, *(u8**)(lbl_8036E548 + 0x68) + 0x34);
    }
}
