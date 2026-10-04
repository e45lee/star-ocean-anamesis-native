// RenderDeviceData's draw: DrawIndexedPrimitive and what it runs before the GL draw call
// (UpdateRenderState: the program, the vertex arrays, the caps, viewport, cull, blending, depth, color
// mask, textures), from the disassembly where Ghidra's C loses arguments or misreads the tail calls
// (port/decomp/render/render_device.c, state_cache.c: "Possible PIC construction"). The wanted state
// in the thread's OglStateSet0 (the setters' records) is compared with what GL has and applied.
//
// Kept on the guest (called from the natives): UpdateShaderProgram, LastMinuteDrawCommands_Textures, the
// index buffer's GetData / Is32BitBuffer, a buffer's upload handler; and the instanced paths (a draw with
// instance data: the natives run the guest original of DrawIndexedPrimitive / UpdateVertexAttribute,
// which reach glVertexAttribDivisor / glDrawElementsInstanced through function pointers the game
// fetched).
//
// Live check (soa --live-check render): gl_run_both over the thread's state set; DrawIndexedPrimitive's
// and UpdateRenderState's checks are of the whole call (their guest callees run in both runs, recorded).
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>

#include "core/cpu.h"
#include "core/loader.h"
#include "hle/gl_host.h"
#include "native/common/guest_std.h"
#include "native/common/native.h"
#include "native/common/test.h"
#include "native/render/render_check.h"
#include "native/render/render_layout.h"

namespace soa::native::render {

namespace {

using Fn = live::RunBothFamily::Fn;

Fn fDraw(fam(), "_ZN4Aska16RenderDeviceData20DrawIndexedPrimitiveEPNS_14RenderDeviceGLENS_8PrimType4TypeERNS_11IndexBufferEmi");
Fn fUpdateRenderState(fam(), "_ZN4Aska16RenderDeviceData17UpdateRenderStateEPNS_14RenderDeviceGLE");
Fn fUpdateVertexAttribute(fam(), "_ZN4Aska16RenderDeviceData21UpdateVertexAttributeEPNS_18ASKA_OGL_STATESET0E");
Fn fBlending(fam(), "_ZN4Aska16RenderDeviceData31LastMinuteDrawCommands_BlendingEPNS_18ASKA_OGL_STATESET0E");
Fn fDepth(fam(), "_ZN4Aska16RenderDeviceData28LastMinuteDrawCommands_DepthEPNS_18ASKA_OGL_STATESET0E");

RenderDeviceGL* render_dev() {
    static RenderDeviceGL** g = reinterpret_cast<RenderDeviceGL**>(guest::sym("_ZN4Aska12g_pRenderDevE"));
    return *g;
}
u64 gsym(const char* s) { return guest::sym(s); }

// PrimType::Type -> GL mode (the guest's table)
u32 prim_mode(u32 prim) { return reinterpret_cast<const u32*>(main_lib()->base + 0x28ce77c)[prim]; }
// LastMinuteDrawCommands_Depth's polygon-offset threshold (a float constant of the guest)
float offset_epsilon() { return *reinterpret_cast<const float*>(main_lib()->base + 0x26fac84); }

// A cap bit pair of OglStateSet0::m_capFlags: wanted bit `want`, GL's bit `set`; glEnable / glDisable
// `cap` when they differ, then GL's bit = the wanted one.
void sync_cap(OglStateSet0* ss, int want, int set, GLenum cap) {
    const u16 f = ss->m_capFlags;
    const u16 w = (f >> want) & 1;
    if (w == ((f >> set) & 1)) return;
    if (w) GLH(glEnable, cap);
    else GLH(glDisable, cap);
    const u16 g = ss->m_capFlags;
    ss->m_capFlags = (u16)((g & ~(1u << set)) | (((g >> want) & 1u) << set));
}

// The guest callees of the draw natives, hooked so a check can record them instead of running them
// (t_mark_callees): a native forwarding to the original, and the same as a --selftest hook (natives
// aren't installed there) for the differential tests.
struct Callee {
    const char* sym;
    const char* name;
    int nargs;
    u64 orig = 0, test_orig = 0;
};
Callee g_updateShaderProgram{"_ZN4Aska16RenderDeviceData19UpdateShaderProgramEv", "UpdateShaderProgram", 1};
Callee g_textures{"_ZN4Aska16RenderDeviceData31LastMinuteDrawCommands_TexturesEPNS_18ASKA_OGL_STATESET0EPNS_14RenderDeviceGLE",
                  "LastMinuteDrawCommands_Textures", 3};
Callee g_setUniform{"_ZN4Aska16RenderDeviceData23SetShaderProgramUniformEPNS_18ShaderProgramValueE", "SetShaderProgramUniform", 2};

template <Callee* C>
void callee_hook(Cpu& c) {
    if (t_mark_callees && glh::t_rec) {
        std::string m = std::string("@") + C->name + "(";
        for (int i = 0; i < C->nargs; i++) {
            char a[24];
            snprintf(a, sizeof a, "%s%#llx", i ? ", " : "", (unsigned long long)c.x(i));
            m += a;
        }
        glh::t_rec->calls.push_back(m + ")");
        return;
    }
    guest_call(C->orig ? C->orig : C->test_orig, {c.x(0), c.x(1), c.x(2)});
}

// Before a check of a draw: a buffer upload would run in the recorded runs (its GL not executed, the
// buffer then marked clean): such calls aren't checked.
bool upload_pending(const IndexBuffer& ib) {
    const GpuResource* r = ib.m_resource;
    return r && r->NeedsUpload();
}

}  // namespace

thread_local bool t_mark_callees = false;

bool GpuResource::EnsureUploaded() {
    if (!NeedsUpload()) return true;
    auto* h = reinterpret_cast<const u64* const*>(m_handler);
    if (!(guest_call((*h)[0], {(u64)m_handler, (u64)this}) & 1)) return false;
    m_dirty = 0;
    return true;
}

NATIVE_FUNCTION_ORIG(g_textures.sym, callee_hook<&g_textures>, "render: (hook) RenderDeviceData::LastMinuteDrawCommands_Textures",
                     &g_textures.orig);
NATIVE_TEST_HOOK(g_updateShaderProgram.sym, callee_hook<&g_updateShaderProgram>, &g_updateShaderProgram.test_orig);
NATIVE_TEST_HOOK(g_textures.sym, callee_hook<&g_textures>, &g_textures.test_orig);
NATIVE_FUNCTION_ORIG(g_setUniform.sym, callee_hook<&g_setUniform>, "render: (hook) RenderDeviceData::SetShaderProgramUniform", &g_setUniform.orig);
NATIVE_TEST_HOOK(g_setUniform.sym, callee_hook<&g_setUniform>, &g_setUniform.test_orig);

// (UpdateShaderProgram is a native, render_program.cpp: it records its marker itself; its test hook
// here serves the --selftest chains.)
bool mark_callee(const char* name, std::initializer_list<u64> args) {
    if (!t_mark_callees || !glh::t_rec) return false;
    std::string m = std::string("@") + name + "(";
    int i = 0;
    for (u64 a : args) {
        char b[24];
        snprintf(b, sizeof b, "%s%#llx", i++ ? ", " : "", (unsigned long long)a);
        m += b;
    }
    glh::t_rec->calls.push_back(m + ")");
    return true;
}

// The arrays the current program uses (its attribute locations, the first m_attribCount of the vertex
// shader) are wanted, the rest up to the device's attribute count (at most 32) not; GL is synced with a
// glEnable / glDisableVertexAttribArray per difference. (The instanced head: the HostFn / callers run the
// guest original instead when UsesInstancing().)
void RenderDeviceData::UpdateVertexAttribute(OglStateSet0* ss) {
    s32 n = m_vertexShader->m_attribCount;
    if (n < 1) n = 0;
    for (s32 i = 0; i < n; i++) {
        const u8 want = m_program->m_attribLocations[i] != -1;
        const u8 gl = ss->m_attribGL[i];
        ss->m_attribWant[i] = want;
        if (want == gl) continue;
        if (want) GLH(glEnableVertexAttribArray, (GLuint)i);
        else GLH(glDisableVertexAttribArray, (GLuint)i);
        ss->m_attribGL[i] = ss->m_attribWant[i];
    }
    const s32 cap = m_vertexAttribCount < 0x20 ? (s32)m_vertexAttribCount : 0x20;
    for (s32 i = n; i < cap; i++) {
        ss->m_attribWant[i] = 0;
        if (ss->m_attribGL[i]) {
            GLH(glDisableVertexAttribArray, (GLuint)i);
            ss->m_attribGL[i] = ss->m_attribWant[i];
        }
    }
}

// Blending: the GL_BLEND cap, then the blend function and equation when they changed (separate unless
// the device is the old GPU / driver combination that needs the plain calls).
void RenderDeviceData::LastMinuteDrawCommands_Blending(OglStateSet0* ss) {
    sync_cap(ss, 3, 10, GL_BLEND);
    const RenderDeviceGL* dev = render_dev();
    bool plain = false;
    if (dev->m_gpuKind == 3 && dev->m_gpuNumber >= 300) {
        if (dev->m_driverVersion[0] < 4) plain = true;
        else plain = dev->m_driverVersion[0] == 4 && dev->m_driverVersion[1] < 3;
    }
    const u32* w = ss->m_blend;
    u32* g = ss->m_blendGL;
    if (w[0] != g[0] || w[1] != g[1] || w[3] != g[3] || w[4] != g[4]) {
        if (plain) GLH(glBlendFunc, w[0], w[1]);
        else GLH(glBlendFuncSeparate, w[0], w[1], w[3], w[4]);
        g[0] = w[0];
        g[1] = w[1];
        g[3] = w[3];
        g[4] = w[4];
    }
    if (w[2] != g[2] || w[5] != g[5]) {
        if (plain) GLH(glBlendEquation, w[2]);
        else GLH(glBlendEquationSeparate, w[2], w[5]);
        g[2] = w[2];
        g[5] = w[5];
    }
}

// Depth: the GL_DEPTH_TEST cap, the depth function, the polygon offset (and GL_POLYGON_OFFSET_FILL on
// when either value is above the threshold).
void RenderDeviceData::LastMinuteDrawCommands_Depth(OglStateSet0* ss) {
    sync_cap(ss, 1, 8, GL_DEPTH_TEST);
    if (ss->m_depthFunc != ss->m_depthFuncGL) {
        GLH(glDepthFunc, ss->m_depthFunc);
        ss->m_depthFuncGL = ss->m_depthFunc;
    }
    const float f = ss->m_polygonOffset[0], u = ss->m_polygonOffset[1];
    if (f == ss->m_polygonOffsetGL[0] && u == ss->m_polygonOffsetGL[1]) return;
    GLH(glPolygonOffset, f, u);
    ss->m_polygonOffsetGL[0] = ss->m_polygonOffset[0];
    ss->m_polygonOffsetGL[1] = ss->m_polygonOffset[1];
    const float eps = offset_epsilon();
    if (std::fabs(ss->m_polygonOffset[0]) > eps || std::fabs(ss->m_polygonOffset[1]) > eps) GLH(glEnable, (GLenum)GL_POLYGON_OFFSET_FILL);
    else GLH(glDisable, (GLenum)GL_POLYGON_OFFSET_FILL);
}

bool RenderDeviceData::UpdateRenderState(RenderDeviceGL* device) {
    guest_call(gsym(g_updateShaderProgram.sym), {(u64)this});
    OglStateSet0* ss = m_stateCache->StateSet0();  // (the HostFn checked it exists)
    if (UsesInstancing()) guest_call(fUpdateVertexAttribute.orig, {(u64)this, (u64)ss});
    else UpdateVertexAttribute(ss);
    sync_cap(ss, 4, 11, GL_SAMPLE_ALPHA_TO_COVERAGE);
    sync_cap(ss, 5, 12, GL_DITHER);
    const s32* vw = ss->m_viewport;
    s32* vg = ss->m_viewportGL;
    if (vw[0] != vg[0] || vw[1] != vg[1] || vw[2] != vg[2] || vw[3] != vg[3]) {
        GLH(glViewport, vw[0], vw[1], vw[2], vw[3]);
        std::memcpy(vg, vw, 16);
    }
    sync_cap(ss, 0, 7, GL_CULL_FACE);
    if (ss->m_frontFace != ss->m_frontFaceGL) {
        GLH(glFrontFace, ss->m_frontFace);
        ss->m_frontFaceGL = ss->m_frontFace;
    }
    if (ss->m_cullFace != ss->m_cullFaceGL) {
        GLH(glCullFace, ss->m_cullFace);
        ss->m_cullFaceGL = ss->m_cullFace;
    }
    LastMinuteDrawCommands_Blending(ss);
    LastMinuteDrawCommands_Depth(ss);
    sync_cap(ss, 2, 9, GL_STENCIL_TEST);
    const u8 cm = (u8)ss->m_colorMask;
    if (((ss->m_colorMaskGL ^ cm) & 0xf) != 0) {
        GLH(glColorMask, (GLboolean)(cm & 1), (GLboolean)((cm >> 1) & 1), (GLboolean)((cm >> 2) & 1), (GLboolean)((cm >> 3) & 1));
        ss->m_colorMaskGL = ss->m_colorMask;
    }
    guest_call(gsym(g_textures.sym), {(u64)this, (u64)ss, (u64)device});
    return true;
}

// The draw: the state (UpdateRenderState), the index buffer bound (uploaded first if needed) or its
// client memory, glDrawElements, then GL_ELEMENT_ARRAY_BUFFER unbound. (Instanced draws: the HostFn runs
// the guest original.)
void RenderDeviceData::DrawIndexedPrimitive(RenderDeviceGL* device, u32 prim, IndexBuffer& ib, u64 start, s32 count) {
    if (!m_drawEnabled) return;
    if (!UpdateRenderState(device)) return;
    u32 buffer = 0;
    if (GpuResource* res = ib.m_resource) {
        res->EnsureUploaded();
        buffer = (u32)ib.m_resource->m_handle;
    }
    OglStateSet0* ss = render_dev()->m_data->m_stateCache->StateSet0();
    if (ss->m_elementBuffer != buffer) {
        GLH(glBindBuffer, (GLenum)GL_ELEMENT_ARRAY_BUFFER, buffer);
        ss->m_elementBuffer = buffer;
    }
    const u32 mode = prim_mode(prim);
    u64 base;
    GpuResource* res = ib.m_resource;
    if (res) res->EnsureUploaded();
    if (res && ib.m_resource->m_handle != 0) base = 0;
    else base = guest_call(gsym("_ZNK4Aska11IndexBuffer7GetDataEi"), {(u64)&ib, 1});
    const bool is32 = guest_call(gsym("_ZNK4Aska11IndexBuffer13Is32BitBufferEv"), {(u64)&ib}) & 1;
    const u64 indices = base + (start << (is32 ? 2 : 1));
    GLH(glDrawElements, mode, count, (GLenum)(is32 ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT), (const void*)indices);
    OglStateSet0* after = render_dev()->m_data->m_stateCache->StateSet0();
    if (after->m_elementBuffer != 0) {
        GLH(glBindBuffer, (GLenum)GL_ELEMENT_ARRAY_BUFFER, 0u);
        after->m_elementBuffer = 0;
    }
}

namespace {

// The natives: the guest original when the thread has no state set yet (or the draw is instanced);
// gl_run_both over the state set when checked.
template <typename Native>
void run(Cpu& c, Fn& f, RenderDeviceData* d, bool fallback, Native native, bool composite = false, bool checkable = true) {
    OglStateSet0* ss = d->m_stateCache->StateSet0();
    if (!ss || fallback) {
        c.set_x(0, guest_call(f.orig, {c.x(0), c.x(1), c.x(2), c.x(3), c.x(4), c.x(5)}));
        return;
    }
    if (__builtin_expect(fam().due(f), 0)) {
        live::RunBothFamily::Scope scope;
        if (!checkable) {
            fam().result(f, live::RunBothFamily::Outcome::Skipped, "a buffer upload pending");
        } else {
            const u64 x[6] = {c.x(0), c.x(1), c.x(2), c.x(3), c.x(4), c.x(5)};
            t_mark_callees = composite;
            std::string why = gl_run_both({{ss, sizeof *ss}}, [&] { guest_call(f.orig, {x[0], x[1], x[2], x[3], x[4], x[5]}); }, [&] { native(); });
            t_mark_callees = false;
            fam().result(f, why.empty() ? live::RunBothFamily::Outcome::Ok : live::RunBothFamily::Outcome::Mismatch, why);
        }
    }
    native();
}

void HostDraw(Cpu& c) {
    auto* d = reinterpret_cast<RenderDeviceData*>(c.x(0));
    auto& ib = *(IndexBuffer*)c.x(3);
    run(c, fDraw, d, d->UsesInstancing(), [&] {
        d->DrawIndexedPrimitive((RenderDeviceGL*)c.x(1), (u32)c.x(2), ib, c.x(4), (s32)c.x(5));
    }, true, !upload_pending(ib));
}
void HostUpdateRenderState(Cpu& c) {
    auto* d = reinterpret_cast<RenderDeviceData*>(c.x(0));
    run(c, fUpdateRenderState, d, d->UsesInstancing(), [&] { c.set_x(0, d->UpdateRenderState((RenderDeviceGL*)c.x(1))); }, true);
}
void HostUpdateVertexAttribute(Cpu& c) {
    auto* d = reinterpret_cast<RenderDeviceData*>(c.x(0));
    run(c, fUpdateVertexAttribute, d, d->UsesInstancing(), [&] { d->UpdateVertexAttribute((OglStateSet0*)c.x(1)); });
}
void HostBlending(Cpu& c) {
    auto* d = reinterpret_cast<RenderDeviceData*>(c.x(0));
    run(c, fBlending, d, false, [&] { d->LastMinuteDrawCommands_Blending((OglStateSet0*)c.x(1)); });
}
void HostDepth(Cpu& c) {
    auto* d = reinterpret_cast<RenderDeviceData*>(c.x(0));
    run(c, fDepth, d, false, [&] { d->LastMinuteDrawCommands_Depth((OglStateSet0*)c.x(1)); });
}

}  // namespace

NATIVE_FUNCTION_ORIG(fDraw.sym, HostDraw, "render: RenderDeviceData::DrawIndexedPrimitive", &fDraw.orig);
NATIVE_FUNCTION_ORIG(fUpdateRenderState.sym, HostUpdateRenderState, "render: RenderDeviceData::UpdateRenderState", &fUpdateRenderState.orig);
NATIVE_FUNCTION_ORIG(fUpdateVertexAttribute.sym, HostUpdateVertexAttribute, "render: RenderDeviceData::UpdateVertexAttribute",
                     &fUpdateVertexAttribute.orig);
NATIVE_FUNCTION_ORIG(fBlending.sym, HostBlending, "render: RenderDeviceData::LastMinuteDrawCommands_Blending", &fBlending.orig);
NATIVE_FUNCTION_ORIG(fDepth.sym, HostDepth, "render: RenderDeviceData::LastMinuteDrawCommands_Depth", &fDepth.orig);

}  // namespace soa::native::render
