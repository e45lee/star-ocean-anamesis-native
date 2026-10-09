"""Wire format of the game-server RPC, from the client's own serializers.

Every request and every reply of the game RPC has a `GameProtocoledData::Set<Name>` serializer
in libSOA.so (390 of them). Each one stores its FunctionID at GameProtocoledData+0x30; this tool
finds that constant in the code (movz/movk into the register that is stored to [x, #0x30]) and
pairs it with the serializer's demangled parameter list.

Usage:
  api_wire.py --list                 print all serializers: kind, name, fid, parameters
  api_wire.py --gen-inc FILE         write the table the `wire/` selftest uses
                                     (port/src/native/api/gen/wire_table.inc)
  api_wire.py --doc LAYOUTS API_MD   insert / refresh the "- **Wire**" line of every API entry in
                                     docs/api.md from the layouts the selftest dumped
                                     (docs/api-wire.txt, SOA_WIRE_DUMP), matched by FunctionID
  api_wire.py --gen-decoder FILE [--layouts docs/api-wire.txt]
                                     write soa-server's request decoder table
                                     (server/net/gen/wire_decode.inc): every request's measured
                                     layout, the server method it maps to, whether it is
                                     encrypted, and its reply (FunctionID, encrypted, body kind)
  api_wire.py --check [--gen-inc FILE] [--gen-decoder FILE]
                                     compare instead of writing (exit 1 when a file is stale);
                                     with neither, both committed files (tools/check_generated.py)

The layouts are measured by the selftest (port/src/native/api/wire_test.cpp), which runs every
request serializer on the original ARM64 code and captures the plaintext body; this script only
formats them. Reply FunctionIDs come from the reply serializers (X <-> XRes, plus the pairs in
REPLY_PAIRS).
"""
import argparse
import os
import re
import subprocess
import sys

import genlib  # (before elfinfo: the default lib is 3.7.0's; tools/genlib.py)
from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs
from capstone.arm64 import ARM64_OP_IMM, ARM64_OP_MEM, ARM64_OP_REG
from elfinfo import lib

PREFIX = "_ZN4Aska5Yayoi7GameRPC18GameProtocoledData"
# Requests whose reply is not simply <Name>Res.
REPLY_PAIRS = {"Login": "LoginResult", "SimpleLogin": "SimpleLoginResult", "StartBridge": "ResultStart",
               "UpdateSession": "ResultUpdateSession", "LimitBreakCharacter_Legacy": "LimitBreakCharacterRes_Legacy"}

# Parameter types -> type code used by the selftest table.
TYPES = {
    "unsigned char": "B", "signed char": "b", "unsigned int": "I", "int": "i", "float": "f",
    "Aska::Yayoi::GameRPC::DeviceType": "D", "unsigned long": "Q", "signed char const*": "S",
    "unsigned long const*": "P", "unsigned int const*": "p",
}


def reg_index(md, reg):
    """w5 / x5 -> 5 (capstone register ids differ for w and x)."""
    n = md.reg_name(reg)
    return n[1:] if n[0] in "wx" else n


def scan():
    L = lib()
    md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
    md.detail = True
    dyn = L.elf.get_section_by_name(".dynsym")
    syms = sorted({(s.name, s["st_value"], s["st_size"]) for s in dyn.iter_symbols()
                   if s.name.startswith(PREFIX) and s["st_value"] and s["st_size"]
                   and re.match(PREFIX + r"\d+Set", s.name)})
    dem = subprocess.run(["c++filt"], input="\n".join(s[0] for s in syms), capture_output=True,
                         text=True).stdout.split("\n")
    out = []
    for (mangled, va, size), d in zip(syms, dem):
        m = re.match(r"Aska::Yayoi::GameRPC::GameProtocoledData::Set(\w+)\((.*)\)$", d)
        if not m:
            continue
        name, params = m.group(1), [p.strip() for p in m.group(2).split(",") if p.strip()]
        regs, fids = {}, []
        for ins in md.disasm(L.read(va, size), va):
            ops = ins.operands
            if ins.mnemonic in ("mov", "movz") and len(ops) == 2 and ops[0].type == ARM64_OP_REG \
                    and ops[1].type == ARM64_OP_IMM:
                v = ops[1].imm << (ops[1].shift.value or 0)
                regs[reg_index(md, ops[0].reg)] = v & 0xFFFFFFFF
            elif ins.mnemonic == "movk" and ops[0].type == ARM64_OP_REG:
                r, sh = reg_index(md, ops[0].reg), ops[1].shift.value or 0
                regs[r] = (regs.get(r, 0) & ~(0xFFFF << sh) | (ops[1].imm << sh)) & 0xFFFFFFFF
            elif ins.mnemonic == "str" and len(ops) == 2 and ops[1].type == ARM64_OP_MEM \
                    and ops[1].mem.disp == 0x30 and reg_index(md, ops[0].reg) in regs:
                fids.append(regs[reg_index(md, ops[0].reg)])
        if len(set(fids)) != 1:
            raise SystemExit(f"{name}: expected one FunctionID store, found {fids}")
        request = bool(params) and params[0] == "Aska::Yayoi::GameRPC::RequestHeader const&"
        ninja = bool(params) and params[-1] == "Aska::Cryption::Ninja*"
        args = params[1 if request else 0:len(params) - (1 if ninja else 0)]
        out.append(dict(name=name, mangled=mangled, fid=fids[0], request=request, encrypted=ninja,
                        params=args, addr=va))
    return out


def reply_of(name, by_name):
    r = REPLY_PAIRS.get(name, name + "Res")
    return by_name.get(r)


CHECK = False  # --check: compare with the file instead of writing it
REPO = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
DEFAULT_INC = os.path.join(REPO, "port", "src", "native", "api", "gen", "wire_table.inc")
DEFAULT_DECODER = os.path.join(REPO, "server", "net", "gen", "wire_decode.inc")


def emit(path, text, what):
    """Writes `text` to `path`, or with --check compares it (False: stale)."""
    if CHECK:
        def body(t):  # (the stamp line names the lib's path: not compared, only its sha256 is)
            return None if t is None else [ln if not ln.startswith("// libSOA.so: ") else ln.split(" (", 1)[-1]
                                           for ln in t.split("\n")]
        have = open(path).read() if os.path.exists(path) else None
        if body(have) != body(text):
            print(f"stale: {path} differs from the generator's output (run tools/api_wire.py without --check)")
            return False
        print(f"same: {path}")
        return True
    os.makedirs(os.path.dirname(os.path.abspath(path)), exist_ok=True)
    open(path, "w").write(text)
    print(f"wrote {path}: {what}")
    return True


def gen_inc(ents, path):
    lines = ["// Generated by tools/api_wire.py --gen-inc: every request serializer",
             "// " + genlib.stamp(),
             "// GameProtocoledData::Set<Name>(RequestHeader const&, args..., [Ninja*]) of the lib.",
             "// {name, mangled symbol, FunctionID, encrypted (takes a Ninja*), argument type codes}",
             "// Codes: B u8, b s8, I u32, i int, f float, D DeviceType, Q u64, S s8 const*,",
             "//        P u64 const*, p u32 const*.", ""]
    for e in ents:
        if not e["request"]:
            continue
        codes = "".join(TYPES[p] for p in e["params"])
        lines.append(f'{{"{e["name"]}", "{e["mangled"]}", 0x{e["fid"]:08x}u, {str(e["encrypted"]).lower()}, "{codes}"}},')
    return emit(path, "\n".join(lines) + "\n", f"{sum(e['request'] for e in ents)} requests")


def fmt_layout(tokens):
    """Selftest layout tokens -> readable request body description."""
    out = []
    for t in tokens:
        m = re.match(r"(\w+)(?:\[(\d+)\])?$", t)
        kind, n = m.group(1), m.group(2)
        out.append({
            "hdr": "RequestHeader(16)", "u8": "u8", "s8": "s8", "u32": "u32", "s32": "s32",
            "f32": "f32", "dev": "u32 DeviceType", "u64": "u64",
            "str": f"char[{n}]", "blob": "u32 len + len bytes",
            "vec64": "u32 n + n×u64", "vec32": "u32 n + n×u32",
        }[kind])
    return " · ".join(out)


def doc(layouts_path, api_md, ents):
    by_name = {e["name"]: e for e in ents}
    by_fid = {e["fid"]: e for e in ents if e["request"]}
    layouts = {}
    for line in open(layouts_path):
        if line.startswith("#") or not line.strip():
            continue
        f = line.split()
        toks = [t for t in f[3:] if t != "range-checked"]
        layouts[f[0]] = (int(f[1], 16), int(f[2]), toks, "range-checked" in f[3:])  # name fid len tokens
    text = open(api_md).read()
    parts = re.split(r"(?m)^(?=### )", text)
    done, missing = 0, []
    for i, p in enumerate(parts):
        m = re.match(r"### (\S+)\n", p)
        fm = re.search(r"- \*\*FunctionID\*\* `([0-9a-f]{8})`", p)
        if not m or "- **FunctionID**" not in p:
            continue
        api = m.group(1)
        p = re.sub(r"(?m)^- \*\*Wire\*\*.*\n", "", p)
        if fm:
            fid = int(fm.group(1), 16)
            e = by_fid.get(fid)
        else:  # the method sends nothing; show the serializer of the same name if there is one
            e = by_name.get(api) if api in by_name and by_name[api]["request"] else None
            fid = e["fid"] if e else 0
        if e is None and not fm:
            wire = "- **Wire**: nothing is sent (no request serializer)\n"
        elif e is None:
            wire = "- **Wire**: no `GameProtocoledData` serializer with this FunctionID (not a game-RPC request)\n"
            missing.append(api)
        else:
            lay = layouts.get(e["name"])
            rep = reply_of(e["name"], by_name)
            rep_s = f"reply `{rep['name']}` fid `{rep['fid']:08x}`" if rep else "reply: none found"
            enc = "encrypted" if e["encrypted"] else "**sent in the clear**"
            if lay:
                size = {"hdr": 16, "u8": 1, "s8": 1, "u32": 4, "s32": 4, "f32": 4, "dev": 4, "u64": 8,
                        "blob": 4, "vec64": 4, "vec32": 4}
                fixed = sum(int(re.match(r"str\[(\d+)\]", t).group(1)) if t.startswith("str") else size[t]
                            for t in lay[2])
                var = any(t in ("blob", "vec64", "vec32") for t in lay[2])
                body = f"{fmt_layout(lay[2])} = {fixed} bytes" + (" + payload" if var else "")
                if lay[3]:
                    body += " (the serializer range-checks an argument, see Wire format)"
            else:
                body = "layout not measured"
            ren = "" if e["name"] == api else f"`Set{e['name']}`, "
            unused = "" if fm else " (serializer only: the method sends nothing)"
            wire = f"- **Wire**{unused}: {ren}request fid `{fid:08x}`, {enc}: {body}; {rep_s}\n"
        # after the Method line (or the FunctionID line)
        anchor = re.search(r"(?m)^- \*\*Method\*\*.*\n", p) or re.search(r"(?m)^- \*\*FunctionID\*\*.*\n", p)
        p = p[:anchor.end()] + wire + p[anchor.end():]
        parts[i] = p
        done += 1
    open(api_md, "w").write("".join(parts))
    print(f"{done} entries updated; no serializer: {', '.join(missing) or '-'}")


# The local server's method name where it differs from the serializer's (the server keys its
# dispatch on FakeApiCaller's method names: port/src/native/api/gen/fakeapi_tables.inc).
SERVER_METHOD = {"UpdateName": "UpdatePlayerName"}


def reply_kind(rep):
    """The reply body's shape from the reply serializer's parameters."""
    p = rep["params"]
    if p == ["signed char const*", "unsigned int"]:
        return "blob"      # u32 length + MessagePack
    if p == ["Aska::Yayoi::GameRPC::GameProtocol::FunctionID", "signed char const*", "unsigned int"]:
        return "fidblob"   # u32 FunctionID + u32 length + MessagePack (LoginResult, SimpleLoginResult)
    if p == ["signed char const*"] * 3:
        return "start"     # ResultStart: char[1024] token, char[128] url, char[8]
    if p == []:
        return "empty"     # ResultUpdateSession
    raise SystemExit(f"{rep['name']}: unexpected reply parameters {p}")


def gen_decoder(ents, layouts_path, path):
    by_name = {e["name"]: e for e in ents}
    rows = []
    for line in open(layouts_path):
        if line.startswith("#") or not line.strip():
            continue
        f = line.split()
        name, fid = f[0], int(f[1], 16)
        toks = [t for t in f[3:] if t != "range-checked"]
        e = by_name.get(name)
        if not e or not e["request"] or e["fid"] != fid:
            raise SystemExit(f"{name}: layout fid {fid:08x} doesn't match the lib's serializer")
        if toks[0] != "hdr":
            raise SystemExit(f"{name}: layout doesn't start with the RequestHeader")
        rep = reply_of(name, by_name)
        if not rep:
            raise SystemExit(f"{name}: no reply serializer")
        rows.append((name, SERVER_METHOD.get(name, name), fid, e["encrypted"], " ".join(toks[1:]),
                     rep["name"], rep["fid"], rep["encrypted"], reply_kind(rep)))
    perr = by_name["ProtocolError"]
    lines = ["// Generated by tools/api_wire.py --gen-decoder from docs/api-wire.txt (the request layouts the",
             "// `wire/request-layouts` selftest measured on the client's serializers) and the client lib's",
             "// GameProtocoledData::Set* serializers (FunctionIDs, Ninja* = encrypted, reply parameters).",
             "// Included by server/net/wire.cpp. Do not edit.",
             "// {serializer name, server method, fid, encrypted, layout after the RequestHeader,",
             "//  reply name, reply fid, reply encrypted, reply body kind}",
             "// Layout tokens: u8 s8 u32 s32 f32 u64, dev (u32 DeviceType), str[N] (fixed N bytes),",
             "//   blob (u32 len + bytes), vec64 / vec32 (u32 n + n elements).",
             "// Reply kinds: blob (u32 len + MessagePack), fidblob (u32 fid + u32 len + MessagePack),",
             "//   start (ResultStart: char[1024] token, char[128] url, char[8]), empty.",
             "static const WireApiRow kWireApiRows[] = {"]
    for r in rows:
        lines.append(f'    {{"{r[0]}", "{r[1]}", 0x{r[2]:08x}u, {str(r[3]).lower()}, "{r[4]}", "{r[5]}", 0x{r[6]:08x}u, '
                     f'{str(r[7]).lower()}, ReplyKind::k{r[8].capitalize()}}},')
    lines.append("};")
    lines.append("// Every reply serializer (names for the packet log): {name, fid, encrypted}.")
    lines.append("static const WireReplyRow kWireReplyRows[] = {")
    for e in ents:
        if not e["request"]:
            lines.append(f'    {{"{e["name"]}", 0x{e["fid"]:08x}u, {str(e["encrypted"]).lower()}}},')
    lines.append("};")
    lines.append(f"static constexpr uint32_t kFidProtocolErrorGen = 0x{perr['fid']:08x}u;")
    return emit(path, "\n".join(lines) + "\n", f"{len(rows)} requests, {sum(not e['request'] for e in ents)} replies")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--gen-inc")
    ap.add_argument("--doc", nargs=2, metavar=("LAYOUTS", "API_MD"))
    ap.add_argument("--gen-decoder")
    ap.add_argument("--layouts", default=os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "docs", "api-wire.txt"))
    ap.add_argument("--check", action="store_true", help="compare with the files instead of writing them")
    a = ap.parse_args()
    global CHECK
    CHECK = a.check
    if a.check and not (a.gen_inc or a.gen_decoder):
        a.gen_inc, a.gen_decoder = DEFAULT_INC, DEFAULT_DECODER
    ents = scan()
    ok = True
    if a.list:
        for e in ents:
            k = "req" if e["request"] else "rep"
            print(f"{k} {e['fid']:08x} {'enc' if e['encrypted'] else 'clr'} {e['name']}({', '.join(e['params'])})")
    if a.gen_inc:
        ok &= gen_inc(ents, a.gen_inc)
    if a.doc:
        doc(a.doc[0], a.doc[1], ents)
    if a.gen_decoder:
        ok &= gen_decoder(ents, a.layouts, a.gen_decoder)
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
