# Calls from natives: to other natives and to the guest

Every guest call a native makes (`guest_call`, `guest_invoke`, `guest_call_raw`, and `live::out_call`,
which is a `guest_call` outside a check), classified (2026-10-08; tests and `*_test*` files left out).
A call to an installed native through `guest_call` already skips the JIT (`direct_thunk`: about 10 ns,
the arguments marshalled through a `Cpu`); a native whose callee is a native of the port calls it as
C++ instead, through `NativeCallee` (`common/native_call.h`), described below.

## The kinds

| Kind | What | Stays? |
|---|---|---|
| (a) original | the hook's own original: a live check's guest run (`f.orig`, `Orig(f)`, a shadow, lockstep or run-both run, `stub_original`), a native's fallback to its original (`fUpdateShaderProgram.orig` when no program is linked; lib_* `forwarding()`), a port hook around the guest function, and a check's own setup (`establish_program`, the scene check's worker) | yes: these call the guest on purpose |
| (b) dynamic | the target isn't known statically: a vtable slot, a callback, a table of handlers (some with a shortcut that calls the known native as a member when the slot holds it: `kernel_dispatcher.cpp` GetMessage, `memory_pools.cpp` `WithPool`, `params_property.cpp` `KnownProperty`, `audio_sequencer.cpp` WaitingNoteNotify) | yes |
| (c) same subsystem | a static target that is a native of the caller's subsystem | converted (`NativeCallee`) |
| (d) other subsystem | a static target that is another subsystem's native | converted (`NativeCallee`) |
| (e) still guest | a static target that is guest code (no native): the porting queue's input, below | yes, until ported |
| (h) helper | a wrapper that makes the call for its callers (`master_connector.cpp` `call`, `yayoi_guest.cpp` `call_status`, `dynamics_family.h` `call`, the live-check harness); its uses are classified by target | — |

| Subsystem | (a) | (b) | (c) | (d) | (e) | (h) |
|---|---|---|---|---|---|---|
| api | 1 | 11 | 1 | 0 | 38 | 0 |
| audio | 13 | 10 | 0 | 1 | 18 | 0 |
| common | 1 | 2 | 0 | 3 | 9 | 5 |
| containers | 0 | 1 | 0 | 0 | 4 | 0 |
| data_formats | 0 | 0 | 0 | 1 | 3 | 0 |
| dynamics | 0 | 1 | 0 | 0 | 0 | 1 |
| hash | 0 | 0 | 0 | 0 | 1 | 0 |
| info | 3 | 2 | 0 | 0 | 1 | 0 |
| input | 3 | 1 | 0 | 0 | 0 | 0 |
| kernel | 9 | 2 | 0 | 0 | 5 | 0 |
| lib_crypto | 2 | 0 | 0 | 0 | 0 | 0 |
| lib_jpeg | 0 | 3 | 0 | 0 | 0 | 0 |
| lib_sqlite | 2 | 2 | 0 | 0 | 0 | 0 |
| lib_vorbis | 29 | 0 | 0 | 0 | 0 | 0 |
| lib_zlib | 3 | 0 | 0 | 0 | 0 | 0 |
| lib_zstd | 5 | 0 | 0 | 0 | 0 | 0 |
| libcxx | 0 | 1 | 0 | 2 | 1 | 0 |
| master | 20 | 1 | 0 | 5 (+7 through `call`) | 5 | 3 |
| memory | 12 | 7 | 0 | 0 | 4 | 0 |
| params | 8 | 4 | 0 | 5 | 6 | 0 |
| particles | 1 | 6 | 0 | 0 | 6 | 1 |
| render | 20 | 1 | 3 | 0 | 2 | 0 |
| resource | 1 | 0 | 0 | 0 | 2 | 0 |
| restore | 3 | 0 | 0 | 0 | 2 | 0 |
| scene | 9 | 0 | 0 | 0 | 0 | 0 |
| sync | 8 | 0 | 0 | 0 | 3 | 0 |
| ui | 1 | 2 | 0 | 0 | 6 | 0 |
| yayoi | 2 | 1 | 0 | 1 (+2 through `call_status`) | 10 | 1 |
| **all** | 156 | 58 | 4 | 18 (+9) | 126 | 11 |

## (c) and (d): natives calling natives as C++

```cpp
NativeCallee kMalloc{"data_formats", "_ZN4Aska4ASON6MallocEm"};  // namespace scope
void* ason_malloc(void* ason, u64 n) {
    if (kMalloc.direct()) return static_cast<ASON*>(ason)->Malloc(n);
    return (void*)guest_call(kMalloc.addr(), {(u64)ason, n});    // the call as it was
}
```

`direct()` is decided once, at the end of `install_native_functions`: the callee's native was installed
there, and none of these is on: a `--live-check` family, the GDB stub (`--gdb`: breakpoints on natives
are taken in `run_direct`), `SOA_DIRECT_CALLS=0`. Otherwise the site makes its guest call exactly as
before, so:

- **Live checks stay what they were.** With any `--live-check`, every converted site goes through the
  guest entry: a record / replay check records the call (`live::out_call`) and its replay finds it, a
  run-both or shadow check's stubs and markers (render's `t_mark_callees`, `StubSession`) see it, and a
  callee is still checked as a nested callee (`only=`; dynamics' `checking()` is the same rule for its
  own family). Nothing of the direct path runs in a checked run.
- **`--selftest`** installs no natives: every site takes its guest call (the differential tests compare
  against the guest as before).
- **`--natives route`, `--natives-skip S`, a false `NATIVE_FUNCTION_IF`**: a callee not installed is
  called through its guest entry (its guest code), whatever the caller is.

The C++ a site calls is what the callee's registered HostFn runs with its family's check off: the member
`wrap_method` / `wrap<>` binds, a leaf family's `run` (its `hook<I>` calls `run` when the family is off),
yayoi's `b_*` bodies (`hook<K, Body>` runs `Body` when the family is off and no shadow runs), params'
`Crypt` (`KnownCryptString`, the HostFn's body), containers' `stl_replace`, render's
`update_shader_program_unchecked` (UpdateShaderProgram's HostFn without its marker and check). Where the
HostFn can be named, the callee carries it (`expect`) and test `native/direct-callees` checks the
registration has it; the test also checks every callee is a registered native of the subsystem it names
(a typo or a removed native would silently keep the guest path) and that nothing is direct in
`--selftest`. soa logs `natives calling natives: N of M callees as C++` at the install. Test
`yayoi/direct-ason-calls` switches yayoi's ASON callees to C++ in `--selftest` (`set_direct_for_test`) and
compares the document built that way with the one built through the guest entries.

**Profiles:** `SOA_PROFILE`'s `calls.tsv` and the `[native]<symbol>` frames count a native when a level
enters it through its thunk (from the JIT or a `guest_call`); a callee called as C++ is counted, and
sampled, inside its caller (e.g. ASON::Malloc: 5.29M calls before, 5K after, almost all from
EntityObject::Serialize). A native's own cost is in `SOA_PROFILE_HOST`'s `host.tsv`
(`port/scripts/host_profile.py`), which samples the host PC.

Render's two hooked callees (`LastMinuteDrawCommands_Textures`, `SetShaderProgramUniform`: guest code,
hooked only so a draw's check can record them as markers) are called through the hook's trampoline to
the original when direct: the same guest code, one host round trip less.

| Caller | Callee | Subsystem | battle-gacha calls |
|---|---|---|---|
| `yayoi_guest.cpp` `ason_malloc` (EntityObject::Serialize's MessagePack) | `ASON::Malloc` | data_formats | 5.28M |
| `yayoi_guest.cpp` `ason_make_array` / `ason_make_map` | `ASON::MakeAValue_Array` / `_Map` | data_formats | 84K |
| `params_guest.cpp` `AMapGet` | `AMap::Get_(char const*)` | data_formats | 150K |
| `params_guest.cpp` `GrowBy` / `GrowByAndReplace` | `basic_string::__grow_by` / `__grow_by_and_replace` | libcxx | 133K |
| `params_guest.cpp` `StlAllocate` / `StlFree`, `common/guest_std.cpp` `stl_alloc` / `stl_free`, `libcxx_string.cpp` `allocate` / `deallocate`, `master_guest.cpp` `StringAllocate` / `StlFree`, `master_hash.cpp` `alloc_block` (`memory_callees.h`) | `CAssignedMemoryManagerForSTLAllocator::Allocate` / `Free` | memory | 723K / 603K |
| `common/memstats.cpp`, `data_formats_ason_memory.cpp` (`memory_callees.h`) | `MemoryManager::CalcFreeSize(bool)` | memory | (rare) |
| `master_connector.cpp` `Locked` | `CMutex::Lock` / `Unlock` | sync | 843 |
| `master_connector.cpp` `Entity`, `serialize_into`, `QueryToResultObject(Sql)` | `EntityObject` C1 / D1 / `Serialize`, `SQLiteDriver::DoOpen` / `Find` | yayoi | 843 |
| `master_stringdb.cpp` `GetNativeString` / `Get` | `CParameterPropertyBase<32>::CryptString`, `CSTLStringUtility_Base::Replace` | params, containers | 200 |
| `render_draw.cpp` `UpdateRenderState` | `RenderDeviceData::UpdateShaderProgram` | render (c) | 502K |
| `render_draw.cpp` `UpdateRenderState`, `render_program.cpp` `UpdateShaderProgram` | `LastMinuteDrawCommands_Textures`, `SetShaderProgramUniform` (hooks: their originals) | render (c) | 502K, 256K |

Not converted:

- **audio** (`audio_3d.cpp` -> math's `Quaternion::Create`, 5K) and **info**: their owner's (agent
  waveA-rest) files while that work runs.
- **particles**, **dynamics**: their last pieces were being merged; dynamics' `checking()` already calls
  ADMJoint's natives as C++ by the same rule.
- **api** `FakeApiCaller` C2 (the route's own hook, once per boot).

## (e): static targets that are still guest code (porting-queue input)

By calls in one battle-gacha run (the 3.7.0 lib, `soa` at 2026-10-08, `guest_call_raw` counted per
target). The large ones first; the rest are cold (once per screen or per request) or asserts.

| Target (guest) | Called from | Calls |
|---|---|---|
| `Aska::IndexBuffer::Is32BitBuffer() const` | `render_draw.cpp` DrawIndexedPrimitive | 490K |
| `Aska::MatrixCalcFunc(...)` | `dynamics_adm.cpp` | 408K |
| `Aska::Vector::ApplyMatrix` / `ApplyMatrixNoTransport` | `dynamics_adm.cpp`, `dynamics_primitives.cpp`, `audio_3d.cpp` | 246K / 157K |
| `Aska::IndexBuffer::GetData(int) const` | `render_draw.cpp` DrawIndexedPrimitive | 155K |
| `StringToNumber<T>(char*)` (an istringstream) | `params_guest.cpp` | 31K |
| `Aska::IParticleEmitter::FillMatrixContext`, `Prepare`, `IParticleObject::SetAnimation` | `particles_simulate.cpp` (native in the particles pieces since merged) | 21K, 20K, 5K |
| `Aska::NotifierThread::AddNotify` / `RemoveNotify` / `Notify` | `kernel_gpu_sync.cpp` | 14K |
| `Aska::MemoryManagerAdapter::AlignedMalloc` / `AlignedFree` | `containers_dynamic_array.h`, `yayoi_guest.h` | 2.6K |
| `operator new[]` / `operator delete[]` / `operator delete` | `guest_std.cpp`, `memory_pools.cpp`, `data_formats_ason.h`, `yayoi_guest.h`, `sync_mutex.cpp`, `sync_thread.cpp`, `master_*` | 2.7K |
| `CSqliteTransaction::rMutex`, `EntityCache` C1 / D1, `SQLiteDriver::BuildQuery<...>`, `__next_prime` | `master_connector.cpp`, `master_hash.cpp` | 1.7K, 1.7K, 422, 145 |
| `Aska::ASON` C1 / D1 / `Init` / `CalcSerializedSize` / `Serialize`, `TSharedPointerCode::Create/DeleteCounter` | `yayoi_guest.cpp`, `yayoi_guest.h`, `api/client_battle_log.cpp` | 1.4K |
| `Framework::CDelayDelete::AddTask`, `FileID::gpFileName` | `resource_manager.cpp` | 562, 0 |
| `CSTLStringUtility_Base::Format` | `master_stringdb.cpp` | 200 |
| `MemoryManager::MallocHigh`, `Global::GetAvailableMemoryManager`, `EventPool::Scoop` / `Sink` | `memory_heap.cpp`, `memstats.cpp`, `data_formats_ason_memory.cpp`, `kernel_dispatcher.cpp` | 0 |
| `Framework::gDoAssert` | every subsystem's assert paths | 0 |
| the route's and the port's own guest calls (CGameResourceManager, CApiNotify, CFiberUnit, ErrorHandler, ASON serializers, cocos nodes, the control commands) | `api/`, `ui/webview_local.cpp`, `restore/`, `common/port_debug.cpp` | per request / per command |

The hottest dynamic (b) targets, for the same queue: `BufferHandlerGL<...>::Upload` (render's
`GpuResource::EnsureUploaded`, 310K), `AofObject::ResetDynamicShaderModifier` / `CheckRenderContexts` /
`PreliminarilyPrepare` / `PrepareForRendering` (scene's dispatch slots, 470K / 109K / 89K / 136K),
`JointObject::MakeMatrix` / `HierarchicalObject::WorldMatrix` / `MakeMatrix` (dynamics' `vcall`,
400K / 329K / 189K), `CMasterParameterBaseSqlite::pPrimaryKeyName` (master's slot, 168K),
`TCSVAccessor<CACSV>::Value` (info's slot, 128K), `PadDroid::ResetStatus` (input's `Pad::Flip`, 23K).
