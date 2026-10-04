// bullet_layout.h: the guest data layouts of the `bullet` subsystem (Bullet Physics 2.7x and Aska's rigid-body wrapper).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/bullet/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types bullet` turns the structs into port/decomp/bullet/types.json for Ghidra.
#ifndef SOA_NATIVE_BULLET_LAYOUT_H
#define SOA_NATIVE_BULLET_LAYOUT_H

#include <cstddef>
#include <cstdint>

namespace soa::native::bullet {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// No natives yet (README.md: the recommendation is to leave Bullet on the guest). These are the
// layouts the investigation read, kept so a later wave starts from typed fields. Bullet's own classes
// are upstream 2.75's layouts except the constraints (README.md "The pin"); only the parts the
// wrapper touches are declared here.

// btTransform (Bullet 2.75, single precision, btVector3 = 4 floats): 0x40 bytes.
struct BtTransform {
    float basis[3][4];  // 0x00: btMatrix3x3, three btVector3 rows
    float origin[4];    // 0x30
};
static_assert(offsetof(BtTransform, origin) == 0x30);
static_assert(sizeof(BtTransform) == 0x40);

// btCollisionObject's head (2.75): what RigidBodyManager::Simulate reads of a btRigidBody.
struct BtCollisionObjectHead {
    const void* vtable;           // 0x00
    BtTransform m_worldTransform;  // 0x08: Simulate copies its rotation and origin to the Aska object
};
static_assert(offsetof(BtCollisionObjectHead, m_worldTransform) == 0x08);

// Aska::RigidBodyPrimitiveBase: guest size 0x48 (the .asf loader's arrays step by 0x48,
// AsfHandler::SetupRigidBodyPrimitive); layout from RigidBodyPrimitiveSphere::CreateBullet,
// LocalCreateBullet and RigidBodyManager::Simulate (port/decomp/bullet/aska_rigidbody.c).
// A TList node: the manager keeps one as its list's sentinel.
class RigidBodyPrimitiveBase {
public:
    const void* vtable;            // 0x00: _ZTVN4Aska22RigidBodyPrimitiveBaseE + 0x10 (or a subclass's)
    RigidBodyPrimitiveBase* prev;  // 0x08
    RigidBodyPrimitiveBase* next;  // 0x10
    u8 unk_18[8];                  // 0x18: the sentinel's byte 0x18 is set to 1 by the manager's ctor
    void* target;                  // 0x20: the Aska object driven by the body (set by SetupRigidBodyPrimitive)
    const void* chunk;             // 0x28: the 'DyPr' chunk entry (mass at +4, shape sizes at +0x30..)
    BtCollisionObjectHead* body;   // 0x30: btRigidBody (in the CreateBullet allocation)
    void* shape;                   // 0x38: btCollisionShape
    void* motion_state;            // 0x40: btDefaultMotionState
};
static_assert(offsetof(RigidBodyPrimitiveBase, next) == 0x10);
static_assert(offsetof(RigidBodyPrimitiveBase, target) == 0x20);
static_assert(offsetof(RigidBodyPrimitiveBase, body) == 0x30);
static_assert(offsetof(RigidBodyPrimitiveBase, motion_state) == 0x40);
static_assert(sizeof(RigidBodyPrimitiveBase) == 0x48);

// Aska::RigidBodyManager: guest size 0xa8 (operator new in Global::InstantiateRigidBodyManager);
// an Aska::Task (0x28 bytes) owning the Bullet world. Layout from its constructor, InitBullet,
// Run, Simulate and the destructor (port/decomp/bullet/aska_rigidbody.c).
class RigidBodyManager {
public:
    const void* vtable;                    // 0x00: _ZTVN4Aska16RigidBodyManagerE + 0x10
    u8 task_08[0x20];                      // 0x08: the rest of Aska::Task
    void* world;                           // 0x28: btDiscreteDynamicsWorld (0x178 bytes)
    void* collision_config;                // 0x30: btDefaultCollisionConfiguration (0xb0)
    void* dispatcher;                      // 0x38: btCollisionDispatcher (0x2988)
    void* broadphase;                      // 0x40: btDbvtBroadphase (0xe0)
    void* solver;                          // 0x48: btSequentialImpulseConstraintSolver (0xf0)
    const void* list_vtable;               // 0x50: Aska::TList<RigidBodyPrimitiveBase>
    RigidBodyPrimitiveBase list_sentinel;  // 0x58: the list's head node (next = first primitive)
    u32 count;                             // 0xa0: primitives in the list; Run(int) calls Simulate only when > 0
    u8 pad_a4[4];                          // 0xa4
};
static_assert(offsetof(RigidBodyManager, world) == 0x28);
static_assert(offsetof(RigidBodyManager, solver) == 0x48);
static_assert(offsetof(RigidBodyManager, list_sentinel) == 0x58);
static_assert(offsetof(RigidBodyManager, count) == 0xa0);
static_assert(sizeof(RigidBodyManager) == 0xa8);

}  // namespace soa::native::bullet

#endif  // SOA_NATIVE_BULLET_LAYOUT_H
