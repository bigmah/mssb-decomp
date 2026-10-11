#include "game/auto_00_000CB6B4_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

typedef struct CB6B4State {
    u8 pad0[0x4];
    void* tex; // 0x04
} CB6B4State;

// Particle spawn parameters (layout as ParticleParamsC in main/file_800263FC.h).
typedef struct CB6B4Particle {
    void* tex;
    u8 pad4[0x58 - 0x4];
} CB6B4Particle;

extern CB6B4State lbl_3_common_bss_35154;
extern void* lbl_3_bss_9FDC;
extern CB6B4Particle lbl_3_data_18268;

// .text:0x000CB6B4 size:0x38 mapped:0x8070A748
// Relocates the texture-archive offset stored at the head of a loaded file.
void fn_3_CB6B4(void** file) {
    *file = (u8*)*file + (u32)file;
    convertTextureHeader(lbl_3_bss_9FDC = *file);
}

// .text:0x000CB6EC size:0x4C mapped:0x8070A780
void fn_3_CB6EC(f32 x, f32 y, f32 z) {
    Vec pos;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    lbl_3_data_18268.tex = lbl_3_common_bss_35154.tex;
    fn_8002955C(&pos, NULL, &lbl_3_data_18268);
}
