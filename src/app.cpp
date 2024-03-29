#include "app.hpp"

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

#include "loaders/mesh_loader.hpp"
#include "loaders/texture_loader.hpp"
#include "math/vector.hpp"
#include "servers/server.hpp"
#include "utils/color.hpp"
#include "utils/file.hpp"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#ifndef ASSETS
#define ASSETS ""
#endif

App::App(uint32_t width, uint32_t height, const char* title)
    : width(width), height(height), title(title) {
    CreateWindowing();
    InitializeRendering();
}

void App::CreateWindowing() {
    if (glfwInit() != GLFW_TRUE) {
        throw std::runtime_error("[ERROR] Error initializing GLFW");
    }

    // TODO detect available versions (somehow)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(width, height, title, 0, 0);

    if (window == NULL) {
        throw std::runtime_error("[ERROR] Error creating window");
    }

    glfwSetWindowUserPointer(window, this);

    // resize callback
    glfwSetWindowSizeCallback(window, [](auto window, auto width, auto height) {
        auto app = static_cast<App*>(glfwGetWindowUserPointer(window));

        app->HandleResizing(width, height);
    });

    // keyboard input
    glfwSetKeyCallback(
        window, [](auto window, int key, int scancode, int action, int mods) {
            auto app = static_cast<App*>(glfwGetWindowUserPointer(window));
            app->HandleKeyInput(key, action, mods);
        });

    // mouse motion input
    glfwSetCursorPosCallback(window, [](auto window, double x, double y) {
        auto app = static_cast<App*>(glfwGetWindowUserPointer(window));
        app->HandleMouseMotionInput(
            glm::vec2(static_cast<float>(x), static_cast<float>(y)));
    });

    // mouse button input
    glfwSetMouseButtonCallback(
        window, [](auto window, int mouse_button, int action, int mods) {
            auto app = static_cast<App*>(glfwGetWindowUserPointer(window));
            app->HandleMouseButtonInput(mouse_button, action, mods);
        });
}

void App::InitializeRendering() {
    glfwMakeContextCurrent(window);

    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) != GL_TRUE) {
        throw std::runtime_error("[ERROR] Error loading OpenGL");
    }

    glViewport(0, 0, width, height);
}

void App::SetupSystems() {
    //
}

App::~App() {}

void App::Run() {
    Model model;
    MeshLoader mesh_loader(mesh_server);

    {
        mesh_loader.LoadFromFile(ASSETS"models/suzanne.obj");
        mesh_loader.LoadFromFile(ASSETS"models/suzanneballer.obj");
        // model = Model{.meshes = meshes, .transform = Transform::identity()};
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void App::Update() {}
void App::Render() {}

// input handlers

void App::HandleKeyInput(int key, int action, int mods) {}

void App::HandleMouseMotionInput(glm::vec2 mouse_position) {}

void App::HandleMouseButtonInput(int mouse_button, int action, int mods) {}

void App::HandleResizing(int new_width, int new_height) {
    this->width = new_width;
    this->height = new_height;
    glViewport(0, 0, width, height);
}
