// Byte-swap passes for disc formats loaded in place (port/src/formats.c).
// Each runs exactly once, at load, right before the game's own relocation.
// Scalars become native; texture data and display lists stay big-endian.
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Message table: u16 count, u16 pad, u32 offsets[count], then u16 text.
void port_swap_msg_table(void* table);

// 2D keyframe animation (Anim/SpaniAnim): port/src/formats_spani.c.
void port_swap_spani_anim(void* anim);

// Texture archive (TexArchive): u16 count, u16 pad, then count 0x20-byte
// images {u32 data, u32 tlut, u16 height, u16 width, u8 wrapS, wrapT, minFilter,
// magFilter, f32 lodBias, u8 x4, u16 tlutEntries, u8 tlutFormat, u8 pad,
// u16 index, u16 pad}. Returns 0 if the archive was already converted
// (relocated), 1 if the caller should relocate it now.
int port_swap_tex_archive(void* archive);

// TPL (charPipeline TEXPalette): u32 version (2142000), u32 numDescriptors,
// u32 descriptorArray; descriptors {u32 textureHeader, u32 CLUTHeader};
// TEXHeader {u16 height, width; u32 format, data, wrapS, wrapT, minFilter,
// magFilter; f32 LODBias; u8 edgeLOD, minLOD, maxLOD, unpacked};
// CLUTHeader {u16 numEntries; u8 unpacked, pad; u32 format, data}. No-op if
// the version already reads native.
void port_swap_tex_palette(void* pal);

// A table of count u32 file offsets at the start of a container file (font
// archive, ...). Call it exactly once per load (values can't tell native
// from big-endian reliably).
void port_swap_offset_table(void* table, uint32_t count);

#ifdef __cplusplus
}
#endif
