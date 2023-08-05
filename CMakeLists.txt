cmake_minimum_required(VERSION 3.17)
project(game)

set (CMAKE_CXX_STANDARD 17)

set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets/")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/")
set(MODULES_DIR "${CMAKE_SOURCE_DIR}/modules/")
set(GLAD_SOURCES "${MODULES_DIR}/glad/glad.c")

set(COMMON_COMPILE_DEFINITIONS ASSETS=${ASSETS_DIR})
set(COMMON_INCLUDE_DIRECTORIES 
    "${SOURCE_DIR}"
    "${MODULES_DIR}"
    "${MODULES_DIR}/assimp/include/"
    "${MODULES_DIR}/glfw/include/"
    "${MODULES_DIR}/glm/"
    "${MODULES_DIR}/"
)

add_subdirectory(src/)
add_subdirectory(modules/)
# add_subdirectory(tests/)