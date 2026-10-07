// JNIEnv / JavaVM function tables backed by the fake VM in jvm.h.
#include "jni/jvm.h"

#include <cinttypes>
#include <cstring>
#include <mutex>
#include <set>
#include <unordered_map>

#include "core/abi.h"
#include "core/log.h"
#include "hle/format.h"
#include "jni/jni_names.h"

namespace soa::jni {

// ===========================================================================
// Object model

std::u16string String::utf16() const {
    std::u16string out;
    const auto* s = (const unsigned char*)utf8.data();
    size_t n = utf8.size();
    for (size_t i = 0; i < n;) {
        u32 cp;
        unsigned char c = s[i];
        if (c < 0x80) cp = c, i += 1;
        else if ((c >> 5) == 6 && i + 1 < n) cp = ((c & 0x1f) << 6) | (s[i + 1] & 0x3f), i += 2;
        else if ((c >> 4) == 14 && i + 2 < n) cp = ((c & 0x0f) << 12) | ((s[i + 1] & 0x3f) << 6) | (s[i + 2] & 0x3f), i += 3;
        else if ((c >> 3) == 30 && i + 3 < n) cp = ((c & 0x07) << 18) | ((s[i + 1] & 0x3f) << 12) | ((s[i + 2] & 0x3f) << 6) | (s[i + 3] & 0x3f), i += 4;
        else cp = 0xfffd, i += 1;
        if (cp >= 0x10000) {
            cp -= 0x10000;
            out.push_back((char16_t)(0xd800 + (cp >> 10)));
            out.push_back((char16_t)(0xdc00 + (cp & 0x3ff)));
        } else {
            out.push_back((char16_t)cp);
        }
    }
    return out;
}

static std::string utf16_to_utf8(const char16_t* s, size_t n) {
    std::string out;
    for (size_t i = 0; i < n; i++) {
        u32 cp = s[i];
        if (cp >= 0xd800 && cp < 0xdc00 && i + 1 < n && s[i + 1] >= 0xdc00 && s[i + 1] < 0xe000) {
            cp = 0x10000 + ((cp - 0xd800) << 10) + (s[i + 1] - 0xdc00);
            i++;
        }
        if (cp < 0x80) out.push_back((char)cp);
        else if (cp < 0x800) out.push_back((char)(0xc0 | (cp >> 6))), out.push_back((char)(0x80 | (cp & 0x3f)));
        else if (cp < 0x10000)
            out.push_back((char)(0xe0 | (cp >> 12))), out.push_back((char)(0x80 | ((cp >> 6) & 0x3f))), out.push_back((char)(0x80 | (cp & 0x3f)));
        else
            out.push_back((char)(0xf0 | (cp >> 18))), out.push_back((char)(0x80 | ((cp >> 12) & 0x3f))), out.push_back((char)(0x80 | ((cp >> 6) & 0x3f))),
                out.push_back((char)(0x80 | (cp & 0x3f)));
    }
    return out;
}

size_t Array::elem_size() const {
    switch (elem) {
    case 'Z':
    case 'B': return 1;
    case 'C':
    case 'S': return 2;
    case 'I':
    case 'F': return 4;
    default: return 8;
    }
}

std::vector<char> parse_params(const std::string& sig, char& ret) {
    std::vector<char> out;
    size_t i = sig.find('(') + 1;
    while (i < sig.size() && sig[i] != ')') {
        char c = sig[i];
        if (c == '[') {
            while (sig[i] == '[') i++;
            if (sig[i] == 'L') i = sig.find(';', i);
            out.push_back('L');
        } else if (c == 'L') {
            i = sig.find(';', i);
            out.push_back('L');
        } else {
            out.push_back(c);
        }
        i++;
    }
    char r = i + 1 < sig.size() ? sig[i + 1] : 'V';
    ret = (r == '[') ? 'L' : r;
    return out;
}

Vm& Vm::get() {
    static Vm vm;
    return vm;
}

Class* Vm::find_class(const std::string& name_in, bool create) {
    std::string name = name_in;
    for (auto& ch : name)
        if (ch == '.') ch = '/';
    std::lock_guard lk(m_);
    auto it = classes_.find(name);
    if (it != classes_.end()) return it->second;
    if (!create) return nullptr;
    auto* c = new Class();
    c->name = name;
    auto jl = classes_.find("java/lang/Class");
    c->cls = jl != classes_.end() ? jl->second : nullptr;
    if (name != "java/lang/Object") c->super = find_class("java/lang/Object");
    classes_[name] = c;
    return c;
}

Class* Vm::define_class(const std::string& name, const std::string& super) {
    Class* c = find_class(name);
    if (!super.empty() && name != "java/lang/Object") c->super = find_class(super);
    return c;
}

Method* Vm::def(const std::string& cls, const std::string& name, const std::string& sig, Impl impl, bool is_static) {
    Class* c = find_class(cls);
    std::lock_guard lk(m_);
    auto*& m = c->methods[name + sig];
    if (!m) {
        // (an existing Method -- find_method's placeholder, or one defined before -- has these
        // already, from the same key; other threads may be reading them)
        auto* n = new Method();
        n->cls = c;
        n->name = name;
        n->sig = sig;
        n->is_static = is_static;
        n->params = parse_params(sig, n->ret);
        m = n;
    }
    m->impl = std::move(impl);
    return m;
}

Method* Vm::override_method(const std::string& cls, const std::string& name, const std::string& sig, Override fn, bool is_static) {
    Class* c = find_class(cls);
    Impl original;
    std::lock_guard lk(m_);  // (recursive: def takes it too; no other override in between)
    for (Class* k = c; k; k = k->super) {
        auto it = k->methods.find(name + sig);
        if (it != k->methods.end()) {
            original = it->second->impl.get();
            break;
        }
    }
    return def(cls, name, sig, [fn = std::move(fn), original](Object* self, const Args& a) -> u64 { return fn(self, a, original); }, is_static);
}

namespace {
std::vector<std::function<void(Vm&)>>& class_installers() {
    static std::vector<std::function<void(Vm&)>> v;
    return v;
}
}  // namespace

bool add_class_installer(std::function<void(Vm&)> fn) {
    class_installers().push_back(std::move(fn));
    return true;
}

Method* Vm::find_method(Class* c, const std::string& name, const std::string& sig, bool is_static) {
    std::lock_guard lk(m_);
    for (Class* k = c; k; k = k->super) {
        auto it = k->methods.find(name + sig);
        if (it != k->methods.end()) return it->second;
    }
    // Unknown: create a placeholder so the game gets a valid ID; calls log a warning.
    LOGW("jni", "unknown method %s.%s%s", c ? c->name.c_str() : "?", name.c_str(), sig.c_str());
    auto* m = new Method();
    m->cls = c;
    m->name = name;
    m->sig = sig;
    m->is_static = is_static;
    m->params = parse_params(sig, m->ret);
    if (c) c->methods[name + sig] = m;
    return m;
}

Method* Vm::resolve_virtual(Method* m, Class* actual) {
    if (!m || !actual || m->cls == actual) return m;
    std::string key = m->name + m->sig;
    std::lock_guard lk(m_);
    for (Class* k = actual; k && k != m->cls; k = k->super) {
        auto it = k->methods.find(key);
        if (it != k->methods.end() && it->second->impl) return it->second;
    }
    return m;
}

Field* Vm::find_field(Class* c, const std::string& name, const std::string& sig, bool is_static) {
    std::lock_guard lk(m_);
    for (Class* k = c; k; k = k->super) {
        auto it = k->fields.find(name);
        if (it != k->fields.end()) return it->second;
    }
    LOGW("jni", "unknown field %s.%s (%s)", c ? c->name.c_str() : "?", name.c_str(), sig.c_str());
    auto* f = new Field{{}, c, name, sig, is_static};
    if (c) c->fields[name] = f;
    return f;
}

String* Vm::str(const std::string& s) {
    auto* o = new String();
    o->cls = find_class("java/lang/String");
    o->utf8 = s;
    return o;
}

Array* Vm::new_array(char elem, size_t n, Class* elem_cls) {
    auto* a = new Array();
    a->elem = elem;
    a->length = n;
    std::string cn = std::string("[") + (elem == 'L' ? "L" + (elem_cls ? elem_cls->name : std::string("java/lang/Object")) + ";" : std::string(1, elem));
    a->cls = find_class(cn);
    if (elem == 'L') a->objs.assign(n, nullptr);
    else a->data.assign(n * a->elem_size(), 0);
    return a;
}

Array* Vm::byte_array(const void* data, size_t n) {
    Array* a = new_array('B', n);
    if (n) memcpy(a->data.data(), data, n);
    return a;
}

Instance* Vm::instance(const std::string& cls) {
    auto* o = new Instance();
    o->cls = find_class(cls);
    return o;
}

Instance* Vm::boolean(bool v) {
    auto* o = instance("java/lang/Boolean");
    o->value = v;
    return o;
}

Instance* Vm::integer(int v) {
    auto* o = instance("java/lang/Integer");
    o->value = (u32)v;
    return o;
}

// ===========================================================================
// JNIEnv thunks

namespace {

Vm& vm() { return Vm::get(); }
Object* obj(u64 r) { return (Object*)r; }

std::unordered_map<std::string, HostFn>& impls() {
    static std::unordered_map<std::string, HostFn> m;
    return m;
}

void unimplemented_jni(Cpu& c) {
    const char* n = thunk_name_at(c.pc() - 4);
    LOGE("jni", "unimplemented JNIEnv function %s", n ? n : "?");
    dump_guest_state(c);
    fatal("unimplemented JNI function");
}

bool is_instance_of(Object* o, Class* c) {
    if (!o || !c) return false;
    for (Class* k = o->cls; k; k = k->super)
        if (k == c) return true;
    return c->name == "java/lang/Object";
}

// ---- argument decoding ----
Args read_args(Method* m, VaSource& va) {
    Args a;
    for (char p : m->params) {
        switch (p) {
        case 'F': {
            float f = (float)va.next_double();
            u32 b;
            memcpy(&b, &f, 4);
            a.push_back(b);
            break;
        }
        case 'D': {
            double d = va.next_double();
            u64 b;
            memcpy(&b, &d, 8);
            a.push_back(b);
            break;
        }
        case 'J':
        case 'L': a.push_back(va.next_int()); break;
        case 'Z': a.push_back(va.next_int() & 0xff); break;
        case 'B': a.push_back((u64)(s64)(signed char)va.next_int()); break;
        case 'C': a.push_back(va.next_int() & 0xffff); break;
        case 'S': a.push_back((u64)(s64)(short)va.next_int()); break;
        default: a.push_back((u64)(s64)(s32)va.next_int()); break;
        }
    }
    return a;
}
Args read_args_a(Method* m, u64 jv) {
    Args a;
    const u64* v = (const u64*)jv;
    for (size_t i = 0; i < m->params.size(); i++) {
        u64 raw = v[i];
        switch (m->params[i]) {
        case 'Z': a.push_back(raw & 0xff); break;
        case 'B': a.push_back((u64)(s64)(signed char)raw); break;
        case 'C': a.push_back(raw & 0xffff); break;
        case 'S': a.push_back((u64)(s64)(short)raw); break;
        case 'I':
        case 'F': a.push_back(raw & 0xffffffff); break;
        default: a.push_back(raw); break;
        }
    }
    return a;
}

// True the first time it is called for `m` (a warning logged once per method, from any thread).
bool warn_once(Method* m) {
    static std::mutex mu;
    static std::set<Method*> warned;
    std::lock_guard lk(mu);
    return warned.insert(m).second;
}

u64 invoke(Method* m, Object* self, const Args& args) {
    if (!m) {
        LOGE("jni", "call with null methodID");
        return 0;
    }
    if (!m->impl) {
        if (warn_once(m))
            LOGW("jni", "call to unimplemented %s.%s%s", m->cls ? m->cls->name.c_str() : "?", m->name.c_str(), m->sig.c_str());
        return 0;
    }
    LOGT("jni", "call %s.%s%s", m->cls ? m->cls->name.c_str() : "?", m->name.c_str(), m->sig.c_str());
    return m->impl(self, args);
}

void set_ret(Cpu& c, char t, u64 v) {
    switch (t) {
    case 'F': c.set_v(0, {v & 0xffffffff, 0}); break;
    case 'D': c.set_v(0, {v, 0}); break;
    case 'V': break;
    case 'Z': c.set_x(0, v & 0xff); break;
    case 'B': c.set_x(0, (u64)(s64)(signed char)v); break;
    case 'C': c.set_x(0, v & 0xffff); break;
    case 'S': c.set_x(0, (u64)(s64)(short)v); break;
    case 'I': c.set_x(0, (u64)(s64)(s32)v); break;
    default: c.set_x(0, v); break;
    }
}

// Kind: 0 = Call<T>Method(env, obj, mid, ...), 1 = CallNonvirtual (env, obj, cls, mid, ...),
//       2 = CallStatic (env, cls, mid, ...), 3 = NewObject (env, cls, mid, ...)
// Mode: 0 = varargs, 1 = va_list, 2 = jvalue*
template <int Kind, int Mode, char T>
void call_thunk(Cpu& c) {
    int mid_reg = Kind == 1 ? 3 : 2;
    Method* m = (Method*)c.x(mid_reg);
    Object* self = nullptr;
    Instance* created = nullptr;
    if (Kind == 0 || Kind == 1) self = obj(c.x(1));
    if (Kind == 3) {
        Class* cls = (Class*)c.x(1);
        created = new Instance();
        created->cls = cls;
        self = created;
    }
    if (!m) {
        LOGE("jni", "Call with null methodID");
        set_ret(c, T, 0);
        return;
    }
    Args args;
    if (Mode == 0) {
        RegVa va(c, mid_reg + 1, 0);
        args = read_args(m, va);
    } else if (Mode == 1) {
        GuestVaList va(c.x(mid_reg + 1));
        args = read_args(m, va);
    } else {
        args = read_args_a(m, c.x(mid_reg + 1));
    }
    // Virtual dispatch: resolve the method on the object's actual class.
    if (Kind == 0 && self && self->cls && m->cls != self->cls) m = vm().resolve_virtual(m, self->cls);
    u64 r = invoke(m, self, args);
    if (Kind == 3) r = (u64)created;
    if constexpr (T == 'L') {
        // Every reference has a non-zero low byte (TaggedAlloc in jvm.h); a method that returns
        // something else (e.g. a host override returning a pointer it didn't get from the Vm)
        // would bring back the 1-in-16 failure of the guest's low-byte tests. Warn once per method.
        if (r && !(r & 0xff)) {
            if (warn_once(m))
                LOGW("jni", "%s.%s%s returned a reference with a zero low byte (%#" PRIx64 "): not a Vm object?", m->cls ? m->cls->name.c_str() : "?",
                     m->name.c_str(), m->sig.c_str(), r);
        }
    }
    set_ret(c, T, r);
}

// ---- fields ----
template <char T>
void get_field(Cpu& c) {
    auto* f = (Field*)c.x(2);
    auto* o = (Instance*)c.x(1);
    u64 v = 0;
    if (f && o) {
        auto it = o->fields.find(f->name);
        if (it != o->fields.end()) v = it->second;
    }
    set_ret(c, T, v);
}
template <char T>
void get_static_field(Cpu& c) {
    auto* f = (Field*)c.x(2);
    set_ret(c, T, f ? f->static_value : 0);
}
template <char T>
u64 field_value_arg(Cpu& c) {
    if (T == 'F') return c.v(0).lo & 0xffffffff;
    if (T == 'D') return c.v(0).lo;
    return c.x(3);
}
template <char T>
void set_field(Cpu& c) {
    auto* f = (Field*)c.x(2);
    auto* o = (Instance*)c.x(1);
    if (f && o) o->fields[f->name] = field_value_arg<T>(c);
}
template <char T>
void set_static_field(Cpu& c) {
    auto* f = (Field*)c.x(2);
    if (f) f->static_value = field_value_arg<T>(c);
}

// ---- arrays ----
template <char T>
void new_array(Cpu& c) { ret_ptr(c, vm().new_array(T, (size_t)(s32)c.x(1))); }
template <char T>
void get_array_elements(Cpu& c) {
    auto* a = (Array*)c.x(1);
    if (c.x(2)) *(u8*)c.x(2) = 0;
    ret_ptr(c, a ? a->data.data() : nullptr);
}
void release_array_elements(Cpu& c) {}
template <char T>
void get_array_region(Cpu& c) {
    auto* a = (Array*)c.x(1);
    size_t es = a->elem_size(), start = (size_t)(s32)c.x(2), len = (size_t)(s32)c.x(3);
    if (start + len > a->length) {
        LOGE("jni", "Get%cArrayRegion out of bounds", T);
        return;
    }
    memcpy((void*)c.x(4), a->data.data() + start * es, len * es);
}
template <char T>
void set_array_region(Cpu& c) {
    auto* a = (Array*)c.x(1);
    size_t es = a->elem_size(), start = (size_t)(s32)c.x(2), len = (size_t)(s32)c.x(3);
    if (start + len > a->length) {
        LOGE("jni", "Set%cArrayRegion out of bounds", T);
        return;
    }
    memcpy(a->data.data() + start * es, (const void*)c.x(4), len * es);
}

// ---- misc ----
void j_GetVersion(Cpu& c) { ret(c, 0x10006); }
void j_FindClass(Cpu& c) {
    const char* n = arg_str(c, 1);
    Class* k = vm().find_class(n, false);
    if (!k) {
        LOGD("jni", "FindClass(%s): creating empty class", n);
        k = vm().find_class(n);
    }
    ret_ptr(c, k);
}
void j_GetSuperclass(Cpu& c) { ret_ptr(c, ((Class*)c.x(1))->super); }
void j_IsAssignableFrom(Cpu& c) {
    Class* a = (Class*)c.x(1);
    Class* b = (Class*)c.x(2);
    bool r = false;
    for (Class* k = a; k; k = k->super)
        if (k == b) r = true;
    ret(c, r);
}
void j_Throw(Cpu& c) {
    LOGW("jni", "Throw()");
    ret(c, 0);
}
void j_ThrowNew(Cpu& c) {
    LOGW("jni", "ThrowNew(%s, %s)", ((Class*)c.x(1))->name.c_str(), arg_str(c, 2));
    ret(c, 0);
}
void j_ret0(Cpu& c) { ret(c, 0); }
void j_ret_arg1(Cpu& c) { ret(c, c.x(1)); }
void j_FatalError(Cpu& c) { fatal("JNI FatalError: %s", arg_str(c, 1)); }
void j_IsSameObject(Cpu& c) { ret(c, c.x(1) == c.x(2)); }
void j_GetObjectClass(Cpu& c) { ret_ptr(c, c.x(1) ? obj(c.x(1))->cls : nullptr); }
void j_IsInstanceOf(Cpu& c) { ret(c, is_instance_of(obj(c.x(1)), (Class*)c.x(2))); }
void j_GetObjectRefType(Cpu& c) { ret(c, 1); }

void j_GetMethodID(Cpu& c) { ret_ptr(c, vm().find_method((Class*)c.x(1), arg_str(c, 2), arg_str(c, 3), false)); }
void j_GetStaticMethodID(Cpu& c) { ret_ptr(c, vm().find_method((Class*)c.x(1), arg_str(c, 2), arg_str(c, 3), true)); }
void j_GetFieldID(Cpu& c) { ret_ptr(c, vm().find_field((Class*)c.x(1), arg_str(c, 2), arg_str(c, 3), false)); }
void j_GetStaticFieldID(Cpu& c) { ret_ptr(c, vm().find_field((Class*)c.x(1), arg_str(c, 2), arg_str(c, 3), true)); }

// ---- strings ----
void j_NewStringUTF(Cpu& c) { ret_ptr(c, c.x(1) ? vm().str(arg_str(c, 1)) : nullptr); }
void j_NewString(Cpu& c) { ret_ptr(c, vm().str(utf16_to_utf8((const char16_t*)c.x(1), (size_t)(s32)c.x(2)))); }
void j_GetStringUTFChars(Cpu& c) {
    if (c.x(2)) *(u8*)c.x(2) = 1;
    auto* s = (String*)c.x(1);
    ret_ptr(c, strdup(s ? s->utf8.c_str() : ""));
}
void j_ReleaseStringUTFChars(Cpu& c) { free((void*)c.x(2)); }
void j_GetStringUTFLength(Cpu& c) { ret(c, c.x(1) ? ((String*)c.x(1))->utf8.size() : 0); }
void j_GetStringLength(Cpu& c) { ret(c, c.x(1) ? ((String*)c.x(1))->utf16().size() : 0); }
void j_GetStringChars(Cpu& c) {
    if (c.x(2)) *(u8*)c.x(2) = 1;
    auto u = ((String*)c.x(1))->utf16();
    auto* p = (char16_t*)malloc((u.size() + 1) * 2);
    memcpy(p, u.c_str(), (u.size() + 1) * 2);
    ret_ptr(c, p);
}
void j_ReleaseStringChars(Cpu& c) { free((void*)c.x(2)); }
void j_GetStringRegion(Cpu& c) {
    auto u = ((String*)c.x(1))->utf16();
    size_t start = (size_t)(s32)c.x(2), len = (size_t)(s32)c.x(3);
    if (start + len <= u.size()) memcpy((void*)c.x(4), u.data() + start, len * 2);
}
void j_GetStringUTFRegion(Cpu& c) {
    auto u = ((String*)c.x(1))->utf16();
    size_t start = (size_t)(s32)c.x(2), len = (size_t)(s32)c.x(3);
    if (start + len > u.size()) return;
    std::string s = utf16_to_utf8(u.data() + start, len);
    memcpy((void*)c.x(4), s.c_str(), s.size() + 1);
}

// ---- arrays (generic) ----
void j_GetArrayLength(Cpu& c) { ret(c, c.x(1) ? ((Array*)c.x(1))->length : 0); }
void j_NewObjectArray(Cpu& c) {
    Array* a = vm().new_array('L', (size_t)(s32)c.x(1), (Class*)c.x(2));
    for (auto& o : a->objs) o = obj(c.x(3));
    ret_ptr(c, a);
}
void j_GetObjectArrayElement(Cpu& c) {
    auto* a = (Array*)c.x(1);
    size_t i = (size_t)(s32)c.x(2);
    ret_ptr(c, a && i < a->objs.size() ? a->objs[i] : nullptr);
}
void j_SetObjectArrayElement(Cpu& c) {
    auto* a = (Array*)c.x(1);
    size_t i = (size_t)(s32)c.x(2);
    if (a && i < a->objs.size()) a->objs[i] = obj(c.x(3));
}
void j_GetPrimitiveArrayCritical(Cpu& c) {
    if (c.x(2)) *(u8*)c.x(2) = 0;
    ret_ptr(c, ((Array*)c.x(1))->data.data());
}

// ---- natives ----
struct NativeMethod {
    u64 name, sig, fn;
};
void j_RegisterNatives(Cpu& c) {
    auto* k = (Class*)c.x(1);
    auto* nm = (NativeMethod*)c.x(2);
    int n = (int)c.x(3);
    for (int i = 0; i < n; i++) {
        const char* name = (const char*)nm[i].name;
        const char* sig = (const char*)nm[i].sig;
        u64 fn = nm[i].fn;
        LOGD("jni", "RegisterNatives %s.%s%s -> %s", k->name.c_str(), name, sig, describe_guest_addr(fn).c_str());
        vm().def(k->name, name, sig, [fn](Object* self, const Args& a) -> u64 {
            GuestArgs ga;
            ga.i(vm().env_ptr()).i((u64)self);
            for (u64 v : a) ga.i(v);  // (int/ref args only; the game's natives take none else)
            return guest_call(fn, ga).x0;
        });
    }
    ret(c, 0);
}
void j_GetJavaVM(Cpu& c) {
    *(u64*)c.x(1) = vm().vm_ptr();
    ret(c, 0);
}

// ---- JavaVM ----
void v_GetEnv(Cpu& c) {
    *(u64*)c.x(1) = vm().env_ptr();
    ret(c, 0);
}
void v_Attach(Cpu& c) {
    if (c.x(1)) *(u64*)c.x(1) = vm().env_ptr();
    ret(c, 0);
}

#define CALL_FAMILY(T, Name)                                      \
    m["Call" Name "Method"] = &call_thunk<0, 0, T>;               \
    m["Call" Name "MethodV"] = &call_thunk<0, 1, T>;              \
    m["Call" Name "MethodA"] = &call_thunk<0, 2, T>;              \
    m["CallNonvirtual" Name "Method"] = &call_thunk<1, 0, T>;     \
    m["CallNonvirtual" Name "MethodV"] = &call_thunk<1, 1, T>;    \
    m["CallNonvirtual" Name "MethodA"] = &call_thunk<1, 2, T>;    \
    m["CallStatic" Name "Method"] = &call_thunk<2, 0, T>;         \
    m["CallStatic" Name "MethodV"] = &call_thunk<2, 1, T>;        \
    m["CallStatic" Name "MethodA"] = &call_thunk<2, 2, T>;

#define FIELD_FAMILY(T, Name)                               \
    m["Get" Name "Field"] = &get_field<T>;                  \
    m["Set" Name "Field"] = &set_field<T>;                  \
    m["GetStatic" Name "Field"] = &get_static_field<T>;     \
    m["SetStatic" Name "Field"] = &set_static_field<T>;

#define ARRAY_FAMILY(T, Name)                                         \
    m["New" Name "Array"] = &new_array<T>;                            \
    m["Get" Name "ArrayElements"] = &get_array_elements<T>;           \
    m["Release" Name "ArrayElements"] = &release_array_elements;      \
    m["Get" Name "ArrayRegion"] = &get_array_region<T>;               \
    m["Set" Name "ArrayRegion"] = &set_array_region<T>;

void build_impls() {
    auto& m = impls();
    CALL_FAMILY('L', "Object")
    CALL_FAMILY('Z', "Boolean")
    CALL_FAMILY('B', "Byte")
    CALL_FAMILY('C', "Char")
    CALL_FAMILY('S', "Short")
    CALL_FAMILY('I', "Int")
    CALL_FAMILY('J', "Long")
    CALL_FAMILY('F', "Float")
    CALL_FAMILY('D', "Double")
    CALL_FAMILY('V', "Void")
    m["NewObject"] = &call_thunk<3, 0, 'L'>;
    m["NewObjectV"] = &call_thunk<3, 1, 'L'>;
    m["NewObjectA"] = &call_thunk<3, 2, 'L'>;
    FIELD_FAMILY('L', "Object")
    FIELD_FAMILY('Z', "Boolean")
    FIELD_FAMILY('B', "Byte")
    FIELD_FAMILY('C', "Char")
    FIELD_FAMILY('S', "Short")
    FIELD_FAMILY('I', "Int")
    FIELD_FAMILY('J', "Long")
    FIELD_FAMILY('F', "Float")
    FIELD_FAMILY('D', "Double")
    ARRAY_FAMILY('Z', "Boolean")
    ARRAY_FAMILY('B', "Byte")
    ARRAY_FAMILY('C', "Char")
    ARRAY_FAMILY('S', "Short")
    ARRAY_FAMILY('I', "Int")
    ARRAY_FAMILY('J', "Long")
    ARRAY_FAMILY('F', "Float")
    ARRAY_FAMILY('D', "Double")

    m["GetVersion"] = j_GetVersion;
    m["FindClass"] = j_FindClass;
    m["GetSuperclass"] = j_GetSuperclass;
    m["IsAssignableFrom"] = j_IsAssignableFrom;
    m["Throw"] = j_Throw;
    m["ThrowNew"] = j_ThrowNew;
    m["ExceptionOccurred"] = j_ret0;
    m["ExceptionDescribe"] = j_ret0;
    m["ExceptionClear"] = j_ret0;
    m["ExceptionCheck"] = j_ret0;
    m["FatalError"] = j_FatalError;
    m["PushLocalFrame"] = j_ret0;
    m["PopLocalFrame"] = j_ret_arg1;
    m["NewGlobalRef"] = j_ret_arg1;
    m["DeleteGlobalRef"] = j_ret0;
    m["DeleteLocalRef"] = j_ret0;
    m["NewLocalRef"] = j_ret_arg1;
    m["NewWeakGlobalRef"] = j_ret_arg1;
    m["DeleteWeakGlobalRef"] = j_ret0;
    m["EnsureLocalCapacity"] = j_ret0;
    m["IsSameObject"] = j_IsSameObject;
    m["AllocObject"] = [](Cpu& c) {
        auto* o = new Instance();
        o->cls = (Class*)c.x(1);
        ret_ptr(c, o);
    };
    m["GetObjectClass"] = j_GetObjectClass;
    m["IsInstanceOf"] = j_IsInstanceOf;
    m["GetObjectRefType"] = j_GetObjectRefType;
    m["GetMethodID"] = j_GetMethodID;
    m["GetStaticMethodID"] = j_GetStaticMethodID;
    m["GetFieldID"] = j_GetFieldID;
    m["GetStaticFieldID"] = j_GetStaticFieldID;
    m["NewString"] = j_NewString;
    m["NewStringUTF"] = j_NewStringUTF;
    m["GetStringUTFChars"] = j_GetStringUTFChars;
    m["ReleaseStringUTFChars"] = j_ReleaseStringUTFChars;
    m["GetStringUTFLength"] = j_GetStringUTFLength;
    m["GetStringLength"] = j_GetStringLength;
    m["GetStringChars"] = j_GetStringChars;
    m["ReleaseStringChars"] = j_ReleaseStringChars;
    m["GetStringCritical"] = j_GetStringChars;
    m["ReleaseStringCritical"] = j_ReleaseStringChars;
    m["GetStringRegion"] = j_GetStringRegion;
    m["GetStringUTFRegion"] = j_GetStringUTFRegion;
    m["GetArrayLength"] = j_GetArrayLength;
    m["NewObjectArray"] = j_NewObjectArray;
    m["GetObjectArrayElement"] = j_GetObjectArrayElement;
    m["SetObjectArrayElement"] = j_SetObjectArrayElement;
    m["GetPrimitiveArrayCritical"] = j_GetPrimitiveArrayCritical;
    m["ReleasePrimitiveArrayCritical"] = release_array_elements;
    m["RegisterNatives"] = j_RegisterNatives;
    m["UnregisterNatives"] = j_ret0;
    m["MonitorEnter"] = j_ret0;
    m["MonitorExit"] = j_ret0;
    m["GetJavaVM"] = j_GetJavaVM;
}

}  // namespace

void Vm::init() {
    build_impls();
    env_table_.resize(kJniFunctionCount);
    for (int i = 0; i < kJniFunctionCount; i++) {
        const char* n = kJniFunctionNames[i];
        auto it = impls().find(n);
        if (it != impls().end()) env_table_[i] = make_thunk(n, it->second);
        else if (strncmp(n, "reserved", 8) == 0) env_table_[i] = 0;
        else env_table_[i] = make_thunk(n, unimplemented_jni);
    }
    env_ = (u64)env_table_.data();

    vm_table_ = {0, 0, 0,
                 make_thunk("JavaVM::DestroyJavaVM", j_ret0),
                 make_thunk("JavaVM::AttachCurrentThread", v_Attach),
                 make_thunk("JavaVM::DetachCurrentThread", j_ret0),
                 make_thunk("JavaVM::GetEnv", v_GetEnv),
                 make_thunk("JavaVM::AttachCurrentThreadAsDaemon", v_Attach)};
    vm_ = (u64)vm_table_.data();

    define_class("java/lang/Object", "");
    define_class("java/lang/Class");
    for (auto& [n, k] : classes_) k->cls = find_class("java/lang/Class");
    define_class("java/lang/String");
    install_android_classes(*this);
    install_playcore_classes(*this);  // 380-ok: the viewer's Play Core classes (stay in the runtime: the user, 2026-10-07)
    for (auto& fn : class_installers()) fn(*this);  // the host's (add_class_installer)
}

}  // namespace soa::jni
