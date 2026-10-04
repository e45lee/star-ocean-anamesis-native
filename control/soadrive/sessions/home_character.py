"""Session `home-character`: how given characters look as the home character. For each --home role
(a master_role id or id_label) a fresh boot from a synthetic seed save (tools/make_test_seed.py: the
test seed's roster plus every --home role and --extra-roles, that role the home character), the
in-process server, soa -v (the client's file opens in the log); then at home:
  10-idle        a few seconds after the popups closed
  11-idle-long   25 s later (the idle motion's variations)
  12-talk, 13-talk-later   a tap on the character (the talk motion and its line), 1.5 s and 5 s after
  14-talk-2      a second tap (the next line)
  15-burst-NN    with --burst N: N idle shots 1 s apart before the first tap
  OUT/<label>.mp4 with --movie SECS: the home recorded by repeated shots (--movie-fps, the character
                 tapped at --movie-taps seconds), half size, H.264; the frames in OUT/<label>-frames/
  20-interactive, 21-interactive-talk, 22-interactive-later   会話モード (interactive mode), a tap there
  23-switched-2d, 24-switched-3d   (a character with a 3D home) its footer's 2D/3D変更 tapped twice:
                 checked by the server's Home3DAnd2DSwitching lines; a 2D-only one (home3d_disable,
                 without --home3d-all): checked that the client asked for the 2D home itself and
                 loaded the illustration
OUT/<label>/ holds each boot's shots, OUT/<label>.log its log; OUT/summary.txt per role its
master_person.home3d_disable, the files the client opened for it (model, Motion/home_*, the Home3D
parameters, the 2D illustration Image/<id>_fv..) and the requests sent. docs/home3d.md has the
client's rules: a home3d_disable character (2B, 9S, A2, ...) gets the 2D home, which the port shows
empty (Home3DAnd2DSwitching unanswered); --home3d-all (soa's debug option) clears the flag.
Prints "PASS: ..." when every boot reached home and its checks passed, else "FAIL: ..." (exit 1).

Usage: control/run.py home-character <soa> <out-dir> <scratch-dir> [--home ROLE]... [--extra-roles R,...]
         [--home3d-all] [--soa-arg FLAG]...
  (default --home: 2B, 9S, A2 (the NieR:Automata collab) and Evelysse (cp0002_b01a), an ordinary character, as a control)
Targets: port-inproc."""
import os
import re
import shutil
import sqlite3
import subprocess
import sys

from .. import proc
from ..flows import launch
from ..targets import Abort
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "a seed save through the in-process server's --seed"
WRAPPER = "control/run.py home-character"
DEFAULT_HOMES = ("role_cc0015_b01a_6551", "role_cc0016_b01a_6563", "role_cc0017_b01a_6572", "role_cp0002_b01a_6025")
INTERACTIVE = "90:740"  # 会話モード (interactive mode), left of the mascot
SWITCH_2D3D = "300:1225"  # 会話モード's footer: 2D/3D変更
CHARACTER = "364:620"  # the character's body at 729x1296 (2D illustration or 3D model)


def options(ap):
    common.port_options(ap, extra=False)
    ap.add_argument("--home", action="append", help="a home character's master_role id or id_label (repeatable)")
    ap.add_argument("--extra-roles", default="", help="more roles for the roster (comma-separated)")
    ap.add_argument("--character", default=CHARACTER, help="where to tap the character (X:Y)")
    ap.add_argument("--burst", type=int, default=0, help="N more idle shots 1 s apart (15-burst-NN), to see the motion")
    ap.add_argument("--movie", type=float, default=0, help="SECS: also record the home as OUT/<label>.mp4 (repeated shots)")
    ap.add_argument("--movie-fps", type=float, default=10, help="the movie's shot rate (default 10)")
    ap.add_argument("--movie-taps", default="24,31", help="seconds into the movie to tap the character (comma-separated)")
    ap.add_argument("--home3d-all", action="store_true", help="soa --home3d-all: the 3D home also for the 2D-only characters")
    ap.add_argument("--soa-arg", action="append", default=[], help="an extra soa flag (repeatable, e.g. -v)")


def seed_for(master, home, homes, extra, path):
    sys.path.insert(0, os.path.join(proc.REPO, "tools"))
    import make_test_seed
    db = sqlite3.connect("file:%s?mode=ro" % master, uri=True)
    k, _, home_id = make_test_seed.build(db, list(homes) + list(extra), home)
    k.save(path)
    row = db.execute("select p.id_label, p.home3d_disable from master_role r join master_person p on p.id = r.master_person_id "
                     "where r.id = ?", (home_id,)).fetchone()
    return home_id, row[0], bool(row[1])


def count(s, rx):
    """The client log's lines matching rx (the whole file)."""
    with open(s.client_log, errors="replace") as f:
        return sum(1 for ln in f if re.search(rx, ln))


def record_movie(s, o, out_mp4):
    """o.movie seconds of the home as repeated shots (o.movie_fps a second asked, the character
    tapped at o.movie_taps), sent as one batch (the client takes them at its own pace), then H.264
    with each frame shown for the time to the next shot (the files' mtimes: real time; ffmpeg's
    concat demuxer); True when written."""
    frames = os.path.join(os.path.dirname(out_mp4), os.path.splitext(os.path.basename(out_mp4))[0] + "-frames")
    shutil.rmtree(frames, ignore_errors=True)
    os.makedirs(frames)
    n = int(o.movie * o.movie_fps)
    gap = int(1000 / o.movie_fps)
    taps = sorted(int(float(x) * o.movie_fps) for x in o.movie_taps.split(",") if x.strip())
    batch = []
    for i in range(n):
        if i in taps:
            batch.append("tap:" + o.character)
        batch += ["shot:" + os.path.join(frames, "frame_%05d.png" % i), "wait:%d" % gap]
    # The client takes a shot per presented frame: two requested before one present keep only the
    # later, so a few frames are missing; the wait gives up on them after the movie's own length.
    s.send(batch, timeout=o.movie * 1.5 + 30)
    files = sorted(os.path.join(frames, f) for f in os.listdir(frames) if f.endswith(".png"))
    if len(files) < 2:
        s.note("movie: %d frames, nothing written" % len(files))
        return False
    times = [os.path.getmtime(f) for f in files]
    lst = os.path.join(frames, "frames.txt")
    with open(lst, "w") as f:
        for i, p in enumerate(files):
            d = times[i + 1] - times[i] if i + 1 < len(files) else 1.0 / o.movie_fps
            f.write("file '%s'\nduration %.4f\n" % (p, max(d, 0.001)))
        f.write("file '%s'\n" % files[-1])
    r = subprocess.run(["ffmpeg", "-y", "-loglevel", "error", "-f", "concat", "-safe", "0", "-i", lst, "-vf",
                        "scale=trunc(iw/4)*2:trunc(ih/4)*2", "-fps_mode", "vfr", "-c:v", "libx264", "-pix_fmt", "yuv420p", out_mp4],
                       capture_output=True, text=True)
    span = times[-1] - times[0]
    s.note("movie: %d frames over %.1f s (%.2f fps) -> %s%s" % (len(files), span, (len(files) - 1) / span if span else 0, out_mp4,
                                                              "" if r.returncode == 0 else ": " + r.stderr[-300:]))
    return r.returncode == 0


def main(o):
    homes = o.home or list(DEFAULT_HOMES)
    extra = [r for r in o.extra_roles.split(",") if r.strip()]
    master = os.path.join(proc.REPO, "data/basmaster-3.7.0.sqlite3")
    o.out, o.tmp = os.path.abspath(o.out), os.path.abspath(o.tmp)
    os.makedirs(o.tmp, exist_ok=True)
    summary, fails = [], []
    for home in homes:
        label = re.sub(r"[^A-Za-z0-9_]", "_", home)
        seed = os.path.join(o.tmp, label + "-seed.xml")
        home_id, person, no3d = seed_for(master, home, homes, extra, seed)
        cfg = common.port_config(o)
        cfg.client_args += ["-v"] + (["--home3d-all"] if o.home3d_all else []) + o.soa_arg
        cfg.seed = seed
        s = common.port_run(o, cfg, name=label)
        c = s.ctl

        def body(s):
            launch.title(s, "01-title")
            try:
                launch.login_to_home(s, "02-notice", "03-login-bonus", "04-home", "00-download-dialog", "00-download-done", None)
            except Abort as e:
                if "login popups" not in str(e) or not s.alive():
                    raise
            if o.movie:  # first: the idle from the start, then the taps
                record_movie(s, o, os.path.join(o.out, label + ".mp4"))
                c("wait:8000")
            c("wait:4000", s.shot_cmd("10-idle"), "wait:25000", s.shot_cmd("11-idle-long"))
            for i in range(o.burst):
                c("wait:1000", s.shot_cmd("15-burst-%02d" % i))
            c("tap:" + o.character, "wait:1500", s.shot_cmd("12-talk"), "wait:3500", s.shot_cmd("13-talk-later"), "wait:8000")
            c("tap:" + o.character, "wait:2000", s.shot_cmd("14-talk-2"), "wait:8000")
            c("tap:" + INTERACTIVE, "wait:4000", s.shot_cmd("20-interactive"), "tap:" + o.character, "wait:2000",
              s.shot_cmd("21-interactive-talk"), "wait:5000", s.shot_cmd("22-interactive-later"))
            # The home's mode (docs/home3d.md): a 2D-only character (home3d_disable, without
            # --home3d-all) makes the client send Home3DAnd2DSwitching(0) by itself and show the 2D
            # illustration (Image/<id>_fv..); for the others the footer's 2D/3D変更 switches to 2D
            # and back (the server's "Home3DAnd2DSwitching: 2D / 3D" lines).
            short = person.split("_")[0]
            if no3d and not o.home3d_all:
                s.check("the client asked for the 2D home by itself (Home3DAnd2DSwitching 2D)", count(s, r"Home3DAnd2DSwitching: 2D") >= 1)
                s.check("the 2D illustration loaded (Image/%s_fv*)" % short,
                        count(s, r"fopen\(\S*/download/Image/(etc2/)?%s_fv\S* -> .*\) = 0x" % short) >= 1)
            else:
                for mode, name in (("2D", "23-switched-2d"), ("3D", "24-switched-3d")):
                    before = count(s, r"Home3DAnd2DSwitching: " + mode)
                    c("tap:" + SWITCH_2D3D)
                    s.check("2D/3D変更 -> Home3DAnd2DSwitching %s" % mode,
                            s.poll(20, lambda: count(s, r"Home3DAnd2DSwitching: " + mode) > before))
                    c("wait:5000", s.shot_cmd(name))

        ok = common.drive(s, body)
        short = person.split("_")[0]  # cc0015: the illustrations and voices use the short id
        opened, other = set(), []
        for ln in open(s.client_log, errors="replace"):
            m = re.match(r"D/io: fopen\(\S*/files/download/(\S+) -> .*\) = (\S+)", ln)
            if m and (short in m.group(1) or m.group(1).startswith("Motion/home_")):
                opened.add("opened %s%s" % (m.group(1), "" if m.group(2) != "(nil)" else " (missing)"))
            elif re.search(r"I/server: request |Unhandled SIG|not found", ln) and "D/io" not in ln:
                other.append(ln.rstrip())
        lines = sorted(opened) + other
        summary.append("== %s (role %d, person %s, home3d_disable %d): %s" % (home, home_id, person, no3d, "home reached" if ok else "FAILED"))
        summary += lines[:200]
        if not ok:
            fails.append("%s: the boot didn't finish" % home)
        elif any(r.startswith("FAIL") for r in s.results):
            fails.append("%s: %d checks failed" % (home, sum(1 for r in s.results if r.startswith("FAIL"))))
    with open(os.path.join(o.out, "summary.txt"), "w") as f:
        f.write("\n".join(summary) + "\n")
    print("\n".join(ln for ln in summary if ln.startswith("==")))
    for f in fails:
        print("FAIL: " + f)
    if fails:
        return 1
    print("PASS: %d home characters shown (%s)" % (len(homes), ", ".join(homes)))
    return 0
