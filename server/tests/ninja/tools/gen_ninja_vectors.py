"""Ground truth for server/net/ninja/ninja_ref: run the client's own Ninja code (ninja_client.py,
unicorn) and write / check vectors.

  .venv/bin/python server/tests/ninja/tools/gen_ninja_vectors.py gen   [out]  write ninja_vectors.txt
  .venv/bin/python server/tests/ninja/tools/gen_ninja_vectors.py ref2client   reference-encrypt (ninja_check
        encrypt) -> client decrypt, for every algorithm and both IV generators
  .venv/bin/python server/tests/ninja/tools/gen_ninja_vectors.py packets [ninja_check]   whole packets: a
        client request (SetSetTitle) decrypted by the reference; reference-encrypted replies
        through the client's Deserialize + GetGachaRes (all algorithms; without flag 0x80 they
        must fail); a clear message (EquipAccessoryRes)
  .venv/bin/python server/tests/ninja/tools/gen_ninja_vectors.py choose        the client's own algorithm
        choice (GameProtocoledData's encrypt helper @0153928c, time()-seeded generator)
  .venv/bin/python server/tests/ninja/tools/gen_ninja_vectors.py requests [out]   whole request packets
        serialized by the client (Set<Api> + its Ninja), for soa-server's decoder: writes
        server/tests/net/client_requests.txt (checked by soa-server --selftest net/client-requests)
  .venv/bin/python server/tests/ninja/tools/gen_ninja_vectors.py replies [soa-server]   reply packets
        built by soa-server (--wire-tool) through the client's Deserialize + Get<Api>Res / GetLoginResult /
        GetResultStart / GetResultUpdateSession / GetProtocolError
"""
import os
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ninja_client import F, Client  # noqa: E402

HERE = os.path.dirname(os.path.abspath(__file__))
ALGS = {"SEED": 0x01E6AC1B, "AES128": 0x021D4314, "Blowfish": 0x03478CAF, "CAST128": 0x048A4DFE,
        "Camellia128": 0x052E3A67, "Serpent": 0x07FEDCA9, "Twofish": 0x08A723AB, "IDEA": 0x0951FAD3,
        "MARS": 0x0A325482, "MISTY1": 0x0B46B571}
# The key is the first 32 chars of the bridge's sharedSecurityKey JSON string (KeyStore::Set
# copies 32 bytes; KeyStore::Get treats a key whose first byte is 0 as "no key").
KEYS = [b"9f86d081884c7d659a2feaa0c55ad015", b"Q2xpZW50U2Vzc2lvbktleS0wMDAwMDE="]
LENS = [1, 4, 7, 8, 9, 15, 16, 17, 20, 31, 32, 33, 100, 255, 1000]
R2S = [0x00000000, 0x00000001, 0x12345678, 0x9ABCDEF1, 0xFFFFFFFF, 0x0BADF00D, 0x7FFFFFFE]


def plaintext(n, seed):
    # Deterministic bytes, plus a realistic body (u32 length + MessagePack map) for the longer ones.
    b = bytes((i * 131 + seed * 17 + 7) & 0xFF for i in range(n))
    if n >= 20:
        mp = b"\x82\xa4data\x81\xa4Time\xb32021-06-30 12:00:00\xa6status\x00"
        body = struct.pack("<I", len(mp)) + mp
        b = (body * (n // len(body) + 1))[:n]
    return b


def salt_of(env):
    return env[0] | env[6] << 8 | env[12] << 16 | env[18] << 24


def gen(out):
    c = Client()
    lines = ["# Ninja envelopes produced by the client's own code (libSOA.so 3.7.0, run under unicorn by",
             "# server/tests/ninja/tools/gen_ninja_vectors.py gen). Checked by server/tests/ninja/ninja_check.sh.",
             "# env <algorithm> <r2> <salt> <key> <plaintext> <envelope>   (hex)"]
    n = 0
    for name, alg in ALGS.items():
        for ki, key in enumerate(KEYS):
            for ri, r2 in enumerate(R2S):
                for li, ln in enumerate(LENS):
                    if (ki + ri + li) % 3:  # a spread of combinations, not the full product
                        continue
                    p = plaintext(ln, ri + li)
                    env, _ = c.encrypt(alg, r2, key, p)
                    if env is None:
                        raise SystemExit("client encrypt failed: %s r2=%08x len=%d" % (name, r2, ln))
                    back, err = c.decrypt(key, env)
                    if back != p:
                        raise SystemExit("client decrypt of its own envelope failed: %s err %d" % (name, err))
                    lines.append("env %s %08x %08x %s %s %s" % (name, r2, salt_of(env), key.hex(), p.hex(), env.hex()))
                    n += 1
    with open(out, "w") as f:
        f.write("\n".join(lines) + "\n")
    print("wrote %d vectors to %s" % (n, out))


def ref2client(check_bin):
    c = Client()
    bad = n = 0
    for name, alg in ALGS.items():
        for key in KEYS[:1]:
            for r2 in (0x12345678, 0x12345679, 0xCAFEBABE, 0xCAFEBABF):  # both generator parities
                for ln in (1, 16, 33, 517):
                    p = plaintext(ln, r2 & 7)
                    salt = (r2 * 7 + ln) & 0xFFFFFFFF
                    r = subprocess.run([check_bin, "encrypt", "%x" % alg, "%x" % r2, "%x" % salt, key.hex(), p.hex()],
                                       capture_output=True, text=True)
                    n += 1
                    if r.returncode:
                        print("FAIL %s: reference encrypt failed" % name)
                        bad += 1
                        continue
                    env = bytes.fromhex(r.stdout.strip())
                    back, err = c.decrypt(key, env)
                    if back != p:
                        bad += 1
                        print("FAIL %s r2=%08x len=%d: client decrypt error %d" % (name, r2, ln, err))
                    # A flipped bit anywhere must be refused (MAC), and a wrong key too.
                    if ln == 33:
                        for pos in (0, 5, 30, len(env) - 1):
                            e2 = bytearray(env)
                            e2[pos] ^= 0x10
                            b2, _ = c.decrypt(key, bytes(e2))
                            if b2 is not None:
                                bad += 1
                                print("FAIL %s: client accepted a corrupted envelope (byte %d)" % (name, pos))
                        b3, _ = c.decrypt(KEYS[1], env)
                        if b3 is not None:
                            bad += 1
                            print("FAIL %s: client accepted the wrong key" % name)
    print("%s: %d/%d reference envelopes decrypted by the client" % ("FAIL" if bad else "PASS", n - bad, n))
    return bad


def choose():
    """Runs the GameProtocoledData encrypt helper (@0153928c) like a request serializer does."""
    import collections
    c = Client()
    ninja = c.new_ninja(KEYS[0])
    names = {v: k for k, v in ALGS.items()}
    seen = collections.Counter()
    out = c.alloc(0x400)
    for i in range(200):
        c.time_value = 1600000000 + i * 37
        p = plaintext(20, i)
        pp = c.alloc(len(p), p)
        r, _ = c.call(F["ninja_encrypt"], ninja, pp, len(p), out, 0x400)
        env = c.read(out, r)
        back, err = c.decrypt(KEYS[0], env)
        alg = header_alg(env)
        seen[names.get(alg, hex(alg))] += 1
        if back != p:
            print("FAIL: client decrypt of a helper envelope (alg %s)" % names.get(alg))
    print("algorithms chosen by the client in 200 messages:", dict(seen))


# --- whole packets through the client's GameProtocoledData (Set*/Serialize/Deserialize/Get*)
GPD = "_ZN4Aska5Yayoi7GameRPC18GameProtocoledData"
SYMS = {
    "SetSetTitle": GPD + "11SetSetTitleERKNS1_13RequestHeaderEjPNS_8Cryption5NinjaE",
    "SetGachaRes": GPD + "11SetGachaResEPKajPNS_8Cryption5NinjaE",
    "GetGachaRes": GPD + "11GetGachaResERPaRjPNS_8Cryption5NinjaE",
    "SetEquipAccessoryRes": GPD + "20SetEquipAccessoryResEPKaj",
    "GetEquipAccessoryRes": GPD + "20GetEquipAccessoryResERPaRj",
    "Deserialize": GPD + "11DeserializeEPKaPmm",
}
FID_GACHA_RES = 0x77F99232


def unscramble(h):
    t = (h[4] << 56 | h[0] << 48 | h[7] << 40 | h[1] << 32 | h[2] << 24 | h[6] << 16 | h[5] << 8 | h[3])
    f = bytes(h[8 + i] ^ (t >> (8 * (i & 7)) & 0xFF) for i in range(16))
    size, fid, counter = struct.unpack("<III", f[:12])
    return size, fid, counter, f[12]


def scramble(size, fid, counter, flags, t=0x1122334455667788):
    f = struct.pack("<IIIB3x", size, fid, counter, flags)
    tb = t.to_bytes(8, "little")
    h = bytearray(24)
    for i, j in enumerate((6, 4, 3, 0, 7, 1, 2, 5)):
        h[i] = tb[j]
    for i in range(16):
        h[8 + i] = f[i] ^ tb[i & 7]
    return bytes(h)


def fake_data(c, cap=0x10000):
    obj = c.alloc(0x100)
    buf = c.alloc(cap)
    c.write(obj + 0x40, struct.pack("<Q", buf))
    c.write(obj + 0x20, struct.pack("<I", cap))
    c.write(obj + 0x34, struct.pack("<I", 0x5A5A0001))
    return obj, buf


def status(c, p):
    return struct.unpack("<q", c.read(p, 8))[0]


def deserialize(c, pkt):
    """GameProtocoledData::Deserialize on a whole wire packet (as wire_test's read_back)."""
    obj = c.alloc(0x100)
    p = c.alloc(len(pkt), pkt)
    st, used = c.alloc(8), c.alloc(8)
    off = 0
    for _ in range(4):
        c.call(c.sym(SYMS["Deserialize"]), obj, p + off, used, len(pkt) - off, x8=st)
        u = struct.unpack("<Q", c.read(used, 8))[0]
        if status(c, st) < 0 or u == 0 or c.read(obj + 0x19, 1)[0]:
            off += u
            break
        off += u
    return obj, status(c, st), c.read(obj + 0x19, 1)[0]


def packets(check_bin):
    import hashlib
    c = Client()
    key = KEYS[0]
    ninja = c.new_ninja(key)
    bad = 0
    # 1. A request built by the client (SetSetTitle: RequestHeader + u32) -> reference decrypt.
    hdr = bytes(range(0x11, 0x21))
    st = c.alloc(8)
    seen = set()
    for i in range(40):
        c.time_value = 1600000000 + 977 * i
        obj, buf = fake_data(c)
        hp = c.alloc(16, hdr)
        c.call(c.sym(SYMS["SetSetTitle"]), obj, hp, 0xA0B0C0D0 + i, ninja, x8=st)
        size = struct.unpack("<I", c.read(obj + 0x24, 4))[0]
        pkt = c.read(buf, size)
        psize, fid, counter, flags = unscramble(pkt)
        env = pkt[24:]
        r = subprocess.run([check_bin, "decrypt", key.hex(), env.hex()], capture_output=True, text=True)
        out = r.stdout.split()
        want = hdr + struct.pack("<I", 0xA0B0C0D0 + i)
        if status(c, st) or psize != size or flags != 0x80 or r.returncode or bytes.fromhex(out[1]) != want:
            bad += 1
            print("FAIL request %d: status %d flags %#x ref %s" % (i, status(c, st), flags, r.stdout.strip()))
        seen.add(out[0] if out else "?")
    print("requests: 40 SetSetTitle packets decrypted by the reference (algorithms: %s)" % " ".join(sorted(seen)))
    # 2. Replies encrypted by the reference -> the client's Deserialize (SHA-1) + GetGachaRes.
    blob = b"\x82\xa4data\x81\xa4Time\xb32021-06-30 12:00:00\xa6status\x00"
    body = struct.pack("<I", len(blob)) + blob
    for name, alg in ALGS.items():
        for flags in (0x80, 0):
            r = subprocess.run([check_bin, "encrypt", "%x" % alg, "%x" % 0x2468ACE1, "%x" % 0x13579BDF, key.hex(), body.hex()],
                               capture_output=True, text=True)
            env = bytes.fromhex(r.stdout.strip())
            size = 24 + len(env)
            pkt = scramble(size, FID_GACHA_RES, 7, flags) + env
            pkt += hashlib.sha1(pkt).digest()
            obj, dst, done = deserialize(c, pkt)
            pp, pn, gst = c.alloc(8), c.alloc(4), c.alloc(8)
            if dst == 0 and done:
                c.call(c.sym(SYMS["GetGachaRes"]), obj, pp, pn, ninja, x8=gst)
            g = status(c, gst) if dst == 0 and done else dst
            got = c.read(struct.unpack("<Q", c.read(pp, 8))[0], len(blob)) if g == 0 else b""
            ok = (g == 0 and got == blob) if flags else g != 0
            if not ok:
                bad += 1
                print("FAIL reply %s flags %#x: deserialize %d, GetGachaRes %d" % (name, flags, dst, g))
            elif not flags:
                print("  reply %-11s without flag 0x80 refused as expected (status %d)" % (name, g))
    print("replies: reference-encrypted GachaRes accepted by Deserialize + GetGachaRes for all algorithms")
    # 3. A clear message (one of the 12 without a Ninja*): EquipAccessoryRes round trip.
    obj, buf = fake_data(c)
    bp = c.alloc(len(body), blob)
    c.call(c.sym(SYMS["SetEquipAccessoryRes"]), obj, bp, len(blob), x8=st)
    size = struct.unpack("<I", c.read(obj + 0x24, 4))[0]
    pkt = c.read(buf, size)
    psize, fid, counter, flags = unscramble(pkt)
    if status(c, st) or flags != 0 or pkt[24:] != body:
        bad += 1
        print("FAIL clear EquipAccessoryRes: flags %#x body %s" % (flags, pkt[24:].hex()))
    else:
        print("clear: EquipAccessoryRes (fid %08x) is u32 length + blob in the clear, flags 0" % fid)
    # 4. Which messages travel in the clear: the Set* serializers that take no Ninja*.
    import re
    sets = {}
    for n in c.L.by_name:
        m = re.match(GPD + r"(\d+)(Set\w+)", n)
        if m:
            name = m.group(2)[:int(m.group(1))]
            sets[name] = "Ninja" in n
    clear = sorted(k for k, enc in sets.items() if not enc)
    print("clear: %d of %d Set* serializers take no Ninja*: %s" % (len(clear), len(sets), " ".join(clear)))
    if len(clear) != 12:
        bad += 1
        print("FAIL: expected 12 clear messages")
    print("%s: packet checks" % ("FAIL" if bad else "PASS"))
    return bad


# --- soa-server's wire layer against the client (server/net/) -------------------------------------
TABLE = os.path.join(HERE, "..", "..", "..", "..", "port", "src", "native", "api", "gen", "wire_table.inc")
NET_TESTS = os.path.join(HERE, "..", "..", "net")
RESPONSES = os.path.join(HERE, "..", "..", "..", "..", "port", "fakeapi", "responses")


def mangled_setters():
    import re
    out = {}
    for line in open(TABLE):
        m = re.match(r'\{"(\w+)", "(\w+)", 0x([0-9a-f]+)u', line)
        if m:
            out[m.group(1)] = (m.group(2), int(m.group(3), 16))
    return out


def mp(v):
    """A tiny MessagePack encoder (the venv has no msgpack module): dict, list, str, bool, int >= 0."""
    if isinstance(v, bool):
        return b"\xc3" if v else b"\xc2"
    if isinstance(v, int):
        if v < 0x80:
            return bytes([v])
        if v <= 0xFF:
            return b"\xcc" + bytes([v])
        if v <= 0xFFFF:
            return b"\xcd" + struct.pack(">H", v)
        if v <= 0xFFFFFFFF:
            return b"\xce" + struct.pack(">I", v)
        return b"\xcf" + struct.pack(">Q", v)
    if isinstance(v, str):
        b = v.encode()
        return (bytes([0xA0 | len(b)]) if len(b) < 32 else b"\xd9" + bytes([len(b)])) + b
    if isinstance(v, list):
        return bytes([0x90 | len(v)]) + b"".join(mp(e) for e in v)
    if isinstance(v, dict):
        hdr = bytes([0x80 | len(v)]) if len(v) < 16 else b"\xde" + struct.pack(">H", len(v))
        return hdr + b"".join(mp(k) + mp(e) for k, e in v.items())
    raise TypeError(v)


# A battle log like the client's CBattleLogInfo serialization (docs/ason.md "Battle log"), shortened:
# a few u32 properties, the bool, and the BattleEvaluationInfo array the server reads.
FAKE_LOG = {"is_defeat": False, "damage_total": 48210, "damage_total_party": 48210, "hit_max": 12, "hit_total": 57,
            "battle_result": 1, "continue_count": 0, "mission_time": 83, "mission_total_time": 91,
            "PlayerCharacter": [], "BattleEvaluationInfo": [{"evaluation_type": 1, "score": 48210},
                                                            {"evaluation_type": 6, "score": 83000}]}


def requests(out):
    """Request packets serialized by the client's own Set<Api> (+ its Ninja for the encrypted ones)."""
    import hashlib
    c = Client()
    key = KEYS[0]
    ninja = c.new_ninja(key)
    setters = mangled_setters()
    hdr = struct.pack("<IIIHH", 123456789, 0, 0x1A2B3C4D, 0, 1471)
    st = c.alloc(8)

    def s(text, n=None):
        b = text.encode() + b"\0"
        return c.alloc(max(len(b), n or 0) + 64, b)

    log = mp(FAKE_LOG)
    uuid = "3f2a9c4e-8b1d-4e7a-9c3f-1b2d3e4f5a6b"
    cases = [  # (name, args after (this, header), expected: method, ints, strs, vecs, dev, log props)
        ("SetTitle", lambda: [0xA0B0C0D0], ("SetTitle", [0xA0B0C0D0], [], [], None, None)),
        ("GetPlayer", lambda: [], ("GetPlayer", [], [], [], None, None)),
        ("Login", lambda: [s(uuid), s("fcm-token-example"), 17, s("00000000-0000-0000-0000-000000000000"), 36, 1],
         ("Login", [], [], [], None, None)),
        ("MissionStart", lambda: [0, 3519778102, 0, 0, 0, 0, 0], ("MissionStart", [0, 3519778102, 0, 0, 0, 0, 0], [], [], None, None)),
        ("MissionEnd", lambda: [3519778102, c.alloc(len(log), log), len(log), 5],
         ("MissionEnd", [3519778102, 5], [], [], None, "mission_time=83,damage_total=48210,is_defeat=0,eval1=48210,eval6=83000")),
        ("GachaOnce", lambda: [4218244542, s("0123456789abcdef0123456789abcdef")],
         ("GachaOnce", [4218244542], ["0123456789abcdef0123456789abcdef"], [], None, None)),
        ("LockItem", lambda: [c.alloc(16, struct.pack("<QQ", 0x7D000001, 0x7D000002)), 2],
         ("LockItem", [], [], [[0x7D000001, 0x7D000002]], None, None)),
        ("CreatePlayer", lambda: [s(uuid), s("Fayt", 191), 2, s("ffffffff-0000-0000-0000-00000000", 32)],
         ("CreatePlayer", [], ["Fayt", uuid, "ffffffff-0000-0000-0000-00000000"], [], 2, None)),
        ("StartBridge", lambda: [], ("StartBridge", [], [], [], None, None)),
        ("UpdateSession", lambda: [s("0123456789abcdef0123456789abcdef")],
         ("UpdateSession", [], ["0123456789abcdef0123456789abcdef"], [], None, None)),
        ("NoLoginStart", lambda: [s("abcdefghijklmnop"), 2], ("NoLoginStart", [], ["abcdefghijklmnop"], [], 2, None)),
    ]
    lines = ["# Request packets serialized by the client's own code (libSOA.so, GameProtocoledData::Set<Api> and its",
             "# Ninja; run under unicorn by server/tests/ninja/tools/gen_ninja_vectors.py requests). The SHA-1 trailer",
             "# is appended here and checked by the client's Deserialize. Checked by soa-server --selftest net/client-requests.",
             "# req NAME KEY(hex) PACKET(hex) METHOD INTS STRS(hex) VECS DEV LOG   ('-' = none)"]
    bad = 0
    for i, (name, args, want) in enumerate(cases):
        sym, fid = setters[name]
        c.time_value = 1600000000 + 977 * i
        obj, buf = fake_data(c)
        hp = c.alloc(16, hdr)
        a = [obj, hp] + args()
        if "Ninja" in sym:
            a.append(ninja)
        c.call(c.sym(sym), *a, x8=st)
        size = struct.unpack("<I", c.read(obj + 0x24, 4))[0]
        if status(c, st) or not size:
            bad += 1
            print("FAIL %s: serializer status %d" % (name, status(c, st)))
            continue
        pkt = c.read(buf, size)
        pkt += hashlib.sha1(pkt).digest()
        _, dst, done = deserialize(c, pkt)  # the client's receiver accepts it (SHA-1, known fid)
        psize, pfid, counter, flags = unscramble(pkt)
        if dst or not done or pfid != fid or flags != (0x80 if "Ninja" in sym else 0):
            bad += 1
            print("FAIL %s: deserialize %d done %d fid %08x flags %#x" % (name, dst, done, pfid, flags))
        m, ints, strs, vecs, dev, lg = want
        lines.append("req %s %s %s %s %s %s %s %s %s" % (
            name, key.hex(), pkt.hex(), m, ",".join(str(v) for v in ints) or "-",
            ",".join(x.encode().hex() for x in strs) or "-", ";".join(",".join(str(e) for e in v) for v in vecs) or "-",
            "-" if dev is None else dev, lg or "-"))
        print("  %-13s fid %08x flags %#04x %4d bytes" % (name, pfid, flags, len(pkt)))
    with open(out, "w") as f:
        f.write("\n".join(lines) + "\n")
    print("%s: wrote %d client request packets to %s" % ("FAIL" if bad else "PASS", len(cases) - bad, out))
    return bad


def replies(server_bin):
    """soa-server's reply packets through the client's own receiver and Get* readers."""
    c = Client()
    key = KEYS[0]
    ninja = c.new_ninja(key)
    bad = 0

    def tool(*args):
        r = subprocess.run([server_bin, "--wire-tool"] + [str(a) for a in args], capture_output=True, text=True)
        if r.returncode:
            raise SystemExit("soa-server --wire-tool %s: %s" % (" ".join(map(str, args)), r.stderr))
        return bytes.fromhex(r.stdout.strip())

    def body_of(name):
        return open(os.path.join(RESPONSES, name), "rb").read()

    def get(obj, sym, nargs_out, with_ninja=True):
        outs = [c.alloc(8) for _ in range(nargs_out)]
        gst = c.alloc(8)
        args = [obj] + outs + ([ninja] if with_ninja else [])
        c.call(c.sym(GPD + sym), *args, x8=gst)
        return status(c, gst), outs

    # Normal replies: u32 length + MessagePack, encrypted (and two clear ones)
    for api, getter, body, enc in [
            ("GetPlayer", "15GetGetPlayerResERPaRjPNS_8Cryption5NinjaE", body_of("player_get.msgp"), True),
            ("MissionStart", "18GetMissionStartResERPaRjPNS_8Cryption5NinjaE", body_of("mission_start.msgp"), True),
            ("MissionEnd", "16GetMissionEndResERPaRjPNS_8Cryption5NinjaE", body_of("mission_end.msgp"), True),
            ("GachaOnce", "15GetGachaOnceResERPaRjPNS_8Cryption5NinjaE", body_of("gacha_once_item.msgp"), True),
            ("NoLoginStart", "18GetNoLoginStartResERPaRj", body_of("player_get.msgp"), False),
            ("EquipAccessory", "20GetEquipAccessoryResERPaRj", body_of("update_home.msgp"), False)]:
        pkt = tool("reply", api, key.decode(), body.hex())
        obj, dst, done = deserialize(c, pkt)
        g, (pp, pn) = get(obj, getter, 2, enc) if dst == 0 and done else (dst, (0, 0))
        got = c.read(struct.unpack("<Q", c.read(pp, 8))[0], struct.unpack("<I", c.read(pn, 4))[0]) if g == 0 else b""
        ok = g == 0 and got == body
        bad += not ok
        print("  %-5s %-22s %5d bytes: deserialize %d, Get %d" % ("ok" if ok else "FAIL", api + " reply", len(pkt), dst, g))
    # LoginResult: u32 fid + u32 length + MessagePack
    body = body_of("player_get.msgp")
    pkt = tool("reply", "Login", key.decode(), body.hex())
    obj, dst, done = deserialize(c, pkt)
    g, (pf, pp, pn) = get(obj, "14GetLoginResultERNS1_12GameProtocol10FunctionIDERPaRjPNS_8Cryption5NinjaE", 3) \
        if dst == 0 and done else (dst, (0, 0, 0))
    ok = g == 0 and struct.unpack("<I", c.read(pf, 4))[0] == 0xA01C67EF and \
        c.read(struct.unpack("<Q", c.read(pp, 8))[0], struct.unpack("<I", c.read(pn, 4))[0]) == body
    bad += not ok
    print("  %-5s %-22s %5d bytes: deserialize %d, GetLoginResult %d" % ("ok" if ok else "FAIL", "LoginResult", len(pkt), dst, g))
    # ResultStart: char[1024] token, char[128] url, char[8]
    pkt = tool("start", "tok123", "http://127.0.0.1:44380/bridge", "x")
    obj, dst, done = deserialize(c, pkt)
    g, outs = get(obj, "14GetResultStartERPaS4_S4_", 3, False) if dst == 0 and done else (dst, [])

    def cstr(pp):
        p = struct.unpack("<Q", c.read(pp, 8))[0]
        return c.read(p, 200).split(b"\0")[0]
    ok = g == 0 and [cstr(o) for o in outs] == [b"tok123", b"http://127.0.0.1:44380/bridge", b"x"]
    bad += not ok
    print("  %-5s %-22s %5d bytes: deserialize %d, GetResultStart %d %s" % ("ok" if ok else "FAIL", "ResultStart", len(pkt), dst, g,
                                                                          [cstr(o) for o in outs] if g == 0 else ""))
    # ResultUpdateSession: header only
    pkt = tool("update-session")
    obj, dst, done = deserialize(c, pkt)
    gst = c.alloc(8)
    if dst == 0 and done:
        c.call(c.sym(GPD + "22GetResultUpdateSessionEv"), obj, x8=gst)
    g = status(c, gst) if dst == 0 and done else dst
    bad += g != 0
    print("  %-5s %-22s %5d bytes: deserialize %d, GetResultUpdateSession %d" % ("ok" if g == 0 else "FAIL", "ResultUpdateSession",
                                                                                 len(pkt), dst, g))
    # ProtocolError: s64 status + u32 fid
    pkt = tool("error", "a01c67ef", 19001)
    obj, dst, done = deserialize(c, pkt)
    g, (pf, ps) = get(obj, "16GetProtocolErrorERNS1_12GameProtocol10FunctionIDERNS_6StatusE", 2, False) \
        if dst == 0 and done else (dst, (0, 0))
    ok = g == 0 and struct.unpack("<I", c.read(pf, 4))[0] == 0xA01C67EF and struct.unpack("<q", c.read(ps, 8))[0] == 19001
    bad += not ok
    print("  %-5s %-22s %5d bytes: deserialize %d, GetProtocolError %d" % ("ok" if ok else "FAIL", "ProtocolError", len(pkt), dst, g))
    print("%s: soa-server reply packets read by the client" % ("FAIL" if bad else "PASS"))
    return bad


def header_alg(e):
    nx = lambda a, b: (~(e[a] ^ e[b])) & 0xFF  # noqa: E731
    v = nx(3, 8) | nx(9, 14) << 8 | nx(15, 2) << 16 | nx(21, 20) << 24
    return int.from_bytes(v.to_bytes(4, "little"), "big")


if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else "gen"
    if cmd == "gen":
        gen(sys.argv[2] if len(sys.argv) > 2 else os.path.join(HERE, "..", "ninja_vectors.txt"))
    elif cmd == "ref2client":
        sys.exit(1 if ref2client(sys.argv[2] if len(sys.argv) > 2 else os.environ.get("NINJA_CHECK_BIN", "/tmp/ninja_check")) else 0)
    elif cmd == "packets":
        sys.exit(1 if packets(sys.argv[2] if len(sys.argv) > 2 else os.environ.get("NINJA_CHECK_BIN", "/tmp/ninja_check")) else 0)
    elif cmd == "choose":
        choose()
    elif cmd == "requests":
        sys.exit(1 if requests(sys.argv[2] if len(sys.argv) > 2 else os.path.join(NET_TESTS, "client_requests.txt")) else 0)
    elif cmd == "replies":
        sys.exit(1 if replies(sys.argv[2] if len(sys.argv) > 2 else os.path.join(HERE, "..", "..", "build", "soa-server")) else 0)
