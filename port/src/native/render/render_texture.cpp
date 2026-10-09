// RenderDeviceGL's texture binds (port/decomp/render/render_device.c, with the disassembly for the
// stores Ghidra drops after the GL calls): SetTexture / RemoveTexture (a draw's stage textures, from
// RenderContext::OnPaint), ActiveTexture and BindTexture (GL calls skipped when the thread's OglStateSet0
// says GL has the state already; the cache updated after a call).
//
// Live check (soa --live-check render): gl_run_both over the thread's state set; SetTexture calls whose
// texture would be uploaded first are skipped (the upload would run in the recorded runs).
#include <cstring>

#include "soaruntime/core/cpu.h"
#include "soaruntime/hle/gl_host.h"
#include "native/common/native.h"
#include "native/render/render_check.h"
#include "native/render/render_layout.h"

namespace soa::native::render {

namespace {
inline OglStateSet0* state_set(const RenderDeviceData* d) { return d->m_stateCache->StateSet0(); }

// The binding cache of `target` in the state set (2D for anything but 3D and cube maps).
u32* binding_cache(OglStateSet0* ss, u32 target) {
    if (target == GL_TEXTURE_3D) return ss->m_texture3D;
    if (target == GL_TEXTURE_CUBE_MAP) return ss->m_textureCube;
    return ss->m_texture2D;
}
}  // namespace

void RenderDeviceGL::BindTexture(u32 target, u32 glName) {
    OglStateSet0* ss = state_set(m_data);
    u32* cache = binding_cache(ss, target);
    if (cache[ss->m_activeUnit] == glName) return;
    GLH(glBindTexture, target, glName);
    cache[ss->m_activeUnit] = glName;
}

void RenderDeviceGL::ActiveTexture(u32 unit) {
    OglStateSet0* ss = state_set(m_data);
    if (m_textureStageCount <= unit || ss->m_activeUnit == (u8)unit) return;
    GLH(glActiveTexture, (GLenum)(GL_TEXTURE0 + unit));
    ss->m_activeUnit = (u8)unit;
}

// The stage's cached bindings forgotten (the next SetTexture rebinds); no GL call.
void RenderDeviceGL::RemoveTexture(u32 stage) {
    if (m_textureStageCount <= stage) return;
    OglStateSet0* ss = state_set(m_data);
    ss->m_texture2D[stage] = 0;
    ss->m_textureCube[stage] = 0;
    ss->m_texture3D[stage] = 0;
}

// Binds the texture `*res` (uploaded first if needed; nothing when that fails) to `stage`: its device
// slot gives the GL target and name; the stage's sampler record notes the slot's flag bit.
void RenderDeviceGL::SetTexture(u32 stage, GpuResource* const* res) {
    if (m_textureStageCount <= stage) return;
    if (!res) {
        RemoveTexture(stage);
        return;
    }
    (*res)->EnsureUploaded();  // (the guest's first upload: its result unused)
    GpuResource* r = *res;
    RenderDeviceData* d = m_data;
    if (r && !r->EnsureUploaded()) return;
    const u32 slot = (u32)r->m_handle;
    if (slot > 0x3ff) return;
    OglStateSet0* ss = state_set(m_data);
    const DeviceTextureSlot& ts = d->m_textureSlots[slot];
    const u32* cache = (ts.m_target & 4) ? ss->m_textureCube : (ts.m_target & 0x10) ? ss->m_texture3D : ss->m_texture2D;
    if (cache[stage] != ts.m_glName) {
        ActiveTexture(stage);
        const u32 target = (ts.m_target & 4) ? GL_TEXTURE_CUBE_MAP : (ts.m_target & 0x10) ? GL_TEXTURE_3D : GL_TEXTURE_2D;
        BindTexture(target, ts.m_glName);
    }
    ss->m_samplers[stage].m_textureFlag = ts.m_flags & 1;
}

namespace {

using Fn = live::RunBothFamily::Fn;
Fn fBindTexture(fam(), "_ZN4Aska14RenderDeviceGL11BindTextureEjj");
Fn fActiveTexture(fam(), "_ZN4Aska14RenderDeviceGL13ActiveTextureEj");
Fn fRemoveTexture(fam(), "_ZN4Aska14RenderDeviceGL13RemoveTextureEj");
Fn fSetTexture(fam(), "_ZN4Aska14RenderDeviceGL10SetTextureEjPKPNS_11GpuResourceE");

// The guest original when the thread has no state set yet; gl_run_both over the state set when checked.
template <typename Native>
void run(Cpu& c, Fn& f, Native native, bool checkable = true) {
    auto* dev = reinterpret_cast<RenderDeviceGL*>(c.x(0));
    OglStateSet0* ss = state_set(dev->m_data);
    if (!ss) {
        guest_call(f.orig, {c.x(0), c.x(1), c.x(2)});
        return;
    }
    if (__builtin_expect(fam().due(f), 0)) {
        live::RunBothFamily::Scope scope;
        if (!checkable) {
            fam().result(f, live::RunBothFamily::Outcome::Skipped, "an upload pending");
        } else {
            const u64 x[3] = {c.x(0), c.x(1), c.x(2)};
            std::string why = gl_run_both({{ss, sizeof *ss}}, [&] { guest_call(f.orig, {x[0], x[1], x[2]}); }, native);
            fam().result(f, why.empty() ? live::RunBothFamily::Outcome::Ok : live::RunBothFamily::Outcome::Mismatch, why);
        }
    }
    native();
}

void HostBindTexture(Cpu& c) {
    auto* dev = reinterpret_cast<RenderDeviceGL*>(c.x(0));
    run(c, fBindTexture, [&] { dev->BindTexture((u32)c.x(1), (u32)c.x(2)); });
}
void HostActiveTexture(Cpu& c) {
    auto* dev = reinterpret_cast<RenderDeviceGL*>(c.x(0));
    run(c, fActiveTexture, [&] { dev->ActiveTexture((u32)c.x(1)); });
}
void HostRemoveTexture(Cpu& c) {
    auto* dev = reinterpret_cast<RenderDeviceGL*>(c.x(0));
    run(c, fRemoveTexture, [&] { dev->RemoveTexture((u32)c.x(1)); });
}
void HostSetTexture(Cpu& c) {
    auto* dev = reinterpret_cast<RenderDeviceGL*>(c.x(0));
    auto* res = reinterpret_cast<GpuResource* const*>(c.x(2));
    const bool pending = res && (u32)c.x(1) < dev->m_textureStageCount && (!*res || (*res)->NeedsUpload());
    run(c, fSetTexture, [&] { dev->SetTexture((u32)c.x(1), res); }, !pending);
}

}  // namespace

NATIVE_FUNCTION_ORIG(fBindTexture.sym, HostBindTexture, "render: RenderDeviceGL::BindTexture", &fBindTexture.orig);
NATIVE_FUNCTION_ORIG(fActiveTexture.sym, HostActiveTexture, "render: RenderDeviceGL::ActiveTexture", &fActiveTexture.orig);
NATIVE_FUNCTION_ORIG(fRemoveTexture.sym, HostRemoveTexture, "render: RenderDeviceGL::RemoveTexture", &fRemoveTexture.orig);
NATIVE_FUNCTION_ORIG(fSetTexture.sym, HostSetTexture, "render: RenderDeviceGL::SetTexture", &fSetTexture.orig);

}  // namespace soa::native::render
