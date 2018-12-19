set(RENDERING_SOURCES
        "bindable.cpp"
        "command.cpp"
        "command_list.cpp"
        "gl_debug.cpp"
        "renderer.cpp"
        "render_pool.cpp"
    )

add_library(rendering ${RENDERING_SOURCES})

target_compile_features(
    rendering
    PRIVATE
        cxx_std_14
        cxx_lambdas
        cxx_constexpr
)

target_link_libraries(
    rendering
    PRIVATE
        common
        system
        thread
        glfw3
        glew
        ${OPENGL_gl_LIBRARY}
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${CORE_VIDEO_LIBRARY}
)

target_include_directories(
    rendering
    PRIVATE
        "${CMAKE_SOURCE_DIR}/source"
        ${GLEW_INCLUDE_DIRS}
)

