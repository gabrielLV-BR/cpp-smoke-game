#pragma once

#include <string>
#include <cstdint>

#include "./shader.hpp"
#include "./texture.hpp"

namespace ProgramUniforms {
const static std::string COLOR = "uColor";
}

enum ProgramBits {
    DIFFUSE_MAP = 1 << 0,
    NORMAL_MAP = 1 << 1,
};

struct Program {
    using bitset = uint32_t;

    uint32_t handle;

    Program(Shader vertex, Shader fragment);
    ~Program();

    int GetUniformLocation(const std::string& name) const;

    template <typename T>
    void SetUniform(std::string name, T value) {
        int location = GetUniformLocation(name);

        if (location == -1)
            return;

        _InternalSetUniform(location, value);
    }

    void Bind();
    void Unbind();

    bool operator==(const Program& other) const {
        return handle == other.handle;
    }

   private:
    template <typename T>
    void _InternalSetUniform(int location, T value) {
        std::cout << "type not implemented\n";
    }

    void _InternalSetUniform(int location, int value);
    void _InternalSetUniform(int location, float value);
    void _InternalSetUniform(int location, const Texture& t);

    void _CheckForErrors();
};

template <>
struct std::hash<Program> {
    size_t operator()(const Program& p) const {
        return std::hash<uint32_t>()(p.handle);
    }
};