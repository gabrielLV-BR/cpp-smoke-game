find_package(GTest)

set("TEST_DIR" "${CMAKE_SOURCE_DIR}/")

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(obj_vec_parsing_test obj_vec_parsing_test.cpp)
target_include_directories(obj_vec_parsing_test PRIVATE "${SOURCE_DIR}")

add_test(NAME obj_vec_parsing COMMAND obj_vec_parsing_test --gtest_filter=test_case_1)