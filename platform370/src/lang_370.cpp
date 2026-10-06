// The client's language (platform370::install_language; Config::lang, Config::voice_lang):
// docs/english.md section 6, docs/PLAN-english.md B1 and B7, docs/client-changes.md "English mode".
//
// B1, --lang en: the 3.7.0 client has a language switch it never uses. CLanguage (12 bytes: Default
// +0, Current +4, Voice +8, a TSingleton) is built once, by CGame::OnInitialize, as CLanguage(0x100)
// (ELF 0x114256c: orr w1, wzr, #0x100), "no language" in all three fields; nothing sets Current
// later (CLanguage::Current(tLanguage) has no caller). With Current = 1 (en)
// CGameResourceManager::FileExistLanguage / RegisteredFileLanguage / IsFileExistDownloadFolder try
// name-en.ext before name.ext for every file the client loads (the master, the story, layouts,
// images, the font), the Japanese file being the fallback per file (english.md 6.3). The hook runs
// the constructor (through a trampoline) and then sets Current to 1; Default stays 0x100 and Voice
// stays as constructed (CUIUtility::EffectiveSetting sets it from BAS:VoiceLanguage afterwards).
// With --lang ja nothing is hooked: the client is exactly as shipped.
//
// B7, --voice-lang ja (default): BAS:VoiceLanguage = 0 (u32) in the phone's Game.xml before the
// client starts, as the sessions set BAS:DownloadEpisodeFlag (control/soadrive/targets.py
// session_client_save). CUIUtility::EffectiveSetting (the last call of CGame::OnInitialize) runs
// SetVoiceLanguage(GetVoiceLanguage()), so CLanguage::Voice is 0, and FileExistLanguage resolves a
// Voice_*.spk through PostfixLanguageCodeFilepath(name, 0): the bare (Japanese) name, with no -en
// probe (english.md 6.1, 6.4). With 0 or 0x100 a file without '-' resolves to the same name, so this
// changes nothing for --lang ja. --voice-lang keep leaves the save's value.
//
// Installed after load_library and before any guest code runs, as patch_370.cpp's patches.
#include <cstring>
#include <string>
#include <vector>

#include <soa/kvs.h>

#include "android/prefs.h"
#include "core/cpu.h"
#include "core/loader.h"
#include "core/log.h"
#include "internal.h"
#include "platform370/platform370.h"

namespace soa::platform370 {
namespace {

std::string g_lang = "ja", g_voice_lang = "ja";
std::vector<std::string> g_hooks;

// CLanguage::tLanguage: 0 ja, 1 en, 0x100 "" (no postfix), 0x101 none (strip a postfix).
constexpr u32 kLangEn = 1;

// ---- B1: CLanguage::CLanguage(tLanguage) ----------------------------------------------------------
// C1 and C2 are one function (ELF 0x13b4b18). Its first two instructions in 3.7.0 (stp x21, x20,
// [sp, #-0x20]!; stp x19, x30, [sp, #0x10]): the trampoline relocates them, and another library
// isn't hooked.
constexpr const char* kCLanguageCtor = "_ZN9CLanguageC2ENS_9tLanguageE";
constexpr u32 kCtorEntry0 = 0xa9be53f5, kCtorEntry1 = 0xa9017bf3;
u64 g_ctor = 0, g_base = 0;

void h_clanguage_ctor(Cpu& c) {
    u64 self = c.x(0), lang = c.x(1);
    u64 ints[2] = {self, lang};
    guest_call_raw(g_ctor, ints, 2, nullptr, 0, 0);
    u32* f = (u32*)self;
    f[1] = kLangEn;
    LOGI("p370", "lang: CLanguage(%#x) built (from %#llx); Current set to 1 (en): Default %#x, Current %#x, Voice %#x",
         (unsigned)lang, (unsigned long long)(c.lr() - g_base), f[0], f[1], f[2]);
}

bool entry_is(u64 a, u32 w0, u32 w1) { return a && ((const u32*)a)[0] == w0 && ((const u32*)a)[1] == w1; }

void hook_clanguage(LoadedLib& lib) {
    u64 a = lib.sym(kCLanguageCtor);
    if (!entry_is(a, kCtorEntry0, kCtorEntry1)) {
        LOGW("p370", "lang: CLanguage::CLanguage isn't 3.7.0's; --lang en has no effect on the files");
        return;
    }
    g_ctor = make_original_trampoline(a);
    if (!g_ctor) fatal("platform370: CLanguage::CLanguage's prologue can't be relocated");
    hook_guest_function(a, "CLanguage::CLanguage [platform370 --lang en: Current = en]", h_clanguage_ctor);
    g_hooks.push_back(kCLanguageCtor);
    LOGI("p370", "lang: CLanguage::CLanguage hooked at %#llx: Current = en (name-en.ext before name.ext)",
         (unsigned long long)(a - lib.base));
}

// ---- B7: BAS:VoiceLanguage in Game.xml -------------------------------------------------------------
constexpr const char* kVoiceKey = "BAS:VoiceLanguage";

void write_voice_language() {
    // Game.xml through the runtime's SharedPreferences (android/prefs.h): the file the guest's
    // Aska::LocalKVS reads through jb.Aska.SharedPreferencesBridge, entry names and values in the
    // game's encoding (soa/kvs.h). Nothing has read it yet, so its cache starts from the file.
    SharedPrefs& prefs = SharedPrefs::get();
    const std::string name = kvs::encode_name(kVoiceKey);
    std::vector<unsigned char> raw = prefs.get_bytes("Game", name);
    std::string old = kvs::crypt(std::string_view((const char*)raw.data(), raw.size()));
    u32 was = 0;
    if (old.size() == 4) std::memcpy(&was, old.data(), 4);
    if (old.size() == 4 && was == 0) {
        LOGI("p370", "voice-lang ja: %s is 0 already (Japanese voices)", kVoiceKey);
        return;
    }
    const u32 zero = 0;
    std::string v = kvs::crypt(std::string_view((const char*)&zero, 4));
    prefs.set_bytes("Game", name, std::vector<unsigned char>(v.begin(), v.end()));
    if (old.empty()) LOGI("p370", "voice-lang ja: %s = 0 written to Game.xml (was not set): Japanese voices, no -en probe", kVoiceKey);
    else LOGI("p370", "voice-lang ja: %s %u -> 0 in Game.xml: Japanese voices, no -en probe", kVoiceKey, (unsigned)was);
}

}  // namespace

void detail::set_language(const std::string& lang, const std::string& voice_lang) { g_lang = lang, g_voice_lang = voice_lang; }

const std::string& language() { return g_lang; }

const std::vector<std::string>& language_hooks() { return g_hooks; }

void install_language(LoadedLib& lib) {
    g_base = lib.base;
    if (g_voice_lang == "ja") write_voice_language();
    if (g_lang != "en") return;
    hook_clanguage(lib);
}

}  // namespace soa::platform370
