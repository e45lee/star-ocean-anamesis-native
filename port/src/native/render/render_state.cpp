// Aska::RenderState::Apply and the RenderDeviceGL / RenderDeviceData render-state setters it replays
// (port/decomp/render/render_context.c, render_device.c, render_device_setters.c): a draw's state
// switch (Apply: 769 guest self samples, its setters ~400 more). With the calling thread's GL state set
// (ASKA_OGL_STATESET0) present, the setters only record the wanted state there (the draw applies it:
// UpdateRenderState); EnableZWrite and the stencil setters call GL at once. Natives: Apply and every
// setter, as members; a setter or Apply called on a thread whose state set doesn't exist yet runs the
// guest original (which creates it; the setters' GL-only paths are for that case).
//
// The tables the setters map engine enums through are the guest's (read in place: the depth / stencil
// function table, the stencil operation table, the blend table, SetCullMode's static iNewMode).
//
// Live check (soa --live-check render): gl_run_both (render_check.h) over the thread's state set.
#include <cstring>

#include "core/cpu.h"
#include "core/loader.h"
#include "hle/gl_host.h"
#include "native/common/guest_std.h"
#include "native/common/native.h"
#include "native/common/native_method.h"
#include "native/render/render_check.h"
#include "native/render/render_layout.h"

namespace soa::native::render {

namespace {

template <typename T>
const T* lib_data(u64 vaddr) {
    return reinterpret_cast<const T*>(main_lib()->base + vaddr);
}
// ZTest::Func / StencilTest::Func -> GL compare function (8), StencilOp::Operation -> GL stencil op (8)
const u32* compare_funcs() { return lib_data<u32>(kCompareFuncTable); }
const u32* stencil_ops() { return lib_data<u32>(kStencilOpTable); }
// AlphaBlend::Operation -> {src, dst, the alpha dst of SeparateAlphaBlendMode 1, equation}
struct BlendEntry {
    u32 src, dst, alphaDst, equation;
};
const BlendEntry* blend_table() { return lib_data<BlendEntry>(kBlendTable); }
const s32* cull_modes() {
    static const s32* t = reinterpret_cast<const s32*>(guest::sym("_ZZN4Aska16RenderDeviceData11SetCullModeENS_4Cull4ModeEE8iNewMode"));
    return t;
}

RenderDeviceGL* render_dev() {
    static RenderDeviceGL** g = reinterpret_cast<RenderDeviceGL**>(guest::sym("_ZN4Aska12g_pRenderDevE"));
    return *g;
}

inline OglStateSet0* state_set(const RenderDeviceData* d) { return d->m_stateCache->StateSet0(); }

constexpr u16 kCapCull = 1 << 0, kCapDepthTest = 1 << 1, kCapStencil = 1 << 2, kCapBlend = 1 << 3;

}  // namespace

// ---- RenderDeviceData ----

void RenderDeviceData::SetCullMode(u32 mode) {
    if (mode > 2) return;
    OglStateSet0* ss = state_set(this);
    const s32 m = cull_modes()[mode];
    u32 front;
    if (m == 2) front = GL_CCW;
    else if (m == 1) front = GL_CW;
    else {
        if (m == 0) ss->m_capFlags &= ~kCapCull;
        return;
    }
    ss->m_frontFace = front;
    ss->m_capFlags |= kCapCull;
    ss->m_cullFace = GL_BACK;
}

void RenderDeviceData::SetAlphaBlendFunction(u32 op, s32 separate) {
    const BlendEntry& b = blend_table()[op];
    u32 alphaSrc, alphaDst;
    if (separate == 2) {
        alphaSrc = GL_ONE;
        alphaDst = GL_ONE;
    } else if (separate == 1) {
        alphaSrc = GL_ZERO;
        alphaDst = b.alphaDst;
    } else {
        alphaSrc = GL_ONE;
        alphaDst = GL_ZERO;
    }
    OglStateSet0* ss = state_set(this);
    ss->m_blend[0] = b.src;
    ss->m_blend[1] = b.dst;
    ss->m_blend[2] = b.equation;
    ss->m_blend[3] = alphaSrc;
    ss->m_blend[4] = alphaDst;
    ss->m_blend[5] = GL_FUNC_ADD;
}

// ---- RenderDeviceGL ----

void RenderDeviceGL::EnableAlphaBlend(bool on) {
    OglStateSet0* ss = state_set(m_data);
    ss->m_capFlags = (u16)((ss->m_capFlags & ~kCapBlend) | (on ? kCapBlend : 0));
}

void RenderDeviceGL::EnableZTest(bool on) {
    OglStateSet0* ss = state_set(m_data);
    ss->m_capFlags = (u16)((ss->m_capFlags & ~kCapDepthTest) | (on ? kCapDepthTest : 0));
}

void RenderDeviceGL::EnableStencil(s32 mode) {
    OglStateSet0* ss = state_set(m_data);
    ss->m_capFlags = (u16)((ss->m_capFlags & ~kCapStencil) | (mode != 0 ? kCapStencil : 0));
}

void RenderDeviceGL::EnableZWrite(bool on) {
    OglStateSet0* ss = state_set(m_data);
    if (ss->m_depthWrite == (u8)on) return;
    ss->m_depthWrite = on;
    GLH(glDepthMask, (GLboolean)on);
}

void RenderDeviceGL::SetZTestFunction(u32 func) {
    if (func > 7) return;
    state_set(m_data)->m_depthFunc = compare_funcs()[func];
}

void RenderDeviceGL::SetCullMode(u32 mode) { m_data->SetCullMode(mode); }

void RenderDeviceGL::SetDepthBias(float a, float b) {
    OglStateSet0* ss = state_set(m_data);
    ss->m_polygonOffset[0] = b;  // glPolygonOffset(b, a) on the guest's no-state-set path
    ss->m_polygonOffset[1] = a;
}

namespace {
void stencil(GLenum face, u32 func, u32 fail, u32 zfail, u32 pass, s32 ref) {
    const u32 f = func < 8 ? compare_funcs()[func] : GL_ALWAYS;
    const u32 sf = fail < 8 ? stencil_ops()[fail] : GL_KEEP;
    const u32 sz = zfail < 8 ? stencil_ops()[zfail] : GL_KEEP;
    const u32 sp = pass < 8 ? stencil_ops()[pass] : GL_KEEP;
    GLH(glStencilFuncSeparate, face, f, ref, 0xffffu);
    GLH(glStencilOpSeparate, face, sf, sz, sp);
}
}  // namespace

void RenderDeviceGL::SetStencilOp(u32 func, u32 fail, u32 zfail, u32 pass, s32 ref) { stencil(GL_FRONT, func, fail, zfail, pass, ref); }
void RenderDeviceGL::SetStencilOpCCW(u32 func, u32 fail, u32 zfail, u32 pass, s32 ref) { stencil(GL_BACK, func, fail, zfail, pass, ref); }

void RenderDeviceGL::SetAlphaBlendFunction(u32 op, s32 separate) { m_data->SetAlphaBlendFunction(op, separate); }

void RenderDeviceGL::SetTextureSamplingFilter(u32 stage, s32 filter) {
    if (stage < 16) state_set(m_data)->m_samplers[stage].m_filter = filter;
}

void RenderDeviceGL::SetTextureSamplingMipmapFilter(u32 stage, s32 filter) {
    if (stage < 16) state_set(m_data)->m_samplers[stage].m_mipFilter = filter;
}

// w is ignored (as in the guest); 10 = leave as is.
void RenderDeviceGL::SetTextureSamplingWrapMode(u32 stage, s32 u, s32 v, s32) {
    if (stage >= 16) return;
    OglSampler& s = state_set(m_data)->m_samplers[stage];
    if (u != 10) s.m_wrapU = u;
    if (v != 10) s.m_wrapV = v;
}

void RenderDeviceGL::SetTextureSamplingMaxAnisotropic(u32 stage, u32 n) {
    if (!m_data->m_anisotropySupported) return;
    if (stage < 16) {
        state_set(m_data)->m_samplers[stage].m_maxAnisotropy = n;
        return;
    }
    GLH(glTexParameterf, (GLenum)GL_TEXTURE_2D, (GLenum)GL_TEXTURE_MAX_ANISOTROPY_EXT, (GLfloat)n);
}

// ---- RenderState::Apply ----

namespace {
inline float f32_at(const u8* p) {
    float f;
    std::memcpy(&f, p, 4);
    return f;
}
}  // namespace

// Replays the recorded commands on `device` (null: g_pRenderDev); unknown opcodes take one byte.
void RenderState::Apply(RenderDeviceGL* device) {
    RenderDeviceGL* dev = device ? device : render_dev();
    if (!m_commands || m_count == 0) return;
    const u8* p = m_commands;
    for (u32 i = 0; i < m_count; i++) {
        const u8 op = p[0];
        switch (op) {
        case kAlphaBlend: dev->EnableAlphaBlend(p[1] != 0); p += 2; break;
        case kAlphaBlendFunction: dev->SetAlphaBlendFunction(p[1], p[2]); p += 3; break;
        case 0xcb: case kAlphaToCoverage: case 0xe0: p += 2; break;
        case 0xcc: p += 3; break;
        case kSamplingFilter: dev->SetTextureSamplingFilter(p[1], p[2]); p += 3; break;
        case kSamplingMipmapFilter: dev->SetTextureSamplingMipmapFilter(p[1], p[2]); p += 3; break;
        case kSamplingWrapMode: dev->SetTextureSamplingWrapMode(p[1], p[2], p[2], 10); p += 3; break;
        case kSamplingWrapModeU: dev->SetTextureSamplingWrapMode(p[1], p[2], 10, 10); p += 3; break;
        case kSamplingWrapModeV: dev->SetTextureSamplingWrapMode(p[1], 10, p[2], 10); p += 3; break;
        case kSamplingMaxAnisotropic: dev->SetTextureSamplingMaxAnisotropic(p[1], p[2]); p += 3; break;
        case kZTest: dev->EnableZTest(p[1] != 0); p += 2; break;
        case kZWrite: dev->EnableZWrite(p[1] != 0); p += 2; break;
        case kZTestFunction: dev->SetZTestFunction(p[1]); p += 2; break;
        case kDepthBias: dev->SetDepthBias(f32_at(p + 1), f32_at(p + 5)); p += 9; break;
        case kCullMode: dev->SetCullMode(p[1]); p += 2; break;
        case kStencil: dev->EnableStencil(p[1]); p += 2; break;
        case kStencilOp:
        case kStencilOpCCW: {
            // the last operand byte swaps the two (0xe3 with 0: SetStencilOp; 0xe4 with 0: the CCW one)
            const bool ccw = (op == kStencilOpCCW) == (p[6] == 0);
            if (ccw) dev->SetStencilOpCCW(p[1], p[2], p[3], p[4], p[5]);
            else dev->SetStencilOp(p[1], p[2], p[3], p[4], p[5]);
            p += 7;
            break;
        }
        default: p += 1; break;
        }
    }
}

// ---- the natives ----

namespace {

using Fn = live::RunBothFamily::Fn;

// A state-set setter / Apply: the guest original when the calling thread has no state set yet; else the
// native, live-checked with gl_run_both over the state set.
template <typename Native>
void run_checked(Cpu& c, Fn& f, RenderDeviceData* data, Native native) {
    OglStateSet0* ss = data ? state_set(data) : nullptr;
    if (!ss) {
        GuestArgs a;
        for (int i = 0; i < 6; i++) a.i(c.x(i));
        a.f(c.s(0)).f(c.s(1));
        guest_call(f.orig, a);
        return;
    }
    if (__builtin_expect(fam().due(f), 0)) {
        live::RunBothFamily::Scope scope;
        const u64 x[6] = {c.x(0), c.x(1), c.x(2), c.x(3), c.x(4), c.x(5)};
        const float s0 = c.s(0), s1 = c.s(1);
        std::string why = gl_run_both({{ss, sizeof *ss}}, [&] {
            GuestArgs a;
            for (u64 v : x) a.i(v);
            a.f(s0).f(s1);
            guest_call(f.orig, a);
        }, native);
        fam().result(f, why.empty() ? live::RunBothFamily::Outcome::Ok : live::RunBothFamily::Outcome::Mismatch, why);
    }
    native();
}

#define DEV_SETTER(id, sym, call)                                                                   \
    Fn f##id(fam(), sym);                                                                           \
    void Host##id(Cpu& c) {                                                                         \
        auto* dev = reinterpret_cast<RenderDeviceGL*>(c.x(0));                                      \
        run_checked(c, f##id, dev->m_data, [&] { call; });                                          \
    }                                                                                               \
    NATIVE_FUNCTION_ORIG(sym, Host##id, "render: RenderDeviceGL::" #id, &f##id.orig)

DEV_SETTER(EnableAlphaBlend, "_ZN4Aska14RenderDeviceGL16EnableAlphaBlendEb", dev->EnableAlphaBlend(c.x(1) & 1));
DEV_SETTER(EnableZTest, "_ZN4Aska14RenderDeviceGL11EnableZTestEb", dev->EnableZTest(c.x(1) & 1));
DEV_SETTER(EnableZWrite, "_ZN4Aska14RenderDeviceGL12EnableZWriteEb", dev->EnableZWrite(c.x(1) & 1));
DEV_SETTER(EnableStencil, "_ZN4Aska14RenderDeviceGL13EnableStencilENS_11StencilMode4ModeE", dev->EnableStencil((s32)c.x(1)));
DEV_SETTER(SetZTestFunction, "_ZN4Aska14RenderDeviceGL16SetZTestFunctionENS_5ZTest4FuncE", dev->SetZTestFunction((u32)c.x(1)));
DEV_SETTER(SetCullMode, "_ZN4Aska14RenderDeviceGL11SetCullModeENS_4Cull4ModeE", dev->SetCullMode((u32)c.x(1)));
DEV_SETTER(SetDepthBias, "_ZN4Aska14RenderDeviceGL12SetDepthBiasEff", dev->SetDepthBias(c.s(0), c.s(1)));
DEV_SETTER(SetAlphaBlendFunction, "_ZN4Aska14RenderDeviceGL21SetAlphaBlendFunctionENS_10AlphaBlend9OperationENS_22SeparateAlphaBlendMode1EE",
           dev->SetAlphaBlendFunction((u32)c.x(1), (s32)c.x(2)));
DEV_SETTER(SetTextureSamplingFilter, "_ZN4Aska14RenderDeviceGL24SetTextureSamplingFilterEjNS_7TexSamp6FilterE",
           dev->SetTextureSamplingFilter((u32)c.x(1), (s32)c.x(2)));
DEV_SETTER(SetTextureSamplingMipmapFilter, "_ZN4Aska14RenderDeviceGL30SetTextureSamplingMipmapFilterEjNS_7TexSamp9MipFilterE",
           dev->SetTextureSamplingMipmapFilter((u32)c.x(1), (s32)c.x(2)));
DEV_SETTER(SetTextureSamplingWrapMode, "_ZN4Aska14RenderDeviceGL26SetTextureSamplingWrapModeEjNS_7TexWrap4ModeES2_S2_",
           dev->SetTextureSamplingWrapMode((u32)c.x(1), (s32)c.x(2), (s32)c.x(3), (s32)c.x(4)));
DEV_SETTER(SetTextureSamplingMaxAnisotropic, "_ZN4Aska14RenderDeviceGL32SetTextureSamplingMaxAnisotropicEjj",
           dev->SetTextureSamplingMaxAnisotropic((u32)c.x(1), (u32)c.x(2)));

// RenderDeviceData's two (RenderDeviceGL's forward to them)
Fn fDataSetCullMode(fam(), "_ZN4Aska16RenderDeviceData11SetCullModeENS_4Cull4ModeE");
void HostDataSetCullMode(Cpu& c) {
    auto* d = reinterpret_cast<RenderDeviceData*>(c.x(0));
    run_checked(c, fDataSetCullMode, d, [&] { d->SetCullMode((u32)c.x(1)); });
}
NATIVE_FUNCTION_ORIG(fDataSetCullMode.sym, HostDataSetCullMode, "render: RenderDeviceData::SetCullMode", &fDataSetCullMode.orig);
Fn fDataSetAlphaBlendFunction(fam(), "_ZN4Aska16RenderDeviceData21SetAlphaBlendFunctionENS_10AlphaBlend9OperationENS_22SeparateAlphaBlendMode1EE");
void HostDataSetAlphaBlendFunction(Cpu& c) {
    auto* d = reinterpret_cast<RenderDeviceData*>(c.x(0));
    run_checked(c, fDataSetAlphaBlendFunction, d, [&] { d->SetAlphaBlendFunction((u32)c.x(1), (s32)c.x(2)); });
}
NATIVE_FUNCTION_ORIG(fDataSetAlphaBlendFunction.sym, HostDataSetAlphaBlendFunction, "render: RenderDeviceData::SetAlphaBlendFunction",
                     &fDataSetAlphaBlendFunction.orig);

// The stencil setters don't touch the state set: GL at once.
Fn fSetStencilOp(fam(), "_ZN4Aska14RenderDeviceGL12SetStencilOpENS_11StencilTest4FuncENS_9StencilOp9OperationES4_S4_i");
Fn fSetStencilOpCCW(fam(), "_ZN4Aska14RenderDeviceGL15SetStencilOpCCWENS_11StencilTest4FuncENS_9StencilOp9OperationES4_S4_i");
template <bool CCW>
void HostStencil(Cpu& c) {
    auto* dev = reinterpret_cast<RenderDeviceGL*>(c.x(0));
    Fn& f = CCW ? fSetStencilOpCCW : fSetStencilOp;
    auto native = [&] {
        if (CCW) dev->SetStencilOpCCW((u32)c.x(1), (u32)c.x(2), (u32)c.x(3), (u32)c.x(4), (s32)c.x(5));
        else dev->SetStencilOp((u32)c.x(1), (u32)c.x(2), (u32)c.x(3), (u32)c.x(4), (s32)c.x(5));
    };
    if (__builtin_expect(fam().due(f), 0)) {
        live::RunBothFamily::Scope scope;
        std::string why = gl_run_both({}, [&] { guest_call(f.orig, {c.x(0), c.x(1), c.x(2), c.x(3), c.x(4), c.x(5)}); }, native);
        fam().result(f, why.empty() ? live::RunBothFamily::Outcome::Ok : live::RunBothFamily::Outcome::Mismatch, why);
    }
    native();
}
NATIVE_FUNCTION_ORIG(fSetStencilOp.sym, HostStencil<false>, "render: RenderDeviceGL::SetStencilOp", &fSetStencilOp.orig);
NATIVE_FUNCTION_ORIG(fSetStencilOpCCW.sym, HostStencil<true>, "render: RenderDeviceGL::SetStencilOpCCW", &fSetStencilOpCCW.orig);

// Apply: the device's state set decides (the original when the thread has none yet).
Fn fApply(fam(), "_ZN4Aska11RenderState5ApplyEPNS_14RenderDeviceGLE");
void HostApply(Cpu& c) {
    auto* rs = reinterpret_cast<RenderState*>(c.x(0));
    auto* dev = reinterpret_cast<RenderDeviceGL*>(c.x(1));
    RenderDeviceGL* d = dev ? dev : render_dev();
    run_checked(c, fApply, d ? d->m_data : nullptr, [&] { rs->Apply(dev); });
}
NATIVE_FUNCTION_ORIG(fApply.sym, HostApply, "render: RenderState::Apply", &fApply.orig);

}  // namespace

}  // namespace soa::native::render
