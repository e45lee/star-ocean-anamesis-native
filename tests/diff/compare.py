"""The comparison of a flow's runs: each target against the reference (the emulator) on
  * the packet log (tools/compare_packets.py; --transport-neutral when the in-process route is one
    side, --mask-battle-log always),
  * the server's state at the end (state.diff: times and ids masked),
  * the milestone screenshots (screens.rmse against the reference's, a limit per screen),
  * the run's own milestones (each must PASS).
Writes the report and returns PASS/FAIL."""
import os
import subprocess
import sys

from soadrive import screens, state
from soadrive.proc import REPO


def packets(ref, run):
    cmd = [sys.executable, os.path.join(REPO, "tools/compare_packets.py"), "--labels", ref.target, run.target, "--mask-battle-log",
           "--collapse-title-repeat", "--float-time-sync", ref.packets, run.packets]
    if "port-inproc" in (ref.target, run.target):
        cmd.insert(2, "--transport-neutral")
    r = subprocess.run(cmd, capture_output=True, text=True)
    return r.returncode == 0, (r.stdout + r.stderr).rstrip()


def state_diff(ref, run):
    if not os.path.exists(ref.state_db) or not os.path.exists(run.state_db):
        return False, "missing: " + ", ".join(x for x in (ref.state_db, run.state_db) if not os.path.exists(x))
    d = state.diff(ref.state_db, run.state_db, ref.target, run.target)
    return not d, "\n".join(d) if d else "identical (times and ids masked; not compared: %s)" % ", ".join(sorted(state.SKIP_TABLES))


def screen_table(ref, run, limits):
    rows, ok = [], True
    for name, spec in limits.items():
        # a limit, or (limit, regions masked on both: screens.HOME_CHARACTER)
        limit, mask = spec if isinstance(spec, tuple) else (spec, ())
        a, b = os.path.join(ref.shots, name + ".png"), os.path.join(run.shots, name + ".png")
        if not os.path.exists(a) or not os.path.exists(b):
            missing = [x for x, p in ((ref.target, a), (run.target, b)) if not os.path.exists(p)]
            # a screen neither run took (e.g. no LOGIN BONUS popup that day) is no difference
            gated = limit is not None and len(missing) == 1
            rows.append((name, None, limit, not gated, "missing in " + ", ".join(missing)))
            ok &= not gated
            continue
        d = screens.rmse(a, b, mask)
        good = limit is None or d <= limit
        ok &= good
        rows.append((name, d, limit, good, "regions masked" if mask else ""))
    return ok, rows


def report(flow, runs, ref_target, path, expected=None):
    """runs: {target: Run}; expected: the targets that should have run (default: those in runs).
    Returns True when every compared item passes; a target without a run, or a comparison without
    the reference run, FAILs (it compared nothing)."""
    lines, ok = [], True
    lines.append("# tests/diff flow %s" % flow.NAME)
    lines.append("")
    lines.append("## Runs (milestones)")
    for t in expected or ():
        if t not in runs:
            lines.append("- %s: FAIL: no run (its driver failed before it started; see the tests/diff log)%s" % (
                t, ": nothing was compared with this reference" if t == ref_target else ""))
            ok = False
    if not runs:
        lines.append("- FAIL: no runs")
        ok = False
    for t, r in runs.items():
        lines.append("- %s: %s in %ds (%s)" % (t, "FAIL" if r.failed else "PASS", r.elapsed_total, r.dir))
        for x in r.results:
            if x.startswith("FAIL"):
                lines.append("    " + x)
        ok &= not r.failed
    ref = runs.get(ref_target)
    for t, r in runs.items():
        if r is ref or ref is None:
            continue
        lines.append("")
        lines.append("## %s vs %s" % (r.target, ref.target))
        p_ok, p_txt = packets(ref, r)
        s_ok, s_txt = state_diff(ref, r)
        sc_ok, rows = screen_table(ref, r, flow.SCREENS)
        lines.append("")
        lines.append("### packets: %s" % ("PASS" if p_ok else "FAIL"))
        lines.extend("    " + x for x in p_txt.splitlines())
        lines.append("")
        lines.append("### server state at the end: %s" % ("PASS" if s_ok else "FAIL"))
        lines.extend("    " + x for x in s_txt.splitlines())
        lines.append("")
        lines.append("### screenshots (RMSE against %s): %s" % (ref.target, "PASS" if sc_ok else "FAIL"))
        lines.append("    %-24s %8s %7s  %s" % ("screen", "rmse", "limit", ""))
        for name, d, limit, good, why in rows:
            lines.append("    %-24s %8s %7s  %s%s" % (name, "-" if d is None else "%.4f" % d, "info" if limit is None else "%.2f" % limit,
                                                    "ok" if good else "FAIL", (" (" + why + ")") if why else ""))
        ok &= p_ok and s_ok and sc_ok
    lines.append("")
    lines.append("%s %s" % ("PASS" if ok else "FAIL", flow.NAME))
    with open(path, "w") as f:
        f.write("\n".join(lines) + "\n")
    return ok
