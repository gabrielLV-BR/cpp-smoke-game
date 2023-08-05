#pragma once

#include <cstdint>

class App {
   private:
    uint32_t width;
    uint32_t height;
    char* title;

   public:
    App(uint32_t width, uint32_t height, char* title);
    ~App();

    void Run();

   private:
    void Update();
    void Render();

    void _CreateWindowing();
    void _InitializeRendering();
};
