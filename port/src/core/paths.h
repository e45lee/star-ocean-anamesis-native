#pragma once
// Repository resources (port code): the files soa reads from the source checkout (the master DBs
// under data/, the seed saves, server/tests/fixtures, port/fakeapi, standin-assets, work/...),
// found from the executable's location, so soa runs from any working directory.
//
// The roots are found once, by the rule every program shares (common soa/install.h, "the repo
// roots"; docs/environment.md "How the programs find the game files"):
//   development build: --repo DIR (RunOptions::repo_dir); else upwards from the executable
//     (build/port/soa -> ../..), the first directory holding port/CMakeLists.txt; else upwards
//     from the working directory. In a git worktree whose work/ is a symlink into the main
//     checkout, that main checkout too (untracked data such as data/basmaster-3.7.0.sqlite3). Then
//     the install dirs (the executable's folder and its game/); without a checkout, the working
//     directory last.
//   release build (scripts/build.sh --release: the packages, README.md "Packaging"): --repo DIR
//     when given, then the install dirs; never a checkout around the program. A packaged soa's data
//     files (data/gacha_pools.sqlite3, data/saves/seed/Game.xml, standin-assets/) sit at their repo
//     paths beside the executable.
//
// Paths the user gives explicitly (command line, SOA_* variables) are never resolved here: they
// stay as given, relative to the working directory.
#include <initializer_list>
#include <string>
#include <vector>

namespace soa {

// The repo root (absolute, no trailing slash), "" when none was found.
const std::string& repo_root();
// The roots searched by find_repo_file, in order (see above).
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
