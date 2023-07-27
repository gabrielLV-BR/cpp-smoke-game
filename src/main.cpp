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

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

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

  ObjLoaderConfig config(ASSETS "models/");
  ObjLoader loader(config);

  loader.load("suzanne.obj");

  Mesh mesh(loader.vertices, loader.indices);

  Texture texture = Texture::from_file(ASSETS "models/dice/dice.png");

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

    program.set_uniform<float>("uTime", elapsed_time);
    program.set_uniform<glm::mat4>("uModel", model_matrix);
    program.set_uniform<int>("uTexture", 0);

    texture.bind();
    mesh.bind();

    glDrawElements(GL_TRIANGLES, mesh.index_count(), GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, mesh.vertex_count());

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}