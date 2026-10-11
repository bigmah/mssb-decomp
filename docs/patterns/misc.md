# Matching patterns: misc

Everything else. One pattern per line, so `grep -i <keyword> docs/patterns/*.md` returns whole entries.

- **Shared scratchpad dir:** parallel agents share one scratchpad directory; use a private subdirectory for variant files or `a.c` gets clobbered.
- **`fnvariants` scores are diff-line counts: lower is better** (0/OK = match). Sort ascending.
- **Dead stack copy of a rodata triple (fn_3_FD51C):** `V3U v = *(V3U*)rodata; *(V3U*)(p+0xC) = v;` reproduces lwz once + both stores + the stack store. A `u32 t[3]` dead copy is optimized away.
- **`(u32)rand() % 23`** gives `mulhwu`, `rand() % 23` gives signed `mulhw`.
- **Sum of scaled terms (`n*0x18 + n*4 + n*4 + n*2`) reassociates unpredictably:** permute the terms AND mix `* k` with `<< k`; `(n << 2) + (n << 1) + (n << 2) + n * 0x18` reproduced the original schedule in fn_3_FA3C0.
- **Clone families (menus rep_0788, rep_0B08):** many functions are byte-identical bodies (e.g. 14 state-machine functions of 436 B, `fn_2_6C020` == `fn_2_6F78C`). Group unmatched functions by an md5 of label-normalised asm; one match gives the whole family. Jump-table clones can differ only in the table, so compare `jumptable_*` contents too (`fndiff` never says MATCH for them; trust report.json).
- **`opt_propagation off` plus `s32 one = 1;`** keeps a hoisted `li rN,1` for several stores and a `slwi` index (menus fn_2_52CC).
- **Symbol splits fix pooled-base reloc differences:** when a `sym+0xC` reloc is folded by CW but the original has a separate symbol, split it in symbols.txt (menus fn_2_B508, fn_2_6784).
- **Never let `fnvariants` hit the shell timeout:** an interrupted run leaves a variant in the source; run it in the background.
- **Stale-r3 result:** `sndFXCtrl(vid, 0x5B, x)` after `sndFXStartEx(...)` passes the first call result.
- **`targsupp` TRK stubs show 0% (one `ASM` function with `entry` labels; separate C `ASM` functions get padded by `-func_align 16` or dead-stripped):** write it as `targsupp.s` with `.balign 16` and four `.fn` blocks; mwld keeps them and the shasum passes.
- **`x = tbl[off + base[idx2]++]` as one statement** gives the original schedule; separate `n = base[..]; base[..] = n + 1` does not (fn_3_10768C).
- **`cmplwi` on a reused `flags & 4` test, and a re-extended `count` compare (fn_2_46D94):** the flags param is `u32` (an `s16` adds `extsh`, `s32` gives `cmpwi`); `lha; extsh rC,count; addi; extsh; sth; cmpw` is `if (++*sel >= count)`, not `*sel = v = (s16)(*sel + 1); if (v >= count)`.
- **`lbl_2_bss_X + 0xA/0xC/0x10` offsets off an unrelated bss symbol (fn_2_4917C):** these are file-static variables addressed from the unit's .bss base, which the original keeps in a saved register (`addi r31, base@l`). An `extern` struct (here `lbl_2_bss_55C0`) is correct C but reloads the address (78%).
