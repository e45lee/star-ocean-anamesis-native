// render_layout.h: the guest data layouts of the `render` subsystem (the GL renderer, shaders, materials, post-processing, cameras).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/render/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types render` turns the structs into port/decomp/render/types.json for Ghidra.
#ifndef SOA_NATIVE_RENDER_LAYOUT_H
#define SOA_NATIVE_RENDER_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../memory/memory_layout.h"

namespace soa::native::render {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// ---- Math value types (opaque here) ---------------------------------------------------------------
// Aska::Vector / Quaternion / Matrix are the math subsystem's (n-hash-math's math_layout.h: {x, y, z, w},
// {x, y, z, w} with w the scalar, m[4][4] with the translation in column 3), not on main yet. Until it
// lands these are opaque values of the guest's size (alignment 4, as there); swap them for
// `using MathVector = math::Vector;` etc. then.
struct MathVector { float f[4]; };       // Aska::Vector, 0x10
struct MathQuaternion { float f[4]; };   // Aska::Quaternion, 0x10
struct MathMatrix { float f[16]; };      // Aska::Matrix, 0x40
static_assert(sizeof(MathVector) == 0x10);
static_assert(sizeof(MathQuaternion) == 0x10);
static_assert(sizeof(MathMatrix) == 0x40);

// ---- Guest addresses (ELF vaddr; add main_lib()->base) of the statics the classes below use ------
inline constexpr u64 kVaddrGlobalObjectManager = 0x2cd0690;        // Aska::Global::m_pObjectManager
inline constexpr u64 kVaddrGlobalObjectManagerJobDispatcher = 0x2cd06d8;  // ...::m_pObjectManagerJobDispatcher
inline constexpr u64 kVaddrGlobalCameraManager = 0x2cce118;        // Aska::Global::m_pCameraManager
inline constexpr u64 kVaddrGlobalLightManager = 0x2cd04c0;         // Aska::Global::m_pLightManager
inline constexpr u64 kVaddrGlobalModifierManager = 0x2cd0608;      // Aska::Global::m_pModifierManager
inline constexpr u64 kVaddrGlobalTextureManager = 0x2d10ea8;       // Aska::Global::m_pTextureManager
inline constexpr u64 kVaddrGlobalRenderStateManager = 0x2cd08d8;   // Aska::Global::m_pRenderStateManager
inline constexpr u64 kVaddrGlobalRenderStatePool = 0x2d10d30;      // Aska::Global::m_pRenderStatePool
inline constexpr u64 kVaddrGlobalShaderLinkManager = 0x2d10d48;    // Aska::Global::m_pShaderLinkManager
inline constexpr u64 kVaddrGlobalShaderConstantBufferPool = 0x2d10d40;  // ...::m_pShaderConstantBufferPool
inline constexpr u64 kVaddrGlobalFrameBuffer = 0x2cd06f0;          // Aska::Global::m_pFrameBuffer
inline constexpr u64 kVaddrRenderDev = 0x2c01018;                  // Aska::g_pRenderDev (RenderDeviceGL*)
inline constexpr u64 kVaddrRenderThreadGPUSync = 0x2d10d38;        // Aska::RenderThread::m_pGPUSync
inline constexpr u64 kVaddrDefaultSphere = 0x2be6ea0;              // Aska::RenderableObject::m_vDefaultSphere (Vector)

// ---- The object hierarchy: IAnimatable -> AnimatableLinkElement -> Task -> HierarchicalObject -> RenderableObject
// Every scene object (AofObject, JointObject, Camera via AimingObject, the post-process objects, particles)
// is one of these. They are guest C++ classes with single inheritance except HierarchicalObject, which
// also derives from HierarchicalObjectContainer (the second base, with its own vptr, at +0x30). Here a
// base is the first member `base` (composition keeps the classes standard-layout); the guest's virtuals
// are listed in vtable order as plain members (slot k = the vtable's (k * 8)-th byte after the
// _ZTV symbol + 0x10). GetClassID(depth) returns the class id chain (u16 ids packed; 0xf000 =
// IAnimatable ends it): IAnimatable::IsThisIt walks it.

// Aska::IAnimatable: the root interface (only a vptr; port/decomp/render/hierarchical_object.c).
// vtable: 0 ~IAnimatable (D1), 1 ~IAnimatable (D0), 2 GetClassID(int) const (0xf000), 3 Clone(IAnimatable
// const*) (same class id), 4 CreateClone(IAnimatable const*) (null), 5 Get(unsigned long, void*) const
// (pure), 6 Set(unsigned long, void const*) (pure).
class IAnimatable {
public:
    void Dtor();                                         // ~IAnimatable()  _ZN4Aska11IAnimatableD2Ev
    void DtorDelete();                                   // ~IAnimatable()  _ZN4Aska11IAnimatableD0Ev
    u64 GetClassID(s32 depth) const;                     // slot 2
    bool Clone(const IAnimatable* src);                  // slot 3
    IAnimatable* CreateClone(const IAnimatable* src);    // slot 4
    bool Get(u64 id, void* out) const;                   // slot 5 (pure here)
    bool Set(u64 id, const void* in);                    // slot 6 (pure here)
    bool IsThisIt(u16 classId) const;                    // walks GetClassID(0..) for classId

    const void* vtable;  // 0x00
};
static_assert(sizeof(IAnimatable) == 0x08);

// Aska::AnimatableLinkElement: IAnimatable + a two-way link (Task's first base: its Get / Set are vtable
// slots 5 / 6 of Task; the links are zeroed by every constructor that inlines it).
class AnimatableLinkElement {
public:
    bool Get(u64 id, void* out) const;                   // slot 5  _ZNK4Aska21AnimatableLinkElement3GetEmPv
    bool Set(u64 id, const void* in);                    // slot 6

    IAnimatable base;                // 0x00
    AnimatableLinkElement* m_next;   // 0x08: the TaskManager's list (zeroed by the constructors)
    AnimatableLinkElement* m_prev;   // 0x10
};
static_assert(offsetof(AnimatableLinkElement, m_next) == 0x08);
static_assert(offsetof(AnimatableLinkElement, m_prev) == 0x10);
static_assert(sizeof(AnimatableLinkElement) == 0x18);

class TaskManager;  // Aska::TaskManager: the kernel subsystem's (opaque here)

// Aska::Task: a unit of per-frame work owned by a TaskManager (kernel). Guest size 0x28 (Task::CreateClone:
// operator new(0x28)); layout from the inlined constructor (RenderableObject::RenderableObject), ~Task,
// Remove, ChangeLevel, Clone, ForceDelete (port/decomp/render/hierarchical_object.c). The kernel
// subsystem owns Task (its TaskManager side); it is here because every renderable derives from it.
// vtable (_ZTVN4Aska4TaskE): 0-6 as IAnimatable / AnimatableLinkElement, 7 DeleteThis(DeleteManager*),
// 8 DeleteThisNextFrame, 9 DeleteThisAfterTwoFrames, 10 DeleteThisImmediately, 11 GetDefaultLevel() const
// (0x40), 12 MessageHandler(unsigned, int, void*, void*), 13 Run(int), 14 IsMulti() const,
// 15 OnDeleteFromTaskManager, 16 OnAddToTaskManager, 17 OnAddTopToTaskManager, 18 OnInsertToTaskManager.
class Task {
public:
    void DtorBase();                                     // ~Task()  _ZN4Aska4TaskD2Ev (removes itself: m_manager slot 8)
    void DtorDelete();                                   // ~Task()  _ZN4Aska4TaskD0Ev
    u64 GetClassID(s32 depth) const;                     // slot 2: 0xf000f001f002 chain
    bool Clone(const IAnimatable* src);                  // slot 3: copies m_level, m_flags24, m_flags26
    Task* CreateClone(const IAnimatable* src);           // slot 4
    void DeleteThis(memory::DeleteManager* dm);          // slot 7: dm (or Global::m_systemDeleteManager)->AddMain(this, 3, 0, 0)
    void DeleteThisNextFrame(memory::DeleteManager* dm); // slot 8: AddMain(this, 3, 1, 0)
    void DeleteThisAfterTwoFrames(memory::DeleteManager* dm);  // slot 9: AddMain(this, 3, 2, 0)
    void DeleteThisImmediately();                        // slot 10: vtable slot 1 (D0)
    u32 GetDefaultLevel() const;                         // slot 11
    u64 MessageHandler(u32 msg, s32 a, void* p, void* q);  // slot 12
    void Run(s32 frames);                                // slot 13
    bool IsMulti() const;                                // slot 14
    void OnDeleteFromTaskManager();                      // slot 15
    void OnAddToTaskManager();                           // slot 16
    void OnAddTopToTaskManager();                        // slot 17
    void OnInsertToTaskManager();                        // slot 18
    void Remove();                                       // m_manager's vtable slot 8 (remove this)
    void ChangeLevel(u32 level);                         // TaskManager::ChangeLevel, then m_level
    void ForceDelete();                                  // m_manager = null, then slot 10

    AnimatableLinkElement base;  // 0x00
    TaskManager* m_manager;      // 0x18: the owning TaskManager (null when not added)
    u32 m_level;                 // 0x20: the task level (GetDefaultLevel() at construction)
    u16 m_flags24;               // 0x24: copied by Clone; meaning unknown
    u8 m_flags26;                // 0x26: copied by Clone; meaning unknown
    u8 unk_27;                   // 0x27
};
static_assert(offsetof(Task, m_manager) == 0x18);
static_assert(offsetof(Task, m_level) == 0x20);
static_assert(offsetof(Task, m_flags24) == 0x24);
static_assert(offsetof(Task, m_flags26) == 0x26);
static_assert(sizeof(Task) == 0x28);

class HierarchicalObject;

// Aska::HierarchicalObjectContainer (HOC): the transform node of the scene graph. Guest size 0x100
// (HierarchicalObjectContainer::CreateClone: operator new(0x100)); layout from CopyParameter, Clone,
// AttachChild, DetachFromParent, HierarchicalObject's setters and the inlined construction
// (port/decomp/render/hierarchical_object.c). In a HierarchicalObject it is the second base, at +0x30.
// Children form a ring (m_prevSibling / m_nextSibling; a lone node points at itself); the parent keeps
// the first child. Flags 0xf8 bit 0: "matrix fixed" (the setters and AttachChild update the hierarchy
// only when it is clear).
// vtable (_ZTVN4Aska27HierarchicalObjectContainerE): 0 D1, 1 D0, 2 GetClassID (0xf000f03d chain),
// 3 Clone, 4 CreateClone, 5 Get, 6 Set.
class HierarchicalObjectContainer {
public:
    void DtorBase();                                     // _ZN4Aska27HierarchicalObjectContainerD2Ev
    void DtorDelete();                                   // _ZN4Aska27HierarchicalObjectContainerD0Ev
    u64 GetClassID(s32 depth) const;                     // slot 2
    bool Clone(const IAnimatable* src);                  // slot 3
    HierarchicalObjectContainer* CreateClone(const IAnimatable* src);  // slot 4
    bool Get(u64 id, void* out) const;                   // slot 5
    bool Set(u64 id, const void* in);                    // slot 6
    bool CopyParameter(const HierarchicalObject* src);   // CopyParameter(&src->m_hoc)
    bool CopyParameter(const HierarchicalObjectContainer* src);
    void DetachFromParent();                             // its children move to its parent
    void AttachChild(HierarchicalObjectContainer* child);// appended to the ring (before m_firstChild)
    void InvalidateMatrixHierarchically();
    void UpdateHierarchically();
    void ForceUpdateHierarchically();
    s32 GetChildObjectCount() const;
    HierarchicalObjectContainer* ChildObject(s32 index) const;
    void MakeTransformParam();
    void MakeMatrix();
    void MakeTransformParamEx();
    void SwapParent(HierarchicalObjectContainer* parent);
    static void ReleaseHOCBuffer();
    static void OpenIterator();                          // a 0x2000-byte iteration stack (operator new[])
    static void AddToIterator();
    static void IterateMakeMatrix();
    void CallCalcTransformMatrix(HierarchicalObject* obj);

    const void* vtable;                          // 0x00: _ZTVN4Aska27HierarchicalObjectContainerE + 0x10
    u64 unk_08;                                  // 0x08
    MathMatrix m_world;                          // 0x10: the world matrix (HierarchicalObject::WorldMatrix)
    MathVector m_position;                       // 0x50: property 5 (SetPosition; w = 1)
    MathQuaternion m_posture;                    // 0x60: property 6 (SetPosture; the Euler setters convert)
    MathVector m_scale;                          // 0x70: property 7 (SetScale)
    MathVector m_param9;                         // 0x80: property 9 (Set also copies a matrix to HierarchicalObject::m_param9Matrix)
    MathVector m_vec90;                          // 0x90: (0, 0, 0, 1) at construction; meaning unknown
    MathVector m_param10;                        // 0xa0: property 10
    MathVector m_param11;                        // 0xb0: property 11
    HierarchicalObjectContainer* m_parent;       // 0xc0
    HierarchicalObjectContainer* m_firstChild;   // 0xc8
    HierarchicalObjectContainer* m_prevSibling;  // 0xd0: ring (self when alone)
    HierarchicalObjectContainer* m_nextSibling;  // 0xd8
    AnimatableLinkElement* m_referrers;          // 0xe0: elements linked to this node (~HierarchicalObject clears their links)
    void* m_owner;                               // 0xe8: the HierarchicalObject this node belongs to
    MathMatrix* m_pWorld;                        // 0xf0: &m_world
    u8 m_flags;                                  // 0xf8: bit 0 matrix fixed (no hierarchy update), bits 2-4 copied by Clone
    u8 m_flags2;                                 // 0xf9: bits 0-1 property 8 (the rotation order, most likely), bit 2
    u8 unk_fa[6];                                // 0xfa
};
static_assert(offsetof(HierarchicalObjectContainer, m_world) == 0x10);
static_assert(offsetof(HierarchicalObjectContainer, m_position) == 0x50);
static_assert(offsetof(HierarchicalObjectContainer, m_posture) == 0x60);
static_assert(offsetof(HierarchicalObjectContainer, m_scale) == 0x70);
static_assert(offsetof(HierarchicalObjectContainer, m_param9) == 0x80);
static_assert(offsetof(HierarchicalObjectContainer, m_param10) == 0xa0);
static_assert(offsetof(HierarchicalObjectContainer, m_param11) == 0xb0);
static_assert(offsetof(HierarchicalObjectContainer, m_parent) == 0xc0);
static_assert(offsetof(HierarchicalObjectContainer, m_firstChild) == 0xc8);
static_assert(offsetof(HierarchicalObjectContainer, m_prevSibling) == 0xd0);
static_assert(offsetof(HierarchicalObjectContainer, m_nextSibling) == 0xd8);
static_assert(offsetof(HierarchicalObjectContainer, m_referrers) == 0xe0);
static_assert(offsetof(HierarchicalObjectContainer, m_owner) == 0xe8);
static_assert(offsetof(HierarchicalObjectContainer, m_pWorld) == 0xf0);
static_assert(offsetof(HierarchicalObjectContainer, m_flags) == 0xf8);
static_assert(offsetof(HierarchicalObjectContainer, m_flags2) == 0xf9);
static_assert(sizeof(HierarchicalObjectContainer) == 0x100);

class Camera;
class Light;
class LightManager;
class RenderContext;
struct RENDERINFO;

// Aska::HierarchicalObject: Task + HierarchicalObjectContainer. Guest size 0x1a0 (HierarchicalObject::
// CreateClone: operator new(0x1a0); data size 0x198); layout from the inlined constructor there, the setters, Get / Set
// (port/decomp/render/hierarchical_object.c). The property ids of Get / Set: 5 position, 6 posture,
// 7 scale, 8 m_hoc.m_flags2 & 3, 9 m_param9 (+ m_param9Matrix), 10, 11, 12 the world matrix (slot 19),
// 13 m_active (Set calls slot 43 OnActive).
// vtable (_ZTVN4Aska18HierarchicalObjectE, 44 slots): 0-18 as Task (2-6, 11, 13 its own), then the members
// below from slot 19 on.
class HierarchicalObject {
public:
    void DtorBase();                                     // _ZN4Aska18HierarchicalObjectD2Ev
    void DtorDelete();                                   // _ZN4Aska18HierarchicalObjectD0Ev
    u64 GetClassID(s32 depth) const;                     // slot 2
    bool Clone(const IAnimatable* src);                  // slot 3
    HierarchicalObject* CreateClone(const IAnimatable* src);  // slot 4
    bool Get(u64 id, void* out) const;                   // slot 5
    bool Set(u64 id, const void* in);                    // slot 6
    u32 GetDefaultLevel() const;                         // slot 11
    void Run(s32 frames);                                // slot 13
    const MathMatrix* WorldMatrix() const;               // slot 19: &m_hoc.m_world
    void SetWorldMatrix(const MathMatrix* m);            // slot 20
    void MakeMatrix();                                   // slot 21
    void InitializeConditions();                         // slot 22
    void CheckSleepAvailability();                       // slot 23
    void SetAppropriateTaskLevel();                      // slot 24
    void SetPosition(float x, float y, float z);         // slot 25 (w = 1)
    void SetPosition(const MathVector* v);               // slot 26
    void SetPosture(float x, float y, float z);          // slot 27 (Euler, Quaternion::CreateFromEuler order 0)
    void SetPosture(const MathVector* euler);            // slot 28
    void SetPosture(const MathQuaternion* q);            // slot 29
    void SetPosture(float x, float y, float z, float w); // slot 30
    void SetScale(float x, float y, float z);            // slot 31
    void SetScale(const MathVector* v);                  // slot 32
    void SetPositionPassive(float x, float y, float z);  // slot 33 (no hierarchy update)
    void SetPositionPassive(const MathVector* v);        // slot 34
    void SetPosturePassive(float x, float y, float z);   // slot 35
    void SetPosturePassive(const MathVector* euler);     // slot 36
    void SetPosturePassive(const MathQuaternion* q);     // slot 37
    void SetPosturePassive(float x, float y, float z, float w);  // slot 38
    void SetScalePassive(float x, float y, float z);     // slot 39
    void SetScalePassive(const MathVector* v);           // slot 40
    MathVector* VirtualBoundingSphere();                 // slot 41
    void* GetBoundingBox(bool update);                   // slot 42
    void OnActive(bool active);                          // slot 43
    void EnableSimpleDynamics(bool on);                  // operator new(0x90): the simple-dynamics state
    void MakeBillboardMatrixFromLocalAxis(HierarchicalObject* target, MathMatrix* out, s32 axis);
    void MakeBillboardMatrixFromLocalAxisSub(HierarchicalObject* target, MathMatrix* out, bool a, bool b, s32 axis);
    void EstimateScaleStat();
    void UpdateSimpleDynamics(const void* params);       // Aska::AFF::SimpleDynamicsParameters const*
    void SwapChangeling(HierarchicalObject* other);
    void InverseKinematics(const MathVector* target, s32 a, s32 b, float c, float d, bool e);

    Task base;                          // 0x000: vtable _ZTVN4Aska18HierarchicalObjectE + 0x10
    void (*m_onDestroy)(HierarchicalObject*);  // 0x028: called by ~HierarchicalObject when set (0 at construction)
    HierarchicalObjectContainer m_hoc;  // 0x030: the second base (its own vptr)
    MathMatrix m_param9Matrix;          // 0x130: property 9's matrix (copied by CreateClone when m_hoc.m_flags bit 2)
    u8 unk_170[0x10];                   // 0x170
    void* m_simpleDynamics;             // 0x180: EnableSimpleDynamics' 0x90-byte state (operator new; freed by the destructor)
    u64 unk_188;                        // 0x188: 0 at construction; RenderableObject::RenderingDecided clears it
    u32 unk_190;                        // 0x190: 0 at construction; byte 0x190 bits 2-4 read by RenderingDecided
    u8 m_active;                        // 0x194: property 13 (1 at construction)
    u8 unk_195;                         // 0x195: 0 at construction
    u8 unk_196;                         // 0x196
    u8 unk_197;                         // 0x197: 0 at construction
    // 0x198: the end of HierarchicalObject's data; its allocation is 0x1a0 (rounded to 16), but derived
    // classes start their members here (the Itanium ABI reuses a non-POD base's tail padding):
    // RenderableObject::m_renderFlags is at 0x198.
};
static_assert(offsetof(HierarchicalObject, m_onDestroy) == 0x28);
static_assert(offsetof(HierarchicalObject, m_hoc) == 0x30);
static_assert(offsetof(HierarchicalObject, m_param9Matrix) == 0x130);
static_assert(offsetof(HierarchicalObject, m_simpleDynamics) == 0x180);
static_assert(offsetof(HierarchicalObject, unk_188) == 0x188);
static_assert(offsetof(HierarchicalObject, m_active) == 0x194);
static_assert(sizeof(HierarchicalObject) == 0x198);  // data size; CreateClone allocates 0x1a0

// Aska::RenderableObject: a HierarchicalObject the ObjectManager can paint. Guest size 0x310
// (RenderableObject::CreateClone: operator new(0x310)); layout from RenderableObject::RenderableObject,
// Clone and the accessors (port/decomp/render/renderable_object.c). Its own members start at 0x198, in
// what is the tail padding of a standalone HierarchicalObject.
// vtable (_ZTVN4Aska16RenderableObjectE, 89 slots): 0-43 as HierarchicalObject (2-7, 11, 13, 22-24, 41,
// 43 its own), then the members below from slot 44 on. The painting pipeline calls 79
// PreliminarilyPrepare, 80 PrepareForRendering, 81 Render, 84 FinishRendering.
class RenderableObject {
public:
    void CtorBase();                                     // RenderableObject()  _ZN4Aska16RenderableObjectC2Ev
    void Dtor();                                         // _ZN4Aska16RenderableObjectD1Ev (= ~HierarchicalObject)
    void DtorDelete();                                   // _ZN4Aska16RenderableObjectD0Ev
    u64 GetClassID(s32 depth) const;                     // slot 2
    bool Clone(const IAnimatable* src);                  // slot 3
    RenderableObject* CreateClone(const IAnimatable* src);  // slot 4
    bool Get(u64 id, void* out) const;                   // slot 5
    bool Set(u64 id, const void* in);                    // slot 6
    void DeleteThis(memory::DeleteManager* dm);          // slot 7
    u32 GetDefaultLevel() const;                         // slot 11 (0x4000)
    void Run(s32 frames);                                // slot 13
    void InitializeConditions();                         // slot 22
    void CheckSleepAvailability();                       // slot 23
    void SetAppropriateTaskLevel();                      // slot 24
    MathVector* VirtualBoundingSphere();                 // slot 41: &m_boundingSphere (slot 75 first unless 0x128 bit 4)
    void OnActive(bool active);                          // slot 43: m_renderFlags bit 13 = !active
    void SetRenderLayerID(u8 id);                        // slot 44
    void UpdateMultiDrawVars();                          // slot 45: m_multiDraw = 0
    void SetShadowManagerIndex(s32 index, u64 value);    // slot 46
    u64 GetShadowManagerIndex(s32 index);                // slot 47
    void* GetShaderAdapterCache(s32 index);              // slot 48
    s32 GetShaderAdapterCacheSize() const;               // slot 49
    void SetShaderAdapterCacheCount(s32 a, s32 b);       // slot 50
    void ResetDynamicShaderModifier();                   // slot 51
    void EnableCastShadow(bool on);                      // slot 52: m_shadowFlags bit 4
    void EnableReceiveShadow(bool on);                   // slot 53: m_shadowFlags bit 5
    void EnableReceiveProjector(bool on);                // slot 54: m_shadowFlags bit 7
    void PrepareLightContext(LightManager* lm);          // slot 55: m_shadowFlags bit 1
    bool IsAffectingLight(Light* light);                 // slot 56
    void MakeBillboardMatrix(Camera* camera);            // slot 57
    void MakeBillboardMatrixFromLocalAxis(Camera* camera);  // slot 58
    s32 QueryPrebuiltVariation() const;                  // slot 59
    void SetPrebuiltVariation(s32 v);                    // slot 60
    s32 GetCurrentPrebuiltVariation() const;             // slot 61
    void CheckRenderContexts();                          // slot 62
    bool DoesInsertToPaintingList(void* ipl, s32 a, s32 b, const s32* c);  // slot 63 (RenderableObject::IPL*)
    void SetSystemColorRate(const MathVector* v);        // slot 64: m_colorRate
    const MathVector* SystemColorRate() const;           // slot 65
    void SetColorRate(const MathVector* v);              // slot 66: m_colorRate (the same field)
    const MathVector* ColorRate() const;                 // slot 67
    void SetSystemColorOffset(const MathVector* v);      // slot 68: m_colorOffset
    const MathVector* SystemColorOffset() const;         // slot 69
    void SetColorOffset(const MathVector* v);            // slot 70
    const MathVector* ColorOffset() const;               // slot 71
    void SetVisibility(float v);                         // slot 72
    void SetProgrammableTransparency(u8 mode);           // slot 73: m_progTrans (RenderableObject::ProgTrans)
    void SetIBLAcceptanceNumber(u32 n);                  // slot 74: m_iblAcceptance
    void ComputeBoundingSphere(bool update);             // slot 75: m_vDefaultSphere, 0x128 bit 4
    bool GetBoundingBoxDirect(void* obb);                // slot 76 (Aska::OrientedBoundingBox*)
    bool HasBoundingBox() const;                         // slot 77
    void RenderingDecided();                             // slot 78
    void PreliminarilyPrepare(LightManager* lm);         // slot 79
    void PrepareForRendering(const RENDERINFO* info);    // slot 80
    void Render(RenderContext* ctx, s32 pass);           // slot 81
    void* ResolveTargetGL(s32 a, s32 b);                 // slot 82
    void RoutineProcedure();                             // slot 83
    void FinishRendering();                              // slot 84
    bool ReleaseShaderCache();                           // slot 85
    void EnableObjectMotionBlur(bool on);                // slot 86: m_renderFlags bit 26
    void ProcessTextureDiscard();                        // slot 87
    void ProcessTextureAllocate();                       // slot 88
    float GetDeepestZ(s32 pass) const;
    float GetShallowestZ(s32 pass) const;
    void SetMultipassRenderingID(const u64* ids, s32 n);         // m_multipassRenderingID[0..min(n, 2))
    void SetMultipassRequestRenderingID(const u64* ids, s32 n);  // m_multipassRequestRenderingID
    void ProcFarObject();
    bool IsPostProcessObject() const;

    HierarchicalObject base;           // 0x000: vtable _ZTVN4Aska16RenderableObjectE + 0x10 (base.base...)
    u32 m_renderFlags;                 // 0x198: bit 13 inactive (OnActive), bit 26 object motion blur; Clone copies
    u8 unk_19c[4];                     // 0x19c
    u64 unk_1a0;                       // 0x1a0: Clone copies
    s32 m_renderQueued;                // 0x1a8: RenderThread::AddRenderQueue adds 1 atomically per queued draw
    u8 unk_1ac[4];                     // 0x1ac
    u32 m_passMask;                    // 0x1b0: RenderingDecided tests bits 0-2 and 9-10; Clone copies
    u8 m_progTrans;                    // 0x1b4: SetProgrammableTransparency
    u8 m_shadowFlags[2];               // 0x1b5: (u16, unaligned) bit 1 light context prepared, 4 cast shadow,
                                       //        5 receive shadow, 7 receive projector; 0x40 at construction
    u8 unk_1b7;                        // 0x1b7: 3 at construction; Clone copies (AofObject: a transparency mode, < 5)
    u8 unk_1b8[0x0c];                  // 0x1b8
    u32 unk_1c4;                       // 0x1c4: 0 at construction
    u32 unk_1c8;                       // 0x1c8: 0 at construction
    u8 unk_1cc[0x0c];                  // 0x1cc
    const IAnimatable* m_cloneSource;  // 0x1d8: Clone stores the source
    u8 unk_1e0[0x18];                  // 0x1e0
    u64 unk_1f8;                       // 0x1f8: Clone copies
    u64 unk_200;                       // 0x200: Clone copies
    u64 m_multipassRenderingID[2];     // 0x208: SetMultipassRenderingID
    u64 m_multipassRequestRenderingID[2];  // 0x218
    u32 m_multiDraw;                   // 0x228: UpdateMultiDrawVars zeroes it
    u8 unk_22c[0x1c];                  // 0x22c
    u8 m_iblAcceptance;                // 0x248: SetIBLAcceptanceNumber
    u8 unk_249[0x17];                  // 0x249
    u64 unk_260;                       // 0x260: Clone copies
    u64 unk_268;                       // 0x268: Clone copies
    MathVector m_colorRate;            // 0x270: (System)ColorRate
    MathVector m_colorOffset;          // 0x280: (System)ColorOffset
    u8 unk_290[0x40];                  // 0x290
    MathVector m_boundingSphere;       // 0x2d0: VirtualBoundingSphere (center xyz, radius w)
    MathVector unk_2e0;                // 0x2e0: Clone copies
    u8 unk_2f0;                        // 0x2f0: Clone copies
    u8 unk_2f1[3];                     // 0x2f1
    u32 unk_2f4;                       // 0x2f4: 0 at construction
    float m_angle2f8;                  // 0x2f8: pi/4 at construction
    float m_angle2fc;                  // 0x2fc: pi/8 at construction
    u64 unk_300;                       // 0x300: 0 at construction
    u8 unk_308[8];                     // 0x308
};
static_assert(offsetof(RenderableObject, m_renderFlags) == 0x198);
static_assert(offsetof(RenderableObject, unk_1a0) == 0x1a0);
static_assert(offsetof(RenderableObject, m_renderQueued) == 0x1a8);
static_assert(offsetof(RenderableObject, m_passMask) == 0x1b0);
static_assert(offsetof(RenderableObject, m_progTrans) == 0x1b4);
static_assert(offsetof(RenderableObject, m_shadowFlags) == 0x1b5);
static_assert(offsetof(RenderableObject, unk_1b7) == 0x1b7);
static_assert(offsetof(RenderableObject, m_cloneSource) == 0x1d8);
static_assert(offsetof(RenderableObject, m_multipassRenderingID) == 0x208);
static_assert(offsetof(RenderableObject, m_multipassRequestRenderingID) == 0x218);
static_assert(offsetof(RenderableObject, m_multiDraw) == 0x228);
static_assert(offsetof(RenderableObject, m_iblAcceptance) == 0x248);
static_assert(offsetof(RenderableObject, m_colorRate) == 0x270);
static_assert(offsetof(RenderableObject, m_colorOffset) == 0x280);
static_assert(offsetof(RenderableObject, m_boundingSphere) == 0x2d0);
static_assert(offsetof(RenderableObject, m_angle2f8) == 0x2f8);
static_assert(sizeof(RenderableObject) == 0x310);

// ==== Section: cameras, aiming and lights (n-types-render) ==========================================
// (AimingObject, Camera, CameraManager, Light, LightManager)

// ==== End of section: cameras, aiming and lights ====================================================




// ==== Section: the device, the render thread and render contexts (n-types-render-device) ============
// (RenderThread, RenderContextServer, RenderContextBase / RenderContext / batches, RenderDeviceGL,
// RenderDeviceData and the GL state caches, RenderState, RenderTarget / RenderTargetManagerGL,
// ShaderCompression / ShaderComprssionTree, RENDERINFO)

// Aska::ShaderComprssionTree (sic): the binary search tree of the LZ word compressor (Okumura's LZSS
// tree over 16-bit words: a 4096-word window, matches of 2..17 words, 0x1000 = NIL). Guest size 0x50058
// (ShaderCompression::CompressLZwordDic: operator new(0x50058) and the constructor inlined); layout from
// ShaderComprssionTree(), InsertNode, DeleteNode (port/decomp/render/shader_compression.c). Node i
// (a window position) has m_parent[i] / m_left[i] / m_right[i]; the roots are m_right[0x1001 + w], one
// per first word w (0x10000 of them); m_text is the window (u32 per word) plus 0x11 words of lookahead
// at the end, so a match can run past the wrap.
// The hot spot: at boot the AHSL cache thread recompresses every compressed shader-cache entry after
// creating its GL shader (AHSLCacheManagerV2::Handler -> ProcDiskCacheEntry -> RebuildL2Database ->
// BuildLinkedDiskCacheL2 -> AHSLBase::CreateCompressedShaderCache -> CompressLZwordDic -> InsertNode).
class ShaderComprssionTree {
public:
    void Ctor();                          // ShaderComprssionTree()  _ZN4Aska20ShaderComprssionTreeC2Ev: every parent and root = NIL
    void InsertNode(s32 r, s32 maxLen);   // inserts window position r; sets m_matchPos / m_matchLen (the longest match, < maxLen... = maxLen replaces)
    void DeleteNode(s32 p);               // removes window position p

    static constexpr s32 kNil = 0x1000;       // also the window size (words)
    static constexpr s32 kMaxMatch = 0x11;    // CompressLZwordDic's maxLen

    s32 m_matchPos;              // 0x00000: InsertNode's result: the matched window position
    s32 m_matchLen;              // 0x00004: and its length in words
    s32 m_parent[0x1001];        // 0x00008
    s32 m_left[0x1001];          // 0x0400c
    s32 m_right[0x11001];        // 0x08010: [0x1001 + w] = the root for first word w
    s32 m_text[0x1011];          // 0x4c014: the window, one word per u32 (big-endian bytes -> word)
};
static_assert(offsetof(ShaderComprssionTree, m_parent) == 0x8);
static_assert(offsetof(ShaderComprssionTree, m_left) == 0x400c);
static_assert(offsetof(ShaderComprssionTree, m_right) == 0x8010);
static_assert(offsetof(ShaderComprssionTree, m_text) == 0x4c014);
static_assert(sizeof(ShaderComprssionTree) == 0x50058);

// Aska::ShaderCompression: the shader cache's LZ codecs (static functions; no data). The word codec with
// a dictionary is the shipped cache's (docs/render/hair-shader.md "Compression"; tools/ahsl_extract.py):
// 16-bit units, a big-endian flag word per 16 items (LSB first), a match = big-endian (len - 2) << 12 |
// word distance, distance 0 ends; the 8 KiB dictionary (0x1000 words) primes the window (the tree's
// m_text, all positions inserted first) and distances before the output read from its end.
class ShaderCompression {
public:
    static void DecompressLZ(u8* src, u8* dst);                                  // _ZN4Aska17ShaderCompression12DecompressLZEPhS1_
    static s32 CompressLZ(void* src, s32 size, void* dst);
    static void DecompressLZword(u16* src, u16* dst);
    static s32 CompressLZword(void* src, s32 size, void* dst);
    static void DecompressLZwordDic(u16* src, u16* dst, u8* dic);               // dic: 0x2000 bytes
    static s32 CompressLZwordDic(void* src, s32 size, void* dst, u8* dic);      // returns the compressed size (0: failed)
};

class RenderContextBatch;
class LightContext;

// Aska::RenderContextServer: the per-frame pools of render contexts, batches and light contexts the
// objects take while they prepare (bump allocators, reset per frame by ResetServer). Guest size 0x58
// (ObjectManager::ObjectManager: operator new(0x58), RenderContextServer(App+0x90, +0x94, +0x98, +0x9c));
// layout from the constructor, the Realloc*, ResetServer and Get* (port/decomp/render/render_thread.c).
// GetRenderBatch / GetRenderBatchLite / GetLightContext take n entries with an atomic add (LDXR/STXR)
// on the used count, so the worker threads share them; GetRenderContext is not atomic. The light
// contexts are double-buffered (m_lightContexts[m_bufferIndex]; ResetServer flips the index).
// vtable (_ZTVN4Aska19RenderContextServerE): 0 D1, 1 D0.
class RenderContextServer {
public:
    void Ctor(s32 contexts, s32 batches, s32 batchLites, s32 lightContexts);  // _ZN4Aska19RenderContextServerC2Eiiii
    void DtorBase();
    void DtorDelete();
    void ReallocRenderContext(s32 n);       // new[] of RenderContext (0x230 each, count cookie at -8)
    void ReallocBatch(s32 n);               // new[] of RenderContextBatch (0x130 each)
    void ReallocBatchLite(s32 n);           // new[] of u32
    void ReallocLightContext(s32 n);        // new[] of 2 * n LightContext (0x550 each)
    void ResetServer();                     // every used count = 0; m_bufferIndex ^= 1
    RenderContext* GetRenderContext(s32 n);
    RenderContextBatch* GetRenderBatch(s32 n);   // atomic: null when the pool is exhausted
    u32* GetRenderBatchLite(s32 n);              // atomic
    LightContext* GetLightContext(s32 n);        // atomic; from the current buffer

    const void* vtable;                     // 0x00
    RenderContext* m_contexts;              // 0x08: new[] (RenderContext, 0x230 each)
    s32 m_contextCount;                     // 0x10
    s32 m_contextUsed;                      // 0x14
    RenderContextBatch* m_batches;          // 0x18: new[] (0x130 each)
    u32 m_batchCount;                       // 0x20
    u32 m_batchUsed;                        // 0x24: atomic
    u32* m_batchLites;                      // 0x28
    u32 m_batchLiteCount;                   // 0x30
    u32 m_batchLiteUsed;                    // 0x34: atomic
    LightContext* m_lightContexts[2];       // 0x38: one new[] of 2 * count; [1] = [0] + count
    u32 m_lightContextUsed;                 // 0x48: atomic
    u32 m_lightContextCount;                // 0x4c: per buffer
    u8 m_bufferIndex;                       // 0x50: which m_lightContexts the frame uses (ResetServer flips it)
    u8 unk_51[7];                           // 0x51
};
static_assert(offsetof(RenderContextServer, m_contexts) == 0x08);
static_assert(offsetof(RenderContextServer, m_contextCount) == 0x10);
static_assert(offsetof(RenderContextServer, m_contextUsed) == 0x14);
static_assert(offsetof(RenderContextServer, m_batches) == 0x18);
static_assert(offsetof(RenderContextServer, m_batchCount) == 0x20);
static_assert(offsetof(RenderContextServer, m_batchUsed) == 0x24);
static_assert(offsetof(RenderContextServer, m_batchLites) == 0x28);
static_assert(offsetof(RenderContextServer, m_batchLiteCount) == 0x30);
static_assert(offsetof(RenderContextServer, m_batchLiteUsed) == 0x34);
static_assert(offsetof(RenderContextServer, m_lightContexts) == 0x38);
static_assert(offsetof(RenderContextServer, m_lightContextUsed) == 0x48);
static_assert(offsetof(RenderContextServer, m_lightContextCount) == 0x4c);
static_assert(offsetof(RenderContextServer, m_bufferIndex) == 0x50);
static_assert(sizeof(RenderContextServer) == 0x58);
inline constexpr u64 kRenderContextSize = 0x230;
inline constexpr u64 kRenderContextBatchSize = 0x130;
inline constexpr u64 kLightContextSize = 0x550;

// Aska::RENDER_REQUEST: one entry of the render thread's command queue (0x28 bytes; written by the
// RenderThread::Add* methods, read by RenderThread::Render). m_type 0 = an object to draw
// (AddRenderQueue: a = RenderableObject*, b = RenderContext*, c = the pass), 1 = begin render
// (AddBeginRender; the other Add* use other types, see the README).
struct RENDER_REQUEST {
    u8 m_type;          // 0x00
    u8 unk_01[7];       // 0x01: (the begin-render entry copies 0x21 bytes from 0x01: whatever its stack held)
    u64 m_arg[4];       // 0x08
};
static_assert(offsetof(RENDER_REQUEST, m_arg) == 0x08);
static_assert(sizeof(RENDER_REQUEST) == 0x28);

// Aska::TQueue<RENDER_REQUEST, 8192>: a ring of 8193 entries (an index wraps to 0 after 0x2000). Add*
// writes the entry at m_write and advances it; it refuses (returns false: the request is dropped) when
// m_write == m_read, i.e. the reader's index is the one slot it holds back (1 / 0 at construction).
struct RenderRequestQueue {
    const void* vtable;                 // 0x00: _ZTVN4Aska6TQueueINS_14RENDER_REQUESTELi8192EEE + 0x10
    s32 m_write;                        // 0x08: the producers' index (1 at construction)
    s32 m_read;                         // 0x0c: the render thread's index (0 at construction)
    RENDER_REQUEST m_entries[0x2001];   // 0x10
};
static_assert(offsetof(RenderRequestQueue, m_write) == 0x08);
static_assert(offsetof(RenderRequestQueue, m_read) == 0x0c);
static_assert(offsetof(RenderRequestQueue, m_entries) == 0x10);
static_assert(sizeof(RenderRequestQueue) == 0x50038);

class Texture;  // Aska::Texture (opaque)

// Aska::RenderThread: the thread that runs the GL device; the game side (ObjectManager::OnPostPaint,
// TraversePaintingList) fills its queue with Add*, the thread drains it in Render(int&, bool&). Guest
// size 0x50298 (ObjectManager::ObjectManager: operator new(0x50298)); layout from RenderThread(),
// ~RenderThread, GetStatus, DeviceReset, AddRenderQueue, AddBeginRender (port/decomp/render/
// render_thread.c). The sync members (Aska::Thread base, Event, CriticalSection, FastCriticalSection,
// Semaphore) are the sync subsystem's: opaque bytes of their sizes here (n-sync: Event 0x68,
// CriticalSection 0x28, FastCriticalSection 0x90 with its lock word at +0x38 and waiters at +0x3c).
// AddRenderQueue writes without m_queueLock (one producer at a time: the painting traversal) and bumps
// the object's RenderableObject::m_renderQueued atomically; the other Add* and GetStatus take
// m_queueLock (a spinning FastCriticalSection: 0x1ff tries, then the semaphore) - the hot spots.
// vtable (_ZTVN4Aska12RenderThreadE, 3 slots): 0 D1, 1 D0, 2 Handler().
class RenderThread {
public:
    void Ctor();                          // RenderThread()  _ZN4Aska12RenderThreadC2Ev (starts the thread)
    void DtorBase();
    void DtorDelete();
    void Handler();                       // slot 2: the thread's loop
    u8 GetStatus() const;                 // m_status under m_queueLock
    void DeviceReset();
    void WaitForInit();
    void Handler_Init();                  // m_initialized = 1
    void BlockCallFunc();
    void Render(s32& a, bool& b);         // drains the queue (41,152 inclusive samples: the whole GL frame)
    void InsertCallBack(s32 id, u64 arg); // RenderThread::CALLBACK_ID
    void SetExposureScale(float a, float b);
    void EnableFastZ(bool on);
    void DirectInsertCallBack(void (*fn)(u64, u64), u64 a, u64 b);
    void CheckBoot();
    bool AddCreateRenderTarget(u32 id, void* env);   // Aska::MULTIPASS_ENVIRONMENT*
    bool AddChangeRenderTarget(u32 id, void* env);
    bool AddReloadZCull();
    bool AddEnableGnmOcclusionQuery(bool on);
    bool AddExposureScale(float a, float b);
    bool AddEnableFastZ(bool on);
    bool AddFinishRenderTarget(u32 id, s32 a, s32 b);
    bool AddTemporaryResolve(RenderableObject* obj, s32 a, s32 b);
    bool AddRenderQueue(RenderableObject* obj, RenderContext* ctx, s32 pass);  // type 0, lock-free
    bool AddBeginRender();                // type 1; m_status = 2 and m_wake set
    bool AddEndRender(void* notify);      // Aska::INotify*
    bool AddCallBack(void (*fn)(u64, u64), u64 a, u64 b);
    void ReqCustomCommandBlock(void (*fn)(u64, u64), u64 a, u64 b);
    void ReqDownloadResourceBlock(void* resource);   // Aska::GpuResource*
    bool AddDataTransfer(void* dst, void* src, u32 size);
    void ExecutePendingTileRegionOperationByAddress(void* p);
    bool AddOcclusionQueryBegin(u32* result);
    bool AddOcclusionQueryEnd();
    void WaitDeviceReset();
    void ReqDeviceReset();
    void ReqExit();
    void ReqSwap();
    void ReqDeviceInit();
    void ReqGpuWait();
    static void GPUIdleCallBack(u64 arg);
    static void FinishRenderCallBack(u64 arg);
    static void RenderThreadCallBack(u64 arg);

    const void* vtable;                 // 0x00000: _ZTVN4Aska12RenderThreadE + 0x10 (Aska::Thread's first word)
    u8 m_thread[0x10];                  // 0x00008: the rest of the Aska::Thread base (sync)
    u8 m_wake[0x68];                    // 0x00018: Aska::Event (AddBeginRender sets it)
    u8 m_event80[0x68];                 // 0x00080: Aska::Event (DeviceReset sets it)
    u8 m_cs[0x28];                      // 0x000e8: Aska::CriticalSection
    u8 m_event110[0x68];                // 0x00110: Aska::Event
    u64 unk_178;                        // 0x00178: 0 at construction
    u8 unk_180[0x10];                   // 0x00180
    u16 unk_190;                        // 0x00190: 0 at construction
    u8 m_status;                        // 0x00192: GetStatus(); 2 after AddBeginRender
    u8 unk_193[5];                      // 0x00193
    RenderRequestQueue m_queue;         // 0x00198
    u8 m_initialized;                   // 0x501d0: Handler_Init
    u8 unk_501d1;                       // 0x501d1: 0 at construction; DeviceReset clears it
    u8 unk_501d2;                       // 0x501d2
    u8 m_needVSyncInit;                 // 0x501d3: 1 at construction; DeviceReset makes the context current, VSync::Initialize, clears it
    u8 unk_501d4;                       // 0x501d4: 0 at construction (u16 store with 0x501d3)
    u8 unk_501d5;                       // 0x501d5
    u8 unk_501d6[2];                    // 0x501d6
    void* m_finishCallbackThread;       // 0x501d8: Aska::RenderFinishCallbackThread (0x2040 bytes)
    void* m_callbackThread;             // 0x501e0: Aska::RenderThreadCallBackThread (0x3088 bytes)
    Texture* m_blankTexture;            // 0x501e8: a 1x1 texture the constructor allocates and clears
    u8 m_queueLock[0x90];               // 0x501f0: Aska::FastCriticalSection (lock word 0x50228, waiters 0x5022c, semaphore 0x50268)
    u64 unk_50280;                      // 0x50280: 0 at construction
    u64 unk_50288;                      // 0x50288: 0 at construction
    u8 unk_50290[8];                    // 0x50290
};
static_assert(offsetof(RenderThread, m_wake) == 0x18);
static_assert(offsetof(RenderThread, m_event80) == 0x80);
static_assert(offsetof(RenderThread, m_cs) == 0xe8);
static_assert(offsetof(RenderThread, m_event110) == 0x110);
static_assert(offsetof(RenderThread, m_status) == 0x192);
static_assert(offsetof(RenderThread, m_queue) == 0x198);
static_assert(offsetof(RenderThread, m_initialized) == 0x501d0);
static_assert(offsetof(RenderThread, m_needVSyncInit) == 0x501d3);
static_assert(offsetof(RenderThread, m_finishCallbackThread) == 0x501d8);
static_assert(offsetof(RenderThread, m_callbackThread) == 0x501e0);
static_assert(offsetof(RenderThread, m_blankTexture) == 0x501e8);
static_assert(offsetof(RenderThread, m_queueLock) == 0x501f0);
static_assert(offsetof(RenderThread, unk_50280) == 0x50280);
static_assert(sizeof(RenderThread) == 0x50298);

// Aska::RenderState: a recorded list of render-state commands, replayed on the device by Apply (769 self
// samples: the per-draw state switch). Guest size 0x18 (RenderState(): three words zeroed); layout from
// Alloc, Reset, Release, ~RenderState, the setters and Apply (port/decomp/render/render_context.c).
// The commands live in a block of Global::m_pRenderStatePool (Alloc(capacity)); each setter appends
// an opcode byte and its operands (no bounds check except in the 3- and 9-byte ones) and counts it;
// Apply walks m_count commands from m_commands, calling the RenderDeviceGL setter of each opcode.
// Opcodes (operand bytes): 0xc8 EnableAlphaBlend (1), 0xc9 SetAlphaBlendFunction (op, separate mode),
// 0xcb / 0xce (AlphaToCoverage) / 0xe0 skipped (1), 0xcc skipped (2), 0xcf SetTextureSamplingFilter
// (stage, filter), 0xd0 ...MipmapFilter (stage, filter), 0xd1 ...WrapMode (stage, mode: U = V), 0xd2
// ...WrapModeU, 0xd3 ...WrapModeV, 0xd9 ...MaxAnisotropic (stage, n), 0xdb EnableZTest (1), 0xdc
// EnableZWrite (1), 0xdd SetZTestFunction (1), 0xde SetDepthBias (f32, f32), 0xdf SetCullMode (1),
// 0xe2 EnableStencil (1), 0xe3 SetStencilOp / 0xe4 SetStencilOpCCW (func, fail, zfail, pass, ref, ccw
// flag: the last byte swaps which of the two device calls is made).
class RenderState {
public:
    enum Op : u8 {
        kAlphaBlend = 0xc8, kAlphaBlendFunction = 0xc9, kAlphaToCoverage = 0xce, kSamplingFilter = 0xcf,
        kSamplingMipmapFilter = 0xd0, kSamplingWrapMode = 0xd1, kSamplingWrapModeU = 0xd2, kSamplingWrapModeV = 0xd3,
        kSamplingMaxAnisotropic = 0xd9, kZTest = 0xdb, kZWrite = 0xdc, kZTestFunction = 0xdd, kDepthBias = 0xde,
        kCullMode = 0xdf, kStencil = 0xe2, kStencilOp = 0xe3, kStencilOpCCW = 0xe4,
    };
    void Ctor();                              // RenderState()  _ZN4Aska11RenderStateC2Ev
    void Dtor();                              // ~RenderState(): the block back to the pool
    bool Alloc(s32 capacity);                 // a block from Global::m_pRenderStatePool; m_cursor = m_commands
    void Reset();                             // m_count = 0, m_cursor = m_commands
    void Release();                           // the block back, then RenderStateManager::Return(this)
    void SetFillMode(s32 mode);               // (no command)
    void SetCullMode(s32 mode);
    void EnableZTest(bool on);
    void EnableZWrite(bool on);
    void SetZTestFunction(s32 func);
    void SetDepthBias(float a, float b);
    void EnableAlphaBlend(bool on);
    void SetAlphaBlendFunction(s32 op, s32 separate);   // AlphaBlend::Operation (< 0x11), SeparateAlphaBlendMode (< 3)
    void EnableAlphaTest(bool on);            // (no command)
    void SetAlphaTestFunction(s32 func, s32 ref);  // (no command)
    void SetAlphaToCoverage(s32 mode);
    void EnableStencil(s32 mode);             // StencilMode::Mode
    void SetStencilOp(s32 func, s32 fail, s32 zfail, s32 pass, s32 ref, s16 mask);
    void SetStencilOpCCW(s32 func, s32 fail, s32 zfail, s32 pass, s32 ref, s16 mask);
    void SetTextureSamplingFilter(s32 stage, s32 filter);
    void SetTextureSamplingMipmapFilter(s32 stage, s32 filter);
    void SetTextureSamplingWrapMode(s32 stage, s32 mode);
    void SetTextureSamplingWrapModeU(s32 stage, s32 mode);
    void SetTextureSamplingWrapModeV(s32 stage, s32 mode);
    void SetTextureSamplingMipmapLODBias(s32 stage, s32 bias);       // (no command)
    void SetTextureSamplingTrilinearClamp(s32 stage, u32 v);         // (no command)
    void SetTextureSamplingMaxAnisotropic(s32 stage, u32 n);
    void SetTextureSamplingAnisotropicBias(s32 stage, s32 bias);     // (no command)
    void Apply(void* device);                 // RenderDeviceGL* (null: g_pRenderDev)
    static void ReadyDefaultRenderState(void* device);
    static void RestoreDefaultRenderState(void* device);
    // RenderState::Static::* (the device setters the opcodes map to) are free functions of the guest.

    u8* m_commands;     // 0x00: the pool block (null: nothing recorded)
    u8* m_cursor;       // 0x08: where the next command goes
    u32 m_capacity;     // 0x10: Alloc's argument (commands)
    u32 m_count;        // 0x14: commands recorded
};
static_assert(offsetof(RenderState, m_cursor) == 0x08);
static_assert(offsetof(RenderState, m_capacity) == 0x10);
static_assert(offsetof(RenderState, m_count) == 0x14);
static_assert(sizeof(RenderState) == 0x18);

class ShaderConstantHandler;
class GpuResource;  // Aska::GpuResource (opaque: textures, buffers)

// Aska::RenderContextBatch (: RenderContextBatchBase): one draw of a RenderContext: its textures, render
// state and constants. Guest size 0x130 (RenderContextServer::ReallocBatch: new[] of 0x130); layout from
// RenderContextBatch(), ApplyState, ApplyTextures, GetTexturesTextureStage, ApplyShaderConstants and
// RenderContext::OnPaint (port/decomp/render/render_context.c). No vtable.
class RenderContextBatch {
public:
    void Ctor();                                        // _ZN4Aska18RenderContextBatchC2Ev
    void Dtor();                                        // (nothing)
    void ApplyState();                                  // (m_stateOverride ?: m_state)->Apply(null)
    void ApplyTextures();                               // m_textures[] -> SetTexture / RemoveTexture, m_extraTextures
    s32 GetTexturesTextureStage(s32 n);                 // the stage of the n-th bound texture
    void PrepairMatricies();                            // (sic; nothing)
    void ApplyShaderConstants(u64 a, void* shaderNodeHandler);  // Base::Apply, then m_constants
    void ApplyBase(u64 a, void* device, void* shaderNodeHandler);  // RenderContextBatchBase::Apply: m_pixelConst -> PS c20

    MathVector m_pixelConst;            // 0x000: RenderContextBatchBase::Apply: pixel constant register 20
    u8 unk_010[0x10];                   // 0x010
    GpuResource* m_textures[16];        // 0x020: per stage (ApplyTextures: up to the device's stage count; 0 = remove)
    GpuResource* m_extraTextures[3];    // 0x0a0: stages 0..2 again, set when non-null (vertex textures?)
    void* m_draw;                       // 0x0b8: what is drawn (OnPaint: +0x10 its VertexBuffer)
    RenderState* m_state;               // 0x0c0
    RenderState* m_stateOverride;       // 0x0c8: wins over m_state when set
    u8 unk_0d0[0x10];                   // 0x0d0
    u64 m_primArg0;                     // 0x0e0: the draw call's arguments (OnPaint)
    u64 m_primArg1;                     // 0x0e8
    u8 unk_0f0[0x10];                   // 0x0f0
    u64 unk_100;                        // 0x100: 0 at construction
    ShaderConstantHandler* m_constants; // 0x108: ApplyShaderConstants calls its SetShaderConstant
    u8 unk_110[2];                      // 0x110
    u16 unk_112;                        // 0x112: 0 at construction
    u8 m_shaderSlot;                    // 0x114: OnPaint: an index (stride 0x1b8) into the context's +0x20 table
    u8 unk_115[0x1b];                   // 0x115
};
static_assert(offsetof(RenderContextBatch, m_textures) == 0x20);
static_assert(offsetof(RenderContextBatch, m_extraTextures) == 0xa0);
static_assert(offsetof(RenderContextBatch, m_draw) == 0xb8);
static_assert(offsetof(RenderContextBatch, m_state) == 0xc0);
static_assert(offsetof(RenderContextBatch, m_stateOverride) == 0xc8);
static_assert(offsetof(RenderContextBatch, m_primArg0) == 0xe0);
static_assert(offsetof(RenderContextBatch, m_constants) == 0x108);
static_assert(offsetof(RenderContextBatch, unk_112) == 0x112);
static_assert(offsetof(RenderContextBatch, m_shaderSlot) == 0x114);
static_assert(sizeof(RenderContextBatch) == kRenderContextBatchSize);

// Aska::RenderContext (: RenderContextBase): one object's draw for one pass: its batches and the per-draw
// vertex / pixel shader constants. Guest size 0x230 (RenderContextServer::ReallocRenderContext: new[] of
// 0x230); layout from RenderContext(), AllocBatch, GetBatchArray, OnPaint, RenderContextBase::
// SetShaderConstant_Vertex / _Pixel / _Vertex_ForInstancing (port/decomp/render/render_context.c). No
// vtable. The register numbers are the AHSL vertex constants (docs/render/hair-shader.md: cmWVS, cmWorld
// [3] ...); which name goes with which register is (d).
class RenderContext {
public:
    void Ctor();                                    // _ZN4Aska13RenderContextC2Ev: the matrices identity
    void Dtor();                                    // m_batches = 0, m_batchCount = 0
    void AllocBatch(s32 n);                         // RenderContextBase::AllocBatch: n batches from the server (atomic)
    RenderContextBatch* GetBatchArray(s32 i);       // &m_batches[i]
    void OnPaint();                                 // the draw (render thread): every batch's state, textures, constants, draw call
    void PrepairMatricies();
    void SetShaderConstant_Vertex(u64 a, void* shaderNodeHandler);   // the flags at 0x140 pick the registers below
    void SetShaderConstant_Pixel(u64 a, void* shaderNodeHandler);    // m_pixelConst -> PS c20
    void SetShaderConstant_Vertex_ForInstancing(u32 i);              // m_instanceMatrices[m_instanceIndex ? [i] : i] -> VS c17 (3)

    RenderContextBatch* m_batches;      // 0x000: AllocBatch (GetRenderBatch from Global::m_pObjectManager's server)
    u16 m_batchCount;                   // 0x008
    u8 unk_00a;                         // 0x00a: flags (bit 2: instanced / screen-space draw in OnPaint; bits 5-6 cleared by AllocBatch)
    u8 unk_00b[0x0d];                   // 0x00b
    u64 unk_018;                        // 0x018: 0 at construction
    void* m_shaderTable;                // 0x020: OnPaint: +8 an array of 0x1b8-byte entries (indexed by the batch's m_shaderSlot)
    u8* m_instanceMatrices;             // 0x028: 0x40 bytes per instance (3 registers used)
    u32* m_instanceIndex;               // 0x030: optional remap of the instance index
    u32 m_instanceCount;                // 0x038
    u8 m_instanceFlags;                 // 0x03c: OnPaint: instancing on (bit 0), bit 1
    u8 unk_03d[3];                      // 0x03d
    GpuResource* m_instanceBuffer;      // 0x040: BindInstanceVertexBuffer
    void* m_target;                     // 0x048: OnPaint: u16 width at +0x28, height at +0x2a (the 2D projection)
    u64 unk_050;                        // 0x050
    u32 unk_058;                        // 0x058: 0 at construction
    u8 unk_05c[4];                      // 0x05c
    MathMatrix m_vc0;                   // 0x060: VS c0..c3 (identity at construction; OnPaint's 2D ortho; cmWVS most likely)
    MathMatrix m_vc10;                  // 0x0a0: VS c10..c13 when flag bit 9
    float m_world[12];                  // 0x0e0: VS c1..c3, a 3x4 (cmWorld most likely)
    MathVector m_vc14;                  // 0x110: VS c14 ((0, 0, 0, 1) at construction)
    MathVector m_pixelConst;            // 0x120: PS c20 ((1, 1, 1, 1) at construction)
    MathVector unk_130;                 // 0x130: (0, 0, 0, 1) at construction
    u64 m_constFlags;                   // 0x140: bit 0 c0 only, 1 c1..c3, 2, 6 screen UV, 9, 14, 15, 16 (SetShaderConstant_Vertex)
    u8 unk_148[8];                      // 0x148
    const MathVector* m_vc11;           // 0x150: VS c11..c13 (3) by pointer
    u8 unk_158[0x18];                   // 0x158
    MathMatrix m_vc9;                   // 0x170: VS c9..c11 (3 used; identity at construction)
    u8 unk_1b0[0x10];                   // 0x1b0
    MathMatrix m_vc15;                  // 0x1c0: VS c15..c18 (4) when flag bit 14
    u8 unk_200[0x10];                   // 0x200
    MathVector m_vc12[2];               // 0x210: VS c12..c13 when flag bit 16
};
static_assert(offsetof(RenderContext, m_batchCount) == 0x08);
static_assert(offsetof(RenderContext, m_shaderTable) == 0x20);
static_assert(offsetof(RenderContext, m_instanceMatrices) == 0x28);
static_assert(offsetof(RenderContext, m_instanceCount) == 0x38);
static_assert(offsetof(RenderContext, m_instanceFlags) == 0x3c);
static_assert(offsetof(RenderContext, m_instanceBuffer) == 0x40);
static_assert(offsetof(RenderContext, m_target) == 0x48);
static_assert(offsetof(RenderContext, m_vc0) == 0x60);
static_assert(offsetof(RenderContext, m_vc10) == 0xa0);
static_assert(offsetof(RenderContext, m_world) == 0xe0);
static_assert(offsetof(RenderContext, m_vc14) == 0x110);
static_assert(offsetof(RenderContext, m_pixelConst) == 0x120);
static_assert(offsetof(RenderContext, m_constFlags) == 0x140);
static_assert(offsetof(RenderContext, m_vc11) == 0x150);
static_assert(offsetof(RenderContext, m_vc9) == 0x170);
static_assert(offsetof(RenderContext, m_vc15) == 0x1c0);
static_assert(offsetof(RenderContext, m_vc12) == 0x210);
static_assert(sizeof(RenderContext) == kRenderContextSize);

// ==== End of section: the device ====================================================================




// ==== Section: materials, shader constants, passes, post-processing (n-types-render-material) =======
// (MaterialList, MaterialContext, ShaderConstantManager / Handler, UniformValueBuffer2, AhslConst,
// RenderPass / RenderPassManager, PostProcessCombinerTBR / PostProcessBufferManager, ShadowManager)

// ==== End of section: materials ====================================================================

}  // namespace soa::native::render

#endif  // SOA_NATIVE_RENDER_LAYOUT_H
