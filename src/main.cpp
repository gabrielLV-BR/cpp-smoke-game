#include <iostream>
#include <cstdint>

#include "renderer/buffer.hpp"
#include "renderer/mesh.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

void check_compilation_status(uint32_t shader) {
    int success;
    char log[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, log);
        std::cout << "[ERROR COMPILING SHADER!]\t" << log << "\n";
    }
}

int main() {
    glfwInit();

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    GLFWwindow* window = glfwCreateWindow(500, 500, "hi", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == GLFW_FALSE) {
        std::cerr << "Error loading OpenGL!\n";
        return -1;
    }

    uint32_t vao, vbo, ebo;

    float vertices[] = {
        -0.5, -0.5, 0.0,
        0.0, 0.5, 0.0,
        0.5, -0.5, 0.0
    };

    uint32_t indices[] = {
        0, 1, 2
    };

    // vao creation
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // shader creation

    const char* vertex_source = 
        "#version 330 core\n"
        "layout(location=0) in vec3 inPos;\n"
        "void main() {\n"
        "   gl_Position = vec4(inPos, 1.0);\n"
        "}\n";

    const char* fragment_source =
        "#version 330 core\n" 
        "out vec4 outColor;\n"
        "void main() {\n"
        "   outColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

    uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);

    uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);

    check_compilation_status(vertex_shader);
    check_compilation_status(fragment_shader);

    uint32_t program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    // glDeleteShader(vertex_shader);
    // glDeleteShader(fragment_shader);

    while(!glfwWindowShouldClose(window)) {

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}