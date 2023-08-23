add_library(renderer renderer.cpp buffer.cpp material.cpp mesh.cpp program.cpp shader.cpp texture.cpp)

target_link_libraries(renderer utils math)
target_compile_definitions(renderer PRIVATE ${COMMON_COMPILE_DEFINITIONS})
target_include_directories(renderer PUBLIC ${COMMON_INCLUDE_DIRECTORIES})