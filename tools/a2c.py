#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""ARM64 -> C++ transcriber for the Aska math port.

Translates one guest function (by mangled symbol or 0xaddr:size) instruction by instruction into
C++ that runs on a small register file (x[], v[] lanes) with goto-based control flow. Supports the
FP/SIMD/integer subset used by the math library; anything else becomes a #error so it can't be
missed. Constant loads through ADRP are folded into literals read from the ELF.

Usage: a2c.py <sym|0xaddr:size> <c-function-name> [--args 'x0,x1,s0,...']
"""
import os
import re
import struct
import functools
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs  # noqa: E402
from elfinfo import lib  # noqa: E402

L = lib()
md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
md_d = Cs(CS_ARCH_ARM64, CS_MODE_ARM)  # with operand details: which registers an instruction writes
md_d.detail = True


def gpr_writes(insn_d):
    """General registers (as 'xN') an instruction writes; calls clobber x0-x18 and x30."""
    out = set()
    try:
        _, w = insn_d.regs_access()
    except Exception:  # (capstone without access info: treat every register operand as written)
        w = []
    for r in w:
        n = insn_d.reg_name(r)
        n = {'fp': 'x29', 'lr': 'x30'}.get(n, n)
        if re.match(r'[wx]\d+$', n):
            out.add('x' + n[1:])
    if insn_d.mnemonic in ('bl', 'blr'):
        out |= {f'x{k}' for k in range(19)} | {'x30'}
    return out
def adrp_flow(insns_d, writes, targets, start, size):
    """{branch target: {reg: static value}} for the registers set by adrp (+ add #imm) that hold
    the same value on every path reaching the target (absent: unknown there)."""
    index = {x.address: k for k, x in enumerate(insns_d)}
    n = len(insns_d)
    TOP = object()
    state_in = [None] * n  # None: not reached yet
    state_in[0] = {}
    work = [0]
    block_starts = sorted({index[t] for t in targets if t in index} |
                          {k + 1 for k, x in enumerate(insns_d[:-1]) if x.mnemonic in ('b', 'br', 'ret', 'brk')})

    def meet(a, b):
        return {r: v for r, v in a.items() if b.get(r, TOP) == v}

    while work:
        k = work.pop()
        st = dict(state_in[k])
        x = insns_d[k]
        mn = x.mnemonic
        if mn == 'adrp':
            r = x.op_str.split(',')[0].strip()
            st[r] = int(x.op_str.split('#')[-1], 16)
        else:
            m = re.match(r'(x\d+), (x\d+), #(0x[0-9a-f]+|\d+)$', x.op_str) if mn == 'add' else None
            if m and m.group(2) in st:
                st[m.group(1)] = st[m.group(2)] + int(m.group(3), 0)
            else:
                for r in writes[k]:
                    st.pop(r, None)
        succ = []
        m = re.search(r'#(0x[0-9a-f]+)$', x.op_str)
        is_branch = (mn.startswith('b') and mn not in ('bl', 'blr', 'br', 'bic', 'bsl', 'bif', 'bit')) or mn in ('cbz', 'cbnz', 'tbz', 'tbnz')
        if is_branch and m and int(m.group(1), 16) in index:
            succ.append(index[int(m.group(1), 16)])
        if mn == 'br':  # a jump table (or a tail call): any block start could follow
            succ += block_starts
        if not (mn in ('b', 'br', 'ret') or mn == 'brk'):
            if k + 1 < n:
                succ.append(k + 1)
        for s2 in succ:
            new = st if state_in[s2] is None else meet(state_in[s2], st)
            if state_in[s2] is None or new != state_in[s2]:
                state_in[s2] = new
                work.append(s2)
    return {a: state_in[index[a]] for a in targets if a in index and state_in[index[a]] is not None}



syms = {}
for s in L.elf.get_section_by_name('.dynsym').iter_symbols():
    if s['st_value']:
        syms.setdefault(s.name, (s['st_value'], s['st_size']))
text = L.elf.get_section_by_name('.text')
TB, TD = text['sh_addr'], text.data()


def _unpatch_843419(tb, td):
    """Undo lld's Cortex-A53 erratum 843419 fix in the code we translate. After an adrp at page
    offset 0xff8/0xffc, lld may replace a load/store by `b veneer`, the veneer holding the
    original instruction and `b back` (pc + 4). Read literally that `b` looks like a tail call
    out of the function (a2c emitted `call; goto L_ret`, skipping the rest of the body), so put
    the original instruction back in place, as tools/verdiff.py's Normaliser.unpatch does. The
    pattern (a `b` whose target's second word branches straight back to the `b`'s successor) is
    what identifies a veneer; 3.7.0 has 93 of them (the offline build had 107, one of them in an a2c body of
    that build)."""
    buf = None
    n = len(td)
    for off in range(0, n - 3, 4):
        w = struct.unpack_from('<I', td, off)[0]
        if w & 0xFC000000 != 0x14000000:
            continue
        imm = w & 0x3FFFFFF
        if imm & (1 << 25):
            imm -= 1 << 26
        t = off + imm * 4
        if not (0 <= t <= n - 8):
            continue
        w1 = struct.unpack_from('<I', td, t + 4)[0]
        if w1 & 0xFC000000 != 0x14000000:
            continue
        imm1 = w1 & 0x3FFFFFF
        if imm1 & (1 << 25):
            imm1 -= 1 << 26
        if t + 4 + imm1 * 4 != off + 4:
            continue
        if buf is None:
            buf = bytearray(td)
        buf[off:off + 4] = td[t:t + 4]
    return bytes(buf) if buf is not None else td


TD = _unpatch_843419(TB, TD)


RO = []
for sec in L.elf.iter_sections():
    if sec.name in ('.rodata',) or (sec.name.startswith('.rodata')):
        RO.append((sec['sh_addr'], sec['sh_addr'] + sec['sh_size']))


def is_ro(va):
    return any(a <= va < b for a, b in RO)


_LOADS = []  # (vaddr, filesz, data) of the PT_LOAD segments, read once (seg.data() rereads the file)


def rd(va, n):
    if not _LOADS:
        for seg in L.elf.iter_segments():
            if seg['p_type'] == 'PT_LOAD':
                _LOADS.append((seg['p_vaddr'], seg['p_filesz'], seg.data()))
    for vaddr, filesz, data in _LOADS:
        if vaddr <= va < vaddr + filesz:
            return data[va - vaddr:va - vaddr + n]
    raise KeyError(hex(va))


# Known callees: PLT name or symbol -> C++ call using the register file.
CALLS = {
    'sqrtf': 'S(0) = g_sqrt(S(0));',
    'atan2f': 'S(0) = g_atan2f(S(0), S(1));',
    'acosf': 'S(0) = g_acosf(S(0));',
    'asinf': 'S(0) = g_asinf(S(0));',
    'cosf': 'S(0) = g_cosf(S(0));',
    'sinf': 'S(0) = g_sinf(S(0));',
    '__isnanf': 'X(0) = std::isnan(S(0)) ? 1 : 0;',
    '__isfinitef': 'X(0) = std::isfinite(S(0)) ? 1 : 0;',
    # imports without a native equivalent are called through their PLT stub in the guest
    '__cxa_guard_acquire': 'X(0) = guest_call_below(SP, LIB + {plt:#x}, X(0));',
    '__cxa_guard_release': 'X(0) = guest_call_below(SP, LIB + {plt:#x}, X(0));',
}
EXTRA_CALLS = {
    '_ZN4Aska10Quaternion6CreateEPKNS_6MatrixE': 'quat_create((Quat*)X(0), (const Mat44*)X(1));',
    '_ZN4Aska10Quaternion6CreateEPKNS_6VectorE': 'quat_create((Quat*)X(0), (const Vec4*)X(1));',
    '_ZN4Aska6Matrix3MulEPKS0_S2_': 'mat_mul((Mat44*)X(0), (const Mat44*)X(1), (const Mat44*)X(2));',
    '_ZN4Aska6Matrix11MulFromLeftEPKS0_': 'mat_mul_from_left((Mat44*)X(0), (const Mat44*)X(1));',
    '_ZN4Aska6Matrix6InvertEv': 'mat_invert((Mat44*)X(0));',
    '_ZN4Aska6Vector11ApplyMatrixEPKNS_6MatrixE': 'vec_apply_matrix((Vec4*)X(0), (const Mat44*)X(1));',
    '_ZN4Aska6Vector22ApplyMatrixNoTransportEPKNS_6MatrixE': 'vec_apply_matrix_no_transport((Vec4*)X(0), (const Mat44*)X(1));',
    '_ZN4Aska6Vector21ApplyMatrixNoWeightedEPKNS_6MatrixE': 'vec_apply_matrix_no_weighted((Vec4*)X(0), (const Mat44*)X(1));',
    '_ZN4Aska6Matrix6CreateEPKNS_10QuaternionE': 'mat_create((Mat44*)X(0), (const Quat*)X(1));',
    '_ZN4Aska10Quaternion6CreateEPKNS_6VectorES3_': 'quat_create((Quat*)X(0), (const Vec4*)X(1), (const Vec4*)X(2));',
    '_ZN4Aska10Quaternion10SquadSlerpEPKS0_S2_f': 'quat_squad_slerp((Quat*)X(0), (const Quat*)X(1), (const Quat*)X(2), S(0));',
    '_ZNK4Aska4AABB8SeparateERKNS_15OrthogonalPlaneEPS0_S4_': 'X(0) = aabb_separate(X(0), X(1), X(2), X(3));',
}


# Optional fallback for calls the tables above don't cover (set by generators that support them):
# CALL_FALLBACK(kind, target, reg) -> C++ statement. kind is 'bl', 'b' (tail call), 'blr' or 'br'
# (tail call through a register); target is the static address (bl/b) or None; reg is the
# register expression (blr/br) or None.
CALL_FALLBACK = None
# Set by generators that provide the guest TPIDR_EL0 value as a C++ expression (enables `mrs xN, tpidr_el0`).
TPIDR = None
# Set by generators whose bodies declare `u64 ex_a_, ex_v_` (the exclusive monitor): enables
# ldxr/ldaxr + stxr/stlxr as a compare-and-swap.
EXCLUSIVE = False


def shift_expr(rhs, spec, w64):
    """A shifted-register operand ("lsl #3", "asr #31", "ror #8")."""
    m = re.match(r'(lsl|lsr|asr|ror) #(\d+)$', spec)
    if not m:
        raise ValueError('shift ' + spec)
    k, sh = m.group(1), int(m.group(2))
    t, st, bits_ = ('u64', 's64', 64) if w64 else ('u32', 's32', 32)
    if k == 'lsl':
        return f'(({t}){rhs} << {sh})'
    if k == 'lsr':
        return f'(({t}){rhs} >> {sh})'
    if k == 'asr':
        return f'({t})(({st})({t}){rhs} >> {sh})'
    return f'(({t}){rhs} >> {sh} | ({t}){rhs} << {(bits_ - sh) % bits_})' if sh else f'(({t}){rhs})'


# Set by generators that want ARM NaN semantics for FP arithmetic (NaN operand propagation and
# the positive default NaN 0x7fc00000; x86 produces 0xffc00000): arithmetic goes through the
# NX_* helpers (models.h) instead of the C operators.
NAN_EXACT = False


def PADD(a, b):
    return f'NX_ADD({a}, {b})' if NAN_EXACT else f'{a} + {b}'


@functools.lru_cache(maxsize=None)  # one c++filt process per symbol, not per translation
def dem(n):
    return subprocess.run(['c++filt', n], capture_output=True, text=True).stdout.strip()


COND = {'eq', 'ne', 'mi', 'pl', 'gt', 'ge', 'lt', 'le', 'hi', 'ls', 'vs', 'vc', 'hs', 'lo', 'cs', 'cc'}


def translate(arg, fname):
    if arg.startswith('0x'):
        a, _, sz = arg.partition(':')
        start, size = int(a, 16), int(sz, 16)
    else:
        start, size = syms[arg]
    insns = list(md.disasm(TD[start - TB:start - TB + size], start))
    targets = set()
    for i in insns:
        if i.mnemonic.startswith('b') and i.mnemonic not in ('bl', 'br', 'bic', 'bsl', 'bif', 'bit') or i.mnemonic in ('cbz', 'cbnz', 'tbz', 'tbnz'):
            m = re.search(r'#(0x[0-9a-f]+)$', i.op_str)
            if m:
                targets.add(int(m.group(1), 16))
    out = []
    jt_state = {}
    targets_late = set()
    adrp = {}  # reg -> page value (static)
    skip_vc = False
    # The adrp tracking follows the code in address order, so a register's static value must be
    # forgotten when anything else writes it (madd, csel, a call, ...), and at branch targets
    # unless every write of it in the function is the same adrp (then it holds on every path).
    insns_d = list(md_d.disasm(TD[start - TB:start - TB + size], start))
    writes = [gpr_writes(x) for x in insns_d]
    adrp_pages = {}
    for x, w in zip(insns_d, writes):
        for r in w:
            if x.mnemonic == 'adrp':
                adrp_pages.setdefault(r, set()).add(x.op_str.split('#')[-1])
            else:
                adrp_pages.setdefault(r, set()).add(None)
    unstable = {r for r, pg in adrp_pages.items() if None in pg or len(pg) > 1}
    # Which of those still hold one static value at each branch target, by a forward data flow
    # over the function's branches (adrp, then add #imm of a known register; anything else writing
    # the register makes it unknown). E.g. "adrp x28; ... add x28, x28, #lo" before a loop whose
    # head is a branch target: the jump table's base stays known in the loop.
    adrp_at_target = adrp_flow(insns_d, writes, targets, start, size)
    adrp_before = None

    def xr(r):  # integer register expression
        if r in ('xzr', 'wzr'):
            return '0'
        if r == 'sp':
            return 'SP'
        n = int(r[1:])
        return f'X({n})' if r[0] == 'x' else f'W({n})'

    def setx(r, e):
        if r in ('xzr', 'wzr'):
            return ''
        if r == 'sp':
            return f'SP = {e};'
        n = int(r[1:])
        return f'X({n}) = (u64)({e});' if r[0] == 'x' else f'X({n}) = (u32)({e});'

    def mem(opnd):
        # "[x1, #0x10]" or "[x1]" or "[x1, x2, lsl #2]" or "[x8, w9, uxtw #2]"
        m = re.match(r'\[(\w+)(?:, #(-?0x[0-9a-f]+|-?\d+))?\](!?)$', opnd)
        if m:
            base, off, wb = m.group(1), int(m.group(2) or '0', 0), m.group(3)
            return base, off, None, wb
        m = re.match(r'\[(\w+), (\w+)(?:, (lsl|uxtw|sxtw) #(\d+))?(?:, (uxtw|sxtw))?\]$', opnd)
        if m:
            base, idx, kind, sh = m.group(1), m.group(2), m.group(3) or m.group(5), int(m.group(4) or 0)
            ie = xr(idx)
            if kind == 'sxtw':
                ie = f'(u64)(s64)(s32){ie}'
            return base, 0, f'({ie} << {sh})', ''
        raise ValueError(opnd)

    def addr_expr(base, off, idx):
        e = xr(base)
        if off:
            e = f'({e} + {off})'
        if idx:
            e = f'({e} + {idx})'
        return e

    def const_addr(base, off):
        if base in adrp and adrp[base] is not None and is_ro(adrp[base] + off):
            return adrp[base] + off
        return None

    def split_ops(s):
        parts, depth, cur = [], 0, ''
        for ch in s:
            if ch == '[':
                depth += 1
            if ch == ']':
                depth -= 1
            if ch == ',' and depth == 0:
                parts.append(cur.strip())
                cur = ''
            else:
                cur += ch
        if cur.strip():
            parts.append(cur.strip())
        return parts

    def vreg(r):  # s5 / d5 / q5 / v5.4s / v5.s[1] -> (n, kind, lane)
        m = re.match(r'([sdqbh])(\d+)$', r)
        if m:
            return int(m.group(2)), m.group(1), None
        m = re.match(r'v(\d+)\.(\w+)(?:\[(\d+)\])?$', r)
        if m:
            return int(m.group(1)), m.group(2), (int(m.group(3)) if m.group(3) else None)
        raise ValueError(r)

    def sv(r):  # scalar operand: s5 or v5.s[2]
        n, k, lane = vreg(r)
        if lane is not None and k != 's':
            raise ValueError('lane kind ' + r)
        return f'V({n},{lane})' if lane is not None else f'S({n})'

    def fimm(s):
        s = s.lstrip('#')
        return repr(float(s)) + 'f'

    def emit(s):
        out.append('    ' + s)

    for idx, i in enumerate(insns):
        a = i.address
        if adrp_before is not None:  # the previous instruction's writes the handlers didn't track
            for r in writes[idx - 1]:
                if r in adrp and adrp_before.get(r, object()) == adrp[r]:
                    adrp.pop(r)
        if a in targets:
            known = adrp_at_target.get(a, {})
            for r in unstable:
                if r in known:
                    adrp[r] = known[r]
                else:
                    adrp.pop(r, None)
        adrp_before = dict(adrp)
        if a in targets:
            out.append(f'L_{a:x}:')
        mn, ops = i.mnemonic, split_ops(i.op_str)
        c = f'/* {a:x}: {mn} {i.op_str} */'
        try:
            # ---- sqrt fallback pattern ----
            if mn == 'fcmp' and len(ops) == 2 and ops[0] == ops[1]:
                skip_vc = True
                emit(f'FCMP(S({vreg(ops[0])[0]}), S({vreg(ops[1])[0]})); {c}')
                continue
            if mn == 'b.vc' and skip_vc:
                skip_vc = False
                t = int(ops[0].lstrip('#'), 16)
                emit(f'goto L_{t:x}; {c}  // fsqrt result is never NaN-different from sqrtf()')
                continue
            skip_vc = False
            # ---- integer / conversion extensions (added for the models transcription) ----
            if mn == 'nop':
                continue
            if mn in ('prfum', 'prfm'):
                continue
            if mn == 'dmb':
                emit(f'__atomic_thread_fence(__ATOMIC_SEQ_CST); {c}')
                continue
            if EXCLUSIVE and mn in ('ldaxr', 'ldxr', 'ldaxrb', 'ldxrb', 'ldaxrh', 'ldxrh'):
                r_, m_ = ops[0], ops[1]
                base, off, idxe, wb = mem(m_)
                w = 8 if mn.endswith('b') else 16 if mn.endswith('h') else 32 if r_[0] == 'w' else 64
                ea = addr_expr(base, off, idxe)
                emit(f'ex_a_ = {ea}; ex_v_ = __atomic_load_n((uint{w}_t*)ex_a_, __ATOMIC_SEQ_CST); {setx(r_, "ex_v_")} {c}')
                continue
            if EXCLUSIVE and mn in ('stlxr', 'stxr', 'stlxrb', 'stxrb', 'stlxrh', 'stxrh'):
                st, r_, m_ = ops[0], ops[1], ops[2]
                base, off, idxe, wb = mem(m_)
                w = 8 if mn.endswith('b') else 16 if mn.endswith('h') else 32 if r_[0] == 'w' else 64
                ea = addr_expr(base, off, idxe)
                emit(f'{{ uint{w}_t e_ = (uint{w}_t)ex_v_; bool ok_ = ex_a_ == (u64)({ea}) && __atomic_compare_exchange_n((uint{w}_t*)({ea}), &e_, (uint{w}_t)({xr(r_)}), false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST); ex_a_ = 0; {setx(st, "ok_ ? 0 : 1")} }} {c}')
                continue
            if EXCLUSIVE and mn == 'clrex':
                emit(f'ex_a_ = 0; {c}')
                continue
            if mn in ('stlr', 'stlrb', 'stlrh'):
                r_, m_ = ops[0], ops[1]
                base, off, idxe, wb = mem(m_)
                w = 8 if mn.endswith('b') else 16 if mn.endswith('h') else 32 if r_[0] == 'w' else 64
                emit(f'__atomic_store_n((uint{w}_t*)({addr_expr(base, off, idxe)}), (uint{w}_t)({xr(r_)}), __ATOMIC_SEQ_CST); {c}')
                continue
            if mn in ('bfi', 'bfxil', 'ubfiz', 'sbfx') and ops[0][0] in 'wx' and mn != 'sbfx':
                d, s1, lsb, wd = ops[0], ops[1], int(ops[2].lstrip('#'), 0), int(ops[3].lstrip('#'), 0)
                mask = (1 << wd) - 1
                if mn == 'bfi':
                    e = f'({xr(d)} & ~(u64)0x{mask << lsb:x}ull) | (((u64){xr(s1)} & 0x{mask:x}ull) << {lsb})'
                elif mn == 'bfxil':
                    e = f'({xr(d)} & ~(u64)0x{mask:x}ull) | (((u64){xr(s1)} >> {lsb}) & 0x{mask:x}ull)'
                else:
                    e = f'((u64){xr(s1)} & 0x{mask:x}ull) << {lsb}'
                emit(f'{setx(d, e)} {c}')
                continue
            if mn in ('ccmp', 'ccmn') and ops[0][0] in 'wx':
                a1, b1, nzcv, cond = ops
                be = b1.lstrip('#') if b1.startswith('#') else xr(b1)
                cm = 'ICMP64' if a1[0] == 'x' else 'ICMP32'
                if mn == 'ccmn':
                    raise ValueError('ccmn')
                emit(f'if (C_{cond.upper()}()) {cm}({xr(a1)}, {be}); else SETNZCV({nzcv.lstrip("#")}); {c}')
                continue
            if mn in ('cinc', 'cinv') and ops[0][0] in 'wx':
                d, s1, cond = ops
                alt = f'{xr(s1)} + 1' if mn == 'cinc' else f'~{xr(s1)}'
                emit(f'{setx(d, f"C_{cond.upper()}() ? {alt} : {xr(s1)}")} {c}')
                continue
            if mn == 'sdiv' and len(ops) == 3:
                d, s1, s2 = ops
                t_ = 's64' if d[0] == 'x' else 's32'
                a_, b_ = f'({t_}){xr(s1)}', f'({t_}){xr(s2)}'
                mn_ = 'INT64_MIN' if d[0] == 'x' else 'INT32_MIN'
                emit(f'{setx(d, f"{b_} == 0 ? 0 : ({a_} == {mn_} && {b_} == -1) ? {a_} : {a_} / {b_}")} {c}')
                continue
            if mn == 'rev' and ops[0][0] in 'wx':
                f = '__builtin_bswap32' if ops[0][0] == 'w' else '__builtin_bswap64'
                emit(f'{setx(ops[0], f"{f}({xr(ops[1])})")} {c}')
                continue
            if mn == 'ldpsw':
                r1, r2, m_ = ops[0], ops[1], ops[2]
                base, off, idxe, wb = mem(m_)
                post = int(ops[3].lstrip('#'), 0) if len(ops) == 4 else None
                o0 = 0 if post is not None else off
                emit(f'{{ u64 a_ = {addr_expr(base, o0, None)}; {setx(r1, "(u64)(s64)(s32)LDI32(a_)")} {setx(r2, "(u64)(s64)(s32)LDI32(a_ + 4)")} }} {c}')
                if wb == '!':
                    emit(f'{setx(base, f"{xr(base)} + {off}")}')
                if post is not None:
                    emit(f'{setx(base, f"{xr(base)} + {post}")}')
                continue
            if mn in ('mov', 'ins') and re.match(r'v\d+\.[ds]\[\d\]$', ops[0]) and ops[1][0] in 'wx':
                n, k, lane = vreg(ops[0])
                if k == 'd':
                    emit(f'r.v[{n}].f[{2 * lane}] = from_bits((u32){xr(ops[1])}); r.v[{n}].f[{2 * lane + 1}] = from_bits((u32)((u64){xr(ops[1])} >> 32)); {c}')
                else:
                    emit(f'r.v[{n}].f[{lane}] = from_bits((u32){xr(ops[1])}); {c}')
                continue
            if mn == 'dup' and ops[0].endswith('.2d') and ops[1][0] == 'x':
                n = vreg(ops[0])[0]
                x_ = f'(u64)({xr(ops[1])})'  # (xzr is a plain 0: widen before shifting)
                emit(f'SETV({n}, from_bits((u32){x_}), from_bits((u32)({x_} >> 32)), from_bits((u32){x_}), from_bits((u32)({x_} >> 32))); {c}')
                continue
            if mn in ('add', 'sub') and ops[0].endswith('.2d'):
                d, a_, b_ = (vreg(o)[0] for o in ops)
                op = '+' if mn == 'add' else '-'
                lanes = []
                for k in range(2):
                    e = f'(V64_(r, {a_}, {k}) {op} V64_(r, {b_}, {k}))'
                    lanes += [f'from_bits((u32){e})', f'from_bits((u32)({e} >> 32))']
                emit(f'{{ V4 t_{{{{{", ".join(lanes)}}}}}; r.v[{d}] = t_; }} {c}')
                continue
            if mn == 'cmeq' and ops[0].endswith('.2d') and ops[2].startswith('v'):
                # 64-bit lanes compared for equality (all ones / zero); used by pointer searches
                d, a_, b_ = (vreg(o)[0] for o in ops)
                lanes = []
                for k in range(2):
                    e = f'(V64_(r, {a_}, {k}) == V64_(r, {b_}, {k}) ? 0xffffffffu : 0u)'
                    lanes += [f'from_bits({e})', f'from_bits({e})']
                emit(f'{{ V4 t_{{{{{", ".join(lanes)}}}}}; r.v[{d}] = t_; }} {c}')
                continue
            if mn == 'xtn' and ops[0].endswith('.2s') and ops[1].endswith('.2d'):
                d, a_ = vreg(ops[0])[0], vreg(ops[1])[0]
                emit(f'{{ V4 t_{{{{V({a_},0), V({a_},2), 0.0f, 0.0f}}}}; r.v[{d}] = t_; }} {c}')
                continue
            if mn == 'mvn' and ops[0].startswith('v'):
                d, a_ = vreg(ops[0])[0], vreg(ops[1])[0]
                if ops[0].endswith('.8b'):  # 64-bit form: upper half zeroed
                    emit(f'SETV({d}, from_bits(~bits(V({a_},0))), from_bits(~bits(V({a_},1))), 0.0f, 0.0f); {c}')
                else:
                    emit(f'SETV({d}, from_bits(~bits(V({a_},0))), from_bits(~bits(V({a_},1))), from_bits(~bits(V({a_},2))), from_bits(~bits(V({a_},3)))); {c}')
                continue
            if mn in ('cmeq', 'cmtst') and ops[0].endswith(('.4s', '.2s')) and ops[2].startswith('#') and int(ops[2].lstrip('#'), 0) == 0 and mn == 'cmeq':
                d, a_ = vreg(ops[0])[0], vreg(ops[1])[0]
                n = 4 if ops[0].endswith('.4s') else 2
                lanes = [f'from_bits(bits(V({a_},{k})) == 0 ? 0xffffffffu : 0u)' for k in range(n)] + ['0.0f'] * (4 - n)
                emit(f'SETV({d}, {", ".join(lanes)}); {c}')
                continue
            if mn == 'addv' and ops[0][0] == 's' and ops[1].endswith('.4s'):
                a_ = vreg(ops[1])[0]
                emit(f'SETS({vreg(ops[0])[0]}, from_bits(bits(V({a_},0)) + bits(V({a_},1)) + bits(V({a_},2)) + bits(V({a_},3)))); {c}')
                continue
            if mn in ('ushr', 'usra') and ops[0].endswith(('.4s', '.2s')) and ops[2].startswith('#'):
                # (32-bit lanes shifted right logically; usra accumulates into the destination)
                d, a_ = vreg(ops[0])[0], vreg(ops[1])[0]
                sh = int(ops[2].lstrip('#'), 0)
                n = 4 if ops[0].endswith('.4s') else 2
                acc = lambda k: f'bits(V({d},{k})) + ' if mn == 'usra' else ''
                lanes = [f'from_bits({acc(k)}(u32)((u64)bits(V({a_},{k})) >> {sh}))' for k in range(n)] + ['0.0f'] * (4 - n)
                emit(f'{{ V4 t_{{{{{", ".join(lanes)}}}}}; r.v[{d}] = t_; }} {c}')
                continue
            if mn == 'mul' and ops[0].startswith('v') and ops[0].endswith(('.4s', '.2s')) and ops[2].startswith('v') and '[' not in ops[2]:
                d, a_, b_ = (vreg(o)[0] for o in ops)
                n = 4 if ops[0].endswith('.4s') else 2
                lanes = [f'from_bits(bits(V({a_},{k})) * bits(V({b_},{k})))' for k in range(n)] + ['0.0f'] * (4 - n)
                emit(f'{{ V4 t_{{{{{", ".join(lanes)}}}}}; r.v[{d}] = t_; }} {c}')
                continue
            if mn in ('add', 'sub') and ops[0].endswith(('.4s', '.2s')) and ops[0].startswith('v'):
                d, a_, b_ = (vreg(o)[0] for o in ops)
                n = 4 if ops[0].endswith('.4s') else 2
                op = '+' if mn == 'add' else '-'
                lanes = [f'from_bits(bits(V({a_},{k})) {op} bits(V({b_},{k})))' for k in range(n)] + ['0.0f'] * (4 - n)
                emit(f'{{ V4 t_{{{{{", ".join(lanes)}}}}}; r.v[{d}] = t_; }} {c}')
                continue
            if mn == 'cmeq' and ops[0].endswith('.4s') and not ops[2].startswith('#'):
                d, a_, b_ = (vreg(o)[0] for o in ops)
                lanes = [f'from_bits(bits(V({a_},{k})) == bits(V({b_},{k})) ? 0xffffffffu : 0u)' for k in range(4)]
                emit(f'SETV({d}, {", ".join(lanes)}); {c}')
                continue
            if mn == 'cnt' and ops[0].endswith('.8b'):
                d, a_ = vreg(ops[0])[0], vreg(ops[1])[0]
                emit(f'{{ u64 b_ = V64_(r, {a_}, 0), o_ = 0; for (int k_ = 0; k_ < 8; k_++) o_ |= (u64)__builtin_popcountll((b_ >> (8 * k_)) & 0xff) << (8 * k_); SETV({d}, from_bits((u32)o_), from_bits((u32)(o_ >> 32)), 0.0f, 0.0f); }} {c}')
                continue
            if mn == 'uaddlv' and ops[1].endswith('.8b') and ops[0][0] == 'h':
                d, a_ = vreg(ops[0])[0], vreg(ops[1])[0]
                emit(f'{{ u64 b_ = V64_(r, {a_}, 0); u32 s_ = 0; for (int k_ = 0; k_ < 8; k_++) s_ += (b_ >> (8 * k_)) & 0xff; SETS({d}, from_bits(s_ & 0xffff)); }} {c}')
                continue
            if mn == 'fcvtzu' and ops[0][0] in 'wx' and ops[1][0] == 's':
                lim = '4294967296.0f' if ops[0][0] == 'w' else '18446744073709551616.0f'
                mx = '0xffffffffull' if ops[0][0] == 'w' else '~0ull'
                emit(f'{{ float f_ = S({vreg(ops[1])[0]}); {setx(ops[0], f"f_ != f_ || f_ <= 0.0f ? 0 : f_ >= {lim} ? {mx} : (u64)f_")} }} {c}')
                continue
            if mn == 'fcvtzs' and ops[0][0] == 'x' and ops[1][0] == 's':
                emit(f'{{ float f_ = S({vreg(ops[1])[0]}); {setx(ops[0], "f_ != f_ ? 0 : f_ >= 9223372036854775808.0f ? 0x7fffffffffffffffull : f_ < -9223372036854775808.0f ? 0x8000000000000000ull : (u64)(s64)f_")} }} {c}')
                continue
            if mn in ('fcvtpu', 'fcvtmu') and ops[0][0] in 'wx' and ops[1][0] == 's':
                # (round towards +inf / -inf, then unsigned saturation: NaN and negatives -> 0)
                rnd = 'std::ceil' if mn == 'fcvtpu' else 'std::floor'
                lim = '4294967296.0f' if ops[0][0] == 'w' else '18446744073709551616.0f'
                mx = '0xffffffffull' if ops[0][0] == 'w' else '~0ull'
                emit(f'{{ float f_ = {rnd}(S({vreg(ops[1])[0]})); {setx(ops[0], f"f_ != f_ || f_ <= 0.0f ? 0 : f_ >= {lim} ? {mx} : (u64)f_")} }} {c}')
                continue
            if mn in ('ldurh', 'ldurb', 'sturh', 'sturb', 'ldursw', 'ldursb', 'ldursh'):
                mn = mn.replace('ur', 'r')
            if mn in ('smaddl', 'umaddl', 'smsubl', 'umsubl'):
                d, s1, s2, s3 = ops
                cast = '(s64)(s32)' if mn[0] == 's' else '(u64)(u32)'
                op = '+' if 'add' in mn else '-'
                emit(f'{setx(d, f"{xr(s3)} {op} (u64)({cast}{xr(s1)} * {cast}{xr(s2)})")} {c}')
                continue
            if mn in ('umulh', 'smulh'):
                d, s1, s2 = ops
                if mn == 'umulh':
                    emit(f'{setx(d, f"(u64)(((unsigned __int128){xr(s1)} * (unsigned __int128){xr(s2)}) >> 64)")} {c}')
                else:
                    emit(f'{setx(d, f"(u64)(((__int128)(s64){xr(s1)} * (__int128)(s64){xr(s2)}) >> 64)")} {c}')
                continue
            if mn in ('lsl', 'lsr', 'asr', 'ror') and len(ops) == 3 and not ops[2].startswith('#'):
                d, s1, s2 = ops
                wdt = 64 if d[0] == 'x' else 32
                sh = f'({xr(s2)} & {wdt - 1})'
                if mn == 'lsl':
                    e = f'{xr(s1)} << {sh}'
                elif mn == 'lsr':
                    e = f'{xr(s1)} >> {sh}'
                elif mn == 'asr':
                    e = f'(s64){xr(s1)} >> {sh}' if wdt == 64 else f'(s32){xr(s1)} >> {sh}'
                else:
                    raise ValueError('ror reg')
                emit(f'{setx(d, e)} {c}')
                continue
            if mn in ('neg', 'negs', 'mvn') and ops[0][0] in 'wx':
                d, s1 = ops[0], ops[1]
                rhs = xr(s1)
                if len(ops) > 2:
                    rhs = shift_expr(rhs, ops[2], d[0] == 'x')
                if mn == 'mvn':
                    emit(f'{setx(d, f"~{rhs}")} {c}')
                elif mn == 'neg':
                    emit(f'{setx(d, f"0 - {rhs}")} {c}')
                else:
                    w = 'ICMP64' if d[0] == 'x' else 'ICMP32'
                    emit(f'{w}(0, {rhs}); {setx(d, f"0 - {rhs}")} {c}')
                continue
            if mn in ('frintm', 'frintp', 'frintz', 'frinta', 'frintn') and ops[0][0] == 's':
                f = {'frintm': 'std::floor', 'frintp': 'std::ceil', 'frintz': 'std::trunc', 'frinta': 'std::round', 'frintn': 'std::nearbyint'}[mn]
                emit(f'SETS({vreg(ops[0])[0]}, {f}(S({vreg(ops[1])[0]}))); {c}')
                continue
            if mn in ('fcvtms', 'fcvtps', 'fcvtas', 'fcvtns') and ops[0][0] == 'w':
                f = {'fcvtms': 'std::floor', 'fcvtps': 'std::ceil', 'fcvtas': 'std::round', 'fcvtns': 'std::nearbyint'}[mn]
                emit(f'{setx(ops[0], f"(u32)fcvtzs({f}(S({vreg(ops[1])[0]})))")} {c}')
                continue
            if mn == 'fcvtzs' and ops[0].startswith('v') and ops[0].endswith(('.2s', '.4s')):
                dn, sn = vreg(ops[0])[0], vreg(ops[1])[0]
                n = 4 if ops[0].endswith('.4s') else 2
                lanes = [f'from_bits((u32)fcvtzs(V({sn},{k})))' for k in range(n)] + ['0.0f'] * (4 - n)
                emit(f'SETV({dn}, {", ".join(lanes)}); {c}')
                continue
            if mn in ('scvtf', 'ucvtf') and ops[0].startswith('v') and ops[0].endswith(('.2s', '.4s')):
                dn, sn = vreg(ops[0])[0], vreg(ops[1])[0]
                n = 4 if ops[0].endswith('.4s') else 2
                cast = '(s32)' if mn == 'scvtf' else '(u32)'
                lanes = [f'(float){cast}bits(V({sn},{k}))' for k in range(n)] + ['0.0f'] * (4 - n)
                emit(f'SETV({dn}, {", ".join(lanes)}); {c}')
                continue
            if mn == 'fcvt' and ops[0][0] == 's' and ops[1][0] == 'd':  # double -> float (round to nearest)
                m = vreg(ops[1])[0]
                emit(f'{{ u64 b_ = (u64)bits(r.v[{m}].f[0]) | ((u64)bits(r.v[{m}].f[1]) << 32); double d_; std::memcpy(&d_, &b_, 8); '
                     f'SETS({vreg(ops[0])[0]}, (float)d_); }} {c}')
                continue
            if mn == 'scvtf' and ops[0][0] == 's' and ops[1][0] == 's':
                emit(f'SETS({vreg(ops[0])[0]}, (float)(s32)bits(S({vreg(ops[1])[0]}))); {c}')
                continue
            if mn in ('scvtf', 'ucvtf') and ops[0][0] == 's' and ops[1][0] == 'x':
                cast = '(s64)' if mn == 'scvtf' else '(u64)'
                emit(f'SETS({vreg(ops[0])[0]}, (float){cast}{xr(ops[1])}); {c}')
                continue
            if mn == 'cmtst' and ops[0].endswith(('.2s', '.4s')):
                dn, an, bn = vreg(ops[0])[0], vreg(ops[1])[0], vreg(ops[2])[0]
                n = 4 if ops[0].endswith('.4s') else 2
                lanes = [f'from_bits((bits(V({an},{k})) & bits(V({bn},{k}))) ? 0xffffffffu : 0u)' for k in range(n)] + ['0.0f'] * (4 - n)
                emit(f'SETV({dn}, {", ".join(lanes)}); {c}')
                continue
            # Lane permutes of 32-bit lanes (.4s / .2s)
            if mn in ('zip1', 'zip2', 'trn1', 'trn2', 'uzp1', 'uzp2') and ops[0].endswith(('.4s', '.2s')):
                dn, an, bn = (vreg(o)[0] for o in ops)
                n = 4 if ops[0].endswith('.4s') else 2
                src = [f'a_.f[{k}]' for k in range(n)] + [f'b_.f[{k}]' for k in range(n)]  # a then b
                h = n // 2
                if mn == 'zip1':
                    idx = [j for k in range(h) for j in (k, n + k)]
                elif mn == 'zip2':
                    idx = [j for k in range(h, n) for j in (k, n + k)]
                elif mn == 'trn1':
                    idx = [j for k in range(0, n, 2) for j in (k, n + k)]
                elif mn == 'trn2':
                    idx = [j for k in range(1, n, 2) for j in (k, n + k)]
                elif mn == 'uzp1':
                    idx = list(range(0, 2 * n, 2))
                else:
                    idx = list(range(1, 2 * n, 2))
                lanes = [src[j] for j in idx] + ['0.0f'] * (4 - n)
                emit(f'{{ V4 a_ = r.v[{an}], b_ = r.v[{bn}]; SETV({dn}, {", ".join(lanes)}); }} {c}')
                continue
            if mn == 'cmeq' and ops[0].endswith(('.4h', '.8h')) and ops[2].startswith('#') and int(ops[2].lstrip('#'), 0) == 0:
                dn, an = vreg(ops[0])[0], vreg(ops[1])[0]
                n = 2 if ops[0].endswith('.4h') else 4
                lanes = [f'from_bits(((bits(V({an},{k})) & 0xffffu) ? 0u : 0xffffu) | ((bits(V({an},{k})) >> 16) ? 0u : 0xffff0000u))' for k in range(n)]
                lanes += ['0.0f'] * (4 - n)
                emit(f'SETV({dn}, {", ".join(lanes)}); {c}')
                continue
            if mn in ('sshll', 'ushll') and ops[0].endswith('.4s') and ops[1].endswith('.4h'):
                dn, sn = vreg(ops[0])[0], vreg(ops[1])[0]
                sh = int(ops[2].lstrip('#'), 0)
                cast = '(u32)(s32)(int16_t)' if mn == 'sshll' else '(u32)(u16)'
                lanes = []
                for k in range(4):
                    h = f'(bits(V({sn},{k // 2})) >> {16 * (k % 2)})'
                    lanes.append(f'from_bits({cast}{h} << {sh})')
                emit(f'{{ V4 t_{{{{{", ".join(lanes)}}}}}; r.v[{dn}] = t_; }} {c}')
                continue
            if mn in ('ldr', 'ldur') and len(ops) == 2 and ops[0][0] in 'hb':
                n = vreg(ops[0])[0]
                base, off, idxe, wb = mem(ops[1])
                w = 16 if ops[0][0] == 'h' else 8
                emit(f'SETS({n}, from_bits((u32)LDI{w}({addr_expr(base, off, idxe)}))); {c}')
                if wb == '!':
                    emit(f'{setx(base, f"{xr(base)} + {off}")}')
                continue
            if mn in ('fmov',) and ops[0][0] == 'x' and ops[1][0] == 'd':
                n = vreg(ops[1])[0]
                emit(f'{setx(ops[0], f"(u64)bits(V({n},0)) | ((u64)bits(V({n},1)) << 32)")} {c}')
                continue
            if mn in ('fmov',) and ops[0][0] == 'd' and ops[1][0] == 'x':
                n = vreg(ops[0])[0]
                emit(f'SETV({n}, from_bits((u32){xr(ops[1])}), from_bits((u32)({xr(ops[1])} >> 32)), 0.0f, 0.0f); {c}')
                continue
            if mn in ('fmadd', 'fmsub', 'fnmadd', 'fnmsub') and ops[0][0] == 's':
                d, s1, s2, s3 = [f'S({vreg(o)[0]})' for o in ops]
                e = {'fmadd': f'NX_FMA({s1}, {s2}, {s3})', 'fmsub': f'NX_FMA(-{s1}, {s2}, {s3})',
                     'fnmadd': f'NX_FMA(-{s1}, {s2}, -{s3})', 'fnmsub': f'NX_FMA({s1}, {s2}, -{s3})'}[mn]
                emit(f'SETS({vreg(ops[0])[0]}, {e}); {c}')
                continue
            if mn in ('fmul', 'fadd', 'fsub', 'fdiv', 'fnmul', 'fmax', 'fmin', 'fmaxnm', 'fminnm', 'fabd'):
                d, s1, s2 = ops
                dn, dk, _ = vreg(d)
                opmap = {'fmul': '*', 'fadd': '+', 'fsub': '-', 'fdiv': '/'}
                nxmap = {'fmul': 'NX_MUL', 'fadd': 'NX_ADD', 'fsub': 'NX_SUB', 'fdiv': 'NX_DIV'}
                if dk == 's':
                    x1, x2 = sv(s1), sv(s2)
                    if mn in opmap and NAN_EXACT:
                        e = f'{nxmap[mn]}({x1}, {x2})'
                    elif mn in opmap:
                        e = f'{x1} {opmap[mn]} {x2}'
                    elif mn == 'fnmul':
                        e = f'-NX_MUL({x1}, {x2})' if NAN_EXACT else f'-({x1} * {x2})'
                    elif mn == 'fabd':
                        e = f'std::fabs(NX_SUB({x1}, {x2}))' if NAN_EXACT else f'std::fabs({x1} - {x2})'
                    else:
                        e = f'A64_{mn.upper()}({x1}, {x2})'
                    emit(f'SETS({dn}, {e}); {c}')
                elif dk in ('4s', '2s'):
                    n = 4 if dk == '4s' else 2
                    an = vreg(s1)[0]
                    bn, bk, bl = vreg(s2)
                    if bl is not None and bk != "s":
                        raise ValueError("by-element kind")
                    lanes = []
                    for k in range(n):
                        be = f'V({bn},{bl})' if bl is not None else f'V({bn},{k})'
                        ae = f'V({an},{k})'
                        if mn in opmap and NAN_EXACT:
                            lanes.append(f'{nxmap[mn]}({ae}, {be})')
                        elif mn in opmap:
                            lanes.append(f'{ae} {opmap[mn]} {be}')
                        elif mn in ('fmin', 'fmax', 'fminnm', 'fmaxnm'):
                            lanes.append(f'A64_{mn.upper()}({ae}, {be})')
                        else:
                            raise ValueError('vec ' + mn)
                    zero = ', 0.0f, 0.0f' if n == 2 else ''
                    emit(f'SETV({dn}, {", ".join(lanes)}{zero}); {c}')
                else:
                    raise ValueError(dk)
                continue
            if mn in ('fneg', 'fabs', 'fsqrt') :
                d, s1 = ops
                dn, dk, _ = vreg(d)
                sn = vreg(s1)[0]
                f = {'fneg': '-{}', 'fabs': 'std::fabs({})', 'fsqrt': 'NX_SQRT({})' if NAN_EXACT else 'g_sqrt({})'}[mn]
                if dk == 's':
                    emit(f'SETS({dn}, {f.format(f"S({sn})")}); {c}')
                elif dk in ('4s', '2s'):
                    n = 4 if dk == '4s' else 2
                    lanes = [f.format(f'V({sn},{k})') for k in range(n)] + (['0.0f', '0.0f'] if n == 2 else [])
                    emit(f'SETV({dn}, {", ".join(lanes)}); {c}')
                else:
                    raise ValueError(dk)
                continue
            if mn == 'fmov':
                d, s1 = ops
                if s1.startswith('#') and d.startswith('v'):
                    dn, dk, _ = vreg(d)
                    f_ = fimm(s1)
                    lanes = [f_] * 4 if dk == '4s' else [f_, f_, '0.0f', '0.0f'] if dk == '2s' else None
                    if lanes is None:
                        raise ValueError('fmov vec kind')
                    emit(f'SETV({dn}, {", ".join(lanes)}); {c}')
                elif s1.startswith('#'):
                    emit(f'SETS({vreg(d)[0]}, {fimm(s1)}); {c}')
                elif s1 in ('wzr', 'xzr'):
                    emit(f'SETS({vreg(d)[0]}, 0.0f); {c}')
                elif d[0] == 'w':
                    emit(f'{setx(d, f"bits(S({vreg(s1)[0]}))")} {c}')
                elif s1[0] == 'w':
                    emit(f'SETS({vreg(d)[0]}, from_bits({xr(s1)})); {c}')
                elif d[0] == 's' and s1[0] == 's':
                    emit(f'SETS({vreg(d)[0]}, S({vreg(s1)[0]})); {c}')
                elif d.startswith('v') and s1.startswith('#'):
                    raise ValueError('fmov vec imm')
                else:
                    raise ValueError('fmov ' + i.op_str)
                continue
            if mn == 'movi':
                d, imm = ops[0], ops[1]
                dn, dk, _ = vreg(d)
                if imm in ('#0', '#0000000000000000') or dk == '2d' and int(imm.lstrip('#'), 0) == 0:
                    emit(f'SETV({dn}, 0.0f, 0.0f, 0.0f, 0.0f); {c}')
                    continue
                if dk in ('2d', 'd') and int(imm.lstrip('#'), 0) == 0:
                    emit(f'SETV({dn}, 0.0f, 0.0f, 0.0f, 0.0f); {c}')
                    continue
                if dk in ('4s', '2s'):
                    v = int(imm.lstrip('#'), 0)
                    if len(ops) > 2:
                        v <<= int(ops[2].split('#')[1])
                    lane = f'from_bits(0x{v:08x}u)'
                    lanes = [lane] * 4 if dk == '4s' else [lane, lane, '0.0f', '0.0f']
                    emit(f'SETV({dn}, {", ".join(lanes)}); {c}')
                    continue
                if dk in ('16b', '8b'):  # (byte replicated into every lane)
                    b_ = int(imm.lstrip('#'), 0) & 0xff
                    lane = f'from_bits(0x{b_ * 0x01010101:08x}u)'
                    lanes = [lane] * 4 if dk == '16b' else [lane, lane, '0.0f', '0.0f']
                    emit(f'SETV({dn}, {", ".join(lanes)}); {c}')
                    continue
                raise ValueError('movi ' + i.op_str)
            if mn == 'mvni' and vreg(ops[0])[1] in ('4s', '2s'):
                dn, dk, _ = vreg(ops[0])
                v = int(ops[1].lstrip('#'), 0)
                if len(ops) > 2:
                    sh = ops[2].split('#')[1]
                    v = (v << int(sh)) | ((1 << int(sh)) - 1) if 'msl' in ops[2] else v << int(sh)
                v = ~v & 0xffffffff
                lane = f'from_bits(0x{v:08x}u)'
                lanes = [lane] * 4 if dk == '4s' else [lane, lane, '0.0f', '0.0f']
                emit(f'SETV({dn}, {", ".join(lanes)}); {c}')
                continue
            # Double precision (scalar d registers: bits in lanes 0-1 of the register file).
            if mn == 'fcvt' and ops[0][0] in 'sd' and ops[1][0] in 'sd' and ops[0][0] != ops[1][0]:
                dn, sn = vreg(ops[0])[0], vreg(ops[1])[0]
                if ops[0][0] == 'd':
                    emit(f'{{ double d_ = (double)S({sn}); V4 t_{{}}; memcpy(t_.f, &d_, 8); r.v[{dn}] = t_; }} {c}')
                else:
                    emit(f'{{ double d_; memcpy(&d_, r.v[{sn}].f, 8); SETS({dn}, (float)d_); }} {c}')
                continue
            if mn == 'fcmp' and ops[0][0] == 'd':
                bd = '0.0' if ops[1].startswith('#') else f'({{ double b_; memcpy(&b_, r.v[{vreg(ops[1])[0]}].f, 8); b_; }})'
                emit(f'{{ double a_, b_ = {bd}; memcpy(&a_, r.v[{vreg(ops[0])[0]}].f, 8); '
                     f'r.nzcv = (a_ != a_ || b_ != b_) ? 0x3 : a_ == b_ ? 0x6 : a_ < b_ ? 0x8 : 0x2; }} {c}')
                continue
            if mn == 'fcmp':
                a1 = f'S({vreg(ops[0])[0]})'
                b1 = '0.0f' if ops[1].startswith('#') else f'S({vreg(ops[1])[0]})'
                emit(f'FCMP({a1}, {b1}); {c}')
                continue
            if mn == 'fccmp':
                a1, b1, nzcv, cond = ops
                b1e = '0.0f' if b1.startswith('#') else f'S({vreg(b1)[0]})'
                emit(f'if (C_{cond.upper()}()) FCMP(S({vreg(a1)[0]}), {b1e}); else SETNZCV({nzcv.lstrip("#")}); {c}')
                continue
            if mn == 'fcsel':
                d, s1, s2, cond = ops
                emit(f'SETS({vreg(d)[0]}, C_{cond.upper()}() ? S({vreg(s1)[0]}) : S({vreg(s2)[0]})); {c}')
                continue
            if mn == 'fcvtzs':
                d, s1 = ops
                if d[0] == 'w' and s1[0] == 'd':  # double source (saturating, NaN -> 0)
                    m = vreg(s1)[0]
                    emit(f'{{ u64 b_ = (u64)bits(r.v[{m}].f[0]) | ((u64)bits(r.v[{m}].f[1]) << 32); double d_; std::memcpy(&d_, &b_, 8); '
                         f's32 i_ = d_ != d_ ? 0 : d_ >= 2147483648.0 ? INT32_MAX : d_ <= -2147483649.0 ? INT32_MIN : (s32)d_; '
                         f'{setx(d, "(u32)i_")} }} {c}')
                    continue
                if d[0] == 'w':
                    emit(f'{setx(d, f"(u32)fcvtzs(S({vreg(s1)[0]}))")} {c}')
                    continue
                raise ValueError('fcvtzs')
            if mn in ('scvtf', 'ucvtf'):
                d, s1 = ops
                if s1[0] == 'w':
                    cast = '(s32)' if mn == 'scvtf' else '(u32)'
                    emit(f'SETS({vreg(d)[0]}, (float){cast}{xr(s1)}); {c}')
                    continue
                if s1[0] == 's' and mn == 'ucvtf':
                    emit(f'SETS({vreg(d)[0]}, (float)bits(S({vreg(s1)[0]}))); {c}')
                    continue
                raise ValueError(mn)
            if mn in ('ldr', 'str', 'ldur', 'stur') and len(ops) >= 2:
                r, m_ = ops[0], ops[1]
                base, off, idxe, wb = mem(m_)
                post = int(ops[2].lstrip('#'), 0) if len(ops) == 3 else None
                ea = addr_expr(base, off if not post else 0, idxe)
                load = mn in ('ldr', 'ldur')
                ca = const_addr(base, off) if (load and idxe is None and post is None) else None
                if r[0] in 'sq' or r[0] == 'd':
                    n, k, _ = vreg(r)
                    if load and ca is not None:
                        nb = {'s': 4, 'd': 8, 'q': 16}[k]
                        fl = struct.unpack(f'<{nb // 4}I', rd(ca, nb))
                        lanes = [f'K(0x{w:08x})' for w in fl] + ['0.0f'] * (4 - len(fl))
                        emit(f'SETV({n}, {", ".join(lanes)}); {c}')
                    elif load:
                        emit(f'LD{k.upper()}({n}, {ea}); {c}')
                    else:
                        emit(f'ST{k.upper()}({n}, {ea}); {c}')
                elif r[0] in 'wx' or r in ('wzr', 'xzr'):
                    w = 4 if r[0] == 'w' else 8
                    if load:
                        if ca is not None and w == 4:
                            v = struct.unpack('<I' if w == 4 else '<Q', rd(ca, w))[0]
                            emit(f'{setx(r, hex(v))} {c}')
                        else:
                            emit(f'{setx(r, f"LDI{w * 8}({ea})")} {c}')
                    else:
                        emit(f'STI{w * 8}({ea}, {xr(r)}); {c}')
                else:
                    raise ValueError('ldr kind')
                if wb == '!':
                    emit(f'{setx(base, f"{xr(base)} + {off}")}')
                if post is not None:
                    emit(f'{setx(base, f"{xr(base)} + {post}")}')
                if load and r[0] in 'wx':
                    adrp.pop(r.replace('w', 'x'), None)
                continue
            if mn in ('ldrb', 'strb', 'ldrh', 'strh', 'ldrsw', 'ldrsb', 'ldrsh'):
                r, m_ = ops[0], ops[1]
                base, off, idxe, wb = mem(m_)
                ea = addr_expr(base, off, idxe)
                ca = const_addr(base, off) if idxe is None else None
                if mn == 'ldrsw' and idxe is not None and base in adrp and adrp[base] is not None:
                    tbl = adrp[base]
                    ents = []
                    # Table length: the bound of the range check before it (`cmp wN, #K` +
                    # `b.hi`: K + 1 entries) when there is one; the scan also stops at the first
                    # entry that leaves the function. (It used to stop after 64 entries: a
                    # longer table's later cases hit the switch's __builtin_unreachable().)
                    n_ents = 64
                    for back in insns[max(0, idx - 12):idx][::-1]:
                        mb = re.match(r'[wx]\d+, #(0x[0-9a-f]+|\d+)$', back.op_str)
                        if back.mnemonic == 'cmp' and mb:
                            n_ents = max(n_ents, int(mb.group(1), 0) + 1)
                            break
                    for k in range(n_ents):
                        tgt = tbl + struct.unpack('<i', rd(tbl + 4 * k, 4))[0]
                        if not (start <= tgt < start + size) or tgt % 4:
                            break
                        ents.append(tgt)
                    jt_state['tbl'] = ents
                    m = re.match(r'\((.*) << 2\)$', idxe)
                    emit(f'jt_ = {m.group(1)}; {c}')
                    for tgt in ents:
                        targets_late.add(tgt)
                    continue
                if mn == 'ldrb':
                    emit(f'{setx(r, f"LDI8({ea})")} {c}')
                elif mn == 'ldrh':
                    emit(f'{setx(r, f"LDI16({ea})")} {c}')
                elif mn == 'ldrsw':
                    emit(f'{setx(r, f"(s64)(s32)LDI32({ea})")} {c}')
                elif mn == 'ldrsb':
                    emit(f'{setx(r, f"(u64)(s64)(int8_t)LDI8({ea})")} {c}')
                elif mn == 'ldrsh':
                    emit(f'{setx(r, f"(u64)(s64)(int16_t)LDI16({ea})")} {c}')
                elif mn == 'strb':
                    emit(f'STI8({ea}, {xr(r)}); {c}')
                elif mn == 'strh':
                    emit(f'STI16({ea}, {xr(r)}); {c}')
                else:
                    raise ValueError(mn)
                if wb == '!':
                    emit(f'{setx(base, f"{xr(base)} + {off}")}')
                if len(ops) == 3:  # post-index
                    emit(f'{setx(base, f"{xr(base)} + {int(ops[2].lstrip(chr(35)), 0)}")}')
                continue
            if mn in ('ldp', 'stp'):
                r1, r2, m_ = ops[0], ops[1], ops[2]
                base, off, idxe, wb = mem(m_)
                post = int(ops[3].lstrip('#'), 0) if len(ops) == 4 else None
                o0 = 0 if post is not None else off
                if mn == 'ldp' and r1[0] in 'wx' and r1[1:] == base[1:]:
                    # the first destination is the base: both loads use the old base
                    w = 4 if r1[0] == 'w' else 8
                    e0, e1 = addr_expr(base, o0, None), addr_expr(base, o0 + w, None)
                    emit(f'{{ u64 t0_ = LDI{w * 8}({e0}), t1_ = LDI{w * 8}({e1}); {setx(r1, "t0_")} {setx(r2, "t1_")} }} {c}')
                elif r1[0] in 'wx' or r1 in ('wzr', 'xzr'):
                    w = 4 if r1[0] == 'w' else 8
                    for k, r in enumerate((r1, r2)):
                        ea = addr_expr(base, o0 + k * w, None)
                        if mn == 'ldp':
                            emit(f'{setx(r, f"LDI{w * 8}({ea})")} {c}')
                        else:
                            emit(f'STI{w * 8}({ea}, {xr(r)}); {c}')
                else:
                    n1, k1, _ = vreg(r1)
                    n2, _, _ = vreg(r2)
                    w = {'s': 4, 'd': 8, 'q': 16}[k1]
                    ca = const_addr(base, off) if mn == 'ldp' and post is None else None
                    for k, n in enumerate((n1, n2)):
                        ea = addr_expr(base, o0 + k * w, None)
                        if ca is not None:
                            fl = struct.unpack(f'<{w // 4}I', rd(ca + k * w, w))
                            lanes = [f'K(0x{x:08x})' for x in fl] + ['0.0f'] * (4 - len(fl))
                            emit(f'SETV({n}, {", ".join(lanes)}); {c}')
                        elif mn == 'ldp':
                            emit(f'LD{k1.upper()}({n}, {ea}); {c}')
                        else:
                            emit(f'ST{k1.upper()}({n}, {ea}); {c}')
                if wb == '!':
                    emit(f'{setx(base, f"{xr(base)} + {off}")}')
                if post is not None:
                    emit(f'{setx(base, f"{xr(base)} + {post}")}')
                continue
            if mn == 'adrp':
                v = int(ops[1].lstrip('#'), 16)
                adrp[ops[0]] = v
                emit(f'{setx(ops[0], f"LIB + 0x{v:x}")} {c}')
                continue
            if mn in ('mov', 'movz') and ops[0][0] in 'wx' and not ops[1].startswith('v'):
                d, s1 = ops
                if s1.startswith('#'):
                    emit(f'{setx(d, s1.lstrip("#"))} {c}')
                else:
                    emit(f'{setx(d, xr(s1))} {c}')
                    if s1 in adrp:
                        adrp[d] = adrp[s1]
                        continue
                adrp.pop(d.replace('w', 'x'), None)
                continue
            if mn == 'movk':
                d, imm = ops[0], ops[1]
                sh = int(ops[2].split('#')[1]) if len(ops) > 2 else 0
                v = int(imm.lstrip('#'), 0)
                emit(f'{setx(d, f"({xr(d)} & ~(0xffffull << {sh})) | ((u64){hex(v)} << {sh})")} {c}')
                continue
            if mn == 'mov' and ops[0].startswith('v') and ops[1].startswith('v'):
                d, s1 = ops
                dn, dk, dl = vreg(d)
                sn, sk, sl = vreg(s1)
                if dk == '16b' and sk == '16b':
                    emit(f'r.v[{dn}] = r.v[{sn}]; {c}')
                elif dk == 'd' and sk == 'd' and dl is not None and sl is not None:
                    emit(f'{{ float lo_ = V({sn},{2 * sl}), hi_ = V({sn},{2 * sl + 1}); r.v[{dn}].f[{2 * dl}] = lo_; r.v[{dn}].f[{2 * dl + 1}] = hi_; }} {c}')
                elif dk == 's' and sk == 's' and dl is not None and sl is not None:
                    emit(f'r.v[{dn}].f[{dl}] = V({sn},{sl}); {c}')
                else:
                    raise ValueError('mov v')
                continue
            if mn == 'mov' and ops[0][0] == 's' and ops[1].startswith('v'):
                sn, sk_, sl = vreg(ops[1])
                if sk_ != 's':
                    raise ValueError('mov lane kind')
                emit(f'SETS({vreg(ops[0])[0]}, V({sn},{sl})); {c}')
                continue
            if mn == 'dup' and ops[1][0] in 'wx':
                dn, dk, _ = vreg(ops[0])
                if dk not in ('4s', '2s'):
                    raise ValueError('dup gp kind')
                lanes = ['t_'] * (4 if dk == '4s' else 2) + (['0.0f', '0.0f'] if dk == '2s' else [])
                emit(f'{{ float t_ = from_bits((u32){xr(ops[1])}); SETV({dn}, {", ".join(lanes)}); }} {c}')
                continue
            if mn == 'dup' and ops[0].endswith('.2d') and ops[1].startswith('v'):
                dn, sn, sl = vreg(ops[0])[0], vreg(ops[1])[0], vreg(ops[1])[2]
                emit(f'{{ float lo_ = V({sn},{2 * sl}), hi_ = V({sn},{2 * sl + 1}); SETV({dn}, lo_, hi_, lo_, hi_); }} {c}')
                continue
            if mn == 'dup':
                d, s1 = ops
                dn, dk, _ = vreg(d)
                sn, sk_, sl = vreg(s1)
                if sk_ != 's' or dk not in ('4s', '2s'):
                    raise ValueError('dup kind')
                n = 4 if dk == '4s' else 2
                lanes = [f'V({sn},{sl})'] * n + (['0.0f', '0.0f'] if n == 2 else [])
                emit(f'{{ float t_ = V({sn},{sl}); SETV({dn}, {", ".join(["t_"] * n + (["0.0f", "0.0f"] if n == 2 else []))}); }} {c}')
                continue
            if mn == 'ext':
                d, s1, s2, imm = ops
                k = int(imm.lstrip('#'), 0)
                if d.endswith('16b') and k % 4 == 0:
                    dn, sn, tn = vreg(d)[0], vreg(s1)[0], vreg(s2)[0]
                    lanes = [(f'a_.f[{j}]' if j < 4 else f'b_.f[{j - 4}]') for j in range(k // 4, k // 4 + 4)]
                    emit(f'{{ V4 a_ = r.v[{sn}], b_ = r.v[{tn}]; SETV({dn}, {", ".join(lanes)}); }} {c}')
                    continue
                if d.endswith('.8b') and k == 4:  # 64-bit form: [s1.s[1], s2.s[0]], upper half zeroed
                    dn, sn, tn = vreg(d)[0], vreg(s1)[0], vreg(s2)[0]
                    emit(f'{{ float a_ = V({sn},1), b_ = V({tn},0); SETV({dn}, a_, b_, 0.0f, 0.0f); }} {c}')
                    continue
                raise ValueError('ext')
            if mn == 'rev64' and ops[0].endswith('.2s'):
                dn, sn = vreg(ops[0])[0], vreg(ops[1])[0]
                emit(f'{{ V4 a_ = r.v[{sn}]; SETV({dn}, a_.f[1], a_.f[0], 0.0f, 0.0f); }} {c}')
                continue
            if mn == 'rev64' and ops[0].endswith('.4s'):
                dn, sn = vreg(ops[0])[0], vreg(ops[1])[0]
                emit(f'{{ V4 a_ = r.v[{sn}]; SETV({dn}, a_.f[1], a_.f[0], a_.f[3], a_.f[2]); }} {c}')
                continue
            if mn == 'mov' and ops[0][0] == 'w' and ops[1].startswith('v'):
                sn, sk_, sl = vreg(ops[1])
                if sk_ != 's':
                    raise ValueError('umov lane kind')
                emit(f'{setx(ops[0], f"bits(V({sn},{sl}))")} {c}')
                continue
            if mn in ('fcmlt', 'fcmgt', 'fcmge', 'fcmle', 'fcmeq') and ops[0].startswith('v'):
                dn, dk, _ = vreg(ops[0])
                an = vreg(ops[1])[0]
                n = 4 if dk == '4s' else 2
                op = {'fcmlt': '<', 'fcmgt': '>', 'fcmge': '>=', 'fcmle': '<=', 'fcmeq': '=='}[mn]
                lanes = []
                for k in range(n):
                    rhs = '0.0f' if ops[2].startswith('#') else f'V({vreg(ops[2])[0]},{k})'
                    lanes.append(f'from_bits((V({an},{k}) {op} {rhs}) ? 0xffffffffu : 0u)')
                lanes += ['0.0f'] * (4 - n)
                emit(f'SETV({dn}, {", ".join(lanes)}); {c}')
                continue
            if mn in ('bsl', 'bit', 'bif', 'bic', 'orr', 'and', 'eor') and ops[0].startswith('v'):
                dn, dk, _ = vreg(ops[0])
                an = vreg(ops[1])[0]
                n = 4 if dk == '16b' else 2
                if ops[2].startswith('#'):
                    raise ValueError('vec logic imm')
                bn = vreg(ops[2])[0]
                lanes = []
                for k in range(n):
                    d_, a_, b_ = f'bits(V({dn},{k}))', f'bits(V({an},{k}))', f'bits(V({bn},{k}))'
                    e = {'bsl': f'({d_} & {a_}) | (~{d_} & {b_})', 'bit': f'({a_} & {b_}) | ({d_} & ~{b_})',
                         'bif': f'({d_} & {b_}) | ({a_} & ~{b_})', 'bic': f'{a_} & ~{b_}', 'orr': f'{a_} | {b_}',
                         'and': f'{a_} & {b_}', 'eor': f'{a_} ^ {b_}'}[mn]
                    lanes.append(f'from_bits({e})')
                lanes += ['0.0f'] * (4 - n)
                emit(f'SETV({dn}, {", ".join(lanes)}); {c}')
                continue
            if mn in ('fmin', 'fmax', 'fminnm', 'fmaxnm') and ops[0].startswith('v'):
                dn, dk, _ = vreg(ops[0])
                an, bn = vreg(ops[1])[0], vreg(ops[2])[0]
                n = 4 if dk == '4s' else 2
                lanes = [f'A64_{mn.upper()}(V({an},{k}), V({bn},{k}))' for k in range(n)] + ['0.0f'] * (4 - n)
                emit(f'SETV({dn}, {", ".join(lanes)}); {c}')
                continue
            if mn == 'st1':
                m = re.match(r'\{v(\d+)\.s\}\[(\d+)\], (\[\w+\])$', i.op_str)
                if not m:
                    raise ValueError('st1 form')
                base, off, idxe, wb = mem(m.group(3))
                emit(f'stf({addr_expr(base, off, idxe)}, V({m.group(1)},{m.group(2)})); {c}')
                continue
            if mn in ('ldarb', 'ldar', 'ldaxr', 'ldarh'):
                r_, m_ = ops[0], ops[1]
                base, off, idxe, wb = mem(m_)
                w = {'ldarb': 8, 'ldarh': 16}.get(mn, 32 if r_[0] == 'w' else 64)
                emit(f'{setx(r_, f"LDI{w}({addr_expr(base, off, idxe)})")} {c}')
                continue
            if mn in ('frsqrte', 'frsqrts'):
                dn, dk, _ = vreg(ops[0])
                srcs = [vreg(o)[0] for o in ops[1:]]
                n = 4 if dk == '4s' else 2 if dk == '2s' else 1
                def lane2(k):
                    if mn == 'frsqrte':
                        return f'frsqrte(V({srcs[0]},{k}))'
                    return f'frsqrts(V({srcs[0]},{k}), V({srcs[1]},{k}))'
                if dk == 's':
                    emit(f'SETS({dn}, {lane2(0)}); {c}')
                else:
                    lanes = [lane2(k) for k in range(n)] + ['0.0f'] * (4 - n)
                    emit(f'SETV({dn}, {", ".join(lanes)}); {c}')
                continue
            if mn in ('frecpe', 'frecps'):
                dn, dk, _ = vreg(ops[0])
                srcs = [vreg(o)[0] for o in ops[1:]]
                n = 4 if dk == '4s' else 2 if dk == '2s' else 1
                def lane(k):
                    if mn == 'frecpe':
                        return f'frecpe(V({srcs[0]},{k}))'
                    return f'frecps(V({srcs[0]},{k}), V({srcs[1]},{k}))'
                if dk == 's':
                    emit(f'SETS({dn}, {lane(0)}); {c}')
                else:
                    lanes = [lane(k) for k in range(n)] + ['0.0f'] * (4 - n)
                    emit(f'SETV({dn}, {", ".join(lanes)}); {c}')
                continue
            if mn in ('ubfx', 'sbfx'):
                d, s1, lsb, w = ops
                lsb, w = int(lsb.lstrip('#'), 0), int(w.lstrip('#'), 0)
                if mn == 'ubfx':
                    e = f'({xr(s1)} >> {lsb}) & {hex((1 << w) - 1)}'
                else:
                    e = f'(u64)(((s64){xr(s1)} << {64 - lsb - w}) >> {64 - w})'
                emit(f'{setx(d, e)} {c}')
                continue
            if mn == 'faddp':
                if len(ops) == 2:  # scalar pairwise: s = v.2s[0] + v.2s[1]
                    dn, sn = vreg(ops[0])[0], vreg(ops[1])[0]
                    emit(f'SETS({dn}, {PADD(f"V({sn},0)", f"V({sn},1)")}); {c}')
                    continue
                d, s1, s2 = ops
                dn, dk, _ = vreg(d)
                an, bn = vreg(s1)[0], vreg(s2)[0]
                if dk == '2s':
                    emit(f'{{ V4 a_ = r.v[{an}], b_ = r.v[{bn}]; SETV({dn}, {PADD("a_.f[0]", "a_.f[1]")}, {PADD("b_.f[0]", "b_.f[1]")}, 0.0f, 0.0f); }} {c}')
                    continue
                if dk == '4s':
                    emit(f'{{ V4 a_ = r.v[{an}], b_ = r.v[{bn}]; SETV({dn}, {PADD("a_.f[0]", "a_.f[1]")}, {PADD("a_.f[2]", "a_.f[3]")}, {PADD("b_.f[0]", "b_.f[1]")}, {PADD("b_.f[2]", "b_.f[3]")}); }} {c}')
                    continue
                raise ValueError('faddp')
            # ---- integer ----
            if mn in ('add', 'sub', 'adds', 'subs') and ops[0][0] in 'wxs' and ops[0] != 'sp' or (mn in ('add', 'sub') and ops[0] == 'sp'):
                d, s1, s2 = ops[0], ops[1], ops[2]
                ext = ops[3] if len(ops) > 3 else None
                if s2.startswith('#'):
                    v = int(s2.lstrip('#'), 0)
                    if ext and 'lsl' in ext:
                        v <<= int(ext.split('#')[1])
                    rhs = str(v)
                    if mn == 'add' and s1 in adrp and adrp[s1] is not None:
                        adrp[d] = adrp[s1] + v
                        emit(f'{setx(d, f"{xr(s1)} + {v}")} {c}')
                        continue
                else:
                    rhs = xr(s2)
                    if ext:
                        m = re.match(r'(lsl|lsr|asr|uxtw|sxtw|uxth|sxth|uxtb|sxtb|uxtx|sxtx)(?: #(\d+))?', ext)
                        if not m:
                            raise ValueError('add ext ' + ext)
                        kind, sh = m.group(1), int(m.group(2) or 0)
                        if kind in ('uxth', 'sxth', 'uxtb', 'sxtb'):
                            cast = {'uxth': '(u64)(u16)', 'sxth': '(u64)(s64)(int16_t)', 'uxtb': '(u64)(u8)', 'sxtb': '(u64)(s64)(int8_t)'}[kind]
                            rhs = f'({cast}{rhs} << {sh})'
                        elif kind in ('uxtx', 'sxtx'):
                            rhs = f'({rhs} << {sh})'
                        elif kind == 'sxtw':
                            rhs = f'((u64)(s64)(s32){rhs} << {sh})'
                        elif kind == 'uxtw':
                            rhs = f'((u64)(u32){rhs} << {sh})'
                        elif kind == 'lsl':
                            rhs = f'({rhs} << {sh})'
                        elif kind == 'lsr':
                            rhs = f'({rhs} >> {sh})'
                        else:
                            rhs = f'(u64)((s64){rhs} >> {sh})' if d[0] == 'x' else f'(u32)((s32){rhs} >> {sh})'
                op = '+' if mn.startswith('add') else '-'
                if mn in ('adds', 'subs'):
                    emit(f'{"ICMN" if op == "+" else "ICMP"}{"64" if d[0] == "x" else "32"}({xr(s1)}, {rhs}); {c}')
                emit(f'{setx(d, f"{xr(s1)} {op} {rhs}")} {c}')
                adrp.pop(d.replace('w', 'x'), None)
                continue
            if mn in ('cmp', 'cmn', 'tst'):
                s1, s2 = ops[0], ops[1]
                w64 = s1[0] == 'x'
                if s2.startswith('#'):
                    rhs = str(int(s2.lstrip('#'), 0))
                    if len(ops) > 2:
                        m = re.match(r'lsl #(\d+)$', ops[2])
                        if not m:
                            raise ValueError('cmp imm shift')
                        rhs = str(int(rhs) << int(m.group(1)))
                else:
                    rhs = xr(s2)
                    if len(ops) > 2:
                        m = re.match(r'(lsl|lsr|asr|uxtb|uxth|uxtw|uxtx|sxtb|sxth|sxtw|sxtx)(?: #(\d+))?$', ops[2])
                        if not m:
                            raise ValueError('cmp shift')
                        k, sh = m.group(1), int(m.group(2) or 0)
                        casts = {'uxtb': '(u64)(u8)', 'uxth': '(u64)(u16)', 'uxtw': '(u64)(u32)', 'uxtx': '(u64)',
                                 'sxtb': '(u64)(s64)(int8_t)', 'sxth': '(u64)(s64)(int16_t)', 'sxtw': '(u64)(s64)(s32)', 'sxtx': '(u64)'}
                        if k in casts:
                            rhs = f'({casts[k]}{rhs} << {sh})'
                        elif k == 'lsl':
                            rhs = f'((u64){rhs} << {sh})'
                        elif k == 'lsr':
                            rhs = f'({rhs} >> {sh})'
                        else:
                            rhs = f'(u64)((s64){rhs} >> {sh})' if w64 else f'(u32)((s32){rhs} >> {sh})'
                if mn == 'tst':
                    emit(f'ITST{"64" if w64 else "32"}({xr(s1)}, {rhs}); {c}')
                elif mn == 'cmn':
                    emit(f'ICMN{"64" if w64 else "32"}({xr(s1)}, {rhs}); {c}')
                else:
                    emit(f'ICMP{"64" if w64 else "32"}({xr(s1)}, {rhs}); {c}')
                continue
            if mn in ('orn', 'eon') and ops[0][0] in 'wx' and not ops[2].startswith('#'):
                d, s1, s2 = ops[0], ops[1], ops[2]
                rhs = xr(s2)
                if len(ops) > 3:
                    rhs = shift_expr(rhs, ops[3], d[0] == 'x')
                o = '|' if mn == 'orn' else '^'
                emit(f'{setx(d, f"{xr(s1)} {o} ~(u64)({rhs})")} {c}')
                continue
            if mn in ('and', 'orr', 'eor', 'bic') and ops[0][0] in 'wx':
                d, s1, s2 = ops[0], ops[1], ops[2]
                rhs = s2.lstrip('#') if s2.startswith('#') else xr(s2)
                if len(ops) > 3:
                    rhs = shift_expr(rhs, ops[3], d[0] == 'x')
                o = {'and': '&', 'orr': '|', 'eor': '^'}.get(mn)
                if mn == 'bic':
                    emit(f'{setx(d, f"{xr(s1)} & ~(u64)({rhs})")} {c}')
                else:
                    emit(f'{setx(d, f"{xr(s1)} {o} ({rhs})")} {c}')
                continue
            if mn in ('lsl', 'lsr', 'asr') and ops[2].startswith('#'):
                d, s1, sh = ops[0], ops[1], ops[2].lstrip('#')
                if mn == 'lsl':
                    e = f'{xr(s1)} << {sh}'
                elif mn == 'lsr':
                    e = f'{xr(s1)} >> {sh}'
                else:
                    e = f'(s64){xr(s1)} >> {sh}' if d[0] == 'x' else f'(s32){xr(s1)} >> {sh}'
                emit(f'{setx(d, e)} {c}')
                continue
            if mn in ('cset', 'csetm'):
                d, cond = ops
                v = '1' if mn == 'cset' else ('~0ull' if d[0] == 'x' else '0xffffffffu')
                emit(f'{setx(d, f"C_{cond.upper()}() ? {v} : 0")} {c}')
                continue
            if mn in ('csel', 'csinc', 'cneg', 'csneg', 'csinv'):
                if mn == 'cneg':
                    d, s1, cond = ops
                    emit(f'{setx(d, f"C_{cond.upper()}() ? 0 - {xr(s1)} : {xr(s1)}")} {c}')
                    continue
                d, s1, s2, cond = ops
                alt = {'csel': xr(s2), 'csinc': f'{xr(s2)} + 1', 'csneg': f'0 - {xr(s2)}', 'csinv': f'~{xr(s2)}'}[mn]
                emit(f'{setx(d, f"C_{cond.upper()}() ? {xr(s1)} : {alt}")} {c}')
                continue
            if mn in ('udiv', 'sdiv', 'mul', 'msub', 'madd'):
                if mn == 'udiv':
                    d, s1, s2 = ops
                    emit(f'{setx(d, f"{xr(s2)} ? {xr(s1)} / {xr(s2)} : 0")} {c}')
                elif mn == 'mul':
                    d, s1, s2 = ops
                    emit(f'{setx(d, f"{xr(s1)} * {xr(s2)}")} {c}')
                else:
                    d, s1, s2, s3 = ops
                    op = '-' if mn == 'msub' else '+'
                    emit(f'{setx(d, f"{xr(s3)} {op} {xr(s1)} * {xr(s2)}")} {c}')
                continue
            if mn in ('smull', 'umull'):
                d, s1, s2 = ops
                cast = '(s64)(s32)' if mn == 'smull' else '(u64)(u32)'
                emit(f'{setx(d, f"(u64)({cast}{xr(s1)} * {cast}{xr(s2)})")} {c}')
                continue
            if mn in ('sxtb', 'sxth', 'uxtb', 'uxth'):
                d, s1 = ops
                cast = {'sxtb': '(s64)(int8_t)', 'sxth': '(s64)(int16_t)', 'uxtb': '(u64)(u8)', 'uxth': '(u64)(u16)'}[mn]
                emit(f'{setx(d, f"(u64)({cast}{xr(s1)})")} {c}')
                continue
            if mn == 'sxtw':
                emit(f'{setx(ops[0], f"(u64)(s64)(s32){xr(ops[1])}")} {c}')
                continue
            if mn == 'sbfiz':
                d, s1, lsb, w = ops
                if int(w.lstrip('#'), 0) != 32:
                    raise ValueError('sbfiz width')
                emit(f'{setx(d, f"(u64)((s64)(s32){xr(s1)} << {lsb.lstrip(chr(35))})")} {c}')
                continue
            # ---- control ----
            if mn == 'b':
                t = int(ops[0].lstrip('#'), 16)
                if start <= t < start + size:
                    emit(f'goto L_{t:x}; {c}')
                else:
                    n = L.name(t).replace('PLT:', '')
                    call = CALLS.get(n) or EXTRA_CALLS.get(n)
                    if not call and CALL_FALLBACK:
                        call = CALL_FALLBACK('b', t, None)
                    if not call:
                        raise ValueError('tail call ' + n)
                    emit(f'{call.format(plt=t) if "{plt" in call else call} goto L_ret; {c}  // tail call')
                continue
            if mn.startswith('b.') and mn[2:] in COND:
                t = int(ops[0].lstrip('#'), 16)
                emit(f'if (C_{mn[2:].upper()}()) goto L_{t:x}; {c}')
                continue
            if mn in ('cbz', 'cbnz'):
                t = int(ops[1].lstrip('#'), 16)
                emit(f'if ({xr(ops[0])} {"==" if mn == "cbz" else "!="} 0) goto L_{t:x}; {c}')
                continue
            if mn in ('tbz', 'tbnz'):
                bit = int(ops[1].lstrip('#'), 0)
                t = int(ops[2].lstrip('#'), 16)
                emit(f'if ((({xr(ops[0])} >> {bit}) & 1) {"==" if mn == "tbz" else "!="} 0) goto L_{t:x}; {c}')
                continue
            if mn == 'bl':
                t = int(ops[0].lstrip('#'), 16)
                n = L.name(t)
                n = n.replace('PLT:', '')
                call = CALLS.get(n) or EXTRA_CALLS.get(n)
                if not call and CALL_FALLBACK:
                    call = CALL_FALLBACK('bl', t, None)
                if not call:
                    raise ValueError('call ' + n)
                emit(f'{call.format(plt=t)} {c}' if '{plt' in call else f'{call} {c}')
                continue
            if mn == 'br' and jt_state.get('tbl'):
                cases = ' '.join(f'case {k}: goto L_{t:x};' for k, t in enumerate(jt_state['tbl']))
                emit(f'switch (jt_) {{ {cases} default: __builtin_unreachable(); }} {c}')
                jt_state['tbl'] = None
                continue
            if mn in ('blr', 'br') and CALL_FALLBACK:
                call = CALL_FALLBACK(mn, None, xr(ops[0]))
                emit(f'{call} {"goto L_ret; " if mn == "br" else ""}{c}')
                continue
            if mn == 'add' and len(ops) == 3 and jt_state.get('tbl') and not ops[2].startswith('#'):
                emit(f'/* {a:x}: {mn} {i.op_str} (jump-table address) */')
                continue
            if mn in ('ld2', 'ld3', 'ld4') and re.match(r'\{v\d+\.4s(, v\d+\.4s)+\}, \[\w+\]$', i.op_str):
                # structure loads of 32-bit elements, de-interleaved: element j of register k is word j*n+k
                regs = [int(x) for x in re.findall(r'v(\d+)\.4s', i.op_str)]
                n_ = int(mn[2])
                if len(regs) != n_:
                    raise ValueError('ldN regs')
                base, off, idxe, wb = mem(re.search(r'\[\w+\]', i.op_str).group(0))
                ea = addr_expr(base, off, idxe)
                loads = ' '.join(f'SETV({rg}, {", ".join(f"ldf(a_ + {4 * (j * n_ + k)})" for j in range(4))});' for k, rg in enumerate(regs))
                emit(f'{{ u64 a_ = {ea}; {loads} }} {c}')
                continue
            if mn in ('ld1r', 'ld1'):
                m = re.match(r'\{v(\d+)\.(\w+)\}(?:\[(\d+)\])?, (\[\w+\])(?:, #(\w+))?$', i.op_str)
                if not m:
                    raise ValueError('ld1 form')
                n, k, lane, mm, post = int(m.group(1)), m.group(2), m.group(3), m.group(4), m.group(5)
                base, off, idxe, wb = mem(mm)
                ea = addr_expr(base, off, idxe)
                if mn == 'ld1r' and k == '4s':
                    emit(f'{{ float t_ = ldf({ea}); SETV({n}, t_, t_, t_, t_); }} {c}')
                elif mn == 'ld1r' and k == '2s':
                    emit(f'{{ float t_ = ldf({ea}); SETV({n}, t_, t_, 0.0f, 0.0f); }} {c}')
                elif mn == 'ld1r' and k in ('16b', '8h', '2d'):  # integer replicate (bit patterns in the float lanes)
                    if k == '2d':
                        emit(f'{{ u64 t_ = ldi<u64>({ea}); float lo_ = from_bits((u32)t_), hi_ = from_bits((u32)(t_ >> 32)); '
                             f'SETV({n}, lo_, hi_, lo_, hi_); }} {c}')
                    else:
                        rep = '(u32)ldi<uint8_t>({ea}) * 0x01010101u' if k == '16b' else '(u32)ldi<uint16_t>({ea}) * 0x00010001u'
                        emit(f'{{ float t_ = from_bits({rep.format(ea=ea)}); SETV({n}, t_, t_, t_, t_); }} {c}')
                elif mn == 'ld1' and k == 's' and lane is not None:
                    emit(f'r.v[{n}].f[{lane}] = ldf({ea}); {c}')
                else:
                    raise ValueError('ld1 kind')
                if post:
                    emit(f'{setx(base, f"{xr(base)} + {int(post, 0)}")}')
                continue
            if mn == 'mrs' and ops[1] == 'tpidr_el0' and TPIDR:  # the guest thread pointer (stack protector canary at +0x28)
                emit(f'{setx(ops[0], TPIDR)} {c}')
                continue
            if mn == 'ret':
                emit(f'goto L_ret; {c}')
                continue
            if mn == 'brk':  # a trap (__builtin_trap): the port's CPU treats a guest BRK as fatal (cpu.cpp ExceptionRaised)
                emit(f'a2c_brk(LIB + 0x{a:x}, {int(ops[0].lstrip("#"), 0)}); {c}')
                continue
            if mn in ('prfm',):
                continue
            raise ValueError('unsupported')
        except (ValueError, KeyError) as e:
            emit(f'#error "a2c: {e}: {mn} {i.op_str} @{a:x}"')
    missing = targets_late - targets
    if missing:
        # jump-table targets discovered during emission: insert their labels
        final = []
        for line in out:
            mm_ = re.match(r'    .*/\* ([0-9a-f]+): ', line)
            if mm_ and int(mm_.group(1), 16) in missing:
                ad = int(mm_.group(1), 16)
                final.append(f'L_{ad:x}:')
                missing.discard(ad)
            final.append(line)
        out = final
    res = [f'// Transcribed from {dem(arg) if not arg.startswith("0x") else arg} @0x{start:x} (a2c.py)']
    res += out
    res.append('L_ret:;')
    return '\n'.join(res) + '\n'


def main():
    print(translate(sys.argv[1], sys.argv[2]), end='')


if __name__ == '__main__':
    main()
