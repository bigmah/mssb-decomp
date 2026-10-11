# Matching patterns: globals

Globals, arrays, struct fields, pointer arithmetic, sda/lis addressing, typed externs. One pattern per line, so `grep -i <keyword> docs/patterns/*.md` returns whole entries.

- **Symbol names must agree.** A header `extern` name and `symbols.txt` have to use the same name. Otherwise the diff shows a relocation mismatch even when the code is right. Rename in `symbols.txt` when the header name is better.
- **Pointer to a `s32` slot incremented in place (`lwzu`, fn_3_9E7D4):** index the array in each use, `((s32*)(g + 0xDC))[i]`, instead of caching `s32* p`.
- **`addi rX, base, K; add rX, rX, idx` (const first, index second):** the compiler folds `base[K + idx*n]` into `add; lbz K(..)`. Assign the const-offset pointer to a variable and add the index afterwards (`e = (T*)(d + 0x798); e += idx;`).
- **A `.sdata2`/`.rodata` symbol used by a function needs a split** (`.sdata2 start:... end:...` in `splits.txt`) before the report counts it as matched (see `Musyx/snd_math.c`).
- **Hoisted struct-element address before stores (fn_3_F65C8):** when the original computes `base + idx*0xE8` (lwz base, mulli, add) before some stores but loads the field after them, take the element pointer in a local at the top (`StadObj78* so = &((StadObj78**)sym)[0][idx];` ... `o = so->w78;`).
- **Rodata symbol names are not checked by report.json:** a function using `lbl_2_rodata_1080` instead of the original `1078` still scores 100%. After each match compare the `@l`/`@ha` relocs against the original asm.
- **`(tbl + a * 4)[b]` instead of `tbl[a * 4 + b]`** gives `lbzx` with the scaled base as the first operand (fn_3_21768).
- **`addi rB, sym@l` once, then `addi r3, rB, 0x30; addi r3, r3, 0x20` (fn_800097A0):** the original addresses several data objects of its own unit through one pooled base register. Not reproducible while that unit's `.data` is unsplit; commit as equivalent.
