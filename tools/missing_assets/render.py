"""The markdown document (part 1: events and gacha banners; part 2: other content) and the plain list
of missing paths. `status` maps every referenced path to the source that has it (None = missing)."""
from __future__ import annotations

import collections
import os
import re
from dataclasses import dataclass

from . import ROOT, rules
from .guess import Guesser
from .model import AssetRef, ContentItem, ContentKind, Status
from .presence import STANDIN_LABEL, Presence

#: Per-kind statistics fold the variable parts of a kind ("(view 2)", "(.asf)", ...).
KIND_VARIANT_RE = re.compile(r" \(view \d+\)| \d+ \(HTML-era gacha screen\)| \(\.\w+\)| \(replaces .*\)| \(dated replacement\)")
UNDATED = "undated"
#: Row and name list lengths in the tables.
BLOCKED_NAMES_SHOWN = 60
BLOCKING_ROWS_SHOWN = 4
REF_ROWS_SHOWN = 3
GACHA_ROWS_SHOWN = 6
PICKS_SHOWN = 6
DANGLING_ROWS_SHOWN = 4
BIGGEST_GAPS = 15
NAME_SOURCE_MARK = {"gl": " *GL*", "glossary": " *gloss*"}


def md_escape(s: str) -> str:
    return (s or "").replace("|", "\\|").replace("\n", " ")


def year_of(item: ContentItem) -> str:
    return item.start[:4] if item.start[:4].isdigit() else UNDATED


def by_start(item: ContentItem):
    """Sort key: dated first, by start, then label."""
    return (item.start == "", item.start, item.label)


def fill_status(status: Status, items, presence: Presence) -> None:
    """Look up every path the items reference that `status` doesn't have yet."""
    for item in items:
        for p in item.refs:
            if p not in status:
                status[p] = presence.where(p)


def has_missing(item: ContentItem, status: Status) -> bool:
    return any(not status[p] for p in item.refs)


def merge_bg(refs: list[AssetRef]) -> list[tuple[str, AssetRef, list[str]]]:
    """Fold the .asf / .aaf / .acf refs of one map into one display row: [(display path, ref, paths)]."""
    rows, by_stem = [], {}
    for r in refs:
        if r.path.startswith("BG/"):
            stem = r.path.rsplit(".", 1)[0]
            if stem in by_stem:
                by_stem[stem][2].append(r.path)
                continue
            by_stem[stem] = [stem, r, [r.path]]
            rows.append(by_stem[stem])
        else:
            rows.append([r.path, r, [r.path]])
    out = []
    for disp, r, paths in rows:
        if len(paths) > 1:
            disp = disp + "." + "/.".join(p.rsplit(".", 1)[1] for p in paths)
        else:  # a lone file of a map keeps its extension
            disp = rules.display_path(paths[0])
        out.append((disp, r, paths))
    return out


def _shortlist(values: list[str], n: int, more: str = " (+{})") -> str:
    return ", ".join(f"`{x}`" for x in values[:n]) + (more.format(len(values) - n) if len(values) > n else "")


# ---------------------------------------------------------------- part 2
@dataclass
class KindStats:
    """Part 2's summary row of a kind."""
    title: str
    rows: int
    usable: int
    blocked: int
    usable_missing_some: int
    blocking_types: collections.Counter  # top folder of each (blocked row, missing gating file) pair


def write_part2(out: list[str], presence: Presence, guesser: Guesser, kinds: list[ContentKind],
                status: Status) -> list[KindStats]:
    """Part 2's sections into `out` (fills `status`); returns the summary rows."""
    w = out.append
    stats = []
    for kind in kinds:
        items = kind.items()
        fill_status(status, items, presence)
        blocked = [o for o in items if any(not status[p] for p in o.gate)]
        extra = [o for o in items if o not in blocked and has_missing(o, status)]
        stats.append(KindStats(kind.title, len(items), len(items) - len(blocked), len(blocked), len(extra),
                               collections.Counter(p.split("/")[0] for o in blocked for p in o.gate if not status[p])))
        w(f"### {kind.title}\n")
        w(kind.description + "\n")
        w(f"{len(items)} rows: **{len(items) - len(blocked)} usable** (every gating file present), "
          f"**{len(blocked)} blocked by missing files**; {len(extra)} of the usable ones miss only non-blocking files.\n")
        for group in kind.groups:
            gb = [o for o in group.items if o in blocked]
            gx = [o for o in group.items if o in extra]
            if not gb and not gx:
                continue
            if len(kind.groups) > 1:
                w(f"#### {md_escape(group.ja)} — {md_escape(group.en) or '(no name)'}"
                  f"{' *GL*' if group.how == 'gl' else ''}\n")
                w(f"{group.note}: {len(group.items)} rows, {len(gb)} blocked"
                  + (f", {len(gx)} usable with non-blocking files missing" if gx else "") + ".\n")
            if gb:
                w("Blocked: " + "; ".join(f"`{o.label}` {md_escape(o.ja)}"
                                           + (f" ({md_escape(o.en)})" if o.en and o.en != o.ja else "")
                                           for o in gb[:BLOCKED_NAMES_SHOWN])
                  + (f"; … (+{len(gb) - BLOCKED_NAMES_SHOWN})" if len(gb) > BLOCKED_NAMES_SHOWN else "") + "\n")
            _write_part2_table(w, guesser, gb + gx, status)
    return stats


def _write_part2_table(w, guesser: Guesser, items: list[ContentItem], status: Status) -> None:
    # missing path -> [ref, first item, rows it blocks, rows it doesn't block]
    files: dict[str, list] = collections.OrderedDict()
    for o in items:
        for r in o.refs.values():
            if not status[r.path]:
                e = files.setdefault(r.path, [r, o, [], []])
                lst = e[2] if r.path in o.gate else e[3]
                if o.label not in lst:
                    lst.append(o.label)
    w("| Missing file | Kind | Blocks | What it probably is | Conf. | Stand-in? |")
    w("|---|---|---|---|---|---|")
    order = sorted(files.values(), key=lambda e: (not e[2], e[0].order, e[0].path))
    for disp, r, _ in merge_bg([e[0] for e in order]):
        _, o, blocks, _ = files[r.path]
        g = guesser.guess(o, r)
        blocks_text = _shortlist(blocks, BLOCKING_ROWS_SHOWN) if blocks else "— (not blocking)"
        w(f"| `{disp}` | {r.kind} | {blocks_text} | {md_escape(g.text)}"
          + (f" ({md_escape(g.evidence)})" if g.evidence else "")
          + f" | {g.confidence} | {rules.standin_verdict(r.path)} |")
    w("")


# ---------------------------------------------------------------- part 1
def kind_counts(owners: list[ContentItem], status: Status) -> dict:
    """(owner type, folded kind) -> Counter of refs, per source label, "missing", "y:<year>" of missing."""
    kinds: dict = collections.OrderedDict()
    for o in owners:
        for r in o.refs.values():
            c = kinds.setdefault((o.typ, KIND_VARIANT_RE.sub("", r.kind)), collections.Counter())
            st = status[r.path]
            c["refs"] += 1
            c[st or "missing"] += 1
            if not st:
                c["y:" + year_of(o)] += 1
    return kinds


def _source_line(presence: Presence) -> str:
    return ", ".join(f"{s.label} `{os.path.relpath(s.path, ROOT) if s.path and os.path.isabs(s.path) else s.path}` "
                     f"({len(s.files)} files)" for s in presence.sources)


def write_intro(w, presence: Presence, p2stats: list[KindStats]) -> None:
    w("# Missing event and gacha assets in 3.7.0\n")
    w("**Generated file — do not edit by hand.** Regenerate with:\n")
    w("```\n.venv/bin/python tools/missing_assets.py\n```\n")
    w("This lists every file that an event (`master_event_area`) or a gacha banner (`master_gacha`, grouped by "
      "`banner_id`) of the 3.7.0 master (`data/basmaster-3.7.0.sqlite3`) references and that no asset source has. "
      f"Sources, in lookup order: {_source_line(presence)}. A file found in a source counts as present; a file found "
      "only in `standin-assets/` is listed as **stand-in** (made-up art, port/README.md \"Stand-in assets\"). The "
      "online CDN dropped old event and gacha art before the last download, so most of what is missing is art and "
      "story data of events and banners that had already closed.\n")
    w("Names: the heading gives the Japanese name from `master_text`, then an English name. English comes from "
      "the Global master (`data/basmaster-gl.sqlite3`, official text, marked *GL*) where it has one, else from "
      "the hand-written table `docs/missing-assets-names.tsv` (established series / anamnesis names where known; "
      "**(tr.)** marks uncertain translations), else from a phrase glossary in the generator (marked *gloss*). "
      "Character names: the Global master, else `soa_save/names_en.json` (the fan wiki's names).\n")
    w("\"What it probably is\" is inference (d) from the referencing column and row, the subject (gacha title, "
      "pick-up role / weapon from `master_gacha_image`, mission name, enemy person), and the size and format of "
      "existing files with the same name pattern (digits folded to `#`), read from their AIF image header. "
      "Confidence: **high** = column and sibling pattern agree; **medium** = subject or size inferred "
      "(siblings disagree, or the panel's subject comes from the pool); **low** = no sibling evidence. The path "
      "rules, the facts, carry the labels of docs/server-rules.md: (a) master data, (b) client-side evidence, "
      "(d) assumption.\n")
    if p2stats:
        w("**Beyond events and gacha** (part 2, at the end): what else the 3.7.0 master describes completely but "
          "missing files block. Usable / blocked master rows:\n")
        w("| Content | Rows | Usable | Blocked | Blocking file types |")
        w("|---|---|---|---|---|")
        for s in p2stats:
            w(f"| {s.title} | {s.rows} | {s.usable} | {s.blocked} | "
              + (", ".join(f"{k} {v}" for k, v in s.blocking_types.most_common()) or "—") + " |")
        w("")
        w("So yes: the blocked rows above would run with their files back. Blocked by 2D images only (icons, "
          "banners, portraits), they would run with made-up stand-ins too; blocked by battle maps, models or "
          "story scripts, they need the real files (a stand-in map or model would only be another one under the "
          "same name). Details per row and file are in part 2.\n")


def write_path_rules(w, presence: Presence, kinds: dict) -> None:
    w("## Path rules and how they were checked\n")
    w("| Reference | File | Label and evidence |")
    w("|---|---|---|")
    for cells in rules.PATH_RULES_TABLE:
        w("| " + " | ".join(cells) + " |")
    w("")
    w("**Checks.** The download tree on disk equals its manifests (every member of the Bulk, Individual and "
      "ep1-3 manifests is a file; `tools/check_download.py`). Presence of what the master references, per kind "
      "(references, not distinct files; *present* = any source):\n")
    w("| Owner | Kind | References | " + " | ".join(s.label for s in presence.sources) + " | Missing |")
    w("|---|---|---|" + "---|" * len(presence.sources) + "---|")
    for (typ, kind), c in kinds.items():
        w(f"| {typ} | {kind} | {c['refs']} | " + " | ".join(str(c[s.label]) for s in presence.sources)
          + f" | {c['missing']} |")
    w("\nThe kinds whose files mostly exist (enemy models, battle maps, voice packs, boss icons) confirm the "
      "path rules; the image kinds of old content are mostly gone, while the same kinds for 2021 content are "
      "present, which is the CDN pruning, not a wrong rule.\n")


def write_summary(w, events, gachas, kinds: dict, status: Status) -> tuple[list, list]:
    """The per-kind / per-year summary; returns (events, gacha banners) with missing files."""
    owners = events + gachas
    years = sorted({year_of(o) for o in owners}, key=lambda y: (y == UNDATED, y))
    distinct_missing = collections.defaultdict(set)
    for o in owners:
        for p in o.missing(status):
            distinct_missing[o.typ].add(p)
    w("## Summary: missing file references per kind and year\n")
    w("Year = the year the owner (event or banner) first opened. A file shared by several owners counts once "
      "per owner. Distinct missing files: "
      + ", ".join(f"{typ} {len(v)}" for typ, v in sorted(distinct_missing.items()))
      + f"; overall {len(set().union(*distinct_missing.values()))}.\n")
    w("| Owner | Kind | " + " | ".join(years) + " | Total |")
    w("|---|---|" + "---|" * len(years) + "---|")
    total = collections.Counter()
    for (typ, kind), c in kinds.items():
        if not c["missing"]:
            continue
        w(f"| {typ} | {kind} | " + " | ".join(str(c['y:' + y]) for y in years) + f" | {c['missing']} |")
        for y in years:
            total[y] += c["y:" + y]
    w("| **all** | | " + " | ".join(f"**{total[y]}**" for y in years) + f" | **{sum(total.values())}** |\n")
    ne = [o for o in events if has_missing(o, status)]
    ng = [o for o in gachas if has_missing(o, status)]
    w(f"Owners with at least one missing file: **{len(ne)} of {len(events)} events**, **{len(ng)} of "
      f"{len(gachas)} gacha banners** ({sum(len(o.gachas) for o in ng)} of {sum(len(o.gachas) for o in gachas)} "
      "gacha rows).\n")
    per_year = collections.defaultdict(lambda: [0, 0, 0, 0])  # events, with missing, banners, with missing
    for o in events:
        per_year[year_of(o)][0] += 1
        per_year[year_of(o)][1] += o in ne
    for o in gachas:
        per_year[year_of(o)][2] += 1
        per_year[year_of(o)][3] += o in ng
    w("| Year | Events | with missing files | Gacha banners | with missing files |")
    w("|---|---|---|---|---|")
    for y in years:
        e = per_year[y]
        w(f"| {y} | {e[0]} | {e[1]} | {e[2]} | {e[3]} |")
    w("")
    biggest = sorted(ne + ng, key=lambda o: (-len(o.missing(status)), o.start, o.label))[:BIGGEST_GAPS]
    w("Biggest gaps (most missing files):\n")
    for o in biggest:
        w(f"- {o.typ} `{o.label}` {o.ja} — {o.en}: {len(o.missing(status))} of {len(o.refs)} files")
    w("")
    standins = [(o, p) for o in owners for p in o.refs if status[p] == STANDIN_LABEL]
    w(f"Stand-ins in use: {len({p for _, p in standins})} files for {len({o.label for o, _ in standins})} owners "
      "(listed in each section).\n")
    w("Not covered: files that the scripts themselves name (talk-scene `.csf`, `Sound/TS_*` SE and `Voice_TS_*` "
      "packs, movies; they are named inside `Script/*.msgp`, not by the master), item icons of event shops and "
      "drops (`master_exchange_shop*` names no file; item thumbnails are shared with the rest of the game), "
      "dated menu BGM (`master_menu_bgm`: by date, not by event), and `master_banner` rows that target nothing.\n")
    return ne, ng


def write_item_section(w, guesser: Guesser, o: ContentItem, status: Status) -> None:
    """One event's or gacha banner's section: heading, info line, missing files, stand-ins."""
    miss = [r for r in o.refs.values() if not status[r.path]]
    stand = [r for r in o.refs.values() if status[r.path] == STANDIN_LABEL]
    dates = f"{o.start or '—'} → {o.end or '—'}" if (o.start or o.end) else "undated"
    w(f"### {md_escape(o.ja) or '(no name)'} — {md_escape(o.en) or '(no name)'}{NAME_SOURCE_MARK.get(o.how, '')}\n")
    w(f"`{o.label}` (id {o.key}) · {dates} · {o.extra} · {len(miss)} missing of {len(o.refs)} files"
      + (f", {len(stand)} stand-in" if stand else ""))
    if o.typ == "event" and o.missions:
        ok = sum(1 for m in o.missions if all(status.get(p) for p in m.gate))
        w(f"\nMissions playable by the local server's check (maps and enemy models; story: script and text): "
          f"**{ok} of {len(o.missions)}**")
    if o.typ == "gacha":
        rows = _shortlist([g.label for g in o.gachas], GACHA_ROWS_SHOWN, " … (+{})")
        w(f"\nGacha rows: {rows}" + (f"\n\nPick-ups: {md_escape('; '.join(o.picks[:PICKS_SHOWN]))}" if o.picks else ""))
    w("")
    if miss:
        w("| Missing file | Kind | Referenced by | What it probably is | Conf. | Evidence | Stand-in? |")
        w("|---|---|---|---|---|---|---|")
        for disp, r, _ in merge_bg(sorted(miss, key=lambda r: (r.order, r.path))):
            g = guesser.guess(o, r)
            cols = "; ".join(f"`{c}`" for c in r.cols)
            w(f"| `{disp}` | {r.kind} | {cols}: {_shortlist(r.rows, REF_ROWS_SHOWN)} | {md_escape(g.text)} | "
              f"{g.confidence} | {md_escape(g.evidence) or '—'} | {rules.standin_verdict(r.path)} |")
        w("")
    if stand:
        w("Stand-ins (made-up, `standin-assets/`): " + ", ".join(
            f"`{rules.display_path(r.path)}` ({r.kind})" for r in stand) + "\n")


def write_dangling(w, dangling: list[ContentItem]) -> None:
    w("## Gacha rows whose banner_id has no master_banner row\n")
    w("A master gap rather than a file gap: `master_gacha.banner_id` names no `master_banner.id_label`, so the "
      "client has no list banner image name for them at all (a). Their other files are in the sections above "
      "when missing.\n")
    w("| banner_id | Gacha rows | Name | Opened |")
    w("|---|---|---|---|")
    for o in sorted(dangling, key=lambda o: (o.start, o.label)):
        rows = ", ".join(f"`{g.label}`" for g in o.gachas[:DANGLING_ROWS_SHOWN])
        w(f"| `{o.label}` | {rows}{' …' if len(o.gachas) > DANGLING_ROWS_SHOWN else ''} "
          f"| {md_escape(o.ja)} — {md_escape(o.en)} | {o.start} |")
    w("")


PART2_INTRO = (
    "For each kind of content: how many master rows have every file their use needs (\"gating\" files: "
    "what the local server's checks or the screens load), how many are blocked by a missing one, and per "
    "missing file what it probably is and whether a made-up stand-in (like `standin-assets/`) would "
    "plausibly do. Files that are missing but don't block (voices, BGM, animations) are listed with "
    "\"not blocking\". Same sources and path rules as above. Images count as blocking where the screen shows "
    "them (an empty frame otherwise, as with the gacha list banners); those rows run with stand-ins.\n")


@dataclass
class Document:
    """The rendered markdown lines and what the other outputs need."""
    lines: list[str]
    events_missing: list[ContentItem]
    gachas_missing: list[ContentItem]
    status: Status

    def text(self) -> str:
        return "\n".join(self.lines) + "\n"


def render_document(presence: Presence, guesser: Guesser, events: list[ContentItem], gachas: list[ContentItem],
                    dangling: list[ContentItem], beyond: list[ContentKind]) -> Document:
    """The whole markdown document."""
    owners = events + gachas
    status: Status = {}
    fill_status(status, owners, presence)
    kinds = kind_counts(owners, status)
    part2: list[str] = []
    p2stats = write_part2(part2, presence, guesser, beyond, status) if beyond else []
    lines: list[str] = []
    w = lines.append
    write_intro(w, presence, p2stats)
    write_path_rules(w, presence, kinds)
    ne, ng = write_summary(w, events, gachas, kinds, status)
    w(rules.STANDIN_LEGEND + "\n")
    w("## Events\n")
    w("Ordered by first opening (master_event_term; else the area's window); weekly and undated areas last.\n")
    for o in sorted(ne, key=by_start):
        write_item_section(w, guesser, o, status)
    w("## Gacha banners\n")
    w("One section per `master_gacha.banner_id` (the list banner; step-up chains and their steps share one), "
      "ordered by the first row's `opened_at`.\n")
    for o in sorted(ng, key=by_start):
        write_item_section(w, guesser, o, status)
    if dangling:
        write_dangling(w, dangling)
    if part2:
        w("## Part 2: content beyond events and gacha blocked only by missing files\n")
        w(PART2_INTRO)
        w(rules.STANDIN_LEGEND + "\n")
        lines.extend(part2)
    return Document(lines, ne, ng, status)


def missing_paths_text(status: Status) -> str:
    """The distinct missing paths (logical names), sorted, one per line."""
    return "".join(p + "\n" for p in sorted(p for p, s in status.items() if not s))
