#pragma once
// Where the server's 3.7.0 master DB comes from (library code; server/README.md "The master DB",
// docs/server-rules.md#core). The decrypted master is the game's own data, so it isn't shipped in
// the release packages (README.md "Packaging"): the server derives it from the user's game files at
// startup instead, with the client's own ADLD decryption (soaserver/adld.h).
//
// The rule (resolve()), first that exists:
//   1. --master FILE (config().master);
//   2. data/basmaster-3.7.0.sqlite3 in the repo roots (a source checkout; find_repo_file);
//   3. derived from the 3.7.0 download's sqlite/basmaster.sqlite3 (ADLD v2, the full 3.7.0 master
//      the client fetches after login): config().download_dir, else the repo's
//      work/download-3.7.0, else a download tree in the install dirs (soa/install.h);
//   4. derived from the 3.7.0 APK's assets/builtin_data/sqlite/basmaster.sqlite3 (the app's
//      built-in, OLDER master: logged as a warning; content added after the APK was built is
//      missing from it): config().apk, else the repo's apk/, else the install dirs' *.apk; only
//      with a zip reader (set_zip_reader: soa has one, soa-server not).
// A derived master is written once into the cache dir (config().data_root + "/master", else this
// platform's default data dir of soa-server + "/master"), named by the SHA-1 of the encrypted
// source (basmaster-3.7.0-<download|apk>-<sha1 12>.sqlite3), so a changed download derives a new
// one and an unchanged one is reused; the decryption of the download's file is byte-identical to
// the committed data/basmaster-3.7.0.sqlite3 (the test cdn/master-source).
#include <cstdint>
#include <string>
#include <vector>

namespace soa::server::master_source {

// Decrypts the ADLD master `encrypted` (the bytes of a sqlite/basmaster.sqlite3) into
// `cache_dir`/basmaster-3.7.0-<tag>-<sha1 12>.sqlite3, unless that file is already there. The path,
// or "" (with *err) when it isn't an ADLD SQLite master or can't be written. *reused (if given):
// the cached file was there.
std::string derive(const std::vector<uint8_t>& encrypted, const std::string& tag, const std::string& cache_dir, std::string* err,
                   bool* reused = nullptr);
// The same from a download tree's sqlite/basmaster.sqlite3 / an APK's built-in master (a stored
// zip entry).
std::string derive_from_download(const std::string& download_dir, const std::string& cache_dir, std::string* err, bool* reused = nullptr);
std::string derive_from_apk(const std::string& apk, const std::string& cache_dir, std::string* err, bool* reused = nullptr);

// The embedder's zip reader (the library reads no zips itself): one entry of a zip into `out`;
// false when the file, the entry or the read fails. soa sets the runtime's (runtime/src/android/zip.h
// read_zip_entry); without one (soa-server) step 4 (the APK) is skipped with a note.
using ZipReader = bool (*)(const std::string& zip, const std::string& entry, std::vector<uint8_t>& out);
void set_zip_reader(ZipReader reader);
bool has_zip_reader();

// The cache dir derived masters go to (see above).
std::string cache_dir();

// The rule above, once: sets config().master to the result and logs where it came from. "" when
// nothing was found (the reason is logged). Later calls return config().master.
const std::string& resolve();
// Forget the cached result (tests).
void reset();

}  // namespace soa::server::master_source
