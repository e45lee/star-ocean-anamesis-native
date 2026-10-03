#!/usr/bin/env python3
"""Scratch prototype (investigation only): a lobby (MultiplayRPC::LobbyProtocol) and a battle relay
(MO::BattleProtocol) for the 3.7.0 client, enough to see how far the unmodified client goes.

Wire (docs/multiplayer.md "The wire"): 24-byte scrambled header as GameRPC, raw struct bodies,
no SHA-1 trailer, no Ninja; flags 0x80 = body XORed with ChaCha20 (fixed key/nonce @0281a93f,
counter 0 per message) for MissionStartPush / MissionEnd / MissionEndPush / MissionContinue(Res).

The relay's API side is CANNED here (README "What it fakes"): MissionStartPush is composed from
MissionStartRes bodies captured from single-player soa-server runs (--start-body SLOT=FILE, one per
player slot; slot 0's is the fallback), MissionEndPush from captured MissionEndRes bodies
(--end-body SLOT=FILE). A real server runs the backend's MissionStart / MissionEnd per player.

The host rule (README "Who is host"): the relay gives the room's creator slot 0 and every joiner the
next free slot (EnterRoomResult), and the composed MissionStartRes gives each character the numeric
player id of its owner (PlayerCharacter[i].player_id = PlayerDetailInfo[i]+0x6c for the players'
characters, the host's id for the fillers): the client groups characters by that id
(CPartyManager::IsMultiplaySendCharacter @013a4e48 compares the owner id at CCharacterObject+0x1068
with the one of the character in its own slot), so two players with the same id both "own" every
player character and both are shown as HOST.
"""
import argparse, socket, struct, threading, time, binascii, os, collections
import msgpack

PERM = [6, 4, 3, 0, 7, 1, 2, 5]
L = dict(EnterLobby=0xfb5d0d73, EnterLobbyResult=0x4e466d87, CreateRoom=0x6a1b49a5, CreateRoomResult=0xeac42001,
         CloseRoom=0xefe1edb6, CloseRoomResult=0xe8fbdaaa, GetRoomList=0x2ddf640d, GetRoomListResult=0xcc88678c,
         UpdateRoomInfo=0xa8efdd88, UpdateRoomInfoResult=0x6b177840, Automatch=0xe3a9a528, AutomatchResult=0x1fed00e2,
         Error=0x05aed673)
B = dict(MissionEnd=0x8312a64c, ForceWinBattleStagePush=0x8566caa5, AIParameter=0x929765c3, StartMultiplayRes=0x948b0716,
         StartBattleStage=0x98905d95, DisconnectNodePush=0xa2667cb1, Stamp=0xa406ad38, UpdatePlayerListResult=0xa629dd36,
         SyncStartRushCombo=0xa6fd1715, StartMultiplay=0xaeb31eca, Reconnect=0xb1533261, FinishBattleStage=0xb24434d1,
         StartRushCombo=0xbad35e28, SyncFinishRushComboRes=0xbcacdd91, UpdatePlayerList=0xbd96f882, Message=0xc1f33acc,
         DebugMessageRes=0xc478bdba, ChangePublicRoomRes=0xd0a58e6d, ChangePublicRoom=0xd4c82eca, Snapshot=0xe0423298,
         MissionEndPush=0xe2d23280, ExitRoomPush=0xe5c49b5a, SyncStartRushComboRes=0xebfee137, ExitRoom=0xf2d53301,
         EnterRoomResult=0xf6dec31d, RequestProxy=0xf8697e7f, Packet=0xfebe96fc, SyncFinishRushCombo=0x0214d5cf,
         Error=0x05aed673, StartBattleStageRes=0x0f074e01, DebugMessage=0x10ce4f8f, AIParameterRes=0x16287e9b,
         SnapshotRes=0x3712ac8e, UpdatePlayerStatus=0x3764a958, StampPush=0x38c5438d, MissionStartPush=0x399501b0,
         MissionContinueRes=0x40db9f93, EnterRoom=0x43610d78, RSSIPush=0x440ed5b8, ExitRoomRes=0x44ac9b5c,
         PacketRes=0x535410ce, RequestProxyResult=0x5528c22a, MessageRes=0x57faa296, UpdatePlayerStatusRes=0x5e3b82b4,
         StartRushComboRes=0x62cd4997, FinishBattleStageRes=0x7309d699, MissionContinue=0x755cba3d)
NAME = {v: k for k, v in list(L.items()) + list(B.items())}
PDI = 0x480
ROOMINFO = 0x450

# ---- ChaCha20 (RFC 7539), the client's fixed key / nonce (InitBattleRPCClient @015a7568) ----
KEY = bytes.fromhex('2f725c277a702075747730385b2d3d2c27552a7d5f2820565e49427b25493300')
NONCE = b'A^#g2074RaJG'
def _rotl(v, c): return ((v << c) & 0xffffffff) | (v >> (32 - c))
def _qr(s, a, b, c, d):
    s[a] = (s[a] + s[b]) & 0xffffffff; s[d] = _rotl(s[d] ^ s[a], 16)
    s[c] = (s[c] + s[d]) & 0xffffffff; s[b] = _rotl(s[b] ^ s[c], 12)
    s[a] = (s[a] + s[b]) & 0xffffffff; s[d] = _rotl(s[d] ^ s[a], 8)
    s[c] = (s[c] + s[d]) & 0xffffffff; s[b] = _rotl(s[b] ^ s[c], 7)
def chacha20_xor(data, counter=0):
    k = struct.unpack('<8I', KEY); n = struct.unpack('<3I', NONCE); out = bytearray()
    for blk in range(0, len(data), 64):
        st = [0x61707865, 0x3320646e, 0x79622d32, 0x6b206574, *k, (counter + blk // 64) & 0xffffffff, *n]
        w = st[:]
        for _ in range(10):
            _qr(w, 0, 4, 8, 12); _qr(w, 1, 5, 9, 13); _qr(w, 2, 6, 10, 14); _qr(w, 3, 7, 11, 15)
            _qr(w, 0, 5, 10, 15); _qr(w, 1, 6, 11, 12); _qr(w, 2, 7, 8, 13); _qr(w, 3, 4, 9, 14)
        ks = struct.pack('<16I', *[(w[i] + st[i]) & 0xffffffff for i in range(16)])
        out += bytes(a ^ b for a, b in zip(data[blk:blk + 64], ks))
    return bytes(out)

def unscramble(b):
    t = 0
    for i in range(8): t |= b[i] << (8 * PERM[i])
    f = bytes(b[8 + i] ^ ((t >> (8 * (i & 7))) & 0xff) for i in range(16))
    size, fid, ctr = struct.unpack_from('<III', f); return size, fid, ctr, f[12]
def packet(fid, body, ctr=0, flags=0):
    t = time.monotonic_ns()
    if flags & 0x80: body = chacha20_xor(body)
    f = struct.pack('<IIIB3x', 24 + len(body), fid, ctr, flags)
    return bytes((t >> (8 * PERM[i])) & 0xff for i in range(8)) + bytes(f[i] ^ ((t >> (8 * (i & 7))) & 0xff) for i in range(16)) + body

COUNT = collections.Counter()   # (message, sender slot) -> count: who sends what
def log(*a):
    s = time.strftime('%H:%M:%S ') + ' '.join(str(x) for x in a)
    print(s, flush=True)

class Conn:
    def __init__(self, sock, tag): self.sock, self.tag, self.lock = sock, tag, threading.Lock()
    def send(self, fid, body, ctr=0, flags=0):
        with self.lock: self.sock.sendall(packet(fid, body, ctr, flags))
        log(f'  {self.tag} > {NAME.get(fid, hex(fid))} len={len(body)} flags={flags:#x}')

def read_packets(sock, tag, handler):
    buf = b''
    while True:
        d = sock.recv(1 << 16)
        if not d: log(tag, 'closed'); return
        buf += d
        while len(buf) >= 24:
            size, fid, ctr, flags = unscramble(buf)
            if size < 24 or size > 1 << 22: log(tag, 'bad size', size); return
            if len(buf) < size: break
            body = buf[24:size]; buf = buf[size:]
            if flags & 0x80: body = chacha20_xor(body)
            quiet = fid in (B['Snapshot'], B['Message'], B['AIParameter'], B['UpdatePlayerList'])
            if not quiet or os.environ.get('MP_VERBOSE'):
                log(f'{tag} < {NAME.get(fid, hex(fid))} ctr={ctr} flags={flags:#x} len={len(body)}', binascii.hexlify(body[:48]).decode())
            handler(fid, body, ctr)

def pdi_str(p):
    """slot, numeric player id, leader uid, name of a PlayerDetailInfo / PlayerInfo"""
    uid = struct.unpack_from('<Q', p, 0)[0]; slot, pid = struct.unpack_from('<II', p, 0x68)
    name = p[0x31:0x61].split(b'\0')[0].decode('utf-8', 'replace')
    return f'slot={slot} player_id={pid} leader_uid={uid} name={name!r}'

def load(path):
    return msgpack.unpackb(open(path, 'rb').read(), raw=False, strict_map_key=False)

def replace_id(o, old, new):
    """every integer equal to old (a player id) becomes new"""
    if isinstance(o, dict): return {k: replace_id(v, old, new) for k, v in o.items()}
    if isinstance(o, list): return [replace_id(v, old, new) for v in o]
    return new if (isinstance(o, int) and not isinstance(o, bool) and o == old) else o

def body_for(files, slot):
    return load(files.get(slot) or files[0])

def compose_start(room, A, recipient):
    """the MissionStartRes for one recipient: its own body (Player, Wallet...) with the room's party:
    each player's leader (its own body's PlayerCharacter[0]) owned by that player's id, then fillers
    from the host's party (owned by the host); multi_player_count = the players."""
    ids = {s: struct.unpack_from('<I', room.pdi[s], 0x6c)[0] for s, o in enumerate(room.conns) if o}
    d = body_for(A.start, recipient)
    own = d['data']['Player']['id']
    d = replace_id(d, own, ids[recipient])
    party, used = [], set()
    for s in sorted(ids):
        pc = dict(body_for(A.start, s)['data']['BattleParameter']['PlayerCharacter'][0]); pc['player_id'] = ids[s]
        party.append(pc); used.add(pc['id'])
    for pc in body_for(A.start, 0)['data']['BattleParameter']['PlayerCharacter'][1:]:
        if len(party) == 4: break
        if pc['id'] in used: continue
        pc = dict(pc); pc['player_id'] = ids[0]; party.append(pc); used.add(pc['id'])
    d['data']['BattleParameter']['PlayerCharacter'] = party
    d['data']['MissionParameter']['multi_player_count'] = len(ids)
    log(f'  MissionStart for slot {recipient}: party', [(p['id'], p['player_id']) for p in party])
    return msgpack.packb(d, use_bin_type=True)

def compose_end(room, A, slot):
    d = body_for(A.end, slot)
    pid = struct.unpack_from('<I', room.pdi[slot], 0x6c)[0]
    own = d['data'].get('Player', {}).get('id')
    if own is not None: d = replace_id(d, own, pid)
    return msgpack.packb(d, use_bin_type=True)

# ---- state ---------------------------------------------------------------------------------------
class Room:
    def __init__(self, rid, host_pi, cond):
        self.id, self.cond = rid, cond
        self.pdi = [bytes(PDI)] * 4
        self.conns = [None] * 4
        self.host_pi = host_pi
        self.stage_waiting = set(); self.finish_waiting = set(); self.loaded = set()
    def count(self): return sum(1 for c in self.conns if c)
    def roominfo(self, A):
        ri = bytearray(ROOMINFO)
        for s in range(4):
            pi = self.pdi[s][:0x70] if self.conns[s] else (self.host_pi if s == 0 and not any(self.conns) else bytes(0x70))
            ri[s * 0x70:(s + 1) * 0x70] = pi
        ri[0x238:0x238 + 0x1e8] = self.cond
        struct.pack_into('<H', ri, 0x428, A.relay_port)
        h = A.relay_host.encode()[:0x21]; ri[0x42a:0x42a + len(h)] = h
        struct.pack_into('<i', ri, 0x44c, self.id)
        return bytes(ri)
ROOMS = {}; RLOCK = threading.Lock(); NEXT = [1001]

def lobby_client(sock, addr, A):
    c = Conn(sock, f'lobby{addr[1]}')
    def h(fid, body, ctr):
        if fid == L['CreateRoom']:
            pi, cond = body[:0x70], body[0x70:0x70 + 0x1e8]
            with RLOCK:
                rid = NEXT[0]; NEXT[0] += 1
                # the room-id string the UI shows / searches (RoomCondition+0x14e)
                cond = bytearray(cond); s = str(rid).encode(); cond[0x14e:0x14e + 0x20] = s.ljust(0x20, b'\0')
                ROOMS[rid] = Room(rid, pi, bytes(cond))
            c.send(L['CreateRoomResult'], ROOMS[rid].roominfo(A), ctr)
        elif fid in (L['GetRoomList'],):
            begin, end = struct.unpack_from('<ii', body, 0x70 + 0x1e8)
            rooms = [r for r in ROOMS.values() if 0 < r.count() < 4][begin:end]
            c.send(L['GetRoomListResult'], struct.pack('<I', len(rooms)) + b''.join(r.roominfo(A) for r in rooms) + struct.pack('<ii', begin, len(rooms)), ctr)
        elif fid == L['Automatch']:
            rooms = [r for r in ROOMS.values() if 0 < r.count() < 4]
            if rooms: c.send(L['AutomatchResult'], struct.pack('<q', 0) + rooms[0].roominfo(A) + struct.pack('<i', 0), ctr)
            else: c.send(L['Error'], struct.pack('<qI', 1, fid), ctr)
        elif fid == L['CloseRoom']:
            c.send(L['CloseRoomResult'], struct.pack('<q', 0), ctr)
        elif fid == L['EnterLobby']:
            c.send(L['EnterLobbyResult'], struct.pack('<q', 0), ctr)
    try: read_packets(sock, c.tag, h)
    except Exception as e: log(c.tag, 'error', repr(e))
    finally: sock.close()

def relay_client(sock, addr, A):
    c = Conn(sock, f'relay{addr[1]}')
    me = {'room': None, 'slot': -1}
    def bcast(room, fid, body, skip=-1, flags=0):
        for s, o in enumerate(room.conns):
            if o and s != skip:
                try: o.send(fid, body, 0, flags)
                except OSError: pass
    def plist(room): return b''.join(room.pdi) + struct.pack('<H', room.count()) + b'\0' + struct.pack('<Q', 0)
    def h(fid, body, ctr):
        room, slot = me['room'], me['slot']
        if room is not None: COUNT[(NAME.get(fid, hex(fid)), slot)] += 1
        if fid == B['EnterRoom']:
            pdi, rid = bytearray(body[:PDI]), struct.unpack_from('<i', body, PDI)[0]
            room = ROOMS.get(rid)
            if not room:
                c.send(B['EnterRoomResult'], struct.pack('<iq', -1, 1) + bytes(4 * PDI) + struct.pack('<i', 0), ctr); return
            with RLOCK:
                slot = room.conns.index(None); room.conns[slot] = c
                struct.pack_into('<I', pdi, 0x68, slot); room.pdi[slot] = bytes(pdi)
            me['room'], me['slot'] = room, slot
            log(f'  room {rid}: EnterRoom ->', pdi_str(room.pdi[slot]), '(slot 0 = host)' if slot == 0 else '(guest)')
            c.send(B['EnterRoomResult'], struct.pack('<iq', slot, 0) + b''.join(room.pdi) + struct.pack('<i', room.count()), ctr)
            bcast(room, B['UpdatePlayerListResult'], plist(room), skip=slot)
        elif room is None:
            return
        elif fid == B['UpdatePlayerList']:
            c.send(B['UpdatePlayerListResult'], plist(room), ctr)
        elif fid == B['UpdatePlayerStatus']:
            pdi = bytearray(body[:PDI]); struct.pack_into('<I', pdi, 0x68, slot); room.pdi[slot] = bytes(pdi)
            c.send(B['UpdatePlayerStatusRes'], struct.pack('<q', 0), ctr)
            bcast(room, B['UpdatePlayerListResult'], plist(room))
        elif fid == B['ChangePublicRoom']:
            c.send(B['ChangePublicRoomRes'], struct.pack('<q', 0), ctr)
        elif fid == B['ExitRoom']:
            et, s = struct.unpack_from('<Ii', body)
            c.send(B['ExitRoomRes'], struct.pack('<I', et), ctr)
        elif fid == B['StartMultiplay']:
            bcast(room, B['StartMultiplayRes'], b''.join(room.pdi) + struct.pack('<H', room.count()))
            # every player "loaded": push the mission start (canned body; present[] = connected slots)
            def later():
                time.sleep(A.start_delay)
                present = bytes(1 if o else 0 for o in room.conns)
                for s, o in enumerate(room.conns):
                    if o:
                        b = compose_start(room, A, s)
                        o.send(B['MissionStartPush'], present + struct.pack('<I', len(b)) + b, 0, 0x80)
            threading.Thread(target=later, daemon=True).start()
        elif fid == B['StartBattleStage']:
            room.stage_waiting.add(slot)
            if room.stage_waiting >= {s for s, o in enumerate(room.conns) if o}:
                room.stage_waiting = set()
                bcast(room, B['StartBattleStageRes'], bytes(1 if o else 0 for o in room.conns))
        elif fid == B['FinishBattleStage']:
            room.finish_waiting.add(slot)
            if room.finish_waiting >= {s for s, o in enumerate(room.conns) if o}:
                room.finish_waiting = set()
                bcast(room, B['FinishBattleStageRes'], b'')
        elif fid == B['Snapshot']:
            bcast(room, B['SnapshotRes'], body, skip=slot)
        elif fid == B['Message']:
            # Message: i32 sender, u32 n, n x {u32 off(+pad), u32 size(+pad)}, payloads; offsets are from
            # the body start (GetMessageRes @01594658 adds body+0x18). MessageRes drops the sender: -4.
            n = struct.unpack_from('<I', body, 4)[0]; out = bytearray(body[4:])
            for i in range(n):
                off = struct.unpack_from('<I', out, 4 + 16 * i)[0]; struct.pack_into('<I', out, 4 + 16 * i, off - 4)
            bcast(room, B['MessageRes'], bytes(out), skip=slot)
        elif fid == B['AIParameter']:
            if room.conns[0] and slot != 0: room.conns[0].send(B['AIParameterRes'], body)
        elif fid == B['Stamp']:
            bcast(room, B['StampPush'], struct.pack('<iI', slot, struct.unpack_from('<I', body)[0]))
        elif fid == B['StartRushCombo']:
            s, tgt = struct.unpack_from('<bb', body)
            bcast(room, B['StartRushComboRes'], struct.pack('<bb', s, tgt))
        elif fid == B['SyncStartRushCombo']:
            s, ok = struct.unpack_from('<bB', body); f = struct.unpack_from('<f', body, 2)[0]
            bcast(room, B['SyncStartRushComboRes'], struct.pack('<bbBBfI', s, 4, ok, 0, f, 0))
        elif fid == B['SyncFinishRushCombo']:
            f, i = struct.unpack_from('<fi', body)
            bcast(room, B['SyncFinishRushComboRes'], struct.pack('<fiB', f, i, 1))
        elif fid == B['MissionEnd']:
            log(f'  MissionEnd from slot {slot}: uuid {body[:36].decode(errors="replace")[:8]}..., battle log {struct.unpack_from("<I", body, 40)[0]} bytes')
            log('  sender counts so far:', dict(sorted(COUNT.items())))
            b = compose_end(room, A, slot)
            c.send(B['MissionEndPush'], struct.pack('<I', len(b)) + b, ctr, flags=0x80)
        elif fid == B['MissionContinue']:
            log('  (MissionContinue not answered by the prototype)')
    try: read_packets(sock, c.tag, h)
    except Exception as e: log(c.tag, 'error', repr(e))
    finally:
        r, s = me['room'], me['slot']
        if r and s >= 0:
            r.conns[s] = None; r.pdi[s] = bytes(PDI)
            bcast(r, B['DisconnectNodePush'], struct.pack('<ii', s, 0))
        sock.close()

def listen(port, fn, A):
    s = socket.socket(); s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1); s.bind((A.bind, port)); s.listen(8)
    log('listening', fn.__name__, A.bind, port)
    while True:
        k, addr = s.accept(); log(fn.__name__, 'connect', addr)
        threading.Thread(target=fn, args=(k, addr, A), daemon=True).start()

if __name__ == '__main__':
    ap = argparse.ArgumentParser()
    ap.add_argument('--bind', default='127.0.0.1'); ap.add_argument('--lobby-port', type=int, required=True)
    ap.add_argument('--relay-port', type=int, required=True); ap.add_argument('--relay-host', default='127.0.0.1')
    ap.add_argument('--start-body', action='append', required=True, help='[SLOT=]FILE: a MissionStartRes (msgpack)')
    ap.add_argument('--end-body', action='append', required=True, help='[SLOT=]FILE: a MissionEndRes (msgpack)')
    ap.add_argument('--start-delay', type=float, default=1.0)
    A = ap.parse_args()
    def slots(items):
        out = {}
        for it in items:
            k, _, v = it.rpartition('=')
            out[int(k) if k else 0] = v
        return out
    A.start, A.end = slots(A.start_body), slots(A.end_body)
    threading.Thread(target=listen, args=(A.relay_port, relay_client, A), daemon=True).start()
    listen(A.lobby_port, lobby_client, A)
