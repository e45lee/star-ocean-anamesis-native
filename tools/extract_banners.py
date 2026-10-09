#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Extract the gacha banner and pickup images of the 3.7.0 data set to PNG, with an index.

Sources (in the 3.7.0 download, --download: work/SOA-3.7.0-canonical-data.zip, read in place, or a folder):
  * Image/etc2/*.aif  (ADLD-XOR + SLZ + AIF: ETC2 / JPEG), the only place the banner art lives (the
    APK's assetpack/Image has none);
  * UI/etc2/gacha*.csf  the gacha screens' Cocos scenes (their texture atlas);
  * the 3.7.0 APK (apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk, --apk) as a fallback for names
    that the download lacks.
Master data: data/basmaster-3.7.0.sqlite3 (read-only).

Which images belong to a gacha (master_gacha row):
  * banner   master_gacha.banner_id -> master_banner.id_label -> master_banner.image
             (the list banner; the same row also holds the webview "details" URL);
  * image1-4 master_gacha.image1..image4 (older gachas: the pickup panels);
  * pickup   master_gacha_image rows (master_gacha_id = gacha id), ordered by view_index:
             the pickup panels of the gacha screen (content_type/content_id name the featured
             role or weapon, None for the main panel).
Plus every other Image/ asset whose name marks it as gacha art (banner_gacha_*, *ticketgacha*,
pickup_img_*, *_PU_*, ...), even if no gacha row refers to it.

Output (work/gacha-banners/ by default; untracked):
  images/<image>.png                one file per distinct image
  ui/<scene>.png                    gacha screen texture atlases
  by-gacha/<id_label>/<role>_<image>.png   relative symlinks, per gacha
  index.html                        every gacha: id, label, name, type, window, costs, rates,
                                    thumbnails (missing images are listed by name)
  gachas.json                       the same data, machine-readable

The decoding is done by tools/aif2png (C++; built on demand with tools/aif2png/build.sh), which reads
the download's stored zip entries in place (ZIP@OFFSET+SIZE: DownloadTree.host_spec).
"""
import argparse
import concurrent.futures as cf
import html
import json
import os
import re
import sqlite3
import subprocess
import sys
import tempfile
import zipfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
from soa_save.download_tree import DEFAULT, DownloadTree  # noqa: E402
from soa_save.paths import master_db  # noqa: E402

TOOL = os.path.join(ROOT, "tools", "aif2png", "aif2png")

GACHA_ART = re.compile(r"(banner_gacha|ticketgacha|pickup_img|_PU_|gacha|banner_sphere|banner_rental_point)", re.I)
GACHA_TYPES = {0: "character", 1: "weapon", 2: "box / event"}


def find_db(path):
    """--db, else data/basmaster-3.7.0.sqlite3 here or in the main checkout (soa_save.paths.master_db)."""
    db = master_db(path)
    if db is None:
        sys.exit("basmaster-3.7.0.sqlite3 not found (use --db)")
    return str(db)


def load_gachas(db):
    c = sqlite3.connect(f"file:{db}?mode=ro", uri=True)
    c.row_factory = sqlite3.Row
    text = {r["message_id"]: r["text_value"] for r in c.execute("select message_id, text_value from master_text")}
    banners = {r["id_label"]: dict(r) for r in c.execute("select * from master_banner")}
    pickups = {}
    for r in c.execute("select * from master_gacha_image order by master_gacha_id, view_index, id"):
        pickups.setdefault(r["master_gacha_id"], []).append(dict(r))
    gachas = []
    for r in c.execute("select * from master_gacha"):
        g = dict(r)
        g["name"] = text.get(g["name_message_id"] or "", "")
        refs = []  # (role, image name, extra)
        b = banners.get(g["banner_id"] or "")
        g["banner_url"] = b["url"] if b else None
        if b and b["image"]:
            refs.append(("banner", b["image"], g["banner_id"]))
        for k in ("image1", "image2", "image3", "image4"):
            if g[k]:
                refs.append((k, g[k], ""))
        for p in pickups.get(g["id"], []):
            refs.append((f"pickup{p['view_index']}", p["image_resource"], p["content_id_label"] or ""))
        g["refs"] = refs
        gachas.append(g)
    gachas.sort(key=lambda g: (g["opened_at"] or "", g["order_id"] or 0, g["id_label"]), reverse=True)
    return gachas


def run_batches(jobs, workers):
    """jobs: [(src, asset name, out png)] -> {src: (ok, [out:WxH:kind] or reason)}."""
    res = {}
    if not jobs:
        return res
    n = max(1, min(workers, len(jobs)))
    chunks = [jobs[i::n] for i in range(n)]

    def one(chunk):
        inp = "".join(f"{s}\t{a}\t{o}\n" for s, a, o in chunk)
        out = subprocess.run([TOOL, "-"], input=inp, capture_output=True, text=True, check=True).stdout
        return out.splitlines()

    with cf.ThreadPoolExecutor(n) as ex:
        for lines in ex.map(one, chunks):
            for line in lines:
                f = line.split("\t")
                res[f[1]] = (f[0] == "ok", f[2:])
    return res


def rate(v):
    return "" if v is None else f"{v:g}%"


def write_index(out, gachas, have, extra, ui, missing_names):
    def thumb(name, role, extra_label):
        info = have.get(name)
        cap = html.escape(f"{role}: {name}" + (f" ({extra_label})" if extra_label else ""))
        if not info:
            return f'<div class="t miss" title="{cap}">{html.escape(role)}<br><code>{html.escape(name)}</code><br>not in 3.7.0 data</div>'
        rel, dims = info
        return (f'<a class="t" href="{rel}" title="{cap} {dims}"><img loading="lazy" src="{rel}" alt="{cap}">'
                f'<span>{html.escape(role)}: {html.escape(name)}</span></a>')

    rows = []
    for g in gachas:
        imgs = "".join(thumb(n, role, x) for role, n, x in g["refs"]) or '<div class="t miss">no image reference</div>'
        rates = " / ".join(rate(g[f"{k}_rank_rate"]) for k in "sabcd")
        bonus = " / ".join(rate(g[f"bonus_{k}_rank_rate"]) for k in "sabc")
        cost = []
        if g["coin"]:
            cost.append(f"{g['coin']} coin{' (paid)' if g['is_pay_coin'] else ''}")
        if g["bulk_count"]:
            cost.append(f"{g['bulk_count']}x for {g['bulk_coin']}")
        if g["ticket_item_id_label"]:
            cost.append(f"{g['ticket_num']}x {g['ticket_item_id_label']}")
        flags = [f for f, on in (("box", g["is_box"]), ("step-up %s/%s" % (g["stepup_number"], g["stepup_max"]), g["is_stepup"]),
                                 ("sale", g["is_sale"])) if on]
        link = f' <a href="{html.escape(g["banner_url"])}">details (dead link)</a>' if g["banner_url"] else ""
        rows.append(f"""<tr data-q="{html.escape((g['id_label'] + ' ' + g['name'] + ' ' + str(g['id'])).lower())}" data-img="{int(any(n in have for _, n, _ in g['refs']))}">
<td><b>{html.escape(g['id_label'])}</b><br><small>id {g['id']}</small><br>{html.escape(g['name'])}{link}</td>
<td>{g['gacha_type']} {GACHA_TYPES.get(g['gacha_type'], '')}<br><small>{html.escape(', '.join(flags))}</small></td>
<td><small>{html.escape(g['opened_at'] or '')}<br>{html.escape(g['closed_at'] or '')}</small></td>
<td><small>S/A/B/C/D {rates}<br>bonus S/A/B/C {bonus}<br>{html.escape('; '.join(cost))}</small></td>
<td class="imgs">{imgs}</td></tr>""")

    def gallery(items):
        return "".join(f'<a class="t" href="{rel}" title="{html.escape(n)} {dims}"><img loading="lazy" src="{rel}" alt="{html.escape(n)}">'
                       f'<span>{html.escape(n)}</span></a>' for n, (rel, dims) in items)

    n_img = sum(1 for g in gachas if any(n in have for _, n, _ in g["refs"]))
    doc = f"""<!doctype html><html lang="en"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1"><title>Gacha banners 3.7.0</title>
<style>
:root{{--bg:#fff;--fg:#111;--mut:#666;--line:#ddd;--chk1:#eee;--chk2:#ccc}}
@media (prefers-color-scheme: dark){{:root{{--bg:#16181c;--fg:#e8e8e8;--mut:#999;--line:#333;--chk1:#2a2a2a;--chk2:#3a3a3a}}}}
body{{background:var(--bg);color:var(--fg);font:14px system-ui,sans-serif;margin:16px}}
table{{border-collapse:collapse;width:100%}} td{{border-top:1px solid var(--line);vertical-align:top;padding:6px}}
small{{color:var(--mut)}} .imgs{{display:flex;flex-wrap:wrap;gap:6px}}
.t{{display:inline-flex;flex-direction:column;max-width:260px;font-size:11px;color:var(--mut);text-decoration:none}}
.t img{{max-width:260px;max-height:150px;object-fit:contain;
background:repeating-conic-gradient(var(--chk1) 0 25%,var(--chk2) 0 50%) 0 0/16px 16px}}
.miss{{border:1px dashed var(--line);padding:6px;width:160px}} .gal{{display:flex;flex-wrap:wrap;gap:8px}}
input{{font-size:14px;padding:4px;width:min(400px,90%)}}
</style></head><body>
<h1>Gacha banners (3.7.0 data)</h1>
<p>{len(gachas)} gachas; {n_img} have at least one image in the 3.7.0 download. {len(have)} images extracted,
{len(missing_names)} referenced images are not in the data set (the server had removed them).
Rates are the master-data rank rates (the live rate dialog took its rates from the server).
Generated by <code>tools/extract_banners.py</code>.</p>
<p><input id="q" placeholder="filter by label / name / id"> <label><input type="checkbox" id="only"> only gachas with images</label>
&nbsp; <a href="#extra">other gacha art</a> · <a href="#ui">gacha screen atlases</a></p>
<table><tbody id="rows">{''.join(rows)}</tbody></table>
<h2 id="extra">Other gacha art (not referenced by any gacha row)</h2><div class="gal">{gallery(extra)}</div>
<h2 id="ui">Gacha screen texture atlases (UI/etc2/*.csf)</h2><div class="gal">{gallery(ui)}</div>
<script>
const q=document.getElementById('q'),only=document.getElementById('only');
function f(){{const s=q.value.toLowerCase();for(const r of document.getElementById('rows').rows)
r.hidden=!(r.dataset.q.includes(s)&&(!only.checked||r.dataset.img==='1'));}}
q.oninput=f;only.onchange=f;
</script></body></html>"""
    with open(os.path.join(out, "index.html"), "w") as fh:
        fh.write(doc)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--download", default=DEFAULT,
                    help="the 3.7.0 download: its zip (default work/SOA-3.7.0-canonical-data.zip, read in place) or a folder")
    ap.add_argument("--apk", default=os.path.join(ROOT, "apk", "STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk"))
    ap.add_argument("--db", default=None)
    ap.add_argument("--out", default=os.path.join(ROOT, "work", "gacha-banners"))
    ap.add_argument("--all-images", action="store_true", help="also convert every Image/ asset (to <out>/all/)")
    ap.add_argument("-j", "--jobs", type=int, default=8)
    a = ap.parse_args()

    if not os.path.exists(TOOL) or os.path.getmtime(TOOL) < os.path.getmtime(TOOL + ".cpp"):
        subprocess.run([os.path.join(ROOT, "tools", "aif2png", "build.sh")], check=True)
    db = find_db(a.db)
    gachas = load_gachas(db)

    tree = DownloadTree.open(a.download)
    on_disk = {f[:-4]: tree.host_spec("Image/etc2/" + f) for f in tree.list("Image/etc2") if f.endswith(".aif")}
    apk_names = {}
    if os.path.exists(a.apk):
        with zipfile.ZipFile(a.apk) as z:
            for n in z.namelist():
                m = re.fullmatch(r"assets/(?:assetpack|builtin_data)/Image/etc2/(.+)\.aif", n)
                if m and m.group(1) not in on_disk:
                    apk_names[m.group(1)] = n

    referenced = {n for g in gachas for _, n, _ in g["refs"]}
    wanted = {n for n in referenced if n in on_disk or n in apk_names}
    art = {n for n in list(on_disk) + list(apk_names) if GACHA_ART.search(n)}
    wanted |= art
    missing_names = sorted(referenced - wanted)

    os.makedirs(os.path.join(a.out, "images"), exist_ok=True)
    os.makedirs(os.path.join(a.out, "ui"), exist_ok=True)
    tmp = tempfile.mkdtemp(prefix="banners-apk-")
    jobs = []
    for n in sorted(wanted):
        src = on_disk.get(n)
        if not src:
            src = os.path.join(tmp, n + ".aif")
            with zipfile.ZipFile(a.apk) as z, open(src, "wb") as fh:
                fh.write(z.read(apk_names[n]))
        jobs.append((src, f"Image/etc2/{n}.aif", os.path.join(a.out, "images", n + ".png")))
    ui_names = [f for f in tree.list("UI/etc2") if re.match(r"gacha", f, re.I) and f.endswith(".csf")]
    for f in ui_names:
        jobs.append((tree.host_spec(f"UI/etc2/{f}"), f"UI/etc2/{f}", os.path.join(a.out, "ui", f[:-4] + ".png")))
    res = run_batches(jobs, a.jobs)
    if a.all_images:  # a separate run: results are keyed by source file
        os.makedirs(os.path.join(a.out, "all"), exist_ok=True)
        all_jobs = [(src, f"Image/etc2/{n}.aif", os.path.join(a.out, "all", n + ".png")) for n, src in sorted(on_disk.items())]
        all_res = run_batches(all_jobs, a.jobs)
        bad = [s for s, (ok, _) in all_res.items() if not ok]
        print(f"all images: {len(all_res) - len(bad)} converted to {os.path.join(a.out, 'all')}, {len(bad)} failed")
        for s in bad[:20]:
            print("  error:", s, " ".join(all_res[s][1]))
    have, ui, errors = {}, [], []
    for src, asset, outp in jobs:
        ok, info = res.get(src, (False, ["no result"]))
        if not ok:
            errors.append(f"{asset}: {' '.join(info)}")
            continue
        for k, field in enumerate(info):
            path, dims, kind = field.rsplit(":", 2)
            rel = os.path.relpath(path, a.out)
            if asset.startswith("UI/"):
                ui.append((os.path.basename(asset) + (f" #{k}" if k else ""), (rel, f"{dims} {kind}")))
            elif k == 0:
                have[os.path.basename(asset)[:-4]] = (rel, f"{dims} {kind}")

    # per-gacha symlinks
    by = os.path.join(a.out, "by-gacha")
    for g in gachas:
        links = [(role, n) for role, n, _ in g["refs"] if n in have]
        if not links:
            continue
        d = os.path.join(by, g["id_label"])
        os.makedirs(d, exist_ok=True)
        for role, n in links:
            lp = os.path.join(d, f"{role}_{n}.png")
            if os.path.lexists(lp):
                os.remove(lp)
            os.symlink(os.path.relpath(os.path.join(a.out, have[n][0]), d), lp)

    extra = sorted((n, v) for n, v in have.items() if n not in referenced)
    write_index(a.out, gachas, have, extra, ui, missing_names)
    keep = ("id", "id_label", "name", "name_message_id", "gacha_type", "gacha_category", "banner_id", "banner_url",
            "opened_at", "closed_at", "is_pay_coin", "coin", "bulk_count", "bulk_coin", "ticket_item_id_label", "ticket_num",
            "is_box", "is_stepup", "stepup_number", "stepup_max", "is_sale",
            "s_rank_rate", "a_rank_rate", "b_rank_rate", "c_rank_rate", "d_rank_rate",
            "bonus_s_rank_rate", "bonus_a_rank_rate", "bonus_b_rank_rate", "bonus_c_rank_rate")
    with open(os.path.join(a.out, "gachas.json"), "w") as fh:
        json.dump([{**{k: g[k] for k in keep},
                    "images": [{"role": r, "image": n, "content": x, "png": have[n][0] if n in have else None} for r, n, x in g["refs"]]}
                   for g in gachas], fh, ensure_ascii=False, indent=1)
    n_img = sum(1 for g in gachas if any(n in have for _, n, _ in g["refs"]))
    print(f"db {db}")
    print(f"{len(gachas)} gachas, {n_img} with images; {len(have)} images, {len(ui)} UI atlases, "
          f"{len(missing_names)} referenced images missing from the data, {len(errors)} errors")
    for e in errors[:20]:
        print("  error:", e)
    print(f"index: {os.path.join(a.out, 'index.html')}")
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main())
