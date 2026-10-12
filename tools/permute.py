#!/usr/bin/env python3
"""Random search over source-level rewrites of a function until its asm matches.

A small, MWCC-friendly cousin of decomp-permuter that works on the C text directly
(no preprocessing). Starting from the function as written (a `#if NONMATCHING`
function is taken out of its block first), each worker applies 1-3 random rewrites,
compiles the unit as nmpromote does (temp copy next to the source, normal flags),
and scores it with fndiff's normalisation (differing asm lines; 0 == match). Better
or equal candidates are kept (a random walk over plateaus), so rewrites combine.

Rewrites: swap adjacent statements; reorder declarations; split / merge a
declaration's initializer; inline a single-use temp; `!x`/`x == 0`, `x != 0`/`x`,
`a != b`/`!(a == b)` flips; swapped operands of ==, !=, +, *, &, |, <, >; `x += y`
/ `x = x + y`; for <-> while; if/else branch swap with the condition negated.

    python3 tools/permute.py fn_3_16C878 [--budget 120] [-j 12]
    python3 tools/permute.py --all --min-pct 97 --budget 60 [--promote]

Matches are written to build/permute/<fn>.c (whole function text). --promote puts
the match into the source and runs nmpromote's checks (full ninja: 100% in
report.json, no regressions, litcheck) and commits `match <fn>`. Without it, review
build/permute/<fn>.c and paste it in yourself (then check with fndiff).
"""
import argparse, json, multiprocessing as mp, os, random, re, sys, tempfile, time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import nmpromote as nmp  # noqa: E402

ROOT = nmp.ROOT
OUT = ROOT / "build" / "permute"

# ------------------------------------------------------------------ locating the function


def find_fn(text: str, fn: str):
    """(start, end) character span of fn's definition in text (end after the `}`)."""
    for m in nmp.FN_START.finditer(text):
        if m.group(1) == fn:
            close = nmp.brace_end(text, m.end() - 1)
            if close > 0:
                return m.start(), close + 1
    return None


def base_text(src: str, fn: str):
    """The unit source with fn outside any NONMATCHING block, and fn's span in it."""
    lines = (ROOT / src).read_text(errors="replace").split("\n")
    block = next((b for b in nmp.parse_blocks(lines) if not b["has_else"]
                  and any(f[0] == fn for f in b["funcs"])), None)
    if block:
        lines = nmp.promote_lines(lines, block, fn)
    text = "\n".join(lines)
    span = find_fn(text, fn)
    return (text, span) if span else (None, None)


# ------------------------------------------------------------------ rewrites

IDENT = r"[A-Za-z_]\w*"
OPERAND = r"(?:[A-Za-z_][\w.]*(?:->[\w.]+)*(?:\[[^\[\]]*\])?|\d+(?:\.\d*)?f?|0x[0-9A-Fa-f]+)"
STMT_SKIP = re.compile(r"^\s*(return|break|continue|goto|case|default|}|{|#|//|else)\b|[{}]\s*$")
DECL_RE = re.compile(r"^(\s+)((?:const\s+|unsigned\s+|signed\s+|struct\s+|volatile\s+)*"
                     r"[A-Za-z_]\w*[\s\*]+)(\w+)((?:\[[^\]]*\])*)\s*(=\s*(.+))?;\s*$")
KEYWORDS = {"return", "goto", "case", "else", "if", "while", "for", "do", "switch", "break", "continue"}


def body_lines(fn_text: str) -> list:
    return fn_text.split("\n")


def is_simple_stmt(l: str) -> bool:
    s = l.strip()
    return (s.endswith(";") and not STMT_SKIP.search(l) and not s.startswith(("for", "if", "while"))
            and "{" not in s and "}" not in s)


def indent(l: str) -> int:
    return len(l) - len(l.lstrip())


def is_decl(l: str) -> bool:
    m = DECL_RE.match(l)
    return bool(m) and m.group(2).split()[0] not in KEYWORDS


def decl_range(L: list):
    """Indices of the declarations at the top of the function body."""
    i = next((k for k, l in enumerate(L) if l.rstrip().endswith("{")), 0) + 1
    out = []
    while i < len(L) and (is_decl(L[i]) or not L[i].strip()):
        if L[i].strip():
            out.append(i)
        i += 1
    return out


def m_swap_stmts(L, rnd):
    decls = set(decl_range(L))
    cand = [i for i in range(len(L) - 1) if i not in decls and i + 1 not in decls
            and is_simple_stmt(L[i]) and is_simple_stmt(L[i + 1]) and indent(L[i]) == indent(L[i + 1])]
    if not cand:
        return None
    i = rnd.choice(cand)
    L[i], L[i + 1] = L[i + 1], L[i]
    return L


def m_move_stmt(L, rnd):
    """Move a simple statement up or down past up to 3 simple statements."""
    decls = set(decl_range(L))
    cand = [i for i in range(len(L)) if i not in decls and is_simple_stmt(L[i])]
    if not cand:
        return None
    i = rnd.choice(cand)
    j = i
    step = rnd.choice((-1, 1))
    for _ in range(rnd.randint(1, 3)):
        k = j + step
        if 0 <= k < len(L) and k not in decls and is_simple_stmt(L[k]) and indent(L[k]) == indent(L[i]):
            j = k
        else:
            break
    if j == i:
        return None
    line = L.pop(i)
    L.insert(j, line)
    return L


def m_swap_decls(L, rnd):
    d = decl_range(L)
    if len(d) < 2:
        return None
    i, j = rnd.sample(d, 2)
    L[i], L[j] = L[j], L[i]
    return L


def m_split_init(L, rnd):
    d = decl_range(L)
    cand = [i for i in d if DECL_RE.match(L[i]).group(5) and "{" not in L[i]]
    if not cand:
        return None
    i = rnd.choice(cand)
    m = DECL_RE.match(L[i])
    ind, ty, name, arr, _, init = m.groups()
    L[i] = f"{ind}{ty}{name}{arr};"
    L.insert(d[-1] + 1, f"{ind}{name} = {init};")
    return L


def m_merge_init(L, rnd):
    d = decl_range(L)
    if not d:
        return None
    first = d[-1] + 1
    while first < len(L) and not L[first].strip():
        first += 1
    if first >= len(L):
        return None
    m = re.match(rf"^\s+({IDENT}) = (.+);\s*$", L[first])
    if not m:
        return None
    for i in d:
        dm = DECL_RE.match(L[i])
        if dm and dm.group(3) == m.group(1) and not dm.group(5) and not dm.group(4):
            L[i] = f"{dm.group(1)}{dm.group(2)}{dm.group(3)} = {m.group(2)};"
            del L[first]
            return L
    return None


def m_inline_temp(L, rnd):
    """x = expr; ... single use of x ... -> use (expr) there."""
    text = "\n".join(L)
    cand = []
    for i, l in enumerate(L):
        m = re.match(rf"^\s+({IDENT}) = ([^;]+);\s*$", l)
        if m and m.group(1) not in KEYWORDS:
            cand.append((i, m.group(1), m.group(2)))
    rnd.shuffle(cand)
    for i, name, expr in cand[:6]:
        uses = [k for k, l in enumerate(L) if k != i and re.search(rf"\b{name}\b", l)
                and not is_decl(l)]
        if len(uses) != 1 or uses[0] < i or len(re.findall(rf"\b{name}\b", L[uses[0]])) != 1:
            continue
        if re.search(rf"\b{name}\s*(=[^=]|\+\+|--|\+=|-=)", L[uses[0]]):
            continue
        k = uses[0]
        L[k] = re.sub(rf"\b{name}\b", f"({expr})", L[k])
        del L[i]
        for j, l in enumerate(L):
            dm = DECL_RE.match(l)
            if dm and dm.group(3) == name and not dm.group(5) and "\n".join(L).count(name) == 1:
                del L[j]
                break
        return L
    return None


REGEX_REWRITES = [
    (rf"\bif \(!({OPERAND})\)", r"if (\1 == 0)"),
    (rf"\bif \(({OPERAND}) == 0\)", r"if (!\1)"),
    (rf"\b(if|while) \(({OPERAND}) != 0\)", r"\1 (\2)"),
    (rf"\b(if|while) \(({OPERAND})\)", r"\1 (\2 != 0)"),
    (rf"\b(if|while) \(({OPERAND}) != ({OPERAND})\)", r"\1 (!(\2 == \3))"),
    (rf"\b(if|while) \(!\(({OPERAND}) == ({OPERAND})\)\)", r"\1 (\2 != \3)"),
    (rf"({OPERAND}) (==|!=|\+|\*|&|\||\^) ({OPERAND})", r"\3 \2 \1"),
    (rf"({OPERAND}) < ({OPERAND})", r"\2 > \1"),
    (rf"({OPERAND}) > ({OPERAND})", r"\2 < \1"),
    (rf"({OPERAND}) <= ({OPERAND})", r"\2 >= \1"),
    (rf"({OPERAND}) >= ({OPERAND})", r"\2 <= \1"),
    (rf"^(\s+)({OPERAND}) (\+|-|\*|\||&|\^)= ([^;]+);", r"\1\2 = \2 \3 \4;"),
    (rf"^(\s+)({OPERAND}) = \2 (\+|-|\*|\||&|\^) ([^;]+);", r"\1\2 \3= \4;"),
    (rf"^(\s+)({IDENT})\+\+;", r"\1\2 += 1;"),
    (rf"^(\s+)({IDENT}) \+= 1;", r"\1\2++;"),
]


def m_regex(L, rnd):
    order = list(range(len(REGEX_REWRITES)))
    rnd.shuffle(order)
    for r in order:
        pat, rep = REGEX_REWRITES[r]
        hits = [(i, m) for i, l in enumerate(L) if not l.lstrip().startswith("//")
                for m in re.finditer(pat, l, re.M)]
        if not hits:
            continue
        i, m = rnd.choice(hits)
        L[i] = L[i][:m.start()] + m.expand(rep) + L[i][m.end():]
        return L
    return None


def block_end(L, i):
    """Index of the line closing the `{` that ends line i."""
    depth = 0
    for k in range(i, len(L)):
        depth += L[k].count("{") - L[k].count("}")
        if depth == 0 and k > i or (depth <= 0 and k > i):
            return k
    return None


def m_for_while(L, rnd):
    cand = [i for i, l in enumerate(L) if re.match(r"^\s+(for \(.*;.*;.*\)|while \(.*\)) \{\s*$", l)]
    if not cand:
        return None
    i = rnd.choice(cand)
    ind = L[i][:indent(L[i])]
    m = re.match(r"^\s+for \(([^;]*);\s*([^;]*);\s*([^)]*(?:\([^)]*\))?[^)]*)\) \{\s*$", L[i])
    if m:
        end = block_end(L, i)
        if end is None or any("continue" in l for l in L[i:end]):
            return None
        init, cond, inc = m.groups()
        L[end:end] = [f"{ind}    {inc};"] if inc.strip() else []
        L[i] = f"{ind}while ({cond or '1'}) {{"
        if init.strip():
            L.insert(i, f"{ind}{init};")
        return L
    m = re.match(r"^\s+while \((.*)\) \{\s*$", L[i])
    if m:
        L[i] = f"{ind}for (; {m.group(1)};) {{"
        return L
    return None


def m_if_else(L, rnd):
    cand = []
    for i, l in enumerate(L):
        m = re.match(r"^(\s+)if \((.*)\) \{\s*$", l)
        if not m:
            continue
        end = block_end(L, i)
        if end is None or L[end].strip() != "} else {":
            continue
        end2 = block_end(L, end)
        if end2 is None or L[end2].strip() != "}":
            continue
        cand.append((i, end, end2, m.group(1), m.group(2)))
    if not cand:
        return None
    i, e1, e2, ind, cond = rnd.choice(cand)
    a, b = L[i + 1:e1], L[e1 + 1:e2]
    L[i:e2 + 1] = [f"{ind}if (!({cond})) {{"] + b + [f"{ind}}} else {{"] + a + [f"{ind}}}"]
    return L


MUTATIONS = [(m_swap_stmts, 4), (m_move_stmt, 3), (m_swap_decls, 3), (m_split_init, 1),
             (m_merge_init, 1), (m_inline_temp, 1), (m_regex, 4), (m_for_while, 1), (m_if_else, 1)]


def mutate(fn_text: str, rnd: random.Random) -> str:
    L = fn_text.split("\n")
    applied = 0
    for _ in range(rnd.choice((1, 1, 1, 2, 2, 3))):
        for _try in range(8):
            f = rnd.choices([m for m, _ in MUTATIONS], [w for _, w in MUTATIONS])[0]
            r = f(list(L), rnd)
            if r is not None and r != L:
                L = r
                applied += 1
                break
    return "\n".join(L) if applied else None


# ------------------------------------------------------------------ search


def worker(args):
    src, fn, unit, prefix, fn_text, suffix, base_score, deadline, seed, found, best_val, lock = args
    rnd = random.Random(seed)
    cur, cur_score = fn_text, base_score
    best, best_score = fn_text, base_score
    tried = 0
    seen = set()
    with tempfile.TemporaryDirectory() as wd:
        while time.time() < deadline and not found.is_set():
            start = cur if rnd.random() < 0.8 else best
            cand = mutate(start, rnd)
            if cand is None or cand in seen:
                continue
            seen.add(cand)
            tried += 1
            obj = nmp.compile_text(src, prefix + cand + suffix, wd)
            if obj is None:
                continue
            sc = nmp.score_obj(obj, unit, fn, wd)
            for p in Path(obj).parent.iterdir():
                p.unlink()
            if sc < 0:
                continue
            if sc <= cur_score:
                cur, cur_score = cand, sc
            if sc < best_score:
                best, best_score = cand, sc
                with lock:
                    if sc < best_val.value:
                        best_val.value = sc
                        OUT.mkdir(parents=True, exist_ok=True)
                        (OUT / f"{fn}.best.c").write_text(cand + "\n")
                if sc == 0:
                    (OUT / f"{fn}.c").write_text(cand + "\n")
                    found.set()
    return best_score, tried


def permute(src: str, fn: str, budget: float, jobs: int, quiet=False):
    """Returns (best score, matching function text or None, candidates tried)."""
    unit = nmp.units_by_source().get(src)
    text, span = base_text(src, fn)
    if not unit or not text:
        return None, None, 0
    prefix, fn_text, suffix = text[:span[0]], text[span[0]:span[1]], text[span[1]:]
    with tempfile.TemporaryDirectory() as wd:
        obj = nmp.compile_text(src, text, wd)
        base = nmp.score_obj(obj, unit, fn, wd) if obj else -2
    if base < 0:
        return base, None, 0
    if base == 0:
        return 0, fn_text, 0
    (OUT / f"{fn}.c").unlink(missing_ok=True)
    mgr = mp.Manager()
    found, lock, best_val = mgr.Event(), mgr.Lock(), mgr.Value("i", base)
    deadline = time.time() + budget
    seed0 = random.randrange(1 << 30)
    with mp.Pool(jobs) as pool:
        res = pool.map(worker, [(src, fn, unit, prefix, fn_text, suffix, base, deadline, seed0 + k,
                                 found, best_val, lock) for k in range(jobs)])
    best = min(r[0] for r in res)
    tried = sum(r[1] for r in res)
    match = (OUT / f"{fn}.c").read_text().rstrip("\n") if found.is_set() else None
    if not quiet:
        print(f"{fn}: base {base} -> best {best} ({tried} candidates)"
              + (f"; MATCH written to {OUT / (fn + '.c')}" if match else
                 f"; best in {OUT / (fn + '.best.c')}" if best < base else ""), flush=True)
    return best, match, tried


# ------------------------------------------------------------------ decomp-permuter backend
#
# decomp-permuter (github.com/simonlindholm/decomp-permuter) does the AST-level search.
# It is installed into build/decomp-permuter on first use. Its inputs, in build/permute/<fn>/:
#   base.c       the unit preprocessed by MWCC itself (-EP), with fn outside its block
#   compile.sh   -> `permute.py --cc`: MWCC with the unit's flags, then fn's asm alone
#                   (fndiff's anonymisation) reassembled into a one-function object
#   target.o     the target's fn, through the same reassembly
# so permuter's objdump scoring sees exactly what fndiff compares.

PERMUTER = ROOT / "build" / "decomp-permuter"
PERMUTER_URL = "https://github.com/simonlindholm/decomp-permuter"
PERMUTER_REV = "8556c81d80d1c1af98a858c8f4dc951357f29139"
AS = ROOT / "build" / "binutils" / "powerpc-eabi-as"
OBJDUMP = ROOT / "build" / "binutils" / "powerpc-eabi-objdump"
# passes that can produce code which only matches by accident of the 32-bit ABI
# (pointer <-> int types, masks, aliasing): the port must not inherit those
PERMUTER_WEIGHTS = {"perm_randomize_internal_type": 0, "perm_randomize_external_type": 0,
                    "perm_randomize_function_type": 0, "perm_cast_simple": 0, "perm_add_mask": 0,
                    "perm_alias_array": 0, "perm_xor_zero": 0, "perm_mult_zero": 0,
                    "perm_float_literal": 0, "perm_pad_var_decl": 0,
                    # reads an uninitialised variable (`if (x) {}`): undefined behaviour in the port
                    "perm_var_cond_block": 0}


def ensure_permuter():
    py = PERMUTER / ".venv" / "bin" / "python"
    if py.exists():
        return py
    import subprocess as sp
    if not (PERMUTER / "permuter.py").exists():
        sp.run(["git", "clone", "-q", PERMUTER_URL, str(PERMUTER)], check=True)
        sp.run(["git", "-C", str(PERMUTER), "checkout", "-q", PERMUTER_REV], check=True)
    sp.run([sys.executable, "-m", "venv", str(PERMUTER / ".venv")], check=True)
    sp.run([str(py), "-m", "pip", "install", "-q", "toml", "Levenshtein"], check=True)
    return py


def fn_object(asm: Path, fn: str, literals: set, out: Path) -> bool:
    """Assemble fn alone from a dtk disassembly, anonymised as fndiff does."""
    import subprocess as sp
    lit_re = re.compile(r"\b(?:" + "|".join(map(re.escape, sorted(literals))) + r")\b") if literals else None
    body, inside = [], False
    for line in asm.read_text().splitlines():
        if line.startswith(f".fn {fn},"):
            inside = True
        if inside:
            l = nmp.fndiff.ANON_DATA_RE.sub("DATA", nmp.fndiff.COMMENT_RE.sub("", line))
            body.append(lit_re.sub("DATA", l) if lit_re else l)
            if line.startswith(f".endfn {fn}"):
                break
    if not body:
        return False
    s = out.with_suffix(".s")
    s.write_text('.include "macros.inc"\n.text\n' + "\n".join(body) + "\n")
    r = sp.run([str(AS), "-mgekko", "-I", str(ROOT / "build/GYQE01/include"), "-o", str(out), str(s)],
               capture_output=True, text=True)
    return r.returncode == 0


def preprocess(src: str, text: str):
    """`text` (a version of `src`) preprocessed by MWCC, in a form pycparser accepts."""
    import subprocess as sp
    cmd = nmp.compile_cmd(src)
    srcp = Path(src)
    tmp_rel = str(srcp.with_name(f"{srcp.stem}.nmtmp{os.getpid()}_pp.c"))
    (ROOT / tmp_rel).write_text(text)
    try:
        c = re.sub(r" -o \S+", "", cmd).replace(f" -c {src}", f" -EP {tmp_rel}")
        r = sp.run(c, shell=True, cwd=ROOT, capture_output=True)
    finally:
        (ROOT / tmp_rel).unlink(missing_ok=True)
    if r.returncode != 0:
        return None
    out = r.stdout.decode("cp932", errors="replace").replace("\r", "")
    out = re.sub(r"^#pragma simple_prepdump on\n", "", out, flags=re.M)
    # pycparser does not know MWCC's __declspec / __attribute__ (they only matter for data
    # placement, which the one-function comparison does not see)
    out = re.sub(r"__declspec\s*\((?:[^()]|\([^()]*\))*\)", "", out)
    out = re.sub(r"__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)", "", out)
    out, blocks = hide_asm(out)
    # MWCC's `T var : 0xADDR;` -> permuter's FIXEDADDR spelling
    out = re.sub(r"^([^=;\n]*[\w\]]) : (0x[0-9A-Fa-f]+);", r"\1 = FIXEDADDR(\2);", out, flags=re.M)
    return out, blocks


ASM_CALL = "__permute_asm"


def hide_asm(text: str):
    """Replace MWCC inline `asm { ... }` blocks with `__permute_asm(N);` (and whole
    `asm` function definitions with a placeholder declaration) so pycparser can parse
    the file (only the parse needs this: compile.sh compiles the real source)."""
    blocks, out, i = [], [], 0
    pat = re.compile(r"^(?:[^\n;{}]*\basm\b[^\n;{}]*\([^;{}]*\)\s*\{)|\basm\s*\{", re.M)
    while True:
        m = pat.search(text, i)
        if not m:
            out.append(text[i:])
            break
        close = nmp.brace_end(text, m.end() - 1)
        if close < 0:
            out.append(text[i:])
            break
        out.append(text[i:m.start()])
        blocks.append(text[m.start():close + 1])
        n = len(blocks) - 1
        if m.group(0).lstrip().startswith("asm") and m.group(0).rstrip().endswith("{") and "(" not in m.group(0):
            out.append(f"{ASM_CALL}({n});")
        else:
            out.append(f"extern int {ASM_CALL}_def{n};")
        i = close + 1
    if blocks:
        out.insert(0, f"void {ASM_CALL}(int);\n")
    return "".join(out), blocks


MARKER = "int __permute_fn_marker;"


def strip_comments(text: str) -> str:
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    return re.sub(r"//[^\n]*", "", text)


def cc_main(src: str, fn: str, d: str, c_in: str, o_out: str) -> int:
    """compile.sh body: take fn from the candidate (pycparser output, macros unexpanded),
    put it into the real source (orig.c) and compile that like the build does, then
    reassemble fn's asm alone."""
    cand = Path(c_in).read_text()
    span = find_fn(cand, fn)
    if not span:
        return 1
    text = (Path(d) / "orig.c").read_text().replace(MARKER, cand[span[0]:span[1]], 1)
    with tempfile.TemporaryDirectory() as wd:
        obj = nmp.compile_text(src, text, wd)
        if obj is None:
            return 1
        s = Path(wd) / "ours.s"
        nmp.fndiff.disasm(obj, s)
        lits = set((Path(d) / "literals.txt").read_text().split())
        return 0 if fn_object(s, fn, lits, Path(o_out)) else 1


C_WORDS = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum",
           "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed",
           "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while",
           "inline"}


def macro_decls(src: str, orig: str, pp_full: str, fn: str, fn_text: str):
    """Declarations that let pycparser and permuter's type inference treat the macros
    fn uses as variables / functions of the type of their expansion. None if a macro
    cannot be handled (the caller then falls back to the expanded function)."""
    if str(PERMUTER) not in sys.path:
        sys.path.insert(0, str(PERMUTER))
    from src.ast_util import parse_c  # noqa: E402  (decomp-permuter)
    from src.ast_types import build_typemap, expr_type, set_decl_name
    from perm_pycparser import c_ast as ca, c_generator
    import copy

    body = strip_comments(fn_text)
    probes = []  # (name, invocation, is_function_like)
    for name in sorted(set(re.findall(r"\b[A-Za-z_]\w*\b", body)) - C_WORDS):
        m = re.search(rf"\b{name}\s*\(", body)
        if m:
            close = nmp.brace_end(body.replace("(", "{").replace(")", "}"), m.end() - 1)
            probes.append((name, body[m.start():close + 1] if close > 0 else name, True))
        probes.append((name, name, False))
    text = orig + "\n" + "\n".join(f"__permute_probe_{k} {inv} __permute_end" for k, (_, inv, _) in enumerate(probes)) + "\n"
    pp = preprocess(src, text)
    if pp is None:
        return None
    exp = {int(m.group(1)): m.group(2).strip()
           for m in re.finditer(r"^__permute_probe_(\d+) ?(.*?) ?__permute_end$", pp[0], re.M)}
    macros = {}
    for k, (name, inv, fnlike) in enumerate(probes):
        e = exp.get(k)
        if e is None or e == inv or name in macros:
            continue
        macros[name] = (fnlike, e)
    if not macros:
        return ""
    # type each expansion inside (a copy of) the expanded function, so locals resolve
    span = find_fn(pp_full, fn)
    if not span:
        return None
    fn_exp = pp_full[span[0]:span[1]]
    names = list(macros)
    probe_fn = fn_exp[:fn_exp.rfind("}")] + "".join(f"({macros[n][1]});\n" for n in names) + "}\n"
    try:
        ast = parse_c(pp_full[:span[0]] + probe_fn + pp_full[span[1]:])
    except Exception:
        return None
    fdef = next(x for x in ast.ext if isinstance(x, ca.FuncDef) and x.decl.name == fn)
    typemap = build_typemap(ast, fdef)
    stmts = fdef.body.block_items[-len(names):]
    decls = []
    gen = c_generator.CGenerator()
    for n, st in zip(names, stmts):
        try:
            t = copy.deepcopy(expr_type(st, typemap))
        except Exception:
            t = ca.TypeDecl(None, [], None, ca.IdentifierType(["int"]))
        if macros[n][0]:
            t = ca.FuncDecl(None, t)
        d = ca.Decl(n, [], [], ["extern"], [], [], t, None, None, None)
        set_decl_name(d)
        decls.append(gen.visit(d) + ";")
    return "\n".join(decls) + "\n"


def setup_permuter_dir(src: str, fn: str):
    """build/permute/<fn>/ ready for permuter.py, or None (with the reason printed)."""
    import shutil
    unit = nmp.units_by_source().get(src)
    text, span = base_text(src, fn)
    if not unit or not text:
        print(f"{fn}: not found")
        return None
    # The function itself stays as written (macros unexpanded, so a match keeps EA_TASK,
    # NULL, OSRoundUp32B... instead of their expansions): the rest of the unit is
    # preprocessed around a marker, and compile.sh splices the candidate back into orig.c.
    fn_text = text[span[0]:span[1]]
    if re.search(r"^\s*#", fn_text, re.M):
        print(f"{fn}: preprocessor lines inside the function")
        return None
    orig = text[:span[0]] + MARKER + text[span[1]:]
    pp = preprocess(src, orig)
    if pp is None or pp[0].count(MARKER) != 1:
        print(f"{fn}: preprocessing failed")
        return None
    full = preprocess(src, text)
    decls = macro_decls(src, orig, full[0], fn, fn_text) if full else None
    if decls is None:
        # fall back to the expanded function (a match then needs its macros put back by hand)
        print(f"{fn}: macros kept expanded", flush=True)
        if not full:
            return None
        pp = full[0]
    else:
        pp = pp[0].replace(MARKER, decls + strip_comments(fn_text))
    d = OUT / fn
    shutil.rmtree(d, ignore_errors=True)
    d.mkdir(parents=True)
    (d / "base.c").write_text(pp)
    (d / "orig.c").write_text(orig)
    with tempfile.TemporaryDirectory() as wd:
        ts, lits = nmp.target_asm(unit, wd)
        (d / "literals.txt").write_text("\n".join(sorted(lits)) + "\n")
        if not fn_object(ts, fn, lits, d / "target.o"):
            print(f"{fn}: could not reassemble the target")
            return None
    nmp._TARGETS.clear()
    (d / "compile.sh").write_text(
        f'#!/bin/sh\nexec "{sys.executable}" "{ROOT / "tools/permute.py"}" --cc "{src}" "{fn}" "{d}" "$1" "$3"\n')
    (d / "compile.sh").chmod(0o755)
    weights = "\n".join(f"{k} = {v}" for k, v in PERMUTER_WEIGHTS.items())
    (d / "settings.toml").write_text(
        f'func_name = "{fn}"\ncompiler_type = "mwcc"\n'
        f'objdump_command = "{OBJDUMP} -dr -EB -mpowerpc -M broadway"\n\n[weight_overrides]\n{weights}\n')
    return d


def permute_ext(src: str, fn: str, budget: float, jobs: int):
    """Run decomp-permuter on fn. Returns (best score, matching fn text or None).
    Scores are permuter's (weighted), not fndiff line counts."""
    import signal, subprocess as sp
    py = ensure_permuter()
    d = setup_permuter_dir(src, fn)
    if not d:
        return None, None
    p = sp.Popen([str(py), str(PERMUTER / "permuter.py"), str(d), "-j", str(jobs), "--stop-on-zero",
                  "--better-only", "--quiet"], cwd=d, stdout=sp.PIPE, stderr=sp.STDOUT, text=True,
                 start_new_session=True)
    try:
        log, _ = p.communicate(timeout=budget)
    except sp.TimeoutExpired:
        os.killpg(p.pid, signal.SIGINT)
        try:
            log, _ = p.communicate(timeout=20)
        except sp.TimeoutExpired:
            os.killpg(p.pid, signal.SIGKILL)
            log, _ = p.communicate()
    (d / "permuter.log").write_text(log or "")
    m = re.search(r"base score = (\d+)", log or "")
    base = int(m.group(1)) if m else None
    outs = sorted(((int(o.name.split("-")[1]), o) for o in d.glob("output-*-*")), key=lambda t: t[0])
    best = outs[0][0] if outs else base
    match = None
    for score, o in outs:
        if score != 0:
            break
        cand = (o / "source.c").read_text()
        span = find_fn(cand, fn)
        if span:
            match = tidy(cand[span[0]:span[1]])
            break
    print(f"{fn}: permuter base {base} -> best {best}"
          + (f"; MATCH in {outs[0][1]}" if match else ""), flush=True)
    return best, match


def tidy(fn_text: str) -> str:
    """Re-indent pycparser output in the project's style (K&R braces, 4 spaces)."""
    raw = [l.strip() for l in fn_text.split("\n") if l.strip()]
    lines = []
    for l in raw:
        if l == "{" and lines and not lines[-1].endswith((";", "{", "}")):
            lines[-1] += " {"
        elif lines and lines[-1] == "}" and (l.startswith("else") or l.startswith("while")):
            lines[-1] += " " + l
        elif lines and lines[-1].endswith("} else") and l.startswith("if "):
            lines[-1] += " " + l
        else:
            lines.append(l)
    out, depth = [], 0
    for l in lines:
        if l.startswith("}"):
            depth -= 1
        label = re.match(r"(case\b.*|default\s*):$", l)
        out.append("    " * (depth - 1 if label else depth) + l)  # labels at the switch's level
        if l.endswith("{"):
            depth += 1
    # blank line after the declarations
    k = 1
    while k < len(out) and re.match(r"^    [A-Za-z_][\w\s\*]*\b\w+(\[[^\]]*\])*( = [^;]*)?;$", out[k]) \
            and not re.match(r"^    (return|goto|break|continue)\b", out[k]):
        k += 1
    if 1 < k < len(out):
        out.insert(k, "")
    text = "\n".join(out)
    text = re.sub(r"\((\+\+|--)(\w+)\)", r"\1\2", text)          # (++i) -> ++i
    text = re.sub(r"\(\(void \*\) 0\)|\(void \*\) 0\b", "NULL", text)
    text = re.sub(r"^(\s+[A-Za-z_][\w ]*?) (\*+)(\w+)", r"\1\2 \3", text, flags=re.M)  # T *x -> T* x
    return text


def apply_match(src: str, fn: str, new_fn_text: str) -> str:
    """Put the matching text in the source and promote it via nmpromote."""
    path = ROOT / src
    original = path.read_text()
    span = find_fn(original, fn)
    path.write_text(original[:span[0]] + new_fn_text + original[span[1]:])
    r = nmp.promote(src, fn)
    if r != "ok":
        path.write_text(original)
        nmp.ninja_ok()
    return r


def high_pct_targets(min_pct: float):
    """(src, fn, pct) for NONMATCHING functions whose comment claims >= min_pct."""
    out = []
    for src in nmp.nm_sources():
        lines = (ROOT / src).read_text(errors="replace").split("\n")
        for b in nmp.parse_blocks(lines):
            if b["has_else"] or len(b["funcs"]) != 1:
                continue
            fn, a, _ = b["funcs"][0]
            lo = b["start"]
            while lo > 0 and re.match(r"^\s*(//|#\s*pragma)", lines[lo - 1]):
                lo -= 1
            pct = None
            for l in lines[lo:a + 1] + lines[b["start"]:a]:
                m = re.search(r"NONMATCHING\s+~?([\d.]+)%", l)
                if m:
                    pct = float(m.group(1))
            if pct is not None and pct >= min_pct:
                out.append((src, fn, pct))
    return out


def main():
    if len(sys.argv) == 7 and sys.argv[1] == "--cc":
        sys.exit(cc_main(*sys.argv[2:]))
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("functions", nargs="*")
    ap.add_argument("--all", action="store_true", help="every NONMATCHING function at >= --min-pct")
    ap.add_argument("--min-pct", type=float, default=97.0)
    ap.add_argument("--budget", type=float, default=120, help="seconds per function (default 120)")
    ap.add_argument("-j", type=int, default=max(1, (os.cpu_count() or 2) - 2))
    ap.add_argument("--promote", action="store_true", help="apply, verify and commit matches")
    ap.add_argument("--start", type=int, default=0, help="with --all: skip the first N targets")
    ap.add_argument("--limit", type=int, default=0, help="with --all: at most N targets")
    ap.add_argument("--skip", default="", help="file with function names to skip (one per line)")
    ap.add_argument("--backend", choices=("text", "permuter", "both"), default="both",
                    help="text: the built-in rewrites; permuter: decomp-permuter; both (default): "
                         "text for a third of the budget, then decomp-permuter")
    args = ap.parse_args()

    if args.all:
        # closest first: order by fndiff-style line count of the unwrapped function
        from concurrent.futures import ProcessPoolExecutor
        hp = high_pct_targets(args.min_pct)
        srcs = sorted({s for s, _, _ in hp})
        score = {}
        with ProcessPoolExecutor(args.j) as ex:
            for s, res in zip(srcs, ex.map(nmp.scan_source, srcs)):
                score.update({(s, fn): sc for fn, whole, _, sc in res if not whole})
        targets = sorted(((s, f) for s, f, _ in hp if score.get((s, f), -1) > 0),
                         key=lambda t: score[t])
        targets = targets[args.start:args.start + args.limit] if args.limit else targets[args.start:]
        print(f"{len(targets)} target(s): " + " ".join(f"{f}({score[(s, f)]})" for s, f in targets), flush=True)
    else:
        targets = []
        for fn in args.functions:
            unit = nmp.fndiff.find_unit(fn)
            targets.append((nmp.fndiff.load_unit(unit)["metadata"]["source_path"], fn))
    skip = set(Path(args.skip).read_text().split()) if args.skip else set()
    matches = 0
    for src, fn in targets:
        if fn in skip:
            continue
        match, best = None, None
        if args.backend in ("text", "both"):
            budget = args.budget if args.backend == "text" else args.budget / 3
            best, match, _ = permute(src, fn, budget, args.j)
        if match is None and best != -2 and args.backend in ("permuter", "both"):
            budget = args.budget if args.backend == "permuter" else args.budget * 2 / 3
            _, match = permute_ext(src, fn, budget, args.j)
        if match is not None and args.promote:
            r = apply_match(src, fn, match)
            print(f"promote {fn}: {r}", flush=True)
            matches += r == "ok"
        elif match is not None:
            matches += 1
    print(f"{matches} match(es)")


if __name__ == "__main__":
    main()
