#!/usr/bin/env python3
"""Inventory of what is still guest code, for planning the move off the JIT (docs/history/REMAINING.md).

Usage: remaining.py DIR [DIR...] --native-list FILE [--top N]

DIR is a SOA_PROFILE + SOA_COVERAGE run (see profile_report.py); several are merged. FILE is the
output of `soa --list-native` for the same build.

Sections:
  - headline numbers (native share of busy time / executed functions / the function table)
  - native replacements by kind: transcribed (tools/a2c.py, gen_*_a2c.py) vs hand-written
  - executed functions that are still guest code, by family, with flags:
      hot   family guest self time >= --hot samples
      init  every executed function of the family first ran before the title screen, and it isn't hot
      boot  the same, but hot: a loop or thread started at boot
      tiny  most executed functions are <= 16 bytes (wrappers, getters, thunks)
      <8B   functions under 8 bytes: the SVC;RET hook patch doesn't fit, so they can't be replaced
  - never-executed code by product area (battle, gacha, multiplayer, debug, ...)

Local (unexported) functions are attributed to the family of the nearest preceding export, as
profile_report.py does; that is a hint (same object file, most of the time), not a certainty.
"""
import argparse
import collections
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from profile_report import IDLE_HLE, demangle_all, family_of, fmt_bytes, load_tsv, table  # noqa: E402

TRANSCRIBED = re.compile(r"a2c|transcribed", re.I)

# Product areas for never-executed code, matched against the family name (first match wins).
AREAS = [
    ("debug", r"Debug|Profiler|Cheat|CTest|DevMenu|Dump"),
    ("libc++ / libc++abi", r"^~?std::|__cxxabiv1|^~?_*cxa|__gnu_cxx|_Unwind"),
    ("third-party C (zstd/jpeg/vorbis/ogg/sqlite/zlib/bullet)", r"^~?(bt[A-Z]|ZSTD|HUF|FSE|jpeg|jinit|jcopy|jdiv|jround|jzero|vorbis|ogg|sqlite3|deflate|inflate|z_|crc32|adler)|^~?_?(ov_|mdct|drft|_vorbis|_ve_|res0|floor|mapping0)"),
    ("animation templates (TAaf*/Aaf)", r"TAaf|Aaf|_HO_sub"),
    ("engine (other Aska::*)", r"^~?Aska::|^Aska$|^Collision$"),
    ("Framework (other)", r"^~?Framework::"),
    ("master data / parameters", r"CMasterParameter|CParameter|CSimpleSqlite|InfoBase|IInfoBase|CMaster|tMessage|Element$"),
    ("battle", r"Battle|Enemy|CFactor|Rush|Combo|CSkill|Damage|Bullet|CAction|Hit|Field|Aiming|Weapon|CPause|CResult|Stage|Boss|Wave|CAI|Mission(?!Menu)|Quest|Arena"),
    ("gacha / shop / payment", r"Gacha|Shop|Payment|Purchase|Coin|Store|Billing|Trade|Exchange|Sphere(Box)?"),
    ("multiplayer / social", r"Multi|Friend|Room|Lobby|Matching|Photon|Chat|Guild|Ranking|Social|Follow"),
    ("online services / network", r"Network|Api|Http|Download|AssetPack|Server|Socket|Login|Notify|Push|Web|Url|CInfoManager|Info$"),
    ("deep space / events / campaigns", r"DeepSpace|Universe|EventMission|Campaign|Raid|Tower|Challenge|Limited|Bonus"),
    ("party / items / growth menus", r"Party|Item|Gear|Equip|Strength|Awaken|LimitOver|LimitBreak|Evolution|Mastery|Training|Talent|Storage|Craft|CCustom|Deco|Studio"),
    ("UI screens / menus (other)", r"Menu|Dialog|List|Window|Scene|View|UI|Popup|Button|Scroll|Title|Home|Chara|Person|Story|Scenario|Library|Book|Album|Gallery|Movie|Voice"),
]

# Work packages for the executed still-guest code (first match wins), used for planning.
PACKAGES = [
    ("main loop, threads, timing", r"^(Framework::CApplication|Framework::CFiberKernel|Aska::(Thread|Global|VSync|WaitVSync|GPUSync|BackBufferSync|PerformanceCounter|NotifierThread|PeripheralManager|BasePeripheral|ModifierManager|DeleteManager|IDeleteObject|Sequencer2|LifeCycleManager|Machine|App|TEvent\w*|SimpleMessageDispatcher|ArrayThreadSafe|StateCacheThreadSafe|Mouse|Task|WaitDraw)|\(free functions\)|Framework::(CFiberUnit|CMutex|CMouse|ResponderChain|CTimeElement|CMessageManager|CApplicationMemory|CTransitionValue)|CGame|CAppState|CPhase\w*|CTitleLogo|CTitle)$"),
    ("render: device/targets/passes/shadows/post (rest)", r"^Aska::(_?RenderDevice\w*|RenderThread\w*|RenderFinishCallbackThread|RenderManagerBase|RenderTarget\w*|RenderPass\w*|RenderContext\w*|RenderState\w*|RenderLayerChooser|RenderablePrimitive|RenderableObject|Shadow\w*|PostProcess\w*|OpticalPhenomenon|ObjectManager|Lens\w*|ToneMapTable|Filter\w*|\w*Filter|DPGHandler|DepthTextureObject|DiffuseCubeMap|MSAAChangerObject|ScissorObject|OccluderManager|Shader\w*|DirectShaderNode|UniformValueBuffer2|FrameBuffer|FrameTextureEntities|ResolveTargetGL|IndexBuffer|VertexBuffer|PrimitiveBuffer|SimplePrimRenderer|MeshGeneratorManager|Light\w*|Camera\w*|Projector|MaterialList|MaterialContext|TriListComp|BoundingVolumeObject|GlobalEnvironment)$|^C?RenderLayer\w*$|^CShadowController$"),
    ("textures, pixel formats, image decode", r"^Aska::(Texture\w*|ITextureHandler|IPixelFormatGL|PixelFormat\w*|DecodeTextureQueue|DecodeJpegObject|TDirectAifImage|VBRBuffer)$|^Framework::(CDirectTexture|CDeleteTextureTask)$"),
    ("particles, effects, dynamics", r"^Aska::(Particle\w*|IParticle\w*|ParticleEmitter<>|ParticleRenderableObject<>|\w*Dynamics\w*|DYNAMICS_CAPSULE|ADMJoint|ADMHandler|RigidBodyManager|IntegratedDynamicsEnvironment)$|^Framework::CEffect\w*$|^CArenaEffect\w*$|^bt\w*$"),
    ("sound and voice (rest)", r"^Aska::(Sound\w*|Audio\w*|WavePlayer|WaveVoiceBase|SEControlObject|MultiMediaStream|AskaADPCM|StaticStream|StreamingStream|AaoStreamingStream)$|^C(Menu|UI)VoiceManager$|^CSoundManager$|^Framework::CSound$|^CParameterSound\w*$|^CVoicePlayPriority$|^CArenaPlaySoundManager$"),
    ("scene objects, models, animation", r"^(CSceneObject\w*|CAnimationModelObject|CCharacterObject|PersonModel|CThingObject|CMapObject|CMapManager|CMovableObject|CBehaviorObject|CPostureObject|CArena|Collision|BehaviorQueueContainer|NormalVisitor|ReceiverWalker|Aska::(AimingObject|AofAhslManager|AacHandler|AaoHandler|CollisionHandler)|Framework::(CAnimation\w*|CCharacterModel|CBlendRatePlayer|CCamera|CCopyCamera|AaiExtractTranslate))$"),
    ("Cocos UI framework + UI managers", r"^(Framework::Cocos|Framework::CFader\w*|Framework::CBitmapFontManager|Framework::tSpriteParameter|CUIManager|CUIObject|CDialog\w*|CCocosSceneUnit|CPopupManager|CSceneReplacement|CInitializeDialog|Aska::(Font|FontHandle|TTextCompositor<>|Utf8))$"),
    ("screens and menus", r"^(CHome\w*|CSystemSettingMenu|CMissionMenu|CMissionSelectPart|COtherMenu|CScenarioLibrary|CDetail\w*|CCharacterPictureBook|CFactorInfoDialog|CCelItemList|CViewerBehavoir|CHaveCommon|CBannerBehavior|CTutorialManager|CPartyComposition|CDecoManager|CEvent|CUIUtility|CCommon|StaminaUtility|MissionUtility)$"),
    ("master data, parameters, user info", r"^(CMaster\w*|CParameter\w*|IInfoBaseMap|InfoBase\w*|CSimpleSqlite\w*|Aska::Yayoi|CInfoManager|C\w*Info|\w*Info|CCharacterData|CUserDataUtility|Master\w*Model|CFactorManager|CGameLocalKVS|Aska::LocalKVS|CStaticTransaction|CBuyHistory|CT_WorldBossInfo|tPlanetOpenCtrl)$"),
    ("platform / store / downloads (offline stubs)", r"^(NetworkApiCaller|ItemShopUtility|CMultiplayObject|AssetPack\w*|CGameAssetPack\w*|CPaymentManager|CCoinShop\w*|CDownload\w*|CNowloadingOnline|CGameResourceDownloader|CGameData\w*|CPhase_DataDownload|GamerServiceManager|CWebView|WebViewUtility|Platform|Aska::AndroidUtil|ANativeActivity_\*|android_\*|_JNIEnv|sqex|CErrorHandlerWrap|ErrorHandler|CGameDataDownloadError|BAS|CBASMessageManager)$"),
    ("resources, files, streams, memory", r"^(Framework::(CResource\w*|CFileLoader|CACSV|CCSV|CInteroperateParameter|CStringHash|CSTL\w*|T[A-Z]\w*|CFixedLengthAllocatorContainer|CHandleManager_Base)|Framework|Functor|CLanguage|CGameResourceManager|CAddShaderCacheManager|Aska::(LIBLManager|AHSL\w*|MappedMemory\w*|MappedResourceFilter|Memory\w*|ResourceManager|ResourceReadyQueue|BaseReadDevice|DiscRead\w*|DirectReadDevice|FakeStream|IStream|Decompress\w*|File|PathUtil|Encode|AffUtil|T[A-Z]\w*|Algo|detail|FileReadManager|IMemoryManager|MappedAddressSet|RingBuffer|StringUtility|FileStream|Aao\w*Stream|App\w*Proxy)|Aska)$"),
    ("event scenario (rest)", r"^EventScenario$"),
    ("libc++ template instances", r"^std::"),
    ("unattributed locals before the first export", r"^\(before first export\)$"),
]


def package_of(fam):
    fam = re.sub(r"(<>|_\*)$", "", fam)  # templates and C prefixes: match on the base name
    for name, rx in PACKAGES:
        if re.search(rx, fam):
            return name
    return "other"


def elf_reader(path):
    """Returns read(vaddr, n) -> bytes over the PROGBITS sections of an ELF file (None if unreadable)."""
    from elftools.elf.elffile import ELFFile
    try:
        with open(path, "rb") as f:
            secs = [(s["sh_addr"], s.data()) for s in ELFFile(f).iter_sections()
                    if s["sh_type"] == "SHT_PROGBITS" and s["sh_addr"]]
    except OSError:
        return None

    def read(va, n):
        for addr, data in secs:
            if addr <= va and va + n <= addr + len(data):
                return data[va - addr:va - addr + n]
        return None
    return read


def need_pyelftools():
    """pyelftools reads the library: under a python without it, run again with the repo's .venv."""
    try:
        import elftools  # noqa: F401
    except ImportError:
        venv = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), ".venv")
        py = os.path.join(venv, "bin", "python")
        if not os.path.exists(py) or os.path.realpath(sys.prefix) == os.path.realpath(venv):
            sys.exit("remaining.py needs pyelftools (pip install -r requirements.txt)")
        os.execv(py, [py, os.path.abspath(__file__)] + sys.argv[1:])


def short_kind(read, va, size):
    """Classifies a function under 8 bytes by its instruction."""
    b = read(va, 4) if read and size >= 4 else None
    if b is None:
        return "?"
    insn = int.from_bytes(b, "little")
    if insn == 0xD65F03C0:
        return "lone RET"
    if insn & 0xFC000000 == 0x14000000:
        return "tail branch (B)"
    return "other one-instruction"


def area_of(fam):
    f = fam.lstrip("~")
    for name, rx in AREAS:
        if re.search(rx, f):
            return name
    return "other game code"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("dirs", nargs="+")
    ap.add_argument("--native-list", required=True)
    ap.add_argument("--top", type=int, default=60)
    ap.add_argument("--hot", type=int, default=100, help="guest self samples for a family to count as hot")
    ap.add_argument("--tsv", help="write the per-function table of executed guest functions here")
    ap.add_argument("--lib", default=os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                                                  "work/libSOA-3.7.0.so"),
                    help="libSOA.so, to classify functions under 8 bytes")
    a = ap.parse_args()
    need_pyelftools()

    funcs = [(int(r[0], 16), int(r[1]), r[3]) for r in load_tsv(os.path.join(a.dirs[0], "functions.tsv"))]
    by_name = {n: i for i, (_, _, n) in enumerate(funcs)}
    by_off = {o: i for i, (o, _, _) in enumerate(funcs)}
    dem = demangle_all([n for _, _, n in funcs])
    fam, last = [], "(before first export)"
    for o, s, n in funcs:
        f = family_of(dem[n])
        fam.append(("~" + last) if f is None else f)
        if f is not None:
            last = f
    # merged family: locals counted with the export family they follow
    mfam = [f.lstrip("~") for f in fam]

    natives, labels = {}, {}
    for line in open(a.native_list):
        p = line.rstrip("\n").split("\t")
        sym, lab = p[0], (p[-1] if len(p) > 1 else "")
        i = by_off.get(int(sym[1:], 16)) if sym.startswith("@") else by_name.get(sym)
        if i is not None:
            natives[i] = sym
            labels[i] = lab

    executed, first_hit = set(), {}
    calls = collections.Counter()
    self_s, incl_s = collections.Counter(), collections.Counter()
    native_self = collections.Counter()
    hle_busy = 0
    other = 0
    boot_hits = set()
    for d in a.dirs:
        cov = load_tsv(os.path.join(d, "coverage.tsv"))
        t_title = min((float(r[1]) for r in cov if r[2].startswith(("_ZN6CTitle", "_ZN10CTitle"))), default=1e9)
        for r in cov:
            i = by_off.get(int(r[0], 16))
            if i is None:
                continue
            executed.add(i)
            t = float(r[1])
            if t < t_title:
                boot_hits.add(i)
        for r in load_tsv(os.path.join(d, "calls.tsv")):
            calls[(r[0], r[3])] += int(r[1])
        sp = os.path.join(d, "stacks.folded")
        if not os.path.exists(sp):
            continue
        for line in open(sp):
            st, n = line.rstrip("\n").rsplit(" ", 1)
            n = int(n)
            frames = [f for f in st.split(";") if f not in ("[hle]<return-to-host>", "[native]<return-to-host>")]
            leaf = frames[-1]
            if leaf.startswith("[hle]"):
                if leaf[5:] not in IDLE_HLE:
                    hle_busy += n
                continue
            if leaf.startswith("[native]"):
                native_self[leaf[8:]] += n
            elif leaf in by_name:
                self_s[by_name[leaf]] += n
            else:
                other += n
            seen = set()
            for f in frames[1:]:
                i = by_name.get(f)
                if i is not None and i not in seen:
                    seen.add(i)
                    incl_s[i] += n
            # (inclusive counts only busy samples: HLE waits were skipped above)

    # Transcribed: an a2c label, or an "aska math" native registered from aska_math_a2c.cpp (it
    # shares its label with the hand-written math functions).
    a2c_syms = set()
    math_a2c = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "src", "native", "engine", "math", "gen", "aska_math_a2c.cpp")
    if os.path.exists(math_a2c):
        a2c_syms.update(re.findall(r'"(_Z[A-Za-z0-9_]+)"', open(math_a2c, errors="ignore").read()))
    transcribed = {i for i in natives if TRANSCRIBED.search(labels[i]) or (labels[i].startswith("aska math") and natives[i] in a2c_syms)}
    native_called = {i for i, s in natives.items() if calls.get(("native", s))}
    guest_exec = executed - set(natives)  # executed and still guest code
    tg, tn = sum(self_s.values()), sum(native_self.values())
    busy = tg + tn + hle_busy + other
    pct = lambda x, t: f"{100.0 * x / t:.1f}%" if t else "-"

    out = []
    P = out.append
    P("# Remaining guest code")
    P("")
    P("runs: " + ", ".join(a.dirs))
    P("")
    P("## Headline")
    P("")
    all_exec = guest_exec | native_called
    read = elf_reader(a.lib)
    short = {i: short_kind(read, funcs[i][0], funcs[i][1]) for i in guest_exec if funcs[i][1] < 8}
    n_ret = sum(1 for k in short.values() if k == "lone RET")
    n_tr = len(transcribed)
    P(table([
        ["busy samples: guest JIT code", tg, pct(tg, busy)],
        ["busy samples: native replacements (incl. host GL they call)", tn, pct(tn, busy)],
        ["busy samples: HLE imports called from guest code", hle_busy, pct(hle_busy, busy)],
        ["busy samples: other/unknown", other, pct(other, busy)],
        ["executed functions (guest + native)", len(all_exec), ""],
        ["  of which native", len(native_called), pct(len(native_called), len(all_exec))],
        ["  of which still guest", len(guest_exec), pct(len(guest_exec), len(all_exec))],
        ["  still-guest bytes", fmt_bytes(sum(funcs[i][1] for i in guest_exec)), ""],
        ["  still guest, excluding lone-RET stubs", len(guest_exec) - n_ret, pct(len(guest_exec) - n_ret, len(all_exec))],
        ["function table", len(funcs), ""],
        ["  natives registered (resolved)", len(natives), pct(len(natives), len(funcs))],
        ["  natives: transcribed (a2c)", n_tr, pct(n_tr, len(natives))],
        ["  natives: hand-written / generated from layouts", len(natives) - n_tr, pct(len(natives) - n_tr, len(natives))],
        ["  never executed and not native", len(funcs) - len(all_exec) - len(set(natives) - native_called), ""],
    ], ["", "count", "%"], ["<", ">", ">"]))
    P("")

    # ---- natives by label
    P("## Native replacements by registration label")
    P("")
    lab_c = collections.Counter(labels.values())
    lab_called = collections.Counter(labels[i] for i in native_called)
    lab_tr = collections.Counter(labels[i] for i in transcribed)
    rows = [[k[:70], n, lab_tr[k], lab_called[k]] for k, n in lab_c.most_common(a.top)]
    P(table(rows, ["label", "fns", "transcribed", "called"], ["<", ">", ">", ">"]))
    P("")
    P("(called = called from guest code during the runs; natives reached only from other natives aren't counted)")
    P("")

    # ---- executed guest code by family
    F = collections.defaultdict(collections.Counter)
    for i in guest_exec:
        k = mfam[i]
        s = funcs[i][1]
        F[k]["fns"] += 1
        F[k]["bytes"] += s
        F[k]["self"] += self_s.get(i, 0)
        F[k]["incl"] = max(F[k]["incl"], incl_s.get(i, 0))
        F[k]["boot"] += i in boot_hits
        F[k]["tiny"] += s <= 16
        F[k]["lt8"] += s < 8
        F[k]["sampled"] += self_s.get(i, 0) > 0
    for k in F:
        F[k]["native"] = sum(1 for i in natives if mfam[i] == k)
        F[k]["total"] = 0
    for i in range(len(funcs)):
        if mfam[i] in F:
            F[mfam[i]]["total"] += 1

    def flags(k):
        c = F[k]
        f = []
        if c["self"] >= a.hot:
            f.append("hot")
        if c["boot"] == c["fns"]:
            f.append("boot" if c["self"] >= a.hot else "init")
        if c["tiny"] * 2 > c["fns"]:
            f.append("tiny")
        if c["lt8"]:
            f.append(f"<8B:{c['lt8']}")
        return ",".join(f)

    def effort(k):
        b = F[k]["bytes"]
        return "S" if b < 2048 else "M" if b < 10240 else "L" if b < 40960 else "XL"

    heads = ["family", "exec", "bytes", "self", "%busy", "incl", "native", "flags", "effort"]
    def rows_for(keys):
        return [[k[:46], F[k]["fns"], fmt_bytes(F[k]["bytes"]), F[k]["self"], pct(F[k]["self"], busy), F[k]["incl"], F[k]["native"], flags(k), effort(k)] for k in keys]

    P(f"## Still-guest executed code: top {a.top} families by guest self time")
    P("")
    P(table(rows_for(sorted(F, key=lambda k: -F[k]["self"])[: a.top]), heads))
    P("")
    P(f"## Still-guest executed code: top {a.top} families by executed bytes")
    P("")
    P(table(rows_for(sorted(F, key=lambda k: -F[k]["bytes"])[: a.top]), heads))
    P("")
    # flag totals
    tot = collections.Counter()
    for k in F:
        fl = flags(k)
        for tag in ("hot", "boot", "init", "tiny"):
            if tag in fl.split(","):
                tot[tag + "_fam"] += 1
                tot[tag + "_fns"] += F[k]["fns"]
                tot[tag + "_bytes"] += F[k]["bytes"]
                tot[tag + "_self"] += F[k]["self"]
    n_lt8 = sum(1 for i in guest_exec if funcs[i][1] < 8)
    n_tiny = sum(1 for i in guest_exec if funcs[i][1] <= 16)
    n_boot = len(guest_exec & boot_hits)
    n_unsampled = sum(1 for i in guest_exec if not incl_s.get(i))
    P("## Still-guest executed code: flag totals")
    P("")
    P(table([
        ["families", len(F), "", "", ""],
        ["hot families (self >= %d samples)" % a.hot, tot["hot_fam"], tot["hot_fns"], fmt_bytes(tot["hot_bytes"]), pct(tot["hot_self"], busy)],
        ["init families (every fn first ran before title; not hot)", tot["init_fam"], tot["init_fns"], fmt_bytes(tot["init_bytes"]), pct(tot["init_self"], busy)],
        ["hot families started at boot (loops/threads)", tot["boot_fam"], tot["boot_fns"], fmt_bytes(tot["boot_bytes"]), pct(tot["boot_self"], busy)],
        ["tiny families (most fns <= 16 bytes)", tot["tiny_fam"], tot["tiny_fns"], fmt_bytes(tot["tiny_bytes"]), pct(tot["tiny_self"], busy)],
        ["functions first run before title (any family)", "", n_boot, fmt_bytes(sum(funcs[i][1] for i in guest_exec & boot_hits)), ""],
        ["functions <= 16 bytes", "", n_tiny, fmt_bytes(sum(funcs[i][1] for i in guest_exec if funcs[i][1] <= 16)), ""],
        ["functions < 8 bytes (not hookable)", "", n_lt8, fmt_bytes(sum(funcs[i][1] for i in guest_exec if funcs[i][1] < 8)), ""],
        ["functions never seen in a sample (incl = 0)", "", n_unsampled, fmt_bytes(sum(funcs[i][1] for i in guest_exec if not incl_s.get(i))), ""],
    ], ["", "families", "fns", "bytes", "%busy self"], ["<", ">", ">", ">", ">"]))
    P("")
    # size histogram of executed guest functions
    bins = [(0, 8), (8, 17), (17, 65), (65, 257), (257, 1025), (1025, 4097), (4097, 1 << 30)]
    rows = []
    for lo, hi in bins:
        sel = [i for i in guest_exec if lo <= funcs[i][1] < hi]
        rows.append([f"{lo}-{hi - 1 if hi < 1 << 30 else '...'} B", len(sel), fmt_bytes(sum(funcs[i][1] for i in sel)), sum(self_s.get(i, 0) for i in sel)])
    P("Size distribution of still-guest executed functions:")
    P("")
    P(table(rows, ["size", "fns", "bytes", "self"]))
    P("")
    kinds = collections.Counter(short.values())
    kfam = collections.defaultdict(collections.Counter)
    for i, k in short.items():
        kfam[k][mfam[i]] += 1
    P("Functions under 8 bytes (not hookable), by instruction. A lone RET does nothing, so it is complete as it is;")
    P("a tail branch goes native with its target:")
    P("")
    P(table([[k, n, ", ".join(f"{f} {c}" for f, c in kfam[k].most_common(6))[:120]] for k, n in kinds.most_common()],
            ["kind", "fns", "main families"], ["<", ">", "<"]))
    P("")

    # ---- executed still-guest code by area
    EA = collections.defaultdict(collections.Counter)
    for i in guest_exec:
        ar = area_of(mfam[i])
        EA[ar]["fns"] += 1
        EA[ar]["bytes"] += funcs[i][1]
        EA[ar]["self"] += self_s.get(i, 0)
        EA[ar]["boot"] += i in boot_hits
        EA[ar]["lt8"] += funcs[i][1] < 8
        EA[ar]["unsampled"] += not incl_s.get(i)
    P("## Still-guest executed code by area")
    P("")
    rows = [[ar, EA[ar]["fns"], fmt_bytes(EA[ar]["bytes"]), EA[ar]["self"], pct(EA[ar]["self"], busy), EA[ar]["boot"], EA[ar]["unsampled"], EA[ar]["lt8"]]
            for ar in sorted(EA, key=lambda k: -EA[k]["self"])]
    P(table(rows, ["area", "fns", "bytes", "self", "%busy", "boot-first", "unsampled", "<8B"], ["<"] + [">"] * 7))
    P("")

    # ---- executed still-guest code by work package
    WP = collections.defaultdict(collections.Counter)
    wfam = collections.defaultdict(collections.Counter)
    for i in guest_exec:
        w = package_of(mfam[i])
        WP[w]["fns"] += 1
        WP[w]["bytes"] += funcs[i][1]
        WP[w]["self"] += self_s.get(i, 0)
        WP[w]["boot"] += i in boot_hits
        WP[w]["lt8"] += funcs[i][1] < 8
        WP[w]["unsampled"] += not incl_s.get(i)
        wfam[w][mfam[i]] += self_s.get(i, 0) + 1
    P("## Still-guest executed code by work package")
    P("")
    rows = [[w, WP[w]["fns"], fmt_bytes(WP[w]["bytes"]), WP[w]["self"], pct(WP[w]["self"], busy), WP[w]["boot"], WP[w]["unsampled"], WP[w]["lt8"],
             ", ".join(k for k, _ in wfam[w].most_common(5))[:110]] for w in sorted(WP, key=lambda k: -WP[k]["self"])]
    P(table(rows, ["package", "fns", "bytes", "self", "%busy", "boot-first", "unsampled", "<8B", "main families"], ["<"] + [">"] * 7 + ["<"]))
    P("")

    # ---- never executed
    never = [i for i in range(len(funcs)) if i not in executed and i not in natives]
    A = collections.defaultdict(collections.Counter)
    afam = collections.defaultdict(collections.Counter)
    for i in never:
        ar = area_of(mfam[i])
        A[ar]["fns"] += 1
        A[ar]["bytes"] += funcs[i][1]
        afam[ar][mfam[i]] += funcs[i][1]
    P("## Never executed (and not native), by area")
    P("")
    rows = []
    for ar in sorted(A, key=lambda k: -A[k]["bytes"]):
        top = ", ".join(f"{k} {fmt_bytes(v)}" for k, v in afam[ar].most_common(6))
        rows.append([ar, A[ar]["fns"], fmt_bytes(A[ar]["bytes"]), top[:150]])
    rows.append(["= total", len(never), fmt_bytes(sum(funcs[i][1] for i in never)), ""])
    never_ret = sum(1 for i in never if funcs[i][1] < 8 and short_kind(read, funcs[i][0], funcs[i][1]) == "lone RET")
    P(table(rows, ["area", "fns", "bytes", "largest families"], ["<", ">", ">", "<"]))
    P("")
    P(f"Of these, {never_ret} are lone-RET stubs.")
    P("")
    nat_never = set(natives) - native_called
    P(f"Natives registered but not called in these runs: {len(nat_never)} ({fmt_bytes(sum(funcs[i][1] for i in nat_never))} of guest code they replace).")
    P("")

    print("\n".join(out))
    if a.tsv:
        with open(a.tsv, "w") as f:
            f.write("# offset\tsize\tself\tincl\tboot\tfamily\tname\n")
            for i in sorted(guest_exec, key=lambda i: (-self_s.get(i, 0), mfam[i])):
                f.write(f"{funcs[i][0]:x}\t{funcs[i][1]}\t{self_s.get(i, 0)}\t{incl_s.get(i, 0)}\t{int(i in boot_hits)}\t{mfam[i]}\t{dem[funcs[i][2]]}\n")


if __name__ == "__main__":
    main()
