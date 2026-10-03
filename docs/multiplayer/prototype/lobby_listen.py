#!/usr/bin/env python3
"""Scratch lobby probe: listens on HOST:PORT (default 127.0.0.1:4001), logs every connection and
every packet of MultiplayRPC::LobbyProtocol / MO::BattleProtocol (24-byte scrambled header as
GameRPC, NO SHA-1 trailer: LobbyProtocol::Serialize @022f8aa4 just memcpys), and optionally answers
EnterLobby with EnterLobbyResult(Status 0) (--answer)."""
import socket, struct, sys, threading, time, binascii, argparse
PERM = [6, 4, 3, 0, 7, 1, 2, 5]
NAMES = {0xa8efdd88: 'UpdateRoomInfo', 0xcc88678c: 'GetRoomListResult', 0xe3a9a528: 'Automatch',
         0xe8fbdaaa: 'CloseRoomResult', 0xeac42001: 'CreateRoomResult', 0xefe1edb6: 'CloseRoom',
         0xfb5d0d73: 'EnterLobby', 0x05aed673: 'Error', 0x1fed00e2: 'AutomatchResult',
         0x2ddf640d: 'GetRoomList', 0x4e466d87: 'EnterLobbyResult', 0x6a1b49a5: 'CreateRoom',
         0x6b177840: 'UpdateRoomInfoResult', 0x43610d78: 'EnterRoom(battle)', 0xaeb31eca: 'StartMultiplay(battle)'}
def unscramble(b):
    t = 0
    for i in range(8): t |= b[i] << (8 * PERM[i])
    f = bytes(b[8 + i] ^ ((t >> (8 * (i & 7))) & 0xff) for i in range(16))
    size, fid, ctr = struct.unpack_from('<III', f); return t, size, fid, ctr, f[12]
def scramble(size, fid, ctr, flags, t):
    f = struct.pack('<IIIB3x', size, fid, ctr, flags)
    return bytes((t >> (8 * PERM[i])) & 0xff for i in range(8)) + bytes(f[i] ^ ((t >> (8 * (i & 7))) & 0xff) for i in range(16))
def log(*a):
    print(time.strftime('%H:%M:%S'), *a, flush=True)
def serve(c, addr, answer):
    log('connect', addr); buf = b''
    try:
        while True:
            d = c.recv(65536)
            if not d: log('closed by peer', addr); return
            buf += d
            while len(buf) >= 24:
                t, size, fid, ctr, flags = unscramble(buf)
                if size < 24 or size > 1 << 20: log('bad size', size, binascii.hexlify(buf[:64])); return
                if len(buf) < size: break
                body = buf[24:size]; buf = buf[size:]
                log(f'< {NAMES.get(fid, "?")} fid={fid:08x} ctr={ctr} flags={flags:#x} size={size} t={t}')
                log('  body', binascii.hexlify(body).decode())
                if answer and fid == 0xfb5d0d73:
                    pkt = scramble(24 + 8, 0x4e466d87, ctr, 0, time.monotonic_ns()) + struct.pack('<q', 0)
                    c.sendall(pkt); log('> EnterLobbyResult(0)')
    except Exception as e:
        log('error', addr, e)
    finally:
        c.close()
ap = argparse.ArgumentParser(); ap.add_argument('--host', default='127.0.0.1'); ap.add_argument('--port', type=int, default=4001)
ap.add_argument('--answer', action='store_true'); a = ap.parse_args()
s = socket.socket(); s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1); s.bind((a.host, a.port)); s.listen(8)
log('listening', a.host, a.port, 'answer' if a.answer else 'log only')
while True:
    c, addr = s.accept(); threading.Thread(target=serve, args=(c, addr, a.answer), daemon=True).start()
