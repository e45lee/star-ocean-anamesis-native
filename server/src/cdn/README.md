# server/src/cdn: what the server's CDN serves

The content of the CDN both server modes serve to the client (soa-server over HTTP, `../../net/cdn_http.cpp`; soa in memory, `port/src/native/api/server_cdn.cpp`). Public API: `../../include/soaserver/cdn.h`, `adld.h`. Rules and labels: docs/server-rules.md#cdn.

| File | What |
|---|---|
| `tree.cpp` | `cdn::Tree`: `Tree::build` as the steps of `TreeBuilder` (a friend of `Tree`): `read_version_bin`, `serve_master`, `serve_english` (`--english`: the English master into the generated root `<scratch>/lang-en`), `add_standins` (the stand-ins, `Options::member_roots`, then the generated root), `read_manifests`, `collect_bundles` (+ `member_of`, `add_standin_bundle`), `hash_bundles` (threads, the bundle-hash cache), `renew_ids` (the revision, the version ids, the manifests' files), `write_version_bin`; `Tree::lookup` (the URL paths), `summary`, `bundle_of`; the `*_from_config` functions |
| `bundle.cpp` | the "\0ISF" bundle image (`bundle_head`, `bundle_stream`, `bundle_size`, `bundle_bytes`, `bundle_sha1`), `Response` (`size`, `read`, `open`: a body read in pieces, `PieceReader`), `sha1_hex` |
| `served_master.cpp` | `make_served_master`: the 3.7.0 master with the modules' `ClientMaster` overrides (`apply_client_master`), VACUUMed, ADLD-AES packed; `make_english_master`: its copy with the English text table's English (`--english`, docs/server-rules.md#english) |
| (the download) | read through `soa::FileTree` (`common/include/soa/file_tree.h`): a folder, or `SOA-3.7.0-canonical-data.zip` read in place: a member or a plain file of a stored entry is a range of the zip (`Member::skip`, `Response::file_range`), a deflated one is read into memory; `tools/server_cdn_check.sh` with `DOWNLOAD_B=` the zip proves the same answers |
| `story_en.cpp` | `make_english_story`, `english_name`: the English story files of `--english` (`Scenario/TS_xxxx-en.msgp`, docs/server-rules.md#english-story) |
| `english_tables.cpp` | `english_tables`: the English tables of `--english` (the derived layer from Global's master, the font and the story files, with our rows; docs/server-rules.md#english-derive), `write_english_tables` (`soa-server --english-dump`) |
| `files.{h,cpp}` | what the three share (namespace `cdn::files`, internal): file reads / writes / stats, the directory walk, `Sha1`, `server_time`, `map_find`, `kMasterName`, `kEnglishMasterName` |
| `adld.cpp` | the ADLD container (the client's encrypted master DB and asset packs) |
| `master_source.cpp` | where the server's master comes from (`soaserver/master_source.h`): `--master`, the checkout's, else decrypted from the download's (or the APK's) encrypted master into `DATA/master/`, keyed by the source's SHA-1 (docs/server-rules.md#master-source) |
| `master_source_tests.cpp` | `cdn/master-source`, `cdn/master-source-resolve`, `gacha/pools-name-from-master` |
| `cdn_tests.cpp` | `cdn/adld-roundtrip`, `cdn/adld-reencrypt-3.7.0`, `cdn/version-bin-roundtrip`, `cdn/bundle-layout`, `cdn/served-master`, `cdn/tree`, `cdn/lang-members`, `cdn/served-master-en`, `cdn/story-en`, `cdn/login-paths` |

Tests: `soa-server --selftest "cdn/"`, and `net/cdn-loopback` / `net/cdn-in-memory`. The replay corpora (RG4) build no CDN: a change here is proven byte-identical with `tools/server_cdn_check.sh BIN_A BIN_B` (every path the CDN serves, with the stand-ins on and off, from an empty scratch dir and from the bundle-hash cache, logs included). Sessions: `emulator/scripts/standin_fetch_test.sh` (the unmodified 3.7.0 client fetching the stand-ins from soa-server's CDN), `emulator/scripts/lang_fetch_test.sh` (the same for the `--english` master).
