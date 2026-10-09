// Aska::RenderDeviceGL / RenderDeviceData's draw path (port/decomp/render/render_device.c): natives that
// issue GL through GLH (hle/gl_host.h: the same host entry points, and translations, as the guest's HLE
// thunks), so a draw's GL calls go to the host directly instead of one HLE trap each.
//
// The per-thread GL state cache (ASKA_OGL_STATESET0) behind a StateCacheThreadSafe pthread key is the
// guest's, in place: the natives read and write it as the guest does, so guest and native device code
// mix on it. The key and the thread's state set are created by the guest on first use (an inlined
// get-or-create in every device method); a native that finds them missing runs the guest original
// instead (once per thread).
//
// Live check (soa --live-check render): render_check.h's gl_run_both.
#include <cstring>

#include "soaruntime/core/cpu.h"
#include "soaruntime/core/hle.h"
#include "soaruntime/hle/gl_host.h"
#include "native/common/guest_std.h"
#include "native/common/native.h"
#include "native/common/native_method.h"
#include "native/render/render_check.h"
#include "native/render/render_layout.h"

namespace soa::native::render {

OglStateSet0* StateCacheThreadSafe::StateSet0() const {
    if (__atomic_load_n(&m_keySet0Created, __ATOMIC_ACQUIRE) == 0) return nullptr;
    return reinterpret_cast<OglStateSet0*>(guest_getspecific(m_keySet0));
}

namespace {

RenderDeviceGL* render_dev() {
    static RenderDeviceGL** g = reinterpret_cast<RenderDeviceGL**>(guest::sym("_ZN4Aska12g_pRenderDevE"));
    return *g;
}

// glVertexAttribPointer's (size, type, normalized) for a vertex element type of the engine; false for a
// type the device skips (the half-float and packed ones on a GLES 2 device).
bool attrib_format(u8 type, GLint& size, GLenum& gltype, GLboolean& normalized) {
    normalized = GL_FALSE;
    switch (type) {
    case 1: size = 1; gltype = GL_FLOAT; return true;
    case 2: size = 2; gltype = GL_FLOAT; return true;
    case 3: size = 3; gltype = GL_FLOAT; return true;
    case 4: size = 4; gltype = GL_FLOAT; return true;
    case 8: size = 4; gltype = GL_SHORT; return true;
    case 9: size = 2; gltype = GL_SHORT; normalized = GL_TRUE; return true;
    case 10: size = 4; gltype = GL_SHORT; normalized = GL_TRUE; return true;
    case 0xb: size = 2; gltype = GL_UNSIGNED_SHORT; return true;
    case 0xc: size = 4; gltype = GL_UNSIGNED_SHORT; return true;
    case 0xd: size = 2; gltype = GL_UNSIGNED_SHORT; normalized = GL_TRUE; return true;
    case 0xe: size = 4; gltype = GL_UNSIGNED_SHORT; normalized = GL_TRUE; return true;
    case 0xf: size = 4; gltype = GL_UNSIGNED_BYTE; return true;
    case 0x10: case 0x1d: size = 4; gltype = GL_UNSIGNED_BYTE; normalized = GL_TRUE; return true;
    default: break;
    }
    // GLES 3 only (the global device's version, as the guest reads it)
    if (render_dev()->m_data->m_glVersion == 0) return false;
    switch (type) {
    case 5: size = 2; gltype = GL_HALF_FLOAT; return true;
    case 6: size = 4; gltype = GL_HALF_FLOAT; return true;
    case 0x17: size = 4; gltype = GL_UNSIGNED_INT_2_10_10_10_REV; return true;
    case 0x18: size = 4; gltype = GL_INT_2_10_10_10_REV; return true;
    default: return false;
    }
}

}  // namespace

// Points the vertex attributes of `format` at `base` (a buffer offset or a client pointer) with
// `stride`: every attribute the device has is marked unneeded in the thread's state set, then each
// element the current vertex shader uses (its location >= 0) is marked needed and pointed; the
// arrays are enabled / disabled later, at the draw (UpdateVertexAttribute). The caller (the HostFn)
// guarantees the thread's state set exists.
void RenderDeviceGL::BindVertexFormat(s32 format, s32 stride, void* base) {
    RenderDeviceData* d = m_data;
    const VertexShader* vs = d->m_vertexShader;
    OglStateSet0* ss = d->m_stateCache->StateSet0();
    for (u32 i = 0; i < m_data->m_vertexAttribCount; i++) ss->m_attribWant[i] = 0;
    const VertexFormatGL& f = m_vertexFormats[format];
    for (u32 k = 0; k < f.m_count; k++) {
        const VertexAttrGL& a = f.m_attrs[k];
        const s32 loc = vs->m_attribLocation[a.m_semantic][a.m_index];
        GLint size;
        GLenum type;
        GLboolean normalized;
        if (loc < 0 || !attrib_format(a.m_type, size, type, normalized)) continue;
        ss->m_attribWant[loc] = 1;
        GLH(glVertexAttribPointer, (GLuint)loc, size, type, normalized, stride, (const void*)((u64)base + a.m_offset));
    }
}

namespace {

live::RunBothFamily::Fn fBindVertexFormat(fam(), "_ZN4Aska14RenderDeviceGL16BindVertexFormatEiiPv");

void HostBindVertexFormat(Cpu& c) {
    auto* dev = reinterpret_cast<RenderDeviceGL*>(c.x(0));
    const s32 format = (s32)c.x(1), stride = (s32)c.x(2);
    void* base = (void*)c.x(3);
    OglStateSet0* ss = dev->m_data->m_stateCache->StateSet0();
    if (!ss) {  // the thread's first device call: the guest creates the key / the state set
        guest_call(fBindVertexFormat.orig, {c.x(0), c.x(1), c.x(2), c.x(3)});
        return;
    }
    if (__builtin_expect(fam().due(fBindVertexFormat), 0)) {
        live::RunBothFamily::Scope scope;
        std::string why = gl_run_both({{ss, sizeof *ss}},
                                      [&] { guest_call(fBindVertexFormat.orig, {c.x(0), c.x(1), c.x(2), c.x(3)}); },
                                      [&] { dev->BindVertexFormat(format, stride, base); });
        fam().result(fBindVertexFormat, why.empty() ? live::RunBothFamily::Outcome::Ok : live::RunBothFamily::Outcome::Mismatch, why);
    }
    dev->BindVertexFormat(format, stride, base);
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN4Aska14RenderDeviceGL16BindVertexFormatEiiPv", HostBindVertexFormat, "render: RenderDeviceGL::BindVertexFormat",
                     &fBindVertexFormat.orig);

}  // namespace soa::native::render
