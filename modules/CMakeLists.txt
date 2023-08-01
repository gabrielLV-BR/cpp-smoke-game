add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(assimp)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glm assimp)