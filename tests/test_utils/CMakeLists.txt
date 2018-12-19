set(sources
    "basic_test_application.cpp"
)

add_library(test_utils ${sources})

target_compile_features(
    test_utils
    PRIVATE
        cxx_std_14
)

target_include_directories(
    test_utils
    PRIVATE
        "${CMAKE_SOURCE_DIR}/source"
)

target_link_libraries(
    test_utils
    image
    geometry
    renderer
)
