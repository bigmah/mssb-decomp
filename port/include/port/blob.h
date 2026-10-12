// Sizes of files loaded from disc (ARAMTransfer and friends), so format
// fixups that only get the buffer can swap the whole file once.
#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void port_blob_note(const void* p, uint32_t size);
uint32_t port_blob_size(const void* p); // 0 if unknown

#ifdef __cplusplus
}
#endif
