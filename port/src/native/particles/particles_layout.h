// particles_layout.h: the guest data layouts of the `particles` subsystem (particles: Aska's particle manager, emitters, particle objects and their rendering).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/particles/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types particles` turns the structs into port/decomp/particles/types.json for Ghidra.
#ifndef SOA_NATIVE_PARTICLES_LAYOUT_H
#define SOA_NATIVE_PARTICLES_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../kernel/kernel_layout.h"
#include "../render/render_layout.h"
#include "../sync/sync_layout.h"
#include "gen/particles_addresses.h"  // kVaddr* / k*: the guest statics and constants (tools/gen_addresses.py)

namespace soa::native::particles {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// The other subsystems' classes these derive from or hold (their layout headers, included above).
using Task = kernel::Task;                                      // Aska::Task, 0x28
using TaskManager = kernel::TaskManager;                        // Aska::TaskManager, 0xff0
using INotify = kernel::INotify;                                // Aska::INotify {vtable}: slot 0 Handler(unsigned long)
using MessageDispatcherBlock = kernel::MessageDispatcherBlock;  // what a notify's Handler gets (m_arg0 / m_arg1)
using SimpleMessageDispatcher = kernel::SimpleMessageDispatcher;
using CriticalSection = sync::CriticalSection;                  // Aska::CriticalSection (0x28)
using Event = sync::Event;                                      // Aska::Event (0x68)
using FastCriticalSection = sync::FastCriticalSection;          // Aska::FastCriticalSection (0x90)
using HierarchicalObject = render::HierarchicalObject;          // Aska::HierarchicalObject (data 0x198)
using RenderableObject = render::RenderableObject;              // Aska::RenderableObject (0x310)

class IParticleEmitter;
class ParticleRenderManager;  // Aska::ParticleRenderManager (0x14570, ParticleManager::Init; not recovered yet)

using MathVector = math::Vector;  // Aska::Vector {x, y, z, w}
using MathMatrix = math::Matrix;  // Aska::Matrix

// Aska::IParticleObject: an emitter's particles (the base of ParticleObject<FeatureList<...>, ...>). Its data
// is 0xa10 bytes (IParticleObject(unsigned, unsigned, unsigned) writes up to 0xa08; CreateParticle
// allocates the concrete objects as 0xa10..0xa40). Fields from the constructor, SetAnimation and the
// emitters' Simulate (port/decomp/particles/object.c, emitter_hot.c); the rest not recovered yet.
class IParticleObject {
public:
    static constexpr int kSlotPrepare = 3;  // vtable: 0 / 1 the destructors, 2 Attach, 3 Prepare, 4 Reset, 5 BeginParticles

    const void* vtable;           // 0x000: _ZTVN4Aska15IParticleObjectE + 0x10 (a concrete object's)
    u8 unk_008[0x10c - 0x008];    // 0x008
    u32 m_textureId;              // 0x10c: the texture's id (IParticleEmitter::Prepare: Texture + 0x18)
    u8 unk_110[0x120 - 0x110];    // 0x110
    IParticleEmitter* m_nextEmitter;  // 0x120: the next emitter of the chain PrepareMatricesTraverse walks
    u8 unk_128[0x140 - 0x128];    // 0x128
    const u8* m_animData;         // 0x140: the texture animations (SetAnimation walks them)
    u8 unk_148[0x16c - 0x148];    // 0x148: SetAnimation's current animation (0x148), frames (0x158)
    u32 m_animation;              // 0x16c: the current animation's index (SetAnimation)
    u8 unk_170[0x178 - 0x170];    // 0x170: (0x174: SetAnimation clears it)
    u32 m_animParam;              // 0x178: the texture unit's parameter (Simulate copies it every frame)
    u8 unk_17c[0x1ac - 0x17c];    // 0x17c
    u16 m_renderLayer;            // 0x1ac: 0xc at construction (Prepare: SetRenderLayer)
    u8 unk_1ae[0x1f4 - 0x1ae];    // 0x1ae
    u16 m_animFlags;              // 0x1f4: bit 1 Prepare's SetRenderLayer flag, bit 11 / bit 12 (SetAnimation), 0 at construction
    u8 m_renderFlags;             // 0x1f6: bit 0 the texture unit's flag bit 2 (Simulate), bit 1 at construction
    u8 unk_1f7[0xa10 - 0x1f7];    // 0x1f7
};
static_assert(offsetof(IParticleObject, m_textureId) == 0x10c);
static_assert(offsetof(IParticleObject, m_nextEmitter) == 0x120);
static_assert(offsetof(IParticleObject, m_renderLayer) == 0x1ac);
static_assert(offsetof(IParticleObject, m_animData) == 0x140);
static_assert(offsetof(IParticleObject, m_animation) == 0x16c);
static_assert(offsetof(IParticleObject, m_animParam) == 0x178);
static_assert(offsetof(IParticleObject, m_animFlags) == 0x1f4);
static_assert(offsetof(IParticleObject, m_renderFlags) == 0x1f6);
static_assert(sizeof(IParticleObject) == 0xa10);

// Aska::IParticleEmitter::MatrixContext: the matrices an emitter's Simulate works with (FillMatrixContext:
// the emitter's world matrix and its inverse, the renderable's, the linked object's or null). 0x28 bytes
// (Simulate's stack frame).
struct MatrixContext {
    const MathMatrix* world;            // 0x00 (Simulate takes the emitter's position from its translation)
    const MathMatrix* invWorld;         // 0x08
    const MathMatrix* renderWorld;      // 0x10
    const MathMatrix* renderInvWorld;   // 0x18
    const MathMatrix* linkedWorld;      // 0x20
};
static_assert(sizeof(MatrixContext) == 0x28);

// Aska::IParticleEmitter::EmitContext: Emit's input (0xe8 bytes in Simulate's frame). Simulate sets m_dt and
// m_flags = 0 (and m_scale when the emitter takes its scale from its matrix); Emit reads the rest only with
// flags set, and writes 0x00..0x17 and 0xd0..0xdf.
struct EmitContext {
    MathVector m_scale;           // 0x00
    u8 unk_10[0xe0 - 0x10];       // 0x10
    float m_dt;                   // 0xe0
    u8 m_flags;                   // 0xe4: bit 0 an offset position (0x30..0x38), bit 3 a scale (0x40..0x4c)
    u8 unk_e5[3];                 // 0xe5
};
static_assert(offsetof(EmitContext, m_dt) == 0xe0);
static_assert(offsetof(EmitContext, m_flags) == 0xe4);
static_assert(sizeof(EmitContext) == 0xe8);

// Aska::ParticleEmitterUnit<ParticleFeatures::Texture> as Simulate reads it (its place in the emitter depends
// on the feature list: the generated table's texture offset).
struct TextureUnit {
    u32 m_animParam;   // 0x0: -> IParticleObject::m_animParam
    u8 unk_4[6];       // 0x4
    u8 m_animation;    // 0xa: the animation to show (SetAnimation when it changes)
    u8 unk_b[3];       // 0xb
    u8 m_flags;        // 0xe: bit 2 -> IParticleObject::m_renderFlags bit 0
};
static_assert(offsetof(TextureUnit, m_animation) == 0xa);
static_assert(offsetof(TextureUnit, m_flags) == 0xe);

// Aska::ParticleRenderableBase: the renderable an emitter draws its particles with (a RenderableObject).
// Every ParticleRenderableObject<...> is allocated as 0xfe0 bytes (ParticleManager::CreateParticle<...>:
// operator new(0xfe0, 0x10, 1)); the fields here from IsBufferReady, SkipThisFrame / IsEmitting and the
// emitters' Simulate (port/decomp/particles/renderable.c, emitter.c, emitter_hot.c). The rest is not
// recovered yet.
// Double-buffered: m_buffer (0 / 1) is the half being filled; each half's stamp (m_stamp) is the
// manager's m_fillFrame when it was filled (renderable.c: End).
class ParticleRenderableBase {
public:
    bool IsBufferReady() const;  // _ZNK4Aska22ParticleRenderableBase13IsBufferReadyEv

    RenderableObject base;   // 0x000: m_renderFlags (0x198): SkipThisFrame tests 0x2101 (bits 0, 8, 13)
    u8 unk_310[0x860 - 0x310];  // 0x310
    MathVector m_emitterPosition;  // 0x860: the emitter's position at its last Simulate
    u8 unk_870[0x8b4 - 0x870];  // 0x870
    s32 m_activeCount;       // 0x8b4: the particles alive (Simulate clears it, IsEmitting = != 0)
    u8 unk_8b8[0x9c0 - 0x8b8];  // 0x8b8
    u64 m_textureName;       // 0x9c0: the object's texture (its animation data + 0x10; Prepare)
    u8 unk_9c8[8];           // 0x9c8
    const void* m_texture;   // 0x9d0: TextureManager::QueryTextureEx(m_textureName) (0: not found yet)
    u8 unk_9d8[0xf50 - 0x9d8];  // 0x9d8
    u32 m_stamp[2];          // 0xf50: per half, the manager's m_fillFrame it was filled in (0: never)
    u32 m_buffer;            // 0xf58: the half being filled
    u8 m_lodFlags;           // 0xf5c: bit 6: Prepare clears the renderable's m_hoc.m_flags bit 4
    u8 unk_f5d[0xfe0 - 0xf5d];  // 0xf5d
};
static_assert(offsetof(ParticleRenderableBase, m_emitterPosition) == 0x860);
static_assert(offsetof(ParticleRenderableBase, m_activeCount) == 0x8b4);
static_assert(offsetof(ParticleRenderableBase, m_textureName) == 0x9c0);
static_assert(offsetof(ParticleRenderableBase, m_texture) == 0x9d0);
static_assert(offsetof(ParticleRenderableBase, m_stamp) == 0xf50);
static_assert(offsetof(ParticleRenderableBase, m_lodFlags) == 0xf5c);
static_assert(offsetof(ParticleRenderableBase, m_buffer) == 0xf58);
static_assert(sizeof(ParticleRenderableBase) == 0xfe0);

// Aska::IParticleEmitter: the base of every ParticleEmitter<FeatureList<...>> (74 instantiations). A
// HierarchicalObject (data 0x198) whose own members start at 0x198. Layout from IParticleEmitter() (writes up
// to 0x324), SkipThisFrame, IsEmitting, PrepareMatrices, FillMatrixContext and ParticleManager's dispatch
// (port/decomp/particles/emitter.c, manager.c). The concrete emitters are 0x400..0x510 bytes
// (CreateParticle's operator new); their feature units follow at 0x328.
// The dispatch protocol (ParticleManager): m_dispatchLock 0 -> 1 (a CAS) takes the emitter for one Simulate
// and clears m_idle; the worker's Handler runs Simulate (vtable slot 51), sets m_idle and puts the lock back
// to 0 (only from 1); ~IParticleEmitter sleeps until m_idle.
// vtable (_ZTVN4Aska16IParticleEmitterE): 0-43 as HierarchicalObject (41 VirtualBoundingSphere, 42
// GetBoundingBox, 43 OnActive its own), then 44 Attach, 45 Prepare, 46 Reset, 47 Stop, 48 / 49 (pure: the
// feature list's), 50 IsEmitting, 51 Simulate(float) (pure), 52 SetLandscapeConstraint,
// 53 GetTotalNumberOfParticles, 54 GetActiveNumberOfParticles.
class IParticleEmitter {
public:
    static constexpr int kSlotPrepare = 45;
    static constexpr int kSlotSimulate = 51;
    // m_flags
    static constexpr u16 kFlagEnabled = 1 << 0;     // RunLow / RunAfterRendering skip an emitter without it
    static constexpr u16 kFlagMatrixLink = 1 << 2;  // PrepareMatrices: the renderable follows the emitter
    static constexpr u16 kFlagSkippable = 1 << 6;   // SkipThisFrame may skip it (the renderable's flags)
    static constexpr u16 kFlagPaused = 1 << 8;      // Simulate does nothing
    // m_emitFlags
    static constexpr u8 kEmitStopWhenStill = 1 << 3;
    static constexpr u8 kEmitScaleFromMatrix = 1 << 4;

    static constexpr int kSlotWorldMatrix = 19, kSlotSetWorldMatrix = 20, kSlotMakeMatrix = 21, kSlotSetPosition = 26,
                         kSlotSetPosture = 29, kSlotSetScale = 32;  // (HierarchicalObject's)

    bool SkipThisFrame() const;             // _ZNK4Aska16IParticleEmitter13SkipThisFrameEv
    void Prepare();                         // slot 45  _ZN4Aska16IParticleEmitter7PrepareEv
    void PrepareMatrices();                 // _ZN4Aska16IParticleEmitter15PrepareMatricesEv
    void PrepareMatricesTraverse();         // _ZN4Aska16IParticleEmitter23PrepareMatricesTraverseEv
    void FillMatrixContext(MatrixContext* m);  // _ZN4Aska16IParticleEmitter17FillMatrixContextEPNS0_13MatrixContextE
    FastCriticalSection* SimulateLock();    // (host) m_simulateLock, made on first use (null when that fails)
    bool IsEmitting() const;                // slot 50  _ZNK4Aska16IParticleEmitter10IsEmittingEv
    s32 GetActiveNumberOfParticles() const; // slot 54  _ZNK4Aska16IParticleEmitter26GetActiveNumberOfParticlesEv

    // slot 51 Simulate(float), the ParticleEmitter<FeatureList<...>> instantiations' (one body: particles_simulate.cpp;
    // `k` the instantiation's callees and its texture unit's offset)
    struct Instantiation;
    void Simulate(float dt, const Instantiation& k);

    // Host helpers (not guest symbols): the virtual calls the manager makes.
    void CallPrepare();               // slot 45 through the guest vtable
    void CallSimulate(float dt);      // slot 51 through the guest vtable

    HierarchicalObject base;      // 0x000: vtable _ZTVN4Aska16IParticleEmitterE + 0x10 (a concrete emitter's)
    u32 m_id;                     // 0x198: the low 32 bits of `this` (the constructor)
    u8 m_idle;                    // 0x19c: 1 when no Simulate is pending or running (1 at construction)
    u8 unk_19d[3];                // 0x19d
    s32 m_dispatchLock;           // 0x1a0: 1 while dispatched to a worker (atomic; 0 at construction)
    u8 unk_1a4[4];                // 0x1a4
    u64 m_dispatchKey;            // 0x1a8: the Simulate message's first key (keeps one emitter on one worker)
    u32 m_serial;                 // 0x1b0: the Simulate message's serial; Handler writes 0xffffffff
    u8 unk_1b4[4];                // 0x1b4
    IParticleObject* m_object;    // 0x1b8: its particles (Reset calls slot 4 on it)
    ParticleRenderableBase* m_renderable;  // 0x1c0
    HierarchicalObject* m_linked; // 0x1c8: an object whose world matrix the matrix context also takes (or 0)
    IParticleEmitter* m_child;    // 0x1d0: PrepareMatricesTraverse descends into it
    void* m_matrixBuffer;         // 0x1d8: UpdateMatrixBuffer's 0x140 bytes (ParticleManager::Malloc)
    FastCriticalSection* m_simulateLock;  // 0x1e0: made by the first Simulate (operator new(0x90, nothrow))
    u8 unk_1e8[0x1fc - 0x1e8];    // 0x1e8: 0 at construction
    float m_unk1fc;               // 0x1fc: 0 at construction; Simulate passes (m_unk200 < m_unk1fc) to RenderProcedure
    float m_unk200;               // 0x200: 0 at construction
    float m_unk204;               // 0x204: 86400.0 at construction
    float m_lastTime;             // 0x208: the manager's m_time at its last Simulate (Handler)
    u8 unk_20c[3];                // 0x20c: 0 at construction
    u8 m_matrixMode;              // 0x20f: FillMatrixContext: 1 = matrices made on demand; RunLow skips it for Simulate
    u8 m_linkMode;                // 0x210: RunLow / Kick make no matrices for it when set; Simulate needs m_matrixBuffer for 1 / 2
    u8 m_linkModeNext;            // 0x211: Prepare copies it to m_linkMode
    u8 unk_212;                   // 0x212: 0 at construction
    u8 m_waitBuffer;              // 0x213: its renderable's buffer wasn't ready (RunLow); RunAfterRendering dispatches it
    u16 m_flags;                  // 0x214: kFlag* (kFlagEnabled at construction)
    u8 unk_216[0x280 - 0x216];    // 0x216
    float m_emitRate;             // 0x280: particles per second (times the time scale)
    float m_emitRandomness;       // 0x284: below 100: the rate varies by a random share (percent); 0 with
                                  //        kEmitStopWhenStill: stop at once
    float m_emitAccum;            // 0x288: the particles due (Simulate emits the whole ones; Reset clears it)
    u8 unk_28c[0x2d9 - 0x28c];    // 0x28c
    u8 m_emitFlags;               // 0x2d9: kEmit* (bits 0-5 cleared at construction)
    u8 unk_2da[6];                // 0x2da
    MathVector m_lastPosition;    // 0x2e0: kEmitStopWhenStill: where it was at the first Simulate (and since)
    MathVector m_prevPosition;    // 0x2f0: (zero at construction; PrepareMatrices' reset: the translation, w 1)
    u8 m_stopped;                 // 0x300: kEmitStopWhenStill: it came within 0.1 of m_lastPosition
    u8 m_resetMatrices;           // 0x301: PrepareMatrices resets 0x2ec.. then (Reset sets it)
    u8 unk_302[0xe];              // 0x302
    MathVector m_scale;           // 0x310: kEmitScaleFromMatrix: the world matrix's scale
    float m_timeScale;            // 0x320: Simulate's dt factor (1 at construction)
    u8 m_firstSimulate;           // 0x324: 1 at construction
    u8 unk_325[3];                // 0x325
};
static_assert(offsetof(IParticleEmitter, m_id) == 0x198);
static_assert(offsetof(IParticleEmitter, m_idle) == 0x19c);
static_assert(offsetof(IParticleEmitter, m_dispatchLock) == 0x1a0);
static_assert(offsetof(IParticleEmitter, m_dispatchKey) == 0x1a8);
static_assert(offsetof(IParticleEmitter, m_serial) == 0x1b0);
static_assert(offsetof(IParticleEmitter, m_object) == 0x1b8);
static_assert(offsetof(IParticleEmitter, m_renderable) == 0x1c0);
static_assert(offsetof(IParticleEmitter, m_linked) == 0x1c8);
static_assert(offsetof(IParticleEmitter, m_child) == 0x1d0);
static_assert(offsetof(IParticleEmitter, m_matrixBuffer) == 0x1d8);
static_assert(offsetof(IParticleEmitter, m_simulateLock) == 0x1e0);
static_assert(offsetof(IParticleEmitter, m_unk1fc) == 0x1fc);
static_assert(offsetof(IParticleEmitter, m_lastTime) == 0x208);
static_assert(offsetof(IParticleEmitter, m_matrixMode) == 0x20f);
static_assert(offsetof(IParticleEmitter, m_linkMode) == 0x210);
static_assert(offsetof(IParticleEmitter, m_waitBuffer) == 0x213);
static_assert(offsetof(IParticleEmitter, m_flags) == 0x214);
// The instantiation-specific pieces of a ParticleEmitter<FeatureList<...>>::Simulate (gen/particles_instantiations.inc):
// its callees' guest addresses and its texture unit's offset (0: none).
struct IParticleEmitter::Instantiation {
    u64 affect = 0, emit = 0, render = 0;
    u32 textureOffset = 0;
};
static_assert(offsetof(IParticleEmitter, m_emitRate) == 0x280);
static_assert(offsetof(IParticleEmitter, m_emitAccum) == 0x288);
static_assert(offsetof(IParticleEmitter, m_emitFlags) == 0x2d9);
static_assert(offsetof(IParticleEmitter, m_lastPosition) == 0x2e0);
static_assert(offsetof(IParticleEmitter, m_stopped) == 0x300);
static_assert(offsetof(IParticleEmitter, m_scale) == 0x310);
static_assert(offsetof(IParticleEmitter, m_timeScale) == 0x320);
static_assert(offsetof(IParticleEmitter, m_firstSimulate) == 0x324);
static_assert(sizeof(IParticleEmitter) == 0x328);

// Aska::ParticleManager: the particle task manager (Global::m_pParticleManager). Guest size 0x90e8
// (Global::InstantiateParticleManager: operator new(0x90e8, nothrow)); layout from ParticleManager(), Init,
// Add / Delete, RunLow, RunAfterRendering, DispatchEmitters, Kick, Handler (port/decomp/particles/manager.c).
// A TaskManager whose task list holds the emitters, and an INotify (at 0xff0: the workers' Simulate
// messages 0x29a.. land in Handler through it). Per frame (Run's levels): RunLow (level 0xe) prepares every
// enabled emitter, lists the ones whose matrices are to be made (message 0x299 to the ParticleMakeMatrix at
// 0x10a0, which goes on to dispatch) and the ones to simulate, and dispatches those (DispatchEmitters: one
// message per worker); RunAfterRendering (level 0x1c) dispatches the emitters RunLow left waiting for a
// buffer. m_inFlight counts the emitters dispatched and not yet simulated: RunLow starts a new round only
// when it is 0.
// vtable (_ZTVN4Aska15ParticleManagerE): TaskManager's with 2 Add, 5 Delete, 6 GetClassID, 16 GetDefaultLevel,
// 17 Handler, 18 Get, 19 Set, 20 Run; then the Task base's (+0x28; thunks) and the INotify's (+0xff0: slot 0
// the Handler thunk _ZThn4080_).
class ParticleManager {
public:
    static constexpr u64 kListCapacity = 0x800;
    static constexpr s32 kRunLowLevel = 0xe, kRunAfterRenderingLevel = 0x1c;
    static constexpr u16 kMsgMakeMatrix = 0x299;  // to m_makeMatrix: (Task form, barrier) a list / one emitter
    static constexpr u16 kMsgSimulate = 0x29a;    // to m_notify: + the worker's index (DispatchEmitters)

    // Virtuals (TaskManager's slots)
    void Add(containers::LinkElement* e);     // slot 2  _ZN4Aska15ParticleManager3AddEPNS_21AnimatableLinkElementE
    void Delete(containers::LinkElement* e);  // slot 5  _ZN4Aska15ParticleManager6DeleteEPNS_21AnimatableLinkElementE
    u64 GetClassID(s32 depth) const;          // slot 6  _ZNK4Aska15ParticleManager10GetClassIDEi (+ thunk)
    u32 GetDefaultLevel() const;              // slot 16 _ZNK4Aska15ParticleManager15GetDefaultLevelEv (+ thunk)
    void Handler(MessageDispatcherBlock* b);  // slot 17 _ZN4Aska15ParticleManager7HandlerEm (+ the INotify thunk)
    void Run(s32 level);                      // slot 20 _ZN4Aska15ParticleManager3RunEi (+ thunk)
    // Methods
    void RunLow();                                        // _ZN4Aska15ParticleManager6RunLowEv
    void RunAfterRendering();                             // _ZN4Aska15ParticleManager17RunAfterRenderingEv
    bool DispatchEmitters();                              // _ZN4Aska15ParticleManager16DispatchEmittersEv
    bool DispatchEmitter(IParticleEmitter* e, bool wait); // _ZN4Aska15ParticleManager15DispatchEmitterEPNS_16IParticleEmitterEb
    void Kick(IParticleEmitter* e);                       // _ZN4Aska15ParticleManager4KickEPNS_16IParticleEmitterE
    void Tick(IParticleEmitter* e, float dt);             // _ZN4Aska15ParticleManager4TickEPNS_16IParticleEmitterEf

    // Host helpers (not guest symbols): the pieces the methods share.
    void SimulateOne(IParticleEmitter* e, float maxDt);  // one emitter of Handler's message
    bool PostSimulate(IParticleEmitter* e, bool wait);  // the 0x29a message for one emitter (DispatchEmitter's body)
    void PostMakeMatrix(u32 barrier, void* a0, void* a1, u64 k0);  // the 0x299 message, retried until queued
    void PostSimulateList(u16 msg, IParticleEmitter** list, u64 n);  // a 0x29a.. message for n emitters, retried
    IParticleEmitter* FirstEmitter() const;
    IParticleEmitter* NextEmitter(const IParticleEmitter* e) const;  // nullptr at the end of the list

    TaskManager base;                  // 0x0000: the emitters are its task list (m_sentinel, m_count)
    INotify m_notify;                  // 0x0ff0: vtable _ZTVN4Aska15ParticleManagerE + 0x170 (Handler thunk)
    float m_time;                      // 0x0ff8: the sum of VSync::GetDt(0) (RunLow)
    CriticalSection m_cs;              // 0x0ffc: the emitter list (Add / Delete / RunLow / RunAfterRendering)
    u8 unk_1024[4];                    // 0x1024
    ParticleRenderManager* m_renderManager;  // 0x1028: Init (also Global::m_pParticleRenderManager)
    Event m_event;                     // 0x1030: Create(true, true)
    s32 m_inFlight;                    // 0x1098: emitters dispatched and not simulated yet (atomic)
    u8 unk_109c[4];                    // 0x109c
    INotify m_makeMatrix;              // 0x10a0: an Aska::ParticleMakeMatrix (vtable _ZTVN4Aska18ParticleMakeMatrixE + 0x10)
    u32 m_fillFrame;                   // 0x10a8: 1 at construction; the renderables stamp their halves with it
    u32 m_drawnFrame;                  // 0x10ac: IsBufferReady: a half stamped after it isn't drawn yet
    u32 m_frameSlots[2];               // 0x10b0: RunAfterRendering stores m_fillFrame at [m_frameSlots[1]] (the
                                       //         second doubles as the index), takes [0] and clears both
    INotify m_deleteHandler;           // 0x10b8: an Aska::ParticleManager::ParticleDeleteHandler
    IParticleEmitter** m_matrixList;   // 0x10c0: = m_matrixStorage: RunLow's emitters to make matrices for
    u64 m_matrixCount;                 // 0x10c8
    IParticleEmitter** m_dispatchList; // 0x10d0: = m_dispatchStorage: RunLow's emitters to simulate
    u64 m_dispatchCount;               // 0x10d8
    IParticleEmitter* m_matrixStorage[kListCapacity];    // 0x10e0
    IParticleEmitter* m_dispatchStorage[kListCapacity];  // 0x50e0
    u8 m_buffersPending;               // 0x90e0: RunLow left an emitter waiting for its buffer
    u8 unk_90e1[7];                    // 0x90e1
};
static_assert(offsetof(ParticleManager, m_notify) == 0xff0);
static_assert(offsetof(ParticleManager, m_time) == 0xff8);
static_assert(offsetof(ParticleManager, m_cs) == 0xffc);
static_assert(offsetof(ParticleManager, m_renderManager) == 0x1028);
static_assert(offsetof(ParticleManager, m_event) == 0x1030);
static_assert(offsetof(ParticleManager, m_inFlight) == 0x1098);
static_assert(offsetof(ParticleManager, m_makeMatrix) == 0x10a0);
static_assert(offsetof(ParticleManager, m_fillFrame) == 0x10a8);
static_assert(offsetof(ParticleManager, m_drawnFrame) == 0x10ac);
static_assert(offsetof(ParticleManager, m_frameSlots) == 0x10b0);
static_assert(offsetof(ParticleManager, m_deleteHandler) == 0x10b8);
static_assert(offsetof(ParticleManager, m_matrixList) == 0x10c0);
static_assert(offsetof(ParticleManager, m_matrixCount) == 0x10c8);
static_assert(offsetof(ParticleManager, m_dispatchList) == 0x10d0);
static_assert(offsetof(ParticleManager, m_dispatchCount) == 0x10d8);
static_assert(offsetof(ParticleManager, m_matrixStorage) == 0x10e0);
static_assert(offsetof(ParticleManager, m_dispatchStorage) == 0x50e0);
static_assert(offsetof(ParticleManager, m_buffersPending) == 0x90e0);
static_assert(sizeof(ParticleManager) == 0x90e8);

}  // namespace soa::native::particles

#endif  // SOA_NATIVE_PARTICLES_LAYOUT_H
