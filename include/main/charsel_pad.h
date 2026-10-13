#ifndef __MAIN_CHARSEL_PAD_H__
#define __MAIN_CHARSEL_PAD_H__

// Other views of lbl_8034E9A0 (CharSelWork, ChallengeRoster, ...) spell the
// CharSelectState's pointer fields as bytes; on PC they pad by how much those grow:
// PAD1 after the heap marks (0x46E8), PAD2 after the menu tasks (0x4748).
#ifdef PORT_LP64
#define CHARSEL_PC_PAD1 0x10
#define CHARSEL_PC_PAD2 0x8
#else
#define CHARSEL_PC_PAD1 0
#define CHARSEL_PC_PAD2 0
#endif

#endif
