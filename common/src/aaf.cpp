// AAF animations: the reader and the controllers' evaluation (soa/aaf.h). Compiled with
// -ffp-contract=off: every float operation below is one guest instruction (the guest code has no
// fused multiply-adds), in the decompile's order (left-associated sums and products as written).
#include <soa/aaf.h>

#include <cmath>
#include <cstring>

namespace soa::aaf {

using aff::rd16;
using aff::rd32;
using aff::rdf;

namespace {

void fail(std::string* err, const std::string& why) {
    if (err) *err = why;
}

float bits(uint32_t u) {
    float f;
    memcpy(&f, &u, 4);
    return f;
}

// AArch64 conversions: FCVTZS / FCVTZU (round toward zero, saturate, NaN -> 0).
int32_t fcvtzs(float f) {
    if (std::isnan(f)) return 0;
    if (f >= 2147483648.0f) return INT32_MAX;
    if (f <= -2147483648.0f) return INT32_MIN;
    return (int32_t)f;
}
uint32_t fcvtzu(float f) {
    if (std::isnan(f) || f <= 0.0f) return 0;
    if (f >= 4294967296.0f) return UINT32_MAX;
    return (uint32_t)f;
}
// SQRT with the guest's NaN fallback to sqrtf (the same value).
float fsqrt(float x) { return std::sqrt(x); }

}  // namespace

const char* attribute_name(int a) {
    switch (a) {
    case kTranslateX: return "translateX";
    case kTranslateY: return "translateY";
    case kTranslateZ: return "translateZ";
    case kTranslateXYZ: return "translate";
    case kRotateX: return "rotateX";
    case kRotateY: return "rotateY";
    case kRotateZ: return "rotateZ";
    case kRotateXYZ: return "rotateEuler";
    case kRotateQuaternion: return "rotation";
    case kScaleX: return "scaleX";
    case kScaleY: return "scaleY";
    case kScaleZ: return "scaleZ";
    case kScaleXYZ: return "scale";
    case 0: return "attr0";
    case 14: case 26: return "vectorElement";
    case 19: return "colour";
    case 21: return "uvU";
    case 22: return "uvV";
    case 23: return "uvW";
    default: return "attr?";
    }
}

const char* cp_type_name(int t) {
    switch (t) {
    case kNormal: return "Normal";
    case kNormalStep: return "Normal_Step";
    case kNormalLinear: return "Normal_Linear";
    case kVector: return "Vector";
    case kVectorStep: return "Vector_Step";
    case kVectorLinear: return "Vector_Linear";
    case kVector4: return "Vector4";
    case kVector4Step: return "Vector4_Step";
    case kVector4Linear: return "Vector4_Linear";
    case kQuaternion: return "Quaternion";
    case kQuaternionStep: return "Quaternion_Step";
    case kQuaternionLinear: return "Quaternion_Linear";
    default: return "?";
    }
}

const char* compression_name(int c) {
    switch (c) {
    case kF32: return "F32";
    case kU24: return "U24";
    case kU16: return "U16";
    case kQuatU32EX: return "U32EX";
    case kQuatU48EX: return "U48EX";
    default: return "?";
    }
}

const char* controller_kind_name(int k) {
    switch (k) {
    case 0: return "keyframe";
    case 1: return "anim-connect";
    case 2: return "keyframe2";
    case 3: return "keyframe3";
    case 4: return "noise";
    case 5: return "morph";
    case 6: return "prs-constraint";
    case 7: return "aim-constraint";
    case 8: return "parent-constraint";
    case 9: case 10: return "multi";
    case 11: return "value-array";
    default: return "?";
    }
}

int components(int t) {
    if (t <= kNormalLinear) return 1;
    if (t <= kVectorLinear) return 3;
    return 4;
}

bool load(const Bytes& d, Animation& a, std::string* err) {
    a = Animation();
    a.file = &d;
    if (d.size() < 0x40 || !aff::tag_is(d.data(), " FAA")) return fail(err, "not an AAF file"), false;
    if (!aff::tag_is(&d[0x10], " FRa")) return fail(err, "no resource chunk"), false;
    size_t h = 0x10 + rd32(&d[0x1c]);
    if (h + 0x30 > d.size()) return fail(err, "header out of range"), false;
    a.header = h;
    a.flags = rd32(&d[h]);
    a.version = rd16(&d[h]);
    if (a.version != 0x2e) return fail(err, "version " + std::to_string(a.version) + " (0x2e expected)"), false;
    a.target_count = rd16(&d[h + 4]);
    a.count_b = rd16(&d[h + 6]);
    a.count_a = rd16(&d[h + 8]);
    a.count_c = rd16(&d[h + 0xa]);
    a.length = rdf(&d[h + 0x10]);
    size_t p = rd32(&d[h + 0x20]);
    for (int ti = 0; ti < a.target_count; ti++) {
        if (p + 0x10 > d.size()) return fail(err, "target table truncated"), false;
        Target t;
        t.flags = d[p];
        t.type = d[p + 1];
        int n = rd16(&d[p + 2]);
        uint32_t size = rd32(&d[p + 4]);
        if (t.flags & 4) {
            t.raw_name = "#" + std::to_string(rd32(&d[p + 8]));  // an index into the names table
        } else {
            size_t k = 0;
            while (k < 32 && p + 8 + k < d.size() && d[p + 8 + k]) k++;
            t.raw_name.assign((const char*)&d[p + 8], k);
        }
        t.name = t.raw_name.rfind("R:", 0) == 0 ? t.raw_name.substr(2) : t.raw_name;
        size_t c = p + ((t.flags & 4) ? 0xc : 0x28);
        for (int ci = 0; ci < n; ci++) {
            if (c + 8 > d.size()) return fail(err, "controller header truncated"), false;
            Controller k;
            k.offset = c;
            k.target = ti;
            k.kind = d[c];
            k.sub = d[c + 1];
            k.size = rd16(&d[c + 2]);
            k.comp = d[c + 4];
            k.flags = d[c + 5];
            uint16_t kfo = rd16(&d[c + 6]);
            if (kfo && k.kind <= 3 && c + kfo + 0x18 <= d.size()) {
                k.kf = c + kfo;
                k.cp_type = d[k.kf + 5];
                k.attr = d[k.kf + 6];
                k.pre = d[k.kf + 8];
                k.post = d[k.kf + 9];
                k.start = rdf(&d[k.kf + 0xc]);
                k.end = rdf(&d[k.kf + 0x10]);
                k.count = rd32(&d[k.kf + 0x14]);
            }
            t.controllers.push_back((int)a.controllers.size());
            a.controllers.push_back(k);
            if (!k.size) break;
            c += k.size;
        }
        a.targets.push_back(std::move(t));
        if (!size) break;
        p += size;
    }
    return true;
}

namespace {

// ---- the keys of one controller ----
struct Keys {
    const uint8_t* kf;
    uint32_t n;
    float start, end;
    const uint8_t* times;  // n floats
    const uint8_t* data;   // the control points / packed keys
    uint8_t figure = 0;    // _U16 / _U24: the keyframe header's +7, the scale's index
    float time(uint32_t i) const { return rdf(times + i * 4); }
};

// AafHandler::GetFigureRate(figure, u24): the divisor of the _U16 / _U24 keys (libSOA 3.7.0
// @029739b0 for _U24, @029739d0 for _U16; beyond the table 10000 / 100).
float figure_rate(uint8_t figure, bool u24) {
    static const uint32_t kU24[8] = {0x4b189680, 0x49742400, 0x47c35000, 0x461c4000, 0x447a0000, 0x42c80000, 0x41200000, 0x3f800000};
    static const uint32_t kU16[8] = {0x47c35000, 0x461c4000, 0x447a0000, 0x42c80000, 0x41200000, 0x3f800000, 0x3dcccccd, 0x3c23d70a};
    if (figure < 8) return bits(u24 ? kU24[figure] : kU16[figure]);
    return u24 ? 10000.0f : 100.0f;
}

// Aska::AafKeyframeData_Quaternion_Linear_U48EX::GetValue (libSOA 3.7.0 @020e9ebc)
void u48ex_value(const uint8_t* p, float out[4]) {
    uint32_t u0 = rd32(p), u1 = rd32(p + 4);
    float q = (float)(uint32_t)(u1 >> 31 | (u0 & 0xffff) << 1) / bits(0x47ffff80);
    float f3 = 1.0f - q * q;
    float w = 0.0f;
    if (0.0f <= f3) {
        w = f3;
        if (1.0f < f3) w = 1.0f;
    }
    float a = (float)(u1 & 0x3fff) * bits(0x38c912ff);
    float b = (float)(u1 >> 14 & 0x3fff) * bits(0x38c912ff);
    float ca = cosf(a), sa = sinf(a), cb = cosf(b), sb = sinf(b);
    float x = sa * cb;
    if (u1 & 0x40000000) x = -(sa * cb);
    float f6 = 1.0f - w * w;
    if (u1 & 0x20000000) ca = -ca;
    float r = fsqrt(f6);
    float z = sa * sb;
    if (u1 & 0x10000000) z = -(sa * sb);
    x = x * r;
    float y = ca * r;
    z = r * z;
    float n = w * w + (x * x + y * y + z * z);
    if (bits(0x358637bd) < n) {
        float s = fsqrt(n);
        x = x / s;
        y = y / s;
        z = z / s;
        w = w / s;
    }
    out[0] = x;
    out[1] = y;
    out[2] = z;
    out[3] = w;
}

// Aska::AafKeyframeData_Quaternion_Linear_U32EX::GetValue (libSOA 3.7.0 @020e7af0)
void u32ex_value(const uint8_t* p, float out[4]) {
    uint32_t v = rd32(p);
    uint32_t u5 = v & 0x3ffff;
    float f2 = (float)(v >> 21) * bits(0x3a001002);
    float f3 = 1.0f - f2 * f2;
    float w = 0.0f;
    if (0.0f <= f3) {
        w = f3;
        if (1.0f < f3) w = 1.0f;
    }
    float f4 = (float)u5;
    float sq = fsqrt(f4);
    int32_t i1 = fcvtzs(sq);
    float g;  // the second angle
    if (i1 == 0) g = 0.0f;
    else g = ((float)(int32_t)(u5 - (uint32_t)(i1 * i1)) * bits(0x3fc90fdb)) / (float)(i1 << 1);
    const float kInvPi = 0.31830987f, kPi = 3.1415927f;
    int32_t q1 = fcvtzs((float)i1 * bits(0x3b497495) * kInvPi);
    int32_t q2 = fcvtzs(g * kInvPi);
    bool neg1 = (q1 & 1) != 0, neg2 = (q2 & 1) != 0;
    float a1 = (float)i1 * bits(0x3b497495) - (float)q1 * kPi;
    float a2 = g - (float)q2 * kPi;
    float z1 = a1 * a1, z2 = a2 * a2;
    float s1 = neg1 ? -a1 : a1, s2 = neg2 ? -a2 : a2;
    const float E0 = bits(0x379fe385), E1 = bits(0xbab02a05), E2 = bits(0x3d2a12df), E3 = bits(0xbeffeaa2),
                E4 = bits(0xbf7ffe19), E5 = bits(0x3f7ffe19);
    float c1p = (((E0 * z1 + E1) * z1 + E2) * z1 + E3) * z1;
    float c2p = (((E0 * z2 + E1) * z2 + E2) * z2 + E3) * z2;
    float cos1 = neg1 ? E4 - c1p : c1p + E5;
    float sin1 = s1 * (z1 * (z1 * (z1 * (z1 * 2.1727453e-06f + -0.00019315313f) + 0.00831233f) + -0.16663246f) + 0.9999845f);
    float sin2 = s2 * (z2 * (z2 * (z2 * (z2 * 2.1727453e-06f + -0.00019315313f) + 0.00831233f) + -0.16663246f) + 0.9999845f);
    float cos2 = neg2 ? E4 - c2p : c2p + E5;
    float x = cos2 * sin1;
    if (v & 0x100000) x = -(sin1 * cos2);
    float r = fsqrt(1.0f - w * w);
    float y = cos1;
    if (v & 0x80000) y = -y;
    float z = sin1 * sin2;
    if (v & 0x40000) z = -(sin1 * sin2);
    x = r * x;
    y = r * y;
    z = r * z;
    float n = w * w + (z * z + (y * y + x * x));
    if (bits(0x358637bd) < n) {
        float inv = 1.0f / fsqrt(n);
        x = x * inv;
        y = y * inv;
        z = z * inv;
        w = w * inv;
    }
    out[0] = x;
    out[1] = y;
    out[2] = z;
    out[3] = w;
}

// Aska::Quaternion::Slerp(out, a, b, t) (libSOA 3.7.0 @0205825c): its own acos and sin
// polynomials.
void slerp(float t, float out[4], const float a[4], const float b[4]) {
    float d = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
    float ad = 0.0f <= d ? d : -d;
    float x, y, z, w;
    bool done = false;
    if (ad <= 1.0f && -1.0f <= ad) {
        float q = ad * ad;
        float ang = ad * (q * (q * (q * (q * (q * (q * (q * bits(0xc233a42b) + bits(0x43135e2f)) + bits(0xc340db0f)) +
                                              bits(0x42ff5b59)) + bits(0xc233e470)) + bits(0x40fe8f6e)) + bits(0xbf4a8e9f)) +
                         bits(0xbf7c7629)) + bits(0x3fc90fdb);
        if (bits(0x3c23d70a) < ang) {
            const float kInvPi = bits(0x3ea2f983), kPi = bits(0x40490fdb);
            const float S0 = bits(0x2f2ea763), S1 = bits(0x2b393458), S2 = bits(0xb2d7109d), S3 = bits(0x3638edce),
                        S4 = bits(0xb9500cf2), S5 = bits(0x3c088888), S6 = bits(0xbe2aaaab);
            float a1 = (1.0f - t) * ang;
            int32_t u1 = fcvtzs(a1 * kInvPi);
            int32_t u2 = fcvtzs(ang * t * kInvPi);
            a1 = a1 - (float)u1 * kPi;
            float a2 = ang * t - (float)u2 * kPi;
            int32_t i3 = fcvtzs(ang * kInvPi);
            float a3 = ang - (float)i3 * kPi;
            float z1 = a1 * a1, z2 = a2 * a2, z3 = a3 * a3;
            if (u1 & 1) a1 = -a1;
            if (u2 & 1) a2 = -a2;
            if (i3 & 1) a3 = -a3;
            float p1 = z1 * (z1 * (z1 * (z1 * (z1 * (z1 * (S0 - z1 * S1) + S2) + S3) + S4) + S5) + S6) + 1.0f;
            float sb = a2 * (z2 * (z2 * (z2 * (z2 * (z2 * (z2 * (S0 - z2 * S1) + S2) + S3) + S4) + S5) + S6) + 1.0f);
            float sa = 0.0f <= d ? a1 * p1 : -(a1 * p1);
            float inv = 1.0f / (a3 * (z3 * (z3 * (z3 * (z3 * (z3 * (z3 * (S0 - z3 * S1) + S2) + S3) + S4) + S5) + S6) + 1.0f));
            x = inv * (sa * a[0] + sb * b[0]);
            y = inv * (sa * a[1] + sb * b[1]);
            z = inv * (sa * a[2] + sb * b[2]);
            w = inv * (sa * a[3] + sb * b[3]);
            done = true;
        }
    }
    if (!done) {
        float k0 = 1.0f - t;
        float k1 = 0.0f <= d ? t : -t;
        x = k0 * a[0] + k1 * b[0];
        y = k0 * a[1] + k1 * b[1];
        z = k0 * a[2] + k1 * b[2];
        w = k0 * a[3] + k1 * b[3];
    }
    float n = w * w + (x * x + y * y + z * z);
    float r = fsqrt(n);
    float inv = 1.0f / r;
    out[0] = x * inv;
    out[1] = inv * y;
    out[2] = inv * z;
    out[3] = inv * w;
}

// Aska::AafControlPoint_Quaternion::AddLoop(out, diff, k) for (int)k == 0 (the only case it is
// reached with: the cycle-offset path calls it with a non-zero count, see supported()).
void add_loop_quat(float out[4], const float dq[4]) {
    float ox = out[0], oy = out[1], oz = out[2], ow = out[3];
    float dx = dq[0], dy = dq[1], dz = dq[2], dw = dq[3];
    float nw = ((dw * ow - ox * dx) - dy * oy) - oz * dz;
    out[0] = (dw * ox + dx * ow + dy * oz) - dz * oy;
    out[1] = ox * dz + ow * dy + (dw * oy - dx * oz);
    out[2] = ow * dz + ((dw * oz + dx * oy) - ox * dy);
    out[3] = nw;
}

// One control point type's operations.
struct Ops {
    int cp, comp;
    const Keys* k;
    bool u48ex2 = false;  // compression 4 on a plain (not frame-sorted) controller: _U48EX2 keys
    // the value of key i as a slot holds it (decoded for the compressed quaternions)
    void key(uint32_t i, float v[4]) const {
        if (comp == kQuatU48EX && u48ex2) {  // _U48EX2 (6 bytes: u16, u32), widened as SetControlPoints does
            uint8_t w[8];
            const uint8_t* p = k->data + (size_t)i * 6;
            uint32_t lo = rd16(p), hi = rd32(p + 2);
            memcpy(w, &lo, 4);
            memcpy(w + 4, &hi, 4);
            return u48ex_value(w, v);
        }
        if (comp == kQuatU48EX) return u48ex_value(k->data + (size_t)i * 8, v);
        if (comp == kQuatU32EX) return u32ex_value(k->data + (size_t)i * 4, v);
        if (comp == kU16 || comp == kU24) {  // SetControlPoints: (float)(int)key / rate per component
            int n = components(cp);
            float rate = figure_rate(k->figure, comp == kU24);
            for (int c = 0; c < 4; c++) v[c] = 0.0f;
            for (int c = 0; c < n; c++) {
                int32_t q;
                if (comp == kU16) {
                    q = (int16_t)rd16(k->data + ((size_t)i * n + c) * 2);
                } else {
                    const uint8_t* b = k->data + ((size_t)i * n + c) * 3;
                    q = (int32_t)((uint32_t)b[0] << 24 | (uint32_t)b[1] << 16 | (uint32_t)b[2] << 8) >> 8;
                }
                v[c] = (float)q / rate;
            }
            return;
        }
        int stride = cp <= kNormalLinear ? (cp == kNormal ? 3 : 1)
                   : cp <= kVectorLinear ? (cp == kVector ? 9 : 3)
                   : cp == kQuaternion ? 0 : 4;
        const uint8_t* p = k->data + (size_t)i * stride * 4;
        for (int c = 0; c < 4; c++) v[c] = c < stride ? rdf(p + c * 4) : 0.0f;
    }
    const uint8_t* raw(uint32_t i) const {
        int stride = cp == kNormal ? 3 : cp == kVector ? 9 : components(cp);
        return k->data + (size_t)i * stride * 4;
    }
    // a slot's value into out (the hold paths)
    void assign(uint32_t i, float out[4]) const {
        float v[4];
        key(i, v);
        int n = components(cp);
        for (int c = 0; c < n; c++) out[c] = v[c];
        if (n == 3) out[3] = 1.0f;
    }
    // the interval [i, i + 1] at frame w
    void interp(uint32_t i, float w, float out[4]) const {
        float t0 = k->time(i), t1 = k->time(i + 1);
        float len = t1 - t0;
        if (len == 0.0f) len = 1.0f;  // AafKeyFrameController::UpdateCurrentRange
        switch (cp) {
        case kNormal: {
            const uint8_t* c = raw(i);
            const uint8_t* n = raw(i + 1);
            // (the disassembly's order, @020abae8..@020abb48)
            float s = (w - t0) / len, sm1 = s + -1.0f;
            float h0 = sm1 * (sm1 * (s + s + 1.0f));
            float h1 = (s * s) * (3.0f - (s + s));
            float h2 = sm1 * (s * sm1);
            float h3 = (s * s) * sm1;
            out[0] = h3 * rdf(n + 4) + (rdf(c + 8) * h2 + (rdf(n) * h1 + rdf(c) * h0));
            return;
        }
        case kNormalStep:
        case kVectorStep:
        case kVector4Step:
        case kQuaternionStep:
            return assign(i, out);
        case kNormalLinear: {
            float a[4], b[4];
            key(i, a);
            key(i + 1, b);
            float v0 = a[0], v1 = b[0];
            out[0] = v0 + ((w - t0) * (v1 - v0)) / len;
            return;
        }
        case kVector: {
            const uint8_t* c = raw(i);
            const uint8_t* n = raw(i + 1);
            // (@020c5124..@020c51d0)
            float s = (w - t0) / len, sm1 = s + -1.0f;
            float h3 = (s * s) * sm1;
            float h1 = (s * s) * (3.0f - (s + s));
            float h2 = sm1 * (s * sm1);
            float h0 = sm1 * (sm1 * (s + s + 1.0f));
            float x = h1 * rdf(n) + rdf(c) * h0 + h2 * rdf(c + 24) + h3 * rdf(n + 12);
            float y = h1 * rdf(n + 4) + rdf(c + 4) * h0 + h2 * rdf(c + 28) + h3 * rdf(n + 16);
            float z = rdf(c + 8) * h0 + h1 * rdf(n + 8) + h2 * rdf(c + 32) + h3 * rdf(n + 20);
            out[3] = 1.0f;
            out[0] = x;
            out[1] = y;
            out[2] = z;
            return;
        }
        case kVectorLinear: {
            float c[4], n[4];
            key(i, c);
            key(i + 1, n);
            float f = (w - t0) * (1.0f / len);
            out[0] = c[0] + f * (n[0] - c[0]);
            out[1] = c[1] + f * (n[1] - c[1]);
            out[2] = c[2] + f * (n[2] - c[2]);
            return;
        }
        case kQuaternionLinear: {
            float a[4], b[4];
            key(i, a);
            key(i + 1, b);
            slerp((w - t0) / len, out, a, b);
            return;
        }
        default: return;
        }
    }
    // the cycle-offset term: k * (last - first)
    void add_loop(float f, float out[4]) const {
        float first[4], last[4];
        key(0, first);
        key(k->n - 1, last);
        int n = components(cp);
        if (n == 1) {
            out[0] = out[0] + f * (last[0] - first[0]);
        } else if (n == 3) {
            for (int c = 0; c < 3; c++) out[c] = f * (last[c] - first[c]) + out[c];
        } else {
            float dq[4] = {last[0] - first[0], last[1] - first[1], last[2] - first[2], last[3] - first[3]};
            add_loop_quat(out, dq);
        }
    }
};

}  // namespace

namespace {
bool supported_keys(const Controller& c, std::string* why, bool euler_ok);
}

bool supported(const Controller& c, std::string* why) { return supported_keys(c, why, false); }

namespace {
bool supported_keys(const Controller& c, std::string* why, bool euler_ok) {
    auto no = [&](const std::string& s) { if (why) *why = s; return false; };
    if (!c.keyframed()) return no(std::string("not a keyframe controller (") + controller_kind_name(c.kind) + ")");
    if (c.frame_sorted()) return no("frame-sorted controller (TAafFrameSort*)");
    if (!euler_ok && c.attr >= kRotateX && c.attr <= kRotateXYZ)
        return no("Euler rotation: the controller returns Quaternion::CreateFromEuler(x, y, z) (Rz Ry Rx; Quaternion::Create's sinf / cosf), not reproduced bit for bit");
    if (c.comp == kQuatU32EX || c.comp == kQuatU48EX) {
        if (c.cp_type != kQuaternionLinear && c.cp_type != kQuaternionStep) return no("compressed quaternion of an unknown kind");
    } else if (c.comp == kU16 || c.comp == kU24) {
        bool ok = c.cp_type == kNormalStep || c.cp_type == kNormalLinear || c.cp_type == kVectorStep || c.cp_type == kVectorLinear;
        if (!ok) return no(std::string(compression_name(c.comp)) + " " + cp_type_name(c.cp_type) + " (not reached by the proof yet)");
    } else if (c.comp != kF32) {
        return no(std::string("compressed keys (") + compression_name(c.comp) + ")");
    }
    switch (c.cp_type) {
    case kNormal: case kNormalStep: case kNormalLinear: case kVector: case kVectorStep: case kVectorLinear:
    case kQuaternionStep: case kQuaternionLinear: break;
    default: return no(std::string("control point type ") + cp_type_name(c.cp_type));
    }
    if (c.pre == 1 || c.post == 1) return no("linear extrapolation (CalcValueByLinearAt*OutOfRange)");
    if ((c.pre == 3 || c.post == 3) && components(c.cp_type) == 4) return no("quaternion cycle with offset (Quaternion::Mul)");
    return true;
}
bool eval_keys(const Animation& a, const Controller& c, float t, float out[4]);
}  // namespace

bool evaluate(const Animation& a, const Controller& c, float t, float out[4]) {
    return supported_keys(c, nullptr, false) && eval_keys(a, c, t, out);
}

bool evaluate_track(const Animation& a, const Controller& c, float t, float out[4]) {
    return supported_keys(c, nullptr, true) && eval_keys(a, c, t, out);
}

namespace {

// TAafNormalController<...>::CalcValueSub(out, t, false): the out-of-range modes, the key search
// and the type's interpolation.
bool eval_keys(const Animation& a, const Controller& c, float t, float out[4]) {
    const Bytes& d = *a.file;
    Keys k;
    k.kf = &d[c.kf];
    k.n = c.count;
    k.start = c.start;
    k.end = c.end;
    k.times = k.kf + 0x18;
    k.data = k.times + (size_t)k.n * 4;
    k.figure = k.kf[7];
    Ops ops{c.cp_type, c.comp, &k};
    ops.u48ex2 = !c.frame_sorted();  // (LocalSetControllerQuaternionU48EX: +5 bit 6 -> _U48EX2)
    // compressed quaternions decode a step as the linear class does; constant groups too
    if ((c.comp == kQuatU32EX || c.comp == kQuatU48EX) && c.cp_type == kQuaternionStep) ops.cp = kQuaternionLinear;
    if (k.n == 0 || k.n == 1) {
        ops.assign(0, out);
        return true;
    }
    const uint32_t last = k.n - 1;
    float s0 = k.start, s1 = k.end;
    float len = s1 - s0;
    bool add = false;
    float factor = 0.0f;
    float w = t;
    enum { kFirst, kLast, kSearch, kPathA } where = kPathA;
    auto cycle = [&](int mode) {
        switch (mode) {
        case 2:
            if (len == 0.0f) w = 0.0f;
            else w = t - len * (float)fcvtzs((t - s0) / len);
            break;
        case 3: {
            float kk = 0.0f;
            w = 0.0f;
            if (len != 0.0f) {
                kk = (float)fcvtzs((t - s0) / len);
                w = t - len * kk;
            }
            add = fcvtzs(kk) != 0;
            factor = add ? kk : 0.0f;
            break;
        }
        case 4:
            if (len != 0.0f) {
                float q = (t - s0) / len;
                uint32_t u = fcvtzu(q);
                float tt = t - len * (float)fcvtzs(q);
                if (u & 1) {
                    w = (s0 + s0 + len) - tt;
                } else {
                    w = tt;
                    where = kPathA;
                    return;
                }
            } else {
                w = 0.0f;
                where = s0 < 0.0f ? kSearch : kFirst;
                return;
            }
            break;
        }
        where = s0 < w ? kSearch : kFirst;
    };
    if (t <= s1) {
        if (s0 <= t) {
            where = kPathA;
        } else {
            switch (c.pre) {
            case 0: where = kFirst; break;
            case 2: case 3: case 4: cycle(c.pre); break;
            default: where = kPathA; break;
            }
        }
    } else {
        switch (c.post) {
        case 0: where = kLast; break;
        case 2: case 3: case 4: cycle(c.post); break;
        default: where = kPathA; break;
        }
    }
    if (where == kPathA) where = w <= s0 ? kFirst : kSearch;
    if (where == kSearch && !(w < s1)) where = kLast;
    if (where == kFirst) {
        ops.assign(0, out);
    } else if (where == kLast) {
        ops.assign(last, out);
    } else {
        // the interval holding w (times[i] <= w < times[i + 1])
        uint32_t i = 0;
        while (i + 1 < last && !(w < k.time(i + 1))) i++;
        while (i > 0 && w < k.time(i)) i--;
        ops.interp(i, w, out);
    }
    if (add) ops.add_loop(factor, out);
    return true;
}

}  // namespace

bool evaluate_constant(const Animation& a, const Controller& c, float out[4]) {
    if (!c.keyframed() || !c.constant()) return false;
    if (c.attr >= kRotateX && c.attr <= kRotateXYZ) return false;  // (a quaternion: see supported())
    const Bytes& d = *a.file;
    if (c.kf + 0x18 > d.size()) return false;
    Keys k;
    k.kf = &d[c.kf];
    k.n = 1;
    k.start = k.end = 0;
    k.times = nullptr;
    k.data = k.kf + 0xc;  // (+8 a u32 0, then the one value: floats, or a packed key)
    k.figure = k.kf[7];
    Ops ops{c.cp_type, c.comp, &k};
    ops.u48ex2 = !c.frame_sorted();
    if ((c.comp == kQuatU32EX || c.comp == kQuatU48EX) && c.cp_type == kQuaternionStep) ops.cp = kQuaternionLinear;
    ops.assign(0, out);
    return true;
}

}  // namespace soa::aaf
