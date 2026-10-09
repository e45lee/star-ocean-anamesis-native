#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Unpack a 3.7.0 download archive and verify it is complete.

Extracts a zip of the game's download tree (the one the client fetches after login: version.bin,
manifest/, sqlite/, EP1-3/, B/, BG/, ...) into DEST, then checks DEST with tools/check_download.py
against its own manifests and version.bin.

The archive may hold the tree at its top level (e.g. SOA-3.7.0-canonical-data.zip) or inside one
top folder (e.g. SOA-data/...); the folder is stripped either way, so DEST is the tree.
Windows "Zone.Identifier" alternate-stream files (`name:Zone.Identifier`, left by copying a
download through Windows) are skipped. With --sha256 FILE (a `sha256sum` line, e.g.
SOA-3.7.0-canonical-data.zip.sha256) the archive is checked before anything is extracted.

This is for users who want the tree as a folder: nothing in the repository needs it. The programs
and tools read the zip itself in place (soa/file_tree.h, soa_save/download_tree.py), and take an
extracted folder too wherever they take the download.

Usage:
  tools/unpack_download.py ARCHIVE.zip DEST [--sha256 FILE] [--force] [--quick] [--jobs N] [--json OUT]

Exit status: 0 when the archive's checksum (if given) matches and the unpacked tree passes the
check; 1 otherwise. DEST must be empty or absent unless --force, which extracts over it.
"""
import argparse
import hashlib
import os
import sys
import zipfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import check_download  # noqa: E402

ZONE_SUFFIX = ":Zone.Identifier"


def sha256_of(path, chunk=1 << 20):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for block in iter(lambda: f.read(chunk), b""):
            h.update(block)
    return h.hexdigest()


def expected_sha256(sha_file):
    """The first hex digest in a `sha256sum` output file."""
    with open(sha_file) as f:
        for line in f:
            word = line.split()[0] if line.split() else ""
            if len(word) == 64 and all(c in "0123456789abcdef" for c in word.lower()):
                return word.lower()
    raise SystemExit(f"{sha_file}: no SHA-256 digest in it")


def top_folder(names):
    """The single top-level folder every entry is under, or "" when the tree is at the top level.

    A tree at the top level has version.bin there; otherwise exactly one top folder may hold it.
    """
    tops = {n.split("/", 1)[0] for n in names if n and not n.startswith("__MACOSX")}
    if "version.bin" in tops or len(tops) != 1:
        return ""
    (top,) = tops
    return top + "/"


def safe_target(dest, rel):
    """DEST/rel, refusing absolute paths and `..` (a malformed or hostile archive)."""
    path = os.path.normpath(os.path.join(dest, rel))
    if os.path.isabs(rel) or not (path == dest or path.startswith(dest + os.sep)):
        raise SystemExit(f"refusing the archive member {rel!r}: outside the destination")
    return path


def extract(archive, dest):
    """Extracts ARCHIVE into DEST (its top folder stripped); returns (files, skipped zone files)."""
    files = skipped = 0
    with zipfile.ZipFile(archive) as z:
        members = z.infolist()
        strip = top_folder([m.filename for m in members])
        for m in members:
            name = m.filename
            if name.endswith(ZONE_SUFFIX):
                skipped += 1
                continue
            rel = name[len(strip):] if strip and name.startswith(strip) else name
            if not rel or rel.endswith("/"):
                continue
            target = safe_target(dest, rel)
            os.makedirs(os.path.dirname(target), exist_ok=True)
            with z.open(m) as src, open(target, "wb") as out:
                while block := src.read(1 << 20):
                    out.write(block)
            files += 1
            if files % 2000 == 0:
                print(f"  {files} files", file=sys.stderr)
    return files, skipped, strip


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0], formatter_class=argparse.RawDescriptionHelpFormatter,
                                 epilog=__doc__)
    ap.add_argument("archive")
    ap.add_argument("dest")
    ap.add_argument("--sha256", metavar="FILE", help="check the archive against this sha256sum file first")
    ap.add_argument("--force", action="store_true", help="extract into a non-empty DEST")
    ap.add_argument("--quick", action="store_true", help="check sizes and headers only (no hashing)")
    ap.add_argument("--jobs", type=int, default=None, help="reader processes for the check")
    ap.add_argument("--json", metavar="OUT", help="write the check's full result as JSON")
    a = ap.parse_args(argv)

    if not zipfile.is_zipfile(a.archive):
        ap.error(f"{a.archive}: not a zip archive")
    dest = os.path.abspath(a.dest)
    if os.path.isdir(dest) and os.listdir(dest) and not a.force:
        ap.error(f"{dest}: not empty (use --force to extract over it)")

    if a.sha256:
        want = expected_sha256(a.sha256)
        print(f"checking {a.archive} against {a.sha256} ...", file=sys.stderr)
        got = sha256_of(a.archive)
        if got != want:
            print(f"FAIL: the archive's SHA-256 is {got}, the file says {want}")
            return 1
        print(f"archive SHA-256 OK ({got})")

    os.makedirs(dest, exist_ok=True)
    print(f"extracting {a.archive} into {dest} ...", file=sys.stderr)
    files, skipped, strip = extract(a.archive, dest)
    print(f"extracted {files} files" + (f" (top folder {strip.rstrip('/')!r} stripped)" if strip else "")
          + (f"; skipped {skipped} Zone.Identifier files" if skipped else ""))

    res = check_download.check(dest, "all", a.jobs, a.quick, None, progress=lambda s: print(s, file=sys.stderr))
    if a.json:
        import json
        with open(a.json, "w") as f:
            json.dump(res, f, indent=1)
    check_download.print_report(res, 20)
    return 0 if res["ok"] else 1


if __name__ == "__main__":
    sys.exit(main())
