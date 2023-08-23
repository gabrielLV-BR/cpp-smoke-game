#include "texture_loader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

TextureLoader::TextureLoader(TextureServer& texture_server)
    : texture_server(texture_server) {}

TextureServer::Key TextureLoader::Load(const std::string path) {
    int width, height, channel_count;
    unsigned char* data =
        stbi_load(path.c_str(), &width, &height, &channel_count, 0);

    Texture* t = new Texture(data, width, height, channel_count);

    auto key = texture_server.Store(t);

    stbi_image_free(data);

    return key;
}