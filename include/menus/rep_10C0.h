#ifndef __REP_10C0_MENUS_H__
#define __REP_10C0_MENUS_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// Menu 3D camera (lbl_2_bss_1A81D4).
typedef struct MenuCamera {
    /*0x00*/ Mtx view;
    /*0x30*/ u16 rotX;    // pitch, 0x10000 = full turn
    /*0x32*/ u16 rotY;    // yaw
    /*0x34*/ f32 strafe;  // free-camera sideways speed (from the stick)
    /*0x38*/ f32 advance; // free-camera forward speed (from the stick)
    /*0x3C*/ f32 fov;
    /*0x40*/ Vec target;
    /*0x4C*/ Vec pos;
    /*0x58*/ s32 _58;
} MenuCamera;

// Damped spring that pulls a point towards a moving goal.
typedef struct MenuCameraSpring {
    /*0x0*/ f32 stiffness;
    /*0x4*/ f32 damping;
    /*0x8*/ f32 rest; // rest length
} MenuCameraSpring;

// One camera preset (lbl_2_data_38E0), size 0x24.
typedef struct MenuCameraPreset {
    /*0x00*/ Vec pos;
    /*0x0C*/ Vec target;
    /*0x18*/ f32 rotX;
    /*0x1C*/ f32 rotY;
    /*0x20*/ f32 fov;
} MenuCameraPreset;

// Camera fields of the large menus work area (lbl_2_bss_1A824C / lbl_2_bss_1A8248).
typedef struct MenuCameraWork {
    /*0x000000*/ u8 _000000[0x197608];
    /*0x197608*/ Vec pos;
    /*0x197614*/ Vec target;
    /*0x197620*/ Vec posPrev;      // goal of the position spring last frame
    /*0x19762C*/ Vec posSpring;    // position spring point
    /*0x197638*/ Vec targetPrev;   // goal of the target spring last frame
    /*0x197644*/ Vec targetSpring; // target spring point
    /*0x197650*/ Vec posClamped;
    /*0x19765C*/ Vec targetClamped;
    /*0x197668*/ MenuCameraSpring posParams;
    /*0x197674*/ MenuCameraSpring targetParams;
    /*0x197680*/ u8 _197680[0x19774A - 0x197680];
    /*0x19774A*/ s16 focusIndex; // -1: use the preset's target
    /*0x19774C*/ u8 _19774C[0x197845 - 0x19774C];
    /*0x197845*/ u8 cameraMode; // 0: preset, 1: free (pad controlled)
    /*0x197846*/ u8 _197846[2];
    /*0x197848*/ u8 noClamp;
    /*0x197849*/ u8 presetIndex;
    /*0x19784A*/ u8 _19784A[0x197855 - 0x19784A];
    /*0x197855*/ u8 springOn;
    /*0x197856*/ u8 focusMode; // 1: offset the preset position by the focus point
    /*0x197857*/ u8 _197857[0x197863 - 0x197857];
    /*0x197863*/ s8 padIndex;
} MenuCameraWork;

void fn_2_927C8(MenuCamera* cam, Vec* goal);

void fn_2_92A34(MenuCamera* cam, Vec* goal);

void fn_2_92CB0(MenuCamera* cam);

void fn_2_92F2C(MenuCamera* cam);

void fn_2_932DC(MenuCamera* cam);

void fn_2_93BF8(MenuCamera* cam);

void fn_2_93C64(void);

void fn_2_94604(u8 value);

void fn_2_9461C(s16 value);

void fn_2_94634(s32 i);

void fn_2_946DC(s32 i);

#endif
