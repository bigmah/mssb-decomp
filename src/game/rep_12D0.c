#include "game/rep_12D0.h"
#include "header_rep_data.h"

extern u8 g_Strikes[];
extern u8 g_Ball[];
extern u8 g_FieldingLogic[];
extern u8 g_Runners[];
extern u8 lbl_3_common_bss_32A94[];
extern u8 g_RunningLogic[];

// .text:0x00077914 size:0xC60 mapped:0x806B69A8
void fn_3_77914(void) {
    return;
}

// .text:0x00078574 size:0x1BC mapped:0x806B7608
// 99%: only register numbering differs (ball r6/r7, idx r7/r10, runner ptr r10/r6); structure matches
void fn_3_78574(s16 arg) {
    s32 flag = 0;
    s32 idx;
    s16 cur;
    s32 val;
    s32 off;
    u8* r;
    u8* e;
    if (*(s8*)(g_FieldingLogic + 0x126) == -1) {
        if (g_FieldingLogic[0x107] == 1) {
            if (g_Runners[*(s16*)(g_FieldingLogic + 0xC4) * 0x154 + 0x123] != 1) {
                *(s8*)(g_FieldingLogic + 0x127) = -1;
                return;
            }
            g_FieldingLogic[0x126] = *(s16*)(g_FieldingLogic + 0xC4);
        }
        if (g_FieldingLogic[0x107] == 2) {
            idx = (*(s16*)(g_FieldingLogic + 0xC4) + 3) & 3;
            if (g_Runners[idx * 0x154 + 0x123] != 1) {
                *(s8*)(g_FieldingLogic + 0x127) = -1;
                return;
            }
            g_FieldingLogic[0x126] = idx;
        }
    }
    if (g_FieldingLogic[0x107] != 0) {
        return;
    }
    if (g_Ball[0x1BD7] > 1) {
        return;
    }
    cur = *(s16*)(g_FieldingLogic + 0xC4);
    if (cur < 0 || cur > 3) {
        return;
    }
    if (*(s16*)(g_Ball + 0x1B7A) == 3) {
        return;
    }
    if (*(s8*)(lbl_3_common_bss_32A94 + 0x22) >= 1) {
        return;
    }
    if (g_Ball[0x1BBE] >= 2) {
        return;
    }
    if (*(s32*)(g_Strikes + 8) > *(s32*)(g_Strikes + 0xC)) {
        return;
    }
    idx = (cur + 3) & 3;
    off = idx * 0x154;
    r = g_Runners + off;
    if (r[0x123] != 1) {
        return;
    }
    val = *(s16*)(g_Ball + 0x1B62) + 0xF;
    if (*(s16*)(r + 0xEE) == 0) {
        if (cur != r[0x127]) {
            return;
        }
        if (cur == r[0x125]) {
            return;
        }
        val += 0x1E;
    }
    e = g_Runners;
    e += off;
    if (val < *(s16*)(e + 0xEA)) {
        flag = 1;
    }
    if (flag != 0) {
        *(s16*)(g_FieldingLogic + 0xEA) = arg;
        g_FieldingLogic[0x113] = idx + 3;
    }
}

// .text:0x00078730 size:0x394 mapped:0x806B77C4
void fn_3_78730(void) {
    return;
}

// .text:0x00078AC4 size:0x57C mapped:0x806B7B58
void fn_3_78AC4(void) {
    return;
}

// .text:0x00079040 size:0x2F8 mapped:0x806B80D4
void fn_3_79040(void) {
    return;
}

// .text:0x00079338 size:0xDC mapped:0x806B83CC
void fn_3_79338(void) {
    s32 i;
    if (*(s32*)(g_Strikes + 0xC) == 2) {
        return;
    }
    if (*(s32*)(g_Strikes + 8) >= 3) {
        return;
    }
    if (lbl_3_common_bss_32A94[0x24] == 0) {
        if (*(s16*)(g_Ball + 0x1B7A) == 3 || g_FieldingLogic[0x113] == 1) {
            if (g_Ball[0x1BBF] >= 2) {
                lbl_3_common_bss_32A94[0x24] = 2;
            }
        }
    } else if (lbl_3_common_bss_32A94[0x24] == 2) {
        if (*(s16*)(g_Ball + 0x1B7A) == 3) {
            for (i = 1; i < 4; i++) {
                if (g_Runners[i * 0x154 + 0x123] == 3) {
                    lbl_3_common_bss_32A94[0x24] = 1;
                }
            }
        }
    }
}

// .text:0x00079414 size:0x194 mapped:0x806B84A8
void fn_3_79414(void) {
    u8* q;
    u8* p;
    u8 a;
    u8 b;
    u8 t;
    s32 i;
    s32 r7;
    s32 r8;
    if (g_Ball[0x1BD3] != 0) {
        lbl_3_common_bss_32A94[0x24] = 0xE;
        return;
    }
    if (*(s32*)(g_Strikes + 0xC) >= 2) {
        return;
    }
    if (g_RunningLogic[0x12] <= 1) {
        return;
    }
    if (lbl_3_common_bss_32A94[0x24] == 0) {
        if (g_Ball[0x1BC9] == 1 || g_Ball[0x1BC9] == 2 || *(s16*)(g_FieldingLogic + 0xCC) >= 0 || *(s16*)(g_FieldingLogic + 0xE8) >= 0) {
            lbl_3_common_bss_32A94[0x24] = 0xC;
        }
    }
    if (lbl_3_common_bss_32A94[0x24] == 0xC || lbl_3_common_bss_32A94[0x24] == 0xF) {
        r7 = 0;
        r8 = 0;
        p = g_Runners + 0x154;
        q = p;
        for (i = 0; i < 3; i++, q += 0x154) {
            if (*(s16*)(q + 0xEE) != 0) r8++;
        }

        for (i = 1; i < 4; i++, p += 0x154) {
            a = p[0x125];
            b = p[0x124];
            if (a > b || (t = p[0x123]) == 3) {
                if (a == 4 && b == 3 && p[0x123] == 2) {
                    lbl_3_common_bss_32A94[0x24] = 0xD;
                    break;
                }
                if (*(s16*)(p + 0xEE) == 0) {
                    r7++;
                }
            } else if (t == 2) {
                lbl_3_common_bss_32A94[0x24] = 0xD;
                break;
            }
        }
        if (r7 != 0 && r8 == 0) {
            lbl_3_common_bss_32A94[0x24] = 0xB;
        }
    }
}

// .text:0x000795A8 size:0x1C4 mapped:0x806B863C
void fn_3_795A8(void) {
    return;
}

