#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "renderer/material.hpp"
#include "renderer/mesh.hpp"
#include "renderer/model.hpp"
#include "renderer/program.hpp"
#include "renderer/shader.hpp"
#include "renderer/texture.hpp"
#include "renderer/vertex.hpp"

#include "loaders/obj_loader.hpp"
#include "math/vector.hpp"
#include "servers/program_server.hpp"
#include "utils/color.hpp"
#include "utils/file.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include "assimp/Importer.hpp"  // C++ importer interface
#include "assimp/scene.h"       // Output data structure
#include "assimp/postprocess.h"

// Remove false-positive errors
#ifndef ASSETS
#define ASSETS ""
#endif

int main() {
  const int WIDTH = 500;
  const int HEIGHT = 500;
  const char* TITLE = "OpenGL Box";

  glfwInit();

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);

  glfwMakeContextCurrent(window);

  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == GLFW_FALSE) {
    std::cerr << "Error loading OpenGL!\n";
    return -1;
  }

  glViewport(0, 0, WIDTH, HEIGHT);
  // depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  // face culling
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

  ProgramServer::initialize();

  glm::mat4 model_matrix = glm::mat4(1.0f);
  model_matrix = glm::rotate(model_matrix, glm::radians(45.0f),
                             glm::vec3(-1.0f, 0.0f, 0.0f));

  Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile(ASSETS "models/dog/dog.obj", 0);

  if (scene == nullptr) {
    std::cerr << "Error opening file!\n";
    return -1;
  }

  const aiMesh* _mesh = scene->mMeshes[0];

  // unsigned int normal_index = 0;
  // for (int i = 0; i < _mesh->mNumVertices; i += 3) {
  //   Vector3 vertex_position(
  //     _mesh->mVertices[i].x, 
  //     _mesh->mVertices[i].y,
  //     _mesh->mVertices[i].z
  //   );

  //   Vector3 vertex_normal(
  //     _mesh->mNormals[i].x, 
  //     _mesh->mNormals[i].y,
  //     _mesh->mNormals[i].z
  //   );

  //   assert(_mesh->mTextureCoords != nullptr);
  //   assert(_mesh->mNumUVComponents[0] > 0);

  //   Vector2 vertex_uv(
  //     _mesh->mTextureCoords[0][i].x,
  //     _mesh->mTextureCoords[0][i].y
  //   );

  //   vertices.emplace_back(vertex_position, vertex_normal, vertex_uv);
  // }

  // for(int i = 0 ; i < _mesh->mNumFaces; i ++) {
  //   std::cout << _mesh->mFaces[i].mNumIndices << std::endl;
  //   indices.push_back(_mesh->mFaces[i].mIndices[0]);
  //   indices.push_back(_mesh->mFaces[i].mIndices[1]);
  //   indices.push_back(_mesh->mFaces[i].mIndices[2]);
  // }

  std::vector<Vertex> vertices = {
    Vertex(
      Vector3(-0.5, -0.5, 0.0),
      Vector3(0.0, 0.0, 0.0),
      Vector2(0.0, 0.0)
    ),
    Vertex(
      Vector3(0.0, 0.5, 0.0),
      Vector3(0.0, 0.0, 0.0),
      Vector2(0.0, 0.0)
    ),
    Vertex(
      Vector3(0.5, -0.5, 0.0),
      Vector3(0.0, 0.0, 0.0),
      Vector2(0.0, 0.0)
    )
  };

  std::vector<GLuint> indices = { 0, 1, 2 };

  // Mesh mesh(vertices, indices);
  uint32_t vbo, ebo, vao;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

  int stride = (3 + 3 + 2) * sizeof(float);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
                        (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);


  Texture texture =
      Texture::from_file(ASSETS "models/dog/textures/youlied.png");

  std::string vertex_source =
      utils::read_file_contents(ASSETS "shaders/basic.vert.glsl");

  std::string fragment_source =
      utils::read_file_contents(ASSETS "shaders/basic.frag.glsl");

  Shader vertex_shader(vertex_source, ShaderType::VERTEX);
  Shader fragment_shader(fragment_source, ShaderType::FRAGMENT);
  Program program(vertex_shader, fragment_shader);

  float elapsed_time = 0;
  while (!glfwWindowShouldClose(window)) {
    elapsed_time = static_cast<float>(glfwGetTime());

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    model_matrix = glm::rotate(glm::mat4(1.0), (float)glfwGetTime(),
                               glm::vec3(0.2, 1.0, 0.0));

    program.bind();
    texture.bind();

    // mesh.bind();
    glBindVertexArray(vao);
    int err = glGetError();

    program.set_uniform<float>("uTime", elapsed_time);
    err = glGetError();

    // program.set_uniform<glm::mat4>("uModel", model_matrix);
    // program.set_uniform<int>("uTexture", 0);
    glUniform1i(glGetUniformLocation(program.handle, "uTexture"), 0);
    err = glGetError();


    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}