#ifndef __STATIC_CAMERA_H_
#define __STATIC_CAMERA_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// Game camera (lbl_803C639C[4], returned by fn_80052768_getCamera). Kept out of
// UnknownHomes_Static.h so main.dol units can use it without that header.
typedef struct camera_803c639c_s {
    /*0x00*/ Mtx44 proj;
    /*0x40*/ Mtx view;
    /*0x70*/ Vec eye;
    /*0x7C*/ Vec target;
    /*0x88*/ Vec Up;
    artificial_padding(0x88, 0xa4, Vec);
    /*0xA4*/ f32 zoom; // unsure
} camera_803c639c_s; // size: 0xA8

typedef void (*fn_800528AC_parameter)(camera_803c639c_s*);

#endif // !__STATIC_CAMERA_H_
