// Unit tests of the layout labels (docs/english.md 7.14; --selftest "english-art/labels"): the
// label walk over a msgpack node tree, the ISF repack, and build() on a synthetic download (no game
// files). Every test gives the same bytes on every run.
#include <unistd.h>

#include <cstring>
#include <string>

#include <soa/aska_image.h>
#include <soa/paths.h>

#include "cdn/files.h"
#include "english_art/art.h"
#include "soa/adld.h"
#include "soaserver/english_art.h"
#include "soaserver/native_test.h"

namespace soa::server::english_art {
namespace {

// msgpack by hand: the exact headers are what the tests check
void str(Bytes& b, const std::string& s, int forced = 0) {
    size_t n = s.size();
    if (forced == 0xd9 || (!forced && n >= 32 && n < 256)) b.insert(b.end(), {0xd9, (uint8_t)n});
    else if (forced == 0xda || (!forced && n >= 256)) b.insert(b.end(), {0xda, (uint8_t)(n >> 8), (uint8_t)n});
    else b.push_back((uint8_t)(0xa0 | n));
    b.insert(b.end(), s.begin(), s.end());
}
void map(Bytes& b, int n) { b.push_back((uint8_t)(0x80 | n)); }
void arr(Bytes& b, int n) { b.push_back((uint8_t)(0x90 | n)); }

// A node tree: {"Name": "root", 7: <bin 3>, "Scale": float32, "Children": [ {"LabelText": ja,
// "FontSize": 24, "x": <ext>}, {"ButtonText": ja2, "Tag": -5}, {"Other": ja} ], "LabelText": <int>}
// with `ja` (the text a label of `table` replaces) also as the value of a key that isn't a label's.
Bytes tree(const std::string& label, const std::string& button, int label_hdr = 0) {
    Bytes b;
    map(b, 5);
    str(b, "Name"), str(b, "root");
    b.push_back(7), b.insert(b.end(), {0xc4, 3, 1, 2, 3});                          // int key, bin 8
    str(b, "Scale"), b.insert(b.end(), {0xca, 0x3f, 0x80, 0x00, 0x00});             // float32 1.0
    str(b, "Children"), arr(b, 3);
    map(b, 3), str(b, "LabelText"), str(b, label, label_hdr), str(b, "FontSize"), b.push_back(24);
    str(b, "x"), b.insert(b.end(), {0xd5, 0x01, 0xaa, 0xbb});                       // fixext 2
    map(b, 2), str(b, "ButtonText"), str(b, button), str(b, "Tag"), b.push_back(0xfb);  // -5
    map(b, 1), str(b, "Other"), str(b, "閉じる");
    str(b, "LabelText"), b.insert(b.end(), {0xcd, 0x01, 0x00});                     // a non-str label value: kept
    return b;
}

// An ISF image laid out as the 3.7.0 scenes are (english.md 7.14): header, entries, names, then the
// payloads at 32-byte boundaries padded with 0xee, each entry's sum its padded payload's.
Bytes isf(const std::vector<std::pair<std::string, Bytes>>& members) {
    Bytes d(16 + 16 * members.size(), 0);
    memcpy(d.data(), "\0ISF", 4);
    d[4] = 4, d[8] = (uint8_t)members.size();
    std::vector<size_t> name_at;
    for (auto& [name, p] : members) {
        name_at.push_back(d.size());
        d.insert(d.end(), name.begin(), name.end());
        d.push_back(0);
    }
    d.resize((d.size() + 31) / 32 * 32, 0);
    for (size_t i = 0; i < members.size(); i++) {
        size_t off = d.size();
        d.insert(d.end(), members[i].second.begin(), members[i].second.end());
        auto put = [&](size_t at, uint32_t v) {
            for (int k = 0; k < 4; k++) d[at + k] = (uint8_t)(v >> (8 * k));
        };
        put(16 + i * 16, (uint32_t)name_at[i]);
        put(16 + i * 16 + 4, (uint32_t)off);
        put(16 + i * 16 + 8, (uint32_t)members[i].second.size());
        d.resize((d.size() + 31) / 32 * 32, 0xee);
        aska::IsfEntry e;
        e.index = i, e.offset = (uint32_t)off, e.size = (uint32_t)members[i].second.size();
        aska::isf_update_sum(d, e);
    }
    return d;
}

const LabelTable kTable = {{"閉じる", "Close"}, {"戻る", "Back"}, {"スキップしますか？\nはい", "Skip this?\nYes"}};

LabelFn lookup(const LabelTable& t) {
    return [&t](const std::string& s) -> const std::string* {
        auto it = t.find(s);
        return it == t.end() ? nullptr : &it->second;
    };
}

}  // namespace

NATIVE_TEST("english-art/labels-walk") {
    Bytes in = tree("閉じる", "戻る"), out;
    size_t n = 99;
    std::string err;
    auto keep = [](const std::string&) -> const std::string* { return nullptr; };
    t.expect_eq(rewrite_labels(in, keep, &out, &n, &err) && out == in && n == 0, true, "nothing replaced: the same bytes");
    // LabelText and ButtonText replaced; the same Japanese under "Other" and the int LabelText kept
    t.expect_eq(rewrite_labels(in, lookup(kTable), &out, &n, &err), true, "the walk");
    t.expect_eq(out, tree("Close", "Back"), "the labels in English, everything else as it was");
    t.expect_eq(n, (size_t)2, "two labels replaced");
    // a str8 Japanese label (the encoder's header) that becomes short gets a fixstr; a long one str8
    Bytes in8 = tree("閉じる", "戻る", 0xd9);
    t.expect_eq(rewrite_labels(in8, lookup(kTable), &out, &n, &err) && out == tree("Close", "Back"), true, "the smallest header");
    std::string long_en(40, 'x');
    LabelTable lt = {{"閉じる", long_en}};
    t.expect_eq(rewrite_labels(in, lookup(lt), &out, &n, &err) && out == tree(long_en, "戻る"), true, "a str8 for 40 bytes");
    // scan mode (no out): the labels found
    LabelTable found;
    Bytes scene = isf({{"a.msgp", in}, {"a.csv", Bytes{'x', ',', '1'}}});
    t.expect_eq(scene_labels(scene, kTable, found, &err) && found.size() == 2 && found.count("閉じる") && found.count("戻る"), true,
                "scene_labels finds the scene's labels");
    // a truncated stream is an error, not a crash
    Bytes cut(in.begin(), in.begin() + in.size() - 2);
    t.expect_eq(rewrite_labels(cut, keep, &out, &n, &err), false, "truncated: false");
}

NATIVE_TEST("english-art/labels-isf-repack") {
    Bytes m1 = tree("閉じる", "戻る"), m2(100, 0x42), m3 = {'n', 'a', 'm', 'e', ',', '0'};
    Bytes d = isf({{"s.msgp", m1}, {"s.aif", m2}, {"s.csv", m3}}), out;
    std::string err;
    t.expect_eq(aska::isf_repack(d, {}, out, &err) && out == d, true, "nothing replaced: the same bytes");
    Bytes big = tree("スキップしますか？\nはい", "閉じる"), small = tree("A", "B");
    for (const Bytes* p : {&big, &small}) {
        t.expect_eq(aska::isf_repack(d, {p, nullptr, nullptr}, out, &err), true, "repack");
        t.expect_eq(out, isf({{"s.msgp", *p}, {"s.aif", m2}, {"s.csv", m3}}), "the layout and sums of a file made with that member");
    }
    // edit_labels: the scene with its tree in English, the other members as they were
    Bytes scene = d;
    size_t n = 0;
    t.expect_eq(edit_labels(scene, kTable, &n, &err) && n == 2, true, "edit_labels");
    t.expect_eq(scene, isf({{"s.msgp", tree("Close", "Back")}, {"s.aif", m2}, {"s.csv", m3}}), "edit_labels: the repacked scene");
    Bytes bad = d;
    bad[16 + 16 + 4] ^= 0x20;  // the second member moved off the layout
    t.expect_eq(aska::isf_repack(bad, {}, out, &err), false, "a scene laid out otherwise is refused");
}

NATIVE_TEST("english-art/labels-build") {
    // a synthetic download: two scenes, one with labels; no font, no recipes
    std::string tmp = soa::temp_dir() + "/soa-english-labels-test-" + std::to_string(getpid());
    std::string dl = tmp + "/dl", out = tmp + "/out";
    auto put = [&](const std::string& rel, const Bytes& plain) {
        cdn::files::mkdirs(dl + "/" + rel.substr(0, rel.rfind('/')));
        Bytes f = adld::encrypt(rel, aska::slz_encode(plain), adld::kXor);
        cdn::files::write_file(dl + "/" + rel, f.data(), f.size());
    };
    Bytes with = isf({{"a.msgp", tree("閉じる", "戻る")}, {"a.csv", Bytes{'x'}}});
    Bytes without = isf({{"b.msgp", tree("ほか", "なし")}});
    put("UI/etc2/a.csf", with);
    put("TalkScene/etc2/b.csf", without);
    Options o;
    o.download = dl, o.out = out, o.labels = kTable;
    Stats s1, s2, s3;
    std::string err;
    if (!build(o, &s1, &err)) t.fail("build: %s", err.c_str());
    t.expect_eq(s1.label_scenes == 1 && s1.built == 1 && s1.labels_replaced == 2 && s1.failed == 0, true, "one scene with labels, built");
    Bytes got, plain;
    cdn::files::read_file(out + "/UI/etc2/a-en.csf", got);
    t.expect_eq(adld::flags_of(got.data(), got.size()), adld::kXor, "ADLD XOR under the -en name");
    aska::slz_decode(adld::decrypt("UI/etc2/a-en.csf", got), plain);
    t.expect_eq(plain, isf({{"a.msgp", tree("Close", "Back")}, {"a.csv", Bytes{'x'}}}), "the scene with its labels in English");
    t.expect_eq(cdn::files::stat_file(out + "/TalkScene/etc2/b-en.csf", nullptr), false, "a scene without labels gets no -en file");
    build(o, &s2, &err);
    t.expect_eq(s2.built == 0 && s2.cached == 1, true, "the second build is a cache hit");
    o.labels = {{"閉じる", "Shut"}};  // another English: built again; no labels: removed
    build(o, &s3, &err);
    t.expect_eq(s3.built, (size_t)1, "a changed label table rebuilds the scene");
    o.labels.clear();
    o.labels["該当なし"] = "none";
    Stats s4;
    build(o, &s4, &err);
    t.expect_eq(s4.removed == 1 && !cdn::files::stat_file(out + "/UI/etc2/a-en.csf", nullptr), true, "a scene no longer translated is removed");
    for (const char* f : {"/dl/UI/etc2/a.csf", "/dl/TalkScene/etc2/b.csf", "/out.art-cache/outputs.txt", "/out.art-cache/UI/etc2/a-en.csf.stamp"})
        ::remove((tmp + f).c_str());
    for (const char* d : {"/dl/UI/etc2", "/dl/UI", "/dl/TalkScene/etc2", "/dl/TalkScene", "/dl", "/out/UI/etc2", "/out/UI", "/out",
                          "/out.art-cache/UI/etc2", "/out.art-cache/UI", "/out.art-cache", ""})
        ::rmdir((tmp + d).c_str());
}

}  // namespace soa::server::english_art
