"""Shared by the code / table generators (tools/gen_*.py, api_wire.py --gen-inc): which libSOA.so they
read, the stamp they write into their output, and lib-agnostic names for unnamed functions.

Import it BEFORE a2c.py / elfinfo.py: it makes the 3.7.0 client (work/libSOA-3.7.0.so, the lib the
port runs since the rebase, docs/history/PLAN-rebase-370.md) the default for SOA_LIB, which elfinfo.py reads
at import time. SOA_LIB=PATH still selects another lib (e.g. the viewer's, to reproduce an old file).

Every generated file names the lib it was generated from (`stamp()`: repo-relative path, version,
sha256), so tools/rebase_inventory.py and a reader can tell which build its addresses belong to.

Unnamed functions (statics, std::function lambdas' operator()s) are named the way tools/verdiff.py
pairs them across builds: `anon:<previous exported symbol>#k` (the k-th unnamed function after it)
and `lambda:<enclosing function>#k.slot`. `local(name)` gives (address, size) in the current lib,
`local_name(addr)` the name of an address. Use these instead of `0xaddr:size` literals.
"""
import hashlib
import os
from functools import lru_cache

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
LIB_370 = os.path.join(REPO, "work", "libSOA-3.7.0.so")
os.environ.setdefault("SOA_LIB", LIB_370)

# sha256 -> version of the builds we know
KNOWN = {
    "698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e": "3.7.0",
    "05cbe39abdb265cfe8d13fde77c907e27f16bf96439a0a92e657f16897c86dbb": "3.8.0",  # the viewer's (380-ok)
}


def lib_path():
    return os.environ["SOA_LIB"]


@lru_cache(None)
def sha256(path=None):
    h = hashlib.sha256()
    with open(path or lib_path(), "rb") as f:
        for b in iter(lambda: f.read(1 << 20), b""):
            h.update(b)
    return h.hexdigest()


def version(path=None):
    return KNOWN.get(sha256(path), "unknown build")


def stamp(path=None):
    """'libSOA.so: work/libSOA-3.7.0.so (3.7.0, sha256 698d...)': one line for a generated header."""
    p = os.path.abspath(path or lib_path())
    r = os.path.relpath(p, REPO)       # (work/ may be a symlink: no realpath)
    if r.startswith(".."):
        r = p
    return "libSOA.so: %s (%s, sha256 %s)" % (r, version(path), sha256(path))


@lru_cache(None)
def _image(path):
    import verdiff  # noqa: E402 (slow: ~5 s per lib)
    img = verdiff.Image(path)
    names = verdiff.anon_names(img)
    return img, names, {n: a for a, n in names.items()}


def local(name, path=None):
    """(address, size) of an unnamed function `anon:...#k` / `lambda:...#k.slot` in the lib."""
    img, _, by_name = _image(path or lib_path())
    a = by_name.get(name)
    if a is None:
        raise KeyError("%s: no such unnamed function in %s" % (name, path or lib_path()))
    return a, img.extent(a)


def local_name(addr, path=None):
    img, names, _ = _image(path or lib_path())
    return names.get(addr)


def resolve_spec(spec, path=None):
    """'anon:...' / 'lambda:...' -> (addr, size); '0xaddr:size' stays accepted (lib-specific)."""
    if spec.startswith(("anon:", "lambda:")):
        return local(spec, path)
    a, _, s = spec.partition(":")
    return int(a, 16), int(s, 16)
