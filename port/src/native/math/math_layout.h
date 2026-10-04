// math_layout.h: the guest data layouts of the `math` subsystem (Math: vectors, matrices, quaternions, primitives, intersection).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/math/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types math` turns the structs into port/decomp/math/types.json for Ghidra.
//
// What other subsystems can rely on (the value types every engine system passes around):
//   - Aska::Vector / Framework::CVector: 4 floats {x, y, z, w} (16 bytes; w is 1 for points, 0 or
//     anything for directions; a Sphere keeps its radius there);
//   - Aska::Quaternion / Framework::CQuaternion: {x, y, z, w}, w the scalar part;
//   - Aska::Matrix / Framework::CMatrix: 4x4 floats, row-major, m[row][col], vectors are columns
//     (v' = M v: out.x = dot(row 0, v)), the translation in column 3 (m[0][3], m[1][3], m[2][3]);
//   - Aska::Matrix34: the top 3 rows of a Matrix (48 bytes);
//   - the primitives: Segment {origin, direction} (end = origin + direction), Plane {point, normal},
//     AABB {center, half extents}, AABB_MinMax {min, max}, Box {center, half extents, 3 axes}.
// The functions with natives (the hot ones: math's README) are declared as members; the others are
// listed as comments and stay guest code.
#ifndef SOA_NATIVE_MATH_LAYOUT_H
#define SOA_NATIVE_MATH_LAYOUT_H

#include <cstddef>
#include <cstdint>

namespace soa::native::math {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// EnumRotateType (a plain enum, passed in w registers): the order Euler angles are applied in.
// 0 is the default (X, then Y, then Z: Quaternion::CreateFromEuler's `default` case); 1-5 the
// other orders (port/decomp/math/quaternion.c, matrix.c CalcEuler's switch).
using EnumRotateType = s32;

class Matrix;
class Quaternion;

// Aska::Vector: guest size 0x10; {x, y, z, w} (Vector::ApplyMatrix reads all four:
// port/decomp/math/vector.c).
class Vector {
public:
    // Guest methods (guest code): ApplyMatrix(Matrix const*), ApplyMatrix(Vector*, Matrix const*)
    // const, ApplyMatrixNoWeighted (x2), ApplyMatrixNoTransport (x2), ApplyQuaternion (x2),
    // GetEuler(Matrix const*), SquaredDistanceToTriangle, IsInsideWithAngle.
    float x, y, z, w;  // 0x00
};
static_assert(sizeof(Vector) == 0x10);

// Aska::Quaternion: guest size 0x10; {x, y, z, w} with w the scalar part (Create(Vector const*):
// w = cos(angle / 2); port/decomp/math/quaternion.c).
class Quaternion {
public:
    // Create(Vector const* axis_angle): the rotation by axis_angle->w radians about the (unit)
    // axis xyz.
    void Create(const Vector* axis_angle);
    // Create(Matrix const*): the rotation of the matrix's upper 3x3.
    void Create(const Matrix* m);
    // The rotation by the Euler angles (x, y, z) applied in `order`.
    void CreateFromEuler(float x, float y, float z, EnumRotateType order);
    // this = slerp(q1, q2, t), normalized; through the shorter arc (q2 negated when the dot is < 0).
    void Slerp(const Quaternion* q1, const Quaternion* q2, float t);
    // Guest code: Create(Vector const*, Vector const*), Mul(Quaternion*, int) const, Squad,
    // SquadSlerp, CalcEuler(Vector*, EnumRotateType) const, IsRotation, Ln, Exp, Intermediate.

    float x, y, z, w;  // 0x00
};
static_assert(sizeof(Quaternion) == 0x10);

// Aska::Matrix: guest size 0x40; m[row][col], the translation in column 3 (Framework::CMatrix::
// Translate writes floats 3, 7, 11; Vector::ApplyMatrix: out.x = dot(row 0, v)).
class Matrix {
public:
    // this = a * b (the 4x4 product).
    void Mul(const Matrix* a, const Matrix* b);
    // The Euler angles (out->x, y, z) of the rotation, for `order`.
    void CalcEuler(Vector* out, EnumRotateType order) const;
    // A view matrix looking from `eye` to `at` (+Z forward) with `up`, rolled by `roll` radians.
    void SetLookAtMatrixZPUp(const Vector* eye, const Vector* at, const Vector* up, float roll);
    // Inverts in place (Gauss-Jordan without pivoting; near-zero pivots replaced by +-1e-5).
    void Invert();
    // out = this * v (4x4; out may be v).
    void ApplyVector(Vector* out, const Vector* v) const;
    // Decomposes into position, rotation and scale (any out pointer may be null).
    void PutPRS(Vector* pos, Quaternion* rot, Vector* scale) const;
    // Guest code: InvertLowError (x2), RotateY, Create / CreateWithoutNormalize /
    // CreateWithNormalize (Quaternion const*[, Vector const*]), Mul(Matrix const*), MulFromLeft,
    // SetRotation, Rotate (x2), SetRotationByUnitVector, RotateByUnitVector, SetTranslate,
    // Translate, Scale, MakeClip, MakeClipToScreen, MulVector (x2),
    // SetLookAtMatrix{XP,XN,YP,YN,ZP,ZN}, SetProjectionShadowMatrixFor{OmniLight,DirectionalLight},
    // Lerp.

    float m[4][4];  // 0x00
};
static_assert(sizeof(Matrix) == 0x40);

// Aska::Matrix34: guest size 0x30; the top three rows of a Matrix (Matrix34::Mul,
// port/decomp/math/matrix34.c). All its methods are guest code.
class Matrix34 {
public:
    float m[3][4];  // 0x00
};
static_assert(sizeof(Matrix34) == 0x30);

// Aska::Segment: guest size 0x20; the points origin + t * direction, t in [0, 1]
// (Segment::SquaredDistance, port/decomp/math/primitives.c).
class Segment {
public:
    // The squared distance to `p`; *t (if not null) the parameter of the closest point.
    float SquaredDistance(const Vector* p, float* t) const;
    // The squared distance to `o` (>= 0); *t_this / *t_other (if not null) the parameters of the
    // closest points. A degenerate (zero-length) segment is treated as its origin.
    float SquaredDistance(const Segment* o, float* t_this, float* t_other) const;

    Vector m_origin;     // 0x00
    Vector m_direction;  // 0x10: end - origin (not normalized)
};
static_assert(offsetof(Segment, m_direction) == 0x10);
static_assert(sizeof(Segment) == 0x20);

// Aska::Sphere: guest size 0x10; the center with the radius in w (AABB::SetSphere copies
// floats 0-3 and spreads float 3 as the extents).
class Sphere {
public:
    Vector m_center_radius;  // 0x00: x, y, z the center, w the radius
};
static_assert(sizeof(Sphere) == 0x10);

// Aska::Plane: guest size 0x20; a point on the plane and its unit normal (Plane::ApplyMatrix
// writes the transformed point at 0 and the renormalized normal at 0x10, w = 1).
class Plane {
public:
    // Guest code: ApplyMatrix(Matrix const*), ComputeVertices(Vector*, float) const.
    Vector m_point;   // 0x00
    Vector m_normal;  // 0x10
};
static_assert(offsetof(Plane, m_normal) == 0x10);
static_assert(sizeof(Plane) == 0x20);

// Aska::AABB: guest size 0x20; center and half extents (AABB::SetBox, SetSphere: extents at
// 0x10; SetBox stores 1e30 in the extents' w).
class AABB {
public:
    // Guest code: ComputeVertices (x2), SquaredDistance, CalcDistance (x2), ClipIntersection,
    // IsContained, CalcOverlappedStatus (x2), Separate*, SetCone, SetCapsule, SetBox, SetSphere.
    Vector m_center;  // 0x00
    Vector m_extent;  // 0x10: half sizes
};
static_assert(offsetof(AABB, m_extent) == 0x10);
static_assert(sizeof(AABB) == 0x20);

// Aska::AABB_MinMax: guest size 0x20; the min and max corners (AABB_MinMax::CalcDistance).
class AABB_MinMax {
public:
    // Guest code: SquaredDistance (x2), CalcDistance.
    Vector m_min;  // 0x00
    Vector m_max;  // 0x10
};
static_assert(offsetof(AABB_MinMax, m_max) == 0x10);
static_assert(sizeof(AABB_MinMax) == 0x20);

// Aska::Box: guest size 0x50; an oriented box: center, half extents along its three axes, the
// axes (AABB::SetBox: |extent.x * axis0| + ...; Box::ComputeVertices).
class Box {
public:
    // Guest code: ComputeVertices, ComputePlanes, SquaredDistance (Line / Segment / Vector),
    // CaseNoZeros, Case0, Case00, Case000, CalcDistance (x2), CalcDistanceByAABB, IsContained,
    // CalcOverlappedStatus, IsIntersected, Face.
    Vector m_center;   // 0x00
    Vector m_extent;   // 0x10: half sizes along m_axis[0..2]
    Vector m_axis[3];  // 0x20
};
static_assert(offsetof(Box, m_extent) == 0x10);
static_assert(offsetof(Box, m_axis) == 0x20);
static_assert(sizeof(Box) == 0x50);

// Framework::CVector / CQuaternion / CMatrix: the framework's wrappers, with the Aska types'
// layouts (Framework::CMatrix::PutPRS is a tail call into Aska::Matrix::PutPRS; CQuaternion::Matrix
// calls Aska::Matrix::Create with its `this`). Their methods are guest code.
class CVector {
public:
    float x, y, z, w;  // 0x00
};
static_assert(sizeof(CVector) == 0x10);
class CQuaternion {
public:
    float x, y, z, w;  // 0x00
};
static_assert(sizeof(CQuaternion) == 0x10);
class CMatrix {
public:
    float m[4][4];  // 0x00
};
static_assert(sizeof(CMatrix) == 0x40);

}  // namespace soa::native::math

#endif  // SOA_NATIVE_MATH_LAYOUT_H
