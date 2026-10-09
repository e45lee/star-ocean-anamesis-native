// RenderDeviceData::UpdateShaderProgram (port/decomp/render/render_device.c, with the disassembly: Ghidra
// returns early where the guest goes on to the uniforms): before every draw, the program of the current
// vertex / pixel shader pair. The current one again: glUseProgram only if the thread's state set 1 says
// another is in use. Another pair: the linked programs' set (a THashSet probed with the SpookyHash of the
// two keys), then the program in use and its uniforms (SetShaderProgramUniform, guest).
//
// The native takes the paths that only find: a pair with no program yet, or one not linked yet (shader
// creation, CompileShaderProgram, the program cache written back), or a thread without its state set 1
// run the guest original, which recomputes everything the native would have written.
//
// Live check (soa --live-check render): gl_run_both over the thread's state set 1 and the device's
// program fields, SetShaderProgramUniform recorded as a marker (t_mark_callees).
#include <cstring>

#include "soaruntime/core/cpu.h"
#include "soaruntime/core/hle.h"
#include "soaruntime/hle/gl_host.h"
#include "native/common/guest_std.h"
#include "native/common/native.h"
#include "native/hash/hash_layout.h"
#include "native/render/render_check.h"
#include "native/render/render_layout.h"

namespace soa::native::render {

OglStateSet1* StateCacheThreadSafe::StateSet1() const {
    if (__atomic_load_n(&m_keySet1Created, __ATOMIC_ACQUIRE) == 0) return nullptr;
    return reinterpret_cast<OglStateSet1*>(guest_getspecific(m_keySet1));
}

OglStateSet1* RenderDeviceData::GetThreadOglState1() { return m_stateCache->StateSet1(); }

// glUseProgram unless the thread's state set 1 has it in use already (no state set: always).
bool RenderDeviceData::UseProgram(u32 program) {
    OglStateSet1* s1 = GetThreadOglState1();
    if (!s1) {
        GLH(glUseProgram, program);
        return false;
    }
    s1->m_programWant = program;
    if (s1->m_programGL != program) {
        GLH(glUseProgram, program);
        s1->m_programGL = s1->m_programWant;
    }
    return true;
}

namespace {

// What UpdateShaderProgram will do for the current shader pair, decided without writing anything.
struct ProgramLookup {
    u64 key[2];
    u64 hash = 0;
    ShaderProgramValue* program = nullptr;  // the one to use (null: the guest's path)
    bool current = false;                   // the device's current program
};

ProgramLookup lookup(const RenderDeviceData* d) {
    ProgramLookup r;
    const PixelShader* ps = d->m_pixelShader ? d->m_pixelShader : d->m_defaultPixelShader;
    r.key[0] = d->m_vertexShader->m_key;
    r.key[1] = ps->m_key;
    if (!d->m_stateCache->StateSet1()) return r;  // the guest creates it
    ShaderProgramValue* cur = d->m_program;
    if (cur && cur->m_vsKey == r.key[0] && cur->m_psKey == r.key[1]) {
        r.program = cur;
        r.current = true;
        return r;
    }
    u64 h2 = 0;
    hash::SpookyHashV2::Hash128(r.key, 16, &r.hash, &h2);
    const auto& b = d->m_programSet.table.m_buckets;
    for (u64 i = 0; i < b.m_count; i++) {
        const auto& e = b.m_data[(r.hash + i) % b.m_count];
        if (e.m_state == 0) break;
        if (e.m_state != 1) continue;
        if (e.m_value->m_vsKey == r.key[0] && e.m_value->m_psKey == r.key[1]) {
            if (e.m_value->m_glProgram != 0) r.program = e.m_value;  // (not linked yet: the guest links it)
            break;
        }
    }
    return r;
}

}  // namespace

bool RenderDeviceData::ProgramReady() const { return lookup(this).program != nullptr; }

// The native part (ProgramReady()); the HostFn runs the guest original otherwise.
void RenderDeviceData::UpdateShaderProgram() {
    const ProgramLookup r = lookup(this);
    m_programKey[0] = r.key[0];
    m_programKey[1] = r.key[1];
    if (r.current) {
        UseProgram(m_program->m_glProgram);
        return;
    }
    m_programHash = r.hash;
    m_program = r.program;
    UseProgram(r.program->m_glProgram);
    call_set_shader_program_uniform(this, m_program);
}

namespace {

live::RunBothFamily::Fn fUpdateShaderProgram(fam(), "_ZN4Aska16RenderDeviceData19UpdateShaderProgramEv");

void HostUpdateShaderProgram(Cpu& c) {
    auto* d = reinterpret_cast<RenderDeviceData*>(c.x(0));
    if (mark_callee("UpdateShaderProgram", {(u64)d})) return;  // (inside a draw's check)
    if (!d->ProgramReady()) {
        guest_call(fUpdateShaderProgram.orig, {(u64)d});
        return;
    }
    if (__builtin_expect(fam().due(fUpdateShaderProgram), 0)) {
        live::RunBothFamily::Scope scope;
        OglStateSet1* s1 = d->GetThreadOglState1();
        t_mark_callees = true;
        std::string why = gl_run_both({{s1, sizeof *s1}, {&d->m_programHash, 0x18}, {&d->m_program, sizeof d->m_program}},
                                      [&] { guest_call(fUpdateShaderProgram.orig, {(u64)d}); }, [&] { d->UpdateShaderProgram(); });
        t_mark_callees = false;
        fam().result(fUpdateShaderProgram, why.empty() ? live::RunBothFamily::Outcome::Ok : live::RunBothFamily::Outcome::Mismatch, why);
    }
    d->UpdateShaderProgram();
}

}  // namespace

void update_shader_program_unchecked(RenderDeviceData* d) {
    if (!d->ProgramReady()) {
        guest_call(fUpdateShaderProgram.orig, {(u64)d});
        return;
    }
    d->UpdateShaderProgram();
}

NATIVE_FUNCTION_ORIG(fUpdateShaderProgram.sym, HostUpdateShaderProgram, "render: RenderDeviceData::UpdateShaderProgram", &fUpdateShaderProgram.orig);

}  // namespace soa::native::render
