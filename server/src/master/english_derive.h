#pragma once
// The derived layer of the English text (docs/server-rules.md#english-derive): Global's official
// English by message_id (the five filters), Global's token rows rewritten (E3), and the exact and
// template translation memory, for the master and the story, computed from Global's master
// (data/basmaster-gl.sqlite3), the JP 3.7.0 master, the game's font and the story files: what
// tools/english_core.py / tools/english_text.py `build` derive, rule for rule, so that a packaged
// server (no Python) builds the same tables. Our own rows (machine / human / reviewed, already
// finished and checked by tools/english_text.py) are merged on top with the same precedence:
//   human / reviewed > official (by id, then E3) > memory (exact) / template > machine > Japanese.
// "By id" and the exact memory also take a Japanese text that differs only in white space
// (english.md 7.9: id-ws, memory-ws).
// Port code, not guest behaviour; every rule is (a) Global's text or (d) the derivation's choice.
#include <cstdint>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "master/english_text.h"

namespace soa::server::english {

// The font's advances (Font/etc2/font.fpk's fontData.bin: id's low 16 bits -> xadvance).
struct Advances {
    std::unordered_map<uint32_t, int> adv;
    bool has(uint32_t cp) const { return adv.count(cp) != 0; }
};
// From the font file's decrypted bytes (ADLD removed). False and *err when it can't be read.
bool load_advances(const std::vector<uint8_t>& fpk_plain, Advances& out, std::string* err);

// (d) px per story line the English is re-broken to: tools/english_text.py STORY_BUDGET (the same
// value; tests/test_english_derive.py checks).
constexpr int kStoryBudget = 480;

// One story file's lines, in file order: (message_id, text_value with real newlines).
struct StoryFile {
    std::string stem;  // "TS_1010"
    std::vector<std::pair<std::string, std::string>> lines;
};

struct DeriveInput {
    std::string master;  // the JP 3.7.0 master DB (the server's)
    std::string global;  // Global's master DB (data/basmaster-gl.sqlite3)
    Advances font;
    std::vector<StoryFile> story;  // sorted by name; empty: no story part
    int story_budget = kStoryBudget;
};

// The derived candidates that pass their checks.
struct Derived {
    // message_id -> (sha1 of the JP text_value, the served English in the master encoding, source
    // official | memory | template); only rows whose candidate passes.
    Table master;
    std::map<std::string, std::string> jp_sha1;  // every JP message_id -> sha1 of its text_value
    // the story: message_id -> (sha1 of the line, English with "\n" escaped, "official")
    Table story;
    std::map<std::string, std::string> story_sha1;  // every story line -> sha1 (the last file's, as Python)
    std::vector<StoryFile> files;
    size_t official = 0, e3 = 0, memory = 0, templ = 0, failing = 0, story_official = 0, story_failing = 0;
};
bool derive(const DeriveInput& in, Derived& out, std::string* err);

// The full master table (english_text.py's master-en.tsv): per JP message_id our human/reviewed row
// (when its ja_sha1 is the JP text's), else the derived row, else our machine row; then our rows of
// new message_ids (an empty ja_sha1).
Table merge_master(const Derived& d, const Table& ours);
// The story tables per file stem (english_text.py's story-en/TS_x.tsv): the same precedence per line.
std::map<std::string, Table> merge_story(const Derived& d, const Table& ours);
// A table in english_text.py's form (header, rows sorted by message_id).
std::string table_text(const Table& t);
// The lines of a story file (its plaintext msgpack) as StoryFile lines.
bool story_lines(const std::vector<uint8_t>& plain, StoryFile& out);

// ---- the text rules (exposed for the tests) ------------------------------------------------------
std::string nfkc(const std::string& s);
std::string fold(const Advances& f, const std::string& s);
std::string rebreak(const Advances& f, const std::string& s, int budget, bool player_px);
std::string fix_percent(const std::string& en, const std::string& ja);
// The white-space-insensitive key of the rules id-ws and memory-ws (english_core.ws_key; a
// master-encoded "\n" counts as a line break): the text without tab, newline, space, U+00A0, U+3000.
std::string ws_key(const std::string& s);
// E3: Global's tokens rewritten; false when the row can't be (why in *why).
bool rewrite_tokens(const std::string& en, const std::string& ja, std::string* out, std::string* why);

}  // namespace soa::server::english
