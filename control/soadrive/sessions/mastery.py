"""Session `mastery`: キャラクター > マスタリー (CMasteryTop) under the local server, in-process or
soa-server (docs/server-rules.md#mastery). The state is planted before the first boot: the seed
save's player (a one-request soa-server replay of Login, the session's seed and RNG) with a master-type
role and a role of its category without one at LV70, the materials of their mastery type's trainings
and a few pass medals (item_Mastery_01). Then, at home:
  道場1 -> 師匠 and 弟子 picked -> 決定 (TrainMastery pairing), the five trainings (the first four with
  the material cards, the fifth with the pass medal) -> 皆伝 (the reward dialog), 皆伝師弟 listed;
then a second boot on the same phone: the マスタリー screen again (GetMasteryInfo: the pair kept,
in the 皆伝 list), 師弟解消 (ResetMastery). Milestones are the server's log lines (both targets):
"TrainMastery: paired ...", "TrainMastery: disciple ... training N/5", "GetMasteryInfo: N pair(s)",
"ResetMastery: parted ...". Screenshots in OUT/shots and OUT/again/; "PASS: ..." / "FAIL: ..." per
check and exit 1 on a failure.

Usage: port/scripts/mastery_session.sh [--target port-inproc|port-server] <soa> <out-dir> <scratch-dir>
Env: SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
Targets: port-inproc, port-server (the state DB is planted before boot; the milestones are the
server's log lines)."""
import os
import shutil
import sqlite3
import subprocess
import tempfile

from ..proc import REPO, repo_file
from . import common

TARGETS = ("port-inproc", "port-server")
TARGETS_WHY = "the state DB is planted before boot; the checks read the server's log, which both targets have"
WRAPPER = "port/scripts/mastery_session.sh"


def options(ap):
    common.port_options(ap, extra=False)


def cast(st, m):
    """(master uid, disciple uid, the master role's mastery type): the first owned character whose
    role has a mastery type, and the first of its category without one."""
    roster = st.execute("select uid, role_id from roster order by uid").fetchall()
    role = {r: m.execute("select ifnull(master_mastery_step_type_id, 0), category_type from master_role where id = ?", (r,)).fetchone()
            for _, r in roster}
    master = next((u, role[r]) for u, r in roster if role[r][0])
    disciple = next(u for u, r in roster if not role[r][0] and role[r][1] == master[1][1])
    return master[0], disciple, master[1][0]


def plant(db, soa_server):
    """The state before the first boot (both targets read TMP's state DB): the seeded player of a
    soa-server replay of one Login, then the two characters at LV70 and the materials."""
    work = tempfile.mkdtemp(prefix="mastery-plant-")
    try:
        corpus = os.path.join(work, "corpus")
        os.makedirs(corpus)
        with open(os.path.join(corpus, "requests.txt"), "w") as f:
            f.write("# tz: UTC\nreq 1 1790856005 Login a01c67ef - - - -\n")
        args = ["--master", repo_file("data/basmaster-3.7.0.sqlite3"), "--seed", repo_file("data/saves/seed/Game.xml"),
                "--seed-rng", os.environ.get("SEED_RNG") or "1", "--download-dir", repo_file("work/download-3.7.0")]
        subprocess.run([soa_server] + args + ["--replay", corpus, "--out", os.path.join(work, "out")], cwd=REPO, check=True,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        src = sqlite3.connect(os.path.join(work, "out", "data", "server.sqlite3"))
        os.makedirs(os.path.dirname(db), exist_ok=True)
        for p in (db, db + "-wal", db + "-shm"):
            if os.path.exists(p):
                os.remove(p)
        dst = sqlite3.connect(db)
        src.backup(dst)
        src.close()
        m = sqlite3.connect("file:%s?mode=ro" % repo_file("data/basmaster-3.7.0.sqlite3"), uri=True)
        dst.execute("pragma foreign_keys = on")  # PLAN-schema S1: every connection that writes the state
        master, disciple, type_id = cast(dst, m)
        dst.execute("update roster set level = 70, exp = 0 where uid in (?, ?)", (master, disciple))

        def add(item, n):
            t = m.execute("select type from master_item where id = ?", (item,)).fetchone()[0]
            dst.execute("insert into stock (master_item_id, item_type, count) values (?,?,?) "
                        "on conflict(master_item_id) do update set count = excluded.count", (item, t, n))

        for (item,) in m.execute("select distinct required_master_item_id from master_mastery_step where type_id = ?", (type_id,)):
            add(item, 500)
        medal = m.execute("select id from master_item where id_label = (select value from master_global "
                          "where key = 'mastery_training_pass_item_id')").fetchone()[0]
        add(medal, 3)
        dst.commit()
        dst.close()
        return master, disciple
    finally:
        shutil.rmtree(work, ignore_errors=True)


def server_count(s, rx):
    return s.count(s.server_log, rx)


# The screens' taps at 729x1296 (seen on 3.7.0, 2026-10-04).
CHARACTER = "180:1245"     # footer キャラクター
MASTERY = "364:765"        # the character menu, scrolled: マスタリー
DOJO1 = "180:450"          # 道場1's card
FIRST_CELL = "95:650"      # the selection list's first character (the LV70 ones lead it)
DECIDE = "620:1120"        # 決定
DIALOG_YES = "515:712"     # the dialogs' right button (決定)
CLOSE = "364:800"          # 師弟関係を結びました! -> 閉じる
CARDS = ("125:800", "364:800", "600:800")  # the three training cards
EXECUTE = "515:780"        # the training dialog's 実行
MEDAL = "364:880"          # マスタリーパスメダルを使う
MEDAL_EXECUTE = "515:800"  # its 実行
ALL_CLEAR_CLOSE = "364:890"  # Full Mastership! -> 閉じる
GRADUATED_TAB = "515:275"  # 皆伝師弟
GRADUATED_PAIR = "180:460"  # the 皆伝 list's first pair
PART = "515:890"           # its dialog's 師弟解消


def step(s, name, rx, cmds, secs=40):
    """cmds, then waits for one more server-log line matching rx; resent once when none came (a
    tap dropped while a screen fades in). Records PASS / FAIL."""
    before = server_count(s, rx)
    for attempt in range(2):
        s.ctl(*cmds)
        if s.poll(secs, lambda: server_count(s, rx) > before):
            s.ok(name)
            return True
        if not s.alive():
            break
        s.note("%s: no server line yet; sending the taps again" % name)
    s.miss(name)
    return False


def open_mastery(s, n_pairs, shot):
    s.ctl("tap:" + CHARACTER, "wait:6000", "drag:364:900:364:400", "wait:2500")
    step(s, "マスタリー -> GetMasteryInfo (%d pair(s))" % n_pairs, r"GetMasteryInfo: %d pair" % n_pairs, ["tap:" + MASTERY, "wait:3000"])
    s.ctl("wait:3000", s.shot_cmd(shot))


def main(o):
    soa_server = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(o.soa))), "server", "soa-server")
    s = common.port_run(o, common.port_config(o, limit=2400))
    planted = {}
    s.before_client = lambda: planted.update(zip(("master", "disciple"), plant(s.state_db, soa_server)))
    c = s.ctl

    def body(s):
        common.port_login(s, notice=None, bonus=None)
        open_mastery(s, 0, "03-mastery")
        # 道場1 -> 師匠 (the list's first: the LV70 master-type role) -> 決定 -> 弟子 -> 決定 -> 決定
        c("tap:" + DOJO1, "wait:5000", s.shot_cmd("04-select-master"), "tap:" + FIRST_CELL, "wait:2500", "tap:" + DECIDE, "wait:3500",
          "tap:" + FIRST_CELL, "wait:2500", s.shot_cmd("05-select-disciple"), "tap:" + DECIDE, "wait:3000", s.shot_cmd("06-pair-confirm"))
        if not step(s, "決定 -> TrainMastery (paired)", r"TrainMastery: paired master", ["tap:" + DIALOG_YES, "wait:3000"]):
            return
        c("wait:2000", s.shot_cmd("07-paired"), "tap:" + CLOSE, "wait:5000", s.shot_cmd("08-training"))
        # trainings 1-4 with a material card (the first, then the middle), 5 with the pass medal
        for n in range(1, 5):
            card = CARDS[0] if n == 1 else CARDS[1]
            if not step(s, "training %d -> TrainMastery" % n, r"TrainMastery: disciple [0-9a-f]+ training %d/5 option" % n,
                        ["tap:" + card, "wait:3000", "tap:" + EXECUTE, "wait:3000"]):
                return
            c("wait:5000", s.shot_cmd("09-training-%d" % n))
        if not step(s, "training 5 with the pass medal -> 皆伝", r"TrainMastery: disciple [0-9a-f]+ training 5/5 option 3 \(pass medal\), FOL -0; 皆伝",
                    ["tap:" + CARDS[2], "wait:3000", "tap:" + MEDAL, "wait:3000", s.shot_cmd("10-medal-confirm"), "tap:" + MEDAL_EXECUTE,
                     "wait:3000"]):
            return
        c("wait:6000", s.shot_cmd("11-full-mastership"), "tap:" + ALL_CLEAR_CLOSE, "wait:5000", "tap:" + GRADUATED_TAB, "wait:3000",
          s.shot_cmd("12-graduated"))

    ok = common.drive(s, body)
    fails = []
    if ok and not s.failed:
        st = sqlite3.connect("file:%s?mode=ro" % s.state_db, uri=True)
        row = st.execute("select master_uid, step1, step2, step3, step4, step5 from mastery where uid = ?", (planted.get("disciple"),)).fetchone()
        st.close()
        s.check("the pair stored with its five trainings (cards 1, 2, 2, 2, 3)", row == (planted.get("master"), 1, 2, 2, 2, 3))
        # ---- a second boot on the same phone: the pair kept (皆伝), then 師弟解消
        s2 = common.port_run_again(o, common.port_config(o, limit=1500), "again.log")
        s2.layout.shots = os.path.join(o.out, "again")
        os.makedirs(s2.layout.shots, exist_ok=True)

        def again(s2):
            common.port_login(s2, notice=None, bonus=None)
            open_mastery(s2, 1, "01-mastery")
            s2.ctl("tap:" + GRADUATED_TAB, "wait:3000", s2.shot_cmd("02-graduated"), "tap:" + GRADUATED_PAIR, "wait:3000",
                   s2.shot_cmd("03-full-mastership"), "tap:" + PART, "wait:3000", s2.shot_cmd("04-part-confirm"))
            step(s2, "師弟解消 -> ResetMastery", r"ResetMastery: parted master", ["tap:" + DIALOG_YES, "wait:3000"])
            s2.ctl("wait:3000", s2.shot_cmd("05-parted"))

        ok = common.drive(s2, again) and ok
        st = sqlite3.connect("file:%s?mode=ro" % s2.state_db, uri=True)
        s2.check("parted: no pair left", st.execute("select count(*) from mastery").fetchone()[0] == 0)
        st.close()
        if s2.failed:
            fails.append("the second boot")
    return common.verdict(s, fails, "mastery: paired, five trainings (one with the pass medal), 皆伝, kept after a re-login, parted")
