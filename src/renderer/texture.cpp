#include "./texture.hpp"

#include "glad/glad.h"

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

Texture::~Texture() {
  glDeleteTextures(1, &handle);
}

Texture Texture::from_file(const std::string& path) {
  int width, height, channel_count;
  unsigned char* data =
      stbi_load(path.c_str(), &width, &height, &channel_count, 0);

  Texture t(data, width, height, channel_count);

  stbi_image_free(data);

  return t;
}

void Texture::bind() const {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, handle);
}

void Texture::unbind() const {
  glBindTexture(GL_TEXTURE_2D, 0);
}