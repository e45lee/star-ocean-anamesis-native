#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
r"""Generate port/src/native/particles/gen/particles_instantiations.inc: the ParticleEmitter<FeatureList<...>>
template instantiations of a libSOA.so whose Simulate(float) the particles subsystem binds
(port/src/native/particles/README.md).

From the dynamic symbols: every Aska::ParticleEmitter<...>::Simulate(float). Its code has one of two shapes
(with a Texture feature unit or without), the same instruction for instruction but for the callees and,
with a texture unit, that unit's offset in the emitter. Per row: the Simulate symbol, the three callees
of its own instantiation (EmitterAffectToParticle, Emit, ParticleRenderableObject<...>::RenderProcedure:
the targets of its BLs) and the texture unit's offset (0: none; the `ldr w8, [x19, #off]` the code reads
the unit's animation parameter with, the index at off + 0xa and the flags at off + 0xe). Each row is
checked against the shape's code (the first row of the shape is the reference, normalized: branch
targets relative, the texture offsets and the callees named); a row that doesn't fit fails the run (a new
code shape needs a look before it is bound). The differential tests (particles/simulate-*) run rows of
both shapes against the guest.

Usage:
  tools/gen_particles_instantiations.py [--lib PATH] [-o OUT]   # default: the 3.7.0 lib, write OUT
  tools/gen_particles_instantiations.py --check FILE           # exit 1 if FILE differs (header line not compared)
"""
import argparse
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import genlib  # noqa: E402 (before elfinfo: the default lib)

from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs  # noqa: E402

REPO = os.path.dirname(HERE)
DEFAULT_OUT = os.path.join(REPO, "port/src/native/particles/gen/particles_instantiations.inc")

RE_SIMULATE = re.compile(r"^_ZN4Aska15ParticleEmitterI(.*)E8SimulateEf$")
# The callees every Simulate makes, in order (the instance-specific ones as AFFECT / EMIT / RENDER).
SHARED = {
    "_ZN4Aska16IParticleEmitter16PerfCounterStartEv": "PerfCounterStart",
    "_ZnwmRKSt9nothrow_t": "new",
    "_ZN4Aska19FastCriticalSectionC1Ev": "FastCriticalSection",
    "_ZNK4Aska9Semaphore7IsReadyEv": "IsReady",
    "_ZNK4Aska9Semaphore4WaitEv": "Wait",
    "_ZN4Aska6Thread5SleepEj": "Sleep",
    "_ZN4Aska16IParticleEmitter17FillMatrixContextEPNS0_13MatrixContextE": "FillMatrixContext",
    "_ZN4Aska6RandomEj": "Random",
    "sqrtf": "sqrtf",
    "_ZNK4Aska6Matrix6PutPRSEPNS_6VectorEPNS_10QuaternionES2_": "PutPRS",
    "_ZN4Aska15IParticleObject12SetAnimationEi": "SetAnimation",
    "_ZN4Aska16IParticleEmitter14PerfCounterEndEv": "PerfCounterEnd",
    "_ZNK4Aska9Semaphore6SignalEv": "Signal",
}


def callee_kind(name, args):
    if name in SHARED:
        return SHARED[name]
    if name.startswith("_ZN4Aska15ParticleEmitterI" + args + "E23EmitterAffectToParticle"):
        return "AFFECT"
    if name.startswith("_ZN4Aska15ParticleEmitterI" + args + "E4EmitEi"):
        return "EMIT"
    if name.startswith("_ZN4Aska24ParticleRenderableObjectI" + args + "E15RenderProcedure"):
        return "RENDER"
    return None


def shape(L, md, va, size, args):
    """(normalized instruction list, callees by kind, texture offset or 0, errors)."""
    insns = list(md.disasm(L.read(va, size), va))
    callees, errors = {}, []
    tex = 0
    for i, ins in enumerate(insns):
        if ins.mnemonic == "str" and ins.op_str == "w8, [x0, #0x178]" and i and insns[i - 1].mnemonic == "ldr":
            m = re.match(r"w8, \[x19, #(0x[0-9a-f]+)\]$", insns[i - 1].op_str)
            if m:
                tex = int(m.group(1), 16)
    norm = []
    for ins in insns:
        op = ins.op_str
        if ins.mnemonic in ("bl", "b") or ins.mnemonic.startswith("b.") or ins.mnemonic in ("cbz", "cbnz", "tbz", "tbnz"):
            target = int(op.split("#")[-1], 16)
            if ins.mnemonic == "bl":
                name = L.name(target).replace("PLT:", "")
                kind = callee_kind(name, args)
                if kind is None:
                    errors.append("calls %s" % name)
                    kind = "?" + name
                if kind in ("AFFECT", "EMIT", "RENDER"):
                    if kind in callees and callees[kind] != name:
                        errors.append("two %s callees" % kind)
                    callees[kind] = name
                op = kind
            else:
                op = re.sub(r"#0x[0-9a-f]+$", "#%+d" % (target - ins.address), op)
        if tex:
            for d, tag in ((0, "T"), (0xa, "T+0xa"), (0xe, "T+0xe")):
                op = op.replace("[x19, #%#x]" % (tex + d), "[x19, #%s]" % tag)
        norm.append(ins.mnemonic + " " + op)
    for k in ("AFFECT", "EMIT", "RENDER"):
        if k not in callees:
            errors.append("no %s callee" % k)
    return norm, callees, tex, errors


def generate(lib_path):
    from elfinfo import Lib
    L = Lib(lib_path)
    md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
    sizes = {}
    for s in L.elf.get_section_by_name(".dynsym").iter_symbols():
        if s.name and s["st_value"]:
            sizes[s.name] = s["st_size"]
    rows, errors = [], []
    reference = {}  # has a texture unit -> the first row's normalized code
    for name in sorted(L.by_name):
        m = RE_SIMULATE.match(name)
        if not m:
            continue
        va = L.by_name[name]
        norm, callees, tex, errs = shape(L, md, va, sizes[name], m.group(1))
        errors += ["%s: %s" % (name, e) for e in errs]
        key = tex != 0
        ref = reference.setdefault(key, norm)
        if norm != ref:
            i = next((k for k, (a, b) in enumerate(zip(norm, ref)) if a != b), min(len(norm), len(ref)))
            errors.append("%s: not the shape (instruction %d: %s / %s)" % (name, i, norm[i] if i < len(norm) else "end", ref[i] if i < len(ref) else "end"))
        rows.append((va, name, callees.get("AFFECT"), callees.get("EMIT"), callees.get("RENDER"), tex))
    if len(reference) != 2:
        errors.append("expected the two shapes (with and without a texture unit), found %d" % len(reference))
    if errors:
        sys.exit("gen_particles_instantiations: rows that don't fit:\n  " + "\n  ".join(errors[:40]))
    rows.sort()
    out = ["// Generated by tools/gen_particles_instantiations.py (the ParticleEmitter<FeatureList<...>> instantiations); do not edit.",
           "// " + genlib.stamp(lib_path),
           "// PARTICLES_SIMULATE(Simulate symbol, EmitterAffectToParticle symbol, Emit symbol, RenderProcedure symbol, texture unit offset or 0),",
           "// %d rows. In code-address order." % len(rows),
           "#define PARTICLES_SIMULATES(X) \\"]
    for _, name, affect, emit, render, tex in rows:
        out.append('    X("%s", "%s", "%s", "%s", %#x) \\' % (name, affect, emit, render, tex))
    out.append("    /* end of PARTICLES_SIMULATES */")
    out.append("")
    return "\n".join(out)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--lib", default=genlib.lib_path())
    ap.add_argument("-o", "--out", default=DEFAULT_OUT)
    ap.add_argument("--check", metavar="FILE")
    a = ap.parse_args()
    text = generate(a.lib)
    if a.check:
        have = open(a.check).read().split("\n")
        want = text.split("\n")
        if have[2:] != want[2:]:
            sys.exit("%s differs from the generator's output for %s" % (a.check, a.lib))
        return
    os.makedirs(os.path.dirname(a.out), exist_ok=True)
    with open(a.out, "w") as f:
        f.write(text)
    print("%s written" % os.path.relpath(a.out, REPO))


if __name__ == "__main__":
    main()
