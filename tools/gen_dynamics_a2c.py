#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Generates port/src/native/dynamics/gen/dynamics_a2c.cpp: the Aska dynamics family transcribed by a2c.py.

Covers the articulated dynamics (hair / cloth / accessory bones): ArticulatedDynamicsManager{,Base},
ADMJoint, ADMHandler, ADMObject, FastIkEndEffector, the DynamicsManager / DynamicsHandler
scheduler, the collision primitives (Dynamics{Cube,Sphere,Capsule,Plane}, DYNAMICS_*), DPGHandler,
force emitters / world wind, the Functor_* locals, and HeightObject / _HO_*. These are FP-heavy
(frecpe / frsqrte Newton steps) and must stay bit-exact, so they are transcribed rather than
rewritten.

Calls: static calls to another transcribed function are C++ calls; indirect calls go through
dyn_icall() (this family's table, then the model layer's, then the guest); everything else is
models_gcall(), which calls native replacements directly. Registration, switches and tests:
dynamics_a2c_rt.cpp.

Selection: the GROUPS patterns' matches that are listed in tools/dynamics_funcs.txt (names, so it
holds for any lib; frozen from the offline-build port's coverage), plus the unnamed locals (genlib
names). DYN_ALL=1 takes every match; DYN_COVERAGE=FILE[,FILE] (SOA_COVERAGE coverage.tsv of the
same lib) prints the executed matches the list lacks.

Lib: SOA_LIB, default work/libSOA-3.7.0.so (tools/genlib.py); the output header records it.

Usage: gen_dynamics_a2c.py <out.cpp>
"""
import importlib.util
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import genlib  # noqa: E402 (before a2c: the default lib is 3.7.0's)

_spec = importlib.util.spec_from_file_location('a2c', os.path.join(HERE, 'a2c.py'))
a2c = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(a2c)
L = a2c.L
OUT = sys.argv[1]

# (group, [symbol regex | 0xaddr:size local]). Groups are for SOA_DYNAMICS_A2C_OFF.
GROUPS = {
    # per-frame simulation of one ArticulatedDynamicsManager (worker threads)
    'sim': [
        r'_ZN4Aska26ArticulatedDynamicsManager8SimulateEfjf$',
        r'_ZN4Aska26ArticulatedDynamicsManager12SimulateMain',
        r'_ZN4Aska26ArticulatedDynamicsManager29PreprocessBeforeInternalForce',
        r'_ZN4Aska30ArticulatedDynamicsManagerBase22CollisionAndConstraint',
        r'_ZN4Aska30ArticulatedDynamicsManagerBase10StandardIK',
        r'_ZN4Aska30ArticulatedDynamicsManagerBase15InterpolateRoot',
        r'_ZN4Aska30ArticulatedDynamicsManagerBase16CollisionSetting',
        r'_ZN4Aska26ArticulatedDynamicsManager26MatrixPreFixAndMotionBlendILb1EEEvPNS_13ADM_CALC_DATA',
        r'_ZN4Aska8ADMJoint13ExternalForce',
        r'^_Z\d+Functor_',
        # the five unnamed locals after Functor_ExternalForceEmitterCalculation<ADM, ...> (link solve,
        # IK bend, bend rotation, capsule-hit response, joint velocity; tools/genlib.py naming)
        *[f'anon:_Z39Functor_ExternalForceEmitterCalculationIN4Aska26ArticulatedDynamicsManagerENS0_20DynamicsForceEmitterEEvPT_PNS0_8ADMJointEPPT0_jfj#{k}' for k in range(1, 6)],
        r'_ZN4Aska8ADMJoint11PrepareCalcEv$',
        r'_ZN4Aska8ADMJoint5FlushEv$',
        r'_ZN4Aska30ArticulatedDynamicsManagerBase11PrepareCalcEf$',
        r'_ZNK4Aska30ArticulatedDynamicsManagerBase5GetDtEv$',
        r'_ZN4Aska30ArticulatedDynamicsManagerBase3RunEv$',
        r'_ZN4Aska30ArticulatedDynamicsManagerBase8ConvergeEifi$',
        r'_ZN4Aska30ArticulatedDynamicsManagerBase21SimulateNotifyHandlerEf$',
        r'_ZN4Aska30ArticulatedDynamicsManagerBase14SimulateNotify7HandlerEm$',
        r'_ZN4Aska30ArticulatedDynamicsManagerBase5FlushEv$',
        r'_ZN4Aska30ArticulatedDynamicsManagerBase46UpdateDynamicsPrimitiveListWithDependencyOfADMEj$',
        r'_ZN4Aska30ArticulatedDynamicsManagerBase44MakeDynamicsPrimitiveListWithDependencyOfADMEPPNS_17DynamicsPrimitiveE$',
        r'_ZN4Aska30ArticulatedDynamicsManagerBase5ScaleEfPNS_10AsfHandlerE$',
        r'_ZN4Aska26ArticulatedDynamicsManager3SetEmPKv$',
        r'_ZN4Aska9ADMObject3SetEmPKv$',
        # per-frame setters over every ADM of a model (Framework helpers)
        r'_ZN9Framework48gSetLocalDTRateToArticulatedDynamicsManagerInAsfERN4Aska10AsfHandlerEf$',
        r'_ZN9Framework56gSetLandscapeConstraintToArticulatedDynamicsManagerInAsfERN4Aska10AsfHandlerEPNS0_20ILandscapeConstraintE$',
    ],
    # scheduling: handlers and the dynamics manager's task list
    'handler': [
        r'_ZN4Aska10ADMHandler3RunEi$',
        r'_ZN4Aska10ADMHandler11FlushNotify7HandlerEm$',
        r'_ZN4Aska10ADMHandler16IsHeavierHandlerEPNS_15DynamicsHandlerE$',
        r'_ZN4Aska10ADMHandler19SortProcessSequenceEv$',
        r'_ZN4Aska10ADMHandler29OnMakeListFromDynamicsManagerEv$',
        r'_ZN4Aska10ADMHandler14IsAddToDynListEv$',
        r'_ZN4Aska10ADMHandler9ExportAllEv$',
        r'_ZN4Aska10ADMHandler6UpdateEv$',
        r'_ZN4Aska10DPGHandler3RunEi$',
        r'_ZN4Aska10DPGHandler29OnMakeListFromDynamicsManagerEv$',
        r'_ZN4Aska10DPGHandler14IsAddToDynListEv$',
        r'_ZN4Aska10DPGHandler9ExportAllEv$',
        r'_ZN4Aska21DynamicsCommandNotify7HandlerEm$',
        r'_ZN4Aska12DynamicsWait3RunEi$',
        r'_ZN4Aska15BarrierDynamics3RunEi$',
        r'_ZN4Aska15DynamicsManager3RunEi$',
        r'_ZN4Aska15DynamicsManager16MakeDynamicsListEv$',
        r'_ZN4Aska15DynamicsManager22GetForceEmitterManagerEv$',
        r'_ZN4Aska15DynamicsHandler14IsAddToDynListEv$',
        r'_ZN4Aska15DynamicsHandler17SetDispatchHandleEim$',
        r'_ZN4Aska15DynamicsHandler25SetDirtyToDynamicsManagerEj$',
        r'_ZN4Aska15DynamicsHandler8SetLevelEj$',
        r'_ZN4Aska15DynamicsHandler14NormalizedFlagERj$',
        r'_ZN4Aska27DynamicsForceEmitterManager11_UpdateTask3RunEi$',
        r'_ZN4Aska27DynamicsForceEmitterManager16MakeDynamicsListEv$',
        r'_ZN4Aska27DynamicsForceEmitterManager15UpdateWorldWindEv$',
        r'_ZN4Aska17DynamicsWorldWind10_WorldWind3RunEi$',
        r'_ZN4Aska17DynamicsWorldWind9EmitForceEfPKNS_6VectorEPS1_f$',
        r'_ZN4Aska20DynamicsForceEmitter17SetDispatchHandleEim$',
    ],
    # collision primitives
    'prim': [
        r'_ZN4Aska(12DynamicsCube|14DynamicsSphere|15DynamicsCapsule|13DynamicsPlane)(3RunEv|5ResetEv|6UpdateEfb)$',
        r'_ZN4Aska(12DynamicsCube|14DynamicsSphere|15DynamicsCapsule|13DynamicsPlane)16TestIntersection',
        r'_ZN4Aska15DynamicsCapsule21TestIntersectionLocal',
        r'_ZN4Aska(16DYNAMICS_CAPSULE|13DYNAMICS_CUBE|15DYNAMICS_SPHERE|14DYNAMICS_PLANE)\d+TestIntersection',
    ],
    'ik': [
        r'_ZN4Aska17FastIkEndEffector17InverseKinematicsEv$',
        r'_ZN4Aska17FastIkEndEffector16CreateParentListEv$',
        r'_ZN4Aska17FastIkEndEffector11SetMaxJointEh$',
        r'_ZN4Aska17FastIkEndEffector12SetEndObjectEPNS_18HierarchicalObjectE$',
        r'_ZN4Aska17FastIkEndEffector14SetIkParameterEPv$',
        'anon:_ZNK4Aska17FastIkEndEffector10GetClassIDEi#1',
    ],
    'height': [
        r'_ZN4Aska12HeightObject12UpdateMinMaxEv$',
        r'_ZN4Aska12HeightObject3RunEi$',
        r'_ZN4Aska18HeightObjectNormal18FindIntersectPoint',
        r'_ZN4Aska10_HO_Config',
        r'_ZN4Aska34_HO_sub_FindIntersectPointMainFunc',
    ],
}

dyn = a2c.syms
LISTED = set()
for _l in open(os.path.join(HERE, 'dynamics_funcs.txt')):
    _l = _l.split('#')[0].strip()
    if _l:
        LISTED.add(_l)
listed = {dyn[n][0] for n in LISTED if n in dyn}
for n in sorted(LISTED - set(dyn)):
    print(f'WARNING: dynamics_funcs.txt: {n} not in the lib', file=sys.stderr)
executed = set()
for _cov in filter(None, os.environ.get('DYN_COVERAGE', '').split(',')):
    for _l in open(_cov):
        if not _l.startswith('#'):
            executed.add(int(_l.split('\t')[0], 16))
ONLY_LISTED = not os.environ.get('DYN_ALL')

FUNCS = []  # (group, name or None, addr, size)
seen = set()
for g, pats in GROUPS.items():
    for p in pats:
        if p.startswith(('0x', 'anon:', 'lambda:')):
            a, s = genlib.resolve_spec(p)
            if a not in seen:
                seen.add(a)
                FUNCS.append((g, None, a, s))
            continue
        rx = re.compile(p if p.startswith('^') else '^' + p)
        hits = sorted((n, v) for n, v in dyn.items() if rx.search(n))
        if not hits:
            print(f'WARNING: no symbol for {p}', file=sys.stderr)
        for n, (a, s) in hits:
            if a in seen:
                continue
            if a in executed and a not in listed and s >= 8:
                print(f'DYN_COVERAGE: executed, not in dynamics_funcs.txt: {n}', file=sys.stderr)
            if ONLY_LISTED and a not in listed:
                continue
            if s < 8:
                continue
            seen.add(a)
            FUNCS.append((g, n, a, s))
body_addrs = {a: (g, n, s) for g, n, a, s in FUNCS}

HOST = {
    'memset': 'memset((void*)X(0), (int)W(1), X(2));',
    'memcpy': 'memcpy((void*)X(0), (const void*)X(1), X(2));',
    'memmove': 'memmove((void*)X(0), (const void*)X(1), X(2));',
}
MATH = {
    '_ZN4Aska6Matrix3MulEPKS0_S2_': 'mat_mul((Mat44*)X(0), (const Mat44*)X(1), (const Mat44*)X(2));',
    '_ZN4Aska6Matrix11MulFromLeftEPKS0_': 'mat_mul_from_left((Mat44*)X(0), (const Mat44*)X(1));',
    '_ZN4Aska6Matrix3MulEPKS0_': 'mat_mul((Mat44*)X(0), (const Mat44*)X(1));',
}
guest_calls = {}


def fallback(kind, t, reg):
    if kind in ('blr', 'br'):
        return f'dyn_icall(r, {reg});'
    if t in body_addrs:
        return f'f_{t:x}(r);'
    n = L.name(t)
    if n.startswith('PLT:'):
        pn = n[4:]
        if pn in HOST:
            return HOST[pn]
        if pn in dyn and dyn[pn][0] != t:
            return fallback(kind, dyn[pn][0], reg)
        guest_calls[t] = pn
        return f'models_gcall(r, LIB + 0x{t:x}); /* {pn} */'
    if n in MATH:
        return MATH[n]
    if n in dyn and dyn[n][1] == 4:
        ins = next(a2c.md.disasm(a2c.TD[t - a2c.TB:t - a2c.TB + 4], t))
        if ins.mnemonic == 'b':
            return fallback(kind, int(ins.op_str.lstrip('#'), 16), reg)
    guest_calls[t] = n
    return f'models_gcall(r, LIB + 0x{t:x}); /* {a2c.dem(n)[:80]} */'


a2c.CALL_FALLBACK = fallback
a2c.EXCLUSIVE = True
a2c.NAN_EXACT = True
a2c.EXTRA_CALLS.clear()
for k in ('__cxa_guard_acquire', '__cxa_guard_release'):
    a2c.CALLS.pop(k, None)
for k, v in MATH.items():
    a2c.EXTRA_CALLS[k] = v

out = ['''// GENERATED by tools/gen_dynamics_a2c.py from libSOA.so's ARM64 code: do not edit by hand; regenerate.
// ''' + genlib.stamp() + '''
//
// The Aska dynamics family (articulated dynamics, collision primitives, IK, height objects)
// transcribed instruction by instruction by tools/a2c.py. Registration, switches and tests:
// dynamics_a2c_rt.cpp.
#pragma GCC optimize("fp-contract=off")
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wuninitialized"
#include <cstdlib>
#include <cstring>

#include "core/cpu.h"
#include "native/engine/math/aska_math.h"
#include "native/dynamics/dynamics_a2c.h"
#include "native/models/models.h"

namespace soa::dynamics {
using namespace ::soa::aska;
using namespace ::soa::aska::a2c;
using namespace ::soa::models;
using a2c::u64;
using a2c::u32;
''']
for a in sorted(body_addrs):
    out.append(f'static void f_{a:x}(A64& r);')
bad = []
bodies = []
bodies_idx = []
for a in sorted(body_addrs):
    g, n, s = body_addrs[a]
    body = a2c.translate(n if n else f'0x{a:x}:0x{s:x}', f'f_{a:x}')
    if '#error' in body:
        bad.append((n or hex(a), re.findall(r'#error "a2c: ([^"]*)"', body)[:3]))
    bodies.append(f'// {a2c.dem(n) if n else "local " + hex(a)}')
    bodies.append(f'static void f_{a:x}(A64& r) {{')
    # (debugging: SOA_DYNAMICS_A2C_GUEST=off,.. runs these bodies' original code instead, also
    # when another body calls them directly)
    bodies.append(f'    if (__builtin_expect(g_dyn_force_guest[{len(bodies_idx)}], 0)) {{ models_gcall(r, LIB + 0x{a:x}); return; }}')
    # (the readable version (dynamics_rd.cpp) when there is one, unless SOA_DYNAMICS_A2C=1 or this
    # thread runs the transcriptions as the reference of a test: t_dyn_a2c)
    bodies.append(f'    if (models::Body rd_ = g_dyn_rd[{len(bodies_idx)}]; rd_ && !t_dyn_a2c) {{ rd_(r); return; }}')
    bodies_idx.append(a)
    bodies.append('    u64 jt_ = 0, ex_a_ = 0, ex_v_ = 0;')
    bodies.append('    (void)jt_; (void)ex_a_; (void)ex_v_;')
    bodies.append(body.rstrip())
    bodies.append('}')
out += bodies
out.append('')
for a in sorted(body_addrs):
    out.append(f'static void h_{a:x}(Cpu& c) {{ models_run_hook(c, f_{a:x}); }}')
out.append('')
out.append('const DynA2cFn g_dyn_a2c_fns[] = {')
for a in sorted(body_addrs):
    g, n, s = body_addrs[a]
    out.append(f'    {{0x{a:x}, {f"{chr(34)}{n}{chr(34)}" if n else "nullptr"}, "{g}", f_{a:x}, h_{a:x}}},')
out.append('};')
out.append('const int g_dyn_a2c_nfns = sizeof g_dyn_a2c_fns / sizeof g_dyn_a2c_fns[0];')
out.append('}  // namespace soa::dynamics')
open(OUT, 'w').write('\n'.join(out) + '\n')
for n, e in bad:
    print(f'UNSUPPORTED {n}: {e}', file=sys.stderr)
print(f'{len(body_addrs)} bodies, {len(guest_calls)} guest call targets, {len(bad)} unsupported', file=sys.stderr)
if os.environ.get('DYN_LIST'):
    for a in sorted(body_addrs):
        g, n, s = body_addrs[a]
        print(f'body {g} {a:x} {s} {a2c.dem(n) if n else "local"}', file=sys.stderr)
if os.environ.get('DYN_LIST_GCALLS'):
    for t, n in sorted(guest_calls.items()):
        print(f'gcall {t:x} {a2c.dem(n)[:150]}', file=sys.stderr)
