#pragma once

#include <memory>
#include <cstdint>
#include <unordered_map>

#include "renderer/mesh.hpp"
#include "renderer/material.hpp"
#include "renderer/program.hpp"
#include "renderer/texture.hpp"

template <typename T>
class Server {
   public:
    using Key = uint32_t;

   private:
    std::vector<std::shared_ptr<T>> data;

   public:
    Server();
    ~Server();

    Key Store(T value);
    std::shared_ptr<T> Get(Key key);

    void Delete(Key key);
};

class MeshServer : public Server<Mesh> {};

class ProgramServer : public Server<Program> {
   public:
    std::shared_ptr<Program> Get(Material material);
};

class TextureServer : public Server<Texture> {};
