#!/usr/bin/env -S sh -c 'exec "${0%/*}/../../tools/py" "$0" "$@"'
"""The native rebuild's queue (port/PLAN.md task 6): guest time per subsystem, and the subsystems' dependency waves.

Usage: rebuild_queue.py NAME=DIR [NAME=DIR...] [--markdown] [--min-edge N] [--native-list FILE | --soa SOA]

Each DIR is a SOA_PROFILE + SOA_COVERAGE run of one flow (port/README.md "Profiling"; NAME labels its
column, e.g. login=/tmp/p/login). Every guest function is assigned to a subsystem:
  1. a scaffolded subsystem's port/decomp/<s>/scope.txt (regexes on the demangled name; tools/subsystem.py);
  2. else the proposed SUBSYSTEMS table below, matched against the function's family (profile_report.py's
     family_of: the class or namespace; a local FUN_ function takes the family of the nearest preceding export,
     a hint, not a certainty).
Prints where the busy time goes per flow (guest code, natives, HLE work), then per subsystem: guest self
time (samples whose leaf is its guest code, the JIT time a native removes; natives never count here) in
total and per flow, native self time (samples whose leaf is one of its natives, `--native-list` or
`--soa`; see Profile for natives calling natives), inclusive time, executed / total functions and executed bytes, and its kind
(rewrite, host library, own track). Then the dependency graph measured from the sampled stacks: an edge
A -> B when A's code calls B's (weight = samples); edges under --min-edge samples are dropped; cycles
(callbacks, virtual calls back up) are merged into one group. The waves: a subsystem can start when every
subsystem it calls is in an earlier wave (types follow the same edges, roughly: a caller holds the callee's
objects); within a wave, hottest first.
"""
import argparse
import collections
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from profile_report import IDLE_HLE, demangle_all, family_of, load_tsv  # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

# (subsystem, level, kind, regex on the family, what). First match wins. Kinds: rewrite (Ghidra ->
# readable C++, types first), library (call the host library at a clean boundary: port/PLAN.md task 6),
# track (its own agent from day one: Cocos, Bullet). Level: the layer, leaves first (values 0, sync 1,
# memory 2, containers / formats 3, kernel / io / params base 4, engine systems and master data 5, the
# scene graph, UI toolkit and client info 6, the game 7). A measured call from a higher level to a lower one
# is a dependency (the caller uses the callee's functions and, mostly, its types); a call upwards is a
# callback (a thread entry, a task or a virtual handler: an interface, not a type dependency).
SUBSYSTEMS = [
    ("libcxx", 0, "library", r"^~?(std::__ndk1|__cxxabiv1|__gnu_cxx|_Unwind_\*|__cxa_\*)", "libc++ / libc++abi"),
    ("lib_sqlite", 0, "library", r"^~?sqlite3_\*", "SQLite 3.13.0"),
    ("lib_vorbis", 0, "library", r"^~?(vorbis\w*_\*|ogg\w*_\*|oggpack_\*|mdct_\*|drft_\*|floor[01]_\*|res[012]_\*|mapping0_\*|ov_\*|_vorbis\w*|_ve_\*|vorbis|book_\*)", "libVorbis 1.3.5 + libogg"),
    ("lib_zstd", 0, "library", r"^~?(ZSTD\w*_\*|HUF\w*_\*|FSE\w*_\*|ZSTDv\d+_\*)", "zstd"),
    ("lib_jpeg", 0, "library", r"^~?(jpeg_\*|jinit_\*|jcopy_\*|jdiv_\*|jround_\*|jzero_\*|j[a-z]+_\*)", "IJG libjpeg 9b"),
    ("lib_zlib", 0, "library", r"^~?(deflate\w*|inflate\w*|z_\*|crc32\w*|adler32\w*|_tr_\*|zcalloc|zcfree)", "zlib 1.2.5"),
    ("lib_crypto", 0, "library", r"^~?(AES_\*|CRYPTO_\*|EVP_\*|SHA\d*_\*|MD5_\*|HMAC\w*|RSA_\*|BN_\*)", "the bundled OpenSSL pieces"),
    ("bullet", 0, "track", r"^~?(bt[A-Z]\w*|gContact\w*)", "Bullet Physics 2.75, modified (stays on the guest: unused by 3.7.0 content)"),
    ("hash", 0, "rewrite", r"^~?(Framework::CHash\d*|Framework::CStringHash|Aska::Hash|Aska::SpookyHash\w*|Aska::CRC\w*|Aska::Utf8)$", "CHash32, SpookyHash, CRC, UTF-8"),
    ("math", 0, "rewrite", r"^~?(Aska::(Matrix\w*|Quaternion|Vector\w*|Segment|Line|Ray|Box|Sphere|Plane|AABB\w*|Frustum|Math\w*|Random\w*|Spline\w*|Curve\w*)|Framework::(CMatrix|CVector|CQuaternion))$", "vectors, matrices, intersection"),
    ("sync", 1, "rewrite", r"^~?(Framework::(CMutex|CThread\w*|CEvent|CSemaphore|CCriticalSection|CSpinLock)|Aska::(Event|Semaphore|Thread|Mutex|CriticalSection|SpinLock|Atomic\w*|FastCriticalSection))$", "mutexes, events, semaphores, threads"),
    ("memory", 2, "rewrite", r"^~?(Aska::(MemoryManager\w*|MappedMemory\w*|MemoryHandleManager|DeleteManager|_MemoryBlock|MemoryPool\w*|TSharedPointerCode)|Framework::(CAssignedMemoryManager\w*|CMemory\w*|CFixedLengthAllocatorContainer|TFixedLengthAllocator<>|CSTLAllocator<>|CHandleManager\w*))$", "the engine heaps, allocators, handles"),
    ("containers", 3, "rewrite", r"^~?(Aska::(T[A-Z]\w*<>|TPool\w*<>|StringUtility|String\w*|RingBuffer|PathUtil)|Framework::(T\w+<>|CSTL\w*<>|TStaticString<>|CString\w*)|TOMQuickSort<>|make_\*)$", "the engine's containers and strings (templates)"),
    ("data_formats", 3, "rewrite", r"^~?(Aska::(ASON|ACSV|MsgPack\w*|Json\w*)|Framework::(CACSV|CCSV)|msgpack|picojson|Json|_AsonSerializer|SerializerImpl|ReceiverWalker<>)$", "ASON, ACSV, msgpack"),
    ("kernel", 4, "rewrite", r"^~?(Aska::(SimpleMessageDispatcher|TaskManager|Task\w*|NotifierThread|GPUSync|AskaMainThread|LifeCycleManager|VSync|WaitVSync|WaitDraw|PerformanceCounter|Global|Functor\w*|Function\w*|AndroidUtil)|Framework::(CFiberKernel|CFiber\w*|CApplication|CTimeElement|ResponderChain|CMessageManager)|Aska|Framework|~?Functor_\*|Function_\*|aska_\*|Platform)$", "tasks, fibers, the message dispatcher, the app loop"),
    ("resource", 4, "rewrite", r"^~?(Aska::(BaseReadDevice|\w*ReadDevice|\w*Stream|Decompress\w*|LocalKVS|AHSL\w*<?>?|LIBLManager|File\w*|Archive\w*|ResourceReadyQueue|MappedResourceFilter|Decode\w*)|Framework::(CFileLoader|CResource\w*)|CGameResource\w*|CGameDataDownload\w*|CAssetInfo|CDownload\w*|CPhase_DataDownload|CGameLocalKVS)$", "files, streams, the resource cache, the downloader"),
    ("input", 4, "rewrite", r"^~?(Aska::(TouchPanel|Pad|Mouse|Keyboard|PeripheralManager|BasePeripheral)|Framework::(CPad\w*|CTouchPanel|CMouse|CKeyboard))$", "touch, pad, mouse, keyboard"),
    ("yayoi", 4, "rewrite", r"^~?Aska::Yayoi$", "Aska::Yayoi: network and the SQLite driver"),
    ("params", 4, "rewrite", r"^~?(CParameter(?!Manager$|Utility$|Sound)\w*<?>?|Parameter)$", "the parameter (de)serialization base: CParameterElementBase, CParameterParser, CParameterProperty*"),
    ("master", 5, "rewrite", r"^~?(CMasterParameter\w*<?>?|CSimpleSqliteConnector<>|StringDB\w*|CMaster\w*)$", "master data (SQLite tables, StringDB)"),
    ("render", 5, "rewrite", r"^~?(Aska::(Render\w*|_RenderDevice\w*|StateCache\w*|Shader\w*|DirectShader\w*|Texture\w*|ITextureHandler|VertexBuffer|IndexBuffer|PrimitiveBuffer|PostProcess\w*|Light\w*|Shadow\w*|Camera\w*|Lens|BackBufferSync|ResolveTarget\w*|MSAA\w*|FrameTexture\w*|Filter\w*|DepthTexture\w*|DiffuseCubeMap|ToneMapTable|Projector\w*|Occluder\w*|Material\w*|UniformValueBuffer\d*|IPixelFormat\w*|SimplePrimRenderer|RenderablePrimitive|OpticalPhenomenon|MeshGenerator\w*|GraphicsDevice\w*|GL\w*|ScissorObject)|Framework::CCamera|CNormalCamera|CRenderLayer\w*|CShadowController)$", "the GL renderer, shaders, post-processing, cameras"),
    ("anim", 5, "rewrite", r"^~?(Aska::(Aaf\w*|TAaf\w*<>|Aai\w*|Sequencer\d*|FastIk\w*|AimingObject|ILandscapeConstraint|GuideEffector)|Framework::(CAnimation\w*|CBlendRatePlayer|Aai\w*)|LocalSetController\w*)$", "animation controllers (TAaf*), blending, IK"),
    ("dynamics", 5, "rewrite", r"^~?(Aska::(Dynamics\w*|DYNAMICS_\w*|ArticulatedDynamics\w*|ADM\w*|IDE\w*|IDE_\w*<>|IntegratedDynamics\w*|CollisionHandler|RigidBody\w*))$", "Aska's own dynamics (cloth, joints, collision)"),
    ("particles", 5, "rewrite", r"^~?(Aska::(\w*Particle\w*<?>?|IParticle\w*))$", "particles"),
    ("audio", 5, "rewrite", r"^~?(Aska::(Sound\w*|Audio\w*|SLVoice|WavePlayer|Wave\w*|AskaOGG|AskaADPCM|SEControlObject|Voice\w*)|Framework::(CSound\w*)|CSound\w*|CParameterSound\w*|C\w*VoiceManager)$", "sound and voice"),
    ("text", 5, "rewrite", r"^~?(Aska::(TTextCompositor<>|Font\w*|Text\w*|Glyph\w*)|Framework::(CFont\w*|CText\w*|CBitmapFont\w*))$", "fonts and text layout"),
    ("scene", 6, "rewrite", r"^~?(Aska::(ObjectManager\w*|RenderableObject|Hierarchical\w*|JointObject|Aof\w*|DirectAof\w*|Asf\w*|DPGHandler|SkinMatrices\w*|TextureNode|ModifierManager|HeightObject\w*)|Framework::(C\w*Model|CEffectManager|CDirectAof\w*)|CArenaEffectModel|CHomeModelViewManager|CAnimationModelObject)$", "the object manager, AOF models, skinning, the framework's models"),
    ("cocos", 6, "track", r"^~?(Framework::Cocos|CCocos\w*)", "Framework::Cocos, tri-Ace's UI scene graph"),
    ("info", 6, "rewrite", r"^~?(CParameterManager|CParameterUtility|C\w*Info|C\w*InfoBase\w*|CInfoManager|IInfoBase\w*<?>?|InfoBase\w*<?>?|CCharacterData|CTimeUtility|StaminaUtility|CServerTime|BAS|MissionUtility|Framework::CInteroperateParameter)$", "the client's info objects and parameter manager (player, roster, missions)"),
    ("battle", 7, "rewrite", r"^~?(CBattle\w*|CArena\w*|CCharacterObject|CMovableObject|CThingObject|CMapObject|CMapManager|CStageManager|CFactorManager|CPartyManager|FieldComponent|CSignalChecker|CAI\w*|CSkill\w*|CEnemy\w*|CDamage\w*|CBullet\w*|CBehavior\w*|Behavior\w*|CMultiplayObject|COrderGaugeManager|CLimitOverCharacter|CDecoManager)$", "battle, arena, characters on the field"),
    ("event", 7, "rewrite", r"^~?(EventScenario|CEvent\w*|CTalk\w*|CScenario\w*)$", "story scenes (EventScenario)"),
    ("ui", 7, "rewrite", r"^~?(CUI\w*|CDialog\w*|CPopupManager|C\w*Menu|CNowLoading\w*|CNowloading\w*|CDownloadProgressBar|CWebView|Framework::CFader\w*|CTitle|CHome\w*|CGacha\w*|CCoinShop|CLoginBonus|CShop\w*|CMenu\w*|CCommon|CResult|CMissionSelect\w*|CBanner\w*)$", "screens, menus, dialogs, the home and gacha screens"),
    ("game", 7, "rewrite", r"^~?(CGame|CPhase\w*|CSceneObjectContainer|CStaticTransaction|CApiNotify|CAPIWatcher|CApiCaller|CPaymentManager|GamerServiceManager|CErrorHandlerWrap|ErrorHandler|sqex|CSaveData\w*|CTutorialManager)$", "the game's phases, transactions, API notifications, the tutorial"),
]
_SUB_RE = [(s, re.compile(r)) for s, _, _, r, _ in SUBSYSTEMS]
LEVEL = {s: lv for s, lv, _, _, _ in SUBSYSTEMS}
KIND = {s: k for s, _, k, _, _ in SUBSYSTEMS}
WHAT = {s: w for s, _, _, _, w in SUBSYSTEMS}


def scaffolded_scopes():
    out = []
    d = os.path.join(REPO, "port", "decomp")
    if os.path.isdir(d):
        for s in sorted(os.listdir(d)):
            p = os.path.join(d, s, "scope.txt")
            if os.path.isfile(p):
                for line in open(p):
                    line = line.strip()
                    if line and not line.startswith("#"):
                        out.append((s, re.compile(line)))
    return out


# The port's own code that runs under a guest name: not a rebuild target, kept out of the waves. FakeApiCaller is
# the in-process route (--server inproc): its natives run the local server's requests inside the client.
PORT_OWN = [("(route)", re.compile(r"^~?FakeApiCaller$"))]


def subsystem_of_family(fam):
    for s, r in _SUB_RE + PORT_OWN:
        if r.search(fam):
            return s
    return None


def native_symbols(lines, by_name, by_off, sub):
    """`soa --list-native` lines -> {native symbol: subsystem}. A native counts for the subsystem its guest
    function belongs to (the same assignment as the guest self time, so a family's guest and native time
    land in one row); a symbol outside the function table takes the subsystem its note starts with
    ("audio: ..."). Conditional natives (`[conditional]`, off unless an option asks) are listed too: they
    are simply never sampled when off."""
    out = {}
    for line in lines:
        p = line.rstrip("\n").split("\t")
        if not p or not p[0]:
            continue
        sym, note = p[0], (p[-1] if len(p) > 1 else "")
        i = by_off.get(int(sym[1:], 16)) if sym.startswith("@") else by_name.get(sym)
        s = sub[i] if i is not None else None
        if s is None or s == "(unassigned)":
            m = re.match(r"(\w+): ", note)
            if m and m.group(1) in LEVEL:
                s = m.group(1)
        out[sym] = s or "(unassigned)"
    return out


class Profile:
    """The runs' samples by subsystem. Leaf frames (profile.cpp's stacks.folded):
      - a guest function            -> guest self of its subsystem (JIT time: what a native would remove);
        when the frame above it is "[native]<the same function>", it is the original body a native runs
        (NATIVE_FUNCTION_ORIG trampolines, callee hooks): still guest code, also counted in `own_hook`;
      - "[native]<symbol>"          -> native self of the symbol's subsystem (native_symbols); a native that
        calls another native as a C++ member keeps the samples (the callee has no frame of its own;
        SOA_PROFILE_HOST + host_profile.py --by-subsystem splits them by C++ code);
      - "[hle]<import>"             -> HLE work, or waiting (IDLE_HLE: not busy, dropped);
      - "[truncated]" / "[unknown]" -> other.
    busy = guest + native + HLE work + other, per run."""

    def __init__(self, runs, native_lines=None):
        self.names = [n for n, _ in runs]
        funcs = [(int(r[0], 16), int(r[1]), r[3]) for r in load_tsv(os.path.join(runs[0][1], "functions.tsv"))]
        if not funcs:
            sys.exit(f"{runs[0][1]}/functions.tsv missing")
        self.funcs = funcs
        dem = demangle_all([n for _, _, n in funcs])
        scopes = scaffolded_scopes()
        fam, sub = [], []
        last = "(before first export)"
        for o, s, n in funcs:
            f = family_of(dem[n])
            if f is None:
                f = "~" + last
            else:
                last = f
            fam.append(f)
            owner = next((s for s, rx in scopes if not n.startswith("FUN_") and rx.search(dem[n])), None)
            sub.append(owner or subsystem_of_family(f.lstrip("~")) or subsystem_of_family(f) or "(unassigned)")
        self.fam, self.sub = fam, sub
        by_name = {n: i for i, (_, _, n) in enumerate(funcs)}
        by_off = {o: i for i, (o, _, _) in enumerate(funcs)}
        self.native_sub = native_symbols(native_lines or [], by_name, by_off, sub)

        C = collections.Counter
        self.self_s, self.native_s, self.own_hook = C(), C(), C()   # subsystem -> samples
        self.self_run = collections.defaultdict(C)                # run -> subsystem -> guest samples
        self.native_run = collections.defaultdict(C)              # run -> subsystem -> native samples
        self.incl_s, self.fam_self, self.edges = C(), C(), C()
        self.native_fn = C()                                      # native symbol -> samples
        self.busy, self.kind = C(), collections.defaultdict(C)    # run -> busy; run -> guest/native/hle/other
        self.executed = set()
        for name, d in runs:
            for r in load_tsv(os.path.join(d, "coverage.tsv")):
                i = by_off.get(int(r[0], 16))
                if i is not None:
                    self.executed.add(i)
            for line in open(os.path.join(d, "stacks.folded")):
                st, n = line.rstrip("\n").rsplit(" ", 1)
                n = int(n)
                frames = [f for f in st.split(";")[1:] if f not in ("[hle]<return-to-host>", "[native]<return-to-host>")]
                if not frames:
                    continue
                leaf = frames[-1]
                if leaf.startswith("[hle]") and leaf[5:] in IDLE_HLE:
                    continue
                self.busy[name] += n
                idx = [by_name.get(f) for f in frames]
                if idx[-1] is not None:
                    s = sub[idx[-1]]
                    self.kind[name]["guest"] += n
                    self.self_s[s] += n
                    self.self_run[name][s] += n
                    self.fam_self[(s, fam[idx[-1]])] += n
                    if len(frames) > 1 and frames[-2] == "[native]" + leaf:
                        self.own_hook[s] += n
                elif leaf.startswith("[native]"):
                    sym = leaf[8:]
                    s = self.native_sub.get(sym)
                    if s is None:
                        i = by_name.get(sym)
                        s = sub[i] if i is not None else "(unassigned)"
                    self.kind[name]["native"] += n
                    self.native_s[s] += n
                    self.native_run[name][s] += n
                    self.native_fn[sym] += n
                elif leaf.startswith("[hle]"):
                    self.kind[name]["hle"] += n
                else:
                    self.kind[name]["other"] += n
                seen = set()
                prev = None
                for i in idx:
                    if i is None:
                        continue
                    s = sub[i]
                    if s not in seen:
                        seen.add(s)
                        self.incl_s[s] += n
                    if prev is not None and prev != s:
                        self.edges[(prev, s)] += n
                    prev = s


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("runs", nargs="+", help="NAME=DIR")
    ap.add_argument("--min-edge", type=int, default=50, help="drop dependency edges under N samples")
    ap.add_argument("--markdown", action="store_true")
    ap.add_argument("--unassigned", type=int, default=25, help="list the N hottest unassigned families")
    ap.add_argument("--native-list", help="output of `soa --list-native` (natives by subsystem; default: run --soa)")
    ap.add_argument("--soa", default=os.path.join(REPO, "build/port/soa"), help="soa binary for --list-native")
    a = ap.parse_args()
    runs = []
    for r in a.runs:
        name, _, d = r.partition("=")
        if not d:
            name, d = os.path.basename(os.path.normpath(r)), r
        runs.append((name, d))
    if a.native_list:
        native_lines = open(a.native_list).read().splitlines()
    else:
        try:
            native_lines = subprocess.run([a.soa, "--list-native"], capture_output=True, text=True, timeout=60).stdout.splitlines()
        except (OSError, subprocess.TimeoutExpired):
            native_lines = []
    P = Profile(runs, native_lines)
    sub, funcs, self_s, native_s, busy = P.sub, P.funcs, P.self_s, P.native_s, P.busy

    total_busy = sum(busy.values())
    nfun = collections.Counter(sub)
    nexec = collections.Counter(sub[i] for i in P.executed)
    bexec = collections.Counter()
    for i in P.executed:
        bexec[sub[i]] += funcs[i][1]
    subs = sorted(set(sub) | set(self_s) | set(native_s), key=lambda s: (-self_s[s], -native_s[s]))

    # Dependencies: measured calls between subsystems, classified by level (see SUBSYSTEMS).
    down, same, up = (collections.defaultdict(list) for _ in range(3))
    for (x, y), w in P.edges.items():
        if w < a.min_edge or "(unassigned)" in (x, y) or x not in LEVEL or y not in LEVEL:
            continue
        (down if LEVEL[y] < LEVEL[x] else same if LEVEL[y] == LEVEL[x] else up)[x].append((y, w))
    for d in (down, same, up):
        for x in d:
            d[x].sort(key=lambda yw: -yw[1])

    pct = lambda x, t=total_busy: f"{100.0 * x / t:.1f}%" if t else "-"
    names = P.names
    fmt = lambda lst, k=6: ", ".join(f"{y} ({w})" for y, w in lst[:k]) + (" ..." if len(lst) > k else "") if lst else "-"

    # Where the busy time goes, per flow.
    kinds = [("guest", "guest code (JIT)"), ("native", "natives"), ("hle", "HLE work (GL, libc, ...)"), ("other", "other (truncated stacks)")]
    tot_kind = collections.Counter()
    for n in names:
        tot_kind.update(P.kind[n])
    if a.markdown:
        print("| | " + " | ".join(names) + " | all |")
        print("|---|" + "---|" * (len(names) + 1))
        print("| busy samples | " + " | ".join(f"{busy[n]:,}" for n in names) + f" | {total_busy:,} |")
        for k, label in kinds:
            print(f"| {label} | " + " | ".join(pct(P.kind[n][k], busy[n]) for n in names) + f" | {pct(tot_kind[k])} |")
    else:
        print(f"busy samples: {total_busy} (" + ", ".join(f"{n} {busy[n]}" for n in names) + ")")
        print("  " + ", ".join(f"{label} {pct(tot_kind[k])}" for k, label in kinds))
    print()

    if a.markdown:
        print("| # | Subsystem | Level | Kind | Guest self | " + " | ".join(names) + " | Native self | Inclusive | Executed fns | Executed bytes | What |")
        print("|---|---|---|---|---|" + "---|" * len(names) + "---|---|---|---|---|")
    for k, s in enumerate(subs, 1):
        per = [f"{100.0 * P.self_run[n][s] / busy[n]:.1f}%" if busy[n] else "-" for n in names]
        row = [str(k), f"`{s}`", str(LEVEL.get(s, "-")), KIND.get(s, "-"), f"{self_s[s]} ({pct(self_s[s])})"] + per + [
            f"{native_s[s]} ({pct(native_s[s])})" if native_s[s] else "-",
            pct(P.incl_s[s]), f"{nexec[s]}/{nfun[s]}", f"{bexec[s] // 1024}K", WHAT.get(s, "")]
        print(("| " + " | ".join(row) + " |") if a.markdown else "  ".join(row))
    print()
    own = sum(P.own_hook.values())
    if own:
        print(f"Guest self includes {own} samples ({pct(own)}) of original bodies run under their own native's hook "
              "(NATIVE_FUNCTION_ORIG trampolines, callee hooks): " + ", ".join(f"{s} {n}" for s, n in P.own_hook.most_common(6)) + ".")
        print()
    levels = sorted({LEVEL[s] for s in subs if s in LEVEL})
    if a.markdown:
        print("| Wave | Subsystem | Guest self | Depends on (measured calls down, samples) | Same-level calls (co-develop) | Callbacks from it upwards |")
        print("|---|---|---|---|---|---|")
    for lv in levels:
        for s in sorted((s for s in subs if LEVEL.get(s) == lv), key=lambda s: -self_s[s]):
            row = [str(lv), f"`{s}`", pct(self_s[s]), fmt(down[s]), fmt(same[s], 4), fmt(up[s], 4)]
            print(("| " + " | ".join(row) + " |") if a.markdown else "wave " + "  ".join(row))
    print()
    un = sorted(((f, n) for (s, f), n in P.fam_self.items() if s == "(unassigned)"), key=lambda x: -x[1])[:a.unassigned]
    if un:
        print("Hottest unassigned families: " + ", ".join(f"{f} ({n})" for f, n in un))

if __name__ == "__main__":
    main()
