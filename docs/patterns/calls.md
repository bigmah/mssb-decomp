# Matching patterns: calls

Call arguments, prototypes, sign/zero extension, tail calls, varargs. One pattern per line, so `grep -i <keyword> docs/patterns/*.md` returns whole entries.

- **`li r3, 0` scheduled after the table load, before the store (fn_3_10F564):** store through a typed pointer cast, `*(s8*)(base + off) = table[...]`, instead of indexing a `u8[]`.
- **Calling a stub the original calls with no args:** cast it `((void(*)(void))f)()` so `r3` stays stale.
- **`base + idx*4` with a big field offset, base hoisted before the shift:** write `p = ((u8**)(sym + 0x2C50))[idx];` (cast base+offset, then index) instead of `*(u8**)(sym + idx*4 + 0x2C50)`.
- **State-setup functions on `lbl_803CC1B8`:** `extern u8* lbl_803CC1B8; u8* p = lbl_803CC1B8; fn_80034E20(p, data); ... *(void**)((u8**)&lbl_803CC1B8)[0] = fn;` reproduces the mixed direct/`addi`+`lwz` loads.
- **`add rN, base, off; lwz 8(rN)` (displacement after the add) for `tbl[idx*8 + 8]`:** write `u8* e = tbl; e += idx * 8; p = *(u8**)(e + 8);` (separate pointer, `+=`), not a single expression. Likewise `u8* e = g_X; e += *(s8*)(e + 0x1904) * 2; *(s16*)(e + 0x1898)` re-materializes the base like the original (fn_3_120F5C, fn_3_11F778).
- **Stubs called with fewer args than the real function:** call through a cast (`((void (*)(void))fn_800B0A14_removeQueue)()`), and pass only the args the original sets up (stale `r4` in `fn_80035CA4(5)`).
- **Struct with bitfield for list refcount (fn_3_154238):** `typedef struct { u8 pad0[0xC]; u8* head; u8 pad[4]; u16 hi:4; u16 cnt:12; } H;` then `h->cnt--`; keep `link = &h->head` for the unlink pointer.
- **Second struct-array access that the original re-materialises:** `u8* f; f = g_Fielders; f += idx * 0x268;` (or `f = g_Runners; f += ...`) stops the compiler from CSE-ing with an earlier `g_Fielders + off` (`fn_3_870AC`: arg `*(s16*)(f + 0x178)` after `f += *(s16*)(g_Ball + 0x1B78) * 0x268`).
- **A spare `li r5,0` before a call is not necessarily a third argument:** it can be a zero reused for earlier stores; passing only 2 args matched (fn_3_1536A8 call in fn_3_153F8C).
- **Table lookup of a `rand()` index scheduled before other stores (fn_3_14E9F0):** `u8 k = tbl[(u32)rand() % 23];` as its own statement before the `v.z = v.y = v.x = 0.0f` stores matched; putting the lookup inside the call argument moved the `lis`/`lbz` around.
- **Reads of a global after a call not CSE'd (fn_3_835B0):** use `g_GameLogic[...]`/`*(s32*)(g_GameLogic + 0xC)` directly; a cached `u8* gl = g_GameLogic` made CW reuse `idx*8` across the call.
- **Calling a matched same-file function with more args than it takes:** cast the call (`((void (*)(s32, s32))fn)(0xD, 0)`); a block-scope `extern` with the wider prototype also works.
- **Scalar `extern u8* sym;`** reloads the pointer for every statement, as the original does (fn_2_8C724).
- **Struct-array stride fixes `addi/stbx` vs `mulli/add/stb`:** `((E28*)*(u8**)(base + OFF))[i].f = 0;` with a typedef'd struct of the element size matched where `p[i * 0x28 + 0x26]` did not (fn_3_116B38).
- **`(tbl + a*4)[b]` instead of `tbl[a*4 + b]`:** keeps the original's `lbz b` before `lbz a` and `lbzx` shape for 2-D byte tables. `s32 chance` (not `u8`) avoids the extra `clrlwi` when later `+= s8`.
- **Struct field signedness is a free parameter:** a `lha` where the header says `u16`/`u8` means change the shared header field to `s16`/`s8` (fn_3_215AC, fn_3_20CEC); check no other file uses it.
- **u8 value shared between compare and store:** `q[0x15] == (u32)(u8)((w + 1) % 14)` with a plain `% 14` store gives one shared `clrlwi` result in r0 (`fn_3_8B258`); `(u8)` on both sides or on neither does not.
- **String args to `OSPanic`:** use `extern char lbl_3_rodata_XXXX[]` per string symbol (names in the asm reloc) instead of literals, or the reloc names differ (`fn_3_90064`).
- **`*(p += OFF)`** gives a load with an offset followed by `addi` on the pointer (`fn_3_49EA8`). Re-deriving `g_Fielders` per access via a padded `typedef struct { u8 b[0x268]; } FldT;` array also matched.
- **`addi r0, idx, K; lbzx` from a pointer-in-global:** `u8* menu = g[0]; u8* entry = menu + idx * 0x34; entry[K]` (separate base and entry pointers); `g[0][idx*0x34+K]` folds K into the displacement (fn_2_4668C).
- **Extra `extsh r3,r3` between an s16-returning call and an s16-param call (fn_2_607DC):** the result went through an `s32` local first (`s32 total = fn_8006C268(...); fn_8006C100(total)`); no prototype change needed.
