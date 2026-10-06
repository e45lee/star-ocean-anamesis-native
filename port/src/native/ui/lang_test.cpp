// platform370's language settings (platform370/src/lang_370.cpp; test-only, nothing native):
// docs/PLAN-english.md B1 and B7.
//
// platform370/lang: the client's CLanguage singleton as the booted client has it, against the
// command line: Default 0x100; Current 1 (en) with --lang en, else 0x100 (as shipped); Voice 0 with
// --voice-lang ja (the default: BAS:VoiceLanguage = 0 written before the client started, read back by
// CUIUtility::EffectiveSetting). With --lang ja platform370 hooked nothing (language_hooks() empty,
// no "[platform370 --lang" hook among hooked_functions()); with --lang en the CLanguage hook is there.
// The file names the client tries: CLanguage::PostfixLanguageCodeFilepath(path, Current()) gives
// Font/etc2/font-en.fpk with --lang en and the name unchanged with --lang ja, and
// PostfixLanguageCodeFilepath(Sound/Voice_x.spk, Voice()) the bare name (no -en voice probe).
// Passes in the plain --selftest run (--lang ja) and in `--selftest platform370/lang --lang en`
// (tests/tiers.json "selftest-lang-en").
#include <cstring>
#include <string>

#include "core/cpu.h"
#include "native/common/test.h"
#include "platform370/platform370.h"

namespace soa {
namespace {

constexpr const char* kPostfix = "_ZN9CLanguage27PostfixLanguageCodeFilepathERN9Framework13TStaticStringILm256EEENS_9tLanguageEb";

std::string postfixed(TestContext& t, const char* name, u32 lang) {
    char path[256] = {};
    std::strncpy(path, name, sizeof path - 1);
    t.call(kPostfix, {(u64)path, lang, 0});
    return path;
}

NATIVE_TEST("platform370/lang") {
    const bool en = platform370::language() == "en";
    u64 inst = *(const u64*)t.sym("_ZN9Framework10TSingletonI9CLanguageE11m_pInstanceE");
    if (!inst) {
        t.fail("no CLanguage instance (CGame::OnInitialize didn't run?)");
        return;
    }
    const u32* f = (const u32*)inst;
    const u32 want_current = en ? 1 : 0x100;
    if (f[0] != 0x100) t.fail("CLanguage Default %#x, want 0x100", f[0]);
    if (f[1] != want_current) t.fail("CLanguage Current %#x, want %#x (--lang %s)", f[1], want_current, platform370::language().c_str());
    // --voice-lang ja (the selftest's default): BAS:VoiceLanguage 0, so Voice 0
    if (f[2] != 0) t.fail("CLanguage Voice %#x, want 0 (--voice-lang ja)", f[2]);

    bool hooked = false;
    for (const HookedFunction& h : hooked_functions())
        if (h.name && std::strstr(h.name, "[platform370 --lang")) hooked = true;
    if (en != hooked) t.fail("platform370's language hooks %s with --lang %s", hooked ? "installed" : "missing", platform370::language().c_str());
    if (en != !platform370::language_hooks().empty()) t.fail("language_hooks() has %zu entries", platform370::language_hooks().size());

    std::string font = postfixed(t, "Font/etc2/font.fpk", f[1]);
    std::string want_font = en ? "Font/etc2/font-en.fpk" : "Font/etc2/font.fpk";
    if (font != want_font) t.fail("PostfixLanguageCodeFilepath(font, Current) = %s, want %s", font.c_str(), want_font.c_str());
    std::string voice = postfixed(t, "Sound/Voice_TS_1010.spk", f[2]);
    if (voice != "Sound/Voice_TS_1010.spk") t.fail("PostfixLanguageCodeFilepath(voice, Voice) = %s, want the bare name", voice.c_str());
}

}  // namespace
}  // namespace soa
