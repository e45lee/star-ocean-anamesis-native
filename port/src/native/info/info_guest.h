#pragma once
// The guest functions and constants the info natives call or pass on (internal to the subsystem).
#include <initializer_list>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/info/info_layout.h"

namespace soa::native::info::g {

inline u64 at(u64 vaddr) { return main_lib()->base + vaddr; }
u64 sym(const char* mangled);  // fatal when missing; callers cache it

// Framework::gDoAssert(file, line, message) (vaddrs; logs, and the caller carries on as the guest does).
void Assert(u64 file_vaddr, int line, u64 msg_vaddr);
// Slot `slot` of the object's guest vtable, and a call of it with the object as `this`.
inline u64 slot_of(const void* obj, u32 slot) { return reinterpret_cast<const u64*>(*reinterpret_cast<const u64*>(obj))[slot]; }
u64 vcall(const void* obj, u32 slot, std::initializer_list<u64> rest);

}  // namespace soa::native::info::g
