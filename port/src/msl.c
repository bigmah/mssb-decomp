// Bits of MSL (the GameCube C library) the game relies on beyond the host libc.

// rand()/srand(): the game's random numbers (0..32767). The prelude maps
// rand/srand to these.
static unsigned int next = 1;

int msl_rand(void)
{
    next = next * 1103515245 + 12345;
    return (int)((next >> 16) & 0x7FFF);
}

void msl_srand(unsigned int seed)
{
    next = seed;
}

// Float constants the game reads as *(f32*)__float_nan etc.
int __float_nan[] = {0x7FFFFFFF};
int __float_huge[] = {0x7F800000};
int __double_huge[] = {0x00000000, 0x7FF00000}; // little-endian 64-bit +inf
