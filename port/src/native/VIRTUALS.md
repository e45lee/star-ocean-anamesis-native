# Virtual functions and cross-subsystem calls in the natives

How native code (port/PLAN.md task 6) handles the game's C++ virtual functions while guest code and
natives share the same objects, how one native subsystem calls into another, and when and how
recovered classes can later become ordinary C++ classes with real `virtual` functions.

Status: parts 1 and 2 describe what the merged subsystems do today (sync, kernel, memory, params,
containers, data_formats, yayoi, input, resource, hash, math, the host libraries). Part 3 is a plan,
not started.

## 1. Virtual functions today: the guest's vtables, used as data

### 1.1 The vtable pointer is a plain field

A recovered class (`port/src/native/<subsystem>/<subsystem>_layout.h`) declares **no C++ `virtual`**.
Its first field is the guest's vtable pointer, a guest address, and every offset is `static_assert`ed.
A C++ `virtual` would make the host compiler add its own vtable pointer, changing the object's size
and offsets. Guest code still allocates, reads and writes these objects, so the layout must stay
byte-for-byte the guest's (`port/src/native/README.md`, "Per-subsystem workflow").

### 1.2 The vtables stay in the game library

Each class's vtable is the guest's own table at its `_ZTV…` symbol in `libSOA.so`'s read-only data.
Its slots hold guest function addresses. Native code never copies, rebuilds or patches a vtable.
When a native constructs an object, it writes the address of the guest's vtable (`_ZTV…` + 16) into
the field, exactly as the guest constructor does.

### 1.3 Overriding a virtual = hooking the function its slot points to

To make a virtual method native for a class, bind the native to the **guest function the slot points
to** (`NATIVE_METHOD("<mangled name>", &Class::Method, "…")`, `common/native_method.h`). At startup
`install_native_functions()` patches that guest function's entry to trap into the host. The slot is
unchanged, but every call through it, from guest code or from a native, now lands on the native.
Guest and native callers therefore stay consistent without anyone touching the vtable.

### 1.4 A native making a virtual call

Read the object's vtable pointer, take slot *N*, and look at the address:

- **It is a function this code (or another native) has replaced:** call the C++ member directly. That
  skips the trap through the hook, and it is most of the speedup on hot virtual paths.
- **Anything else** (still guest code, or an override in a class nobody has ported): run it with
  `guest_call(fn, {this, args…})` under the JIT.

The worked example is `kernel`'s dispatcher (`kernel/kernel_dispatcher.cpp`):

```cpp
const u64* vt = vtable_of(vtable);
u64 fn = vt[kSlotCheckToDispatch];                 // slot 3
if (fn == fn_check_to_dispatch()) return true;      // the base implementation, which is native here
return (guest_call(fn, {(u64)this, (u64)b}) & 1) != 0;  // a derived override: run the guest's
```

A native never needs to know which concrete class an object is: the guest's vtable already says.

### 1.5 Where the slot numbers come from

`tools/subsystem.py skeleton` reads each class's `_ZTV…` symbol and its relocations from the library
and emits the virtual methods **in slot order**, naming inherited slots and noting this-adjusting
thunks (multiple inheritance) as comments. Slot constants (`kSlotGetMessage = 2`, `Task::Run` = 13,
`INotify::Handler` = 0) come from there. A layout test can check a live object's vtable pointer
against the expected `_ZTV` symbol.

## 2. Calling another native subsystem

Three cases, depending on what the target is today.

| Target | How | Example on main |
|---|---|---|
| **Already native** | A direct C++ call. Include the lower subsystem's layout header and call the member. Both sides work on the same guest-memory structures (heap blocks, lock words, queues), so guest→native and native→native calls see the same state. | `memory`'s pools call `sync::CMutex::Lock()` / `FastCriticalSection::Enter()`; `kernel`'s dispatcher uses sync's `Enter`/`Leave`; `params` and `containers`' `THashMap::Find_` hash with `hash::CHash32::Of`; `yayoi` uses `hash`'s SpookyHash and calls the host `sqlite3_*` that `lib_sqlite` set up |
| **Still guest code** | `guest_call(addr, args)`: the runtime runs the guest function under the JIT. Allocator calls use `live::out_call` (`common/live_call.h`), which a live check can record and stub. When the target goes native, the call site switches to a direct call. | `yayoi` reaches ASON serialization and `memory`'s `AlignedMalloc` this way, until those are native |
| **Virtual** | Through the guest vtable, as in 1.4. This is also how **upward** calls work: a lower subsystem calls back into a higher one through an interface, without needing the higher one's types. | `kernel` → `Task::Run` (slot 13), `INotify::Handler` (slot 0) |

What keeps this safe across many parallel agents:

- **Layering.** A subsystem includes only the layout headers of subsystems below it
  (port/REBUILD-QUEUE.md levels). Upward calls go through vtables only.
- **Build.** `tools/subsystem.py check` compiles every layout header on its own (with `-I port/src`),
  and each subsystem's `subsystem.cmake` links in the pinned order (D8), so cross-subsystem calls
  resolve.
- **Hooks.** Guest code calling a native function still lands on it through its hook; natives
  calling each other skip that hop.
- **Live checks.** A native that runs inside another native's check is not itself checked, so
  subsystems that call each other are live-checked one layer at a time (`params` did whole family,
  then properties, then the parser).

## 3. Later: real C++ `virtual` functions

### 3.1 Why not now

Real `virtual`s need the object to carry a **host** vtable pointer laid out the way the host
compiler wants. While any guest code can see an object of the class, the object must keep the
**guest** layout and the guest vtable pointer:

- guest code may allocate it (with the guest's vtable) and pass it to natives;
- guest code may read its fields at fixed offsets, or call through its vtable;
- guest code may compare or test the vtable pointer (RTTI, `dynamic_cast`, type checks).

So the migration is possible only for a class family that has been **sealed off from guest code**.

### 3.2 When a family is ready (all must hold)

1. **Every method of every class in the family is native**, including constructors, destructors,
   and every override of every virtual in every derived class. `symbols.tsv` shows no `typed` or
   guest status for the family.
2. **No guest code creates, destroys, copies or reads objects of the family.** Proven by:
   - a caller scan (`tools/callers.py`, `xref_got.py`) showing no guest call to any of the family's
     constructors, vtable symbols or accessors;
   - a coverage run (`SOA_COVERAGE` over the four flows plus the long sessions) showing no guest
     instruction touching the family's objects. A watchpoint mode on the objects' memory would make
     this stronger, but the GDB stub has no watchpoints yet.
3. **No guest RTTI use** of the family: no `__dynamic_cast` or `typeid` with its type info, no vtable
   pointer comparisons in remaining guest code.
4. **Objects don't cross the boundary**, except as opaque pointers that only natives dereference.
5. The family's live checks have been at 0 mismatches for at least one full wave.

The natural first candidates are leaf families whose objects never leave native code once their
owners are native, e.g. `kernel`'s dispatcher blocks after `game`/`ui` stop posting from guest code,
or `sync`'s wrappers once every locker is native. The game-layer classes (`battle`, `ui`, `game`)
come last, since they are the most entangled.

### 3.3 How, per family

1. **Inventory:** list the family's classes, their vtable slots (`subsystem.py skeleton`), every
   override, and every place natives call through the vtable (`vtable_of(...)` / slot constants).
2. **Introduce the C++ hierarchy** alongside the layout classes: real base classes with `virtual`
   methods in the same order, the derived classes overriding them. Data members keep their names and
   types but no longer need guest offsets.
3. **Switch construction:** natives allocate the new C++ objects (host memory, or the native heap if
   the guest heap is still shared) instead of guest-layout objects.
4. **Switch the call sites:** slot-reading dispatch (1.4) becomes ordinary virtual calls; the
   `guest_call` fallbacks for the family disappear, because by 3.2 no override is guest code.
5. **Remove the hooks** for the family's guest functions (the guest code is now unreachable), and
   drop the layout `static_assert`s and the family's entries in `types.json`.
6. **Prove it:** the family's differential tests are ported to the new classes; the four flows and
   T1 pass; screenshots and packets stay equal in tests/diff; a coverage run shows the old guest code
   is never entered.
7. **One family per commit series,** merged and gated like any other native change, so a problem
   bisects to one family.

### 3.4 What stays guest-layout for good

Anything the remaining guest code, the game's data files or the save format sees: classes serialized
by the game (ASON-backed parameters, saved state), objects handed to guest callbacks, and the
`libc++` NDK layouts as long as any guest code uses `std::` containers. Those stay layout classes with
vtables as data, as in part 1.
