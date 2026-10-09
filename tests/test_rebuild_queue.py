"""port/scripts/rebuild_queue.py on a synthetic profile: guest self is guest code only, natives by subsystem.

The stacks are the shapes runtime/src/core/profile.cpp writes (stacks.folded, leaf last): a native that
calls another native through guest_call's direct path (run_direct) is "[native]A;[native]B", guest code
called from a native is "[native]A;guest", an original body a native runs under its own hook
(NATIVE_FUNCTION_ORIG) is "[native]A;A", a native's host wait ends in "[hle]native_wait".
"""
import os

import rebuild_queue

SIGNAL = "_ZN4Aska7SLVoice11AudioSignalEm"          # audio (Aska::SLVoice)
AUDIO_RUN = "_ZN4Aska11SoundObject8AudioRunEv"     # audio (Aska::SoundObject)
LOCK = "_ZN9Framework6CMutex4LockEv"               # sync (Framework::CMutex)
DISPATCH = "_ZN4Aska23SimpleMessageDispatcher11PostMessageEv"  # kernel
LOGGED_IN = "_ZNK13FakeApiCaller8LoggedInEv"       # the in-process route
ENTRY = "_ZN4Aska6Thread4MainEPv"


def write_profile(d, stacks):
    os.makedirs(d, exist_ok=True)
    names = [ENTRY, SIGNAL, AUDIO_RUN, LOCK, DISPATCH, LOGGED_IN]
    with open(os.path.join(d, "functions.tsv"), "w") as f:
        f.write("# offset\tsize\tsource\tname\n")
        for k, n in enumerate(names):
            f.write(f"{0x1000 + 0x100 * k:x}\t256\texport\t{n}\n")
    with open(os.path.join(d, "coverage.tsv"), "w") as f:
        f.write(f"# offset\tfirst\tname\n{0x1000:x}\t1.0\t{ENTRY}\n")
    with open(os.path.join(d, "stacks.folded"), "w") as f:
        for st, n in stacks:
            f.write(f"thread:{ENTRY};{st} {n}\n")


NATIVES = [f"{SIGNAL}\taudio: SLVoice::AudioSignal", f"{LOCK}\tsync: CMutex::Lock",
           f"{DISPATCH}\tkernel: PostMessage", f"{LOGGED_IN}\tFakeApiCaller const"]


def test_guest_self_is_guest_code_only(tmp_path):
    d = str(tmp_path / "battle")
    write_profile(d, [
        (f"{ENTRY};{AUDIO_RUN}", 10),                                # plain guest code
        (f"{ENTRY};[native]{SIGNAL};[native]{LOCK}", 5),             # native -> native (run_direct)
        (f"{ENTRY};[native]{SIGNAL};{AUDIO_RUN}", 7),                # native -> guest
        (f"{ENTRY};[native]{DISPATCH};{DISPATCH}", 3),               # the original under its own hook
        (f"{ENTRY};[native]{SIGNAL}", 2),                            # native work
        (f"{ENTRY};[native]{SIGNAL};[hle]native_wait", 100),         # a native's wait: not busy
        (f"{ENTRY};[native]{SIGNAL};[hle]glDrawElements", 4),        # HLE work under a native
        (f"[native]{LOGGED_IN}", 6),                                 # the route
        (f"{ENTRY};[truncated]", 1),
    ])
    p = rebuild_queue.Profile([("battle", d)], NATIVES)
    assert p.busy["battle"] == 10 + 5 + 7 + 3 + 2 + 4 + 6 + 1
    assert dict(p.kind["battle"]) == {"guest": 20, "native": 13, "hle": 4, "other": 1}
    assert p.self_s["audio"] == 17 and p.self_s["kernel"] == 3 and p.self_s["sync"] == 0
    assert p.native_s["sync"] == 5 and p.native_s["audio"] == 2 and p.native_s["(route)"] == 6
    assert p.own_hook == {"kernel": 3}
    assert p.native_fn[LOCK] == 5


def test_native_without_list_takes_its_function_subsystem(tmp_path):
    d = str(tmp_path / "run")
    write_profile(d, [(f"{ENTRY};[native]{LOCK}", 9), ("[native]<coverage>", 1)])
    p = rebuild_queue.Profile([("run", d)], [])
    assert p.native_s["sync"] == 9 and p.native_s["(unassigned)"] == 1


def test_note_prefix_for_symbols_outside_the_table():
    m = rebuild_queue.native_symbols(["@1234\taudio: by offset", "_Zmissing\taudio: a native", "_Zother\tcommon: helper"], {}, {}, [])
    assert m == {"@1234": "audio", "_Zmissing": "audio", "_Zother": "(unassigned)"}
