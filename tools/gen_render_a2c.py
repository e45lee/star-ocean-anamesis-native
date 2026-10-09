#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Generates port/src/native/render/gen/render_a2c.cpp: render-pipeline functions transcribed by a2c.py.

Covers the parts of the render pipeline that are long, FP-heavy or lock-heavy (post-processing
passes and their constants, the render thread's command loop, the GL resource handlers), where a
hand-written version would be hard to keep bit-exact. Runtime and dispatch are the model layer's
(models.h): direct calls between the bodies here are C++ calls, virtual calls go through
models_icall(), and everything else is models_gcall(), which calls native replacements directly.

Usage: gen_render_a2c.py <out.cpp>
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

# (group, mangled symbol). Groups are for SOA_RENDER_A2C_OFF.
# Left out because their prologue can't be relocated for a test hook (so the live test can't reach
# them): Camera::AdjustCameraEV, CameraFilterManager::GetCombinerBias,
# OpticalPhenomenon::GetBloomBlendRates, PostProcessBufferManager::PrepareForRendering. Also left out:
# PostProcessCombinerTBR::UpdateBloomTargetBorder / MakePrim / MakeGrainUV, which only run when the
# bloom targets are (re)built, so no test run reaches them.
GROUPS = {
    'post': [
        '_ZN4Aska22PostProcessCombinerTBR6RenderEPNS_13RenderContextEi',
        '_ZN4Aska22PostProcessCombinerTBR11RenderBloomEv',
        '_ZN4Aska22PostProcessCombinerTBR18SetShaderConstantsEv',
        '_ZN4Aska22PostProcessCombinerTBR12PrepareBloomEPKNS_10RENDERINFOE',
        '_ZN4Aska22PostProcessCombinerTBR30PrepareForPostPorcessRenderingEPKNS_10RENDERINFOE',
        '_ZN4Aska22PostProcessCombinerTBR27ExternalPrepareForRenderingEPKNS_10RENDERINFOEb',
        '_ZN4Aska22PostProcessCombinerTBR19PrepareForRenderingEPKNS_10RENDERINFOE',
        '_ZN4Aska22PostProcessCombinerTBR20PreliminarilyPrepareEPNS_12LightManagerE',
        '_ZN4Aska24PostProcessBufferManager6RenderEPNS_13RenderContextEi',
        '_ZN4Aska24PostProcessBufferManager20PreliminarilyPrepareEPNS_12LightManagerE',
        '_ZN4Aska24PostProcessBufferManager21ProcessTextureDiscardEv',
        '_ZN4Aska24PostProcessBufferManager22ProcessTextureAllocateEv',
        '_ZN4Aska24PostProcessBufferManager24DoesInsertToPaintingListEPNS_16RenderableObject3IPLEiiPKi',
        '_ZN4Aska19PostProcessBloomTBR19PrepareForRenderingEPKNS_10RENDERINFOE',
        '_ZN4Aska19PostProcessBloomTBR20PreliminarilyPrepareEPNS_12LightManagerE',
        '_ZN4Aska17OpticalPhenomenon20GetBloomUpscaleConstEv',
        '_ZN4Aska17OpticalPhenomenon17GetBloomGaussCoefEi',
        '_ZNK4Aska17OpticalPhenomenon19GetBloomGaussTapCntEi',
    ],
    # cameras: view / projection matrices, frustum planes, exposure
    'camera': [
        '_ZN4Aska6Camera20MakeViewFrustumPlaneEi',
        '_ZN4Aska6Camera16MakeCameraMatrixEv',
        '_ZN4Aska6Camera10MakeMatrixEv',
        '_ZN4Aska6Camera14SetWorldMatrixEPKNS_6MatrixE',
        '_ZN4Aska6Camera3RunEi',
        '_ZN4Aska6Camera11GetFogConstEv',
        ('_ZN4Aska6Camera28MakeLocalViewFrustumVerticesEPNS_6VectorEi', 'x1:0x100'),
        '_ZN4Aska13CameraManager14UpdatePrevViewEv',
        '_ZN4Aska19CameraFilterManager20GetIsoExposureOffsetEv',
        '_ZN4Aska19CameraFilterManager15UpdatePreMatrixEv',
    ],
    # lights and projectors
    'light': [
        '_ZN4Aska12LightManager25PrepareLightsForRenderingEPPNS_16RenderableObjectEi',
        # (MakeLightContext(RenderableObject*, LightContextSimple*) transcribes (a2c now has fcvt d, s),
        # but only ParticleRenderableBase::PrepareForRendering calls it, about once a session, and no
        # test run reached it (not even tapping the 3D character during the check): left out)
        '_ZN4Aska12LightManager17PrepareForTextureEv',
        ('_ZN4Aska12LightManager25CalcHemisphereLightCoeffsEPNS0_10SHAmbConstEPKNS_5LightEPNS_6VectorE', 'x1:0x100'),
        ('_ZN4Aska12LightManager21CalcBounceLightCoeffsEPNS0_10SHAmbConstEPNS_16RenderableObjectEPPNS_5LightEiS7_i', 'x1:0x100'),
        '_ZN4Aska9Projector20MakeProjectionMatrixEv',
        '_ZN4Aska9Projector10SyncCameraEv',
        '_ZN4Aska9Projector17SetShaderConstantEPNS_21ShaderConstantManagerEi',
        '_ZN4Aska16ProjectorManager3RunEi',
    ],
    'misc': [
        '_ZN4Aska15MaterialContext5ApplyEmPNS_14RenderDeviceGLEPNS_17ShaderNodeHandlerE',
        '_ZN4Aska19FilterShaderManager9SetShaderEii',
        '_ZN4Aska16RenderDeviceData12ResolveDepthEPNS_15ResolveTargetGLEPNS_12RenderTargetEbiiii',
        # (its prologue can't carry a test hook: render-a2c/bloom-blend-rates tests it on synthetic objects)
        ('_ZN4Aska17OpticalPhenomenon18GetBloomBlendRatesEv', 'nohook'),
    ],
    # GL vertex / index buffers (GpuResource handlers): not idempotent (GL objects), tested by
    # render-a2c/buffer-handlers on fake resources with the GL calls recorded
    'gpu': [
        (f'_ZN4Aska15_RenderDeviceGL15BufferHandlerGLILj{t}EXadL_ZNS_18ASKA_OGL_STATESET0{b}EEEXadL_ZNS0_{u}EPNS_11GpuResourceEEEE{m}ES4_', 'nohook')
        for t, b, u in (('34962', '14m_u32ArrayBind', '20GetUsageVertexBuffer'), ('34963', '21m_u32ElementArrayBind', '19GetUsageIndexBuffer'))
        for m in ('6Upload', '6Create', '6Update', '13ReleaseNative')
    ],
    # particle helpers whose effects the live check covers (the context structs they fill, the
    # object's animation fields). (IParticleObject::GatherActive, IParticleEmitter::Prepare,
    # ParticleRenderableBase::End and ParticleManager::RunAfterRendering transcribe and matched
    # too, but they also age particles / unlock mesh instances / post messages outside anything
    # the check compares: left out.)
    'particle': [
        ('_ZN4Aska15IParticleObject17CalcAnimationSizeEii', 'obj:0x200'),
        ('_ZN4Aska15IParticleObject12SetAnimationEi', 'obj:0x200'),
        ('_ZN4Aska16IParticleEmitter17FillMatrixContextEPNS0_13MatrixContextE', 'obj:0x400,x1:0x30'),
        ('_ZN4Aska22ParticleRenderableBase17CreateDrawContextEPNS0_11DrawContextE', 'obj:0x400,x1:0xe0'),
        ('_ZN4Aska22ParticleRenderableBase17CreateFillContextEPNS_19ParticleFillContextEj', 'obj:0x400,x1:0x48'),
    ],
    # scene objects: the aiming (look-at) objects' per-frame matrices
    'scene': [
        ('_ZN4Aska12AimingObject10MakeMatrixEv', 'obj:0x200,@x0+0x1b0:0x300,@x0+0x1b8:0x300'),
        ('_ZN4Aska12AimingObject14MakeMatrixMainEv', 'obj:0x200,@x0+0x1b0:0x300,@x0+0x1b8:0x300'),
    ],
    # shadow casters / receivers (ShadowManager, ShadowManagerRegistry): the per-frame ones. (The rest
    # of ShadowManager transcribes too but never ran in a test: AllocCandidateBuffer,
    # DeleteCandidateBuffer, Start/FinishAddReceiversToRenderList, AddOneReceiver,
    # GetBorderWidthForESM, Get, Set, Init, LocalClone.) The live checks of this group run in a
    # sandbox (render_shadow.h). Regions: "@xN+off:n" is the
    # buffer a pointer at xN+off points to, "*xN#xM:n" each object of the pointer array xN (count wM),
    # "@om+off:n" / "@@om+off:n" part of the ObjectManager / what a pointer in it points to, "$SYM:n"
    # the RenderableObject a global pointer points to.
    'shadow': [
        # (the caster / receiver arrays, the candidate buffers and the shadow camera, the ShadowManagerRegistry
        # (ObjectManager+0x104f0) slots; FinalReceiverCheckFunction
        # and the ReceiverWalkers are only called from here, and are tested through it)
        ('_ZN4Aska13ShadowManager19ShadowCasterCullingEPPNS_16RenderableObjectEiS3_i',
         'obj:0x400,@x0+0xd0:0x8000,@x0+0xd8:0x8000,@x0+0x200:0xf90,@x0+0xb8:0x400,@x0+0xc8:0x400,*x1#x2:0x800,*x3#x4:0x800,@@om+0x104f0:0x1200,'
         '@om+0x1c00:0x300,@om+0x3ee0:0x40,@@om+0x1ac8:0x4000,@om+0x4600:0x1300,@om+0x8de0:0x1300,@om+0xb1e0:0x220,'
         '$_ZN4Aska21ShadowManagerRegistry24m_pDummyRenderableObjectE:0x310'),
        ('_ZN4Aska13ShadowManager26FinalReceiverCheckFunctionEPPNS_16RenderableObjectEPNS_32FinalReceiverCheckFunctionParamsE', 'nohook'),
        ('_ZN14ReceiverWalkerI13NormalVisitorE4WalkEPPN4Aska16RenderableObjectEPNS2_32FinalReceiverCheckFunctionParamsEPNS2_5LightEPtPhhjPfPNS2_13ShadowManagerE', 'nohook'),
        ('_ZN14ReceiverWalkerI14CascadeVisitorE4WalkEPPN4Aska16RenderableObjectEPNS2_32FinalReceiverCheckFunctionParamsEPNS2_5LightEPtPhhjPfPNS2_13ShadowManagerE', 'nohook'),
        ('_ZN14ReceiverWalkerI16NormalVisitorESME4WalkEPPN4Aska16RenderableObjectEPNS2_32FinalReceiverCheckFunctionParamsEPNS2_5LightEPtPhhjPfPNS2_13ShadowManagerE', 'nohook'),
        ('_ZN14ReceiverWalkerI17CascadeVisitorESME4WalkEPPN4Aska16RenderableObjectEPNS2_32FinalReceiverCheckFunctionParamsEPNS2_5LightEPtPhhjPfPNS2_13ShadowManagerE', 'nohook'),
        ('_ZN4Aska21ShadowManagerRegistry12FirstPrepareEPNS_12LightManagerE', 'obj:0x1000'),
    ],
    # render-thread queue producers (not idempotent: tested on a fake RenderThread only)
    'thread': [
        '_ZN4Aska12RenderThread14AddBeginRenderEv',
        '_ZN4Aska12RenderThread12AddEndRenderEPNS_7INotifyE',
        '_ZN4Aska12RenderThread21AddChangeRenderTargetEjPNS_21MULTIPASS_ENVIRONMENTE',
        '_ZN4Aska12RenderThread21AddFinishRenderTargetEjii',
        '_ZN4Aska12RenderThread16AddExposureScaleEff',
        '_ZN4Aska12RenderThread14AddEnableFastZEb',
        '_ZN4Aska12RenderThread19AddTemporaryResolveEPNS_16RenderableObjectEii',
        '_ZN4Aska12RenderThread11AddCallBackEPFvmmEmm',
        '_ZN4Aska12RenderThread7ReqSwapEv',
    ],
}

dyn = a2c.syms
by_addr = {}
for n, (a, s) in dyn.items():
    by_addr.setdefault(a, n)

FUNCS = []
seen = set()
EXTRA = {}  # sym -> extra memory regions the live test snapshots ("x1:0x100,...")
for g, names in GROUPS.items():
    for n in names:
        if isinstance(n, tuple):
            n, EXTRA[n] = n
        if n not in dyn:
            print(f'WARNING: {n} not exported', file=sys.stderr)
            continue
        a, s = dyn[n]
        if s < 8:
            print(f'WARNING: {n} is {s} bytes (not hookable)', file=sys.stderr)
            continue
        if a in seen:
            continue
        seen.add(a)
        FUNCS.append((g, n))
body_addrs = {dyn[n][0]: (g, n) for g, n in FUNCS}

MATH = {
    '_ZN4Aska6Matrix3MulEPKS0_S2_': 'mat_mul((Mat44*)X(0), (const Mat44*)X(1), (const Mat44*)X(2));',
    '_ZN4Aska6Matrix11MulFromLeftEPKS0_': 'mat_mul_from_left((Mat44*)X(0), (const Mat44*)X(1));',
    '_ZN4Aska6Matrix3MulEPKS0_': 'mat_mul((Mat44*)X(0), (const Mat44*)X(1));',
}
HOST = {
    'memset': 'memset((void*)X(0), (int)W(1), X(2));',
    'memcpy': 'memcpy((void*)X(0), (const void*)X(1), X(2));',
    'memmove': 'memmove((void*)X(0), (const void*)X(1), X(2));',
}
guest_calls = set()


def fallback(kind, t, reg):
    if kind in ('blr', 'br'):
        return f'models_icall(r, {reg});'
    if t in body_addrs:
        return f'f_{t:x}(r);'
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

out = ['''// GENERATED by tools/gen_render_a2c.py from libSOA.so's ARM64 code: do not edit by hand; regenerate.
// ''' + genlib.stamp() + '''
//
// Render-pipeline functions transcribed instruction by instruction by tools/a2c.py (post-processing
// passes and constants, ...). Calls dispatch like the model layer's (models.h). Registration and
// switches: render_a2c_rt.cpp.
#pragma GCC optimize("fp-contract=off")
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wuninitialized"
#include <cstdlib>
#include <cstring>

#include "core/cpu.h"
#include "native/engine/math/aska_math.h"
#include "native/models/models.h"
#include "native/render/render_a2c.h"

namespace soa::render {
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
for idx, a in enumerate(sorted(body_addrs)):
    g, n = body_addrs[a]
    body = a2c.translate(n, f'f_{a:x}')
    if '#error' in body:
        bad.append((n, re.findall(r'#error "a2c: ([^"]*)"', body)[:3]))
    bodies.append(f'// {a2c.dem(n)}')
    bodies.append(f'static void f_{a:x}(A64& r) {{')
    # the readable version (render_rd.cpp) when there is one, unless SOA_RENDER_A2C=1 or this
    # thread runs the transcriptions as a test's reference (t_render_a2c)
    bodies.append(f'    if (models::Body rd_ = g_render_rd[{idx}]; rd_ && !t_render_a2c) {{ rd_(r); return; }}')
    bodies.append('    u64 jt_ = 0, ex_a_ = 0, ex_v_ = 0;')
    bodies.append('    (void)jt_; (void)ex_a_; (void)ex_v_;')
    bodies.append(body.rstrip())
    bodies.append('}')
out += bodies
out.append('')
for a in sorted(body_addrs):
    out.append(f'static void h_{a:x}(Cpu& c) {{ models_run_hook(c, f_{a:x}); }}')
out.append('')
out.append('const RenderA2cFn g_render_a2c_fns[] = {')
for a in sorted(body_addrs):
    g, n = body_addrs[a]
    ret = 'true' if re.search(r'(Get[A-Z]\w*|DoesInsert\w*|IsSupported\w*|Offset|Bias)E', n) else 'false'
    if g == 'shadow':
        ret = 'true' if re.search(r'(AllocCandidateBuffer|FinalReceiverCheckFunction|Walk|Init|Get|Set|GetBorderWidthForESM)E', n) else 'false'
    # Bytes of the object at x0 the live test snapshots (PostProcessCombinerTBR >= 0x1ed8,
    # Camera 0xf90; the others: a conservative prefix).
    osz = {'post': 0x2000, 'camera': 0xf90, 'light': 0x400, 'shadow': 0x400, 'scene': 0x200}.get(g, 0x100)
    out.append(f'    {{0x{a:x}, "{n}", "{g}", f_{a:x}, h_{a:x}, {ret}, "{EXTRA.get(n, "")}", 0x{osz:x}}},')
out.append('};')
out.append('const int g_render_a2c_nfns = sizeof g_render_a2c_fns / sizeof g_render_a2c_fns[0];')
out.append('}  // namespace soa::render')
open(OUT, 'w').write('\n'.join(out) + '\n')
for n, e in bad:
    print(f'UNSUPPORTED {n}: {e}', file=sys.stderr)
print(f'{len(body_addrs)} bodies, {len(guest_calls)} guest call targets, {len(bad)} unsupported', file=sys.stderr)
if os.environ.get('RENDER_LIST_GCALLS'):
    for t in sorted(guest_calls):
        print(f'gcall {t:x} {a2c.dem(L.name(t).replace("PLT:", ""))}', file=sys.stderr)
