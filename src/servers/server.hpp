#pragma once

#include <memory>
#include <cstdint>
#include <unordered_map>

#include "renderer/mesh.hpp"
#include "renderer/material.hpp"
#include "renderer/program.hpp"
#include "renderer/texture.hpp"

template <typename T, typename K = uint32_t>
class Server {
   private:
    std::unordered_map<K, std::shared_ptr<T>> data;

   public:
    Server();
    ~Server();

    void Store(K key, T value);
    std::shared_ptr<T> Get(K key);

    void Delete(K key);
    void HasItem(K key);
};

extern template class Server<Mesh>;
extern template class Server<Program, Material>;
extern template class Server<Texture>;

typedef Server<Mesh> MeshServer;
typedef Server<Program, Material> ProgramServer;
typedef Server<Texture> TextureServer;
