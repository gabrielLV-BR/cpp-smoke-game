#include "mesh_loader.hpp"

#include <iostream>
#include <vector>
#include <exception>

#include "renderer/vertex.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

MeshLoader::MeshLoader(MeshServer& mesh_server) : mesh_server(mesh_server) {}

std::vector<MeshServer::Key> MeshLoader::LoadFromFile(const std::string& path) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, 0);

    if (scene == NULL) {
        throw std::runtime_error("Error loading mesh");
    }

    return Load(path, scene);
}

std::vector<MeshServer::Key> MeshLoader::Load(
    const std::string& path,
    const aiScene* scene) {
    std::vector<Mesh>* meshes = new std::vector<Mesh>();
    meshes->reserve(scene->mNumMeshes);

    for (int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* raw_mesh = scene->mMeshes[i];

        Mesh mesh = _MeshFromRaw(raw_mesh);
        meshes->push_back(mesh);
    }

    mesh_server.Store(path, meshes);

    return;
}

Mesh MeshLoader::_MeshFromRaw(aiMesh* mesh) {
    std::string name(mesh->mName.C_Str());

    std::vector<Vertex> vertices;
    vertices.reserve(mesh->mNumVertices);

    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D raw_position = mesh->mVertices[i];
        aiVector3D raw_normal = mesh->mNormals[i];
        aiVector3D raw_uv = mesh->mTextureCoords[0][i];

        Vector3 position(raw_position.x, raw_position.y, raw_position.z);

        Vector3 normal(raw_normal.x, raw_normal.y, raw_normal.z);

        Vector2 uv(raw_uv.x, raw_uv.y);

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

    return Mesh(name, vertices, indices);
}