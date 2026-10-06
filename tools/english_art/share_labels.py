#!/usr/bin/env python3
"""Copy the English art recipes' labels to every other scene whose atlas has the same sprite.

  .venv/bin/python tools/english_art/share_labels.py [--download DIR] [--recipes DIR]

The UI scenes (UI/etc2/*.csf, TalkScene/etc2/*.csf) each carry their own copy of shared sprites
(the Back button, the badges, the footer...). A label written once in one scene's recipe
(standin-assets-en/recipes/<scene>.json) is copied, with its box, cover and style, into the recipe of
every scene whose atlas has a sprite of the same name, size and (nearly) the same pixels: the copy is
marked "_from": "<scene>" (a comment key for the server). A scene's own labels win; copies are
recomputed on each run. Needs build/tools/aif2png/aif2png (atlases) and Pillow + numpy.
docs/english.md section 8.
"""
import argparse
import glob
import json
import os
import struct
import subprocess
import sys
import tempfile

import numpy as np
from PIL import Image

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from make_standin_banners import read_aif  # noqa: E402  (ADLD + SLZ)


def scene_tables(download):
    """{source rel: (csv text, atlas png path)} for every scene with a sprite table."""
    out = {}
    for d in ("UI", "TalkScene"):
        for p in sorted(glob.glob(os.path.join(download, d, "etc2", "*.csf"))):
            rel = os.path.relpath(p, download).replace(os.sep, "/")
            try:
                data = read_aif(p, rel)
            except (ValueError, RuntimeError, struct.error):
                continue
            if data[:4] != b"\0ISF":
                continue
            for i in range(struct.unpack_from("<I", data, 8)[0]):
                no, off, ln, _ = struct.unpack_from("<4I", data, 16 + 16 * i)
                if data[no:data.index(b"\0", no)].decode().endswith(".csv"):
                    out[rel] = data[off:off + ln].decode()
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--download", default=os.path.join(ROOT, "work", "download-3.7.0"))
    ap.add_argument("--recipes", default=os.path.join(ROOT, "standin-assets-en", "recipes"))
    a = ap.parse_args()
    aif2png = os.path.join(ROOT, "build", "tools", "aif2png", "aif2png")
    tables = scene_tables(a.download)
    tmp = tempfile.mkdtemp(prefix="share-labels-")
    pngs = {rel: os.path.join(tmp, rel.replace("/", "_") + ".png") for rel in tables}
    batch = "".join(f"{os.path.join(a.download, rel)}\t{rel}\t{png}\n" for rel, png in pngs.items())
    subprocess.run([aif2png, "-"], input=batch, text=True, check=True, capture_output=True)
    rects = {rel: {l.split(",")[0]: tuple(map(int, l.split(",")[1:])) for l in t.splitlines() if l.count(",") == 4} for rel, t in tables.items()}
    atlases = {}

    def crop(rel, name):
        if rel not in atlases:
            atlases[rel] = np.array(Image.open(pngs[rel]).convert("RGBA")).astype(int)
        x, y, w, h = rects[rel][name]
        return atlases[rel][y:y + h, x:x + w]

    own = {}
    for p in sorted(glob.glob(os.path.join(a.recipes, "*.json"))):
        r = json.load(open(p, encoding="utf-8"))
        r["labels"] = [l for l in r["labels"] if "_from" not in l]
        own[r["source"]] = (p, r)
    catalog = {}
    for src, (p, r) in own.items():
        for l in r["labels"]:
            for s in l["sprites"]:
                catalog.setdefault(s, (l, r["styles"], src))
    copied = {}
    for rel in sorted(tables):
        have = {s for l in own.get(rel, (None, {"labels": []}))[1]["labels"] for s in l["sprites"]}
        new = {}
        for s, (l, styles, ref) in catalog.items():
            if ref == rel or s not in rects[rel] or s in have or ref not in rects:
                continue
            x, y = crop(ref, s), crop(rel, s)
            if x.shape != y.shape or np.abs(x - y).mean() > 4:
                continue
            key = json.dumps({k: v for k, v in l.items() if k != "sprites"}, sort_keys=True, ensure_ascii=False)
            new.setdefault(key, (l, styles, ref, []))[3].append(s)
        if not new:
            continue
        scene = os.path.basename(rel)[:-4]
        p, r = own.get(rel) or (os.path.join(a.recipes, scene + ".json"),
                                {"note": "Labels shared with other scenes' atlases (the same sprites), copied by tools/english_art/share_labels.py.",
                                 "source": rel, "styles": {}, "labels": []})
        own[rel] = (p, r)
        for key, (l, styles, ref, sprites) in sorted(new.items()):
            ref_scene = os.path.basename(ref)[:-4]
            name = l["style"]
            if name in r["styles"] and r["styles"][name] != styles[name]:
                name = f"{ref_scene}_{name}"
            r["styles"][name] = styles[l["style"]]
            r["labels"].append(dict(l, sprites=sorted(sprites), style=name, _from=ref_scene))
        copied[rel] = sum(len(v[3]) for v in new.values())
    for p, r in own.values():
        with open(p, "w", encoding="utf-8") as f:
            f.write(json.dumps(r, ensure_ascii=False, indent=1) + "\n")
    for rel, n in sorted(copied.items()):
        print(f"{rel}: {n} sprites")
    print(f"share_labels: {len(copied)} scenes got shared labels")


if __name__ == "__main__":
    main()
