#pragma once

#include <cstdint>

#include "servers/server.hpp"

#include "glm/vec2.hpp"

#include "flecs/flecs.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class App {
   private:
    uint32_t width;
    uint32_t height;
    const char* title;

    GLFWwindow* window;

    ProgramServer program_server;
    TextureServer texture_server;
    MeshServer mesh_server;

    flecs::world ecs_world;

   public:
    App(uint32_t width, uint32_t height, const char* title);
    ~App();

    void Run();

   private:
    void Update();
    void Render();

    // input handlers
    void HandleKeyInput(int key, int action, int mods);
    void HandleMouseMotionInput(glm::vec2 mouse_position);
    void HandleMouseButtonInput(int mouse_button, int action, int mods);
    void HandleResizing(int new_width, int new_height);

    void CreateWindowing();
    void InitializeRendering();
    void SetupSystems();
};
