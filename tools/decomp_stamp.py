#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Files a resolved Ghidra decompile (tools/decomp.sh / decomp_at.sh) into a subsystem's decompile store.

Usage (called by tools/decomp.sh / decomp_at.sh --into; not usually by hand):
  decomp_stamp.py --into SUBSYSTEM[/TOPIC] --tool-script NAME --command CMD RESOLVED.c

Writes port/decomp/<subsystem>/<topic>.c (topic defaults to the subsystem's name) and upserts one row
per function into port/decomp/<subsystem>/symbols.tsv. The subsystem must exist (tools/subsystem.py
new <subsystem>).

The .c file is data, not code (nothing builds it). It starts with a header naming the lib (file
name, sha256, size), the tool (Ghidra version, script, tools/resolve_decomp.py) and every run that
wrote to it (date, command). Each function carries its own stamp line:

  // ==== <demangled name>
  // vaddr 0x... | ghidra 0x... | size N | symbol <mangled or FUN_<ghidra>> | lib <file> | <date>

A function decompiled again replaces its block (keyed by vaddr); blocks are kept sorted by vaddr,
so two branches that decompile different functions into one topic merge as separate hunks.

symbols.tsv (tab-separated, a header row, sorted by vaddr) has the columns of SYMBOLS_COLUMNS; a
row that exists keeps its status and note (the subsystem's authors set them: decompiled, typed,
native, tested, skip).
"""
import argparse
import datetime
import hashlib
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GHIDRA_BASE = 0x100000
SYMBOLS_COLUMNS = ["vaddr", "ghidra", "size", "symbol", "demangled", "topic", "status", "note"]
NAME_RE = re.compile(r"^[a-z][a-z0-9_]*$")


def lib_path():
    return os.environ.get("SOA_LIB") or os.path.join(REPO, "work", "libSOA-3.7.0.so")


def elf_symbols(path):
    """{vaddr: (name, size)} of the defined function symbols (.dynsym, .symtab)."""
    from elftools.elf.elffile import ELFFile
    out = {}
    with open(path, "rb") as f:
        elf = ELFFile(f)
        for secname in (".dynsym", ".symtab"):
            sec = elf.get_section_by_name(secname)
            if not sec:
                continue
            for s in sec.iter_symbols():
                if s.name and s["st_value"] and s["st_info"]["type"] in ("STT_FUNC", "STT_GNU_IFUNC"):
                    out.setdefault(s["st_value"], (s.name, s["st_size"]))
    return out


def demangle(names):
    names = list(names)
    if not names:
        return {}
    r = subprocess.run(["c++filt"], input="\n".join(names) + "\n", capture_output=True, text=True, check=True)
    return dict(zip(names, r.stdout.splitlines()))


def ghidra_version():
    home = os.environ.get("GHIDRA_HOME", "/snap/ghidra/current/ghidra")
    try:
        with open(os.path.join(home, "Ghidra", "application.properties")) as f:
            for line in f:
                if line.startswith("application.version="):
                    return line.split("=", 1)[1].strip()
    except OSError:
        pass
    return "?"


def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def parse_resolved(text):
    """[(ghidra_addr, title, body_lines)] from decomp.sh / decomp_at.sh output."""
    blocks, cur = [], None
    for line in text.splitlines():
        if line.startswith("// ==== "):
            cur = {"title": line[8:].strip(), "addr": None, "body": []}
            blocks.append(cur)
            m = re.match(r"@([0-9a-fA-F]+)$", cur["title"])  # DecompileAt: "// ==== @00123456"
            if m:
                cur["addr"] = int(m.group(1), 16)
                cur["title"] = None
            continue
        if cur is None:
            continue
        if cur["addr"] is None and not cur["body"]:
            m = re.match(r"^// (\S+) @ ([0-9a-fA-F]+)$", line)  # DecompileMatching: "// <raw> @ <addr>"
            if m:
                cur["addr"] = int(m.group(2), 16)
                continue
        cur["body"].append(line)
    out = []
    for b in blocks:
        if b["addr"] is None:
            continue
        while b["body"] and not b["body"][-1].strip():
            b["body"].pop()
        while b["body"] and not b["body"][0].strip():
            b["body"].pop(0)
        out.append((b["addr"], b["title"], b["body"]))
    return out


STAMP_RE = re.compile(r"^// vaddr (0x[0-9a-f]+) \|")


def read_store(path):
    """(header_lines, {vaddr: block_lines}) of an existing topic file."""
    header, blocks, cur = [], {}, None
    if not os.path.exists(path):
        return header, blocks
    with open(path) as f:
        lines = f.read().splitlines()
    i = 0
    while i < len(lines):
        line = lines[i]
        if line.startswith("// ==== ") and i + 1 < len(lines) and STAMP_RE.match(lines[i + 1]):
            cur = int(STAMP_RE.match(lines[i + 1]).group(1), 16)
            blocks[cur] = [line]
        elif cur is None:
            header.append(line)
        else:
            blocks[cur].append(line)
        i += 1
    for k in blocks:
        while blocks[k] and not blocks[k][-1].strip():
            blocks[k].pop()
    return header, blocks


def read_symbols(path):
    rows = {}
    if os.path.exists(path):
        with open(path) as f:
            for n, line in enumerate(f):
                line = line.rstrip("\n")
                if not line or line.startswith("#") or (n == 0 and line.startswith("vaddr\t")):
                    continue
                cols = line.split("\t") + [""] * len(SYMBOLS_COLUMNS)
                rows[int(cols[0], 16)] = dict(zip(SYMBOLS_COLUMNS, cols))
    return rows


def write_symbols(path, rows):
    with open(path, "w") as f:
        f.write("\t".join(SYMBOLS_COLUMNS) + "\n")
        for va in sorted(rows):
            f.write("\t".join(str(rows[va].get(c, "")) for c in SYMBOLS_COLUMNS) + "\n")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--into", required=True, help="SUBSYSTEM[/TOPIC]")
    ap.add_argument("--tool-script", default="DecompileMatching.java")
    ap.add_argument("--command", default="")
    ap.add_argument("--root", default=REPO, help="the repository (default: this checkout)")
    ap.add_argument("--date", help="override the date (tests)")
    ap.add_argument("resolved")
    a = ap.parse_args()

    sub, _, topic = a.into.partition("/")
    topic = topic or sub
    if not NAME_RE.match(sub) or not re.match(r"^[A-Za-z0-9_][A-Za-z0-9_.-]*$", topic) or ".." in topic:
        sys.exit(f"decomp_stamp: bad --into {a.into!r}: SUBSYSTEM is [a-z][a-z0-9_]*, TOPIC a file name")
    store = os.path.join(a.root, "port", "decomp", sub)
    if not os.path.isdir(store):
        sys.exit(f"decomp_stamp: {os.path.relpath(store, a.root)} doesn't exist: scaffold the subsystem first "
                 f"(tools/subsystem.py new {sub})")

    lib = lib_path()
    libname = os.path.basename(lib)
    date = a.date or datetime.datetime.now(datetime.timezone.utc).strftime("%Y-%m-%d")
    stamp_time = a.date or datetime.datetime.now(datetime.timezone.utc).strftime("%Y-%m-%d %H:%M UTC")
    syms = elf_symbols(lib)
    with open(a.resolved) as f:
        funcs = parse_resolved(f.read())
    if not funcs:
        sys.exit(f"decomp_stamp: no function in {a.resolved} (nothing matched?)")
    mangled = {g - GHIDRA_BASE: syms.get(g - GHIDRA_BASE, (None, 0)) for g, _, _ in funcs}
    dem = demangle(n for n, _ in mangled.values() if n)

    path = os.path.join(store, topic + ".c")
    header, blocks = read_store(path)
    rows = read_symbols(os.path.join(store, "symbols.tsv"))
    for g, title, body in funcs:
        va = g - GHIDRA_BASE
        name, size = mangled[va]
        sym = name or "FUN_%08x" % g
        pretty = (dem.get(name) if name else None) or title or sym
        blocks[va] = [f"// ==== {pretty}",
                      f"// vaddr {va:#x} | ghidra {g:#x} | size {size} | symbol {sym} | lib {libname} | {date}"] + body
        old = rows.get(va, {})
        rows[va] = {"vaddr": f"{va:#x}", "ghidra": f"{g:#x}", "size": str(size), "symbol": sym,
                    "demangled": pretty, "topic": topic,
                    "status": old.get("status") or "decompiled", "note": old.get("note", "")}

    runs = [h for h in header if h.startswith("// run ")]
    runs.append(f"// run      {stamp_time}: {a.command}".rstrip())
    rel = os.path.relpath(path, a.root)
    head = [
        f"// {rel}: Ghidra decompiles for the {sub} subsystem. Data, not code: nothing builds this file.",
        "// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,",
        "// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).",
        f"// lib      {libname}  sha256 {sha256(lib)}  ({os.path.getsize(lib)} bytes)",
        f"// tool     Ghidra {ghidra_version()} analyzeHeadless -noanalysis, tools/ghidra_scripts/{a.tool_script}, tools/resolve_decomp.py",
    ] + runs
    with open(path, "w") as f:
        f.write("\n".join(head) + "\n")
        for va in sorted(blocks):
            f.write("\n" + "\n".join(blocks[va]) + "\n")
    write_symbols(os.path.join(store, "symbols.tsv"), rows)
    # types.json lists each class's methods from symbols.tsv: keep it current (tools/subsystem.py check).
    try:
        import json
        import subsystem
        doc = subsystem.export_structs(a.root, sub)
        with open(os.path.join(store, "types.json"), "w") as f:
            f.write(json.dumps(doc, indent=1) + "\n")
    except Exception as e:  # noqa: BLE001 (clang missing, a header that doesn't compile: check reports it)
        print(f"decomp_stamp: types.json not regenerated ({e}); run tools/subsystem.py export-types {sub}", file=sys.stderr)
    print(f"{rel}: {len(funcs)} function(s) ({len(blocks)} in the file); "
          f"{os.path.relpath(os.path.join(store, 'symbols.tsv'), a.root)}: {len(rows)} row(s)")


if __name__ == "__main__":
    main()
