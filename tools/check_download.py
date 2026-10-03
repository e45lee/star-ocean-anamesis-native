#!/usr/bin/env python3
"""Validate a downloaded 3.7.0 asset folder against its own manifests and version.bin.

  .venv/bin/python tools/check_download.py DIR [--manifest {all,Bulk,Individual,ep1,ep2,ep3}]
        [--version-bin FILE] [--jobs N] [--quick] [--json OUT] [--max-list N]

DIR is either the unpacked CDN download (work/download-3.7.0) or a client's storage directory
(a phone's data/files/download, e.g. work/phone-3.7.0/data/files/download): both have the same
layout (docs/online-server.md "Asset delivery", server/README.md "The CDN"):
  version.bin                                   MessagePack {revision, version, appliversion,
                                                assets: name -> {md5, size, time, parentHash, flags,
                                                encType, ep_data, meta}}
  manifest/<fmt>/<q>/version_latest_<M>.bin     {version, toolversion, assets: bundle ->
                                                {member -> {size, md5, p, e, ep_data, meta}, md5, size, meta}}
  manifest/<fmt>/<q>/version_latest_<M>.version "version:<id>\\r\\ntotalSize:<n>\\r\\n"
  manifest/<fmt>/<q>/version.version            version.bin's id
  <member name>                                 each member as the client writes it (UnpackNotify::Handler):
                                                "ADLD", u32 e, 8 zero bytes, payload; the whole file is
                                                the payload when e = 0.

The rules checked (server/src/cdn/tree.cpp Tree::build, soa_save/adld.py; checked against the 3.7.0 data):
  * a member's "size" and "md5" (40 hex: SHA-1) are of its PLAINTEXT: the payload (file minus the
    16-byte ADLD header when e != 0) decrypted by ADLD (e & 1: XOR with "%x" of CHash32(name), so
    size = file - 16; e & 2: AES-CBC, the master only, plaintext inside a "DCNE" wrapper);
  * the ADLD header's flags equal the member's "e"; manifests that list the same member agree;
  * version.bin, per asset (flags 0): size = the stored file's size, md5 = the plaintext's SHA-1,
    encType = e, parentHash = CHash32 of a bundle that lists it (the original CDN: its Individual
    bundle; a phone records the bundle it actually fetched, e.g. Bulk's for the master);
    flags 1 entries are bundles: md5 = that bundle's md5 in a manifest, parentHash = CHash32(name);
  * each .version: the id equals the manifest's "version", totalSize = the sum of its members' sizes;
    Bulk and Individual carry version.bin's id; version.version holds it;
  * a member sits in one bundle per manifest (else "duplicate"); a bundle's "p" is its name minus .bin;
  * every file in DIR is a listed member or version.bin asset (else "extra"; manifest/ and
    version.bin themselves are skipped);
  * DIR/version.bin against the canonical data/version-3.7.0.bin: byte-identical when it claims the
    canonical revision (1471); a note when it is our rebuilt revision (1472: a phone, a soa-server
    CDN), which lists the served master and the stand-ins.

Problems (exit 1): missing, size, hash, enc, conflict, duplicate, bundle, parentHash, version-file,
version-bin, extra. Warnings (reported, exit stays 0): "unbundled" (a version.bin asset that no
manifest lists, e.g. Sound/TS_C121_Common_SE.spk in the 3.7.0 original) and "unindexed" (a member
version.bin doesn't list). --manifest restricts the member and duplicate checks to one manifest
(extras are still files that nothing lists); version.bin's entries are checked only with "all".

--quick checks existence, sizes and ADLD headers only (no hashing; the AES master's plaintext size
comes from decrypting its first block). The full check reads and decrypts every byte (about 4 GB),
in --jobs processes (default: the CPU count). --json OUT writes every finding as JSON.
"""
import argparse
import concurrent.futures as cf
import glob
import hashlib
import json
import os
import struct
import sys
import time
from collections import defaultdict

import msgpack
import numpy as np

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)
from soa_save.adld import IV, _digits16, chash32  # noqa: E402

CANONICAL = os.path.join(ROOT, "data", "version-3.7.0.bin")
MANIFESTS = ["Bulk", "Individual", "ep1", "ep2", "ep3"]
SHARED_ID = ("Bulk", "Individual")  # (b) these carry version.bin's id
ADLD_HEADER = 16
CHUNK = 1 << 22
PROBLEM_KINDS = ["missing", "size", "hash", "enc", "conflict", "duplicate", "bundle", "parentHash", "version-file", "version-bin", "extra"]
WARNING_KINDS = ["unbundled", "unindexed"]


def load_msgpack(path):
    with open(path, "rb") as f:
        return msgpack.unpackb(f.read(), raw=False, strict_map_key=False)


# ---- one stored file -------------------------------------------------------------------------------
def _xor_key(name):
    return np.frombuffer(b"%x" % chash32(name.encode()), np.uint8)


def _aes(name):
    from Crypto.Cipher import AES

    return AES.new(_digits16("%032u" % chash32(name.encode())), AES.MODE_CBC, IV)


def examine(root, name, enc, quick):
    """The stored file `name` read as a member with ADLD flags `enc`: {size, flags, plain_size, sha1}
    (flags = the ADLD header's, None without one; plain_size / sha1 None when unknown)."""
    path = os.path.join(root, name)
    try:
        size = os.path.getsize(path)
        with open(path, "rb") as f:
            head = f.read(ADLD_HEADER)
            flags = struct.unpack_from("<I", head, 4)[0] if len(head) == ADLD_HEADER and head[:4] == b"ADLD" else None
            out = {"size": size, "flags": flags, "plain_size": None, "sha1": None}
            if enc == 0:
                out["plain_size"] = size
                if not quick:
                    f.seek(0)
                    h = hashlib.sha1()
                    for block in iter(lambda: f.read(CHUNK), b""):
                        h.update(block)
                    out["sha1"] = h.hexdigest()
                return out
            if size < ADLD_HEADER:
                return out
            body_len = size - ADLD_HEADER
            if flags is not None and flags & 1:
                out["plain_size"] = body_len
                if not quick:
                    key = _xor_key(name)
                    step = len(key) * (CHUNK // len(key))  # every chunk starts at key offset 0
                    keyrep = np.resize(key, min(step, body_len))  # sized to the file: most are small
                    h = hashlib.sha1()
                    for block in iter(lambda: f.read(step), b""):
                        a = np.frombuffer(block, np.uint8)
                        h.update((a ^ keyrep[: len(a)]).tobytes())
                    out["sha1"] = h.hexdigest()
            elif flags is not None and flags & 2:
                body = f.read() if not quick else f.read(16)
                body = body[: len(body) // 16 * 16]
                plain = _aes(name).decrypt(body)
                if plain[:4] == b"DCNE" and struct.unpack_from("<I", plain, 4)[0] == 1:
                    end = struct.unpack_from("<I", plain, 8)[0]
                    out["plain_size"] = end - 16
                    plain = plain[16:end]
                else:
                    out["plain_size"] = body_len // 16 * 16
                if not quick:
                    out["sha1"] = hashlib.sha1(plain).hexdigest()
            return out
    except OSError as e:
        return {"error": str(e)}


def examine_batch(root, items, quick):
    return {name: examine(root, name, enc, quick) for name, enc in items}


# ---- the check -------------------------------------------------------------------------------------
class Report:
    def __init__(self):
        self.problems = []
        self.warnings = []
        self.notes = []

    def problem(self, kind, name, detail, manifest=None):
        self.problems.append({"kind": kind, "manifest": manifest, "name": name, "detail": detail})

    def warning(self, kind, name, detail, manifest=None):
        self.warnings.append({"kind": kind, "manifest": manifest, "name": name, "detail": detail})


def find_manifests(root, which):
    """{label: (bin path, .version path)}; the label is the manifest name (with its format dir when
    DIR holds more than one)."""
    found = sorted(glob.glob(os.path.join(root, "manifest", "*", "*", "version_latest_*.bin")))
    dirs = sorted({os.path.dirname(p) for p in found})
    out = {}
    for p in found:
        name = os.path.basename(p)[len("version_latest_") : -len(".bin")]
        if which != "all" and name != which:
            continue
        label = name if len(dirs) == 1 else os.path.relpath(os.path.dirname(p), os.path.join(root, "manifest")) + "/" + name
        out[label] = (p, p[:-4] + ".version")
    return out, dirs


def parse_version_file(path):
    with open(path, "rb") as f:
        text = f.read().decode("ascii", "replace")
    fields = {}
    for line in text.split("\r\n"):
        if ":" in line:
            k, v = line.split(":", 1)
            fields[k] = v
    return fields


def check(root, which="all", jobs=None, quick=False, version_bin=None, progress=None):
    t0 = time.time()
    rep = Report()
    root = os.path.abspath(root)
    own_vb = os.path.join(root, "version.bin")
    vb_path = version_bin or (own_vb if os.path.exists(own_vb) else CANONICAL)
    vb = load_msgpack(vb_path)
    assets = vb.get("assets", {})
    vb_id = vb.get("version")
    info = {"dir": root, "mode": "quick" if quick else "full", "manifest": which, "version_bin": vb_path,
            "revision": vb.get("revision"), "version": vb_id, "assets": len(assets)}

    # DIR's own version.bin against the canonical one.
    if os.path.exists(own_vb) and os.path.exists(CANONICAL):
        canon = load_msgpack(CANONICAL)
        own = load_msgpack(own_vb) if vb_path != own_vb else vb
        if own.get("revision") == canon.get("revision"):
            with open(own_vb, "rb") as a, open(CANONICAL, "rb") as b:
                if a.read() != b.read():
                    rep.problem("version-bin", "version.bin", f"claims the canonical revision {canon.get('revision')} but differs from data/version-3.7.0.bin")
                else:
                    rep.notes.append(f"version.bin is the canonical 3.7.0 index (revision {canon.get('revision')})")
        else:
            oa, ca = own.get("assets", {}), canon.get("assets", {})
            added = [k for k in oa if k not in ca]
            dropped = [k for k in ca if k not in oa]
            fields = defaultdict(list)
            for k in sorted(oa.keys() & ca.keys()):
                for f in set(oa[k]) | set(ca[k]):
                    if oa[k].get(f) != ca[k].get(f):
                        fields[f].append(k)
            kind = lambda names, d: f"{sum(1 for k in names if d[k].get('flags') == 1)} bundle entries, " + (  # noqa: E731
                ", ".join(k for k in names if d[k].get("flags") != 1) or "no assets")
            rep.notes.append(f"version.bin is revision {own.get('revision')}, not the canonical {canon.get('revision')}: a rebuilt index "
                             f"(a phone's own record, or a soa-server CDN's); added: {kind(added, oa)}; dropped: {kind(dropped, ca)}; "
                             "fields changed: " + (", ".join(f"{f} {len(n)}" + (f" ({', '.join(n)})" if len(n) <= 3 else "") for f, n in sorted(fields.items())) or "none"))
    elif not os.path.exists(own_vb):
        rep.notes.append(f"DIR has no version.bin; using {vb_path}")

    manifests, fmt_dirs = find_manifests(root, which)
    if not manifests:
        rep.problem("version-file", "manifest/", f"no manifest version_latest_{'*' if which == 'all' else which}.bin")
    all_manifests = which == "all"

    # Every manifest's members.
    loaded = {}
    member_info = defaultdict(dict)  # name -> {label: member dict}
    member_bundles = defaultdict(lambda: defaultdict(list))  # name -> label -> [bundle]
    bundle_md5 = defaultdict(dict)  # bundle -> {label: md5}
    summary = {}
    for label, (bin_path, ver_path) in manifests.items():
        m = load_msgpack(bin_path)
        loaded[label] = m
        total = 0
        nmembers = 0
        for bundle, bb in m.get("assets", {}).items():
            bundle_md5[bundle][label] = bb.get("md5")
            for name, mem in bb.items():
                if not isinstance(mem, dict):
                    continue
                nmembers += 1
                total += mem.get("size", 0)
                member_bundles[name][label].append(bundle)
                prev = member_info[name].get(label)
                if prev is not None and (prev.get("md5"), prev.get("size"), prev.get("e")) != (mem.get("md5"), mem.get("size"), mem.get("e")):
                    rep.problem("conflict", name, f"two bundles of {label} disagree", label)
                member_info[name][label] = mem
                if bundle.endswith(".bin") and mem.get("p") != bundle[:-4]:
                    rep.problem("bundle", name, f"p = {mem.get('p')!r} in bundle {bundle}", label)
        summary[label] = {"bundles": len(m.get("assets", {})), "members": nmembers, "bytes": total, "version": m.get("version")}
        # .version
        if not os.path.exists(ver_path):
            rep.problem("version-file", os.path.relpath(ver_path, root), "missing", label)
        else:
            vf = parse_version_file(ver_path)
            if vf.get("version") != m.get("version"):
                rep.problem("version-file", os.path.relpath(ver_path, root), f"version {vf.get('version')} != the manifest's {m.get('version')}", label)
            if vf.get("totalSize") != str(total):
                rep.problem("version-file", os.path.relpath(ver_path, root), f"totalSize {vf.get('totalSize')} != the members' sizes {total}", label)
            summary[label]["totalSize"] = vf.get("totalSize")
        if label.split("/")[-1] in SHARED_ID and m.get("version") != vb_id:
            rep.problem("version-file", os.path.relpath(bin_path, root), f"version {m.get('version')} != version.bin's {vb_id}", label)
    for d in fmt_dirs:
        vv = os.path.join(d, "version.version")
        if os.path.exists(vv) and all_manifests:
            with open(vv, "rb") as f:
                content = f.read().decode("ascii", "replace").strip()
            if content != vb_id:
                rep.problem("version-file", os.path.relpath(vv, root), f"{content!r} != version.bin's id {vb_id}")

    # Duplicates (a member in more than one bundle of one manifest) and cross-manifest conflicts.
    for name, by_label in member_bundles.items():
        for label, bundles in by_label.items():
            if len(bundles) > 1:
                rep.problem("duplicate", name, f"in {len(bundles)} bundles: {', '.join(bundles)}", label)
        infos = member_info[name]
        keys = {(i.get("md5"), i.get("size"), i.get("e")) for i in infos.values()}
        if len(keys) > 1:
            rep.problem("conflict", name, "manifests disagree: " + "; ".join(f"{l}: size {i.get('size')} e {i.get('e')} md5 {i.get('md5')}" for l, i in infos.items()))

    # What each file should be: the manifests' member (any; they agree, else a conflict was
    # reported) and version.bin's asset entry.
    files = {}  # name -> enc
    for name, infos in member_info.items():
        files[name] = next(iter(infos.values())).get("e", 0)
    vb_files = {k: e for k, e in assets.items() if isinstance(e, dict) and e.get("flags", 0) == 0}
    if all_manifests:
        for name, e in vb_files.items():
            files.setdefault(name, e.get("encType", 0))

    # Examine every file (processes: threads measured slower than one, the GIL).
    results = {}
    present = []
    for n in files:
        if os.path.isfile(os.path.join(root, n)):
            present.append(n)
        else:
            results[n] = None
    jobs = jobs or os.cpu_count() or 1
    t1 = time.time()
    # Batches of about the same byte count (a few futures per process), largest files first.
    present.sort(key=lambda n: -os.path.getsize(os.path.join(root, n)))
    batches = [present[i :: jobs * 4] for i in range(min(len(present), jobs * 4))]
    done = 0
    with cf.ProcessPoolExecutor(max_workers=jobs) as pool:
        futs = [pool.submit(examine_batch, root, [(n, files[n]) for n in b], quick) for b in batches]
        for fut in cf.as_completed(futs):
            out = fut.result()
            results.update(out)
            done += len(out)
            if progress and len(futs) >= 10 and (done - len(out)) * 10 // len(present) != done * 10 // len(present):
                progress(f"  {done}/{len(present)} files")
    info["read_seconds"] = round(time.time() - t1, 2)

    def check_member(name, label, mem):
        r = results.get(name)
        if r is None:
            rep.problem("missing", name, f"in bundle {', '.join(member_bundles[name][label])}", label)
            return False
        if "error" in r:
            rep.problem("missing", name, r["error"], label)
            return False
        ok = True
        e = mem.get("e", 0)
        if e and r["flags"] != e:
            rep.problem("enc", name, f"ADLD flags {r['flags']} != e {e}", label)
            ok = False
        if r["plain_size"] is not None and r["plain_size"] != mem.get("size"):
            rep.problem("size", name, f"plaintext {r['plain_size']} != {mem.get('size')} (file {r['size']})", label)
            ok = False
        if r["sha1"] is not None and r["sha1"] != mem.get("md5"):
            rep.problem("hash", name, f"SHA-1 {r['sha1']} != {mem.get('md5')}", label)
            ok = False
        return ok

    for label in manifests:
        good = bad = 0
        for name, infos in member_info.items():
            if label in infos:
                if check_member(name, label, infos[label]):
                    good += 1
                else:
                    bad += 1
        summary[label].update({"ok_files": good, "bad_files": bad})

    # version.bin's entries.
    vb_summary = {"assets": len(vb_files), "bundles": 0, "parent_hash": defaultdict(int)}
    if all_manifests:
        chash = {}
        for name, e in assets.items():
            if not isinstance(e, dict):
                continue
            if e.get("flags", 0) == 1:  # a bundle's own entry
                vb_summary["bundles"] += 1
                if name not in bundle_md5:
                    rep.problem("version-bin", name, "a bundle entry (flags 1) that no manifest lists")
                elif e.get("md5") not in bundle_md5[name].values():
                    rep.problem("version-bin", name, f"md5 {e.get('md5')} != the manifests' {sorted(set(bundle_md5[name].values()))}")
                if e.get("parentHash") != chash32(name.encode()):
                    rep.problem("parentHash", name, f"bundle entry: {e.get('parentHash')} != CHash32(name) {chash32(name.encode())}")
                continue
            r = results.get(name)
            if r is None or "error" in r:
                if name not in member_info:
                    rep.problem("missing", name, "a version.bin asset (no manifest lists it)")
                # else already reported per manifest
            else:
                if e.get("size") != r["size"]:
                    rep.problem("size", name, f"version.bin: stored size {r['size']} != {e.get('size')}")
                if r["sha1"] is not None and e.get("md5") != r["sha1"]:
                    rep.problem("hash", name, f"version.bin: SHA-1 {r['sha1']} != {e.get('md5')}")
                enc = e.get("encType", 0)
                if enc and r["flags"] != enc:
                    rep.problem("enc", name, f"version.bin: ADLD flags {r['flags']} != encType {enc}")
            infos = member_info.get(name)
            if not infos:
                rep.warning("unbundled", name, "in version.bin, in no manifest")
                continue
            for label, mem in infos.items():
                if mem.get("e", 0) != e.get("encType", 0):
                    rep.problem("enc", name, f"version.bin encType {e.get('encType')} != e {mem.get('e')}", label)
            matched = None
            for label, bundles in member_bundles[name].items():
                for b in bundles:
                    if b not in chash:
                        chash[b] = chash32(b.encode())
                    if chash[b] == e.get("parentHash"):
                        matched = label
            if matched is None:
                rep.problem("parentHash", name, f"{e.get('parentHash')} is no bundle listing it ({', '.join(b for bs in member_bundles[name].values() for b in bs)})")
            else:
                vb_summary["parent_hash"][matched.split("/")[-1]] += 1
        for name in member_info:
            if name not in assets:
                rep.warning("unindexed", name, "listed in " + ", ".join(member_info[name]) + ", not in version.bin")
    vb_summary["parent_hash"] = dict(vb_summary["parent_hash"])

    # Extras: files nothing lists.
    listed = set(member_info) | set(vb_files)
    if not all_manifests:  # the other manifests' members aren't extras either
        for bin_path, _ in find_manifests(root, "all")[0].values():
            if bin_path not in {b for b, _ in manifests.values()}:
                for bb in load_msgpack(bin_path).get("assets", {}).values():
                    listed.update(n for n, mem in bb.items() if isinstance(mem, dict))
    nfiles = 0
    for dirpath, dirnames, filenames in os.walk(root):
        rel = os.path.relpath(dirpath, root)
        if rel == "manifest" or rel.startswith("manifest" + os.sep):
            dirnames[:] = []
            continue
        for fn in filenames:
            name = fn if rel == "." else os.path.join(rel, fn).replace(os.sep, "/")
            if name == "version.bin":
                continue
            nfiles += 1
            if name not in listed:
                rep.problem("extra", name, f"{os.path.getsize(os.path.join(root, name))} bytes; no manifest or version.bin entry lists it")
    info["files_on_disk"] = nfiles
    info["seconds"] = round(time.time() - t0, 2)

    for label, s in summary.items():
        s["status"] = "OK" if not any(p["manifest"] == label for p in rep.problems) else "FAIL"
    return {"info": info, "manifests": summary, "version_bin": vb_summary, "problems": rep.problems,
            "warnings": rep.warnings, "notes": rep.notes, "ok": not rep.problems}


# ---- the report ------------------------------------------------------------------------------------
def print_report(res, max_list, out=sys.stdout):
    i = res["info"]
    p = lambda *a: print(*a, file=out)  # noqa: E731
    p(f"{i['dir']}: {i['mode']} check, manifest {i['manifest']}")
    p(f"version.bin {i['version_bin']}: revision {i['revision']}, id {i['version']}, {i['assets']} entries")
    for n in res["notes"]:
        p(f"note: {n}")
    p(f"{'manifest':<12} {'bundles':>8} {'members':>8} {'bytes':>14} {'totalSize':>14} {'ok':>8} {'bad':>6}  status")
    for label, s in res["manifests"].items():
        p(f"{label:<12} {s['bundles']:>8} {s['members']:>8} {s['bytes']:>14} {str(s.get('totalSize')):>14} {s['ok_files']:>8} {s['bad_files']:>6}  {s['status']}")
    vb = res["version_bin"]
    if i["manifest"] == "all":
        p(f"version.bin: {vb['assets']} assets, {vb['bundles']} bundle entries; parentHash names a bundle of: "
          + ", ".join(f"{k} {v}" for k, v in sorted(vb["parent_hash"].items())))
    p(f"files on disk: {i['files_on_disk']} (without manifest/ and version.bin); read in {i['read_seconds']} s, total {i['seconds']} s")
    for title, items, kinds in (("problems", res["problems"], PROBLEM_KINDS), ("warnings", res["warnings"], WARNING_KINDS)):
        by = defaultdict(list)
        for it in items:
            by[it["kind"]].append(it)
        for kind in kinds:
            if not by[kind]:
                continue
            p(f"{title[:-1]} {kind}: {len(by[kind])}")
            for it in by[kind][:max_list]:
                p(f"  {(it['manifest'] + ': ') if it['manifest'] else ''}{it['name']}: {it['detail']}")
            if len(by[kind]) > max_list:
                p(f"  ... {len(by[kind]) - max_list} more (--json for all)")
    p(("PASS" if res["ok"] else "FAIL") + f": {len(res['problems'])} problems, {len(res['warnings'])} warnings")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0], formatter_class=argparse.RawDescriptionHelpFormatter, epilog=__doc__)
    ap.add_argument("dir")
    ap.add_argument("--manifest", default="all", choices=["all"] + MANIFESTS)
    ap.add_argument("--version-bin", help="the index to check against (default: DIR/version.bin, else data/version-3.7.0.bin)")
    ap.add_argument("--jobs", type=int, default=None, help="reader processes (default: the CPU count)")
    ap.add_argument("--quick", action="store_true", help="existence, sizes and ADLD headers only; no hashing")
    ap.add_argument("--json", metavar="OUT", help="write the full result as JSON")
    ap.add_argument("--max-list", type=int, default=20, help="findings listed per kind (default 20)")
    a = ap.parse_args(argv)
    if not os.path.isdir(a.dir):
        ap.error(f"{a.dir}: not a directory")
    res = check(a.dir, a.manifest, a.jobs, a.quick, a.version_bin, progress=lambda s: print(s, file=sys.stderr))
    if a.json:
        with open(a.json, "w") as f:
            json.dump(res, f, indent=1)
    print_report(res, a.max_list)
    return 0 if res["ok"] else 1


if __name__ == "__main__":
    sys.exit(main())
