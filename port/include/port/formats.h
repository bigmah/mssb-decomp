// Byte-swap passes for disc formats loaded in place (port/src/formats.c).
// Each runs exactly once, at load, right before the game's own relocation.
// Scalars become native; texture data and display lists stay big-endian.
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Message table: u16 count, u16 pad, u32 offsets[count], then u16 text.
void port_swap_msg_table(void* table);

// Texture archive (TexArchive): u16 count, u16 pad, then count 0x20-byte
// images {u32 data, u32 tlut, u16 height, u16 width, u8 wrapS, wrapT, minFilter,
// magFilter, f32 lodBias, u8 x4, u16 tlutEntries, u8 tlutFormat, u8 pad,
// u16 index, u16 pad}. Returns 0 if the archive was already converted
// (relocated), 1 if the caller should relocate it now.
int port_swap_tex_archive(void* archive);

#ifdef __cplusplus
}
#endif
