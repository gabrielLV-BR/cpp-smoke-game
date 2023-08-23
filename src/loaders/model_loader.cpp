#include "model_loader.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

Model ModelLoader::LoadModel(std::string path) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, 0);

    if (scene == NULL) {
        throw std::runtime_error("Error loading model");
    }
}