// MSL's rand()/srand(): the game's random numbers (0..32767) on PC.

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
