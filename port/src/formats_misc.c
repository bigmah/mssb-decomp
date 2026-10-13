// Small offset-table headers ("file of 32-bit offsets from its own start").
#include "port/formats.h"
#include "port/endian.h"

// Swaps a file's leading big-endian offset table once: the table runs up to
// the first offset (where the data starts), at most max entries. A table
// that is already native (first offset small) is left alone.
void port_swap_offset_header(void* file, unsigned max)
{
    uint32_t* t = (uint32_t*)file;
    if (t[0] != 0 && t[0] < 0x01000000u)
        return; // already swapped
    uint32_t first = __builtin_bswap32(t[0]);
    unsigned n = first / 4;
    if (n == 0 || n > max)
        n = max;
    swap32_array(t, n);
}
