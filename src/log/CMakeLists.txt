add_library(log log.cpp)

target_compile_definitions(log PRIVATE ${COMMON_COMPILE_DEFINITIONS})
target_include_directories(log PRIVATE ${COMMON_INCLUDE_DIRECTORIES})