# Common BSS

When passed the `-common on` flag, `mwcc` will generate global BSS symbols as **common**. The linker deduplicates common symbols with the same name, and allocates an area at the **end** of `.bss` for them.

This is a legacy feature, allowing uninitialized global variables to be defined in headers without linker errors:

```c
// foo.h
int foo;
```

With `-common on`, any TU that includes `foo.h` will define `foo` as a **common** symbol. The linker will deduplicate `foo` across TUs, similar to weak symbols. Common symbols are then generated at the **end** of `.bss`, after all other `.bss` symbols.

With `-common off`, `foo` would be defined as a **global** symbol, and the linker would error out with a duplicate symbol error if `foo.h` was included in multiple TUs.

In `splits.txt`, common BSS can be defined with the `common` attribute:

```yaml
foo.cpp:
	.text       start:0x80047E5C end:0x8004875C
	.ctors      start:0x803A54C4 end:0x803A54C8
	.data       start:0x803B1B40 end:0x803B1B60
	.bss        start:0x803DF828 end:0x803DFA8C
	.bss        start:0x8040D4AC end:0x8040D4D8 common
```

As shown above, a file can contain both regular `.bss` and common `.bss`. Marking common `.bss` appropriately is important for determining the final link order.

## Detection

Example from Pikmin 2:
```
00016e60 00000c 805069c0  1 .bss 	utilityU.a PSMainSide_CreaturePrm.cpp
00016e60 00000c 805069c0  4 @3464 	utilityU.a PSMainSide_CreaturePrm.cpp
00016e6c 000048 805069cc  4 saoVVOutput_direction___Q214JStudio_JStage14TAdaptor_light 	JSystem.a object-light.cpp
00016eb4 0000d0 80506a14  4 saoVVOutput___Q214JStudio_JStage14TAdaptor_actor 	JSystem.a object-actor.cpp
```

In this example, we see a symbol from `utilityU.a PSMainSide_CreaturePrm.cpp`. We know that this file is very close to the _end_ of the link order. Afterwards, there's a symbol from `JSystem.a object-light.cpp`, which is very close to the _beginning_ of the link order.

A file can't be both at the beginning and end of the link order, so it's a strong indication that `saoVVOutput_direction___Q214JStudio_JStage14TAdaptor_light` marks the beginning of the common BSS section.

One other indication from this example is the lack of a `.bss` section symbol from `JSystem.a object-actor.cpp` and any following files in the link order. Section symbols aren't generated for common BSS.

Without a map, it's harder to tell if there's a common BSS section, but guesses can be made. When looking at XREFs in Ghidra, if a symbol is close to the _end_ of `.bss`, but has XREFs from various addresses close to the _beginning_ of `.text`, it could be an indication of common BSS.

For games built with older versions of the linker, the inflation bug (described below) can also be used to detect common BSS.

## Inflation bug

In older versions of the linker (<= GC 2.6?), when calculating the size of common symbols, the linker will accidentally set the size of the first common symbol in a TU to the size of the _entire_ common section in that TU.

Example from Pikmin 2:

```
# Section Addr | Size | Addr | Alignment | Name | File
00017260 000188 80506dc0  4 mPadList__10JUTGamePad 	JSystem.a JUTGamePad.cpp
000173e8 000030 80506f48  4 mPadStatus__10JUTGamePad 	JSystem.a JUTGamePad.cpp
00017418 0000c0 80506f78  4 mPadButton__10JUTGamePad 	JSystem.a JUTGamePad.cpp
000174d8 000040 80507038  4 mPadMStick__10JUTGamePad 	JSystem.a JUTGamePad.cpp
00017518 000040 80507078  4 mPadSStick__10JUTGamePad 	JSystem.a JUTGamePad.cpp
00017558 00000c 805070b8  4 sPatternList__19JUTGamePadLongPress 	JSystem.a JUTGamePad.cpp
```

In this example, `mPadList__10JUTGamePad` is the first common symbol in the TU, and was inflated to include the size of all other common symbols in the TU. In reality, it's only supposed to be `0xC` bytes, given `0x188 - 0x30 - 0xC0 - 0x40 - 0x40 - 0xC`.

This can be useful to determine if symbols are in the same TU without a map: if a `.bss` symbol is much larger than expected, it could be the first common symbol in a TU. One can subtract the sizes of following symbols to find the true size of the symbol, along with the end of the TU's common symbols.

To reproduce this behavior, the `.comment` section must be present in the object. See [`.comment` section](comment_section.md) for more details.

## In this project (menus.rel)

menus.rel's `.bss` ends with a common block from `0xB644` to `0x340DDC` (~3.3 MB). It is reproduced byte-for-byte
(see `config/GYQE01/menus/splits.txt`, `.bss ... common` lines). What was measured with the project's own tools:

- **Pipeline.** The final REL link is `mwldeppc` GC/1.3.2 `-r1` over the individual objects (`build.ninja`, `.plf`
  step), so inflation is per object. (The `-r` `.preplf` step merges everything into one object; there the *first*
  common of the whole module would be inflated by the module's total. It is only used for symbol resolution.)
- **Inflation.** The first common symbol of an object is laid out with the size of the object's whole common block
  (all its commons, alignment included, even ones another object already defined); the others follow it. So a block
  `[s1, s2..sn]` occupies `real(s1) + 2*sum(s2..sn)`. `lbl_2_bss_B644` (a `u32`, `OSGetTick()` in `fn_2_554`) shows
  this: its gap is `0x2314`.
- **Order.** Objects in link order; inside an object, symbol-table order. dtk writes split objects' commons in address
  order. mwcc's order for C is *not* source order (it looked hash-like in tests); check `readelf -s` of the object.
- **Alignment.** Each object's block starts 4-aligned even for `char` commons (mwcc gives arrays COM alignment 4,
  scalars their natural alignment); inside a block, a 1-aligned common can follow at an odd address.
  `lbl_2_bss_33FBF5` (odd address) therefore sits inside the block that starts at `0x33FBCC`, with `align:1` in
  `symbols.txt`.
- **dtk.** `common` on a `.bss` split makes dtk emit `SHN_COMMON` symbols with the `symbols.txt` sizes (use the *real*
  size of a block's first symbol, not the inflated gap) and `align:` as the COM value. Each object can own only one
  contiguous block.
- **C side.** menus compiles with `-common on` (`configure.py`): uninitialised globals become commons, so file-local
  `.bss` must be `static` (as in the original, where only statics sit in the regular `.bss`).
- **objdiff** does not count `SHN_COMMON` symbols, so the 3.3 MB left the menus data total (and data % rose) when
  the region became common.
- **Unknowns.** Only the inflation gaps and references locate block boundaries; where they don't (unlabeled bytes,
  the size of a first symbol), the split chosen is one that reproduces the layout: e.g. `lbl_2_bss_FC68` and
  `lbl_2_bss_33FBF8` are unreferenced block starts, and the last block (`0x340234`) is assigned to `rep_1028.c`
  (not linked) so that the linked `rep_0FD8.c` needs no common definitions.

## In this project (challenge.rel)

challenge.rel's `.bss` ends with a common region `0x472B4`-`0x4C720` (after rep_7BF0's `.bss`). It links byte-for-byte
with four blocks (`config/GYQE01/challenge/splits.txt`, `.bss ... common` lines), using the same inflation rule:

| block | owner (split) | commons, in order (real size) | first symbol's slot |
|---|---|---|---|
| `0x472B4`-`0x477F4` | rep_00B0.c | `472B4` viewer work (0x240), `47674` sound test (0x24), `47698` (0x15C) | 0x240 + 0x24 + 0x15C = 0x3C0 |
| `0x477F4`-`0x49A78` | rep_0138.c | `477F4` (0x2074, unreferenced), `49970` (0x10), `49980` (0x14), `49994` (0xE4) | 0x2074 + 0x108 = 0x217C |
| `0x49A78`-`0x4BC30` | rep_0610.c | `49A78` (0x21B8) | no inflation |
| `0x4BC30`-`0x4C720` | rep_74A0.c | `4BC30` animations (0xAA0 = 85 x 0x20), `4C6F8` resources (0x28) | 0xAA0 + 0x28 = 0xAC8 |

- The block sizes are pinned by the gaps: `472B4` is a 0x240 struct everywhere it is used, so its 0x3C0 gap means
  0x180 of other commons in the same object; `4BC30` is an array of 0x20-byte records, so its 0xAC8 gap is 0xAA0 plus
  the 0x28 of `4C6F8`; the 3D-sound-test params `49970/49980/49994` sit unpadded right after the unlabeled
  `477F4` area, which is exactly that object's inflated first slot.
- The owners are a choice, not evidence: any objects in link order with one block each give the same bytes. They are
  units that are not linked yet (their `.o` comes from dtk), so no C file has to define a common today. When one of
  these units is linked, its C must define those commons (tentative definitions, compiled `-common on`) in the same
  symbol-table order, or the blocks must move to other units. `49A78` (0x21B8, used as a 0x50-byte struct by
  auto_00_00009EA0 and a byte array by rep_02A8) is most likely also an inflated first symbol with already-defined
  commons in its object; one 0x21B8 common reproduces it.
- challenge compiles with `-common on` (`Rel()` in `configure.py`); the linked units' uninitialised globals
  (rep_7920 `lbl_1_bss_47050/47052`, rep_7BA0 `lbl_1_bss_47058`) became `static`, otherwise they turn into commons.
