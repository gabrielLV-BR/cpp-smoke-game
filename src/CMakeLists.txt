add_executable(${PROJECT_NAME} main.cpp ${GLAD_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE ${COMMON_COMPILE_DEFINITIONS})
target_include_directories(${PROJECT_NAME} PRIVATE ${COMMON_COMPILE_DEFINITIONS})

add_subdirectory(utils/)
add_subdirectory(servers/)
add_subdirectory(renderer/)
add_subdirectory(math/)
add_subdirectory(loaders/)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    utils servers renderer math loaders
)