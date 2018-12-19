set(sources
    "main.cpp"
)

add_executable(write_image ${sources})

target_compile_features(
    write_image
    PRIVATE
        cxx_std_14
)

target_include_directories(
    write_image
    PRIVATE
        "${CMAKE_SOURCE_DIR}/source"
)

target_link_libraries(
    write_image
    image
)

