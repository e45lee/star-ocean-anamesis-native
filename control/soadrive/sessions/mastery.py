"""Session `mastery`: キャラクター > マスタリー (CMasteryTop) under the local server, in-process or
soa-server (docs/server-rules.md#mastery), and ChangeRole (docs/server-rules.md#role-change). The state is planted before the first boot: the seed
save's player (a one-request soa-server replay of Login, the session's seed and RNG) with a master-type
role and a role of its category without one at LV70, the materials of their mastery type's trainings
and a few pass medals (item_Mastery_01). Then, at home: 装備・技・アシスト変更 -> the seed's role-changeable ★6
(cp0010_b01a_6165) -> ロール選択 -> アタッカー (ChangeRole);
  道場1 -> 師匠 and 弟子 picked -> 決定 (TrainMastery pairing), the five trainings (the first four with
  the material cards, the fifth with the pass medal) -> 皆伝 (the reward dialog), 皆伝師弟 listed;
then 会話モード > キャラデコ (GetDecoInfo), a favourite (FavoriteDecoObject) and a decoration set
(SetCharacterDeco, sent by the list's 決定); then a second boot on the same phone: the
マスタリー screen again (GetMasteryInfo: the pair kept, in the 皆伝 list), 師弟解消 (ResetMastery),
キャラデコ again (the setting and the favourite kept). Milestones are the server's log lines (both targets):
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
                "--seed-rng", os.environ.get("SEED_RNG") or "1", "--download-dir", repo_file("work/SOA-3.7.0-canonical-data.zip")]
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
        # キャラデコ: three decorations (two objects, one hair colour), as grants would add them
        for i, (deco,) in enumerate(m.execute("select id from (select id, order_id from master_deco_object order by order_id limit 2) "
                                              "union all select id from (select id from master_deco_hair order by order_id limit 1)")):
            dst.execute("insert into deco_owned (id, master_deco_id, created_at) values (?, ?, 0)", (i + 1, deco))
        dst.commit()
        dst.close()
        return master, disciple
    finally:
        shutil.rmtree(work, ignore_errors=True)


def server_count(s, rx):
    return s.count(s.server_log, rx)


# The screens' taps at 729x1296 (seen on 3.7.0, 2026-10-04).
CHARACTER = "180:1245"     # footer キャラクター
MASTERY = "364:638"        # the character menu scrolled to its end: マスタリー
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
EQUIPMENT = "364:435"      # the character menu: 装備・技・アシスト変更
ROLE_CHANGER = "495:330"   # its list's fourth: the seed's cp0010_b01a_6165 (★6 ヒーラー, master_role_change)
ROLE_SELECT = "380:353"    # ロール選択
ATTACKER = "364:410"       # the role dialog's アタッカー
HOME = "60:1245"           # footer ホーム
INTERACTIVE = "90:740"     # home: 会話モード
DECO = "545:1245"          # 会話モード's footer: キャラデコ
DECO_SELECT = "180:1245"   # the deco menu's footer: デコ選択
DECO_SLOT = "320:685"      # キャラデコ設定: the first デコ選択 slot
DECO_FIRST = "320:588"     # the slot's list: the first decoration
DECO_STAR = "640:588"      # its favourite star
DECO_ADJUST = "300:1245"   # the footer's デコ調整 (the decoration's position)


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
    # scrolled to the end (three drags: one drag's length varies with its speed)
    s.ctl("tap:" + CHARACTER, "wait:6000", *(["drag:364:1000:364:300", "wait:1500"] * 3), "wait:1500")
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
        # ---- ChangeRole: 装備・技・アシスト変更 -> the role-changeable ★6 -> ロール選択 -> アタッカー
        c("tap:" + CHARACTER, "wait:6000", "tap:" + EQUIPMENT, "wait:5000", "tap:" + ROLE_CHANGER, "wait:5000", s.shot_cmd("03a-equipment"),
          "tap:" + ROLE_SELECT, "wait:4000", s.shot_cmd("03b-role-select"))
        step(s, "ロール選択 -> アタッカー -> ChangeRole", r"ChangeRole [0-9a-f]+: role [0-9]+ -> [0-9]+", ["tap:" + ATTACKER, "wait:3000"])
        c("wait:2000", s.shot_cmd("03c-role-changed"), "tap:" + CLOSE, "wait:4000", s.shot_cmd("03d-attacker"))
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
        # ---- キャラデコ: ホーム -> 会話モード -> キャラデコ (GetDecoInfo: the planted three) -> デコ選択 -> a slot
        # -> ☆ (FavoriteDecoObject) -> the first decoration -> 決定 (SetCharacterDeco) -> デコ調整
        c("tap:" + HOME, "wait:7000", "tap:" + INTERACTIVE, "wait:5000")
        step(s, "キャラデコ -> GetDecoInfo (3)", r"GetDecoInfo: 3 decoration", ["tap:" + DECO, "wait:4000"])
        c("wait:3000", s.shot_cmd("13-deco"), "tap:" + DECO_SELECT, "wait:4000", "tap:" + DECO_SLOT, "wait:4000", s.shot_cmd("14-deco-list"))
        step(s, "☆ -> FavoriteDecoObject", r"FavoriteDecoObject: 1 decoration", ["tap:" + DECO_STAR, "wait:2000"])
        c("tap:" + DECO_FIRST, "wait:3000")
        step(s, "the first decoration -> 決定 -> SetCharacterDeco (one object)", r"SetCharacterDeco [0-9a-f]+: hair [0-9]+, pose [0-9]+, 1 object",
             ["tap:" + DECIDE, "wait:3000"])
        c("wait:2000", s.shot_cmd("15-deco-set"), "tap:" + DECO_ADJUST, "wait:4000", s.shot_cmd("16-deco-adjust"))

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
            s2.ctl("wait:3000", s2.shot_cmd("05-parted"), "tap:" + CLOSE, "wait:3000")
            # the decorations kept: キャラデコ again (GetDecoInfo; the character wears its decoration,
            # from its CPersonInfo)
            s2.ctl("tap:" + HOME, "wait:7000", "tap:" + INTERACTIVE, "wait:5000")
            step(s2, "キャラデコ again -> GetDecoInfo (3)", r"GetDecoInfo: 3 decoration", ["tap:" + DECO, "wait:4000"])
            s2.ctl("wait:3000", s2.shot_cmd("06-deco-kept"))

        ok = common.drive(s2, again) and ok
        st = sqlite3.connect("file:%s?mode=ro" % s2.state_db, uri=True)
        s2.check("parted: no pair left", st.execute("select count(*) from mastery").fetchone()[0] == 0)
        m = sqlite3.connect("file:%s?mode=ro" % repo_file("data/basmaster-3.7.0.sqlite3"), uri=True)
        attackers = {r for (r,) in m.execute("select master_role_id from master_role_change c join master_role r on r.id = c.master_role_id "
                                             "where r.category_type = 1")}
        s2.check("the decoration setting and the favourite kept",
                 st.execute("select count(*) from character_deco").fetchone()[0] == 1 and
                 st.execute("select count(*) from deco_owned where is_favorite = 1").fetchone()[0] == 1)
        s2.check("the role change kept (an attacker role of master_role_change)",
                 any(r in attackers for (r,) in st.execute("select role_id from roster")))
        st.close()
        if s2.failed:
            fails.append("the second boot")
    return common.verdict(s, fails, "mastery: a role changed, paired, five trainings (one with the pass medal), 皆伝, a decoration set and "
                          "a favourite, kept after a re-login, parted")
