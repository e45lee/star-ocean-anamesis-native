#!/usr/bin/env python3
"""Index table of docs/history/libsoa-3.7.0-vs-3.8.0.md: every function tools/verdiff.py found changed,
with its subsystem group, a one-line summary and how the port handles it.
History tool (the port runs 3.7.0 only).

Usage: tools/verdiff_index.py [work/verdiff/changed.tsv] > table.md   (group counts on stderr)

Groups and port handling are rules over the owning class / method (kept in step with
port/src/native/restore/restore370.cpp and docs/client-changes.md by hand); summaries are derived from
verdiff's characterisation, with hand-written ones (OVR, NOISE) for the functions read in the
decompiles. Summaries marked [D] were checked in both builds' Ghidra output.
"""
import csv
import re
import subprocess
import sys
from collections import Counter

import os

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
path = sys.argv[1] if len(sys.argv) > 1 else os.path.join(REPO, "work/verdiff/changed.tsv")
rows = list(csv.DictReader(open(path), delimiter="\t"))


def cxxfilt(names):
    out = subprocess.run(["c++filt"], input="\n".join(names), capture_output=True, text=True).stdout
    return out.splitlines()


def parse_nested(s):
    """'N5CHome5SetupEv...' or '5CHome5SetupEv' -> ['CHome', 'Setup']"""
    i = 1 if s.startswith("N") else 0
    parts = []
    while i < len(s) and s[i].isdigit():
        m = re.match(r"\d+", s[i:])
        n = int(m.group())
        i += len(m.group())
        parts.append(s[i:i + n])
        i += n
    return parts


SLOT = {"1": "~D0", "2": "~D2", "3": "clone", "4": "clone(p)", "5": "destroy", "6": "operator()", "7": "target"}


def owner_and_name(r):
    sym, dem = r["symbol"], r["demangled"]
    if sym.startswith("lambda:ZZ"):
        body = sym[len("lambda:"):].lstrip("Z")
        parts = parse_nested(body)
        inner = re.search(r"\$_(\d+)", sym)
        slot = sym.rsplit(".", 1)[-1]
        cls, meth = parts[0], parts[1]
        nm = f"{cls}::{meth} → $_{inner.group(1) if inner else '?'} inner lambda .{SLOT.get(slot, slot)}"
        return cls, meth, nm
    if sym.startswith("lambda:"):
        m = re.match(r"lambda:(.*)#(\d+)\.(\d+)$", sym)
        nested, k, slot = m.groups()
        if nested.startswith("_Z"):
            parts = parse_nested(nested[3:] if nested.startswith("_ZN") else nested[2:])
        else:
            parts = parse_nested(nested)
        cls, meth = parts[0], parts[1] if len(parts) > 1 else ""
        return cls, meth, f"{cls}::{meth} [lambda #{k}] .{SLOT.get(slot, slot)}"
    if sym.startswith("anon:"):
        return r["class"], "", dem
    return None, None, dem


plain = [r for r in rows if not r["symbol"].startswith(("lambda:", "anon:"))]
dm = dict(zip([r["symbol"] for r in plain], cxxfilt([r["symbol"] for r in plain])))


def short(d, n=90):
    d = d.replace("std::__ndk1::", "std::").replace("Framework::", "")
    d = re.sub(r"basic_string<char, std::char_traits<char>, CSTLAllocator<char, CSTLStringAllocatorInf> >", "string", d)
    return d if len(d) <= n else d[: n - 1] + "…"


# ----------------------------------------------------------------------------------- groups
def group_of(cls, meth, name, r):
    sym = r["symbol"]
    n = name
    if r["class"] in ("(runtime / toolchain)", "(unnamed static functions)") and cls is None:
        if "SortCharaElem" in n:
            return "Party, sort & adjutant"
        return "Toolchain / noise"
    if "SortCharaElem" in n:
        return "Party, sort & adjutant"
    if cls is None and n.startswith("CParameterUtility") and any(f in n for f in FAVOR_NATIVE):
        return "Favorability"
    if "CManageFiber" in n or "FavorBonusElement" in n or "sqlite3_db_readonly" in n or n.startswith("anon:start#"):
        return "Toolchain / noise"
    if cls == "CFriendMenu":
        return "Toolchain / noise"
    c = cls or n.split("::")[0]
    if c.startswith("CUISort") or "SortCondition" in n or c.startswith("CSortDialogWrapper") and "Favor" not in n:
        return "Party, sort & adjutant"
    if "SetupFavorFilter" in n:
        return "Favorability"
    if c in ("CPartyComposition", "CAdjutantSelect") or "CAdjutantSelect" in n:
        return "Party, sort & adjutant"
    if c in ("CPhase_Login", "CTitle", "CPlayerInitializeMenu") or "CPlayerInitializeMenu" in n:
        return "Login, title & new player"
    if c in ("CPhase", "CPhase_TutorialNext", "CTutorialManager"):
        return "Phase flow & tutorial"
    if c == "NetworkApiCaller":
        return "Network / API caller"
    if "Favor" in n and (c.startswith("CParameterUtility")):
        return "Favorability"
    if c in ("CTimeUtility", "CServerTime", "CHomeUtility") or (c == "CUIUtility" and re.search(
            r"OnPause|IsFooterBadge|MasterCharacterLimitBreakList|GetMaxShipCount|GetNowOpenEventRankingGroupId|IsWithinDay|GetUnusedShipCount|IsTimeOverCoinSale|IsGachaSaleType|SetLocalKVSNoticeBordDay|SetLocalKVSGuideInformationTime", n)):
        return "Clock (service_stop_day)"
    if c == "CUIUtility" and re.search(r"Campaign|GetDecMissionContinueCoin", n):
        return "Missions & campaign"
    if c in ("CHome", "CCommon", "COtherMenu"):
        return "Home & menus"
    if c in ("CSystemSettingMenu", "CMenuVoiceManager", "CUIVoiceManager", "CUIVoiceDataCache") or re.search(
            r"MenuVoice|ResetSettingMenuParameter", n):
        return "Settings & menu voices"
    if c in ("CCharacterPictureBook", "CDetailDialog_Character") or "CollectData" in n or "SetCharaFaceIconStatus" in n:
        return "Character book & details"
    if c in ("CMissionMenu", "CMissionSelectPart", "CScenarioLibrary", "MissionUtility", "CTrainingMissionMenu",
             "CEventMissionMenu", "CTowerMissionMenu", "CWorldMapMissionList") or "CommonResourceButtonMission" in n \
            or n.startswith("EventScenario"):
        return "Missions & campaign"
    if c in ("BAS", "Platform", "CWebView", "WebViewUtility", "CTestKakiuchi", "CBuildInfo") or n.startswith(
            ("BAS::", "Platform::", "WebViewUtility")):
        return "Platform services & web views"
    if c in ("CGameResourceManager", "CGameResourceDownloader", "CAnimationModelObject", "CMovieManager",
             "CSoundManager", "CGame", "CPhase_DataDownload") or "CGameResourceManager" in n:
        return "Resources & asset packs"
    if c == "CUserDataUtility":
        return "Local save"
    if n.startswith(("Aska::", "float Framework", "unsigned char Framework", "int Framework")) or "GetEasingValue" in n:
        return "Toolchain / noise"
    return "Other"


# ----------------------------------------------------------------------------------- handling
R370 = {
    "CHome": "restore370 `home`", "CCommon": "restore370 `common`", "COtherMenu": "restore370 `othermenu`",
    "CAdjutantSelect": "restore370 `adjutant`", "CPartyComposition": "restore370 `party`",
    "CPhase_Login": "restore370 `login`", "CPlayerInitializeMenu": "restore370 `playerinit`",
    "CTutorialManager": "restore370 `tutorial`", "CPhase_TutorialNext": "restore370 `phase`",
}
FAVOR_NATIVE = ("GetFavorabilityLevel", "GetFavorabilityParam", "GetFavorApBonusBySameRoleID", "GetFavorDropIconImageName",
                "GetAssistesFavorabilityLevel", "InitializeFromMaster", "InitializeAssitCharaData",
                "GetNotReceiveGoaledFavorabilityAchievement")


def handling(cls, meth, name, r, grp):
    n = name
    c = cls or n.split("::")[0]
    if grp == "Toolchain / noise":
        return "n/a"
    if "SetupFavorFilter" in n:
        return "restore370 `sort` + `restore_favor` patch"
    if grp == "Party, sort & adjutant":
        if "SortCharaElem" in n:
            return "restore370 `sort` (local helper)"
        if c in R370 or "CAdjutantSelect" in n:
            return R370.get(c, "restore370 `adjutant`")
        return "restore370 `sort`"
    if c in R370:
        return R370[c]
    if "CPlayerInitializeMenu" in n:
        return "restore370 `playerinit`"
    if c == "CPhase":
        return "restore370 `phase`" if meth == "Switch" or "Switch(" in n else "not needed (assert line)"
    if c == "CTitle":
        if meth == "Setup" or n.startswith("CTitle::Setup"):
            return "restore370 `title` (off by default)"
        if re.match(r"CTitle::(Progress|StartGame|ToRelease|CTitle)\(", n):
            return "kept 3.8.0 (menu-voice id)"
        return "kept 3.8.0"
    if grp == "Favorability":
        return "`restore_favor` native" if any(f in n for f in FAVOR_NATIVE) else "kept 3.8.0"
    if grp == "Clock (service_stop_day)":
        if n.startswith(("CTimeUtility::NowTime()", "BAS::LocalTime")):
            return "server: `service_stop_day` row dropped"
        return "follows `NowTime` (row dropped)"
    if "CreateCollectList" in n:
        return "`restore_home` (CheckTime wrapper)"
    if "NextPhase" in n and c == "CMissionMenu":
        return "`restore_campaign` (3.7.0 block)"
    if n.startswith("EventScenario::CEventScenario::Exit"):
        return "`restore_campaign` (EndMissionTalk)"
    if n.startswith("CMissionSelectPart::Setup [lambda #2]"):
        return "`restore_campaign` patch (#7 → #5)"
    if "CMissionSelectPart::CreateList" in n:
        return "kept; episode tap patched (`restore_campaign`)"
    if "Load_PartyInfo" in n:
        return "hooked (`restore_campaign` GetPlayer)"
    if c == "CUserDataUtility":
        return "server writes the save keys"
    if n.startswith("CWebView::OpenView"):
        return "`webview_local` wrapper (port)"
    if grp == "Platform services & web views":
        return "not needed (no desktop service)" if c != "CBuildInfo" else "not needed"
    if grp == "Resources & asset packs":
        return "not needed (port asset overlay)"
    if grp == "Missions & campaign":
        if "Campaign" in n or "GetDecMissionContinueCoin" in n:
            return "kept 3.8.0 (live clock)"
        return "kept 3.8.0"
    if grp == "Network / API caller":
        return "not needed (FakeApiCaller route)"
    return "kept 3.8.0"


# ----------------------------------------------------------------------------------- summaries
def lastpart(x):
    x = re.sub(r"<.*>", "", x)
    x = x.split("(")[0]
    return "::".join(x.split("::")[-2:])


def summarise(ch):
    ch = ch.strip()
    out = []
    m = re.match(r"3\.8\.0 stubbed out \(([^)]*)\)", ch)
    if m:
        out.append(f"stubbed to `{m.group(1)}`")
    m = re.match(r"3\.8\.0 (cut down|grew) (\d+) -> (\d+) bytes", ch)
    if m:
        out.append(m.group(1).replace("cut down", "cut"))
    for kind in ("calls removed", "calls added"):
        m = re.search(kind + r": (.*?)(;|$)", ch)
        if m:
            names = [lastpart(x.strip()) for x in re.split(r", (?=[A-Za-z_~])", m.group(1)) if x.strip()]
            names = [x for x in names if x and not re.search(r"basic_string|__ndk1|gDoAssert|Allocate$|Free$|operator|__push_back|__emplace|memcpy|memmove|strlen|memcmp|__grow|reserve|~|__func|__release|swap$", x)]
            seen = []
            for x in names:
                if x not in seen:
                    seen.append(x)
            if seen:
                s = ", ".join(seen[:3]) + (" …" if len(seen) > 3 else "")
                out.append(("−" if kind == "calls removed" else "+") + " " + s)
    for kind in ("strings removed", "strings added"):
        m = re.search(kind + r": (.*?)(; calls|; strings|$)", ch)
        if m:
            ss = [s for s in re.findall(r"'([^']*)'", m.group(1)) if not re.search(r"BAS_Submission|is null|aNumElements|out of range|^$", s)]
            if ss:
                out.append(("−" if kind == "strings removed" else "+") + " '" + "', '".join(ss[:2]) + "'" + (" …" if len(ss) > 2 else ""))
    m = re.search(r"constant/operand change: (.*)", ch)
    if m:
        out.append("constant: " + m.group(1)[:60])
    if "only field offsets" in ch:
        out.append("field offsets only (layout)")
    if not out and "control/data flow" in ch:
        out.append("flow changed")
    return "; ".join(out).replace("|", "\\|")


OVR = {
    "CTimeUtility::NowTime()": "returns `service_stop_day` when the key is set, else LocalTime + FixTime [D]",
    "BAS::LocalTime(bool)": "new `bool`: when true, returns `service_stop_day` if set, else `time()` [D]",
    "CPhase::Switch(unsigned int)": "drops TutorialNext / Relogin / SyncServerTime phases",
    "NetworkApiCaller::BeginBridge": "drops the already-bridged shortcut [D]",
    "CSystemSettingMenu::ProgressResetApi()": "local reset + dialog instead of the ResetConfig request [D]",
    "CUIUtility::GetSortCondition(char const*": "one-time `BAS:Sort_StandAloneFlag` migration: stored chara sort kind − 1 [D]",
    "CUIUtility::IsMenuVoiceCoroEnable()": "`_Ver2` key, migrated once from the old key AND the 'other' switch [D]",
    "CUIUtility::IsMenuVoiceEveleashEnable()": "`_Ver2` key, migrated once from the old key AND the 'other' switch",
    "CMenuVoiceManager::IsSystemSettingMenuVoiceEnable": "no longer ANDs with `IsMenuVoiceOtherEnable` [D]",
    "CPhase_DataDownload::CheckDownloadError": "state constant 0x1f → 0x22 (state enum renumbered) [D]",
    "CGameResourceManager::AddDirectFile": "download-folder branch moved into a helper that also checks asset packs [D]",
    "CUserDataUtility::Load_PlayerInfo()": "also reads `player_home_pc_roleid` from the local KVS [D]",
    "CMissionMenu::NextPhase(int)": "no longer copies the chosen mission / helper into CParameterUI",
    "CHome::GetAdjutant": "adjutant falls back to `offline_Character_1` once its role closed (by `service_stop_day`)",
    "CTitle::Setup()": "player id, cache check, update panel, service-end dialog, movie / refund buttons removed",
    "CPartyComposition::Progress()": "party-select top, scene replacement, stamp, edit buttons removed",
    "CPartyComposition::Setup()": "cut to the character-encyclopedia list",
    "CScenarioLibrary::Progress()": "RequestListReceiveApi → RequestListLocal (list from sqlite)",
    "CCommon::Initialize()": "layout `common` → `common_sa`",
    "CSystemSettingMenu::Initialize()": "layout `config_top` → `config_top_sa`",
    "CHome::Setup()": "layout `home` → `home_sa`; only `main_button2`; event / extra dungeon / campaign badge gone",
    "EventScenario::CEventScenario::Exit()": "no EndMissionTalk request at scene end",
    "CBuildInfo::": "build stamp",
    "CPhase_Login::CPhase_Login()": "also zeroes the new flag at +0x28 (object 0x28 → 0x30)",
    "CPhase::SetShortcut": "assert `__LINE__` argument only (Phase.cpp edited)",
    "CPhase::SetRestoreShortcut": "assert `__LINE__` argument only (Phase.cpp edited)",
    "CTitle::Progress [lambda #0] .operator()": "tap-to-start: only `PlayTapToStart` left (3.7.0 also set up a node first)",
    "CMissionSelectPart::Setup [lambda #2] .operator()": "episode tap: next phase 5 (CPhase_Mission) → 7 (CPhase_ScenarioLibrary)",
    "CMissionSelectPart::CreateList()": "downloaded-episode and maintenance checks removed",
    "CCharacterPictureBook::CreateCollectList": "list from every master role open at `service_stop_day` instead of owned characters + their categories",
    "CPhase_Login::Progress()": "online login / CreatePlayer / terms flow → local stand-alone new player (`offline_Character_1..3`)",
    "CPlayerInitializeMenu::Initialize(": "terms / name-entry dialog cut to the stand-alone terms prompt",
    "CAdjutantSelect::UpdateList()": "list built from master roles (CreateCharaList) instead of owned characters",
    "CTutorialManager::IsStartTutorial() const": "stubbed: always 0 (no tutorial)",
    "CTutorialManager::IsStartTutorialNext() const": "stubbed: always 0",
    "CGame::OnInitialize()": "operator new 0x70 → 0x78 (CGameResourceManager grew)",
}


NOISE = [
    ("anon:CSoundManager::CManageFiber", "lld Cortex-A53 erratum-843419 veneer spliced into the body (toolchain), same code"),
    ("anon:std::__hash_table<std::__hash_value_type<unsigned int, CMasterParameterFavorBonus", "lld Cortex-A53 erratum veneer (toolchain), same code"),
    ("CFriendMenu::NextStateAddBlock", "lld Cortex-A53 erratum veneer (toolchain), same code"),
    ("anon:start#", "libc++ locale string-array static (destructor / atexit form), toolchain"),
    ("std::__time_get_c_storage", "points at a renumbered libc++ static (toolchain)"),
    ("std::basic_string<char, std::char_traits<char>, std::allocator<char> >::assign", "libc++ inlining difference (toolchain)"),
    ("anon:sqlite3_db_readonly", "SQLite static: a constant table's bytes differ (toolchain / data)"),
    ("__register_frame_info", "libgcc unwinder: data offsets (toolchain)"),
    ("__sfp_handle_exceptions", "libgcc soft-fp: literal-pool neighbour (toolchain)"),
    ("Aska::ShadowManager", "page-offset artefact, not a field (checked by hand)"),
    ("Aska::SoundUtility", "page-offset artefact, not a field"),
    ("float Framework::Cocos::detail", "page-offset artefact, not a field"),
    ("unsigned char Framework::Cocos::detail", "page-offset artefact, not a field"),
    ("int Framework::Cocos::detail", "page-offset artefact, not a field"),
]


def summary_for(name, r):
    for k, v in NOISE:
        nn = name.replace("std::__ndk1::", "std::").replace("Framework::", "")
        if nn.startswith(k.replace("Framework::", "")):
            return v
    for k, v in OVR.items():
        if name.startswith(k):
            return v
    s = summarise(r["characterisation"])
    m = re.fullmatch(r"− ([\w:]+); \+ ([\w:]+)", s)
    if m and m.group(1) == m.group(2):
        s = f"calls the changed-signature `{m.group(1)}` (new parameter)"
    if "lambda" in name and "Lambdas are paired" in r["characterisation"]:
        s = s or "body differs"
    return s or "flow changed"


out = []
grp_count = Counter()
for r in rows:
    cls, meth, nm = owner_and_name(r)
    if cls is None:
        nm = dm.get(r["symbol"], r["demangled"])
    grp = group_of(cls, meth, nm, r)
    grp_count[grp] += 1
    hd = handling(cls, meth, nm, r, grp)
    sz = f"{r['old_size']} → {r['new_size']}"
    out.append((grp, nm, sz, summary_for(nm, r), hd, r["diff_instrs"]))

ORDER = ["Network / API caller", "Login, title & new player", "Phase flow & tutorial", "Clock (service_stop_day)",
         "Home & menus", "Party, sort & adjutant", "Character book & details", "Favorability", "Missions & campaign",
         "Settings & menu voices", "Local save", "Platform services & web views", "Resources & asset packs", "Other",
         "Toolchain / noise"]
out.sort(key=lambda t: (ORDER.index(t[0]), t[1]))
print("| # | Function | Size (bytes) | Δ | Group | Summary | Port handling |")
print("|---|---|---|---|---|---|---|")
for i, (g, n, sz, s, h, d) in enumerate(out, 1):
    name = short(n).replace("|", "\\|")  # (outside the f-string: a backslash in one needs Python 3.12)
    print(f"| {i} | `{name}` | {sz} | {d} | {g} | {s} | {h} |")
for g in ORDER:
    print(g, grp_count[g], file=sys.stderr)
