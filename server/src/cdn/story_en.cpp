// The English story files of --english (soaserver/cdn.h make_english_story): a 3.7.0
// Scenario/TS_xxxx.msgp with the English story table's text, served as Scenario/TS_xxxx-en.msgp.
// Our code; rules and labels in docs/server-rules.md#english-story.
#include "cdn/files.h"
#include "core/log.h"
#include "master/english_text.h"
#include "soaserver/adld.h"
#include "soaserver/cdn.h"
#include "soaserver/msgpack.h"

namespace soa::server::cdn {

namespace {

// (b) the story files' text: kana or kanji is a Japanese line (tools/english_core.py has_kana:
// U+3040..U+30FF, U+4E00..U+9FFF)
bool has_japanese(const std::string& s) {
    for (size_t i = 0; i < s.size();) {
        unsigned char c = (unsigned char)s[i];
        uint32_t cp = c;
        size_t n = 1;
        if (c >= 0xf0 && i + 3 < s.size()) cp = ((c & 7u) << 18) | ((s[i + 1] & 0x3fu) << 12) | ((s[i + 2] & 0x3fu) << 6) | (s[i + 3] & 0x3fu), n = 4;
        else if (c >= 0xe0 && i + 2 < s.size()) cp = ((c & 15u) << 12) | ((s[i + 1] & 0x3fu) << 6) | (s[i + 2] & 0x3fu), n = 3;
        else if (c >= 0xc0 && i + 1 < s.size()) cp = ((c & 31u) << 6) | (s[i + 1] & 0x3fu), n = 2;
        if ((cp >= 0x3040 && cp <= 0x30ff) || (cp >= 0x4e00 && cp <= 0x9fff)) return true;
        i += n;
    }
    return false;
}

// (b) the tags CEventScenario::ParseMessage (ELF 0x142fcc8) knows: <player>, <fontcolor=..>,
// <fontsize=..>, </font>, spaces inside a tag ignored; an unknown tag most likely crashes it and a
// tag without '>' asserts (docs/english.md 1.2, 3.3). (d) English with any other tag isn't served.
bool story_tags_ok(const std::string& s) {
    for (size_t i = s.find('<'); i != std::string::npos; i = s.find('<', i + 1)) {
        size_t e = s.find('>', i);
        if (e == std::string::npos) return false;
        std::string tag;
        for (size_t k = i + 1; k < e; k++)
            if (s[k] != ' ') tag += s[k];
        if (tag != "player" && tag != "/font" && tag.rfind("fontcolor=", 0) != 0 && tag.rfind("fontsize=", 0) != 0) return false;
    }
    return true;
}

// "\n" (two characters) -> a newline: the story files hold real newlines (docs/english.md 1.2).
std::string unescape_newlines(const std::string& s) {
    std::string o;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '\\' && i + 1 < s.size() && s[i + 1] == 'n') {
            o += '\n';
            i++;
        } else o += s[i];
    }
    return o;
}
std::string escape_newlines(const std::string& s) {
    std::string o;
    for (char c : s) o += c == '\n' ? std::string("\\n") : std::string(1, c);
    return o;
}

}  // namespace

std::string english_name(const std::string& name) {
    size_t dot = name.rfind('.'), slash = name.rfind('/');
    if (dot == std::string::npos || (slash != std::string::npos && dot < slash)) return name + "-en";
    return name.substr(0, dot) + "-en" + name.substr(dot);
}

std::vector<uint8_t> make_english_story(const std::string& name, const std::vector<uint8_t>& file, const std::string& table,
                                        EnglishStoryStats* stats) {
    if (stats) *stats = EnglishStoryStats{};
    english::Table t;
    std::string why;
    if (!english::load(table, t, &why)) {
        LOGW("cdn", "english story %s: %s", name.c_str(), why.c_str());
        return {};
    }
    return make_english_story(name, file, t, stats);
}

std::vector<uint8_t> make_english_story(const std::string& name, const std::vector<uint8_t>& file, const english::Table& t,
                                        EnglishStoryStats* stats) {
    EnglishStoryStats st;
    if (stats) *stats = st;
    std::vector<uint8_t> plain = adld::decrypt(name, file);
    Value v = mp_decode(plain);
    Value* rows = files::map_find(v, "master_text");
    if (!rows || rows->type != Value::Arr) {
        LOGW("cdn", "english story %s: no master_text rows", name.c_str());
        return {};
    }
    for (Value& row : rows->arr) {
        st.rows++;
        Value* mid = files::map_find(row, "message_id");
        Value* text = files::map_find(row, "text_value");
        if (!mid || mid->type != Value::Str || !text || text->type != Value::Str) continue;
        bool japanese = has_japanese(text->s);
        if (japanese) st.japanese++;
        // (d) the English of exactly this Japanese (english_text.h's rule), its sha1 over the
        // story file's text with real newlines or with "\n" (the master's encoding)
        const english::Entry* e = nullptr;
        bool match = english::match(t, mid->s, text->s, &e) == english::Match::kReplace ||
                     english::match(t, mid->s, escape_newlines(text->s), &e) == english::Match::kReplace;
        if (match && story_tags_ok(e->en)) {
            text->s = unescape_newlines(e->en);
            st.english++;
        } else if (japanese) st.missing++;
    }
    if (stats) *stats = st;
    // (d) PLAN-english Q12: a story file's English version only when every Japanese line has English
    if (st.missing || !st.english) return {};
    std::vector<uint8_t> out = mp_encode(v);
    return adld::encrypt(english_name(name), out, adld::kXor);
}

}  // namespace soa::server::cdn
