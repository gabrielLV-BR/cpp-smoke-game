#pragma once

#include <cstdint>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

struct Texture {
  uint32_t handle;

  Texture(const void* data, int width, int height, int channel_count);
  ~Texture();

  static Texture from_file(const std::string& path);

  inline void bind() const;
  inline void unbind() const;
};