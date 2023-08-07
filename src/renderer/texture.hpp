#pragma once

#include <cstdint>
#include <string>

struct Texture {
    uint32_t handle;

    Texture(const void* data, int width, int height, int channel_count);
    ~Texture();

    void Bind() const;
    void Unbind() const;
};