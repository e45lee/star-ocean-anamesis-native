"""Missing assets of the 3.7.0 master: which files events, gacha banners and the rest of the game
reference that no asset source has.

What it does
------------
It reads the 3.7.0 master (``data/basmaster-3.7.0.sqlite3``), turns what each content row
references into asset paths (the path rules), looks each path up in the asset sources (the 3.7.0
download, the 3.7.0 APK, the repo's stand-ins) and writes:

- ``docs/missing-assets-3.7.0.md``: a linked table of contents; part 1, every event and gacha
  banner with missing files (each event followed by its banners, then the banners without an
  event), with Japanese and English names and a best guess per file; part 2, the other content
  (missions, Sphere 211, characters, items, ...), which rows missing files block, and the
  unreleased / test rows counted apart;
- ``docs/missing-assets-3.7.0.txt``: the distinct missing paths of both parts, one per line;
- optionally a JSON dump (``--json``) and the untranslated name residue (``--residue``).

Everything is recomputed from the master and the sources; the output is deterministic.

How to run
----------
::

    .venv/bin/python tools/missing_assets.py            # regenerate docs/missing-assets-3.7.0.{md,txt}
    .venv/bin/python tools/missing_assets.py --help     # the sources and outputs can be overridden
    .venv/bin/python -m pytest -q tests/test_missing_assets.py

Layout (one responsibility per module)
--------------------------------------
``model``      the records: ``AssetRef`` (one referenced file), ``ContentItem`` (an event, a gacha
               banner, a part-2 row), ``Guess``, part 2's ``ContentKind`` / ``ContentGroup``.
``rules``      the asset path rules, each with its evidence label (a) master data, (b) client-side
               evidence, (d) assumption and a one-line reason; the stand-in verdict per path.
``presence``   the asset sources and the presence index; the AIF image header reader (ADLD / SLZ).
``names``      Japanese text and English name resolution (TSV, Global master, names_en.json,
               phrase glossary).
``master``     the master-DB index (lookup tables) and the subject names of roles, items, persons.
``references`` the shared reference collectors: banners and missions.
``events``     part 1: events (``master_event_area``).
``gachas``     part 1: gacha banners (``master_gacha`` grouped by ``banner_id``).
``associate``  part 1: which event a gacha banner belongs to (bonus characters, released together).
``beyond``     part 2: missions, Sphere 211, characters, items and the small kinds; the
               unreleased / test row rule.
``guess``      "what it probably is": the description, confidence and evidence per missing file.
``render``     the markdown and text writers (contents, explicit ``<a id>`` anchors from master labels).
``cli``        the command line.

How to add a path rule
----------------------
Add a ``PathRule`` to ``rules.py`` with its template, label and reason, and build paths with
``RULE.path(name)`` in the collector that reads the column. If the rule belongs in the document's
"Path rules" table, add a row to ``PATH_RULES_TABLE`` there too.

How to add a kind of content
----------------------------
Part 1 (owners with sections): write a collector like ``events.collect_events`` returning
``ContentItem`` objects and render them with ``render.write_item_section`` (give each section an
anchor from its master label via ``render.Anchors``).
Part 2 (rows that missing files block): add a function to ``beyond.py`` that turns one master row
into a ``ContentItem`` (``item.add(...)`` for every referenced file; ``item.gate`` for the files
its use needs) and register it in ``beyond.ROW_KINDS`` (one row = one item) or, for grouped kinds,
append a ``ContentKind`` in ``beyond.collect_beyond``. The renderer and the counts pick it up.
"""
import os
import sys

#: The repository root (tools/missing_assets/ is two levels below it).
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)
