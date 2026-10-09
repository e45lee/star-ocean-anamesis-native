#pragma once
// AAF: the game's animations (Motion/*.apk members, MapHome/*.aaf, Effect/*.aaf; part of soa_models).
// docs/notes.md "Models and animation" and "Animations (AAF) for tools" describe the layout. This
// reader follows Aska::AafHandler::AttachAaf (targets, controller headers, keyframe headers) and
// the evaluation follows the controllers' CalcValueSub (TAafNormalController<AafType<ControlPoint,
// false, false, 0>> and the compressed quaternion ones): the same operations in the same order, so
// that a value is bit for bit the one the game computes (proved by the port's selftest
// models/aaf-eval against the guest; see tools/aafdump --verify).
#include <soa/aff.h>

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace soa::aaf {

using Bytes = aff::Bytes;

// The keyframe header's +5: the control point type (AafControlPoint_*).
enum CpType : uint8_t {
    kNormal = 0, kNormalStep = 1, kNormalLinear = 2,
    kVector = 5, kVectorStep = 6, kVectorLinear = 7,
    kVector4 = 8, kVector4Step = 9, kVector4Linear = 10,
    kQuaternion = 11, kQuaternionStep = 12, kQuaternionLinear = 13,
};
// The controller header's +4 for keyframe controllers: how the keys are stored.
// (kQuatU48EX on a plain controller, +5 bit 6 set, is _U48EX2: 6-byte keys, u16 then u32; on a
// frame-sorted one _U48EX: 8-byte keys.)
enum Compression : uint8_t { kF32 = 0, kU24 = 1, kU16 = 2, kQuatU32EX = 3, kQuatU48EX = 4 };
// The keyframe header's +6: what is animated (EnumAafDetailAttribute, the factory
// LocalSetControllerF32_Default_TrRtSc and its siblings).
enum Attribute : uint8_t {
    kTranslateX = 1, kTranslateY = 2, kTranslateZ = 3, kTranslateXYZ = 4,
    kRotateX = 5, kRotateY = 6, kRotateZ = 7, kRotateXYZ = 8, kRotateQuaternion = 9,
    kScaleX = 10, kScaleY = 11, kScaleZ = 12, kScaleXYZ = 13,
};
const char* attribute_name(int attr);
const char* cp_type_name(int t);
const char* compression_name(int c);
// The controller header's +0 (AafHandler::SetController): 0..3 keyframe controllers (the
// LocalSetController family; 1 anim-connect, 2 ...), 4 noise, 6 PRS constraint, 7 aim
// constraint, 8 parent constraint, 9 / 10 multi controllers, 11 value array.
const char* controller_kind_name(int kind);

struct Controller {
    size_t offset = 0;      // the controller header in the file
    int target = -1;
    uint8_t kind = 0, sub = 0, comp = 0, flags = 0;
    uint16_t size = 0;
    size_t kf = 0;          // the keyframe header (0: none)
    uint8_t cp_type = 0, attr = 0, pre = 0, post = 0;
    float start = 0, end = 0;
    uint32_t count = 0;
    bool frame_sorted() const { return !(flags & 0x40); }  // TAafFrameSort* (+5 bit 6 clear)
    bool constant() const { return (flags & 0x80) != 0; }  // the constant group (+5 bit 7)
    bool keyframed() const { return kf != 0 && kind <= 3; }
};
struct Target {
    std::string name;       // without "R:"
    std::string raw_name;
    uint8_t flags = 0, type = 0;  // type 0 a node, 1 a collision shape, 3 a constraint's target, ...
    std::vector<int> controllers;
};
struct Animation {
    const Bytes* file = nullptr;
    size_t header = 0;      // AafHeader
    uint16_t version = 0, target_count = 0, count_a = 0, count_b = 0, count_c = 0;
    uint32_t flags = 0;
    float length = 0;       // +0x10: frames
    std::vector<Target> targets;
    std::vector<Controller> controllers;
};

// Reads a decoded .aaf (`d` must outlive `out`). False (and *err) when it isn't one.
bool load(const Bytes& d, Animation& out, std::string* err = nullptr);

// Whether evaluate() implements the controller (its control point type and compression), and
// why not.
bool supported(const Controller& c, std::string* why = nullptr);

// The controller's value at frame t, as its CalcValue(out, t) writes it (out[0] for Normal,
// out[0..2] (+ w) for Vector, out[0..3] for Quaternion x, y, z, w). Only the components the game
// writes are written: pass the same initial `out` as a comparison's other side. False for an
// unsupported controller.
bool evaluate(const Animation& a, const Controller& c, float t, float out[4]);

// The track's own values for the controllers evaluate() leaves out as returning something else:
// the Euler rotations' angles (x, y, z in radians; the game turns them into
// Quaternion::CreateFromEuler(x, y, z) = Rz Ry Rx, which this doesn't reproduce bit for bit).
bool evaluate_track(const Animation& a, const Controller& c, float t, float out[4]);

// A constant controller's value (the +5 bit 7 group: one value, kept at the keyframe header's +8
// (F32: the floats; U32EX / U48EX: the packed key), read by the game with CalcValueConstant).
bool evaluate_constant(const Animation& a, const Controller& c, float out[4]);

// Number of value components (1, 3, 4) of a control point type.
int components(int cp_type);

}  // namespace soa::aaf
