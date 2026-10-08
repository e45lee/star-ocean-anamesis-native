// dynamics_layout.h: the guest data layouts of the `dynamics` subsystem (Aska's own dynamics: cloth, joints, collision).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/dynamics/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types dynamics` turns the structs into port/decomp/dynamics/types.json for Ghidra.
//
// Value types are math's (math_layout.h: Vector {x, y, z, w}, Matrix row-major with v' = M v,
// Segment {origin, direction}); the scene node a primitive follows is render's HierarchicalObject.
#ifndef SOA_NATIVE_DYNAMICS_LAYOUT_H
#define SOA_NATIVE_DYNAMICS_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../math/math_layout.h"
#include "../render/render_layout.h"

namespace soa::native::dynamics {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

using Vector = math::Vector;
using Matrix = math::Matrix;
using Segment = math::Segment;
using HierarchicalObject = render::HierarchicalObject;

// The HierarchicalObject slots the primitives call (render_layout.h's list): 19 WorldMatrix (&the
// world matrix), 21 MakeMatrix (when m_hoc.m_flags bit 0 says the matrix is stale).
inline constexpr int kSlotWorldMatrix = 19;
inline constexpr int kSlotMakeMatrix = 21;
// HierarchicalObjectContainer::m_flags bits the primitives read and set.
inline constexpr u8 kHocMatrixStale = 0x01;   // bit 0: MakeMatrix before reading the world matrix
inline constexpr u8 kHocInverseValid = 0x04;  // bit 2: HierarchicalObject::m_invWorld is current

// ---- the collision shapes (DYNAMICS_*) ----
//
// The shape a DynamicsPrimitive embeds at +0x60 (DynamicsPrimitive::m_data points at it): the
// DynamicsCapsule / DynamicsCube thunks pass `this + 0x60` to DYNAMICS_CAPSULE / DYNAMICS_CUBE
// (port/decomp/dynamics/primitives.c). Its head is the primitive's collision parameters, read by
// ArticulatedDynamicsManagerBase::CollisionAndConstraint through m_data: two floats it passes on
// to the response (+0x00, +0x04) and the ArticulatedDynamicsManager that owns the primitive (+0x10;
// collisions within one ADM are filtered).
class DYNAMICS_PRIMITIVE {
public:
    float m_response0;  // 0x00: CollisionAndConstraint's response argument (with m_response1)
    float m_response1;  // 0x04
    u8 unk_08[8];       // 0x08
    void* m_owner;      // 0x10: the ArticulatedDynamicsManager the primitive belongs to (or none)
    u8 unk_18[8];       // 0x18
};
static_assert(offsetof(DYNAMICS_PRIMITIVE, m_response1) == 0x04);
static_assert(offsetof(DYNAMICS_PRIMITIVE, m_owner) == 0x10);
static_assert(sizeof(DYNAMICS_PRIMITIVE) == 0x20);

// Aska::DYNAMICS_CAPSULE: a capsule (a segment swept by a sphere). Two roles: as `this`
// (DynamicsCapsule + 0x60) its segment is m_segment (+0x20); as the `other` operand of
// TestIntersection (a joint's capsule CollisionAndConstraint builds on its stack, or another
// primitive's) only m_otherSegment (+0x40) and m_radius are read. In a DynamicsCapsule +0x50 is the
// local axis (DynamicsCapsule::Run). Layout from DynamicsCapsule::Run / Update and the
// TestIntersection family (primitives.c, adm_templates.c CollisionAndConstraint's stack capsule).
class DYNAMICS_CAPSULE {
public:
    // Capsule vs capsule (this: m_segment, other: m_otherSegment). On contact: *normal the unit
    // direction from this capsule's closest point to the other's (w = 1), *t the other segment's
    // parameter, *depth (r + r') - distance; returns true. The bool is unused.
    bool TestIntersection(DYNAMICS_CAPSULE* other, bool unused, Vector* normal, float* t, float* depth);
    // Keeps the point p (radius r) inside the capsule: when it is farther out than radius - r,
    // *out = p moved back onto that surface (w = 1); returns whether it moved.
    bool TestIntersection(const Vector* p, float r, Vector* out);
    // Guest code (not executed in the measured flows): TestIntersectionLocal, TestIntersectionSphere.

    DYNAMICS_PRIMITIVE m_head;   // 0x00
    Segment m_segment;           // 0x20: the world segment (Run: origin, then the unit-scaled axis)
    Segment m_otherSegment;      // 0x40: the segment read when this capsule is the `other` operand
    Vector m_velocity;           // 0x60: the origin's change over the last Run
    Vector m_current;            // 0x70: the origin at the last Run (Update interpolates back from it)
    float m_radius;              // 0x80
    u8 unk_84[0xc];              // 0x84
};
static_assert(offsetof(DYNAMICS_CAPSULE, m_segment) == 0x20);
static_assert(offsetof(DYNAMICS_CAPSULE, m_otherSegment) == 0x40);
static_assert(offsetof(DYNAMICS_CAPSULE, m_velocity) == 0x60);
static_assert(offsetof(DYNAMICS_CAPSULE, m_current) == 0x70);
static_assert(offsetof(DYNAMICS_CAPSULE, m_radius) == 0x80);
static_assert(sizeof(DYNAMICS_CAPSULE) == 0x90);

// Aska::DYNAMICS_CUBE: an oriented box (DynamicsCube + 0x60): center and half extents, the three
// world axes, the world matrix and its inverse, as DynamicsCube::Run copies them (primitives.c).
class DYNAMICS_CUBE {
public:
    // Keeps the point p (radius r) inside the box: in box space each coordinate beyond
    // +-(half - r) is clamped to it; when any was, *out is the clamped point back in world space
    // (w as transformed) and the result true.
    bool TestIntersection(const Vector* p, float r, Vector* out);
    // Guest code (not executed in the measured flows): TestIntersection(DYNAMICS_CAPSULE*, ...),
    // TestIntersectionLocal (FRECPE), TestIntersectionSphere.

    DYNAMICS_PRIMITIVE m_head;  // 0x00
    Vector m_center;            // 0x20: the world center
    Vector m_halfExtents;       // 0x30: property (CreateClone copies it)
    Vector m_axis[3];           // 0x40: the world X, Y, Z axes (unit length unless shorter than kEpsilon)
    Matrix m_world;             // 0x70: the node's world matrix
    Matrix m_invWorld;          // 0xb0: its inverse (the node's cached m_invWorld)
    Vector m_velocity;          // 0xf0: the center's change over the last Run
    Vector m_current;           // 0x100: the center at the last Run
};
static_assert(offsetof(DYNAMICS_CUBE, m_center) == 0x20);
static_assert(offsetof(DYNAMICS_CUBE, m_halfExtents) == 0x30);
static_assert(offsetof(DYNAMICS_CUBE, m_axis) == 0x40);
static_assert(offsetof(DYNAMICS_CUBE, m_world) == 0x70);
static_assert(offsetof(DYNAMICS_CUBE, m_invWorld) == 0xb0);
static_assert(offsetof(DYNAMICS_CUBE, m_velocity) == 0xf0);
static_assert(offsetof(DYNAMICS_CUBE, m_current) == 0x100);
static_assert(sizeof(DYNAMICS_CUBE) == 0x110);

// Aska::DYNAMICS_SPHERE (DynamicsSphere + 0x60): radius, center, velocity, current center.
// DynamicsSphere implements its tests itself on these fields (they aren't thunks).
class DYNAMICS_SPHERE {
public:
    DYNAMICS_PRIMITIVE m_head;  // 0x00
    float m_radius;             // 0x20
    u8 unk_24[0xc];             // 0x24
    Vector m_center;            // 0x30
    Vector m_velocity;          // 0x40
    Vector m_current;           // 0x50
};
static_assert(offsetof(DYNAMICS_SPHERE, m_radius) == 0x20);
static_assert(offsetof(DYNAMICS_SPHERE, m_center) == 0x30);
static_assert(offsetof(DYNAMICS_SPHERE, m_velocity) == 0x40);
static_assert(offsetof(DYNAMICS_SPHERE, m_current) == 0x50);
static_assert(sizeof(DYNAMICS_SPHERE) == 0x60);

// The plane's shape (DynamicsPlane + 0x60; no class of that name has functions): unit normal,
// a point, velocity, current point.
class DYNAMICS_PLANE {
public:
    DYNAMICS_PRIMITIVE m_head;  // 0x00
    Vector m_normal;            // 0x20: the node's Y axis (m_vUnitY), unit length unless shorter than kEpsilon
    Vector m_point;             // 0x30
    Vector m_velocity;          // 0x40
    Vector m_current;           // 0x50
};
static_assert(offsetof(DYNAMICS_PLANE, m_normal) == 0x20);
static_assert(offsetof(DYNAMICS_PLANE, m_point) == 0x30);
static_assert(sizeof(DYNAMICS_PLANE) == 0x60);

// ---- the primitives (Aska::DynamicsPrimitive and its shapes) ----
//
// Aska::DynamicsPrimitive: a collision shape following a scene node (m_handler). Layout from
// DynamicsCube::CreateClone (operator new(0x170); 0x30 the local position (0, 0, 0, 1), 0x50 =
// &the shape at 0x60) and the Run / Update / TestIntersection members (primitives.c).
// vtable (_ZTVN4Aska17DynamicsPrimitiveE): ... 13 Run(int) (DynamicsPrimitiveElement), the
// primitives' own Run() / Update(float, bool) / Reset() and, at byte offsets 0x80 / 0x88 / 0x90 / 0x98,
// TestIntersection(DYNAMICS_CAPSULE*, ...), TestIntersectionLocal, TestIntersectionSphere,
// TestIntersection(Vector const*, float, Vector*) (CollisionAndConstraint calls 0x80, 0x88, 0x98).
class DynamicsPrimitive {
public:
    const void* vtable;              // 0x00
    u8 unk_08[0x18];                 // 0x08: IAnimatable's (0x18: 1 at construction)
    HierarchicalObject* m_handler;   // 0x20: the node the shape follows (none: Run does nothing)
    u8 unk_28[8];                    // 0x28
    Vector m_localPosition;          // 0x30: in the node's space ((0, 0, 0, 1) at construction)
    u8 unk_40[0x10];                 // 0x40
    DYNAMICS_PRIMITIVE* m_data;      // 0x50: &the shape at 0x60
    u8 unk_58[8];                    // 0x58
};
static_assert(offsetof(DynamicsPrimitive, m_handler) == 0x20);
static_assert(offsetof(DynamicsPrimitive, m_localPosition) == 0x30);
static_assert(offsetof(DynamicsPrimitive, m_data) == 0x50);
static_assert(sizeof(DynamicsPrimitive) == 0x60);

// Aska::DynamicsSphere: guest size 0xc0 (CreateClone: operator new(0xc0)).
class DynamicsSphere {
public:
    void Run();                         // the center from the node (ApplyMatrix), velocity, current
    void Update(float t, bool end);     // the center interpolated back: current - (1 - t) velocity
    // As DYNAMICS_CAPSULE's, with the sphere's center as the other's point and m_otherSegment;
    // *normal from the center to the capsule (w the capsule direction's w).
    bool TestIntersection(DYNAMICS_CAPSULE* other, bool unused, Vector* normal, float* t, float* depth);
    // Keeps p (radius r) inside the sphere: *out = p moved back (w = p's w).
    bool TestIntersection(const Vector* p, float r, Vector* out);

    DynamicsPrimitive base;   // 0x00
    DYNAMICS_SPHERE m_shape;  // 0x60
};
static_assert(offsetof(DynamicsSphere, m_shape) == 0x60);
static_assert(sizeof(DynamicsSphere) == 0xc0);

// Aska::DynamicsCapsule: guest size 0xf0 (CreateClone: operator new(0xf0)).
class DynamicsCapsule {
public:
    void Run();                      // the segment from the node: origin, the axis through the scale-free rotation
    void Update(float t, bool end);  // the origin interpolated back (end: the current one, w = 1)

    DynamicsPrimitive base;    // 0x00
    DYNAMICS_CAPSULE m_shape;  // 0x60 (m_shape.m_otherSegment.m_direction, 0xb0: the local axis)
};
static_assert(offsetof(DynamicsCapsule, m_shape) == 0x60);
static_assert(sizeof(DynamicsCapsule) == 0xf0);

// Aska::DynamicsCube: guest size 0x170 (CreateClone: operator new(0x170)).
class DynamicsCube {
public:
    void Run();                      // center, axes, world matrix and its (cached) inverse from the node
    void Update(float t, bool end);  // the center interpolated back

    DynamicsPrimitive base;  // 0x00
    DYNAMICS_CUBE m_shape;   // 0x60
};
static_assert(offsetof(DynamicsCube, m_shape) == 0x60);
static_assert(sizeof(DynamicsCube) == 0x170);

// Aska::DynamicsPlane: guest size 0xc0 (its fields end at 0xc0).
class DynamicsPlane {
public:
    void Run();                      // the point from the node, the normal from its Y axis
    void Update(float t, bool end);  // the point interpolated back
    // Keeps p (radius r) on the normal's side: when its distance is below r, *out = p pushed out
    // along the normal (w = p's w).
    bool TestIntersection(const Vector* p, float r, Vector* out);

    DynamicsPrimitive base;  // 0x00
    DYNAMICS_PLANE m_shape;  // 0x60
};
static_assert(offsetof(DynamicsPlane, m_shape) == 0x60);
static_assert(sizeof(DynamicsPlane) == 0xc0);

}  // namespace soa::native::dynamics

#endif  // SOA_NATIVE_DYNAMICS_LAYOUT_H
