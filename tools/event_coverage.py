#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Asset coverage of the master DB's events, Sphere 211, tower and banners against asset sources.

Usage: event_coverage.py --db MASTER.sqlite3 --src PATH [--src PATH ...] [--json OUT] [--md OUT] [--quiet]

A source is the 3.7.0 download (its zip work/SOA-3.7.0-canonical-data.zip, read in place, or an
extracted folder), an extracted APK dir, or an .apk/zip (top-level .apk members of a split-APK bundle are opened too). Paths are normalised to the game's logical
names: anything up to 'builtin_data/' or 'assetpack/' is stripped, and the quality subdirs
'etc2/hi/' and 'etc2/' are folded away, so 'BG/etc2/hi/bm0001_b01a.asf' -> 'BG/bm0001_b01a.asf'.
Zero-size files count as absent (the download's I/, B/ placeholders).

Nothing about which events or images exist is hard-coded; everything is recomputed from the
DB and the sources, so rerun it whenever more assets are downloaded:
  .venv/bin/python tools/event_coverage.py --db data/basmaster-3.7.0.sqlite3 \\
    --src work/SOA-3.7.0-canonical-data.zip --src apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk --md docs/restore-inventory.md
"""
import argparse, collections, io, json, os, re, sqlite3, sys, zipfile

from soa_save.download_tree import DownloadTree


def norm(p):
    p = p.replace("\\", "/")
    for m in ("builtin_data/", "assetpack/"):
        i = p.find(m)
        if i >= 0:
            p = p[i + len(m):]
    return re.sub(r"/etc2(/hi)?/", "/", p)


def scan_zip(zf, label, out):
    for i in zf.infolist():
        if i.filename.endswith((".apk", ".zip")) and "/" not in i.filename.strip("/"):
            try:
                scan_zip(zipfile.ZipFile(io.BytesIO(zf.read(i))), label, out)
            except zipfile.BadZipFile:
                pass
        elif i.file_size > 0 and not i.is_dir():
            out.setdefault(norm(i.filename), label)


def scan(src):
    out = {}
    if os.path.isdir(src):
        t = DownloadTree.open(src)
        for name in t.files():
            if t.size(name) > 0:
                out.setdefault(norm(name), src)
    else:
        scan_zip(zipfile.ZipFile(src), src, out)
    return out


class Cov:
    def __init__(self, db, srcs):
        self.have, self.per_src = {}, []
        for s in srcs:
            m = scan(s)
            self.per_src.append((s, len(m)))
            for k, v in m.items():
                self.have.setdefault(k, v)
        c = sqlite3.connect(f"file:{db}?mode=ro", uri=True)
        c.row_factory = sqlite3.Row
        self.c = c
        self.tabs = {r[0] for r in c.execute("select name from sqlite_master where type='table'")}
        self.text = {r[0]: r[1] for r in c.execute("select message_id,text_value from master_text")}
        self.banners = {r["id_label"]: dict(r) for r in c.execute("select * from master_banner")}
        self.stages = collections.defaultdict(list)
        for r in c.execute("select master_mission_id, master_map_id_label, master_enemy_party_id from master_mission_stage"):
            self.stages[r[0]].append(dict(r))
        self.parties = {r["id"]: dict(r) for r in c.execute("select * from master_enemy_party")}
        self.ebase = {r[0]: r[1] for r in c.execute("select id, master_person_id from master_enemy_base_parameter")}
        self.person = {r[0]: r[1] for r in c.execute("select id, asf from master_person")}
        self.replace = {}
        for r in c.execute("select * from master_replace_resource where res_type=4"):
            self.replace.setdefault(r["replace_group_id"], {})[r["original_res"]] = r["replace_res"]

    def q(self, sql, *p):
        return [dict(r) for r in self.c.execute(sql, p)]

    def ok(self, logical):
        return logical in self.have

    def img(self, name):
        return bool(name) and self.ok(f"Image/{name}.aif")

    def stand_in(self, name):
        """Generic same-stem substitutes present in the sources: a `_256` copy, else the same name whose
        trailing number differs by at most 2 (nearest first, at most 2 suggestions)."""
        if self.img(f"{name}_256"):
            return [f"{name}_256"]
        m = re.match(r"(.*_)(\d+)$", name)
        if not m:
            return []
        stem, num, width = m.group(1), int(m.group(2)), len(m.group(2))
        cands = [f"{stem}{n:0{width}d}" for d in (1, 2) for n in (num - d, num + d) if n >= 0]
        return [c for c in cands if self.img(c)][:2]

    def enemy_models(self, party_id):
        p = self.parties.get(party_id)
        out = []
        for i in range(1, 9):
            asf = self.person.get(self.ebase.get(p.get(f"member{i}_id"))) if p else None
            if asf:
                out.append(f"Character/{asf}.asf")
        return out

    def missions_assets(self, mission_ids, rep=None):
        rep = rep or {}
        maps, enemies = set(), set()
        for mid in mission_ids:
            for st in self.stages.get(mid, []):
                if st["master_map_id_label"]:
                    maps.add(rep.get(st["master_map_id_label"], st["master_map_id_label"]))
                enemies.update(self.enemy_models(st["master_enemy_party_id"]))
        maps_ok = {m for m in maps if all(self.ok(f"BG/{m}.{e}") for e in ("asf", "aaf", "acf"))}
        return dict(maps=len(maps), maps_ok=len(maps_ok), maps_missing=sorted(maps - maps_ok),
                    enemies=len(enemies), enemies_ok=sum(self.ok(x) for x in enemies),
                    enemies_missing=sorted(x[10:-4] for x in enemies if not self.ok(x)))

    # ---------------------------------------------------------------- events
    def events(self):
        ranking = {r["master_event_mission_area_id"] for r in self.q("select master_event_mission_area_id from master_event_ranking_group")}
        weekly = collections.Counter(r["master_event_area_id"] for r in self.q("select master_event_area_id from master_event_weekly"))
        terms = collections.defaultdict(list)
        for r in self.q("select master_event_area_id, opened_day, closed_day from master_event_term"):
            terms[r["master_event_area_id"]].append(r)
        missions = collections.defaultdict(list)
        for r in self.q("select * from master_event_mission order by order_id, id"):
            missions[r["master_event_area_id"]].append(r)
        out = []
        for ar in self.q("select * from master_event_area order by order_id, id"):
            ms = missions.get(ar["id"], [])
            a = self.missions_assets([m["id"] for m in ms], self.replace.get(ar["resource_replace_group_id"], {}))
            scripts = set()
            for m in ms:
                if m["talk_event_id_label"]:
                    scripts.add(f"Script/{m['talk_event_id_label']}.msgp")
                if m["talk_message_file"]:
                    scripts.add(f"Scenario/{m['talk_message_file']}.msgp")
            b = self.banners.get(ar["master_banner_id_label"] or "")
            banner = b["image"] if b else None
            kinds = []
            if ar["event_type"] == 1 or (ar["event_id_label"] or "").startswith("world_boss"): kinds.append("worldboss")
            if ar["event_type"] == 2: kinds.append("god")
            if ar["event_type"] == 3: kinds.append("type3")
            if ar["event_tab"] == 1: kinds.append("daily")
            if ar["id"] in ranking: kinds.append("ranking")
            if any(m["is_bighunt"] for m in ms): kinds.append("bighunt")
            if weekly[ar["id"]]: kinds.append("weekly")
            if scripts: kinds.append("story")
            if not kinds: kinds.append("battle")
            t = terms.get(ar["id"], [])
            e = dict(id=ar["id"], label=ar["id_label"], name=self.text.get(ar["name_message_id"] or "", ""),
                     kind="+".join(kinds), board=ar["is_mission_board"] == 1, terms=len(t),
                     first=min((x["opened_day"] for x in t if x["opened_day"]), default="") or "",
                     last=max((x["closed_day"] for x in t if x["closed_day"]), default="") or "",
                     missions=len(ms),
                     bg=ar["bg_resource"] or "", bg_ok=self.img(ar["bg_resource"]) if ar["bg_resource"] else None,
                     banner=banner or "", banner_ok=self.img(banner) if banner else None,
                     scripts=len(scripts), scripts_ok=sum(self.ok(s) for s in scripts), **a)
            if not ms:
                e["class"] = "NO-MISSIONS"
            elif e["maps_ok"] < e["maps"] or e["enemies_ok"] < e["enemies"]:
                e["class"] = "BROKEN"
            elif e["scripts_ok"] == e["scripts"] and e["bg_ok"] is not False and e["banner_ok"] is not False:
                e["class"] = "FULL"
            else:
                e["class"] = "PLAYABLE"
            e["facts"] = self.event_facts(ar, ms, t)
            out.append(e)
        return out

    def _facts_tables(self):
        if hasattr(self, "_ft"):
            return self._ft
        drops = collections.defaultdict(collections.Counter)
        for r in self.q("select master_mission_id, content_id_label from master_mission_drop where content_id_label like 'item_coin%'"):
            drops[r["master_mission_id"]][r["content_id_label"]] += 1
        items = {r["id_label"]: r["name_message_id"] for r in self.q("select id_label, name_message_id from master_item")}
        ach = collections.defaultdict(list)
        for r in self.q("select target_id, name_message_id from master_achievement where target_id is not null"):
            ach[r["target_id"]].append(self.text.get(r["name_message_id"] or "", ""))
        gachas = [(r["opened_at"] or "", self.text.get(r["name_message_id"] or "", "")) for r in
                  self.q("select opened_at, name_message_id from master_gacha where opened_at is not null")]
        pname = {r["asf"]: self.text.get(r["name_message_id"] or "", "") for r in self.q("select asf, name_message_id from master_person")}
        wb = {r["id_label"]: r for r in self.q("select * from master_world_boss")}
        self._ft = (drops, items, ach, gachas, pname, wb)
        return self._ft

    def event_facts(self, ar, ms, terms):
        """Descriptive facts from master data only (names are the game's Japanese text)."""
        drops, items, ach, gachas, pname, wb = self._facts_tables()
        oneline = lambda x: re.sub(r"\s+", " ", (x or "").replace("\\n", " ")).strip()
        names = [oneline(self.text.get(m["name_message_id"] or "", "")) for m in ms]
        story = [n for m, n in zip(ms, names) if m["talk_event_id_label"] and n]
        tiers = sorted({t for n in names for t in re.findall(r"【([^】]+)】", n)})
        battles = sorted({re.sub(r"【[^】]+】", "", n).strip() for m, n in zip(ms, names) if not m["talk_event_id_label"] and n})
        hardest = sorted(ms, key=lambda m: -(m["recommend_level"] or 0))[:1]
        bosses = []
        for m in hardest:
            for st in self.stages.get(m["id"], []):
                for x in self.enemy_models(st["master_enemy_party_id"]):
                    nm = pname.get(x[10:-4], "")
                    if nm and nm not in bosses:
                        bosses.append(nm)
        cur = collections.Counter()
        for m in ms:
            cur.update(drops.get(m["id"], {}))
        currency = [oneline(self.text.get(items.get(k) or "", "")) or k for k, _ in cur.most_common(3)]
        achs = [a for m in ms for a in ach.get(m["id"], []) if a]
        prefixes = collections.Counter(a.split("：")[0] for a in achs if "：" in a)
        first = min((x["opened_day"] for x in terms if x["opened_day"]), default="") or ""
        conc = []
        if first:
            d = first[:10]
            import datetime as _dt
            try:
                lo = _dt.date.fromisoformat(d) - _dt.timedelta(days=2)
                hi = _dt.date.fromisoformat(d) + _dt.timedelta(days=2)
                conc = sorted({n for o, n in gachas if n and o[:10] and lo.isoformat() <= o[:10] <= hi.isoformat()})[:4]
            except ValueError:
                conc = []
        f = dict(story=story[:4], story_count=len(story), battles=battles[:6], tiers=tiers,
                 max_level=max((m["recommend_level"] or 0 for m in ms), default=0),
                 bosses=bosses[:4], currency=currency, tag=[p for p, _ in prefixes.most_common(2)],
                 gachas=conc)
        w = wb.get(ar["event_id_label"] or "")
        if w:
            f["world_boss"] = oneline(self.text.get(w.get("message_id_label") or "", "")) or w["id_label"]
        return f

    # ---------------------------------------------------------------- Sphere 211
    def sphere211(self):
        if "master_sphere211" not in self.tabs:
            return None
        seasons = self.q("select * from master_sphere211 order by season_index, id")
        floors = self.q("select * from master_sphere211_floor")
        bgs = sorted({f["bg_resource"] for f in floors if f.get("bg_resource")})
        maps = sorted({f[k] for f in floors for k in f if "map" in k and f[k] and isinstance(f[k], str)})
        box_missions = [r["master_mission_id"] for r in self.q("select * from master_sphere211_mission_box")
                        if r.get("master_mission_id")] if "master_sphere211_mission_box" in self.tabs else []
        a = self.missions_assets(sorted(set(box_missions)))
        counts = {t: self.c.execute(f"select count(*) from {t}").fetchone()[0]
                  for t in sorted(self.tabs) if t.startswith("master_sphere211")}
        return dict(seasons=seasons, floors=len(floors), floor_bgs=[(b, self.img(b)) for b in bgs],
                    floor_maps=[(m, all(self.ok(f"BG/{m}.{e}") for e in ("asf", "aaf", "acf"))) for m in maps],
                    box_missions=len(set(box_missions)), assets=a, tables=counts)

    # ---------------------------------------------------------------- tower
    def tower(self):
        if "master_tower_area" not in self.tabs:
            return None
        areas = self.q("select * from master_tower_area order by id")
        ms = collections.defaultdict(list)
        for r in self.q("select * from master_tower_mission"):
            ms[r["master_tower_area_id"]].append(r["id"])
        out = []
        for ar in areas:
            b = self.banners.get(ar.get("master_banner_id_label") or "")
            a = self.missions_assets(ms.get(ar["id"], []))
            out.append(dict(label=ar["id_label"], name=self.text.get(ar.get("name_message_id") or "", ""),
                            opened=ar.get("opened_at") or "", closed=ar.get("closed_at") or "",
                            missions=len(ms.get(ar["id"], [])), banner=b["image"] if b else "",
                            banner_ok=self.img(b["image"]) if b else None, **a))
        return out

    # ---------------------------------------------------------------- banners
    def banner_inventory(self):
        refs = collections.defaultdict(set)

        def add(cat, sql):
            if re.search(r"from (\w+)", sql).group(1) not in self.tabs:
                return
            try:
                for r in self.c.execute(sql):
                    for v in r:
                        if v: refs[cat].add(v)
            except sqlite3.OperationalError:
                pass
        add("event_area.bg_resource", "select bg_resource from master_event_area")
        add("event_area.banner", "select b.image from master_event_area a join master_banner b on b.id_label=a.master_banner_id_label")
        add("tower_area.banner", "select b.image from master_tower_area a join master_banner b on b.id_label=a.master_banner_id_label")
        add("gacha.banner", "select b.image from master_gacha g join master_banner b on b.id_label=g.banner_id")
        add("gacha.image1-4", "select image1,image2,image3,image4 from master_gacha")
        add("gacha_image.pickup", "select image_resource from master_gacha_image")
        for (h,) in self.c.execute("select distinct is_home from master_banner"):
            add(f"banner(is_home={h})", f"select image from master_banner where is_home is {h if h is not None else 'null'}")
        add("banner_replace", "select image from master_banner_replace")
        add("login_bonus.banner_image", "select banner_image from master_login_bonus")
        add("premium_login_bonus.banner_image", "select banner_image from master_premium_login_bonus")
        add("selectpart.img_resource", "select img_resource from master_selectpart")
        add("loading_message.image", "select image from master_loading_message")
        add("expiration_information", "select title_image,description_image from master_expiration_information")
        add("guide_information", "select description_image from master_guide_information")
        add("area.bg_resource", "select bg_resource from master_area")
        add("training_area.bg_resource", "select bg_resource from master_training_area")
        add("sphere211_floor.bg_resource", "select bg_resource from master_sphere211_floor")
        add("world_map_group_mission.loading_bg", "select loading_bg from master_world_map_group_mission")
        add("world_boss.enemy_icon", "select enemy_icon from master_world_boss")
        rep = {}
        for cat, names in refs.items():
            miss = sorted(n for n in names if not self.img(n))
            rep[cat] = dict(total=len(names), present=len(names) - len(miss), missing=miss,
                            stand_ins={n: self.stand_in(n) for n in miss if self.stand_in(n)})
        allref = set().union(*refs.values()) if refs else set()
        bannerish = re.compile(r"(banner|^bbg|^ebg|^00_bm|_PU_|pickup|^\d{8}_)", re.I)
        unref = sorted(k[6:-4] for k in self.have if k.startswith("Image/") and k.endswith(".aif")
                       and bannerish.search(k[6:-4]) and k[6:-4] not in allref
                       and not (k[6:-4].endswith("_256") and k[6:-8] in allref))
        return rep, unref


def yn(v):
    return "–" if v is None else ("yes" if v else "**no**")


def write_md(cov, ev, sp, tw, bi, unref, argv, path):
    L = []
    w = L.append
    w("# Restore inventory: events, Sphere 211, tower and banners in the available assets\n")
    w("**Generated snapshot — do not edit by hand, and do not hard-code anything from it.** The game and the "
      "local server decide at runtime what is usable; this file only reports what the current asset sources hold. "
      "Regenerate after downloading more assets:\n")
    w("```\n.venv/bin/python tools/event_coverage.py " + " ".join(argv) + "\n```\n")
    w("Sources scanned (logical files): " + ", ".join(f"`{s}` ({n})" for s, n in cov.per_src) + "\n")
    w("Classes: **FULL** = maps, enemy models, talk scripts, background and banner all present; "
      "**PLAYABLE** = every battle map and enemy model present, but some talk scripts / background / banner missing "
      "(battles work, story scenes or art don't); **BROKEN** = a battle map or enemy model is missing; "
      "**NO-MISSIONS** = the area has no missions. Not checked: TalkScene .csf, movies, voices, motions, item icons.\n")
    cnt = collections.Counter(e["class"] for e in ev)
    w("## Events\n")
    w(f"{len(ev)} event areas: " + ", ".join(f"{k} {cnt[k]}" for k in ("FULL", "PLAYABLE", "BROKEN", "NO-MISSIONS")) + ".\n")
    for cls in ("FULL", "PLAYABLE", "BROKEN", "NO-MISSIONS"):
        rows = sorted((e for e in ev if e["class"] == cls), key=lambda e: (e["first"], e["label"]))
        if not rows:
            continue
        w(f"### {cls} ({len(rows)})\n")
        w("| event | name | kind | terms (first..last) | missions | scripts | maps | enemies | bg | banner | missing |")
        w("|---|---|---|---|---|---|---|---|---|---|---|")
        for e in rows:
            miss = []
            if e["maps_missing"]: miss.append("maps " + " ".join(e["maps_missing"]))
            if e["enemies_missing"]: miss.append("enemies " + " ".join(e["enemies_missing"]))
            if e["bg_ok"] is False: miss.append("bg " + e["bg"])
            if e["banner_ok"] is False: miss.append("banner " + e["banner"])
            w(f"| `{e['label']}` | {e['name']} | {e['kind']} | {e['terms']} ({e['first'][:10]}..{e['last'][:10]}) | {e['missions']} "
              f"| {e['scripts_ok']}/{e['scripts']} | {e['maps_ok']}/{e['maps']} | {e['enemies_ok']}/{e['enemies']} "
              f"| {yn(e['bg_ok'])} | {yn(e['banner_ok'])} | {'; '.join(miss)} |")
        w("")
    allmaps = sorted({m for e in ev for m in e["maps_missing"]})
    allen = sorted({m for e in ev for m in e["enemies_missing"]})
    w(f"Missing across all events: {len(allmaps)} battle maps ({' '.join(allmaps)}); "
      f"{len(allen)} enemy models ({' '.join(allen)}); talk scripts "
      f"{sum(e['scripts'] - e['scripts_ok'] for e in ev)} of {sum(e['scripts'] for e in ev)} (per-event counts above).\n")
    w("## Event guide\n")
    w("What each event was, ordered by first term. **About** is a hand-written English summary from "
      "`docs/event-notes.tsv` (interpretation of the data; \"likely\" marks guesses). The other lines come straight "
      "from master data (the game's Japanese text): story chapters, battle missions, difficulty tiers, the bosses of "
      "the highest-level mission, event drop currencies, gachas that opened within two days of the event, world boss.\n")
    for e in sorted(ev, key=lambda e: (e["first"] or "9999", e["label"])):
        f = e["facts"]
        w(f"#### `{e['label']}` — {e['name'] or '(no name)'} · {e['class']}\n")
        w(f"- **About:** {e['note'] or '(no description yet — add one to docs/event-notes.tsv)'}")
        w(f"- **Kind:** {e['kind']}; {e['missions']} missions; terms {e['first'][:10] or '–'} .. {e['last'][:10] or '–'} ({e['terms']})"
          + (f"; recommended level up to {f['max_level']}" if f["max_level"] else ""))
        if f["story"]:
            w(f"- **Story ({f['story_count']}):** " + " / ".join(f["story"]) + (" / …" if f["story_count"] > len(f["story"]) else ""))
        if f["battles"]:
            w("- **Battles:** " + " / ".join(f["battles"]))
        if f["tiers"]:
            w("- **Difficulty tiers:** " + " ".join(f["tiers"]))
        if f["bosses"]:
            w("- **Bosses (hardest mission):** " + " / ".join(f["bosses"]))
        if f["currency"]:
            w("- **Event currency / drops:** " + " / ".join(f["currency"]))
        if f.get("world_boss"):
            w("- **World boss:** " + f["world_boss"])
        if f["tag"]:
            w("- **Achievement tag:** " + " / ".join(f["tag"]))
        if f["gachas"]:
            w("- **Gachas opening alongside:** " + " / ".join(f["gachas"]))
        w("")
    if sp:
        w("## Sphere 211\n")
        w("Sphere 211 was the live endgame mode in 3.7.0, reached through the home screen's extra-dungeon button.\n")
        w("| season | index | opened | closed | ranking opened | ranking closed |")
        w("|---|---|---|---|---|---|")
        for s in sp["seasons"]:
            w(f"| {s.get('id')} | {s.get('season_index', '')} | {s.get('opened_at', '')} | {s.get('closed_at', '')} "
              f"| {s.get('ranking_opened_at', '')} | {s.get('ranking_closed_at', '')} |")
        a = sp["assets"]
        w(f"\nFloors: {sp['floors']}. Floor backgrounds: " + (", ".join(f"`{b}` {yn(ok)}" for b, ok in sp["floor_bgs"]) or "–") +
          ". Floor maps: " + (", ".join(f"`{m}` {yn(ok)}" for m, ok in sp["floor_maps"]) or "–") + ".\n")
        w(f"Mission-box missions: {sp['box_missions']} distinct; battle maps {a['maps_ok']}/{a['maps']}, "
          f"enemy models {a['enemies_ok']}/{a['enemies']}."
          + (f" Missing maps: {' '.join(a['maps_missing'])}." if a["maps_missing"] else "")
          + (f" Missing enemies: {' '.join(a['enemies_missing'])}." if a["enemies_missing"] else "") + "\n")
        w("Table rows: " + ", ".join(f"`{t}` {n}" for t, n in sp["tables"].items()) + "\n")
    if tw:
        w("## Tower\n")
        w("Note: the tower was already switched off in 3.7.0 (`CParameterUtility::IsOpenTowerMission` returns 0 in the "
          "3.7.0 client). In the port it is an opt-in (see docs/client-changes.md).\n")
        w("| area | name | opened | closed | missions | banner | maps | enemies | missing |")
        w("|---|---|---|---|---|---|---|---|---|")
        for t in tw:
            miss = " ".join(t["maps_missing"] + t["enemies_missing"])
            w(f"| `{t['label']}` | {t['name']} | {str(t['opened'])[:10]} | {str(t['closed'])[:10]} | {t['missions']} "
              f"| {yn(t['banner_ok'])} | {t['maps_ok']}/{t['maps']} | {t['enemies_ok']}/{t['enemies']} | {miss} |")
        w("")
    w("## Banners and images by category\n")
    w("| category | present / total |")
    w("|---|---|")
    for cat, r in bi.items():
        w(f"| {cat} | {r['present']}/{r['total']} |")
    w("\n### Stand-ins found in the sources\n")
    w("Same-stem images that could replace a missing one (a `_256` copy, or the same name with another numeric "
      "suffix). Computed by rule, not listed by hand. A stand-in is only a candidate: a nearby number can be "
      "different content (e.g. `banner_event_chr_NNN` are different characters), so the events plan must decide "
      "per image family whether substitution is acceptable:\n")
    detail = re.compile(r"(event_area|tower|sphere211|login_bonus|area|training_area|world_|banner\(is_home=2)")
    any_si = False
    for cat, r in bi.items():
        if not detail.match(cat):
            if r["stand_ins"]:
                w(f"- {cat}: {len(r['stand_ins'])} missing images have a stand-in (see `--json`)")
            continue
        for n, s in r["stand_ins"].items():
            any_si = True
            w(f"- {cat}: `{n}` → " + ", ".join(f"`{x}`" for x in s[:5]))
    if not any_si:
        w("- none")
    w("\n### Missing images per category\n")
    w("Full lists for the event, Sphere 211, tower, login-bonus and area categories; the other categories' "
      "lists are in the `--json` output.\n")
    for cat, r in bi.items():
        if r["missing"] and re.match(r"(event_area|tower|sphere211|login_bonus|area|training_area|world_|banner\(is_home=2)", cat):
            w(f"<details><summary>{cat}: {len(r['missing'])} missing</summary>\n\n" + " ".join(f"`{n}`" for n in r["missing"]) + "\n</details>\n")
    w(f"\n### Banner-like images present but not referenced by master data ({len(unref)})\n")
    w("Excluding `_256` copies of referenced images.\n")
    w(" ".join(f"`{n}`" for n in unref) + "\n")
    with open(path, "w") as f:
        f.write("\n".join(L))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--db", required=True)
    ap.add_argument("--src", action="append", required=True)
    ap.add_argument("--json")
    ap.add_argument("--md")
    ap.add_argument("--notes", help="TSV label<TAB>English description (hand-written, e.g. docs/event-notes.tsv)")
    ap.add_argument("--quiet", action="store_true")
    a = ap.parse_args()
    cov = Cov(a.db, a.src)
    ev, sp, tw = cov.events(), cov.sphere211(), cov.tower()
    notes = {}
    if a.notes and os.path.exists(a.notes):
        for line in open(a.notes, encoding="utf-8"):
            if line.strip() and not line.startswith("#") and "\t" in line:
                k, v = line.rstrip("\n").split("\t", 1)
                notes[k] = v
    for e in ev:
        e["note"] = notes.get(e["label"], "")
    bi, unref = cov.banner_inventory()
    if a.json:
        with open(a.json, "w") as f:
            json.dump(dict(sources=cov.per_src, events=ev, sphere211=sp, tower=tw, banners=bi,
                           unreferenced_bannerlike=unref), f, ensure_ascii=False, indent=1, default=str)
    if a.md:
        argv = [x for x in sys.argv[1:]]
        write_md(cov, ev, sp, tw, bi, unref, argv, a.md)
    if a.quiet:
        return
    for s, n in cov.per_src:
        print(f"# source {s}: {n} files")
    print("events:", dict(collections.Counter(e["class"] for e in ev)))
    if sp:
        print(f"sphere211: {len(sp['seasons'])} seasons, {sp['floors']} floors, box maps {sp['assets']['maps_ok']}/{sp['assets']['maps']}")
    if tw:
        print(f"tower: {len(tw)} areas, maps {sum(t['maps_ok'] for t in tw)}/{sum(t['maps'] for t in tw)}")
    for cat, r in bi.items():
        print(f"{cat}: {r['present']}/{r['total']}")


main()
