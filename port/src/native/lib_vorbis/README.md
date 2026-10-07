# `lib_vorbis`: libVorbis 1.3.5 + libogg: the host libraries at the ogg_* / vorbis_* API

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/lib_vorbis/scope.txt`](../../../decomp/lib_vorbis/scope.txt).
- Decompiles and the function list: [`port/decomp/lib_vorbis/`](../../../decomp/lib_vorbis/) (`symbols.tsv`; `tools/decomp.sh --into lib_vorbis/<topic>`).
- Types: [`lib_vorbis_layout.h`](lib_vorbis_layout.h); for Ghidra, `tools/subsystem.py export-types lib_vorbis` -> `port/decomp/lib_vorbis/types.json`.
- Build settings of its own (a host library, a definition): none; a `subsystem.cmake` here would hold them (port/CMakeLists.txt includes it).

## Types (classes with their methods attached)

The library's structs as the guest lays them out ([`lib_vorbis_layout.h`](lib_vorbis_layout.h)); C structs
of a C library, no methods.

| Struct | Guest size | Found from | Status |
|---|---|---|---|
| `OggPacket` (`ogg_packet`) | 0x30 | libogg's `ogg.h` (LP64); `Aska::AskaOGG::Decode_LoopStart` reads `granulepos` (+0x20) | typed; crosses converted |
| `OggPage` (`ogg_page`) | 0x20 | `ogg.h`; AskaOGG reads `header[5]` (the flags) | typed; host's in place |
| `VorbisInfo` (`vorbis_info`) | 0x38 | `codec.h`; AskaOGG reads `channels` (+4) and `rate` (+8, as an int) | typed; host's in place |
| `OggSyncState`, `OggStreamState`, `VorbisComment`, `VorbisDspState`, `VorbisBlock` | 0x20, 0x198, 0x20, 0x90, 0xc0 | `ogg.h` / `codec.h`; the offsets of Aska::AskaOGG's decode context agree | opaque: host's in place |

## Natives

32 functions: the whole API the game calls (`tools`-scanned: every BL / ADRP+ADD reference to the
library from outside it is from `Aska::AskaOGG`, port/decomp/lib_vorbis/aska_ogg.c). The library's
other functions (the encoder, the internals) are unreachable once these are native.

| Guest symbol | File | Differential tests | Live check |
|---|---|---|---|
| `ogg_sync_{init,clear,reset,buffer,wrote,pageout}`, `ogg_page_{eos,serialno}`, `ogg_stream_{init,clear,reset,pagein,packetout,packetpeek}` | `lib_vorbis_api.cpp` | `lib_vorbis/decode-bgm`, `lib_vorbis/decode-damaged`, `lib_vorbis/live-check` | 0 mismatches (login 15,000+, battle 49,000+, gacha 45,000+, story 80,000+ checks) |
| `vorbis_info_{init,clear,blocksize}`, `vorbis_comment_{init,clear}`, `vorbis_synthesis_{headerin,init,trackonly,blockin,pcmout,read,restart}`, `vorbis_synthesis`, `vorbis_dsp_clear`, `vorbis_block_{init,clear}`, `vorbis_packet_blocksize` | `lib_vorbis_api.cpp` | same | same |
| `ogg_memory_hook` | `lib_vorbis_api.cpp` | - (a no-op: below) | - |

**Host libraries:** vcpkg's libogg 1.3.6 and libVorbis 1.3.7 (linked by port/CMakeLists.txt). The game's
libVorbis is 1.3.5; decoding is bit-identical (the tests compare every float sample, the live check every
`vorbis_synthesis_pcmout`), so no pinned build: the guest's code has no fused multiply-adds (none in the
library's range) and the host build no `-ffast-math`.

**Differential tests:** two BGM streams from the download's `Sound/` (`work/SOA-3.7.0-canonical-data.zip`, read in place; skipped when absent) decoded
through the guest (`t.call`) and through the natives the way `Aska::AskaOGG` drives them (0x2000-byte feeds,
the headers, synthesis / blockin / pcmout / read, and `Decode_LoopStart`'s seek: stream / synthesis / sync
reset, packetpeek + packet_blocksize + trackonly up to a sample); damaged streams (flipped bytes with CRC
errors, flipped bytes behind valid CRCs, a cut stream); every result, packet and sample compared.

**Live check:** `--live-check lib_vorbis[:out=FILE]` (native/common/lockstep.h): the guest library runs in
lockstep on shadow structs; results, pages, packets, stream parameters and every decoded sample compared.
Measured over `battle_session.sh` (battle BGM, voices, SE) and `campaign_session.sh` (the story mission and
scene mc01_030), both PASS.

**Guest time:** 4,267 samples (1.5% of the four flows' guest time; login 1.0%, battle 1.3%, gacha 1.4%,
story 1.8%) before, 0 after (no library function executes on the guest; port/REBUILD-QUEUE.md's flows,
`port/scripts/rebuild_queue.py`).

## Dependencies

None (a leaf). The `audio` subsystem (`Aska::AskaOGG`, `Aska::SLVoice`) calls it.

## RE notes

- **Where the structs live:** `Aska::AskaOGG`'s decode context (0x450 bytes, zeroed by its constructor)
  embeds `ogg_sync_state` +0x000, `ogg_stream_state` +0x020, `ogg_page` +0x1b8, `ogg_packet` +0x1d8,
  `vorbis_info` +0x208, `vorbis_comment` +0x240, `vorbis_dsp_state` +0x260, `vorbis_block` +0x2f0; its own
  fields from +0x3b0 (8 decode buffers at +0x3d0, their sizes at +0x410, the buffer index +0x430, the
  header count +0x43c, the loop state +0x43d). `~DecodeContext` clears all six (also never-initialized,
  zeroed ones: the host's clear functions accept those).
- **In place:** the host's structs are the guest's on LP64 hosts; on Windows (`long` 32-bit) they are
  smaller and differ in layout, but the fields the game reads keep their offsets (`ogg_page.header`,
  `vorbis_info.channels` / `.rate`), so they stay in place there too. `ogg_packet.granulepos` moves (0x20 ->
  0x18), so packets cross as `OggPacket`, converted (on every host: one code path).
- **What the game reads:** `ogg_page.header[5] & 4` (end of stream; AskaOGG's `+0x3c9`), `vorbis_info.channels`
  and `.rate` (as an int: `rate / 4` is the frame), `ogg_packet.granulepos` (`Decode_LoopStart`), and
  the `float**` of `vorbis_synthesis_pcmout`, which `Decode_Pcmout` converts itself:
  `(int)(sample * 32767.0f + 0.5f)`, clamped to [-0x8000, 0x7fff], interleaved by channel.
- **`ogg_memory_hook`** (the game's libogg patch): `Aska::AskaOGG::InitializeMemory` hands it the sound-memory
  allocators `aska_ogg_{malloc,calloc,realloc,free}`. The host libraries allocate with the host's malloc
  (the guest's malloc too); the game never frees library memory itself, so the hook is a no-op native. It
  is not forwarded to the guest library either: that runs only as a live check's shadow.
- **The guest library calls its own exports** (`vorbis_synthesis_headerin` -> `vorbis_info_clear`,
  `vorbis_synthesis_init` -> `vorbis_dsp_clear`, on errors): under the live check those calls carry the
  shadows, and the natives forward them to the originals.
- **Trampolines:** 9 of the 32 start with a pc-relative instruction (`cbz x0` in `ogg_sync_init`, an
  ADRP in `ogg_memory_hook`, ...): they need the relocated trampolines (native/common/trampoline.h);
  before those, such a native was left uninstalled, and guest and host library ran on one state (a crash
  in the first live run).
