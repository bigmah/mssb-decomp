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

// Stadium collision table (fn_3_6424): u16 n, u16 pad, u32 offsets[n + 1];
// offsets[0] -> AABB boxes (n x 6 f32), offsets[1..n] -> triangle groups of
// each box: { u8, u8 isList, u16 count, vertices } until count == 0, where a
// vertex is { f32 x, y, z; u16 type; u16 pad } and a group has count * 3
// (triangles) or count + 2 (strip) vertices. Swapped once (marker: the pad
// halfword is set to 0xFFFF).
void port_swap_stadium_collision(void* table)
{
    uint8_t* b = (uint8_t*)table;
    if (*(uint16_t*)(b + 2) == 0xFFFF)
        return;
    swap16_inplace(b);
    *(uint16_t*)(b + 2) = 0xFFFF;
    uint16_t n = *(uint16_t*)b;
    uint32_t* offs = (uint32_t*)(b + 4);
    swap32_array(offs, (uint32_t)n + 1);
    swap32_array(b + offs[0], (uint32_t)n * 6);
    for (uint32_t i = 1; i <= n; i++)
    {
        uint8_t* g = b + offs[i];
        for (;;)
        {
            swap16_inplace(g + 2);
            uint16_t count = *(uint16_t*)(g + 2);
            if (count == 0)
                break;
            uint32_t verts = g[1] ? (uint32_t)count + 2 : (uint32_t)count * 3;
            uint8_t* v = g + 4;
            for (uint32_t k = 0; k < verts; k++, v += 16)
            {
                swap32_array(v, 3);
                swap16_inplace(v + 12);
            }
            g = v;
        }
    }
}
