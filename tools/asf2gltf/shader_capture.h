// The game's own shaders for a model's materials, from a capture of its draws (soa with
// SOA_GL_DRAW_DUMP=DIR: draws.tsv, program_N.txt, draw_N.txt), for the SOA_aska_shader extension
// (docs/notes.md "glTF export"), and the raw vertex streams those shaders read (shader_replay.py).
#pragma once

#include <soa/asf.h>

#include <nlohmann/json.hpp>

#include <string>

namespace gltf {

// {"shaders": [{"stage", "glsl", "programs"}], "materials": {"<object>/<material>": {"passes": [...]}}}:
// each pass is a captured draw whose bound textures are the material's, in slot order: its
// program's shaders (indices into "shaders"), the draw state, the vertex attributes, and every
// uniform with where its value comes from (a texture slot, a material constant, the material's
// header, or the engine: then the captured value). Empty when the directory holds no capture.
nlohmann::ordered_json capture_shaders(const soa::asf::Scene& s, const std::string& dir, std::string* err);

// DIR/<object>_<meshset>.f32 (per vertex, per vertex element: 4 floats as GL hands them to the
// vertex shader), .u32 (the indices) and .json (the elements' usages, in order): the meshsets as
// the game's vertex shaders see them (object space, palette indices), for shader_replay.py.
bool write_raw_streams(const soa::asf::Scene& s, const std::string& dir, std::string* err);

}  // namespace gltf
