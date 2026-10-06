#pragma once
// The English text table of --english (docs/server-rules.md#english): one generated, committed
// file, data/english/master-en.tsv (tools/english_text.py build), read-only. Port code, not guest
// behaviour. Two users, one matching rule (match() below):
//   - the CDN's -en master (cdn/served_master.cpp make_english_master): the served master with the
//     English in its `ja_` rows' text_value, and new rows for ids the master lacks;
//   - the server's own texts under --english (ext::display_text: present lines, the notice page's
//     names; the gacha rate headings).
// The server's rules keep reading the Japanese master (kDefaultEventKeywords matches Japanese
// text): only what the player sees is looked up here.
//
// The file: UTF-8, a header line "message_id\tja_sha1\ten\tsource", then one row per message_id,
// sorted. `en` is the text_value to serve as is (a line break is the two characters "\n", as in
// the master). `ja_sha1` is the SHA-1 (hex) of the Japanese text_value the English translates;
// empty for a message_id the Japanese master doesn't have (a new id, e.g. port_en_*). `source`
// (official, memory, template, machine, human, reviewed) is informational.
#include <map>
#include <memory>
#include <string>

#include "soaserver/english_table.h"

namespace soa::server::english {

// Parses the table file into `out`; false (with *err) on an unreadable file, a wrong header or a
// row without four fields.
bool load(const std::string& path, Table& out, std::string* err);

// Our own rows: --english-text, else data/english/master-en.tsv (machine / human / reviewed and the
// client strings, finished by tools/english_text.py); "" when none exists.
std::string table_path();

// The English story tables' directory (TS_xxxx.tsv files, the same form; docs/server-rules.md#english-story):
// story-en beside an explicit --english-text, else data/english/story-en (find_repo_file); "" when
// none exists.
std::string story_dir();

// Publishes the full table the CDN built (english_derive.h: the derived layer with our rows), which
// table() answers without an explicit --english-text.
void set_served_table(std::shared_ptr<const Table> t);

// The table in force under --english: the one the CDN published (set_served_table), else
// --english-text's file alone (loaded once per path: a replay, a test); nullptr without --english
// or without a table (an unreadable file is warned once).
std::shared_ptr<const Table> table();

// What the table says for a row whose Japanese text_value is `ja` (the matching rule, d).
enum class Match {
    kNone,      // no English for the id
    kReplace,   // English for exactly this Japanese text (sha1(ja) == ja_sha1)
    kStale,     // English for another Japanese text: the Japanese stays
    kNewId,     // English for an id the Japanese master doesn't have (ja_sha1 empty)
};
Match match(const Table& t, const std::string& message_id, const std::string& ja, const Entry** entry);

// The text the player sees for `message_id` whose Japanese is `ja`: the English under --english
// when the table has it for this Japanese (kReplace), or for a new id when `ja` is empty (kNewId);
// else `ja`.
std::string display(const std::string& message_id, const std::string& ja);

// True when the printf conversions of `a` and `b` are the same, in the same order ("%%" is a
// literal): a template the server fills itself (the gacha rate headings) only takes an English
// one with the Japanese one's arguments.
bool same_specifiers(const std::string& a, const std::string& b);

}  // namespace soa::server::english
