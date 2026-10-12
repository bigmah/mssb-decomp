// Byte-swap passes for disc formats loaded in place (port/src/formats.c).
// Each runs exactly once, at load, right before the game's own relocation.
// Scalars become native; texture data and display lists stay big-endian.
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Message table: u16 count, u16 pad, u32 offsets[count], then u16 text.
void port_swap_msg_table(void* table);

// 2D keyframe animation (Anim/SpaniAnim): port/src/formats_spani.c.
void port_swap_spani_anim(void* anim);
// Spani file: u32 offsets of its texture archive and its animation.
void port_swap_spani_file(void* file);

#ifdef __cplusplus
}
#endif
