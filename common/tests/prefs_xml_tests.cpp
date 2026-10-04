// soa/prefs_xml.h (part of soa_codec_tests): escaping and entities, the element forms, and the
// committed saves (data/saves, port/server-data/test-seed.xml) parsed and written back byte for byte.
#include <cstdio>
#include <string>

#include <soa/prefs_xml.h>

#include "codec_check.h"

namespace {
std::string file_bytes(const std::string& path, bool& ok) {
    std::string s;
    FILE* f = fopen(path.c_str(), "rb");
    ok = f != nullptr;
    if (!f) return s;
    char buf[65536];
    size_t k;
    while ((k = fread(buf, 1, sizeof buf, f)) > 0) s.append(buf, k);
    fclose(f);
    return s;
}
const std::string kHead = "<?xml version='1.0' encoding='utf-8' standalone='yes' ?>\n<map>\n";
}  // namespace

void prefs_xml_tests() {
    using namespace soa::prefs_xml;
    // the writer: Android's bytes
    codec_check(serialize({}) == kHead + "</map>\n", "serialize: no entries");
    codec_check(serialize({{"a", "QQ==\n    "}, {"b", ""}}) ==
                    kHead + "    <string name=\"a\">QQ==&#10;    </string>\n    <string name=\"b\"></string>\n</map>\n",
                "serialize: a value's line break as &#10;, an empty text");
    codec_check(escape("a&b<c>d\"e'f") == "a&amp;b&lt;c&gt;d&quot;e'f", "escape: & < > \" as entities, ' as is");
    codec_check(escape(std::string("\t\r\n\x01\x1f ", 6)) == "&#9;&#13;&#10;&#1;&#31; ", "escape: control characters as &#N;, space as is");
    codec_check(escape("\xe3\x81\x82") == "\xe3\x81\x82", "escape: UTF-8 as is");

    // the reader
    Entries e = parse(kHead + "    <string name=\"k&amp;&lt;&gt;&quot;&apos;&#10;\">v&amp;&lt;&gt;&quot;&apos;&#10;&#x41;&#9;</string>\n</map>\n");
    codec_check(e.size() == 1 && e[0].first == "k&<>\"'\n" && e[0].second == "v&<>\"'\nA\t", "parse: entities and character references");
    e = parse(kHead + "    <string name=\"u\">&#12354;</string>\n</map>\n");
    codec_check(e.size() == 1 && e[0].second == "\xe3\x81\x82", "parse: a character reference above 0x7f as UTF-8");
    e = parse(kHead + "    <string name=\"x\" />\n    <string name=\"y\">    </string>\n    <string name=\"z\"></string>\n</map>\n");
    codec_check(e == Entries{{"x", ""}, {"y", "    "}, {"z", ""}}, "parse: <string/>, a whitespace-only text kept, an empty text");
    e = parse(kHead + "    <int name=\"i\" value=\"1\" />\n    <string name=\"s\">t</string>\n    <boolean name=\"b\" value=\"true\" />\n"
                      "    <set name=\"st\"><string>in a set</string></set>\n</map>\n");
    codec_check(e == Entries{{"s", "t"}}, "parse: only the map's <string> entries");
    e = parse(kHead + "    <string name=\"a\">1</string>\n    <string name=\"b\">2</str");
    codec_check(!e.empty() && e[0] == std::pair<std::string, std::string>{"a", "1"}, "parse: a truncated file gives the entries before the cut");
    codec_check(parse("").empty() && parse("not xml").empty(), "parse: nothing");
    Entries odd = {{"k\t\"<&>", "v\r\n\x01 x"}, {"", ""}, {"\xe3\x81\x82", "    "}};
    codec_check(parse(serialize(odd)) == odd, "parse(serialize) round trip of escapable names and texts");

    // the committed saves: parse + serialize gives the file back
    for (const char* rel : {"port/server-data/test-seed.xml", "data/saves/seed/Game.xml", "data/saves/client/Game.xml", "data/saves/client/Aska.xml"}) {
        bool ok = false;
        std::string in = file_bytes(std::string(SOA_REPO_DIR) + "/" + rel, ok);
        if (!ok) {
#ifdef _WIN32
            fprintf(stderr, "skip  %s: not staged\n", rel);
#else
            codec_check(false, std::string(rel) + " is missing");
#endif
            continue;
        }
        Entries entries = parse(in);
        codec_check(!entries.empty() && serialize(entries) == in, std::string(rel) + ": " + std::to_string(entries.size()) + " entries, written back byte for byte");
    }
}
