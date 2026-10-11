#ifndef __GAME_rep_1188_H_
#define __GAME_rep_1188_H_

#include "mssbTypes.h"

// g_Fielders entry (stride 0x268), the fields set up by fn_3_6E24C.
typedef struct InMemFielderView {
    /*0x000*/ u8 _000[0x58];
    /*0x058*/ f32 maxVelocity;
    /*0x05C*/ f32 velocityPerWeight; // maxVelocity / _1D1
    /*0x060*/ u8 _060[0xE8 - 0x60];
    /*0x0E8*/ f32 reach[9]; // per-character reach table (lbl_3_data_79B4) scaled by the character size;
                            // [4]/[5] are [2] +/- a third
    /*0x10C*/ u8 _10C[0x16C - 0x10C];
    /*0x16C*/ f32 _16C;
    /*0x170*/ u8 _170[0x178 - 0x170];
    /*0x178*/ s16 rosterID;
    /*0x17A*/ s16 charID;
    /*0x17C*/ s16 starMissionCharID;
    /*0x17E*/ u8 _17E[0x1C4 - 0x17E];
    /*0x1C4*/ u8 aiLevel;
    /*0x1C5*/ u8 _1C5[2];
    /*0x1C7*/ u8 handedness;
    /*0x1C8*/ u8 characterClass;
    /*0x1C9*/ u8 weight;
    /*0x1CA*/ u8 catchType;     // 5 with magical catch, else the weight
    /*0x1CB*/ u8 wallAbility;   // 1 wall splat, 2 wall jump, 3 clamber
    /*0x1CC*/ u8 superJump;
    /*0x1CD*/ u8 throwStrength; // from the throwing-arm stat
    /*0x1CE*/ u8 throwingArm;
    /*0x1CF*/ u8 _1CF;
    /*0x1D0*/ u8 speed;
    /*0x1D1*/ u8 _1D1;
    /*0x1D2*/ u8 _1D2[0x218 - 0x1D2];
    /*0x218*/ u8 opponentIdx; // 0 for the captain, else 1..n
    /*0x219*/ u8 _219[0x268 - 0x219];
} InMemFielderView; // size: 0x268

void fn_3_6D6D4(int idx);
void fn_3_6D964(int rosterID, int runnerIdx);
void setInMemBatterConstants(int rosterID);
u8 fn_3_6E1D4(u8 v);
void fn_3_6E24C(int rosterID, int fielderIdx);
void fn_3_6EBB4(int rosterID);
void fn_3_6EF1C(void);

#endif // !__GAME_rep_1188_H_
