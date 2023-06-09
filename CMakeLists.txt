cmake_minimum_required(VERSION 3.17)
project(game)

set("SOURCE_DIR" "${CMAKE_SOURCE_DIR}/src/")
set("MODULES_DIR" "${CMAKE_SOURCE_DIR}/modules/")

add_executable(
    ${PROJECT_NAME}

    src/main.cpp    
    src/math/camera.cpp
    src/math/vector.cpp
    src/renderer/texture.cpp
    src/renderer/shader.cpp
    src/renderer/mesh.cpp
    src/renderer/material.cpp
    src/loaders/obj_loader.cpp
    src/servers/program_server.cpp
    src/utils/file.cpp

    modules/glad/glad.c
)

target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS="${CMAKE_SOURCE_DIR}/assets/")
target_include_directories(${PROJECT_NAME} PRIVATE "${SOURCE_DIR}" "${MODULES_DIR}")

add_subdirectory(modules/)
add_subdirectory(tests/)