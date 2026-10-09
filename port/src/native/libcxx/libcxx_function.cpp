// std::function's inlined copy constructor and destructor (libcxx_function.h): guest calls through the
// callable's __base vtable, as the game's code makes them.
#include "native/libcxx/libcxx_function.h"

#include "core/cpu.h"

namespace soa::native::libcxx {

namespace {
u64 addr(const void* p) { return reinterpret_cast<u64>(p); }
}  // namespace

u64 function_slot(const function& f, FunctionSlot s) { return reinterpret_cast<u64>(f.f->vtable[s]); }

void function_copy_construct(function* dst, const function& src) {
    if (!src.f) {
        dst->f = nullptr;
    } else if (src.is_inline()) {
        dst->f = reinterpret_cast<function_base*>(dst->buf);
        guest_call(function_slot(src, kFuncSlotCloneInto), {addr(src.f), addr(dst->f)});
    } else {
        dst->f = reinterpret_cast<function_base*>(guest_call(function_slot(src, kFuncSlotClone), {addr(src.f)}));
    }
}

void function_destroy(function* f) {
    if (f->is_inline()) guest_call(function_slot(*f, kFuncSlotDestroy), {addr(f->f)});
    else if (f->f) guest_call(function_slot(*f, kFuncSlotDestroyDeallocate), {addr(f->f)});
}

}  // namespace soa::native::libcxx
