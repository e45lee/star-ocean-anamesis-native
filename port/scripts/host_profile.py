#!/usr/bin/env python3
"""Self time per host C++ function inside native replacements, from a SOA_PROFILE_HOST=1 profile.

    SOA_PROFILE=DIR SOA_PROFILE_HOST=1 <soa run>     (writes DIR/host.tsv, see core/profile.cpp)
    port/scripts/host_profile.py DIR [DIR...] --soa build/port/soa [--top 80] [--grep REGEX]

The PCs are symbolized with `nm` of the soa executable (the one that ran: RelWithDebInfo keeps the
static functions). Transcribed bodies (a2c: f_<library offset>) are also given the guest function
at that offset (DIR/functions.tsv). Samples outside any symbol (libc, the JIT's code cache: none
are expected, the sampler only signals threads inside native replacements) show as "?".
"""
import argparse
import bisect
import collections
import os
import re
import subprocess
import sys


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('dirs', nargs='+')
    ap.add_argument('--soa', default='build/port/soa')
    ap.add_argument('--top', type=int, default=60)
    ap.add_argument('--grep', help='only functions matching this regex (after the ranking)')
    a = ap.parse_args()

    out = subprocess.run(['nm', '-n', '-S', '-C', '--defined-only', a.soa], capture_output=True, text=True, check=True).stdout
    starts, syms = [], []
    for line in out.splitlines():
        p = line.split(' ', 3)
        if len(p) == 4 and p[2] in 'tTwW':
            starts.append(int(p[0], 16))
            syms.append((int(p[1], 16), p[3]))
    guest = {}
    for d in a.dirs:
        ft = os.path.join(d, 'functions.tsv')
        if os.path.exists(ft):
            for line in open(ft):
                if line.startswith('#'):
                    continue
                p = line.rstrip('\n').split('\t')
                guest[int(p[0], 16)] = p[3]
    hist = collections.Counter()
    total = 0
    for d in a.dirs:
        for line in open(os.path.join(d, 'host.tsv')):
            if line.startswith('#'):
                continue
            pc, n = line.split()
            pc, n = int(pc, 16), int(n)
            total += n
            i = bisect.bisect_right(starts, pc) - 1
            name = '?'
            if i >= 0 and pc < starts[i] + max(syms[i][0], 1):
                name = syms[i][1]
            hist[name] += n
    print(f'# {total} host samples in native replacements')
    print(f'{"samples":>7}  {"%":>5}  function')
    shown = 0
    for name, n in hist.most_common():
        if a.grep and not re.search(a.grep, name):
            continue
        m = re.search(r'\bf_([0-9a-f]+)\(', name)
        extra = ''
        if m and int(m.group(1), 16) in guest:
            extra = '   = ' + guest[int(m.group(1), 16)]
        print(f'{n:7d}  {100.0 * n / max(total, 1):5.1f}  {name[:110]}{extra[:140]}')
        shown += 1
        if shown >= a.top:
            break


if __name__ == '__main__':
    sys.exit(main())
