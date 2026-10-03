#include "android/prefs.h"

#include <cstring>
#include <fstream>
#include <sstream>

#include "core/log.h"
#include "core/vfs.h"

namespace soa {

namespace {
const char* kB64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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

std::string java_base64(const std::vector<unsigned char>& d) {
    std::string raw;
    for (size_t i = 0; i < d.size(); i += 3) {
        uint32_t v = d[i] << 16;
        if (i + 1 < d.size()) v |= d[i + 1] << 8;
        if (i + 2 < d.size()) v |= d[i + 2];
        raw.push_back(kB64[(v >> 18) & 63]);
        raw.push_back(kB64[(v >> 12) & 63]);
        raw.push_back(i + 1 < d.size() ? kB64[(v >> 6) & 63] : '=');
        raw.push_back(i + 2 < d.size() ? kB64[v & 63] : '=');
    }
    std::string out;
    for (size_t i = 0; i < raw.size(); i += 76) out += raw.substr(i, 76) + "\n";
    return out;
}

std::vector<unsigned char> base64_decode(const std::string& s) {
    std::vector<unsigned char> out;
    uint32_t acc = 0;
    int bits = 0;
    for (char c : s) {
        const char* p = c ? strchr(kB64, c) : nullptr;
        if (!p) continue;
        acc = (acc << 6) | (uint32_t)(p - kB64);
        bits += 6;
        if (bits >= 8) {
            bits -= 8;
            out.push_back((unsigned char)(acc >> bits));
        }
    }
    return out;
}

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
        if (k == key) return base64_decode(v);
    return {};
}

void SharedPrefs::set_bytes(const std::string& file, const std::string& key, const std::vector<unsigned char>& value) {
    std::lock_guard lk(m_);
    File& f = load(file);
    // Android's serializer leaves the value's trailing newline followed by 4 spaces of indentation.
    std::string text = java_base64(value) + "    ";
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
