#include "core/loader.h"

#include <cxxabi.h>
#include <elf.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <cinttypes>
#include <cstring>
#include <functional>
#include <unordered_map>

#include "core/hle.h"
#include "core/log.h"

namespace soa {

namespace {
LoadedLib* g_main = nullptr;
std::vector<LoadedLib*> g_libs;
}  // namespace

LoadedLib* main_lib() { return g_main; }
const std::vector<LoadedLib*>& loaded_libs() { return g_libs; }

bool LoadedLib::section(const char* name, u64& addr, u64& size) const {
    for (const auto& s : sections)
        if (s.name == name) {
            addr = s.addr;
            size = s.size;
            return true;
        }
    return false;
}

u64 LoadedLib::sym(const std::string& name) const {
    auto it = exports.find(name);
    return it == exports.end() ? 0 : it->second.addr;
}

bool LoadedLib::symbolize(u64 addr, std::string& name, u64& offset) const {
    if (addr < base || addr >= base + size || sorted_syms.empty()) return false;
    auto it = std::upper_bound(sorted_syms.begin(), sorted_syms.end(), addr, [](u64 a, const Sym& s) { return a < s.addr; });
    if (it == sorted_syms.begin()) return false;
    --it;
    int status = 0;
    char* dem = abi::__cxa_demangle(it->name, nullptr, nullptr, &status);
    name = status == 0 && dem ? dem : it->name;
    free(dem);
    offset = addr - it->addr;
    return true;
}

u64 translate_symbol_addr(const LoadedLib& from, const LoadedLib& to, u64 addr) {
    if (addr < from.base || addr >= from.base + from.size) return 0;
    auto hi = std::upper_bound(from.sorted_syms.begin(), from.sorted_syms.end(), addr, [](u64 a, const LoadedLib::Sym& s) { return a < s.addr; });
    if (hi == from.sorted_syms.begin()) return 0;
    u64 start = (hi - 1)->addr, off = addr - start;
    // Every symbol at that address (aliases such as C1/C2 constructors).
    for (auto it = hi; it != from.sorted_syms.begin() && (it - 1)->addr == start;) {
        --it;
        if (off >= std::max<u64>(it->size, 1)) continue;
        auto t = to.exports.find(it->name);
        if (t != to.exports.end() && off < std::max<u64>(t->second.size, 1)) return t->second.addr + off;
    }
    return 0;
}

std::string describe_guest_addr(u64 addr) {
    char buf[64];
    snprintf(buf, sizeof buf, "0x%" PRIx64, addr);
    std::string out = buf;
    if (const char* t = thunk_name_at(addr)) return out + " <thunk:" + t + ">";
    for (LoadedLib* l : g_libs) {
        if (addr < l->base || addr >= l->base + l->size) continue;
        std::string n;
        u64 off;
        snprintf(buf, sizeof buf, " [lib+0x%" PRIx64 "]", addr - l->base);
        out += buf;
        if (l->symbolize(addr, n, off)) {
            if (n.size() > 160) n = n.substr(0, 160) + "...";
            snprintf(buf, sizeof buf, "+0x%" PRIx64, off);
            out += " " + n + buf;
        }
    }
    return out;
}

static LoadedLib* load_image(const std::string& path) {
    int fd = open(path.c_str(), O_RDONLY);
    if (fd < 0) fatal("cannot open %s", path.c_str());
    struct stat st;
    fstat(fd, &st);
    auto* file = (const u8*)mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (file == MAP_FAILED) fatal("mmap %s failed", path.c_str());

    auto* eh = (const Elf64_Ehdr*)file;
    if (memcmp(eh->e_ident, ELFMAG, SELFMAG) != 0 || eh->e_machine != EM_AARCH64) fatal("%s: not an AArch64 ELF", path.c_str());
    auto* ph = (const Elf64_Phdr*)(file + eh->e_phoff);

    u64 max_va = 0;
    for (int i = 0; i < eh->e_phnum; i++)
        if (ph[i].p_type == PT_LOAD) max_va = std::max<u64>(max_va, ph[i].p_vaddr + ph[i].p_memsz);
    max_va = (max_va + 0xffff) & ~0xffffull;

    void* mem = mmap(nullptr, max_va, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) fatal("mmap for image failed");
    u64 base = (u64)mem;

    auto* lib = new LoadedLib();
    lib->path = path;
    lib->base = base;
    lib->size = max_va;
    const Elf64_Dyn* dyn = nullptr;
    for (int i = 0; i < eh->e_phnum; i++) {
        if (ph[i].p_type == PT_LOAD) memcpy((void*)(base + ph[i].p_vaddr), file + ph[i].p_offset, ph[i].p_filesz);
        if (ph[i].p_type == PT_DYNAMIC) dyn = (const Elf64_Dyn*)(base + ph[i].p_vaddr);
        if (ph[i].p_type == PT_GNU_EH_FRAME) lib->eh_frame_hdr = base + ph[i].p_vaddr;
        if (ph[i].p_type == PT_LOAD && ph[i].p_offset == 0) lib->phdr = base + ph[i].p_vaddr + eh->e_phoff;
    }
    lib->phnum = eh->e_phnum;
    // Allocated sections (name, address, size) from the section headers, when present.
    if (eh->e_shoff && eh->e_shentsize == sizeof(Elf64_Shdr) && eh->e_shstrndx < eh->e_shnum &&
        eh->e_shoff + (u64)eh->e_shnum * sizeof(Elf64_Shdr) <= (u64)st.st_size) {
        auto* sh = (const Elf64_Shdr*)(file + eh->e_shoff);
        const Elf64_Shdr& strs = sh[eh->e_shstrndx];
        for (int i = 0; i < eh->e_shnum; i++)
            if ((sh[i].sh_flags & SHF_ALLOC) && sh[i].sh_name < strs.sh_size && strs.sh_offset + strs.sh_size <= (u64)st.st_size)
                lib->sections.push_back({std::string((const char*)file + strs.sh_offset + sh[i].sh_name,
                                                     strnlen((const char*)file + strs.sh_offset + sh[i].sh_name, strs.sh_size - sh[i].sh_name)),
                                         base + sh[i].sh_addr, sh[i].sh_size});
    }
    if (!dyn) fatal("no PT_DYNAMIC");

    const Elf64_Sym* symtab = nullptr;
    const char* strtab = nullptr;
    const Elf64_Rela *rela = nullptr, *jmprel = nullptr;
    u64 relasz = 0, jmprelsz = 0, init_array = 0, init_arraysz = 0, nsyms = 0;
    for (const Elf64_Dyn* d = dyn; d->d_tag != DT_NULL; d++) {
        switch (d->d_tag) {
        case DT_SYMTAB: symtab = (const Elf64_Sym*)(base + d->d_un.d_ptr); break;
        case DT_STRTAB: strtab = (const char*)(base + d->d_un.d_ptr); break;
        case DT_RELA: rela = (const Elf64_Rela*)(base + d->d_un.d_ptr); break;
        case DT_RELASZ: relasz = d->d_un.d_val; break;
        case DT_JMPREL: jmprel = (const Elf64_Rela*)(base + d->d_un.d_ptr); break;
        case DT_PLTRELSZ: jmprelsz = d->d_un.d_val; break;
        case DT_INIT_ARRAY: init_array = base + d->d_un.d_ptr; break;
        case DT_INIT_ARRAYSZ: init_arraysz = d->d_un.d_val; break;
        case DT_INIT: lib->init_fn = base + d->d_un.d_ptr; break;
        case DT_HASH: nsyms = ((const u32*)(base + d->d_un.d_ptr))[1]; break;
        }
    }
    if (!symtab || !strtab || !nsyms) fatal("missing dynamic symbol info");

    // Exports
    lib->exports.reserve(nsyms);
    for (u64 i = 1; i < nsyms; i++) {
        const Elf64_Sym& s = symtab[i];
        if (s.st_shndx == SHN_UNDEF) continue;
        const char* n = strtab + s.st_name;
        lib->exports[n] = {base + s.st_value, s.st_size, (u8)ELF64_ST_TYPE(s.st_info)};
        if (ELF64_ST_TYPE(s.st_info) == STT_FUNC || ELF64_ST_TYPE(s.st_info) == STT_OBJECT)
            lib->sorted_syms.push_back({base + s.st_value, s.st_size, n});
    }
    std::sort(lib->sorted_syms.begin(), lib->sorted_syms.end(), [](auto& a, auto& b) { return a.addr < b.addr; });

    // Import resolution cache per symbol index
    std::vector<u64> resolved(nsyms, ~0ull);
    auto& hle = Hle::get();
    int missing = 0;
    auto resolve = [&](u32 si) -> u64 {
        if (resolved[si] != ~0ull) return resolved[si];
        const Elf64_Sym& s = symtab[si];
        u64 v;
        if (s.st_shndx != SHN_UNDEF) {
            v = base + s.st_value;
        } else {
            std::string n = strtab + s.st_name;
            v = hle.lookup(n);
            if (!v) {
                if (ELF64_ST_BIND(s.st_info) == STB_WEAK) {
                    v = 0;
                } else {
                    LOGD("loader", "unresolved import %s", n.c_str());
                    missing++;
                    v = hle.missing(n);
                }
            }
        }
        resolved[si] = v;
        return v;
    };

    auto apply = [&](const Elf64_Rela* r, u64 sz) {
        for (u64 k = 0; k < sz / sizeof(Elf64_Rela); k++) {
            u64* where = (u64*)(base + r[k].r_offset);
            u32 type = ELF64_R_TYPE(r[k].r_info);
            u32 si = ELF64_R_SYM(r[k].r_info);
            switch (type) {
            case R_AARCH64_RELATIVE: *where = base + r[k].r_addend; break;
            case R_AARCH64_ABS64:
            case R_AARCH64_GLOB_DAT:
            case R_AARCH64_JUMP_SLOT: *where = resolve(si) + r[k].r_addend; break;
            case R_AARCH64_NONE: break;
            default: fatal("unsupported relocation type %u", type);
            }
        }
    };
    apply(rela, relasz);
    apply(jmprel, jmprelsz);
    if (missing) LOGW("loader", "%d imports have no HLE implementation (they abort if called)", missing);

    for (u64 i = 0; i < init_arraysz / 8; i++) {
        u64 f = ((u64*)init_array)[i];
        if (f && f != ~0ull) lib->init_array.push_back(f);
    }
    munmap((void*)file, st.st_size);
    LOGI("loader", "loaded %s at 0x%" PRIx64 " (%" PRIu64 " KiB, %zu init functions)", path.c_str(), base, max_va / 1024, lib->init_array.size());
    g_libs.push_back(lib);
    return lib;
}

LoadedLib* load_library(const std::string& path) {
    LoadedLib* lib = load_image(path);
    if (!g_main) g_main = lib;
    return lib;
}

void run_initializers(LoadedLib& lib) {
    if (lib.init_fn) guest_call(lib.init_fn, {});
    for (u64 f : lib.init_array) guest_call(f, {});
}

}  // namespace soa
