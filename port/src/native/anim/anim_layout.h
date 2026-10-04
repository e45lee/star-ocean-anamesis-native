// anim_layout.h: the guest data layouts of the `anim` subsystem (animation controllers (TAaf*), blending, IK).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/anim/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types anim` turns the structs into port/decomp/anim/types.json for Ghidra.
#ifndef SOA_NATIVE_ANIM_LAYOUT_H
#define SOA_NATIVE_ANIM_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../containers/containers_layout.h"
#include "../render/render_layout.h"

namespace soa::native::anim {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// The engine bases (render_layout.h: the object hierarchy) and the math values (opaque until math lands).
using render::HierarchicalObject;
using render::IAnimatable;
using render::MathMatrix;
using render::MathQuaternion;
using render::MathVector;

class AafHandler;
class AafController;
class CAnimationElement;
class CAnimationBlendContainer;

// Return types of the guest methods below: from Ghidra's signatures in port/decomp/anim/ (float results
// fixed by hand where the decompile shows an s0 return); a `void` may still hide a result Ghidra didn't
// see: check the decompile before binding a member with NATIVE_METHOD.

// ---- AAF data (the animation file, read in place) ---------------------------------------------------

// Aska::AafHeader: the AAF chunk header (the file is "AAF " + an AskaResource; AafHandler::AttachAaf finds
// this block (its first u16 is 0x2e) and stores it as m_header). Only what AafHandler reads is named
// (port/decomp/anim/aaf_handler.c: AttachAaf, Length, IsChunkReady, GetComplementBufferSize).
struct AafHeader {
    u16 m_version;              // 0x00: 0x2e (AttachAaf checks it)
    u16 m_flags;                // 0x02: bit 0 streamed (AafHandler::m_flags bit 6)
    u16 m_targetCount;          // 0x04: targets (AafHandler::m_targetCount)
    u16 m_countC;               // 0x06: the independent controllers (AafHandler::m_countC)
    u16 m_countA;               // 0x08: the normal controllers (AafHandler::m_countA)
    u16 m_countB;               // 0x0a: (AafHandler::m_countB)
    u16 m_param0c;              // 0x0c: copied to AafHandler::m_param48
    u16 m_chunkCount;           // 0x0e: streamed chunks (0: one block)
    float m_length;             // 0x10: the animation's length in frames (AafHandler::Length)
    u8 unk_14[4];               // 0x14
    u32 m_complementBufferSize; // 0x18: GetComplementBufferSize
    u8 unk_1c[4];               // 0x1c
    u32 m_targetsOffset;        // 0x20: the first target header, from the file start
    u8 unk_24[4];               // 0x24
    u32 m_chunkTableOffset;     // 0x28: the chunk records (0xc bytes each) from AafHandler::m_data
    float m_chunkLength;        // 0x2c: frames per chunk
};
static_assert(offsetof(AafHeader, m_flags) == 0x02);
static_assert(offsetof(AafHeader, m_targetCount) == 0x04);
static_assert(offsetof(AafHeader, m_countA) == 0x08);
static_assert(offsetof(AafHeader, m_chunkCount) == 0x0e);
static_assert(offsetof(AafHeader, m_length) == 0x10);
static_assert(offsetof(AafHeader, m_complementBufferSize) == 0x18);
static_assert(offsetof(AafHeader, m_targetsOffset) == 0x20);
static_assert(offsetof(AafHeader, m_chunkTableOffset) == 0x28);
static_assert(offsetof(AafHeader, m_chunkLength) == 0x2c);
static_assert(sizeof(AafHeader) == 0x30);

// One animated target of an AafHandler (AafHandler::m_targets, 0x10 each; AttachAaf fills the header,
// CreateControllers the object).
struct AafTarget {
    const u8* m_header;       // 0x00: the target's header in the file (u8 flags, u8 kind, u16 controller count, u32 size, ...)
    IAnimatable* m_object;    // 0x08: the animated object (null until the controllers are created)
};
static_assert(sizeof(AafTarget) == 0x10);

// Aska::AafControllerInfo: one controller of an AafHandler (0x30 each, in AafHandler::m_infos; AttachAaf
// fills them, the calc functors walk them: AafCalcCommonFunctor::CalcAndSetSubFunctor).
struct AafControllerInfo {
    u64 m_setArg;               // 0x00: the packed target argument passed to SetValueToTarget (an AafSetValueArg's first word)
    AafController* m_controller;// 0x08: the controller object (an IController: TAafNormalController<...> etc.)
    const u8* m_header;         // 0x10: its AafControllerHeader in the file (u8 type, ..., u16 size at +2, u16 key header offset at +6)
    const u8* m_keyHeader;      // 0x18: its keyframe header (null: no keys)
    const u8* m_chunkData;      // 0x20: the current chunk's data (streamed animations)
    u32 m_chunkPos;             // 0x28
    u16 m_targetIndex;          // 0x2c: index into AafHandler::m_targets
    u8 m_flags;                 // 0x2e: bits 0-2 disabled / detached (the functors skip a controller unless 0), bit 2 no
                                //        collision target, bit 5 (with 0x27 the complement skip), bit 6 one key
    u8 unk_2f;                  // 0x2f
};
static_assert(offsetof(AafControllerInfo, m_controller) == 0x08);
static_assert(offsetof(AafControllerInfo, m_keyHeader) == 0x18);
static_assert(offsetof(AafControllerInfo, m_targetIndex) == 0x2c);
static_assert(offsetof(AafControllerInfo, m_flags) == 0x2e);
static_assert(sizeof(AafControllerInfo) == 0x30);

// ---- Aska::AafHandler: one animation (an AAF) bound to a model's objects ---------------------------
// Guest size 0x120 (AafHandler::Instantiate: operator new(0x120) or AafHandler::m_pMemoryManager->Malloc);
// layout from Instantiate, ~AafHandler, AttachAaf, Length, IsChunkReady, the complement-buffer methods and
// the hot functor AafCalcCommonFunctor::CalcAndSetSubFunctor<...> (port/decomp/anim/aaf_handler.c,
// controllers.c). Its base is Aska::TSmartPointer<false> (vptr + the reference count; ~AafHandler ends by
// storing that vtable), flattened here: the base's data ends at 0x0c and m_flags reuses its tail padding.
// vtable (_ZTVN4Aska10AafHandlerE): 0 D1, 1 D0 only.
// Per frame: SetValues(frame) -> CalcAndSetSubFunctor: picks the chunk for the frame (streamed
// animations), CheckCache marks the controllers whose key interval changed, then for each controller
// info calls the controller's vtable slot 10 (CalcValue) and 43 (SetValueToTarget).
class AafHandler {
public:
    // Constructors / destructors (bound as Ctor / Dtor: a C++ constructor can't be bound)
    void DtorBase();  // Aska::AafHandler::~AafHandler()
    void DtorDelete();  // Aska::AafHandler::~AafHandler()
    // Virtuals in vtable order (_ZTVN4Aska10AafHandlerE), as plain members: no C++ `virtual` (the guest's vtable is the field)
    // vtable slot 0: Aska::AafHandler::~AafHandler() (declared above)
    // vtable slot 1: Aska::AafHandler::~AafHandler() (declared above)
    // Methods (a static one: declare it static and bind it with NATIVE_FUNCTION(sym, wrap<&C::F>(), ...))
    static void Function_SearchKeyFrameData(void**, void*, s32*, u32, void*, u16, s32, s32, bool);  // Aska::AafHandler::Function_SearchKeyFrameData(void*&, Aska::FrameSortDataForSearchOld*&, int&, unsigned int, Aska::FrameSortDataForSearchOld*, unsigned short, int, int, bool)
    static void Function_RenewalAllControllerCache(float, u32*, u32*, u32, AafControllerInfo*, u32, void*, u32, bool);  // Aska::AafHandler::Function_RenewalAllControllerCache(float, unsigned int*, unsigned int*, unsigned int, Aska::AafControllerInfo*, unsigned int, Aska::FrameSortDataForSearchOld*, unsigned int, bool)
    // bool Aska::AafHandler::Function_UpdateKeyFrameData_All<0u>(unsigned int*, unsigned int&, unsigned int*, unsigned int&, Aska::AafControllerInfo*, unsigned int, unsigned int, Aska::FrameSortDataForSearchOld*, unsigned int, int, int, bool): an operator: name it by hand
    // bool Aska::AafHandler::Function_UpdateKeyFrameData_All<1u>(unsigned int*, unsigned int&, unsigned int*, unsigned int&, Aska::AafControllerInfo*, unsigned int, unsigned int, Aska::FrameSortDataForSearchOld*, unsigned int, int, int, bool): an operator: name it by hand
    // bool Aska::AafHandler::Function_UpdateKeyFrameData_All<2u>(unsigned int*, unsigned int&, unsigned int*, unsigned int&, Aska::AafControllerInfo*, unsigned int, unsigned int, Aska::FrameSortDataForSearchOld*, unsigned int, int, int, bool): an operator: name it by hand
    static void Function_GetChunkInfo(const AafHandler*, const AafHeader*, float*, u32*, u64*, void*);  // Aska::AafHandler::Function_GetChunkInfo(Aska::AafHandler const*, Aska::AafHeader const*, float&, unsigned int&, unsigned long&, Aska::AafFrameSortChunkInfo*&)
    static AafHandler* Instantiate();  // Aska::AafHandler::Instantiate()
    // Aska::AafHandler::operator new(unsigned long, std::nothrow_t const&): an operator: name it by hand
    void DeleteThis();  // Aska::AafHandler::DeleteThis()
    u64 DecodeData(void*);  // Aska::AafHandler::DecodeData(void*)
    void DeleteControllers();  // Aska::AafHandler::DeleteControllers()
    u64 AttachResource(void*);  // Aska::AafHandler::AttachResource(Aska::ResourceManager*)
    void* GetTargetName(void*) const;  // Aska::AafHandler::GetTargetName(Aska::AafTargetHeaderBase const*) const
    void ResolveConstraints(float);  // Aska::AafHandler::ResolveConstraints(float)
    void AddAutoControllerTask(void*, float*);  // Aska::AafHandler::AddAutoControllerTask(Aska::TaskManager*, float*)
    void RemoveAutoControllerTask();  // Aska::AafHandler::RemoveAutoControllerTask()
    void Clone(void*, AafHandler*, void*, void*, bool);  // Aska::AafHandler::Clone(Aska::AsfHandler*, Aska::AafHandler*, Aska::CollisionHandler*, Aska::AsfTargetNameList*, bool)
    void CreateControllers(void*, void*, void*, bool);  // Aska::AafHandler::CreateControllers(Aska::AsfHandler*, Aska::CollisionHandler*, Aska::AsfTargetNameList*, bool)
    void Copy(void*, AafHandler*, void*, void*, bool);  // Aska::AafHandler::Copy(Aska::AsfHandler*, Aska::AafHandler*, Aska::CollisionHandler*, Aska::AsfTargetNameList*, bool)
    u64 AttachConstantChunkData(u8*);  // Aska::AafHandler::AttachConstantChunkData(unsigned char*)
    u64 AttachChunkData(s32, u8*);  // Aska::AafHandler::AttachChunkData(int, unsigned char*)
    void PrecreateControllers(void*, void*, void*);  // Aska::AafHandler::PrecreateControllers(Aska::AsfHandler*, Aska::CollisionHandler*, Aska::AsfTargetNameList*)
    void AttachAaf(const void*, void*, void*, void*);  // Aska::AafHandler::AttachAaf(void const*, Aska::AsfHandler*, Aska::CollisionHandler*, Aska::AsfTargetNameList*)
    void DetachObject();  // Aska::AafHandler::DetachObject()
    static void CalcRuntimeMemorySize1(void*, const AafHeader*);  // Aska::AafHandler::CalcRuntimeMemorySize1(Aska::AFF::AskaFile const*, Aska::AafHeader const*)
    void GetTargetControllerObject(s32, s32, s32);  // Aska::AafHandler::GetTargetControllerObject(int, int, int)
    u32 CheckPlatformID(void*);  // Aska::AafHandler::CheckPlatformID(Aska::AafControllerHeader const*)
    u64 InitializeAllConstantCache(u16*);  // Aska::AafHandler::InitializeAllConstantCache(unsigned short*)
    u32 GetComplementBufferSize() const;  // Aska::AafHandler::GetComplementBufferSize() const
    bool AttachComplementBuffer(void*, u32);  // Aska::AafHandler::AttachComplementBuffer(void*, unsigned int)
    void DetachComplementBuffer();  // Aska::AafHandler::DetachComplementBuffer()
    bool IsAttachedComplementBuffer() const;  // Aska::AafHandler::IsAttachedComplementBuffer() const
    void HaltAnimation(IAnimatable*, bool);  // Aska::AafHandler::HaltAnimation(Aska::IAnimatable*, bool)
    void HaltAnimation(const char*, bool);  // Aska::AafHandler::HaltAnimation(char const*, bool)
    void HaltAnimation(IAnimatable*, bool, u32);  // Aska::AafHandler::HaltAnimation(Aska::IAnimatable*, bool, Aska::EnumAafControllerType)
    void GetControllerInterface(IAnimatable*, u32);  // Aska::AafHandler::GetControllerInterface(Aska::IAnimatable*, Aska::EnumAafDetailAttribute)
    void LocalGetControllerInterface(IAnimatable*, u32);  // Aska::AafHandler::LocalGetControllerInterface(Aska::IAnimatable*, Aska::EnumAafDetailAttribute)
    void GetControllerInterface(const char*, u32);  // Aska::AafHandler::GetControllerInterface(char const*, Aska::EnumAafDetailAttribute)
    void GetAllControllerInterface(AafController**, s32, IAnimatable*, u32, s32*);  // Aska::AafHandler::GetAllControllerInterface(Aska::IController**, int, Aska::IAnimatable*, Aska::EnumAafControllerType, int*)
    void GetControllerInterface(IAnimatable*, u32, s32);  // Aska::AafHandler::GetControllerInterface(Aska::IAnimatable*, Aska::EnumAafControllerType, int)
    void GetControllerInterface(const char*, u32, s32);  // Aska::AafHandler::GetControllerInterface(char const*, Aska::EnumAafControllerType, int)
    void DisableControllers(u32);  // Aska::AafHandler::DisableControllers(Aska::EnumAafControllerType)
    void DetachController(IAnimatable*);  // Aska::AafHandler::DetachController(Aska::IAnimatable*)
    void DetachControllers(u32);  // Aska::AafHandler::DetachControllers(Aska::EnumAafControllerType)
    void DetachAllControllers();  // Aska::AafHandler::DetachAllControllers()
    void AttachController(IAnimatable*, const char*);  // Aska::AafHandler::AttachController(Aska::IAnimatable*, char const*)
    u64 AttachController(const char*);  // Aska::AafHandler::AttachController(char const*)
    void MakeBiArray(float);  // Aska::AafHandler::MakeBiArray(float)
    void RenewalAllControllerCache(float);  // Aska::AafHandler::RenewalAllControllerCache(float)
    static void CalcRuntimeMemorySize0(u32*, u32*, u32*, const void*, AafHeader**);  // Aska::AafHandler::CalcRuntimeMemorySize0(unsigned int&, unsigned int&, unsigned int&, void const*, Aska::AafHeader*&)
    void SearchModifierTarget(const char*, s32*, void*);  // Aska::AafHandler::SearchModifierTarget(char const*, int*, Aska::AsfHandler*)
    u64 PrepareForComplement();  // Aska::AafHandler::PrepareForComplement()
    void CalcDifferenceOfValue(void*, u64, float, float);  // Aska::AafHandler::CalcDifferenceOfValue(void*, unsigned long, float, float)
    void CalcDifferenceOfValue(float*, AafControllerInfo*, float, float);  // Aska::AafHandler::CalcDifferenceOfValue(float*, Aska::AafControllerInfo*, float, float)
    void CalcDifferenceOfValue(MathVector*, AafControllerInfo*, float, float);  // Aska::AafHandler::CalcDifferenceOfValue(Aska::Vector*, Aska::AafControllerInfo*, float, float)
    void CalcDifferenceOfValue(s32*, AafControllerInfo*, float, float);  // Aska::AafHandler::CalcDifferenceOfValue(int*, Aska::AafControllerInfo*, float, float)
    void CalcDifferenceOfValue(MathQuaternion*, AafControllerInfo*, float, float);  // Aska::AafHandler::CalcDifferenceOfValue(Aska::Quaternion*, Aska::AafControllerInfo*, float, float)
    static const AafHeader* GetAafHeader(void*);  // Aska::AafHandler::GetAafHeader(Aska::AFF::AskaFile*)
    void SetValues(float);  // Aska::AafHandler::SetValues(float)
    void SetValues(float, s32);  // Aska::AafHandler::SetValues(float, int)
    void AddValues(float);  // Aska::AafHandler::AddValues(float)
    void BlendValues(float, float);  // Aska::AafHandler::BlendValues(float, float)
    void SetValuesHighSpeed(float);  // Aska::AafHandler::SetValuesHighSpeed(float)
    void SetValuesHighSpeed(float, s32);  // Aska::AafHandler::SetValuesHighSpeed(float, int)
    void SetOneValue(IAnimatable*, float);  // Aska::AafHandler::SetOneValue(Aska::IAnimatable*, float)
    void SetOneValue(IAnimatable*, float, s32);  // Aska::AafHandler::SetOneValue(Aska::IAnimatable*, float, int)
    void SetOneValue(AafController*, float);  // Aska::AafHandler::SetOneValue(Aska::IController*, float)
    void SetOneValue(AafController*, float, s32);  // Aska::AafHandler::SetOneValue(Aska::IController*, float, int)
    void SetAutoComplement(float, float, AafHandler*, float, void*);  // Aska::AafHandler::SetAutoComplement(float, float, Aska::AafHandler*, float, Aska::AsfHandler*)
    bool IsChunkReady(float) const;  // Aska::AafHandler::IsChunkReady(float) const
    void SearchTarget(const char*, void*);  // Aska::AafHandler::SearchTarget(char const*, Aska::AsfHandler*)
    void LocalGetControllerInfoByDetail(IAnimatable*, u32);  // Aska::AafHandler::LocalGetControllerInfoByDetail(Aska::IAnimatable*, Aska::EnumAafDetailAttribute)
    void LocalGetControllerInfoByIndexAndDetail(IAnimatable*, u64, u32);  // Aska::AafHandler::LocalGetControllerInfoByIndexAndDetail(Aska::IAnimatable*, unsigned long, Aska::EnumAafDetailAttribute)
    void LocalGetControllerInfoByIndex(IAnimatable*, u64);  // Aska::AafHandler::LocalGetControllerInfoByIndex(Aska::IAnimatable*, unsigned long)
    float Length() const;  // Aska::AafHandler::Length() const
    void DisappearHandler(bool);  // Aska::AafHandler::DisappearHandler(bool)
    void CalcAndSetDifferenceOfValueMain(AafControllerInfo*);  // Aska::AafHandler::CalcAndSetDifferenceOfValueMain(Aska::AafControllerInfo*)
    static s32 CalcRuntimeMemorySize(const void*);  // Aska::AafHandler::CalcRuntimeMemorySize(void const*)
    // Aska::AafHandler::operator new(unsigned long, unsigned long, bool): an operator: name it by hand
    // Aska::AafHandler::operator new[](unsigned long, unsigned long, bool): an operator: name it by hand
    // Aska::AafHandler::operator new[](unsigned long, std::nothrow_t const&): an operator: name it by hand
    u32 GetFigureRate(u8, u8) const;  // Aska::AafHandler::GetFigureRate(unsigned char, unsigned char) const
    void LocalGetControllerInfoAndIndex(s32*, IAnimatable*, u32);  // Aska::AafHandler::LocalGetControllerInfoAndIndex(int*, Aska::IAnimatable*, Aska::EnumAafDetailAttribute)
    void LocalGetControllerInfoByType(IAnimatable*, u32, s32);  // Aska::AafHandler::LocalGetControllerInfoByType(Aska::IAnimatable*, Aska::EnumAafControllerType, int)
    void LocalGetAllControllerInfoByType(AafControllerInfo**, s32, IAnimatable*, u32, s32*);  // Aska::AafHandler::LocalGetAllControllerInfoByType(Aska::AafControllerInfo**, int, Aska::IAnimatable*, Aska::EnumAafControllerType, int*)
    void GetControllerInfoByDetail(IAnimatable*, u32);  // Aska::AafHandler::GetControllerInfoByDetail(Aska::IAnimatable*, Aska::EnumAafDetailAttribute)
    void GetControllerInfoByIndex(IAnimatable*, u64);  // Aska::AafHandler::GetControllerInfoByIndex(Aska::IAnimatable*, unsigned long)
    void GetControllerInfoByIndexAndDetail(IAnimatable*, u64, u32);  // Aska::AafHandler::GetControllerInfoByIndexAndDetail(Aska::IAnimatable*, unsigned long, Aska::EnumAafDetailAttribute)
    void GetControllerInfoAndIndex(s32*, IAnimatable*, u32);  // Aska::AafHandler::GetControllerInfoAndIndex(int*, Aska::IAnimatable*, Aska::EnumAafDetailAttribute)
    void GetControllerInfoByType(IAnimatable*, u32, s32);  // Aska::AafHandler::GetControllerInfoByType(Aska::IAnimatable*, Aska::EnumAafControllerType, int)
    void GetAllControllerInfoByType(AafControllerInfo**, s32, IAnimatable*, u32, s32*);  // Aska::AafHandler::GetAllControllerInfoByType(Aska::AafControllerInfo**, int, Aska::IAnimatable*, Aska::EnumAafControllerType, int*)
    void GetChunkSize(s32, u64*, u64*, u64*, u64*);  // Aska::AafHandler::GetChunkSize(int, unsigned long*, unsigned long*, unsigned long*, unsigned long*)
    void GetChunkSize(void*, const AafHeader*, s32, u64*, u64*, u64*, u64*);  // Aska::AafHandler::GetChunkSize(Aska::AFF::AskaFile const*, Aska::AafHeader const*, int, unsigned long*, unsigned long*, unsigned long*, unsigned long*)
    void GetConstantChunkSize(u64*, u64*, u64*, u64*);  // Aska::AafHandler::GetConstantChunkSize(unsigned long*, unsigned long*, unsigned long*, unsigned long*)
    void GetConstantChunkSize(void*, const AafHeader*, u64*, u64*, u64*, u64*);  // Aska::AafHandler::GetConstantChunkSize(Aska::AFF::AskaFile const*, Aska::AafHeader const*, unsigned long*, unsigned long*, unsigned long*, unsigned long*)
    void DetachConstantChunkData();  // Aska::AafHandler::DetachConstantChunkData()
    void DetachChunkData(s32);  // Aska::AafHandler::DetachChunkData(int)
    bool IsChunkReadyByIndex(s32) const;  // Aska::AafHandler::IsChunkReadyByIndex(int) const
    // void Aska::AafHandler::RenewalOneControllerCache<1>(float, int): an operator: name it by hand
    static void Function_RenewalOneControllerCache(float, u16, s32, AafControllerInfo*, void*, void*, void*, u32, bool);  // Aska::AafHandler::Function_RenewalOneControllerCache(float, unsigned short, int, Aska::AafControllerInfo*, Aska::AAF_RENEWAL_ONE_CP*, Aska::AafKeyframeHeader*, Aska::FrameSortDataForSearchOld*, unsigned int, bool)
    void SetController(AafControllerInfo*, u8**, u8**);  // Aska::AafHandler::SetController(Aska::AafControllerInfo*, unsigned char**, unsigned char**)

    const void* vtable;                 // 0x000: _ZTVN4Aska10AafHandlerE + 0x10
    s32 m_refCount;                     // 0x008: TSmartPointer<false>'s count (CAnimationElement::CreateAafHandler increments it)
    u32 m_flags;                        // 0x00c: bit 1 controllers created (SetValues runs only then), 2 m_data not owned,
                                        //        3 an AAF attached, 4 objects attached, 5 values set this frame (the blend
                                        //        notify sets it), 6 streamed (chunks), 8 (with 5: the post pass); 0x20 at Instantiate
    u8* m_data;                         // 0x010: the animation data (delete[]d unless bit 2)
    void* m_targetNames;                // 0x018: Aska::AsfTargetNameList*
    const void* m_file;                 // 0x020: the AAF file ("AAF ")
    const AafHeader* m_header;          // 0x028
    u8 unk_030[8];                      // 0x030
    u32 m_controllerCount;              // 0x038: m_countA + m_countB + m_countC
    u32 m_countA;                       // 0x03c: the normal controllers (m_infosA; the cached ones)
    u32 m_countB;                       // 0x040: m_infosB (the post pass, flags 0x120)
    u32 m_countC;                       // 0x044: m_infosC (the independent ones, vtable slot 57)
    u32 m_param48;                      // 0x048: AafHeader::m_param0c; the functor's chunk record word
    u8 unk_04c[4];                      // 0x04c
    u8* m_buffer;                       // 0x050: one new[] block: targets, infos, the cache arrays, the chunk table
    u8 unk_058[0x10];                   // 0x058
    void* m_complementBuffer;           // 0x068: AttachComplementBuffer
    u8 m_complement;                    // 0x070: complement (blending from another animation) prepared
    u8 m_complementShared;              // 0x071: no buffer of its own (GetComplementBufferSize 0)
    u8 m_complementDirty;               // 0x072: AttachComplementBuffer clears it
    u8 unk_073[5];                      // 0x073
    AafTarget* m_targets;               // 0x078: m_targetCount entries
    AafControllerInfo* m_infos;         // 0x080: all controllers (A, then B, then C)
    AafControllerInfo* m_infosA;        // 0x088: null when m_countA is 0
    AafControllerInfo* m_infosB;        // 0x090
    AafControllerInfo* m_infosC;        // 0x098
    render::Task* m_autoTask;           // 0x0a0: AddAutoControllerTask's Aska::AafAutoRunTask (0x38 bytes)
    u32 m_cacheWords;                   // 0x0a8: (m_countA + 31) / 32
    u8 unk_0ac[4];                      // 0x0ac
    u32* m_cacheBits0;                  // 0x0b0: m_cacheWords words (CheckCache memsets them)
    u32* m_cacheBits1;                  // 0x0b8
    AafControllerInfo** m_activeInfos;  // 0x0c0: the infos to evaluate this frame (CheckCache fills it)
    u16* m_cacheIndex0;                 // 0x0c8: m_countA entries
    u16* m_cacheIndex1;                 // 0x0d0
    u8 unk_0d8[8];                      // 0x0d8
    const u8* m_currentChunk;           // 0x0e0: the chunk the last SetValues used
    float m_complementStart;            // 0x0e8: the complement's frame range [start, end)
    float m_complementEnd;              // 0x0ec
    float m_complementLength;           // 0x0f0
    u16 m_targetCount;                  // 0x0f4
    u8 unk_0f6;                         // 0x0f6
    u8 m_complementActive;              // 0x0f7: complement in progress (CalcValueComplement on every controller)
    u8 m_complementOnce;                // 0x0f8: clear m_complementActive after the range
    u8 unk_0f9;                         // 0x0f9
    u8 m_unk0fa;                        // 0x0fa: 1 at Instantiate
    u8 unk_0fb[0x1d];                   // 0x0fb
    u8** m_chunkTable;                  // 0x118: AafHeader::m_chunkCount chunk pointers (null: not streamed)
};
static_assert(offsetof(AafHandler, m_refCount) == 0x008);
static_assert(offsetof(AafHandler, m_flags) == 0x00c);
static_assert(offsetof(AafHandler, m_data) == 0x010);
static_assert(offsetof(AafHandler, m_header) == 0x028);
static_assert(offsetof(AafHandler, m_controllerCount) == 0x038);
static_assert(offsetof(AafHandler, m_countC) == 0x044);
static_assert(offsetof(AafHandler, m_buffer) == 0x050);
static_assert(offsetof(AafHandler, m_complementBuffer) == 0x068);
static_assert(offsetof(AafHandler, m_complement) == 0x070);
static_assert(offsetof(AafHandler, m_targets) == 0x078);
static_assert(offsetof(AafHandler, m_infos) == 0x080);
static_assert(offsetof(AafHandler, m_infosC) == 0x098);
static_assert(offsetof(AafHandler, m_autoTask) == 0x0a0);
static_assert(offsetof(AafHandler, m_cacheWords) == 0x0a8);
static_assert(offsetof(AafHandler, m_activeInfos) == 0x0c0);
static_assert(offsetof(AafHandler, m_currentChunk) == 0x0e0);
static_assert(offsetof(AafHandler, m_complementStart) == 0x0e8);
static_assert(offsetof(AafHandler, m_targetCount) == 0x0f4);
static_assert(offsetof(AafHandler, m_complementActive) == 0x0f7);
static_assert(offsetof(AafHandler, m_unk0fa) == 0x0fa);
static_assert(offsetof(AafHandler, m_chunkTable) == 0x118);
static_assert(sizeof(AafHandler) == 0x120);

// ---- Aska::AafController: the base of the TAaf*Controller templates (an IController) ------------------
// No vtable of its own (abstract); its slots as the functors call them (slot k at vptr + 8k): 12 CalcValue
// (void* out, float frame) (+0x60), 40 CalcValueComplement (+0x140), 41 CalcValueConstant (+0x148), 42 / 43
// the out-of-range calcs CalcValueSub calls (+0x150 / +0x158), 45 SetValueToTarget(void* value,
// AafSetValueArg*) (+0x168), 57 SwapControlPoint (+0x1c8, after a key change), 59 IsIndependentController
// (+0x1d8). The fields are TAafNormalController's (port/decomp/anim/controllers.c: CalcValueSub
// <Quaternion_Linear>); GetControllerSize() of the base is
// 0x10, so the fields from 0x10 on belong to TAafNormalController<...>.
class AafController {
public:
    // Methods (a static one: declare it static and bind it with NATIVE_FUNCTION(sym, wrap<&C::F>(), ...))
    u64 Clone(AafController*, bool);  // Aska::AafController::Clone(Aska::IController*, bool)
    u64 Copy(AafController*, bool);  // Aska::AafController::Copy(Aska::IController*, bool)
    void CalcValue(void*, float);  // Aska::AafController::CalcValue(void*, float)
    u64 GetAafKeyframeHeader() const;  // Aska::AafController::GetAafKeyframeHeader() const
    u64 GetKeyframe(float*, s32) const;  // Aska::AafController::GetKeyframe(float*, int) const
    u64 GetControlPoint(void*, s32) const;  // Aska::AafController::GetControlPoint(void*, int) const
    u64 GetIAnimatable();  // Aska::AafController::GetIAnimatable()
    void CallDestructor();  // Aska::AafController::CallDestructor()
    void DetachObject();  // Aska::AafController::DetachObject()
    void SetControlBuffer(u8**, s32);  // Aska::AafController::SetControlBuffer(unsigned char**, int)
    void SetComplementBuffer(u8**);  // Aska::AafController::SetComplementBuffer(unsigned char**)
    void SetControlPoint(s32, float, void*);  // Aska::AafController::SetControlPoint(int, float, void*)
    void ForceSetControlPoint(s32, float, void*);  // Aska::AafController::ForceSetControlPoint(int, float, void*)
    void SwapControlPoint();  // Aska::AafController::SwapControlPoint()
    void SetLoopCount(s32);  // Aska::AafController::SetLoopCount(int)
    void SetLoopCount(float);  // Aska::AafController::SetLoopCount(float)
    void SetFigureRate(float);  // Aska::AafController::SetFigureRate(float)
    bool IsNecessaryToRenewalCache(float, float, float);  // Aska::AafController::IsNecessaryToRenewalCache(float, float, float)
    void GetDifferenceOfValue(void*);  // Aska::AafController::GetDifferenceOfValue(void*)
    void SetDifferenceOfValue(void*);  // Aska::AafController::SetDifferenceOfValue(void*)
    void AddDifferenceOfValue(void*, float);  // Aska::AafController::AddDifferenceOfValue(void*, float)
    void GetValue(void*, void*);  // Aska::AafController::GetValue(void*, void*)
    void GetComplementValue(s32, void*);  // Aska::AafController::GetComplementValue(int, void*)
    void GetComplementTangent(s32, void*, void*);  // Aska::AafController::GetComplementTangent(int, void*, void*)
    void CalcValueComplement(void*, float, float, float);  // Aska::AafController::CalcValueComplement(void*, float, float, float)
    void CalcValueConstant(void*, s32);  // Aska::AafController::CalcValueConstant(void*, int)
    void CalcValueByLinearAtPreOutOfRange(void*, float);  // Aska::AafController::CalcValueByLinearAtPreOutOfRange(void*, float)
    void CalcValueByLinearAtPostOutOfRange(void*, float);  // Aska::AafController::CalcValueByLinearAtPostOutOfRange(void*, float)
    void SetValueOfDirectAddr(void*, void*);  // Aska::AafController::SetValueOfDirectAddr(void*, void*)
    void AddValueOfDirectAddr(void*, void*);  // Aska::AafController::AddValueOfDirectAddr(void*, void*)
    void AddValueToTarget(void*, void*);  // Aska::AafController::AddValueToTarget(void*, Aska::AafSetValueArg*)
    void BlendValueOfDirectAddr(void*, void*, float);  // Aska::AafController::BlendValueOfDirectAddr(void*, void*, float)
    void BlendValueToTarget(void*, void*);  // Aska::AafController::BlendValueToTarget(void*, Aska::AafSetValueArg*)
    u64 GetInputAddrForValue(void*);  // Aska::AafController::GetInputAddrForValue(Aska::AafSetValueArg*)
    u64 GetOutputAddrForValue(void*);  // Aska::AafController::GetOutputAddrForValue(Aska::AafSetValueArg*)
    u64 GetInputAddrForValue(IAnimatable*);  // Aska::AafController::GetInputAddrForValue(Aska::IAnimatable*)
    u64 GetOutputAddrForValue(IAnimatable*);  // Aska::AafController::GetOutputAddrForValue(Aska::IAnimatable*)
    void UpdateTargetForValue(void*);  // Aska::AafController::UpdateTargetForValue(Aska::AafSetValueArg*)
    u64 GetControllerSize();  // Aska::AafController::GetControllerSize()
    void SetConstantComplementPoint();  // Aska::AafController::SetConstantComplementPoint()
    void UpdateCurrentRange();  // Aska::AafController::UpdateCurrentRange()
    void GetCurrentRange();  // Aska::AafController::GetCurrentRange()
    void GetKeyframe(s32) const;  // Aska::AafController::GetKeyframe(int) const
    void AttachObject(void*, void*, void*);  // Aska::AafController::AttachObject(Aska::AsfHandler*, Aska::AafSetValueArg*, Aska::AafControllerHeader const*)
    bool IsIndependentController();  // Aska::AafController::IsIndependentController()
    void SetValueToTarget(void*, void*);  // Aska::AafController::SetValueToTarget(void*, Aska::AafSetValueArg*)
    // fields at the guest's offsets

    const void* vtable;           // 0x00
    s32 m_loopState;              // 0x08: the loop count / -1 (CalcValueSub's out-of-range handling)
    u8 unk_0c;                    // 0x0c
    u8 m_keySlot;                 // 0x0d: which of the two cached keys is the current one (flips)
    u8 unk_0e[2];                 // 0x0e
    // TAafNormalController<AafType<...>> from here:
    float m_keyTime[2];           // 0x10: the cached keys' frames (indexed by m_keySlot)
    u8 unk_18[8];                 // 0x18
    const void* m_keyValue[2];    // 0x20: the cached keys' control points
    u8 unk_30[8];                 // 0x30
    const u8* m_header;           // 0x38: the controller header (its key header at m_header + *(u16*)(m_header + 6))
    u32 m_keyIndex;               // 0x40: the current key interval
    u8 unk_44[4];                 // 0x44
};
static_assert(offsetof(AafController, m_loopState) == 0x08);
static_assert(offsetof(AafController, m_keySlot) == 0x0d);
static_assert(offsetof(AafController, m_keyTime) == 0x10);
static_assert(offsetof(AafController, m_keyValue) == 0x20);
static_assert(offsetof(AafController, m_header) == 0x38);
static_assert(offsetof(AafController, m_keyIndex) == 0x40);
static_assert(sizeof(AafController) == 0x48);

// ---- Aska::AafBlendManager: blends several AafHandlers onto one model ------------------------------
// Guest size 0x48 (CAnimationBlendContainer::PlayAnimation: operator new(0x48), then the vtables of the
// manager and its _CalcNotify, then Initialize); layout from Initialize, Create, Open, Close, AddAaf,
// Get/SetPlayFrame, Get/SetWeight, Get/SetNotify, NormalizeWeights, _CalcNotify::Handler
// (port/decomp/anim/aaf_handler.c). vtable (_ZTVN4Aska15AafBlendManagerE): 0 CalcValues, 1 CopyMatrices(int),
// 2 SetValues, 3 D1, 4 D0.
struct AafBlendInfo {           // Aska::IAafBlendManager::_AafInfo, 0x30 each (m_infos)
    float m_playFrame;          // 0x00: GetPlayFrame / SetPlayFrame
    float m_normalizedWeight;   // 0x04: NormalizeWeights: m_weight / the sum (when the sum is over a tiny epsilon)
    float m_weight;             // 0x08: GetWeight / SetWeight
    u8 unk_0c[4];               // 0x0c
    AafHandler* m_handler;      // 0x10: AddAaf
    void* m_notify;             // 0x18: Aska::INotify* (Get/SetNotify); when set, _CalcNotify calls it instead
    u8 unk_20[0x10];            // 0x20
};
static_assert(offsetof(AafBlendInfo, m_weight) == 0x08);
static_assert(offsetof(AafBlendInfo, m_handler) == 0x10);
static_assert(offsetof(AafBlendInfo, m_notify) == 0x18);
static_assert(sizeof(AafBlendInfo) == 0x30);

class AafBlendManager;
struct AafBlendCalcNotify {     // Aska::AafBlendManager::_CalcNotify (an INotify run per info by the message dispatcher)
    const void* vtable;         // 0x00: _ZTVN4Aska15AafBlendManager11_CalcNotifyE + 0x10
    AafBlendManager* m_owner;   // 0x08
};
static_assert(sizeof(AafBlendCalcNotify) == 0x10);

class AafBlendManager {
public:
    // Constructors / destructors (bound as Ctor / Dtor: a C++ constructor can't be bound)
    void DtorBase();  // Aska::AafBlendManager::~AafBlendManager()
    void DtorDelete();  // Aska::AafBlendManager::~AafBlendManager()
    // Virtuals in vtable order (_ZTVN4Aska15AafBlendManagerE), as plain members: no C++ `virtual` (the guest's vtable is the field)
    void CalcValues();  // vtable slot 0: Aska::AafBlendManager::CalcValues()
    void CopyMatrices(s32);  // vtable slot 1: Aska::AafBlendManager::CopyMatrices(int)
    bool SetValues();  // vtable slot 2: Aska::AafBlendManager::SetValues()
    // vtable slot 3: Aska::AafBlendManager::~AafBlendManager() (declared above)
    // vtable slot 4: Aska::AafBlendManager::~AafBlendManager() (declared above)
    // Methods (a static one: declare it static and bind it with NATIVE_FUNCTION(sym, wrap<&C::F>(), ...))
    void Create(s32);  // Aska::AafBlendManager::Create(int)
    bool Open(s32);  // Aska::AafBlendManager::Open(int)
    bool Close(u8);  // Aska::AafBlendManager::Close(unsigned char)
    u64 AllocateControllerBuffer();  // Aska::AafBlendManager::AllocateControllerBuffer()
    void FreeControllerBuffer();  // Aska::AafBlendManager::FreeControllerBuffer()
    bool AddAaf(AafHandler*);  // Aska::AafBlendManager::AddAaf(Aska::AafHandler*)
    float GetPlayFrame(s32) const;  // Aska::AafBlendManager::GetPlayFrame(int) const
    float GetPlayFrame(const AafHandler*) const;  // Aska::AafBlendManager::GetPlayFrame(Aska::AafHandler const*) const
    bool SetPlayFrame(s32, float);  // Aska::AafBlendManager::SetPlayFrame(int, float)
    void SetPlayFrame(const AafHandler*, float);  // Aska::AafBlendManager::SetPlayFrame(Aska::AafHandler const*, float)
    float GetWeight(s32) const;  // Aska::AafBlendManager::GetWeight(int) const
    float GetWeight(const AafHandler*) const;  // Aska::AafBlendManager::GetWeight(Aska::AafHandler const*) const
    bool SetWeight(s32, float);  // Aska::AafBlendManager::SetWeight(int, float)
    void SetWeight(const AafHandler*, float);  // Aska::AafBlendManager::SetWeight(Aska::AafHandler const*, float)
    void* GetNotify(s32);  // Aska::AafBlendManager::GetNotify(int)
    void* GetNotify(const AafHandler*);  // Aska::AafBlendManager::GetNotify(Aska::AafHandler const*)
    void SetNotify(s32, void*);  // Aska::AafBlendManager::SetNotify(int, Aska::INotify*)
    void SetNotify(const AafHandler*, void*);  // Aska::AafBlendManager::SetNotify(Aska::AafHandler const*, Aska::INotify*)
    bool NormalizeWeights();  // Aska::AafBlendManager::NormalizeWeights()
    static void StaticCalcValues_NoFiber(AafBlendManager*, s32);  // Aska::AafBlendManager::StaticCalcValues_NoFiber(Aska::AafBlendManager*, int)
    void RestoreSnapShot(void*, void*);  // Aska::AafBlendManager::RestoreSnapShot(Aska::SceneSnapShot*, Aska::IAafBlendManager::_AafInfo&)
    bool SetValues(void*);  // Aska::AafBlendManager::SetValues(Aska::SceneSnapShot**)
    void Initialize();  // Aska::AafBlendManager::Initialize()

    const void* vtable;               // 0x00: _ZTVN4Aska15AafBlendManagerE + 0x10
    u8 m_created;                     // 0x08: Create succeeded (every accessor checks it)
    u8 m_closeMode;                   // 0x09: Close's argument (2 at Initialize)
    u8 unk_0a[2];                     // 0x0a
    float m_weightSum;                // 0x0c: SetValues zeroes it; _CalcNotify adds each blended weight
    AafBlendCalcNotify m_calcNotify;  // 0x10
    s32 m_firstUsed;                  // 0x20: Close: the first info with a handler
    s32 m_capacity;                   // 0x24: Create(n)
    s32 m_count;                      // 0x28: Open(n)
    s32 m_prevCount;                  // 0x2c
    s32 m_added;                      // 0x30: AddAaf's next slot (-1 when closed)
    u8 unk_34[4];                     // 0x34
    AafBlendInfo* m_infos;            // 0x38: m_capacity entries (operator new[](n * 0x30, 16))
    u32 unk_40;                       // 0x40: 0 at Initialize and on a single-handler Close
    u8 unk_44[4];                     // 0x44
};
static_assert(offsetof(AafBlendManager, m_created) == 0x08);
static_assert(offsetof(AafBlendManager, m_weightSum) == 0x0c);
static_assert(offsetof(AafBlendManager, m_calcNotify) == 0x10);
static_assert(offsetof(AafBlendManager, m_capacity) == 0x24);
static_assert(offsetof(AafBlendManager, m_count) == 0x28);
static_assert(offsetof(AafBlendManager, m_added) == 0x30);
static_assert(offsetof(AafBlendManager, m_infos) == 0x38);
static_assert(sizeof(AafBlendManager) == 0x48);

// ---- Framework: the model-side animation (CAnimationModel -> CAnimationBlendContainer -> elements) -----

// Framework::CBlendRatePlayer: the blend-rate curves of a container's elements. Guest size 0x18
// (CAnimationBlendContainer::Initialize: operator new(0x18)); pieces of 0x1c bytes (Initialize).
struct BlendRatePiece {        // Framework::CBlendRatePlayer::CPiece
    u32 m_used;                // 0x00
    u32 m_handle;              // 0x04: NumPlayHandle counts the used pieces with a handle
    u8 unk_08[0x14];           // 0x08: the rate curve (CPiece::Rate)
};
static_assert(sizeof(BlendRatePiece) == 0x1c);

class CBlendRatePlayer {
public:
    // Constructors / destructors (bound as Ctor / Dtor: a C++ constructor can't be bound)
    void Ctor();  // Framework::CBlendRatePlayer::CBlendRatePlayer()
    void Dtor();  // Framework::CBlendRatePlayer::~CBlendRatePlayer()
    void DtorDelete();  // Framework::CBlendRatePlayer::~CBlendRatePlayer()
    // Virtuals in vtable order (_ZTVN9Framework16CBlendRatePlayerE), as plain members: no C++ `virtual` (the guest's vtable is the field)
    // vtable slot 0: Framework::CBlendRatePlayer::~CBlendRatePlayer() (declared above)
    // vtable slot 1: Framework::CBlendRatePlayer::~CBlendRatePlayer() (declared above)
    // Methods (a static one: declare it static and bind it with NATIVE_FUNCTION(sym, wrap<&C::F>(), ...))
    void Release();  // Framework::CBlendRatePlayer::Release()
    void Initialize(u32);  // Framework::CBlendRatePlayer::Initialize(unsigned int)
    void Progress(float);  // Framework::CBlendRatePlayer::Progress(float)
    u64 Add(float);  // Framework::CBlendRatePlayer::Add(float)
    u32 MakeBlank();  // Framework::CBlendRatePlayer::MakeBlank()
    void Remove(u32);  // Framework::CBlendRatePlayer::Remove(unsigned int)
    void Defrag();  // Framework::CBlendRatePlayer::Defrag()
    BlendRatePiece* crPiece(u32) const;  // Framework::CBlendRatePlayer::crPiece(unsigned int) const
    BlendRatePiece* rPiece(u32) const;  // Framework::CBlendRatePlayer::rPiece(unsigned int) const
    s32 NumPlayHandle() const;  // Framework::CBlendRatePlayer::NumPlayHandle() const
    void SetTerminatedForIndependentCalcBlendRate();  // Framework::CBlendRatePlayer::SetTerminatedForIndependentCalcBlendRate()

    const void* vtable;        // 0x00: _ZTVN9Framework16CBlendRatePlayerE + 0x10
    u32 m_count;               // 0x08: Initialize(n)
    u8 unk_0c[4];              // 0x0c
    BlendRatePiece* m_pieces;  // 0x10
};
static_assert(offsetof(CBlendRatePlayer, m_count) == 0x08);
static_assert(offsetof(CBlendRatePlayer, m_pieces) == 0x10);
static_assert(sizeof(CBlendRatePlayer) == 0x18);

// Framework::CAnimationTimeElement: frame, loop and speed of one animation (CAnimationElement's base).
// Size 0x28 (CAnimationElement's own fields start at 0x28); layout from Initialize, Reset, SetMaxLoopCount,
// SetPresentFrame, CheckLoopFrame. vtable: 0 Reset, 1 Progress(float), 2 SetStartFrame, 3 SetEndFrame.
class CAnimationTimeElement {
public:
    // Virtuals in vtable order (_ZTVN9Framework21CAnimationTimeElementE), as plain members: no C++ `virtual` (the guest's vtable is the field)
    void Reset();  // vtable slot 0: Framework::CAnimationTimeElement::Reset()
    void Progress(float);  // vtable slot 1: Framework::CAnimationTimeElement::Progress(float)
    void SetStartFrame(float);  // vtable slot 2: Framework::CAnimationTimeElement::SetStartFrame(float)
    void SetEndFrame(float);  // vtable slot 3: Framework::CAnimationTimeElement::SetEndFrame(float)
    // Methods (a static one: declare it static and bind it with NATIVE_FUNCTION(sym, wrap<&C::F>(), ...))
    void Initialize();  // Framework::CAnimationTimeElement::Initialize()
    void SetMaxLoopCount(u32);  // Framework::CAnimationTimeElement::SetMaxLoopCount(unsigned int)
    void SetPresentFrame(float);  // Framework::CAnimationTimeElement::SetPresentFrame(float)
    void Start();  // Framework::CAnimationTimeElement::Start()
    void OrFlag(u32);  // Framework::CAnimationTimeElement::OrFlag(unsigned int)
    void CheckLoopFrame(float, float*, float*) const;  // Framework::CAnimationTimeElement::CheckLoopFrame(float, float&, float&) const
    void TerminateProcess(u32);  // Framework::CAnimationTimeElement::TerminateProcess(unsigned int)
    void AndFlag(u32);  // Framework::CAnimationTimeElement::AndFlag(unsigned int)
    void ClearLoopedFlag();  // Framework::CAnimationTimeElement::ClearLoopedFlag()
    void ClearAllFlag();  // Framework::CAnimationTimeElement::ClearAllFlag()

    const void* vtable;        // 0x00
    u8 m_initialized;          // 0x08: Initialize sets it
    u8 unk_09[3];              // 0x09
    u32 m_flag;                // 0x0c: the loop / end flags (CAnimationBlendContainer::Flag returns the current element's)
    float m_presentFrame;      // 0x10: SetPresentFrame (CAnimationBlendContainer::PresentFrame returns it)
    float m_startFrame;        // 0x14: slot 2 (most likely)
    float m_endFrame;          // 0x18: slot 3 (most likely)
    u32 m_loopCount;           // 0x1c: Reset zeroes it
    u32 m_maxLoopCount;        // 0x20: SetMaxLoopCount
    float m_speed;             // 0x24: 1.0 at Reset
};
static_assert(offsetof(CAnimationTimeElement, m_flag) == 0x0c);
static_assert(offsetof(CAnimationTimeElement, m_presentFrame) == 0x10);
static_assert(offsetof(CAnimationTimeElement, m_loopCount) == 0x1c);
static_assert(offsetof(CAnimationTimeElement, m_maxLoopCount) == 0x20);
static_assert(offsetof(CAnimationTimeElement, m_speed) == 0x24);
static_assert(sizeof(CAnimationTimeElement) == 0x28);

// Framework::CAnimationElement: one animation of a blend container (its AafHandler). Guest size 0x68
// (CAnimationBlendContainer::Initialize: new[](n * 0x68 + 8), each constructed); layout from the
// constructor, CreateAafHandler, CAnimationBlendContainer::PlayAnimation / rElement / OrAllFlag.
// vtable (_ZTVN9Framework17CAnimationElementE): 0 Reset, 1 Progress, 2 SetStartFrame, 3 SetEndFrame, 4 D1, 5 D0.
class CAnimationElement {
public:
    // Constructors / destructors (bound as Ctor / Dtor: a C++ constructor can't be bound)
    void CtorBase();  // Framework::CAnimationElement::CAnimationElement()
    void Dtor();  // Framework::CAnimationElement::~CAnimationElement()
    void DtorDelete();  // Framework::CAnimationElement::~CAnimationElement()
    // Virtuals in vtable order (_ZTVN9Framework17CAnimationElementE), as plain members: no C++ `virtual` (the guest's vtable is the field)
    void Reset();  // vtable slot 0: Framework::CAnimationElement::Reset()
    void Progress(float);  // vtable slot 1: Framework::CAnimationElement::Progress(float)
    void SetStartFrame(float);  // vtable slot 2: Framework::CAnimationElement::SetStartFrame(float)
    void SetEndFrame(float);  // vtable slot 3: Framework::CAnimationElement::SetEndFrame(float)
    // vtable slot 4: Framework::CAnimationElement::~CAnimationElement() (declared above)
    // vtable slot 5: Framework::CAnimationElement::~CAnimationElement() (declared above)
    // Methods (a static one: declare it static and bind it with NATIVE_FUNCTION(sym, wrap<&C::F>(), ...))
    void Release();  // Framework::CAnimationElement::Release()
    void Initialize(void*, const void*, s32, bool);  // Framework::CAnimationElement::Initialize(Aska::AsfHandler&, void const*, int, bool)
    void AfterInitialize();  // Framework::CAnimationElement::AfterInitialize()
    void CreateAafHandler();  // Framework::CAnimationElement::CreateAafHandler()
    void ReplaceAafAndAet(const void*, const void*);  // Framework::CAnimationElement::ReplaceAafAndAet(void const*, void const*)
    void DeleteAafHandler();  // Framework::CAnimationElement::DeleteAafHandler()
    void AttachAet(const void*);  // Framework::CAnimationElement::AttachAet(void const*)
    void PresentBlendRate(float);  // Framework::CAnimationElement::PresentBlendRate(float)
    void DirectionBlendRadian(float);  // Framework::CAnimationElement::DirectionBlendRadian(float)
    void Start(u32);  // Framework::CAnimationElement::Start(unsigned int)
    float GetAnimationLength() const;  // Framework::CAnimationElement::GetAnimationLength() const
    void DirectSetValues(void*);  // Framework::CAnimationElement::DirectSetValues(Aska::FiberTask*)
    void OverwriteAetValueX(u32, float);  // Framework::CAnimationElement::OverwriteAetValueX(unsigned int, float)
    void OverwriteAetValueY(u32, float);  // Framework::CAnimationElement::OverwriteAetValueY(unsigned int, float)
    void OverwriteAetValueZ(u32, float);  // Framework::CAnimationElement::OverwriteAetValueZ(unsigned int, float)
    void SetDirectionBlend(s32, float, float);  // Framework::CAnimationElement::SetDirectionBlend(int, float, float)
    u32 DirectionBlendParentElementId() const;  // Framework::CAnimationElement::DirectionBlendParentElementId() const
    float DirectionBlend_RadianCenter() const;  // Framework::CAnimationElement::DirectionBlend_RadianCenter() const
    float DirectionBlend_RadianRange() const;  // Framework::CAnimationElement::DirectionBlend_RadianRange() const
    float DirectionBlendRadian() const;  // Framework::CAnimationElement::DirectionBlendRadian() const
    void DirectionBlendRate(float);  // Framework::CAnimationElement::DirectionBlendRate(float)
    float DirectionBlendRate() const;  // Framework::CAnimationElement::DirectionBlendRate() const

    CAnimationTimeElement base;  // 0x00
    s32 m_animId;                // 0x28: the animation id (-1: empty slot; rElement searches it)
    u8 unk_2c[4];                // 0x2c
    const void* m_aafData;       // 0x30: the AAF (CreateAafHandler attaches it)
    AafHandler* m_aafHandler;    // 0x38: CreateAafHandler (AafHandler::Instantiate)
    void* m_asfHandler;          // 0x40: Aska::AsfHandler* (the model's)
    void* unk_48;                // 0x48: 0 at construction (the AET, most likely)
    u32 m_blendPiece;            // 0x50: the CBlendRatePlayer piece (OrAllFlag: 0 = none)
    float m_blendRate;           // 0x54: the blend rate PlayAnimation applies (> 0: blended)
    u8 unk_58[4];                // 0x58
    u8 unk_5c[4];                // 0x5c: 0 at construction
    u8 m_additive;               // 0x60: PlayAnimation: AddValues instead of BlendValues
    u8 m_overwrite;              // 0x61
    u8 unk_62[2];                // 0x62
    u8 unk_64;                   // 0x64: 0 at construction
    u8 unk_65[3];                // 0x65
};
static_assert(offsetof(CAnimationElement, m_animId) == 0x28);
static_assert(offsetof(CAnimationElement, m_aafData) == 0x30);
static_assert(offsetof(CAnimationElement, m_aafHandler) == 0x38);
static_assert(offsetof(CAnimationElement, m_asfHandler) == 0x40);
static_assert(offsetof(CAnimationElement, m_blendPiece) == 0x50);
static_assert(offsetof(CAnimationElement, m_blendRate) == 0x54);
static_assert(offsetof(CAnimationElement, m_additive) == 0x60);
static_assert(sizeof(CAnimationElement) == 0x68);

// Framework::CAnimationBlendContainer::_tBlendMotionData: one blended motion (0x10; the TArray PlayAnimation walks).
struct BlendMotionData {
    float m_weight;                 // 0x00: AafBlendManager::SetWeight
    float m_frame;                  // 0x04: AafBlendManager::SetPlayFrame
    CAnimationElement* m_element;   // 0x08: its m_aafHandler is AddAaf'ed
};
static_assert(sizeof(BlendMotionData) == 0x10);

// Framework::CAnimationBlendContainer: a model's animations and their blending. Size 0xb0 (the last field
// the constructor writes is at 0xa8; its allocation site is in the model's constructor, scene's); layout
// from the constructor, Initialize, PlayAnimation, rElement, PresentFrame, Flag, OrAllFlag
// (port/decomp/anim/animation_model.c). vtable (_ZTVN9Framework24CAnimationBlendContainerE, 25 slots):
// the animation interface shared with CAnimationModel (0 StartAnimation .. 22 AndFlag), 23 D1, 24 D0.
// Per frame (CAnimationModel::Progress): ProgressBlend, ProgressFrame, PlayAnimation (opens the blend
// manager with every motion's handler, sets frames and weights, normalizes, slot 2 SetValues; then the
// additive / overwrite elements' AddValues / BlendValues).
class CAnimationBlendContainer {
public:
    // Constructors / destructors (bound as Ctor / Dtor: a C++ constructor can't be bound)
    void CtorBase();  // Framework::CAnimationBlendContainer::CAnimationBlendContainer()
    void DtorBase();  // Framework::CAnimationBlendContainer::~CAnimationBlendContainer()
    void DtorDelete();  // Framework::CAnimationBlendContainer::~CAnimationBlendContainer()
    // Virtuals in vtable order (_ZTVN9Framework24CAnimationBlendContainerE), as plain members: no C++ `virtual` (the guest's vtable is the field)
    void StartAnimation(s32, float, bool);  // vtable slot 0: Framework::CAnimationBlendContainer::StartAnimation(int, float, bool)
    void StartFrame(float);  // vtable slot 1: Framework::CAnimationBlendContainer::StartFrame(float)
    void EndFrame(float);  // vtable slot 2: Framework::CAnimationBlendContainer::EndFrame(float)
    void PresentFrame(float);  // vtable slot 3: Framework::CAnimationBlendContainer::PresentFrame(float)
    void TerminateProcess(u32);  // vtable slot 4: Framework::CAnimationBlendContainer::TerminateProcess(unsigned int)
    bool IsEnableLoop() const;  // vtable slot 5: Framework::CAnimationBlendContainer::IsEnableLoop() const
    bool IsEnableFrameStopAtEnd() const;  // vtable slot 6: Framework::CAnimationBlendContainer::IsEnableFrameStopAtEnd() const
    bool IsEnableFreeTerm() const;  // vtable slot 7: Framework::CAnimationBlendContainer::IsEnableFreeTerm() const
    bool IsLooped() const;  // vtable slot 8: Framework::CAnimationBlendContainer::IsLooped() const
    bool IsLoopedAtOnce() const;  // vtable slot 9: Framework::CAnimationBlendContainer::IsLoopedAtOnce() const
    u32 NumLoop() const;  // vtable slot 10: Framework::CAnimationBlendContainer::NumLoop() const
    void ClearLoopedFlag();  // vtable slot 11: Framework::CAnimationBlendContainer::ClearLoopedFlag()
    void AnimationSpeed(float);  // vtable slot 12: Framework::CAnimationBlendContainer::AnimationSpeed(float)
    void AnimationSpeedByTransitionValue(u32, float, float);  // vtable slot 13: Framework::CAnimationBlendContainer::AnimationSpeedByTransitionValue(unsigned int, float, float)
    float AnimationSpeed() const;  // vtable slot 14: Framework::CAnimationBlendContainer::AnimationSpeed() const
    float StartFrame() const;  // vtable slot 15: Framework::CAnimationBlendContainer::StartFrame() const
    float PresentFrame() const;  // vtable slot 16: Framework::CAnimationBlendContainer::PresentFrame() const
    float EndFrame() const;  // vtable slot 17: Framework::CAnimationBlendContainer::EndFrame() const
    float PresentBlendRate() const;  // vtable slot 18: Framework::CAnimationBlendContainer::PresentBlendRate() const
    u32 Flag() const;  // vtable slot 19: Framework::CAnimationBlendContainer::Flag() const
    void ClearAllFlag();  // vtable slot 20: Framework::CAnimationBlendContainer::ClearAllFlag()
    void OrFlag(u32);  // vtable slot 21: Framework::CAnimationBlendContainer::OrFlag(unsigned int)
    void AndFlag(u32);  // vtable slot 22: Framework::CAnimationBlendContainer::AndFlag(unsigned int)
    // vtable slot 23: Framework::CAnimationBlendContainer::~CAnimationBlendContainer() (declared above)
    // vtable slot 24: Framework::CAnimationBlendContainer::~CAnimationBlendContainer() (declared above)
    // Methods (a static one: declare it static and bind it with NATIVE_FUNCTION(sym, wrap<&C::F>(), ...))
    void Release();  // Framework::CAnimationBlendContainer::Release()
    void Initialize(u32, u32);  // Framework::CAnimationBlendContainer::Initialize(unsigned int, unsigned int)
    void Open();  // Framework::CAnimationBlendContainer::Open()
    void AttachAaf(void*, u32, const void*, s32, bool);  // Framework::CAnimationBlendContainer::AttachAaf(Aska::AsfHandler&, unsigned int, void const*, int, bool)
    void DetachAafByIndex(u32);  // Framework::CAnimationBlendContainer::DetachAafByIndex(unsigned int)
    void DetachAafByAnimID(u32);  // Framework::CAnimationBlendContainer::DetachAafByAnimID(unsigned int)
    CAnimationElement* pSearch(s32);  // Framework::CAnimationBlendContainer::pSearch(int)
    void AttachAet(u32, const void*);  // Framework::CAnimationBlendContainer::AttachAet(unsigned int, void const*)
    void ReplaceAafAndAet(u32, const void*, const void*);  // Framework::CAnimationBlendContainer::ReplaceAafAndAet(unsigned int, void const*, void const*)
    void Close();  // Framework::CAnimationBlendContainer::Close()
    u32 pSearchForIndex(s32) const;  // Framework::CAnimationBlendContainer::pSearchForIndex(int) const
    u32 pSearchEmpty() const;  // Framework::CAnimationBlendContainer::pSearchEmpty() const
    void ProgressBlend(float);  // Framework::CAnimationBlendContainer::ProgressBlend(float)
    void ProgressFrame(float, void*);  // Framework::CAnimationBlendContainer::ProgressFrame(float, Framework::CAnimationBlendContainer::tProgressFrame_Arguments const*)
    void ProgressFrame_Direct(float);  // Framework::CAnimationBlendContainer::ProgressFrame_Direct(float)
    void PlayAnimation(void*);  // Framework::CAnimationBlendContainer::PlayAnimation(Aska::FiberTask*)
    u32 OrAllFlag() const;  // Framework::CAnimationBlendContainer::OrAllFlag() const
    u32 NumElements() const;  // Framework::CAnimationBlendContainer::NumElements() const
    CAnimationElement* rElement(s32);  // Framework::CAnimationBlendContainer::rElement(int)
    CAnimationElement* crElement(s32) const;  // Framework::CAnimationBlendContainer::crElement(int) const
    bool IsExist(s32) const;  // Framework::CAnimationBlendContainer::IsExist(int) const
    void BlendRateAtLastRequestedElement() const;  // Framework::CAnimationBlendContainer::BlendRateAtLastRequestedElement() const
    void SetBlendRateElapsedTimeLimitToLastRequestedElement(float);  // Framework::CAnimationBlendContainer::SetBlendRateElapsedTimeLimitToLastRequestedElement(float)
    bool MakeBlank(float);  // Framework::CAnimationBlendContainer::MakeBlank(float)
    void StartDirectionBlendAnimation(void*, s32, float);  // Framework::CAnimationBlendContainer::StartDirectionBlendAnimation(Framework::CAnimationBlendContainer::tDirectionBlend_Arguments const*, int, float)
    void DirectionBlendRadian(u32, float);  // Framework::CAnimationBlendContainer::DirectionBlendRadian(unsigned int, float)
    void StartAddAnimation(u32, float, bool);  // Framework::CAnimationBlendContainer::StartAddAnimation(unsigned int, float, bool)
    void StartOverwriteAnimation(u32, float, bool);  // Framework::CAnimationBlendContainer::StartOverwriteAnimation(unsigned int, float, bool)
    void ResetAnimationControllers(void*, void*);  // Framework::CAnimationBlendContainer::ResetAnimationControllers(Aska::AsfHandler*, Aska::CollisionHandler*)
    void GetAnimationLength(u32);  // Framework::CAnimationBlendContainer::GetAnimationLength(unsigned int)
    void DetachApk(const void*);  // Framework::CAnimationBlendContainer::DetachApk(void const*)
    void InitializeKeepHipsPosition(HierarchicalObject*);  // Framework::CAnimationBlendContainer::InitializeKeepHipsPosition(Aska::HierarchicalObject*)
    void InitializeKeepPosRootPosition(HierarchicalObject*);  // Framework::CAnimationBlendContainer::InitializeKeepPosRootPosition(Aska::HierarchicalObject*)
    void DeleteBlendManager();  // Framework::CAnimationBlendContainer::DeleteBlendManager()

    const void* vtable;                                 // 0x00: _ZTVN9Framework24CAnimationBlendContainerE + 0x10
    containers::TArray<BlendMotionData, false> m_motions; // 0x08: the motions blended this frame (m_motions.m_size)
    u8 unk_40[8];                                       // 0x40
    AafBlendManager* m_blendManager;                    // 0x48: PlayAnimation creates it (0x48 bytes) when blending
    CBlendRatePlayer* m_blendRatePlayer;                // 0x50: Initialize
    u32 m_numElements;                                  // 0x58: NumElements
    u8 unk_5c[4];                                       // 0x5c
    CAnimationElement* m_elements;                      // 0x60: m_numElements (new[] with the count at -8)
    void* m_postNotify;                                 // 0x68: called by PlayAnimation after the blend (slot 0, arg 0)
    float m_speed;                                      // 0x70: 1.0 after Initialize
    u32 unk_74;                                         // 0x74
    u8 unk_78[0x10];                                    // 0x78
    float unk_88;                                       // 0x88: NaN at construction
    u8 unk_8c[4];                                       // 0x8c
    s32 m_currentAnimId;                                // 0x90: the present animation (-1 after Initialize)
    u8 unk_94[4];                                       // 0x94
    u16 unk_98;                                         // 0x98: 0 at construction
    u8 unk_9a[6];                                       // 0x9a
    void* m_keepHipsPosition;                           // 0xa0: InitializeKeepHipsPosition's object (0x50), run after the blend
    void* m_keepPosRootPosition;                        // 0xa8: InitializeKeepPosRootPosition's (0x18)
};
static_assert(offsetof(CAnimationBlendContainer, m_motions) == 0x08);
static_assert(offsetof(CAnimationBlendContainer, m_blendManager) == 0x48);
static_assert(offsetof(CAnimationBlendContainer, m_blendRatePlayer) == 0x50);
static_assert(offsetof(CAnimationBlendContainer, m_numElements) == 0x58);
static_assert(offsetof(CAnimationBlendContainer, m_elements) == 0x60);
static_assert(offsetof(CAnimationBlendContainer, m_speed) == 0x70);
static_assert(offsetof(CAnimationBlendContainer, m_currentAnimId) == 0x90);
static_assert(offsetof(CAnimationBlendContainer, m_keepHipsPosition) == 0xa0);
static_assert(sizeof(CAnimationBlendContainer) == 0xb0);

// Framework::CAnimationModel: the animation side of a Framework model (CCharacterModel, CEffectModel derive
// from it: scene). Layout from the constructor and the accessors (port/decomp/anim/animation_model.c);
// its data ends at 0x64: a derived class's first member may sit at 0x64, in the tail padding (sizeof here
// is 0x68).
// vtable (_ZTVN9Framework15CAnimationModelE, 29 slots): 0-22 the animation interface (forwarded to
// m_pBlend: PresentFrame() = m_pBlend's slot 16, Flag() = slot 19), 23 D1, 24 D0, 25 Release,
// 26 Progress(float), 27 UpdatePosture(CMatrix const&), 28 UpdateScale(CVector const&).
class CAnimationModel {
public:
    // Constructors / destructors (bound as Ctor / Dtor: a C++ constructor can't be bound)
    void CtorBase();  // Framework::CAnimationModel::CAnimationModel()
    void Dtor();  // Framework::CAnimationModel::~CAnimationModel()
    void DtorDelete();  // Framework::CAnimationModel::~CAnimationModel()
    // Virtuals in vtable order (_ZTVN9Framework15CAnimationModelE), as plain members: no C++ `virtual` (the guest's vtable is the field)
    void StartAnimation(s32, float, bool);  // vtable slot 0: Framework::CAnimationModel::StartAnimation(int, float, bool)
    void StartFrame(float);  // vtable slot 1: Framework::CAnimationModel::StartFrame(float)
    void EndFrame(float);  // vtable slot 2: Framework::CAnimationModel::EndFrame(float)
    void PresentFrame(float);  // vtable slot 3: Framework::CAnimationModel::PresentFrame(float)
    void TerminateProcess(u32);  // vtable slot 4: Framework::CAnimationModel::TerminateProcess(unsigned int)
    bool IsEnableLoop() const;  // vtable slot 5: Framework::CAnimationModel::IsEnableLoop() const
    bool IsEnableFrameStopAtEnd() const;  // vtable slot 6: Framework::CAnimationModel::IsEnableFrameStopAtEnd() const
    bool IsEnableFreeTerm() const;  // vtable slot 7: Framework::CAnimationModel::IsEnableFreeTerm() const
    bool IsLooped() const;  // vtable slot 8: Framework::CAnimationModel::IsLooped() const
    bool IsLoopedAtOnce() const;  // vtable slot 9: Framework::CAnimationModel::IsLoopedAtOnce() const
    u32 NumLoop() const;  // vtable slot 10: Framework::CAnimationModel::NumLoop() const
    void ClearLoopedFlag();  // vtable slot 11: Framework::CAnimationModel::ClearLoopedFlag()
    void AnimationSpeed(float);  // vtable slot 12: Framework::CAnimationModel::AnimationSpeed(float)
    void AnimationSpeedByTransitionValue(u32, float, float);  // vtable slot 13: Framework::CAnimationModel::AnimationSpeedByTransitionValue(unsigned int, float, float)
    float AnimationSpeed() const;  // vtable slot 14: Framework::CAnimationModel::AnimationSpeed() const
    float StartFrame() const;  // vtable slot 15: Framework::CAnimationModel::StartFrame() const
    float PresentFrame() const;  // vtable slot 16: Framework::CAnimationModel::PresentFrame() const
    float EndFrame() const;  // vtable slot 17: Framework::CAnimationModel::EndFrame() const
    float PresentBlendRate() const;  // vtable slot 18: Framework::CAnimationModel::PresentBlendRate() const
    u32 Flag() const;  // vtable slot 19: Framework::CAnimationModel::Flag() const
    void ClearAllFlag();  // vtable slot 20: Framework::CAnimationModel::ClearAllFlag()
    void OrFlag(u32);  // vtable slot 21: Framework::CAnimationModel::OrFlag(unsigned int)
    void AndFlag(u32);  // vtable slot 22: Framework::CAnimationModel::AndFlag(unsigned int)
    // vtable slot 23: Framework::CAnimationModel::~CAnimationModel() (declared above)
    // vtable slot 24: Framework::CAnimationModel::~CAnimationModel() (declared above)
    void Release();  // vtable slot 25: Framework::CAnimationModel::Release()
    void Progress(float);  // vtable slot 26: Framework::CAnimationModel::Progress(float)
    void UpdatePosture(const MathMatrix*);  // vtable slot 27: Framework::CAnimationModel::UpdatePosture(Framework::CMatrix const&)
    void UpdateScale(const MathVector*);  // vtable slot 28: Framework::CAnimationModel::UpdateScale(Framework::CVector const&)
    // Methods (a static one: declare it static and bind it with NATIVE_FUNCTION(sym, wrap<&C::F>(), ...))
    void Initialize();  // Framework::CAnimationModel::Initialize()
    void ResetPosture();  // Framework::CAnimationModel::ResetPosture()
    void AssignResource(void*, CAnimationBlendContainer*);  // Framework::CAnimationModel::AssignResource(Aska::AsfHandler&, Framework::CAnimationBlendContainer&)
    s64 rAssignedAsfHandler();  // Framework::CAnimationModel::rAssignedAsfHandler()
    s64 crAssignedAsfHandler() const;  // Framework::CAnimationModel::crAssignedAsfHandler() const
    s64 rObjectRoot();  // Framework::CAnimationModel::rObjectRoot()
    s64 pObjectRoot();  // Framework::CAnimationModel::pObjectRoot()
    s64 cpObjectRoot() const;  // Framework::CAnimationModel::cpObjectRoot() const
    void SetObjectRoot(HierarchicalObject*);  // Framework::CAnimationModel::SetObjectRoot(Aska::HierarchicalObject*)
    CAnimationBlendContainer* rAnimationBlendContainer();  // Framework::CAnimationModel::rAnimationBlendContainer()
    bool HasTranslateRoot() const;  // Framework::CAnimationModel::HasTranslateRoot() const
    void OffsetAtTranslateRoot() const;  // Framework::CAnimationModel::OffsetAtTranslateRoot() const
    void OffsetAtTranslateRoot(const MathVector*);  // Framework::CAnimationModel::OffsetAtTranslateRoot(Framework::CVector const&)
    u32 PresentAnimation() const;  // Framework::CAnimationModel::PresentAnimation() const
    u32 PresentAnimationChangeTime() const;  // Framework::CAnimationModel::PresentAnimationChangeTime() const
    void GetVelocityByAnimation(float);  // Framework::CAnimationModel::GetVelocityByAnimation(float)
    void GetVelocityByAet(float);  // Framework::CAnimationModel::GetVelocityByAet(float)
    void GetRotateByAet(float);  // Framework::CAnimationModel::GetRotateByAet(float)
    void InvalidateMatrix(HierarchicalObject*);  // Framework::CAnimationModel::InvalidateMatrix(Aska::HierarchicalObject*)
    void EnableFrameOnly(bool);  // Framework::CAnimationModel::EnableFrameOnly(bool)

    const void* vtable;                 // 0x00: _ZTVN9Framework15CAnimationModelE + 0x10
    void* m_asfHandler;                 // 0x08: Aska::AsfHandler* (AssignResource)
    CAnimationBlendContainer* m_pBlend; // 0x10: AssignResource ("m_pBlend is null")
    HierarchicalObject* m_objectRoot;   // 0x18: SetObjectRoot (most likely)
    u64 unk_20;                         // 0x20: 0 at construction
    u8 unk_28[8];                       // 0x28
    u32 unk_30;                         // 0x30: 0 at construction
    u8 unk_34[8];                       // 0x34: 0 at construction
    float m_vec3c[4];                   // 0x3c: a constant vector at construction (the posture offset, most likely)
    float m_vec4c[4];                   // 0x4c: the same constant
    float m_scale5c;                    // 0x5c: 1.0 at construction
    u32 unk_60;                         // 0x60: 0 at construction
};
static_assert(offsetof(CAnimationModel, m_pBlend) == 0x10);
static_assert(offsetof(CAnimationModel, unk_30) == 0x30);
static_assert(offsetof(CAnimationModel, m_vec3c) == 0x3c);
static_assert(offsetof(CAnimationModel, m_scale5c) == 0x5c);
static_assert(sizeof(CAnimationModel) == 0x68);

}  // namespace soa::native::anim

#endif  // SOA_NATIVE_ANIM_LAYOUT_H
