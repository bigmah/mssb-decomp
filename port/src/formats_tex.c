// Texture archive headers (TexArchive/TexImage, include/main/file_80024184.h).
// Only the headers are swapped: texel and palette data stay big-endian, which
// is what aurora's GXInitTexObj/GXInitTlutObj take.
#include "port/formats.h"
#include "port/endian.h"

// pad[1] of a converted archive; zero on disc.
#define TEX_ARCHIVE_SWAPPED 0x50

int port_swap_tex_archive(void* archive)
{
    uint8_t* b = (uint8_t*)archive;
    if (b[3] == TEX_ARCHIVE_SWAPPED)
        return 0;
    // Archives built into the executable (port/gen) are already native. A
    // big-endian count below 256 reads back with a zero low byte.
    if ((*(uint16_t*)b & 0xFF) != 0)
    {
        b[3] = TEX_ARCHIVE_SWAPPED;
        return 1;
    }
    swap16_inplace(b);
    uint16_t count = *(uint16_t*)b;
    for (uint32_t i = 0; i < count; i++)
    {
        uint8_t* e = b + 4 + i * 0x20;
        swap32_array(e + 0x00, 2); // data, tlut
        swap16_array(e + 0x08, 2); // height, width
        swap32_inplace(e + 0x10);  // lodBias
        swap16_inplace(e + 0x18);  // tlutEntries
        swap16_inplace(e + 0x1C);  // index
    }
    b[3] = TEX_ARCHIVE_SWAPPED;
    return 1;
}

void port_swap_offset_table(void* table, uint32_t count)
{
    swap32_array(table, count);
}

#define TPL_VERSION 2142000u

void port_swap_tex_palette(void* pal)
{
    uint8_t* b = (uint8_t*)pal;
    if (*(uint32_t*)b == TPL_VERSION)
        return;
    swap32_array(b, 3);
    uint32_t count = ((uint32_t*)b)[1];
    uint8_t* desc = b + ((uint32_t*)b)[2];
    for (uint32_t i = 0; i < count; i++)
    {
        uint32_t* d = (uint32_t*)(desc + i * 8);
        swap32_array(d, 2);
        // unpacked = 2: swapped, not relocated yet (headers can be shared).
        if (d[0] != 0)
        {
            uint8_t* t = b + d[0];
            if (t[0x23] == 0)
            {
                swap16_array(t, 2);
                swap32_array(t + 4, 7); // format, data, wrapS, wrapT, minFilter, magFilter, LODBias
                t[0x23] = 2;
            }
        }
        if (d[1] != 0)
        {
            uint8_t* c = b + d[1];
            if (c[2] == 0)
            {
                swap16_inplace(c);
                swap32_array(c + 4, 2); // format, data
                c[2] = 2;
            }
        }
    }
}
