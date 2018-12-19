set(sources
    "main.cpp"
)

add_executable(open_window ${sources})

target_compile_features(
    open_window
    PRIVATE
        cxx_std_14
)

target_include_directories(
    open_window
    PRIVATE
        "${CMAKE_SOURCE_DIR}/source"
)

target_link_libraries(
    open_window
    renderer
)
