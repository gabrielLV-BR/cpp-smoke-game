add_library(utils color.cpp file.cpp)

target_compile_definitions(utils PRIVATE ${COMMON_COMPILE_DEFINITIONS})
target_include_directories(utils PRIVATE ${COMMON_INCLUDE_DIRECTORIES})