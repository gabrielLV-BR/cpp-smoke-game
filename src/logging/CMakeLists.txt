add_library(logging logger.cpp)

target_compile_definitions(logging PRIVATE ${COMMON_COMPILE_DEFINITIONS})
target_include_directories(logging PRIVATE ${COMMON_INCLUDE_DIRECTORIES})