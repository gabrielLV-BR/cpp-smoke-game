#pragma once

#include <string>
#include <vector>

#include "renderer/mesh.hpp"
#include "servers/server.hpp"

#include "assimp/scene.h"

class MeshLoader {
   private:
    MeshServer& mesh_server;

   public:
    MeshLoader(MeshServer& mesh_server);

    std::vector<MeshServer::Key> LoadFromFile(std::string path);
    std::vector<MeshServer::Key> Load(const aiScene* scene);

   private:
    Mesh* _NewMeshFromRaw(aiMesh* mesh);
};