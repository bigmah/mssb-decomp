// Small runtime hooks used by the prelude's helpers.
#include <stdio.h>
#include <stdlib.h>

void port_ptr32_fail(const void* p)
{
    fprintf(stderr, "FATAL: pointer %p is outside the game heap and can't be stored in 32 bits\n", p);
    abort();
}
