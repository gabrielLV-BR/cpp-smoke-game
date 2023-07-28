add_subdirectory(glfw)
add_subdirectory(glm)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glm)