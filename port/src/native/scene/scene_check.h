// The live check of the job dispatcher's natives (soa --live-check scene[:every=N][:budget=N][:only=..][:out=FILE]).
//
// A native Dispatch_X runs job X inline; the guest posts it to its worker, which runs it on its own thread.
// So a check compares the native with the guest's whole path, replayed on a private *shadow* (the sync
// pattern, native/sync/sync_check.h, plus a record / replay of the job's callees):
//   - the native runs for real while the thread's recorder (t_rec) notes every call the job body makes
//     (a virtual of a batch object, MakePaintingList*, the culling, DetectLIBL): its target, arguments,
//     result, the RENDERINFO bytes a PrepareForRendering call sees, and the object's bytes (or the result
//     words, for the culling) after it;
//   - the shadow is a dispatcher with one worker of this thread's (built once by the guest's constructor,
//     with its own Event), set to idle in mode X, the worker's parameters copied from the real one, the
//     result words and the batch objects copied as the native found them (a ResetSystemFlags chain
//     re-linked through the copies);
//   - then the guest's Dispatch_X (the hook's trampoline) posts the job to the shadow worker and the
//     worker's Handler_X runs it once on this thread, every recorded callee answered by a replay stub
//     (live::ensure_stub) that checks the call against the record (the object, the arguments, the
//     RENDERINFO bytes) and plays its effects back into the copies;
//   - the result, the call sequence, the result words, the worker's parameter bytes and the objects'
//     bytes must be equal (the shadow's pointers to its copies counted as the real ones).
// ChangeMode / RetryChangeMode* / WaitIdle / WaitAllIssued / Sleep and the Set*BasicParameter forms run
// the guest original on the shadow (its worker idle in another mode) and compare the dispatcher's and
// workers' parameter bytes.
#pragma once

#include <vector>

#include "core/cpu.h"
#include "native/common/shadow_check.h"
#include "native/scene/scene_layout.h"

namespace soa::native::scene {

live::ShadowFamily& family();

// One call of a job body, as the native made it (scene_dispatch.cpp's job_call notes it when t_rec is set).
struct JobCall {
    u64 target = 0;
    u64 x[9] = {};
    int n = 0;
    u64 ret = 0;
    int obj = -1;               // the batch object it was called on (x0), or -1
    std::vector<u8> info;       // a PrepareForRendering call: the RENDERINFO bytes it saw
    std::vector<u8> objAfter;   // the object's first kObjSnap bytes after the call
    std::vector<u8> bitsAfter;  // a culling call: the result words after it
};
constexpr u32 kObjSnap = 0x248;  // what the job bodies read and write of an object (up to 0x23f)

struct JobRecorder {
    const ObjectManagerWorkerThread* worker = nullptr;
    std::vector<RenderableObject*> objs;  // the batch (index = the call's obj)
    u64* bits = nullptr;                  // the result words a culling call writes (bitsWords of them)
    size_t bitsWords = 0;
    std::vector<JobCall> calls;
};
extern thread_local JobRecorder* t_rec;

// A job body's outgoing call (guest function `fn`, integer arguments `a`), recorded when t_rec is set.
u64 job_call(u64 fn, const u64* a, size_t n);

}  // namespace soa::native::scene
