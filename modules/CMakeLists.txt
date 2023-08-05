add_subdirectory(glfw)
add_subdirectory(glm)

set(BUILD_SHARED_LIBS ON)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_INSTALL OFF)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF)
set(ASSIMP_BUILD_OBJ_IMPORTER ON)

add_subdirectory(assimp)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glm assimp)