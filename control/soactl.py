#!/usr/bin/env python3
"""Drive a running `soa --control FIFO` instance.

Usage: soactl.py FIFO COMMAND...

Commands (coordinates are window pixels):
  tap:X:Y  drag:X1:Y1:X2:Y2[:MS]  wheel:X:Y:DY  back  text:STRING
  shot:PATH  resize:W:H  fullscreen  quit
  wait:MS    pause the queue inside the game, so timing is exact

All commands are sent in one write and run in order by the game's main loop. The script
returns once every screenshot in the batch has been written (or after --timeout seconds).

Example:
  soactl.py /tmp/soa.fifo tap:364:980 wait:8000 shot:/tmp/home.png

A thin CLI over control/soadrive/fifo.py (the driver library).
"""
import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from soadrive import fifo  # noqa: E402


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("fifo")
    ap.add_argument("commands", nargs="+")
    ap.add_argument("--timeout", type=float, default=300)
    a = ap.parse_args()
    if not os.path.exists(a.fifo):
        sys.exit(f"{a.fifo} doesn't exist; start soa with --control {a.fifo}")
    sent, pending = fifo.deliver(a.fifo, a.commands, a.timeout, on_shot=lambda p: print(p, flush=True))
    if not sent:
        sys.exit(f"no reader on {a.fifo} (is soa still running?)")
    if pending:
        sys.exit("timed out waiting for: " + ", ".join(pending))


if __name__ == "__main__":
    main()
