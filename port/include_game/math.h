// "math.h" in the decomp means include/stl/math.h (MWCC searches include/stl):
// the host libm plus the decomp's PI/TAU/SQUARE helpers.
#include_next <math.h>
#include "../../include/stl/math.h"
