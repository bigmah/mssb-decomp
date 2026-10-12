#ifndef __MENUS_FIELD_POSITION_DATA_H__
#define __MENUS_FIELD_POSITION_DATA_H__

#include "mssbTypes.h"

// Unreferenced table of field positions (values 0..8), 5 rows of 8. File-scope static
// of a header: each including unit has its own copy in .data (11 copies in menus.rel).
// TODO type: meaning of the rows.
static u8 fieldPositionTable[5][8] = {
    {2, 5, 4, 3, 8, 3, 4, 5},
    {2, 6, 0, 1, 8, 6, 7, 1},
    {2, 0, 7, 4, 4, 3, 1, 2},
    {5, 1, 2, 4, 6, 8, 7, 6},
    {8, 5, 3, 3, 5, 7, 4, 6},
};

#endif
