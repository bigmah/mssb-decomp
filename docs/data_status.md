# REL data still in `auto_*` units

Ranges of `.data`/`.bss` that no `splits.txt` entry owns yet (dtk puts them in
`auto_04_*`/`auto_05_*` units), largest first, with the units whose code references
them and why they are still open. REL `.rodata` has no auto ranges left.

How a range was assigned: a TU's `.data` starts 8-aligned and holds its file-scope
objects first, then each function's jump tables (and function-local statics) in
function order. So the jump tables after a block of tables name the TU that owns it,
an odd start address continues the previous TU, and each copy of the 0x2C2-byte
`debug_menu_data.h` block starts a menus TU.

| Size | Module | Section | Range | Referenced by | Status |
|---:|---|---|---|---|---|
| 0x4248 | menus | .data | 0x2A3C0-0x2E608 | auto 71EC4 | Five TUs (rodata-only rep_0C50..rep_0D90), each with its own debug-menu copy; needs auto 71EC4 split into those units first. |
| 0x2618 | menus | .data | 0x180-0x2798 | auto 1254, rep_0568, rep_04B0, rep_0438 | Same: auto 1254 holds the TUs of rep_0200..rep_03E8 (six debug-menu copies). |
| 0x1718 | menus | .data | 0x1F4D8-0x20BF0 | auto 5597C, auto 4B1AC, rep_0A58 | Two TUs: 0x1F4D8-0x1F8EC (tail of auto 4B1AC) and 0x1F8F0-0x20BEC (rep_0A58 with the 4B1AC tail and the start of auto 5597C); each starts with a debug-menu copy and header statics. |
| 0x16C8 | game | .data | 0x69C0-0x8088 | rep_E08, rep_1188, game_batter, ... | Shared tables (BatterHitbox, ...) between rep_EA0 and rep_1200; no jump table marks the owner (rep_F80/rep_10E8/auto 6D4A0/rep_1188 are possible). |
| 0xE48 | menus | .bss | 0x758-0x15A0 | rep_0568, auto 1254, rep_0640 | Multi-TU auto 1254, as above. |
| 0x360 | menus | .bss | 0x9E10-0xA170 | rep_0AB0, auto 4B1AC | 0x9E10 is one `s8` in the code but 0x358 bytes in symbols.txt; 0xA168/0xA169 are rep_0AB0's. |
| 0x360 | game | .data | 0x188E8-0x18C48 | auto 106DFC, rep_28A8, auto DEB90, auto D8A10 | Defined (typed) in auto DEB90.c already. rep_28A8 and auto DEB90 are one TU (one rodata header); giving the range to DEB90 makes a cyclic link order and rep_28A8.c declares other views of the same objects. Needs the two units merged. |
| 0x268 | game | .data | 0x1B820-0x1BA88 | sta_c5 | sta_c5 reads it through a `StaC5Data` view of the pooled block; the declared element types don't match the symbol sizes. |
| 0x3C | game | .bss | 0x9FDC-0xA018 | auto CB6B4 | Starts at a 4-aligned address inside a previous TU's `.bss`; the code reads one pointer. |
| 0x1C | game | .data | 0x6804-0x6820 | none | Zero padding before rep_EA0 (32-aligned). |
| 0x10 | menus | .bss | 0xB2A8-0xB2B8 | none | Unreferenced. |
| 0x10 | challenge | .data | 0x1F0-0x200 | none | Zero padding between rep_0000 and rep_00B0. |

## Assigned in this pass

game: rep_16B8 (0x8D88-0xF4D0, screen layout tables), auto 5985C (0x3D60-0x65EC,
batting/fielding tables; the text of rep_CC8/D18/D68/DB8), rep_E08, rep_A00
(0x1D28-0x3C40), rep_3880, auto 157DB8, rep_18E8/auto AC9F8/auto B3B70
(0xF50C-0x10AB0), kinoko, rep_4090, rep_1770, rep_1E08, the jump-table chunks of
auto 759BC/7976C/DEB90/114FC0/1608F0. menus: rep_0788, auto 33E70, auto 1B1BC
(0x2E40-0x4C64), rep_0AB0, auto 5E84C, rep_0B08, rep_08E8, auto 3C03C, auto 4B1AC
(jump table), rep_0F60. challenge: rep_0610, rep_74A0, rep_7730 (jump tables).
Linked: game/rep_3AE8.

Jump tables of `NONMATCHING` functions are defined next to the function under
`#if !NONMATCHING` (`void* jumptable_N_data_X[] = {(u8*)fn + off, ...}`); tables of
matched functions are renamed to `@N` in symbols.txt (`tools/litnames.py --incomplete`)
so objdiff pairs them with the compiler's.

## Found on the way

- Two matched menus functions had wrong jump tables (missing case labels): fn_2_2CF58,
  fn_2_306D8 (fixed). objdiff and fndiff can't see this; comparing each table's
  relocations with the original's does.
- Same check, not fixed: menus fn_2_1578/fn_2_1800/fn_2_1DC8 (auto 1254) jump to the
  case bodies of 2/3 and 5/6 in swapped order. That's harmless only if those bodies are
  identical.
- game rep_3B70 still can't link. Its three float constants must be literals (the
  original pools them in this file's `.rodata`), and then mwcc hoists the shared
  `/ 100000.0f` and `* 0.5f` out of both branches.
