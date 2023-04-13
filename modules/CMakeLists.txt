add_subdirectory(glfw)
add_subdirectory(glm)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glm)

target_include_directories(${PROJECT_NAME} PRIVATE
 "${CMAKE_SOURCE_DIR}/glfw/include/"
 "${CMAKE_SOURCE_DIR}/glm/"
)