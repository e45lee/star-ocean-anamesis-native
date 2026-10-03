#!/usr/bin/env python3
"""Extract the decompiled functions the multiplayer study relied on into topic files here
(docs/multiplayer/decomp/<topic>.c) plus symbols.tsv (address, topic, symbol).

The sources are the study's Ghidra decompiles of work/libSOA-3.7.0.so (tools/decomp.sh output,
work/decomp/multiplayer-study-*.resolved.c, regenerable: see README.md) and the lambda bodies
decompiled from an analyzed project copy (LAMBDAS, optional). Addresses are Ghidra addresses
(ELF vaddr + 0x100000).

Usage: python3 docs/multiplayer/decomp/extract.py [DECOMP_DIR] [LAMBDA_FILE...]
"""
import glob, os, re, sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, '../../..'))
DECOMP = sys.argv[1] if len(sys.argv) > 1 else os.path.join(REPO, 'work/decomp')
LAMBDAS = sys.argv[2:]

TOPICS = [
    ('framing', r'(LobbyProtocol|BattleProtocol|GameProtocol)::(Serialize|Deserialize|GetFunctionName|CheckRecast|CheckTime)\b'
                r'|ProtocoledData::(_write_header|_read_header|Deserialize|AllocateBuffer)\b'
                r'|TProtocolSuite<.*LobbyProtocol.*>::Open'),
    ('lobby_messages', r'LobbyProtocoledData::(Get\w+|SetEnterLobby|SetCreateRoom|SetGetRoomList|SetCloseRoom)\b'),
    ('battle_messages', r'BattleProtocoledData::(Get\w+|SetMissionEnd|SetMessage|SetEnterRoom|SetStartMultiplayRes)\b'),
    ('manager', r'CMultiplayManager::(InitBattleRPCClient|InitMatchingClient|Initialize|InitMultiplayManager|Progress|On\w+'
                r'|Send\w+|Pack\w+|IsMultiplay|SetSendCharacter|IsSendCharacter)\b'
                r'|IMultiplayManagerBase::(Init|FlushSendSnapshot|FlushSendMessage|Run|RunSnapshot|RunMessage)\b'
                r'|IMultiplayNotify::OnProtocolError'),
    ('ownership', r'CPartyManager::(IsMultiplaySendCharacter|SetDisconnectPlayer|SetupCharacter_Local)\b|CBattleUtility::CreateCharacter\('
                  r'|CUIUtility::(IsMultiplayHost|SetMultiplayHost)\b|CPauseMenu::IsHost'),
    ('ui_flow', r'CMultiPlay3::(Server_\w+|RoomInfo2RoomData|IsEnableBattleStart|IsHost|InitializeEx|StateInit|UpdatePlayerListEx'
                r'|GetLobbyOpenedMaxTime|RetryAutoMatch)\b|CMissionMenu::ToMultiUI\w*|CParameterUtility::IsOpenMulti'
                r'|CParameterPlayer::CopyForMultiplay|CUIMatchingNotify::On\w+|MatchingClient::\w+'),
    ('mission_api', r'CStageManager::(CallMissionEnd|CallMissionStart|CallMissionFailed)\b|CApiNotify::OnMissionStart\b'),
]

def blocks(path):
    src = open(path, encoding='utf-8', errors='replace').read()
    for b in re.split(r'(?m)^(?=// ==== )', src):
        if not b.startswith('// ==== '): continue
        head = b.split('\n', 1)[0]
        m = re.search(r'@ ?([0-9a-f]{8})', b[:600])
        yield head, (m.group(1) if m else ''), b.rstrip() + '\n'

def main():
    seen = set(); out = {t: [] for t, _ in TOPICS}; rows = []
    files = sorted(glob.glob(os.path.join(DECOMP, 'multiplayer-study-*.resolved.c')))
    for f in files:
        for head, addr, body in blocks(f):
            if 'non-virtual thunk' in head: continue
            name = re.sub(r'^// ==== (undefined\d* |\w+ \*? ?)?', '', head)
            for topic, rx in TOPICS:
                if re.search(rx, name):
                    if (addr or name) in seen: break
                    seen.add(addr or name); out[topic].append(body)
                    rows.append((addr, topic, re.sub(r'Aska::Yayoi::', '', name)[:200]))
                    break
    for f in LAMBDAS:
        for head, addr, body in blocks(f):
            if addr in seen: continue
            seen.add(addr); out.setdefault('ui_lambdas', []).append(body)
            rows.append((addr, 'ui_lambdas', head[8:].strip()[:200]))
    for topic, bodies in out.items():
        if not bodies: continue
        with open(os.path.join(HERE, topic + '.c'), 'w') as o:
            o.write(f'// {topic}: Ghidra decompiles of work/libSOA-3.7.0.so (3.7.0), extracted by extract.py.\n'
                    '// Data, not code: see README.md and docs/multiplayer.md for what they show.\n\n')
            o.writelines(b + '\n' for b in bodies)
    with open(os.path.join(HERE, 'symbols.tsv'), 'w') as o:
        o.write('address\ttopic\tsymbol\n')
        for r in sorted(rows): o.write('\t'.join(r) + '\n')
    print(len(rows), 'functions')

main()
