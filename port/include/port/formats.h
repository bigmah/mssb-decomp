// Byte-swap passes for disc formats loaded in place (port/src/formats.c).
// Each runs exactly once, at load, right before the game's own relocation.
// Scalars become native; texture data and display lists stay big-endian.
#pragma once

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

#ifdef __cplusplus
}
#endif
