// The live check of the render natives: the family (render_check.h).
#include "native/render/render_check.h"

#include <cstring>
#include <vector>

#include "hle/gl_host.h"

namespace soa::native::render {

live::RunBothFamily& fam() {
    static live::RunBothFamily f("render", 1);
    return f;
}

}  // namespace soa::native::render

namespace soa::native::render {

std::string gl_run_both(std::initializer_list<std::pair<void*, size_t>> regions, const std::function<void()>& guest,
                        const std::function<void()>& native) {
    std::vector<std::vector<u8>> pre, after_guest;
    for (auto& [p, n] : regions) pre.emplace_back((u8*)p, (u8*)p + n);
    auto restore = [&] {
        size_t k = 0;
        for (auto& [p, n] : regions) std::memcpy(p, pre[k++].data(), n);
    };
    glh::Recorder rg, rn;
    glh::Recorder* outer = glh::t_rec;
    glh::t_rec = &rg;
    guest();
    glh::t_rec = outer;
    for (auto& [p, n] : regions) after_guest.emplace_back((u8*)p, (u8*)p + n);
    restore();
    glh::t_rec = &rn;
    native();
    glh::t_rec = outer;
    std::string why;
    size_t k = 0;
    for (auto& [p, n] : regions) {
        if (why.empty()) {
            std::string d = live::RunBothFamily::diff_bytes(p, after_guest[k].data(), n);
            if (!d.empty()) why = "region " + std::to_string(k) + " " + d;
        }
        k++;
    }
    if (why.empty() && rg.calls != rn.calls) {
        size_t i = 0;
        while (i < rg.calls.size() && i < rn.calls.size() && rg.calls[i] == rn.calls[i]) i++;
        why = "GL call " + std::to_string(i) + ": native " + (i < rn.calls.size() ? rn.calls[i] : std::string("(none)")) + ", guest " +
              (i < rg.calls.size() ? rg.calls[i] : std::string("(none)")) + " (" + std::to_string(rn.calls.size()) + " / " +
              std::to_string(rg.calls.size()) + " calls)";
    }
    restore();
    return why;
}

}  // namespace soa::native::render
