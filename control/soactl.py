#!/usr/bin/env -S sh -c 'exec "${0%/*}/../tools/py" "$0" "$@"'
"""Drive a running `soa --control FIFO` instance.

Usage: soactl.py FIFO COMMAND...
       soactl.py tcp:HOST:PORT COMMAND...   (--control tcp:HOST:PORT; e.g. a Windows .exe from WSL;
                                             add --windows-paths to send shot:PATH as a Windows path)

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
import sys

from soadrive import fifo


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("fifo")
    ap.add_argument("commands", nargs="+")
    ap.add_argument("--timeout", type=float, default=300)
    ap.add_argument("--windows-paths", action="store_true", help="shot:PATH as the Windows spelling (soadrive/winhost.py)")
    a = ap.parse_args()
    if a.windows_paths:
        from soadrive import winhost
        fifo.CLIENT_PATH[a.fifo] = winhost.winpath
    if not fifo.listening(a.fifo):
        sys.exit(f"{a.fifo} isn't there; start soa with --control {a.fifo}")
    sent, pending = fifo.deliver(a.fifo, a.commands, a.timeout, on_shot=lambda p: print(p, flush=True))
    if not sent:
        sys.exit(f"no reader on {a.fifo} (is soa still running?)")
    if pending:
        sys.exit("timed out waiting for: " + ", ".join(pending))


if __name__ == "__main__":
    main()
