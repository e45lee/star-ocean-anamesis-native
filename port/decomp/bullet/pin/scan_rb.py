"""Scan the 3.7.0 asset set for Aska rigid-body chunks ('DyPr', stored b'rPyD') and the
constraint chunk names. ADLD -> SLZ (zstd frames) -> AFF."""
import os, sys, concurrent.futures as cf
REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../.."))
sys.path.insert(0, REPO)
from soa_save import adld, slz
from soa_save.download_tree import DEFAULT, DownloadTree
# the 3.7.0 download (its zip, read in place) and the APK's extracted builtin_data
ROOTS = [DEFAULT, REPO + "/work/extracted/com.square_enix.android_googleplay.StarOceanj/assets/builtin_data"]
_TREES = {}
def tree(root):
    if (os.getpid(), root) not in _TREES: _TREES[(os.getpid(), root)] = DownloadTree.open(root)
    return _TREES[(os.getpid(), root)]
unslz = slz.decode  # SLZ: chunks of codec 0 (stored), 5 (raw deflate), 7 (zstd)
def scan(job):
    root, rel = job
    p = rel
    try:
        raw = tree(root).read(rel)
        d = adld.decode(raw, rel) if raw.startswith(b"ADLD") else raw
        d = unslz(d)
    except Exception as e:
        return (rel, "ERR " + str(e)[:60], 0)
    if p.endswith((".asf", ".acf", ".aaf")) and not d.startswith((b" FSA", b" FCA", b" FAA")): return (rel, "ERR not AFF " + repr(d[:4]), 0)
    return (rel, d.count(b"rPyD"), d.count(b"RIGIDBODY"))
if __name__ != "__main__": raise ImportError("run as a script")
jobs = []
for r in ROOTS:
    if not os.path.exists(r): continue
    for f in tree(r).files():
        if f.endswith((".asf", ".acf", ".aaf", ".apk", ".csf", ".fpk", ".tpk", ".bin")): jobs.append((r, f))
print(len(jobs), "files", file=sys.stderr)
hits = errs = 0
with cf.ProcessPoolExecutor(12) as ex:
    for rel, a, b in ex.map(scan, jobs, chunksize=16):
        if isinstance(a, str): errs += 1; print("ERR", rel, a) if errs <= 20 else None; continue
        if a or b: hits += 1; print("HIT", rel, a, b)
print(f"files {len(jobs)} hits {hits} errors {errs}")
