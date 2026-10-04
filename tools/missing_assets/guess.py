""""What it probably is": a description, confidence and evidence for a missing file, inferred (d)
from the referencing column and row, the subject (gacha title, pick-up role / weapon, mission,
person) and the size / format of existing images of the same name pattern (digits folded to `#`).

Confidence: high = column and sibling pattern agree; medium = subject or size inferred (siblings
disagree, a family pattern, or the panel's subject comes from the pool)."""
from __future__ import annotations

import collections
import re
from dataclasses import dataclass, field
from typing import Optional

from .model import AssetRef, ContentItem, Guess
from .presence import ImageInfo, Presence, image_info

#: How many existing siblings are read: the first and last N by name (all when at most 2N).
SIBLING_SAMPLE = 3
#: How many sizes the description shows (most common first).
SIZES_SHOWN = 2
#: How many pick-ups / rows a description names.
PICKS_SHOWN = 3
#: A mission-board background named after a home map: `00_<map>_...`.
HOME_MAP_BACKGROUND_RE = re.compile(r"00_(bm\d+_b\d+[a-z])_")
#: A name pattern with a letter prefix (`bbc#_#_#`): with no sibling, try other prefixes (`bbg#_#_#`).
LETTER_PREFIX_RE = re.compile(r"[A-Za-z]+#")


def name_pattern(name: str) -> str:
    """The name with every run of digits folded to `#`."""
    return re.sub(r"\d+", "#", name)


def image_stem(path: str) -> str:
    """`Image/<stem>.aif` -> `<stem>`."""
    return path[len("Image/"):-len(".aif")]


@dataclass
class SiblingSizes:
    """Existing images of a missing image's name pattern: the pattern shown (`*<rest>` for a letter
    family), how many exist, and (name, size) of the ones read."""
    pattern: str
    count: int
    examples: list[tuple[str, ImageInfo]] = field(default_factory=list)


class Guesser:
    """Guesses per missing file; sibling sizes are cached per name pattern."""

    def __init__(self, presence: Presence):
        self.presence = presence
        self._siblings: dict[str, SiblingSizes] = {}

    # -------------------------------------------------------- sibling sizes
    def _existing_images(self) -> list[tuple[str, object]]:
        return [(image_stem(p), s) for s in self.presence.real_sources() for p in s.files
                if p.startswith("Image/") and p.endswith(".aif")]

    def _read_sizes(self, stems: list[str], dedupe: bool) -> list[tuple[str, ImageInfo]]:
        real = self.presence.real_sources()
        got: list[tuple[str, ImageInfo]] = []
        for n in stems:
            src = next(s for s in real if f"Image/{n}.aif" in s.files)
            info = image_info(src, f"Image/{n}.aif")
            if info and (not dedupe or (n, info) not in got):
                got.append((n, info))
        return got

    def sibling_sizes(self, path: str) -> Optional[SiblingSizes]:
        """Sizes of existing images of the same name pattern (the first and last 3 by name); with
        none and a letter prefix, of the letter family (`bbc#_#_#` -> `bbg#_#_#` and kin)."""
        if not path.startswith("Image/"):
            return None
        pat = name_pattern(image_stem(path))
        if pat in self._siblings:
            return self._siblings[pat]
        existing = self._existing_images()
        have = sorted({n for n, _ in existing if name_pattern(n) == pat})
        sample = have[:SIBLING_SAMPLE] + have[-SIBLING_SAMPLE:] if len(have) > 2 * SIBLING_SAMPLE else have
        result = SiblingSizes(pat, len(have), self._read_sizes(sample, dedupe=True))
        if not have and LETTER_PREFIX_RE.match(pat):
            rest = re.sub(r"^[A-Za-z]+", "", pat)
            family = sorted({n for n, _ in existing if self._in_letter_family(n, pat, rest)})
            if family:
                result = SiblingSizes("*" + rest, len(family), self._read_sizes(family[:SIBLING_SAMPLE], dedupe=False))
        self._siblings[pat] = result
        return result

    @staticmethod
    def _in_letter_family(name: str, pat: str, rest: str) -> bool:
        """`name` is letters + `rest` (digits folded) and starts with the pattern's first letter."""
        np = name_pattern(name)
        return bool(re.fullmatch(r"[A-Za-z]+", np[:-len(rest)] or "-")) and np.endswith(rest) and np[0] == pat[0]

    # -------------------------------------------------------- the guess
    def guess(self, item: ContentItem, ref: AssetRef) -> Guess:
        """What `ref` (missing, referenced by `item`) probably is."""
        conf, evidence = "high", []
        size = ""
        siblings = self.sibling_sizes(ref.path)
        if siblings:
            dims = collections.Counter(f"{i.width}×{i.height} {i.format}" for _, i in siblings.examples)
            if dims:
                size = " / ".join(d for d, _ in dims.most_common(SIZES_SHOWN))
                first_name, first = siblings.examples[0]
                evidence.append(f"{siblings.count} existing `{siblings.pattern}` (e.g. `{first_name}`: "
                                f"{first.width}×{first.height})")
                if len(dims) > 1 or siblings.pattern.startswith("*"):
                    conf = "medium"
            else:
                conf = "medium"
                evidence.append(f"no existing `{siblings.pattern}` file")
        text, conf = describe(item, ref, conf, evidence)
        if size:
            text += f"; {size}"
        return Guess(text, conf, "; ".join(evidence))


def _medium_unless_lower(conf: str) -> str:
    return "medium" if conf == "high" else conf


def _rows(rows: list[str], n: int) -> str:
    return ", ".join(rows[:n]) + ("…" if len(rows) > n else "")


def describe(item: ContentItem, ref: AssetRef, conf: str, evidence: list[str]) -> tuple[str, str]:
    """The description by the ref's kind; returns (text, confidence) and may add evidence."""
    k, subj = ref.kind, ref.subject
    name = ref.path.split("/", 1)[1].rsplit(".", 1)[0]
    owner = item.en or item.ja
    picks = "; ".join(item.picks[:PICKS_SHOWN])
    if k == "gacha list banner":
        return f"list banner for the gacha \"{owner}\"" + (f", featuring {picks}" if item.picks else ""), conf
    if k.startswith("pick-up panel (view") or k.startswith("main panel"):
        if k.startswith("pick-up"):
            return f"pick-up panel for {subj}", conf
        t = f"main (first) panel of \"{owner}\""
        if item.picks:
            return t + f" showing {picks}", _medium_unless_lower(conf)
        return t, conf
    if k.startswith("pick-up panel"):  # image1..4 of the HTML-era screen
        n = int(re.search(r"panel (\d)", k).group(1))
        t = f"pick-up panel {n} of \"{owner}\""
        if len(item.picks) >= n:
            return t + f", probably {item.picks[n - 1]}", "medium"
        if item.picks:
            return t + f" (pick-ups: {picks})", "medium"
        return t, conf
    if k in ("event banner", "event banner (dated replacement)"):
        return f"banner for the event \"{owner}\"", conf
    if k.startswith("home / notice banner"):
        evidence.append(f"banner row `{ref.rows[0]}`")
        return f"home-screen / notice banner announcing \"{owner}\"", conf
    if k == "event list banner":
        return f"event list banner for \"{owner}\"", conf
    if k == "mission-board map background":
        t = f"mission-board (event map) background for \"{owner}\""
        m = HOME_MAP_BACKGROUND_RE.match(name)
        if m:
            return t + f", a picture of home map `{m.group(1)}`", _medium_unless_lower(conf)
        return t, conf
    if k == "story scene script":
        evidence.append("path rule (b)")
        return f"story scene command script for mission {ref.rows[0]} \"{subj}\"", conf
    if k == "story dialogue text pack":
        evidence.append("path rule (b)")
        return f"dialogue text for story chapter `{name}` (missions {_rows(ref.rows, 3)})", conf
    if k.startswith("battle map"):
        return f"3D battle map `{name}` for stage(s) {_rows(ref.rows, 2)}", conf
    if k.startswith("gacha scene map"):
        return f"{k}: the draw scene's backdrop `{name}`", conf
    if "BGM" in k:
        return f"{k} for \"{subj}\" (stage {ref.rows[0]})", conf
    if k == "event menu voice pack":
        return f"voice lines of the event menu ({subj})", conf
    if k.startswith("enemy"):
        evidence.append(f"party `{ref.rows[0]}`")
        return f"{k} of {subj}", conf
    if k in ("boss icon", "world boss icon"):
        return f"{k} ({subj})", conf
    return k + (f" of {subj}" if subj else ""), conf
