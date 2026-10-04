// Differential tests of Aska::Quaternion's natives (math_quaternion.cpp) and of the .rodata
// constants the math natives copy, against the 3.7.0 guest.
#include "core/loader.h"
#include "native/math/math_constants.h"
#include "native/math/math_layout.h"
#include "native/math/math_test_util.h"

namespace soa::native::math {

using namespace test;


NATIVE_TEST("math/constants") {
    for (const RodataConstant& c : kConstants)
        for (int i = 0; i < c.count; i++) {
            float guest;
            std::memcpy(&guest, (const void*)(main_lib()->base + c.vaddr + 4 * i), 4);
            if (!same(guest, c.values[i])) t.fail("constant at %#llx: guest %s, native %s", (unsigned long long)(c.vaddr + 4 * i), hex(guest).c_str(), hex(c.values[i]).c_str());
        }
}

NATIVE_TEST("math/quaternion-create") {
    Mismatches bad{t, "Quaternion::Create(Vector)"};
    for (int k = 0; k < 30000; k++) {
        int special = k < 25000 ? 0 : 150;
        Vector v = rand_vector(t, 2, special);
        if (k % 3 == 0) {  // a unit axis, angles up to a few turns
            float n = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
            if (n > 0) v.x /= n, v.y /= n, v.z /= n;
            v.w = rand_float(t, k % 2 ? 7 : 1000, special);
        }
        Quaternion g{9, 9, 9, 9}, n{9, 9, 9, 9};
        t.call("_ZN4Aska10Quaternion6CreateEPKNS_6VectorE", GuestArgs().p(&g).p(&v));
        n.Create(&v);
        bad.check(k, same(g, n), "axis-angle " + hex(v.x) + " " + hex(v.y) + " " + hex(v.z) + " " + hex(v.w) + ": w guest " + hex(g.w) + " native " + hex(n.w) + ", x " + hex(g.x) + " / " + hex(n.x));
    }
    Mismatches badm{t, "Quaternion::Create(Matrix)"};
    for (int k = 0; k < 30000; k++) {
        Matrix m = rand_matrix(t, k < 25000 ? 10 : 300);
        if (k % 50 == 0) m = Matrix{{{-1, 0, 0, 0}, {0, -1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};  // trace < 1, ties
        if (k % 50 == 1) m = Matrix{{{1, 0, 0, 0}, {0, -1, 0, 0}, {0, 0, -1, 0}, {0, 0, 0, 0}}};
        Quaternion g{9, 9, 9, 9}, n{9, 9, 9, 9};
        t.call("_ZN4Aska10Quaternion6CreateEPKNS_6MatrixE", GuestArgs().p(&g).p(&m));
        n.Create(&m);
        badm.check(k, same(g, n), "guest " + hex(g.x) + " " + hex(g.y) + " " + hex(g.z) + " " + hex(g.w) + ", native " + hex(n.x) + " " + hex(n.y) + " " + hex(n.z) + " " + hex(n.w));
    }
}

NATIVE_TEST("math/quaternion-euler") {
    Mismatches bad{t, "Quaternion::CreateFromEuler"};
    for (int k = 0; k < 30000; k++) {
        int special = k < 25000 ? 0 : 150;
        float ax = rand_float(t, 7, special), ay = rand_float(t, 7, special), az = rand_float(t, 7, special);
        int order = k % 8 == 7 ? t.rand_int(-3, 100) : k % 7;
        Quaternion g{9, 9, 9, 9}, n{9, 9, 9, 9};
        t.call("_ZN4Aska10Quaternion15CreateFromEulerEfff14EnumRotateType", GuestArgs().p(&g).f(ax).f(ay).f(az).i((u64)(u32)order));
        n.CreateFromEuler(ax, ay, az, order);
        bad.check(k, same(g, n), "order " + std::to_string(order) + ": guest " + hex(g.x) + " " + hex(g.w) + ", native " + hex(n.x) + " " + hex(n.w));
    }
}

NATIVE_TEST("math/quaternion-slerp") {
    Mismatches bad{t, "Quaternion::Slerp"};
    for (int k = 0; k < 40000; k++) {
        int special = k < 32000 ? 0 : 150;
        Quaternion q1 = rand_quaternion(t, special), q2 = rand_quaternion(t, special);
        int kind = t.rand_int(0, 9);
        if (kind == 0) q2 = q1;  // equal: the linear path
        else if (kind == 1) q2 = {-q1.x, -q1.y, -q1.z, -q1.w};
        else if (kind == 2) q2 = {q1.x + 1e-3f, q1.y, q1.z - 1e-3f, q1.w};  // nearly equal
        float tt = kind == 3 ? rand_float(t, 3, special) : std::uniform_real_distribution<float>(0, 1)(t.rng());
        if (k % 100 == 0) tt = (float)t.rand_int(0, 1);
        Quaternion g{9, 9, 9, 9}, n{9, 9, 9, 9};
        t.call("_ZN4Aska10Quaternion5SlerpEPKS0_S2_f", GuestArgs().p(&g).p(&q1).p(&q2).f(tt));
        n.Slerp(&q1, &q2, tt);
        bad.check(k, same(g, n), "t " + hex(tt) + ": guest " + hex(g.x) + " " + hex(g.y) + " " + hex(g.z) + " " + hex(g.w) + ", native " + hex(n.x) + " " + hex(n.y) + " " + hex(n.z) + " " + hex(n.w));
        // in place (this == q1), as the game calls it
        Quaternion g1 = q1, n1 = q1;
        t.call("_ZN4Aska10Quaternion5SlerpEPKS0_S2_f", GuestArgs().p(&g1).p(&g1).p(&q2).f(tt));
        n1.Slerp(&n1, &q2, tt);
        bad.check(k, same(g1, n1), "in place: guest " + hex(g1.x) + ", native " + hex(n1.x));
    }
}

}  // namespace soa::native::math
