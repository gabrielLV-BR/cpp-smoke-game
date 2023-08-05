add_library(servers server.cpp)

target_compile_definitions(servers PRIVATE ${COMMON_COMPILE_DEFINITIONS})
target_include_directories(servers PRIVATE ${COMMON_INCLUDE_DIRECTORIES})