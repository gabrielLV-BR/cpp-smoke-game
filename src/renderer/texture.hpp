#pragma once

#include <cstdint>
#include <string>

struct Texture {
  uint32_t handle;

  Texture(const void* data, int width, int height, int channel_count);
  ~Texture();

  static Texture from_file(const std::string& path);

<<<<<<< HEAD
  inline void bind() const;
  inline void unbind() const;
=======
  void bind() const;
  void unbind() const;
>>>>>>> d27f141ba1857a353d8e1b7469aa15d3daff0602
};