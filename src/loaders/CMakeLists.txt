add_library(loaders texture_loader.cpp model_loader.cpp mesh_loader.cpp)

target_link_libraries(loaders math renderer assimp)
target_compile_definitions(loaders PRIVATE ${COMMON_COMPILE_DEFINITIONS})
target_include_directories(loaders PRIVATE ${COMMON_INCLUDE_DIRECTORIES})