// Runtime tests of the loader's errors (core/loader.h). Run by `soa --selftest` and soaruntime_tests.
//
// loader/rejects-bad-files: load_library returns nullptr with a reason for a file that isn't a
// loadable AArch64 shared library (a missing file, not ELF, another machine, a truncated header,
// a segment past the end of the file, no PT_DYNAMIC, no dynamic symbol table, an unsupported
// relocation), and registers nothing: before, each of these ended the process (fatal) or read past
// the file.
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "core/elf64.h"
#include "soaruntime/core/loader.h"
#include "soaruntime/core/selftest.h"

namespace soa {
namespace {

namespace fs = std::filesystem;

// A minimal AArch64 shared object: the ELF header, two program headers (one PT_LOAD of the whole
// file at vaddr 0, one PT_DYNAMIC), the dynamic table, a symbol table of one null symbol, DT_HASH
// (nbucket 1, nchain 1) and a one-byte string table. `rel_type` != 0 adds a DT_RELA with one
// relocation of that type; `with_symtab` false leaves DT_SYMTAB out.
std::vector<u8> make_elf(bool with_symtab = true, u32 rel_type = 0) {
    constexpr u64 kPh = sizeof(Elf64_Ehdr), kDyn = kPh + 2 * sizeof(Elf64_Phdr), kDynCount = 8;
    constexpr u64 kSym = kDyn + kDynCount * sizeof(Elf64_Dyn), kHash = kSym + sizeof(Elf64_Sym), kStr = kHash + 16,
                  kRela = kStr + 8, kSize = kRela + sizeof(Elf64_Rela);
    std::vector<u8> f(kSize, 0);
    auto* eh = (Elf64_Ehdr*)f.data();
    memcpy(eh->e_ident, ELFMAG, SELFMAG);
    eh->e_ident[EI_CLASS] = ELFCLASS64;
    eh->e_ident[5] = 1;  // EI_DATA: little-endian
    eh->e_ident[6] = 1;  // EI_VERSION
    eh->e_type = 3;      // ET_DYN
    eh->e_machine = EM_AARCH64;
    eh->e_version = 1;
    eh->e_phoff = kPh;
    eh->e_ehsize = sizeof(Elf64_Ehdr);
    eh->e_phentsize = sizeof(Elf64_Phdr);
    eh->e_phnum = 2;
    auto* ph = (Elf64_Phdr*)(f.data() + kPh);
    ph[0].p_type = PT_LOAD;
    ph[0].p_filesz = ph[0].p_memsz = kSize;
    ph[1].p_type = PT_DYNAMIC;
    ph[1].p_offset = ph[1].p_vaddr = kDyn;
    ph[1].p_filesz = ph[1].p_memsz = kDynCount * sizeof(Elf64_Dyn);
    auto* d = (Elf64_Dyn*)(f.data() + kDyn);
    int n = 0;
    auto add = [&](s64 tag, u64 v) {
        d[n].d_tag = tag;
        d[n].d_un.d_val = v;
        n++;
    };
    if (with_symtab) add(DT_SYMTAB, kSym);
    add(DT_STRTAB, kStr);
    add(DT_HASH, kHash);
    if (rel_type) {
        add(DT_RELA, kRela);
        add(DT_RELASZ, sizeof(Elf64_Rela));
        auto* r = (Elf64_Rela*)(f.data() + kRela);
        r->r_offset = kStr;
        r->r_info = rel_type;
    }
    add(DT_NULL, 0);
    u32* hash = (u32*)(f.data() + kHash);
    hash[0] = 1, hash[1] = 1;  // nbucket, nchain = the symbol count
    return f;
}

struct TempDir {
    fs::path dir;
    TempDir() {
        dir = fs::temp_directory_path() /
              ("soa-loader-test-" + std::to_string((long long)fs::file_time_type::clock::now().time_since_epoch().count()));
        fs::create_directories(dir);
    }
    ~TempDir() {
        std::error_code ec;
        fs::remove_all(dir, ec);
    }
    std::string write(const char* name, const std::vector<u8>& bytes) {
        std::string p = (dir / name).string();
        std::ofstream(p, std::ios::binary).write((const char*)bytes.data(), (std::streamsize)bytes.size());
        return p;
    }
};

}  // namespace

RUNTIME_TEST("loader/rejects-bad-files") {
    TempDir tmp;
    const size_t libs_before = loaded_libs().size();
    const LoadedLib* main_before = main_lib();
    auto expect_error = [&](const std::string& path, const char* reason, const char* what) {
        std::string err;
        LoadedLib* lib = load_library(path, &err);
        if (lib) t.fail("%s: loaded", what);
        else if (err.find(reason) == std::string::npos || err.rfind(path, 0) != 0)
            t.fail("%s: error \"%s\" doesn't name the file and \"%s\"", what, err.c_str(), reason);
    };
    expect_error((tmp.dir / "missing.so").string(), "cannot open", "a missing file");
    expect_error(tmp.write("text.so", std::vector<u8>(100, 'x')), "not an ELF", "not ELF");
    expect_error(tmp.write("tiny.so", {0x7f, 'E', 'L', 'F'}), "not an ELF", "shorter than an ELF header");
    {
        auto f = make_elf();
        ((Elf64_Ehdr*)f.data())->e_machine = 62;  // EM_X86_64
        expect_error(tmp.write("x86.so", f), "not an AArch64", "an x86-64 ELF");
    }
    {
        auto f = make_elf();
        f.resize(sizeof(Elf64_Ehdr) + 8);  // cut inside the program headers
        expect_error(tmp.write("cut.so", f), "truncated", "truncated program headers");
    }
    {
        auto f = make_elf();
        ((Elf64_Phdr*)(f.data() + sizeof(Elf64_Ehdr)))[0].p_filesz += 4096;  // the segment runs past the file
        ((Elf64_Phdr*)(f.data() + sizeof(Elf64_Ehdr)))[0].p_memsz += 4096;
        expect_error(tmp.write("past.so", f), "truncated", "a segment past the end of the file");
    }
    {
        auto f = make_elf();
        ((Elf64_Phdr*)(f.data() + sizeof(Elf64_Ehdr)))[1].p_type = 0;  // PT_NULL
        expect_error(tmp.write("nodyn.so", f), "no PT_DYNAMIC", "no PT_DYNAMIC");
    }
    expect_error(tmp.write("nosym.so", make_elf(false)), "missing dynamic symbol info", "no DT_SYMTAB");
    expect_error(tmp.write("rel.so", make_elf(true, 1)), "unsupported or bad relocation (type 1)", "an unsupported relocation");
    if (loaded_libs().size() != libs_before || main_lib() != main_before) t.fail("a failed load registered an image");
}

}  // namespace soa
