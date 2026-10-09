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

#include "../containers/containers_layout.h"
#include "../kernel/kernel_layout.h"
#include "../math/math_layout.h"
#include "../memory/memory_layout.h"
#include "../sync/sync_layout.h"
#include "gen/render_addresses.h"  // kVaddr*: the guest statics (tools/gen_addresses.py)

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

// ---- Guest addresses (ELF vaddr; add main_lib()->base) of the statics the classes below use: the
// generated gen/render_addresses.h (tools/gen_addresses.py, from addresses.txt: each found in the lib),
// included above.

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

// Aska::AnimatableLinkElement and Aska::Task (+ TaskManager) are the kernel subsystem's (kernel_layout.h:
// Task = {containers::LinkElement link (vtable, m_prev, m_next), m_owner, m_level, m_flags}, 0x28 bytes);
// every renderable derives from Task. The aliases keep render's / scene's / anim's names.
using AnimatableLinkElement = containers::LinkElement;  // Aska::AnimatableLinkElement {vtable, m_prev, m_next}
using Task = kernel::Task;                              // Aska::Task, 0x28
using TaskManager = kernel::TaskManager;                // Aska::TaskManager, 0xff0

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
    MathVector m_param9;                         // 0x80: property 9 (Set also copies a matrix to HierarchicalObject::m_invWorld)
    MathVector m_jointOrientation;               // 0x90: (0, 0, 0, 1) at construction; a JointObject's joint orientation (property 15)
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

// Aska::RENDERINFO: what one painting pass passes to its objects' PrepareForRendering (slot 80). 0x20 bytes:
// ObjectManager::OnPostPaint builds one on its stack (four 8-byte words, zeroed, then the pass bits) and
// ObjectManagerJobDispatcher::SetPrepareForRenderingBasicParameter copies the four words into each worker
// (ObjectManagerWorkerThread::m_renderInfo), which rewrites +6 / +8 (and +0x10 for job kind 1) per object
// before the call (port/decomp/scene/object_manager.c: Handler_PrepareForRendering, OnPostPaint).
struct RENDERINFO {
    u16 m_index;                   // +0x00: OnPostPaint counts it up per multipass layer
    u8 unk_02;                     // +0x02
    u8 m_passBits;                 // +0x03: bits 0-2 the pass kind (0 color, 1 z-prepass, 2 shadow cast, 3 vertex,
                                   //        4 object motion blur, 5 multi-draw: AofObject::PrepareForRendering),
                                   //        3-4 and 5 set by OnPostPaint per layer
    u8 unk_04[2];                  // +0x04
    u16 m_contextCount;            // +0x06: per object: m_contextsWanted / m_contextDivisor (0 when the divisor is 0)
    RenderContext* m_contexts;     // +0x08: per object: m_contexts + m_contextsUsed (0x230 bytes each)
    Camera* m_camera;              // +0x10: the pass's camera (job kind 1: the object's own m_camera, else the default)
    u64 unk_18;                    // +0x18: OnPostPaint's fourth word
};
static_assert(offsetof(RENDERINFO, m_passBits) == 0x03);
static_assert(offsetof(RENDERINFO, m_contextCount) == 0x06);
static_assert(offsetof(RENDERINFO, m_contexts) == 0x08);
static_assert(offsetof(RENDERINFO, m_camera) == 0x10);
static_assert(sizeof(RENDERINFO) == 0x20);

// Aska::HierarchicalObject: Task + HierarchicalObjectContainer. Guest size 0x1a0 (HierarchicalObject::
// CreateClone: operator new(0x1a0); data size 0x198); layout from the inlined constructor there, the setters, Get / Set
// (port/decomp/render/hierarchical_object.c). The property ids of Get / Set: 5 position, 6 posture,
// 7 scale, 8 m_hoc.m_flags2 & 3, 9 m_param9 (+ m_invWorld), 10, 11, 12 the world matrix (slot 19),
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
    MathMatrix m_invWorld;              // 0x130: the cached inverse world matrix, valid when m_hoc.m_flags bit 2 (MakeSkinMatrices,
                                        //        Camera::MakeCameraMatrix: the view); property 9's Set and CreateClone copy it
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
static_assert(offsetof(HierarchicalObject, m_invWorld) == 0x130);
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
    u32 m_renderFlags;                 // 0x198: bit 9 skinned, 13 inactive (OnActive), 21, 25 (scene's decompile), 26 object
                                       //        motion blur; Clone copies
    u8 unk_19c[4];                     // 0x19c
    Camera* m_camera;                  // 0x1a0: the camera it is drawn with (scene's decompile); Clone copies
    s32 m_renderQueued;                // 0x1a8: RenderThread::AddRenderQueue adds 1 atomically per queued draw
    s32 m_contextDivisor;              // 0x1ac: per-object context divisor / multi-draw count (scene's decompile)
    u32 m_passMask;                    // 0x1b0: RenderingDecided tests bits 0-2 and 9-10; Clone copies
    u8 m_progTrans;                    // 0x1b4: SetProgrammableTransparency
    u8 m_shadowFlags[2];               // 0x1b5: (u16, unaligned) bit 1 light context prepared, 4 cast shadow,
                                       //        5 receive shadow, 7 receive projector; bit 0 prepared this frame (scene's
                                       //        decompile); 0x40 at construction
    u8 unk_1b7;                        // 0x1b7: 3 at construction; Clone copies (AofObject: a transparency mode, < 5)
    u8 unk_1b8[8];                     // 0x1b8
    s32 m_contextsWanted;              // 0x1c0: render contexts wanted this frame (scene's decompile)
    u32 unk_1c4;                       // 0x1c4: 0 at construction
    u32 unk_1c8;                       // 0x1c8: 0 at construction
    s32 m_contextsUsed;                // 0x1cc: render contexts used
    RenderContext* m_contexts;         // 0x1d0: the contexts (an array, 0x230 bytes each)
    const IAnimatable* m_cloneSource;  // 0x1d8: Clone stores the source
    u64 unk_1e0;                       // 0x1e0
    u64 m_frameScratch1e8[2];          // 0x1e8: zeroed every frame (ObjectManager's ResetSystemFlags job)
    u64 unk_1f8;                       // 0x1f8: Clone copies; zeroed every frame (ResetSystemFlags)
    u64 unk_200;                       // 0x200: Clone copies; zeroed every frame (ResetSystemFlags)
    u64 m_multipassRenderingID[2];     // 0x208: SetMultipassRenderingID
    u64 m_multipassRequestRenderingID[2];  // 0x218
    u32 m_multiDraw;                   // 0x228: UpdateMultiDrawVars zeroes it
    u32 m_multiDrawLimit;              // 0x22c: (scene's decompile)
    u64 m_frameScratch230[2];          // 0x230: zeroed every frame (ResetSystemFlags)
    u64 unk_240;                       // 0x240
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
static_assert(offsetof(RenderableObject, m_camera) == 0x1a0);
static_assert(offsetof(RenderableObject, m_contextDivisor) == 0x1ac);
static_assert(offsetof(RenderableObject, m_contextsWanted) == 0x1c0);
static_assert(offsetof(RenderableObject, m_contextsUsed) == 0x1cc);
static_assert(offsetof(RenderableObject, m_contexts) == 0x1d0);
static_assert(offsetof(RenderableObject, m_multiDrawLimit) == 0x22c);
static_assert(offsetof(RenderableObject, m_renderQueued) == 0x1a8);
static_assert(offsetof(RenderableObject, m_passMask) == 0x1b0);
static_assert(offsetof(RenderableObject, m_progTrans) == 0x1b4);
static_assert(offsetof(RenderableObject, m_shadowFlags) == 0x1b5);
static_assert(offsetof(RenderableObject, unk_1b7) == 0x1b7);
static_assert(offsetof(RenderableObject, m_cloneSource) == 0x1d8);
static_assert(offsetof(RenderableObject, m_frameScratch1e8) == 0x1e8);
static_assert(offsetof(RenderableObject, unk_1f8) == 0x1f8);
static_assert(offsetof(RenderableObject, unk_200) == 0x200);
static_assert(offsetof(RenderableObject, m_frameScratch230) == 0x230);
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

// Aska::AimingObject: a HierarchicalObject that aims at a target (and an "up" target): Camera's base.
// Guest size 0x200 (AimingObject::CreateClone: operator new(0x200)), data size 0x1f5 (Camera's first
// member is the byte at 0x1f5); layout from AimingObject(), TargetObject, UpTargetObject, Get / Set
// (property 0xf: m_roll, most likely) (port/decomp/render/camera.c). Moved to render's scope from anim's
// (it is Camera's base). Because a derived class's members start inside its 8-byte tail, Camera holds
// these bytes as `m_aiming` and reinterprets them as an AimingObject (AsAimingObject()).
class AimingObject {
public:
    void CtorBase();                               // AimingObject()  _ZN4Aska12AimingObjectC2Ev
    void DtorBase();
    void DtorDelete();
    HierarchicalObject* TargetObject() const;      // m_target
    HierarchicalObject* UpTargetObject() const;    // m_upTarget
    bool Clone(const IAnimatable* src);
    AimingObject* CreateClone(const IAnimatable* src);
    void MakeMatrixMain();
    void MakeMatrix();                             // slot 21
    bool Get(u64 id, void* out) const;             // HierarchicalObject's, then 0xf: m_roll
    bool Set(u64 id, const void* in);
    u64 GetClassID(s32 depth) const;

    HierarchicalObject base;                       // 0x000
    u64 unk_198;                                   // 0x198
    u32 unk_1a0;                                   // 0x1a0: 0 at construction
    float unk_1a4[3];                              // 0x1a4: (1, 0, 1) at construction
    HierarchicalObject* m_target;                  // 0x1b0: TargetObject()
    HierarchicalObject* m_upTarget;                // 0x1b8: UpTargetObject()
    HierarchicalObjectContainer* m_aimNode;        // 0x1c0: &base.m_hoc at construction
    u8 unk_1c8[0x10];                              // 0x1c8
    HierarchicalObjectContainer* m_upNode;         // 0x1d8: &base.m_hoc at construction
    u8 unk_1e0[0x10];                              // 0x1e0
    float m_roll;                                  // 0x1f0: property 0xf
    u8 m_aimFlags;                                 // 0x1f4: 0 at construction
    u8 unk_1f5[0x0b];                              // 0x1f5: (the derived class's: Camera's members start here)
};
static_assert(offsetof(AimingObject, unk_1a0) == 0x1a0);
static_assert(offsetof(AimingObject, m_target) == 0x1b0);
static_assert(offsetof(AimingObject, m_upTarget) == 0x1b8);
static_assert(offsetof(AimingObject, m_aimNode) == 0x1c0);
static_assert(offsetof(AimingObject, m_upNode) == 0x1d8);
static_assert(offsetof(AimingObject, m_roll) == 0x1f0);
static_assert(offsetof(AimingObject, m_aimFlags) == 0x1f4);
static_assert(sizeof(AimingObject) == 0x200);

class Lens;               // Aska::Lens (opaque): Camera::m_lens
class OpticalPhenomenon;  // Aska::OpticalPhenomenon (opaque)

// Aska::Camera: guest size 0xf90 (CameraFactory / Camera::CreateClone: operator new(0xf90)); layout
// partly from Camera(), Get (the property ids below), GetFogConst, MakeCameraMatrix,
// MakeViewFrustumPlane, CameraManager::UpdateAllCameras (port/decomp/render/camera.c). Most of it is
// still padding: the matrices between 0x170 and 0xd50 are named where MakeCameraMatrix's products show
// them. Property ids (Get / Set): 0x10 m_fov0de4, 0x11 m_e04, 0x12 m_e00, 0x13..0x15 the lens'
// +0xc..+0x14, 0x16 m_zRange1, 0x17 m_zRange0 (doubles: SetZBufferRange(double, double)), 0x18 m_fogFar, 0x19
// m_fogNear, 0x1a m_fogDensity, 0x1b m_fogColor, 0x1c m_fogMode, 0x20 m_d50.
class Camera {
public:
    void Ctor();                                    // Camera()  _ZN4Aska6CameraC2Ev
    void Dtor();
    void DtorDelete();
    AimingObject* AsAimingObject() { return reinterpret_cast<AimingObject*>(this); }
    u64 GetClassID(s32 depth) const;
    void CheckSleepAvailability();
    const MathVector* GetFogConst();                // the fog constants (0xf20..0xf4f) for cvFogCoef; (13 self)
    void MakeCameraMatrix();                        // (430 self): the view = inverse(world) into base.m_invWorld (0x130), the projections, the products
    void MakeViewFrustumPlane(s32 target);          // (244 self)
    void MakeLocalViewFrustumVertices(MathVector* out, s32 target);
    void Run(s32 frames);
    void SetWorldMatrix(const MathMatrix* m);        // slot 20
    void MakeMatrix();                              // slot 21
    void PrepareScreenProjection();
    void ProjectScreen(MathVector* v);
    void ProjectFrontScreen(MathVector* v);
    void SetViewMatrix(const MathMatrix* m);
    void SetViewObjectMatrix(const MathMatrix* m);
    void Default();
    void DefaultCommon();
    void SetZBufferRange(double zNear, double zFar);
    void AdjustCameraEV();
    void ResetViewFrustum();
    void SetNumberOfAFPoints(s64 n);
    void SetAFPoint(s64 i, float x, float y);
    bool Get(u64 id, void* out) const;
    bool Set(u64 id, const void* in);

    HierarchicalObject base;              // 0x000: vtable _ZTVN4Aska6CameraE + 0x10
    u8 m_aiming[0x5d];                    // 0x198: AimingObject's members (AsAimingObject())
    u8 unk_1f5;                           // 0x1f5: 0 at construction
    u8 unk_1f6[0x75a];                    // 0x1f6: (MakeCameraMatrix's products at 0x9a0, 0x9e0, 0xa20)
    u64 unk_950;                          // 0x950: (0x950: the view's Euler angles, CalcEuler)
    u8 unk_958[0x3f8];                    // 0x958
    float unk_d50;                        // 0xd50: property 0x20 (a vector at 0xd50)
    float unk_d54[3];                     // 0xd54
    u8 unk_d60[0x40];                     // 0xd60
    MathMatrix unk_da0;                   // 0xda0: MakeCameraMatrix: MulFromLeft(0x9a0)
    u8 unk_de0[4];                        // 0xde0
    float m_de4;                          // 0xde4: property 0x10
    u8 unk_de8[0x18];                     // 0xde8
    float m_e00;                          // 0xe00: property 0x12
    float m_e04;                          // 0xe04: property 0x11
    u8 unk_e08[8];                        // 0xe08
    Lens* m_lens;                         // 0xe10: properties 0x13.. read through it
    u8 unk_e18[0x18];                     // 0xe18
    OpticalPhenomenon* m_optical;         // 0xe30: property 0x2b reads +0x5c
    u8 unk_e38[0x76];                     // 0xe38
    u8 m_targetIndex;                     // 0xeae: the render target (Get: the ObjectManager's target table)
    u8 unk_eaf[3];                        // 0xeaf
    u8 m_fogMode;                         // 0xeb2: property 0x1c (0 none, 2 linear, else exponential)
    u8 m_camFlags[2];                     // 0xeb3: (u16, unaligned) bit 1 update requested (UpdateAllCameras), bit 2 fog, bit 11
    u8 unk_eb5[3];                        // 0xeb5
    double m_zRange0;                     // 0xeb8: property 0x17; SetZBufferRange's first argument (near or far: not checked)
    double m_zRange1;                     // 0xec0: property 0x16; its second
    float m_zRange1F;                     // 0xec8: (float)m_zRange1
    float m_zRange0F;                     // 0xecc: (float)m_zRange0
    u8 unk_ed0[0x18];                     // 0xed0
    float m_fogFar;                       // 0xee8: property 0x18
    float m_fogNear;                      // 0xeec: property 0x19
    float m_fogDensity;                   // 0xef0: property 0x1a
    u8 unk_ef4[0xc];                      // 0xef4
    MathVector m_fogColor;                // 0xf00: property 0x1b
    u8 unk_f10[0x10];                     // 0xf10
    MathVector m_fogConst[3];             // 0xf20: GetFogConst's result
    MathMatrix unk_f50;                   // 0xf50: MakeCameraMatrix multiplies it with the view (0x130)
};
static_assert(offsetof(Camera, m_aiming) == 0x198);
static_assert(offsetof(Camera, unk_1f5) == 0x1f5);
static_assert(offsetof(Camera, unk_d50) == 0xd50);
static_assert(offsetof(Camera, m_de4) == 0xde4);
static_assert(offsetof(Camera, m_e00) == 0xe00);
static_assert(offsetof(Camera, m_e04) == 0xe04);
static_assert(offsetof(Camera, m_lens) == 0xe10);
static_assert(offsetof(Camera, m_optical) == 0xe30);
static_assert(offsetof(Camera, m_targetIndex) == 0xeae);
static_assert(offsetof(Camera, m_fogMode) == 0xeb2);
static_assert(offsetof(Camera, m_camFlags) == 0xeb3);
static_assert(offsetof(Camera, m_zRange0) == 0xeb8);
static_assert(offsetof(Camera, m_zRange1) == 0xec0);
static_assert(offsetof(Camera, m_zRange0F) == 0xecc);
static_assert(offsetof(Camera, m_fogFar) == 0xee8);
static_assert(offsetof(Camera, m_fogNear) == 0xeec);
static_assert(offsetof(Camera, m_fogDensity) == 0xef0);
static_assert(offsetof(Camera, m_fogColor) == 0xf00);
static_assert(offsetof(Camera, m_fogConst) == 0xf20);
static_assert(sizeof(Camera) == 0xf90);

// Aska::Light (: AimingObject): guest size 0x430 (AsfHandler::CreateInstanceOfObject: operator new(0x430));
// layout partly from Light(), SetLightType, GetIlluminance, Get (port/decomp/render/light.c). Get's
// property ids: 0x10 m_color (rgb + intensity), 0x11 m_intensity, 0x13 m_direction (0x210), 0x16
// m_groundColor, 0x17 m_type, 0x18 m_lightFlags bit 0, 0x1a m_2a8 (u64), 0x1d m_2a0, 0x29 m_color2,
// 0x2a..0x2c three more vectors (0x250, 0x260, 0x270), 0x12 / 0x14 / 0x15 / 0x1c / 0x31..0x33 floats.
// Type (SetLightType, < 9): 4 hemisphere (the average of m_color and m_groundColor), 5 m_color2 is the
// colour, others m_color.
class Light {
public:
    void Ctor();                                  // Light()  _ZN4Aska5LightC2Ev
    void Dtor();
    void DtorDelete();
    void CalcSpotCoefficient();
    void CalcAttenuation();                       // m_attenuation from the range
    void SetLightType(s32 type);                  // < 9 -> m_type
    float GetIlluminance() const;
    float GetColorTemperature() const;
    void SetIlluminance(float lux);
    void SetColorByTemperature(float kelvin);
    float CalcHemisphereIntensity(RenderableObject* obj);
    bool Get(u64 id, void* out) const;
    bool Set(u64 id, const void* in);
    void OnActive(bool on);

    HierarchicalObject base;              // 0x000: vtable _ZTVN4Aska5LightE + 0x10
    u8 m_aiming[0x5d];                    // 0x198: AimingObject's members (see Camera)
    u8 unk_1f5;                           // 0x1f5: 0 at construction
    u8 unk_1f6[0x1a];                     // 0x1f6
    MathVector m_direction;               // 0x210: property 0x13
    float m_attenuation[4];               // 0x220: GetIlluminance: 1 / (a + b r + c r^2) - d (CalcAttenuation)
    MathVector m_color;                   // 0x230: property 0x10 (rgb; w = m_intensity)
    // (m_color.w at 0x23c is the intensity: property 0x11; 100 at construction)
    MathVector m_color2;                  // 0x240: property 0x29 (the colour of type 5)
    MathVector m_vec250;                  // 0x250: property 0x2a
    MathVector m_vec260;                  // 0x260: property 0x2b
    MathVector m_vec270;                  // 0x270: property 0x2c
    MathVector m_groundColor;             // 0x280: property 0x16 (hemisphere lights: the lower colour)
    u8 unk_290[0x10];                     // 0x290
    u8 m_2a0;                             // 0x2a0: property 0x1d
    u8 m_type;                            // 0x2a1: property 0x17 (SetLightType)
    u8 m_2a2;                             // 0x2a2: property 0x27
    u8 unk_2a3[2];                        // 0x2a3
    u8 m_lightFlags[3];                   // 0x2a5: bit 0 property 0x18, 3 (0x1b), 6 (0x21), 7 (0x2e), 11, 12; 0x2a6 bit 0 (0x2d)
    u64 m_2a8;                            // 0x2a8: property 0x1a
    u8 unk_2b0[0x430 - 0x2b0];            // 0x2b0
};
static_assert(offsetof(Light, m_aiming) == 0x198);
static_assert(offsetof(Light, m_direction) == 0x210);
static_assert(offsetof(Light, m_attenuation) == 0x220);
static_assert(offsetof(Light, m_color) == 0x230);
static_assert(offsetof(Light, m_color2) == 0x240);
static_assert(offsetof(Light, m_groundColor) == 0x280);
static_assert(offsetof(Light, m_2a0) == 0x2a0);
static_assert(offsetof(Light, m_type) == 0x2a1);
static_assert(offsetof(Light, m_lightFlags) == 0x2a5);
static_assert(offsetof(Light, m_2a8) == 0x2a8);
static_assert(sizeof(Light) == 0x430);

// Aska::LightManager::LightContext: what an object's draw gets of the lights (0x550 bytes:
// RenderContextServer::ReallocLightContext; LightManager::MakeLightContext fills it). Opaque.
class LightContext {
public:
    u8 m_bytes[0x550];
};
static_assert(sizeof(LightContext) == 0x550);  // kLightContextSize

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
// ~RenderThread, GetStatus, DeviceReset, the Add* / Req*, Handler and Render (port/decomp/render/
// render_thread.c). The sync members are sync's classes (sync_layout.h), in place.
// The protocol: producers write the entry at m_queue.m_write and advance it (refused when m_write ==
// m_read); Render consumes from m_read + 1 until it reaches m_write. AddRenderQueue writes without
// m_queueLock (one producer at a time: the painting traversal) and bumps the object's
// RenderableObject::m_renderQueued atomically; the other Add* / Req* take m_queueLock (a
// FastCriticalSection) and, when m_status isn't 2 (rendering), set it to 2 and Set m_wake. The thread
// (Handler) loops GetStatus -> Render while the status is 2, so with an empty queue it spins on
// GetStatus until the next request; with status 0 it waits on m_wake (unless m_endRenderCount says a
// frame is still pending: then status 2 again). Render's swap entry (type 10) sets the status to 0.
// Request types (RENDER_REQUEST::m_type; Render's switch): 0 AddRenderQueue, 1 AddBeginRender,
// 2 AddChangeRenderTarget, 3 AddFinishRenderTarget, 4 AddTemporaryResolve, 6 AddEndRender, 7 AddCallBack,
// 8 AddOcclusionQueryBegin, 9 AddOcclusionQueryEnd, 10 ReqSwap, 0xb AddReloadZCull, 0xc AddDataTransfer,
// 0xe ExecutePendingTileRegionOperationByAddress, 0x10 AddExposureScale, 0x11 AddEnableFastZ,
// 0x13 ReqDeviceInit, 0x14 AddEnableGnmOcclusionQuery.
// vtable (_ZTVN4Aska12RenderThreadE, 3 slots): 0 D1, 1 D0, 2 Handler().
class RenderThread {
public:
    // request types (above)
    enum : u8 {
        kReqRenderQueue = 0, kReqBeginRender = 1, kReqChangeRenderTarget = 2, kReqFinishRenderTarget = 3,
        kReqTemporaryResolve = 4, kReqEndRender = 6, kReqCallBack = 7, kReqOcclusionQueryBegin = 8,
        kReqOcclusionQueryEnd = 9, kReqSwap = 10, kReqReloadZCull = 0xb, kReqDataTransfer = 0xc,
        kReqTileRegion = 0xe, kReqExposureScale = 0x10, kReqEnableFastZ = 0x11, kReqDeviceInit = 0x13,
        kReqGnmOcclusionQuery = 0x14,
    };
    static constexpr u8 kStatusIdle = 0, kStatusRendering = 2;

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
    bool ReqDownloadResourceBlock(void* resource);   // Aska::GpuResource*
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

    // The natives' shared steps (render_thread.cpp, not guest symbols): a request appended (false when
    // the ring is full) with the idle thread's wakeup, m_queueLock held / taken; a Req* flag set under
    // the lock with the wakeup; the ring as Render sees it; GetStatus's wait for the next request.
    bool PushLocked(u8 type, u64 a0, u64 a1, u64 a2);
    bool Push(u8 type, u64 a0, u64 a1, u64 a2);
    void RequestFlag(u8 RenderThread::*flag);
    bool QueueEmpty() const;              // Render would return at once (m_read + 1 == m_write)
    void WaitForRequest() const;

    sync::Thread base;                  // 0x00000: Aska::Thread (vtable _ZTVN4Aska12RenderThreadE + 0x10, the pthread)
    u64 unk_10;                         // 0x00010
    sync::Event m_wake;                 // 0x00018: Set by a request that finds the thread idle (status != 2)
    sync::Event m_resetDone;            // 0x00080: DeviceReset / Render's swap Set it, ReqDeviceReset resets it, WaitDeviceReset waits
    sync::CriticalSection m_blockCallCs;   // 0x000e8: one ReqCustomCommandBlock / ReqDownloadResourceBlock at a time
    sync::Event m_blockCallDone;        // 0x00110: the thread Sets it after running m_blockCall
    u64 m_blockCall;                    // 0x00178: void (*)(u64, u64): run by the thread (Handler / Render), then cleared
    u64 m_blockCallArg[2];              // 0x00180
    u16 m_endRenderCount;               // 0x00190: AddEndRender adds one (under the lock); Handler re-enters status 2 while it's not 0
    u8 m_status;                        // 0x00192: GetStatus(); 2 rendering, 0 idle
    u8 unk_193[5];                      // 0x00193
    RenderRequestQueue m_queue;         // 0x00198
    u8 m_initialized;                   // 0x501d0: Handler_Init
    u8 m_resetRequested;                // 0x501d1: ReqDeviceReset sets it; DeviceReset / the swap clear it (WaitDeviceReset waits while set)
    u8 m_gpuWaitRequested;              // 0x501d2: ReqGpuWait sets it; Handler's idle path clears it
    u8 m_needVSyncInit;                 // 0x501d3: 1 at construction; DeviceReset makes the context current, VSync::Initialize, clears it
    u8 m_exitRequested;                 // 0x501d4: ReqExit sets it; Handler's idle path tears the device down and exits the thread
    u8 m_fastZ;                         // 0x501d5: EnableFastZ / the 0x11 request
    u8 unk_501d6[2];                    // 0x501d6
    void* m_finishCallbackThread;       // 0x501d8: Aska::RenderFinishCallbackThread (0x2040 bytes)
    void* m_callbackThread;             // 0x501e0: Aska::RenderThreadCallBackThread (0x3088 bytes)
    Texture* m_blankTexture;            // 0x501e8: a 1x1 texture the constructor allocates and clears
    sync::FastCriticalSection m_queueLock;  // 0x501f0: the Add* / Req* / GetStatus lock (word 0x50228, waiters 0x5022c, semaphore 0x50268)
    u64 unk_50280;                      // 0x50280: 0 at construction
    u64 unk_50288;                      // 0x50288: 0 at construction
    float m_exposureScale[2];           // 0x50290: SetExposureScale / the 0x10 request
};
static_assert(offsetof(RenderThread, m_wake) == 0x18);
static_assert(offsetof(RenderThread, m_resetDone) == 0x80);
static_assert(offsetof(RenderThread, m_blockCallCs) == 0xe8);
static_assert(offsetof(RenderThread, m_blockCallDone) == 0x110);
static_assert(offsetof(RenderThread, m_blockCall) == 0x178);
static_assert(offsetof(RenderThread, m_endRenderCount) == 0x190);
static_assert(offsetof(RenderThread, m_status) == 0x192);
static_assert(offsetof(RenderThread, m_queue) == 0x198);
static_assert(offsetof(RenderThread, m_initialized) == 0x501d0);
static_assert(offsetof(RenderThread, m_needVSyncInit) == 0x501d3);
static_assert(offsetof(RenderThread, m_exitRequested) == 0x501d4);
static_assert(offsetof(RenderThread, m_finishCallbackThread) == 0x501d8);
static_assert(offsetof(RenderThread, m_callbackThread) == 0x501e0);
static_assert(offsetof(RenderThread, m_blankTexture) == 0x501e8);
static_assert(offsetof(RenderThread, m_queueLock) == 0x501f0);
static_assert(offsetof(RenderThread, unk_50280) == 0x50280);
static_assert(offsetof(RenderThread, m_exposureScale) == 0x50290);
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
class RenderDeviceGL;

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
    void Apply(RenderDeviceGL* device);       // (null: g_pRenderDev)
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
// Aska::GpuResource (partial): a device resource (texture, buffer) in RenderDeviceGL's pool (0x78
// bytes each); layout from DrawIndexedPrimitive (port/decomp/render/render_device.c): before a draw uses
// a buffer, its handler (vtable slot 0, with the resource) uploads it when m_dirty is set or it has no
// GL object yet.
class GpuResource {
public:
    // The upload before use (DrawIndexedPrimitive, SetTexture): when m_dirty or no handle yet, the
    // handler's Update; true when it ran and succeeded (m_dirty cleared then) or wasn't needed.
    bool NeedsUpload() const { return m_dirty != 0 || m_handle == 0; }
    bool EnsureUploaded();

    u8 unk_00[0x40];        // 0x00
    static constexpr int kHandlerSlotUpdate = 0;  // m_handler's vtable: bool Update(GpuResource*)
    void* m_handler;        // 0x40: an object whose vtable slot 0 is bool Update(GpuResource*)
    u64 m_handle;           // 0x48: 0 until uploaded; a buffer's GL name (low 32 bits), a texture's slot in
                            //       RenderDeviceData::m_textureSlots (< 0x400)
    u8 unk_50[0x18];        // 0x50
    u32 m_dirty;            // 0x68: cleared by a successful Update
    u8 unk_6c[0xc];         // 0x6c
};
static_assert(offsetof(GpuResource, m_handler) == 0x40);
static_assert(offsetof(GpuResource, m_handle) == 0x48);
static_assert(offsetof(GpuResource, m_dirty) == 0x68);
static_assert(sizeof(GpuResource) == 0x78);

// Aska::IndexBuffer (partial): DrawIndexedPrimitive's argument; its GpuResource (null: client memory
// only, GetData). GetData / Is32BitBuffer stay guest code.
class IndexBuffer {
public:
    GpuResource* m_resource;  // 0x00
};

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

// ---- The GL device: RenderDeviceGL (g_pRenderDev) and its RenderDeviceData -----------------------

// Aska::_RenderDeviceGL::TextureStateCache: the sampler state last applied to one GL texture (0x14
// bytes: TPoolFast<TextureStateCache> stride in RenderDeviceData::GetTextureStateCaches, which fills a
// new one with a 16-byte default (vaddr 0x29cd0f0) and 1 at +0x10).
struct TextureStateCache {
    u32 m_state[4];     // 0x00: filter / mip filter / wrap state (the default at 0x29cd0f0)
    u32 m_valid;        // 0x10: 1 when created
};
static_assert(sizeof(TextureStateCache) == 0x14);

// One texture unit's sampler state in OglStateSet0 (the RenderDeviceGL::SetTextureSampling* setters
// record it; applied to the texture's own state at the draw). 0x18 bytes.
struct OglSampler {
    s32 m_wrapU;            // +0x00 (TexWrap::Mode; 10 in a setter: unchanged)
    s32 m_wrapV;            // +0x04
    u32 m_maxAnisotropy;    // +0x08
    s32 m_filter;           // +0x0c (TexSamp::Filter; 1 by default)
    s32 m_mipFilter;        // +0x10 (TexSamp::MipFilter; 0 by default)
    u8 m_textureFlag;       // +0x14: SetTexture copies bit 0 of the texture slot's m_flags (0 by default)
    u8 unk_15[3];           // +0x15
};
static_assert(sizeof(OglSampler) == 0x18);

// Aska::ASKA_OGL_STATESET0: the GL state the calling thread last set (one per thread: a pthread key of
// StateCacheThreadSafe), so the device skips redundant GL calls. Guest size 0x3e0
// (StateCacheThreadSafe::AllocateAndStoreStateSet0: operator new(0x3e0), then SetDefaults: 0xff
// everywhere, the GL defaults read back); layout from RenderDeviceGL::BindTexture, GetBoundTextureID,
// BindVertexFormat, UpdateVertexAttribute, UpdateRenderState, DrawIndexedPrimitive (port/decomp/render/
// render_device.c, state_cache.c).
struct OglStateSet0 {
    u64 m_owner;                // 0x000: the StateCacheThreadSafe (SetDefaults' last store)
    u32 m_texture2D[16];        // 0x008: the texture bound to GL_TEXTURE_2D per unit
    u32 m_textureCube[16];      // 0x048: GL_TEXTURE_CUBE_MAP (0x8513)
    u32 m_texture3D[16];        // 0x088: GL_TEXTURE_3D (0x806f)
    u8 m_activeUnit;            // 0x0c8: glActiveTexture's unit
    u8 unk_0c9[3];              // 0x0c9
    u32 m_arrayBuffer;          // 0x0cc: GL_ARRAY_BUFFER's binding (UpdateVertexAttribute)
    u32 m_elementBuffer;        // 0x0d0: GL_ELEMENT_ARRAY_BUFFER's (DrawIndexedPrimitive)
    u8 unk_0d4[0x98];           // 0x0d4
    OglSampler m_samplers[16];  // 0x16c: the sampler state per texture unit the next draw wants
    u8 m_depthWrite;            // 0x2ec: EnableZWrite's (glDepthMask called on a change)
    u8 unk_2ed[3];              // 0x2ed
    float m_clearColor[4];      // 0x2f0: (SetDefaults: GL_COLOR_CLEAR_VALUE)
    u16 m_capFlags;             // 0x300: the glEnable caps: bits 0-6 wanted (0 cull face, 1 depth test, 2 stencil,
                                //        3 blend, 4 alpha to coverage, 5 dither, 6 scissor), 7-12 set in GL
    u8 unk_302[2];              // 0x302
    u32 m_colorMask;            // 0x304: wanted (bits 0-3 RGBA)
    u32 m_colorMaskGL;          // 0x308
    u32 m_frontFace;            // 0x30c: wanted (SetCullMode: GL_CW / GL_CCW)
    u32 m_frontFaceGL;          // 0x310
    u32 m_cullFace;             // 0x314: wanted (GL_BACK)
    u32 m_cullFaceGL;           // 0x318
    u32 m_blendGL[6];           // 0x31c: the blend state set in GL (src, dst, equation; alpha src, dst, equation)
    s32 m_viewportGL[4];        // 0x334
    u32 m_blend[6];             // 0x344: wanted (SetAlphaBlendFunction)
    s32 m_viewport[4];          // 0x35c: wanted
    u32 m_depthFunc;            // 0x36c: wanted (SetZTestFunction)
    u32 m_depthFuncGL;          // 0x370
    u8 unk_374[8];              // 0x374: (the clear depth, the clear stencil: SetDefaults)
    float m_polygonOffset[2];   // 0x37c: wanted (SetDepthBias: factor, units)
    float m_polygonOffsetGL[2]; // 0x384
    u8 m_attribWant[0x20];      // 0x38c: the vertex attribute arrays the next draw needs (BindVertexFormat sets them)
    u8 m_attribGL[0x20];        // 0x3ac: the arrays enabled in GL (UpdateVertexAttribute syncs them)
    u8 unk_3cc[0x14];           // 0x3cc
};
static_assert(offsetof(OglStateSet0, m_texture2D) == 0x08);
static_assert(offsetof(OglStateSet0, m_textureCube) == 0x48);
static_assert(offsetof(OglStateSet0, m_texture3D) == 0x88);
static_assert(offsetof(OglStateSet0, m_activeUnit) == 0xc8);
static_assert(offsetof(OglStateSet0, m_arrayBuffer) == 0xcc);
static_assert(offsetof(OglStateSet0, m_elementBuffer) == 0xd0);
static_assert(offsetof(OglStateSet0, m_samplers) == 0x16c);
static_assert(offsetof(OglStateSet0, m_depthWrite) == 0x2ec);
static_assert(offsetof(OglStateSet0, m_capFlags) == 0x300);
static_assert(offsetof(OglStateSet0, m_colorMask) == 0x304);
static_assert(offsetof(OglStateSet0, m_frontFace) == 0x30c);
static_assert(offsetof(OglStateSet0, m_cullFace) == 0x314);
static_assert(offsetof(OglStateSet0, m_blendGL) == 0x31c);
static_assert(offsetof(OglStateSet0, m_viewportGL) == 0x334);
static_assert(offsetof(OglStateSet0, m_blend) == 0x344);
static_assert(offsetof(OglStateSet0, m_viewport) == 0x35c);
static_assert(offsetof(OglStateSet0, m_depthFunc) == 0x36c);
static_assert(offsetof(OglStateSet0, m_polygonOffset) == 0x37c);
static_assert(offsetof(OglStateSet0, m_attribWant) == 0x38c);
static_assert(offsetof(OglStateSet0, m_attribGL) == 0x3ac);
static_assert(sizeof(OglStateSet0) == 0x3e0);

// The calling thread's second GL state set (RenderDeviceData::GetThreadOglState1: operator new(0x10), a
// StateCacheThreadSafe key of its own): the program in use.
struct OglStateSet1 {
    u64 m_owner;                        // 0x00: the StateCacheThreadSafe
    u32 m_programWant;                  // 0x08: (-1 at first)
    u32 m_programGL;                    // 0x0c: glUseProgram's
};
static_assert(sizeof(OglStateSet1) == 0x10);

// Aska::StateCacheThreadSafe: the per-thread GL state caches (pthread keys created on first use, guarded
// by an atomic flag each). Partial: from BindTexture / GetBoundTextureID / GetThreadOglState1.
struct StateCacheThreadSafe {
    // The calling thread's state set 0 when its key exists and the thread has one, else null (the guest
    // creates both on first use: natives leave that to the guest original).
    OglStateSet0* StateSet0() const;
    OglStateSet1* StateSet1() const;   // likewise for state set 1 (m_keySet1)

    u8 unk_00[8];               // 0x00
    u32 m_keySet0;              // 0x08: pthread key of the thread's OglStateSet0
    u32 m_keySet1;              // 0x0c: the second state set's (GetThreadOglState1), most likely
    s32 m_keySet0Created;       // 0x10: 0 until the key is created (LDXR/STXR)
    s32 m_keySet1Created;       // 0x14
};
static_assert(offsetof(StateCacheThreadSafe, m_keySet0) == 0x08);
static_assert(offsetof(StateCacheThreadSafe, m_keySet0Created) == 0x10);
static_assert(offsetof(StateCacheThreadSafe, m_keySet1Created) == 0x14);

// One texture slot of the device (RenderDeviceData::m_textureSlots; 0x20 bytes; SetTexture: the slot of
// a GpuResource handle, its GL target at +0x0 and name at +0xc).
struct DeviceTextureSlot {
    u32 m_target;               // 0x00: (SetTexture compares and binds through it)
    u8 unk_04[8];               // 0x04
    u32 m_glName;               // 0x0c: the GL texture name (BindTexture's argument)
    u8 unk_10[8];               // 0x10
    u8 m_flags;                 // 0x18: bit 0 copied to the per-unit state
    u8 unk_19[7];               // 0x19
};
static_assert(offsetof(DeviceTextureSlot, m_glName) == 0x0c);
static_assert(offsetof(DeviceTextureSlot, m_flags) == 0x18);
static_assert(sizeof(DeviceTextureSlot) == 0x20);

// Aska::VertexShader (partial): the attribute locations of the linked program by vertex semantic and
// index (RenderDeviceGL::BindVertexFormat: m_attribLocation[semantic][index], -1 when unused). Size not
// recovered: the semantic count (16 here) is (d).
class VertexShader {
public:
    u8 unk_00[0x30];                    // 0x00
    u64 m_key;                          // 0x30: the shader's key (a program is looked up by its VS / PS keys)
    u8 unk_38[0x10];                    // 0x38
    s32 m_attribLocation[9][8];         // 0x48: [semantic][index] (UpdateVertexAttribute's instanced path: [1..] or [8])
    s32 m_attribCount;                  // 0x168: the program's attribute count (UpdateVertexAttribute)
};
static_assert(offsetof(VertexShader, m_key) == 0x30);
static_assert(offsetof(VertexShader, m_attribLocation) == 0x48);

// Aska::PixelShader (partial): its key (UpdateShaderProgram).
class PixelShader {
public:
    u8 unk_00[0x30];                    // 0x00
    u64 m_key;                          // 0x30
};
static_assert(offsetof(PixelShader, m_key) == 0x30);
static_assert(offsetof(VertexShader, m_attribCount) == 0x168);

// Aska::ShaderProgramValue (partial): a linked program (RenderDeviceData::m_program).
// Guest size 0x40 (UpdateShaderProgram: operator new(0x40) on a miss).
class ShaderProgramValue {
public:
    u64 m_hash;                         // 0x00: SpookyHash of {VS key, PS key} (the set's hash)
    u64 m_vsKey;                        // 0x08
    u64 m_psKey;                        // 0x10
    u32 m_glProgram;                    // 0x18: 0 until linked (CompileShaderProgram)
    u8 unk_1c[4];                       // 0x1c
    s32* m_attribLocations;             // 0x20: per attribute of the vertex shader, -1 when unused
    void* m_uniformLocations;           // 0x28: (SetVertexShaderConstant)
    u8 unk_30[0x10];                    // 0x30
};
static_assert(offsetof(ShaderProgramValue, m_vsKey) == 0x08);
static_assert(offsetof(ShaderProgramValue, m_glProgram) == 0x18);
static_assert(offsetof(ShaderProgramValue, m_attribLocations) == 0x20);
static_assert(sizeof(ShaderProgramValue) == 0x40);



// Aska::RenderDeviceData: the GL device's data (RenderDeviceGL::m_data). Guest size 0xc6b0
// (RenderDeviceGL::RenderDeviceGL: operator new(0xc6b0)); layout from RenderDeviceData() (its first
// part), GetTextureStateCaches, GetBoundTextureID, BindTexture, SetTexture, SetVertexShader,
// BindVertexFormat (port/decomp/render/render_device.c). Most of it is still padding.
// GetTextureStateCaches (479 self samples) is an open-addressing THashMap lookup by GL texture name,
// walked twice (count, then find), with a 64-bit division per probe; a miss takes a TPoolFast slot.
class RenderDeviceData {
public:
    void Ctor();                                       // _ZN4Aska16RenderDeviceDataC2Ev
    TextureStateCache* GetTextureStateCaches(u32 glName);
    u32 GetBoundTextureID(u32 target);                 // from the thread's OglStateSet0 (else glGetIntegerv)
    OglStateSet1* GetThreadOglState1();                // (natives: the existing one; creating it is the guest's)
    void UpdateShaderProgram();                        // (587 self) picks the program of the current VS / PS, uploads its uniforms
    bool UseProgram(u32 program);                      // UpdateShaderProgram's glUseProgram through the thread's state set 1
    bool ProgramReady() const;                         // UpdateShaderProgram only finds (the native's case): no program to create or link
    bool UpdateRenderState(RenderDeviceGL* device);    // (280 self) before a draw: the program, vertex arrays, caps, blending, depth, textures
    void UpdateVertexAttribute(OglStateSet0* ss);      // the arrays the program uses enabled, the others disabled
    void LastMinuteDrawCommands_Textures(OglStateSet0* ss, RenderDeviceGL* device);
    void LastMinuteDrawCommands_Blending(OglStateSet0* ss);
    void LastMinuteDrawCommands_Depth(OglStateSet0* ss);
    void UpdateTextureFilters(void* stateSet0, s32 unit, u32 glName);
    void DrawIndexedPrimitive(RenderDeviceGL* device, u32 prim, IndexBuffer& indexBuffer, u64 start, s32 count);  // (788 self)
    bool UsesInstancing() const { return m_instanceVbo != 0 || m_instanceData != nullptr || m_instanceDivisorMask != 0; }
    void BindFrameBuffer(GpuResource* target);
    void SetShaderProgramUniform(void* program);       // ShaderProgramValue*
    void SetCullMode(u32 mode);                        // Cull::Mode (< 3; the static iNewMode table maps it)
    void SetAlphaBlendFunction(u32 op, s32 separate);  // AlphaBlend::Operation, SeparateAlphaBlendMode::E

    u8 unk_000[6];                                                     // 0x000
    u8 m_anisotropySupported;                                          // 0x006: SetTextureSamplingMaxAnisotropic does nothing without it
    u8 unk_007[0x21];                                                  // 0x007
    u64 unk_028;                                                       // 0x028: 0 at construction
    u8 unk_030[0x110];                                                 // 0x030
    u32 unk_140;                                                       // 0x140: 0 at construction
    u32 m_instanceVbo;                                                 // 0x144: an instance-data vertex buffer (instanced draws)
    u8* m_instanceData;                                                // 0x148: or client memory
    u32 m_instanceAttribMask;                                          // 0x150: the instance attributes (bit per attribute)
    u32 m_instanceDivisorMask;                                         // 0x154: the arrays given a divisor (reset next draw)
    u32 m_instanceStride;                                              // 0x158
    u32 m_instanceCount;                                               // 0x15c: glDrawElementsInstanced from 2 on
    u8 m_drawEnabled;                                                  // 0x160: 1 at construction (with 0x161); 0: draws do nothing
    u8 unk_161;                                                        // 0x161
    u8 unk_162[0x56];                                                  // 0x162
    containers::TPoolFast<TextureStateCache> m_textureStatePool;       // 0x1b8
    containers::THashMap<u32, TextureStateCache*> m_textureStates;     // 0x200: GL name -> its cache (0x400 buckets at first)
    s32 m_glVersion;                                                   // 0x230: 0 at construction; GetGLVersion (0: GLES 2; BindVertexFormat's half-float / packed formats need it)
    u32 unk_234;                                                       // 0x234
    u8 unk_238;                                                        // 0x238: 1 at construction
    u8 unk_239[7];                                                     // 0x239
    u8 m_event[0x68];                                                  // 0x240: Aska::Event (sync)
    u32 m_vertexAttribCount;                                           // 0x2a8: BindVertexFormat disables attributes up to it
    u8 unk_2ac[4];                                                     // 0x2ac
    StateCacheThreadSafe* m_stateCache;                                // 0x2b0: the per-thread GL state
    DeviceTextureSlot m_textureSlots[0x400];                           // 0x2b8: indexed by a GpuResource's slot (count (d): ends at 0x82b8)
    u8 m_resourceArray[0x28];                                          // 0x82b8: Aska::TDynamicArray<TPair<GpuResource*, u32>> (vtable at 0x82b8)
    u8 m_shaderKeys[0x28];                                             // 0x82e0: TDynamicArray<ShaderKeyValue*>
    u8 m_programs[0x28];                                               // 0x8308: TDynamicArray<ShaderProgramValue*>
    u8 m_shaderKeySet[0x30];                                           // 0x8330: THashSet<ShaderKeyValue*> (0x11 buckets at first)
    u8 unk_8360[0x20];                                                 // 0x8360
    u8 m_bytes[0x28];                                                  // 0x8380: TDynamicArray<u8>
    containers::THashSet<ShaderProgramValue*> m_programSet;           // 0x83a8: the linked programs, by their keys' hash
    u64 m_programHash;                                                 // 0x83d8: UpdateShaderProgram's last lookup
    u64 m_programKey[2];                                               // 0x83e0: {VS key, PS key} hashed
    u8 unk_83f0[0x28];                                                 // 0x83f0
    VertexShader* m_vertexShader;                                      // 0x8418: SetVertexShader
    PixelShader* m_pixelShader;                                        // 0x8420: SetPixelShader (null: m_defaultPixelShader)
    PixelShader* m_defaultPixelShader;                                 // 0x8428
    u8 unk_8430[0x10];                                                 // 0x8430
    ShaderProgramValue* m_program;                                     // 0x8440: the current program
    u8 unk_8448[0xc6b0 - 0x8448];                                      // 0x8448
};
static_assert(offsetof(RenderDeviceData, m_anisotropySupported) == 0x6);
static_assert(offsetof(RenderDeviceData, m_instanceVbo) == 0x144);
static_assert(offsetof(RenderDeviceData, m_instanceData) == 0x148);
static_assert(offsetof(RenderDeviceData, m_instanceAttribMask) == 0x150);
static_assert(offsetof(RenderDeviceData, m_instanceCount) == 0x15c);
static_assert(offsetof(RenderDeviceData, m_drawEnabled) == 0x160);
static_assert(offsetof(RenderDeviceData, m_textureStatePool) == 0x1b8);
static_assert(offsetof(RenderDeviceData, m_textureStatePool.m_used.m_bits) == 0x1d0);
static_assert(offsetof(RenderDeviceData, m_textureStatePool.m_cursor) == 0x1f0);
static_assert(offsetof(RenderDeviceData, m_textureStatePool.m_count) == 0x1f4);
static_assert(offsetof(RenderDeviceData, m_textureStates) == 0x200);
static_assert(offsetof(RenderDeviceData, m_textureStates.table.m_maxLoadFactor) == 0x20c);
static_assert(offsetof(RenderDeviceData, m_textureStates.table.m_buckets.m_data) == 0x220);
static_assert(offsetof(RenderDeviceData, m_glVersion) == 0x230);
static_assert(offsetof(RenderDeviceData, m_event) == 0x240);
static_assert(offsetof(RenderDeviceData, m_vertexAttribCount) == 0x2a8);
static_assert(offsetof(RenderDeviceData, m_stateCache) == 0x2b0);
static_assert(offsetof(RenderDeviceData, m_textureSlots) == 0x2b8);
static_assert(offsetof(RenderDeviceData, m_resourceArray) == 0x82b8);
static_assert(offsetof(RenderDeviceData, m_shaderKeySet) == 0x8330);
static_assert(offsetof(RenderDeviceData, m_programSet) == 0x83a8);
static_assert(offsetof(RenderDeviceData, m_programSet.table.m_buckets.m_data) == 0x83c8);
static_assert(offsetof(RenderDeviceData, m_programHash) == 0x83d8);
static_assert(offsetof(RenderDeviceData, m_programKey) == 0x83e0);
static_assert(offsetof(RenderDeviceData, m_pixelShader) == 0x8420);
static_assert(offsetof(RenderDeviceData, m_defaultPixelShader) == 0x8428);
static_assert(offsetof(RenderDeviceData, m_vertexShader) == 0x8418);
static_assert(offsetof(RenderDeviceData, m_program) == 0x8440);
static_assert(sizeof(RenderDeviceData) == 0xc6b0);

// One vertex format of the device (RenderDeviceGL::m_vertexFormats; 0x2c bytes, 0x80 of them):
// BindVertexFormat(format, stream, base) walks m_count attributes {offset, type, semantic, index}.
struct VertexAttrGL {
    u8 m_offset, m_type, m_semantic, m_index;   // 0x9c / 0x9d / 0x9e / 0x9f in BindVertexFormat
};
struct VertexFormatGL {
    VertexAttrGL m_attrs[10];   // 0x00
    u8 m_count;             // 0x28: the attribute count
    u8 unk_29[3];           // 0x29
};
static_assert(offsetof(VertexFormatGL, m_count) == 0x28);
static_assert(sizeof(VertexFormatGL) == 0x2c);

// Aska::RenderDeviceGL (: RenderManagerBase): the GL device, Aska::g_pRenderDev. Guest size 0xec0c8
// (Global::InstantiateVideoManager / VideoManager::Init: operator new(0xec0c8)); layout from
// RenderDeviceGL(), RenderManagerBase() (its start), BindTexture, SetTexture, BindVertexFormat,
// GetGLVersion, RenderContextBatch::ApplyTextures (port/decomp/render/render_device.c). The base is
// almost all of it: a TPoolAtomic<GpuResource, 8000> (0x78-byte resources) and a TPoolFast of temp
// surfaces. Most setters (EnableZTest, SetCullMode, ...) go through the calling thread's
// OglStateSet0 (m_data->m_stateCache) and call GL only on a change.
class RenderDeviceGL {
public:
    void Ctor();                                           // _ZN4Aska14RenderDeviceGLC2Ev
    void BindTexture(u32 target, u32 glName);              // skipped when the thread's state has it
    void ActiveTexture(u32 unit);                          // skipped past the stage count or when active
    s32 GetGLVersion() const;                              // m_data's 0x230
    void BindVertexFormat(s32 format, s32 stride, void* base);   // (1371 self: the hottest device method)
    void BindVertexFormat(void* vertexBuffer);
    void SetTexture(u32 stage, GpuResource* const* res);
    void RemoveTexture(u32 stage);
    void SetScissorRect(const void* rect, bool on);
    void BindVertexBuffer(u64 a, void* b);
    void SetVertexShaderConstant(s32 reg, const void* data, s32 count);
    void SetPixelShaderConstant(s32 reg, const void* data, s32 count);
    void SetVertexShaderConstant(void* buffer);            // UniformValueBuffer2*
    void SetPixelShaderConstant(void* buffer);
    void SetVertexShader(VertexShader* vs);                // m_data->m_vertexShader
    void SetPixelShader(PixelShader* ps);
    // The render-state setters (RenderState::Apply's targets): they record the wanted state in the calling
    // thread's OglStateSet0, applied at the next draw (UpdateRenderState); the natives require the state
    // set to exist (render_state.cpp).
    void EnableZTest(bool on);
    void EnableZWrite(bool on);                            // glDepthMask on a change
    void SetZTestFunction(u32 func);                       // ZTest::Func (< 8)
    void SetCullMode(u32 mode);                            // m_data->SetCullMode
    void SetDepthBias(float a, float b);
    void EnableStencil(s32 mode);
    void SetStencilOp(u32 func, u32 fail, u32 zfail, u32 pass, s32 ref);      // GL_FRONT's, at once
    void SetStencilOpCCW(u32 func, u32 fail, u32 zfail, u32 pass, s32 ref);   // GL_BACK's
    void EnableAlphaBlend(bool on);
    void SetAlphaBlendFunction(u32 op, s32 separate);      // m_data->SetAlphaBlendFunction
    void SetTextureSamplingFilter(u32 stage, s32 filter);
    void SetTextureSamplingMipmapFilter(u32 stage, s32 filter);
    void SetTextureSamplingWrapMode(u32 stage, s32 u, s32 v, s32 w);
    void SetTextureSamplingMaxAnisotropic(u32 stage, u32 n);

    const void* vtable;                     // 0x00000: RenderManagerBase's first base: TPoolAtomic<GpuResource, 8000>
    u8 m_resourceUsed[0x3f0];               // 0x00008: the pool's used bits (zeroed by the constructor)
    u8 m_resources[8000][0x78];             // 0x003f8: the GpuResource pool
    u32 unk_ea9f8;                          // 0xea9f8
    u32 unk_ea9fc;                          // 0xea9fc
    u8 unk_eaa00;                           // 0xeaa00: 1 after the constructor
    u8 unk_eaa01[7];                        // 0xeaa01
    u8 m_tempSurfaces[0x48];                // 0xeaa08: TPoolFast<RenderManagerBase::TempSurface> (0x40 slots)
    u8 unk_eaa50[0x30];                     // 0xeaa50
    RenderDeviceData* m_data;               // 0xeaa80
    u32 m_textureStageCount;                // 0xeaa88: RenderContextBatch::ApplyTextures' stage count
    u32 m_extraTextureStageCount;           // 0xeaa8c: (up to 3 used)
    float unk_eaa90[2];                     // 0xeaa90: (1, 1) at construction
    u32 unk_eaa98;                          // 0xeaa98: 0x100 at construction
    VertexFormatGL m_vertexFormats[0x80];   // 0xeaa9c
    u8 unk_ec09c[4];                        // 0xec09c
    u32 m_gpuKind;                          // 0xec0a0: 0 at construction; 3 + m_gpuNumber >= 300 + an old driver: no separate blending
    u32 m_gpuNumber;                        // 0xec0a4    (LastMinuteDrawCommands_Blending; names (d))
    u32 unk_ec0a8;                          // 0xec0a8: 0 at construction
    u8 unk_ec0ac[0xc];                      // 0xec0ac
    s32 m_driverVersion[2];                 // 0xec0b8: major, minor (Blending: < 4.3 is old)
    u8 unk_ec0c0[8];                        // 0xec0c0
};
static_assert(offsetof(RenderDeviceGL, m_resources) == 0x3f8);
static_assert(offsetof(RenderDeviceGL, unk_ea9f8) == 0xea9f8);
static_assert(offsetof(RenderDeviceGL, m_tempSurfaces) == 0xeaa08);
static_assert(offsetof(RenderDeviceGL, m_data) == 0xeaa80);
static_assert(offsetof(RenderDeviceGL, m_textureStageCount) == 0xeaa88);
static_assert(offsetof(RenderDeviceGL, m_extraTextureStageCount) == 0xeaa8c);
static_assert(offsetof(RenderDeviceGL, unk_eaa98) == 0xeaa98);
static_assert(offsetof(RenderDeviceGL, m_vertexFormats) == 0xeaa9c);
static_assert(offsetof(RenderDeviceGL, m_gpuKind) == 0xec0a0);
static_assert(offsetof(RenderDeviceGL, m_driverVersion) == 0xec0b8);
static_assert(offsetof(RenderDeviceGL, unk_ec0a8) == 0xec0a8);
static_assert(sizeof(RenderDeviceGL) == 0xec0c8);

// ==== End of section: the device ====================================================================




// ==== Section: materials, shader constants, passes, post-processing (n-types-render-material) =======
// (MaterialList, MaterialContext, ShaderConstantManager / Handler, UniformValueBuffer2, AhslConst,
// RenderPass / RenderPassManager, PostProcessCombinerTBR / PostProcessBufferManager, ShadowManager)

// Aska::MaterialContext: one material's shader inputs (textures, samplers, constants) for the draw.
// Guest size 0x290 (MaterialList::Alloc: one per material, 0x2a0 apart, at +0x10 of a MaterialEntry);
// layout from MaterialContext(), Reset, MaterialList::Connect / IsPunchthrough / IsZprepassOFF /
// SetShaderLod (port/decomp/render/material.c). vtable (_ZTVN4Aska15MaterialContextE): 0 D1, 1 D0, then
// Apply(unsigned long, RenderDeviceGL*, ShaderNodeHandler*), ApplyToCommandBuffer.
class MaterialContext {
public:
    void Ctor();                                               // _ZN4Aska15MaterialContextC2Ev
    void Dtor();
    void Reset();
    void SetDefault(void* samplerMode);                        // Aska::TextureSamplerMode*
    void AddShaderTexture(s32 kind, void* texInfo, s32 slot);  // ShaderContext::ShaderTexKind, TEXTUREINFO*
    void RemoveShaderTexture(s32 kind, s32 slot);
    void MakeShaderConstant(void* manager);                    // ShaderConstantManager*
    void Apply(u64 a, void* device, void* shaderNodeHandler);
    void ApplyToCommandBuffer(u64 a, void* b, void* c);

    const void* vtable;          // 0x000: _ZTVN4Aska15MaterialContextE + 0x10
    u64 unk_008;                 // 0x008: 0 at construction
    u64 unk_010;                 // 0x010: 0 at construction (u64 at 0x17 too)
    u8 unk_018[8];               // 0x018
    u8 m_textures[0x200];        // 0x020: the shader textures (AddShaderTexture), zeroed by Reset
    u64 unk_220;                 // 0x220
    u64 unk_228;                 // 0x228
    u8 unk_230;                  // 0x230: 0xff at construction
    u8 unk_231[3];               // 0x231
    u32 unk_234;                 // 0x234
    u16 unk_238;                 // 0x238
    u8 unk_23a[8];               // 0x23a: 0xff.. at construction
    u8 unk_242;                  // 0x242: 0xff
    u8 unk_243;                  // 0x243: 0xff
    u8 unk_244;                  // 0x244
    u8 m_flags[2];               // 0x245: (u16, unaligned) 0x2001 at construction; bit 0 connected (MaterialList::Connect),
                                 //        bits 2-3 punch-through (IsPunchthrough), bit 3 Z-prepass off (IsZprepassOFF)
    u8 unk_247;                  // 0x247
    u8 unk_248;                  // 0x248: 3 at construction
    u8 unk_249;                  // 0x249
    u8 unk_24a[6];               // 0x24a
    u16 unk_250;                 // 0x250
    u8 unk_252[6];               // 0x252
    u64 unk_258;                 // 0x258
    u64 unk_260;                 // 0x260
    u16 unk_268;                 // 0x268
    u8 unk_26a[6];               // 0x26a
    u64 unk_270[4];              // 0x270
};
static_assert(offsetof(MaterialContext, m_textures) == 0x20);
static_assert(offsetof(MaterialContext, unk_230) == 0x230);
static_assert(offsetof(MaterialContext, m_flags) == 0x245);
static_assert(offsetof(MaterialContext, unk_248) == 0x248);
static_assert(sizeof(MaterialContext) == 0x290);

class MaterialData;  // Aska::MaterialData (the model's material record; opaque)

// One material of a MaterialList (0x2a0 bytes; MaterialList::Alloc: a buffer of n of them + 0x10).
struct MaterialEntry {
    const MaterialData* m_data;  // 0x000: MaterialList::Connect
    u64 unk_008;                 // 0x008
    MaterialContext m_context;   // 0x010
};
static_assert(offsetof(MaterialEntry, m_context) == 0x10);
static_assert(sizeof(MaterialEntry) == 0x2a0);

// Aska::ShaderConstantManager: a pass batch's material constants, a singly linked list of records
// {next, ..., u16 id & 0x7fff at +0x10, u8 slot & 0xf | 0x80 at +0x13} whose values come from a
// TPoolFast<Aska::Vector> (SetShaderConstantF_lockable, SetShaderConstantRefF, SetShaderConstantFUC;
// MaterialList::Activate fills it through AhslConst::AofConvertToNativeConstant: docs/render/
// hair-shader.md). Partial; the start of a RenderPassBatch.
class ShaderConstantManager {
public:
    void Dtor();
    bool SetShaderConstantFUC(s32 id, s32 slot, const MathVector* v, s32 count);   // (147 self)
    void SetShaderConstantRefF(s32 id, s32 slot, const MathVector* v, s32 count);
    void UpdatePacket(void* buffer, void* shaderCache);                              // UniformValueBuffer2*, ShaderCache*
    bool IsShaderConstantManagerDirty() const;

    void* m_head;                // 0x00: the first constant record
    u64 unk_08;                  // 0x08
    u8* m_ready;                 // 0x10: points at m_one (RenderPass::Init's inlined constructor)
    u16 unk_18;                  // 0x18
    u16 m_count;                 // 0x1a: records
    u8 m_dirty;                  // 0x1c: bit 0 set by a change; bits 0-1 = 2 after RenderPass::Init
    u8 m_one;                    // 0x1d: 1 after RenderPass::Init
    u8 unk_1e[2];                // 0x1e
};
static_assert(offsetof(ShaderConstantManager, m_count) == 0x1a);
static_assert(offsetof(ShaderConstantManager, m_dirty) == 0x1c);
static_assert(sizeof(ShaderConstantManager) == 0x20);

// Aska::RenderPassBatch: one material's slot in a RenderPass (0x1b8 bytes; RenderPass::Init: new[] of
// them after an 8-byte count; destroyed as ShaderConstantManagers). Layout from RenderPass::Init / Create / ~RenderPass.
struct RenderPassBatch {
    ShaderConstantManager m_constants;   // 0x000
    void* m_shaderNode;                  // 0x020: ShaderNodeModifier / DirectShaderNode (Create: &m_modifier; deleted via slot 0)
    u8 unk_028[0x10];                    // 0x028
    void* m_shaderCache[2];              // 0x038: refcounted (+0x4c atomic count) shader caches
    RenderState* m_renderState;          // 0x048: released by ~RenderPass
    u8 unk_050[8];                       // 0x050
    u8 unk_058;                          // 0x058: bits 0-2 cleared by Init
    u8 unk_059[0xc7];                    // 0x059: (0x5c..0xdf zeroed by Init)
    u8 m_modifier[0x98];                 // 0x120: Aska::ShaderNodeModifier (vtable) after Create(0) / DirectShaderNode after Create(1)
};
static_assert(offsetof(RenderPassBatch, m_shaderNode) == 0x20);
static_assert(offsetof(RenderPassBatch, m_shaderCache) == 0x38);
static_assert(offsetof(RenderPassBatch, m_renderState) == 0x48);
static_assert(offsetof(RenderPassBatch, m_modifier) == 0x120);
static_assert(sizeof(RenderPassBatch) == 0x1b8);

// Aska::RenderPass: the draw setup of one pass (color, shadow cast, Z prepass, ...) of a model: one
// RenderPassBatch per material. Guest size 0x1c8 (RenderPassManager::GetPass: operator new(0x1c8));
// layout from RenderPass(), Init, Create, ~RenderPass (port/decomp/render/render_pass.c). The passes
// derived from one (GetShadowCastPass, GetZprePass, ...) hang off m_children through m_nextSibling.
// vtable (_ZTVN4Aska10RenderPassE): 0 D1, 1 D0, ...
class RenderPass {
public:
    void Ctor();                                    // _ZN4Aska10RenderPassC2Ev
    void Dtor();                                    // _ZN4Aska10RenderPassD2Ev
    void DtorDelete();
    bool Init(s32 batches, void* storage);          // new[] RenderPassBatch (count cookie at -8); m_batchCount
    bool Create(s32 kind);                          // 0: ShaderNodeModifiers, 1: DirectShaderNodes, 2: ...
    bool Clone(const RenderPass* a, const RenderPass* b, bool c);
    void SetNoneModifyingShader();
    void BeginModifyingShader();
    void EndModifyingShader(void* materials);       // MaterialList*
    void AddShaderAdapter(void* adapter, s32 n);
    void InvalidateShaders();
    void InvalidateShaderCaches();
    void ReadyShaderKey(s32 a, s32 b, void* materials, bool c);
    u32 GetShaderKeyFlags(const RenderPassBatch* b);
    void ReadyShader();                             // (185 self)
    void UpdatePacket();
    void PrepareRenderState(void* materials, bool b);
    void UpdateTexture(void* materials, void* modifiers, const RENDERINFO* info, s32 a, bool b);   // (343 self)
    void UpdateMaterial(void* materials);
    void ClearTexture();
    void UpdateTextureShadowPass(void* materials, void* modifiers, const RENDERINFO* info, s32 a);
    s32 GetVertexPassNum() const;

    const void* vtable;              // 0x000: _ZTVN4Aska10RenderPassE + 0x10
    RenderPassBatch* m_batches;      // 0x008: Init's new[]
    u8 unk_010[0x10];                // 0x010
    u8 unk_020[6];                   // 0x020: 0 at construction
    u8 m_batchCount;                 // 0x026: Init's count
    u8 unk_027[2];                   // 0x027
    u8 unk_029;                      // 0x029: 0 after Init
    u16 unk_02a;                     // 0x02a: 0 at construction
    u8 unk_02c;                      // 0x02c
    u8 unk_02d;                      // 0x02d: 0 at construction
    u8 unk_02e;                      // 0x02e
    u8 m_bits2f[3];                  // 0x02f: 24 flag bits (0x20013 set at construction)
    u8 unk_032[6];                   // 0x032
    RenderPass* m_parent;            // 0x038: the pass this one derives from (its m_children list)
    RenderPass* m_children;          // 0x040: the derived passes
    RenderPass* m_nextSibling;       // 0x048
    u8 unk_050[0x130];               // 0x050: zeroed by the constructor (0x38..0x1c0)
    u64 unk_180;                     // 0x180: 0xfefefefefefefefe at construction
    u16 unk_188;                     // 0x188: 0xfefe at construction
    u8 unk_18a[0x0e];                // 0x18a
    u8* m_buffer;                    // 0x198: delete[]d by ~RenderPass
    u8 unk_1a0[0x28];                // 0x1a0: (0x1a0..0x1bf zeroed by the constructor; 0x1c0.. allocation padding)
};
static_assert(offsetof(RenderPass, m_batches) == 0x08);
static_assert(offsetof(RenderPass, m_batchCount) == 0x26);
static_assert(offsetof(RenderPass, m_bits2f) == 0x2f);
static_assert(offsetof(RenderPass, m_parent) == 0x38);
static_assert(offsetof(RenderPass, m_children) == 0x40);
static_assert(offsetof(RenderPass, m_nextSibling) == 0x48);
static_assert(offsetof(RenderPass, unk_180) == 0x180);
static_assert(offsetof(RenderPass, m_buffer) == 0x198);
static_assert(sizeof(RenderPass) == 0x1c8);

class RenderPassManager;  // Aska::RenderPassManager (0x3c0 bytes; MaterialList's constructor makes one): not recovered

// Aska::RenderPassManagerList: MaterialList's list of RenderPassManagers (0x28 bytes: a vtable, then an
// Aska::LinkElement sentinel whose links point at itself when empty, and a count).
struct RenderPassManagerList {
    const void* vtable;                  // 0x00: _ZTVN4Aska21RenderPassManagerListE + 0x10 (slot 2: Add)
    const void* m_linkVtable;            // 0x08: _ZTVN4Aska11LinkElementE + 0x10 (the sentinel)
    void* m_next;                        // 0x10: (self when empty; the first manager after the constructor's Add)
    RenderPassManager* m_last;           // 0x18: MaterialList::Alloc uses it as the manager
    u32 m_count;                         // 0x20
    u8 unk_24[4];                        // 0x24
};
static_assert(offsetof(RenderPassManagerList, m_last) == 0x18);
static_assert(sizeof(RenderPassManagerList) == 0x28);

// Aska::MaterialList: a model's materials (one MaterialEntry each) and its passes. Embedded in
// AofHandler at +0xe8 (scene; AofHandler::AofHandler calls MaterialList()); data size 0x228 (the
// RenderPass member is last); layout from MaterialList(), Alloc, Connect, IsPunchthrough, IsZprepassOFF,
// SetShaderLod, EnablePerMatLightContext, GetActualPerPixelLightCount, SetActiveMaterialCount, Activate
// (port/decomp/render/material.c). Activate (docs/render/hair-shader.md) copies the model's
// AFF::MaterialInfo flags into m_flags and each material's constants into m_pass.m_batches[i].m_constants.
class MaterialList {
public:
    void Ctor();                                       // _ZN4Aska12MaterialListC2Ev (also makes a RenderPassManager, 0x3c0)
    u32 GetAllocBufSize(s32 n, const void* meshset) const;   // n * 0x2a0 | 0x10, + extras per mesh
    bool Alloc(s32 n, void* buffer);                   // n MaterialEntry in buffer; Init / Create the passes
    void DeleteBuffer();
    void Connect(s32 i, s32 j, const MaterialData* data);    // m_entries[i].m_data, its context's connected bit
    void SetPerPixelLightCount(s32 n);
    void EnablePerMatLightContext(bool on);            // m_flags bit 6
    void SetPerMatLightContext(s32 a, s32 b, s32 freq);
    void UpdatePunchthroughZprepass();
    void SetAmbientBRDFCapability(s32 a, bool b);
    void DisableAmbientBRDFCapability();
    void Activate(const void* data, const void* info, s32 n, void* meshsets);   // AFF::MaterialInfo const*, AofhMeshset**
    bool Create(s32 n);
    void Clone(const MaterialList* src, bool b);
    void SetDirectMaterial(s32 i, void* m, void* prim, u64 a);
    void SetShaderConstantF(s32 i, s32 id, s32 slot, const MathVector* v, s32 count);
    void SetMaterialColor(s32 i, MathVector* v);       // SetShaderConstantF(i, 0x14, 0, v, 1)
    void SetTexSelector(s32 i, float v);
    void SetColorMultiplier(s32 i, const MathVector& mul, const MathVector& add);
    void SetUVMatrix(s32 i, const MathMatrix& m);
    s32 GetActualPerPixelLightCount() const;           // m_perPixelLights, 3 when -1
    void EnableAmbientBRDF(s32 type);
    void EnableShadowNoise(bool on);
    void EnableIBL(Light* light, bool b, s32 offsetType);
    void EnableSecondaryIBL(Light* light);
    void SetShaderLod(s32 lod);                        // every context's 0x1d and m_shaderLod
    void ServeShaderConstantBody();
    bool IsPunchthrough();                             // any active context with m_flags & 0xc
    bool IsZprepassOFF();                              // any with m_flags bit 3
    void UpdateMaterialContext();
    void SetActiveMaterialCount(u8 n);

    u8* m_ownedBuffer;                 // 0x000: delete[]d when m_flags & 3
    const void* m_materialData;        // 0x008: Activate's data
    u8* m_extra;                       // 0x010: after the entries (Alloc: buffer + (n * 0x2a0 | 0x10))
    MaterialEntry* m_entries;          // 0x018
    u16 m_flags;                       // 0x020: bits 0-1 owns the buffer, 2, 4-7 / 8 / 10 / 11 from AFF::MaterialInfo, 6 per-material light context, 9
    u8 m_activeCount;                  // 0x022: materials in use
    u8 m_count;                        // 0x023: Alloc's n
    s8 m_perPixelLights;               // 0x024: -1 at construction (3 then)
    u8 unk_025;                        // 0x025
    u8 unk_026[4];                     // 0x026: (an unaligned u32) 0 by EnablePerMatLightContext
    u8 unk_02a;                        // 0x02a
    u8 unk_02b;                        // 0x02b: 0xff at construction (u16 store)
    u8 m_shaderLod;                    // 0x02c
    u8 unk_02d;                        // 0x02d
    u8 unk_02e;                        // 0x02e: 0 at construction
    u8 unk_02f;                        // 0x02f
    RenderPass* m_activePass;          // 0x030: &m_pass after Alloc
    RenderPassManagerList m_managers;  // 0x038 (its m_count at 0x058)
    RenderPass m_pass;                 // 0x060
};
static_assert(offsetof(MaterialList, m_entries) == 0x18);
static_assert(offsetof(MaterialList, m_flags) == 0x20);
static_assert(offsetof(MaterialList, m_activeCount) == 0x22);
static_assert(offsetof(MaterialList, m_count) == 0x23);
static_assert(offsetof(MaterialList, m_perPixelLights) == 0x24);
static_assert(offsetof(MaterialList, m_shaderLod) == 0x2c);
static_assert(offsetof(MaterialList, m_activePass) == 0x30);
static_assert(offsetof(MaterialList, m_managers) == 0x38);
static_assert(offsetof(MaterialList, m_pass) == 0x60);
static_assert(sizeof(MaterialList) == 0x228);

// ==== End of section: materials ====================================================================

}  // namespace soa::native::render

#endif  // SOA_NATIVE_RENDER_LAYOUT_H
