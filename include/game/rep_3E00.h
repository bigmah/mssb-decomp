#ifndef __GAME_rep_3E00_H_
#define __GAME_rep_3E00_H_

#include "mssbTypes.h"
#include "main/file_80024D2C.h" // ShapeData, ShapeAnimPlayer

// lbl_3_common_bss_32724: shape animation of the trail model (only the fields used here).
typedef struct TrailShapeWork {
    /*0x00*/ ShapeData* shape;     // inside lbl_8036E548.trailFile
    /*0x04*/ ShapeAnimPlayer anim; // anim.set is inside trailFile too
} TrailShapeWork;

void fn_3_166448(void);

#endif // !__GAME_rep_3E00_H_
