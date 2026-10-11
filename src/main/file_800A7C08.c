#include "main/file_800A7C08.h"
#include "Dolphin/os.h"
#include "Dolphin/gx.h"
#include "Dolphin/vi.h"
#include "Dolphin/card.h"
#include "Dolphin/dvd.h"

extern OSThread* GXSetCurrentGXThread(void);
extern s32 OSSignalSemaphore(OSSemaphore* sem);

// .text:0x800A7C08 size:0x144
void fn_800A7C08(void) {
    return;
}

// .text:0x800A7D4C size:0x30
void fn_800A7D4C(s32 index, DrawCallbackNode* node) {
    node->next.bits.addr = lbl_803C7420.drawList[index].bits.addr;
    lbl_803C7420.drawList[index].raw = (u32)node | 1;
}

// .text:0x800A7D7C size:0x34
void fn_800A7D7C(DrawLink* list, s32 count) {
    lbl_803C7420.drawList = list;
    count--;
    do {
        list->raw = (u32)(list + 1) | 1;
        list++;
    } while (--count != 0);
    list->raw = 0;
}

// .text:0x800A7DB0 size:0x50
void fn_800A7DB0(void) {
    return;
}

// .text:0x800A7E00 size:0x110
void fn_800A7E00(void) {
    return;
}

// .text:0x800A7F10 size:0x1D8
void fn_800A7F10(void) {
    return;
}

// .text:0x800A80E8 size:0x3DC
void initRenderMode(void) {
    return;
}

// .text:0x800A84C4 size:0x54
void fn_800A84C4(void) {
    return;
}

// .text:0x800A8518 size:0x19C
void fn_800A8518(void) {
    return;
}

// .text:0x800A86B4 size:0x1B0
void fn_800A86B4(void) {
    return;
}

extern u8 lbl_803CC135;

extern u8 lbl_803CC134;

// fn_800A8864, size:0x14
u16 fn_800A8864(void) {
    u16 value = lbl_803CC135;
    value = (value << 8) | lbl_803CC134;
    return value;
}

// .text:0x800A8878 size:0x48
void fn_800A8878(void) {
    return;
}

extern u32 lbl_803CC140;

extern u32 lbl_803CC148;

extern u32 lbl_803CC154;

// fn_800A88C0, size:0x8
u32 fn_800A88C0(void) {
    return lbl_803CC154;
}

// fn_800A88C8, size:0x8
u32 fn_800A88C8(void) {
    return lbl_803CC148;
}

// fn_800A88D0, size:0x8
u32 fn_800A88D0(void) {
    return lbl_803CC140;
}

// .text:0x800A88D8 size:0x1D8
void fn_800A88D8(void) {
    return;
}

extern u32 lbl_803CC140;

// fn_800A8AB0, size:0x8
void fn_800A8AB0(u32 value) {
    lbl_803CC140 = value;
}

// .text:0x800A8AB8 size:0xC0
void fn_800A8AB8(void) {
    return;
}

// .text:0x800A8B78 size:0x144
void fn_800A8B78(void) {
    return;
}

// .text:0x800A8CBC size:0x174
void LoadFile(void) {
    return;
}

// .text:0x800A8E30 size:0x138
void fn_800A8E30(void) {
    return;
}

// .text:0x800A8F68 size:0x74
void fn_800A8F68(void) {
    return;
}

// .text:0x800A8FDC size:0x58
void fn_800A8FDC(void) {
    return;
}

// .text:0x800A9034 size:0x58
void fn_800A9034(void) {
    return;
}

// .text:0x800A908C size:0x58
void fn_800A908C(void) {
    return;
}

// .text:0x800A90E4 size:0x84
void fn_800A90E4(void) {
    return;
}

// .text:0x800A9168 size:0x48
void fn_800A9168(void) {
    return;
}

// .text:0x800A91B0 size:0x1FC
void fn_800A91B0(void) {
    return;
}

// .text:0x800A93AC size:0x78
void fn_800A93AC(void) {
    return;
}

// .text:0x800A9424 size:0x84
void fn_800A9424(void) {
    return;
}

extern u32 lbl_803CC13C;

extern u32 lbl_803CC12C;

// fn_800A94A8, size:0x1C
void fn_800A94A8(u8 flag) {
    if (flag == 0) {
        lbl_803CC12C = 1;
        lbl_803CC13C = 0;
    }
}

// .text:0x800A94C4 size:0x5C
void fn_800A94C4(void) {
    return;
}

// .text:0x800A9520 size:0x2B0
void fn_800A9520(void) {
    return;
}

extern u8 lbl_80110080[];

extern u8 lbl_803C77B8[];

// fn_800A97EC, size:0x50
void fn_800A97EC(s32 index, u32 enable, u8 type) {
    u8* entry = lbl_803C77B8 + index * 0x20;
    if (!(lbl_80110080[6] & (1 << index))) {
        entry[0xA] = enable;
        entry[0xB] = 0;
        if (enable != 0) {
            entry[0xB] = type;
        }
        entry[9] = 1;
    }
}

// fn_800A97D0, size:0x1C
void fn_800A97D0(u8 value, s32 index) {
    lbl_80110080[7] = value;
    lbl_80110080[8] = -index;
    lbl_80110080[9] = index;
}

// .text:0x800A983C size:0x28
void fn_800A983C(void) {
    return;
}

// .text:0x800A9864 size:0x98
void fn_800A9864(void) {
    return;
}

// .text:0x800A98FC size:0x3FC
void fn_800A98FC(void) {
    return;
}

// .text:0x800A9CF8 size:0x13C
void fn_800A9CF8(void) {
    return;
}

// .text:0x800A9E34 size:0x98
void fn_800A9E34(void) {
    return;
}

// .text:0x800A9ECC size:0x480
void fn_800A9ECC(void) {
    return;
}

// .text:0x800AA34C size:0x100
void fn_800AA34C(void) {
    return;
}

// .text:0x800AA44C size:0x4E4
void fn_800AA44C(void) {
    return;
}

// .text:0x800AA930 size:0x140
void fn_800AA930(void) {
    return;
}

// .text:0x800AAA70 size:0x474
void fn_800AAA70(void) {
    return;
}

// .text:0x800AAEE4 size:0x108
void fn_800AAEE4(void) {
    return;
}

// .text:0x800AAFEC size:0x488
void fn_800AAFEC(void) {
    return;
}

// .text:0x800AB474 size:0xC0
void fn_800AB474(void) {
    return;
}

// .text:0x800AB534 size:0x5E0
void fn_800AB534(void) {
    return;
}

// .text:0x800ABB14 size:0x4C
void fn_800ABB14(void) {
    return;
}

// .text:0x800ABB60 size:0x70
void fn_800ABB60(void) {
    return;
}

// .text:0x800ABBD0 size:0x374
void fn_800ABBD0(void) {
    return;
}

// .text:0x800ABF44 size:0x5C4
void fn_800ABF44(void) {
    return;
}

// .text:0x800AC508 size:0x764
void fn_800AC508(void) {
    return;
}

extern u8 lbl_803C7838[];

// fn_800ACCD4, size:0x14
void fn_800ACCD4(void) {
    *(u8*)(lbl_803C7838 + 0x55) = 0x7;
}

// fn_800ACC6C, size:0x68
s32 fn_800ACC6C(s32 mode, s32 a, s32 b) {
    s32 base = mode;
    s32 total;
    s32 q;
    switch (mode) {
    case 0:
        base = 0;
        break;
    case 1:
        base = 0x1800;
        break;
    case 2:
        base = 0xE00;
        break;
    }
    total = base + a + b;
    q = total / 0x2000;
    if (total % 0x2000 != 0) {
        q++;
    }
    return q;
}

// .text:0x800ACCE8 size:0x5C
void fn_800ACCE8(void) {
    return;
}

// .text:0x800ACD44 size:0x20
void fn_800ACD44(void) {
    return;
}

// .text:0x800ACD64 size:0x1B0
void fn_800ACD64(void) {
    return;
}

// Simple two-ended arena: blocks are allocated upward from lo or downward from hi.
typedef struct HeapArena {
    /*0x0*/ s32 freeSize;
    /*0x4*/ u8* lo;
    /*0x8*/ u8* hi;
} HeapArena;

// Header placed just before every block handed out by the arena.
typedef struct HeapBlockHeader {
    /*0x0*/ u8* prev; // arena end (lo or hi) before this allocation
    /*0x4*/ s32 size;
} HeapBlockHeader;

extern HeapArena lbl_803C7898;

// .text:0x800ACF14 size:0x20
void fn_800ACF14(void* block) {
    u8* hi = ((HeapBlockHeader*)block)[-1].prev;
    lbl_803C7898.hi = hi;
    lbl_803C7898.freeSize = hi - lbl_803C7898.lo;
}

// .text:0x800ACF34 size:0x44
void fn_800ACF34(void) {
    return;
}

// .text:0x800ACF78 size:0x38
void fn_800ACF78(void) {
    return;
}

// .text:0x800ACFB0 size:0x20
void fn_800ACFB0(void* block) {
    u8* lo = ((HeapBlockHeader*)block)[-1].prev;
    lbl_803C7898.lo = lo;
    lbl_803C7898.freeSize = lbl_803C7898.hi - lo;
}

// .text:0x800ACFD0 size:0x4C
void _OSAllocFromHeap(void) {
    return;
}

// .text:0x800AD01C size:0x1C
void fn_800AD01C(void* hi) {
    lbl_803C7898.hi = hi;
    lbl_803C7898.freeSize = (u8*)hi - lbl_803C7898.lo;
}

// .text:0x800AD038 size:0x1C
void fn_800AD038(void* lo) {
    lbl_803C7898.lo = lo;
    lbl_803C7898.freeSize = lbl_803C7898.hi - (u8*)lo;
}

// .text:0x800AD054 size:0x1C
void fn_800AD054(void* lo, void* hi) {
    lbl_803C7898.lo = lo;
    lbl_803C7898.hi = hi;
    lbl_803C7898.freeSize = (u8*)hi - (u8*)lo;
}

// .text:0x800AD070 size:0x420
void fn_800AD070(void) {
    return;
}

// .text:0x800AD490 size:0x70
void fn_800AD490(void) {
    return;
}

// .text:0x800AD500 size:0x1BC
void fn_800AD500(void) {
    return;
}

// .text:0x800AD6BC size:0xC4
void fn_800AD6BC(void) {
    return;
}

// .text:0x800AD780 size:0xB0
void fn_800AD780(void) {
    return;
}

// .text:0x800AD830 size:0xE4
void fn_800AD830(void) {
    return;
}

// .text:0x800AD914 size:0x48
void fn_800AD914(void) {
    return;
}

// .text:0x800AD95C size:0x98
void fn_800AD95C(void) {
    return;
}

// .text:0x800AD9F4 size:0x108
void fn_800AD9F4(void) {
    return;
}

extern u8 lbl_803CC17D;

// fn_800ADAFC, size:0x8
u8 fn_800ADAFC(void) {
    return lbl_803CC17D;
}

// .text:0x800ADB04 size:0xF8
void fn_800ADB04(void) {
    return;
}

// .text:0x800ADBFC size:0x44
void fn_800ADBFC(void) {
    return;
}
