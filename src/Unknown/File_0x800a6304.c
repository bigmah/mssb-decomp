#include "Unknown/File_0x800a6304.h"

typedef struct
{
    u32 _00; // 00
    u32 _04; // 04
} lbl_803C6780_inner_struct;

typedef struct
{
    u32 tempValue;  // 000
    u32 count1;     // 004
    u32 count2;     // 008
    lbl_803C6780_inner_struct values1[0x20]; // 00C
    lbl_803C6780_inner_struct values2[0x20]; // 10C
} lbl_803C6780_struct;

static lbl_803C6780_struct data_803C6780;

void fn_800A6304(void)
{
    int iVar1;

    if (data_803C6780.count2 != 0)
    {
        data_803C6780.tempValue += data_803C6780.values2[data_803C6780.count2]._04;
        data_803C6780.values2[data_803C6780.count2--]._04 = data_803C6780.values2[data_803C6780.count2]._00 = 0;
    }
}

// 97%: register numbering of new_val/base differs (orig: base r6, new_val r5)
u32 fn_800A6354(u32 param_1)
{
    u32 new_val;

    param_1 = ALIGN_NEXT(param_1, 32);

    new_val = data_803C6780.values2[data_803C6780.count2]._00 - param_1;

    data_803C6780.count2++;

    data_803C6780.values2[data_803C6780.count2]._00 = new_val;
    data_803C6780.values2[data_803C6780.count2]._04 = param_1;

    data_803C6780.tempValue = new_val - (data_803C6780.values1[data_803C6780.count1]._00 + data_803C6780.values1[data_803C6780.count1]._04);

    return data_803C6780.values2[data_803C6780.count2]._00;
}

void fn_800A63C8(void)
{
    if (data_803C6780.count1 != 0)
    {
        data_803C6780.tempValue += data_803C6780.values1[data_803C6780.count1]._04;

        data_803C6780.values1[data_803C6780.count1--]._04 = data_803C6780.values1[data_803C6780.count1]._00 = 0;
    }
}

u32 fn_800A6418(u32 param_1)
{
    u32 new_val;
    u32 a;
    param_1 = ALIGN_NEXT(param_1, 32);
    a = data_803C6780.values1[data_803C6780.count1]._00;
    new_val = a + data_803C6780.values1[data_803C6780.count1++]._04;
    data_803C6780.values1[data_803C6780.count1]._00 = new_val;
    data_803C6780.values1[data_803C6780.count1]._04 = param_1;
    data_803C6780.tempValue = data_803C6780.values2[data_803C6780.count2]._00 - (new_val + param_1);
    return data_803C6780.values1[data_803C6780.count1]._00;
}

void fn_800A648C()
{
    memset(&data_803C6780, 0, sizeof(data_803C6780));
    data_803C6780.values1[0]._00 = 0x00804000;
    data_803C6780.values2[0]._00 = 0x01000000;
    data_803C6780.tempValue = 0x7fc000;
}