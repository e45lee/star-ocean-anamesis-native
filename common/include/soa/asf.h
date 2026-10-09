#pragma once
// ASF: the game's 3D scenes (Character/, Weapon/, BG/, MapHome/, Deco/, Effect/ *.asf; part of
// soa_models). docs/notes.md "Meshes (ASF)" documents the layout; this reader follows the game's
// own loaders: Aska::AsfHandler::CreateTree (the node tree, 'eert'), Aska::AofHandler::Attach
// (an object's meshsets, '__oa'), Attach_IndexList / Attach_VertexList (the index and vertex
// blocks, through the AMF buffers: soa/aff.h), Aska::RenderablePrimitive::CreateVertexFormat (a
// vertex list's attribute bits to its elements), Aska::MaterialList::Activate (the materials,
// 'stam'), Aska::AsfHandler::GetInverseBindPose (a joint's inverse bind matrix).
// Input: the decoded file (ADLD and SLZ undone).
#include <soa/aff.h>

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace soa::asf {

using Bytes = aff::Bytes;

// ---- vertex formats -------------------------------------------------------------------------------
// One element of Aska::VertexFormat: byte offset, data type, usage (semantic) and usage index,
// packed as the game keeps them (offset | type << 8 | usage << 16 | index << 24).
struct VertexElement {
    uint8_t offset = 0, type = 0, usage = 0, index = 0;
};
// Usages (by the data they carry and the CreateVertexFormat bit groups they come from):
enum Usage : uint8_t {
    kPosition = 1,     // bits 0-3
    kColor = 2,        // bit 28 (ubyte4 normalized) or bit 37 (float4)
    kNormal = 3,       // bits 4-7
    kTangent = 4,      // bits 16-19 (w: the bitangent's sign)
    kTexcoord = 5,     // bits 8-11, 12-15, 20-23, 24-27 (sets 0-3), 44-45 (set 4)
    kBlendWeight = 6,  // bits 40-43
    kBlendIndex = 7,   // bit 30 (ubyte4: indices into the meshset's bone palette)
};
// Data types (RenderDeviceGL::BindVertexFormat's switch): components, GL type, normalized, bytes.
struct TypeInfo {
    int components = 0;
    uint32_t gl_type = 0;  // GL_FLOAT 0x1406, GL_HALF_FLOAT 0x140b, GL_SHORT 0x1402, ...
    bool normalized = false;
    int bytes = 0;
};
bool type_info(uint8_t type, TypeInfo& out);
// Aska::RenderablePrimitive::CreateVertexFormat(VertexFormat*, u64 asm_bits): false for bits it
// rejects. The tables are the game's (libSOA 3.7.0 @029d1cb0..029d1ea0).
bool vertex_format(uint64_t asm_bits, std::vector<VertexElement>& out);
// "POSITION" ... for a usage, "" for an unknown one.
const char* usage_name(uint8_t usage);

// ---- the scene ----------------------------------------------------------------------------------------
// Node kinds (the 'atta' chunk's +0x49; the counts per kind are the 'eert' chunk's +0x18 table):
enum NodeKind : uint8_t {
    kRoot = 0,
    kTransform = 1,      // a transform (locators, attach points such as itemLink_L)
    kJoint = 2,          // a skeleton joint (Aska::JointObject): has an inverse bind matrix
    kObject = 3,         // a mesh object (Aska::AofObject): its '__oa' chunk
    kDynamicsChain = 12, // a spring chain (trADM_*: hair, skirt, accessories): physics at run time
    kCollisionSphere = 20, kCollisionCapsule = 21, kCollisionPlane = 22,  // (19 too: a collision group)
};
const char* node_kind_name(int kind);

struct Node {
    int index = 0;
    std::string name;       // without the "R:" resource prefix
    std::string raw_name;   // as stored
    int kind = 0;
    int parent = -1;        // node index (the root is its own parent in the file: -1 here)
    uint32_t hash = 0;      // +0x30
    uint32_t link = 0;      // +0x34 (kObject: the file offset of its '__oa' chunk)
    uint8_t flags = 0;      // +0x4b
    int children = 0;       // +0x40
    std::array<float, 4> pos{}, rot{0, 0, 0, 1}, scale{1, 1, 1, 1}, pos_offset{};
    std::array<std::array<float, 4>, 4> pivot{};  // +0xc0..+0xf0
    bool joint = false;     // kJoint: the next two are present
    std::array<float, 16> inverse_bind{};  // +0x100, row-major, translation in column 3
    std::array<float, 4> joint_orient{0, 0, 0, 1};  // +0x140 (quaternion x, y, z, w)
    size_t chunk = 0, chunk_size = 0;
    int object = -1;        // kObject: index into Scene::objects
    std::vector<int> chain; // kDynamicsChain: the joints it drives (+0x11a u16 count, +0x128 the
                            // offset of 0x30-byte records whose first u32 is a node index)
};

// A texture embedded in an object (' FIA' chunk; its images, 'Xgmi', are blocks of the AMF buffer).
struct TextureLevel {
    int fmt = 0, w = 0, h = 0;
    aff::Auid pixels;
};
struct Texture {
    uint32_t id = 0;     // Xgmi +0x10: what the materials' texture references name
    uint32_t cls = 0;    // Xgmi +0x14 ('BA1H')
    std::vector<TextureLevel> levels;  // level 0 first
    aff::Auid header;    // the AMF block holding the 'Xgmi' headers
};
// A material's texture reference (32 bytes; the material's +0x2c table).
struct TextureRef {
    uint32_t id = 0;     // a Texture::id of this object, or (cls 'BA1G') a texture the game supplies
    uint32_t cls = 0;
    uint32_t word8 = 0;
    uint16_t wrap = 0, slot_kind = 0;
    std::array<uint8_t, 32> raw{};
};
// A shader constant ({u16 id, u8 index, u8 count << 2, s32 offset} + count vec4s).
struct ShaderConst {
    uint16_t id = 0;
    uint8_t index = 0;
    std::vector<std::array<float, 4>> values;
};
struct Material {
    size_t chunk = 0;    // 'stam'
    std::vector<TextureRef> textures;
    std::vector<ShaderConst> constants;
    uint32_t flags = 0;  // +0x3c (bit 0/3/8: ..., 4: ...; MaterialList::Activate)
    uint8_t blend = 0;   // +0x41
    std::vector<uint8_t> raw;  // the whole chunk (until its constants), for the extras
};
struct Meshset {
    int material = -1;   // index into Object::materials
    int prim = 0;        // PrimType: 0 triangle list, 1 quads, 2 lines, 3 line strip, 4 triangle strip, 5 fan, 7 points
    uint32_t vertex_count = 0, index_count = 0;
    uint64_t asm_bits = 0;
    uint16_t stride = 0;
    uint16_t flags = 0;  // the 'mess' +0x1e
    int shares = -1;     // +0x1c set: the meshset whose geometry this one draws
    std::vector<uint16_t> palette;  // 'ipnb': blend index -> index into Object::bones
    std::vector<VertexElement> elements;
    Bytes vertices;      // vertex_count * stride bytes, as the game uploads them
    Bytes indices;       // u16 (or u32 when index32) indices
    bool index32 = false;
    aff::Auid vertex_block, index_block;
};
struct Object {
    std::string name;                // the '__oa' +0xb0 name ("R:m_bodyShape" -> "m_bodyShape")
    int node = -1;                   // its kObject node
    size_t chunk = 0;
    std::vector<uint16_t> bones;     // 'lpnb': node indices
    std::vector<Texture> textures;
    std::vector<Material> materials;
    std::vector<Meshset> meshsets;
};
struct Scene {
    std::vector<Node> nodes;
    std::vector<Object> objects;
    std::vector<std::string> link_names;  // 'lnbc': names of external nodes (other files)
    aff::Amf amf;
};

// Reads a decoded .asf. False (and *err) when the file isn't one or a part doesn't decode; a
// meshset or texture whose block is missing is kept with empty data and a note in *warnings.
bool load(const Bytes& file, Scene& out, std::string* err = nullptr, std::vector<std::string>* warnings = nullptr);

// A texture level's pixels (ETC2 / EAC: soa/aska_image.h) as RGBA8, top-down.
bool decode_texture(const Scene& s, const TextureLevel& t, Bytes& rgba, std::string* err = nullptr);

}  // namespace soa::asf
