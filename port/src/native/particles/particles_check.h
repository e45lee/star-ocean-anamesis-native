#pragma once
// The live check of the particle manager's natives (soa --live-check particles[:every=N][:budget=N][:only=..]
// [:out=FILE]) and the pieces the differential tests share with it.
//
// The manager's natives work on shared, stateful objects (the emitter list under m_cs, the emitters'
// dispatch locks, m_inFlight, which the workers change concurrently) and their callees have effects a
// replay can't undo (a posted message is a real Simulate on a worker). So they are shadow checks
// (common/shadow_check.h): the native runs for real with its outgoing calls recorded (particles_calls.h)
// and the moments that matter noted (the list as it found it under m_cs, the lock values its
// compare-and-swaps saw, the times it read); then the guest original runs on a private World built from
// that (a manager and copies of the emitters, their vtable a fake whose Prepare / Simulate only log),
// with its callees (the PostMessage forms, Event::Wait, VSync::GetDt, SkipThisFrame, IsBufferReady)
// stubbed and answered from the record. The call lists must match call by call (pointers named by what
// they point into: the manager, emitter i, the dispatcher) and so must the state the guest left in the
// World and the native's at the same point.
// The differential tests (particles_manager_test.cpp) run both sides on private Worlds with the callees
// answered from a random script.
#include <functional>
#include <initializer_list>
#include <string>
#include <vector>

#include "native/common/shadow_check.h"
#include "native/particles/particles_calls.h"
#include "native/particles/particles_layout.h"

namespace soa::native::particles {

live::ShadowFamily& family();

// Pointer naming for comparisons: the manager ("M+off"), emitter i ("E<i>+off"), the dispatcher ("D+off"),
// else the value in hex.
struct View {
    const ParticleManager* m = nullptr;
    std::vector<const IParticleEmitter*> e;
    struct Region {
        u64 base, size;
        std::string name;
    };
    std::vector<Region> regions;  // more named objects ("O", "R": Simulate's object, renderable)
    std::string name(u64 v) const;
    // One call as text, its pointers named (a PostMessage's out-pointer as "S" / "0": the caller's stack).
    std::string text(const Call& c) const;
    std::string texts(const std::vector<Call>& calls) const;
};

// The emitter fields the manager's natives read or write.
struct EState {
    u8 idle = 0, waitBuffer = 0, linkMode = 0, matrixMode = 0;
    u16 flags = 0;
    s32 lock = 0;
    u32 serial = 0;
    float lastTime = 0;
    u64 key = 0;
    ParticleRenderableBase* renderable = nullptr;
    static EState of(const IParticleEmitter* e);
    void apply(IParticleEmitter* e) const;
    std::string text() const;  // what is compared (not key / renderable / flags / modes: only read)
};

// The manager fields they read or write.
struct MState {
    u32 time = 0;  // (bits)
    u64 matrixCount = 0, dispatchCount = 0;
    std::vector<std::string> matrixList, dispatchList;  // named
    u8 buffersPending = 0;
    u32 fillFrame = 0, drawnFrame = 0, frameSlots[2] = {};
    static MState of(const ParticleManager* m, const View& v);
    std::string text() const;
};

// A private manager and emitters (copies), for the guest original (and, in the tests, the native too).
struct World {
    static constexpr int kMaxEmitters = 4096;
    ParticleManager* m = nullptr;
    std::vector<IParticleEmitter*> e;   // e[0..n): in use (allocated on demand, kept)
    int n = 0;
    MessageDispatcherBlock* block = nullptr;  // a message block for Handler
    World();
    ~World();
    World(const World&) = delete;
    World& operator=(const World&) = delete;
    // n emitters, zeroed but for their vtable (the fake one), linked into m's list in order; the manager
    // zeroed but for its CriticalSection, its list sentinel and its list pointers (into its storage).
    void reset(int count);
    View view() const;
    static const u64* fake_vtable();  // slot 45 Prepare / 51 Simulate log; the others return 0
};

// The guest original, run on this thread with the manager's callees stubbed: each call is logged in
// `log` and answered from `script` (in order; a call the script doesn't have is an error). `after` runs
// after each answer (its index), e.g. to move the World on as the native's run saw it move.
struct GuestRun {
    const std::vector<Call>* script = nullptr;
    size_t next = 0;
    std::function<void(Call&, size_t)> answer;  // instead of `script` (Recorder::answer)
    size_t perKind[(int)CallKind::kCount] = {};
    std::vector<Call> log;
    std::string error;
    std::function<void(size_t, Call&)> after;
    std::vector<std::pair<u64, CallKind>> extra;  // more callees to stub (Simulate's), by guest address
    GuestResult result{};
    // Runs fn(x..., s0 when given).
    void run(u64 fn, std::initializer_list<u64> x, const float* s0 = nullptr);
};

// The guest addresses of Simulate's shared callees (FillMatrixContext, Random, SetAnimation).
u64 sym_fill_matrix();
u64 sym_random();
u64 sym_set_animation();

// The bound Simulate instantiations (particles_simulate.cpp, from gen/particles_instantiations.inc).
size_t simulate_rows();
const char* simulate_row_symbol(size_t i);
const IParticleEmitter::Instantiation& simulate_row(size_t i);

// "first difference" of two texts (empty when equal), for check messages.
std::string first_diff(const std::string& native, const std::string& guest);

}  // namespace soa::native::particles
