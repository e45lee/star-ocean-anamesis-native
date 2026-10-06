#!/usr/bin/env python3
"""Checks the reconstructed gacha pick-ups (data/gacha_pools.sqlite3) against the banner images.

Every character banner of STAR OCEAN: anamnesis is composited from the characters' own illustrations
(Image/etc2/<person>_fl<costume>.aif, the full illustration with alpha, and _cs, the card art). So
"which characters does this banner show" is a same-source image-matching problem: SIFT keypoints of
the banner are matched against every illustration (one FLANN index, Lowe's ratio test), the matches
are grouped by illustration, and each candidate is verified geometrically with a RANSAC similarity
transform (cv2.estimateAffinePartial2D: scale + rotation + translation, no shear), plus a scale and
an inlier-ratio check. Overlapping detections are suppressed by their projected boxes.

Characters are compared by their art key, `<person>_b<NN><x>` (master_role.master_person_id_label
up to the costume letter, e.g. cp0002_b10a): every role of one costume shares one illustration
(rarity 5 and its rarity-6 evolution, the 歌星 idol2020 variants).

Per gacha (master_gacha), the images are the list banner (master_gacha.banner_id -> master_banner
.image, 512x128), image1..4, and the pick-up panels (master_gacha_image, 1024x512). The detections
over all of them are compared with gacha_pickup and with the gacha's S/A pools.

Calibration: master_gacha_image rows with content_type 2 name the role their panel shows; the
precision / recall on those panels are measured first and printed (and written to the report).

Usage:
  tools/gacha_verify.py [--master data/basmaster-3.7.0.sqlite3] [--download work/download-3.7.0]
                        [--pools data/gacha_pools.sqlite3] [--gl data/basmaster-gl.sqlite3]
                        [--apk apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk]
                        [--out work/gacha-verify] [--report docs/gacha-verify.md] [-j N]
Output (under --out; derived game images, never committed):
  png/            decoded banners and illustrations (tools/aif2png)
  feat/           cached SIFT features (npz)
  detections.json every image's detections; results.json every gacha's classification
  sheets/         a contact sheet per mismatching banner group
Needs opencv-python-headless, numpy, pillow (requirements.txt) and tools/aif2png.
"""
import argparse
import collections
import json
import multiprocessing as mp
import os
import re
import sqlite3
import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)

ART_KEY = re.compile(r"(c[a-z]\d+)_b(\d+)([a-z])")
REF_KINDS = ("fl", "cs")  # full illustration (alpha-masked), card art
PERMANENT_TABLES = {"master_gacha_item_jousetu", "master_gacha_item_sphere211", "master_gacha_item_galaxy"}

# Detector parameters (tuned on the calibration panels; see the report).
RATIO = 0.75          # Lowe's ratio test
MIN_MATCHES = 6       # candidate illustrations need this many ratio-test matches
MIN_INLIERS = 6       # recorded in detections.json; accepted per image size by ACCEPT below
MIN_INLIER_FRAC = 0.15
# accepted detections: RANSAC inliers >= ACCEPT[size class] (list banner 512x128, panel 1024x512)
ACCEPT = {"list": 8, "panel": 10}
SCALE_RANGE = (0.08, 4.0)
RANSAC_PX = 6.0       # reprojection threshold, in query pixels (panel scale)
REF_MAX_SIDE = 768    # illustrations are resized to this before SIFT
REF_MAX_FEATURES = 1500
QUERY_SMALL_UPSCALE = 3  # the 512x128 list banners are upscaled before SIFT


def art_key(person_label):
    m = ART_KEY.match(person_label or "")
    return f"{m[1]}_b{m[2]}{m[3]}" if m else None


def ref_names(key):
    m = ART_KEY.fullmatch(key)
    return {k: f"{m[1]}_{k}{m[2]}{m[3]}" for k in REF_KINDS}


# ---------------------------------------------------------------- features

def _cv2():
    import cv2
    return cv2


def root_sift(desc):
    """RootSIFT (Arandjelovic & Zisserman 2012): L1-normalise, square root."""
    if desc is None or len(desc) == 0:
        return np.zeros((0, 128), np.float32)
    desc = desc / (np.abs(desc).sum(axis=1, keepdims=True) + 1e-7)
    return np.sqrt(desc).astype(np.float32)


def features(img_bgra, mask=None, max_side=None, upscale=1, nfeatures=0):
    """SIFT keypoints (x, y in the input image's pixels) and RootSIFT descriptors."""
    cv2 = _cv2()
    img = img_bgra
    if img.ndim == 3 and img.shape[2] == 4:
        if mask is None:
            mask = (img[:, :, 3] > 128).astype(np.uint8) * 255
        img = img[:, :, :3]
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY) if img.ndim == 3 else img
    s = 1.0
    h, w = gray.shape
    if max_side and max(h, w) > max_side:
        s = max_side / max(h, w)
    elif upscale != 1:
        s = float(upscale)
    if s != 1.0:
        gray = cv2.resize(gray, (round(w * s), round(h * s)), interpolation=cv2.INTER_AREA if s < 1 else cv2.INTER_CUBIC)
        if mask is not None:
            mask = cv2.resize(mask, (gray.shape[1], gray.shape[0]), interpolation=cv2.INTER_NEAREST)
    if mask is not None:
        mask = cv2.erode(mask, np.ones((5, 5), np.uint8))
    sift = cv2.SIFT_create(nfeatures=nfeatures)
    kps, desc = sift.detectAndCompute(gray, mask)
    pts = np.array([k.pt for k in kps], np.float32).reshape(-1, 2) / s
    return pts, root_sift(desc)


def load_bgra(path):
    cv2 = _cv2()
    img = cv2.imread(path, cv2.IMREAD_UNCHANGED)
    if img is None:
        raise IOError(f"cannot read {path}")
    if img.ndim == 2:
        img = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
    return img


class Matcher:
    """References (name -> points, descriptors, size) in one FLANN index; detect() on a query."""

    def __init__(self, refs):
        cv2 = _cv2()
        self.names = sorted(refs)
        self.pts, self.size, descs, owner = [], [], [], []
        for i, n in enumerate(self.names):
            p, d, sz = refs[n]
            self.pts.append(p)
            self.size.append(sz)
            descs.append(d)
            owner.append(np.full(len(d), i, np.int32))
        self.desc = np.concatenate(descs) if descs else np.zeros((0, 128), np.float32)
        self.owner = np.concatenate(owner) if owner else np.zeros(0, np.int32)
        self.offset = np.cumsum([0] + [len(d) for d in descs])
        self.flann = cv2.FlannBasedMatcher(dict(algorithm=1, trees=6), dict(checks=96))
        self.flann.add([self.desc])
        self.flann.train()

    def detect(self, qpts, qdesc):
        """[{ref, inliers, matches, scale, box}] verified, overlap-suppressed, best first."""
        cv2 = _cv2()
        if len(qdesc) < 2 or len(self.desc) < 2:
            return []
        knn = self.flann.knnMatch(qdesc, k=2)
        by_ref = collections.defaultdict(list)
        for m in knn:
            if len(m) < 2 or m[0].distance >= RATIO * m[1].distance:
                continue
            t = m[0].trainIdx
            by_ref[int(self.owner[t])].append((m[0].queryIdx, t))
        cands = sorted(by_ref.items(), key=lambda kv: -len(kv[1]))[:25]
        found = []
        for ri, pairs in cands:
            if len(pairs) < MIN_MATCHES:
                break
            q = np.array([qpts[a] for a, _ in pairs], np.float32)
            r = np.array([self.pts[ri][b - self.offset[ri]] for _, b in pairs], np.float32)
            M, inl = cv2.estimateAffinePartial2D(r, q, method=cv2.RANSAC, ransacReprojThreshold=RANSAC_PX,
                                                 maxIters=4000, confidence=0.995)
            if M is None:
                continue
            n_in = int(inl.sum())
            scale = float(np.hypot(M[0, 0], M[1, 0]))
            if n_in < MIN_INLIERS or n_in < MIN_INLIER_FRAC * len(pairs):
                continue
            if not SCALE_RANGE[0] <= scale <= SCALE_RANGE[1]:
                continue
            # the box of the inlying reference points, projected into the query
            rin = r[inl.ravel() == 1]
            x0, y0 = rin.min(axis=0)
            x1, y1 = rin.max(axis=0)
            corners = np.array([[x0, y0], [x1, y0], [x1, y1], [x0, y1]], np.float32)
            proj = corners @ M[:, :2].T + M[:, 2]
            box = [float(proj[:, 0].min()), float(proj[:, 1].min()), float(proj[:, 0].max()), float(proj[:, 1].max())]
            found.append(dict(ref=self.names[ri], inliers=n_in, matches=len(pairs), scale=round(scale, 3),
                              box=[round(v, 1) for v in box]))
        found.sort(key=lambda d: -d["inliers"])
        keep = []
        for d in found:  # one figure, one illustration: suppress overlapping weaker ones
            if any(overlap(d["box"], k["box"]) > 0.5 and art_of_ref(d["ref"]) != art_of_ref(k["ref"]) for k in keep):
                continue
            keep.append(d)
        return keep


def overlap(a, b):
    """Intersection over the smaller box."""
    ix = max(0.0, min(a[2], b[2]) - max(a[0], b[0]))
    iy = max(0.0, min(a[3], b[3]) - max(a[1], b[1]))
    area = min((a[2] - a[0]) * (a[3] - a[1]), (b[2] - b[0]) * (b[3] - b[1]))
    return ix * iy / area if area > 0 else 0.0


def art_of_ref(ref):
    """cp0002_fl10a -> cp0002_b10a"""
    m = re.fullmatch(r"(c[a-z]\d+)_[a-z]{2}(\d+)([a-z])", ref)
    return f"{m[1]}_b{m[2]}{m[3]}" if m else ref


# ---------------------------------------------------------------- data

class Master:
    def __init__(self, master, pools, gl):
        import extract_banners
        self.gachas = extract_banners.load_gachas(master)
        c = sqlite3.connect(f"file:{master}?mode=ro", uri=True)
        self.text = dict(c.execute("select message_id, text_value from master_text"))
        self.role = {}
        for rid, label, person, cat, rarity, rank, msg in c.execute(
                "select id, id_label, master_person_id_label, role_category_id, rarity, rank, name_message_id "
                "from master_role"):
            self.role[rid] = dict(id=rid, label=label, art=art_key(person), person=person, cat=cat, rarity=rarity, rank=rank)
        self.art_of_label = {r["label"]: r["art"] for r in self.role.values()}
        self.person_name = {}
        for label, msg in c.execute("select id_label, name_message_id from master_person"):
            self.person_name[label] = self.text.get(msg, "").strip()
        self.box_roles = collections.defaultdict(set)
        for gid, cid in c.execute("select master_gacha_id, content_id from master_box_gacha where content_type = 2"):
            if cid in self.role:
                self.box_roles[gid].add(cid)
        self.table = dict(c.execute("select id, table_name from master_gacha"))
        self.en = {}
        if gl and os.path.exists(gl):
            g = sqlite3.connect(f"file:{gl}?mode=ro", uri=True)
            en_text = dict(g.execute("select message_id, text_value from master_text where lang = 'en'"))
            for label, msg in g.execute("select id_label, name_message_id from master_person"):
                if msg in en_text:
                    self.en[label] = en_text[msg].strip()
        p = sqlite3.connect(f"file:{pools}?mode=ro", uri=True)
        self.pg = {r[0]: dict(kind=r[1], source=r[2], name=r[3]) for r in
                   p.execute("select gacha_id, kind, pickup_source, name from gacha")}
        self.pickup = collections.defaultdict(list)
        for gid, ct, cid, src in p.execute("select gacha_id, content_type, content_id, source from gacha_pickup"):
            self.pickup[gid].append((ct, cid, src))
        sets = collections.defaultdict(set)
        for sid, ct, cid in p.execute("select set_id, content_type, content_id from pool_set where content_type = 2"):
            sets[sid].add(cid)
        self.rank_pool = collections.defaultdict(dict)
        for gid, rank, sid in p.execute("select gacha_id, rank, set_id from gacha_rank where set_id is not null"):
            self.rank_pool[gid][rank] = sets.get(sid, set())

    def name(self, art):
        """English name of an art key (the global client's text), else the base name + the JP name."""
        if art in self.en:
            return self.en[art]
        jp = self.person_name.get(art, "")
        base = self.en.get(re.sub(r"_b\d+[a-z]$", "_b01a", art))
        if base:
            return f"{base} ({jp})" if jp and jp != base else base
        return jp or art

    def art_keys(self):
        """Every art key of a role (playable characters and NPC roles alike)."""
        return sorted({r["art"] for r in self.role.values() if r["art"]})


# ---------------------------------------------------------------- decode + features (cached)

def decode(jobs, workers):
    """jobs: [(aif path, png path)] -> decoded (skips existing PNGs)."""
    import extract_banners
    todo = [(s, "Image/etc2/" + os.path.basename(s), o) for s, o in jobs if not os.path.exists(o)]
    for _, _, o in todo:
        os.makedirs(os.path.dirname(o), exist_ok=True)
    if todo:
        res = extract_banners.run_batches(todo, workers)
        bad = [s for s, (ok, _) in res.items() if not ok]
        if bad:
            print(f"warning: {len(bad)} images failed to decode, e.g. {bad[:3]}", file=sys.stderr)


def _feat_job(args):
    png, npz, kind = args
    if os.path.exists(npz):
        return npz
    img = load_bgra(png)
    if kind == "ref":
        pts, desc = features(img, max_side=REF_MAX_SIDE, nfeatures=REF_MAX_FEATURES)
    else:
        up = QUERY_SMALL_UPSCALE if img.shape[0] <= 200 else 1
        pts, desc = features(img, upscale=up)
    np.savez_compressed(npz, pts=pts, desc=desc.astype(np.float16), size=np.array(img.shape[:2]))
    return npz


def load_feat(npz):
    z = np.load(npz)
    return z["pts"], z["desc"].astype(np.float32), tuple(int(v) for v in z["size"])


_MATCHER = None


def _detect_job(args):
    name, npz = args
    pts, desc, size = load_feat(npz)
    return name, size, _MATCHER.detect(pts, desc)


# ---------------------------------------------------------------- comparison

def size_class(info):
    return "list" if info["size"][0] <= 200 else "panel"


def accepted(info):
    """{art key: best inliers} of one image's detections that pass ACCEPT."""
    out = {}
    th = ACCEPT[size_class(info)]
    for d in info["detections"]:
        if d["inliers"] >= th:
            a = art_of_ref(d["ref"])
            out[a] = max(out.get(a, 0), d["inliers"])
    return out


def gacha_images(m, g, det_by_image):
    """[(slot, image, content art or None)] of the images present; [image] of those missing."""
    have, missing = [], []
    for slot, n, extra in g["refs"]:
        if n not in det_by_image:
            missing.append(n)
            continue
        content = m.art_of_label.get(extra) if slot.startswith("pickup") and extra else None
        have.append((slot, n, content))
    return have, missing


def classify(m, g, det_by_image):
    """One gacha -> dict(status, detected, recorded, missing, extra, ...)."""
    gid = g["id"]
    pg = m.pg.get(gid, {})
    kind = pg.get("kind")
    imgs, missing_imgs = gacha_images(m, g, det_by_image)
    det = {}
    for _, n, _ in imgs:
        for a, k in accepted(det_by_image[n]).items():
            if k > det.get(a, (0, ""))[0]:
                det[a] = (k, n)
    if kind == "role":
        rec = sorted({m.role[cid]["art"] for ct, cid, _ in m.pickup.get(gid, []) if ct == 2 and cid in m.role})
    elif kind == "box":
        rec = sorted({m.role[c]["art"] for c in m.box_roles.get(gid, ())})
    else:
        rec = []
    pools = m.rank_pool.get(gid, {})

    def where(a):
        for rank in ("S", "A", "B", "C"):
            if any(m.role[c]["art"] == a for c in pools.get(rank, ()) if c in m.role):
                return rank
        return "-"

    detected = sorted(det, key=lambda a: -det[a][0])
    missing = [a for a in detected if a not in rec]
    extra = [a for a in rec if a not in det]
    # An extra (recorded, not seen) is judged only where the images are complete: every image of the
    # gacha is present, or its first pick-up panel (pickup1: the main panel that shows every pick-up)
    # is. The list banner alone has a lower recall (see the calibration), and the older banners (image1..4) have
    # one panel per pick-up, some of them lost.
    main_panel = any(slot == "pickup1" and c is None and size_class(det_by_image[n]) == "panel"
                     for slot, n, c in imgs)
    complete = main_panel or (not missing_imgs and any(size_class(det_by_image[n]) == "panel" for _, n, _ in imgs))
    if kind == "weapon":
        status = "weapon (not checked)"
    elif not imgs:
        status = "banner not available"
    elif kind == "box":
        status = "box (detections listed)"
    elif m.table.get(gid) in PERMANENT_TABLES:
        status = "permanent showcase"
    elif not det:
        status = "inconclusive"
    elif missing and extra and complete:
        status = "mismatch (both)"
    elif missing:
        status = "missing from pickup"
    elif extra and complete:
        status = "extra in pickup"
    elif extra:
        status = "inconclusive"
    else:
        status = "confirmed"
    person = lambda a: a.split("_")[0]  # noqa: E731
    return dict(gacha_id=gid, id_label=g["id_label"], name=g["name"], kind=kind, opened_at=g["opened_at"],
                closed_at=g["closed_at"], banner_id=g["banner_id"], pickup_source=pg.get("source"),
                is_stepup=g["is_stepup"], images=[n for _, n, _ in imgs], missing_images=missing_imgs,
                main_panel=main_panel, complete=complete, detected=detected, inliers={a: det[a][0] for a in detected},
                seen_on={a: det[a][1] for a in detected}, recorded=rec, missing=missing, extra=extra,
                detected_in={a: where(a) for a in detected},
                costume_swaps=sorted({(x, y) for x in missing for y in extra if person(x) == person(y)}),
                status=status)


def calibration(m, det_by_image):
    """Precision / recall per image class against labelled ground truth, per inlier threshold."""
    sets = collections.defaultdict(dict)  # set name -> {image: truth arts}
    for g in m.gachas:
        imgs, _ = gacha_images(m, g, det_by_image)
        for slot, n, content in imgs:
            if content:
                sets["named panel"].setdefault(n, set()).add(content)
        pg = m.pg.get(g["id"], {})
        if pg.get("kind") == "role" and pg.get("source") in ("R-PU-IMAGE", "R-PU-GROUP"):
            rec = {m.role[cid]["art"] for ct, cid, _ in m.pickup[g["id"]] if ct == 2 and cid in m.role}
            for slot, n, content in imgs:
                if content is None:
                    name = "list banner" if size_class(det_by_image[n]) == "list" else "main panel"
                    sets[name].setdefault(n, set()).update(rec)
    out = {}
    for name, truth in sets.items():
        rows = []
        for th in (6, 8, 10, 12, 15, 20):
            tp = fn = other = 0
            for n, t in truth.items():
                d = {art_of_ref(x["ref"]) for x in det_by_image[n]["detections"] if x["inliers"] >= th}
                tp, fn, other = tp + len(t & d), fn + len(t - d), other + len(d - t)
            rows.append(dict(threshold=th, tp=tp, fn=fn, other=other))
        cls = "list" if name == "list banner" else "panel"
        out[name] = dict(images=len(truth), accept=ACCEPT[cls], rows=rows,
                         misses=sorted((n, sorted(t - set(accepted(det_by_image[n])))) for n, t in truth.items()
                                       if t - set(accepted(det_by_image[n]))),
                         others=sorted((n, sorted(set(accepted(det_by_image[n])) - t)) for n, t in truth.items()
                                       if set(accepted(det_by_image[n])) - t))
    # negative control: the weapon banners (no character expected)
    weapon = [n for n in det_by_image if "weapon" in n]
    out["weapon banners (negative control)"] = dict(
        images=len(weapon), detections=sum(len(accepted(det_by_image[n])) for n in weapon),
        raw=sum(len(det_by_image[n]["detections"]) for n in weapon))
    return out


ISSUES = ("mismatch (both)", "missing from pickup", "extra in pickup")
STATUS_ORDER = ("confirmed", "missing from pickup", "extra in pickup", "mismatch (both)", "inconclusive",
                "banner not available", "permanent showcase", "box (detections listed)", "weapon (not checked)")


def groups(results, statuses):
    """Gachas with the same images and the same outcome, one group (step-ups, single / 10-draw)."""
    by = collections.OrderedDict()
    for r in sorted(results, key=lambda r: (r["opened_at"] or "", r["id_label"])):
        if r["status"] not in statuses:
            continue
        k = (r["status"], tuple(r["images"]), tuple(r["detected"]), tuple(r["recorded"]))
        by.setdefault(k, []).append(r)
    return list(by.values())


def sheet_name(rs):
    return re.sub(r"[^A-Za-z0-9_.-]", "_", rs[0]["id_label"]) + ".png"


def contact_sheets(m, results, det_by_image, png, out_dir):
    """One sheet per mismatching group: the images with their detections, then the icons of the
    recorded (green: seen, red: not seen) and the detected-but-not-recorded characters (orange)."""
    from PIL import Image, ImageDraw, ImageFont
    os.makedirs(out_dir, exist_ok=True)
    font = None
    for f in ("/usr/share/fonts/opentype/ipaexfont-gothic/ipaexg.ttf", "/usr/share/fonts/opentype/ipafont-gothic/ipag.ttf"):
        if os.path.exists(f):
            font = ImageFont.truetype(f, 16)
            break
    font = font or ImageFont.load_default()
    n_written = 0
    for rs in groups(results, ISSUES + ("inconclusive",)):
        r = rs[0]
        tiles = []
        for n in r["images"]:
            im = Image.open(os.path.join(png, n + ".png")).convert("RGB")
            f = 2 if im.height <= 200 else 1
            if f != 1:
                im = im.resize((im.width * f, im.height * f))
            d = ImageDraw.Draw(im)
            acc = accepted(det_by_image[n])
            for x in det_by_image[n]["detections"]:
                a = art_of_ref(x["ref"])
                if a not in acc or x["inliers"] < ACCEPT[size_class(det_by_image[n])]:
                    continue
                b = [v * f for v in x["box"]]
                col = (40, 220, 40) if a in r["recorded"] else (255, 140, 0)
                d.rectangle(b, outline=col, width=3)
                d.text((b[0] + 4, b[1] + 4), f"{a} {m.name(a)} ({x['inliers']})", fill=col, font=font,
                       stroke_width=2, stroke_fill=(0, 0, 0))
            d.text((6, im.height - 22), n, fill=(255, 255, 255), font=font, stroke_width=2, stroke_fill=(0, 0, 0))
            tiles.append(im)
        icons = []
        for a, col in [(a, (40, 220, 40) if a in r["detected"] else (230, 40, 40)) for a in r["recorded"]] + \
                      [(a, (255, 140, 0)) for a in r["missing"]]:
            p = os.path.join(png, ref_names(a)["fl"].replace("_fl", "_ic") + ".png")
            ic = Image.new("RGB", (128, 150), (30, 30, 30))
            if os.path.exists(p):
                ic.paste(Image.open(p).convert("RGB").resize((120, 120)), (4, 4))
            dd = ImageDraw.Draw(ic)
            dd.rectangle([0, 0, 127, 127], outline=col, width=4)
            dd.text((2, 130), a, fill=col, font=font)
            icons.append(ic)
        W = max([t.width for t in tiles] + [min(len(icons), 8) * 130])
        H = sum(t.height for t in tiles) + 40 + ((len(icons) + 7) // 8) * 152
        sheet = Image.new("RGB", (W, H), (20, 20, 20))
        d = ImageDraw.Draw(sheet)
        d.text((6, 8), f"{r['status']}: {r['id_label']} (+{len(rs) - 1}) {r['name'][:50]}", fill=(255, 255, 255), font=font)
        y = 40
        for t in tiles:
            sheet.paste(t, (0, y))
            y += t.height
        for i, ic in enumerate(icons):
            sheet.paste(ic, ((i % 8) * 130, y + (i // 8) * 152))
        sheet.save(os.path.join(out_dir, sheet_name(rs)))
        n_written += 1
    return n_written


# ---------------------------------------------------------------- report

def print_summary(cal, results):
    c = collections.Counter(r["status"] for r in results)
    for s in STATUS_ORDER:
        print(f"  {s:28s} {c.get(s, 0)}")
    for name, v in cal.items():
        if "rows" in v:
            row = next(x for x in v["rows"] if x["threshold"] == v["accept"]) if v["accept"] in (6, 8, 10, 12, 15, 20) else v["rows"][0]
            print(f"  calibration {name}: {v['images']} images, tp {row['tp']} fn {row['fn']} other {row['other']} "
                  f"at >= {v['accept']} inliers")
        else:
            print(f"  calibration {name}: {v['images']} images, {v['detections']} detections")


def md_names(m, arts, tag=None):
    return ", ".join(f"{m.name(a)} `{a}`" + (f" ({tag[a]})" if tag else "") for a in arts) or "-"


def write_report(m, cal, results, path, out):
    """The generated part of docs/gacha-verify.md, between the GENERATED markers."""
    L = []
    c = collections.Counter(r["status"] for r in results)
    kinds = collections.Counter((r["kind"], r["status"]) for r in results)
    L.append("| status | gachas | role | box | weapon | banner groups |")
    L.append("|---|---:|---:|---:|---:|---:|")
    for s in STATUS_ORDER:
        L.append(f"| {s} | {c.get(s, 0)} | {kinds.get(('role', s), 0)} | {kinds.get(('box', s), 0)} | "
                 f"{kinds.get(('weapon', s), 0)} | {len(groups(results, (s,)))} |")
    L.append(f"| **total** | {len(results)} | | | | |")
    L.append("")
    L.append("**Measured accuracy** (detections accepted at the threshold in bold; tp = a labelled character "
             "found, fn = missed, other = a character found that the label doesn't name):")
    L.append("")
    L.append("| ground truth | images | " + " | ".join(f">= {t}" for t in (6, 8, 10, 12, 15, 20)) + " |")
    L.append("|---|---:|" + "---|" * 6)
    for name, v in cal.items():
        if "rows" not in v:
            continue
        cells = []
        for x in v["rows"]:
            cell = f"{x['tp']}/{x['tp'] + x['fn']} +{x['other']}"
            cells.append(f"**{cell}**" if x["threshold"] == v["accept"] else cell)
        L.append(f"| {name} | {v['images']} | " + " | ".join(cells) + " |")
    neg = cal["weapon banners (negative control)"]
    L.append("")
    L.append(f"Cells are recall `tp/(tp+fn)` and `+other`. Negative control: {neg['images']} weapon banners, "
             f"{neg['raw']} raw detections (>= {MIN_INLIERS} inliers), {neg['detections']} accepted.")
    for name in ("named panel", "main panel", "list banner"):
        v = cal.get(name)
        if not v:
            continue
        if v["misses"]:
            L.append(f"- {name}, missed: " + "; ".join(f"`{n}`: {md_names(m, a)}" for n, a in v["misses"]))
        if v["others"]:
            L.append(f"- {name}, other: " + "; ".join(f"`{n}`: {md_names(m, a)}" for n, a in v["others"]))
    L.append("")
    L.append("### Mismatches")
    L.append("")
    L.append("One row per banner (gachas with the same images and outcome: the steps of a step-up, single / "
             "10-draw variants, reruns under one banner). *Detected, not recorded* lists each character with "
             "the rank of this gacha's pools that holds it (S, A, B, C, or - for none). Sheets: "
             f"`{os.path.relpath(os.path.join(out, 'sheets'), ROOT) if out.startswith(ROOT) else out}/<first id>.png`; "
             "images `png/<name>.png` beside them.")
    L.append("")
    L.append("| status | opened | gachas | title | source | images | detected, not recorded | recorded, not seen | sheet |")
    L.append("|---|---|---|---|---|---|---|---|---|")
    for rs in groups(results, ISSUES):
        r = rs[0]
        ids = r["id_label"] + (f" +{len(rs) - 1}" if len(rs) > 1 else "")
        extra = md_names(m, r["extra"]) if r["complete"] or not r["extra"] else \
            md_names(m, r["extra"]) + " (images incomplete: not judged)"
        L.append(f"| {r['status']} | {r['opened_at'][:10]} | {ids} | {r['name']} | {r['pickup_source'] or 'none'} | "
                 + ", ".join(f"`{n}`" for n in r["images"]) + f" | {md_names(m, r['missing'], r['detected_in'])} | "
                 f"{extra} | `{sheet_name(rs)}` |")
    L.append("")
    L.append("### Inconclusive")
    L.append("")
    L.append("No character detected, or recorded pick-ups not seen where only the list banner or some of the "
             "per-character panels survive.")
    L.append("")
    L.append("| opened | gachas | title | source | images | detected | recorded, not seen |")
    L.append("|---|---|---|---|---|---|---|")
    for rs in groups(results, ("inconclusive",)):
        r = rs[0]
        ids = r["id_label"] + (f" +{len(rs) - 1}" if len(rs) > 1 else "")
        L.append(f"| {r['opened_at'][:10]} | {ids} | {r['name']} | {r['pickup_source'] or 'none'} | "
                 + ", ".join(f"`{n}`" for n in r["images"]) + f" | {md_names(m, r['detected'])} | {md_names(m, r['extra'])} |")
    for title, sts in (("Box gachas: characters on their banners", ("box (detections listed)",)),
                       ("Permanent banners: showcased characters", ("permanent showcase",))):
        L.append("")
        L.append(f"### {title}")
        L.append("")
        L.append("<details><summary>show</summary>")
        L.append("")
        L.append("| opened | gachas | title | detected |")
        L.append("|---|---|---|---|")
        for rs in groups(results, sts):
            r = rs[0]
            if not r["detected"]:
                continue
            ids = r["id_label"] + (f" +{len(rs) - 1}" if len(rs) > 1 else "")
            L.append(f"| {r['opened_at'][:10]} | {ids} | {r['name']} | {md_names(m, r['detected'], r['detected_in'])} |")
        L.append("")
        L.append("</details>")
    L.append("")
    L.append("### Confirmed")
    L.append("")
    L.append("<details><summary>show</summary>")
    L.append("")
    L.append("| opened | gachas | title | source | pick-ups (all seen) |")
    L.append("|---|---|---|---|---|")
    for rs in groups(results, ("confirmed",)):
        r = rs[0]
        ids = r["id_label"] + (f" +{len(rs) - 1}" if len(rs) > 1 else "")
        L.append(f"| {r['opened_at'][:10]} | {ids} | {r['name']} | {r['pickup_source']} | {md_names(m, r['recorded'])} |")
    L.append("")
    L.append("</details>")
    gen = "\n".join(L)
    begin, end = "<!-- BEGIN GENERATED (tools/gacha_verify.py) -->", "<!-- END GENERATED -->"
    text = open(path).read() if os.path.exists(path) else f"# Gacha pick-ups vs banner images\n\n{begin}\n{end}\n"
    if begin not in text:
        text += f"\n{begin}\n{end}\n"
    a, b = text.index(begin) + len(begin), text.index(end)
    with open(path, "w") as fh:
        fh.write(text[:a] + "\n" + gen + "\n" + text[b:])


# ---------------------------------------------------------------- main

def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--master", default=os.path.join(ROOT, "data", "basmaster-3.7.0.sqlite3"))
    ap.add_argument("--download", default=os.path.join(ROOT, "work", "download-3.7.0"))
    ap.add_argument("--apk", default=os.path.join(ROOT, "apk", "STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk"),
                    help="the 3.7.0 APK: its images fill names the download lacks")
    ap.add_argument("--pools", default=os.path.join(ROOT, "data", "gacha_pools.sqlite3"))
    ap.add_argument("--gl", default=os.path.join(ROOT, "data", "basmaster-gl.sqlite3"),
                    help="the global client's master DB, for English names")
    ap.add_argument("--out", default=os.path.join(ROOT, "work", "gacha-verify"))
    ap.add_argument("--report", default=None, help="write the markdown report here (e.g. docs/gacha-verify.md)")
    ap.add_argument("-j", "--jobs", type=int, default=max(1, (os.cpu_count() or 2) - 2))
    a = ap.parse_args()

    import extract_banners
    if not os.path.exists(extract_banners.TOOL):
        import subprocess
        subprocess.run([os.path.join(ROOT, "tools", "aif2png", "build.sh")], check=True)

    m = Master(a.master, a.pools, a.gl)
    img_dir = os.path.join(a.download, "Image", "etc2")
    on_disk = {f[:-4]: os.path.join(img_dir, f) for f in os.listdir(img_dir) if f.endswith(".aif")}
    if os.path.exists(a.apk):  # the APK's own images, for names the download lacks (ticket gachas)
        import zipfile
        apk_dir = os.path.join(a.out, "apk")
        os.makedirs(apk_dir, exist_ok=True)
        with zipfile.ZipFile(a.apk) as z:
            for zn in z.namelist():
                mm = re.fullmatch(r"assets/(?:assetpack|builtin_data)/Image/etc2/(.+)\.aif", zn)
                if mm and mm.group(1) not in on_disk:
                    dst = os.path.join(apk_dir, mm.group(1) + ".aif")
                    if not os.path.exists(dst):
                        with open(dst, "wb") as fh:
                            fh.write(z.read(zn))
                    on_disk[mm.group(1)] = dst
    png = os.path.join(a.out, "png")
    feat = os.path.join(a.out, "feat")
    os.makedirs(feat, exist_ok=True)

    # 1. decode: every image a gacha refers to, and every role's illustrations
    banners = sorted({n for g in m.gachas for _, n, _ in g["refs"] if n in on_disk})
    refs = sorted({rn for k in m.art_keys() for rn in ref_names(k).values() if rn in on_disk})
    icons = sorted({ref_names(k)["fl"].replace("_fl", "_ic") for k in m.art_keys()} & set(on_disk))
    decode([(on_disk[n], os.path.join(png, n + ".png")) for n in banners + refs + icons], a.jobs)
    print(f"{len(banners)} banner images, {len(refs)} illustrations ({len(m.art_keys())} art keys)")

    # 2. features
    jobs = [(os.path.join(png, n + ".png"), os.path.join(feat, n + ".ref.npz"), "ref") for n in refs]
    jobs += [(os.path.join(png, n + ".png"), os.path.join(feat, n + ".q.npz"), "query") for n in banners]
    jobs = [j for j in jobs if os.path.exists(j[0])]
    with mp.Pool(a.jobs) as pool:
        list(pool.imap_unordered(_feat_job, jobs, chunksize=4))

    # 3. match
    global _MATCHER
    ref_feats = {}
    for n in refs:
        p = os.path.join(feat, n + ".ref.npz")
        if os.path.exists(p):
            ref_feats[n] = load_feat(p)
    _MATCHER = Matcher(ref_feats)
    print(f"index: {len(_MATCHER.desc)} descriptors from {len(ref_feats)} illustrations")
    qjobs = [(n, os.path.join(feat, n + ".q.npz")) for n in banners if os.path.exists(os.path.join(feat, n + ".q.npz"))]
    det_by_image = {}
    ctx = mp.get_context("fork")
    with ctx.Pool(a.jobs) as pool:
        for name, size, dets in pool.imap_unordered(_detect_job, qjobs, chunksize=2):
            det_by_image[name] = dict(size=size, detections=dets)
    with open(os.path.join(a.out, "detections.json"), "w") as fh:
        json.dump(det_by_image, fh, ensure_ascii=False, indent=0, sort_keys=True)

    # 4. calibration, comparison, report
    results = [classify(m, g, det_by_image) for g in m.gachas]
    cal = calibration(m, det_by_image)
    with open(os.path.join(a.out, "results.json"), "w") as fh:
        json.dump(dict(calibration=cal, gachas=results), fh, ensure_ascii=False, indent=0)
    print_summary(cal, results)
    contact_sheets(m, results, det_by_image, png, os.path.join(a.out, "sheets"))
    if a.report:
        write_report(m, cal, results, a.report, a.out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
