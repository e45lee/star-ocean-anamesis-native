#include "soaruntime/core/loader.h"

#include <cxxabi.h>
#include "core/elf64.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <cinttypes>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <functional>
#include <unordered_map>

#include "soaruntime/core/hle.h"
#include "soaruntime/core/host_mem.h"
#include "soaruntime/core/log.h"

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

namespace {

// What load_image holds until the image is good: the file mapping and the image's memory are
// released on every failure, so a bad --lib is an error the host reports, not a leak or an abort.
struct ImageLoad {
    const std::string& path;
    std::string* error;
    hostmem::MappedFile mf;
    void* mem = nullptr;
    u64 mem_size = 0;
    LoadedLib* lib = nullptr;

    ~ImageLoad() {
        if (mf.data) hostmem::unmap_file(mf);
        if (lib) delete lib;  // still set only on failure
        if (mem) hostmem::unmap(mem, mem_size);
    }
    LoadedLib* fail(const char* fmt, ...) __attribute__((format(printf, 2, 3))) {
        char buf[512];
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(buf, sizeof buf, fmt, ap);
        va_end(ap);
        std::string msg = path + ": " + buf;
        LOGE("loader", "%s", msg.c_str());
        if (error) *error = msg;
        return nullptr;
    }
};

// [off, off + len) inside a buffer of `size` bytes, without overflow.
bool in_range(u64 off, u64 len, u64 size) { return off <= size && len <= size - off; }

}  // namespace

static LoadedLib* load_image(const std::string& path, std::string* error) {
    ImageLoad L{path, error};
    if (!hostmem::map_file(path, &L.mf)) return L.fail("cannot open or map the file");
    const u8* file = L.mf.data;
    const u64 file_size = L.mf.size;

    if (file_size < sizeof(Elf64_Ehdr)) return L.fail("not an ELF file (%" PRIu64 " bytes)", file_size);
    auto* eh = (const Elf64_Ehdr*)file;
    if (memcmp(eh->e_ident, ELFMAG, SELFMAG) != 0) return L.fail("not an ELF file");
    if (eh->e_ident[EI_CLASS] != ELFCLASS64 || eh->e_machine != EM_AARCH64)
        return L.fail("not an AArch64 (64-bit ARM) ELF (machine %u): the game's libSOA.so is lib/arm64-v8a's", (unsigned)eh->e_machine);
    if (eh->e_phentsize != sizeof(Elf64_Phdr) || !in_range(eh->e_phoff, (u64)eh->e_phnum * sizeof(Elf64_Phdr), file_size))
        return L.fail("truncated: the program headers are outside the file");
    auto* ph = (const Elf64_Phdr*)(file + eh->e_phoff);

    u64 max_va = 0;
    for (int i = 0; i < eh->e_phnum; i++) {
        if (ph[i].p_type != PT_LOAD) continue;
        if (!in_range(ph[i].p_offset, ph[i].p_filesz, file_size)) return L.fail("truncated: segment %d is outside the file", i);
        if (ph[i].p_filesz > ph[i].p_memsz || ph[i].p_vaddr + ph[i].p_memsz < ph[i].p_vaddr || ph[i].p_vaddr + ph[i].p_memsz > (1ull << 40))
            return L.fail("segment %d has a bad size or address", i);
        max_va = std::max<u64>(max_va, ph[i].p_vaddr + ph[i].p_memsz);
    }
    if (!max_va) return L.fail("no loadable segment");
    max_va = (max_va + 0xffff) & ~0xffffull;

    L.mem = hostmem::map_rw(max_va);
    if (!L.mem) return L.fail("mapping %" PRIu64 " bytes for the image failed", max_va);
    L.mem_size = max_va;
    u64 base = (u64)L.mem;

    auto* lib = L.lib = new LoadedLib();
    lib->path = path;
    lib->base = base;
    lib->size = max_va;
    const Elf64_Dyn* dyn = nullptr;
    u64 dyn_size = 0;
    for (int i = 0; i < eh->e_phnum; i++) {
        if (ph[i].p_type == PT_LOAD) memcpy((void*)(base + ph[i].p_vaddr), file + ph[i].p_offset, ph[i].p_filesz);
        if (ph[i].p_type == PT_DYNAMIC) {
            if (!in_range(ph[i].p_vaddr, ph[i].p_memsz, max_va)) return L.fail("PT_DYNAMIC is outside the image");
            dyn = (const Elf64_Dyn*)(base + ph[i].p_vaddr);
            dyn_size = ph[i].p_memsz;
        }
        if (ph[i].p_type == PT_GNU_EH_FRAME) lib->eh_frame_hdr = base + ph[i].p_vaddr;
        if (ph[i].p_type == PT_LOAD && ph[i].p_offset == 0) lib->phdr = base + ph[i].p_vaddr + eh->e_phoff;
    }
    lib->phnum = eh->e_phnum;
    // Allocated sections (name, address, size) from the section headers, when present.
    if (eh->e_shoff && eh->e_shentsize == sizeof(Elf64_Shdr) && eh->e_shstrndx < eh->e_shnum &&
        eh->e_shoff + (u64)eh->e_shnum * sizeof(Elf64_Shdr) <= file_size) {
        auto* sh = (const Elf64_Shdr*)(file + eh->e_shoff);
        const Elf64_Shdr& strs = sh[eh->e_shstrndx];
        for (int i = 0; i < eh->e_shnum; i++)
            if ((sh[i].sh_flags & SHF_ALLOC) && sh[i].sh_name < strs.sh_size && strs.sh_offset + strs.sh_size <= file_size)
                lib->sections.push_back({std::string((const char*)file + strs.sh_offset + sh[i].sh_name,
                                                     strnlen((const char*)file + strs.sh_offset + sh[i].sh_name, strs.sh_size - sh[i].sh_name)),
                                         base + sh[i].sh_addr, sh[i].sh_size});
    }
    if (!dyn) return L.fail("no PT_DYNAMIC: not a shared library");

    const Elf64_Sym* symtab = nullptr;
    const char* strtab = nullptr;
    const Elf64_Rela *rela = nullptr, *jmprel = nullptr;
    u64 relasz = 0, jmprelsz = 0, init_array = 0, init_arraysz = 0, nsyms = 0;
    u64 symtab_off = 0, strtab_off = 0, rela_off = 0, jmprel_off = 0, init_array_off = 0;
    bool dyn_end = false;
    for (u64 k = 0; k < dyn_size / sizeof(Elf64_Dyn); k++) {
        const Elf64_Dyn* d = dyn + k;
        if (d->d_tag == DT_NULL) {
            dyn_end = true;
            break;
        }
        const u64 v = d->d_un.d_val;
        switch (d->d_tag) {
        case DT_SYMTAB: symtab_off = v; symtab = (const Elf64_Sym*)(base + v); break;
        case DT_STRTAB: strtab_off = v; strtab = (const char*)(base + v); break;
        case DT_RELA: rela_off = v; rela = (const Elf64_Rela*)(base + v); break;
        case DT_RELASZ: relasz = v; break;
        case DT_JMPREL: jmprel_off = v; jmprel = (const Elf64_Rela*)(base + v); break;
        case DT_PLTRELSZ: jmprelsz = v; break;
        case DT_INIT_ARRAY: init_array_off = v; init_array = base + v; break;
        case DT_INIT_ARRAYSZ: init_arraysz = v; break;
        case DT_INIT: lib->init_fn = base + v; break;
        case DT_HASH:
            if (!in_range(v, 8, max_va)) return L.fail("DT_HASH is outside the image");
            nsyms = ((const u32*)(base + v))[1];
            break;
        }
    }
    if (!dyn_end) return L.fail("PT_DYNAMIC has no DT_NULL end");
    if (!symtab || !strtab || !nsyms) return L.fail("missing dynamic symbol info (DT_SYMTAB, DT_STRTAB, DT_HASH)");
    if (!in_range(symtab_off, nsyms * sizeof(Elf64_Sym), max_va) || strtab_off >= max_va ||
        (rela && !in_range(rela_off, relasz, max_va)) || (jmprel && !in_range(jmprel_off, jmprelsz, max_va)) ||
        (init_array && !in_range(init_array_off, init_arraysz, max_va)))
        return L.fail("a dynamic table is outside the image");

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

    // Returns the first unsupported relocation type, or 0.
    auto apply = [&](const Elf64_Rela* r, u64 sz) -> u32 {
        for (u64 k = 0; k < sz / sizeof(Elf64_Rela); k++) {
            u32 type = ELF64_R_TYPE(r[k].r_info);
            u32 si = ELF64_R_SYM(r[k].r_info);
            if (type != R_AARCH64_NONE && !in_range(r[k].r_offset, 8, max_va)) return type;
            u64* where = (u64*)(base + r[k].r_offset);
            switch (type) {
            case R_AARCH64_RELATIVE: *where = base + r[k].r_addend; break;
            case R_AARCH64_ABS64:
            case R_AARCH64_GLOB_DAT:
            case R_AARCH64_JUMP_SLOT:
                if (si >= nsyms) return type;
                *where = resolve(si) + r[k].r_addend;
                break;
            case R_AARCH64_NONE: break;
            default: return type;
            }
        }
        return 0;
    };
    if (u32 t = apply(rela, relasz)) return L.fail("unsupported or bad relocation (type %u)", t);
    if (u32 t = apply(jmprel, jmprelsz)) return L.fail("unsupported or bad relocation (type %u)", t);
    if (missing) LOGW("loader", "%d imports have no HLE implementation (they abort if called)", missing);

    for (u64 i = 0; i < init_arraysz / 8; i++) {
        u64 f = ((u64*)init_array)[i];
        if (f && f != ~0ull) lib->init_array.push_back(f);
    }
    LOGI("loader", "loaded %s at 0x%" PRIx64 " (%" PRIu64 " KiB, %zu init functions)", path.c_str(), base, max_va / 1024, lib->init_array.size());
    g_libs.push_back(lib);
    L.lib = nullptr, L.mem = nullptr;  // the image is the program's now
    return lib;
}

LoadedLib* load_library(const std::string& path, std::string* error) {
    LoadedLib* lib = load_image(path, error);
    if (lib && !g_main) g_main = lib;
    return lib;
}

void run_initializers(LoadedLib& lib) {
    if (lib.init_fn) guest_call(lib.init_fn, {});
    for (u64 f : lib.init_array) guest_call(f, {});
}

}  // namespace soa
