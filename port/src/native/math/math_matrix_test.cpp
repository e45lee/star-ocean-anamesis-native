// Differential tests of Aska::Matrix's natives (math_matrix.cpp) against the 3.7.0 guest.
#include "native/math/math_layout.h"
#include "native/math/math_test_util.h"

namespace soa::native::math {

using namespace test;

namespace {

std::string dump(const Matrix& m) {
    std::string s;
    for (auto& row : m.m)
        for (float v : row) s += hex(v) + " ";
    return s;
}

// A matrix for CalcEuler / PutPRS: a rotation (often about one axis only, or a gimbal-lock
// one), sometimes scaled, or arbitrary.
Matrix rand_rotation(TestContext& t, int special) {
    int kind = t.rand_int(0, 9);
    if (kind < 3) {  // about a single axis: the special cases
        float a = rand_float(t, 4, special), c = std::cos(a), s = std::sin(a);
        Matrix m{{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
        int i = (kind + 1) % 3, j = (kind + 2) % 3;
        m.m[i][i] = c, m.m[i][j] = -s, m.m[j][i] = s, m.m[j][j] = c;
        if (t.rand_int(0, 3) == 0) m.m[i][j] += 1e-7f;  // near the tolerance
        return m;
    }
    if (kind == 3) {  // 90 degrees about Y (or X, Z): cos = 0
        Matrix m{{{0, 0, 1, 0}, {0, 1, 0, 0}, {-1, 0, 0, 0}, {0, 0, 0, 1}}};
        if (t.rand_int(0, 1)) m = Matrix{{{0, -1, 0, 0}, {1, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
        if (t.rand_int(0, 1)) m = Matrix{{{1, 0, 0, 0}, {0, 0, -1, 0}, {0, 1, 0, 0}, {0, 0, 0, 1}}};
        return m;
    }
    return rand_matrix(t, special);
}

}  // namespace

NATIVE_TEST("math/matrix-mul") {
    Mismatches bad{t, "Matrix::Mul(Matrix, Matrix)"};
    for (int k = 0; k < 20000; k++) {
        int special = k < 16000 ? 0 : 100;
        Matrix a = rand_matrix(t, special ? special : 300), b = rand_matrix(t, special ? special : 300);
        Matrix g, n;
        std::memset(&g, 0x55, sizeof g), std::memset(&n, 0x55, sizeof n);
        if (k % 10 == 0) {  // in place: this == a
            g = a, n = a;
            t.call("_ZN4Aska6Matrix3MulEPKS0_S2_", GuestArgs().p(&g).p(&g).p(&b));
            n.Mul(&n, &b);
        } else {
            t.call("_ZN4Aska6Matrix3MulEPKS0_S2_", GuestArgs().p(&g).p(&a).p(&b));
            n.Mul(&a, &b);
        }
        bad.check(k, same(g, n), "guest " + dump(g) + "\n native " + dump(n));
    }
}

NATIVE_TEST("math/matrix-invert") {
    Mismatches bad{t, "Matrix::Invert"};
    for (int k = 0; k < 20000; k++) {
        int special = k < 16000 ? 0 : 150;
        Matrix m = rand_matrix(t, special ? special : 200);
        if (k % 7 == 0) m.m[t.rand_int(0, 3)][t.rand_int(0, 3)] = (float)t.rand_int(-1, 1) * 1e-6f;  // small pivots
        if (k % 11 == 0) m.m[t.rand_int(0, 3)][t.rand_int(0, 3)] = from_bits(0x7fc00000u | (u32)t.rand_int(1, 1000));
        Matrix g = m, n = m;
        t.call("_ZN4Aska6Matrix6InvertEv", GuestArgs().p(&g));
        n.Invert();
        bad.check(k, same(g, n), "matrix " + dump(m) + "\n guest " + dump(g) + "\n native " + dump(n));
    }
}

NATIVE_TEST("math/matrix-applyvector") {
    Mismatches bad{t, "Matrix::ApplyVector"};
    for (int k = 0; k < 20000; k++) {
        int special = k < 16000 ? 0 : 150;
        Matrix m = rand_matrix(t, special ? special : 200);
        Vector v = rand_vector(t, 20, special);
        Vector g{7, 7, 7, 7}, n = g;
        if (k % 4 == 0) {  // in place
            g = v, n = v;
            t.call("_ZNK4Aska6Matrix11ApplyVectorEPNS_6VectorEPKS1_", GuestArgs().p(&m).p(&g).p(&g));
            m.ApplyVector(&n, &n);
        } else {
            t.call("_ZNK4Aska6Matrix11ApplyVectorEPNS_6VectorEPKS1_", GuestArgs().p(&m).p(&g).p(&v));
            m.ApplyVector(&n, &v);
        }
        bad.check(k, same(g, n), "guest " + hex(g.x) + " " + hex(g.y) + " " + hex(g.z) + " " + hex(g.w) + ", native " + hex(n.x) + " " + hex(n.y) + " " + hex(n.z) + " " + hex(n.w));
    }
}

NATIVE_TEST("math/matrix-lookat") {
    Mismatches bad{t, "Matrix::SetLookAtMatrixZPUp"};
    for (int k = 0; k < 20000; k++) {
        int special = k < 16000 ? 0 : 150;
        Vector eye = rand_vector(t, 50, special), dir = rand_vector(t, 5, special), up = rand_vector(t, 2, special);
        int kind = t.rand_int(0, 9);
        if (kind == 0) dir = Vector{0, 0, 0, 1};
        else if (kind == 1) up = Vector{0, 1, 0, 0};
        else if (kind == 2) up = Vector{dir.x * 2, dir.y * 2, dir.z * 2, 0};  // parallel: no right axis
        else if (kind == 3) dir = Vector{1e-7f, 0, 0, 0};
        float roll = kind == 4 ? 0.0f : rand_float(t, kind == 5 ? 1000 : 7, special);
        Matrix g, n;
        std::memset(&g, 0x55, sizeof g), std::memset(&n, 0x55, sizeof n);
        t.call("_ZN4Aska6Matrix19SetLookAtMatrixZPUpEPKNS_6VectorES3_S3_f", GuestArgs().p(&g).p(&eye).p(&dir).p(&up).f(roll));
        n.SetLookAtMatrixZPUp(&eye, &dir, &up, roll);
        bad.check(k, same(g, n), "guest " + dump(g) + "\n native " + dump(n));
    }
}

NATIVE_TEST("math/matrix-putprs") {
    Mismatches bad{t, "Matrix::PutPRS"};
    for (int k = 0; k < 20000; k++) {
        int special = k < 16000 ? 0 : 150;
        Matrix m = rand_rotation(t, special);
        if (k % 3 == 0)  // scaled columns, sometimes by almost 1
            for (int j = 0; j < 3; j++) {
                float s = t.rand_int(0, 2) ? 1.0f + 1e-7f * (float)t.rand_int(-20, 20) : rand_float(t, 3, special);
                for (int i = 0; i < 3; i++) m.m[i][j] *= s;
            }
        Vector gp{7, 7, 7, 7}, np = gp, gs = gp, ns = gp;
        Quaternion gr{7, 7, 7, 7}, nr = gr;
        int outs = k % 8;  // which out-parameters
        t.call("_ZNK4Aska6Matrix6PutPRSEPNS_6VectorEPNS_10QuaternionES2_",
               GuestArgs().p(&m).p(outs & 1 ? nullptr : &gp).p(outs & 2 ? nullptr : &gr).p(outs & 4 ? nullptr : &gs));
        m.PutPRS(outs & 1 ? nullptr : &np, outs & 2 ? nullptr : &nr, outs & 4 ? nullptr : &ns);
        bad.check(k, same(gp, np) && same(gr, nr) && same(gs, ns),
                  "matrix " + dump(m) + "\n guest rot " + hex(gr.x) + " " + hex(gr.w) + " scale " + hex(gs.x) + ", native " + hex(nr.x) + " " + hex(nr.w) + " " + hex(ns.x));
    }
}

NATIVE_TEST("math/matrix-euler") {
    Mismatches bad{t, "Matrix::CalcEuler"};
    for (int k = 0; k < 30000; k++) {
        int special = k < 25000 ? 0 : 150;
        Matrix m = rand_rotation(t, special);
        int order = k % 8 == 7 ? t.rand_int(-2, 9) : k % 7;
        Vector g{7, 7, 7, 7}, n{7, 7, 7, 7};
        t.call("_ZNK4Aska6Matrix9CalcEulerEPNS_6VectorE14EnumRotateType", GuestArgs().p(&m).p(&g).i((u64)(u32)order));
        m.CalcEuler(&n, order);
        bad.check(k, same(g, n), "order " + std::to_string(order) + " matrix " + dump(m) + "\n guest " + hex(g.x) + " " + hex(g.y) + " " + hex(g.z) + ", native " + hex(n.x) + " " + hex(n.y) + " " + hex(n.z));
    }
}

}  // namespace soa::native::math
