#pragma once

#include <memory>
#include <cstdint>
#include <unordered_map>
#include <string>

#include "renderer/mesh.hpp"
#include "renderer/material.hpp"
#include "renderer/program.hpp"
#include "renderer/texture.hpp"

template <typename K, typename T>
class Server {
   public:
    using Key = K;

   private:
    std::unordered_map<K, std::shared_ptr<T>> data;

   public:
    void Store(K key, T* value);
    std::shared_ptr<T> Get(K key);

    void Delete(K key);
};

class MeshServer : public Server<std::string, std::vector<Mesh>> {};

class TextureServer : public Server<std::string, Texture> {};

class ProgramServer : public Server<Program::bitset, Program> {
    std::shared_ptr<Program> GetForMaterial(Material material);
};
