add_library(math camera.cpp vector.cpp)

target_compile_definitions(math PRIVATE ${COMMON_COMPILE_DEFINITIONS})
target_include_directories(math PRIVATE ${COMMON_INCLUDE_DIRECTORIES})