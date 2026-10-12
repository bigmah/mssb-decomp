#ifndef __HEADER_REP_INLINE_H__
#define __HEADER_REP_INLINE_H__

#include <types.h>

// Every REL source file starts its .rodata with the same 20 floats. They are
// the local static table of an inline function from a common header that the
// files include but never call. Under mwcc that function is `extern inline`,
// which emits the table in every file; the table is not poolable, so mwcc
// also stops pooling the file's other .rodata constants behind one base
// register (the originals load each constant with its own lis/lfs). A plain
// `static const` array (header_rep_data.h) gives the same bytes but pooled
// constant loads.
//
// The table is a weak symbol named after the function, and the linker keeps
// only one weak symbol per name, so each file names the function itself:
//     #define REP_HEADER_FN repHeader_7A28
//     #include "header_rep_inline.h"
//
// Elsewhere (the port) the function is static inline so it is not defined
// in every object.
#ifndef REP_HEADER_FN
#error "define REP_HEADER_FN (a per-file name) before including header_rep_inline.h"
#endif
#ifdef __MWERKS__
#define REP_HEADER_LINKAGE extern
#else
#define REP_HEADER_LINKAGE static
#endif

REP_HEADER_LINKAGE inline f32 REP_HEADER_FN(s32 i) {
    static const f32 table[20] = {
        1.f, 1.5707964f, 1.f, -1.f, 4.712389f, 3.1415927f, -1.f, 0.f, -1.f, 1.f,
        1.f, 1.5707964f, 1.f, -1.f, 4.712389f, 3.1415927f, -1.f, 0.f, -1.f, 1.f,
    };
    return table[i];
}

#endif
