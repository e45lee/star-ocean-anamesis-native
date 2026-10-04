// Layout tests for anim_layout.h (port/PLAN.md task 6, types first): the recovered classes read against
// real guest objects. Private objects are built by the guest's constructors and driven by its methods
// (natives are not installed in --selftest); live ones are taken in the calls the game makes on its own
// (render_test_util.h TEST_PROBE: the test body runs on the calling thread), at home where a character
// animates (port/scripts/selftest_live.sh build/port/soa OUT TMP anim/ --at home). At the title nothing
// animates: the live tests note it and pass.
#include <cmath>
#include <cstring>

#include "native/anim/anim_layout.h"
#include "native/common/test.h"
#include "native/render/render_test_util.h"

namespace soa::native::anim {
namespace {

using namespace render::testutil;

int probe_timeout() { return live_screen() ? 30000 : 4000; }

// A guest float getter: this (+ an int) in, s0 out.
float call_f(u64 fn, const void* self) { return guest_invoke<float>(fn, (u64)self); }
float call_f(u64 fn, const void* self, s32 i) { return guest_invoke<float>(fn, (u64)self, i); }

bool same_float(float a, float b) { return std::memcmp(&a, &b, 4) == 0 || (std::isnan(a) && std::isnan(b)); }

TEST_PROBE(g_probeSetValues, "_ZN4Aska10AafHandler9SetValuesEf");
TEST_PROBE(g_probePlayAnimation, "_ZN9Framework24CAnimationBlendContainer13PlayAnimationEPN4Aska9FiberTaskE");
TEST_PROBE(g_probeModelProgress, "_ZN9Framework15CAnimationModel8ProgressEf");
TEST_PROBE(g_probeBlendCalc, "_ZN4Aska15AafBlendManager10CalcValuesEv");

// The AafHandler checks (a live handler in SetValues, or one a container's element holds).
void check_handler(TestContext& t, const AafHandler* h, const char* where) {
    t.expect_eq(has_vtable(t, h, "_ZTVN4Aska10AafHandlerE"), true, "AafHandler vtable");
    t.expect_eq(h->m_refCount > 0, true, "AafHandler m_refCount > 0");
    const AafHeader* hd = h->m_header;
    if (!t.expect_eq(hd != nullptr, true, "AafHandler m_header")) return;
    t.expect_eq((u32)hd->m_version, 0x2eu, "AafHeader m_version 0x2e");
    t.expect_eq((u32)h->m_targetCount, (u32)hd->m_targetCount, "m_targetCount = header's");
    t.expect_eq(h->m_countA, (u32)hd->m_countA, "m_countA = header's");
    t.expect_eq(h->m_countB, (u32)hd->m_countB, "m_countB = header's");
    t.expect_eq(h->m_countC, (u32)hd->m_countC, "m_countC = header's");
    t.expect_eq(h->m_controllerCount, h->m_countA + h->m_countB + h->m_countC, "m_controllerCount = A + B + C");
    t.expect_eq(h->m_param48, (u32)hd->m_param0c, "m_param48 = header 0x0c");
    t.expect_eq(h->m_cacheWords, (h->m_countA + 31) / 32, "m_cacheWords = (A + 31) / 32");
    t.expect_eq((h->m_flags >> 6) & 1u, (u32)(hd->m_flags & 1), "m_flags bit 6 = header streamed bit");
    t.expect_eq((const u8*)h->m_targets, (const u8*)h->m_buffer, "m_targets at the buffer's start");
    t.expect_eq((const u8*)h->m_infos, (const u8*)h->m_targets + (u64)h->m_targetCount * sizeof(AafTarget), "m_infos after the targets");
    t.expect_eq(h->m_infosA, h->m_countA ? h->m_infos : nullptr, "m_infosA");
    t.expect_eq(h->m_infosB, h->m_countB ? h->m_infos + h->m_countA : nullptr, "m_infosB");
    t.expect_eq(h->m_infosC, h->m_countC ? h->m_infos + h->m_countA + h->m_countB : nullptr, "m_infosC");
    t.expect_eq((const u8*)h->m_cacheBits0, (const u8*)(h->m_infos + h->m_controllerCount), "m_cacheBits0 after the infos");
    t.expect_eq(h->m_cacheBits1, h->m_cacheBits0 + h->m_cacheWords, "m_cacheBits1");
    t.expect_eq((const u8*)h->m_activeInfos, (const u8*)(h->m_cacheBits1 + h->m_cacheWords), "m_activeInfos");
    t.expect_eq((const u8*)h->m_cacheIndex0, (const u8*)(h->m_activeInfos + h->m_countA), "m_cacheIndex0");
    t.expect_eq(h->m_cacheIndex1, h->m_cacheIndex0 + h->m_countA, "m_cacheIndex1");
    TestContext& tc = t;
    float len = call_f(tc.sym("_ZNK4Aska10AafHandler6LengthEv"), h);
    t.expect_eq(same_float(len, hd->m_length), true, "Length() = header m_length");
    u32 cbs = (u32)tc.call("_ZNK4Aska10AafHandler23GetComplementBufferSizeEv", {(u64)h});
    u32 want = ((h->m_flags & 2) && h->m_complement && !h->m_complementShared) ? hd->m_complementBufferSize : 0;
    t.expect_eq(cbs, want, "GetComplementBufferSize()");
    bool att = tc.call("_ZNK4Aska10AafHandler26IsAttachedComplementBufferEv", {(u64)h}) & 1;
    bool want_att = (h->m_flags & 2) && (!h->m_complement || h->m_complementBuffer != nullptr);
    t.expect_eq(att, want_att, "IsAttachedComplementBuffer()");
    // The controller infos: target indexes in range; a live controller's header and key header.
    int checked = 0;
    for (u32 i = 0; i < h->m_controllerCount && checked < 16; i++) {
        const AafControllerInfo& in = h->m_infos[i];
        t.expect_eq(in.m_targetIndex < h->m_targetCount, true, "info m_targetIndex < m_targetCount");
        if (in.m_keyHeader && in.m_header) {
            u16 off = *reinterpret_cast<const u16*>(in.m_header + 6);
            t.expect_eq(in.m_keyHeader, in.m_header + off, "info m_keyHeader = m_header + *(u16*)(m_header + 6)");
        }
        checked++;
    }
    (void)where;
}

}  // namespace

// AafBlendManager: a private one, set up as CAnimationBlendContainer::PlayAnimation does (the two vtables,
// Initialize), then Create / Open / AddAaf / SetWeight / SetPlayFrame / NormalizeWeights / Close through the
// guest, the fields read through the class.
NATIVE_TEST("anim/layout-blend-manager") {
    alignas(16) static u8 storage[sizeof(AafBlendManager)];
    alignas(16) static u8 fake_handlers[2][sizeof(AafHandler)];
    std::memset(storage, 0, sizeof storage);
    std::memset(fake_handlers, 0, sizeof fake_handlers);
    auto* m = reinterpret_cast<AafBlendManager*>(storage);
    m->vtable = vtable_of(t, "_ZTVN4Aska15AafBlendManagerE");
    m->m_calcNotify.vtable = vtable_of(t, "_ZTVN4Aska15AafBlendManager11_CalcNotifyE");
    t.call("_ZN4Aska15AafBlendManager10InitializeEv", {(u64)m});
    t.expect_eq(m->m_calcNotify.m_owner, m, "Initialize: _CalcNotify owner = this");
    t.expect_eq(m->m_closeMode, (u8)2, "Initialize: m_closeMode 2");
    t.expect_eq(m->m_created, (u8)0, "Initialize: not created");
    t.expect_eq(m->m_added, -1, "Initialize: m_added -1");
    t.call("_ZN4Aska15AafBlendManager6CreateEi", {(u64)m, 3});
    t.expect_eq(m->m_created, (u8)1, "Create: m_created");
    t.expect_eq(m->m_capacity, 3, "Create: m_capacity");
    if (!t.expect_eq(m->m_infos != nullptr, true, "Create: m_infos")) return;
    t.expect_eq(t.call("_ZN4Aska15AafBlendManager4OpenEi", {(u64)m, 2}) & 0xff, (u64)1, "Open(2)");
    t.expect_eq(m->m_count, 2, "Open: m_count");
    t.expect_eq(m->m_added, 0, "Open: m_added 0");
    for (auto& f : fake_handlers) reinterpret_cast<AafHandler*>(f)->m_flags = 2;  // controllers created
    t.call("_ZN4Aska15AafBlendManager6AddAafEPNS_10AafHandlerE", {(u64)m, (u64)fake_handlers[0]});
    t.call("_ZN4Aska15AafBlendManager6AddAafEPNS_10AafHandlerE", {(u64)m, (u64)fake_handlers[1]});
    t.expect_eq(m->m_added, 2, "AddAaf x2: m_added");
    t.expect_eq((u8*)m->m_infos[1].m_handler, fake_handlers[1], "AddAaf: m_infos[1].m_handler");
    guest_call(t.sym("_ZN4Aska15AafBlendManager9SetWeightEif"), GuestArgs().i((u64)m).i(0).f(0.25f));
    guest_call(t.sym("_ZN4Aska15AafBlendManager9SetWeightEif"), GuestArgs().i((u64)m).i(1).f(0.75f));
    guest_call(t.sym("_ZN4Aska15AafBlendManager12SetPlayFrameEif"), GuestArgs().i((u64)m).i(1).f(12.5f));
    t.expect_eq(m->m_infos[0].m_weight, 0.25f, "SetWeight -> m_weight");
    t.expect_eq(m->m_infos[1].m_playFrame, 12.5f, "SetPlayFrame -> m_playFrame");
    t.expect_eq(call_f(t.sym("_ZNK4Aska15AafBlendManager9GetWeightEi"), m, 1), 0.75f, "GetWeight(1)");
    t.expect_eq(call_f(t.sym("_ZNK4Aska15AafBlendManager12GetPlayFrameEi"), m, 1), 12.5f, "GetPlayFrame(1)");
    t.expect_eq(t.call("_ZN4Aska15AafBlendManager16NormalizeWeightsEv", {(u64)m}) & 0xff, (u64)1, "NormalizeWeights");
    t.expect_eq(m->m_infos[0].m_normalizedWeight, 0.25f, "normalized weight 0");
    t.expect_eq(m->m_infos[1].m_normalizedWeight, 0.75f, "normalized weight 1");
    u64 notify = 0x1234;
    t.call("_ZN4Aska15AafBlendManager9SetNotifyEiPNS_7INotifyE", {(u64)m, 0, notify});
    t.expect_eq((u64)m->m_infos[0].m_notify, notify, "SetNotify -> m_notify");
    t.expect_eq(t.call("_ZN4Aska15AafBlendManager9GetNotifyEi", {(u64)m, 0}), notify, "GetNotify");
    t.call("_ZN4Aska15AafBlendManager5CloseEh", {(u64)m, 2});
    t.expect_eq(m->m_added, -1, "Close: m_added -1");
    t.expect_eq(m->m_firstUsed, 0, "Close: m_firstUsed = the first info with a handler");
    t.call("_ZN4Aska15AafBlendManagerD1Ev", {(u64)m});
}

// CAnimationBlendContainer / CAnimationElement / CAnimationTimeElement / CBlendRatePlayer: a private
// container, constructed and initialized (3 elements, 2 blend pieces) by the guest, then destroyed.
NATIVE_TEST("anim/layout-blend-container") {
    alignas(16) static u8 storage[sizeof(CAnimationBlendContainer)];
    std::memset(storage, 0xa5, sizeof storage);
    auto* c = reinterpret_cast<CAnimationBlendContainer*>(storage);
    t.call("_ZN9Framework24CAnimationBlendContainerC1Ev", {(u64)c});
    t.expect_eq(c->vtable, vtable_of(t, "_ZTVN9Framework24CAnimationBlendContainerE"), "vtable");
    t.expect_eq(c->m_motions.vtable, vtable_of(t, "_ZTVN4Aska6TArrayIN9Framework24CAnimationBlendContainer17_tBlendMotionDataELb0EEE"),
                "m_motions: TArray<_tBlendMotionData> vtable at 0x08");
    t.expect_eq(c->m_motions.m_minCapacity, (s64)8, "m_motions.m_minCapacity 8");
    t.expect_eq(c->m_motions.m_size, (s64)0, "m_motions empty");
    t.expect_eq(std::isnan(c->unk_88), true, "0x88 NaN");
    t.expect_eq(c->m_blendManager, (AafBlendManager*)nullptr, "no blend manager yet");
    t.call("_ZN9Framework24CAnimationBlendContainer10InitializeEjj", {(u64)c, 3, 2});
    t.expect_eq(c->m_numElements, 3u, "Initialize: m_numElements");
    t.expect_eq((u32)t.call("_ZNK9Framework24CAnimationBlendContainer11NumElementsEv", {(u64)c}), c->m_numElements, "NumElements()");
    t.expect_eq(c->m_currentAnimId, -1, "Initialize: no present animation");
    t.expect_eq(c->m_speed, 1.0f, "Initialize: speed 1");
    if (t.expect_eq(c->m_elements != nullptr, true, "m_elements")) {
        t.expect_eq(*reinterpret_cast<const u64*>(reinterpret_cast<const u8*>(c->m_elements) - 8), (u64)3, "new[] count before m_elements");
        for (u32 i = 0; i < 3; i++) {
            const CAnimationElement& e = c->m_elements[i];
            t.expect_eq(e.base.vtable, vtable_of(t, "_ZTVN9Framework17CAnimationElementE"), "element vtable (0x68 apart)");
            t.expect_eq(e.m_animId, -1, "element m_animId -1");
            t.expect_eq(e.m_aafHandler, (AafHandler*)nullptr, "element m_aafHandler");
        }
    }
    CBlendRatePlayer* brp = c->m_blendRatePlayer;
    if (t.expect_eq(brp != nullptr, true, "m_blendRatePlayer")) {
        t.expect_eq(brp->vtable, vtable_of(t, "_ZTVN9Framework16CBlendRatePlayerE"), "CBlendRatePlayer vtable");
        t.expect_eq(brp->m_count, 2u, "CBlendRatePlayer m_count");
        t.expect_eq((s32)t.call("_ZNK9Framework16CBlendRatePlayer13NumPlayHandleEv", {(u64)brp}), 0, "NumPlayHandle() 0");
        brp->m_pieces[1].m_used = 1;
        brp->m_pieces[1].m_handle = 7;
        t.expect_eq((s32)t.call("_ZNK9Framework16CBlendRatePlayer13NumPlayHandleEv", {(u64)brp}), 1, "NumPlayHandle() counts piece 1 (0x1c apart)");
        brp->m_pieces[1].m_used = 0;
        brp->m_pieces[1].m_handle = 0;
    }
    // The time element: SetPresentFrame / SetMaxLoopCount / Reset on element 0.
    CAnimationElement& e0 = c->m_elements[0];
    guest_call(t.sym("_ZN9Framework21CAnimationTimeElement15SetPresentFrameEf"), GuestArgs().i((u64)&e0).f(42.0f));
    t.expect_eq(e0.base.m_presentFrame, 42.0f, "SetPresentFrame -> m_presentFrame");
    t.call("_ZN9Framework21CAnimationTimeElement15SetMaxLoopCountEj", {(u64)&e0, 5});
    t.expect_eq(e0.base.m_maxLoopCount, 5u, "SetMaxLoopCount -> m_maxLoopCount");
    e0.base.m_loopCount = 9;
    e0.base.m_flag = 0xff;
    vcall(&e0, 0);  // slot 0: CAnimationElement::Reset (ends in CAnimationTimeElement::Reset's fields)
    t.expect_eq(e0.base.m_loopCount, 0u, "Reset: m_loopCount 0");
    t.expect_eq(e0.base.m_speed, 1.0f, "Reset: m_speed 1");
    t.call("_ZN9Framework24CAnimationBlendContainerD1Ev", {(u64)c});
}

// Live (home): an AafHandler in SetValues(frame): the header-derived counts, the one-block layout of the
// targets / infos / cache arrays AttachAaf builds, Length(), the complement getters, the infos.
NATIVE_TEST("anim/layout-live-aaf-handler") {
    bool ok = probe_call(t, g_probeSetValues, [&](Cpu& c) {
        auto* h = reinterpret_cast<const AafHandler*>(c.x(0));
        if (!h || !h->m_header) return false;
        check_handler(t, h, "SetValues");
        return true;
    }, probe_timeout(), "Aska::AafHandler::SetValues", live_screen());
    (void)ok;
}

// Live (home): a CAnimationBlendContainer in PlayAnimation: its elements, the present animation's frame and
// flag through the guest's getters, the motions, the blend manager and blend-rate player, each element's
// AafHandler.
NATIVE_TEST("anim/layout-live-blend-container") {
    probe_call(t, g_probePlayAnimation, [&](Cpu& cpu) {
        auto* c = reinterpret_cast<const CAnimationBlendContainer*>(cpu.x(0));
        t.expect_eq(has_vtable(t, c, "_ZTVN9Framework24CAnimationBlendContainerE"), true, "container vtable");
        t.expect_eq((u32)t.call("_ZNK9Framework24CAnimationBlendContainer11NumElementsEv", {(u64)c}), c->m_numElements, "NumElements()");
        const CAnimationElement* cur = nullptr;
        for (u32 i = 0; i < c->m_numElements; i++) {
            const CAnimationElement& e = c->m_elements[i];
            t.expect_eq(e.base.vtable, vtable_of(t, "_ZTVN9Framework17CAnimationElementE"), "element vtable");
            if (e.m_animId == c->m_currentAnimId && e.m_animId != -1) cur = &e;
            if (e.m_aafHandler) check_handler(t, e.m_aafHandler, "element");
        }
        if (cur) {
            float pf = call_f(t.sym("_ZNK9Framework24CAnimationBlendContainer12PresentFrameEv"), c);
            t.expect_eq(same_float(pf, cur->base.m_presentFrame), true, "PresentFrame() = the present element's m_presentFrame");
            t.expect_eq((u32)t.call("_ZNK9Framework24CAnimationBlendContainer4FlagEv", {(u64)c}), cur->base.m_flag, "Flag() = its m_flag");
        }
        t.expect_eq(c->m_motions.m_size >= 0 && c->m_motions.m_size <= c->m_motions.m_capacity, true, "m_motions size <= capacity");
        for (s64 i = 0; i < c->m_motions.m_size; i++) {
            const CAnimationElement* e = c->m_motions.m_data[i].m_element;
            t.expect_eq(e >= c->m_elements && e < c->m_elements + c->m_numElements, true, "motion m_element in m_elements");
        }
        if (c->m_blendManager) {
            t.expect_eq(has_vtable(t, c->m_blendManager, "_ZTVN4Aska15AafBlendManagerE"), true, "m_blendManager vtable");
            t.expect_eq(c->m_blendManager->m_calcNotify.m_owner, c->m_blendManager, "blend manager _CalcNotify owner");
        }
        if (c->m_blendRatePlayer) {
            const CBlendRatePlayer* b = c->m_blendRatePlayer;
            t.expect_eq(has_vtable(t, b, "_ZTVN9Framework16CBlendRatePlayerE"), true, "m_blendRatePlayer vtable");
            s32 n = 0;
            for (u32 i = 0; i < b->m_count; i++) n += (b->m_pieces[i].m_used && b->m_pieces[i].m_handle) ? 1 : 0;
            t.expect_eq((s32)t.call("_ZNK9Framework16CBlendRatePlayer13NumPlayHandleEv", {(u64)b}), n, "NumPlayHandle()");
        }
        return true;
    }, probe_timeout(), "Framework::CAnimationBlendContainer::PlayAnimation", live_screen());
}

// Live (home): a CAnimationModel in Progress(dt): m_pBlend and the forwarded getters.
NATIVE_TEST("anim/layout-live-animation-model") {
    probe_call(t, g_probeModelProgress, [&](Cpu& cpu) {
        auto* m = reinterpret_cast<const CAnimationModel*>(cpu.x(0));
        if (!m->m_pBlend) return false;
        t.expect_eq(has_vtable(t, m->m_pBlend, "_ZTVN9Framework24CAnimationBlendContainerE"), true, "m_pBlend's vtable");
        t.expect_eq(t.call("_ZN9Framework15CAnimationModel24rAnimationBlendContainerEv", {(u64)m}), (u64)m->m_pBlend,
                    "rAnimationBlendContainer() = m_pBlend");
        if (m->m_pBlend->m_numElements && m->m_pBlend->m_currentAnimId != -1) {
            float a = call_f(t.sym("_ZNK9Framework15CAnimationModel12PresentFrameEv"), m);
            float b = call_f(t.sym("_ZNK9Framework24CAnimationBlendContainer12PresentFrameEv"), m->m_pBlend);
            t.expect_eq(same_float(a, b), true, "PresentFrame() forwards to m_pBlend");
        }
        t.expect_eq(m->m_scale5c == m->m_scale5c, true, "0x5c is a float");
        return true;
    }, probe_timeout(), "Framework::CAnimationModel::Progress", live_screen());
}

// Live (home, while two motions blend): an AafBlendManager in CalcValues: the infos through the getters.
NATIVE_TEST("anim/layout-live-blend-manager") {
    probe_call(t, g_probeBlendCalc, [&](Cpu& cpu) {
        auto* m = reinterpret_cast<const AafBlendManager*>(cpu.x(0));
        t.expect_eq(has_vtable(t, m, "_ZTVN4Aska15AafBlendManagerE"), true, "vtable");
        t.expect_eq(m->m_calcNotify.m_owner, m, "_CalcNotify owner");
        t.expect_eq(m->m_created, (u8)1, "m_created");
        t.expect_eq(m->m_count <= m->m_capacity, true, "m_count <= m_capacity");
        for (s32 i = 0; i < m->m_count; i++) {
            t.expect_eq(call_f(t.sym("_ZNK4Aska15AafBlendManager9GetWeightEi"), m, i), m->m_infos[i].m_weight, "GetWeight(i)");
            t.expect_eq(call_f(t.sym("_ZNK4Aska15AafBlendManager12GetPlayFrameEi"), m, i), m->m_infos[i].m_playFrame, "GetPlayFrame(i)");
            if (m->m_infos[i].m_handler)
                t.expect_eq(has_vtable(t, m->m_infos[i].m_handler, "_ZTVN4Aska10AafHandlerE"), true, "info's AafHandler");
        }
        return true;
    }, live_screen() ? 15000 : 3000, "Aska::AafBlendManager::CalcValues (only while motions blend)", false);
}

}  // namespace soa::native::anim
