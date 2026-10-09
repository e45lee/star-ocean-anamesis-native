#pragma once
// android.content.SharedPreferences, as used through jb.Aska.SharedPreferencesBridge:
// string values holding Base64 (DEFAULT flags) of raw bytes (soa/base64.h).
//
// Files are written in the same byte format as Android's, so soa_save (the save editor)
// works on desktop saves unchanged: <data>/shared_prefs/<name>.xml
#include <map>
#include <mutex>
#include <string>
#include <vector>

namespace soa {

class SharedPrefs {
public:
    static SharedPrefs& get();

    // Returns decoded bytes, or an empty vector when missing.
    std::vector<unsigned char> get_bytes(const std::string& file, const std::string& key);
    void set_bytes(const std::string& file, const std::string& key, const std::vector<unsigned char>& value);
    void remove(const std::string& file, const std::string& key);
    void clear(const std::string& file);

private:
    struct File {
        bool loaded = false;
        std::vector<std::pair<std::string, std::string>> entries;  // key -> raw XML text (unescaped)
    };
    File& load(const std::string& name);
    void save(const std::string& name, const File& f);
    std::mutex m_;
    std::map<std::string, File> files_;
};

}  // namespace soa
