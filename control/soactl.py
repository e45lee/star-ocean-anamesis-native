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
"""
import argparse
import os
import sys
import time


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("fifo")
    ap.add_argument("commands", nargs="+")
    ap.add_argument("--timeout", type=float, default=300)
    a = ap.parse_args()

    shots = {}
    for c in a.commands:
        if c.startswith("shot:"):
            path = os.path.abspath(c[5:])
            shots[path] = os.path.getmtime(path) if os.path.exists(path) else None
    cmds = ["shot:" + os.path.abspath(c[5:]) if c.startswith("shot:") else c for c in a.commands]

    if not os.path.exists(a.fifo):
        sys.exit(f"{a.fifo} doesn't exist; start soa with --control {a.fifo}")
    # Open without blocking forever: if soa has exited (or never started listening), there's no
    # reader and a plain open() would hang.
    deadline = time.monotonic() + a.timeout
    while True:
        try:
            fd = os.open(a.fifo, os.O_WRONLY | os.O_NONBLOCK)
            break
        except OSError:
            if time.monotonic() > deadline:
                sys.exit(f"no reader on {a.fifo} (is soa still running?)")
            time.sleep(0.2)
    os.set_blocking(fd, True)
    with os.fdopen(fd, "w") as f:
        f.write("\n".join(cmds) + "\n")

    deadline = time.monotonic() + a.timeout
    pending = dict(shots)
    while pending and time.monotonic() < deadline:
        for p, old in list(pending.items()):
            if os.path.exists(p) and os.path.getmtime(p) != old and os.path.getsize(p) > 0:
                # the PNG is written in one go; give it a moment to be complete
                time.sleep(0.2)
                print(p)
                del pending[p]
        time.sleep(0.2)
    if pending:
        sys.exit("timed out waiting for: " + ", ".join(pending))


if __name__ == "__main__":
    main()
