// The object manager's job dispatcher, native (scene_dispatch.cpp; README "The job dispatcher"): what the
// natives, their differential tests and the live check share.
#pragma once

#include <initializer_list>

#include "native/scene/scene_layout.h"

namespace soa::native::scene {

// RenderableObject's virtual slots the jobs call (render_layout.h lists the class's slots).
constexpr int kSlotResetDynamicShaderModifier = 51;  // vptr + 0x198
constexpr int kSlotCheckRenderContexts = 62;         // vptr + 0x1f0
constexpr int kSlotPreliminarilyPrepare = 79;        // vptr + 0x278
constexpr int kSlotPrepareForRendering = 80;         // vptr + 0x280
constexpr int kSlotRoutineProcedure = 83;            // vptr + 0x298

static_assert(sizeof(RenderContext) == 0x230, "RENDERINFO::m_contexts steps by the guest's 0x230");

// The guest functions the job bodies call (and Aska::Global::m_pObjectManager's address).
struct GuestFns {
    u64 makePaintingList, makePaintingListMultipass, makePaintingListShadow, makePaintingListPost;
    u64 viewFrustumCulling, subViewFrustumCulling, occlusionCulling, detectLIBL;
    u64 globalObjectManager;
};
const GuestFns& guest_fns();

// A guest virtual call: slot `slot` of the object's guest vtable with the object as x0 and `rest` after it.
u64 vcall(const void* obj, int slot, std::initializer_list<u64> rest = {});

// The task after `o` in its owner's list (the Task's link, +0x10).
inline RenderableObject* next_task(const RenderableObject* o) {
    return reinterpret_cast<RenderableObject*>(o->base.base.link.m_next);
}

// One object's per-frame reset: the body of the ResetSystemFlags job.
void ResetObjectSystemFlags(RenderableObject* o);

}  // namespace soa::native::scene
