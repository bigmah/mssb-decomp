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

// Camera animation list (g_Camera views[0].animList): u32 offsets ending with
// 0. Swapped once per file (remembered by address).
void port_swap_camera_anim_list(void* list)
{
    static void* s_last;
    if (list == s_last)
        return;
    s_last = list;
    for (uint32_t* l = (uint32_t*)list;; l++)
    {
        *l = __builtin_bswap32(*l);
        if (*l == 0)
            break;
    }
}

// One camera animation (rep_3090 ReplayAnim), copied out of the list before
// fn_3_105C84 relocates it: u32 _0, u16 numFrames, s16 numTracks, u32
// frameTbl, u32 tracks[numTracks]; frameTbl = u16 n, u16, then (frame, value)
// u16 pairs; a track = s16 parent, u16 pad, u16 count, u8 type, u8 flags,
// s32 target, then count keys of 52/56/48 bytes (type 0/1/2): u16 frame,
// u16 pad, then 32-bit values.
void port_swap_camera_anim(void* anim)
{
    static const uint32_t kStride[3] = {52, 56, 48};
    uint8_t* b = (uint8_t*)anim;
    swap32_inplace(b);
    swap16_array(b + 4, 2);
    int16_t numTracks = *(int16_t*)(b + 6);
    swap32_array(b + 8, 1 + (uint32_t)numTracks);
    uint32_t* offs = (uint32_t*)(b + 8);
    uint16_t* tbl = (uint16_t*)(b + offs[0]);
    swap16_array(tbl, 2);
    swap16_array(tbl + 2, 2u * ((uint32_t)tbl[0] + 1));
    for (int i = 0; i < numTracks; i++)
    {
        uint8_t* t = b + offs[1 + i];
        swap16_array(t, 3);
        swap32_inplace(t + 8);
        uint16_t count = *(uint16_t*)(t + 4);
        uint8_t type = t[6];
        uint32_t stride = type < 3 ? kStride[type] : 52;
        uint8_t* k = t + 0xC;
        for (uint32_t j = 0; j < count; j++, k += stride)
        {
            swap16_inplace(k);
            swap32_array(k + 4, (stride - 4) / 4);
        }
    }
}

// SpaniDesc list (include/main/SpaniDesc.h, 0x20 bytes each) ending with
// type 3, declared as bytes in some units: u16 type, u16 animId, f32 x, y,
// s32, u8, u8, s16 parent, u8[4], f32 scale, u8, u8, s16.
void port_swap_spani_descs(void* descs)
{
    for (uint8_t* d = (uint8_t*)descs;; d += 0x20)
    {
        swap16_array(d, 2);
        swap32_array(d + 4, 3);
        swap16_inplace(d + 0x12);
        swap32_inplace(d + 0x18);
        swap16_inplace(d + 0x1E);
        if (*(uint16_t*)d == 3)
            break;
    }
}

// Whether a SpaniDesc list is in host order: types are 0..3 and the list ends
// with type 3, so a big-endian list shows a type >= 0x100 before any 3.
int port_spani_descs_native(const void* descs)
{
    const uint8_t* d = (const uint8_t*)descs;
    for (int i = 0; i < 1024; i++, d += 0x20)
    {
        uint16_t type = *(const uint16_t*)d;
        if (type == 3)
            return 1;
        if (type > 3)
            return 0;
    }
    return 1;
}
