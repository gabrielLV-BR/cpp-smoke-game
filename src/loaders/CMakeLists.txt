add_library(loaders obj_loader.cpp)

target_link_libraries(loaders math renderer)
target_compile_definitions(loaders PRIVATE ${COMMON_COMPILE_DEFINITIONS})
target_include_directories(loaders PRIVATE ${COMMON_INCLUDE_DIRECTORIES})