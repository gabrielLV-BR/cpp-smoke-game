#pragma once

#include <string>

#include "renderer/mesh.hpp"
#include "renderer/model.hpp"
#include "renderer/texture.hpp"
#include "renderer/material.hpp"

class ModelLoader {
   public:
    ModelLoader();

    Model LoadModel(std::string path);

   private:
    Mesh LoadMesh(std::string path);
};