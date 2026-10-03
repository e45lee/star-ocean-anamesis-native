#pragma once
// A tiny fake Java VM: just enough object model for the game's JNI calls.
#include <functional>
#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "core/cpu.h"

namespace soa::jni {

struct Class;

// JNI references, method IDs and field IDs are the host addresses of these objects. ART's are
// indirect references whose low bits carry the reference kind, so a reference's low byte is never
// zero on a phone, and game code relies on it: 3.7.0 LocalKVS::SetBinaryAndroid (ELF 0x1f28474)
// tests the low byte of the java.lang.Boolean *reference* SetSharedPreferences returns. A plain
// 16-aligned heap address has a zero low byte 1 time in 16 (the save then counted as failed:
// null UUID, NoLoginStart never sent, error 1003; emulator/README.md "The lost first request").
// So every object the guest can hold a handle to is allocated through TaggedAlloc, at 8 (mod 16)
// past a 16-aligned block: its address ends in 8, its low byte is never zero. All of them are
// created with `new` (Vm::str / new_array / instance / boolean / integer / find_class, NewObject,
// AllocObject, Method / Field); none is static, embedded or made by make_shared (asserted in the
// tests: jni/references-low-byte). 8-byte alignment is all these types need with libstdc++.
// With libc++ (the Windows build) std::function is 16-aligned (Instance::on_destroy), so there the
// block is 256-aligned and the object at 16 past it: 16-aligned, its low byte 0x10.
struct TaggedAlloc {
#ifdef _LIBCPP_VERSION
    static constexpr size_t kAlign = 256, kTag = 16;
    static void* operator new(size_t n) { return static_cast<char*>(::operator new(n + kAlign, std::align_val_t(kAlign))) + kTag; }
    static void operator delete(void* p) {
        if (p) ::operator delete(static_cast<char*>(p) - kTag, std::align_val_t(kAlign));
    }
#else
    static constexpr size_t kAlign = 16, kTag = 8;
    static void* operator new(size_t n) { return static_cast<char*>(::operator new(n + 16)) + kTag; }
    static void operator delete(void* p) {
        if (p) ::operator delete(static_cast<char*>(p) - kTag);
    }
#endif
    static void* operator new[](size_t) = delete;  // the offset trick isn't wired for arrays
    static void operator delete[](void*) = delete;
};

struct Object : TaggedAlloc {
    Class* cls = nullptr;
    virtual ~Object() = default;
};

struct String : Object {
    std::string utf8;  // modified UTF-8 is treated as plain UTF-8
    std::u16string utf16() const;
};

struct Array : Object {
    char elem = 'B';  // JNI signature char of the element type ('L' for objects)
    size_t length = 0;
    std::vector<u8> data;        // primitive arrays
    std::vector<Object*> objs;   // object arrays
    size_t elem_size() const;
};

// Instance of a class with arbitrary host-side state.
struct Instance : Object {
    std::map<std::string, u64> fields;
    std::function<void()> on_destroy;
    u64 value = 0;  // boxed primitive value (java/lang/Boolean, Integer)
};

// Method/field IDs
using Args = std::vector<u64>;  // raw jvalue bits in signature order
using Impl = std::function<u64(Object* self, const Args& args)>;
// An override (Vm::override_method) gets the implementation it replaces (empty when there was
// none), to delegate to.
using Override = std::function<u64(Object* self, const Args& args, const Impl& original)>;

struct Method : TaggedAlloc {  // jmethodID
    Class* cls;
    std::string name, sig;
    bool is_static;
    Impl impl;
    std::vector<char> params;  // one char per parameter ('L' for refs)
    char ret;
};

struct Field : TaggedAlloc {  // jfieldID
    Class* cls;
    std::string name, sig;
    bool is_static;
    u64 static_value = 0;
};

struct Class : Object {
    std::string name;  // slash form: java/lang/String
    Class* super = nullptr;
    std::map<std::string, Method*> methods;  // key: name + sig
    std::map<std::string, Field*> fields;    // key: name
};

class Vm {
public:
    static Vm& get();

    Class* find_class(const std::string& name, bool create = true);
    Class* define_class(const std::string& name, const std::string& super = "java/lang/Object");
    Method* def(const std::string& cls, const std::string& name, const std::string& sig, Impl impl, bool is_static = false);
    Method* find_method(Class* c, const std::string& name, const std::string& sig, bool is_static);
    // Extension point: replaces the implementation of cls.name+sig (defining the method, and the
    // class, when they don't exist). `fn` receives the implementation it replaces: the one `cls`
    // or its nearest superclass had, or an empty Impl. Method IDs the game already holds stay
    // valid (the Method object of `cls` is reused), so this also works after the game started;
    // override a method on the class that defines it, since IDs resolved through a subclass point
    // at the superclass's Method.
    Method* override_method(const std::string& cls, const std::string& name, const std::string& sig, Override fn, bool is_static = false);
    Field* find_field(Class* c, const std::string& name, const std::string& sig, bool is_static);

    String* str(const std::string& s);
    Array* byte_array(const void* data, size_t n);
    Array* new_array(char elem, size_t n, Class* elem_cls = nullptr);
    Instance* boolean(bool v);
    Instance* integer(int v);
    Instance* instance(const std::string& cls);

    u64 vm_ptr() const { return (u64)&vm_; }
    u64 env_ptr() const { return (u64)&env_; }

    // The activity object (activity->clazz).
    Instance* activity = nullptr;

    void init();

private:
    std::recursive_mutex m_;
    std::map<std::string, Class*> classes_;
    u64 env_ = 0;  // JNIEnv: pointer to function table
    u64 vm_ = 0;   // JavaVM: pointer to invoke table
    std::vector<u64> env_table_, vm_table_;
};

inline std::string jstr(u64 ref) { return ref ? ((String*)ref)->utf8 : std::string(); }
std::vector<char> parse_params(const std::string& sig, char& ret);

// Defined in java_*.cpp
void install_android_classes(Vm& vm);
void install_playcore_classes(Vm& vm);

// Extension point: `fn` runs at the end of Vm::init(), after the built-in classes (java_*.cpp),
// in registration order. Host programs use it to add classes and methods (Vm::define_class /
// Vm::def) or replace built-in ones (Vm::override_method) before the game sees them. Register
// before Vm::init(), e.g. from a static initializer; returns true.
bool add_class_installer(std::function<void(Vm&)> fn);

}  // namespace soa::jni
