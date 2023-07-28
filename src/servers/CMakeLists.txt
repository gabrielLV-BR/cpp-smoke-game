add_library(servers program_server.cpp)

target_link_libraries(servers renderer)
target_compile_definitions(servers PRIVATE ${COMMON_COMPILE_DEFINITIONS})
target_include_directories(servers PRIVATE ${COMMON_INCLUDE_DIRECTORIES})