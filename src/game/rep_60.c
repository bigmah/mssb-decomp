#include "game/rep_60.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"

extern u8* lbl_803CC1B8;
extern u8 lbl_8036E548[];
extern u8 lbl_803C6CF8[];
extern u8 lbl_800EFBE8[];
extern u8 lbl_3_common_bss_350E4[];
extern u8 lbl_3_data_228[];
extern s32 ARAMTransfer(void*, int, int, int);
extern u8 lbl_803716B8[];
extern u8 lbl_3_common_bss_35154[];
extern void OSReport(const char*, ...);
extern void fn_800229CC(void);
extern s32 fn_3_BF878(void);
extern void fn_3_BD7D8(void);
extern s32 fn_3_106E50(void);
extern void fn_3_106DFC(void);
extern void fn_8001CBD4(void);
extern void fn_3_5EC0(s32);
extern s32 fn_3_B9BB4(u8);

// .text:0x000004F4 size:0x168
void manageStadiumLoading(void) {
    u8* p = lbl_803CC1B8;
    switch (*(s16*)(p + 0x10)) {
    case 0:
        fn_8001CBD4();
        *(s32*)(lbl_8036E548 + 4) =
            ARAMTransfer(lbl_800EFBE8 + (g_d_GameSettings.miniGameStadiumIndicator + g_d_GameSettings.StadiumID * 3) * 16, 0, 0, 0);
        *(s16*)(p + 0x10) += 1;
        break;
    case 1:
        if (*(s8*)(lbl_803C6CF8 + 0x715) == 1) {
            fn_3_5EC0(*(s32*)(lbl_8036E548 + 4));
            *(s16*)(p + 0x10) += 1;
        }
        break;
    case 2: {
        switch (fn_3_B9BB4(g_d_GameSettings.StadiumID)) {
        case 1:
            *(s16*)(p + 0x10) = 3;
            break;
        case -1:
            *(s16*)(p + 0x10) = 4;
            break;
        }
        break;
    }
    case 3:
        if (lbl_3_common_bss_350E4[0x6A] == 0) {
            *(s16*)(p + 0x10) += 1;
        }
        break;
    default:
        *(s16*)(*(u8**)(p + 0xC) + 0x10) = 1;
        lbl_3_data_228[0x10] = 1;
        fn_800B0A14_removeQueue(lbl_3_data_228);
        break;
    }
}

// .text:0x0000065C size:0x278 mapped:0x8063F6F0
void manageLoadingState(void) {
    u8* p = lbl_803CC1B8;
    u8* r;
    switch (*(s16*)(p + 0x10)) {
    case 0:
        r = lbl_803716B8;
        if (*(u32*)(r + 0x1CC) != 0) {
            if (*(s8*)(lbl_803C6CF8 + 0x715) == 1) {
                s32 t = ARAMTransfer(lbl_800EFBE8 + (g_d_GameSettings.miniGameStadiumIndicator + g_d_GameSettings.StadiumID * 3) * 16, 0, 3,
                                     *(u32*)(r + 0x1CC));
                *(s32*)(p + 0x14) = t;
                *(s32*)(lbl_8036E548 + 4) = t;
                OSReport("Sta %d-%d aram:%x -> mem:%x\n", g_d_GameSettings.StadiumID, g_d_GameSettings.miniGameStadiumIndicator,
                         *(u32*)(r + 0x1CC), *(s32*)(p + 0x14));
                goto set1;
            }
        } else {
            s32 t = ARAMTransfer(lbl_800EFBE8 + (g_d_GameSettings.miniGameStadiumIndicator + g_d_GameSettings.StadiumID * 3) * 16, 0, 0, 0);
            *(s32*)(p + 0x14) = t;
            *(s32*)(lbl_8036E548 + 4) = t;
        set1:
            *(s16*)(p + 0x10) = 1;
        }
        break;
    case 1:
        if (*(s8*)(lbl_803C6CF8 + 0x715) == 1) {
            fn_3_5EC0(*(s32*)(p + 0x14));
            *(s16*)(p + 0x10) = 2;
            fn_800229CC();
        }
        break;
    case 2:
        switch (fn_3_B9BB4(g_d_GameSettings.StadiumID)) {
        case 1:
            *(s16*)(p + 0x10) = 3;
            break;
        case -1:
            *(s16*)(p + 0x10) = 4;
            break;
        }
        break;
    case 3:
        if (lbl_3_common_bss_350E4[0x6A] == 0) {
            *(s16*)(p + 0x10) = 4;
        }
        break;
    case 4:
        if (fn_3_BF878() != 0) {
            *(s16*)(p + 0x10) = 5;
        }
        break;
    case 5:
        if (lbl_3_common_bss_35154[0x3B0] == 0) {
            *(s16*)(p + 0x10) = 6;
        }
        break;
    case 6:
        fn_3_BD7D8();
        *(s16*)(p + 0x10) = 7;
        break;
    case 7:
        if (fn_3_106E50() != 0) {
            *(s16*)(p + 0x10) = 8;
        }
        break;
    case 8:
        if (*(s8*)(lbl_803C6CF8 + 0x715) == 1) {
            fn_3_106DFC();
            *(s16*)(p + 0x10) = 9;
        }
        break;
    default:
        *(s16*)(*(u8**)(p + 0xC) + 0x10) = 1;
        lbl_3_data_228[0x10] = 1;
        fn_800B0A14_removeQueue(lbl_3_data_228);
        break;
    }
}

