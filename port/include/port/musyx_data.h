// Endian conversion for MusyX and streamed-audio data loaded from disc.
//
// All of these swap a freshly loaded big-endian buffer to native order, in
// place, exactly once. Layouts follow the MusyX runtime's parsing code
// (decomp/musyx: s_data.c, synthdata.c, seq.c); see port/src/audio/musyx_data.cpp.
//
// What stays big-endian: sample data (.samp, uploaded to ARAM and decoded by
// the DSP emulation), ADPCM stream payloads, and pool "curve" tables (byte
// curves, and ADSR tables that are stored little-endian on disc and read
// through explicit byte composition by synthmacros.c).
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Project (.proj): group list, ID lists, FX tables, song-group pages/MIDI setups.
void port_musyx_swap_proj(void* data, uint32_t size);
// Pool (.pool): macros (u32 command pairs), keymaps, layers.
void port_musyx_swap_pool(void* data, uint32_t size);
// Sample directory (.sdir): entries and their ADPCM info (coefficients, ADPCM+ blocks).
void port_musyx_swap_sdir(void* data, uint32_t size);
// Song / arrangement (.song) as read by seq.c.
void port_musyx_swap_song(void* data, uint32_t size);

// DSPADPCM header (0x60 bytes, sDSPADPCM in GCStream.h / the standard .dsp header).
void port_swap_dsp_adpcm_header(void* hdr);
// Interleaved stream header (.idsp): char[4] "IDSP", u32 interleave, u32 length.
void port_swap_idsp_header(void* hdr);

#ifdef __cplusplus
}
#endif
