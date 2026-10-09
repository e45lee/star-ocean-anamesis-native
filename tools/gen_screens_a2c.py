#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Generates port/src/native/ui/screen/gen/screen_a2c.cpp: large screen / game-flow functions transcribed by a2c.py.

The per-frame state machines of the home screen, its 3D model view (touch / pinch input, talk
mode) and the mission menu are long and full of inlined libc++ string and std::function code, so
they are transcribed instruction by instruction instead of hand-written. Every outgoing call goes
through screen_gcall() / screen_icall() (screen_a2c.h), which normally dispatch like the model
layer's calls (models_gcall / models_icall) and, in the live test, record and replay them.

Usage: gen_screens_a2c.py <out.cpp>
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

# (mangled symbol, bytes of the object at x0 the live test snapshots, returns a value)
FUNCS = [
    ('_ZN5CHome8ProgressEv', 0x530, False),
    # CHome::Update: left out (only called inside other checked functions, so the live test never
    # checks it on its own)
    ('_ZN5CHome13PopupProgressEv', 0x530, True),
    # CHome::PlayTalk: left out (its live replay diverged: a callee's stack-string result isn't captured)
    ('_ZN21CHomeModelViewManager8ProgressEv', 0x3300, False),
    ('_ZN21CHomeModelViewManager10CheckInputEv', 0x3300, False),
    ('_ZN21CHomeModelViewManager17Progress_HomeTalkEv', 0x3300, False),
    ('_ZN12CMissionMenu8ProgressEv', 0x1720, False),
    ('_ZN12CMissionMenu5InputENS_16MissionMenuSceneEb', 0x1720, False),
    ('_ZN12CMissionMenu9ShowStateENS_7tUIModeE', 0x1720, False),
    ('_ZN16CScenarioLibrary10ChangeShowEbNS_7SceneIDE', 0x2e0, False),
    ('_ZN16CScenarioLibrary15ChangeActiveTabENS_7TabTypeE', 0x2e0, False),
    ('_ZN16CScenarioLibrary17SetSceneTitleInfoENS_14SceneTitleInfoE', 0x2e0, False),
    # (CHome::UpdatePremiumLoginBonus is left out: its live replay broke the game. TalkMotion /
    # PlayMotion / UpdateEventBadge / CMissionMenu::NextPhase / SetMultiBtn: not reached on their own
    # by the live test's session, so not transcribed.)
    ('_ZN21CHomeModelViewManager20PlayStayMotionRandomEPNS_13HomeCharacterEjf', 0x3300, False),
    ('_ZN21CHomeModelViewManager23TapReactionMotionRandomEPNS_13HomeCharacterE', 0x3300, False),
    ('_ZN21CHomeModelViewManager15MouthMotionStopEPNS_13HomeCharacterE', 0x3300, False),
    ('_ZN5CHome11UpdateBadgeEv', 0x530, False),
    ('_ZN5CHome20UpdateMainteAnnounceEv', 0x530, False),
    ('_ZN5CHome24UpdateStarterMissionListEv', 0x530, False),
    ('_ZN5CHome26SetFavorabilityIconVisibleEv', 0x530, False),
    ('_ZN5CHome11SetTalkModeEbb', 0x530, False),
    ('_ZN5CHome14ExitCommonMenuEv', 0x530, False),
    ('_ZN12CMissionMenu18StateCheckTimeOverEv', 0x1720, True),
    ('_ZN12CMissionMenu17PatrySelectReturnEv', 0x1720, False),
    ('_ZN16CScenarioLibrary22StopAnimationTabButtonEv', 0x2e0, False),
    ('_ZN16CScenarioLibrary14ExitCommonMenuEv', 0x2e0, False),
    # batch 3: boot / flow phases, character picture book. (CPhase_Server / CPhase_Login::Progress
    # are left out: their replays diverge, they read state their callees change elsewhere.)
    ('_ZN19CPhase_DataDownload8ProgressEv', 0x58, True),
    ('_ZN19CPhase_TutorialNext8ProgressEv', 0x28, True),
    ('_ZN21CCharacterPictureBook14ReplacementEndERN9Framework10CSTLVectorIN17CParameterUtility11tCharaParamEEE', 0x378, False),
    # batch 4 (agent cleanups): CMissionMenu::Initialize.
    ('_ZN12CMissionMenu10InitializeENS_9eInitModeE', 0x1720, False),
    # batch 5: CMissionMenu::Setup / ToMissionDetail. (Their live check used to crash the process:
    # the transcriptions' stores weren't in the check's undo log, so the original's replay started
    # from the memory the transcription left, took other branches than the recorded run and called
    # through recorded results that weren't meant for it.) ShowEx: checked where the original
    # ShowState calls it. StateDetailMission: 14 arguments with `this`, six on the stack (the check
    # runs the original at the entry SP, so they are in place).
    ('_ZN12CMissionMenu5SetupEv', 0x1720, False),
    ('_ZN12CMissionMenu15ToMissionDetailEi', 0x1720, False),
    ('_ZN12CMissionMenu6ShowExENS_7tUIModeEb', 0x1720, False),
    ('_ZN12CMissionMenu18StateDetailMissionEjjjlRKNSt6__ndk18functionIFvvEEERKNS1_IFviEEERKNS1_IFvbEEESD_RKNS1_IFvbbEEElbbb', 0x1720, False),
]

dyn = a2c.syms
# memset / memcpy / memmove run on the host (screen_memop, screen_a2c.h: 1 / 2 / 3); the live check
# records them as calls (and undoes / redoes their stores).
HOST = {'memset': 1, 'memcpy': 2, 'memmove': 3}
calls = {}


def fallback(kind, t, reg):
    if kind in ('blr', 'br'):
        return f'screen_icall(r, {reg});'
    n = L.name(t)
    if n.startswith('PLT:') and n[4:] in HOST:
        return f'screen_memop(r, LIB + 0x{t:x}, {HOST[n[4:]]});'
    calls[t] = n
    return f'screen_gcall(r, LIB + 0x{t:x}); /* {a2c.dem(n.replace("PLT:", ""))[:80]} */'


a2c.CALL_FALLBACK = fallback
a2c.EXCLUSIVE = True
a2c.NAN_EXACT = True
a2c.EXTRA_CALLS.clear()
for k in ('__cxa_guard_acquire', '__cxa_guard_release'):
    a2c.CALLS.pop(k, None)

out = ['''// GENERATED by tools/gen_screens_a2c.py from libSOA.so's ARM64 code: do not edit by hand; regenerate.
// ''' + genlib.stamp() + '''
//
// Screen / game-flow functions transcribed instruction by instruction by tools/a2c.py (the home
// screen's and its 3D view's per-frame state machines, the mission menu). Calls go through
// screen_gcall / screen_icall (screen_a2c.h). Registration, switches and tests: screen_a2c_rt.cpp.
#pragma GCC optimize("fp-contract=off")
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wuninitialized"
#include <cstdlib>
#include <cstring>

#include "core/cpu.h"
#include "native/engine/math/aska_math.h"
#include "native/common/live_check.h"
#include "native/models/models.h"
#include "native/ui/screen/screen_a2c.h"

namespace soa::screen_a2c {
using namespace ::soa::aska;
using namespace ::soa::aska::a2c;
using namespace ::soa::models;
using a2c::u64;
using a2c::u32;
using ::soa::live::t_undo_on;
using ::soa::live::undo_note;

// Stores (for the live check's undo log, live_check.h: the replay of the original starts from the
// memory the transcription's run saw).
template <class T>
inline void screen_sti(u64 a, T v) {
    if (t_undo_on) [[unlikely]] undo_note(a, sizeof(T));
    sti<T>(a, v);
}
inline void screen_stf(u64 a, float v) {
    if (t_undo_on) [[unlikely]] undo_note(a, 4);
    stf(a, v);
}
#undef STI8
#undef STI16
#undef STI32
#undef STI64
#undef STS
#undef STD
#undef STQ
#define STI8(a, v) screen_sti<u8>(a, (u8)(v))
#define STI16(a, v) screen_sti<u16>(a, (u16)(v))
#define STI32(a, v) screen_sti<u32>(a, (u32)(v))
#define STI64(a, v) screen_sti<u64>(a, (u64)(v))
#define STS(n, a) screen_stf(a, r.v[n].f[0])
#define STD(n, a) (screen_stf(a, r.v[n].f[0]), screen_stf((a) + 4, r.v[n].f[1]))
#define STQ(n, a) (screen_stf(a, r.v[n].f[0]), screen_stf((a) + 4, r.v[n].f[1]), screen_stf((a) + 8, r.v[n].f[2]), screen_stf((a) + 12, r.v[n].f[3]))
''']
bad = []
bodies = []
table = []
for n, osz, ret in FUNCS:
    if n not in dyn:
        print(f'WARNING: {n} not exported', file=sys.stderr)
        continue
    a, s = dyn[n]
    body = a2c.translate(n, f'f_{a:x}')
    if '#error' in body:
        bad.append((n, re.findall(r'#error "a2c: ([^"]*)"', body)[:3]))
    bodies.append(f'// {a2c.dem(n)}')
    bodies.append(f'static void f_{a:x}(A64& r) {{')
    bodies.append('    u64 jt_ = 0, ex_a_ = 0, ex_v_ = 0;')
    bodies.append('    (void)jt_; (void)ex_a_; (void)ex_v_;')
    bodies.append(body.rstrip())
    bodies.append('}')
    bodies.append(f'static void h_{a:x}(Cpu& c) {{ models_run_hook(c, f_{a:x}); }}')
    table.append(f'    {{0x{a:x}, "{n}", f_{a:x}, h_{a:x}, 0x{osz:x}, {"true" if ret else "false"}}},')
out += bodies
out.append('')
out.append('const ScreenA2cFn g_screen_a2c_fns[] = {')
out += table
out.append('};')
out.append('const int g_screen_a2c_nfns = sizeof g_screen_a2c_fns / sizeof g_screen_a2c_fns[0];')
out.append('}  // namespace soa::screen_a2c')
open(OUT, 'w').write('\n'.join(out) + '\n')
for n, e in bad:
    print(f'UNSUPPORTED {n}: {e}', file=sys.stderr)
print(f'{len(table)} bodies, {len(calls)} call targets, {len(bad)} unsupported', file=sys.stderr)
