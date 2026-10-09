#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Generates port/src/native/objbase/gen/objbase_a2c.cpp: the animation / object base layer transcribed by a2c.py.

Framework::CAnimationBlendContainer, Framework::CAnimationModel, CAnimationModelObject,
CMovableObject, CBehaviorObject and CThingObject (the base classes under CCharacterObject and the
home / gacha scene objects), instruction by instruction. The functions listed
(tools/objbase_funcs.txt) are the ones that executed in the 2026-09-29 restore-run profile.

Every outgoing call goes through ob_gcall() / ob_icall() (objbase.h): calls to other transcribed
functions of this table run their bodies directly, other calls go to the guest (or the host
function of another native), and the live check (soa --live-check objbase) records and replays them
(objbase_rt.cpp).

Each body starts with a dispatch to its readable version (objbase_rd.cpp, g_ob_rd) when there is
one and SOA_OBJBASE_A2C doesn't switch it off (t_ob_a2c: the tests' reference side).

Usage: .venv/bin/python tools/gen_objbase_a2c.py port/src/native/objbase/gen/objbase_a2c.cpp
"""
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

# Bytes of the object at x0 the live check snapshots, by class: the largest field offset (plus
# the access size) that the class's executed functions touch through x0 or a register copied from
# it, rounded up to 16 (see obj_extent()).
CLASSES = ['Framework::CAnimationBlendContainer::', 'Framework::CAnimationModel::', 'CAnimationModelObject::', 'CMovableObject::',
           'CBehaviorObject::', 'CThingObject::']

# Executed functions of the family (profile coverage), mangled.
FUNCS = [ln.strip() for ln in open(os.path.join(HERE, 'objbase_funcs.txt')) if ln.strip() and not ln.startswith('#')]


def obj_extent(n):
    """Largest [base, #imm] extent over x0 and its copies in function n (a straight scan)."""
    a, s = a2c.syms[n]
    code = a2c.rd(a, s)
    alias = {'x0'}
    ext = 0
    for ins in a2c.md_d.disasm(code, a):
        ops = ins.op_str
        m = re.match(r'(x\d+), (x\d+)$', ops)
        if ins.mnemonic == 'mov' and m:
            if m.group(2) in alias:
                alias.add(m.group(1))
            else:
                alias.discard(m.group(1))
            continue
        mm = re.search(r'\[(x\d+)(?:, #(-?0x[0-9a-f]+|-?\d+))?\]', ops)
        if mm and mm.group(1) in alias and ins.mnemonic[:2] in ('ld', 'st'):
            off = int(mm.group(2), 0) if mm.group(2) else 0
            sz = 16 if ins.mnemonic in ('ldp', 'stp') or ' q' in ' ' + ops[:3] else 8
            ext = max(ext, off + sz)
        if ins.mnemonic in ('bl', 'blr'):
            alias &= {f'x{k}' for k in range(19, 29)}
        else:
            alias -= a2c.gpr_writes(ins)
    return ext


def mark_sret(body):
    """Calls right after `x8 = sp + k` (the sret idiom: a struct result, e.g. a CVector or CMatrix,
    returned into the caller's frame) become ob_gcall_sret / ob_icall_sret: the live check then
    sees every byte the callee writes there (objbase_rt.cpp)."""
    lines = body.split('\n')
    for i, ln in enumerate(lines):
        if 'ob_gcall(r,' not in ln and 'ob_icall(r,' not in ln:
            continue
        for j in range(i - 1, max(i - 8, -1), -1):
            p = lines[j]
            if 'ob_gcall' in p or 'ob_icall' in p or p.startswith('L_') or 'goto' in p or 'memset' in p or 'memcpy' in p or 'memmove' in p:
                break
            if re.match(r'\s*X\(8\) = \(u64\)\(SP[ )+-]', p):
                lines[i] = ln.replace('ob_gcall(r,', 'ob_gcall_sret(r,').replace('ob_icall(r,', 'ob_icall_sret(r,')
                break
            if re.match(r'\s*X\(8\) = ', p):
                break
    return '\n'.join(lines)


def is_simple(n):
    """No calls or indirect branches, and every memory access based on an unmodified argument
    register (x0-x7) or SP: the synthetic test (objbase_test.cpp) can run it on buffers of plain
    values without it chasing pointers."""
    a, s = a2c.syms[n]
    args = {f'x{k}' for k in range(8)}
    for ins in a2c.md_d.disasm(a2c.rd(a, s), a):
        if ins.mnemonic in ('bl', 'blr', 'br', 'blraa', 'braa'):
            return False
        if ins.mnemonic == 'b' or ins.mnemonic.startswith('b.') or ins.mnemonic in ('cbz', 'cbnz', 'tbz', 'tbnz'):
            t = int(ins.op_str.split('#')[-1], 0)
            if not a <= t < a + s:
                return False
        mm = re.search(r'\[(\w+)', ins.op_str)
        if mm and mm.group(1) not in args and mm.group(1) != 'sp':
            return False
        if mm and re.search(r'\[\w+, [wx]\d+', ins.op_str):
            return False  # (register offsets: an index from the buffers)
        for w in a2c.gpr_writes(ins):
            args.discard(w)
    return True


# The functions the tests verified (0 live-check mismatches over the sessions, or the synthetic
# test for `simple` ones): only these are installed by default (SOA_OBJBASE_ALL=1 installs all, to
# live-check the rest).
VERIFIED = set(ln.split()[0] for ln in open(os.path.join(HERE, 'objbase_verified.txt')) if ln.strip() and not ln.startswith('#'))

OBJ = {}
for n in FUNCS:
    if n in a2c.syms:
        d = a2c.dem(n)
        c = next((p for p in CLASSES if d.startswith(p)), None)
        if c:
            OBJ[c] = max(OBJ.get(c, 0), obj_extent(n))
OBJ = {c: min((v + 15) & ~15, 0x2000) for c, v in OBJ.items()}
print(OBJ, file=sys.stderr)

dyn = a2c.syms
HOST = {
    'memset': 'memset((void*)X(0), (int)W(1), X(2));',
    'memcpy': 'memcpy((void*)X(0), (const void*)X(1), X(2));',
    'memmove': 'memmove((void*)X(0), (const void*)X(1), X(2));',
}
calls = {}


def fallback(kind, t, reg):
    if kind in ('blr', 'br'):
        return f'ob_icall(r, {reg});'
    n = L.name(t)
    if n.startswith('PLT:') and n[4:] in HOST:
        return HOST[n[4:]]
    calls[t] = n
    return f'ob_gcall(r, LIB + 0x{t:x}); /* {a2c.dem(n.replace("PLT:", ""))[:80]} */'


a2c.CALL_FALLBACK = fallback
a2c.EXCLUSIVE = True
a2c.NAN_EXACT = True
a2c.EXTRA_CALLS.clear()
for k in ('__cxa_guard_acquire', '__cxa_guard_release'):
    a2c.CALLS.pop(k, None)

out = ['''// GENERATED by tools/gen_objbase_a2c.py from libSOA.so's ARM64 code: do not edit by hand; regenerate.
// ''' + genlib.stamp() + '''
//
// The animation / object base layer (Framework::CAnimationBlendContainer / CAnimationModel,
// CAnimationModelObject, CMovableObject, CBehaviorObject, CThingObject) transcribed instruction by
// instruction by tools/a2c.py. Calls go through ob_gcall / ob_icall (objbase.h). Registration,
// switches and tests: objbase_rt.cpp. A body with a readable version (objbase_rd.cpp, g_ob_rd)
// runs that instead, unless SOA_OBJBASE_A2C switches it back to the transcription.
#pragma GCC optimize("fp-contract=off")
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wuninitialized"
#include <cstdlib>
#include <cstring>

#include "core/cpu.h"
#include "native/objbase/objbase.h"
#include "native/engine/math/aska_math.h"
#include "native/models/models.h"

namespace soa::objbase {
using namespace ::soa::aska;
using namespace ::soa::aska::a2c;
using namespace ::soa::models;
using a2c::u64;
using a2c::u32;
''']
bad = []
bodies = []
table = []
for n in FUNCS:
    if n not in dyn:
        print(f'WARNING: {n} not exported', file=sys.stderr)
        continue
    a, s = dyn[n]
    if s < 8:
        continue  # the hook patch doesn't fit
    d = a2c.dem(n)
    osz = next((b for p, b in OBJ.items() if d.startswith(p)), None)
    if osz is None:
        print(f'WARNING: no class size for {d}', file=sys.stderr)
        osz = 0
    body = mark_sret(a2c.translate(n, f'f_{a:x}'))
    if '#error' in body:
        bad.append((n, re.findall(r'#error "a2c: ([^"]*)"', body)[:3]))
        continue
    bodies.append(f'// {d}')
    bodies.append(f'static void f_{a:x}(A64& r) {{')
    # (the readable version (objbase_rd.cpp) when there is one, unless SOA_OBJBASE_A2C switches it
    # off or this thread runs the transcriptions as the reference of a test: t_ob_a2c)
    bodies.append(f'    if (models::Body rd_ = g_ob_rd[{len(table)}]; rd_ && !t_ob_a2c) {{ rd_(r); return; }}')
    bodies.append('    u64 jt_ = 0, ex_a_ = 0, ex_v_ = 0;')
    bodies.append('    (void)jt_; (void)ex_a_; (void)ex_v_;')
    bodies.append(body.rstrip())
    bodies.append('}')
    table.append(f'    {{0x{a:x}, "{n}", f_{a:x}, 0x{osz:x}, {int(is_simple(n))}, {int(n in VERIFIED or is_simple(n))}}},')
out += bodies
out.append('')
out.append('const ObjA2cFn g_objbase_a2c_fns[] = {')
out += table
out.append('};')
out.append('const int g_objbase_a2c_nfns = sizeof g_objbase_a2c_fns / sizeof g_objbase_a2c_fns[0];')
out.append('}  // namespace soa::objbase')
open(OUT, 'w').write('\n'.join(out) + '\n')
for n, e in bad:
    print(f'UNSUPPORTED {n}: {e}', file=sys.stderr)
print(f'{len(table)} bodies, {len(calls)} call targets, {len(bad)} unsupported', file=sys.stderr)
