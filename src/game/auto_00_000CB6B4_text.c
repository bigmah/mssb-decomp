#include "game/auto_00_000CB6B4_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

typedef struct CB6B4State {
    u8 pad0[0x4];
    void* tex; // 0x04
} CB6B4State;

extern CB6B4State lbl_3_common_bss_35154;
extern void* lbl_3_bss_9FDC;
// Completes the forward declaration from UnknownHomes_Static.h (same layout as ParticleParamsC in
// main/file_800263FC.h, which conflicts with UnknownHomes_Static.h here).
struct ParticleParamsC {
    /* 0x00 */ void* tex; // TexArchive*
    /* 0x04 */ s32 prm[20];
};
extern struct ParticleParamsC lbl_3_data_18268;

// Relocates the texture-archive offset stored at the head of a loaded file.

// .text:0x000CB6EC size:0x4C mapped:0x8070A780
void fn_3_CB6EC(f32 x, f32 y, f32 z) {
    Vec pos;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    lbl_3_data_18268.tex = lbl_3_common_bss_35154.tex;
    fn_8002955C(&pos, NULL, &lbl_3_data_18268);
}

// .text:0x000CB6B4 size:0x38 mapped:0x8070A748
void fn_3_CB6B4(void** file) {
    // TODO(port): in-place offset relocation (the slot holds a 32-bit offset)
    *(u32*)file += PTR_TO_U32(file);
    convertTextureHeader(lbl_3_bss_9FDC = U32_TO_PTR(*(u32*)file));
}

// .data 0x18268: particle burst parameters (tex is filled in by fn_3_CB6EC).
struct ParticleParamsC lbl_3_data_18268 = {NULL, {25, 100, 40, 60, 18000, 20000, -2000000, 2000000, 80000, 100000, 200, -1, 0, 0, 1, 0, 0, 0, 0, 0}};
