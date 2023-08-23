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

    std::vector<MeshServer::Key> Load(std::string path);

   private:
    Mesh* _LoadMesh(aiMesh* mesh);
};