# server/src/cdn: what the server's CDN serves

The content of the CDN both server modes serve to the client (soa-server over HTTP, `../../net/cdn_http.cpp`; soa in memory, `port/src/native/api/server_cdn.cpp`). Public API: `../../include/soaserver/cdn.h`, `adld.h`. Rules and labels: docs/server-rules.md "soa-server: the CDN".

| File | What |
|---|---|
| `tree.cpp` | `cdn::Tree`: `Tree::build` as the steps of `TreeBuilder` (a friend of `Tree`): `read_version_bin`, `serve_master`, `add_standins`, `read_manifests`, `collect_bundles` (+ `member_of`, `add_standin_bundle`), `hash_bundles` (threads, the bundle-hash cache), `renew_ids` (the revision, the version ids, the manifests' files), `write_version_bin`; `Tree::lookup` (the URL paths), `summary`, `bundle_of`; the `*_from_config` functions |
| `bundle.cpp` | the "\0ISF" bundle image (`bundle_head`, `bundle_stream`, `bundle_size`, `bundle_bytes`, `bundle_sha1`), `Response` (`size`, `read`, `open`: a body read in pieces, `PieceReader`), `sha1_hex` |
| `served_master.cpp` | `make_served_master`: the 3.7.0 master with the modules' `ClientMaster` overrides (`apply_client_master`), VACUUMed, ADLD-AES packed |
| `files.{h,cpp}` | what the three share (namespace `cdn::files`, internal): file reads / writes / stats, the directory walk, `Sha1`, `server_time`, `map_find`, `kMasterName` |
| `adld.cpp` | the ADLD container (the client's encrypted master DB and asset packs) |
| `cdn_tests.cpp` | `cdn/adld-roundtrip`, `cdn/adld-reencrypt-3.7.0`, `cdn/version-bin-roundtrip`, `cdn/bundle-layout`, `cdn/served-master`, `cdn/tree`, `cdn/login-paths` |

Tests: `soa-server --selftest "cdn/"`, and `net/cdn-loopback` / `net/cdn-in-memory`. The replay corpora (RG4) build no CDN: a change here is proven byte-identical with `tools/server_cdn_check.sh BIN_A BIN_B` (every path the CDN serves, with the stand-ins on and off, from an empty scratch dir and from the bundle-hash cache, logs included). Session: `emulator/scripts/standin_fetch_test.sh` (the unmodified 3.7.0 client fetching the stand-ins from soa-server's CDN).
