#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "renderer/mesh.hpp"
#include "renderer/program.hpp"
#include "renderer/shader.hpp"
#include "renderer/vertex.hpp"

#include "loaders/obj_loader.hpp"
#include "physics/vector.hpp"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "glm/ext/matrix_clip_space.hpp"  // glm::perspective
#include "glm/ext/matrix_transform.hpp"  // glm::translate, glm::rotate, glm::scale
#include "glm/ext/scalar_constants.hpp"  // glm::pi
#include "glm/mat4x4.hpp"                // glm::mat4
#include "glm/vec3.hpp"                  // glm::vec3
#include "glm/vec4.hpp"                  // glm::vec4

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
  glDepthFunc(GL_ALWAYS);
  // face culling
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glm::mat4 model_matrix = glm::mat4(1.0f);
  model_matrix = glm::rotate(model_matrix, glm::radians(45.0f),
                             glm::vec3(-1.0f, 0.0f, 0.0f));

  ObjLoaderConfig config(ASSETS "models/dice/");
  ObjLoader loader(config);

  loader.load("dice.obj");

  Mesh mesh(loader.vertices, loader.indices);

  const char* vertex_source =
      "#version 330 core\n"
      "layout(location=0) in vec3 inPos;\n"
      "layout(location=1) in vec3 inNor;\n"
      "layout(location=2) in vec2 inUV;\n"
      "out vec2 aUV;"
      "uniform mat4 uModel;\n"
      "void main() {\n"
      "   gl_Position = uModel * vec4(inPos / 10, 1.0);\n"
      "   aUV = inUV;\n"
      "}\n";

  const char* fragment_source =
      "#version 330 core\n"
      "in vec2 aUV;\n"
      "out vec4 outColor;\n"
      "uniform float uTime;\n"
      "void main() {\n"
      "//   outColor = vec4(1.0, sin(uTime), 0.0, 1.0);\n"
      "   outColor = vec4(aUV, 1.0, 1.0);\n"
      "}\n";

  Shader vertex_shader(vertex_source, ShaderType::VERTEX);
  Shader fragment_shader(fragment_source, ShaderType::FRAGMENT);
  Program program(vertex_shader, fragment_shader);

  float elapsed_time = 0;

  while (!glfwWindowShouldClose(window)) {
    elapsed_time = static_cast<float>(glfwGetTime());

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    model_matrix = glm::rotate(glm::mat4(1.0), (float)glfwGetTime(),
                               glm::vec3(0.0, 1.0, 0.0));

    program.bind();
    program.set_uniform<float>("uTime", elapsed_time);
    program.set_uniform<glm::mat4>("uModel", model_matrix);

    mesh.bind();

    glDrawElements(GL_TRIANGLES, mesh.index_count(), GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, mesh.vertex_count());

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}