#!/usr/bin/env python3
"""Make stand-in gacha images (made-up art, not the original) for gachas whose banner / pick-up
images were lost: the online server had removed them, so neither the 3.7.0 download nor the APKs
have them. Writes game-format .aif files into the stand-in asset overlay (standin-assets/,
served by the port with --server inproc (the default) / --standin-assets; see port/README.md "Stand-in assets").

  .venv-or-any-python tools/make_standin_banners.py [gacha id_label ...]

Default gachas: the Summer '17 swimsuit pick-ups gacha_pickup_role_0054 (常夏のミキ/常夏のミュリア) and
gacha_pickup_role_0056 (常夏のレイミ/常夏のソフィア), and the NieR:Automata rerun
gacha_pickup_role_0283 (復刻NieR:Automataピックアップキャラガチャ: ２Ｂ/９Ｓ/Ａ２; its list banner
20200227_chara_002 and its panels pickup_img_chara_0015..0017). For each gacha, every image it
refers to (master_banner.image of its banner_id, master_gacha.image1..4, master_gacha_image rows)
that no real source has is generated:
  * list banners:  the gacha title, the pick-up names, the dates, a "STAND-IN" tag;
  * pick-up panels: the pick-up character's name, rarity and role type, a "STAND-IN" tag.
The pick-ups are the names in the title's brackets (as the gacha pools' R-PU-NAME rule does), else
the roles of its master_gacha_image rows (content_id_label role_<cp>_<n>). The look is a theme
(THEMES, picked per gacha in GACHA_THEMES): "beach" (default; the Summer '17 ones): a summer beach
gradient with the characters' universe-chip portraits (Image/etc2/u_chip_<cp>.aif from the
download); "automata" (NieR): a beige/grey YoRHa-style backdrop with the gacha's title as the
banner's header, the chip portraits on the banner and the characters' full-figure art
(Image/etc2/<character>_fv<costume>.aif, e.g. cc0015_fv01a for cc0015_b01a) on the panels. Art that is missing is left out.

Format: the size and pixel format of the real images of the same kind (a template: the first real
Image/etc2/<same prefix>*.aif in the download, e.g. banner_gacha_pickup_role_* 512x128 and
pickup_img_chara_* 1024x512, both ETC2 RGBA8). The template's AIF container is reused with fresh
GUIDs and texture id and the pixel block replaced by our ETC2 RGBA8 encoding; then SLZ (codec 5, raw deflate,
64 KiB chunks) and ADLD (XOR with the "%x" of CHash32("Image/etc2/<name>.aif")), the inverse of
tools/aif2png. Each output is decoded again with tools/aif2png and compared with the source picture.

Needs Pillow, numpy and zstandard (pip install pillow numpy zstandard) and the Japanese font
IPAexGothic (fonts-ipaexfont) or Droid Sans Fallback. Master data: data/basmaster-3.7.0.sqlite3.
"""
import argparse
import hashlib
import os
import re
import sqlite3
import struct
import subprocess
import sys
import tempfile
import zlib

import numpy as np
from PIL import Image, ImageDraw, ImageFilter, ImageFont

try:
    import zstandard
except ImportError:  # only needed for zstd-compressed templates
    zstandard = None

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
AIF2PNG = os.path.join(ROOT, "tools", "aif2png", "aif2png")
DEFAULT_GACHAS = ["gacha_pickup_role_0054", "gacha_pickup_role_0056", "gacha_pickup_role_0283"]
FONTS = ["/usr/share/fonts/opentype/ipaexfont-gothic/ipaexg.ttf", "/usr/share/fonts/opentype/ipafont-gothic/ipag.ttf",
         "/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf"]


# ---------------------------------------------------------------- ADLD / SLZ (as tools/aif2png)
def chash32(s):
    c = len(s.encode())
    for b in s.encode():
        c ^= b
        x = c & 0xff
        for _ in range(8):
            x = (x >> 1) ^ 0xEDB88320 if x & 1 else x >> 1
        c = x ^ (c >> 8)
    return c


def adld_xor(body, name):
    key = ("%x" % chash32(name)).encode()
    k = np.frombuffer((key * (len(body) // len(key) + 1))[:len(body)], np.uint8)
    return (np.frombuffer(body, np.uint8) ^ k).tobytes()


def read_aif(path, name):
    """The decrypted, decompressed AIF container of an .aif file."""
    d = open(path, "rb").read()
    if d[:4] == b"ADLD":
        flags = struct.unpack_from("<I", d, 4)[0]
        if flags & 2:
            raise ValueError("ADLD AES variant")
        d = adld_xor(d[16:], name) if flags & 1 else d[16:]
    if d[:3] != b"SLZ":
        return d
    codec, dsz, off, chunk = d[3], struct.unpack_from("<i", d, 0xc)[0], struct.unpack_from("<I", d, 0x14)[0], d[0x19] * 1024 or None
    chunk = chunk or dsz
    out, p = bytearray(), off
    while len(out) < dsz:
        want = min(chunk, dsz - len(out))
        if codec == 0:
            out += d[p:p + want]
            p += want
            continue
        n = struct.unpack_from("<H", d, p)[0]
        p += 2
        if n == 0:
            out += d[p:p + want]
            p += want
            continue
        if codec == 5:
            out += zlib.decompressobj(-15).decompress(d[p:p + n])
        elif codec == 7:
            if zstandard is None:
                raise RuntimeError("zstandard module needed for this template")
            out += zstandard.ZstdDecompressor().decompressobj().decompress(d[p:p + n])
        else:
            raise ValueError(f"SLZ codec {codec}")
        p += n
    return bytes(out)


def write_aif(container, name):
    """SLZ codec 5 (64 KiB raw-deflate chunks; a chunk that doesn't shrink is stored, size 0) + ADLD XOR."""
    chunks = []
    for i in range(0, len(container), 65536):
        raw = container[i:i + 65536]
        co = zlib.compressobj(9, zlib.DEFLATED, -15)
        z = co.compress(raw) + co.flush()
        chunks.append(struct.pack("<H", len(z)) + z if len(z) < min(len(raw), 65536) else struct.pack("<H", 0) + raw)
    payload = b"".join(chunks)
    # header as the shipped files: 'SLZ', codec, 0, 1 block, 0x25, compressed size (chunks incl. their
    # u16 sizes), decompressed size, 0, payload offset 0x20, flags 1, 64 KiB chunks, 0x10, no chain
    hdr = struct.pack("<3sBBBHiiIIBBHI", b"SLZ", 5, 0, 1, 0x25, len(payload), len(container), 0, 0x20, 1, 64, 0x10, 0)
    slz = hdr + payload
    slz += b"\0" * (-len(slz) % 4)
    return b"ADLD" + struct.pack("<I", 1) + b"\0" * 8 + adld_xor(slz, name)


def find16(d, tag, start, end):
    for i in range(start, min(end, len(d)) - 15, 16):
        if d[i:i + 4] == tag:
            return i
    return -1


def image_layout(d):
    """(format, width, height, pixel offset, pixel size, [GUIDs]) of the first image of a container."""
    amf = find16(d, b" FMA", 0, len(d))
    amf_end = amf + struct.unpack_from("<I", d, amf + 4)[0]
    buff = find16(d, b"ffub", amf, amf_end)
    start = amf_end - struct.unpack_from("<I", d, buff + 0x10)[0]
    img = find16(d, b"Xgmi", 0, len(d))
    fmt, w, h = d[img + 0x20], *struct.unpack_from("<HH", d, img + 0x28)
    guid = d[img + 0x40:img + 0x50]
    guids, a, data = [], amf, None
    while (a := find16(d, b"rdda", a, start)) >= 0:
        guids.append(d[a + 0x10:a + 0x20])
        if d[a + 0x10:a + 0x20] == guid:
            data = (start + struct.unpack_from("<Q", d, a + 0x28)[0], struct.unpack_from("<I", d, a + 0x20)[0])
        a += 16
    head = find16(d, b"daeh", amf, amf_end)
    if head >= 0:
        guids.append(d[head + 0x20:head + 0x30])
    return fmt, w, h, data, guids


# ---------------------------------------------------------------- ETC2 RGBA8 encoder
ETC_MOD = np.array([[2, 8], [5, 17], [9, 29], [13, 42], [18, 60], [24, 80], [33, 106], [47, 183]])
# pixel index i (msb<<1|lsb): 0 +small, 1 +large, 2 -small, 3 -large
MODS = np.stack([ETC_MOD[:, 0], ETC_MOD[:, 1], -ETC_MOD[:, 0], -ETC_MOD[:, 1]], 1)  # (8 tables, 4)
EAC_MOD = np.array([
    [-3, -6, -9, -15, 2, 5, 8, 14], [-3, -7, -10, -13, 2, 6, 9, 12], [-2, -5, -8, -13, 1, 4, 7, 12],
    [-2, -4, -6, -13, 1, 3, 5, 12], [-3, -6, -8, -12, 2, 5, 7, 11], [-3, -7, -9, -11, 2, 6, 8, 10],
    [-4, -7, -8, -11, 3, 6, 7, 10], [-3, -5, -8, -11, 2, 4, 7, 10], [-2, -6, -8, -10, 1, 5, 7, 9],
    [-2, -5, -8, -10, 1, 4, 7, 9], [-2, -4, -8, -10, 1, 3, 7, 9], [-2, -5, -7, -10, 1, 4, 6, 9],
    [-3, -4, -7, -10, 2, 3, 6, 9], [-1, -2, -3, -10, 0, 1, 2, 9], [-4, -6, -8, -9, 3, 5, 7, 8],
    [-3, -5, -7, -9, 2, 4, 6, 8]])


def etc1_blocks(px):
    """px (N,4,4,3) uint8 [block][y][x][c] -> (N,) uint64 ETC1 (individual / differential) blocks."""
    n = px.shape[0]
    p = px.astype(np.int32)
    best_err = np.full(n, np.inf)
    best = np.zeros(n, np.uint64)
    yy, xx = np.mgrid[0:4, 0:4]
    for flip in (0, 1):
        second = (yy >= 2) if flip else (xx >= 2)  # (4,4)
        avg = np.stack([p[:, ~second].mean(1), p[:, second].mean(1)], 1)  # (N,2,3)
        q5 = np.clip(np.rint(avg * 31 / 255), 0, 31).astype(np.int64)
        dq = q5[:, 1] - q5[:, 0]
        diff = np.all((dq >= -4) & (dq <= 3), 1)
        q4 = np.clip(np.rint(avg * 15 / 255), 0, 15).astype(np.int64)
        base = np.where(diff[:, None, None], (q5 << 3) | (q5 >> 2), q4 * 17)  # (N,2,3)
        # per pixel: its sub-block's base colour
        pb = np.where(second[None, :, :, None], base[:, None, None, 1, :], base[:, None, None, 0, :])  # (N,4,4,3)
        cand = np.clip(pb[:, :, :, None, None, :] + MODS[None, None, None, :, :, None], 0, 255)  # (N,4,4,8,4,3)
        err = ((cand - p[:, :, :, None, None, :]) ** 2).sum(-1)  # (N,4,4,8,4)
        idx = err.argmin(-1)  # (N,4,4,8)
        emin = err.min(-1)  # (N,4,4,8)
        e0 = (emin * (~second)[None, :, :, None]).sum((1, 2))  # (N,8)
        e1 = (emin * second[None, :, :, None]).sum((1, 2))
        t0, t1 = e0.argmin(1), e1.argmin(1)
        tot = e0.min(1) + e1.min(1)
        tsel = np.where(second[None], t1[:, None, None], t0[:, None, None])  # (N,4,4)
        pix = np.take_along_axis(idx, tsel[..., None], -1)[..., 0].astype(np.uint64)  # (N,4,4)
        v = np.zeros(n, np.uint64)
        for c, sh in ((0, 56), (1, 48), (2, 40)):
            dv = (dq[:, c] & 7).astype(np.uint64)
            vd = (q5[:, 0, c].astype(np.uint64) << np.uint64(sh + 3)) | (dv << np.uint64(sh))
            vi = (q4[:, 0, c].astype(np.uint64) << np.uint64(sh + 4)) | (q4[:, 1, c].astype(np.uint64) << np.uint64(sh))
            v |= np.where(diff, vd, vi)
        v |= t0.astype(np.uint64) << np.uint64(37)
        v |= t1.astype(np.uint64) << np.uint64(34)
        v |= diff.astype(np.uint64) << np.uint64(33)
        v |= np.uint64(flip) << np.uint64(32)
        for y in range(4):
            for x in range(4):
                j = np.uint64(x * 4 + y)
                v |= ((pix[:, y, x] >> np.uint64(1)) & np.uint64(1)) << (j + np.uint64(16))
                v |= (pix[:, y, x] & np.uint64(1)) << j
        better = tot < best_err
        best = np.where(better, v, best)
        best_err = np.where(better, tot, best_err)
    return best


def eac_block(a):
    """a (4,4) [y][x] alpha -> 8 bytes of EAC alpha."""
    lo, hi = int(a.min()), int(a.max())
    if lo == hi:  # table 13 has a 0 modifier (index 4)
        return bytes([lo, 1 << 4 | 13]) + (sum(4 << (45 - 3 * i) for i in range(16))).to_bytes(6, "big")
    av = a.T.reshape(16).astype(np.int32)  # pixel i = x*4+y
    best = None
    for base in range(max(0, (lo + hi) // 2 - 8), min(255, (lo + hi) // 2 + 8) + 1, 2):
        for mult in range(1, 16):
            vals = np.clip(base + EAC_MOD * mult, 0, 255)  # (16,8)
            err = (vals[:, :, None] - av[None, None, :]) ** 2  # (16,8,16)
            e = err.min(1).sum(1)
            t = int(e.argmin())
            if best is None or e[t] < best[0]:
                best = (int(e[t]), base, mult, t, err[t].argmin(0))
    _, base, mult, t, idx = best
    bits = 0
    for i in range(16):
        bits |= int(idx[i]) << (45 - 3 * i)
    return bytes([base, mult << 4 | t]) + bits.to_bytes(6, "big")


def encode_etc2_rgba8(img):
    a = np.array(img.convert("RGBA"))
    h, w = a.shape[:2]
    bh, bw = (h + 3) // 4, (w + 3) // 4
    pad = np.zeros((bh * 4, bw * 4, 4), np.uint8)
    pad[:h, :w] = a
    blocks = pad.reshape(bh, 4, bw, 4, 4).transpose(0, 2, 1, 3, 4).reshape(-1, 4, 4, 4)
    colour = etc1_blocks(blocks[..., :3])
    out = bytearray()
    for k in range(blocks.shape[0]):
        out += eac_block(blocks[k, :, :, 3])
        out += int(colour[k]).to_bytes(8, "big")
    return bytes(out)


# ---------------------------------------------------------------- art
def font(size):
    for f in FONTS:
        if os.path.exists(f):
            return ImageFont.truetype(f, size)
    return ImageFont.load_default()


def beach(w, h, horizon=0.62, sand=0.84):
    """Sky -> sea -> sand gradient with a sun and a few wave lines."""
    y = np.linspace(0, 1, h)[:, None]
    sky_top, sky_low = np.array([70, 160, 235]), np.array([255, 226, 170])
    sea0, sea1 = np.array([40, 170, 215]), np.array([20, 90, 170])
    sand0 = np.array([245, 225, 170])
    col = np.where(y < horizon, sky_top + (sky_low - sky_top) * (y / horizon) ** 1.5,
                   np.where(y < sand, sea0 + (sea1 - sea0) * ((y - horizon) / (sand - horizon)), sand0))
    col = np.clip(col, 0, 255)
    rgb = np.repeat(col[:, None, :], w, 1).reshape(h, w, 3).astype(np.uint8)
    im = Image.fromarray(rgb, "RGB").convert("RGBA")
    d = ImageDraw.Draw(im)
    r = int(h * 0.16)
    cx, cy = int(w * 0.82), int(h * horizon) - r // 3
    glow = Image.new("RGBA", im.size, (0, 0, 0, 0))
    ImageDraw.Draw(glow).ellipse((cx - 2 * r, cy - 2 * r, cx + 2 * r, cy + 2 * r), fill=(255, 240, 180, 110))
    im.alpha_composite(glow.filter(ImageFilter.GaussianBlur(r * 0.6)))
    d.ellipse((cx - r, cy - r, cx + r, cy + r), fill=(255, 245, 200, 255))
    for k in range(4):  # wave lines
        yy = int(h * horizon + (h * (sand - horizon)) * (k + 1) / 5)
        for x0 in range(-40 + 23 * k % 60, w, 90):
            d.arc((x0, yy - 5, x0 + 50, yy + 5), 200, 340, fill=(255, 255, 255, 150), width=2)
    return im


def automata(w, h, horizon=None, sand=None):
    """A YoRHa-style backdrop: warm beige to grey, a faint square grid, thin rules and a few
    scattered squares (the arguments are beach()'s, unused)."""
    y = np.linspace(0, 1, h)[:, None, None]
    x = np.linspace(0, 1, w)[None, :, None]
    top, bot = np.array([218, 212, 187]), np.array([150, 145, 128])
    col = top + (bot - top) * (0.75 * y + 0.25 * x)
    im = Image.fromarray(np.clip(col, 0, 255).astype(np.uint8), "RGB").convert("RGBA")
    over = Image.new("RGBA", im.size, (0, 0, 0, 0))
    d = ImageDraw.Draw(over)
    step = max(8, h // 10)
    for gx in range(0, w, step):
        d.line((gx, 0, gx, h), fill=(78, 75, 66, 22))
    for gy in range(0, h, step):
        d.line((0, gy, w, gy), fill=(78, 75, 66, 22))
    rng = np.random.default_rng(w * 7919 + h)
    for _ in range(18):
        sx, sy, sz = int(rng.integers(0, w)), int(rng.integers(0, h)), int(rng.integers(step // 4, step // 2 + 1))
        d.rectangle((sx, sy, sx + sz, sy + sz), fill=(78, 75, 66, int(rng.integers(25, 70))))
    for k in (0.12, 0.88):
        d.line((0, int(h * k), w, int(h * k)), fill=(78, 75, 66, 120), width=max(1, h // 160))
    im.alpha_composite(over)
    return im


# per theme: the backdrop, the text colours, the banner's header (the gacha title, or a fixed
# caption), and the panel's art (the chip portrait, or the full figure cc0015_fv01a)
THEMES = {
    # (fill, stroke) of: the banner's names, the panel's name, the small print, "ピックアップ!"
    "beach": {"bg": beach, "head_bg": (20, 60, 120, 200), "head": "ピックアップキャラガチャ", "panel_art": "chip",
              "bname": ((255, 255, 240), (20, 60, 120)), "pname": ((255, 255, 245), (10, 70, 150)),
              "small": ((255, 255, 255), (20, 60, 120)), "accent": ((255, 250, 200), (20, 60, 120))},
    "automata": {"bg": automata, "head_bg": (78, 75, 66, 230), "head": None, "panel_art": "figure",
                 "bname": ((78, 75, 66), (235, 230, 210)), "pname": ((78, 75, 66), (235, 230, 210)),
                 "small": ((60, 57, 50), (225, 220, 200)), "accent": ((150, 40, 40), (235, 230, 210))},
}
GACHA_THEMES = {"gacha_pickup_role_0283": "automata"}


def text(d, xy, s, f, fill=(255, 255, 255), stroke=(20, 60, 120), sw=3, anchor="la"):
    d.text(xy, s, font=f, fill=fill, stroke_width=sw, stroke_fill=stroke, anchor=anchor)


def standin_tag(im, x, y, size):
    d = ImageDraw.Draw(im)
    f = font(size)
    s = "STAND-IN"
    b = d.textbbox((x, y), s, font=f)
    d.rounded_rectangle((b[0] - size // 3, b[1] - size // 4, b[2] + size // 3, b[3] + size // 4), radius=size // 3,
                        fill=(200, 30, 50, 235), outline=(255, 255, 255, 255), width=max(1, size // 8))
    d.text((x, y), s, font=f, fill=(255, 255, 255))


def portrait(chip, size, border=4):
    """The universe-chip portrait scaled, with a white frame and a soft shadow."""
    p = chip.convert("RGBA").resize((size, size), Image.LANCZOS)
    out = Image.new("RGBA", (size + 2 * border + 8, size + 2 * border + 8), (0, 0, 0, 0))
    sh = Image.new("RGBA", out.size, (0, 0, 0, 0))
    ImageDraw.Draw(sh).rounded_rectangle((6, 6, out.size[0] - 1, out.size[1] - 1), radius=size // 8, fill=(0, 30, 60, 120))
    out.alpha_composite(sh.filter(ImageFilter.GaussianBlur(3)))
    ImageDraw.Draw(out).rounded_rectangle((0, 0, size + 2 * border, size + 2 * border), radius=size // 8, fill=(255, 255, 255, 255))
    out.alpha_composite(p, (border, border))
    return out


def rounded_mask(w, h, box, radius):
    m = Image.new("L", (w, h), 0)
    ImageDraw.Draw(m).rounded_rectangle(box, radius=radius, fill=255)
    return m


def date_md(s):
    m = re.match(r"(\d{4})-(\d\d)-(\d\d)", s or "")
    return (m.group(1), m.group(2), m.group(3)) if m else None


def make_banner(w, h, g, chars, theme=THEMES["beach"]):
    """The list banner: the real ones fill about x 55..455, y 14..113 of 512x128 (rounded)."""
    sx, sy = w / 512, h / 128
    box = (int(56 * sx), int(14 * sy), int(456 * sx), int(114 * sy))
    bw, bh = box[2] - box[0], box[3] - box[1]
    im = Image.new("RGBA", (w, h), (0, 0, 0, 0))
    art = theme["bg"](bw, bh, horizon=0.55, sand=0.82)
    x = 6
    for c in chars:
        if c.get("chip") is not None:
            pic = portrait(c["chip"], int(bh * 0.74), 2)
            art.alpha_composite(pic, (x, int(bh * 0.2)))
            x += pic.size[0] - 4
    d = ImageDraw.Draw(art)
    d.rectangle((0, 0, bw, int(bh * 0.19)), fill=theme["head_bg"])
    tag_x = bw - int(bh * 0.62)
    head = theme["head"] or g["name"]
    size = int(bh * 0.15)
    while d.textlength(head, font=font(size)) > tag_x - 14 and size > 8:
        size -= 1
    text(d, (8, 1 + (int(bh * 0.15) - size) // 2), head, font(size), sw=0, fill=(255, 255, 255))
    tx = max(x + 6, int(bw * 0.36))
    names = [c["name"] for c in chars] or [g["name"]]
    f = font(int(bh * (0.2 if len(names) > 1 else 0.24)))
    if len(names) > 2 and theme["head"] is None:  # several short names (２Ｂ ９Ｓ Ａ２): one line
        names = [" ".join(names)]
        size = int(bh * 0.26)
        while d.textlength(names[0], font=font(size)) > bw - tx - 8 and size > 8:
            size -= 1
        f = font(size)
    for k, n in enumerate(names):
        text(d, (tx, int(bh * (0.24 + 0.22 * k))), n, f, fill=theme["bname"][0], stroke=theme["bname"][1], sw=3)
    if theme["head"] is None:
        text(d, (tx, int(bh * 0.55)), "ピックアップ!", font(int(bh * 0.14)), fill=theme["accent"][0], stroke=theme["accent"][1], sw=2)
    o, c = date_md(g["opened_at"]), date_md(g["closed_at"])
    if o and c:
        text(d, (bw - 6, bh - 3), f"{o[0]}/{o[1]}/{o[2]} 〜 {c[1]}/{c[2]}", font(int(bh * 0.13)), fill=(255, 255, 255),
             stroke=(30, 30, 30), sw=2, anchor="rd")
    standin_tag(art, tag_x, int(bh * 0.03), int(bh * 0.1))
    im.paste(art, box[:2])
    alpha = rounded_mask(w, h, box, int(10 * sy))
    frame = ImageDraw.Draw(im)
    frame.rounded_rectangle(box, radius=int(10 * sy), outline=(255, 255, 255, 255), width=2)
    im.putalpha(Image.fromarray(np.minimum(np.array(im)[..., 3], np.array(alpha))))
    return im


def figure(fig, h):
    """A full-figure cut-out (e.g. cc0015_fv01a, transparent around the character) cropped to its
    opaque part and scaled to height h."""
    fig = fig.convert("RGBA")
    box = fig.getchannel("A").point(lambda v: 255 if v > 16 else 0).getbbox() or (0, 0, *fig.size)
    fig = fig.crop(box)
    return fig.resize((max(1, round(fig.width * h / fig.height)), h), Image.LANCZOS)


def make_pickup(w, h, g, c, theme=THEMES["beach"]):
    """A pick-up panel: the real ones fill about x 128..896 of 1024x512."""
    sx = w / 1024
    x0, x1 = int(128 * sx), int(896 * sx)
    bw = x1 - x0
    art = theme["bg"](bw, h)
    d = ImageDraw.Draw(art)
    fill, stroke = theme["small"]
    if theme["panel_art"] == "figure" and c.get("figure") is not None:
        pic = figure(c["figure"], int(h * 0.98))
        art.alpha_composite(pic, (max(0, int(bw * 0.27) - pic.width // 2), h - pic.height))
    elif c.get("chip") is not None:
        pic = portrait(c["chip"], int(h * 0.6), 6)
        art.alpha_composite(pic, (int(bw * 0.05), int(h * 0.16)))
    tx = int(bw * 0.52)
    if theme["head"] is None:  # a light card behind the text column, over the figure's edge
        card = Image.new("RGBA", art.size, (0, 0, 0, 0))
        ImageDraw.Draw(card).rectangle((tx - 16, int(h * 0.06), bw, int(h * 0.97)), fill=(225, 220, 200, 170))
        art.alpha_composite(card)
    stars = "★" + str(c["rarity"]) if c.get("rarity") else ""
    if stars:
        text(d, (tx, int(h * 0.1)), stars, font(int(h * 0.13)), fill=(255, 220, 60), stroke=(150, 60, 0), sw=4)
    if c.get("role"):
        rs = int(h * 0.07)
        while d.textlength(c["role"], font=font(rs)) > bw - tx - int(h * 0.3) - 12 and rs > 10:
            rs -= 1
        text(d, (tx + int(h * 0.3), int(h * 0.14)), c["role"], font(rs), fill=(255, 255, 255), stroke=(20, 60, 120) if theme["head"] else (78, 75, 66), sw=3)
    name = c["name"]
    size = int(h * 0.13)
    f = font(size)
    while d.textlength(name, font=f) > bw - tx - 20 and size > 20:
        size -= 2
        f = font(size)
    text(d, (tx, int(h * 0.3)), name, f, fill=theme["pname"][0], stroke=theme["pname"][1], sw=5)
    text(d, (tx, int(h * 0.5)), "ピックアップ!", font(int(h * 0.07)), fill=theme["accent"][0], stroke=theme["accent"][1], sw=3)
    o, cl = date_md(g["opened_at"]), date_md(g["closed_at"])
    if o and cl:
        text(d, (tx, int(h * 0.62)), f"{o[0]}/{o[1]}/{o[2]} 〜 {cl[1]}/{cl[2]}", font(int(h * 0.05)), fill=fill, stroke=stroke, sw=2)
    if theme["head"] is None:  # the gacha the panel belongs to
        sub = g["name"]
        size = int(h * 0.04)
        while d.textlength(sub, font=font(size)) > bw - tx - 12 and size > 10:
            size -= 1
        text(d, (tx, int(h * 0.71)), sub, font(size), fill=fill, stroke=stroke, sw=2)
    standin_tag(art, tx, int(h * 0.8), int(h * 0.055))
    text(d, (tx, int(h * 0.92)), "代替画像 (original art not in the 3.7.0 data)", font(int(h * 0.032)), fill=fill, stroke=stroke, sw=2)
    im = Image.new("RGBA", (w, h), (0, 0, 0, 0))
    im.paste(art, (x0, 0))
    # soft edges like the real panels (they fade out at the sides)
    a = np.zeros((h, w), np.float32)
    ramp = np.clip(np.minimum(np.arange(w) - x0, x1 - 1 - np.arange(w)) / (24 * sx), 0, 1)
    a[:, :] = ramp[None, :]
    im.putalpha(Image.fromarray((a * 255).astype(np.uint8)))
    return im


# ---------------------------------------------------------------- data
def find_db(path):
    cands = [path] if path else []
    cands.append(os.path.join(ROOT, "data", "basmaster-3.7.0.sqlite3"))
    try:
        common = subprocess.run(["git", "-C", ROOT, "rev-parse", "--path-format=absolute", "--git-common-dir"],
                                capture_output=True, text=True, check=True).stdout.strip()
        cands.append(os.path.join(os.path.dirname(common), "data", "basmaster-3.7.0.sqlite3"))
    except (subprocess.CalledProcessError, FileNotFoundError):
        pass
    for c in cands:
        if c and os.path.isfile(c) and os.path.getsize(c) > 0:
            return c
    sys.exit("basmaster-3.7.0.sqlite3 not found (use --db)")


def decode_png(src, asset, tmp):
    out = os.path.join(tmp, os.path.basename(asset) + ".png")
    r = subprocess.run([AIF2PNG, src, asset, out], capture_output=True, text=True)
    if not r.stdout.startswith("ok"):
        raise RuntimeError(r.stdout + r.stderr)
    return Image.open(out).convert("RGBA")


class Sources:
    """Where real Image/etc2 assets are: the download, then the APK asset pack."""

    def __init__(self, download, apks):
        self.dir = os.path.join(download, "Image", "etc2")
        self.names = {f[:-4] for f in os.listdir(self.dir) if f.endswith(".aif")} if os.path.isdir(self.dir) else set()
        self.apk_names = set()
        import zipfile
        for apk in apks:
            if os.path.exists(apk):
                with zipfile.ZipFile(apk) as z:
                    for n in z.namelist():
                        m = re.fullmatch(r"assets/(?:assetpack|builtin_data)/Image/(?:etc2/(?:hi/)?)?(.+)\.aif", n)
                        if m:
                            self.apk_names.add(m.group(1))

    def has(self, name):
        return name in self.names or name in self.apk_names

    def path(self, name):
        return os.path.join(self.dir, name + ".aif") if name in self.names else None


def load_gacha(db, label):
    c = sqlite3.connect(f"file:{db}?mode=ro", uri=True)
    c.row_factory = sqlite3.Row
    g = c.execute("select * from master_gacha where id_label = ?", (label,)).fetchone()
    if not g:
        sys.exit(f"no master_gacha row {label}")
    g = dict(g)
    t = c.execute("select text_value from master_text where message_id = ?", (g["name_message_id"],)).fetchone()
    g["name"] = t[0] if t else label
    b = c.execute("select image from master_banner where id_label = ?", (g["banner_id"] or "",)).fetchone()
    g["banner"] = b[0] if b and b[0] else None

    def char(cp, name=None):
        """A pick-up: its name (<cp>_message unless given), lowest rarity and role type."""
        ch = {"cp": cp}
        if name is None:
            t = c.execute("select text_value from master_text where message_id = ?", (f"{cp}_message",)).fetchone()
            name = t[0] if t else cp
        ch["name"] = name
        r = c.execute("select min(r.rarity), t.text_value from master_role r left join master_text t on t.message_id = r.name_message_id "
                      "where r.id_label like ?", (f"role_{cp}_%",)).fetchone()
        if r and r[0]:
            ch["rarity"], ch["role"] = r[0], r[1]
        return ch

    # the pick-ups named in the title's brackets (as the gacha pools' R-PU-NAME rule does)
    m = re.search(r"[(（](.+)[)）]", g["name"])
    chars = []
    for n in (m.group(1).split("/") if m else []):
        ch = {"name": n}
        for (mid,) in c.execute("select message_id from master_text where text_value = ? and message_id like 'cp%_message'", (n,)):
            ch = char(mid[:-len("_message")], n)
            break
        chars.append(ch)
    # the master_gacha_image rows: a panel each, showing the role of its content_id_label
    rows = [(r[0], r[1] or "") for r in c.execute("select image_resource, content_id_label from master_gacha_image "
                                                  "where master_gacha_id = ? order by view_index, id", (g["id"],)) if r[0]]
    row_chars = []
    for _, role in rows:
        mm = re.fullmatch(r"role_([a-z]{2}\d{4}_[a-z]\d\d[a-z])_\d+", role)
        row_chars.append(char(mm.group(1)) if mm else None)
    if not chars:  # no names in the title: the panels' roles are the pick-ups
        chars = [ch for ch in row_chars if ch]
    # every panel with the character it shows: image1..4 in title order, the rows their own role
    fixed = [g[k] for k in ("image1", "image2", "image3", "image4") if g[k]]
    g["panels"] = [(p, chars[k] if k < len(chars) else None) for k, p in enumerate(fixed)]
    g["panels"] += [(p, ch or (chars[k] if k < len(chars) else None)) for k, ((p, _), ch) in enumerate(zip(rows, row_chars), len(fixed))]
    g["chars"] = chars
    return g


def template(src, prefix, tmp):
    """The first real image named <prefix>* with a readable ETC2 RGBA8 container."""
    for n in sorted(src.names):
        if not n.startswith(prefix):
            continue
        try:
            d = read_aif(src.path(n), f"Image/etc2/{n}.aif")
            fmt, w, h, data, guids = image_layout(d)
        except (ValueError, RuntimeError, struct.error, TypeError):
            continue
        if fmt == 49 and data and data[1] == ((w + 3) // 4) * ((h + 3) // 4) * 16:
            return n, d, w, h, data, guids
    sys.exit(f"no ETC2 RGBA8 template image {prefix}* in the download")


def build(name, pic, tpl):
    tname, d, w, h, (off, size), guids = tpl
    d = bytearray(d)
    for gd in guids:  # fresh GUIDs (deterministic per name): not the template's identity
        new = hashlib.md5(f"{name}:{gd.hex()}".encode()).digest()
        d = bytearray(bytes(d).replace(gd, new))
    # the image header's +0x10 u32 is a per-texture id, unique across the real files (0x1e100 ..
    # ~0x760000, multiples of 0x100); the client caches textures by it (two stand-ins sharing the
    # template's id showed the same picture), so give each a distinct one above the real range
    img = find16(d, b"Xgmi", 0, len(d))
    tex_id = 0xF00000 | (int.from_bytes(hashlib.md5(name.encode()).digest()[:2], "little") & 0xfff) << 8
    struct.pack_into("<I", d, img + 0x10, tex_id)
    pix = encode_etc2_rgba8(pic)
    assert len(pix) == size
    d[off:off + size] = pix
    return write_aif(bytes(d), f"Image/etc2/{name}.aif")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("gachas", nargs="*", default=DEFAULT_GACHAS, help="master_gacha id_labels")
    ap.add_argument("--db")
    ap.add_argument("--download", default=os.path.join(ROOT, "work", "download-3.7.0"))
    ap.add_argument("--apk", default=os.path.join(ROOT, "apk", "STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk"), help="the APK whose Image/ assets count as real (the 3.7.0 APK)")
    ap.add_argument("--out", default=os.path.join(ROOT, "standin-assets"))
    ap.add_argument("--png", help="also write the source pictures as PNG here")
    ap.add_argument("--force", action="store_true", help="also replace images a real source has (never needed)")
    a = ap.parse_args()
    if not os.path.exists(AIF2PNG) or os.path.getmtime(AIF2PNG) < os.path.getmtime(AIF2PNG + ".cpp"):
        subprocess.run([os.path.join(ROOT, "tools", "aif2png", "build.sh")], check=True)
    db = find_db(a.db)
    src = Sources(a.download, [a.apk])
    out_dir = os.path.join(a.out, "Image", "etc2")
    os.makedirs(out_dir, exist_ok=True)
    tmp = tempfile.mkdtemp(prefix="standin-")
    tpls = {}
    for label in a.gachas:
        g = load_gacha(db, label)
        theme = THEMES[GACHA_THEMES.get(label, "beach")]
        for ch in g["chars"] + [ch for _, ch in g["panels"] if ch]:
            if "chip" in ch:
                continue
            # the figure art is named per costume: cc0015_b01a -> cc0015_fv01a
            chip, fig = f"u_chip_{ch.get('cp', '')}", re.sub(r"_b(\d\d[a-z])$", r"_fv\1", ch.get("cp", ""))
            ch["chip"] = decode_png(src.path(chip), f"Image/etc2/{chip}.aif", tmp) if src.path(chip) else None
            if theme["panel_art"] == "figure":
                ch["figure"] = decode_png(src.path(fig), f"Image/etc2/{fig}.aif", tmp) if src.path(fig) else None
        jobs = []
        if g["banner"]:
            jobs.append((g["banner"], lambda w, h: make_banner(w, h, g, g["chars"], theme)))
        for p, ch in g["panels"]:
            ch = ch or {"name": g["name"]}
            jobs.append((p, lambda w, h, ch=ch: make_pickup(w, h, g, ch, theme)))
        for name, draw in jobs:
            if src.has(name) and not a.force:
                print(f"{label}: {name} exists in the real data, skipped")
                continue
            prefix = re.sub(r"[\d_]+$", "", name) + "_"
            if prefix not in tpls:
                tpls[prefix] = template(src, prefix, tmp)
            tpl = tpls[prefix]
            pic = draw(tpl[2], tpl[3])
            blob = build(name, pic, tpl)
            path = os.path.join(out_dir, name + ".aif")
            with open(path, "wb") as fh:
                fh.write(blob)
            if a.png:
                os.makedirs(a.png, exist_ok=True)
                pic.save(os.path.join(a.png, name + ".png"))
            # round trip: decode with tools/aif2png and compare
            back = np.array(decode_png(path, f"Image/etc2/{name}.aif", tmp)).astype(np.int32)
            ref = np.array(pic).astype(np.int32)
            vis = ref[..., 3] > 0
            rmse = float(np.sqrt(((back[..., :3] - ref[..., :3])[vis] ** 2).mean()))
            amax = int(np.abs(back[..., 3] - ref[..., 3]).max())
            print(f"{label}: {name}.aif {tpl[2]}x{tpl[3]} (template {tpl[0]}) {len(blob)} bytes, round trip RGB rmse {rmse:.1f}, alpha max err {amax}")
            if rmse > 20 or amax > 40:
                sys.exit(f"{name}: round trip too far off")


if __name__ == "__main__":
    main()
