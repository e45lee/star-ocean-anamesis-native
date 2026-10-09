#include "soaruntime/android/prefs.h"

#include <soa/base64.h>
#include <soa/prefs_xml.h>

#include <fstream>
#include <sstream>

#include "soaruntime/core/log.h"
#include "soaruntime/core/vfs.h"

namespace soa {

SharedPrefs& SharedPrefs::get() {
    static SharedPrefs p;
    return p;
}

SharedPrefs::File& SharedPrefs::load(const std::string& name) {
    File& f = files_[name];
    if (f.loaded) return f;
    f.loaded = true;
    std::ifstream in(host_shared_prefs_dir() + "/" + name + ".xml", std::ios::binary);
    if (!in) return f;
    std::stringstream ss;
    ss << in.rdbuf();
    f.entries = prefs_xml::parse(ss.str());
    LOGI("prefs", "loaded %s.xml (%zu entries)", name.c_str(), f.entries.size());
    return f;
}

void SharedPrefs::save(const std::string& name, const File& f) {
    std::string out = prefs_xml::serialize(f.entries);
    std::string path = host_shared_prefs_dir() + "/" + name + ".xml";
    std::string tmp = path + ".tmp";
    {
        std::ofstream o(tmp, std::ios::binary | std::ios::trunc);
        o << out;
    }
    rename(tmp.c_str(), path.c_str());
}

std::vector<unsigned char> SharedPrefs::get_bytes(const std::string& file, const std::string& key) {
    std::lock_guard lk(m_);
    File& f = load(file);
    for (auto& [k, v] : f.entries)
        if (k == key) {
            std::string b = base64::decode(v);
            return {b.begin(), b.end()};
        }
    return {};
}

void SharedPrefs::set_bytes(const std::string& file, const std::string& key, const std::vector<unsigned char>& value) {
    std::lock_guard lk(m_);
    File& f = load(file);
    // Android's serializer leaves the value's trailing newline followed by 4 spaces of indentation.
    std::string text = base64::android_default(std::string_view((const char*)value.data(), value.size())) + "    ";
    bool found = false;
    for (auto& [k, v] : f.entries)
        if (k == key) v = text, found = true;
    if (!found) f.entries.emplace_back(key, text);
    save(file, f);
}

void SharedPrefs::remove(const std::string& file, const std::string& key) {
    std::lock_guard lk(m_);
    File& f = load(file);
    std::erase_if(f.entries, [&](auto& e) { return e.first == key; });
    save(file, f);
}

void SharedPrefs::clear(const std::string& file) {
    std::lock_guard lk(m_);
    File& f = load(file);
    f.entries.clear();
    save(file, f);
}

}  // namespace soa
