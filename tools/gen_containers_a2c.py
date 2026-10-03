#!/usr/bin/env python3
"""Generates port/src/native/containers/gen/containers_a2c.cpp: the Aska array / pool / hash-map templates
(TDynamicArray<T, A> and its TArrayIterator inserts, Algo::QuickSort over them, TPoolFast<T, b>,
THashMap<K, V, ...>) transcribed from the ARM64 by a2c.py (CALL_FALLBACK: other calls go to the
guest, or straight to a native replacement).

Their instantiations differ in element type, constructor functor and allocator, so each has its
own code; transcription keeps every one exact without writing ~150 bodies by hand.

Also the executed functions of Aska::Yayoi, Aska::Global and the other EXEC_FAMILIES (one-shot setup
and per-frame glue): the names in tools/containers_exec_funcs.txt (frozen from the coverage list the
first committed file was made with; lib-agnostic). Given a coverage list (executed mangled names)
and the current native list (`soa --list-native`), it also prints the executed EXEC_FAMILIES
functions the list lacks, to extend it.

Lib: SOA_LIB, default work/libSOA-3.7.0.so (tools/genlib.py); the output header records it.

Usage: .venv/bin/python tools/gen_containers_a2c.py port/src/native/containers/gen/containers_a2c.cpp [executed.txt native.txt]"""
import importlib.util
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import genlib  # noqa: E402 (before a2c: the default lib is 3.7.0's)

_spec = importlib.util.spec_from_file_location('a2c', os.path.join(os.path.dirname(os.path.abspath(__file__)), 'a2c.py'))
a2c = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(a2c)
a2c.EXCLUSIVE = True


def call_fallback(kind, target, reg):
    fn = f'LIB + {target:#x}' if target is not None else reg
    return f'CONT_A2C_CALL({fn});'


a2c.CALL_FALLBACK = call_fallback
a2c.TPIDR = 'A2C_TPIDR()'  # (containers_a2c.h)
a2c.CALLS['memset'] = 'std::memset((void*)X(0), (int)W(1), (size_t)X(2));'
a2c.CALLS['memcpy'] = 'std::memcpy((void*)X(0), (const void*)X(1), (size_t)X(2));'
a2c.CALLS['memmove'] = 'std::memmove((void*)X(0), (const void*)X(1), (size_t)X(2));'

FAMILIES = [
    r'^Aska::TDynamicArray<',
    r'^Aska::TArrayIterator<Aska::TDynamicArray<.*> > Aska::TDynamicArray<',
    r'^void Aska::Algo::detail::QuickSort<Aska::TArrayIterator<Aska::TDynamicArray<',
    r'^Aska::TPoolFast<',
    r'^Aska::THashMap<',
]

syms = []
for s in a2c.L.elf.get_section_by_name('.dynsym').iter_symbols():
    if s.name and s['st_value'] and s['st_size'] >= 8 and s['st_info']['type'] == 'STT_FUNC':
        syms.append(s.name)
syms = sorted(set(syms))
dem = dict(zip(syms, subprocess.run(['c++filt'], input='\n'.join(syms), capture_output=True, text=True).stdout.split('\n')))
pick = [s for s in syms if any(re.search(f, dem[s]) for f in FAMILIES)]
# destructors of classes with virtual bases or thunks are left alone
pick = [s for s in pick if not s.startswith('_ZThn')]
# already native elsewhere: the ASON work-buffer array (ason.cpp)
pick = [s for s in pick if 'WorkBufferContext' not in s]

# Executed-only families (one-shot setup code and SDK glue): the functions listed in an executed-
# functions file (profile coverage), minus those already native (`soa --list-native`).
EXEC_FAMILIES = [
    r'^Aska::Yayoi::',
    r'^Aska::Global::',
    r'^Aska::Camera(Manager|FilterManager)?::',  # view / projection matrices, frustum planes, exposure
    # per-frame engine managers no other port covers
    r'^Aska::(ModifierManager|VSync|AimingObject|PerformanceCounter|DeleteManager|ParticleManager|LightManager)::',
    r'^(CTimeUtility|StaminaUtility)::',
    r'^Framework::(CCamera|CTimeElement|CResourceManager|CACSV)::',
]
LISTED = set()
for _l in open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'containers_exec_funcs.txt')):
    _l = _l.split('#')[0].strip()
    if _l:
        LISTED.add(_l)
for _n in sorted(LISTED - set(syms)):
    print(f'containers_exec_funcs.txt: {_n} not in the lib (skipped)', file=sys.stderr)
pick += [s for s in syms if s in LISTED and s not in pick]
if len(sys.argv) > 3:
    executed = set(l.strip() for l in open(sys.argv[2]))
    native = set(l.split('\t')[0].strip() for l in open(sys.argv[3]))
    extra = [s for s in syms if s in executed and s not in native and any(re.search(f, dem[s]) for f in EXEC_FAMILIES)]
    extra = [s for s in extra if not re.search(r'Global::InitializeMemoryManager', dem[s])]  # the engine heap's setup stays with aska_memory
    for s in extra:
        if s not in pick:
            print(f'candidate for containers_exec_funcs.txt (executed, not native): {s}  {dem[s][:100]}', file=sys.stderr)

OUT = sys.argv[1]
bodies, failed = [], []
for i, sym in enumerate(pick):
    name = f'c{i}'
    try:
        body = a2c.translate(sym, name)
    except Exception as e:  # noqa: BLE001
        failed.append((sym, str(e)))
        continue
    if '#error' in body:
        failed.append((sym, 'untranslated'))
        continue
    if re.search(r': br x', body) and not any(re.search(f, dem[sym]) for f in FAMILIES):
        # an indirect branch inside the function (a jump table) would continue in the guest
        # without the body's frame: left in ARM64
        failed.append((sym, 'indirect branch'))
        continue
    bodies.append((sym, name, body))

out = ['// GENERATED by tools/gen_containers_a2c.py from libSOA.so (a2c.py: CALL_FALLBACK + EXCLUSIVE) -- do not edit.',
       '// ' + genlib.stamp(),
       '// Aska::TDynamicArray / TArrayIterator inserts / QuickSort / TPoolFast / THashMap instantiations,',
       '// transcribed instruction by instruction (containers_a2c_test.cpp has the tests).',
       '#include <cstring>',
       '',
       '#include "native/engine/math/aska_math.h"',
       '#include "native/engine/math/aska_math_a2c.h"',
       '#include "native/containers/containers_a2c.h"',
       '#include "native/engine/objmgr_a2c.h"',
       '',
       'namespace soa::cont::a2c_body {',
       'using namespace ::soa::aska;',
       'using namespace ::soa::aska::a2c;',
       '']
for sym, name, _ in bodies:
    out.append(f'void b_{name}(A64& r);')
out.append('')
for sym, name, body in bodies:
    out.append(f'// {dem[sym][:200]}')
    out.append(f'void b_{name}(A64& r) {{')
    out.append('    u64 jt_ = 0, ex_a_ = 0, ex_v_ = 0;')
    out.append('    (void)jt_, (void)ex_a_, (void)ex_v_;')
    out.append(body.rstrip())
    out.append('}')
    out.append('')
out.append('const Entry kEntries[] = {')
for sym, name, _ in bodies:
    out.append(f'    {{"{sym}", hook<b_{name}>, b_{name}}},')
out.append('};')
out.append('const size_t kNumEntries = sizeof kEntries / sizeof kEntries[0];')
out.append('')
out.append('}  // namespace soa::cont::a2c_body')
open(OUT, 'w').write('\n'.join(out) + '\n')
print(f'{len(bodies)} transcribed, {len(failed)} skipped', file=sys.stderr)
for s, e in failed:
    print(f'  skipped {dem[s][:120]}: {e[:80]}', file=sys.stderr)
