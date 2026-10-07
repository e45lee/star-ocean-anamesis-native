// Differential tests of the device natives (render_device.cpp) against the 3.7.0 guest, on the render
// thread's real calls: a probe takes a call, and the guest's function and the native run on it with the
// thread's GL calls recorded (render_check.h's gl_run_both: the state set saved and put back between
// them, the GL call lists and the state set compared), then the call goes on as usual.
#include <set>
#include <string>

#include "native/common/test.h"
#include "native/render/render_check.h"
#include "native/render/render_layout.h"
#include "native/render/render_test_util.h"

namespace soa::native::render {
namespace {

using namespace testutil;

TEST_PROBE(g_probeBindVertexFormat, "_ZN4Aska14RenderDeviceGL16BindVertexFormatEiiPv");
TEST_PROBE(g_probeApply, "_ZN4Aska11RenderState5ApplyEPNS_14RenderDeviceGLE");
TEST_PROBE(g_probeSetTexture, "_ZN4Aska14RenderDeviceGL10SetTextureEjPKPNS_11GpuResourceE");
TEST_PROBE(g_probeRemoveTexture, "_ZN4Aska14RenderDeviceGL13RemoveTextureEj");
TEST_PROBE(g_probeUpdateShaderProgram, "_ZN4Aska16RenderDeviceData19UpdateShaderProgramEv");
TEST_PROBE(g_probeDraw, "_ZN4Aska16RenderDeviceData20DrawIndexedPrimitiveEPNS_14RenderDeviceGLENS_8PrimType4TypeERNS_11IndexBufferEmi");

}  // namespace

// BindVertexFormat on 300 of the render thread's calls (the formats the title / home draw use).
NATIVE_TEST("render/device-bind-vertex-format") {
    std::set<s32> formats;
    int calls = 0, bad = 0;
    for (int n = 0; n < 300 && bad < 3; n++) {
        bool ok = probe_call(t, g_probeBindVertexFormat, [&](Cpu& c) {
            auto* dev = reinterpret_cast<RenderDeviceGL*>(c.x(0));
            OglStateSet0* ss = dev->m_data->m_stateCache->StateSet0();
            if (!ss) return false;
            const u64 x[4] = {c.x(0), c.x(1), c.x(2), c.x(3)};
            std::string why = gl_run_both({{ss, sizeof *ss}},
                                          [&] { guest_call(g_probeBindVertexFormat.orig, {x[0], x[1], x[2], x[3]}); },
                                          [&] { dev->BindVertexFormat((s32)x[1], (s32)x[2], (void*)x[3]); });
            if (!why.empty()) {
                t.fail("BindVertexFormat(format %d, stride %d): %s", (s32)x[1], (s32)x[2], why.c_str());
                bad++;
            }
            formats.insert((s32)x[1]);
            calls++;
            return true;
        }, 20000, "RenderDeviceGL::BindVertexFormat");
        if (!ok) break;
    }
    fprintf(stderr, "    %d calls, %zu formats\n", calls, formats.size());
    t.expect_eq(calls > 0, true, "calls taken");
}

// RenderState::Apply (and through it every render-state setter: the guest's chain against the natives')
// on 1,000 of the render thread's calls; the opcodes seen are reported.
NATIVE_TEST("render/state-apply") {
    std::set<u8> ops;
    int calls = 0, bad = 0;
    for (int n = 0; n < 1000 && bad < 3; n++) {
        bool ok = probe_call(t, g_probeApply, [&](Cpu& c) {
            auto* rs = reinterpret_cast<RenderState*>(c.x(0));
            auto* dev = reinterpret_cast<RenderDeviceGL*>(c.x(1));
            RenderDeviceGL* d = dev ? dev : global_ptr<RenderDeviceGL>(kVaddrRenderDev);
            OglStateSet0* ss = d->m_data->m_stateCache->StateSet0();
            if (!ss || !rs->m_commands) return false;
            const u8* p = rs->m_commands;
            for (u32 i = 0; i < rs->m_count; i++) {  // (the opcodes, for the report; sizes as Apply's)
                ops.insert(p[0]);
                switch (p[0]) {
                case 0xc8: case 0xcb: case 0xce: case 0xe0: case 0xdb: case 0xdc: case 0xdd: case 0xdf: case 0xe2: p += 2; break;
                case 0xc9: case 0xcc: case 0xcf: case 0xd0: case 0xd1: case 0xd2: case 0xd3: case 0xd9: p += 3; break;
                case 0xde: p += 9; break;
                case 0xe3: case 0xe4: p += 7; break;
                default: p += 1; break;
                }
            }
            std::string why = gl_run_both({{ss, sizeof *ss}}, [&] { guest_call(g_probeApply.orig, {c.x(0), c.x(1)}); },
                                          [&] { rs->Apply(dev); });
            if (!why.empty()) {
                t.fail("Apply (%u commands): %s", rs->m_count, why.c_str());
                bad++;
            }
            calls++;
            return true;
        }, 20000, "RenderState::Apply");
        if (!ok) break;
    }
    std::string list;
    for (u8 o : ops) list += " " + std::to_string(o);
    fprintf(stderr, "    %d calls, opcodes:%s\n", calls, list.c_str());
    t.expect_eq(calls > 0, true, "calls taken");
}

// DrawIndexedPrimitive with all it runs before the draw (UpdateRenderState, UpdateVertexAttribute, the
// blending and depth commands): the guest's chain against the natives' on 1,000 of the render thread's
// draws, UpdateShaderProgram and the texture commands recorded as markers (t_mark_callees); draws with
// a buffer upload pending or instance data are left out (the natives run the guest's then). The program is
// established for real first (establish_program, as the live check does); every 4th draw starts from a null
// m_program, the state CompileShaderProgramCache leaves (the battle's loading): the marked runs crashed in
// UpdateVertexAttribute on it before establish_program.
NATIVE_TEST("render/device-draw") {
    int calls = 0, bad = 0, skipped = 0, nulled = 0;
    for (int n = 0; n < 1000 && bad < 3; n++) {
        bool ok = probe_call(t, g_probeDraw, [&](Cpu& c) {
            auto* d = reinterpret_cast<RenderDeviceData*>(c.x(0));
            auto* ib = reinterpret_cast<IndexBuffer*>(c.x(3));
            OglStateSet0* ss = d->m_stateCache->StateSet0();
            if (!ss) return false;
            if (d->UsesInstancing() || (ib->m_resource && ib->m_resource->NeedsUpload())) {
                skipped++;
                return false;
            }
            const u64 x[6] = {c.x(0), c.x(1), c.x(2), c.x(3), c.x(4), c.x(5)};
            if (d->m_drawEnabled) {
                if (n % 4 == 0) {
                    d->m_program = nullptr;
                    nulled++;
                }
                establish_program(d);
                if (!d->m_program) {
                    t.fail("no program after establish_program");
                    bad++;
                    return true;
                }
            }
            t_mark_callees = true;
            std::string why = gl_run_both({{ss, sizeof *ss}}, [&] { guest_call(g_probeDraw.orig, {x[0], x[1], x[2], x[3], x[4], x[5]}); },
                                          [&] { d->DrawIndexedPrimitive((RenderDeviceGL*)x[1], (u32)x[2], *ib, x[4], (s32)x[5]); });
            t_mark_callees = false;
            if (!why.empty()) {
                t.fail("DrawIndexedPrimitive(prim %u, start %llu, count %d): %s", (u32)x[2], (unsigned long long)x[4], (s32)x[5], why.c_str());
                bad++;
            }
            calls++;
            return true;
        }, 20000, "RenderDeviceData::DrawIndexedPrimitive");
        if (!ok) break;
    }
    fprintf(stderr, "    %d draws compared (%d from a null program), %d skipped\n", calls, nulled, skipped);
    t.expect_eq(calls > 0, true, "draws taken");
    t.expect_eq(nulled > 0, true, "draws from a null program");
}

// SetTexture (with ActiveTexture and BindTexture under it) and RemoveTexture on the render thread's calls;
// SetTexture calls with an upload pending are left out.
NATIVE_TEST("render/device-textures") {
    int calls = 0, removes = 0, bad = 0, skipped = 0;
    for (int n = 0; n < 1000 && bad < 3; n++) {
        bool ok = probe_call(t, g_probeSetTexture, [&](Cpu& c) {
            auto* dev = reinterpret_cast<RenderDeviceGL*>(c.x(0));
            auto* res = reinterpret_cast<GpuResource* const*>(c.x(2));
            OglStateSet0* ss = dev->m_data->m_stateCache->StateSet0();
            if (!ss) return false;
            if (res && (u32)c.x(1) < dev->m_textureStageCount && (!*res || (*res)->NeedsUpload())) {
                skipped++;
                return false;
            }
            const u64 x[3] = {c.x(0), c.x(1), c.x(2)};
            std::string why = gl_run_both({{ss, sizeof *ss}}, [&] { guest_call(g_probeSetTexture.orig, {x[0], x[1], x[2]}); },
                                          [&] { dev->SetTexture((u32)x[1], res); });
            if (!why.empty()) {
                t.fail("SetTexture(stage %u): %s", (u32)x[1], why.c_str());
                bad++;
            }
            calls++;
            return true;
        }, 20000, "RenderDeviceGL::SetTexture");
        if (!ok) break;
    }
    for (int n = 0; n < 200 && bad < 3; n++) {
        bool ok = probe_call(t, g_probeRemoveTexture, [&](Cpu& c) {
            auto* dev = reinterpret_cast<RenderDeviceGL*>(c.x(0));
            OglStateSet0* ss = dev->m_data->m_stateCache->StateSet0();
            if (!ss) return false;
            const u64 x[2] = {c.x(0), c.x(1)};
            std::string why = gl_run_both({{ss, sizeof *ss}}, [&] { guest_call(g_probeRemoveTexture.orig, {x[0], x[1]}); },
                                          [&] { dev->RemoveTexture((u32)x[1]); });
            if (!why.empty()) {
                t.fail("RemoveTexture(stage %u): %s", (u32)x[1], why.c_str());
                bad++;
            }
            removes++;
            return true;
        }, 20000, "RenderDeviceGL::RemoveTexture", false);
        if (!ok) break;
    }
    fprintf(stderr, "    %d SetTexture compared (%d skipped), %d RemoveTexture\n", calls, skipped, removes);
    t.expect_eq(calls > 0, true, "SetTexture calls taken");
}

// UpdateShaderProgram on the render thread's calls that only find a linked program (the native's case),
// SetShaderProgramUniform recorded as a marker; the thread's state set 1 and the device's program
// fields compared.
NATIVE_TEST("render/device-shader-program") {
    int calls = 0, current = 0, bad = 0, skipped = 0;
    for (int n = 0; n < 1000 && bad < 3; n++) {
        bool ok = probe_call(t, g_probeUpdateShaderProgram, [&](Cpu& c) {
            auto* d = reinterpret_cast<RenderDeviceData*>(c.x(0));
            OglStateSet1* s1 = d->GetThreadOglState1();
            if (!s1 || !d->ProgramReady()) {
                skipped++;
                return false;
            }
            const PixelShader* ps = d->m_pixelShader ? d->m_pixelShader : d->m_defaultPixelShader;
            if (d->m_program && d->m_program->m_vsKey == d->m_vertexShader->m_key && d->m_program->m_psKey == ps->m_key) current++;
            t_mark_callees = true;
            std::string why = gl_run_both({{s1, sizeof *s1}, {&d->m_programHash, 0x18}, {&d->m_program, sizeof d->m_program}},
                                          [&] { guest_call(g_probeUpdateShaderProgram.orig, {(u64)d}); }, [&] { d->UpdateShaderProgram(); });
            t_mark_callees = false;
            if (!why.empty()) {
                t.fail("UpdateShaderProgram: %s", why.c_str());
                bad++;
            }
            calls++;
            return true;
        }, 20000, "RenderDeviceData::UpdateShaderProgram");
        if (!ok) break;
    }
    fprintf(stderr, "    %d compared (%d with the current program), %d skipped\n", calls, current, skipped);
    t.expect_eq(calls > current, true, "lookups of another program compared");
}

}  // namespace soa::native::render
