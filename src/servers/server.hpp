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
    Key Store(T* value);
    std::shared_ptr<T> Get(Key key);

    void Delete(Key key);
};

class MeshServer : public Server<Mesh> {};

class TextureServer : public Server<Texture> {};

// program server is different enough to deserve its own thing

class ProgramServer {
   private:
    std::unordered_map<Program::bitset, std::shared_ptr<Program>> data;

   public:
    void Store(Program::bitset bitset, Program* program);
    std::shared_ptr<Program> Get(Program::bitset bitset);
    std::shared_ptr<Program> GetForMaterial(Material material);
};
