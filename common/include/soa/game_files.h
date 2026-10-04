#pragma once
// The install-dir lookup's zip-aware half (target soa_gamefiles; the folder-only half is the
// header-only soa/install.h): the 3.7.0 APK recognised by its contents, the 3.7.0 download as a
// folder or as SOA-3.7.0-canonical-data.zip (read in place: soa/file_tree.h), and the APK's
// libSOA.so extracted. Used by soa, soa-emu and soa-server (README.md "Packaging").
#include <string>
#include <vector>

#include "soa/install.h"

namespace soa::install {

// Is `path` the 3.7.0 APK (a zip whose lib/arm64-v8a/libSOA.so has 3.7.0's size)?
bool is_apk_370(const std::string& path);
// The first 3.7.0 APK at the top level of `dirs` (apk_candidates' order); `notes` gets the
// rejected candidates.
std::string find_apk(const std::vector<std::string>& dirs, std::vector<std::string>* notes = nullptr);

// Is `path` a 3.7.0 download, a folder or a zip (soa::is_download_tree)?
bool is_download(const std::string& path);
// The 3.7.0 download among `dirs`: a folder tree first (find_download_dir), else a zip at their
// top level: kDataZipName first, then any other *.zip that holds a download tree. `notes` gets the
// zips that were looked at and rejected.
std::string find_download(const std::vector<std::string>& dirs, std::vector<std::string>* notes = nullptr);

// Extracts the entry `name` of the zip `zip` to the file `out` (through "<out>.tmp" and a rename).
bool extract_entry(const std::string& zip, const std::string& name, const std::string& out);

}  // namespace soa::install
