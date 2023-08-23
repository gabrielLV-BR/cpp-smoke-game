#include "mesh_loader.hpp"

#include <vector>
#include <exception>

#include "renderer/vertex.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

MeshLoader::MeshLoader(MeshServer& mesh_server) : mesh_server(mesh_server) {}

std::vector<MeshServer::Key> MeshLoader::Load(std::string path) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, 0);

    if (scene == NULL) {
        throw std::runtime_error("Error loading mesh");
    }

    std::vector<MeshServer::Key> mesh_keys;
    mesh_keys.reserve(scene->mNumMeshes);

    for (int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* raw_mesh = scene->mMeshes[i];

        Mesh* mesh = _LoadMesh(raw_mesh);

        auto key = mesh_server.Store(mesh);
        mesh_keys.push_back(key);
    }

    return mesh_keys;
}

Mesh* MeshLoader::_LoadMesh(aiMesh* mesh) {
    std::string name(mesh->mName.C_Str());

    std::vector<Vertex> vertices;
    vertices.reserve(mesh->mNumVertices);

    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D position = mesh->mVertices[i];
        aiVector3D normal = mesh->mNormals[i];
        aiVector3D uv = mesh->mTextureCoords[0][i];

        vertices.emplace_back(position, normal, uv);
    }

    std::vector<uint32_t> indices;
    // every face is a tri
    indices.reserve(mesh->mNumFaces * 3);

    for (int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for (int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return new Mesh(name, vertices, indices);
}