#!/usr/bin/env python3
"""Generates port/src/native/models/gen/models_a2c.cpp: the model / animation object layer transcribed by a2c.py.

Every function in FUNCS (plus every other instantiation whose machine code is identical, see
`clusters`) becomes a C++ body over the a2c register file, a guest hook, and an entry in a dispatch
table. Calls inside the bodies are resolved like this:
  - static calls (bl/b) to another transcribed function: a direct C++ call;
  - static calls to Aska math functions with a native version (aska_math.h): a direct call;
  - memset/memcpy/memmove: the host functions;
  - indirect calls (blr/br, i.e. virtual calls): models_icall(), which looks the target up in the
    dispatch table and falls back to the guest;
  - anything else: models_gcall(), a guest call with the full argument register file.

Symbols with a hand-written implementation (tools/models_readable.py -> models_anim.cpp) are
registered from models_anim_tab.inc (written next to <out.cpp>) instead; their transcriptions are
still generated, as the reference the tests compare against (g_models_ref_fns), and calls to them
from transcribed bodies go through the dispatch table.

Usage: gen_models_a2c.py <out.cpp> [<insn.cpp>]
"""
import bisect
import hashlib
import importlib.util
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import genlib  # noqa: E402 (before a2c / elfinfo: the default lib is 3.7.0's; tools/genlib.py)
_spec = importlib.util.spec_from_file_location('a2c', os.path.join(HERE, 'a2c.py'))
a2c = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(a2c)
L = a2c.L

OUT = sys.argv[1]

# ---- what to transcribe (mangled symbols; groups are for SOA_MODELS_OFF) ----
GROUPS = {
    # animation evaluation: AafHandler -> per-controller CalcValue -> SetValueToTarget
    'anim': [
        r'_ZN4Aska10AafHandler9SetValuesEf$',
        r'_ZN4Aska10AafHandler11BlendValuesEff$',
        r'_ZN4Aska15AafBlendManager11_CalcNotify7HandlerEm$',
        r'_ZN4Aska15AafBlendManager16NormalizeWeightsEv$',
        r'_ZN4Aska15AafBlendManager12SetPlayFrameEif$',
        r'_ZN4Aska15AafBlendManager9SetWeightEif$',
        r'_ZNK4Aska15AafBlendManager9GetWeightEi$',
        r'_ZN4Aska20AafCalcCommonFunctor20CalcAndSetSubFunctorINS_11AafCalcTypeILNS_17kTYPE_AAFCALCCNTRE0ELNS_19kTYPE_AAFCALCANDSETE0ELNS_18kTYPE_AAFCALCSPEEDE0ELNS_13kTYPE_AAFCALCE0ELNS_22kTYPE_AAFLOOPCONDITIONE0EEELb0ELb[01]ELS3_0EEclEPNS_10AafHandlerEPNS_11IAnimatableEPNS_11IControllerEffj$',
        r'_ZN4Aska20AafCalcCommonFunctor10CheckCacheINS_11AafCalcTypeILNS_17kTYPE_AAFCALCCNTRE0ELNS_19kTYPE_AAFCALCANDSETE0ELNS_18kTYPE_AAFCALCSPEEDE0ELNS_13kTYPE_AAFCALCE0ELNS_22kTYPE_AAFLOOPCONDITIONE0EEEEEvPNS_10AafHandlerEPjSB_PPNS_17AafControllerInfoERiSF_PtSG_SF_jPNS_11IAnimatableEfPNS_25FrameSortDataForSearchOldEj$',
        r'_ZN4Aska21AafKeyFrameController18UpdateCurrentRangeEv$',
        r'_ZN4Aska13AafController23IsIndependentControllerEv$',
        r'_ZNK4Aska39AafKeyframeData_Quaternion_Linear_U32EX8GetValueEPf$',
        # controllers: value evaluation and target setters of the instantiations that run
        r'_ZN4Aska20TAafNormalControllerINS_7AafTypeINS_\d+AafControlPoint_(Normal|Vector|Quaternion_Step|Quaternion_Linear|Quaternion_Linear_U32EX|Vector_Step_U16)ELb0ELb0ELj0EEEE(9CalcValueEPvf|12CalcValueSubEPvfb|17CalcValueConstantEPvi)$',
        r'_ZN4Aska\d+TAaf(TranslateX|TranslateY|TranslateXYZ|RotateQuaternion)ControllerINS_20TAafNormalControllerINS_7AafTypeINS_\d+AafControlPoint_(Normal|Vector|Quaternion_Step|Quaternion_Linear|Quaternion_Linear_U32EX|Vector_Step_U16)ELb0ELb0ELj0EEEEEE\d+(SetValueOfDirectAddr|SetValueToTarget|BlendValueOfDirectAddr|BlendValueToTarget)E',
        # every instantiation of the per-frame controller methods (vtable slots 0x60, 0x140-0x188,
        # 0x1c8), whether or not the profiled sessions ran it: 312 code shapes cover ~4,700
        # instantiations
        r'_ZNK?4Aska\d+TAaf\w*E\d+(CalcValueEPvf|CalcValueSubEPvfb|CalcValueConstantEPvi|CalcValueComplementEPvfff|CalcValueByLinearAtPreOutOfRangeEPvf|CalcValueByLinearAtPostOutOfRangeEPvf|SetValueOfDirectAddrEPvS\w*|SetValueToTargetEPvPNS_14AafSetValueArgE|BlendValueOfDirectAddrEPvS\w*|BlendValueToTargetEPvPNS_14AafSetValueArgE|AddValueOfDirectAddrEPvS\w*|AddValueToTargetEPvPNS_14AafSetValueArgE|SetControlPointsE\w*)$',
        r'_ZNK4Aska\d+AafKeyframeData_\w+8GetValueEPf$',
        # the whole evaluation functor family and the AafHandler entry points into it
        r'_ZN4Aska20AafCalcCommonFunctor\w+$',
        r'_ZN4Aska10AafHandler(9SetValuesEf|9SetValuesEfi|11BlendValuesEff|9AddValuesEf|18SetValuesHighSpeedEf|18SetValuesHighSpeedEfi|11SetOneValue\w+|25RenewalAllControllerCacheEf|34Function_RenewalAllControllerCache\w+|34Function_RenewalOneControllerCache\w+|21CalcDifferenceOfValue\w+|31CalcAndSetDifferenceOfValueMain\w+)$',
        r'_ZN4Aska10AafHandler25RenewalOneControllerCacheILi\d+EEEvfi$',
    ],
    # bone / node matrices
    'hier': [
        r'_Z41Function_UpdateHierarchicallyByUsingStackILi256ELb0EEvPN4Aska27HierarchicalObjectContainerE$',
        r'_ZN4Aska27HierarchicalObjectContainer10MakeMatrixEv$',
        r'_ZN4Aska27HierarchicalObjectContainer20MakeTransformParamExEv$',
        r'_ZN4Aska27HierarchicalObjectContainer17IterateMakeMatrixEv$',
        r'_ZN4Aska27HierarchicalObjectContainer12OpenIteratorEv$',
        r'_ZN4Aska27HierarchicalObjectContainer13AddToIteratorEv$',
        r'_ZNK4Aska27HierarchicalObjectContainer19GetChildObjectCountEv$',
        r'_ZNK4Aska27HierarchicalObjectContainer11ChildObjectEi$',
        r'_ZN4Aska11JointObject10MakeMatrixEv$',
        r'_ZN4Aska18HierarchicalObject11SetPositionE(fff|PKNS_6VectorE)$',
        r'_ZN4Aska18HierarchicalObject10SetPostureE(fff|ffff|PKNS_10QuaternionE)$',
        r'_ZN4Aska18HierarchicalObject8SetScaleE(fff|PKNS_6VectorE)$',
        r'_ZN4Aska18HierarchicalObject14SetWorldMatrixEPKNS_6MatrixE$',
        r'_ZN4Aska18HierarchicalObject3RunEi$',
        r'_ZNK4Aska18HierarchicalObject11WorldMatrixEv$',
        r'_ZN4Aska12SkinMatrices16MakeSkinMatricesEv$',
        r'_ZN4Aska18SkinMatricesSimple16MakeSkinMatricesEv$',
        r'_ZN4Aska16SkinMatricesBase11KickPaletteEPNS_8Matrix34E$',
    ],
}

dyn = a2c.syms  # name -> (addr, size)
by_addr = {}
for n, (a, s) in dyn.items():
    by_addr.setdefault(a, n)

# ---- code-shape clustering: instantiations with identical machine code share one body ----
def shape(addr, size):
    """Instruction stream with PC-relative operands resolved to absolute targets: two functions
    with equal shapes behave identically (their ADRP pages / BL targets are the same)."""
    toks = []
    for i in a2c.md.disasm(a2c.TD[addr - a2c.TB:addr - a2c.TB + size], addr):
        op = i.op_str
        if i.mnemonic in ('b', 'bl') or i.mnemonic.startswith('b.') or i.mnemonic in ('cbz', 'cbnz', 'tbz', 'tbnz', 'adr', 'adrp'):
            m = re.search(r'#(0x[0-9a-f]+)$', op)
            if m:
                t = int(m.group(1), 16)
                if addr <= t < addr + size and i.mnemonic not in ('adrp', 'adr'):
                    op = op[:m.start()] + 'L%x' % (t - addr)
        toks.append(i.mnemonic + ' ' + op)
    return hashlib.md5('\n'.join(toks).encode()).hexdigest()


def select():
    chosen = []  # (group, sym)
    for g, pats in GROUPS.items():
        for p in pats:
            rx = re.compile(p)
            hits = sorted(n for n in dyn if rx.match(n))
            if not hits:
                print(f'WARNING: no symbol matches {p}', file=sys.stderr)
            for n in hits:
                chosen.append((g, n))
    for line in open(os.path.join(HERE, 'models_funcs.txt')):
        if line.startswith('#') or not line.strip():
            continue
        g, n = line.split('\t')[:2]
        if n in dyn:
            chosen.append((g, n))
        else:
            print(f'WARNING: {n} not exported', file=sys.stderr)
    seen, res = set(), []
    for g, n in chosen:
        a = dyn[n][0]
        if a in seen:
            continue
        seen.add(a)
        res.append((g, n))
    return res


FUNCS = select()
# One body per code shape: chosen functions with identical machine code share a body, and every
# other exported instantiation of these families with that code is registered with it too.
by_size = {}
for n, (a, s) in dyn.items():
    if s >= 8:
        by_size.setdefault(s, []).append((a, n))
# Only instantiations of the families ported here (identical code elsewhere is someone else's).
ALIAS_OK = re.compile(r'Aska\d+(TAaf|Aaf|HierarchicalObject|JointObject|SkinMatrices|AofObject|AofHandler|DirectAof)')
_shape_cache = {}


def cached_shape(a, s):
    if a not in _shape_cache:
        _shape_cache[a] = shape(a, s)
    return _shape_cache[a]


aliases = {}  # body addr -> [other addrs with same code]
body_addrs = {}
primary_of = {}  # (size, shape) -> body addr
for g, n in FUNCS:
    a, s = dyn[n]
    key = (s, cached_shape(a, s))
    if key in primary_of:
        continue
    primary_of[key] = a
    body_addrs[a] = (g, n)
    same = [a2 for a2, n2 in by_size.get(s, []) if a2 != a and ALIAS_OK.search(n2) and cached_shape(a2, s) == key[1]]
    aliases[a] = sorted(set(same))

# ---- symbols with a hand-written implementation (tools/models_readable.py) ----
_rspec = importlib.util.spec_from_file_location('models_readable', os.path.join(HERE, 'models_readable.py'))
models_readable = importlib.util.module_from_spec(_rspec)
_rspec.loader.exec_module(models_readable)
READABLE = {}  # addr -> C++ expression
_expr_shapes = {}
for a in body_addrs:
    for a2 in [a] + aliases[a]:
        e = models_readable.readable_expr(a2c.dem(by_addr[a2]))
        if e:
            READABLE[a2] = e
            _expr_shapes.setdefault(e, set()).add(a)
def loose_shape(addr, size):
    """shape() without the addresses of the function's own rodata (jump tables): instantiations
    that differ only there behave identically."""
    toks, prev = [], None
    for i in a2c.md.disasm(a2c.TD[addr - a2c.TB:addr - a2c.TB + size], addr):
        op = i.op_str
        if i.mnemonic in ('b', 'bl') or i.mnemonic.startswith('b.') or i.mnemonic in ('cbz', 'cbnz', 'tbz', 'tbnz'):
            m = re.search(r'#(0x[0-9a-f]+)$', op)
            if m and addr <= int(m.group(1), 16) < addr + size:
                op = op[:m.start()] + 'L%x' % (int(m.group(1), 16) - addr)
            elif m:  # a call to a hand-written function: by its implementation
                t = int(m.group(1), 16)
                n = L.name(t)
                if n.startswith('PLT:') and n[4:] in dyn:
                    t = dyn[n[4:]][0]
                if t in READABLE:
                    op = op[:m.start()] + READABLE[t]
        # own rodata and GOT slots (a wrapper tail-calls its own instantiation's worker; the
        # workers are checked on their own)
        if i.mnemonic == 'adrp' or (i.mnemonic in ('add', 'ldr') and prev == 'adrp'):
            op = re.sub(r'#0x[0-9a-f]+', '#PAGE', op)
        toks.append(i.mnemonic + ' ' + op)
        prev = i.mnemonic
    return '\n'.join(toks)


for e, shapes in _expr_shapes.items():
    if len({loose_shape(a, dyn[body_addrs[a][1]][1]) for a in shapes}) != 1:
        sys.exit(f'models_readable: {e} covers {len(shapes)} different machine-code shapes: ' +
                 ', '.join(a2c.dem(body_addrs[a][1]) for a in sorted(shapes)))

# ---- call resolution ----
MATH = {
    '_ZN4Aska10Quaternion5SlerpEPKS0_S2_f': 'quat_slerp((Quat*)X(0), (const Quat*)X(1), (const Quat*)X(2), S(0));',
    '_ZN4Aska14MatrixCalcFuncEPNS_6MatrixEPKNS_6VectorEPKNS_10QuaternionES7_S4_S4_PKS0_':
        'matrix_calc_func((Mat44*)X(0), (const Vec4*)X(1), (const Quat*)X(2), (const Quat*)X(3), (const Vec4*)X(4), (const Vec4*)X(5), (const Mat44*)X(6));',
    '_ZN4Aska6Matrix3MulEPKS0_S2_': 'mat_mul((Mat44*)X(0), (const Mat44*)X(1), (const Mat44*)X(2));',
    '_ZN4Aska6Matrix11MulFromLeftEPKS0_': 'mat_mul_from_left((Mat44*)X(0), (const Mat44*)X(1));',
    '_ZN4Aska6Matrix6CreateEPKNS_10QuaternionE': 'mat_create((Mat44*)X(0), (const Quat*)X(1));',
    '_ZN4Aska6Matrix6InvertEv': 'mat_invert((Mat44*)X(0));',
    '_ZN4Aska6Matrix3MulEPKS0_': 'mat_mul((Mat44*)X(0), (const Mat44*)X(1));',
    '_ZN4Aska7ToColorERKNS_6VectorE': 'X(0) = to_color((const Vec4*)X(0));',
    '_ZN4Aska8ToColorvEj': 'to_colorv((Vec4*)X(8), (uint32_t)W(0));',
    '_ZN4Aska6Vector11ApplyMatrixEPKNS_6MatrixE': 'vec_apply_matrix((Vec4*)X(0), (const Mat44*)X(1));',
    '_ZN4Aska10Quaternion6CreateEPKNS_6MatrixE': 'quat_create((Quat*)X(0), (const Mat44*)X(1));',
    '_ZN4Aska6Matrix14InvertLowErrorEv': 'X(0) = mat_invert_low_error((Mat44*)X(0)) ? 1 : 0;',
    '_ZNK4Aska6Matrix14InvertLowErrorEPS0_': 'X(0) = mat_invert_low_error((const Mat44*)X(0), (Mat44*)X(1)) ? 1 : 0;',
    '_ZN4Aska10Quaternion15CreateFromEulerEfff14EnumRotateType': 'quat_create_from_euler((Quat*)X(0), S(0), S(1), S(2), (int)W(1));',
}
HOST = {
    'memset': 'memset((void*)X(0), (int)W(1), X(2));',
    'memcpy': 'memcpy((void*)X(0), (const void*)X(1), X(2));',
    'memmove': 'memmove((void*)X(0), (const void*)X(1), X(2));',
}
# The aska-math bodies aren't linked by name; math symbols not in MATH go to the guest (hooked).

guest_calls = set()


def fallback(kind, t, reg):
    if kind in ('blr', 'br'):
        return f'models_icall(r, {reg});'
    if t in READABLE:  # hand-written: through the dispatch table
        return f'models_icall(r, LIB + 0x{t:x});'
    if t in body_addrs:
        return f'f_{t:x}(r);'
    n = L.name(t)
    if n.startswith('PLT:'):
        pn = n[4:]
        if pn in HOST:
            return HOST[pn]
        if pn in dyn and dyn[pn][0] != t:  # PLT stub of a library function: resolve it
            return fallback(kind, dyn[pn][0], reg)
        guest_calls.add(t)
        return f'models_gcall(r, LIB + 0x{t:x}); /* {pn} */'
    if n in MATH:
        return MATH[n]
    if n in dyn and dyn[n][1] == 4:  # 4-byte trampoline: "b target"
        ins = next(a2c.md.disasm(a2c.TD[t - a2c.TB:t - a2c.TB + 4], t))
        if ins.mnemonic == 'b':
            return fallback(kind, int(ins.op_str.lstrip('#'), 16), reg)
    for a2 in aliases:  # a call to an alias of a body
        if t in aliases[a2]:
            return f'f_{a2:x}(r);'
    guest_calls.add(t)
    return f'models_gcall(r, LIB + 0x{t:x});'


a2c.CALL_FALLBACK = fallback
a2c.EXCLUSIVE = True
a2c.NAN_EXACT = True
# The a2c tables would route these to the aska-math transcriptions (not visible here).
a2c.EXTRA_CALLS.clear()
for k in ('__cxa_guard_acquire', '__cxa_guard_release'):
    a2c.CALLS.pop(k, None)
for k, v in MATH.items():
    a2c.EXTRA_CALLS[k] = v


def dem(n):
    return a2c.dem(n)


out = ['''// GENERATED by tools/gen_models_a2c.py from libSOA.so's ARM64 code: do not edit by hand; regenerate.
// ''' + genlib.stamp() + '''
//
// The model / animation object layer (Aska::TAaf* animation controllers and AafHandler evaluation,
// the HierarchicalObject bone-matrix pass, AofObject / AofHandler render preparation), transcribed
// instruction by instruction by tools/a2c.py. See models.h for the call dispatch (virtual calls go
// through models_icall) and models.cpp for the hand-written parts and the tests.
#pragma GCC optimize("fp-contract=off")
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wuninitialized"
#include <cstdlib>
#include <cstring>

#include "core/cpu.h"
#include "native/engine/math/aska_math.h"
#include "native/models/models.h"
#include "native/common/native.h"

namespace soa::models {
using namespace ::soa::aska;
using namespace ::soa::aska::a2c;
using a2c::u64;
using a2c::u32;
''']
for a in sorted(body_addrs):
    out.append(f'static void f_{a:x}(A64& r);')
bodies = []
bad = []
for a in sorted(body_addrs):
    g, n = body_addrs[a]
    body = a2c.translate(n, f'f_{a:x}')
    if '#error' in body:
        errs = re.findall(r'#error "a2c: ([^"]*)"', body)
        bad.append((n, errs[:3]))
    bodies.append(f'// {dem(n)}')
    for a2 in aliases[a]:
        bodies.append(f'//   also {dem(by_addr[a2])}')
    bodies.append(f'static void f_{a:x}(A64& r) {{')
    bodies.append('    u64 jt_ = 0, ex_a_ = 0, ex_v_ = 0;')
    bodies.append('    (void)jt_; (void)ex_a_; (void)ex_v_;')
    bodies.append(body.rstrip())
    bodies.append('}')
if bad:
    for n, e in bad:
        print(f'UNSUPPORTED {n}: {e}', file=sys.stderr)
out += bodies
# hooks
out.append('')
for a in sorted(body_addrs):
    out.append(f'static void h_{a:x}(Cpu& c) {{ models_run_hook(c, f_{a:x}); }}')
out.append('')
# Symbols with a hand-written version are registered from models_anim_tab.inc; their
# transcriptions stay in g_models_ref_fns for the differential tests.
for tab, want in (('g_models_fns', False), ('g_models_ref_fns', True)):
    out.append(f'const ModelsFn {tab}[] = {{')
    for a in sorted(body_addrs):
        g, n = body_addrs[a]
        for a2 in [a] + aliases[a]:
            if (a2 in READABLE) == want:
                out.append(f'    {{0x{a2:x}, "{by_addr[a2]}", "{g}", f_{a:x}, h_{a:x}, {"true" if a2 == a else "false"}}},')
    out.append('};')
    n = 'g_models_nfns' if tab == 'g_models_fns' else 'g_models_ref_nfns'
    out.append(f'const int {n} = sizeof {tab} / sizeof {tab}[0];')
out.append('}  // namespace soa::models')
open(OUT, 'w').write('\n'.join(out) + '\n')
tab = ['// GENERATED by tools/gen_models_a2c.py (classification: tools/models_readable.py): every model /',
       '// ' + genlib.stamp(),
       '// animation symbol with a hand-written implementation and the template instance that implements it.']
group_of = {a2: body_addrs[a][0] for a in body_addrs for a2 in [a] + aliases[a]}
for a2 in sorted(READABLE, key=lambda x: by_addr[x]):
    g = group_of[a2]
    tab.append(f'{{0x{a2:x}, "{by_addr[a2]}", "{g}", RD({READABLE[a2]}), true}},  // {a2c.dem(by_addr[a2])}')
open(os.path.join(os.path.dirname(OUT), 'models_anim_tab.inc'), 'w').write('\n'.join(tab) + '\n')
print(f'{len(READABLE)} symbols hand-written ({len(_expr_shapes)} template instances)', file=sys.stderr)
nal = sum(len(v) for v in aliases.values())
print(f'{len(body_addrs)} bodies, {nal} aliases, {len(guest_calls)} guest call targets, {len(bad)} unsupported', file=sys.stderr)
if os.environ.get('MODELS_LIST_GCALLS'):
    for t in sorted(guest_calls):
        print(f'gcall {t:x} {dem(L.name(t).replace("PLT:", ""))}', file=sys.stderr)

# ---- instruction-level validation table (models_a2c_insn.cpp) ----
# Every distinct non-memory, non-branch instruction encoding used by the bodies is transcribed on
# its own; the self-test runs it in the JIT and natively on random register states.
if len(sys.argv) > 2:
    SKIP = re.compile(r'^(b|bl|br|blr|ret|cbz|cbnz|tbz|tbnz|b\..*|ld.*|st.*|prf.*|adrp|adr|svc|mrs|msr|dmb|dsb|isb|clrex|nop|cas.*|swp.*)$')
    encs = {}
    for a in sorted(body_addrs):
        g, n = body_addrs[a]
        start, size = dyn[n]
        for i in a2c.md.disasm(a2c.TD[start - a2c.TB:start - a2c.TB + size], start):
            if SKIP.match(i.mnemonic) or 'sp' in re.split(r'[\s,\[\]]+', i.op_str) or 'wsp' in i.op_str:
                continue
            e = int.from_bytes(i.bytes, 'little')
            encs.setdefault(e, (i.address, i.mnemonic, i.op_str))
    io = ['// GENERATED by tools/gen_models_a2c.py: every distinct ALU/FP/SIMD instruction the model-layer',
          '// ' + genlib.stamp(),
          '// transcription uses, transcribed alone (for the models/a2c-instructions self-test).',
          '#pragma GCC optimize("fp-contract=off")',
          '#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"',
          '#pragma GCC diagnostic ignored "-Wunused-label"',
          '#pragma GCC diagnostic ignored "-Wuninitialized"',
          '#include <cstring>', '#include "native/engine/math/aska_math.h"', '#include "native/models/models.h"',
          'namespace soa::models {', 'using namespace ::soa::aska;', 'using namespace ::soa::aska::a2c;',
          'using a2c::u64;', 'using a2c::u32;']
    rows = []
    a2c.CALL_FALLBACK = None
    for e, (ad, mn, op) in sorted(encs.items(), key=lambda kv: kv[1][0]):
        body = a2c.translate(f'0x{ad:x}:4', 'x')
        if '#error' in body or 'goto' in body.replace('goto L_ret', ''):
            continue
        io.append(f'static void i_{ad:x}(A64& r) {{ u64 jt_ = 0, ex_a_ = 0, ex_v_ = 0; (void)jt_; (void)ex_a_; (void)ex_v_;')
        io.append(body.rstrip())
        io.append('}')
        rows.append(f'    {{0x{e:08x}u, 0x{ad:x}, "{mn} {op}", i_{ad:x}}},')
    # loads / stores: the base register is pointed at a scratch buffer by the test
    MEM = re.compile(r'^(ld|st)(?!.*xr$)(?!xr)')
    mrows = []
    seen_m = set()
    for a in sorted(body_addrs):
        g, n = body_addrs[a]
        start, size = dyn[n]
        for i in a2c.md.disasm(a2c.TD[start - a2c.TB:start - a2c.TB + size], start):
            if not MEM.match(i.mnemonic) or 'xr' in i.mnemonic or '[' not in i.op_str:
                continue
            m = re.search(r'\[(x\d+|sp)(?:, (\w+))?', i.op_str)
            if not m:
                continue
            base, idx = m.group(1), m.group(2)
            if base == 'sp' or (idx and not re.match(r'[wx]\d+$', idx)):
                if base == 'sp':
                    continue
                idx = None
            e = int.from_bytes(i.bytes, 'little')
            if e in seen_m:
                continue
            seen_m.add(e)
            body = a2c.translate(f'0x{i.address:x}:4', 'x')
            if '#error' in body or 'goto L_' in body.replace('goto L_ret', ''):
                continue
            io.append(f'static void m_{i.address:x}(A64& r) {{ u64 jt_ = 0, ex_a_ = 0, ex_v_ = 0; (void)jt_; (void)ex_a_; (void)ex_v_;')
            io.append(body.rstrip())
            io.append('}')
            b_ = int(base[1:])
            ix = int(idx[1:]) if idx else -1
            sx = 1 if (idx and ('sxtw' in i.op_str)) else 0
            mrows.append(f'    {{0x{e:08x}u, 0x{i.address:x}, "{i.mnemonic} {i.op_str}", m_{i.address:x}, {b_}, {ix}, {sx}}},')
    io.append('const MemInsnCase g_models_mem_insns[] = {')
    io += mrows
    io.append('};')
    io.append('const int g_models_nmem_insns = sizeof g_models_mem_insns / sizeof g_models_mem_insns[0];')
    print(f'{len(mrows)} distinct memory instructions for validation', file=sys.stderr)
    io.append('const InsnCase g_models_insns[] = {')
    io += rows
    io.append('};')
    io.append('const int g_models_ninsns = sizeof g_models_insns / sizeof g_models_insns[0];')
    io.append('}  // namespace soa::models')
    open(sys.argv[2], 'w').write('\n'.join(io) + '\n')
    print(f'{len(rows)} distinct instructions for validation', file=sys.stderr)
