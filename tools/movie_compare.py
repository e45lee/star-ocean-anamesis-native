#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""The proof that the movie player on FFmpeg's libraries (runtime/src/frontend/movie_decoder.cpp)
decodes the game's movies as the ffmpeg program it replaced did.

For every movie (default: the 12 Movie/*.mp4 of the 3.7.0 download, --zip, read in place) it compares the player's decoder
(build/tools/movie_check/movie_check) with the ffmpeg program (any ffmpeg on PATH, e.g. Ubuntu's):

  pictures  every decoded picture's yuv420p planes: the same count and the same bytes (SHA-256) as
            `ffmpeg -i M -f rawvideo -pix_fmt yuv420p -`, with the program's default frame-rate
            handling (what the old player read, so the picture count and the k / fps pacing are
            the old ones) and with -fps_mode passthrough (every decoded picture once);
  sound     the samples as f32le stereo 48 kHz against the old player's own command
            (`ffmpeg -i M -vn -f f32le -ac 2 -ar 48000 -`): the samples both have, bit for bit (or
            the largest difference in 16-bit LSBs), and the samples only one has at the end
            ("same+tail": FFmpeg 9 ends the sound where the MP4 edit list does, dropping the AAC
            encoder's trailing padding, which FFmpeg 6.1 kept: allowed when the player's count is
            exactly the edit list's);
  colour    --rgba-frames pictures spread over the movie as RGBA, turned upright, from movie_check's CPU copy of
            the player's shader against the old player's command (`-vf transpose=2 -pix_fmt rgba`):
            the largest and mean difference per channel (swscale's integer tables vs the shader's
            float maths; not expected to be identical);
  sources   the same pictures and sound read the other ways the player reads them: the download
            zip's stored entry in place (--zip, default work/SOA-3.7.0-canonical-data.zip; for a
            MOVIE.mp4 given as a file) and the APK's stored entry in place (--apk, for the movie the
            APK has).

A movie of the zip is read in place everywhere: the player as tree:ZIP:Movie/NAME, the ffmpeg
program through its subfile protocol (the stored entry's byte range), the edit list from the
entry's bytes (soa_save/download_tree.py).

Exit 0 when the picture counts and the decoded pictures match and the sources agree. Small sound
and colour differences are reported, not failed (accepted, runtime/README.md "Movies"): sound fails
only past --audio-lsb or a tail longer than --audio-tail, colour only past --rgba-max; those
catch a broken decoder or shader, not rounding.

Usage: tools/movie_compare.py [--movie-check BIN] [--ffmpeg BIN] [--jobs N] [MOVIE.mp4 ...]
"""
import argparse
import concurrent.futures as cf
import hashlib
import os
import struct
import subprocess
import sys

import numpy as np

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)
from soa_save.download_tree import DEFAULT, DownloadTree  # noqa: E402


def stream(cmd, consume, chunk=1 << 20):
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.DEVNULL)
    while True:
        b = p.stdout.read(chunk)
        if not b:
            break
        consume(b)
    err = p.stderr.read().decode(errors="replace").strip()
    if p.wait() != 0:
        raise RuntimeError(f"{' '.join(cmd)}: exit {p.returncode}: {err}")
    return err


def sha_count(cmd):
    h, n = hashlib.sha256(), [0]

    def eat(b):
        h.update(b)
        n[0] += len(b)

    stream(cmd, eat)
    return h.hexdigest(), n[0]


def read_all(cmd):
    parts = []
    stream(cmd, parts.append)
    return b"".join(parts)


def info(mc, src):
    """movie_check --info: width=.. height=.. fps=.. frames=.. samples=.. ffmpeg=<the rest of the line>"""
    out = subprocess.run([mc, src, "--info"], capture_output=True, text=True, check=True).stdout.strip()
    head, lib = out.split(" ffmpeg=", 1)
    return dict(kv.split("=", 1) for kv in head.split()) | {"ffmpeg": lib}


def mp4_boxes(d, off, end):
    while off + 8 <= end:
        size, typ = struct.unpack(">I4s", d[off:off + 8])
        hdr = 8
        if size == 1:
            size, hdr = struct.unpack(">Q", d[off + 8:off + 16])[0], 16
        elif size == 0:
            size = end - off
        if size < hdr:
            return
        yield typ, off + hdr, off + size
        off += size


def edit_list_samples(d):
    """The sound's length as the MP4 edit list presents it: its one segment's duration (movie
    timescale) from media_time, clipped at the end of the media (mdhd), in samples at the media's
    rate; None when the file (its bytes `d`) has no such edit list."""
    for t, s, e in mp4_boxes(d, 0, len(d)):
        if t != b"moov":
            continue
        movie_ts = None
        for t2, s2, e2 in mp4_boxes(d, s, e):
            if t2 == b"mvhd":
                movie_ts = struct.unpack(">I", d[s2 + 12:s2 + 16] if d[s2] == 0 else d[s2 + 20:s2 + 24])[0]
            if t2 != b"trak":
                continue
            elst = mdhd = hdlr = None
            for t3, s3, e3 in mp4_boxes(d, s2, e2):
                if t3 == b"edts":
                    for t4, s4, e4 in mp4_boxes(d, s3, e3):
                        if t4 == b"elst" and struct.unpack(">I", d[s4 + 4:s4 + 8])[0] == 1:
                            elst = struct.unpack(">Ii", d[s4 + 8:s4 + 16]) if d[s4] == 0 else struct.unpack(">Qq", d[s4 + 8:s4 + 24])
                if t3 == b"mdia":
                    for t4, s4, e4 in mp4_boxes(d, s3, e3):
                        if t4 == b"mdhd":
                            mdhd = struct.unpack(">II", d[s4 + 12:s4 + 20]) if d[s4] == 0 else struct.unpack(">IQ", d[s4 + 20:s4 + 32])
                        if t4 == b"hdlr":
                            hdlr = d[s4 + 8:s4 + 12]
            if hdlr == b"soun" and elst and mdhd and movie_ts:
                (ts, dur), (seg, media_time) = mdhd, elst
                return min(seg * ts // movie_ts, dur - media_time)
    return None


def compare(movie, a):
    """`movie`: a file path, or (DownloadTree, rel) for a stored entry of the zip, read in place."""
    if isinstance(movie, tuple):
        tree, rel = movie
        name = os.path.basename(rel)
        _, off, size = tree.locate(rel)
        src, ff_in, data = f"tree:{tree.path}:{rel}", f"subfile,,start,{off},end,{off + size},,:{tree.path}", tree.read(rel)
    else:
        tree, name = None, os.path.basename(movie)
        src, ff_in = "file:" + movie, movie
        with open(movie, "rb") as fh:
            data = fh.read()
    r = {"movie": name, "ok": True, "notes": []}
    meta = info(a.movie_check, src)
    w, h = int(meta["width"]), int(meta["height"])
    fsize = w * h + 2 * ((w + 1) // 2) * ((h + 1) // 2)
    r["size"] = f"{w}x{h}"
    r["fps"] = float(meta["fps"])
    r["library"] = meta["ffmpeg"]
    ff = [a.ffmpeg, "-v", "error", "-nostdin", "-i", ff_in]

    # pictures
    new = sha_count([a.movie_check, src, "--yuv"])
    cfr = sha_count(ff + ["-f", "rawvideo", "-pix_fmt", "yuv420p", "-"])
    pas = sha_count(ff + ["-fps_mode", "passthrough", "-f", "rawvideo", "-pix_fmt", "yuv420p", "-"])
    r["frames"] = {"player": new[1] // fsize, "ffmpeg": cfr[1] // fsize, "ffmpeg_passthrough": pas[1] // fsize}
    r["pictures_equal"] = new == cfr and new == pas
    if not r["pictures_equal"]:
        r["ok"] = False
        r["notes"].append(f"pictures differ: player {new}, ffmpeg {cfr}, passthrough {pas}")

    # sound
    an = np.frombuffer(read_all([a.movie_check, src, "--audio"]), dtype="<f4")
    ar = np.frombuffer(read_all(ff + ["-vn", "-f", "f32le", "-ac", "2", "-ar", "48000", "-"]), dtype="<f4")
    r["samples"] = {"player": an.size // 2, "ffmpeg": ar.size // 2}
    n = min(an.size, ar.size)
    # The samples both have: bit for bit.
    differ = an[:n].view(np.uint32) != ar[:n].view(np.uint32)
    d = np.abs(an[:n].astype(np.float64) - ar[:n].astype(np.float64))
    r["audio_differing"] = int(np.count_nonzero(differ))
    r["audio_max_lsb16"] = float(d.max()) * 32768 if d.size else 0.0
    r["audio_identical"] = r["audio_differing"] == 0 and an.size == ar.size
    # Samples only one side has: FFmpeg 9 presents the sound as the MP4 edit list says (from
    # media_time for the segment's duration, clipped at the media's end), so it drops the AAC
    # encoder's padding after the last real sample; FFmpeg 6.1 kept it. Allowed when the player's
    # count is the edit list's exactly and only the ffmpeg program has more.
    extra = ar[n:] if ar.size > an.size else an[n:]
    r["edit_list_samples"] = edit_list_samples(data)
    r["audio_tail"] = {"side": "ffmpeg" if ar.size > an.size else "player", "samples": extra.size // 2,
                       "max_lsb16": float(np.abs(extra).max()) * 32768 if extra.size else 0.0}
    if r["audio_differing"] and r["audio_max_lsb16"] > a.audio_lsb:
        r["ok"] = False
        r["notes"].append(f"sound differs by up to {r['audio_max_lsb16']:.3f} 16-bit LSBs in {r['audio_differing']} samples")
    if extra.size:
        t = r["audio_tail"]
        msg = (f"{t['samples']} samples at the end only in {t['side']}'s output (up to {t['max_lsb16']:.3f} 16-bit LSBs); "
               f"the edit list presents {r['edit_list_samples']}")
        if t["side"] == "ffmpeg" and r["edit_list_samples"] == an.size // 2:
            r["notes"].append(msg + ": the player ends where the edit list does (accepted)")
        elif t["samples"] <= a.audio_tail:
            r["notes"].append(msg + " (accepted: within --audio-tail)")
        else:
            r["ok"] = False
            r["notes"].append(msg)

    # colour (the shader's conversion vs the old swscale output)
    n = a.rgba_frames
    step = max(1, r["frames"]["player"] // n)  # spread over the movie
    rn = np.frombuffer(read_all([a.movie_check, src, "--rgba", str(n), str(step)]), dtype=np.uint8).astype(np.int16)
    vf = f"select=not(mod(n\\,{step}))" + (",transpose=2" if h > w else "")
    rr = np.frombuffer(read_all(ff + ["-vf", vf, "-fps_mode", "passthrough", "-frames:v", str(n), "-f", "rawvideo", "-pix_fmt", "rgba", "-"]),
                       dtype=np.uint8).astype(np.int16)
    if rn.size != rr.size:
        r["ok"] = False
        r["notes"].append(f"RGBA sizes differ: {rn.size} vs {rr.size}")
    else:
        dd = np.abs(rn - rr).reshape(-1, 4)[:, :3]
        r["rgba_max"] = int(dd.max())
        r["rgba_mean"] = float(dd.mean())
        r["rgba_over2"] = float(np.count_nonzero(dd > 2) / dd.size)
        if r["rgba_max"] > a.rgba_max:
            r["ok"] = False
            r["notes"].append(f"RGBA differs by up to {r['rgba_max']}")

    # the other sources: the same bytes decoded from a zip in place
    r["sources"] = {}
    others = []
    if tree is None and a.zip and os.path.exists(a.zip):
        others.append(("data zip, in place", f"tree:{a.zip}:Movie/{name}"))
    if a.apk and os.path.exists(a.apk):
        listing = subprocess.run(["unzip", "-l", a.apk, f"assets/builtin_data/Movie/{name}"], capture_output=True, text=True).stdout
        if f"Movie/{name}" in listing:
            others.append(("APK, in place", f"zip:{a.apk}:assets/builtin_data/Movie/{name}"))
    for label, s in others:
        v = sha_count([a.movie_check, s, "--yuv"])
        au = sha_count([a.movie_check, s, "--audio"])
        same = v == new and au == (hashlib.sha256(an.tobytes()).hexdigest(), an.nbytes)
        r["sources"][label] = same
        if not same:
            r["ok"] = False
            r["notes"].append(f"{label}: decoded differently from the file")
    return r


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("movies", nargs="*")
    ap.add_argument("--movie-check", default=os.path.join(ROOT, "build/tools/movie_check/movie_check"))
    ap.add_argument("--ffmpeg", default="ffmpeg")
    ap.add_argument("--zip", default=DEFAULT, help="the 3.7.0 download: its zip (or a folder); the default movies are its Movie/*.mp4")
    ap.add_argument("--apk", default=os.path.join(ROOT, "apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk"))
    ap.add_argument("--rgba-frames", type=int, default=60)
    ap.add_argument("--rgba-max", type=int, default=16,
                    help="largest RGBA channel difference before it fails (default 16; the shader vs swscale: up to 3)")
    ap.add_argument("--audio-lsb", type=float, default=64.0,
                    help="largest sound difference before it fails, in 16-bit LSBs (default 64: a broken decoder, not rounding)")
    ap.add_argument("--audio-tail", type=int, default=2048,
                    help="most samples only one side may have at the end before it fails (default 2048, two AAC frames)")
    ap.add_argument("--jobs", type=int, default=4)
    a = ap.parse_args()
    movies = a.movies
    if not movies:
        tree = DownloadTree.open_or_none(a.zip)
        if tree is not None and tree.is_zip:
            movies = [(tree, "Movie/" + n) for n in tree.list("Movie") if n.endswith(".mp4")]
        elif tree is not None:
            movies = [os.path.join(tree.path, "Movie", n) for n in tree.list("Movie") if n.endswith(".mp4")]
    if not movies:
        sys.exit("movie_compare: no movies (pass MOVIE.mp4 paths)")
    print(f"movie_compare: {len(movies)} movies; ffmpeg program: "
          + subprocess.run([a.ffmpeg, "-version"], capture_output=True, text=True).stdout.splitlines()[0])
    with cf.ThreadPoolExecutor(a.jobs) as ex:
        results = list(ex.map(lambda m: compare(m, a), movies))
    print(f"player's FFmpeg: {results[0]['library']}")
    print(f"{'movie':16} {'size':8} {'fps':>6} {'pictures (player/ffmpeg/passthrough)':>36} {'same':>5} "
          f"{'samples (player/ffmpeg)':>24} {'sound':>10} {'rgba max/mean/>2':>18}  sources")
    bad = 0
    for r in results:
        f, s = r["frames"], r["samples"]
        sound = ("identical" if r["audio_identical"] else "same+tail" if not r["audio_differing"] else f"{r['audio_max_lsb16']:.3f}lsb")
        rgba = f"{r.get('rgba_max', '-')}/{r.get('rgba_mean', 0):.3f}/{100 * r.get('rgba_over2', 0):.2f}%"
        srcs = ", ".join(f"{k}: {'same' if v else 'DIFFERENT'}" for k, v in r["sources"].items()) or "-"
        pics = f"{f['player']}/{f['ffmpeg']}/{f['ffmpeg_passthrough']}"
        print(f"{r['movie']:16} {r['size']:8} {r['fps']:6.2f} {pics:>36} {'yes' if r['pictures_equal'] else 'NO':>5} "
              f"{str(s['player']) + '/' + str(s['ffmpeg']):>24} {sound:>10} {rgba:>18}  {srcs}")
        for n in r["notes"]:
            print(f"    {n}")
        bad += not r["ok"]
    print("PASS" if not bad else f"FAIL ({bad} of {len(results)} movies)")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
