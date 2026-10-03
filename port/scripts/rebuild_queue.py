#!/usr/bin/env python3
"""The native rebuild's queue (port/PLAN.md task 6): guest time per subsystem, and the subsystems' dependency waves.

Usage: rebuild_queue.py NAME=DIR [NAME=DIR...] [--markdown] [--min-edge N]

Each DIR is a SOA_PROFILE + SOA_COVERAGE run of one flow (port/README.md "Profiling"; NAME labels its
column, e.g. login=/tmp/p/login). Every guest function is assigned to a subsystem:
  1. a scaffolded subsystem's port/decomp/<s>/scope.txt (regexes on the demangled name; tools/subsystem.py);
  2. else the proposed SUBSYSTEMS table below, matched against the function's family (profile_report.py's
     family_of: the class or namespace; a local FUN_ function takes the family of the nearest preceding export,
     a hint, not a certainty).
Prints, per subsystem: guest self time (samples where its code is the leaf, the JIT time a native removes)
in total and per flow, inclusive time, executed / total functions and executed bytes, and its kind
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
    ("bullet", 0, "track", r"^~?(bt[A-Z]\w*|gContact\w*)", "Bullet Physics 2.7x (the version pin)"),
    ("hash", 0, "rewrite", r"^~?(Framework::CHash\d*|Aska::Hash|Aska::detail|Aska::SpookyHash\w*|Aska::CRC\w*|Aska::Cryption|Aska::Utf8)$", "CHash32, SpookyHash, CRC, UTF-8"),
    ("math", 0, "rewrite", r"^~?(Aska::(Matrix\w*|Quaternion|Vector\w*|Segment|Box|Sphere|Plane|Frustum|Math\w*|Random\w*|Spline\w*|Curve\w*|_HO_\w*<?>?|Collision|AffUtil)|Framework::CMatrix|Collision|NormalVisitor)$", "vectors, matrices, intersection"),
    ("sync", 1, "rewrite", r"^~?(Framework::(CMutex|CThread\w*|CEvent|CSemaphore|CCriticalSection|CSpinLock)|Aska::(Event|Semaphore|Thread|Mutex|CriticalSection|SpinLock|Atomic\w*|GPUSync|StateCacheThreadSafe))$", "mutexes, events, semaphores, threads"),
    ("memory", 2, "rewrite", r"^~?(Aska::(MemoryManager\w*|MappedMemory\w*|MemoryHandleManager|DeleteManager|_MemoryBlock|MemoryPool\w*|TSharedPointerCode)|Framework::(CAssignedMemoryManager\w*|CMemory\w*|CFixedLengthAllocatorContainer|TFixedLengthAllocator<>|CSTLAllocator<>|CHandleManager\w*))$", "the engine heaps, allocators, handles"),
    ("containers", 3, "rewrite", r"^~?(Aska::(T[A-Z]\w*<>|TPool\w*<>|StringUtility|String\w*|RingBuffer|PathUtil)|Framework::(T\w+<>|CSTL\w*<>|TStaticString<>|CString\w*)|TOMQuickSort<>|make_\*)$", "the engine's containers and strings (templates)"),
    ("data_formats", 3, "rewrite", r"^~?(Aska::(ASON|ACSV|MsgPack\w*|Json\w*)|Framework::(CACSV|CCSV)|msgpack|picojson|Json|_AsonSerializer|SerializerImpl|ReceiverWalker<>)$", "ASON, ACSV, msgpack"),
    ("kernel", 4, "rewrite", r"^~?(Aska::(SimpleMessageDispatcher|TaskManager|Task\w*|NotifierThread|AskaMainThread|LifeCycleManager|VSync|WaitVSync|WaitDraw|PerformanceCounter|Global|Functor\w*|Function\w*|AndroidUtil)|Framework::(CFiberKernel|CFiber\w*|CApplication|CTimeElement|ResponderChain|CMessageManager)|Aska|Framework|~?Functor_\*|Function_\*|aska_\*|Platform)$", "tasks, fibers, the message dispatcher, the app loop"),
    ("resource", 4, "rewrite", r"^~?(Aska::(BaseReadDevice|\w*ReadDevice|\w*Stream|Decompress\w*|LocalKVS|AHSL\w*<?>?|LIBLManager|File\w*|Archive\w*|ResourceReadyQueue|MappedResourceFilter|Decode\w*)|Framework::(CFileLoader|CResource\w*)|CGameResource\w*|CGameDataDownload\w*|CAssetInfo|CDownload\w*|CPhase_DataDownload|CGameLocalKVS)$", "files, streams, the resource cache, the downloader"),
    ("input", 4, "rewrite", r"^~?(Aska::(TouchPanel|Pad|Mouse|Keyboard|PeripheralManager|BasePeripheral)|Framework::(CPad\w*|CTouchPanel|CMouse|CKeyboard))$", "touch, pad, mouse, keyboard"),
    ("yayoi", 4, "rewrite", r"^~?Aska::Yayoi$", "Aska::Yayoi: network and the SQLite driver"),
    ("params", 4, "rewrite", r"^~?(CParameter(?!Manager$|Utility$|Sound)\w*<?>?|Parameter)$", "the parameter (de)serialization base: CParameterElementBase, CParameterParser, CParameterProperty*"),
    ("master", 5, "rewrite", r"^~?(CMasterParameter\w*<?>?|CSimpleSqliteConnector<>|StringDB\w*|CMaster\w*)$", "master data (SQLite tables, StringDB)"),
    ("render", 5, "rewrite", r"^~?(Aska::(Render\w*|_RenderDevice\w*|Shader\w*|DirectShader\w*|Texture\w*|ITextureHandler|VertexBuffer|IndexBuffer|PrimitiveBuffer|PostProcess\w*|Light\w*|Shadow\w*|Camera\w*|Lens|BackBufferSync|ResolveTarget\w*|MSAA\w*|FrameTexture\w*|Filter\w*|DepthTexture\w*|DiffuseCubeMap|ToneMapTable|Projector\w*|Occluder\w*|Material\w*|UniformValueBuffer\d*|IPixelFormat\w*|SimplePrimRenderer|RenderablePrimitive|OpticalPhenomenon|MeshGenerator\w*|GraphicsDevice\w*|GL\w*|ScissorObject)|Framework::CCamera|CNormalCamera|CRenderLayer\w*|CShadowController)$", "the GL renderer, shaders, post-processing, cameras"),
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


def subsystem_of_family(fam):
    for s, r in _SUB_RE:
        if r.search(fam):
            return s
    return None


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("runs", nargs="+", help="NAME=DIR")
    ap.add_argument("--min-edge", type=int, default=50, help="drop dependency edges under N samples")
    ap.add_argument("--markdown", action="store_true")
    ap.add_argument("--unassigned", type=int, default=25, help="list the N hottest unassigned families")
    a = ap.parse_args()
    runs = []
    for r in a.runs:
        name, _, d = r.partition("=")
        if not d:
            name, d = os.path.basename(os.path.normpath(r)), r
        runs.append((name, d))

    funcs = [(int(r[0], 16), int(r[1]), r[3]) for r in load_tsv(os.path.join(runs[0][1], "functions.tsv"))]
    if not funcs:
        sys.exit(f"{runs[0][1]}/functions.tsv missing")
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
    by_name = {n: i for i, (_, _, n) in enumerate(funcs)}
    by_off = {o: i for i, (o, _, _) in enumerate(funcs)}

    self_s = collections.Counter()           # subsystem -> guest leaf samples
    self_run = collections.defaultdict(collections.Counter)  # run -> subsystem -> samples
    incl_s = collections.Counter()
    fam_self = collections.Counter()
    edges = collections.Counter()            # (caller sub, callee sub) -> samples
    busy = collections.Counter()
    executed = set()
    for name, d in runs:
        for r in load_tsv(os.path.join(d, "coverage.tsv")):
            i = by_off.get(int(r[0], 16))
            if i is not None:
                executed.add(i)
        for line in open(os.path.join(d, "stacks.folded")):
            st, n = line.rstrip("\n").rsplit(" ", 1)
            n = int(n)
            frames = [f for f in st.split(";")[1:] if f not in ("[hle]<return-to-host>", "[native]<return-to-host>")]
            if not frames:
                continue
            leaf = frames[-1]
            if leaf.startswith("[hle]") and leaf[5:] in IDLE_HLE:
                continue
            busy[name] += n
            idx = [by_name.get(f) for f in frames]
            if idx[-1] is not None:
                s = sub[idx[-1]]
                self_s[s] += n
                self_run[name][s] += n
                fam_self[(s, fam[idx[-1]])] += n
            seen = set()
            prev = None
            for i in idx:
                if i is None:
                    continue
                s = sub[i]
                if s not in seen:
                    seen.add(s)
                    incl_s[s] += n
                if prev is not None and prev != s:
                    edges[(prev, s)] += n
                prev = s

    total_busy = sum(busy.values())
    nfun = collections.Counter(sub)
    nexec = collections.Counter(sub[i] for i in executed)
    bexec = collections.Counter()
    for i in executed:
        bexec[sub[i]] += funcs[i][1]
    subs = sorted(set(sub) | set(self_s), key=lambda s: -self_s[s])

    # Dependencies: measured calls between subsystems, classified by level (see SUBSYSTEMS).
    down, same, up = (collections.defaultdict(list) for _ in range(3))
    for (x, y), w in edges.items():
        if w < a.min_edge or "(unassigned)" in (x, y) or x not in LEVEL or y not in LEVEL:
            continue
        (down if LEVEL[y] < LEVEL[x] else same if LEVEL[y] == LEVEL[x] else up)[x].append((y, w))
    for d in (down, same, up):
        for x in d:
            d[x].sort(key=lambda yw: -yw[1])

    pct = lambda x: f"{100.0 * x / total_busy:.1f}%" if total_busy else "-"
    names = [n for n, _ in runs]
    fmt = lambda lst, k=6: ", ".join(f"{y} ({w})" for y, w in lst[:k]) + (" ..." if len(lst) > k else "") if lst else "-"
    if a.markdown:
        print("| # | Subsystem | Level | Kind | Guest self | " + " | ".join(names) + " | Inclusive | Executed fns | Executed bytes | What |")
        print("|---|---|---|---|---|" + "---|" * len(names) + "---|---|---|---|")
    else:
        print(f"busy samples: {total_busy} (" + ", ".join(f"{n} {busy[n]}" for n in names) + ")")
    for k, s in enumerate(subs, 1):
        per = [f"{100.0 * self_run[n][s] / busy[n]:.1f}%" if busy[n] else "-" for n in names]
        row = [str(k), f"`{s}`", str(LEVEL.get(s, "-")), KIND.get(s, "-"), f"{self_s[s]} ({pct(self_s[s])})"] + per + [
            pct(incl_s[s]), f"{nexec[s]}/{nfun[s]}", f"{bexec[s] // 1024}K", WHAT.get(s, "")]
        print(("| " + " | ".join(row) + " |") if a.markdown else "  ".join(row))
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
    un = sorted(((f, n) for (s, f), n in fam_self.items() if s == "(unassigned)"), key=lambda x: -x[1])[:a.unassigned]
    if un:
        print("Hottest unassigned families: " + ", ".join(f"{f} ({n})" for f, n in un))


if __name__ == "__main__":
    main()
