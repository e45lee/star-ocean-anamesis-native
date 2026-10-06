"""The command line: build the model from the master and the sources, write the outputs."""
from __future__ import annotations

import argparse
import dataclasses
import json
import os

from . import ROOT
from .associate import associate
from .beyond import collect_beyond
from .events import collect_events
from .gachas import collect_gachas
from .guess import Guesser
from .master import MasterIndex, open_master
from .model import ContentItem
from .names import Names
from .presence import STANDIN_LABEL, Presence, Source
from .render import Document, missing_paths_text, render_document

USAGE = """\
  .venv/bin/python tools/missing_assets.py [--db data/basmaster-3.7.0.sqlite3]
        [--download work/SOA-3.7.0-canonical-data.zip] [--apk apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk]
        [--standins standin-assets]
        [--gl data/basmaster-gl.sqlite3] [--names docs/missing-assets-names.tsv]
        [--md docs/missing-assets-3.7.0.md] [--txt docs/missing-assets-3.7.0.txt] [--json OUT] [--residue OUT]
"""


def rel(*parts: str) -> str:
    return os.path.join(ROOT, *parts)


def parse_args(argv=None) -> argparse.Namespace:
    ap = argparse.ArgumentParser(
        description="List the files that events and gacha banners of the 3.7.0 master reference but no source has.",
        usage=USAGE)
    ap.add_argument("--db", default=rel("data", "basmaster-3.7.0.sqlite3"))
    ap.add_argument("--download", default=rel("work", "SOA-3.7.0-canonical-data.zip"),
                    help="the 3.7.0 download: its zip (read in place) or an extracted folder")
    ap.add_argument("--apk", default=rel("apk", "STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk"))
    ap.add_argument("--standins", default=rel("standin-assets"))
    ap.add_argument("--gl", default=rel("data", "basmaster-gl.sqlite3"))
    ap.add_argument("--names", default=rel("docs", "missing-assets-names.tsv"))
    ap.add_argument("--md", default=rel("docs", "missing-assets-3.7.0.md"))
    ap.add_argument("--txt", default=rel("docs", "missing-assets-3.7.0.txt"),
                    help="the distinct missing paths (both parts), one per line, sorted")
    ap.add_argument("--json")
    ap.add_argument("--residue", help="write the Japanese names the glossary could not fully translate")
    return ap.parse_args(argv)


def open_presence(args: argparse.Namespace) -> Presence:
    """The asset sources in lookup order: the 3.7.0 download, the 3.7.0 APK, the repo's stand-ins."""
    return Presence([Source("download", args.download), Source("APK 3.7.0", args.apk),
                     Source(STANDIN_LABEL, args.standins)])


def write_file(path: str, text: str) -> None:
    os.makedirs(os.path.dirname(os.path.abspath(path)), exist_ok=True)
    with open(path, "w", encoding="utf-8") as f:
        f.write(text)


def json_dump(doc: Document, guesser: Guesser, events: list[ContentItem], gachas: list[ContentItem]) -> dict:
    """Every event and gacha banner with its files, their status and the guess for missing ones."""
    def item(o: ContentItem) -> dict:
        return dict(type=o.typ, key=o.key, label=o.label, ja=o.ja, en=o.en, start=o.start, end=o.end,
                    files=[dict(path=r.path, kind=r.kind, cols=r.cols, rows=r.rows,
                                status=doc.status[r.path] or "missing",
                                guess=list(dataclasses.astuple(guesser.guess(o, r))) if not doc.status[r.path] else None)
                           for r in o.refs.values()])
    return dict(events=[item(o) for o in events], gachas=[item(o) for o in gachas])


def main(argv=None) -> None:
    args = parse_args(argv)
    conn = open_master(args.db)
    names = Names(conn, args.gl, args.names)
    master = MasterIndex(conn, names)
    presence = open_presence(args)
    guesser = Guesser(presence)
    events = collect_events(master)
    gachas, dangling = collect_gachas(master)
    beyond = collect_beyond(master)
    doc = render_document(presence, guesser, events, gachas, dangling, beyond, associate(master, gachas))
    write_file(args.md, doc.text())
    if args.txt:
        write_file(args.txt, missing_paths_text(doc.status))
    if args.json:
        with open(args.json, "w", encoding="utf-8") as f:
            json.dump(json_dump(doc, guesser, events, gachas), f, ensure_ascii=False, indent=1)
    if args.residue:
        with open(args.residue, "w", encoding="utf-8") as f:
            for k, n in sorted(names.residue.items()):
                f.write(f"{k}\t{n}\n")
    missing = [p for p, s in doc.status.items() if not s]
    print(f"events {len(doc.events_missing)}/{len(events)} with missing files; gacha banners "
          f"{len(doc.gachas_missing)}/{len(gachas)}; distinct missing files {len(missing)}; "
          f"untranslated names {len(names.residue)}")
