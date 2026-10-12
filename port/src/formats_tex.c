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
