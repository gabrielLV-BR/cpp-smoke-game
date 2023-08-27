#pragma once

#include <memory>
#include <string>

#include "servers/server.hpp"

class TextureLoader {
   private:
    TextureServer& texture_server;

   public:
    TextureLoader(TextureServer&);
    std::shared_ptr<Texture> Load(const std::string& path);
};