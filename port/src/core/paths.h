#pragma once
// Repository resources (port code): the files soa reads from the source checkout (the master DBs
// under data/, the seed saves, port/server-data, port/fakeapi, standin-assets, work/...),
// found from the executable's location, so soa runs from any working directory.
//
// The repo root is found once:
//   1. --repo DIR / SOA_REPO (RunOptions::repo_dir), when set;
//   2. else upwards from the executable (/proc/self/exe: build/port/soa -> ../..), the first
//      directory holding port/CMakeLists.txt;
//   3. else upwards from the working directory, the same way.
// In a git worktree whose work/ is a symlink into the main checkout, files the worktree lacks
// (untracked data such as data/basmaster-3.7.0.sqlite3) are also looked up
// in that main checkout.
//
// Paths the user gives explicitly (command line, SOA_* variables) are never resolved here: they
// stay as given, relative to the working directory.
#include <initializer_list>
#include <string>
#include <vector>

namespace soa {

// The repo root (absolute, no trailing slash), "" when none was found.
const std::string& repo_root();
// The roots searched by find_repo_file: repo_root(), then the main checkout (see above).
const std::vector<std::string>& repo_roots();
// repo_root() + "/" + rel ("rel" unchanged when no root was found).
std::string repo_path(const std::string& rel);
// The first existing path among `rels` (repo-relative), searched in every root in order of the
// candidates: all roots for the first candidate, then the next. "" when none exists.
std::string find_repo_file(std::initializer_list<const char*> rels);
std::string find_repo_file(const std::string& rel);
// Every existing path among `rels`, in the same order (for callers that try each in turn).
std::vector<std::string> repo_files(std::initializer_list<const char*> rels);

}  // namespace soa
