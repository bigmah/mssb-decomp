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

// Geometry palette (charPipeline DODisplayData): header, descriptors, layouts
// and their attribute headers; position/texcoord/normal arrays to native.
void port_swap_geo_palette(void* palette);

// Actor layout (C3 ActorLayout): header, bones and their orientation controls.
void port_swap_actor_layout(void* layout);

// Animation bank (C3 ANIMBank): sequences, tracks, key frames and their data.
void port_swap_anim_bank(void* bank);

// Skin (SKNHeader): lists, vertex data (compSize 4: f32 skins, 2: s16),
// vertex and flush indices.
void port_swap_skin(void* skin, uint32_t compSize);

// Shape (morph target) data and shape animation sets (file_80024D2C.h).
void port_swap_shape(void* shape);
void port_swap_shape_anim_set(void* set);

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
// Swaps such a table and relocates it in place to PTR32s.
void port_relocate_offset_table(void* table, uint32_t count);

// Character stats records (0xA0 bytes each), port/src/formats_game.c.
void port_swap_char_stats(void* data, uint32_t count);
// Stadium collision table, port/src/formats_game.c.
void port_swap_stadium_collision(void* table);
// Replay/scene camera animations, port/src/formats_game.c.
void port_swap_camera_anim_list(void* list);
void port_swap_camera_anim(void* anim);
// SpaniDesc lists declared as bytes, port/src/formats_game.c.
void port_swap_spani_descs(void* descs);
int port_spani_descs_native(const void* descs);
// Game song files (offset table + MusyX songs), port/src/formats_game.c.
void port_swap_song_table(void* base, uint32_t count);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
// Leading big-endian offset table of a file, up to max entries (formats_misc.c).
void port_swap_offset_header(void* file, unsigned max);
#ifdef __cplusplus
}
#endif
