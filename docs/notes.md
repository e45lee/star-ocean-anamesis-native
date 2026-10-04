# STAR OCEAN: anamnesis (JP) — save format and reverse-engineering notes

Binary: `work/libSOA-3.7.0.so`, the client the port runs (symbols not stripped). Most addresses below were read in the offline build's lib, before the port moved to 3.7.0; 3.7.0's are shifted (map them by symbol, unnamed functions with `tools/genlib.py`). Sections that give 3.7.0 addresses say so.
Ghidra addresses = ELF vaddr + 0x100000 (`tools/elfinfo.py`).

## Storage: Aska::LocalKVS → Android SharedPreferences

- Native `Aska::LocalKVS::SetBinaryAndroid` → JNI `AskaActivity.SetSharedPreferences(name, key, byte[])`
  → `getSharedPreferences(name, 0)` → `putString(key, Base64.encodeToString(bytes, DEFAULT))`.
  - `Base64.DEFAULT`: line break every 76 chars and a trailing `\n`.
- The prefs file name is the KVS name, so the file is `shared_prefs/<name>.xml`.
- There are two stores:

| KVS name | File | Created by | Contents |
|---|---|---|---|
| `Aska` | `Aska.xml` | `Aska::Global::InstantiateLocalKVS` | `version`, `crc`, device UUID (`BAS::GetUUID`) |
| `Game` | `Game.xml` | `CGameLocalKVS::CGameLocalKVS` | `version`, `crc`, all `BAS:*` settings, `player_*` / `person_*` summary |

## Cipher (`LocalKVS::SetCipher`, `CipherEncryptKey`, `CipherEncryptVal`, `CipherDecryptVal`)

- Standard RFC 7539 ChaCha20: 32-byte key, 12-byte nonce, counter starts at 0. The code is `Aska::Cryption::TChaCha20<false>`; I checked that `CreateKeyStream`, emulated in unicorn, matches pycryptodome.
- **The counter is reset to 0 for every key and every value**, so each one is `plaintext XOR keystream[0:len]`.
- Key name in XML = `Base64(ChaCha20(key_name_bytes))`, with no NUL, using the native `Aska::Encode::Base64Encode`. **Quirk (confirmed on samples):** when `len % 3 == 0` it appends `====` instead of no padding.
- Value in XML = `Base64.DEFAULT(ChaCha20(value_bytes))` followed by 4 spaces, with newlines written as `&#10;`.
- `soa_save/kvs.py` round-trips the saves in `data/saves/` (`Aska.xml`, `Game.xml`) byte for byte (`tests/test_kvs.py`).
- Key selection (`CGameLocalKVS::_SetCipherKey` / `_VersionCheck`):
  - version `"1.1"` (current): fixed key `xp1666a2P7QGhOCRxCjG8aWj5PmxZOrY`, nonce `g7TtZVIKyqc0`.
  - version `"1.0"` (legacy, or any other value): `SetCipher(true, NULL, NULL)` →
    key = `"pO%q8Yu2.gb\/(bG7L+ 6{S,O1z}_=w` (32 bytes at vaddr 0x2872229) XOR uid8,
    nonce = `vH9=-2.OP(VN` (vaddr 0x287224a) XOR uid8, where `uid8[i % 8]` comes from
    `Aska::Machine::GetUniqueID`, falling back to `GetStrayMacAddress`. Device-bound.
  - `"version"` holds the string plus NUL. `"crc"` holds `Aska::Hash::CRC(version)` as a u32. If the check
    fails, the store is re-initialised with version `"1.1"`.

## What the save contains (`CUserDataUtility::Save_PlayerInfo` / `Save_PartyInfo`, Game store)

| key | type |
|---|---|
| `player_name` | C string, passed through `CParameterPropertyBase<53>::CryptString` (in the samples the stored value is plain UTF-8, e.g. `Fayt`) |
| `player_level` | u32 (CParameterManager+0x738) |
| `player_fol` | u32 (+0x8e8) |
| `player_stamina_max` | u32 (+0x798) |
| `player_exp` | u32 (+0x7f8) |
| `player_home_pc_roleid` | u32 |
| `player_is_3d_home` | u8 |
| `person_size` | u32 |
| `person_master_role_id_%d` | u32 per party member |

Plus about 100 `BAS:*` UI and settings keys.

## Open question

No code path in this APK persists inventory, characters, gear or story state locally:

- `Aska::File::Write` and `FileStream::Write` callers are only logs, shader caches and downloads.
- `sqlite3_open` is used only for the master DB.

Full player state arrives over `Aska::Yayoi::GameRPC` (TCP). Either the offline build keeps its state somewhere this APK doesn't show, or it's a different build.

## Sample findings (samples/, 2021)
- `Aska.xml`: `uuid`, `version`=`1.1`, `crc`=zlib.crc32(b"1.1").
- `Game.xml`: 248 entries = 161 `BAS:*` settings, 74 `person_master_role_id_N`, 7 `player_*`, `HomeMascotID` (`cp0003`), `BASN:*` download flags.
- Role IDs are 32-bit hashes. Mapping them to names needs the master DB (not in the APK; it's downloaded).

## Master DB (shipped in the base APK)
- `assets/builtin_data/sqlite/basmaster.sqlite3` is an **ADLD** container. It's decrypted by the lambda that `CGame::OnInitialize` registers through `CFileLoader::SetDecryptFunction` (operator() at vaddr 0x1149238):
  - header: `ADLD`, u32 flags, 8 unused bytes; payload at +0x10.
  - flags&1: XOR with ASCII `"%x" % CHash32(name)`.
  - flags&2: AES-128-CBC (OpenSSL via `Encrypt::CEncryptAES128`). Key = `"%032u" % CHash32(name)`, IV = `"09375711857134629684891855841614"`; both pack one decimal digit per nibble. An optional `DCNE` v1 inner header holds the real size.
  - `name` is the path relative to `builtin_data`: `sqlite/basmaster.sqlite3`.
- `Framework::CHash32(const char*)`: the standard CRC-32 table, seeded with `strlen`, no final XOR.
- Decrypted DB: 176 `master_*` tables, integrity ok, text in `ja` only.
- **Every `*_id` in saves = CHash32(`id_label`)**, e.g. role `role_cp0303_b04a_6131` → 813289606. All 74 roster ids in the sample resolve.
- Code: `soa_save/adld.py`, `soa_save/master.py`; CLI `python -m soa_save roster samples/Game.xml`.

## Event scripts (install-time asset pack)
- In the offline build's install-time asset pack, which `soa_save.script` reads: `assets/assetpack/Script/<event>.msgp` (458) and `Scenario/TS_<chapter>.msgp` (28). `EventScenario::CEventScenario::SetEventId` builds the names from `"Script/%s.msgp"` and `"Scenario/%s.msgp"`.
- All are ADLD flags=1 (XOR). The CHash32 name is the path relative to `assetpack/`, e.g. `Script/1000_010.msgp`.
- The plaintext is MessagePack, loaded with `Aska::ASON::DeserializeBinary` in `CEventScenario::InitializeCommandList`:
  - Script: `{"Script": {<event>: [{id, command_type, command_param0..8}]}}`
  - Scenario: `{"master_text": [{message_id, lang, text_value, category_id_label, ...}]}`. Only `ja`. The master DB's `master_text` holds only system text.
- `command_type` indexes `CEventScenario::CalcCommand_Table` (vaddr 0x2bc7690): 78 pointer-to-member entries, `CalcCommand_<Name>`. The names are in `soa_save/script.py` `COMMANDS`; 60 types are used.
- Dialogue commands (`MessageChange`, `MessageAppend`, `BacklogChange`, `BacklogAppend`) take param0 = message_id and param1 = speaker model (`cp0003_ta01a`). `SelectMenu` / `SelectMenu_ErrorSE` take (message_id, jump label) pairs in param0..7. `Label`, `Jump`, `Flag` and `IfJump` do the control flow.
- 16,742 of 17,373 dialogue references resolve against the shipped Scenario files. The rest (events 20xx, 60xx) point at text this build doesn't ship.
- Tool: `python -m soa_save.script`.

## English names
- Source: Star Ocean Fandom wiki, "Star Ocean: Anamnesis playable characters", fetched via the MediaWiki API (`api.php?action=parse&prop=wikitext`, because the HTML page returns 402). Saved in `docs/wiki/soa_playable_characters.json`.
- `soa_save/names_en.json` maps character code → (JP base, EN name, full name), and JP title prefix → the wiki's variant wording. A JP name is title + base (e.g. 渚の+マリア → Summer Maria).
- 277/280 master-DB names produce a variant name that appears verbatim on the wiki. The exceptions are `ティニーク（狼版）`, `渚のシマダ` (not on the wiki list) and `フィリア` (cm505, not playable).
- The JP↔EN pairing for a few characters was made by elimination against the wiki list rather than a direct source: アーリィ=Hrist, フレイ=Freya / フレイア=Frei, ルシファー=Luther / ルシフェル=Lucifer, イレーネ=Eleyna, スティーブ=Stephen, クレール=Chloe, ヴァルキリー=Valkyrie (Alicia).

## Runtime structure (from the desktop port, `port/`)
- The Java side is thin: `jb.Aska.AskaActivity` (a `NativeActivity`) and `SOAActivity`. The native side calls into it over JNI for:
  - SharedPreferences
  - display size
  - movies (`PlayMovie` / `MovieFinished`)
  - text entry (`StartKeyboardActivity` / `IsEndKeyboardActivity` / `GetEditText`)
  - Play Core asset packs
  - a few device queries
- Startup is the standard `android_native_app_glue`:
  - `JNI_OnLoad` registers 2 natives.
  - `ANativeActivity_onCreate` spawns `android_main`, which starts `Aska::g_thMain` and runs `DroidLoop`.
- Library versions linked in: zlib 1.2.5, SQLite 3.13.0, libjpeg, libogg/libvorbis (with an `ogg_memory_hook` allocator patch).

### Offline mode
- **API calls**: the game uses `NetworkApiCaller` (as `CApiCaller`). Offline, its only request is `NoLoginStart` (the port has no server; see `jni/java_android.cpp`). The built-in fake server `FakeApiCaller` is never constructed; see "Offline server (FakeApiCaller)".
- **Master DB load**: `CStaticTransaction::Progress` decrypts `sqlite/basmaster.sqlite3` to `files/download/temp.sqlite3`, then loads it into memory:
  1. opens `:memory:`
  2. `ATTACH DATABASE '<android path>' AS newdb`
  3. `create table X as select * from newdb.X` for each table
  4. `DETACH`
- **Asset packs** (the offline build only; 3.7.0 has no Play Asset Delivery and downloads these files): `CGameAssetPackManager` knows three packs.
  - install-time: images, characters, motions, scenario, scripts, talk scenes, movies.
  - `assetfastfollow`: `Sound/*.aac` BGM, 635 files.
  - `assetondemand1`: `Sound/TS_*` talk-scene SE, 573 files.
  - The file lists are MessagePack maps name → `{size}` in `assetpack/filelist_*.bin`.
  - Pack sounds are read with `fopen("<assetsPath>/assetpack/Sound/...")`, so a pack needs `STORAGE_FILES` with a real `assetsPath`.

### Offline server (FakeApiCaller)
**Summary: `FakeApiCaller` is dead code in the shipped build, and its canned responses don't exist.**
- **Nothing constructs it.** `FakeApiCaller::FakeApiCaller()` (0x149155c) has no callers (no `BL`, no address reference; `tools/callers.py`, `tools/xref_got.py`). No profiled session executed any of its functions.
- **What the game uses instead.** `CGame::OnInitialize` always does `new (nothrow) NetworkApiCaller` (0xde0 bytes). It then overwrites the vtable pointer with `CApiCaller`'s: `CApiCaller` is `NetworkApiCaller` plus its own destructors. It stores the object in `TSingleton<CApiCaller>::m_pInstance` and calls `Initialize` (vtable +0x10).
  - In offline play the only API request is `NetworkApiCaller::NoLoginStart`. The game then polls `IsRequesting` / `IsSuccess` / `ErrorCode`, and `CErrorHandlerWrap` handles the failure.
  - `CErrorHandlerWrap::SetFakeAppCaller` / `IsFakeAppCaller` / `IsFake` exist for the fake caller. `IsFake` runs offline (on the real caller).
- **The canned files are missing.** The 60 `FakeApi/*.msgp` names are plain strings in `libSOA.so` (0x271e280..0x271e823), but no file of that name, or with its `CHash32` name, is shipped:
  - not in the base APK's `builtin_data`;
  - not in the install-time pack;
  - not in the 3.7.0 online download set. Its manifest `work/download-3.7.0/version.bin` (a msgpack map `assets: {name: {md5, …}}`) lists 8.5k assets and no `FakeApi/`.
  - They were a developer-only stub server. Serving responses needs our own msgp files; `reach` is adding a port option for that.

**Object layout** (size 0x60 + `sizeof(CApiNotify)`):

| Offset | Contents |
|---|---|
| +0x00 | `IApiCaller` vtable (`_ZTV13FakeApiCaller`+0x10) |
| +0x08 | `Framework::CFiberUnit` (stack 0x600; vtable `_ZTV13FakeApiCaller`+0x700). Its `Progress` thunk runs `FakeApiCaller::Progress` once per frame. |
| +0x40 | `std::map<FunctionID, Info>`: begin, root, size |
| +0x60 | `CApiNotify` (constructed with `this` as its `IApiCaller*`) |

- **Constructor.** Sets up the fields above, registers the fiber unit with `CMainTask::rRootFiberKernel()` (vtable +0x48), then calls `CErrorHandlerWrap::SetFakeAppCaller()`.
- **Map node:** 0x80 bytes, allocated with `CAssignedMemoryManagerForSTLAllocator` (`STL_Map.h` line 0x21).
  - +0x20: `FunctionID` key (u32).
  - +0x30: `Info` (aligned to 16 because it holds a `std::function`):
    - Info+0: fid (u32);
    - Info+4: state (u32): 0 queued, 1 loading, 2 done;
    - Info+8: file name (`std::string`, CSTL allocator);
    - Info+0x20: `std::function<Status(s8*, u32&)>` (32-byte buffer, `__f_` at Info+0x40 = node+0x70).

**Request flow** (every API that has a canned file):
1. **The method** (e.g. `MissionStart(...)`) ignores all its arguments.
   - It builds a local `std::function` holding a lambda `{vtable, FakeApiCaller* this}`, calls `AddLocalFile(fid, "FakeApi/x.msgp", fn)`, destroys the local function and returns `Status` 1 through x8.
   - The lambda vtables sit at 0x29c8cd0 + 0x80·k; operator() is slot +0x30.
2. **`AddLocalFile`.**
   - If `fid` is already in the map, it only resets that entry's state to 0. **The stored file name and lambda are kept.**
   - Otherwise it copies the name into a CSTL string, copies the function, builds an `Info` and move-inserts it (`__emplace_unique_key_args`).
3. **`Progress`** walks the map in key order:
   - **State 0:** `CGameResourceManager::AddDirectFile(1, name, 0, false, 0)`, then state 1.
   - **State 1,** once `CGameResourceManager::IsLoading()` is false:
     - `Lock()`;
     - `el = crResourceElementDirectFile(name)`. There's no null check, so a missing file would crash here;
     - `size = CFileLoader::Size(el)` (u32), `data = el->vtbl[0x50](el)`;
     - calls the stored function (`__f_->vtbl[0x30](&status, &data, &size)`); the `Status` is discarded;
     - `Unlock()`, `RemoveDirectFile(name)`, then state 2.
   - While the resource manager is loading anything, entries in state 1 wait.
4. **The lambda.** All but two are 4-instruction tail calls: `return CApiNotify::OnXxxRes(this+0x60, data, size)` (the `Status` goes through x8).
   - **`Login`/`SimpleLogin`** (identical, 0x14954cc / 0x149584c) first fake a login:
     - `gethostname(buf, 0x18)` (the result is unused);
     - `name = snprintf("Dummy_%x", Aska::Random())`;
     - `id = Aska::Random()`;
     - builds ASON (`Init(0x4000, true)`) `{"Player": {"Id": id (uint), "Name": name}}`;
     - `CParameterManager::Deserialize(&root.map)`;
     - then `OnGetPlayerRes(this+0x60, data, size)`.
   - No lambda randomises drops or gacha results, and none reads the request parameters. Everything a response carries comes from the canned file as it is.

**Queries:**
- `IsRequesting(fid)` is true when the fid isn't in the map (a quirk: an unknown request counts as "in flight"), else state ≠ 2.
- `IsSuccess` → 1, `IsFailure` → 0, `ErrorCode` → 0, `LoggedIn` → 1.
- `GetApiNotify` → **nullptr** (not `this+0x60`), `GetApiWatcher` → nullptr.
- `Initialize`, `BeginBridge`, `EndBridge` → `Status` 1. `Release` clears the map. `Reset`, `ResetBRIDGE`, `SetRetry`, `SetSharedSecurityKey` and `DeleteWatcher` do nothing.

**APIs without a canned file** just return a `Status` through x8 and do nothing else:
- **1:** `AchievementListReceive`, `GetBirthYearMonth`, `UpdateBirthYearMonth`, `InheritAccessory`, `CoinDeposit{IOS,Android,Amazon}Update`, `ItemShopList`, `DirectItemShopList`, `Home3DAnd2DSwitching`, `ChangeMascot`.
- **0:** everything else, including:
  - storage, gear, config, world-boss / world-map / scenario-library, Sphere211 and deep-space lists;
  - `MissionContinue` and `MissionLose`;
  - **every `Debug_*` method** (`Debug_OpenMission`, `Debug_Gear`, `Debug_GetFol`, `Debug_DeepMissionDrop`, …). **They're empty; the fake server has no debug features.**

**Quirks:**
- **FunctionIDs shared by several methods** (marked * in the table below). Because `AddLocalFile` keeps the first `Info` for a fid, the second method of each pair gets the **first one's file and handler**:
  - `EquipAccessory` after `EquipWeapon` loads `equip_weapon.msgp`;
  - `Blacklist*` after `Follow*` goes to `OnFollow*Res`, and vice versa;
  - `AchievementReceiveList` shares `AchievementActiveList`'s fid;
  - `SendErrorLog` shares `UpdateKiyakuVersion`'s fid;
  - `LimitBreakCharacter` and `_Legacy` share a fid;
  - the five sale/clear-new methods share one fid (`OnSellItemRes`).
- **Wrong handlers:** `ClearNewItem`, `ClearNewStackItem` and `ClearNewCharacter` go to `OnSellItemRes` with `sale.msgp`. `MissionTalk` and `MissionFailed` use `player_get.msgp`.

**Bringing it up** (for a port option; untested):
1. Allocate the object with `operator new`: 0x60 bytes plus `CApiNotify`.
2. Run `FakeApiCallerC2`. It registers its own fiber and flags `CErrorHandlerWrap` as fake.
3. Put it in `TSingleton<CApiCaller>::m_pInstance` in place of the `NetworkApiCaller`. Callers only use the `IApiCaller` vtable.
4. Provide every `FakeApi/<name>.msgp` the flow requests as a direct file (`CGameResourceManager::AddDirectFile` type 1). A missing file crashes in `Progress`, because it doesn't check `crResourceElementDirectFile` for null.
5. Write each response in the server's msgpack shape that the `CApiNotify::On*Res` handler parses.

**Port option `--fake-server DIR`: the fake server, live.** This is our invention, not guest behaviour, and it's off by default.
- **Swap-in.** After `CGame::OnInitialize`, the port constructs a `FakeApiCaller` with its own constructor and stores it in `TSingleton<CApiCaller>::m_pInstance`. The `NetworkApiCaller` stays allocated but unused.
- **Serving.** Every request is answered from `DIR/<name>.msgp`: the canned name without `FakeApi/`, e.g. `mission_start.msgp`. The file's bytes go to the API's `CApiNotify::On*Res` through the guest lambda, one frame after the request.
- **Missing file.** It's answered with an empty msgpack map (`0x80`) and logged as `W/fakeapi: fid …: … missing`. The guest would crash instead.
- **Verified:** with an empty `DIR`, the offline boot's only request, `NoLoginStart`, is answered with `{}` and the smoke session passes unchanged.
- **`CApiNotify::EndRequest` is a no-op here.** It returns early because nothing sets the in-flight fid at `CApiNotify+0x510`. That fid is set on the network path, so `GetApiWatcher()` returning nullptr is never dereferenced.
- **Callers see requests finish through the virtuals:** `IsRequesting` goes false (state 2) and `IsSuccess` is always 1.
- **Response bodies** must use the key names `CParameterManager::Deserialize` expects; see "API response handling (CApiNotify)". Which API reads which file is in the table below. Several APIs share a FunctionID, so the **first** method used decides the file for all of them.

**Response schema.** `--fake-server-schema FILE`, set together with `--fake-server`, writes what `CParameterManager::Deserialize` accepts. The committed dump, `port/fakeapi/schema.txt`, was made on the offline build, before the rebase.
- **Registered parameter sets.** The list at `+0x68` holds `Sound`, `Player`, `master_*`, … Each one takes its top-level key.
- **`"data"`** is the `CInfoManager` at `+0x600`. Most responses fill it. Its properties and child infos are keyed by the `CHash32` of the key names, which the dump recovers by hashing every `.rodata` string.
- **`"status"`** (uint) goes to `+0xb728`.
- A response body is therefore `{"data": {<key>: …}, "status": n}`. Child *list* infos (e.g. `GachaItems`, `Item`) are shown without their element fields.
- **Element fields.** `port/fakeapi/fields.txt` (from `tools/fakeapi_fields.py`) lists each info class's field names: the string literals its `Initialize()` hashes. For example, `CGachaResultInfo`: `master_item_id`, `player_item_id`, `master_role_id`, `player_character_id`, `duplication`, `is_mutation`. Fields registered by a base class appear under that class.
- **Building responses.** `tools/fakeapi_msgp.py` turns JSON into response files: `SRC_DIR/<name>.json` becomes `DIR/<name>.msgp`.
- **Verified end to end:** `update_home.msgp` = `{"data": {"GameID": 0x5eedbeef}, "status": 0}` answers the boot's `NoLoginStart`, and the `data` info's `GameID` property then holds `0x5eedbeef` (property object +0x28).

**Generated responses** (our invention): `tools/fakeapi_responses.py DIR --db data/basmaster-3.7.0.sqlite3 [--mission mf01_001] [--draws 10] [--seed 1] [--save Game.xml] [--party LABELS] [--level N]` writes `DIR/json/*.json` and `DIR/*.msgp`. A default set is committed in `port/fakeapi/responses/` (generated with `--save data/saves/client/Game.xml`), so use `--fake-server port/fakeapi/responses`. `mission_start` carries the battle party (`BattleParameter.PlayerCharacter`) and `gacha_in_data` the gacha hash list and a wallet; see "Playing a battle and a gacha through" below.
- **`mission_start`:** `data.MissionParameter` for the mission (stamina cost, and every `master_mission_stage` row as `mission_stage`; no drops), plus `data.PlayMission`.
- **`mission_end`:** `data.MissionEndResult` and `data.DropList` (the mission's fol; no items), `data.AddItem` (one item, uid 0x7d000001), `data.StockItem` (one stack item), `data.MissionResultCharacter` (for the first gacha character, uid 0x7f000000) and `data.MissionResultCharacterFavor` (character id 1), so `OnMissionEnd`'s per-character, favor, `AddItem` and `UpdateStackItem` paths all run.
- **`gacha_pc` / `gacha_ticket` / `gacha_once_item`:** `data.GachaItems`, N seeded random `role_cp*` draws. Each draw is also a new character in `data.AddCharacter` with `player_character_id` / `id` = 0x7f000000+ (0x100 apart per file), which `CApiNotify::AddCharacter` appends to the roster. `AddCharacter` has no duplicate check, so serving the same file twice adds the same uids twice.
- **`present_get_all`** (`PresentList`): `data.PresentBox`, 5 presents (ids 1..5; fol / free coin / item contents).
- **`present_get_item`** (`GetPresent`): `data.PresentGetResult` with `get` = the received ids [1, 2], `add` = the box afterwards (presents 3..5), and `result.fol` / `free_coin`. `ApplyGetPresent` erases the received ids from the box, clears it and refills it from `add`, so `add` must hold the whole remaining box.
- **`player_get` / `update_home`:** `{"data": {}, "status": 0}`. With `--save <shared_prefs Game.xml>`, `player_get` also lists the save's roster (`person_master_role_id_N`) as owned characters (`data.Character`, uid 0x7e000000+N). Nothing requests `player_get` at boot: offline only `NoLoginStart` → `update_home` is requested.
- **Response shapes learned from the live check** (see "Live check" in "API response handling"):
  - list-shaped infos (`Character`, `GachaItems`, `PresentBox`, `AddItem`, `StockItem`) take msgpack arrays of element maps;
  - **map-shaped infos** (`AddCharacter`, `MissionResultCharacter`, `MissionResultCharacterFavor`, and the other `...Map` / `CAdd*List` infos keyed by id) take a msgpack **map keyed by the id as a string**, e.g. `{"2130706432": {"id": 2130706432, ...}}`. Given an array they stay empty;
  - `data.Character` fills the owned roster (`+0x1178`) directly and **replaces** it, so the earlier generator's gacha bodies (which used it) replaced the roster with the draws instead of adding them.
  - the element key `id` (a base-class field, missing from `fields.txt`) works: e.g. `+0x4b50` is keyed by it.
- **Verified at the data level** with the live check (`port/scripts/apinotify_live.sh`): presents, the five gacha variants, mission start / end / restart / end, and GetPlayer apply without asserts, and the player state is identical with and without the native handlers. **Not yet verified on screen:** whether the battle and gacha screens accept these bodies.

**The in-process local server (`--server inproc`, the default): the local server emulator** (`server/`, 2026-09-29). Our code, not guest behaviour; the rules and their sources are in `docs/server-rules.md`.
- **Route.** It rides the `--fake-server` route:
  - the native request hooks hand each method's arguments to `server_port::capture`, port/src/native/api/server_adapters.cpp (read from x1..x7 by the mangled signature);
  - `ServeProgress` takes the body from `server::handle` before looking for `DIR/<name>.msgp`.
- **State.** A persistent SQLite state in `DATA/server.sqlite3`, seeded from `work/Game-3.7.0.xml` (74 roles, level 87, FOL, name).
- **Save sync.** The offline client shows the player summary cached in its own `Game.xml` (name, level, EXP, FOL, stamina max, home character, roster) over what the boot response sent. So the server writes its state into that file before the game starts.
- **Verified on screen** (`port/scripts/restore_session.sh`):
  - home shows the server's player (Fayt, rank 87, stamina 134/134, 10,000 紋章石, FOL 1,675,605);
  - `mf01_001` plays with party 1's own characters (★6, level 60);
  - the result shows 24 調査ポイント, 360 FOL and the party's 150 EXP;
  - the gacha lists the 29 banners open at the real date, and a sale 10-draw of `gacha_role_0001` debits 2,500 紋章石, with 限界突破 on duplicates and NEW on new characters.
- **Arguments seen:**
  - `MissionStart(type 0 or 0xffffffff, mission id, 0, 0, 0, 0, 0)` on the `mission:` route;
  - `MissionEnd(mission id, 0)`;
  - `SaleGacha(gacha id, hash)` (the hash is the one `GetGachaInData` sent).
- **The data check.** With the server's large roster, the boot's `CPhase_DataDownload` (phase 19) runs longer. Switching phase before it ends (phase 23, then home 4) leaves its dialog on screen.
- **Clock.** The offline build's clock is frozen at `master_global.service_stop_day`. The in-process server drops that row from the client's in-memory master copy (lib_sqlite hook at the prepared `DETACH`), and every response carries `data.Time`.
  - After a battle, home then shows スタミナ 132/134 with the regeneration timer running. Before, it showed 134/134: the frozen clock made the client compute a full bar.
- **Result screen.** `ResultUtility::PushToItemList<CMissionResultDropInfo>` lists `DropList.item` / `.character` / `.stock_item` by each element's first property (`id`) as the content id, plus `content_type` / `drop_type`. So the server sends the master id there, and the uids in `AddItem`.
  - The result shows the dropped weapons, the real mission time from the client's `CBattleLogInfo` (`CParameterManager+0x52d8`), and 限界突破 on duplicate draws (`LimitBreakCharacter`).

**Native:** `port/src/native/api/fakeapi.cpp`. Every method and lambda is native and differentially tested (`fakeapi/*`); it's dormant because nothing constructs the object.

| Method | FunctionID | Canned file (`FakeApi/`) | Lambda → `CApiNotify::` handler |
|---|---|---|---|
| `Login()` | `a01c67ef` * | `player_get.msgp` | (see Login) |
| `SimpleLogin()` | `a01c67ef` * | `player_get.msgp` | (see Login) |
| `CreatePlayer(s8 const*, s8 const*)` | `e3e463ad` | `player_get.msgp` | `OnCreatePlayerRes` |
| `GetPlayer()` | `9a056905` | `player_get.msgp` | `OnGetPlayerRes` |
| `GetPlayMission()` | `7c1b7a1b` | `player_get.msgp` | `OnGetPlayMissionRes` |
| `SearchPlayer(s8 const*)` | `5e598152` | `update_name.msgp` | `OnSearchPlayerRes` |
| `UpdatePlayerName(s8 const*)` | `e8e5c4da` | `update_name.msgp` | `OnUpdateNameRes` |
| `UpdateKiyakuVersion(s8 const*)` | `e5af488c` * | `update_kiyaku_version.msgp` | `OnUpdateKiyakuVersionRes` |
| `MissionStart(u32, u32, u32, u64, u32, u64, u32)` | `b7c62bc2` | `mission_start.msgp` | `OnMissionStartRes` |
| `MissionRestart()` | `1f96f310` | `mission_start.msgp` | `OnMissionRestartRes` |
| `MultiMissionRestart()` | `8c788f39` | `mission_start.msgp` | `OnMultiMissionRestartRes` |
| `TrainingMissionStart(u32, u32, u64)` | `0a16fd90` | `mission_start.msgp` | `OnTrainingMissionStartRes` |
| `MissionEnd(u32, u32)` | `8312a64c` | `mission_end.msgp` | `OnMissionEndRes` |
| `MissionTalk(u32, u32, u32, uns8)` | `816dc8b4` | `player_get.msgp` | `OnMissionTalkRes` |
| `MissionFailed(u32, u32)` | `479604f6` | `player_get.msgp` | `OnMissionFailedRes` |
| `BoostCharacter(u64, u32, u32)` | `e5a04db6` | `boost_character.msgp` | `OnBoostCharacterRes` |
| `EvolutionCharacter(u64)` | `990921b6` | `evolution.msgp` | `OnEvolutionCharacterRes` |
| `LimitBreakCharacter(u64, u32)` | `78972d03` * | `limit_break.msgp` | `OnLimitBreakCharacterRes` |
| `LimitBreakCharacter_Legacy(u64, u32)` | `78972d03` * | `limit_break.msgp` | `OnLimitBreakCharacterRes_Legacy` |
| `AddStatusCharacter(u64, u32, u32)` | `74e09417` | `boost_character.msgp` | `OnAddStatusCharacterRes` |
| `ItemCompose(u64, u32, ...)` | `02a5cd1d` * | `compose.msgp` | `OnItemComposeRes` |
| `ItemComposeArray(u64, vector<u64> const&)` | `02a5cd1d` * | `compose.msgp` | `OnItemComposeRes` |
| `ItemGradeUp(u64, u32, ...)` | `8952aa02` * | `grade_up.msgp` | `OnItemGradeUpRes` |
| `ItemGradeUpArray(u64, vector<u64> const&)` | `8952aa02` * | `grade_up.msgp` | `OnItemGradeUpRes` |
| `UpdateParty(u32, u64, u64, u64)` | `ef02dd83` | `party_update.msgp` | `OnUpdatePartyRes` |
| `UpdateSupport(u64)` | `3e77af96` | `update_support.msgp` | `OnUpdateSupportRes` |
| `EquipWeapon(u64, u64)` | `1f3c9eca` * | `equip_weapon.msgp` | `OnEquipWeaponRes` |
| `EquipAccessory(u64, u64)` | `1f3c9eca` * | `equip_accessory.msgp` | `OnEquipWeaponRes` |
| `EquipSkill(u64, u32, u32, u32)` | `4656d729` | `equip_skill.msgp` | `OnEquipSkillRes` |
| `EquipAuto(u64)` | `7827ff6a` | `equip_auto.msgp` | `OnEquipAutoRes` |
| `GetPresent(u64, ...)` | `4072d7e1` * | `present_get_item.msgp` | `OnGetPresentRes` |
| `GetPresentArray(vector<u64> const&)` | `4072d7e1` * | `present_get_item.msgp` | `OnGetPresentRes` |
| `PresentList()` | `fa782a45` | `present_get_all.msgp` | `OnPresentListRes` |
| `LockItem(u32, ...)` | `88f29383` * | `item_lock.msgp` | `OnLockItemRes` |
| `LockItemArray(vector<u64> const&)` | `88f29383` * | `item_lock.msgp` | `OnLockItemRes` |
| `UnlockItem(u32, ...)` | `2f9569e5` * | `item_unlock.msgp` | `OnUnlockItemRes` |
| `UnlockItemArray(vector<u64> const&)` | `2f9569e5` * | `item_unlock.msgp` | `OnUnlockItemRes` |
| `ClearNewItem(vector<u64> const&)` | `00ee45f7` * | `sale.msgp` | `OnSellItemRes` |
| `ClearNewStackItem(vector<u32> const&)` | `00ee45f7` * | `sale.msgp` | `OnSellItemRes` |
| `ClearNewCharacter(vector<u64> const&)` | `00ee45f7` * | `sale.msgp` | `OnSellItemRes` |
| `SellItem(u32, ...)` | `00ee45f7` * | `sale.msgp` | `OnSellItemRes` |
| `SellItemArray(vector<u64> const&)` | `00ee45f7` * | `sale.msgp` | `OnSellItemRes` |
| `SellStackItem(u32, u32)` | `445ab956` | `sale_stock.msgp` | `OnSellStackItemRes` |
| `UseHealItem(u32, u32)` | `baeea1ba` | `use_heal.msgp` | `OnUseHealItemRes` |
| `UpdateItemStock()` | `cf39cc5c` | `update_item_stock.msgp` | `OnUpdateItemStockRes` |
| `ExshopExchange(u32, u32)` | `70d0f3ce` | `exshop_exchange.msgp` | `OnExshopExchangeRes` |
| `ExshopExchangeList()` | `7329eff2` | `exshop_exchange.msgp` | `OnExshopExchangeListRes` |
| `ExItemShop(u32)` | `33d09fb7` | `exitem_shop.msgp` | `OnExItemShopRes` |
| `MaterialCompose(u32, u32)` | `f9a4ba8c` | `material_compose.msgp` | `OnMaterialComposeRes` |
| `StaminaHeal()` | `737fac92` | `stamina_heal.msgp` | `OnStaminaHealRes` |
| `UpdateFollowMax()` | `7c2b82bf` | `update_follow_max.msgp` | `OnUpdateFollowMaxRes` |
| `GachaOnce(u32, s8 const*)` | `992ccbe5` | `gacha_once_item.msgp` | `OnGachaOnceRes` |
| `Gacha(u32, s8 const*, u32)` | `a0a1940b` | `gacha_pc.msgp` | `OnGachaRes` |
| `GachaTicket(u32, u32, s8 const*)` | `ee11c3d3` | `gacha_ticket.msgp` | `OnGachaTicketRes` |
| `BoxGacha(u32, u32)` | `5be25d4b` | `gacha_pc.msgp` | `OnBoxGachaRes` |
| `ResetBoxGacha(u32)` | `c292cf48` | `gacha_pc.msgp` | `OnResetBoxGachaRes` |
| `GetBoxGacha()` | `af250236` | `gacha_pc.msgp` | `OnGetBoxGachaRes` |
| `SaleGachaOnce(u32, s8 const*)` | `2d230806` | `gacha_once_item.msgp` | `OnSaleGachaOnceRes` |
| `SaleGacha(u32, s8 const*)` | `b164b4c5` | `gacha_pc.msgp` | `OnSaleGachaRes` |
| `GetGachaRate(u32, s8 const*)` | `d6bcb49d` | `gacha_pc.msgp` | `OnGetGachaRateRes` |
| `FollowList()` | `9bddc9d7` * | `follow_list.msgp` | `OnFollowListRes` |
| `FollowAdd(u32)` | `2559b5a1` * | `follow_add.msgp` | `OnFollowAddRes` |
| `FollowRemove(u32)` | `408f02f6` * | `follow_remove.msgp` | `OnFollowRemoveRes` |
| `Blacklist()` | `9bddc9d7` * | `blacklist.msgp` | `OnBlacklistRes` |
| `BlacklistAdd(u32)` | `2559b5a1` * | `blacklist_add.msgp` | `OnBlacklistAddRes` |
| `BlacklistRemove(u32)` | `408f02f6` * | `blacklist_remove.msgp` | `OnBlacklistRemoveRes` |
| `NeighborRegist(float, float)` | `9a57cfc9` | `__dummy.msgp` | `OnNeighborRegistRes` |
| `NeighborList(float, float)` | `451d30bf` | `__dummy.msgp` | `OnNeighborListRes` |
| `LocationRegist(float, float)` | `49898ba4` | `__dummy.msgp` | `OnLocationRegistRes` |
| `AchievementActiveList(u32)` | `d0b25cb6` * | `achievement_active_list.msgp` | `OnAchievementActiveListRes` |
| `AchievementReceive(u64)` | `47e9dee6` | `achievement_receive.msgp` | `OnAchievementReceiveRes` |
| `AchievementReceiveList()` | `d0b25cb6` * | `achievement_receive_list.msgp` | `OnAchievementReceiveListRes` |
| `UpdateHome(u64)` | `46e0807c` | `update_home.msgp` | `OnUpdateHomeRes` |
| `UpdateTutorial(u64)` | `1cf2b3d7` | `update_home.msgp` | `OnUpdateTutorialRes` |
| `NoLoginStart(s8 const*)` | `95804837` | `update_home.msgp` | `OnNoLoginStartRes` |
| `GetServerTime()` | `98b03930` | `update_home.msgp` | `OnGetServerTimeRes` |
| `CbtCertification(s8 const*)` | `5f583f50` | `update_home.msgp` | `OnCbtCertificationRes` |
| `SetStampSlot(vector<u32> const&)` | `58123949` | `compose.msgp` | `OnSetStampSlotRes` |
| `SetTitle(u32)` | `4332363c` | `compose.msgp` | `OnSetTitleRes` |
| `UpdateAwakenLevel(u64, u32)` | `2d714808` | `compose.msgp` | `OnUpdateAwakenLevelRes` |
| `DeepSpaceMissionStart(u32, u32, vector<u64> const&)` | `63c9927a` | `compose.msgp` | `OnDeepSpaceMissionStartRes` |
| `DeepSpaceMissionEnd(u32)` | `140e365b` | `compose.msgp` | `OnDeepSpaceMissionEndRes` |
| `DeepSpaceMissionEndNow(u32)` | `2df0328c` | `compose.msgp` | `OnDeepSpaceMissionEndNowRes` |
| `DeepSpaceAutoMemberSelect(u32, u32)` | `ed9aae28` | `compose.msgp` | `OnDeepSpaceAutoMemberSelectRes` |
| `SendErrorLog(s8 const*)` | `e5af488c` * | `send_error_log.msgp` | `OnSendErrorLogRes` |
| `UseFavorItem(u32, u32, u32)` | `88af959e` | `use_item.msgp` | `OnUseFavorItemRes` |
| `StaminaHealByFavor()` | `960546a3` | `stamina_heal_by_favor.msgp` | `OnStaminaHealByFavorRes` |
| `UpdateFavorByTap(u32)` | `e06ec7b3` | `update_favor_by_tap.msgp` | `OnUpdateFavorByTapRes` |
| `GetMasteryInfo()` | `45bea005` | `get_mastery_info.msgp` | `OnGetMasteryInfoRes` |
| `TrainMastery(u64, u64, uns8, u32, uns8, uns8)` | `bb0e7ef9` | `train_mastery.msgp` | `OnTrainMasteryRes` |
| `ResetMastery(u64, u64)` | `614fa7ea` | `reset_mastery.msgp` | `OnResetMasteryRes` |
| `GetDecoInfo()` | `33015ed5` | `get_deco_info.msgp` | `OnGetDecoInfoRes` |
| `FavoriteDecoObject(vector<u32> const&)` | `2b486f97` | `favorite_deco_object.msgp` | `OnFavoriteDecoObjectRes` |
| `UnFavoriteDecoObject(vector<u32> const&)` | `6c67993d` | `unfavorite_deco_object.msgp` | `OnUnFavoriteDecoObjectRes` |
| `SetCharacterDeco()` | `0747f39c` | `set_character_deco.msgp` | `OnSetCharacterDecoRes` |

### Reaching battle, gacha and the debug windows offline
Port options and scripts are in `port/README.md` "Reaching battle, gacha and the debug windows". What the routes showed:
- **Where offline assets come from.** `CGame::OnInitialize` sets `CFileLoader::SetDefaultDirectLoadFolder` to `builtin_download/` or `builtin_data/` when the APK has that asset dir (it has `builtin_data`), otherwise `<Aska::Global::m_pszStorageRootPath>/data/`. So the offline build reads everything through `AAssetManager` as `builtin_data/<rel>`, and a downloaded file `<rel>` (the online download tree's layout) slots in there (`--download-dir`).
- **Phase ids:** 4 Home, 8 SelectPart (the Mission button), 0xf Battle, 0x11 Gacha, 0x16 Server (title after "give up"), 0x17 TutorialNext (see `screen_phase.cpp`).
- **Battle start.** `CPhase_Battle::Progress` state 1 creates `CStageManager` and calls `CStageManager::Initialize(mission = CParameterUI+0x1a0, party index = +0x1b0, ..., MissionType = +0x140)`. The offline mission select never sets +0x1a0 (0 → "invalid mission stage: mission=%u" from `MissionToStageInfo`).
- `CStageManager::Progress` states: 1 `InitializeMissionData` + `CallMissionStart` (the `MissionStart` API); 2 wait for it (`IsRequesting`/`IsSuccess`/`ErrorCode` through the `CApiCaller` vtable +0x6a8..+0x6c0), 3 `MissionToStageInfo` + `CBattleDownloader::RequestDownoadStart` ("not found stage parameter: %d" when a stage has no parameter), 5 `IsDownloaded` → `CArena::InitializeBattle`, 6 `CArena::IsMain`, then the party from `CParameterManager+0x23d8` (a vector of 0x1690-byte entries; empty offline → "invalid selected party !") into `CPartyManager::InitializePlayer`.
- **`MissionStart` response** (as `CApiNotify::OnMissionStart` → `DeserializeToInfo` reads it): `MissionParameter` {`master_mission_id`, `master_mission_id_label`, `is_surprise`, `multi_player_count`, `stamina_cost`, `is_event_drop_by_favor`, `add_enemy_level`, `overwrite_enemy_level`, `mission_stage`: [{`serial_number`, `master_mission_id(_label)`, `master_stage_layout_id(_label)`, `master_enemy_party_id`, `master_map_id(_label)`, `stage_bgm`, `is_surprise_enemy_stage`}], drops}, `BattleParameter` {`rental_sub_character_id`}. All of it is in `master_mission` / `master_mission_stage`.
- **Gacha.** `CGacha` asks `GetGachaInData` (fid 0x8e4a88d7) first. The open gachas come from `GachaHashMap` (`CGachaHashInfoMap`: `IInfoBaseMap<u64, CGachaHashInfoListInfo>` of `CGachaHashInfo` {`master_gacha_id`, `opened_at`, `closed_at`}); with none the tabs say 現在、表示できるガチャはありません. `FakeApiCaller::GetGachaInData` only returns a Status, so the list stays empty with the fake server.
- **`NetworkApiCaller` request state** is a single slot: +0xcc0 function id (0x7b1a9377 = none), +0xcc4 error code, +0xcc8 "requesting"; `GetApiNotify` = this+0x7b0.
- **Debug windows.** `CDebugWindows::Initialize(u32, u32)` (arguments unused; 50 window slots) creates the `CManager` singleton and the skin; `CDebugWindows::Progress(float)` updates the windows and the mouse cursor. Nothing in the game calls either, nor `CDebugMenu`'s constructor (`CDebugMenu::Initialize` has no callers). `CDebugWindowsScript` compiles text orders named like its `CompileOrder_*` functions (`CreateNewWindow`, `CreateButton`, ...).

#### Playing a battle and a gacha through (fake server, 2026-09-28)
- **The selected party** is `BattleParameter.PlayerCharacter` of the `MissionStart` response: `CPlayerCharacterInfoList` (= `InfoBaseArray<CPersonStatusInfo>`) at `CParameterManager+0x23a0`, its vector at `+0x23d8` (0x1690-byte `CPersonStatusInfo`, up to 4 used). It's the server's precomputed battle status of each member; the client never builds it. `CStageManager::Progress` state 6 hands `entry.id` (+0x60) and "`id == 0 && master_role_id != 0`" per slot to `CPartyManager::InitializePlayer`, which calls `CBattleUtility::CreateCharacterInfoByAPI(i)` for each non-empty slot. `CBattleDownloader::RequestDownoadStart` also queues each member's files from it (`CreateCharacterFileListByAPI`).
- **`CPersonStatusInfo` properties** (value = property + 0x28; property offsets from `--fake-server-schema`): `id` u64 @0x60, `player_id` @0x90, `player_level` @0x100, `player_name` @0xc0, `master_role_id` @0x130, `weapon_item_id` u64 @0x160, `accessory_item_id` u64 @0x190, `level` @0x1c0, `exp`, `limit_break_count`, `skill1..3` (id, `_label`, `_level`), floats `hp` @0x430, `attack` @0x460, `intelligence` @0x490, `defence` @0x4c0, `hit` @0x4f0, `guard` @0x520, `ap` @0x550, `def_fire/water/wind/earth/thunder/light/dark`, `rush1`, `rush1_label`, `rush_skill1_factor_id`, `rush1_level`, `next_exp`, `weapon_id` @0x7d0 (a `master_weapon` id: its kind gives the model and attacks), `master_weapon_kind_id`, `weapon_kind_id_label`, `weapon_master_item_id`, `weapon_limit_break_count`, `weapon_level`, `accessory_*`, `up_exp_rate`, `up_fol_rate`, `add_drop_num`, `add_character_bonus`, `add_event_drop_num`, `is_rookie`, `is_subscription`, `title`, `add_hp/attack/intelligence/defence/hit/guard/ap`, `add_ap_by_favor`, `awaken_level`, `rush_gauge_max` @0xcc0, `rush_gauge_use` @0xcf0, `is_multi_main_character`, `favor_level`, `parent_master_role_id`, `mastery_talent_id`, `hair_id`, `pose_id`, `is_rarity_7`; children `factor_list` (`CFactorInfoMap`, @0xfe8), `DeityInfo`, `UniverseAddStatusInfo`, `UniverseDeityBoostInfo`, `Assist`, `CharacterDecoObject`, `UniverseEffectualTalentInfoList`. `tools/fakeapi_responses.py` fills them from `master_role` (base stats × (1 + level/10), HP × 10, AP 100, the first `master_weapon` of the role's weapon kind; our invention).
- **"not found stage parameter: 0"** was the response's fault: `CMissionStageInfo` (`mission_stage` entries) has `id` (the `master_mission_stage` id `CBattleDownloader` and `MissionToStageInfo` use), `id_label`, `order_id`, `is_boss`, and `stage_bgm` is a **uint** (CHash32 of the label), not a string. The generator now sends them.
- **Result:** with `--fake-server` + `--download-dir`, `mf01_001` plays through: STAGE 1/2 loading, BATTLE START, the party fights on its own (skills, special attacks, hit combos), WIN, STAGE 2/2, WIN, `MissionEnd` (answered from `mission_end.msgp`), the Mission Result screens (rank/points/FOL/time, then party EXP; members show "RENTAL" since their ids aren't owned characters). About 40 s of battle. `port/scripts/battle_session.sh` does it all; runs in `work/profile/battle`.
- **Profiles (2026-09-28, 21:50):** `work/profile/battle` (183 s: the whole mission and its result screens; 1992 functions the smoke and profiling sessions never ran, led by `CBattleUtility`, `CBattleManager`, `CCharacterObject`, the battle UI) and `work/profile/gacha` (167 s: list, tabs, a 10-draw with its summon and result; 792 new functions, led by `CGacha`, `CGachaManager`). `new-families.txt` in each ranks them (`port/scripts/coverage_diff.py`).
- **Battle crash, fixed:** about half the battle runs died at the stage 1 → 2 switch with `E/cpu: unimplemented instruction 0000xxxx` at `Aska::WavePlayer::~WavePlayer()+0xb8`, then `FATAL: interpreter fallback`. With libSOA's .text write-protected (a debug experiment), the writer was `smd::post` storing a message id through `out_id` = that code address: `SimpleMessageDispatcher::PostMessage(Task*, barrier, type, notify, a, b, k1, k2, u32* out_id, s8 prio)` takes `k2`, `out_id` and `prio` on the stack, and its caller `ParticleManager::RunLow` is an a2c transcription (containers) that calls it through the PLT stub, i.e. by `guest_call`. `guest_call` runs the callee on the next pooled CPU at *the current SP − 512*, so the body's stack arguments weren't where the callee read them. Fixed in `containers_a2c_test.cpp` `call()` (the body's stack slots are passed explicitly). The same "move the SP to the body's SP, then guest_call" pattern was in `objmgr.cpp` `a2c_call` and `cocos_guireader.cpp` `gr_call` (no stack arguments passed at all) and `models.cpp` `models_gcall` / `screen_a2c_rt.cpp` `gcall_jit` (8 words, unbounded). All runtimes now share core `a2c_guest_call` (cpu.h): it passes the body's first 16 stack slots, bounded by the CPU's SP; test `a2c/call-stack-args`. The direct paths (`hooked_host_fn`, run with SP = the body's SP) were already correct.
- **The gacha list** is `GachaHashMap` (`CGachaHashInfoMap` at `CParameterManager+0x5070`, map root at `+0x50b0`): key = master gacha id (a string or uint in the response, `InfoBaseNumberMap::ConvertParserValueToKey` parses strings with `istream >> u64`), value `{"GachaHashList": [CGachaHashInfo]}` (0x128 bytes each: `master_gacha_id` @0x60, `hash` string @0x90, `opened_at` @0xd0, `closed_at` @0x110). Its only reader is `CGacha::IsEnableHash(bool, u32 id, string& hash)` (called from `FirstCreateNormalAndStepup`, `AddListBoxSeries`, `AddTicketItemSeriesList`, `RemoveClosedStepUpFromSeriesList` with the master element's id at +0x38): the first entry with `str2time_t(opened_at) <= CGacha+0x358 (now) <= str2time_t(closed_at)` wins and its hash goes to the draw request; without one the gacha isn't listed ("dummy" otherwise). The master row's own dates still filter (29 of 2281 `master_gacha` rows are open after 2026 in both DBs).
- **`GetGachaInData`** is answered by `CApiNotify::OnGetGachaInDataRes` (DeserializeToInfo + the usual acknowledgement). The guest `FakeApiCaller` never queues it (Status 0); the port queues it in serve mode (`gacha_in_data.msgp`: the hash map for every master gacha plus a `Wallet`).
- **Coins:** the offline save has 0 紋章石 and the draw buttons then say 紋章石が足りません。紋章石の販売は停止しています。 The wallet is `Wallet` (`CWalletInfo` at `CParameterManager+0x1f20`: `free_coin`, `pay_coin`, `total_coin`, `android_coin`, one unnamed #2267f31d); the header shows it. `gacha_in_data` sends 100000 free.
- **Draw:** the recommended tab's first gacha (10連, ×2500, SALE) goes through `SaleGacha` (fid b164b4c5 → `gacha_pc.msgp`, `OnSaleGachaRes`): 10 `GachaItems` + 10 new `Character`s. The presentation runs in full with the download dir (召喚開始 → the summon room, discs, the magic circle, each character's reveal with rarity and name, ALL SKIP), then the ガチャリザルト list of the 10 characters, then a hint dialog (召喚完了っと!). The wallet isn't debited (the response doesn't send one). `port/scripts/gacha_session.sh` does all of it; runs in `work/profile/gacha`.

### Battle flow
From the desktop port's native `CBattleManager` / `CBattleLogModel` (`port/src/native/battle/battle_core.cpp`, `battle_log.cpp`). How a battle is reached offline: "Reaching battle, gacha and the debug windows offline" above.

**Who drives what.** `CPhase_Battle::Progress` creates `CStageManager`; `CStageManager::Progress` runs the mission (MissionStart API, stage download, `CArena::InitializeBattle`, party setup through `CPartyManager::InitializePlayer`, stage changes, MissionEnd). `CArena` owns the per-battle objects: `CBattleManager` (0x2120 bytes), `CPartyManager`, `CBattleUIManager` (with `CBattle`, the in-battle HUD: order gauge, skill buttons, target change), the camera. Every frame `CArena` calls `CBattleManager::Progress(dt)`.

**`CBattleManager` state** (`+0`, a u32; several places store `+0` and `+4` together as one u64):
- 1: `OnInitBattleManager` → 2.
- 2: create the boss intro camera (`CAnimationCameraObject`, `Camera/Boss.asf`, controller `BossCameraController`), add it to the arena's scene container (vtable +0, layer 3) and time element (vtable +0x10); start delay `+0x20d0` = `+0xc8`; kills carried over (`+0x20d8 += +0x20d4`, `+0x20d4 = 0`); hit counter reset → 3 (sub-state 0).
- 3: `Progress_BattleMain(dt)`; 5: `Progress_BattleResult(dt)`; 4 (result wait) and 6 (multiplayer exit) do nothing here.
- `+0x20c8` (the mission time) accumulates `dt` in every state.

**`Progress_BattleMain`, per frame:**
1. `CBattleOptimizeChecker::Check` (`+0x1f30`).
2. The battle clock runs (flag 0x80 of the u16 at `+0x20f0`, set when `dt != 0`) once the battle started (flag 2), unless a rush combo is requested (flag 1), a trans scene starts (flag 0x40) or the sub-state is 4/7. Then `CBattleFrameTime::Update(+0x20b8, dt)` (its first float is the battle time) and the temporary-auto check: while the result is lose/retire or the continue dialog runs (sub-states 9-12) temporary auto is switched off; otherwise, in multiplayer, idle time `+0x2118` accumulates and past `+0x1328` temporary auto switches on (`SetTemporaryAutoMode`: `CPartyManager::ChangeAutoMode`, `CBattleAnime::ShowTemporaryAuto`).
3. A drag on the touch panel ends temporary auto (or resets the idle time).
4. Target: the battle HUD's requested target (`CBattle::GetChangeTarget`) replaces the controlled character's target (`+0x618`) with SE 0x65; a missing or dead target is replaced by `CPartyManager::ChoiceTarget(chara+0x76d8, 0, 0, 0, true)`.
5. The hit combo times out: `+0x20e4` counts down (held at `+0x2a8` during a rush combo) and at 0 resets the counter (`SetHitCounter(0, 0, true)`); the character-change recast `+0x20e8` counts down.
6. The sub-state (`+4`):
   - 1 start delay (`+0x20d0`), then `OnStartBattle`;
   - 2 boss intro: waits for the boss's voice and for the camera animation to loop, releases the camera, marks the boss (`+0x77fe |= 2`), `LocalStartBattle`; flag 8 of `+0x2104` holds it;
   - 3 normal play: `CAITargetManager::Progress(+0x1554, dt)`, `Progress_LocalBattleNormal`, `CheckBattleResult` → `SetBattleResult`;
   - 5 rush combo: `Progress_LocalBattleRushCombo`; 7 trans scene: `CTransSceneManager::Progress` until its state is 6, then sub-state 8 and `ReleaseTransScene`;
   - 9 game over: `+0x20ec` (60 s, set by `SetBattleResult(lose)`) counts down, then `CBattleUIManager::ContinueOpen` → 11 (continue offered) or 10;
   - 10: when the dialog closed (`+0x2104` bit 2 clear), retire (`SetBattleResult(3)`); 11: bit 2 = failed (`CStageManager::ForceFinishSphereMission`), bit 1 = continue → 12 and `ContinueClose(true)`;
   - 13 battle end: waits for the controlled character's win resources (last stage only) and the end delay `+0x20d0`, closes the pause menu (only in multiplayer; otherwise waits), `CArena::FinishOrder`, `CBattle::StopOrder(false, true)`, resets the hit counter; on the last stage (not retired) fades BGM and 3D SE over 1.6 s; lose/retire: in a multiplayer stage (`CStageManager+0x58 == 4`) → state 6 / sub-state 14, else SE 4; win: SE 3 (last stage) or 400 (next stage); then `CBattleAnime::PlayBattleEnd(result, std::function{this, last stage})` → 14.
   - 4, 6, 8, 12, 14 are waits driven by other objects.

**Counters and bonuses** (all `CBattleManager` offsets):
- kills `+0x20d4` (cap 9999; `+0x20d8` earlier stages; `+0x20dc` needed, `GetKillCountLeft` = max(needed - kills, 0) or -1);
- hits `+0x20e0` (cap 99999) with the timer `+0x20e4` = keep time `+0x2a8` + extra; the hit bonus `+0x1ff0` is the bonus of the highest reached threshold in the 6-entry table `+0x1fa8` ({hits, bonus}), else 100. Both are sent to the multiplayer room when asked (`CMultiplayManager::SetKillCount` / `SetHitCounter`) and the best combo goes to the battle log;
- rush combo damage per character `+0x1ff8[4]`, total `+0x2008` (the log keeps the maximum);
- cancel bonuses: `GetCancelBonus(n)` = `+0x200c[clamp(n, 0, 9)]`, `GetCancelBonusRush()` = heat-up order bonus `+0x1f6c` (float) + `+0x2034[clamp(count +0x1ff4)]`, truncated;
- battle time `+0x20b8`, limit `+0x20bc` (`BattleTimeFrameLeft` = max(limit - time, 0), or -1 without a limit), sum of earlier stages `+0x20c4`.

**Rush combo / trans scene requests.** `StartRushCombo` copies the 20-byte request to `+0x1f5c` and sets flag 1 (not while one runs); `RideRushCombo` adds a character to a running combo (`CRushComboManager::AddRushCombo(chara, 10)`) or to the 5-slot ring `+0x1f90` (head `+0x1f88`, tail `+0x1f8c`). `StartTransScene` copies its 0x50-byte request to `+0x2060` and sets flag 0x40. The managers (`+0x1f70`, `+0x20b0`) have their own `{state, sub-state}`: state 4 runs (sub-state 4: waiting for the attack), 5 ends. The camera forwards (`StartRushComboCamera`, `BindTo*Camera`, `NoLink*Camera`) only act in sub-state exactly 5 / 7.

**Battle log** (`CBattleLogModel`, `CBattleManager+0x1538`): the mission_end statistics. The model keeps the total damage (capped at 4.2e9, computed in 64 bits), the largest single hit, the battle time, the best hit combo and the largest rush damage; the rest goes to the parameter manager's battle-log record (u32 values 0x30 bytes apart from `CParameterManager+0x5368`: damage, player damage, best combo, hits, rush cooperation, rush count, continues, mission type, 8 abnormal states from `+0x5518`, assist cut-ins, orders by type, the defeated-enemy list at `+0x58f8`).

**Tactics orders** (`COrderGaugeManager`, owned by `CArena`): the gauge lives in the controlled character (`+0x1338` points, `+0x1368` active order, -1 none, `+0x1398` order time left in seconds, -1 when ended); the manager holds the character index (+0), points per stock (+4), stock count (+8), per-order stock costs (+0x1c) and durations (+0x28), per-source gain multipliers (+0x58, sources 1-4) and the view values (+0xc partial stock, +0x10 whole stocks, +0x14 time left). `AddGauge` clamps at stocks x points and returns false when it hit the cap; `ActivateOrder(n)` pays `cost[n]` stocks and starts order n; `Progress(ms)` counts the order down (`ms / 1000`) unless stopped (+0x18) and plays SE 0x1f9 when the heat-up order (2) enters its last 5 s. `AddStock(float)` ignores its argument and adds one full stock.

**AI targets** (`CAITargetManager`, `CBattleManager+0x1554`): 12 rows (one per character slot) of 12 entries {hate, two hate rates copied from each character's +0x3018 / +0x3048, hostile flag}; `UpdateTarget` picks the most hated hostile entry with hate > 0 (the first of equals), else `CPartyManager::ChoiceTarget`; hates are recomputed every `CBattleManager+0x848` seconds.


**Quirks.**
- `Progress_BattleMain` calls `Progress_LocalBattleNormal(float)` without setting `s0`: it gets whatever `CAITargetManager::Progress` left there.
- `CBattleLogModel::EndBattle(float, u32)` asserts the parameter manager but adds the time to the model, ignoring the float.
- `IsBattleTimeOut` is flag 0x100 of `+0x20f0`, not the result.
- `SetBattleStart` only sets the sub-state to 1.
- The hit counters wrap like the guest's 32-bit adds (`AddKillCount` of 0x7fffffff gives 0x80000000, below the cap).

### Gacha
The gacha screen, its dialogs and the 3D draw sequence. Reached offline with `phase:0x11` and the fake server (see above and `port/scripts/gacha_session.sh`). The native port is `port/src/native/gacha/gacha.cpp` / `gacha_ui.cpp`.

**Master data.**
- `master_gacha` has 2281 rows in both the 3.7.0 and the offline DB. Each row is one banner step:
  - `gacha_type`, `gacha_category`, `table_name`;
  - costs: `coin`, `bulk_count` / `bulk_coin`, `ticket_item_id` / `ticket_num`;
  - rank rates `s..d_rank_rate` and bonus rates;
  - box fields: `is_box`, `next_box_gacha_id`, `box_gacha_index`, `reset_count`;
  - step-up fields: `is_stepup`, `next_stepup_gacha_id`, `stepup_number` / `stepup_max`;
  - sale fields: `sale_*`;
  - the window `opened_at` / `closed_at`, and `gacha_pickup_group_id`.
- Other tables:
  - `master_gacha_image`: 3703 rows, the banner and pickup images per gacha (`CMasterParameterGachaImage::ParameterFromMasterGachaID`);
  - `master_gacha_pickup`: 24 rows;
  - `master_box_gacha`: 11826 rows, box contents;
  - `master_gift_gacha`: 740 rows.
  
  The row counts match between the 3.7.0 and the offline databases. There is no rate table: the rates shown in the rate dialog come from the server.

**Server data** (in `CParameterManager`):
- `GachaHashMap` (+0x5070): which gachas are open, and their hash (see "Playing a battle and a gacha through").
- The rate list: a vector at +0x5058 of `CGachaRateInfo`, 0x1a8 bytes each, with `stepup_number` at +0x150 (its key table: `id`, `title`, `introduction_msg`, `bonus_msg`, `stepup_number`, then the `GachaRateContentInfoList` vector at +0x190). `GetGachaRate` fills it, and `CGachaRatio::SearchRatioInfo` reads it: it takes the first entry, or for a step-up gacha the entry whose `stepup_number` is the current step. The row types are in docs/server-rules.md#gacha-pools.
- The draw results: a vector at +0x4fb8 of `CGachaResultInfo`, 0x188 bytes each:
  - +0x60 item id;
  - +0xc0 role id (0 means an item);
  - +0x120, +0x150 and +0x180 flags.
- Gift-gacha results: a vector at +0x73b8, 0x158 bytes each: +0xc0 id, +0xf0 kind (2 character, 1 item).
- Also count, step-up, box and sale infos (`CGachaCountInfoList`, `CStepUpGachaInfoList`, `CBoxGachaInfoList`, `CSaleGachaCountInfoList`, day limits).

**Screen flow.**
- `CPhase_Gacha` (0x30 bytes) is a menu phase (see `screen_phase.cpp`): +0x24 the `CGacha` id, +0x28 the `CGacha`. `IsEnableRelease` returns state > 3, and `ToClose` forwards to `CGacha::ToClose`.
- `CGacha` (0xc00 bytes, a `CUIObject` / `CHaveCommon`) owns dialog units: `CDialogCommon` at +0x1a0, +0x390, +0x4e0 and +0x610, a `CCoinShop` at +0x730, and another at +0x970. Each frame `Progress` runs them all, then its state at +0x188 (sub-state +0x190):
  - 0: waits for the menu voice resource and the scene, then `Setup` (vtable +0x118).
  - 1: sub-state 0 waits for `GetGachaInData`. Then it builds the series list (`FirstCreateNormalAndStepup`, `AddListBoxSeries`, the pickup images, `CreateTabList`, `UpdateListOption`) and fades in.
  - 3 / 4, 5 / 6: fade and maintenance checks.
  - 0xd onward: the selection, the confirm dialog, the request, and the production (`ProcProduction`) with `CGachaManager`.
- `CGacha::IsEnableHash(stepup, id, hash&)` sets `hash = "dummy"` first. For a step-up gacha it always returns true. Otherwise it looks the id up in `GachaHashMap` and succeeds when now (+0x358) lies within an entry's `opened_at`..`closed_at`, copying that entry's hash.

**The draw sequence: `CGachaManager`** (0x4f8 bytes, `TSingleton<CGachaManager>`, own `CArena`).
- **`Initialize`** copies the results (+0x4fb8, or the gift results +0x73b8) into up to 10 entries of 0x68 bytes at +0x08:
  - +0x08 kind: 1 character, 2 item (gift gachas: 1 character, 0 item);
  - +0x0c role id, +0x10 item id;
  - +0x1c rarity index;
  - +0x4e the entry's camera animation name.
- **`Progress`** state (+0x00):
  - 1: waits for `CArena::IsMain`, loads map `bg99_01`, `LoadResource`, and the character `Character/cp0002_b01b.asf` with `Motion/Gacha.apk` as a `CThingObject`.
  - 2: waits for the map, the character and the resource and sound loads. Then it fades in (12), makes the map's `camera1` node the current camera, sets the audio listener, starts `Camera/gacha_camera_01.aaf`, warms up the character (60 frames), plays `gacha_cp0002_01.aaf` and the opening effect, and plays SE 0x2b.
  - 4: `Progress_Main` until +0x480 (exit) and +0x481 (done).
  - 5: BGM volume back to 1, fade out, `StopAllSE` (system SEs 0x2b..0x35 and the two arena SEs at +0x460 / +0x468).
  - 6: once faded, restores the main camera and removes the audio listener, then `DeleteStage`, `ReleaseResource`, `CArena::ToRelease`.
  - 7: waits for the arena (vtable +0x40), then deletes it.
  - 8: done (`IsProcessEnd`).
  
  A state store is 8 bytes wide, so it also clears the sub-state +0x04. Every frame ends by clearing the tap flag +0x482.
- **`Progress_Main`'s steps** (sub-state):
  - `CheckDisc` starts entry `i`'s disc effect when the base effect (+0x494) reaches frame `table[i]` (floats at `.rodata` 0x26e5d08). The node is `disc_posi_11` for a single draw, else from the node table 0x299c6f8. Its effect id comes from a function-local static copy of three effect ids, indexed by the rarity index. After the last disc: sub-state 2.
  - `CheckDiscDisappear` stops the discs at frame 0x26e48a4: sub-state 3.
  - `CheckMagicEffect` adds a magic mark per entry at frame 0x26e48a8: sub-state 4.
  - `CheckMagicEnd` waits for the map object's added (camera) animation to end (flag bit 2 at +0xc): sub-state 5.
  - Sub-state 15 is the 2D result page per entry: `Is2DWait` / `Get2DWaitIndex`, and `RequestNextChara` sets +0x483.
- **`RarityIndex(rarity, rainbow)`**: 0 below rarity 4, 1 for 4, 2 above. The rainbow variant is only for rarity 5, on `Aska::Random(2) == 0`.
- **`StartEffectToEffect`** plays an effect, links its animation to the parent effect's, and re-parents its root to a named node of the parent model.
- **Quirk:** `CheckDisc` and `CheckMagicEffect` pass a leftover `x0` as `this` to `StartEffectToEffect`, which doesn't use it.

**Dialogs.**
- **`CGachaRatio`**, the rate dialog, is a `CUIObject` with secondary vtables at +0x50 and +0xc8:
  - fields: +0x128 state (0 opening, 1 open, 2 close requested, 3 releasing), +0x12c step-up flag, +0x130 step, +0x134 step count, +0x138 name, +0x150 scene;
  - vectors: +0x158 `RatioData` (0xc0 each), +0x170 u32;
  - layout `gacha_ratio`, and the step label `Panel_1/window/Node_3/Image_step/AtlasLabel_step` (`"%u/%u"`);
  - while it's open, the "now loading" online indicator is disabled (flag 3).
- **`CGachaShortage`** (layout `gacha_dialog`), **`CGachaConfirm`** (`gacha_result2`) and **`CBoxGachaResetConfirm`** (`gacha_box_dialog`) are `CDialog`s. Their `RequestClose` passes a lambda to `CDialogCommon::Close`.
- **`CBoxGachaCompleteDialog`** (`gacha_box_complete`):
  - `StopBGM` stops the box-complete BGM (type 0x10) if it plays, and starts the `tTimeDelegate` at +0x120: 20 s, then a lambda sets +0x160, which is `IsEnableClose`.
  - `tTimeDelegate::Progress` counts down by `FrameworkDT`. **Quirk:** a NaN timer never fires. After the subtraction the guest skips on `b.hi`, which is also taken when the comparison is unordered, so a plain C `0.0f < left` test would not match it.

### Rendering
- The render size comes from `CGame::OnColdStart`. `CUIUtility::IsResolutionLegacy()` is hard-coded `true` and `CUIUtility::GetDefaultBackBufferScale()` returns 0.75, so on a 1280×720 display the game renders at 720×405 via `ANativeWindow_setBuffersGeometry` (`Aska::RenderDeviceGL::CreateSurface`).
- The non-legacy path (full size) works; it's the port's `--hires` option.
- The game creates one GLES 2 probe context, then a GLES 3 context plus two shared loader contexts.

### Orientation and the home camera
- The game is portrait: the phone is held upright, and in Waydroid it runs 9:16. It adapts its layout to any aspect ratio, but the 3D home camera (`CHomeModelViewManager::SetCameraPos`) is tuned for tall screens:
  - zoom = `((w/h / 0.5625 − 1) · 0.9 + 1) · 0.5`
  - aim height = 90 + `master_person.height` + `home3d_camera_height_offset` + `(1 − 0.1·(w/h / 0.5625 − 1)) · −130`
  - camera: the home map's `camera1`/`camera1_aim` nodes, 15° field of view.
- On a landscape screen these put the character's head at mid-screen, cut off by the bottom menu.

### Movies
- All MP4s (`builtin_data/Movie`, `assetpack/Movie`) are stored 540×960 portrait with the picture rotated. Android shows them in a portrait-locked activity while the phone is held landscape; upright is a 90° counter-clockwise rotation.

### Asset encryption (ADLD)
- Header: `"ADLD"`, u32 flags, 8 unused bytes. `flags & 1` means XOR with the ASCII `"%x"` of `CHash32(name)`, repeated. `flags & 2` means AES-128-CBC.
  - Key: the `"%032u"` of `CHash32(name)`, one decimal digit per nibble.
  - IV: `"09375711857134629684891855841614"`, packed the same way.
  - An optional `DCNE` v1 inner header gives the real plaintext size.
- `CHash32` is CRC-32 (reflected, poly 0xEDB88320) seeded with the input length, with no final XOR. Empty input hashes to 0.
- The game's `CHash32::operator<` / `operator>` are swapped (`lt` returns `rhs < this`); the port keeps that.

### Event scripts and text
- `ASON` is Aska's MessagePack reader. An `AValue` is 0x20 bytes: type at +0, then pointer/value at +8 and +0x10, and length at +0x18.
  - Types: 0 nil, 1 bool, 2 uint (non-negative ints), 3 int, 4 double (float32 is widened), 5 string, 6 array, 7 map.
  - A map entry is 0x40 bytes (key value, then value). Strings stay UTF-8 (`Utf8ToMultiByte` is an identity copy).
- Event script files look like `{"Script":{"<name>":[{id, command_type, command_param0..8}, ...]}}`. `CEventScenario::InitializeCommandList` turns one into a `vector<tCommandData>` at +0x278:
  - Each `tCommandData` is 0x30 bytes: id, type, 9 float params (a missing param is `2143289344.0f`), and a flag byte = 1 at +0x2c.
  - The string table is a `list<string>` at +0x290 (`AddString` returns an existing index or appends).
  - The script and message paths are at +0x28 and +0x40.
- Text lookups (`StringDB::GetNativeString`):
  1. Compute `CHash32("ja_" + id)`.
  2. Look it up with `CParameterManager::pStringDB()->pParameterFromHash`.
  3. Take the text at record +0xa8 and XOR it with 0x20 (`CryptString<32>`).

  `StringDB::Get` additionally turns a literal `\n` into a newline.

### ObjectManager: the per-frame render preparation (from the desktop port, `port/src/native/engine/objmgr.cpp`)

`Aska::ObjectManager` (global `Aska::Global::m_pObjectManager`, one per process) owns every
`RenderableObject` and prepares them for the render thread each frame. The main thread runs it from
`AskaMainThread::Handler` → `TaskManager::OwnersKickTask`:

1. **`Prerender()`** (task): camera matrices, `PrepareMatrices`, culling, candidate lists.
2. **`OnPrePaint()`**: painting lists, `PreliminarilyPrepare` on every candidate.
3. **`OnPaint()` → `OnPostPaint()`**: per render pass, `TraversePaintingList[NoResolve]` runs
   `PrepareForRendering` on each object of a painting list and queues it on the render thread
   (`RenderThread::AddRenderQueue`, `AddTemporaryResolve`).

Each step fans out to the `ObjectManagerJobDispatcher` worker threads and collects per-object results
from a **result bitmap** (`om+0x1ba0`, capacity in objects `om+0x1ba8`, grown with `new[]`): 2 bits per
object, `0` pending, `1` skipped/visible, `2` true, `3` false, OR-ed in atomically by the workers. The
main thread consumes results strictly in list order, up to 2 (or 10+ for culling) per poll, so the
render queue order is deterministic even though the work is parallel.

**ObjectManager layout** (partial):

| Offset | |
|---|---|
| +0x08 | intrusive list of all renderables (sentinel; `obj+0x08` prev, `obj+0x10` next; first at `om+0x18`) |
| +0x1000 | `RenderContextServer*` (per-frame `RenderContext` arrays: `ResetServer`, `GetRenderContext(n)`) |
| +0x1010 | array of objects on "post" layers (count `om+0x1bc4`) |
| +0x1018 | array of live objects built by `PrepareMatrices` (count u16 `om+0x4452`; each object's index in `obj+0x1b8`) |
| +0x1020 + 16·p | per sub-camera/pass `p`: painting list output (`+0`) and candidate array (`+8`); counts s32 `om+0x1bc8 + 4p` |
| +0x1ac8 | frame candidate list (count s32 `om+0x3ef4`): every object `PreliminarilyPrepare`/`PrepareForRendering` sees |
| +0x1ae0 / +0x1b08 | objects whose use count (`+0x1ac`) is bumped each frame |
| +0x1af0 / u16 +0x3f00 | animatables (`IAnimatable::IsThisIt(0xf113)`) found by `PrepareMatrices` |
| +0x1c08 (s32×128), +0x1e08 (u16×64) | multipass / shadow painting lists in use this frame (→ `MakePaintingListMultipass/Shadow`) |
| +0x20a8 + 0x38·p | `RenderInfoCond` list per pass (`MakeRenderInfoConditionList`) |
| +0x3ef0 | u16 base index for the post-filter render contexts |
| +0x3f09 | u8 frame phase (3 in Prerender, 4 after culling, 5 done) |
| +0x3f0b | u8 "separate Z pre-pass" (MakePaintingList adds objects with flags `&0x20400010 == 0x10` to layer 0) |
| +0x3f0c / +0x3f0e / +0x3f13 / +0x3f14 | u8 prerendered / skip frame / painting lists ready / first-frame latch |
| +0x3f1c, +0x3f1d | effective render-layer condition, "limit condition" flag |
| +0x3f20 | s32 sub-camera (pass) count, `max(1, n)` used everywhere |
| +0x3f48 + 8·p | `RenderableObjectContext*` per pass: the depth keys `TOMQuickSort` sorts by |
| +0x4468..+0x45a8 | per-frame `TLongInt<2>` multipass-ID masks |
| +0x4478 | render layer table: u32 count, +8 → u16 per layer (byte 1 flags: bit0 sort descending, bit1 ascending, bit2 custom sorter `om+0x1b00`, bit3 multi-draw, bit4/5 frame-texture entry), +0x10 + layer id → u8 layer group, +0x1e/+0x21/+0x25 u8 condition thresholds |
| +0x4480 | `RenderThread*` (`+0x501d1` u8: device lost/resetting) |
| +0x45b0..+0x45c8, +0xb420 | system renderables re-added to the candidate list every frame (clear targets, post-process combiner…) |
| +0x4620 + 0x48·i | multipass environment `i` (object at +0, s8 flags at +0x12) |
| +0x104f8 (×64), s32 +0x106f8 | post filters (`PostProcessCombinerTBR`), given fresh `RenderContext`s in `OnPrePaint` |
| +0xb418 | `PostProcessCombinerTBR*` |

**RenderableObject** fields the pipeline uses: `+0x198` u32 system flags (meanings inferred from use: bit 3
skips culling, bit 6 set when found visible, bit 8 cleared when added to the candidates, any of
`0x6081` excludes the object from the frame, bit 21 → vfunc `+0x298` and bit 25 → vfunc `+0x1f0` on
reset/cull), `+0x19a`/`+0x19b` behaviour flags (temporary resolve, post-cull hook),
`+0x1a0` own camera, `+0x1ac` s32 use count (atomic), `+0x1b5` u16 frame flags (bit 0 prepared,
bit 3 in candidate list, bit 8 on a post layer), `+0x1b7` u8 layer id, `+0x1c0` s32 RenderContext
count, `+0x1cc` s32 next context index, `+0x1d0` `RenderContext*` array (0x230 bytes each),
`+0x1e8..+0x208`, `+0x230..+0x240` per-frame multipass/sub-camera bit masks, `+0x218/+0x220`
multipass IDs, `+0x22c` u32 extra-pass count. Virtuals: `+0x198` reset per frame, `+0x270` added to
candidates, `+0x278` `PreliminarilyPrepare(LightManager*)`, `+0x280` `PrepareForRendering(const
RENDERINFO*)`, `+0x1f0` / `+0x298` reset / release hooks, `+0x1f8` post-filter painting-list hook.

**Painting list build** (`MakePaintingList(pass)`, on a worker): a counting sort of the pass's
candidates by layer group (`layers[+0x10 + obj->layer]`), objects with extra passes counted once per
pass, frame-texture entries and post filters inserted per layer; then each layer's slice is sorted
with `TOMQuickSort<RenderableObject, float, 64, 10>::Ascend/Descend` (quicksort with an insertion
sort below 10 elements, keyed by the pass's `RenderableObjectContext`) or handed to the custom sorter.
The final count replaces `om+0x1bc8 + 4p`, and `MakeRenderInfoConditionList` records where the layer
conditions change.

**Culling inputs**: the current camera is `CameraManager+0xff0`; `Camera::MakeCameraMatrix` and
`MakeViewFrustumPlane(sub)` (unless `camera+0x940/+0x941+sub` says they're current) fill the frustum:
eye/axis vectors at `camera+0x130..+0x158`, per sub-camera planes at `camera + 0x60·(sub+1) +
0x200..0x258` and `+0x560..0x5b8`. `ViewFrustumCulling(camera, sub, pass, objs, first, last, bitmap)`
tests each object's bounds against them and writes `1` (visible) / `2` (culled, needs reset hook) into
the bitmap; `OcclusionCulling` does the same against the `OccluderManager` list when occluders exist.

**ObjectManagerJobDispatcher** (global `m_pObjectManagerJobDispatcher`): `+0x98` array of
`ObjectManagerWorkerThread` (0x210 bytes each), `+0xac` worker count, `+0xb4` index of the worker the
render thread borrows (`< 0` none), `+0xb8` it is excluded. A worker runs one *mode* at a time (1 make
painting lists, 2 PreliminarilyPrepare, 3 PrepareForRendering, 4 culling, 5 DetectLIBL, 6 reset system
flags, 7 sleep): the dispatcher's `ChangeMode(m)` waits until no jobs are in flight and hands every
worker the new mode (`ObjectManagerWorkerThread::ChangeMode`: `+0x114` requested, `+0x119` pending,
under the worker's FastCriticalSection at `+0x80`). `Dispatch_X` gives one job to the first worker
that is started (`+0x11a`), idle (`+0x118`), has no pending change and no job (`+0x11c == 0`) and
runs mode X, and otherwise nudges idle workers into mode X and returns false — the callers retry.
Job parameters live in the worker (see the layout comment in `objmgr.cpp`). Guest quirks: with no
workers, `Dispatch_MakePaintingList` retries for ever; `Dispatch_RenderingDecided` posts a culling job
of kind 3 that no handler implements.

**Why it was slow under the JIT**: every retry and every "is the next result in?" poll was a busy loop
(`Aska::Thread::Switch()` is a no-op), so the main thread spent ~10% of its time spinning in
`TraversePaintingList` / `Dispatch_PrepareForRendering` / `OnPrePaint`. The native pipeline blocks on
a futex that the native workers bump when they publish a result or change state.

**In the port** (`port/src/native/engine/objmgr.cpp`, `objmgr_a2c.cpp`, `smd.cpp`): the dispatcher, the
worker handlers, `OnPrePaint`, `PrepareMatrices`, `TraversePaintingList[NoResolve]` and
`MultithreadViewFrustumCulling` are hand-written C++; `ViewFrustumCulling`, `MultithreadOcclusionCulling`,
`MakePaintingList[Post]`, `TOMQuickSort`, `MakeRenderInfoConditionList`, `AddPaintingListCandidates`,
`Prerender[_MultiPass|_VersatileAndMotionBlur]`, `OnPaint` and `OnPostPaint` are transcribed from the
ARM64 by `tools/gen_objmgr_a2c.py` (a2c with guest-call fallback and exclusive monitor). Guest quirks kept: `OnPrePaint` sets
`om+0x3f13` only when the result bitmap could be allocated; `MultithreadViewFrustumCulling` writes
`in[count] = in[count-1]` even for `count == 0` (i.e. `in[0] = in[-1]`); `DeleteMessage` never returns
the block to the free ring (and a negative id empties the queue without fixing the counters); a
`Send*` whose event can't be created leaves an unfilled block queued; a multi-post that runs out of
blocks unlinks what it queued without returning those blocks to the ring either. The dispatcher's
`ChangeMode` is satisfied once *one* worker accepted the new mode, so a worker still applying the
previous change keeps its old mode until a later `ChangeMode` (harmless in the game, which changes
modes every frame; a test that waits for every worker to reach sleep mode must ask each one).

### Shadows: ShadowManager / ShadowManagerRegistry (from the desktop port, `render_a2c` group "shadow")

`ShadowManagerRegistry` (at `ObjectManager+0x104f0`, a task) runs once a frame (`Run`): `FirstPrepare`
picks each manager's light (`+0xb8`, by name or light mask when `+0x230` says so) and ORs the light
masks into `registry+0xff0`; the frame's candidates with receive-shadow set (`obj+0x1b5` bit 5) become
receivers (`om+0x1ad8`, count u16 `om+0x3ef8`) and the shadow casters (`om+0x1ad0`, count `om+0x3efa`);
up to 32 active managers are sorted by a priority word (`mgr+0x258`) into `registry+0x12f0`, and
`ShadowManager::ShadowCasterCulling(casters, n, receivers, m)` runs for each (and for each cascade clone
in the slot table). Registry: `+0x08` intrusive list of managers, `+0xff8` / `+0xffa` / `+0xffb` u8 slot
counters, `+0x1000` slot bitmaps, `+0x10f8` slot → manager table.

ShadowManager (0x2e0 bytes): `+0xa0` 128-bit multipass-ID mask, `+0xb0` light mask, `+0xb8` Light*,
`+0xc8` override light, `+0xd0` / `+0xd8` two 0x8000-byte candidate buffers (double-buffered; freed
by `Run` after 150 idle frames, `+0x1c0` u16 counter), `+0xe0 + 8i` per-cascade receiver arrays (counts
u16 `+0x1a6 + 2i`), `+0x1c2` u8 registry slot (0xff none), `+0x1c3` cascade count, `+0x1c9` u8 kind,
`+0x200` the shadow Camera. `ShadowCasterCulling` fits the light's frustum / cone to the casters,
may take cascade clones (`ShadowManagerRegistry::AllocClone`: a new 0x2e0-byte ShadowManager each
time), calls `ObjectManager::SetShadowEnvironment` / `SetShadowMapResolver` (the latter creates a
0x440-byte `ShadowMapResolver` in `om+0xb1f0 + 8·slot` when missing and appends it to the frame's
candidate list), and marks receivers through `AofObject::SetShadowManagerIndex`, which keeps the
per-receiver slot bytes (`ReceiverShadowManagerIndex::AddOnce`: 6 bytes, 5-bit id + 3-bit cascade) in a
node of the object's hash table (`AofObject+0x398`, created on first use). None of that can be
snapshotted and put back, which is why its live check replays those callees (see `render_shadow.h`).

### Event scenes: the script interpreter (`EventScenario::CEventScenario`)

Sources: `work/decomp/story-es.resolved.c` (and `story-base`/`story-objs`), plus a decode of all 458
`Script/*.msgp` files of the offline build's install-time pack (87,856 commands; the 3.7.0 download has 598 in `Script/`). Counts below come from that decode.

#### Script loading

- `InitializeCommandList` (ASON = MessagePack) converts each `{id, command_type, command_param0..8}` to a
  `tCommandData` (0x30 bytes): `s32 id @0`, `s32 type @4`, `float p[9] @8..@0x28`, `u8 valid @0x2c` (always 1).
  Value conversion: bool -> 1/0, int/uint/double -> float, string -> `AddString()` index (the table is
  deduplicated, `list<string>` at +0x290, count +0x2a0), missing key -> `NaN-ish 2143289344.0f` ("absent").
  Every `bool`-style test in the handlers is `p != 0 || p == absent` (default true) or `p != absent && p != 0`
  (default false). Scripts often pass the *strings* `"True"`/`"False"`. They become string indices, and a
  string index is nonzero unless the string was the first one interned, so `"False"` usually tests **true**
  (quirk, as decompiled).
- The first key of `Script` is copied to +0x260 (the script name).
- `InitializeFromBuffer` walks the commands to collect resources (csf/aif/SE banks, including `Fukidashi`
  balloons for 0x17/0x1f). It calls **`ParseMessage`** on every MessageChange (23) and BacklogChange (59), then
  sets state 5. `ParseMessage` gets the message text from `StringDB` by p0 and expands `<player>` to the
  player name. It then splits the text at the inline tags `fontcolor`, `fontsize` and `/font` (tag map: player=1,
  fontcolor=2, fontsize=3, /font=4) and **inserts** a MessageAppend (50) after the command for each segment, or
  a BacklogAppend (60) for a BacklogChange. So opcodes 50 and 60 never appear in files but run at runtime (?
  exact split rules).
- `GetEventScenarioInfo` only builds a debug text: the object list printed as `BackGround`, `Character`, …
  with `%.2f` times, plus `End`. It has no gameplay role.

#### Command table

`f/30`: script value in frames, divided by 30 to get seconds. `T`: default fade of 0.33 s. `w`: "wait" bool.
The handler stores it in `obj+0x14`, and CalcCommand blocks while the object's `IsWait()` is set.
`name`: the object's identification name (`obj+0x18`), used to find an existing object of that type. Count 0
means the command never appears in the shipped scripts.

| # | name | count | params (p# = meaning, default) | effect |
|---|------|------:|--------------------------------|--------|
| 0 | None | 0 | – | no-op; never dispatched (only types 1..77 are); used as a placeholder by rewrites |
| 1 | EventExit | 458 | p0 num: `0` → end now; absent/≠0 → fade-out first | p0==0 → `Exit()`. Otherwise it rewrites itself to EventExit(0) and inserts before that: None, MessageClear, CharacterHide(each char, 10f, w=0), WaitTime 5, BgShow(str idx +0x480, 15f, w=0), WaitTime 20, MessageHide(T, w=0) per window, WaitTime 15, FilterShow(30f). Scripts: p0=0 in 223 files, absent in 235 |
| 2 | MessageShow | 530 | p0 str window image (""), p1 f/30 (T; forced 0 if node +0x110 visible), p2 w (true) | find or create MessageWindow (type 6) → `Show(img,t,w)`; an enabled StageDirections is hidden with the same t |
| 3 | MessageHide | 304 | p0 f/30 (T), p1 w (true) | `MessageWindow::Hide` |
| 4 | CharacterShow | 8404 | p0 str csf (`cp0002_ta01a`), p1 str face ("def"), p2 x (0: ±180 or 0 in data), p3 bool front (false), p4 fade f/30 (T; 0 when reusing), p5 z (150), p6 w (true), p7 str name (reuse existing), p8 bool (true) | new or reused Character (type 3) → `Show(csf,face,x,0,t,z,w',name,p8)`, with w' = p6 ∨ (p8==0). Then `SetShowPriority`: p3 true → this character true and the others false; p3 false → the reverse |
| 5 | CharacterHide | 199 | p0 name, p1 f/30 (T), p2 w (true) | `Character::Hide(t,w)` |
| 6 | MessageSpeedChange | 230 | p0 seconds per character (0.033) | +0x484 = p0, and the window's +0x74 |
| 7 | BgShow | 2770 | p0 str bg (`(file:anim)` or file), p1 f/30 (**0**), p2 w (true), p3 str name, p4 str color `(r:g:b:a)`, p5 z offset (z = 50+p5) | BackGround (type 1) `Show(file,color,t,w,name)`. If it is the first command (only SkinChange before it), it first runs FilterShow(p0=0.33, default color) (?) |
| 8 | BgHide | 23 | p0 f/30 (T), p1 w (true), p2 name | `BackGround::Hide` |
| 9 | WaitTime | 16236 | p0 frames (no default) | +0x2d8 = p0/30 (blocks until ≤0) |
| 10 | WaitInput | 655 | – | +0x2d4 = 1 (wait for tap) |
| 11 | TelopShow | 0 | p0 str color, p1 f/30 (T), p2 w (true) | Telop (type 7) `Show(color,t,w)` |
| 12 | TelopHide | 0 | p0 f/30 (T), p1 w (true) | `Telop::Hide` |
| 13 | SpriteShow | 125 | p0 str `(file:anim)`, p1 x (0), p2 y (0), p3 f/30 (T), p4 z (200), p5 bool (true), p6 name, p7 bool (true) | Sprite (type 4) `Show(file,x,y,t,z,p5∧p7,name)` |
| 14 | SpriteHide | 106 | p0 f/30 (T), p1 w (true), p2 name | `Sprite::Hide` |
| 15 | FilterShow | 1199 | p0 f/30 (T), p1 str color, p2 z (800), p3 w (true), p4 name | Filter (type 8) `Show(color,t,z,w,name)`; also forces UI buttons +0x150/+0x168/+0x1e8/+0x1f8 visible |
| 16 | FilterHide | 1390 | p0 f/30 (T), p1 w (true), p2 name | `Filter::Hide` |
| 17 | ShakeStart | 1147 | p0 duration f/30 (absent → -1 = endless), p1 amp X, p2 amp Y, p3 jitter period /30 (1/30 s), p4 w (true; only if duration ≥0), p5 bool (false) | new `tShakeData` ×2 at +0x328/+0x330; p5 → +0x338 (?) |
| 18 | ShakeEnd | 76 | p0 fade f/30, p1 w (true) | +0x328: remaining = p0/30, wait flag |
| 19 | BgmPlay | 819 | p0 str cue, p1 volume % (100, clamped 0..1), p2 fade-in ms (0), p3 ms (30) (?) | BGM object (type 0xb) → `CSoundManager::PlayBgm(cue,vol,p2,p3,-1)` (both times 0 while skipping); +0x2c0 = 1 |
| 20 | BgmStop | 868 | p0 fade ms (0) | before any BgmPlay (+0x2c0==0): `CSoundManager::StopBgm(p0)` stops the BGM already playing, then +0x2c0=1; otherwise `BGM::Stop` |
| 21 | SePlay | 4189 | p0 str `(bank:cue)`, p1 loop (false), p2 volume (1), p3 ? (0), p4 pan? (0), p5 w (false), p6 name, p7 ms? (0), p8 keep (true) | SE (type 9) `Play`; loop→+0x40, keep→+0x41 (such SEs survive the next MessageChange); non-looping SEs skipped while fast-forwarding (?) |
| 22 | SeStop | 1077 | p0 fade ms (0), p1 name | `SE::Stop` |
| 23 | MessageChange | 17259 | p0 str message key (StringDB), p1 str speaker (character name), p2 str face, p3 str manpu, p4 wait-input (true), p5 str voice, p6 str name-plate key (`<player>` → player name; absent → speaker's name key), p7 bool all-lit (false) | find or create the window (`Show("",T)`) and apply +0x484/+0x488/+0x48c/+0x490/+0x494. Then `Change(text,name,voice)`, or `StageDirections::PushMessageID` if SD is enabled; p4 → +0x2d4. `Face(p2)` and `ManpuShow(p3)` on the speaker. `Stop(500ms)` every SE/voice with +0x40 and +0x41 both 0. `SetSpeechActivate` (speaker, or everyone if p7) and `SetShowPriority(speaker)`. Backlog (type 2, created if needed) `PushLogID` |
| 24 | Label | 173 | p0 str label | no-op |
| 25 | Jump | 116 | p0 str label | +0x2c8 = first Label whose p0 matches (execution continues after it) |
| 26 | CharacterShakeStart | 3113 | p0 name, p1 duration f/30 (-1), p2 amp X, p3 amp Y, p4 period /30 (1/30 s), p5 w (true, only if duration ≥0) | `Character::SetShakeData(new tShakeData)` |
| 27 | CharacterShakeEnd | 119 | p0 name, p1 fade f/30, p2 w (true) | char+0x140 shake: remaining/wait |
| 28 | MessageColorChange | 0 | p0, p1 str colors | +0x488/+0x48c; `MessageWindow::SetColor` |
| 29 | TelopChange | 0 | p0 str text, p1 int (5), p2 wait-input (true), p3 str | find or create Telop (`Show(T,0x80000000)`) → `Change(p0,p1,p3)`; p2 → +0x2d4 |
| 30 | SelectMenu | 45 | (p0 text key, p1 label) ×4 in p0..p7 | count +0x3b8 = 1..4 (by p2/p4/p6 present); texts → labels at +0x198[i]; targets → +0x3c0[i]; +0x3e0=-1; show panel +0x170, play anim `Select%d_on`, +0x2dc=1 (blocks until chosen; the jump to the chosen label happens in a callback (?)) |
| 31 | CharacterManpuShow | 149 | p0 name, p1 str balloon (`Fukidashi03`), p2 int (0) (±1 = side?), p3 bool persist (false), p4 bool (false) | `ManpuShow(p1,p2,p3,p4)`; p3 → char+0x168=1 (not auto-hidden) |
| 32 | CharacterManpuHide | 134 | p0 name, p1 bool (false) | `ManpuHide(p1)`, char+0x168=0 |
| 33 | CharacterAnimationStart | 2726 | p0 name, p1 str anim (`Cha_Nod`, `ChaInRun_L`…), p2 loop (false), p3 w (true, ignored if loop), p4 flag (false) | `AnimationStart(anim,loop,w,flag)` (shared Sprite impl; flag → tCustomAnimation+5 (?)) |
| 34 | CharacterAnimationStop | 8 | p0 name, p1 anim | `AnimationStop(anim)` |
| 35 | BgAnimationStart | 9 | p0 anim, p1 loop (false), p2 w (true), p3 bg name, p4 flag (**true**) | on BackGround |
| 36 | BgAnimationStop | 0 | p0 anim, p1 bg name | |
| 37 | SpriteAnimationStart | 106 | as 35, p3 = sprite name | on Sprite (type 4) |
| 38 | SpriteAnimationStop | 0 | p0 anim, p1 sprite name | |
| 39 | AnimationStart | 0 | p0 anim (base scene +0x78), p1 loop (false), p2 w (true, only if !loop), p3 flag (true) | `CCocosScene::PlayAnimation`; tCustomAnimation stored in map +0x340; skipped at once while fast-forwarding |
| 40 | AnimationStop | 0 | p0 anim | `StopAnimation`, remove from +0x340 |
| 41 | Flag | 5 | p0 str flag, p1 op (0 set, 1 add, 2 mul), p2 int | `unordered_map<string,int>` +0x458 |
| 42 | IfJump | 4 | p0 flag, p1 cmp (0 ==, 1 !=, 2 <, 3 >, 4 <=, 5 >=; flag ∘ p2), p2 int, p3 label | jump like Jump if true; unknown flag → no jump |
| 43 | CharacterHidePosition | 7515 | p0 x (0), p1 y (0), p2 f/30 (T), p3 w (true) | `Hide` every character whose (+0x78,+0x7c) == (p0,p1) |
| 44 | None | 0 | – | no-op |
| 45 | MessageClear | 9011 | – | find or create the window → `MessageWindow::Clear()` |
| 46 | CharacterLayoutChangeSingle | 66 | CharacterShow params | rewrites itself to None and inserts MessageClear, CharacterHide(each char, 7f, w only on the last one (?)), WaitTime 3, CharacterShow(p0..p8) |
| 47 | CharacterLayoutChangeAdd | 20 | CharacterShow params | as 46, but re-shows each existing character at x = −p2 (same csf/name/z) before CharacterShow(p0..p8) |
| 48 | ParticlePlay | 91 | p0 str `(file:anim)`, p1 bool (false), p2 bool (true), p3 x (0), p4 y (0), p5 z (200), p6 name | Particle (type 5) `Show` |
| 49 | ParticleStop | 90 | p0 name, p1 bool (false) | `Particle::Hide(p1)` |
| 50 | MessageAppend | 0 (generated) | p0 str text key, p4 wait-input (true), p5 str, p7 str color (+0x488), p8 bool (false) | `MessageWindow::Append(text,color,0xff000000,w,p8)` or SD `PushMessageID`; backlog `PushLogID`. Does **not** trigger manpu auto-hide |
| 51 | VoicePlay | 127 | p0 str cue, p2 volume (1), p3 (0), p4 pan? (0), p5 w (false), p6 name, p7 (0) | SE object of type 10 `Play` (never loops) |
| 52 | VoiceStop | 59 | p0 fade ms (0), p1 name | `SE::Stop` on type 10 |
| 53 | SelectMenu_ErrorSE | 1 | as 30, p8 = 1-based choice | as SelectMenu; +0x3e0 = p8−1 (the "wrong" choice that plays an error SE (?)) |
| 54 | SeChangeVolume | 10 | p0 name, p1 volume (1), p2 ms (0) | `SE::Volume` |
| 55 | OffscreenFilterShow | 1 | – | `CUIUtility::Show(+0x1d0,true)` |
| 56 | OffscreenFilterHide | 1 | – | same, false |
| 57 | SkinChange | 0 | – | no-op (ignored by the first-command checks) |
| 58 | MessageNameColorChange | 0 | p0, p1 colors | +0x490/+0x494; `SetNameColor` |
| 59 | BacklogChange | 70 | p0 str message key, p1 str speaker | backlog-only entry: `BackLog::PushLogID` (backlog created if needed) |
| 60 | BacklogAppend | 0 (generated) | p0 text, p7 color, p8 bool | `PushLogID` |
| 61 | InsertBlank | 1560 | p0 lines (1.0) | StageDirections (0xc, created if needed) `PushBlankLine` |
| 62 | StageDirectionsInvisible | 89 | p0 frames (10; 0 if SD node +0x1e0 hidden), p1 w (true) | `SD::Hide(p0/30,w)`; does nothing without +0x1e0 |
| 63 | StageDirectionsAppear | 90 | p0 frames (10; 0 if already visible), p1 bool (true), p2 w (true) | `SD::Show`; also hides the message window if +0x110 is visible |
| 64 | MessageDelete | 360 | p0 frames (10; 0 if SD hidden; passed **unscaled**), p1 w (true) | `SD::DeleteMessage` |
| 65 | PlayMovie | 14 | p0 str movie, p1 str cover color, p2 f/30 (1/3 s), p3 str end color | no-op if a Movie (0xd) exists. Otherwise create Movie → `Show`, then a Filter named after the movie (z 800, fade p2), then Hide/Stop every BG/char/sprite/particle/window/telop/filter/SE/BGM/SD/SpriteNew |
| 66 | StageDirectionsCharacterShow | 1099 | p0 str csf (`cp0005_fl01a`), p1 time (0, raw), p2 bool (false) | type 0xe `Show` |
| 67 | StageDirectionsCharacterHide | 349 | p0 bool (false) | `Hide` on type 0xe |
| 68 | SpriteShowNew | 861 | as 13 | SpriteNew (type 0xf) |
| 69 | SpriteHideNew | 803 | as 14 | |
| 70 | SpriteAnimationStartNew | 769 | as 37 | |
| 71 | SpriteAnimationStopNew | 0 | as 38 | |
| 72 | StageDirectionsMessageFlush | 0 | p4 wait-input (true) | if SD is enabled: `MessageFlush()`, +0x2d4 |
| 73 | MovieFilterHide | 12 | p0 f/30 (T), p1 w (true) | the movie's Filter gets `ChangeColor(end color)` then `Hide`; the Movie is unlinked and released |
| 74 | SetEnableSkipButton | 0 | p0 bool (true) | `SetTouchEnable(+0x150)` |
| 75 | SetEnableBackLogButton | 15 | p0 bool (true) | `SetTouchEnable(+0x1f8)` |
| 76 | SetEnableAutoButton | 4 | p0 bool (true) | p0==0 → auto off (+0x3e4=0, +0x3e5/6=0, +0x3e8=0, "Image_auto" hidden); `SetTouchEnable(+0x168)` |
| 77 | SetEnableFastForwardButton | 0 | p0 bool (true) | p0==0 → +0x420=0; `SetTouchEnable(+0x1e8)` |

#### Object types (`obj+0x10`, `CEventScenarioBase::tType`)

1 BackGround, 2 BackLog, 3 Character, 4 Sprite, 5 Particle, 6 MessageWindow, 7 Telop, 8 Filter, 9 SE,
10 Voice (a CEventScenarioSE), 0xb BGM, 0xc StageDirections (novel-style full-screen text), 0xd Movie,
0xe StageDirectionsCharacter, 0xf SpriteNew. (0 = unset, set by the base ctor.)
Object header: `+0 vptr`, `+8 CEventScenario*`, `+0x10 tType`, `+0x14 u8 wait`, `+0x18 std::string name`,
`+0x30 float z`. Vtable offsets: +0x10 Initialize (returns bool), +0x18 Release, +0x20 Run, +0x28 Skip,
+0x30 IsVisibleObject (?), +0x38 IsWait (base: returns +0x14), +0x40 IsInputWait. For MessageWindow,
IsInputWait means text is still typing (+0x68 != +0x6c).
Objects that are created and fail `Show` are deleted. "Find" skips objects queued in the delete list +0x2f8.

#### Per-frame flow (`Run(int)`, state at +0x5c)

- 0 idle. 1: `CMasterManager::Request(+0x40 message file)` and `StringDB::SetAddLoadFileName`, skipped if
  +0x4a4 (no message file). 2: wait for resources and master data. 3: `LoadResource(1, +0x28 script path)`.
  4: wait, then `InitializeFromBuffer`; that sets state 5, and on failure `Exit()` sets state 7. 5: build the base
  `CCocosScene` (+0x78) from +0x230 (`TalkScene/EventBase.csf`), `SetupBaseScene`, load extra `.csf` scenes from
  +0x60 (multimap +0x248) and external `.aif`. 6: wait for resources and `CSoundManager` loading. 7+: running.
- Running frame: `if IsEnd() return` → `CalcWait()` (ends with `CalcAutoModeWait()`) → `CalcCommand()` →
  `UpdateShake()` → every object's `Run()` → delete objects in +0x2f8 → free finished custom animations
  (+0x350) → drop finished sound handles (list +0x380, count +0x390) → `UpdateHitRet()` → `+0x2d0 += dt`
  (time spent on the current command; CalcCommand resets it to 0 after each command).
- **CalcCommand** loops while `cur(+0x2c8) != end(+0x280)`, `state>5`, `!+0x2d4` (wait input), `+0x2d8<=0`
  (wait timer), `!+0x2dc` (select menu), and the shake at +0x328 is not waiting (`+0x18`). It returns if any
  custom animation `IsWait` or any object `IsWait`/`IsInputWait`. It then runs the command: for types 1..77,
  except 50 and 60, it first `ManpuHide`s every character whose +0x168 is 0 (that is what `OnCommandNext` does),
  then calls `CalcCommand_Table[type]`. After that it re-reads +0x2c8 (a Jump may have changed it) and moves it
  forward by 0x30. So any number of non-blocking commands run in one frame.
- **IsEnd**: the same conditions with `cur == end`, plus no pending sounds (+0x390==0) and a
  `CApiCaller` check (vcall +0x6a8 with hash 0x1d00a78c).
- **Skip/fast-forward** (CalcWait): if `CPad::GetNow() & 0xa00` (held skip keys) or +0x420 (fast-forward
  toggle) is set, then +0x318 = 1. Every 0.1 s (timer +0x31c) it: sets the shake to zero duration, skips waiting
  custom animations (`SkipAnimation`), calls `Skip()` on every object, clears +0x2d4 and +0x2d8. Otherwise
  +0x318 = 0. +0x421 mirrors the state for the FF button image (+0x428 on / +0x440 off). Handlers read
  +0x318 to skip animations and SE, and to zero BGM fades.
- **Auto mode** (+0x3e4, from `CUIUtility::GetLocalKVSAutoScenario`; speed +0x3ec =
  `GetEventAutoPageSpeed()*0.2`). When waiting for input with nothing typing and not yet armed (+0x3e5=0):
  +0x3e8 = (text length >20 ? 4.0 : 2.5)·(1+speed). Text length comes from the enabled StageDirections, else
  the MessageWindow; with neither it is 4·(1+speed). +0x3e5 = 1 marks it armed. `CalcAutoModeWait` counts
  +0x3e8 down while the overlays +0x170/+0x1c0/+0x1c8 are hidden. It then waits for the window's (or SD's)
  voice handle to stop (+0x3e6) and sets +0x398 = 1. On the next CalcWait, +0x398 clears +0x2d4, which advances.
- **UpdateHitRet**: shows the "tap to continue" icon (+0x130, or +0x1f0 when SD node +0x1e0 is visible, and
  +0x148) only when +0x2d4 is set, state>5, no object is `IsInputWait`, and the overlays
  +0x170/+0x1c0/+0x1c8 are hidden.

#### CEventScenario fields

| off | type | meaning |
|-----|------|---------|
| +0x28 | string | script file path (LoadResource) |
| +0x40 | string | message/master file name (CMasterManager, StringDB) |
| +0x58 | float | init arg (frame-rate/scale?) passed to InitializeFromBuffer / scene |
| +0x5c | int | Run state 0..7 |
| +0x60 | vector<string> | extra resource files (.csf/.aif) |
| +0x78 | CCocosScene* | base scene (`TalkScene/EventBase.csf`) |
| +0x80 | node* | shake target node (?) |
| +0x110 | node* | message window node (visibility decides fades) |
| +0x128 | node* | node found by tree name at MessageChange/BacklogChange (?) |
| +0x130, +0x148 | node* | hit-ret icons (+0x130 also holds "Image_auto") |
| +0x150/+0x168/+0x1e8/+0x1f8 | node* | Skip / Auto / Fast-forward / Backlog buttons |
| +0x170 | node* | select-menu panel; +0x198[4] its choice labels |
| +0x1c0, +0x1c8 | node* | other overlays (backlog/menu?) that pause auto and hit-ret |
| +0x1d0 | node* | offscreen filter |
| +0x1e0, +0x1f0 | node* | StageDirections root / its hit-ret icon |
| +0x230 | string | base csf path |
| +0x248 | multimap<string,CCocosScene*> | extra scenes |
| +0x260 | string | script name (first `Script` key) |
| +0x278/+0x280/+0x288 | vector<tCommandData> | commands begin/end/cap |
| +0x290 (+0x298 first, +0x2a0 size) | list<string> | string table |
| +0x2c0 | u8 | BGM touched this event (BgmPlay/BgmStop) |
| +0x2c8 | tCommandData* | current command |
| +0x2d0 | float | seconds on current command |
| +0x2d4 | u8 | waiting for input |
| +0x2d8 | float | WaitTime timer (s) |
| +0x2dc | u8 | select menu open |
| +0x2e0 (+0x2e8 first, +0x2f0 size) | list<CEventScenarioBase*> | live objects (new ones are appended) |
| +0x2f8 (+0x300, +0x308) | list<CEventScenarioBase*> | pending delete |
| +0x318 | u8 | skipping (pad 0xa00 or FF) |
| +0x31c | float | skip repeat timer (0.1 s) |
| +0x328, +0x330 | tShakeData* | screen shake (0x2c bytes: time, ampX, ampY, period, offX, offY, u8 wait@0x18, total, acc, base xy) |
| +0x338 | u8 | ShakeStart p5 |
| +0x340..+0x358 | unordered_map<string,tCustomAnimation*> | AnimationStart list (+0x350 first node, +0x358 count) |
| +0x368 | list | per-message extra list built at load (?) |
| +0x380 (+0x390 count) | list<sound handle> | sounds that must finish before IsEnd |
| +0x398 | u8 | auto-advance fired |
| +0x3b8 | int | select choice count; +0x3c0[4] target labels (char*) |
| +0x3e0 | int | SelectMenu_ErrorSE choice (-1 none) |
| +0x3e4/+0x3e5/+0x3e6 | u8 | auto on / auto timer armed / voice finished |
| +0x3e8 | float | auto timer; +0x3ec auto speed |
| +0x3f0, +0x408 / +0x428, +0x440 | string | auto button images / FF button images |
| +0x420, +0x421 | u8 | FF toggle / last skip state |
| +0x458..+0x478 | unordered_map<string,int> | script flags (Flag/IfJump) |
| +0x480 | int | string idx of the BG used by the EventExit fade-out (set at load) |
| +0x484 | float | message speed (0.033) |
| +0x488/+0x48c, +0x490/+0x494 | u32 | text colours, name colours |
| +0x4a4 | u8 | no message file (skip StringDB/master loading) |

#### Native port (`port/src/native/event/event_runtime.cpp`)
- **Native:**
  - `Run`, for states 0, 6 and 7+. The one-time loading states 1-5 run the original code through a trampoline.
  - `IsEnd`, `IsWait`, `CalcWait`, `CalcAutoModeWait`, `CalcCommand`, `OnCommandNext`, `UpdateHitRet`, `UpdateShake`, `tShakeData::Update` and `GetString`.
  - 71 of the 78 command-table entries (`native_handler()`). The rest are still dispatched through the guest `CalcCommand_Table`: TelopShow/Hide/Change and AnimationStart/Stop, which no shipped script uses, and Flag and PlayMovie.
  - The per-frame object virtuals and `tCustomAnimation::IsWait` / `IsEnd`. These are called directly when an object's vtable points at the guest function.
  - `CMessagePrint::Update` (the typewriter text), `MessageWindow::Run` / `GetMessageTextLength`, `BackLog::PushLogID` / `Run` and `Sprite::Run`. Node creation (`CreateLogMessageNode`, `SetupNode`), `UnisonParent` (Cocos layout) and `CMessagePrint::UpdateText` stay guest.
  - `GetSepalateDataString` / `GetSepalateDataColor`, the `"(a:b:c)"` parameter parsers. Quirk: they copy the whole remainder of the string before cutting it at the separator.
- **Still guest code:** scene objects, Cocos nodes, sound, StringDB and resources. They are called through `guest_call` and the objects' vtables:
  - `+0x08` deleting destructor
  - `+0x10` Initialize
  - `+0x18` Release
  - `+0x20` Run
  - `+0x28` Skip
  - `+0x38` IsWait
  - `+0x40` IsInputWait
- **Inlined constructors.** The handlers that create objects contain the classes' inlined constructors, and the port reproduces exactly which fields they write. Several leave bytes unwritten, for example +0xa4..+0xa7 after the 1.0 stored at +0xa0 in Sprite/BG/Character. Objects are appended with `push_back` on the list at +0x2e0. A reused object (found by name) is unlinked first, so it moves to the end of the list.
- **Float compares** follow the guest's FCMP branch conditions: an unordered compare takes `b.le`, `b.lt` and `b.pl`. So NaN inputs take the same paths as in the guest.
  - An invalid operation (0·∞) produces the default NaN, which is `0x7fc00000` on ARM but `0xffc00000` on x86. The shake maths normalises it.
  - `BgmPlay`'s clamp uses AArch64 `FMIN` semantics.
- **Quirks kept:**
  - When `StageDirectionsCharacterShow`'s `Show` fails, it deletes the new object while the object is still in the list.
  - `MessageChange` stops the k-th SE or else the k-th voice for each k, so voices whose index is below the SE count are never stopped.
  - `CharacterHidePosition`, `OnCommandNext` and the speaker-lighting loops rescan the object list from the head for every k (O(n²)).
  - Copied `tCommandData` and `BackLog::LogData` padding carries 3 bytes of the copying function's stack.
- **Tests** (`event_runtime_test.cpp`) run guest and native code in lock-step on a sandbox world. The world holds the scenario, fake objects (fake vtables mixed with real guest virtuals), Cocos nodes, the command array, the string table, the animation hash map and the sound list.
  - Every outside callee is stubbed through `guest_stub.h`, logged and answered by a seeded oracle.
  - Each step compares the sandbox bytes, the call logs and the results.
  - Freed blocks are wiped, and new blocks are pattern-filled, so unwritten bytes count.
  - The suites are `event/interpreter-fuzz` (fuzzed interpreter states), `event/handlers-fuzz` (6000 fuzzed commands), `event/objects`, `event/text-and-backlog`, `event/sepalate-data`, `event/ifjump`, `event/GetString`, and `event/scripts-lockstep`. The last runs all 458 shipped scripts frame by frame through `Run` (about 430,000 frames), alternating auto and manual-tap mode.
  - `SOA_STUB_TRACE=1` prints the stubbed calls as they happen.

### Master data in memory (`CParameterManager`)
- **Loading.** `CStaticTransaction` copies the shipped `basmaster.sqlite3` into an in-memory SQLite DB at boot (see "Offline mode"). Records are *not* loaded up front.
  - A table's record is fetched on first use: its `CSimpleSqliteConnector<Entity>` runs `SELECT * FROM master_x WHERE id=?`, and `Aska::Yayoi::SQLiteDriver::EntityObject::Serialize` turns the row into MessagePack.
  - `CMasterParameterBaseSqlite::DeserializeMsgPack<T>` then builds the element. Each field is a `CParameterPropertyValue<type, N>` / `CParameterPropertyString<N>` matched by the CHash32 of its column name (`NameHash()`, a `CHash32` at property +0x18, hash at +0x20).
  - The non-SQL parameter sets (`pParameterUI`, `pParameterSound`, `pParameterPlayer`, `pParameterDownload`, `pParameterCocosCommonResource`, at manager +0x38..+0x60) come from msgp files through `LoadMsgp`/`Deserialize` (ASON).
- **Keys.** A record's key is the table's `id` column, which is `CHash32(id_label)`. `master_text` rows are keyed by `CHash32("ja_" + message_id)`.
- **Tables.** `CParameterManager` (singleton `Framework::TSingleton<CParameterManager>::m_pInstance`) holds a pointer block at +0x5f8. The `pMasterParameterX()` accessors are `*(*(this+0x5f8)+off)`; `pStringDB()` is `this+0x48`. `tools/gen_parameter_tables.py` lists all 174 accessors with their offsets.
- **`CMasterParameterBaseSqlite_Simple<T>`** (one record per id):
  - +0x08 is the connector. +0x18 is an `unordered_map<u32, shared_ptr<T>>` (bulk records). +0x40 is the same map type for on-demand records, capped at the count at +0x68: when it's exceeded, the map is emptied before the next insert.
  - +0x70 is the `ParameterByQuery` cache, keyed by `MakeCacheKey` = CHash32 of the SQL text concatenated with each `QueryParam` value (0x28-byte params, value `char*` at +0x10), built in a 256-byte buffer. It's capped at +0x98.
  - `pParameterFromHash(id)` checks +0x40, then +0x18. On a miss it loads the row and inserts it into +0x40. It returns a `shared_ptr` copy (one reference taken), or null when there's no row.
- **`CMasterParameterBaseSqlite_Category<T>`** (records grouped, e.g. skills by `group_id`): `pParameterFromHash(key)` returns `shared_ptr<unordered_map<u32, T>>`, checking +0x18, then +0x48.
- **libc++ `unordered_map` layout:** buckets, bucket_count, first node, size, max_load_factor. Nodes are `{next, hash, u32 key, value}`. `std::hash<u32>` is the identity, and the bucket is `h & (n-1)` for power-of-two counts, else `h % n`.
- **Obfuscated strings.** String fields are stored XOR `(N & 0xff)`, where N is the property index. `CParameterPropertyBase<N>::CryptString(dst, src)` clears `dst` and `push_back`s each decoded byte, so the capacity follows libc++ growth.
  - Examples: `master_text.text_value` is `<32>`, `master_global.value` is `<43>` (record +0xe8), and role `category` is `<134>` (+0x1c8).
- **`CParameterUtility`** is a stateless helper namespace over the above:
  - `FindGlobal*WithKey` queries `master_global` by key through `ParameterByQuery`, then decodes the value with `atoi`/`atof`.
  - The `IsOpenX()` / `IsXMaintenance()` feature flags scan a `std::map` at manager +0x74a8. Each node has a u64 key = CHash32(feature name) at +0x20 and a maintenance byte at +0x88. `IsOpen` means not found, or found with the byte clear. The map is empty offline.
  - `tMessage` is a `map<string, string>` cache of StringDB text.
  - `tCharaData` (about 0x2d40 bytes) is the UI's character view. Its getters choose between the own `CPersonInfo` (+0x470), follow/rental info (+0x4c0/+0x510), NPC (+0x460), multiplayer member (+0x40/+0xa1), gacha preview (+0x4d0), and so on. The field map is in `port/src/native/params/parameter_chara.cpp`.
- **Record parsing.** `CParameterElementBase::Deserialize(AMap)` walks the map's string keys. For each key it finds the first property in the element's list (head at element +8, `next` at property +8) whose `NameHash()` matches, and calls that property's `Deserialize(map)`.
  - That call runs `CParameterParser::GetValue<T>(map, NameHash())` → `GetParserValue`, which is a linear scan that CHash32s every key, then converts the value.
  - Conversions:
    - AArch64 `FCVTZ*` saturation for doubles;
    - `bool` accepts only 0 and 1;
    - `u8` from a string goes through `istringstream >> unsigned char`, i.e. the first *character*;
    - a string field takes the value's string pointer for any non-nil type.
  - `AddProperty` appends unless the property is already listed, but it never compares the tail, so re-adding the tail makes a self-loop.
- **`CMasterCache`** (`pParameterUI()+0x90`) memoizes level caps per rarity, limit-break caps per rank, weapon level caps and weapon kinds in `std::map`s (`map<u32,u32>`: key at node+0x1c, value at +0x20).
  - `CMasterCache::LevelMax` is a single 4-byte branch, too short to hook with `SVC; RET`. Its target is hooked instead.
  - Misses (native in `parameter_cache.cpp`): a level cap is `master_role_level_max.rarity = ?` (record +0xd8, 0 without a record), except rarity 7, which adds the open universe boards' levels to rarity 6's (time-dependent; guest); a limit-break cap is `CParameterUtility::CalcMasterRole2LimitBreakMax(rank)`. `tRoleNameCache` (a `map<string, string>`) caches `CUIUtility::GetSystemMessage`.
- **Native port** (`port/src/native/params/parameter*.cpp`, tables generated by `tools/gen_parameter_tables.py`):
  - The lookups and parsing are native: every accessor, the map hits of `pParameterFromHash`, `ParameterByQuery`, `MakeCacheKey` and `CMasterCache`, and field parsing (`ElementBase::Deserialize` with the value/string property `Deserialize`s).
  - Misses fall through to the original guest code (the SQL fetch and record construction) via `NATIVE_FUNCTION_ORIG` trampolines, except for the parts the loader port below covers.

### Master-data loader (the cache miss path)
Native in `port/src/native/params/parameter_loader.cpp` and `parameter_elements.cpp`; types and layouts in `parameter_elements.inc` (`tools/gen_loader_tables.py`) and `parameter_layouts.inc` (dumped by the `param/elements/layout` self-test).
- **Pipeline.** `Simple<T>::pParameterFromHash` miss: `IsLoadable()` (table vtable +0x28), then the connector's `Open` (+0x10), `QueryToMsgPack(mode, key, TSharedArray&, long& size)` (+0x28; mode 0 all rows, 1 by id, 2 by the second key) and `Close` (+0x18). `QueryToMsgPack` locks `CStaticTransaction`'s `CSqliteTransaction::rMutex` (+0x40+400), builds an `EntityObject` on the stack, runs `QueryToResultObject` (+0x20: `BuildQuery` replaces `__TABLE_NAME__` in the connector's static `queries[mode]`, `SQLiteDriver::Find` = `_Prepare` + positional `sqlite3_bind_text` of each `QueryParam` value + `Store`), then `EntityObject::Serialize`.
- **`SQLiteDriver`**: +0x18 `sqlite3*`, +0x20 the one live statement (`_Prepare` finalizes the previous one), +0x10 last bound params, +0x28 in a transaction, +0x30 current `DBAddress`, +0x38 SQL buffer. A failing `_Prepare` *closes the database*.
- **Connectors natively** (`parameter_connector.cpp`, 163 of 170; seven with another `BuildQuery` shape stay guest): the EntityObject is skipped and the driver's statement serialized directly; `_Prepare`, `_Execute`'s binding and `BuildQuery` (buffer grown with `MemoryManager::Realloc` from `Global::m_pNetworkAllocator`, else the available manager) keep the driver's fields as the guest leaves them. The key buffer (connector +0x18, 256 bytes) holds the last `"%u"` key.
- **`EntityObject::Serialize`** (native): an array of one map per row, `{column name: value}`; `INTEGER` via `sqlite3_value_int` (truncated to 32 bits), `FLOAT` as a double, `TEXT`/`BLOB` via `snprintf("%s")` (cut at the first NUL), `NULL` left nil. Column names come from the `THashMap<const char*, int>` `Store` fills (duplicate names: the last index wins and the others are uninitialised). No rows or columns: size -0x3a4 and a null array.
- **`DeserializeMsgPack<T>`** (native for 149 types): the ASON is `Init(max(size * 4, 0x2000), multibyte)`. With a map: `rehash(ceil(count / max_load))`, then per row: stop at the first row without the key column (`this` vtable +0x18); build a temporary (`T()`, `Initialize()`, `ElementBase::Deserialize`); key = `CHash32` of the key column's multibyte text, else `GetValueUInt` (ints: low 32 bits, doubles `fcvtzu`, else 0); insert a copy unless the key exists. Without a map, `single->Initialize()` / `Deserialize()` (vtable +0 / +8) of the first row only. A map root (one row) is deserialized before its key is looked up.
- **`SetStoreAllCacheSize`** (6 tables: Item, Rank, Role, Factor, Person, Talent) loads the whole table, builds and destroys every record just to store the record count as the on-demand cache limit (+0x68). Natively only the key column of the rows is read (no MessagePack either); in the smoke session that took the loader from 4.4% to 1.0% of busy time (mostly SQLite now: the master DB has no indexes, so every `WHERE id=?` scans the table).
- **Elements**: `CParameterElementBase` (vtable, list head) followed by back-to-back properties: `CParameterPropertyValue<T,N>` (0x30 bytes: vtable, next, u8 flag, `CHash32` {vtable, hash}, value at +0x28) or `CParameterPropertyString<N>` (0x40, string at +0x28). `T()` sets vtables and zeroes list/flag/hash/strings but not values; `Initialize()` sets each property's hash, flag 1 and default (a few non-zero: floats like 100.0, -1, 9) and `AddProperty`s it (list order ≠ member order). All 157 types fit this. Four (DeepSpaceBonus, Home3D, EventWeekly, Factor) have a property `Initialize()` never adds (a game bug): it keeps `T()`'s state, hash 0, flag 0 and an uninitialised value.
- **Copy quirk**: `T(const T&)` and `operator=` copy the list pointers verbatim, so every cached record's property list points into the temporary it was copied from (a dead stack object for `DeserializeMsgPack` records). Nothing walks those lists afterwards. `operator=` keeps the destination's vtables; strings use libc++ copy (allocation `round_up(n + 1, 16)`) vs assign (`__grow_by_and_replace`: capacity `recommend(max(n, 2 * old))`).
- **`ParameterByQuery(sql, QueryParam*, n)` miss**: key = `MakeCacheKey`; the connector's `QueryToMsgPack(sql, …)` (+0x30); the first row goes into a `new(nothrow) T` (`T()` then single-record `DeserializeMsgPack`), owned by a `__shared_ptr_pointer<T*, default_delete>`, then `InsertCustomizeCache(key, p)`: the query cache (+0x70) is emptied once its size reaches the limit (+0x98), and p is added unless the key is present. Quirk: nothing resets the values here, so a property the row doesn't set (missing column, or text that doesn't convert) keeps allocator garbage.
- **`Category<T>::pParameterFromHash` miss**: group query (mode 2); the on-demand map (+0x18, limit +0x40) gets a `make_shared<unordered_map<u32, T>>` unless the group is there, and the result is that entry with every loaded record copied in. Three of the five Category tables (AI, Signal, AttackAction: battle data) are missing from the offline DB, and querying a missing table makes `_Prepare` close the master DB.
- **`pParameterFromHash` miss** (Simple): empty the on-demand map (+0x40) if its size exceeds the limit (+0x68); `DeserializeMsgPack` into a temporary map; each record becomes a `__shared_ptr_emplace<T, ParameterAllocator>` (`T()`, `operator=`) inserted unless its key exists; the answer is the on-demand map's entry.
- **`ParameterFromIdList(ids, map&, column)`**: `SELECT * FROM <table> WHERE <column, else the key column> IN (<non-zero ids, sorted, unique>)` through `ParameterByQuery(sql, map&)`; nothing when no non-zero id remains. `StringDB::GetList` does the same for texts with `CHash32("ja_" + id)`, and with an empty list builds `IN ()`, whose prepare fails (and closes the DB).
- **`DeserializeParameter(map&, AArray*)`** (msgp-backed tables, e.g. StringDB at boot): per row with a key (text: `CHash32` of its multibyte copy, skipped when empty; else `GetValueUInt`, skipped when it fails), an existing record is deserialized again from the row; a new one is `make_shared`, inserted, then `Initialize()`d and deserialized through its vtable.
- **Destructors** leave each property's vtable as `CParameterPropertyBase<N>`'s, and a derived element (`WorldMapMission` from `Mission`) ends in its base's destructor, leaving the base's vtable.

### UI scene graph (`Framework::Cocos`)

The game's own cocos2d-x-like retained-mode UI (`port/src/native/ui/cocos/cocos_*.cpp`). Layouts are
Cocos Studio CSB/CSF files; `CCocosObjectFactory::Instantiate(type)` maps the Cocos Studio object
type to a class (sizes from its `operator new`): `SingleNodeObjectData` → `CCocosNode` (0x230),
`SpriteObjectData` → `CCocosSprite` (0x260), `ImageViewObjectData` → `CCocosImage` (0x280),
`ButtonObjectData` → `CCocosButton` (0x2d0), `PanelObjectData` → `CCocosPanel` (0x2d0),
`TextObjectData` → `CCocosLabel` (0x290), `TextAtlasObjectData` → `CCocosAtlasLabel` (0x290),
`LoadingBarObjectData` → `CCocosProgressBar` (0x280), `SliderObjectData` / `CheckBoxObjectData` /
`TextFieldObjectData` (0x320), `ParticleObjectData` (0x470), `ListView` (0x450), `PageView` (0x3f0),
`ScrollView` (0x3a0). Image, Button, Panel and AtlasLabel derive from Sprite. `CCocosScene`
(~0x340) is the root node of one layout; `CCocosDirector` (singleton
`TSingleton<CCocosDirector>::m_pInstance`) holds `vector<CCocosScene*>` at +0x08 and each frame
`SceneProgress(dt)` runs `CCocosScene::Progress` on every scene.

- **Tree** (`THierarchy<CCocosNode>`): intrusive first-child / next-sibling list. +0x08 parent,
  +0x10 next sibling, +0x18 first child, +0x20 cleared on detach. `AddChild` appends at the end
  of the child list (draw order = list order; the z-order is resolved later by
  `CCocosDrawPriority`). `THierarchy::DetachSelf` hands the node's children to its parent.
- **CCocosNode fields**: +0x00 vtable, +0x28 name (`std::string`, CSTLAllocator), +0x84 anchor,
  +0x8c position, +0x94 content size, +0x9c scale, +0xa4 rotation X/Y (degrees), +0xac layout bits,
  +0xb4 tag, +0xb8 action tag, +0xbc opacity (float), +0xc0 colour (u32), +0xcc dirty flags,
  +0xd5 cached visibility, +0xd6/+0xd7 flip, +0xd8 state (bit0 visible, bit1 touchable, bit5 has
  stacked renderer), +0xe0 touch listener, +0xe8 stacked renderer, +0xf0/+0x130 local matrices
  (layout / plain), +0x170/+0x1b0 world matrices, +0x228 cached colour, +0x22c cached opacity.
- **Dirty flags** (+0xcc): 1/2 local matrix, 4/5 world matrix, 0x400 colour, 0x800 opacity,
  0x1000 visibility, 0x4000 colour/opacity changed, 0x10000 re-run PreDrawSelf, 0x80000 label
  text changed, 0x800000 re-check external image; on the root: 0x4000000 / 0x8000000 draw
  priorities must be recomputed, 0x20000000 flags must be propagated before the next query,
  0x10000000 / 0x40000000 propagation in progress. `_PropagateFlag(f)` ORs `f` into a node and
  its later siblings and passes `flags & 0x117ddf` down. The `*Hierarchy()` getters
  (visible = own bit AND parent's, opacity = product, colour = bitwise AND) are cached and
  recomputed only when their dirty bit is set.
- **Search**: `SearchByName` searches the node, its subtree and then its *later siblings* (the
  recursion follows the sibling link); `SearchByTreeName("a/b/c")` finds `a` anywhere below the
  node, then `b/c` below that. `ActionBy*` call a `std::function<void(CCocosNode*)>` on matches.
- **Frame**: `CCocosScene::Progress` → `_PreComputeSelf` (fit to the projector rect),
  timeline animation, renderer updates, then `_DrawHierarchy`: propagate flags,
  `PreDrawHierarchy` (virtual `PreDrawSelf`, slot 0x40, on visible nodes), recompute draw
  priorities when the root says so (`CalcCocosDrawPriority`), collect blend states
  (`GetRenderState_DrawSelf`, slot 0x88), sort them (`tSortBlending`), bind renderers, and call
  `DrawSelf` (slot 0x48) on every node in draw order.
- **Draw order** (`CalcCocosDrawPriority`, run when the root has bit 27): nodes are bucketed
  per render layer (+0xd4, signed) and draw mode (normal / key 0xf0000000 / external image,
  doubled by state bit 3), with clipping marks for clipping nodes (their subtree is ordered
  recursively and closed by a "clipping end" entry, kind 1); layers are emitted in ascending
  order, modes in the order given by the node's eDrawPrioMode nibbles (+0xd0; bit 31 = draw
  after everything, bit 30 = start a new batch). Each emitted node gets a priority (+0xc8)
  from a running counter (reset by +0xc4 >= 0, bumped for groups).
- **Blend states / renderers**: `GetBlendingResult` (slot 0x80) gives up to three blend keys
  per node (0xf0000000 text, 0xf0000001 panel colour, 0xf0000002 panel image / clipping, else
  the sprite's blend mode +0x258); `GetRenderState_DrawSelf` (slot 0x88) appends 32-byte
  tRenderState {node, renderer, key, count, kind, no-merge, bound} (consecutive equal states
  merge); `_DrawHierarchy` sorts them, finds or creates a renderer per state
  (`_pSearchRendererLight`) and stores it in the node (+0xe8, and +0x298/+0x2a0 for nodes
  with three renderers, +0xae bit 0); `DrawSelf` (slot 0x48) then fills the renderer.
- **Timeline animation** (scene+0x2c0): key frames per frame index; a key frame applies to
  every node with its action tag (+0xb8), found by walking the whole scene each time.

- **DrawSelf** (slot 0x48) returns 0 (nothing), 1 (the renderer still holds this node's
  quads: only the renderer's quad counter +0x78c advances, by the number of quads) or 5 (quads
  rebuilt). The node remembers the renderer's (counter +0x78c, generation +0x798) pair at +0x220
  (Panel background: +0x290; Label: (generation, PutCounter, CharCount<<48)) and rebuilds when it
  differs or when flags 0x2000/0x4000/0x8000 are set. A quad is a `tSpriteParameter_Quad`
  (vtable, +0x10/+0x14/+0x18 floats, then four {x, y, u, v, colour} vertices at +0x1c); vertex
  positions go through rows 0-1 of the world matrix as (x, y, 0, 1), the colour is
  `ColorHierarchy | (u32)(OpacityHierarchy*255) << 24`. Image 9-slice (+0x270, insets
  +0x260..+0x26c) emits nine quads; Sprite multiplies its texture matrix (scale +0x248/+0x24c,
  translation +0x250/+0x254) into the world matrix; AtlasLabel emits one quad per character,
  glyph index = char - '.', converted *unsigned* (a character below '.' gives a huge U offset:
  quirk). Panel draws its image at the image's own size centred by temporarily setting anchor
  0.5 / position / size and restoring them and the cached world matrix / basic rect afterwards.
- **Touch input**: `CCocosDirector::InputProgress` turns the `CTouchPanel` drag state (+0x265c:
  state 0-3, deltas, position, id; +0x46 cancel request) into the director's single
  `CCocosTouch` (+0x60) and dispatches a `CCocosEventTouch` (code 0 began, 1 moved, 2 ended,
  3 cancelled, 4 cancel-all). `DispatchTouchEvent` walks the listener vector in order; a
  listener (0x390 bytes: +0x60 enabled, +0x68 node, +0x70 paused, +0x71 registered, 15
  std::functions with `__f_` at +0xa0 + 0x30k, +0x350 claimed touches, +0x368 swallow) claims
  a touch when its began callback returns true; later codes only reach claiming listeners.
  `CCocosNode::SetEventListenerTouchCallback` fills the first five callbacks with the node's
  lambdas (hit test, button state, tap / hold / flick timing through `Aska::Global::GetCPUTime`,
  SE), which call the user callbacks in slots 5-14 (set by `CUIUtility::SetTapEvent` & co.).
- **Reaching a story scene** in a live run (all-characters save, 729x1296): from home
  `tap:90:1080` (Mission), `tap:364:475` (Episode 3), `tap:364:446` (chapter 6), `tap:364:446`
  (6-18), `tap:515:712` (start); after ~15 s the scene runs, `tap:364:1000` advances,
  `tap:614:44` toggles the backlog.

### ASON (MessagePack) in detail
Native in `port/src/native/params/ason.cpp`; layouts in `ason.h`.
- **`Aska::ASON` object** (0x90 bytes): vtable; a 0x200-byte scratch area carved from the first work buffer (+0x08 ptr, +0x10 size, +0x18 used); a `TDynamicArray<WorkBufferContext>` at +0x20 (vtable, begin, end, capacity); +0x48 current work buffer, +0x50 sum of all buffer sizes, +0x58 u16 current buffer index; the root `AValue` at +0x60; +0x80 last status (s64); +0x88 multibyte flag, +0x89 multi-root flag, +0x8a initialised.
- **Work buffers** (`WorkBufferContext`, 0x20 bytes: ptr, size, used, owned): a bump allocator. `Malloc(n)` rounds up to 4 bytes; when the current buffer is full it allocates a new one (`operator new[]`) as large as all previous buffers together, so capacity doubles. `Init(size, mb)` needs size ≥ 0x2000 and allocates the first buffer; `Init(buf, size, mb)` uses the caller's. Resetting (`ClearRoot`, `AllFree`, `ClearWorkBuffer`, each `Deserialize`) frees all buffers but the first, rewinds it and carves the scratch area again.
- **`AValue` fields beyond the basic ones**: string +0x10 is a NUL-terminated copy made only in multibyte mode, +0x1c/+0x1e are the buffer indexes of the +8/+0x10 allocations (0xffff = none); arrays/maps/bin keep a buffer index at +0x14; ext: +0x14 type byte, +0x16 index. Strings, bin and ext **point into the source buffer**, which must outlive the tree. `AMap::Get_(const char*)` compares against the multibyte copies, so name lookups only work on multibyte ASONs; `Get_(const AValue*)` compares by type and value (containers by identity; a double key matches any double entry when either is NaN).
- **Unpacker**: msgpack-c's resumable `template_execute` (cs / trail / top, 32-level stack, context 0xa30 bytes: current value, state, 32 × {container, remaining count, map-key/value state, buffer index, pending key}). `UnpackMessagePack<false>` only counts (it still allocates containers); `DeserializeBinary` first counts the top-level objects, resets the buffers, then builds. Several top-level objects become a root array (multi-root flag set). The return value is the number of bytes consumed.
- **Quirks** (reproduced by the port):
  - an empty fixstr points at the start of the most recently read length/value field in the same call (msgpack-c's `n`), or NULL; an empty str8/16/32 or bin points at its own length field;
  - the unpacker reuses one `AValue` for every value, and scalars only overwrite part of it: nil only the type, bool only the low byte of +8, integers/floats +0 and +8. The remaining bytes are left over from the previous value (often a pointer);
  - strings/bin/ext record the buffer index saved for stack level `top` (0 unless a container was opened at that depth earlier in the same call; for multi-root input every level starts at the current index). At 32 open containers this reads one entry past the stack;
  - input that ends inside an open container "finishes": the root becomes the last value parsed and the reported size is one byte more than the input. Input that ends inside a field returns what was consumed so far, and `Deserialize` then starts a new top-level object there;
  - container slots are zeroed except bytes +4 (and +0x24 in map entries);
  - `PackMessagePack` checks a string/bin/ext payload against the space left before its header, so it can write up to 5 bytes past the buffer.

### SLZ compressed files
Native in `port/src/native/engine/slz.cpp` (the codecs run on host zlib / libzstd).
- **Header** (`Aska::COMPRESSHEADER`, 0x20 bytes): `"SLZ"` or `"SLE"`, u8 codec, u8 +4, u8 +5 (AMF: number of blocks), u16 0x25 at +6, s32 compressed size at +8, s32 decompressed size at +0xc, u32 +0x10 (AMF: offset of the AskaFile in the output), u32 offset of the payload at +0x14, u8 flags at +0x18 (bit 0: AMF container, whose further block headers follow at +0x20), u8 chunk size in KiB at +0x19 (0 = a single chunk), u32 offset of the next header in a chain at +0x1c (0 = last).
- **Chunks**: each decompresses to chunk-size bytes (the last to the rest). Codec 0 chunks are stored back to back; the other codecs prefix each chunk with a little-endian u16 compressed size, where 0 means stored raw.
- **Codecs**: 0 stored, 1/2/3 Aska's own LZ variants, 5 raw deflate (`AskaUncompressGzip`, windowBits −15; the decompressed size is also passed as the input size), 7 zstd (`_DecodeMain<*,7>`: streamed above 64 KiB, with a one-shot fallback). The shipped assets use only 5 (643 files: `.aif` textures, `.csf` Cocos scenes, some `.asf`) and 7 (~3,200 files). Every file has 64 KiB chunks and a single header; about 60% are AMF containers.
- **SLE**: the payload is obfuscated with a 16-byte key at library offset 0x2bc9139: `plain[i] = (enc[i] − k) ^ key[i & 15]` with `k = 3, 6, 9, …` (mod 256). It is decrypted in place on the first decode, which also rewrites the tag to `"SLZ"`. `DecodeKey` does the same with a caller's key.
- **Quirks**: `DecodeMain` returns false only for a bad tag / magic or codecs 4, 6 and above 7; a failing chunk stops decoding but still returns true. In-place decoding (compressed data inside the output buffer) goes through a static 64 KiB scratch buffer and fails for larger chunks.

### Image assets and gacha banners
Converter: `tools/aif2png/` (C++, standalone; `build.sh`) and `tools/extract_banners.py`, which writes the gacha art of the 3.7.0 download to `work/gacha-banners/` with an `index.html`. With `--all-images` it also converts every `Image/` asset, into `all/`.

**Where the images are.**
- All 2D images are `Image/etc2/<name>.aif`: 7,029 in the 3.7.0 download and 2,433 in the APK's `assetpack/Image/etc2`. Names are plain, with no hashing. The game loads them as `"Image/" + name + ".aif"`.
- `version.bin` lists them under `assets` with `encType 1` (ADLD XOR).
- The download's `I/` (234 entries) and `B/` are empty placeholders: size 0 in `version.bin`, and no files on disk.
- The APK has no gacha banners: every banner and pickup image comes from the download.
- The gacha screens' own art is the texture atlas embedded in the Cocos scenes `UI/etc2/gacha_*.csf` and `Gacha_Insert.csf`.

**File layers.**
1. **ADLD.** The XOR key is the `"%x"` of `CHash32("Image/etc2/<name>.aif")`.
2. **SLZ.** Present on about 94% of files: codec 7 (zstd) or 5 (deflate), 64 KiB chunks. The ~430 JPEG files are stored uncompressed.
   - **Pitfall:** each zstd chunk's u16 size counts one pad byte after the frame, so `ZSTD_decompress(dst, out, src, n)` fails with "Src size is incorrect".
   - The game passes the output size as the input size and zstd stops at the frame end. Decode with the size from `ZSTD_findFrameCompressedSize`.
3. **AIF container.** Tags are reversed four-character codes, 16-byte aligned:
   - `' FIA'` header (+4 header size);
   - `' FRa'`, `' DRD'`;
   - then `' FMA'`, the AMF chunk (+4 chunk size). It holds `head`, `buff` and `addr` chunks, and it **ends with the data buffer**. The buffer starts at AMF start + AMF size − `buff`+0x10 (buffer size).
   - Each `addr` chunk names a block of the buffer: GUID +0x10, size +0x20, offset +0x28.
4. **Image header: the `'Xgmi'` chunk** (bytes `58 67 6d 69`, 0x70 bytes).
   - +0x20 u8 format, +0x22 u8 flags (3 on JPEGs);
   - +0x28 u16 width, +0x2a u16 height;
   - +0x2c u16 mip levels (always 1), +0x2e u16 bits per pixel;
   - +0x30 u16 bytes per block, +0x32 u16 blocks across, +0x34 u16 blocks down, +0x38 u32 row pitch;
   - +0x40 the GUID of its `addr` block, which is where the pixels are.
   
   ETC images keep the `Xgmi` inside the buffer, after a nested 0x80-byte `' FIA'`. JPEG images have it in the file header.

**Formats** (+0x20). Seen in the 3.7.0 download:

| Code | Format | Files | Used for |
|---|---|---|---|
| 49 | ETC2 RGBA8: 16-byte blocks, an EAC alpha block then an ETC2 colour block | 6,260 | Most images: character art, banners |
| 48 | ETC2 RGB8 punch-through alpha1 (8-byte blocks, bit 33 = opaque) | 199 | Many `*_PU_*` pickup panels |
| 47 | ETC2 RGB8 (ETC1-compatible) | 139 | Opaque icons and backgrounds |
| 39 | Baseline JPEG, no alpha | 431 | Background images such as `00_bm*`, `bbg*` and `mbg*` |

- 48 and 49 were confirmed by decoding: clean transparent borders, with no block artefacts in T/H/planar blocks.
- Rows are top-down, the colours are straight RGBA (not premultiplied), and there is no swizzle.

**Gacha ↔ image links** (master data):
- `master_gacha.banner_id` is a `master_banner.id_label`. That row's `image` is the list banner (e.g. `20210610_chara_004`) and its `url` the webview details page.
- `master_gacha.image1..4` are the pickup panels of older gachas (2017-18, `pickup_img_*`).
- `master_gacha_image` holds the pickup panels per gacha:
  - `view_index` gives the order;
  - `content_type` + `content_id_label` give the featured role or weapon: 2 = role, 0 and 1 = weapon items (their exact difference is not established), null = the main panel.
- In the 3.7.0 data:
  - 1,341 of the 2,281 gachas have at least one image;
  - 537 of the 1,808 referenced images exist. The server had already deleted the rest; the index lists them by name.
  - 19 more gacha-art files (`banner_gacha_*`, `ticketgacha_*`, ...) are not referenced by any row.
- `master_gacha_pickup` groups featured roles (`pickup_group_id`) and has no images.
- `master_banner_replace` swaps home-banner images by date.

### Shader cache compression (`Aska::ShaderCompression`)
The AHSL shader disk cache compresses shader text with `CompressLZwordDic` (native in `port/src/native/render/shader_compression.cpp`). It is Okumura's LZSS over 16-bit big-endian words, with a 4096-word ring whose initial content is a caller-supplied 8 KiB dictionary, and matches of 2 to 17 words.
- **Output**: groups of a big-endian u16 flag word followed by 16 codes, consumed LSB first. Flag 1 means a literal word (its two bytes as in the input). Flag 0 means a big-endian match word `(length − 2) << 12 | distance`, with the distance in words (1..4095). Distance 0 ends the stream. The compressor returns the output size in bytes.
- **Decoding**: matches that reach before the start of the output read the dictionary, which the decoder treats as the 4096 words immediately preceding the output.
- **Quirks**: the compressor reads one word past the end of odd-sized or tiny inputs. Near the end of the input a match is clamped when `consumed + length − 16 ≥ total words`.

### ACSV (CSV tables)
Native in `port/src/native/engine/acsv.cpp`. `DeserializeText` makes three passes over the text with one scanner:
1. count the columns of the first line;
2. infer each column's type from all rows;
3. parse every field into a 16-byte value.
- **Syntax**: fields are separated by the separator byte (+0x54, default `,`). Rows end with `\n`, `\r` or `\r\n`. A field starting with `"` runs to a closing `"` that is followed by the separator or a line break; `""` escapes a quote.
- **Field text**: unquoted fields are trimmed of spaces. Quoted fields are passed whole, quotes included.
- **Types**: 0 none, 1 bool, 2/3 s8/u8, 4/5 s16/u16, 6/7 s32/u32, 8/9 s64/u64, 10 float, 11 double, 12 string (pointer + length into the text).
- **Type inference** (`UnpackTextType`): "TRUE"/"FALSE" give bool; `0x…` gives a hex integer; a dot gives float (more than 7 digits: double); a leading `-` gives a signed type; anything else gives string. Integer columns widen to fit the largest magnitude seen in the column (the `PriorityContext`). A quoted field forces string. Otherwise the larger type code wins.
- **Values**: integers are parsed with `atoi` / `strtol` / `strtoul` (base 16 after `0x`), floats with `atof`. With the blank extension (flag bit 0), empty fields set a bit in a `TBitArray`.
- **Memory**: a work buffer from `Init` holds three slots (types, blank bits, values). A slot that doesn't fit falls back to `operator new[]`.
- **Quirks**:
  - with m leading spaces, the trailing-space trim starts m bytes past the end of the field;
  - the last line is parsed only if it has at least two fields, so a lone final field without a newline is dropped;
  - a one-character bool is always false;
  - `Init` leaks the new buffer when it fails the alignment check.

### Models and animation (Aska AFF files; `port/src/native/models/models*.cpp`)
- **Files.** `.asf` = scene (node tree, mesh objects, materials, texture references), `.aaf` = animation (controllers + keyframes), `.acf` = collision shapes. On disk they are ADLD-encrypted (XOR key from `CHash32` of the path relative to `builtin_data/`, e.g. `"MapHome/bh01_01.aaf"`); large ones are additionally SLZ v7 (zstd frames from byte 34).
- **AFF container.** Every file starts with a 16-byte file header: u32 tag, u32 file size, two u32s (ASF: the size again). Tags are multi-character constants stored little-endian, so they read backwards in a hex dump: `" FAA"` = `'AAF '`, `" FSA"` = `'ASF '`, `" FCA"` = `'ACF '`.
  - At +0x10 comes an `'aRF '` resource chunk (`Aska::ArfHandler::Attach`, `AFF::AskaResource`): u32 size, u32 0, u32 offset (from the chunk) of the type-specific header; then u16 1, u16 1, the type tag again with a u32 version (`AAF ` 0x2e, `ACF ` 7), a platform tag `'ANY '`, and a 16-byte block that is identical in every file.
  - Inside ASF files, chunks and names use the same reversed 4-character tags (`'DRD '`, `'AIF '`, `'AMF '`, `head`, `idxl`, `mess`, ...) and resource names carry an `R:` prefix (`R:m_W10LaShape`, `R:t_Basic02_Alb2`).
- **AAF header** (`AafHeader`, checked by `AafHandler::AttachAaf`): u16 at +0 is 0x2e; +4 u16 number of animated targets (nodes); +6, +8, +0xa u16 controller counts of three kinds (their sum is the controller total; the home background `bh01_01.aaf` has 23 targets / 45 controllers); +0xe u16 count of 8-byte extra entries; bit 16 of the first word selects frame-sorted evaluation (`AafHandler` flag 0x40); +0x20 u32 offset of the target table.
  - Target entry: flags byte (bit 2: short entry, controllers start at +0xc, else +0x28), u16 controller count at +2.
  - `AafControllerHeader`: kind byte at +0 (what is animated: translate X/Y/Z/XYZ, rotate XYZ / quaternion, scale, UV, colour element, visibility, link, aim constraint, ...), +1 sub-kind, +2 u16 size, +5 flags (bit 7: compressed track), +6 u16 offset of its `AafKeyframeHeader`.
  - `AafKeyframeHeader` (uncompressed tracks, read by `TAafNormalController::Attach` / `CalcValueSub`): +4 keyed flag (0: a single constant value at +8), +8 pre-infinity mode, +9 post-infinity mode, +0xc start frame, +0x10 end frame, +0x14 key count, +0x18 key times (floats), then the control points. `Normal` (scalar) points are {value, in-tangent, out-tangent}; `Vector` and `Quaternion` points have the same shape per component; `_Linear` / `_Step` variants drop the tangents.
  - Infinity modes (outside [start, end]): 0 hold the first/last key, 1 linear extrapolation (`CalcValueConstant` at the end keys), 2 cycle, 3 cycle with offset (each cycle adds last−first; tracks using it get the `TAafFrameSortController<..., true, ...>` instantiations), 4 oscillate (ping-pong).
  - Interpolation between keys k0 and k1 with s = (t − t0) / (t1 − t0): cubic Hermite `v = p0·(s−1)²(2s+1) + p1·s²(3−2s) + out0·s(s−1)² + in1·s²(s−1)` (the tangents are stored pre-scaled by the key interval). Quaternion tracks slerp (`Quaternion::Slerp`).
  - Compressed tracks (`_U16`, `_U24`, `_U32EX` control points) keep the keyframe header at +0x48 of the controller and decode keys on demand into a per-handler control buffer (`TAafControllerCompressionLayer::SetControlBuffer`, `SetControlPoints`); `_U32EX` quaternions pack three components in 32 bits (`AafKeyframeData_Quaternion_Linear_U32EX::GetValue` rebuilds w from 1 − x² − y² − z²).
- **Controllers.** `TAafNormalController<AafType<ControlPoint, frameSort, ?, n>>` evaluates a track (`CalcValue` = `CalcValueSub(t, false)`; state: current key index at +0x40, the two current control-point pointers at +0x20/+0x28 with their times at +0x10/+0x14, key-interval length at +0x18). Target classes (`TAafTranslateXController<...>`, `TAafRotateQuaternionController<...>`, ...) write the value into the node: `SetValueToTarget` refreshes the node's hierarchy if needed, then position at node+0x80, rotation at +0x90; `BlendValueToTarget` lerps / slerps with a weight.
  - Evaluation per frame: `AafBlendManager::CalcValues` posts one message per animation to the dispatcher workers; `_CalcNotify::Handler` calls `AafHandler::SetValues(frame)` (first animation) or `BlendValues(frame, w)`; both run `AafCalcCommonFunctor::CalcAndSetSubFunctor`, which sorts controllers into in-range / before / after lists (`CheckCache`) and calls `CalcValue` + `SetValueToTarget` (or `BlendValueToTarget`) through the vtable (slots +0x60, +0x168, +0x188; +0x148 `CalcValueConstant` for constant tracks).
  - The template family has ~15k instantiations; many share identical machine code. The per-frame methods (`CalcValue`, `CalcValueSub`, `CalcValueConstant`, `CalcValueComplement`, `CalcValueByLinearAt{Pre,Post}OutOfRange`, `Set/Add/BlendValue{OfDirectAddr,ToTarget}`, `SetControlPoints`) of all ~4,700 instantiations come in 312 distinct code shapes.
- **Controller object layout** (all `TAafController`s): +0x08 range state (-1 before, 0 inside, 1 after the keyed range, or the cycle count), +0x0d `cur` (which of the two key slots holds the earlier key), +0x10/+0x14 slot times, +0x18 interval length (`UpdateCurrentRange`, vtable +0x1c8), +0x20/+0x28 slot control points, +0x30 complement points (a pointer; inline when the `AafType` is frame-sorted). Then the keyframe header pointer and current key index: +0x38/+0x40 (frame-sorted +0x48/+0x50); compressed tracks keep the dequantisation scale at +0x38 (+0x48) and the header / key at +0x48/+0x50 (frame-sorted: after an inline control buffer for the two keys, +0x50 + 2 * point size). `_U16` values are int16, `_U24` big-endian signed 24-bit, each / scale. Moving to interval i reuses a slot that already holds key i or i+1 (the roles swap via `cur`). Infinity modes 2-4 use floor (`frintm` / `fcvtms`); oscillate runs odd cycles backwards as (2*start + len) - t.
  - Guest quirks (kept in `port/src/native/models/models_anim.cpp`): `TAafRotateXController::BlendValueOfDirectAddr` multiplies where it should add (angle = (1-w)*a*v*w; Y and Z are right); `TAafTranslateXYZ` / `TAafScaleXYZ` `BlendValueOfDirectAddr` write the weighted value back into the source; linear extrapolation after the track (`CalcValueByLinearAtPostOutOfRange`, _Linear keys) starts from the earlier key; quaternion tracks use one function for pre and post extrapolation; Vector _Linear interpolation leaves w untouched; the Vector4 cycle offset adds last.w instead of last.w - first.w; `TAafController<Vector4>::AddValueToTarget` is empty; the Vector4 complement's w is the sum of the Hermite basis; Int tracks in cycle-offset mode add the track change once, whatever the cycle count; `TAafVectorElement` / `TAafUVElement` / `TAafDiffuse` / `TAafU8-U32` targets read-modify-write through IAnimatable (UV keeps its pair in the controller, U8-U32 round half away from zero).
- **Node transform** (`HierarchicalObject`, container base at +0x30): world matrix +0x40, position +0x80, rotation quaternion +0x90, scale +0xa0, position offset +0xb0, pivot terms +0xd0 / +0xe0, flags +0x128 (bit 0: hierarchy up to date; setters call `UpdateHierarchically` first when it is clear). `HierarchicalObjectContainer::MakeMatrix` builds rows r_i = (0,0,0,1)*(pos+offset)_i + sum_k axis_k * R[i][k], where R is the rotation matrix from the quaternion (1-2y²-2z², 2xy-2wz, ...), axis_k = scale_k * e_k with the pivot correction (A_k - B_k*scale_k) in w, row 3 = (0,0,0,1); then world = local x parent world (row by row, in that summation order), children list: first child at container+0xc8, siblings ring through +0xd8. `JointObject::MakeMatrix` uses the parent's pivot (+0x70 of the parent container) only when the parent owner has flag 0x195 bit 0 and the joint's +0x198 is set. Packed quaternion keys (`_U32EX` 4 bytes, `_U48EX` 8, `_U48EX2` 6 widened to the 8-byte layout) are decoded by `AafKeyframeData_Quaternion_Linear_U32EX/U48EX::GetValue`.
- **AafBlendManager** (per model): +0x08 open flag, +0x0c running weight sum, +0x28 slot count, +0x30 slots used, +0x38 slots (0x30 bytes each: +0 play frame, +4 normalised weight, +8 weight, +0x10 AafHandler*, +0x18 custom evaluator). `NormalizeWeights` fails while a handler lacks flag 2 (ready) and uses 1/sum only when sum > 1e-6. `_CalcNotify::Handler(slot)`: custom evaluator if any, else (weight > 0) handler flag |= 0x20, first slot `SetValues(frame)`, later ones `BlendValues(frame, w / (sum + w))`, then sum += w. The `AafHandler` entry points only run `AafCalcCommonFunctor::CalcAndSetSubFunctor<AafCalcType<0, 0, speed, 0, loop>, add, blend, 0>` if flag 2 is set (weight -1 when not blending).
- **Bone matrices.** `HierarchicalObjectContainer::MakeMatrix` / `IterateMakeMatrix` / `Function_UpdateHierarchicallyByUsingStack<256>` walk the node tree; `JointObject::MakeMatrix` builds each joint's matrix with `MatrixCalcFunc(out, scale, rot, jointOrient, translate, pivot, parent)`; `SkinMatrices::MakeSkinMatrices` multiplies by the inverse bind poses into the palette (`KickPalette`, `Matrix34`).
- **Rendering.** `AofObject::PrepareForRendering` picks passes (`GetColorPass`, `RenderPassManager::GetPass`) and has the object's `AofHandler` (mesh data: `AofhMeshset`s from the ASF) build its `RenderContext` (`AofHandler::MakeRenderContext`, one batch per meshset via `RenderContext::AllocBatch`); `AofObject::Render` hands it to `RenderContext::OnPaint`. `DirectAofHandler` is the immediate-mode variant used by `Framework::CDirectAofPrimitiveRenderer` (2D quads / UI sprites) and `DirectAofText`.

### Engine heap (`Aska::MemoryManager`)
Every guest `operator new`/`new[]` (plain and nothrow) calls `MemoryManager::Malloc` on `Aska::Global::GetAvailableMemoryManager()`. That returns `Global::m_pMemoryManager` if set, else the default manager. `operator delete`/`delete[]` call `LocalFree(header->manager, header)`. None of them touch libc malloc. The port runs all of this natively (`port/src/native/engine/aska_memory.cpp`), instruction for instruction, on the same layout and lock.

- **Default manager**: `Global::InitializeMemoryManager` `mmap`s `App+0x30` bytes (default 0x1a000000 = 416 MB) + 0x100.
  - The 0xf0-byte manager object sits at the start of the mapping. The heap starts right after it, at `(m + 0xff) & ~0xf` = m+0xf0.
  - Heap-in-heap managers (`MemoryManager(size)` / `InitHeap(size)`, e.g. `CAssignedMemoryManagerForSTLAllocator::CreateAndAttach`) take their heap from `operator new[](size + 0x10, nothrow)` and set the owns-heap flag.
- **MemoryManager** (0xf0 bytes, vtable `_ZTVN4Aska13MemoryManagerE`):
  - +8: u8 high mode. When set, `Malloc`/`AlignedMalloc` forward to `MallocHigh`/`AlignedMallocHigh`.
  - +0x10: `_Srbk` table; +0x18: u32 table entries; +0x20: heap base; +0x28: heap size.
  - +0x30: bad-alloc handler. Called when nothing fits, as described under "Out of memory" below.
  - +0x38: u8 owns heap.
  - +0x40/+0x48/+0x50/+0x58: manager ring (root, next, prev, ?). An allocation that fails in one manager tries `next` until it wraps around. `Add(MemoryManager*)` builds the ring; it never runs in offline play.
  - +0x60: inlined `Aska::FastCriticalSection`: +0x98 lock word (-1 free, 0 held), +0x9c waiter count (base 20), +0xd8 `Aska::Semaphore`.
    - Lock: 512 LDAXR/STLXR tries, then register as a waiter and sleep on the semaphore, or `Thread::Sleep(1)` if it has none.
    - Unlock: store -1; if waiters > 20, decrement and post.
    - The port uses `sync::fcs_lock`/`fcs_unlock` on the same words, so guest methods still in ARM64 (`IsEmpty`, `CalcFreeSize`, `SearchNextBlock`, `Move`, ...) interoperate.
- **Super-blocks**: the heap is cut into 64 KB chunks with one `_Srbk` (0x28 bytes) each. The table lies at the end of the heap buffer: `InitHeap` computes `count = (size - 0x52) / 0x10028` and drops the last chunk if it has less than 0x80 usable bytes.
  - A *run* is a group of consecutive chunks headed by an `_Srbk` with byte +0 = 1. Its other fields: +4 u32 next run, +8 u32 prev run (a ring through run 0), +0x10 used bytes, +0x18 free bytes, +0x20 largest free block (recomputed after every change).
  - Each run starts with a 0x40-byte sentinel block that is always marked used. Its size can grow above 0x40 when an aligned allocation gives it the alignment gap; `LocalFree` returns the gap.
  - When an allocation lands in an entirely free run, the space after it (or, for the high variants, below it) is split off as a new run at the next 64 KB boundary.
  - When a run's used count drops to 0, `LocalFree` merges it into an empty previous run and then an empty next run.
- **`_MemoryBlock` header** (0x40 bytes before the user pointer):
  - +0: size, including the header, a multiple of 16.
  - +8/+0x10: next/prev in the run's physical ring.
  - +0x18/+0x20: next/prev in the run's address-ordered free ring, which goes through the sentinel.
  - +0x28: owning manager. `GetAllocatedManager(p)` = `p[-0x18]`.
  - +0x30: u8 allocated-from-top flag; +0x31: u8 used.
  - +0x38: `IMemoryNotify*`. `LocalFree` calls its vfunc 1 without the lock held. `Realloc` asks vfunc 0 before moving, and a false answer vetoes the move (the new block is freed and 0 returned).
- **Sizes and fit**: a request of n bytes needs `(n + 0x4f) & ~0xf`.
  - `Malloc` is first fit over the runs from run 0, splitting when at least 0x50 bytes remain. `MallocHigh` is first fit from the last run downward over the free ring backwards, and takes the top of the block.
  - Aligned variants clamp the alignment to at least 4. A leading gap of 0x50 or more stays a free block; a smaller one is added to the previous block, and counted as used when that block is used.
  - `Realloc` resizes in place when the block belongs to this manager and `p % align == 0`. AArch64 `UDIV` by 0 gives 0, so align 0 never counts as aligned. Otherwise it does `AlignedMalloc` + copy of `min(old, n)` rounded up to 4 + free. A shrink can also cut a new run off at a 64 KB boundary inside the freed tail.
  - `Split(p, q)` cuts a block at q. The second part copies the first's header. It returns the second part's size, not a pointer.
- **Out of memory**: the manager's handler (+0x30) gets vfunc 0 `(handler, {manager, size, align or 4, u32 0, int* retry, void* result})`. A non-null result is returned; otherwise the search runs once more, and then gives up with 0. The throwing `operator new` then throws `std::bad_alloc`, which nothing catches; the port calls `fatal()` instead.
- **No debug tracking in this build**: the `file`/`line` arguments of `CAssignedMemoryManagerForSTLAllocator::Allocate` are ignored, and `PrintMemoryChain` and the debug memory map are empty stubs.
- **STL allocator**: `CAssignedMemoryManagerForSTLAllocator::Allocate(n, file, line)` first asks the attached `CFixedLengthAllocatorContainer`. That is `TFixedLengthAllocator<16/32/64/128/256/512>` pools (32-byte-per-slot headers, one `Framework::CMutex` each). Only then does it go to the attached manager, or `operator new[](n, nothrow)` if there is none. `Free` mirrors this.
- **Quirks kept by the port**:
  - `MemoryManager::LocalFree(void*)` has no null check (the guest would fault on `p[-0x18]`); the native version ignores null like `operator delete`.
  - The free-ring walk that recomputes a run's largest block stops at the first entry whose address is not above the sentinel, and skips entries marked used.
  - The inlined unlock tests "waiters > 20" and decrements separately, so two racing unlockers can both claim one waiter. The count then drops below 20 for good, and a stale semaphore post remains.
  - Guest methods that stay in ARM64: the ctor/`InitHeap`/`InitSrbk`/dtor, `Add`, `Remove`, `Move`, `IsEmpty`, `CountFreeBlocks`, `SearchNextBlock`, `DeleteHeap`. `Move` calls the native allocators.
  - `VirtualMalloc`/`VirtualAlignedMalloc`/`VirtualRealloc`/`VirtualSplit`/`VirtualCalcFreeSize` are 4-byte `b` thunks. They cannot be hooked (the 8-byte hook stub would overwrite the next function), and don't need to be: they branch to the hooked targets. An early attempt that hooked them turned `VirtualMallocHigh` into a bare `ret`, which returned the manager itself as "memory".

- **What still depends on the guest heap layout** (blocks moving to host malloc later):
  - Header readers: `MappedMemoryManager` calls `IMemoryManager::GetAllocatedManager` (manager and size) in `Attach/Move/DetachMappingEx` and `EliminateSourceBufferEx`, and `MemoryManager::GetAllocatedManager` in `DetachMappingEx` and `EliminateMappedBufferEx`. It also registers `IMemoryNotify`s in the header. `AudioSmallHeap::Reallocate` reads `GetMemorySize` (the header size). `MemoryManager::Move` and the realloc-style `operator new(size, void*, align)` read the manager from the header.
  - Statistics readers: `CalcFreeSize` is used by the `Framework::g*MemoryManager*` reports, `MemoryManagerHelper`, `CApplicationMemory::SetPrimaryMemoryManager`, and `Aska::ASON::Malloc`, which sizes its work buffers from the free space.

### Sound engine (`Aska::SoundManager` → `SLVoice` → OpenSL ES; `port/src/native/audio/audio_*.cpp`)

- **Layers**, top to bottom:
  - `Framework::CSoundManager`: the game-side front end. It holds `CSound::CElement`s (0x70 bytes each, in a `TObjectContainer`; +8 is the handle, `CSound::iInvalidHandle` when the slot is free). Two `CManageFiber`s run `PreProgress` (clear each live element's +0x19) and `PostProgress` (`CElement::PostProgress` on each live element, counting them into +0x70) every frame, under the manager's `CMutex` (+0x68).
    - Quirk: `PostProgress` passes the manager's dt only to the first element. Each later element gets whatever float the previous `CElement::PostProgress` left in s0, because the guest keeps no copy of dt. The port reproduces this.
  - `Aska::SoundManager` (the `Global::m_pSoundManager` singleton): owns the sound objects (`SoundObject`, `WavePlayer`, `SEControlObject`, `Sequencer2`, ...), a command list, the `SoundServer` (+0xe8: pools of sound objects, handles and ADPCM decode buffers) and the `AudioSignal` task (+0x40).
    - The `SoundManagerThread` loops every 16 ms over `SoundProcessSync` (pause/resume interrupts, command lists, sound passes, 3D, mixer and effectors) and `AudioSafetySignalNotify`.
    - +0x38 f32 plus 200 while +0x3c is set: the delete countdown given to voices whose stream ended.
    - +0x1228 / +0x1230: a silence buffer that voices enqueue when their stream stalls.
  - `Aska::SLVoice` (0x648 bytes): one OpenSL ES buffer-queue player per playing wave. Layout in `audio_slvoice.cpp`. The formats are 0xc PCM, 0xd Aska ADPCM, and 0xe Ogg Vorbis (BGM `.aac` containers and the Ogg entries of `.spk` packs).
  - `Aska::AskaOGG` (0x450 bytes, at `SLVoice` +0x58): the streaming decoder over libogg/libvorbis. Layout in `audio_ogg.cpp`.
- **Categories, volume, loops**:
  - `CSoundManager::PlayBGM` / `PlayMemorySE` take a free element slot, start an `Aska::SoundManager::PlaySound(id, loop, ..., category, settings)`, and mount a handle for the element. BGM is category 2: `PlayBGM(name)` copies the path into a `SoundServer` file-path buffer and plays it looped. Memory SE are category 5 and can carry a 3D emitter. `PlaySound` acquires a sound object and a handle from the `SoundServer` and queues a play command (kind 1) that the sound thread's `ProcessCommandList` executes; `StopSound` queues kind 2 with the fade. The element keeps the Aska `SoundObject*` (+0x10), a category byte (+0x18) and, for positional sounds, a hierarchical object (+0x20) whose matrix feeds an `AudioEmitter`.
  - `SoundObject` +0x1e8 flags pick the manager list: bit 0 → +0xf8 (the SE set that `StopSE` stops), bit 1 → +0x120 (streams: BGM and voices), bit 3 → the object streams from a read device (`UpdateReadDeviceAccessStatus`).
  - Stops fade through `CElement::SendStopRequest(seconds)`.
  - Allocation: the `SoundServer` (+0xe8) owns fixed pools of sound objects, handles, commands, passes and 0x6000-byte ADPCM decode buffers (`TPoolLegacy`). A voice's `WaveBuffer` (0x78 bytes, from `SoundMemory::Malloc`) is a `VBRBuffer` or a `CBRBuffer` depending on the container's bit-rate type (`AacUtil::GetBitRateType`); Ogg voices lock through `VBRBuffer::LockBufferEx`.
  - Volume: `AudioMixer::BuildFinalVolumeAndPanpot` combines the voice volume with the bus volumes. `SLVoice::UpdateVolumeMatrix` turns the result into millibels (20·log10, a -96 dB floor, clamped to -9600 mB and the player's maximum) and the pan into permille. `UpdatePitchbend` sets 2^octaves as a rate in permille, clamped to the player's range.
  - Loops: the container header gives the loop-start sample (`+0x48` table indexed by `+0x58`, plus `+0x68`) to `AskaOGG::DecodeInit`. `VBRBuffer::LockBufferEx` returns the loop end with the chunk that contains it; the source is then re-fed from the start while `AskaOGG` seeks.
- **Refill protocol**:
  - The OpenSL callback (`SLPlayerCallback` → `ProcAudioBuffer`) only counts a free buffer (+0x638) for ADPCM and Ogg voices. PCM voices unlock and relock the `WaveBuffer` right in the callback.
  - Every frame, `AudioSignal::Run` posts messages 0x467 and 0x468 for its two `AudioSignalNotify` lists (+0x28 and +0x160; 20 voices each). The dispatcher runs `AudioSignalNotify::Handler`, which calls `SLVoice::AudioSignal` for each registered voice under the list's lock.
  - `SLVoice::AudioSignal` works under the voice's `FastCriticalSection` (+0x5a8). For each free buffer, it pops the submit-queue entry of the buffer that finished playing. If that buffer came from a `WaveBuffer` lock, it unlocks it, and when the stream has ended it arms the delete countdown. Otherwise it subtracts the entry's bytes from +0x518, then refills:
    - `LockAndSubmitOGG` → `VBRBuffer::LockBufferEx` gives the next chunk of the stream plus its loop parameters. `SubmitBufferDataOGG` → `AskaOGG::Decode` puts PCM into one of the decoder's 8 output buffers, and `Enqueue` queues it.
    - While the decoder is still holding input back (AskaOGG +0x3c8), the saved source is resubmitted first.
    - A stalled stream enqueues the manager's silence buffer.
  - The submit queues (`TQueue<OggSubmitContext, 8>` at +0x4c0, `TQueue<AdpcmSubmitContext, 3>` at +0x4a8) remember each enqueued buffer's size, and whether a source lock has to be released when that buffer finishes.
- **Decoding** (`AskaOGG`):
  - The header packets are read first; each feed to `ogg_sync` is at most 8 KiB.
  - `DecodePackets` stops after the frame limit (40 ms, or 120 ms when at most that much is queued) unless the page carries EOS or a loop end is pending.
  - PCM is converted with `floor(x * 32767 + 0.5)`, clamped to [-32768, 32767] (fmul, fadd, fcvtms: not fused).
  - At a loop end (the last argument of `Decode`), the trailing frames are cut from the byte count, the stream and synthesis are reset, and `Decode_LoopStart` seeks to the loop start on the following calls. It finds a packet with a granule position, tracks block sizes with `vorbis_synthesis_trackonly`, and decodes and discards up to the loop sample.
  - The output buffers grow in 64 KiB steps. The new size also goes to the global `m_uiDecodePoolSize`, so later voices start with it.
- **Port notes**:
  - `AudioSignal::DeleteSignalVoiceList` tries the first list, then the second. Ghidra's decompilation drops the second attempt as "unreachable". A port that followed the decompilation left voices from the second list registered after `DeleteVoice`. The handler then ran `AudioSignal` on freed voices, which showed up as glibc tcache/fastbin corruption a second after the title tap, in about one run in six.
  - The HLE OpenSL mixer (`hle/opensles.cpp`) runs the buffer-queue callbacks it collected after dropping its lock, so a callback can still arrive right after `RegisterCallback(NULL)` / `Destroy`. The guest code tolerates that for Ogg and ADPCM voices: the callback is an atomic increment on the voice.
  - `AudioSignalNotify::GetSignalCount` releases its lock before counting in the guest; the port counts under the lock.
  - `SLVoice` is native as a whole, including `CreateVoice`. `CreateVoice` sets up the OpenSL player: PCM format, a buffer-queue locator with 8 (Ogg), 3 (ADPCM) or 3 (PCM) buffers, and the play, buffer-queue, volume and playback-rate interfaces. It accepts rates of 8 to 192 kHz from a fixed list and 8, 16, 24 or 32 bits, and primes every buffer before registering the voice for signals.
- **Sound data.** The offline APK had only `BAS_SYSTEM_BGM_06/09.aac` (Ogg, title), `SystemCommonSE.spk` (UI SE) and `Voice_UI_020.spk` (title call), so story scenes played only UI SE there. The 3.7.0 download has the rest: 113 BGM `.aac` and 254 talk-scene `TS_*` files in `work/download-3.7.0/Sound/`.

### Input (`Aska::TouchPanel`, `Aska::Pad`, `Framework::CTouchPanel` / `CPad`; `port/src/native/input/input_*.cpp`)

- **Touch path**:
  - `Aska::TouchCallback` (the native-activity input hook, main thread) appends each motion event to the global ring `TouchPanel::m_queueSystemTouchData` (65 slots of {action, pointer id, x, y, pressure}). It records only the pointer the action index names, which is why the port's pinch emulation moves one finger per event.
    - Back and Menu key events set `PadDroid::m_bBack` / `m_bMenu`.
  - The PeripheralManager thread's `TouchPanel::GetStatus` → `GetDeviceData` drains the ring into up to 64 `TouchData` records (8 reports each). It converts window coordinates to frame-buffer pixels and pressure to 0..255.
    - Kinds: 1 down (`ACTION_DOWN`/`POINTER_DOWN`), 2 up (`UP`, `CANCEL`, `OUTSIDE`, `POINTER_UP`), 3 move.
    - A move for a pointer already reported down or up in this frame is dropped. A second report for the same pointer starts a new record.
  - The main thread's `CTouchPanel::Progress` then:
    1. does `ResetGestureParam`, `CopyMessages` and `UpdateGesture`;
    2. reads taps, double taps, drag, touch-and-hold and pinch;
    3. derives its own tap position, virtual stick (+0x30: the drag vector from its start point, normalised to a 150 px radius with a 30 px dead zone) and pinch delta;
    4. finally calls the panel's `ResetStatus`.
- **Gestures** (`UpdateGesture`):
  - Each finger gets a `TouchOrigin` (8 slots). Fingers that go down within 400 ms of each other form a group, so a tap is counted for the whole group.
  - A finger that leaves the tap slop (max(frame-buffer w, h) × 80 / 1280 px, L1 distance) loses its tap and hold flags, and so do the other fingers of its group.
  - A double tap is a group with the same finger count as the last tap, each finger landing near one of its points within 250 ms.
  - Touch-and-hold is reported every frame after 500 ms.
  - The pinch uses the first two origins. Its scale is the current finger distance over the initial one; coincident starting points give 0/0, and the port keeps ARM's default NaN (`arm_float.h`).
- **Quirks kept**:
  - A drag's dx/dy is measured from `DragParam[0]`'s position whatever the slot.
  - `GetDeviceData` stamps a new record's time into record 0.
  - With no group yet, each finger of a new group gets a fresh group id from the global counter.
  - `Pad` / `CPad` do all the key bookkeeping (double-buffered status, edges, repeat counters) every frame even though `PadDroid` never reports buttons.
- **Verification**:
  - Scripted and random multi-touch streams (tap, double tap, drag, hold, two-finger pinch, cancel) through the guest and native code on private panels, with the clock faked.
  - `CTouchPanel::Progress` and `CPad::Progress` run inside the game's own frames.

## API response handling (CApiNotify)

`CApiNotify` (224 exported functions, `Source/Game/Network/ApiNotify.cpp`) receives the game server's responses and applies them to the player state. The player state lives in the **`CParameterManager` singleton**, next to the master-data tables. It holds the owned characters, items, stack items, gear, party, favor and so on, plus one "result" container per response kind. There are no separate user-data classes. `CUserDataUtility::SaveToLocalKVS` = `Save_PlayerInfo` + `Save_PartyInfo` later copies a small summary into LocalKVS (see "What the save contains" above). The handlers never save.

Native port: `port/src/native/api/api_notify.cpp` (see "Port status" at the end of this section).

### Dispatch

- `CApiNotify` implements `Aska::Yayoi::GameRPC::Cli::IGameProtocolNotify`. Its vtable (`0x29c3e98`, 204 slots) starts with the protocol callbacks:
  - `OnProtocolError`, `OnError`, `OnDoubt`, `OnStart`, `PreDispatch`, `OnDisconnect`, `OnResultStart`, `OnResultUpdateSession`, `OnLoginResult`, `OnSimpleLoginResult`;
  - then one `On<Api>Res(signed char* data, unsigned& size)` per API (e.g. `+0x58` `OnGetPlayerRes`, `+0x1a8` `OnMissionStartRes`, `+0x1b8` `OnMissionEndRes`, `+0x2d0` `OnGachaRes`).
  - Every handler returns `Aska::Status` through x8. `this` is x0, the MessagePack body x1, and a pointer to its size x2.
- **Network path:** `GameProtocolProxy::DispatchNotify` / `GameProtocolNotifyMT::Run` call the virtual for the response's `FunctionID` on the main thread. In offline play only the constructor runs: coverage shows no handler executing (`work/profile/*/coverage.tsv`).
- **Offline server path:** `FakeApiCaller` embeds a `CApiNotify` at `+0x60`. Each API's `std::function` lambda (`AddLocalFile(fid, "FakeApi/<name>.msgp", fn)`) is `{vtable, FakeApiCaller*}`, and its `operator()` tail-calls the handler directly. For example, `GetPlayer`'s lambda (`0x1495b1c`) is `x0 = this->fake + 0x60; b OnGetPlayerRes`. The per-API map is in the FakeApiCaller section.

### CApiNotify fields used by the handlers

| offset | meaning |
|---|---|
| `+0x510` | `FunctionID` of the request in flight. `0x7b1a9377` = none (set by the constructor, `InitErrorCode`, `ResetErrorCode`). |
| `+0x514` | last error code (`_SetErrorCode`) |
| `+0x518` | bool: a response is waiting to be acknowledged |
| `+0x4c0` | back pointer to the owning `IApiCaller` (constructor argument, at slot `0x98`) |

### Handler shape

Almost every `On<Api>Res` is one template:

```
if (!CErrorHandlerWrap::Instance()->byte[0x1ad]) {   // "skip apply"; cleared by the ctor, no exported setter
    DeserializeToInfo(data, size);                      // Status ignored
    <post-apply steps>;                                 // per API, table below
}
EndRequest();
return 0;
```

**`EndRequest`** is inlined at the end of every handler:

```
if (fid == NONE) return;
if (pending) {
    pending = 0;
    if (fid not in {0xd4053e85, 0xe3e463ad, 0xea04f3fd, 0x5f583f50}) {   // signed compares, 2-level tree
        error = 0x3ee;
        CApiCaller::inst->vfunc[0x480]();  CApiCaller::inst->vfunc[0x478](1, 1);   // both Status via x8
    }
    ErrorHandler::Instance()->Success(fid);
    error = 0;
}
atomic_exchange(&CApiCaller::inst->vfunc[0x688]()->word[0x28/8], 0);   // ldaxr/stlxr loop: release the request slot
```

The `CApiCaller` singleton pointer isn't null-checked. The `ErrorHandler` and `CErrorHandlerWrap` ones are: `gDoAssert("TSingleton.h", 35, "m_pInstance is null.")`, then re-read.

**`DeserializeToInfo(data, size)`** (7.6 KB):
1. `CServerTime::SetLocalTime()`.
2. It clears every per-response result container in `CParameterManager`. Among them:
   - maps (`map<u64, T>`): new items `+0x4ab0` (CItemInfo), new characters `+0x4b50` (CPersonInfo), stack-item updates `+0x1128` / `+0x1440`, boost results `+0x1308`, mission results per character `+0x2870`, favor results `+0x30e0`, limit-break results `+0x6170`, limit-break items `+0x61c0`, box gacha `+0x7318` / `+0x7368`, step-up gacha `+0x7458`, character exp `+0x3920`, drop contents `+0x3970`, storage `+0x8b08` / `+0x8b58`, gear `+0x8ce8`, attached gear `+0x8d88`, battle evaluation `+0x8928`, friend gauge `+0x6548`, follows `+0x65e8`, partial maintenance `+0x74a8`, …;
   - vectors: presents `+0x4480` (CPresentBoxInfo, 0x248 bytes), gacha results `+0x4fb8` (CGachaResultInfo, 0x188), gift gacha results `+0x5008` (0x1b8), world-boss items `+0x42b0` (0xc8), and several `CParameterPropertyValue` id lists (0x30 bytes each);
   - the four `CMissionResultDropInfo` at `+0x2888` / `+0x2a90` / `+0x2c98` / `+0x2ea0`, and the `Initialize()` of the favor, gear-generation, Sphere211, universe and assist result infos.
3. It swaps a fresh `CHostPlayerInfo` / `UpdateMissionStartPlayerInfo` into `+0xf50` / `+0xf88`, and re-registers `+0xf88` and `+0x10f0` in the child-info map at `+0xf70` by name hash.
4. `ASON::Init(max(size * 4, 0x2000))`, `ASON::Deserialize(data, size)`, then `CParameterManager::Deserialize(root map)`. A failing Status is written to x8 and returned.
5. Post-processing:
   - the ids in `+0x6f08` go into the `+0x12b8` list;
   - if the host player (`+0xfe8`) is this player (`+0x698`), the player's name, level and stack items are refreshed from the host-player info;
   - `CServerTime::UpdateServerTimeOffset()`.

**`CParameterManager::Deserialize(AMap*)`** (`0x16f1e14`) is the reflective apply step:
- for each registered `InfoBase*` in the list at `+0x68`, it calls `info->Deserialize(map)` (vtable `+0x20`). Every `InfoBase` has a property map (`map<u32 hash, IParameterProperty*>` at `+0x08`) and a child map (`map<u32, InfoBase*>` at `+0x20`), keyed by the `CHash32` of the MessagePack key name;
- it looks up the info at `+0x600` by its own name (vtable `+0x18`) and passes the value's payload to vtable `+0` if it's an array (AValue type 6) or to `+8` if it's a map (type 7);
- it stores `"status"` in `+0xb728`.

### Post-apply steps

These are guest functions called right after `DeserializeToInfo` **without setting x0**, so the stale x0 is passed as "this". They don't use it.

| step | what it does |
|---|---|
| `AddItem` (`0x13c69a0`) | new items (`+0x4ab0`) into the owned item list |
| `AddCharacter` (`0x13c6f90`) | new characters (`+0x4b50`, CPersonInfo values at node+0x28) appended to the owned-character vector `+0x1178` (0xb88 bytes each, uid at +0x60): copy-construct at `end` if there's capacity (asserting if `end` is null), else `__push_back_slow_path`. No duplicate check. |
| `AddLimitBreak` (`0x13c70a8`, also inlined) | for each limit-break result (`+0x6170`), every owned character with that uid gets `+0x1f0` ← result `+0x158`, and `+0x100` ← result `+0xf8` if non-zero |
| `UpdateStackItem` | stack-item deltas into the stack-item list |
| `UpdateStepUpGacha` / `UpdateBoxGacha` | step-up / box-gacha progress |
| `ApplyAutoEquipResult`, `ApplyGetPresent`, `AddStorage`, `DeleteStorage(bool)`, `DeleteOneTimeStorage`, `AddPresentBox` | equipment, presents and storage |

Handlers by post-apply steps ("apply" = `DeserializeToInfo`; "inline" = handler-specific code between the apply and `EndRequest`):

| steps | handlers |
|---|---|
| apply (85) | GetBirthYearMonth, UpdateBirthYearMonth, TrainingMissionStart, GetMissionList, MissionTalk, EndMissionTalk, MissionFailed, MissionLose, MissionContinue, GetWorldBossInfo, GetWorldMapInfoList, GetScenarioLibraryInfoList, DeepSpaceActiveList, DeepSpaceAutoMemberSelect, CoinList, CoinDepositCreate, CoinDepositAmazonUpdate, ExshopExchangeList, ItemShopList, DirectItemShopList, CreatePlayer, SearchPlayer, UpdateKiyakuVersion, SendErrorLog, GetPlayMission, UpdateSupport, Sphere211AutoMemberSelect, PresentList, GetStorageInfo, GetOneTimeStorageInfo, GetGearInfo, UpdateGearStock, GetConfig, ResetConfig, UpdateItemStock, UpdateFollowMax, GetGachaInData, GetBoxGacha, GetGachaRate, Blacklist, UpdateRelationship, NeighborRegist, LocationRegist, AchievementReceiveList, UpdateHome, Home3DAnd2DSwitching, ChangeMascot, UpdateTutorial, UpdateView, NoLoginStart, SendGuideInformation, ReadExpirationInfo, GetServerTime, CbtCertification, SetStampSlot, SetTitle, GetRecentlyPlayedList, Sphere211MissionFailed, Sphere211MissionContinue, GetPlayerDetailInfo, GetEventRankingInfo, ClearNewEventRanking, GetUniverseBoardIdList, GetMasteryInfo, GetSubscriptionHistory, GetDecoInfo, and 19 Debug* |
| apply + three `CParameterManager` singleton checks | GetPlayer |
| apply + AddItem + AddCharacter + AddLimitBreak (inlined) + UpdateStackItem | CoinDepositIOSUpdate, CoinDepositAndroidUpdate, ExshopExchange, GachaTicket, SaleGachaOnce, SaleGacha; + UpdateStepUpGacha: GachaOnce, Gacha; + UpdateBoxGacha: BoxGacha |
| apply + UpdateStackItem | Sphere211StaminaHeal, Sphere211UseRerollItem, GetSphere211RankingInfo, Sphere211MissionStart, ExchangingUniverseCurrency |
| apply + AddItem + UpdateStackItem | MaterialCompose, GetSphere211Info, CheckEventRankingResult, ReceiveEventRankingResult |
| apply + ApplyAutoEquipResult | EquipAuto, EquipAutoParty, Sphere211EquipAuto |
| apply + DeleteOneTimeStorage + AddItem | WithdrawItemFromOneTimeStorage, BulkWithdrawItemFromOneTimeStorage |
| apply + other single step | GetPresent (ApplyGetPresent), DepositItem (AddStorage), ResetBoxGacha (UpdateBoxGacha), WithdrawItemFromStorage (`DeleteStorage(false)`), SellItemsFromStorage (`DeleteStorage(true)`) |
| apply + longer inline code (not native yet) | ChangeRole, ItemCompose, InheritAccessory, UpdateName, UpdateParty, UpdatePartySet, EquipWeapon, EquipAccessory, SetAssist, EquipSkill, Lock/UnlockItem, ClearNewItem / StackItem / Character / Gear / OneTimeStorageItem, SellItem, SellStackItem, SellGear, Lock/UnlockStorageItem, AttachGear, RemoveGear, GenerateGear, UseHealItem, UpdateConfig, StaminaHeal, Follow List/Add/Remove, Blacklist Add/Remove, NeighborList, AchievementActiveList, AchievementReceive, AchievementListReceive, Sphere211SelectedFloor, Sphere211FloorClear, ReturnSphere211, UseFavorItem, StaminaHealByFavor, UpdateFavorByTap, TrainMastery, ResetMastery, (Un)FavoriteDecoObject, SetCharacterDeco, EvolutionCharacter, LimitBreakCharacter, AddStatusCharacter, BoostCharacter, UpdateAwakenLevel, AcquireUniverse, UniverseReset, SetDeity, ExItemShop, ItemGradeUp, DeepSpaceMissionStart / End / EndNow |
| no apply, `EndRequest` only | DebugGradeUpCharacter, DebugGetCoin, DebugGetFol, DebugGetCharacter, DebugGetItem, DebugOpenMission, DebugDeletePlayer, DebugTowerMax |

### Entering and leaving a battle

- **`OnMissionStart`** applies the response without acknowledging it: `DeserializeToInfo` + `UpdateStackItem`, and **no** `EndRequest`. With the skip switch set it only acknowledges.
- **`OnMissionStartRes`**, `OnMissionRestartRes` and `OnMultiMissionRestartRes` call it and then acknowledge, unless the Status is negative. With the skip switch set the request is acknowledged twice; the second time is a no-op apart from releasing the slot again.
- **`OnMissionEnd`** is the same pattern (`OnMissionEndRes`, `OnSphere211MissionEndRes`). After `DeserializeToInfo`:
  1. **Per-character results** (`+0x2870`, `map<u64 uid, CMissionResultCharacterInfo>`): the owned character with that uid gets `+0x190` ← result `+0xc8` and `+0x1c0` ← result `+0xf8`. An unknown uid asserts `"not found"` (ApiNotify.cpp line 869) and is skipped.
  2. **Favor results** (`+0x30e0`, keyed by a **u32** character id, widened to u64):
     - the value is copied, then `favorMap(+0x8410)[id]` gets `+0xc0` ← `+0xf0` and `+0x90` ← `+0x120`;
     - its encrypted name (`+0xf0`) is re-keyed from the favor's (`+0x150`): `CryptString<201>` decrypts it to plain text and `CryptString<16>` encrypts it into the element;
     - quirk: the plain string is then copied into a temporary that's destroyed unused, which costs one allocation when it is longer than 22 characters.
  3. `AddItem`, `UpdateStackItem`, `AddCharacter`, `AddLimitBreak` (inlined), and `UpdateStackItem` again.

### Gacha draws

`OnGachaRes`, `OnGachaOnceRes`, `OnGachaTicketRes`, `OnBoxGachaRes` and the sale gachas:
- apply: `DeserializeToInfo` fills the gacha result vector at `+0x4fb8`, new items and characters;
- `AddItem` and `AddCharacter` then move the drawn items and characters into the inventory;
- the inlined limit-break sync covers characters drawn again: their limit-break count and level cap come from `+0x6170`;
- `UpdateStackItem` updates currencies and stack items, and `UpdateStepUpGacha` / `UpdateBoxGacha` update the per-banner progress.

### Port status

The natives of this section were removed with the rebase (docs/history/PLAN-rebase-370.md revision 2). What they were, their tests, the guest quirks they found and the live check against the offline server: [`docs/history/notes-native-switches.md`](history/notes-native-switches.md).

### Battle factors (buffs, debuffs, passive effects; `port/src/native/battle/battle_factor*.cpp`)

- **Master data** (tables identical in 3.7.0 and the offline DB):
  - `master_factor` (7,590): a trigger `timing` (+ options, probability) and up to four seeds, each with a target / target option, plus up to four chained factors.
  - `master_factor_seed` (13,455): one effect. `elment_type` (1-94) selects the seed class, `effct_type` is buff / debuff, `anti_type` links it to NoEffectAntiType, `category_id` feeds the priority, the on/off condition columns (or `condition_category` → `master_factor_condition`, 227 rows) gate it, and `param1..5` are class-specific.
  - `master_factor_boost` (47): per element type, extra `value` for one parameter (`param1`) and `add_priority` (`Factor::FactorBoostInfo`, 0x14 bytes).
  - In memory, `CMasterParameterFactorSeedElement` properties sit every 0x30 bytes with the value at +0x28: elment_type +0xe8, effct_type +0x118, anti_type +0x148, category_id +0x178, priority +0x1a8 (unused by the seeds), condition_category +0x1d8, on_condition / option / option2 +0x208 / +0x238 / +0x268, off_* +0x298 / +0x2c8 / +0x2f8, param1..5 +0x328 .. +0x3e8, icon_id (encrypted string) +0xa8.
- **Seeds** (`CFactorSeedBase`, 0x78 bytes; the subclasses add 0x08-0x50 of parameters from +0x78):
  - +0x08 `vector<EnableCondition>` (0x2c each: on condition, option, option2, target a/b, off condition, ..., owner argument). +0x20 seed id, +0x24 element type, +0x28 effect type, +0x2c anti type, +0x30 boost (float), +0x34 grant boost, +0x38 grant priority, +0x3c category (-1 until Initialize), +0x40/+0x44/+0x48 the factory's target / owner / source arguments, +0x50 icon id string, +0x68 remaining frames (-1 = unlimited), +0x6c condition category, +0x71 active (chosen by CheckSeed), +0x72 released, +0x73 has a condition, +0x74 blocked by an anti seed.
  - Virtual table: 0/1 destructors, 2 Initialize, 3 FactorBoost, 4 GrantFactorBoost, 5 SetParam(p1..p5), 6 OnProgress(dt, frame), 7 CheckPriority, 8 GetTypeId, 9 GetTypeIdSub, 10-12 CheckSameId(u32 / p1..p4 / seed*).
  - `CFactorSeedFactory::Create(shared_ptr<element>, id, target, source, owner, boosts, grant boosts)`: a switch on the element type (89 classes; 44, 50-52 and 56 have none and return null: 50-52 are status-screen-only types) → `operator new(nothrow)`, zero, base constructor, vtable, the two boost maps for the map seeds; then virtual Initialize (with the decrypted icon id), FactorBoost for every boost of this element type, GrantFactorBoost likewise, and SetParam(param1..5).
  - `Initialize` copies the header fields and builds the conditions: every `master_factor_condition` row of the seed's condition category (via `ParameterByQuery`), else the seed's own on/off columns.
  - `SetParam` shapes: durations are `seconds > 0 ? seconds × 60 : -1` frames; "boosted" parameters are `(boost + p) + (float)grant_boost`; integer parameters use FCVTZU (negative → 0, saturating). AvoidDistanceAndSpeed boosts only non-zero parameters and associates `p + (boost + grant)`; AvoidState stores `p / 60 × 60`; RecieveOverHeal / JustAvoidComboPlus add the boosts as integers.
  - Six seeds keep `std::map<param, {value, priority}>` boosts (AlwaysSuperArmor, AbnormalDefenceUp, Add/ReceiveDamageUp at +0x80/+0x98; ChangeParameter(Fix) at +0x98/+0xb0) and fold the matching entries in SetParam. ChangeParameter's parameter index is 0-5, 98 = parameters 1-5, 99 = all six; its six outputs (+0x7c..+0x90) are `(p2 + boost[i]) + grant[i]`. A key above 5 trips an assert and then indexes past a 6-float stack array (no master data does that).
  - `GetTypeId` / `CheckSameId`: the field that tells two seeds of a class apart (abnormal state, attribute, parameter index ...), compared against an id, the FCVTZU'd SetParam argument, or another seed's GetTypeId (+ GetTypeIdSub).
- **Manager** (`CFactorManager`, one per character; owner handle at +0x1880):
  - +0x00 pending seeds, +0x18 active seeds, +0x90 the manager's merged condition list, +0xb0 a seed-element cache (`map<id, shared_ptr>`), and from +0xb0 one 0x40-byte slot per element type (95): a `std::function<void(u32 owner, vector<seed*>&)>` (that class's static CheckSeed) and at +0x40·type+0xf0 the flags changed / condition changed / anti changed. +0x1884-0x1887: progress, changed, anti-seed-changed, FactorGuard.
  - Adding: `AddFactorSeed` / `StartFactor*` create seeds into the pending list; `CheckAddList` moves each through `CheckPriorityAndAddList`: every active seed gets `existing->CheckPriority(new)`: 0 keep both, 1 the new one replaces it (deleted), 2 the new one is rejected (deleted). Only seeds of the same element and effect type with the same id compete, never ones with flag70 or target 0x10. The higher `grant priority + category` wins; unlimited timers and conditional seeds have extra rules (an unconditional seed beats a conditional one); on a tie the newcomer wins and inherits the longer timer.
  - `Update(dt)`: CheckAddList, then drop released seeds (+0x72), then each seed's `Update`: its virtual OnProgress (per-frame effects: HP/AP regeneration, revival, gauges) or its timer running out ends it; then CheckAntiSeed (seeds whose anti type matches an active NoEffectAntiType's +0x78 are blocked), and if anything changed `OnChangeFactor`.
  - `OnChangeFactor`: for each flagged element type, collect the active seeds of that type that are not conditional (+0x73) or blocked (+0x74) and call the type's CheckSeed callback with them; then rebuild the merged condition list.
  - **How stats change**: CheckSeed (static, per class) picks winners among the seeds of its type (priority `grant priority + category`, strictly greater wins, so the first of equals; for buff/debuff classes the best seed with value > 0 and the best with value ≤ 0) and writes the combined value into the owner `CCharacterObject` (fields such as +0x12d8 / +0x1308 AP cost, per-kind tables of 0x30-byte elements for damage-up / attribute / abnormal / race / skill slots, usually × 0.01 for percentages). ChangeParameter(Fix) call `CCharacterData::BasicParameterAdd[Fix](stat 0-5, sub 0-3, value)` then `CheckBasicParameter`; ExchangeParameter calls `BasicParameterChange`. The battle damage code reads those fields.
- **Outside battle**: `MasterFactorModel::GetParam` folds a seed record into the status screens' `FactorParameter` (0x68 bytes): ChangeParameter adds to stat[p1]; ExchangeParameter moves `round_half_away(p3 × stat[p1] / 100)` (through double) from stat p1 to p2; ChangeParameterFix / AddMaxAPUpFix; types 50-52 keep the highest-category record (50 counts `ceil(p2)` levels, at least one).
- **Quirks kept**: FCVTZU everywhere Ghidra shows `(int)`; element types 50-52 exist in master data (13 records) but have no battle class; `EnableCondition::IsSame` compares "target 3" entries by the second operand's owner argument; `CFactorSeedBase::Update` treats a NaN timer as unlimited; the factory's icon string grows through `__grow_by_and_replace` (capacity from max(n, 44)).
- Destructors: back to the base vtable, free a long icon string and the condition buffer (the map seeds first destroy their two boost maps, the second one first), then `operator delete` for the deleting ones.
- **Verification**: every SetParam on random inputs (with boost maps built by the guest's own `SetFactorBoost_WithType`); all 13,455 seed records through the guest and native factories with random boosts, the objects compared field by field (conditions, icon string, maps) plus `Update`; the 104 type-id methods; the deleting destructors (frees logged through isolated stubs); `CheckPriority` on random seed pairs; two synthetic managers driven through random add / release / anti / delete passes; `GetParam` on every relevant record; the CheckSeed / OnProgress classes against a stubbed owner (`battle-factor/*`). A live check isn't possible yet: the scripted battle route (`port/scripts/battle_session.sh`) stops in the loading screen before any factor code runs.

### Battle formulas (`ICalculateParameter`, `CBattleUtility`; `port/src/native/battle/battle_calc.cpp`)

Read from the ARM64 disassembly; Ghidra's output drops several clamps (`FMIN`, `FMAXNM`) and gets `CalcDamage`'s result type wrong. The stat indices are `battle::BasicParameterType`: 0 HP, 1 attack, 2 intelligence, 3 defence, 4 hit, 5 guard (the column order of `master_enemy_base_parameter` / `master_character_common_parameter`). The attributes (`BAS::eAttribute`) are 0 none, then 1-7 fire, water, wind, earth, thunder, light, dark (`def_*` columns).

- **Battle random generator** (`detail::Random`, `RandomFloat`, `InitRandom`, `ShuffleRandom`):
  - Knuth's subtractive generator (Numerical Recipes `ran3`), the same algorithm as `Aska::Random` but a separate state: index at `.bss` 0x2bef94c, table `ma[1..55]` after it.
  - `ICalculateParameter::SetRandomSeed(s)` = `InitRandom(s)`. `InitRandomSeed()` seeds from `Aska::GetLocalTime`: `((u16@+4 << 16) | u16@+10) * 0x9534c85 + 0x9535932`.
  - Fractions are `u32 * 2.3283067e-10` (0x2f800001, a hair above 2^-32), so `RandomFloat` can round up to 1.0. Percent rolls are that times 100.
- **Base damage** (`CalcDamage(type, ignoreDef, power, atk, def, maxHp, cancel, attr)`, inlined again in `Damage`). Two draws are always taken, `r1` and `r2`:
  - `base = atk * (1 + r1 * 2^-32) * 0.01` (a 1-2% of attack random bonus), `r3 = r2 & 3` (0-3 flat).
  - type 0, normal attack or skill: `(max((2*atk - def) / 1.5, 0) * power + base + r3) * attr * cancel`. The defence term is dropped when `ignoreDef` is set (flag bit 1 in `Damage`).
  - type 1, max-HP ratio: `power * maxHp` (the target's max HP).
  - type 2, defence-ignoring: `(power * atk + base + r3) * cancel`.
  - type 3, flat: `power * 100`.
  - Any other type returns `power` unchanged.
  - In `Damage`, `atk` is the attacker's intelligence when the attack parameter's magic byte (+0x34) is set, else its attack. `power` is the attack parameter's +0x14, the type is its +0x3c, `cancel` is `CCharacterData::CancelBonus()` (+ the rush controller's bonus / 100 in rush mode). The multiplication order differs slightly from `CalcDamage` (`cancel * (attr * (...))`).
- **Attribute rate**: over the attack's attributes (bit mask at +0x48 of the damage argument), take the defender's lowest `DefAttribute` (the first strict minimum). If that attribute is not 0: `attr = (100 - 5 * min(res, 20)) * 0.01`, so resistance 20 or more means 0 damage and negative resistance is a weakness. Otherwise `attr = 1`. The attacker's best positive attribute bonus (its per-attribute vector +0x2ce8) is added to the damage-rate sum below.
- **Damage-rate sum** (hostile targets only): `dmg += dmg * (taken + dealt)`, clamped at 0 with `FMAX`.
  - `taken` is the defender's rates (vector +0x2f48, value +0x28 of each 0x30-byte entry): [0] all + [1 or 2] physical/magic + [3 or 4] (by the attack data's +0x14c flag).
  - `dealt` is the attacker's: the same three from +0x2ef8, + by the defender's race (+0x2c98[def+0x5054]), + by attack id (+0x2d38[id]), + the best attribute bonus, + +0x1898 (+0x18c8 with flag bit 5), + +0x18f8 in rush mode, + +0x2f88 when defence is ignored.
  - The target takes 0 unless flag bit 9 is set, if it's invincible (+0x32e8 or +0x34c8) or flag bits 10-11 are set.
  - Non-hostile hits (heals) with a non-positive value instead get `dmg += dmg * (target +0x1728 + source +0x16f8)`.
- **Guard** (flag bit 0): one more draw. If the defender has +0x1ac8 set and `draw% <= +0x1978`, it's a perfect guard (0). Otherwise `dmg *= clamp((100 - (guard - hit) / 2.5) * 0.5, GuardCut_Min, GuardCut_Max) %`, from `CBattleManager` +0x9f8 / +0xa28 = `master_battle_global` `Battle_GuardCut_Min` 30 / `_Max` 70.
- **Multiplayer**: an attacker of kind 2 (+0x76d4, enemy) gets `dmg += dmg * CBattleManager::GetEnemyDamageRate()`.
- **Critical** (`Critical` gives the rate, `IsCritical` rolls `draw% <= rate`):
  - `rate = clamp(hit + 5 - guard, 0, 20)`, with `FMINNM`, so a NaN difference gives 20.
  - Plus `CBattleManager`+0x998 if the attacker has +0x7738 set (charge assault; `Battle_Critical_Rate_ChargeAssault`).
  - Plus defender +0x29e8 + attacker +0x29b8, and defender +0x19d8 + `CBattleManager`+0x9c8 when the defender's controller flags are set.
  - Times 0 for attack type 2.
  - A defender in abnormal state 2 is always critical (100) unless bit 2 of the collision argument +0x48 is set.
- **Guts** (survive a lethal hit): none in abnormal states 1, 2, 3, 8 or for kind 2. A forced guts gives `CBattleManager`+0xa88 HP. Otherwise, if `damage / maxHp >= +0x2958` (unordered counts as below), the character keeps +0x2988 HP.
- **IsGuard**: never for a "no guard" hit, without a controller (+0x610), with +0x5118, super armor, in rush mode, or in abnormal states 1, 2, 4. It needs `IsNeutral()`, then either +0x1af8 (guard from any side) or `IsFront(dir)`.
- **Assist cut-in**: needs a non-empty cut-in name (+0x51f8 string), then `draw% <= GetAssistCutinRate()`.
- **CBattleUtility helpers**:
  - `IsBullet(type)` = bit `type-1` of 0x7f1f943 for types 1-27.
  - `CalcCorrectLevel(level, rank, role)` = `level * table[rank-1][role-3]` (ranks 1-5, roles 3-6; 0.82-1.49). Anything else asserts "invalid role rank!!" and returns 1.
  - `BattleTimeFrameToMilliSeconds(f)` = `(int)(f / 60 * 1000)`, rounded half-up to 10 ms within each second.
  - `CalcCharacterSize(a, b)`: 0-3 by `a + b` against `CBattleManager` +0x38 / +0x68 / +0x98 (`Character_Size_*`); 1 outside battle.
  - `CheckRandomParam(rate, scale)` = `Aska::RandomFloat() * scale <= rate`.
  - `IsActionCategory(cat, timing)` matches categories 0-27 and 99 against `TimingSkillCheckType::TransrateTimingSkillCheckType(timing)`'s {kind, sub, attribute}: kind 2 normal attack, 3-4 skill, 1, 4, 5, 6 others; sub 0/1; attributes 0-7.
- **Character stats** (`CCharacterData`, the battle-side character at `CCharacterObject`+0x1010; `battle_chardata.cpp`):
  - Values live in 0x30-byte slots (value at +0x28), inline or in `CSTLVector`s. The "(int)" casts Ghidra shows are `FRINTA` (round half away from zero, kept as a float): `MaxHP()` is the rounded stat 0.
  - **Parameters** (`CheckBasicParameter`), for each of the six parameters i:
    - `fix = base[i] + add_fix0..3[i]` (+0x14a8, +0x1638 + 0x50k) and `rate = add0..3[i]` (+0x14f8 + 0x50k), each summed from 0 in slot order; `v[i] = fix + rate * fix`.
    - The conversions (+0x1778 + 0x50t, `BasicParameterChange(t, j, x)`: move a share x of parameter t into parameter j) are applied as `conv[j] += e[t][j] * v[t]` and `v[t] -= (sum_j e[t][j]) * v[t]`.
    - The result is `stat[j] = FMAX(v[j] + conv[j], 1)`. When the rounded max HP changed, `HP(round(newMaxHp), false)` refills HP.
  - **HP** (`HP(x, allowOver)`): x is clamped at 0.
    - Without `allowOver`, a heal above the current total stops at max HP (or keeps the current total if that is already above max HP).
    - Otherwise the cap is `round(overMax +0x208) + round(maxHp)`.
    - Anything above max HP is over-HP (+0x1d8), the rest HP (+0x118), and dead (+0xf98) = `HP <= 0`.
    - Barrier (+0x178, max +0x148) and AP (+0x268, max +0x298) are clamped to [0, max]. `NaN < 0` is false, so a NaN is stored as is.
  - **Gauges**:
    - Tension (+0xcf8) gains `x * rate (+0xd28)` and is capped at 100 (`FMIN`).
    - The rush gauge (+0xd58) is capped at `max + max * bonus` (+0xd88, +0xdb8) and costs `use + use * bonus` (+0xde8).
    - `CancelBonus()` = `CBattleManager::GetCancelBonus(cancel count +0xf08)` (or `GetCancelBonusRush()` in rush mode) / 100.
  - **Timers**: no damage (+0x748), forced guts (+0x778) and super armor (+0x7a8) count down to 0; a NaN count stays NaN, because `B.HI` treats unordered as greater. Stun uses +0x12c8 / +0x12f8, with defaults from `CBattleManager`+0x608 / +0x12c8 / +0x638.
  - **Other state**:
    - Faint points: +0x20f8 against the max +0x1b28.
    - `DefAttribute(a) = (base + bonus) * (1 + rate)`, from +0x1a18 / +0x1a68 / +0x1ab8.
    - `AddAbnormalCheck(s)` = not `CheckRandomParam(resist + bonus, 100)`.
- **Battle power** (`CParameterUtility::tCharaData::CalcBP(CPersonStatusInfo)`, `battle_misc.cpp`): `sum_i 100 * p_i / ((lv1_i + 1.75 * lv70_i) / 2)`.
  - `p_i` are the six parameters at `CPersonStatusInfo`+0x430 + 0x30i.
  - `lv1` / `lv70` are the level-1 and level-70 rows of `master_character_common_parameter`.
  - A character with exactly the average stats of the mid curve scores 600.
- **Resource names** (`battle_files.cpp`, run while a battle loads):
  - `Effect/<id>.asf` / `.apk` / `<id>.aaf`; `Weapon/<id>.asf` / `.apk`; `Deco/<id>.asf` / `.aaf`.
  - `BG/<map>.asf` / `.aaf` / `.acf` with the map id first mapped through `CResourceReplaceManager::GetResourceName(id, 4)` (`master_replace_resource`, e.g. the gacha map `bg99_01`).
  - `EffectFileReplaceId` = `CHash32(GetResourceName(name, 5))`.
- **Sound queues** (`CheckSeQue`): the id's ten-thousands are flags (>= 80000, 50000, 20000, 10000, removed in that order and returned in bytes 7..4 of the second result word). Then:
  - 9000+ is a `BattleCommonSE` queue.
  - Otherwise the thousands pick one of the attack data's four sound packages (+0x68 + 0x18k).
  - If that package has no such queue, it falls back to the character's own package (+0x50e8).
- **Damage objects** (`CBaseDamageObject`, bullets; `battle_damage_object.cpp`):
  - Start copies the 0xac-byte start arguments and registers the object with its effect container and with the shooter's (or the arena's) time element.
  - It then plays the attached effect (+0x238) on the launch matrix with the shooter's attack-effect alpha, scales it by +0x200, and flattens it to a Y rotation for ground effects (model +0x2a1, which sets +0x25d).
  - Progress:
    - counts down the disappear timer (+0x258) and the life (+0x254 elapsed against +0x220);
    - at the end of life, plays the end effect (+0x240) or disappears, unless the shooter's attack still has live parts (vtable +0x1e8);
    - moves the object (vtable +0x1c0);
    - keeps ground-bound objects at y = 0.
  - Disappear plays the effect's end animation, or fades it out over 20 frames.
  - The collision is a capsule for linear, homing and boomerang bullets (types 0, 2, 6: radius from AttackParameter +0x50, length +0x1a4 x scale); otherwise the attack's own shape.
  - StartAttackSignal restarts the object as the next part when the bullet setups match (AttackParameter +0x38 / +0xc8). Otherwise it hands the signal to the shooter from the object's flattened matrix, lifted to at least y = 0.1.
- **Attacks** (`CBattleUtility`, `battle_calc.cpp`):
  - `CollisionAndEffectByAttackParameter` optionally plays the body effect and SE (`CCharacterObject::PlayAttackBodyEffectAndSE`), then dispatches by attack type (`AttackParameter`+0x38): bullets for the type mask 0x0fe3f286, collisions for 0x140009, direct damage for 0xc00.
  - **Bullets**: `CreateBulletArgs` fills `BaseDamageObject_StartArguments`:
    - The bullet kind by attack type: 0 linear, 2 homing, 6 boomerang (the collision assert names these three), 1 and 3 others. A shooter in abnormal state 7 fires straight shots, and uses its own rotation for types 22, 23, 25-27.
    - The launch matrix (given, or `BulletLaunchPosition`) times the parameter's rotation (+0xf0, `CMatrix::MakeRotate`) and offset (+0xe0).
    - The speed from +0x94, or `CBattleManager`+0x188 when that isn't positive.
    - The team: -1 when straight, else the given one, else the shooter's +0x76b4.
  - `CreateBulletByAttackParameter` then creates a `CBulletObject` named `<attack id>AttackBullet`, adds it to the scene and starts it.
  - **Direct damage** (types 10 / 11): type 11 hits one character (the given handle or the shooter's target). Type 10 hits party slots by the parameter's mode (+0x40):
    - 0: the opposing side (slots 0-3 against 4-11, by kind +0x76d4);
    - 1: the own side;
    - otherwise: all 12 slots.
    Each target gets `ReceiveAttack`, and the shooter gets `SendAttack` with the damage it returned.
  - `DeleteAttackObject(freeze)`:
    1. tells kind 5 and 8 scene objects to go away (vtable +0x38);
    2. freezes the rest (time rate 0) when `freeze` is set;
    3. stops every effect container's effects;
    4. clears the attack collisions.
- **Characters**:
  - The person resource names are `Character/<model>.asf`, `Motion/<motion>.apk`, `Character/<anim>.acf` and `Character/<package>.apk`, from the crypted person fields +0xe8, +0x168, +0x128, +0x1a8. An empty field gives an empty name.
  - The voice parameter and package are the person's current voice switch (`CUIUtility::GetPersonVoiceSwitchID`, `master_voice_switch`) while its period is open. Otherwise they are the person's own, and the switch is reset.
  - `CreateCharacterInfo::SetRoleToAssist(role, level)` picks the highest-level `master_assist_skill_parameter` row of the role's category that is not above `level`.
  - `FixWeaponNodeScale` scales the nodes listed (space-separated) in `master_weapon_kind.weapon_scale_node`.
- **Quirks kept**:
  - `DefAttribute` is called twice for each new minimum.
  - Out-of-range vector reads happen after the range assert, as in the guest.
  - The second draw of `CalcDamage` / `Damage` is taken even for types that don't use it.
  - The guard branch draws even when the perfect-guard chance is off.
- **Verification**: `battle/*` self-tests.
  - `CalcDamage`: 6,000 cases, 75% built from 3.7.0 enemy stats and skill powers, the rest edge values including NaNs and infinities.
  - The generator: 23,000 cases.
  - The actor functions: 1,500 synthetic scenes (real enemy stats, battle globals), comparing results, generator state and stub call logs bit for bit.
  - `battle/chardata`: every `CCharacterData` method, 25,200 cases on synthetic blocks, compared byte for byte.
  - `battle/calc-bp`, `battle/file-names` (17,164 cases over the 3.7.0 effect and map ids, strings compared including capacity), `battle/check-se-que`.
  - Not covered: the multiplayer branch of `Damage`, because `CMultiplayManager` doesn't exist offline and its singleton can't be faked safely while the game runs.

### Tutorial battle damage (`ms00_001`, agent tutorial-dmg, 2026-09-29)

The battle tutorial of the new-player flow (`--server inproc`, `--new-player`, a brand-new `--data` dir: no `Game.xml`, no `server.sqlite3`), played by `port/scripts/newplayer_session.sh`, with `SOA_TRACE` on `CCharacterObject::OnDamage` (the value the hit applies and the HUD shows, truncated to int). The 2026-09-29 runs also logged the native damage code's inputs and compared it with the guest: [`docs/history/notes-native-switches.md`](history/notes-native-switches.md).

**Inputs.**
- **Party:** the three NPCs of `master_mission_npc` (`tutorial_npc_role0001..3`, level 60), sent by the local server in `BattleParameter.PlayerCharacter` (docs/server-rules.md#tutorial-battle). All three roles are rank 4 (`master_rank` ×1.00). Their stats, before → after the fix below:

  | NPC (role) | weapon (`master_npc_base_parameter.master_item_id`) | HP | attack | intelligence | defence | hit | guard |
  |---|---|---|---|---|---|---|---|
  | `role_cp0501_b01a_6011` (sword) | `item_W01Sw_21` (attack 110) | 7,781 | 1,152 → **1,281** | 755 | 960 | 551 | 397 |
  | `role_cp0303_b01a_6033` (gun) | `item_W03Gu_11` (attack 120, intelligence 117) | 6,859 | 1,069 → **1,208** | 762 → **898** | 832 | 616 | 451 |
  | `role_cp0408_b01a_6024` (rod) | `item_W02Ro_19` (intelligence 120) | 5,989 | 749 | 1,434 → **2,045** | 653 | 516 | 407 |

  The base is round(`master_role` stat × `master_character_common_parameter`[60] / 100), e.g. HP 152 × 5,119 / 100 = 7,781. The additions are the weapon's `master_item` stats plus its factors and the roles' talents (`talent_000_130_000_020` → `factor30001` etc.), as the client's NPC model computes them.
- **Enemies:** `master_enemy_party` rows `ms00_001_Stage01_Enemy` (`cm128_b01c` ×2, `cm142_b01d`) and `_Stage02_Enemy` (`cm142_b01d`) have member level 0. The enemy level is `member level + MissionParameter.add_enemy_level`, or `overwrite_enemy_level` when set (`CPartyManager::InitializeEnemy`). The base level is the mission's **`recommend_level`**: `CStageManager::InitializeMissionData` copies it (`MasterMissionModel` element +0x338) to the stage manager, and `CStageManager::Progress` passes it to `InitializeEnemy`. For `ms00_001` that is **120**. Enemy stats are `master_enemy_base_parameter` % × `master_enemy_common_parameter`[120] (`CBattleUtility::CreateCharacterInfoByEnemyBaseId`, HP × (1 + enemy HP rate)):
  - `cm128_b01c`: HP 106% × 10,853 = 11,504, attack 1,598.48, intelligence 1,198.86, defence 1,260, hit 697.2, guard 770.24.
  - `cm142_b01d`: HP 32,559, defence 1,420, guard 830.

  This is all master data and client code, so level-120 enemies against a level-60 party is as designed.

**Formula check** (docs/notes.md "Battle formulas"). Every logged hit (136 before the fix, 103 after) lies inside `cancel × attr × (max((2·atk − def)/1.5, 0) × power + atk·[0.01, 0.02] + [0, 3])`, and the damage-rate sums are 0 in this battle. For example, the sword NPC's normal attack (attack id 1, power 0.5) on `cm128_b01c`:
- **Before:** (2·1,152 − 1,260)/1.5 × 0.5 + 11.5..23 + 0..3 = 360..374. Seen: 362-369.
- **After:** (2·1,281 − 1,260)/1.5 × 0.5 + 12.8..25.6 + 0..3 = 447..463. Seen: 453-462.

Other cases:
- **Guarded hits:** ×0.30, because `(100 − (guard − hit)/2.5) × 0.5` = 6.2 is clamped to `Battle_GuardCut_Min` 30. Seen: 109 before, 135-138 after.
- **Rod NPC's ice magic** (power 2.01, magic → intelligence) on `cm142_b01d`: attribute rate 0.95 (water resistance 1 → (100 − 5)/100). The result goes from 1,870 to 3,425.
- **Cancel bonus:** combo hits with cancel 1.5 / 2 scale as expected, e.g. attack id 9 power 0.62: 456 → 893-912.
- **No critical hits are possible:** rate = clamp(hit + 5 − guard, 0, 20), and every NPC's hit (516-616) is below the enemies' guard (770 / 830).
- **Every `OnDamage` value equals the preceding `Damage()` result** (103/103).
- **On screen:** the HUD shows these results truncated. One screenshot taken after the fix shows 1113 and 1119 (attack id 9, "Cancel Bonus 200%", logged 1,113.13 / 1,119.10) and 2626 (the special attack サイクロン・ブレード, attack id 8, power 2, cancel 1.5, logged 2,626.87; formula (1,736 + 12.8..28.6) × 1.5 = 2,623..2,647).

**Tutorial-specific code** (3.7.0 decompiles in `work/decomp/tutorial-dmg-*.resolved.c`). No damage value is forced. What the tutorial changes, while `CTutorialManager::IsStartTutorial()` is true:
- `CCharacterObject::OnDamage` leaves a party character (kind 1) at 1 HP on a lethal hit, so the party can't die.
- `CCharacterObject::SetRushGauge` doesn't fill the gauge (the tutorial scripts RUSH).
- `AIControlComponent::CheckNextAction` lets the party's AI (slots < 4) act only when `CBattleManager`+0x20f4 is set.
- `CPhase_TutorialNext::Net_NextPhase` builds `tCharaData::InitializeNPC` for `Tutorial_Character_1..3` (`master_global`) at step 0xf and discards them. The party the battle uses is the server's `BattleParameter.PlayerCharacter`.

**Finding and fix.**
- **The finding:** the local server built the NPCs with the roster formula and the first weapon of the role's kind, so the NPCs' own weapons (`master_npc_base_parameter.master_item_id`), their factors and the roles' talents were missing. Attack / intelligence were 10-30 % low, and the damage numbers were 20-45 % low. For example, the rod NPC's ice magic did 1,870 instead of 3,425 (+83 %).
- **The fix (server side, `client_npc_status` in `port/src/native/api/server_client_status.cpp`):** the server now asks the client's own NPC model for each NPC's status. The client has one: `MasterMissionNpcModel::CalculateParameter(master_mission_npc id)` → `MasterNpcBaseParameterModel::GetCharacterParameter`, which is what `tCharaData::CalcStatus` runs for an NPC `tCharaData`. The server takes the stats and the weapon (`weapon_master_item_id`, `weapon_id`) from it.
- **Test:** `server/tutorial-npc-status`.
- **Seeded save:** a new player and a seeded save now get the same NPC status. Before the fix, the seeded save's AP could differ by the favor AP bonus of the NPC's same role. The seeded path doesn't play the tutorial; in a replay outside the tutorial, the HP floor and the AI gating above don't apply.
- **Skills (agent cleanups, 2026-09-30):** `MasterRoleModel::AddSkillInfo` writes `skill1..3` (CPersonStatusInfo +0x250 / +0x2f0 / +0x390: the role's `master_skillN_id` if open at the level, else 0), `skill1..3_level` (+0x2c0 / +0x360 / +0x400: always 1) and the labels (+0x280 / +0x320 / +0x3c0, CryptString). They are the properties of those names; they looked missing because the result's property map is stale: `CalculateParameter` builds the status in its own frame and returns it with `CPersonStatusInfo(CPersonStatusInfo&&)`, which leaves the map pointing at the moved-from members (a destroyed stack frame, where the skills read 0 and the stats happened to survive). `client_npc_status` now reads every member at its offset (taken from the map of a freshly constructed and `Initialize`d CPersonStatusInfo), and copies the skills too. For the three tutorial NPCs the skills are unchanged (all three open at level 1, level 1). Test: `server/tutorial-npc-status` (checks the skills against `master_role` and against the raw members).

## Battle presentation

What the player sees around a battle, from the port (`port/src/native/battle/battle_nowloading.cpp`, `battle_camera.cpp`; reached with `port/scripts/battle_session.sh`, see port/README.md "Reaching battle, gacha and the debug windows").

**Loading screen (`CNowLoadingBattle` : `CNowLoadingBase` : `CUIObject`).** `CPhase_Battle` opens it before the stage loads and between stages. It has four Cocos scenes:
- `+0x148` the tips window (`pop1`, `pop2/window/Text`, `pop2/window/tips_banner`, `pop2/Node_download`): a random `master_parameter_loading_message` tip, changed every 600 frames (`UpdateTipsText`);
- `+0x150` the "Now Loading…" animation (`nl`, looped, id at `+0x168`);
- `+0x158` the download plate (`dl_plate`, progress bar `LoadingBar_1` at `+0x160`);
- `+0x188` the battle part: the mission map background (`Node_bg`), the stage track `stage_base` (stage icons and lines, `UpdateStageData`: "STAGE n/m" from `SetNextStage`), the SD character walking along it (animations `sdchara` then `loop`, `sd_stop` once the stage is cleared, id at `+0x198`), a `dialog`, and the multiplayer `loading_status` panel (players 1-3 with face, name, progress and ok / AI / disconnected icons).

`CNowLoadingBase::Progress` is a fade state machine at `+0x128`: 0 closed → (open requested, scenes loaded) 1 fading in over `+0x12c` frames (default 60) → 2 shown → (closed) 3 fading out → 0. Each state change goes through the virtual `RequestNextPhase(n)`; each frame calls the virtual `SetOpacity(fade)` and `ProgressChild(fade)`. `CNowLoadingBattle::ProgressChild` fades the multiplayer status panel in (state `+0x178`: 1 wait for the multiplayer cache, 2 fade in, 3 shown) and polls which players dropped (`UpdateDisconnect`); `SetOpacity` also fades `Node_bg`, `stage_base` and `dialog`.

Quirk: in the fade-in state `Progress` also runs the "shown" step in the same frame, so `ProgressChild` is called twice per frame (with the fade value, then with 1.0) and the tips timer advances by two frames' time. Ghidra's decompilation of `CNowLoadingBattle::SetOpacity` drops two of its three `CUIUtility::SetOpacity` calls (the in-frame test caught it).

**Camera (`CArenaCamera`).** The front end over the active controller (`+0x08`, a `CNormalCamera` : `CFieldBaseCamera` in battle; `CameraMode(mode, manual)` stores the requested mode 0/1 at `+0x18` and the controller's manual flag, and sets a 0.005 blend). `InitializeCamera` resets the parameter blocks at `+0xc0..+0x1d8` (position, look-at, up, zoom). `GetOriginalCamera` is the map model's own camera node (named by the string at `+0x30`, if `+0x28 >= 0` and the map is loaded), whose lens (f-stop, focus) the controller copies to the system camera. `PositionCamera` / `PositionLookAt` read the main task's camera parameters.

**HUD owner (`CBattleUIManager`, a member of the battle manager).** It owns the in-battle screens, each a `CUIObject` with its UI id next to the pointer: `+0x10` `CBattle` (the HUD proper: party panels, skill buttons with their handles at `+0xa9c` and wait-animation flags at `+0xa90`, the target guide flag `+0xc08`, the battle-info log), `+0x20` `CBattleAnime` (battle start / end telops, skill cut-ins), `+0x30` `CPauseMenu`, `+0x40` the result screen, `+0x50` the rush-combo UI, `+0x60` `CBattleTransScene` (the white flash between stages), `+0x70` the boss cut-in, `+0x80` `CStampUI`. `+0x00` is its state (3 initialized, 5 ready). The `r*` / `cr*` accessors assert on a null screen (a log line in the release build) and return it anyway; the skill-animation and battle-info calls are no-ops without a `CBattle`. `GetTappedSkillHandle(i)` treats an out-of-range slot as "the selected slot" (`+0xacc`). `CPauseMenu::Progress` only runs while the arena is in its main phase; `CBattleTransScene` counts a delayed white-end (`+0x1ac`) down by the arena's frame time (float subtract, truncating convert) and then stops its animation.

Still guest: `CNormalCamera` (the battle camera motion, ~12 KB of FP), `CArenaCamera::ProgressCamera`, `CBattleUIManager::Initialize` / `Progress` / `BattleProgress` (15 KB) / `Start` / `Release` and its texture and icon loaders, `CBattleAnime`, the rest of `CBattleTransScene` and `CPauseMenu` (setup, open / close, continue).

The canned `FakeApi/*.msgp` responses aren't shipped (see the FakeApiCaller section), so no real response bodies exist to replay. The handlers never run in offline play today.

## Debug windows (Framework::CDebugWindows and friends)

The framework ships a complete developer debug-window system, but the release build never switches it on: nothing calls `CDebugWindows::Initialize`, `CDebugMenu::Initialize`, `CDebugWindow_SoundPreviewer::Initialize`, the `CDebugWindowsScript` constructor or any `CDebugPrimitiveManager::Add*`. The port option `debugwin:W:H` (control command, `port_debug.cpp`; scripted in `port/scripts/debug_session.sh`) calls `Initialize` and then `CDebugWindows::Progress(1/30)` every frame; `call:` can then create windows.

**What's in it, and what isn't.** Only generic tooling survives; the game-specific debug menus were compiled out:
- No battle, scene-jump, gacha or cheat tools exist in `libSOA.so`. `CTest_DebugMenu` is empty (its `Initialize` / `Progress` / `Release` are single `RET`s), and `CDebugMenu::AddPiece` is only called by `CDebugMenu::RunPiece`, which has no callers.
- The only prebuilt window is `CDebugWindow_SoundPreviewer` ("Framework: [ Sound Previewer ]", resource name `windowResourceName_SoundPreviewer`): a "Sound Play Log" log console with `NumPlaying[%d]` status and `%02d:%02d:%02d: SE[%s]` / `BGM[%s]` lines. `CSound` feeds it (`AddSELog` / `AddBGMLog`, see `audio_csound.cpp`) when its singleton exists, which it never does in the release build.
- The `Debug*Info*` classes (`CDebugGearGenerationInfo`, `CDebugBonusInfoMap`, `CDeepSpaceDebug*`, ...) are master-data/API parse types for server debug responses, unrelated to the windows.

**Creation.** `CDebugWindows::Initialize(W, H)` ignores both arguments. It fills the default skin (`gMakeDefaultSkin`: colours at `gpSkin+0x00..0x70`, e.g. `+0x48` the cursor text colour, `+0x70` `0xff0f090b`; the button glyphs `$[cd0e020]x$[cffffff]` close, `...o...` and `...v...`, where `$[cRRGGBB]` is the text colour escape), allocates the `CManager` singleton (0x68 bytes) with a 50-slot window table, and creates the mouse cursor, a `CTextScreen` showing `^`.

**Windows.** `CreateNewWindow(name, id, x, y, w, h, resourceName, noActivate)` / `CreateTabWindow(..., tabs)` take the first free slot, give it the next handle (1, 2, ...), `new` a `CWindow` (0x1c20 bytes) or `CTabWindow` (0x1c40), `Initialize` it with the rect `{top=y, left=x, bottom=y+h, right=x+w}` (`CRect` is top, left, bottom, right), post message 1 (created) and activate it. A `CWindow` embeds its controls: two `CButton`s (close / pause), a title `CTextBox`, and a `CControlContainer` holding the user's controls (`CButton`, `CCheckBox`, `CNamedCheckBox`, `CRadioButton`, `CVRadioButtons`, `CHSlideBar` (int / float), `CValueEdit` / `CValueEditFloat`, `CTextBox` / `CTextBoxLine`, `CBoxLine`, `CHLine` / `CVLine`, `CListBox` (pull-down), `CListView`, `CColorEdit`, `CColorRect`, `CTextureView`, scroll bars). They draw with `CSprite` quads (`tSpriteParameter_Quad`) and `CTextScreen` / `Aska::TextLegacy` text, in z bands `nZOrder_Desktop`, `_OnWindow`, `_ActiveWindow`, `_Pulldown`, `_MouseCursor`. In the port the frames draw but the title and control text don't (seen by `reach`; not investigated).

**Input and messages.** Each window has a `CMessageQueue` (a `std::deque` of 12-byte `tMessage {type, a, b}`) and a virtual `Procedure(tMessage)`. Every `Progress` the manager:
1. reads the mouse from `Framework::CMouse` (the touch panel drives it: `CMouse::InputFromPanel`);
2. pumps each window's queue into its `Procedure` until it's empty or a quit (3) was handled;
3. sends 8 (new frame) to every window;
4. hit-tests the cursor against the windows in table order (the table is kept in activation order, so this finds the topmost window): the hit window gets 7 (mouse over, x, y), 0xb / 0xc (wheel up / down) and, on a press, is activated (4) and gets 5 (press, x, y). A press on the 16-pixel title strip of a draggable window (`+0x25` bit 0) starts a drag;
5. sends 6 (release, x, y) to every shown window on a release;
6. moves the dragged window with the cursor (clamped at 0);
7. renumbers the z order and re-places every window.

In the port, `CMouse` gets the touch panel's position in the game's 810x1440 render pixels, and its left button only from taps: a touch drag moves the cursor without pressing, so windows can be activated by tapping but not dragged. `port/scripts/debug_input_session.sh` taps overlapping windows to the front.

Controls report changes through `CManager::LastModifiedControl(window, control)`, which callers poll with `pLastModifiedControl` / `LastModifiedWindow` / `IsModifiedAnything`. `IsPause(bool)` hides all windows and stops input.

**Script.** `CDebugWindowsScript::Compile(text)` builds windows from a line-based script (`;`-terminated orders, words split by `Words`), with the orders `CreateNewWindow`, `DestroyWindow`, `CreateButton`, `CreateCheckBox`, `CreateNamedCheckBox`, `CreateHSlideBar`, `CreateHSlideBarFloat`, `CreateValueEdit`, `CreateValueEditFloat`, `CreateTextBox`, `CreateTextBoxLine`, `CreateTextBoxLineUp`, `CreateBoxLine`, `CreateBoxLineUp`, `CreateVRadioButtons`, `CreateListBox`, `CreateListView`, `CreateListViewSingle`, `Enable/DisableAllListViewItems`, `Enable/DisableListViewItem`, `CreateColorEdit`. The Sound Previewer is built this way.

**Log console.** `CDebugLogConsole` keeps lines in a character ring plus a ring of line starts, with back scroll and horizontal scroll; `Draw` hands each visible line to the virtual `DrawLine`. `CDebugWindows_LogConsole` is the windowed version (a window plus a text box per line).

**Primitives.** `CDebugPrimitive::C*` objects build a mesh through `Aska::DirectAofHandler` (`Open`, `BeginMesh`, `AddVertex`, the 16-bit index buffer, `EndMesh`, `Close`, or its `Sphere` / `Box` / `Capsule` builders) and wrap it in an `Aska::AofObject` registered with the object manager. `CDebugPrimitiveManager` keeps nine pools of them (lines, spheres, line spheres, boxes, line boxes, ...), each a list with a cursor: every frame `Reset()` hides everything and rewinds the cursors, and `Add{Line, Axis, Box, LinesBox, Sphere, LinesSphere, LinesHemisphere, Capsule, LinesCylinder, Rect, Text}` take the next primitive of their pool (making one when the pool is used up), place, colour and scale it. So debug shapes live for one frame and are recycled. Nothing in the game adds any. Quirk: `Reset` doesn't rewind the last pool's cursor before its hiding pass, so it only hides that pool's primitives past last frame's cursor (and on a fresh manager, before `DeleteAll`, the null cursor crashes).

**Guest quirks found while porting** (kept in the native code):
- `UpdateActiveWindow(0)` matches a free slot and pushes a message to its null window, which crashes.
- `pTabWindow`'s final handle search has no bound.
- `CWindowBase::Release` detaches only the first control it finds before freeing the queue (`RemoveAllControls` detaches them all).
- `CreateNewWindow` doesn't clear the resource-name field before asserting that it's empty (`operator new` memory).
- The mouse position is rounded through `u32` (`fcvtzu`), so negative coordinates clamp to 0 for hit tests, and `CMouseCursor::X/Y` return `u32`.
- `CDebugLogConsole::Draw` measures a line with `strlen` at its ring position, which doesn't wrap at the ring's end.
- Ghidra's decompilation of `CManager::Progress` drops the whole input section as "unreachable", and that of `CMouseCursor::Update` drops the cursor drawing, so work from the disassembly.

## What the offline build changed, and the campaign restore (history)

Moved to [`docs/history/notes-3.8.0.md`](history/notes-3.8.0.md): the 3.7.0-vs-offline-build comparison (clock, missions, party building, adjutant select, title and login, resources, the layout check) and the 2026-09-29 investigation of the original campaign (3.7.0 flow and classes, the server data it needs, the restore). The port runs the 3.7.0 client, so those screens and flows are the client's own now.

## Tower layout (試練の遺跡, agent `a11-tower`, 2026-09-30)
The tower was closed by 3.7.0 (`CParameterUtility::IsOpenTowerMission` returns 0 in both 3.7.0 and the offline build). The opt-in `--restore-tower` opens it; the tower menu then lists floors and its battles play. Session `port/scripts/tower_session.sh`. The changes are in docs/client-changes.md ("The tower (試練の遺跡) opened", "Tower banner rows added to the client's master copy") and docs/server-rules.md#tower.

**Where the tower's UI comes from.** `CExtraDungeonMenu::Progress` builds a `CTowerMissionMenu` (0x530 bytes; the constructor is inlined there and sets the tab field +0x448 to 2 and +0x444 to -1) when part 0 of `MissionUtility::GetExtraDungeonList` is picked. That part exists only while `IsOpenTowerMission()` is true. `CTowerMissionMenu::Initialize` adds three Cocos scenes, which the event menu (`CEventMissionMenu`) uses too:

| Scene | Menu field | What the tower uses from it |
|---|---|---|
| `mission_menu_common` | +0x138 | `banner`, `btn_trade`, `btn_achieve`, `btn_restart`, `btn_restart_old`, `planet_name`, `btn_ranking`, `Button_back`, `Node_1/Text_1`/`Text_2` (the title `uimsg_tower_top_name` / `_info`), `Button_planet_multi` (hidden), `bg` (the background `Image/ubg05_01_01.aif`) |
| `eventmission_top` | +0x128 | the floor list: `all/list` → `list` (ListView), `slider`, `Node_tab` (hidden), `pickup_banner/image`; the header banner slider (`header_gp/banner/...`), `Button_cointrade`, `Button_achievement` |
| `mission_list2` | +0x130 | a floor's missions: `all/list/ListView_1` (items `Button_mission_%d`, `.../new/icon_vanish_1`), `Slider_1`, `all/banner`, `all/list/banner`, `vanish_plate`, and `play_plate/0`..`3` |

The node names are from the 3.7.0 decompilation of every `CTowerMissionMenu` member (`tools/decomp.sh --v370`; the inline string constants resolved from the ELF). All lookups but one family are null-checked, asserted on nodes that exist, or loop until a miss. The exception is `play_plate/0`..`play_plate/3` in `Setup`, looked up in `mission_list2` and written unchecked: plate *n* is shown when the tower tries left (`StaminaUtility::NowStamina(1)`, CParameterManager+0xc48, max 3) equal *n*, and plate 3 for 3 or more.

**No other copy of the layout exists.** Every `.csf` in `work/download-3.7.0` (352 decoded: ADLD-XOR with the `%x` of CHash32(path), then SLZ zstd/deflate chunks, then an `ISF` container of `<name>.msgp` (the Cocos Studio 3.10 node tree in MessagePack), `.aif` and `.csv`) and in both APKs (the offline APK's builtin_data and the 3.7.0 APK's) was searched for `play_plate`: there is none. The download's manifests (`manifest/etc2/hi/version_latest_{Bulk,Individual,ep1-3}.bin`) list each UI file once, all already downloaded; there is no older version and no tower-only UI file. The 3.7.0 `mission_list2` node tree was re-authored after the tower closed (its atlas still has the plates' textures, below): it has the event menu's `vanish_plate`, and a bare `RLM_` image as the list's first child. Its nodes: `Scene/all/list/{ListView_1/RLM_, Slider_1, banner/{Panel_touch, time_limit_blue, icon_affection, Button_achievement, Button_cointrade, vanish_plate}}` plus a hidden root `list` button (the old item template: `Battle/{mission, mission_title, mission_text*, vanish, icon_story, new, clear, icon_limitbadge}`, `no_countinue`).

**What actually blocked the floor list.** The missing layout nodes were not the cause. The WIP's stand-in for *every* missing name hid two other problems:
1. **Banners.** `MissionUtility::GetEventAreaList(now, 2, …)` got the five areas from the server (the `TowerArea` map had 5 entries) and found them in `master_tower_area`, but `MissionUtility::tAreaInfo::tAreaInfo` zeroes the area id when the area's `master_banner_id` isn't among `CUIUtility::CollectMasterBanner`'s rows (`SELECT * FROM master_banner`), and the list drops such areas. The 3.7.0 master lacks `banner801`..`banner805` (the permanent `tower_01`..`05`), while their images `Image/banner_TrialSpace_001`..`005.aif` are in the download. Fix: stand-in `master_banner` rows in the client's master copy (server side; the image name follows the 16 surviving tower banner rows).
2. **The mission buttons.** The item callback (`SetupEventMissionSelect`'s `function<bool(int,int)>`, at 0x1b55328 in the offline build) does `CUIUtility::GetButton(scene, "all/list/ListView_1/Button_mission_%d")` and returns early when it fails. The items are cloned from the common-resource scene's `Button_mission` (`common_resource.csf`), which `CEventMissionMenu::Initialize` adds with `CUIObject::AddCommonResourceScene()` and `CTowerMissionMenu::Initialize` never does. The tower code was updated to `SetupCommonResource_ButtonMission` like the event menu, but not its `Initialize`. Without it the list shows `mission_list2`'s bare plates, which ignore taps. Fix: call `AddCommonResourceScene()` after the tower's `Initialize`.
3. The WIP's catch-all stand-in also made `SetupEventMissionSelect`'s probe loop (`Button_mission_%d/new/icon_vanish_1` until a miss) endless. The stand-in is now limited to the four `play_plate` names, only inside `Setup`.

**Rebuilding the plates in code** (designed, not done). The textures survive: the 3.7.0 `mission_list2.aif` atlas still has `plate_challenge_0.png`..`plate_challenge_3.png` (60×80) and `plate_challenge_all.png` (65×69) (`mission_list2.csv`), unused by the re-authored node tree. So the four nodes could be rebuilt: in the `Setup` wrapper, before the guest body, when `mission_list2` has no `play_plate`, make a `play_plate` node under `all/list/banner` (next to `vanish_plate`, which the tower's Setup looks up and hides) with four image children `0`..`3`: clone `vanish_plate` (`CCocosImage::Clone` / `CopyTo`), rename, `CUIUtility::SetImageResource(image, "plate_challenge_<n>.png")`, place it (the original position is unknown: a guess, e.g. where `vanish_plate` sits), `CCocosNode::AddChild`. Left out for now: the position would be invented, the plates only repeat the try count, and the server doesn't count tries down (so plate 3 would always show); the extra-dungeon banner already shows "3/3". The hidden stand-ins keep the guest's writes harmless.

**Seen working** (`tower_session.sh`): home → スフィア211 → the extra-dungeon menu with 試練の遺跡 3/3 and スフィア211 → the floor list (the five areas' banners with NEW, and the header banner slider) → 呪い → 試練の遺跡1階(呪い)【初級】 (level 40, 1 stage, コンティニュー不可) → the detail (first-clear reward ×21 coins, reward ×4) → rental list → party → the battle → MissionEnd (first clear, 2F unlocked) → result pages → the floor's list with 1F CLEAR and 2F NEW. Not served: the ランキング and イベントメニュー buttons (event-menu features); the try count isn't decremented (docs/server-rules.md#tower).

**Debugging aids added on the way:** `SOA_TRACE` accepts `0x<ELF vaddr>` for unnamed functions such as lambdas (`runtime/src/core/trace.cpp`). Tracing a function with stack arguments (more than 8 integer arguments, e.g. `tAreaInfo`'s constructor) crashes the guest: the trace thunk doesn't forward them.
