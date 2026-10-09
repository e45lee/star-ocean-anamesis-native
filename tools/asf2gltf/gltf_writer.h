#pragma once
// asf2gltf's glTF 2.0 writer: a soa::asf::Scene (+ animations) as one .glb or .gltf + .bin.
// JSON by nlohmann-json (vcpkg.json); the buffer, accessors and GLB framing by hand (glTF 2.0
// spec, "GLB File Format Specification").
#include <soa/aff.h>
#include <soa/asf.h>

#include <string>
#include <vector>

namespace gltf {

struct Options {
    bool separate = false;   // .gltf + .bin instead of .glb
    bool extensions = true;  // KHR_animation_pointer / KHR_node_visibility / KHR_texture_transform;
                             // false (--no-ext): baked or dropped for plain viewers
};

struct Anim {
    std::string name;        // its game path (Motion/... or an .aaf inside a package: PKG:member)
    soa::aff::Bytes file;    // decoded
    std::string role;        // the animation-set role (idle, attack, ...), "" when unknown
};

struct Input {
    const soa::asf::Scene* scene = nullptr;
    std::string source_name;
    std::vector<Anim> anims;
};

bool write(const Input& in, const Options& opt, const std::string& out_path, std::string* err);

}  // namespace gltf
