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

#include "loaders/model_loader.hpp"
#include "math/vector.hpp"
#include "servers/program_server.hpp"
#include "utils/color.hpp"
#include "utils/file.hpp"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

App::App(uint32_t width, uint32_t height, char* title) {
    _CreateWindowing();
    _InitializeRendering();
}

void App::_CreateWindowing() {
    if (glfwInit() != GLFW_TRUE) {
        throw std::runtime_error("[ERROR] Error initializing GLFW");
    }

    // TODO detect available versions (somehow)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
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

void App::_InitializeRendering() {
    glfwMakeContextCurrent(window);
}

App::~App() {}

void App::Run() {}

void App::Update() {}
void App::Render() {}

// input handlers

void App::HandleKeyInput(int key, int action, int mods) {}

void App::HandleMouseMotionInput(glm::vec2 mouse_position) {}

void App::HandleMouseButtonInput(int mouse_button, int action, int mods) {}

void App::HandleResizing(int new_width, int new_height) {
    this->width = new_width;
    this->height = new_height;
}
