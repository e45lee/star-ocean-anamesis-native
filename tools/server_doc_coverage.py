#!/usr/bin/env python3
"""The local server's doc-comment coverage (server/PLAN-readability.md 2.5 and R19), for
tools/check_server_docs.sh:

    tools/server_doc_coverage.py [--server BIN]     exit 1 when something lacks its doc comment

  1. handlers: every registered API's handler has the 2.5 block above it: `API:` and `Rules:` lines
     and at least one (a)-(d) label, or the explicit `Rules: none (transport)`;
  2. hooks: every module hook (`soa-server --list-hooks`) has a doc comment above the function it
     registers (its definition or a declaration in the module's folder; for a lambda, the function
     the lambda calls);
  3. public functions: every function declared in server/include/soaserver/ has a doc comment: the
     comment directly above it, or above the contiguous group of declarations it is part of, or a
     trailing one on its line. Constructors, destructors, operators, `= default` and macro bodies are
     exempt (the class's comment covers them).
Each finding is printed as `FILE:LINE: what`.
"""
import argparse
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "tools"))
import server_index as si  # noqa: E402

LABEL_RE = re.compile(r"\(([abcd])\)|\(([abcd]):|[;,] ([abcd]):")  # as tools/server_evidence.py
HEADERS = os.path.join(REPO, "server/include/soaserver")


def comment_above(lines, line):
    """The `//` block directly above 1-based `line` (its text; "" when there is none)."""
    out, i = [], line - 2
    while i >= 0 and lines[i].lstrip().startswith("//"):
        out.append(lines[i])
        i -= 1
    return "\n".join(reversed(out))


def handlers():
    bad, seen = [], set()
    for method, (f, line, fn, _body) in sorted(si.module_handlers().items()):
        if (f, line) in seen:
            continue
        seen.add((f, line))
        b = comment_above(si.read(os.path.join(REPO, f)), line)
        if "API:" not in b or "Rules:" not in b:
            bad.append("%s:%d: %s (%s): no 2.5 block (API: / Rules:)" % (f, line, fn, method))
        elif not LABEL_RE.search(b) and "Rules: none (transport)" not in b:
            bad.append("%s:%d: %s (%s): the 2.5 block has no (a)-(d) label and isn't `Rules: none (transport)`" % (f, line, fn, method))
    return bad, len(seen)


def hook_function(reg):
    """The function a registration line hands over: add_x(fn), add_x(key, fn), or a lambda that calls one."""
    m = re.search(r"add_\w+\((.*)\);", reg)
    args = m.group(1) if m else ""
    lam = re.search(r"\]\s*\([^)]*\)\s*\{\s*(?:return\s+)?([A-Za-z_][\w:]*)\(", args)
    if lam:
        return lam.group(1)
    ids = re.findall(r"[A-Za-z_][\w:]*", args.split(",")[-1])
    return ids[-1] if ids else None


def hooks(server):
    r = subprocess.run([server, "--list-hooks"], capture_output=True, text=True)
    if r.returncode != 0:
        return ["%s --list-hooks failed (exit %d)" % (server, r.returncode)], 0
    bad, n = [], 0
    for ln in r.stdout.splitlines():
        kind, module, loc = ln.split("\t")[:3]
        f, line = loc.rsplit(":", 1)
        n += 1
        src = si.read(os.path.join(REPO, f))
        reg = src[int(line) - 1] if int(line) <= len(src) else ""
        if "add_" not in reg:
            bad.append("%s: %s hook of %s: no registration on that line (soa-server older than the sources? rebuild)" % (loc, kind, module))
            continue
        fn = hook_function(reg)
        if not fn:
            bad.append("%s: %s hook of %s: can't tell which function it registers" % (loc, kind, module))
            continue
        name = fn.split("::")[-1]
        decl = re.compile(r"^\S[^;{}()]*\b%s\(" % re.escape(name))
        folder = os.path.join(REPO, os.path.dirname(f))
        found = documented = False
        for g in sorted(os.listdir(folder)):
            if not g.endswith((".cpp", ".h")):
                continue
            lines = si.read(os.path.join(folder, g))
            for i, x in enumerate(lines, 1):
                if decl.match(x) and not x.startswith("//"):
                    found = True
                    documented |= bool(comment_above(lines, i).strip())
        if not documented:
            bad.append("%s: %s hook of %s: %s %s" % (loc, kind, module, fn, "has no doc comment" if found else
                                                    "not found in the module's folder"))
    return bad, n


CONTAINER = re.compile(r"^\s*(namespace\b|(template\s*<.*>\s*)?(struct|class|union|enum)\b|extern \"C\")")
CLASS_NAME = re.compile(r"^\s*(?:template\s*<.*>\s*)?(?:struct|class|union)\s+(\w+)")
DECL = re.compile(r"^\s*(?:template\s*<[^>]*>\s*)?(?:(?:inline|static|constexpr|virtual|explicit|friend|extern|\[\[nodiscard\]\])\s+)*"
                  r"(?:[\w:<>,]+(?:\s*[*&]+)?\s+)*?[*&]?~?(?:operator\S+|[A-Za-z_]\w*)\s*\(")
NOT_DECL = re.compile(r"^\s*(return|if|for|while|switch|else|case|using|typedef|#|//|static_assert|[A-Z_]+\()")


def header_functions(path):
    """(line, text) of the undocumented function declarations of one header (namespace and class scope)."""
    lines = open(path, encoding="utf-8").read().split("\n")
    stack, names = [], []  # per open brace: "c" a namespace / class body, "b" anything else; the class name
    pending, pending_name = False, ""
    bad = []
    for i, ln in enumerate(lines):
        code = re.sub(r'"(\\.|[^"\\])*"', '""', ln)
        code = re.sub(r"//.*", "", code)
        cls = [n for n in names if n]
        ctor = bool(cls) and re.match(r"^\s*(?:constexpr\s+|explicit\s+|virtual\s+)*~?%s\s*\(" % re.escape(cls[-1]), code)
        macro = code.rstrip().endswith("\\") or (i > 0 and lines[i - 1].rstrip().endswith("\\"))
        exempt = ctor or "operator" in code or "= default" in code or macro or "(*" in code
        if (all(s == "c" for s in stack) and not exempt and DECL.match(code) and not NOT_DECL.match(code)
                and not CONTAINER.match(code)):
            ok = "//" in ln[len(code.rstrip()):]
            j = i - 1
            while not ok and j >= 0:
                t = lines[j].strip()
                if t.startswith("//") or t.endswith("*/"):
                    ok = True
                elif (not t or (t.endswith("{") and CONTAINER.match(lines[j])) or t.startswith("#")
                      or t in ("public:", "private:", "protected:")):
                    break
                j -= 1
            if not ok:
                bad.append((i + 1, ln.strip()))
        for ch in code:
            if ch == "{":
                is_c = bool(CONTAINER.match(code) or pending) and all(s == "c" for s in stack)
                stack.append("c" if is_c else "b")
                m = CLASS_NAME.match(code)
                names.append((m.group(1) if m else pending_name) if is_c else "")
                pending, pending_name = False, ""
            elif ch == "}" and stack:
                stack.pop()
                names.pop()
        if CONTAINER.match(code) and "{" not in code and not code.rstrip().endswith(";"):
            m = CLASS_NAME.match(code)
            pending, pending_name = True, (m.group(1) if m else "")
    return bad


def public_functions():
    bad = []
    for f in sorted(os.listdir(HEADERS)):
        if f.endswith(".h"):
            for line, text in header_functions(os.path.join(HEADERS, f)):
                bad.append("%s:%d: no doc comment: %s" % (os.path.relpath(os.path.join(HEADERS, f), REPO), line, text[:100]))
    return bad


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--server", default=os.path.join(REPO, "build/server/soa-server"))
    a = ap.parse_args()
    found = 0
    h, n = handlers()
    print("handlers: %d of %d have the 2.5 block with a label" % (n - len(h), n))
    if os.access(a.server, os.X_OK):
        k, m = hooks(a.server)
        print("hooks: %d of %d have a doc comment" % (m - len(k), m))
    else:
        k = []
        print("hooks: no %s: not checked (build soa-server, or pass --server)" % a.server)
    p = public_functions()
    print("include/soaserver functions: %s" % ("%d without a doc comment" % len(p) if p else "every one has a doc comment"))
    for x in h + k + p:
        print("  " + x)
        found += 1
    return 1 if found else 0


if __name__ == "__main__":
    sys.exit(main())
