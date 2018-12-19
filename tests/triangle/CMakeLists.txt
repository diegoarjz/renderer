set(sources
    "main.cpp"
)

add_executable(triangle ${sources})

target_compile_features(
    triangle
    PRIVATE
        cxx_std_14
)

target_include_directories(
    triangle
    PRIVATE
        "${CMAKE_SOURCE_DIR}/source"
        "${CMAKE_SOURCE_DIR}/tests/test_utils"
)

target_link_libraries(
    triangle
    renderer
    test_utils
)
