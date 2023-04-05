cmake_minimum_required(VERSION 3.17)
project(game)

set("SOURCE_DIR" "${CMAKE_SOURCE_DIR}/src/")
set("MODULES_DIR" "${CMAKE_SOURCE_DIR}/modules/")

add_subdirectory(modules/glfw)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp    
    modules/glad/glad.c
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_include_directories(${PROJECT_NAME} PRIVATE "${SOURCE_DIR}/" "${MODULES_DIR}")

add_subdirectory(tests/)