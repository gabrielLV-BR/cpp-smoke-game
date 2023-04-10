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

#include <GLFW/glfw3.h>
#include "glad/glad.h"

int main() {
  glfwInit();

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

  GLFWwindow* window = glfwCreateWindow(500, 500, "hi", nullptr, nullptr);

  glfwMakeContextCurrent(window);

  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == GLFW_FALSE) {
    std::cerr << "Error loading OpenGL!\n";
    return -1;
  }

  ObjLoaderConfig config(ASSETS "models/dice/");
  ObjLoader loader(config);

  loader.load("dice.obj");

  for (const auto& v : loader.vertex_positions) {
    std::cout << v.to_string() << "\n";
  }

  Mesh mesh(loader.vertex_positions, loader.indices);

  const char* vertex_source =
      "#version 330 core\n"
      "layout(location=0) in vec3 inPos;\n"
      "layout(location=1) in vec3 inNormal;\n"
      "layout(location=2) in vec2 inUV;"
      "void main() {\n"
      "   gl_Position = vec4(inPos, 1.0);\n"
      "}\n";

  const char* fragment_source =
      "#version 330 core\n"
      "out vec4 outColor;\n"
      "uniform float uTime;\n"
      "void main() {\n"
      "   outColor = vec4(1.0, sin(uTime), 0.0, 1.0);\n"
      "}\n";

  Shader vertex_shader(vertex_source, ShaderType::VERTEX);
  Shader fragment_shader(fragment_source, ShaderType::FRAGMENT);
  Program program(vertex_shader, fragment_shader);

  float elapsed_time = 0;

  while (!glfwWindowShouldClose(window)) {
    elapsed_time = static_cast<float>(glfwGetTime());

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    program.bind();
    program.set_uniform<float>("uTime", elapsed_time);

    mesh.bind();

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}