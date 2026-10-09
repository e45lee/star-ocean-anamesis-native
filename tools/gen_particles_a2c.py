#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Generates port/src/native/particles/gen/particles_a2c.cpp: the particle simulation (Aska::ParticleEmitter<>,
ParticleObject<>, IParticleEmitter / IParticleObject, the ParticleEmitter*Unit property blocks,
the rest of ParticleManager, ParticleMakeMatrix) transcribed by a2c.py.

The emitter / object templates are instantiated over Aska::FeatureList<ParticleFeatures...>; each
instantiation has its own machine code (the element layout differs per feature list), so every
executed instantiation gets its own transcription. Instantiations whose code is byte-identical
(after relocation) share one body.

The function list is tools/particles_funcs.txt (mangled names of the functions executed in the
offline and restore-run profiles, minus those native elsewhere: render_a2c.cpp and containers_a2c.cpp
own a few particle functions). Runtime and dispatch are the model layer's (models.h): direct calls
between bodies here are C++ calls, virtual calls go through particles_icall() (a body of this file,
of the model layer, or the guest), everything else is models_gcall(), which calls native
replacements directly.

Usage: gen_particles_a2c.py <out.cpp>
"""
import importlib.util
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
import genlib  # noqa: E402 (before a2c / elfinfo: the default lib is 3.7.0's; tools/genlib.py)
_spec = importlib.util.spec_from_file_location('a2c', os.path.join(HERE, 'a2c.py'))
a2c = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(a2c)
L = a2c.L
OUT = sys.argv[1]

dyn = a2c.syms
NAMES = [l.split('#')[0].strip() for l in open(os.path.join(HERE, 'particles_funcs.txt'))]
NAMES = [n for n in NAMES if n]
# The render side (group 'render': ParticleRenderManager, IParticleRenderManager, ParticleRenderableBase,
# ParticleRenderableObject<>::RenderProcedure, ParticleDrawContext, ParticleShaderKeyUtil).
RENDER = [l.split('#')[0].strip() for l in open(os.path.join(HERE, 'particles_render_funcs.txt'))]
# ('!sym': left to the guest on purpose, also as a sibling; see the comment in the list)
EXCLUDE = {n[1:] for n in RENDER if n.startswith('!')}
RENDER = [n for n in RENDER if n and not n.startswith('!')]
NAMES += [n for n in RENDER if n not in NAMES]

# The FeatureList combinations a battle uses change from run to run (skills, enemies), and a
# combination that was only created in the profiled runs simulates in the next one. So for every
# combination with any executed function, the per-frame and setup methods of its emitter, object,
# PosFuncRotation and PropertySetVisitor instantiations are transcribed too (the method kinds that
# ran for some combination; LifeDistance / LifeExtend / LinkEmitterTick / LineSpeedAffection...,
# which never ran, stay guest).
import subprocess  # noqa: E402
TEMPLATES = ('15ParticleEmitterINS_11FeatureList', '14ParticleObjectINS_11FeatureList', '15PosFuncRotationINS_11FeatureList',
             '18PropertySetVisitorINS_11FeatureList', '21FeatureListFuncCallerINS_18PropertySetVisitor',
             '24ParticleRenderableObjectINS_11FeatureList')
_cand = sorted(n for n in dyn if any(t in n for t in TEMPLATES) and not n.startswith('_ZThn'))
_dem = dict(zip(_cand, subprocess.run(['c++filt'], input='\n'.join(_cand), capture_output=True, text=True).stdout.split('\n')))


def _combo(d):
    m = re.search(r'Aska::(?:ParticleEmitter|ParticleObject|ParticleRenderableObject|PosFuncRotation|PropertySetVisitor|FeatureListFuncCaller)<(?:Aska::PropertySetVisitor<)?(Aska::FeatureList<.*?Aska::StNULL[ >]*>)', d)
    return m.group(1) if m else None


def _kind(d):
    m = re.search(r'::(~?\w+)\((?!.*\)::)', d)
    return (re.sub(r'<.*', '', d.split('::')[1]) if '::' in d else '') + '::' + (m.group(1) if m else '')


_executed = set(NAMES)
_combos = {_combo(_dem[n]) for n in _cand if n in _executed} - {None}
_kinds = {_kind(_dem[n]) for n in _cand if n in _executed}
_added = [n for n in _cand if n not in _executed and n not in EXCLUDE and _combo(_dem[n]) in _combos and _kind(_dem[n]) in _kinds]
# (an added one a2c can't transcribe stays guest: e.g. the StBoolean<true> SetupParticleTails, a
# vector shl)
a2c.CALL_FALLBACK = lambda kind, t, reg: '/* call */;'  # (calls are fine: the real fallback comes below)
a2c.EXCLUSIVE = True
_added = [n for n in _added if '#error' not in a2c.translate(n, 'probe')]
a2c.CALL_FALLBACK = None
NAMES += _added
print(f'{len(_combos)} FeatureLists with executed functions; {len(_added)} sibling methods added', file=sys.stderr)


def group_of(n):
    d = a2c.dem(n)
    if n in RENDER or re.search(r'Aska::(ParticleRenderableObject<.*|ParticleRenderManager|IParticleRenderManager|ParticleRenderableBase|ParticleDrawContext|ParticleShaderKeyUtil)::', d):
        return 'render'
    if 'ParticleEmitter<' in d and '::Emit' in d:
        return 'emit'
    if 'ParticleObject<' in d and 'Procedure' in d or 'PosFunc' in d:
        return 'proc'
    if 'ParticleEmitter<' in d and re.search(r'::(Simulate|Tick|EmitterAffectToParticle)\(', d):
        return 'sim'
    if 'ParticleMakeMatrix' in d or 'PrepareMatrices' in d:
        return 'matrix'
    if 'ParticleManager' in d:
        return 'manager'
    if 'IParticleObject' in d or 'IParticleEmitter' in d:
        return 'base'
    return 'setup'


def code_key(a, s):
    """Machine code with pc-relative targets made absolute, to find identical instantiations."""
    out = []
    for ins in a2c.md.disasm(a2c.TD[a - a2c.TB:a - a2c.TB + s], a):
        out.append((ins.mnemonic, ins.op_str if not re.match(r'^(b|bl|adrp|adr|cbz|cbnz|tbz|tbnz|b\..*)$', ins.mnemonic) else ins.op_str))
    return tuple(out)


FUNCS = []  # (group, sym, addr)
seen = set()
for n in NAMES:
    if n not in dyn:
        print(f'WARNING: {n} not exported', file=sys.stderr)
        continue
    a, s = dyn[n]
    if s < 8:
        continue
    if a in seen:
        continue
    seen.add(a)
    FUNCS.append((group_of(n), n, a))
body_addrs = {a: (g, n) for g, n, a in FUNCS}
INDEX = {a: i for i, a in enumerate(sorted(body_addrs))}  # (table order)

MATH = {
    '_ZN4Aska6Matrix3MulEPKS0_S2_': '::soa::particles::plog_range(X(0), 64); mat_mul((Mat44*)X(0), (const Mat44*)X(1), (const Mat44*)X(2));',
    '_ZN4Aska6Matrix11MulFromLeftEPKS0_': '::soa::particles::plog_range(X(0), 64); mat_mul_from_left((Mat44*)X(0), (const Mat44*)X(1));',
    '_ZN4Aska6Matrix3MulEPKS0_': '::soa::particles::plog_range(X(0), 64); mat_mul((Mat44*)X(0), (const Mat44*)X(1));',
}
HOST = {
    'memset': '::soa::particles::pmemset(X(0), (int)W(1), X(2));',
    'memcpy': '::soa::particles::plog_range(X(0), X(2)); memcpy((void*)X(0), (const void*)X(1), X(2));',
    'memmove': '::soa::particles::plog_range(X(0), X(2)); memmove((void*)X(0), (const void*)X(1), X(2));',
    # (the HLE libm imports are the host functions: hle/libm.cpp)
    'expf': 'S(0) = ::expf(S(0));',
    'tanf': 'S(0) = ::tanf(S(0));',
}
guest_calls = set()


def fallback(kind, t, reg):
    if kind in ('blr', 'br'):
        return f'particles_icall(r, {reg});'
    if t in body_addrs:
        # (with a live check on, through particles_direct(), which may check the call)
        return f'if (__builtin_expect(g_check_direct, 0)) particles_direct(r, {INDEX[t]}); else g_pbody[{INDEX[t]}](r);'
    n = L.name(t)
    if n.startswith('PLT:'):
        pn = n[4:]
        if pn in HOST:
            return HOST[pn]
        if pn in dyn and dyn[pn][0] != t:
            return fallback(kind, dyn[pn][0], reg)
        guest_calls.add(t)
        return f'models_gcall(r, LIB + 0x{t:x}); /* {pn} */'
    if n in MATH:
        return MATH[n]
    if n in dyn and dyn[n][1] == 4:
        ins = next(a2c.md.disasm(a2c.TD[t - a2c.TB:t - a2c.TB + 4], t))
        if ins.mnemonic == 'b':
            return fallback(kind, int(ins.op_str.lstrip('#'), 16), reg)
    guest_calls.add(t)
    return f'models_gcall(r, LIB + 0x{t:x}); /* {a2c.dem(n)[:80]} */'


a2c.CALL_FALLBACK = fallback
a2c.EXCLUSIVE = True
a2c.NAN_EXACT = True
a2c.EXTRA_CALLS.clear()
for k in ('__cxa_guard_acquire', '__cxa_guard_release'):
    a2c.CALLS.pop(k, None)
for k, v in MATH.items():
    a2c.EXTRA_CALLS[k] = v

out = ['''// GENERATED by tools/gen_particles_a2c.py from libSOA.so's ARM64 code: do not edit by hand; regenerate.
// ''' + genlib.stamp() + '''
//
// The particle simulation (ParticleEmitter<> / ParticleObject<> instantiations, IParticleEmitter /
// IParticleObject, ParticleEmitter*Unit, ParticleManager, ParticleMakeMatrix) transcribed
// instruction by instruction by tools/a2c.py. Registration, switches and tests: particles_rt.cpp.
#pragma GCC optimize("fp-contract=off")
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wuninitialized"
#include <cmath>
#include <cstdlib>
#include <cstring>

#include "core/cpu.h"
#include "native/engine/math/aska_math.h"
#include "native/models/models.h"
#include "native/particles/particles.h"

// Stores go through the check's store log (particles.h: off unless a live check is running).
#undef STI8
#undef STI16
#undef STI32
#undef STI64
#undef STS
#undef STD
#undef STQ
#define STI8(a, v) ::soa::particles::psti<u8>(a, (u8)(v))
#define STI16(a, v) ::soa::particles::psti<u16>(a, (u16)(v))
#define STI32(a, v) ::soa::particles::psti<u32>(a, (u32)(v))
#define STI64(a, v) ::soa::particles::psti<u64>(a, (u64)(v))
#define STS(n, a) ::soa::particles::pstf(a, r.v[n].f[0])
#define STD(n, a) (::soa::particles::pstf(a, r.v[n].f[0]), ::soa::particles::pstf((a) + 4, r.v[n].f[1]))
#define STQ(n, a) (::soa::particles::pstf(a, r.v[n].f[0]), ::soa::particles::pstf((a) + 4, r.v[n].f[1]), ::soa::particles::pstf((a) + 8, r.v[n].f[2]), ::soa::particles::pstf((a) + 12, r.v[n].f[3]))

namespace soa::particles {
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
BODY_TEXT = {}
for a in sorted(body_addrs):
    g, n = body_addrs[a]
    body = a2c.translate(n, f'f_{a:x}')
    # (raw lane stores: through the store log too)
    body = re.sub(r'(?<![\w:])stf\(', '::soa::particles::pstf(', body)
    assert not re.search(r'(?<![\w:])sti<', body), n
    if '#error' in body:
        bad.append((n, re.findall(r'#error "a2c: ([^"]*)"', body)[:3]))
    BODY_TEXT[a] = body
    bodies.append(f'// {a2c.dem(n)}')
    bodies.append(f'static void f_{a:x}(A64& r) {{')
    bodies.append('    u64 jt_ = 0, ex_a_ = 0, ex_v_ = 0;')
    bodies.append('    (void)jt_; (void)ex_a_; (void)ex_v_;')
    bodies.append(body.rstrip())
    bodies.append('}')
out += bodies
out.append('')
for i, a in enumerate(sorted(body_addrs)):
    out.append(f'static void h_{a:x}(Cpu& c) {{ particles_hook(c, {i}); }}')
out.append('')
# Guest callees that make a call unrepeatable (allocation, synchronization with other threads, the
# render side filling vertex buffers, scene-graph links): a body reaching one (itself or through
# its direct callees) is not live-checked.
UNREPEATABLE = re.compile(r'Semaphore::|FastCriticalSection|Thread::Sleep|operator new|operator delete|Malloc|::Free\(|AlignedMalloc|'
                          r'RenderProcedure|AttachChild|DetachFromParent|SetRenderLayer|BitArray::Alloc|QueryTexture|ReleaseImmediately|'
                          r'DeleteThisImmediately|pthread_mutex|RunLow|RunAfterRendering|DispatchEmitters|PostMessage')
BY_INDEX = sorted(body_addrs)
direct = {a: set(BY_INDEX[int(m)] for m in re.findall(r'particles_direct\(r, (\d+)\)', BODY_TEXT[a])) - {a} for a in body_addrs}
own_bad = {a: bool(UNREPEATABLE.search(' '.join(re.findall(r'/\* ([^*]*) \*/ /\*', BODY_TEXT[a])))) for a in body_addrs}
DRAWS = re.compile(r'Aska::Random|Aska::MT::Rand|ShuffleRandom')
own_draw = {a: bool(DRAWS.search(' '.join(re.findall(r'/\* ([^*]*) \*/ /\*', BODY_TEXT[a])))) or 'particles_icall' in BODY_TEXT[a] for a in body_addrs}
def reaches_draw(a, seen=None):
    seen = seen or set()
    if own_draw[a]:
        return True
    seen.add(a)
    return any(reaches_draw(b, seen) for b in direct[a] if b in body_addrs and b not in seen)
def reaches_bad(a, seen=None):
    seen = seen or set()
    if own_bad[a]:
        return True
    seen.add(a)
    return any(reaches_bad(b, seen) for b in direct[a] if b in body_addrs and b not in seen)
# The render group is live-checked (by stores) only where a call is repeatable as a whole: no
# virtual calls and no guest callees but pure queries and math (the render device / GL, shader keys,
# index buffers, mesh-instance locks and the like act outside the store log: they would run twice).
PURE = re.compile(r'Aska::Matrix::|Aska::Vector::|ObjectManager::Is(ReducedBufferLayer|NeedZLayer)|VertexBuffer::GetData|'
                  r'Camera::GetFogConst|ObjectManager::GetNoTexture|RenderableObject::Get(Deepest|Shallowest)Z|GetDefaultLogicalId')
def render_pure(a, seen=None):
    seen = seen or set()
    t = BODY_TEXT[a]
    if 'particles_icall' in t or 'models_gcall(r, LIB + 0x' in t and any(not PURE.search(c) for c in re.findall(r'models_gcall\(r, LIB \+ 0x\w+\); /\* (.*?) \*/ /\* [0-9a-f]+: ', t)):
        return False
    seen.add(a)
    return all(render_pure(b, seen) for b in direct[a] if b in body_addrs and b not in seen)
out.append('const ParticlesFn g_particles_fns[] = {')
for a in sorted(body_addrs):
    g, n = body_addrs[a]
    d = a2c.dem(n)
    # The live check runs a call twice (transcription, then the original from the undone state):
    # functions that allocate, free, take semaphores / reference counts or post work can't be
    # run twice. They are tested by particles/setup-units and the smoke / battle runs instead.
    nocheck = bool(re.search(r'CreateParticle|PreAllocateBuffers|::Prepare\(\)|ParticleManager::Run\(|::Handler\(|::Alloc\(|operator new|operator delete|'
                             r'::~|DeleteThisImmediately|::Release\(|DeleteCallback|AddRef|::Reset\(|::Attach|AttachObject|AttachTexture|'
                             r'::Initialize\(|OnActive|SetEmissionMesh|DetachRenderable|gSetParticleEmitterNum|::I?Particle\w*\(\)$|Unit\(\)$', d) or re.search(r'(\w+)::\1\(', d)) or reaches_bad(a)
    if g == 'render':
        nocheck = nocheck or not render_pure(a)
    # (ParticleEmitter<FL>::Emit is void: its w0 / s0 are left over, not a result)
    ret = bool(re.search(r'::(Get\w*|Is\w*|SkipThisFrame|GatherActive|GetDefaultLevel|ColorRate|LockBuffer|FillSprite\w*|FillVerts|Fill|End|Begin|BindShader)\(', d))
    draws = reaches_draw(a)  # (draws random numbers, or makes a virtual call that might: the check compares the random state)
    out.append(f'    {{0x{a:x}, "{n}", "{g}", f_{a:x}, h_{a:x}, {"false" if nocheck else "true"}, {"true" if ret else "false"}, {"true" if draws else "false"}}},')
out.append('};')
out.append('const int g_particles_nfns = sizeof g_particles_fns / sizeof g_particles_fns[0];')
# The guest callees of the render group's unrepeatable bodies (render device, shader keys, index
# buffers, ...): the render check (particles_rt.cpp) stubs them in its two comparison runs and
# compares the calls made to them. (Pure queries and libc stay real.)
callees = {}
for a in sorted(body_addrs):
    if body_addrs[a][0] != 'render':
        continue
    for t, nm in re.findall(r'models_gcall\(r, LIB \+ 0x([0-9a-f]+)\); /\* (.*?) \*/ /\* [0-9a-f]+: ', BODY_TEXT[a]):
        t = int(t, 16)
        n = L.name(t)
        if n.startswith('PLT:') or PURE.search(nm) or t in body_addrs:
            continue
        callees[t] = n
def arity(n):
    # (integer / float argument registers of a callee, from its signature: `this` for members,
    # except RenderState::Static's functions, which are static)
    d = a2c.dem(n)
    m = re.search(r'\((.*)\)( const)?$', d)
    args, depth, cur = [], 0, ''
    for ch in (m.group(1) if m else ''):
        depth += ch in '<(' and 1 or ch in '>)' and -1 or 0
        if ch == ',' and depth == 0:
            args.append(cur.strip())
            cur = ''
        else:
            cur += ch
    if cur.strip() and cur.strip() != 'void':
        args.append(cur.strip())
    nf = sum(1 for x in args if x in ('float', 'double'))
    ints = [x for x in args if x not in ('float', 'double')]
    if n.startswith('_ZN') and '11RenderState' not in n:
        ints = ['this*'] + ints
    # (bytes of each integer argument that are defined: the rest of a w / byte register is not)
    def width(x):
        if x.endswith(('*', '&')) or x in ('unsigned long', 'long', 'unsigned long long', 'long long'):
            return 8
        if x in ('bool', 'unsigned char', 'signed char', 'char'):
            return 1
        if x in ('unsigned short', 'short'):
            return 2
        return 4  # int, unsigned int, enums
    return ''.join(str(width(x)) for x in ints), nf
out.append('const ParticlesCallee g_particles_render_callees[] = {')
for t in sorted(callees):
    ni, nf = arity(callees[t])
    out.append(f'    {{0x{t:x}, "{callees[t]}", "{ni}", {nf}}},  // {a2c.dem(callees[t])[:100]}')
out.append('};')
out.append('const int g_particles_render_ncallees = sizeof g_particles_render_callees / sizeof g_particles_render_callees[0];')
out.append('}  // namespace soa::particles')
open(OUT, 'w').write('\n'.join(out) + '\n')
for n, e in bad:
    print(f'UNSUPPORTED {n}: {e}', file=sys.stderr)
print(f'{len(body_addrs)} bodies, {len(guest_calls)} guest call targets, {len(bad)} unsupported', file=sys.stderr)
if os.environ.get('PARTICLES_LIST_GCALLS'):
    for t in sorted(guest_calls):
        print(f'gcall {t:x} {a2c.dem(L.name(t).replace("PLT:", ""))}', file=sys.stderr)
