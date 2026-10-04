#include "android/prefs.h"

#include <soa/base64.h>

#include <cstring>
#include <fstream>
#include <sstream>

#include "core/log.h"
#include "core/vfs.h"

namespace soa {

namespace {
std::string xml_unescape(const std::string& s) {
    std::string out;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] != '&') {
            out.push_back(s[i]);
            continue;
        }
        size_t e = s.find(';', i);
        if (e == std::string::npos) {
            out.push_back(s[i]);
            continue;
        }
        std::string ent = s.substr(i + 1, e - i - 1);
        if (ent == "amp") out.push_back('&');
        else if (ent == "lt") out.push_back('<');
        else if (ent == "gt") out.push_back('>');
        else if (ent == "quot") out.push_back('"');
        else if (ent == "apos") out.push_back('\'');
        else if (!ent.empty() && ent[0] == '#') {
            long cp = ent.size() > 1 && (ent[1] == 'x' || ent[1] == 'X') ? strtol(ent.c_str() + 2, nullptr, 16) : strtol(ent.c_str() + 1, nullptr, 10);
            if (cp < 0x80) out.push_back((char)cp);
            else out += "?";
        } else {
            out += "&" + ent + ";";
        }
        i = e;
    }
    return out;
}

std::string xml_escape(const std::string& s) {
    std::string out;
    for (char c : s) {
        switch (c) {
        case '&': out += "&amp;"; break;
        case '<': out += "&lt;"; break;
        case '>': out += "&gt;"; break;
        case '"': out += "&quot;"; break;
        case '\n': out += "&#10;"; break;
        default: out.push_back(c);
        }
    }
    return out;
}
}  // namespace

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
    std::string xml = ss.str();
    size_t pos = 0;
    while ((pos = xml.find("<string name=\"", pos)) != std::string::npos) {
        pos += 14;
        size_t q = xml.find('"', pos);
        std::string key = xml_unescape(xml.substr(pos, q - pos));
        size_t gt = xml.find('>', q);
        if (xml[gt - 1] == '/') {  // <string name="x" />
            f.entries.emplace_back(key, "");
            pos = gt;
            continue;
        }
        size_t end = xml.find("</string>", gt);
        f.entries.emplace_back(key, xml_unescape(xml.substr(gt + 1, end - gt - 1)));
        pos = end;
    }
    LOGI("prefs", "loaded %s.xml (%zu entries)", name.c_str(), f.entries.size());
    return f;
}

void SharedPrefs::save(const std::string& name, const File& f) {
    std::string out = "<?xml version='1.0' encoding='utf-8' standalone='yes' ?>\n<map>\n";
    for (auto& [k, v] : f.entries) out += "    <string name=\"" + xml_escape(k) + "\">" + xml_escape(v) + "</string>\n";
    out += "</map>\n";
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
