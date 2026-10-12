// Byte-swap passes for game-flow data files (character stats, ...).
// See port/include/port/formats.h.
#include "port/formats.h"
#include "port/endian.h"

// Character stats file (0x46E0 bytes, loaded into the character-select state):
// 54 records of 0xA0 bytes (u32 fielding flags at 0x20, s16 id at 0x24,
// u16[21] at 0x74; the rest bytes), then byte tables.
void port_swap_char_stats(void* data, uint32_t count)
{
    uint8_t* p = (uint8_t*)data;
    for (uint32_t i = 0; i < count; i++, p += 0xA0)
    {
        swap32_inplace(p + 0x20);
        swap16_inplace(p + 0x24);
        swap16_array(p + 0x74, 21);
    }
}
