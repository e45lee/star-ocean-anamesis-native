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
using Quaternion = math::Quaternion;
using Matrix = math::Matrix;
using Segment = math::Segment;
using HierarchicalObject = render::HierarchicalObject;
using HierarchicalObjectContainer = render::HierarchicalObjectContainer;

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

// ---- the articulated dynamics (ADM: joint chains: hair, cloth, accessories) ----

class ADMJoint;

// Aska::ADM_CALC_DATA: a joint's transform as the solver builds it (MatrixCalcFunc's inputs and
// output), 0xa0 bytes: ADMJoint + 0xb0, and ArticulatedDynamicsManagerBase's array at +0xa0
// (stride 0xa0; MatrixPreFixAndMotionBlend). ExternalForce reads the matrix's translation column.
// Layout from ADMJoint::InitCalcData / Init (port/decomp/dynamics/adm.c), ArticulatedDynamicsManager
// Base::PrepareCalc's MatrixCalcFunc arguments.
class ADM_CALC_DATA {
public:
    Matrix m_matrix;           // 0x00: MatrixCalcFunc's result (the joint's world matrix)
    Vector m_position;         // 0x40: local translation (the node's position, or its pivot form)
    Quaternion m_rotation;     // 0x50: the node's posture
    Vector m_scale;            // 0x60: the node's scale
    Quaternion m_orientation;  // 0x70: the node's joint orientation (InitCalcData: node + 0x90)
    // 0x80: the parent's calc data (its m_matrix and m_scale are MatrixCalcFunc's parent arguments);
    // a root's points at a buffer ADMJoint::PrepareCalc fills with the node parent's world matrix.
    ADM_CALC_DATA* m_parent;
    u8 unk_88[0x18];           // 0x88
};
static_assert(offsetof(ADM_CALC_DATA, m_position) == 0x40);
static_assert(offsetof(ADM_CALC_DATA, m_rotation) == 0x50);
static_assert(offsetof(ADM_CALC_DATA, m_scale) == 0x60);
static_assert(offsetof(ADM_CALC_DATA, m_orientation) == 0x70);
static_assert(offsetof(ADM_CALC_DATA, m_parent) == 0x80);
static_assert(sizeof(ADM_CALC_DATA) == 0xa0);

// A joint's link to another joint (ADMJoint::m_links, 0x50 each; the ADM's own link array at +0x78
// has the same form): flags at +0x20 (bit 4: keep the rest length current), the rest length at
// +0x28, the two joints at +0x40 / +0x48 (PrepareCalc measures to +0x48).
class ADMLink {
public:
    Vector m_offset;   // 0x00: flags bit 2: the link's segment starts there (in the joint's frame)
    Vector m_localPoint;  // 0x10: TestIntersectionLocal's point argument
    u8 m_flags;        // 0x20: bit 4 the length follows the joints (ADMJoint::PrepareCalc)
    u8 m_mode;         // 0x21: the ADM's links: SolveLink's mode (0 NEON form, 1 exact)
    u8 unk_22[2];      // 0x22
    float m_capsuleRadius;  // 0x24: the link's capsule against the collision primitives
    float m_length;    // 0x28
    float m_friction;  // 0x2c: a contact adds m_friction * response to both joints' m_contactFriction
    float m_bounce;    // 0x30: a fast contact's depth is scaled by (m_bounce * response + 1)
    float m_stiffness; // 0x34: the ADM's links: SolveLink's k1
    float m_sweepStart;  // 0x38: flags bit 1: only [start, end] of the segment collides
    float m_sweepEnd;    // 0x3c
    ADMJoint* m_joint0;  // 0x40
    ADMJoint* m_joint1;  // 0x48: the other end (PrepareCalc sets its m_lengthDirty)
};
static_assert(offsetof(ADMLink, m_localPoint) == 0x10);
static_assert(offsetof(ADMLink, m_flags) == 0x20);
static_assert(offsetof(ADMLink, m_capsuleRadius) == 0x24);
static_assert(offsetof(ADMLink, m_sweepStart) == 0x38);
static_assert(offsetof(ADMLink, m_length) == 0x28);
static_assert(offsetof(ADMLink, m_friction) == 0x2c);
static_assert(offsetof(ADMLink, m_bounce) == 0x30);
static_assert(offsetof(ADMLink, m_mode) == 0x21);
static_assert(offsetof(ADMLink, m_stiffness) == 0x34);
static_assert(offsetof(ADMLink, m_joint0) == 0x40);
static_assert(offsetof(ADMLink, m_joint1) == 0x48);
static_assert(sizeof(ADMLink) == 0x50);

// Aska::ADMJoint: one simulated joint, 0x1c0 bytes (the ADM's joint array: new[] of count * 0x1c0;
// ArticulatedDynamicsManager::CreateClone, the loops' stride). It follows a scene node (m_node, the
// node's HierarchicalObjectContainer: position 0x50, posture 0x60, scale 0x70, m_param9 0x80 the
// pivot base, joint orientation 0x90, m_owner 0xe8, m_flags 0xf8). Layout from InitCalcData, Init,
// DefaultParam, PrepareCalc, Flush, ExternalForce (adm.c) and the ADM templates (adm_templates.c).
class ADMJoint {
public:
    // The node's state into the joint (m_calc's position / rotation / scale), the parent's world
    // matrix into a root's parent buffer, the links' lengths.
    void PrepareCalc();
    // The joint's result back into the node (position, the posture when m_writesPosture, scale).
    void Flush();
    // One explicit step of gravity (g along -y when m_flags1 bit 0), damping (bit 1 or `full`:
    // velocity scaled by min(rate / mass, max_rate)) and an external acceleration (bit 6) over dt;
    // a fixed joint (m_flags0 bit 0) takes calc's translation instead.
    void ExternalForce(float dt, float max_rate, float g, const Vector* ext, ADM_CALC_DATA* calc, bool full);

    const void* vtable;          // 0x00
    u8 unk_08[8];                // 0x08
    Vector m_position;           // 0x10: the simulated position (w = 1)
    Vector m_prevPosition;       // 0x20
    Vector m_rootTarget;         // 0x30: a fixed root's animated position at the frame's first step (InterpolateRoot)
    Vector m_rootLocal;          // 0x40: its local position then
    Vector m_velocity;           // 0x50
    Quaternion m_prevRotation;   // 0x60
    Quaternion m_rotation70;     // 0x70
    Quaternion m_rotation80;     // 0x80: the rotation when it last changed (PrepareCalc(float)'s reset)
    Vector m_contactNormal;      // 0x90: the step's contact normals summed ((0, 0, 0, 1) each step: PreprocessBeforeInternalForce)
    Vector m_pivot;              // 0xa0: the pivot offset (m_hasPivot)
    ADM_CALC_DATA m_calc;        // 0xb0 (its m_parent at 0x130)
    u8* m_constraints;           // 0x150: indices into the ADM's constraint list
    u32 m_constraintCount;       // 0x158
    u8 unk_15c[4];               // 0x15c
    ADMLink* m_links;            // 0x160
    u32 m_linkCount;             // 0x168
    u8 unk_16c[4];               // 0x16c
    float m_param170;            // 0x170: 0.03 by default (DefaultParam)
    float m_blendWeight;         // 0x174: scales the ADM's motion blend (PrepareCalc(float))
    float m_damping;             // 0x178: ExternalForce's rate
    float m_dampingDown;         // 0x17c: the rate while falling (m_dampDownwards and velocity.y < 0)
    float m_mass;                // 0x180: 1 by default; damping only when > 0; the link solver's weight
    float m_stiffness;           // 0x184: the link solver's (fast mode) stiffness
    float m_collisionRadius;     // 0x188: against the constraints and the land (scaled by Scale)
    float m_contactFriction;     // 0x18c: the step's contact friction summed (0 each step)
    ADMJoint* m_parentJoint;     // 0x190: the joint the IK turns for this one (StandardIK)
    u8 m_lengthDirty;            // 0x198: set when a link's length was measured to it
    u8 m_isRoot;                 // 0x199 (SetRoot)
    u8 m_writesPosture;          // 0x19a: the node has a parent (Init): Flush writes the posture
    u8 m_dampDownwards;          // 0x19b
    u8 m_flags0;                 // 0x19c: bit 0 fixed (follows the animation)
    u8 m_flags1;                 // 0x19d: bit 0 gravity, bit 1 damping, bit 6 external acceleration
    u8 m_index19e;               // 0x19e
    u8 m_contact;                // 0x19f: bit 0 touched this step, bit 1 also its own group's (0 each step); UpdateVelocity damps when set, StandardIK scales m_contactDamping by 0.9 (at least 0.6) after bit 1
    u8 unk_1a0[0x10];            // 0x1a0
    HierarchicalObjectContainer* m_node;  // 0x1b0
    float m_contactDamping;      // 0x1b8: 0.8 each step
    u8 m_hasPivot;               // 0x1bc: the position is (node m_param9 + position) + pivot rotated
    u8 unk_1bd[3];               // 0x1bd
};
static_assert(offsetof(ADMJoint, m_position) == 0x10);
static_assert(offsetof(ADMJoint, m_prevPosition) == 0x20);
static_assert(offsetof(ADMJoint, m_rootTarget) == 0x30);
static_assert(offsetof(ADMJoint, m_rootLocal) == 0x40);
static_assert(offsetof(ADMJoint, m_velocity) == 0x50);
static_assert(offsetof(ADMJoint, m_prevRotation) == 0x60);
static_assert(offsetof(ADMJoint, m_rotation80) == 0x80);
static_assert(offsetof(ADMJoint, m_pivot) == 0xa0);
static_assert(offsetof(ADMJoint, m_calc) == 0xb0);
static_assert(offsetof(ADMJoint, m_constraints) == 0x150);
static_assert(offsetof(ADMJoint, m_constraintCount) == 0x158);
static_assert(offsetof(ADMJoint, m_links) == 0x160);
static_assert(offsetof(ADMJoint, m_linkCount) == 0x168);
static_assert(offsetof(ADMJoint, m_blendWeight) == 0x174);
static_assert(offsetof(ADMJoint, m_damping) == 0x178);
static_assert(offsetof(ADMJoint, m_mass) == 0x180);
static_assert(offsetof(ADMJoint, m_stiffness) == 0x184);
static_assert(offsetof(ADMJoint, m_parentJoint) == 0x190);
static_assert(offsetof(ADMJoint, m_lengthDirty) == 0x198);
static_assert(offsetof(ADMJoint, m_isRoot) == 0x199);
static_assert(offsetof(ADMJoint, m_flags0) == 0x19c);
static_assert(offsetof(ADMJoint, m_flags1) == 0x19d);
static_assert(offsetof(ADMJoint, m_node) == 0x1b0);
static_assert(offsetof(ADMJoint, m_hasPivot) == 0x1bc);
static_assert(sizeof(ADMJoint) == 0x1c0);

// The ADM's local helpers (no symbols; after Functor_ExternalForceEmitterCalculation<ADM>):
// static functions of the solver, bound by address (addresses.txt).
struct ADMSolver {
    // FUN_02429994: the distance constraint between two joints (rest length `rest`): each moves
    // along their direction by its share (the other's weight over the sum; a fixed joint takes
    // none). Mode 1: exact (FSQRT, scaled by k1 * k2); mode 0: the NEON form (FRSQRTE / FRECPE with
    // one Newton step, scaled by a's m_stiffness, w = 1); other modes: nothing.
    static void SolveLink(u8 mode, ADMJoint* a, ADMJoint* b, float rest, float k1, float k2);
    // FUN_0242a9f4: a contact between joints a and b found by CollisionAndConstraint (t: the
    // contact's parameter along the pair, depth, normal *n): the normal summed into both joints'
    // m_contactNormal, the link's friction into m_contactFriction, and a and / or b pushed out by
    // depth * n by their shares (a fixed joint none; a fast contact pushed further: m_bounce).
    static void ResolveContact(ADMLink* link, ADMJoint* a, ADMJoint* b, const Vector* n, float t, float depth, float response0,
                               float response1, float speed, float dt);
    // FUN_0242ac84: the joint's velocity from its step ((position - previous) * inv_dt; `rest`:
    // zero), the tangential part reduced by the contact friction, damped when touched; the previous
    // rotation from calc.
    static void UpdateVelocity(ADMJoint* j, ADM_CALC_DATA* calc, bool rest, float inv_dt);
    // FUN_0242a08c: *out = calc's rotation turned by the angle between the directions from calc's
    // position to the child's animated position (child_calc) and to its simulated one (in calc's
    // space: the rotation axis through calc's inverse), unless the child is fixed (m_flags0 bit 2) or
    // the angle is below the one cos(angle) = 1 - eps / factor allows. All NEON: FRSQRTE / FRECPE
    // with Newton steps, a vectorized acos and sin / cos polynomials.
    static void AimRotation(Quaternion* out, ADM_CALC_DATA* calc, ADMJoint* child, ADM_CALC_DATA* child_calc, float factor);
    // FUN_02429d78: calc's rotation aimed (AimRotation), then slerped towards the joint's m_rotation70
    // by its m_param170 (m_flags1 bit 2) and towards m_rotation80 by m_blendWeight * blend, both
    // rates adjusted to `steps` sub-steps of length dt.
    static void BlendRotation(ADMJoint* j, ADM_CALC_DATA* calc, ADMJoint* child, ADM_CALC_DATA* child_calc, u32 steps, float blend, float dt);
};

// A root of the ADM's joint chains: its first joint's index and the number of joints in the chain
// (consecutive in the joint array). ArticulatedDynamicsManagerBase::m_roots.
struct ADMRoot {
    u32 m_first;  // 0x0
    u32 m_count;  // 0x4
};
static_assert(sizeof(ADMRoot) == 8);

// A node of the ADM's extra collision list (AddExtraCollision*): next at +0x10, the primitive at
// +0x38; the list's head (a sentinel) is the ADM's m_extraCollisions.
struct ADMExtraNode {
    u8 unk_00[0x10];          // 0x00
    ADMExtraNode* m_next;     // 0x10
    u8 unk_18[0x20];          // 0x18
    DynamicsPrimitive* m_primitive;  // 0x38
};
static_assert(offsetof(ADMExtraNode, m_next) == 0x10);
static_assert(offsetof(ADMExtraNode, m_primitive) == 0x38);

// Aska::ArticulatedDynamicsManagerBase: a joint chain set (ArticulatedDynamicsManager: 0x1c0,
// ArticulatedDynamicsManagerMP: 0x200; their CreateClone). Layout from PrepareCalc(float), Flush,
// Simulate and the ADM templates (adm.c, adm_templates.c); the rest is padding until recovered.
class ArticulatedDynamicsManagerBase {
public:
    // The joints from their nodes: the motion-blend write-back, ADMJoint::PrepareCalc, MatrixCalcFunc
    // per joint, the gravity through the node; then the velocities (from the motion over dt) or, at
    // rest, the pose reset.
    void PrepareCalc(float dt);
    // The joints back into their nodes (ADMJoint::Flush) unless just reset; m_flushed set.
    void Flush();

    // The templates (instantiated for ArticulatedDynamicsManager, the one that runs), static
    // functions of the guest taking the ADM as their first argument:
    // the primitives' Update(t, last step) for step `step` of `steps` (all the collision /
    // constraint lists).
    static void CollisionSetting(ArticulatedDynamicsManagerBase* adm, u32 steps, u32 step);
    // The fixed roots moved towards their animated position over the remaining steps, their chains'
    // matrices recomputed.
    static void InterpolateRoot(ArticulatedDynamicsManagerBase* adm, ADMJoint* first, ADMJoint* end, float dt, u32 steps, u32 step);
    // A step's start: InterpolateRoot, CollisionSetting, then per joint the motion blend
    // (MatrixPreFixAndMotionBlend) or the reset of the step's contact state, MatrixCalcFunc and
    // ExternalForce; the force emitters.
    static void PreprocessBeforeInternalForce(ArticulatedDynamicsManagerBase* adm, ADMJoint* first, ADMJoint* end, float dt, float inv_dt,
                                              u32 steps, u32 step, bool simulating);
    // The solver loop: steps x (Preprocess, the link constraints (m_iterations), IK, collisions),
    // repeated up to `repeat` times until every joint is slower than `rest_speed`.
    static void SimulateMain(ArticulatedDynamicsManagerBase* adm, ADMJoint* first, ADMJoint* end, u32 iterations, s32 step0, s32 steps,
                             u32 ik_steps, u32 repeat, float dt, float inv_dt, float rest_speed);
    // CollisionAndConstraint<ADM>: per joint, each colliding link's capsule (world or joint space,
    // swept) against the collision primitives (ResolveContact on a contact, SolveLink after one),
    // then the joint against the ADM's / the world's constraints and the land.
    static void CollisionAndConstraint(ArticulatedDynamicsManagerBase* adm, ADMJoint* first, ADMJoint* end, u32 collisions, u32 constraints,
                                       float dt);
    // StandardIK<ADM, true>: per root chain, the joints' calc data from their simulated positions,
    // each IK joint's parent turned towards it (BlendRotation), the velocities (UpdateVelocity).
    static void StandardIK(ArticulatedDynamicsManagerBase* adm, u32 steps, float dt, float inv_dt);
    // ArticulatedDynamicsManager::Simulate: the step count and length from dt and the base dt.
    bool Simulate(float dt, u32 repeat, float rest_speed);

    const void* vtable;              // 0x00
    u8 unk_08[0x38];                 // 0x08
    Vector m_gravityWorld;           // 0x40: m_gravity through the gravity node's rotation
    Vector m_gravity;                // 0x50
    s16 m_jointCount;                // 0x60
    s16 m_linkCount;                 // 0x62
    s16 m_collisionCount;            // 0x64
    s16 m_constraintCount;           // 0x66
    u8 unk_68[8];                    // 0x68
    ADMJoint* m_joints;              // 0x70: m_jointCount of them
    ADMLink* m_linkList;             // 0x78: m_linkCount of them
    u8 unk_80[8];                    // 0x80
    u32 m_emitters;                  // 0x88: the force emitters apply
    u32 m_emitterSeed;               // 0x8c: + 0x56b46fd1 after each use
    u8* m_hitFlags;                  // 0x90: CollisionAndConstraint marks the joints' groups (ADMJoint::m_index19e)
    u8 unk_98[2];                    // 0x98
    u8 m_ik;                         // 0x9a: bit 0: the IK form of the step end (StandardIK<true>)
    u8 m_solverMode;                 // 0x9b: 1 links forward and back m_iterations times; 2 the IK form, iterated per joint
    u8 unk_9c[4];                    // 0x9c
    ADM_CALC_DATA* m_rootCalc;       // 0xa0: one per root (stride 0xa0)
    ADMRoot* m_roots;                // 0xa8
    s32 m_rootCount;                 // 0xb0
    u8 unk_b4[0x24];                 // 0xb4
    u8 m_enabled;                    // 0xd8
    u8 m_skipFlush;                  // 0xd9: set by PrepareCalc's velocity pass, cleared by the pose reset; while set Flush writes nothing and PrepareCalc skips the gravity node
    u8 m_resetVelocity;              // 0xda: velocities from the motion every PrepareCalc
    u8 unk_db;                       // 0xdb
    u8 m_motionBlend;                // 0xdc: write the blended pose back first (m_blendRate)
    u8 m_dtDiv;                      // 0xdd: with m_bDtDiv: the steps scale with dt / m_fBaseDt
    u8 m_worldCollision;             // 0xde: the world collision / constraint lists apply
    u8 unk_df;                       // 0xdf
    u8 m_flushed;                    // 0xe0: Flush ran (cleared with 0xe1 by PrepareCalc)
    u8 m_resetPending;               // 0xe1: the pose reset may run; Simulate runs only when set
    u8 m_simulating;                 // 0xe2: passed to Preprocess (ExternalForce's full damping)
    u8 unk_e3;                       // 0xe3
    u8 m_resetRequest;               // 0xe4
    u8 unk_e5[7];                    // 0xe5
    s32 m_steps;                     // 0xec
    float m_blendRate;               // 0xf0: below kBlendFull the ADM blends with the motion
    float m_gravityScale;            // 0xf4: ExternalForce's g
    u8 unk_f8[8];                    // 0xf8
    render::RenderableObject* m_model;  // 0x100: the model; while its m_renderFlags & 0x2101 the velocities follow the motion
    HierarchicalObject* m_gravityNode;  // 0x108: m_gravity is in its space
    u8 unk_110[8];                   // 0x110
    u32 m_moving;                    // 0x118: SimulateMain clears it when every joint came to rest
    u8 unk_11c[5];                   // 0x11c
    u8 m_dependentPrimitives;        // 0x121: UpdateDynamicsPrimitiveListWithDependencyOfADM each step
    u8 m_minTwoSteps;                // 0x122: at least two steps
    u8 unk_123[0xd];                 // 0x123
    void* m_landConstraint;          // 0x130: counts as one more constraint
    u8 unk_138[0x10];                // 0x138
    DynamicsPrimitive** m_collisions;   // 0x148: m_collisionCount
    DynamicsPrimitive** m_constraints;  // 0x150: m_constraintCount
    u8 unk_158[8];                   // 0x158
    ADMExtraNode m_extraCollisions;  // 0x160: the list's sentinel (its m_next at 0x170)
    u32 m_extraCollisionCount;       // 0x1a0
    u8 unk_1a4[4];                   // 0x1a4
};
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_gravityWorld) == 0x40);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_jointCount) == 0x60);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_joints) == 0x70);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_linkList) == 0x78);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_emitters) == 0x88);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_hitFlags) == 0x90);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_ik) == 0x9a);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_rootCalc) == 0xa0);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_rootCount) == 0xb0);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_enabled) == 0xd8);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_motionBlend) == 0xdc);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_flushed) == 0xe0);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_resetRequest) == 0xe4);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_steps) == 0xec);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_blendRate) == 0xf0);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_model) == 0x100);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_gravityNode) == 0x108);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_moving) == 0x118);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_dependentPrimitives) == 0x121);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_landConstraint) == 0x130);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_collisions) == 0x148);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_extraCollisions) == 0x160);
static_assert(offsetof(ArticulatedDynamicsManagerBase, m_extraCollisionCount) == 0x1a0);
static_assert(sizeof(ArticulatedDynamicsManagerBase) == 0x1a8);  // (recovered so far; ArticulatedDynamicsManager is 0x1c0)

}  // namespace soa::native::dynamics

#endif  // SOA_NATIVE_DYNAMICS_LAYOUT_H
