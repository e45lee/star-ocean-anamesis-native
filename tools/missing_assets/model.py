"""The records: a referenced asset file, a content item that references files, a guess, and part 2's
kinds and groups. Items and refs compare by identity (``eq=False``): two rows that look alike are
still two rows."""
from __future__ import annotations

from dataclasses import dataclass, field
from typing import Optional

#: Where a file was found: a source label (``presence.Source.label``), or None when missing.
Status = dict[str, Optional[str]]


@dataclass(eq=False)
class AssetRef:
    """One file a content item references, with every column and row that names it."""
    path: str      # logical path, e.g. ``Image/foo.aif`` (no quality folder)
    kind: str      # what the file is for, e.g. "event banner", "battle map (.asf)"
    cols: list[str]
    rows: list[str]  # id_labels of the referencing rows
    subject: str   # who / what the file shows or belongs to
    order: int     # display order within an item (rendering sorts by (order, path))


@dataclass
class MissionFiles:
    """A mission's label, display name and the files the local server's playability check needs."""
    label: str
    name: str
    gate: set[str]


@dataclass
class GachaRow:
    """One ``master_gacha`` row of a banner group."""
    label: str
    name: str
    opened_at: Optional[str]
    closed_at: Optional[str]


@dataclass(eq=False)
class ContentItem:
    """Something that references files: an event, a gacha banner (part 1) or a part-2 row."""
    typ: str       # "event", "gacha", "mission", "character", ...
    key: object    # master id (or the banner id for gacha groups)
    label: str
    ja: str
    en: str
    how: str       # where `en` came from: "tsv", "gl", "glossary", "same", "names", "none"
    start: str
    end: str
    extra: str     # a short note for the section's info line
    refs: dict[str, AssetRef] = field(default_factory=dict)  # by path, in insertion order
    missions: list[MissionFiles] = field(default_factory=list)  # events
    gachas: list[GachaRow] = field(default_factory=list)        # gacha banners
    picks: list[str] = field(default_factory=list)              # gacha pick-up names
    gate: set[str] = field(default_factory=set)  # part 2: the files the item's use needs

    def add(self, path: str, kind: str, col: str, row: str, subject: str = "", order: int = 0) -> None:
        """Record a reference; a path already referenced gains the column / row (first kind wins)."""
        ref = self.refs.get(path)
        if ref is None:
            self.refs[path] = AssetRef(path, kind, [col], [row], subject, order)
            return
        if col not in ref.cols:
            ref.cols.append(col)
        if row not in ref.rows:
            ref.rows.append(row)
        if subject and not ref.subject:
            ref.subject = subject

    def missing(self, status: Status) -> list[str]:
        """The referenced paths no source has."""
        return [p for p in self.refs if not status[p]]


@dataclass
class Guess:
    """What a missing file probably is."""
    text: str
    confidence: str  # "high" / "medium"
    evidence: str


@dataclass
class ContentGroup:
    """A part-2 group of rows under one heading (an area, a floor group, ...)."""
    ja: str
    en: str
    how: str
    note: str  # the master table / rule the rows come from
    items: list[ContentItem]


@dataclass
class ContentKind:
    """A part-2 kind of content (missions, characters, ...) with its groups."""
    title: str
    description: str
    groups: list[ContentGroup]

    def items(self) -> list[ContentItem]:
        return [o for g in self.groups for o in g.items]
