#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "soaruntime/core/cpu.h"

namespace soa {

struct LoadedLib {
    std::string path;
    u64 base = 0;
    u64 size = 0;
    u64 phdr = 0;  // guest address of program headers
    u16 phnum = 0;
    std::vector<u64> init_array;
    u64 init_fn = 0;
    u64 eh_frame_hdr = 0;

    // Allocated sections from the ELF's section headers (name, guest address, size), e.g. for
    // tests that need .rodata / .data.rel.ro bounds. Empty when the file has no section headers.
    struct Section {
        std::string name;
        u64 addr, size;
    };
    std::vector<Section> sections;
    // The named section's guest address and size; false when it isn't there.
    bool section(const char* name, u64& addr, u64& size) const;

    // Returns guest address of an exported symbol, or 0.
    u64 sym(const std::string& name) const;
    // Nearest preceding defined function symbol for an address (for diagnostics).
    bool symbolize(u64 addr, std::string& name, u64& offset) const;

    struct Sym {
        u64 addr, size;
        const char* name;
    };
    std::vector<Sym> sorted_syms;
    std::vector<char> strtab_copy;

    struct Export {
        u64 addr, size;
        u8 type;  // STT_*
    };
    std::unordered_map<std::string, Export> exports;
};

// Loads and relocates an AArch64 shared object. Imports are resolved via Hle.
LoadedLib* load_library(const std::string& path);

// The address of the same exported symbol (+ the same offset into it) in another loaded image
// (e.g. another build of the library). 0 when `addr` isn't inside an exported function/object of `from`, or `to`
// has no symbol of that name (or a smaller one).
u64 translate_symbol_addr(const LoadedLib& from, const LoadedLib& to, u64 addr);
// All loaded images (live first), e.g. for dl_iterate_phdr.
const std::vector<LoadedLib*>& loaded_libs();
void run_initializers(LoadedLib& lib);
LoadedLib* main_lib();

}  // namespace soa
