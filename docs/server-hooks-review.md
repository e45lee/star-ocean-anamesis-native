# Server hooks the port uses: review notes (2026-10-01)

**Status: done (H, 2026-10-01, agent p3h-cleanup-hooks).** The FakeApiCaller route builds its requests as the 3.7.0 wire carries them (`server_port::inproc_request`): MissionEnd, MissionFailed, Sphere211MissionEnd and Sphere211MissionFailed carry the battle log the client's own serializer makes (the four request lambdas are identical but for the FunctionID and the `Send<Api>`: @015d68bc, @015d7048, @015f09e8, @015f0c18), parsed by the server library's `soaserver/battle_log.h` (moved there from `server/net`). `BattleLog` as a hook, `StatusProvider` and `InGameHooks` are gone from `soaserver/hooks.h`; only `AssetIndex` remains. Proof: port selftest `wire/inproc-parity` (the route's `Request` vs soa-server's decode of the client's own packet, the battle-log APIs through the real request lambdas). The notes below are the review as it was.

**The user's preference:** keep the in-process route as an override of FakeApiCaller, or a native in-process shim used in its place. Don't move it down to the GameRPC transport.

## Current hooks and whether 3.7.0 still needs them
Evidence: the unmodified 3.7.0 client over TCP (`soa-emu` + `soa-server`) reaches the same server state as the port's in-process server (E6 parity, `emulator/README.md` "Parity"), and it does so without any of the guest-reading hooks.

| Hook | In-process role | After the rebase |
|---|---|---|
| `server_port::capture` → `server::submit` / `handle` / `error_code` / `logged_in` / `enabled` (`port/src/native/api/fakeapi.cpp`) | the FakeApiCaller route itself | needed (the route) |
| `server::campaign::on_request` / `on_response` (from `fakeapi.cpp`) | the campaign module's per-request processing; `soa-server` calls the same functions | needed (it's server logic, not a guest read) |
| `BattleLog` (`soaserver/hooks.h`; port impl reads `CParameterManager+0x52d8…`) | battle-log values for MissionEnd (ranking, world boss, evaluations) | needed in-process: `FakeApiCaller::MissionEnd(u32, u32)` carries no log, while the wire `MissionEnd` (`hdr u32 blob u32`) does |
| `AssetIndex` | hides content whose assets are missing | needed (both modes) |
| `apply_client_master` (from the guest `sqlite3_exec` hook, `native/libs/lib_sqlite.cpp`) | edits the client's master copy (date shift, texts, banners) | needed in-process, unless the in-process route serves the edited master file the way `soa-server`'s CDN does |
| `StatusProvider` (guest `CalcStatus`) | character/NPC status from client code | likely removable: since T1 the server computes NPC status from master data (= the client, 822 rows); E6 parity matched without it |
| `InGameHooks::client_tutorial_cleared` | fallback when the server has no tutorial state | likely removable (the server's own state is the normal path) |
| `InGameHooks::add_login_bonus_popup` | pushes the popup into the offline client | likely removable on 3.7.0, whose client builds popups from the response (worked over TCP) |
| `InGameHooks::client_party_set` | campaign reads the party roster from guest memory | probably removable (the campaign worked over TCP); confirm |
| `server::campaign::end_mission_talk` (from `native/restore/restore_campaign.cpp`) | clears story missions because the offline build dropped MissionTalk | removable: 3.7.0 sends `EndMissionTalk` |
| `server::enabled` in `restore_home`, `restore_favor*` | gates the restore370-era client changes | removed with `restore370` (P3) |
| `server::web_page` (`native/ui/webview_local.cpp`) | the local notice-board page | port-only UI; keep or drop as wanted |
| `server::clock_now` / `set_server_clock` (`native/common/port_debug.cpp`) | debug commands | debug only |

Not hooks: `mp_encode` / `Value` (InfoBase tests), `soa::adld` (shared codec, common/), `server::testing` (test runner).

## Decision (the user, 2026-10-01): the FakeApiCaller overrides produce what the wire carries
**Direction:** the port's FakeApiCaller stand-ins / native overrides (or a native in-process shim used in their place) **generate the same information the 3.7.0 `NetworkApiCaller` sends over the wire**. The server then gets everything from the request itself, the way `soa-server` does, and **the custom guest-reading hooks are dropped**.

Still scheduled after the 3.7.0 rebase (`docs/history/PLAN-rebase-370.md`): it's done on the rebased port, and the details are confirmed with the user then.

**Why it's possible:** the battle log and the other wire-only data were never arguments of the API interface. Every `IApiCaller` implementation has the same signature, e.g. `MissionEnd(unsigned int, unsigned int)`. `NetworkApiCaller` collects the extra data itself, inside the lambda it passes to `BeginBridge`. That lambda calls `GameProtocolProxy::Send<Api>` with the full argument list, e.g. `SendMissionEnd(header, mission, const s8* log, u32 log_len, u32)`; `docs/online-server.md` "A call, end to end". `FakeApiCaller` has no network layer, so that data is never produced. The override can produce it the same way.

### Confirmed by Ghidra: how the wire battle log is built (3.7.0)
`NetworkApiCaller::MissionEnd` @015ba170 passes a lambda to `BeginBridge`. Its `operator()` is at **@015d68bc**, found from the closure's `std::function` vtable `@02ac8e68` slot +0x30. Decompiled with `tools/decomp_at.sh --v370` into `work/decomp/battlelog-lambda.resolved.c`:
```c
Aska::ASON ason;
AsonSerializer::Serialize<CBattleLogInfo>(ason, CParameterManager + 0x52d8, 0, 0x4000, 1);
size = ason.CalcSerializedSize();
if (size <= 0x1000 && ason.Serialize(buf /*4096*/, size) >= 0) {
    hdr = NetworkApiCaller::PresendApiCall(0x8312a64c /*MissionEnd*/, false, true);
    GameProtocolProxy::SendMissionEnd(hdr, mission /*closure+0x10*/, buf, size, x /*closure+0x14*/);
}
```
- **The source:** the battle log is the client's `CBattleLogInfo` at `CParameterManager+0x52d8`, the same object the port's `BattleLog` hook reads today.
- **How to reproduce it:** the FakeApiCaller override can produce byte-identical bytes by calling those same guest functions: `AsonSerializer::Serialize<CBattleLogInfo>` then `ASON::Serialize`, or a verified native equivalent.
- **A size limit:** a log over 0x1000 bytes makes the real client skip sending MissionEnd. The override should copy that behaviour, or at least log it.
- **The other wire-only blobs** need the same check: MissionFailed, Sphere211MissionEnd and Sphere211MissionFailed, plus any others `docs/api-wire.txt` shows (deco data and so on). Their lambdas are found the same way, from the vtable slot +0x30 of the closure each `NetworkApiCaller::<Api>` passes to `BeginBridge`.

### Per hook
| Hook | What the FakeApiCaller override must generate | Then |
|---|---|---|
| `BattleLog` (guest reads of `CParameterManager+0x52d8…`) | For MissionEnd, MissionFailed, Sphere211MissionEnd and Sphere211MissionFailed: the ASON battle-log blob, built the way `NetworkApiCaller`'s lambda builds it. Preferably by calling the client's own serialization code that the lambda uses, so the bytes are identical. It's attached as `Request::battle_log` through `soa-server`'s wire parser (`server/net`). | drop the hook and the port's guest-reading `BattleLog` implementation |
| other wire-only arguments (DeviceType on NoLoginStart / CreatePlayer, any argument `docs/api-wire.txt` has that the FakeApiCaller signature lacks) | the same values `NetworkApiCaller` sends (`tools/api_wire.py` lists every request's wire layout; compare it with the FakeApiCaller signatures to find all of them) | in-process `Request`s equal the wire-decoded ones |
| `StatusProvider` (guest `CalcStatus`) | nothing: the server computes status from master data (NPCs since T1; player characters by its own rules) | drop, after checking every status the 3.7.0 client shows against `soa-emu` |
| `InGameHooks::client_tutorial_cleared` | nothing: the server's own tutorial state | drop |
| `InGameHooks::add_login_bonus_popup` | nothing: the 3.7.0 client builds the popup from the response | drop (verify on the rebased port) |
| `InGameHooks::client_party_set` | whatever party data the wire request carries for the campaign (check MissionStart and the party APIs in `docs/api-wire.txt`) | drop |
| `server::campaign::end_mission_talk` (from `restore_campaign.cpp`) | nothing: 3.7.0 sends `EndMissionTalk` itself | drop with `restore370` (P3) |
| `server::enabled` in `restore_home` / `restore_favor*` | nothing | drop with `restore370` (P3) |

What stays:
- **The route itself:** the override, `submit`, `handle` and `error_code`.
- **`AssetIndex`:** both modes gate content on assets.
- **`apply_client_master`,** a separate question, not a FakeApiCaller one. The in-process client reads its own master copy. Keep the `sqlite3_exec` hook, or give the in-process client the same edited, re-encrypted master `soa-server` serves (through the download dir) and drop that hook too. **Ask the user.**

### Test that proves it
A differential check, per API. For the same action, the `server::Request` the port's override builds must equal the one `soa-server` decodes from the 3.7.0 client's packet: method, ints, strings, vectors and battle-log bytes. The packet comes from the `tests/diff/` flows or the unicorn request harness in `server/tests/ninja/tools/`. Any difference fails.

### Rejected
Hooking the GameRPC transport (`TARPCPeer` / `GameProtocoledData`) instead of FakeApiCaller was declined. The in-process route stays a FakeApiCaller override or a native shim.
