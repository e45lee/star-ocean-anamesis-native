# `lib_sqlite`: SQLite 3.13.0 (the game's bundled copy) replaced by the host SQLite

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/lib_sqlite/scope.txt`](../../../decomp/lib_sqlite/scope.txt).
- Decompiles and the function list: [`port/decomp/lib_sqlite/`](../../../decomp/lib_sqlite/) (`symbols.tsv`; `tools/decomp.sh --into lib_sqlite/<topic>`).
- Types: [`lib_sqlite_layout.h`](lib_sqlite_layout.h); for Ghidra, `tools/subsystem.py export-types lib_sqlite` -> `port/decomp/lib_sqlite/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

## The boundary

The game's own code calls SQLite in one place: `Aska::Yayoi::SQLiteDriver` (its `EntityObject` reads
the rows). `tools/callers.py` over every exported `sqlite3_*` of `work/libSOA-3.7.0.so` (BL targets,
direct and through the PLT; `tools/xref_got.py` for the GOT slots) finds 20 functions called from
outside SQLite, all from the driver, and no custom function, collation, VFS, hook or `sqlite3_config`:
SQLite runs with its defaults. The master DB is the only database (docs/notes.md "Master DB load"):
`CStaticTransaction` decrypts the ADLD `basmaster.sqlite3` to `files/download/temp.sqlite3` with its own
code (`CFileLoader`'s decrypt function, not SQLite), then opens `:memory:`, `ATTACH DATABASE
'<android path>' AS newdb`, `create table X as select * from newdb.X` per table, `DETACH`; the
connectors run `SELECT * FROM master_x WHERE id=?` and the other `SELECT` strings of the lib, binding every
parameter with `sqlite3_bind_text` (SQLITE_STATIC).

Those 20 functions plus `sqlite3_free` (for `sqlite3_exec`'s error message, which the host SQLite
allocates) are natives calling the host SQLite (vcpkg's `sqlite3`, 3.45.1 with Ubuntu's options: the one
the server links). The rest of the guest's SQLite (797 functions, 505 KB) is dead code: nothing reaches
it outside the live check.

What crosses (lib_sqlite_api.cpp):
- **Handles** (`sqlite3*`, `sqlite3_stmt*`, `sqlite3_value*`) are opaque to the game: host objects. The
  driver keeps them (+0x18 db, +0x20 the one live statement) and passes them back; no 3.13.0 struct is
  read by guest code (lib_sqlite_layout.h has none).
- **Strings and blobs** SQLite returns (column names, `sqlite3_value_text` / `_blob`, `sqlite3_errmsg`)
  are host memory the guest reads in place (identity-mapped); their lifetimes are SQLite's, as before.
  `EntityObject::Store` keeps `sqlite3_column_name`'s pointers while the statement lives: the same rule.
- **Paths**: the file names are the guest's Android paths. The natives open every database on the
  guest-path VFS (lib_sqlite_vfs.cpp: the host's default VFS with `xFullPathname` mapping the name through
  `core/vfs.h` `host_path`, as the HLE `open` / `fopen` do); an `ATTACH` inherits it, so `ATTACH DATABASE
  '/data/data/<pkg>/files/download/temp.sqlite3'` reads the file the guest's own I/O wrote.
- **Callbacks** are guest functions: `sqlite3_exec`'s row callback runs through `guest_call` (the game
  passes none); `sqlite3_bind_text`'s destructor: SQLITE_STATIC / SQLITE_TRANSIENT pass through, a guest
  function is called when the host SQLite releases the text (a host destructor looks it up by the text's address), as 3.13.0 does: a failed bind at once, a NULL text that binds never (the game passes SQLITE_STATIC).
- **Allocators**: SQLite's memory is the host's; `sqlite3_free` is bound for what it hands out.

**Versions.** The host is 3.45.1, not 3.13.0. A newer planner may order rows differently where a query
has no `ORDER BY` or ties in it; the game's queries were compared against the guest's 3.13.0 on the
3.7.0 master (the tests below: every row, in order, equal, including `SELECT * FROM master_party_symbol
ORDER BY page_no DESC LIMIT 1`, where 7 rows tie), and live over the four flows (below). So no pin of
3.13.0 via FetchContent is needed. Differences that remain, none of which the game observes:
- `sqlite3_errmsg`'s texts (e.g. `SELECT * FROM `: 3.13.0 `near " ": syntax error`, 3.45.1 `incomplete
  input`). Its one caller, `SQLiteDriver::_Prepare`, drops the text (a failing prepare then closes the
  database, as before).
- Host build options (cmake/vcpkg-triplets/x64-linux.cmake): `SQLITE_USE_URI=1` (a `file:` name would be
  a URI; the game's names are plain paths), `SQLITE_LIKE_DOESNT_MATCH_BLOBS` (no `LIKE` in the game's
  queries), `SQLITE_SECURE_DELETE`.

## Types (classes with their methods attached)

None: the boundary is SQLite's C API, and its handles are opaque (lib_sqlite_layout.h). The bound
functions are free functions (`NATIVE_FUNCTION`-style registration, one hook per function).

## Natives

21 functions, family `lib_sqlite` (`soa --list-native | grep lib_sqlite`), in
[`lib_sqlite_api.cpp`](lib_sqlite_api.cpp); the guest-path VFS in [`lib_sqlite_vfs.cpp`](lib_sqlite_vfs.cpp).

| Guest symbol | Caller in the game | Bridged | Differential tests | Live check: mismatches / checks |
|---|---|---|---|---|
| `sqlite3_open` | `SQLiteDriver::DoOpen` | the name (guest-path VFS) | master-*, bridge | 0 / 8 |
| `sqlite3_close` | `~SQLiteDriver`, `Close`, `_Prepare`, `DoOpen` | | master-*, bridge | 0 / 4 |
| `sqlite3_exec` | `BEGIN;` / `COMMIT;` / `ROLLBACK;` of the driver | row callback (guest), error message (host memory) | bridge | not called |
| `sqlite3_prepare_v2` | `SQLiteDriver::_Prepare` | | master-*, bridge | 0 / 3,654 |
| `sqlite3_errmsg` | `SQLiteDriver::_Prepare` (dropped) | | master-* (both have one), bridge | not called (text logged, not compared) |
| `sqlite3_bind_parameter_count` | `SQLiteDriver::_Prepare` | | master-*, bridge | 0 / 3,654 |
| `sqlite3_bind_text` | `SQLiteDriver::_Execute` | destructor (guest) | master-*, bridge | 0 / 2,058 |
| `sqlite3_step` | `_Execute`, `EntityObject::Fetch` / `Serialize` | | master-*, bridge | 0 / 606,712 |
| `sqlite3_reset` | `_Execute`, `EntityObject::Serialize` | | master-*, bridge | 0 / 7,778 |
| `sqlite3_finalize` | `_Prepare`, `Close`, `DoOpen`, `~SQLiteDriver` | | master-*, bridge | 0 / 3,650 |
| `sqlite3_column_count` | `EntityObject::Store` | | master-*, bridge | 0 / 2,214 |
| `sqlite3_column_name` | `EntityObject::Store` | | master-*, bridge | 0 / 38,216 |
| `sqlite3_column_value` | `EntityObject::Get*` / `Serialize` | | master-*, bridge | 0 / 12,970,109 |
| `sqlite3_value_type` | `EntityObject::Get*` / `Serialize` | | master-*, bridge | 0 / 12,970,109 |
| `sqlite3_value_int` | `EntityObject::GetInteger` / `GetShort` / `GetTinyInt` / `Serialize` | | master-*, bridge | 0 / 1,940,948 |
| `sqlite3_value_int64` | `EntityObject::GetLong` | | master-accessors, bridge | not called |
| `sqlite3_value_double` | `EntityObject::GetFloat` / `GetDouble` / `Serialize` | | master-*, bridge | 0 / 165,844 |
| `sqlite3_value_text` | `EntityObject::GetString` / `GetStringLength` / `Serialize` | | master-*, bridge | 0 / 2,645,042 |
| `sqlite3_value_blob` | `EntityObject::GetData` / `GetFieldLength` | | master-*, bridge | not called |
| `sqlite3_value_bytes` | `EntityObject::GetData` | | master-*, bridge | not called |
| `sqlite3_free` | (none: `sqlite3_exec`'s error message) | | bridge | not called |

**Differential tests** (`soa --selftest lib_sqlite/`; natives aren't installed there, so `guest_api()`
is the guest's 3.13.0 and `native_api()` thunks to the same hook functions the natives install; both
driven through guest calls):
- `lib_sqlite/master-queries`: the 3.7.0 master (`data/basmaster-3.7.0.sqlite3`) staged at an Android
  path and loaded the game's way on both sides (`:memory:`, `ATTACH` by the guest path, `create table ...
  as select`, `DETACH`; the 176 table names compared). Then the corpus: every `SELECT * FROM ...` string
  of `work/libSOA-3.7.0.so` (read from the file), the connectors' `__TABLE_NAME__` templates for every
  table with the columns, plus `SELECT * FROM t` and `... WHERE id=?` per table; placeholders (`?` bound
  as text, `%s` / `%u` / `%d`, a trailing `IN (` / `= ` the code completes) filled with up to 6 tuples of
  the master's values plus one matching nothing. 6,140 queries, 580,300 rows: column names, return codes,
  types and the values as the game reads them (the typed getter per `sqlite3_value_type`), row by row in
  order: equal. ~7 s.
- `lib_sqlite/master-accessors`: the same with every accessor of every value (int, int64, double bits,
  text, bytes: the conversions), up to 3 tuples per template: 3,821 queries, 561,091 rows, equal. ~11 s.
- `lib_sqlite/bridge`: one scripted session on each side: `sqlite3_exec` with a guest row callback and
  its argument, a callback abort (`SQLITE_ABORT`), the error message and `sqlite3_free`, a guest
  destructor on `sqlite3_bind_text` (called when SQLite releases the text: the same calls at the same
  steps as 3.13.0; a NULL text never, a failed bind at once), SQLITE_TRANSIENT with the buffer
  changed after the bind, explicit lengths, an out-of-range bind, `pzTail`, blobs (also empty), NULLs,
  `1e300`, `sqlite3_finalize(NULL)`.
- `lib_sqlite/live-check`: the live check on the natives: the bridge session shadowed (checks, no
  mismatch), then a shadow diverged on purpose (a row inserted on the host database only) is caught.

**Live check** (`soa --live-check lib_sqlite[:out=FILE]`, lib_sqlite_api.cpp): a shadow run. Every database
the game opens is also opened in the guest's own SQLite (the original code, through the hooks'
trampolines), and every call is repeated there on the shadow handles; return codes, column names,
strings and blobs byte for byte, doubles bit for bit must match (so rows and their order do).
`sqlite3_exec`'s rows reach the shadow through a replaying callback that compares them and gives the
host callback's answers. Inside a shadow call the guest SQLite's own calls to its exported functions
(through the PLT) land on the hooks, which then run the originals (`t_guest`). `out=` gets per-function
counts. (`every=` / `only=` / `budget=` don't apply: the shadow must see every call to stay in step.)

Results (2026-10-04, `--live-check lib_sqlite:out=FILE` over the four flows of port/REBUILD-QUEUE.md:
`rebase_inproc_session` (login -> home), `battle_session`, `gacha_session`, `campaign_session` (story),
each PASS): **0 mismatches in 31,360,000 checks**, 0 skipped (the counts in the table: the flows' `out=`
files, written every 20,000 checks, so the last few calls of each run are not in them). Not called in
these flows (the tests cover them): `sqlite3_exec` (the driver's transactions), `sqlite3_errmsg` (no
prepare fails), `sqlite3_value_int64` / `_blob` / `_bytes` (no `GetLong` / `GetData` column read),
`sqlite3_free`.

**Guest time** (`SOA_PROFILE` at 1000 Hz, `port/scripts/rebuild_queue.py`, the four flows of
port/REBUILD-QUEUE.md, run side by side on this machine): before (main, 669ac6e) the guest SQLite was
15,829 of 293,654 busy samples, **5.4%** (login 5.3%, battle 5.5%, gacha 4.0%, story 6.4%); after, **0**
(the guest SQLite no longer runs). The host SQLite in its place: 4,820 samples of the natives (1.4% of
346,631; `sqlite3_step` 4,584, `sqlite3_prepare_v2` 135, the rest under 100), so the work costs about a
third of what it did under the JIT; guest JIT code 80.6% -> 79.8% of busy samples, natives 1.0% -> 2.3%.
(The after runs shared the machine with other agents' sessions: more busy samples for the same flows, so
the shares compare, the sample counts less so; fps not measured: the battle is paced by the session.)

**Since yayoi's driver went native** (port/src/native/yayoi/README.md, family `yayoi_sqlite`): the driver
calls the host SQLite directly, so these natives are reached only by guest code that still calls
`sqlite3_*` (none in the flows) and by yayoi's live check (its shadow drivers run the guest's driver code
over these natives). Don't switch both live checks on in one run.

## Dependencies

None in the guest: the boundary's only caller is `yayoi` (`Aska::Yayoi::SQLiteDriver`, port/REBUILD-QUEUE.md
wave 4), which can be ported against the host SQLite directly (its natives then call `sqlite3_*` of the
host, and these hooks only serve what is still guest code). Host: vcpkg's `sqlite3` (subsystem.cmake).

## RE notes

- `SQLiteDriver` (docs/notes.md "Master data"): +0x18 `sqlite3*`, +0x20 the one live statement
  (`_Prepare` finalizes the previous one), +0x10 the last bound `QueryParam*`, +0x28 in a transaction,
  +0x29 a transaction requested, +0x30 the current `DBAddress*`, +0x60 prepared. A failing
  `sqlite3_prepare_v2` closes the database (after `ROLLBACK;` when in a transaction). `_Execute` binds
  each `QueryParam` (stride 0x28: text at +0x10, length at +0x18) with SQLITE_STATIC and steps while
  `SQLITE_BUSY`; `EntityObject::Store` maps column names to indices in an `Aska::THashMap<const char*,
  int>` (SpookyHash V2 of the name), keeping SQLite's name pointers.
- The guest's SQLite calls its own exported functions through the PLT (e.g. `sqlite3_exec` ->
  `sqlite3_prepare_v2` / `sqlite3_step` / `sqlite3_column_text`), and uses `sqlite3_free` as a destructor
  pointer (GOT): with these hooks installed, any guest SQLite code that still ran would reach the natives
  with guest handles. Nothing does outside the live check, which routes those calls to the originals.
