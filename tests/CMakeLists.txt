enable_testing()

find_package(GTest)

set("TEST_DIR" "${CMAKE_SOURCE_DIR}/")

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(obj_vec_parsing obj_vec_parsing.cpp)
target_link_libraries(obj_vec_parsing GTest::GTest)
target_include_directories(obj_vec_parsing PRIVATE "${SOURCE_DIR}")

add_test(obj_vec_parsing_test obj_vec_parsing)