#include "./texture.hpp"

#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture::Texture(const void* data, int width, int height, int channel_count) {
  glGenTextures(1, &handle);

  bind();

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  unbind();
}

<<<<<<< HEAD
Texture::~Texture() {
  glDeleteTextures(1, &handle);
}
=======
Texture::~Texture() { glDeleteTextures(1, &handle); }
>>>>>>> d27f141ba1857a353d8e1b7469aa15d3daff0602

Texture Texture::from_file(const std::string& path) {
  int width, height, channel_count;
  unsigned char* data =
      stbi_load(path.c_str(), &width, &height, &channel_count, 0);

  Texture t(data, width, height, channel_count);

  stbi_image_free(data);

  return t;
}

<<<<<<< HEAD
inline void Texture::bind() const {
=======
void Texture::bind() const {
>>>>>>> d27f141ba1857a353d8e1b7469aa15d3daff0602
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, handle);
}

<<<<<<< HEAD
inline void Texture::unbind() const {
  glBindTexture(GL_TEXTURE_2D, 0);
}
=======
void Texture::unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
>>>>>>> d27f141ba1857a353d8e1b7469aa15d3daff0602
