// The corpus of CParameterElementBase::Deserialize inputs (params_corpus.h).
#include "native/params/params_corpus.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <unordered_set>

#include "core/loader.h"
#include "core/log.h"
#include "native/params/params_check.h"
#include "native/params/params_property.h"

namespace soa::native::params {

namespace {

constexpr u32 kVersion = 1;

struct Writer {
    std::vector<u8> b;
    void raw(const void* p, size_t n) { b.insert(b.end(), (const u8*)p, (const u8*)p + n); }
    template <typename T>
    void put(T v) { raw(&v, sizeof v); }
    void str(const char* p, size_t n) {
        put<u32>((u32)n);
        raw(p, n);
    }
    void str(const std::string& s) { str(s.data(), s.size()); }
};

// The mangled _ZTV symbol of a vtable address point (vtable symbol + 0x10), or "".
std::string symbol_of(const void* vtable) {
    const LoadedLib& lib = *main_lib();
    u64 a = (u64)vtable - 0x10;
    auto it = std::lower_bound(lib.sorted_syms.begin(), lib.sorted_syms.end(), a, [](const LoadedLib::Sym& y, u64 x) { return y.addr < x; });
    for (; it != lib.sorted_syms.end() && it->addr == a; ++it)
        if (std::strncmp(it->name, "_ZTV", 4) == 0) return it->name;
    return {};
}

void put_value(Writer& w, const AValue& v, int depth) {
    w.put<u32>(depth > 64 ? 0 : v.m_kind);
    if (depth > 64) return;
    switch (v.m_kind) {
    case AValue::kBool:
    case AValue::kUInt:
    case AValue::kSInt:
    case AValue::kFloat: w.raw(&v.m_body, 8); break;
    case AValue::kString: {
        const auto& s = v.m_body.str;
        w.put<u32>(v.m_length);
        u32 n = v.m_length == 0xffffffffu ? 0 : v.m_length;
        w.put<u8>(s.m_data != nullptr);
        w.str(s.m_data ? s.m_data : "", s.m_data ? n : 0);
        w.put<u8>(s.m_cstr != nullptr);
        w.str(s.m_cstr ? s.m_cstr : "", s.m_cstr ? strlen(s.m_cstr) : 0);
        break;
    }
    case AValue::kArray:
        w.put<u32>(v.m_body.array.m_count);
        for (u32 i = 0; i < v.m_body.array.m_count; i++) put_value(w, v.m_body.array.m_elements[i], depth + 1);
        break;
    case AValue::kMap:
        w.put<u32>(v.m_body.map.m_count);
        for (u32 i = 0; i < v.m_body.map.m_count; i++) {
            put_value(w, v.m_body.map.m_pairs[i].key, depth + 1);
            put_value(w, v.m_body.map.m_pairs[i].value, depth + 1);
        }
        break;
    case AValue::kBinary:
    case AValue::kExt:
        w.put<s8>(v.m_body.bin.m_extType);
        w.str((const char*)v.m_body.bin.m_data, v.m_body.bin.m_data ? v.m_body.bin.m_size : 0);
        break;
    default: break;
    }
}

std::mutex g_m;
FILE* g_file = nullptr;
std::unordered_set<std::string>* g_seen = nullptr;
u64 g_records = 0, g_skipped = 0;

}  // namespace

bool corpus_on() { return fam().on() && fam().family().dump; }

void corpus_record(const CParameterElementBase* e, const AMap* map) {
    if (!map) return;
    Writer w;
    w.str(symbol_of(e->vtable));
    std::vector<const IParameterProperty*> props;
    bool self = false;
    for (const IParameterProperty* p = e->m_first; p; p = p->m_next) {
        props.push_back(p);
        if (p->m_next == p) {
            self = true;
            break;
        }
        if (props.size() > 0x10000) return;
    }
    w.put<u32>((u32)props.size());
    for (const IParameterProperty* p : props) {
        std::string ztv = symbol_of(p->vtable);
        u8 kind = ztv.rfind("_ZTV23CParameterPropertyValue", 0) == 0 ? 0 : ztv.rfind("_ZTV24CParameterPropertyString", 0) == 0 ? 1 : 2;
        if (kind == 2 || !KnownProperty(p->vtable)) {
            std::lock_guard lk(g_m);
            g_skipped++;
            return;  // (only lists of bound properties are rebuilt by the test)
        }
        w.put<s64>((s64)((const u8*)p - (const u8*)e));
        w.str(ztv);
        w.put<u8>(kind);
        u8 head[0x28];
        std::memcpy(head, p, sizeof head);
        std::memset(head, 0, 0x10);         // vtable, m_next
        std::memset(head + 0x18, 0, 8);     // m_name's vtable
        w.raw(head, sizeof head);
        if (kind == 0) {
            w.raw((const u8*)p + 0x28, 8);
        } else {
            const String& s = reinterpret_cast<const CParameterPropertyString<0>*>(p)->m_value;
            w.put<u64>(s.capacity());
            w.str(s.data(), s.size());
        }
    }
    w.put<u8>(self);
    AValue root{};
    root.m_kind = AValue::kMap;
    root.m_body.map = *map;
    put_value(w, root, 0);

    std::lock_guard lk(g_m);
    if (!g_seen) g_seen = new std::unordered_set<std::string>;
    std::string key((const char*)w.b.data(), w.b.size());
    if (!g_seen->insert(std::move(key)).second) return;
    if (!g_file) {
        std::string path = (fam().family().out_path.empty() ? std::string("params") : fam().family().out_path) + ".corpus";
        g_file = fopen(path.c_str(), "wb");
        if (!g_file) return;
        fwrite("PRMC", 1, 4, g_file);
        fwrite(&kVersion, 4, 1, g_file);
        LOGI("params_check", "corpus: writing %s", path.c_str());
    }
    u32 n = (u32)w.b.size();
    fwrite(&n, 4, 1, g_file);
    fwrite(w.b.data(), 1, n, g_file);
    fflush(g_file);
    if (++g_records % 1000 == 0) LOGI("params_check", "corpus: %llu records (%llu skipped)", (unsigned long long)g_records, (unsigned long long)g_skipped);
}

// ---- reading ----

namespace {
struct Reader {
    const u8* p;
    const u8* end;
    bool ok = true;
    bool raw(void* out, size_t n) {
        if ((size_t)(end - p) < n) return ok = false;
        std::memcpy(out, p, n);
        p += n;
        return true;
    }
    template <typename T>
    T get() {
        T v{};
        raw(&v, sizeof v);
        return v;
    }
    std::string str() {
        u32 n = get<u32>();
        if (!ok || (size_t)(end - p) < n) {
            ok = false;
            return {};
        }
        std::string s((const char*)p, n);
        p += n;
        return s;
    }
};

bool get_value(Reader& r, CorpusValue& v, int depth) {
    v.kind = r.get<u32>();
    if (!r.ok || depth > 64) return false;
    switch (v.kind) {
    case AValue::kBool:
    case AValue::kUInt:
    case AValue::kSInt:
    case AValue::kFloat: r.raw(v.body, 8); break;
    case AValue::kString:
        v.length = r.get<u32>();
        v.has_data = r.get<u8>();
        v.data = r.str();
        v.has_cstr = r.get<u8>();
        v.cstr = r.str();
        break;
    case AValue::kArray: {
        u32 n = r.get<u32>();
        if (n > 1000000) return false;
        v.items.resize(n);
        for (auto& x : v.items)
            if (!get_value(r, x, depth + 1)) return false;
        break;
    }
    case AValue::kMap: {
        u32 n = r.get<u32>();
        if (n > 1000000) return false;
        v.items.resize(2 * (size_t)n);
        for (auto& x : v.items)
            if (!get_value(r, x, depth + 1)) return false;
        break;
    }
    case AValue::kBinary:
    case AValue::kExt:
        v.ext = r.get<s8>();
        v.data = r.str();
        break;
    default: break;
    }
    return r.ok;
}
}  // namespace

bool corpus_read(const std::string& path, std::vector<CorpusRecord>& out) {
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return false;
    std::vector<u8> b;
    u8 buf[65536];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, f)) > 0) b.insert(b.end(), buf, buf + n);
    fclose(f);
    if (b.size() < 8 || std::memcmp(b.data(), "PRMC", 4) != 0) return false;
    u32 version;
    std::memcpy(&version, b.data() + 4, 4);
    if (version != kVersion) return false;
    size_t pos = 8;
    while (pos + 4 <= b.size()) {
        u32 len;
        std::memcpy(&len, b.data() + pos, 4);
        pos += 4;
        if (pos + len > b.size()) return false;
        Reader r{b.data() + pos, b.data() + pos + len};
        pos += len;
        CorpusRecord rec;
        rec.element = r.str();
        u32 np = r.get<u32>();
        if (!r.ok || np > 0x10000) return false;
        rec.props.resize(np);
        for (auto& p : rec.props) {
            p.offset = r.get<s64>();
            p.ztv = r.str();
            p.kind = r.get<u8>();
            r.raw(p.head, sizeof p.head);
            if (p.kind == 0) {
                r.raw(p.value, 8);
            } else {
                p.capacity = r.get<u64>();
                p.bytes = r.str();
            }
        }
        rec.self_linked = r.get<u8>();
        if (!get_value(r, rec.map, 0) || rec.map.kind != AValue::kMap) return false;
        out.push_back(std::move(rec));
    }
    return true;
}

HostAson::HostAson(const CorpusValue& root) {
    blocks_.emplace_back(new u8[sizeof(AValue)]());
    root_ = (AValue*)blocks_.back().get();
    build(root, *root_);
}

void HostAson::build(const CorpusValue& v, AValue& out) {
    std::memset(&out, 0, sizeof out);
    out.m_kind = v.kind;
    out.m_cstrWork = 0xffff;
    auto keep = [&](const std::string& s) {
        blocks_.emplace_back(new u8[s.size() + 1]());
        std::memcpy(blocks_.back().get(), s.data(), s.size());
        return (const char*)blocks_.back().get();
    };
    switch (v.kind) {
    case AValue::kBool:
    case AValue::kUInt:
    case AValue::kSInt:
    case AValue::kFloat: std::memcpy(&out.m_body, v.body, 8); break;
    case AValue::kString:
        out.m_length = v.length;
        out.m_body.str.m_data = v.has_data ? keep(v.data) : nullptr;
        out.m_body.str.m_cstr = v.has_cstr ? keep(v.cstr) : nullptr;
        break;
    case AValue::kArray: {
        u32 n = (u32)v.items.size();
        blocks_.emplace_back(new u8[sizeof(AValue) * (n ? n : 1)]());
        AValue* a = (AValue*)blocks_.back().get();
        for (u32 i = 0; i < n; i++) build(v.items[i], a[i]);
        out.m_body.array.m_elements = a;
        out.m_body.array.m_count = n;
        break;
    }
    case AValue::kMap: {
        u32 n = (u32)(v.items.size() / 2);
        blocks_.emplace_back(new u8[sizeof(ASON_Pair) * (n ? n : 1)]());
        ASON_Pair* a = (ASON_Pair*)blocks_.back().get();
        for (u32 i = 0; i < n; i++) {
            build(v.items[2 * i], a[i].key);
            build(v.items[2 * i + 1], a[i].value);
        }
        out.m_body.map.m_pairs = a;
        out.m_body.map.m_count = n;
        break;
    }
    case AValue::kBinary:
    case AValue::kExt:
        out.m_body.bin.m_data = (const u8*)keep(v.data);
        out.m_body.bin.m_size = (u32)v.data.size();
        out.m_body.bin.m_extType = v.ext;
        break;
    default: break;
    }
}

}  // namespace soa::native::params
