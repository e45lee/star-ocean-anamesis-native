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

#include "../math/math_layout.h"
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

// ---- Math value types: the math subsystem's (math_layout.h: Vector / Quaternion {x, y, z, w}, Matrix
// m[4][4] row-major with the translation in column 3). The Math* names are the aliases render, scene and
// anim use.
using MathVector = math::Vector;          // Aska::Vector, 0x10
using MathQuaternion = math::Quaternion;  // Aska::Quaternion, 0x10
using MathMatrix = math::Matrix;          // Aska::Matrix, 0x40

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
    u8 unk_1a8[8];                     // 0x1a8
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

// ==== End of section: the device ====================================================================




// ==== Section: materials, shader constants, passes, post-processing (n-types-render-material) =======
// (MaterialList, MaterialContext, ShaderConstantManager / Handler, UniformValueBuffer2, AhslConst,
// RenderPass / RenderPassManager, PostProcessCombinerTBR / PostProcessBufferManager, ShadowManager)

// ==== End of section: materials ====================================================================

}  // namespace soa::native::render

#endif  // SOA_NATIVE_RENDER_LAYOUT_H
