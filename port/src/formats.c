// Byte-swap passes for disc formats loaded in place. See
// port/include/port/formats.h and the format list in port/STATUS.md.
#include "port/formats.h"
#include "port/blob.h"
#include "port/endian.h"

#include <stdio.h>

void port_swap_msg_table(void* table)
{
    uint8_t* b = (uint8_t*)table;
    uint32_t size = port_blob_size(table);
    swap16_array(b, 2);
    uint16_t count = *(uint16_t*)b;
    swap32_array(b + 4, count);
    uint32_t text = 4 + 4u * count;
    if (size < text)
    {
        // Unknown size: swap each message up to its end code (0x4001).
        fprintf(stderr, "[port] msg table %p: unknown size, swapping per message\n", table);
        for (uint32_t i = 0; i < count; i++)
        {
            uint32_t off = ((uint32_t*)(b + 4))[i];
            if (off == 0)
                continue;
            uint16_t* s = (uint16_t*)(b + off);
            for (;;)
            {
                uint16_t c = __builtin_bswap16(*s);
                *s++ = c;
                if (c == 0x4001)
                    break;
            }
        }
        return;
    }
    swap16_array(b + text, (size - text) / 2);
}
