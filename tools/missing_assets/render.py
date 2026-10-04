"""The markdown document (part 1: events and gacha banners; part 2: other content) and the plain list
of missing paths. `status` maps every referenced path to the source that has it (None = missing)."""
from __future__ import annotations

import collections
import os
import re
from dataclasses import dataclass

from . import ROOT, rules
from .associate import RULE_AMBIGUOUS, RULE_BONUS, RULE_RELEASE, Association
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


class Anchors:
    """Explicit `<a id>` anchors made from master labels: stable across runs and unique (a clash is
    an error, not a silent suffix)."""

    def __init__(self):
        self.used: set[str] = set()

    @staticmethod
    def make(prefix: str, key) -> str:
        return prefix + re.sub(r"[^A-Za-z0-9_-]", "-", str(key))

    def tag(self, anchor: str) -> str:
        """The inline anchor for a heading (registers it)."""
        if anchor in self.used:
            raise ValueError(f"duplicate anchor {anchor!r}")
        self.used.add(anchor)
        return f'<a id="{anchor}"></a>'


def link_text(s: str) -> str:
    return md_escape(s).replace("[", "\\[").replace("]", "\\]")


def item_title(o: ContentItem) -> str:
    return f"{md_escape(o.ja) or '(no name)'} — {md_escape(o.en) or '(no name)'}"


def event_anchor(o: ContentItem) -> str:
    return Anchors.make("ev-", o.label)


def gacha_anchor(o: ContentItem) -> str:
    return Anchors.make("g-", o.key)


# fixed section anchors
A_CONTENTS, A_ABOUT, A_PATH_RULES, A_SUMMARY = "contents", "about", "path-rules", "summary"
A_EVENTS, A_UNASSOCIATED, A_DANGLING, A_PART2 = "events", "unassociated-banners", "dangling-banners", "part-2"


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
    unreleased: int
    usable_missing_some: int
    blocking_pairs: collections.Counter     # top folder -> (blocked row, missing gating file) pairs
    blocking_files: collections.Counter     # top folder -> distinct missing gating files

    def blocking_types(self) -> str:
        """`Image 12 (30), BG 3 (18)`: distinct files per type, (row, file) pairs in parentheses."""
        kinds = sorted(self.blocking_files, key=lambda k: (-self.blocking_files[k], k))
        return ", ".join(f"{k} {self.blocking_files[k]} ({self.blocking_pairs[k]})" for k in kinds) or "—"


def part2_anchor(title: str) -> str:
    return "p2-" + re.sub(r"[^a-z0-9]+", "-", title.lower()).strip("-")


def _blocking(items: list[ContentItem], status: Status) -> tuple[collections.Counter, collections.Counter]:
    pairs = collections.Counter(p.split("/")[0] for o in items for p in o.gate if not status[p])
    files = collections.Counter(p.split("/")[0] for p in {p for o in items for p in o.gate if not status[p]})
    return pairs, files


def write_part2(out: list[str], presence: Presence, guesser: Guesser, kinds: list[ContentKind],
                status: Status, anchors: "Anchors") -> list[KindStats]:
    """Part 2's sections into `out` (fills `status`); returns the summary rows. Unreleased / test
    rows count apart from usable and blocked and are listed under their own heading."""
    w = out.append
    stats = []
    for kind in kinds:
        items = kind.items()
        fill_status(status, items, presence)
        real = [o for o in items if not o.unreleased]
        test = [o for o in items if o.unreleased]
        blocked = [o for o in real if any(not status[p] for p in o.gate)]
        extra = [o for o in real if o not in blocked and has_missing(o, status)]
        stats.append(KindStats(kind.title, len(items), len(real) - len(blocked), len(blocked), len(test), len(extra),
                               *_blocking(blocked, status)))
        w(f"### {anchors.tag(part2_anchor(kind.title))}{kind.title}\n")
        w(kind.description + "\n")
        w(f"{len(items)} rows: **{len(real) - len(blocked)} usable** (every gating file present), "
          f"**{len(blocked)} blocked by missing files**; {len(extra)} of the usable ones miss only non-blocking files"
          + (f"; **{len(test)} unreleased / test rows**, counted apart (below)" if test else "") + ".\n")
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
                w("Blocked: " + _row_names(gb) + "\n")
            _write_part2_table(w, guesser, gb + gx, status)
        test_missing = [o for o in test if has_missing(o, status)]
        if test_missing:
            w(f"#### {kind.title}: unreleased / test rows\n")
            w("Rows that were never really available, so their missing files block nothing that was played: "
              + "; ".join(f"`{o.label}` {md_escape(o.ja)}" + (f" ({md_escape(o.en)})" if o.en and o.en != o.ja else "")
                          + f" — {o.unreleased}" for o in test_missing[:BLOCKED_NAMES_SHOWN])
              + (f"; … (+{len(test_missing) - BLOCKED_NAMES_SHOWN})" if len(test_missing) > BLOCKED_NAMES_SHOWN else "")
              + "\n")
            _write_part2_table(w, guesser, test_missing, status)
    return stats


def _row_names(items: list[ContentItem]) -> str:
    return ("; ".join(f"`{o.label}` {md_escape(o.ja)}" + (f" ({md_escape(o.en)})" if o.en and o.en != o.ja else "")
                      for o in items[:BLOCKED_NAMES_SHOWN])
            + (f"; … (+{len(items) - BLOCKED_NAMES_SHOWN})" if len(items) > BLOCKED_NAMES_SHOWN else ""))


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


def write_header(w) -> None:
    w("# Missing event and gacha assets in 3.7.0\n")
    w("**Generated file — do not edit by hand.** Regenerate with:\n")
    w("```\n.venv/bin/python tools/missing_assets.py\n```\n")


@dataclass
class Part1Layout:
    """Part 1's order: events (each with its banners), then the banners without an event."""
    events: list[ContentItem]
    banners_of: dict[str, list[ContentItem]]  # event label -> its banners with missing files
    unassociated: list[ContentItem]


def part1_layout(events_missing: list[ContentItem], all_events: list[ContentItem],
                 gachas_missing: list[ContentItem], association: Association) -> Part1Layout:
    """An event is listed when it or one of its banners misses files; every list by first opening."""
    banners_of = {e.label: sorted(association.banners_of(e.label, gachas_missing), key=by_start) for e in all_events}
    shown = [e for e in all_events if e in events_missing or banners_of[e.label]]
    unassociated = [g for g in gachas_missing if g.key not in association.event_of]
    return Part1Layout(sorted(shown, key=by_start), {e.label: banners_of[e.label] for e in shown},
                       sorted(unassociated, key=by_start))


def _toc_entry(o: ContentItem, anchor: str, status: Status) -> str:
    when = o.start[:10] if o.start else "undated"
    return f"[{link_text(o.ja or '(no name)')} — {link_text(o.en or '(no name)')}](#{anchor}) · {when} · " \
           f"{len(o.missing(status))} missing"


def write_toc(w, layout: Part1Layout, dangling: list[ContentItem], kinds: list[ContentKind], status: Status,
              anchors: Anchors) -> None:
    """The contents: part 1's events with their banners, the banners without an event (one line per
    year), part 2's kinds."""
    w(f"## {anchors.tag(A_CONTENTS)}Contents\n")
    w(f"- [About this list](#{A_ABOUT}) (sources, names, guesses; part 2's summary)")
    w(f"- [Path rules and how they were checked](#{A_PATH_RULES})")
    w(f"- [Summary: missing file references per kind and year](#{A_SUMMARY})")
    nested = sum(len(b) for b in layout.banners_of.values())
    w(f"- [Events and their gacha banners](#{A_EVENTS}): {len(layout.events)} events, {nested} banners")
    for e in layout.events:
        w(f"  - {_toc_entry(e, event_anchor(e), status)}")
        for g in layout.banners_of[e.label]:
            w(f"    - {_toc_entry(g, gacha_anchor(g), status)}")
    w(f"- [Gacha banners without an event](#{A_UNASSOCIATED}): {len(layout.unassociated)} banners")
    by_year = collections.defaultdict(list)
    for g in layout.unassociated:
        by_year[year_of(g)].append(g)
    for y in sorted(by_year, key=lambda y: (y == UNDATED, y)):
        w(f"  - {y}: " + ", ".join(f"[{link_text(g.en or g.ja or g.label)}](#{gacha_anchor(g)})" for g in by_year[y]))
    if dangling:
        w(f"- [Gacha rows whose banner_id has no master_banner row](#{A_DANGLING})")
    if kinds:
        w(f"- [Part 2: content beyond events and gacha blocked only by missing files](#{A_PART2})")
        for k in kinds:
            w(f"  - [{k.title}](#{part2_anchor(k.title)})")
    w("")


def write_intro(w, presence: Presence, p2stats: list[KindStats], anchors: Anchors) -> None:
    w(f"## {anchors.tag(A_ABOUT)}About this list\n")
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
          "missing files block. Usable / blocked master rows; unreleased / test rows are counted apart, so "
          "\"blocked\" means content that was really available:\n")
        w("| Content | Rows | Usable | Blocked | Unreleased / test | "
          "Blocking file types: distinct missing files (blocked row × file pairs) |")
        w("|---|---|---|---|---|---|")
        for st in p2stats:
            w(f"| {st.title} | {st.rows} | {st.usable} | {st.blocked} | {st.unreleased} | {st.blocking_types()} |")
        w("")
        w("Unreleased / test rows ((d), from the master's dates and names): a row open for at most an hour "
          "(the roles of 2017-05-20 04:00-05:00: Idol Tika, wolf T'nique, Seaside Shimada), a dummy or test "
          "name (ダミー, テスト), or a mission of an area with no `master_area` row. Each kind lists them under "
          "their own heading.\n")
        w("So yes: the blocked rows above would run with their files back. Blocked by 2D images only (icons, "
          "banners, portraits), they would run with made-up stand-ins too; blocked by battle maps, models or "
          "story scripts, they need the real files (a stand-in map or model would only be another one under the "
          "same name). Details per row and file are in part 2.\n")


def write_path_rules(w, presence: Presence, kinds: dict, anchors: Anchors) -> None:
    w(f"## {anchors.tag(A_PATH_RULES)}Path rules and how they were checked\n")
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


def write_summary(w, events, gachas, kinds: dict, status: Status, anchors: Anchors) -> tuple[list, list]:
    """The per-kind / per-year summary; returns (events, gacha banners) with missing files."""
    owners = events + gachas
    years = sorted({year_of(o) for o in owners}, key=lambda y: (y == UNDATED, y))
    distinct_missing = collections.defaultdict(set)
    for o in owners:
        for p in o.missing(status):
            distinct_missing[o.typ].add(p)
    w(f"## {anchors.tag(A_SUMMARY)}Summary: missing file references per kind and year\n")
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


def write_item_section(w, guesser: Guesser, o: ContentItem, status: Status, level: int = 3, anchor: str = "") -> None:
    """One event's or gacha banner's section: heading (at `level`, with `anchor`), info line,
    missing files, stand-ins."""
    miss = [r for r in o.refs.values() if not status[r.path]]
    stand = [r for r in o.refs.values() if status[r.path] == STANDIN_LABEL]
    dates = f"{o.start or '—'} → {o.end or '—'}" if (o.start or o.end) else "undated"
    w(f"{'#' * level} {anchor}{item_title(o)}{NAME_SOURCE_MARK.get(o.how, '')}\n")
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


def write_dangling(w, dangling: list[ContentItem], anchors: Anchors) -> None:
    w(f"## {anchors.tag(A_DANGLING)}Gacha rows whose banner_id has no master_banner row\n")
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


def association_note(association: Association) -> str:
    n = association.by_rule
    return (f"Banners placed by the bonus-character rule: {n[RULE_BONUS]}; released together: {n[RULE_RELEASE]}; "
            f"several candidate events (left unassociated): {n[RULE_AMBIGUOUS]}; no candidate: {n['none']} "
            f"(all banners, with or without missing files; {association.excluded} of the unplaced ones are not event "
            "draws and skip rule 2).")


def render_document(presence: Presence, guesser: Guesser, events: list[ContentItem], gachas: list[ContentItem],
                    dangling: list[ContentItem], beyond: list[ContentKind], association: Association) -> Document:
    """The whole markdown document."""
    owners = events + gachas
    status: Status = {}
    fill_status(status, owners, presence)
    kinds = kind_counts(owners, status)
    anchors = Anchors()
    part2: list[str] = []
    p2stats = write_part2(part2, presence, guesser, beyond, status, anchors) if beyond else []
    body: list[str] = []
    w = body.append
    write_intro(w, presence, p2stats, anchors)
    write_path_rules(w, presence, kinds, anchors)
    ne, ng = write_summary(w, events, gachas, kinds, status, anchors)
    layout = part1_layout(ne, events, ng, association)
    w(rules.STANDIN_LEGEND + "\n")
    w(f"## {anchors.tag(A_EVENTS)}Events and their gacha banners\n")
    w("Events ordered by first opening (master_event_term; else the area's window); weekly and undated areas "
      "last. Each event is followed by its gacha banners (one per `master_gacha.banner_id`: the list banner; "
      "step-up chains and their steps share one), ordered by the first row's `opened_at`. An event is listed when "
      "it or one of its banners misses files, so this part can list more events than the summary's count of "
      "events with missing files.\n")
    w("Which event a banner belongs to: the master has no gacha -> event column, so two rules join what it "
      "records, the first giving exactly one event wins. (1) **Bonus characters** ((a) the join, (d) the time "
      "check): one of the event's bonus characters (`master_mission_character_bonus.master_role_category_id`, "
      "its `master_area_id` = the event's `master_event_area.id`) is a pick-up of the banner (`master_gacha_image` "
      "content_type 2, `master_gacha_pickup`; by `master_role.role_category_id`), and the banner opens inside one "
      "of the event's windows; several such events: those also passing (2). (2) **Released together** ((d)): "
      "the banner opens within an hour of the first window start of exactly one story event (an event with a "
      "talk-script mission). Rule 2 skips banners that are not event draws ((a) the columns, (d) what they mean): "
      "every gacha row is a step-up row (`is_stepup`), a ticket draw (not a box, `coin` 0, paid with "
      "`ticket_item_id`) or a free limited draw (not a box, `coin` 0, no ticket, `limit_count` > 0: download "
      "milestone and campaign \"once per person\" draws); box draws paid with event coins stay in. A banner_id reused for a later release is placed by its earliest opening. "
      + association_note(association) + "\n")
    for e in layout.events:
        write_item_section(w, guesser, e, status, 3, anchors.tag(event_anchor(e)))
        for g in layout.banners_of[e.label]:
            write_item_section(w, guesser, g, status, 4, anchors.tag(gacha_anchor(g)))
    w(f"## {anchors.tag(A_UNASSOCIATED)}Gacha banners without an event\n")
    w("Banners that neither rule places (standard, step-up, ticket and milestone banners, reruns without an "
      "event, and banners with several candidate events), ordered by the first row's `opened_at`.\n")
    for g in layout.unassociated:
        write_item_section(w, guesser, g, status, 3, anchors.tag(gacha_anchor(g)))
    if dangling:
        write_dangling(w, dangling, anchors)
    if part2:
        w(f"## {anchors.tag(A_PART2)}Part 2: content beyond events and gacha blocked only by missing files\n")
        w(PART2_INTRO)
        w(rules.STANDIN_LEGEND + "\n")
        body.extend(part2)
    lines: list[str] = []
    write_header(lines.append)
    write_toc(lines.append, layout, dangling, beyond, status, anchors)
    return Document(lines + body, ne, ng, status)


def missing_paths_text(status: Status) -> str:
    """The distinct missing paths (logical names), sorted, one per line."""
    return "".join(p + "\n" for p in sorted(p for p, s in status.items() if not s))
