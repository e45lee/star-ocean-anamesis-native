#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""List the files that events and gacha banners of the 3.7.0 master reference but no source has.

  .venv/bin/python tools/missing_assets.py [--md docs/missing-assets-3.7.0.md] [--txt docs/missing-assets-3.7.0.txt]

The code is the package tools/missing_assets/ (its docstring: what it does, the layout, how to add a
path rule or a kind of content); --help lists the options.
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from missing_assets.cli import main  # noqa: E402  (the package beside this script)

if __name__ == "__main__":
    main()
