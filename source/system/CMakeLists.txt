set(SYSTEM_SOURCES
        "frame_memory.cpp"
    )

add_library(system ${SYSTEM_SOURCES})

target_compile_features(
    system
    PRIVATE
        cxx_std_14
        cxx_lambdas
        cxx_constexpr
)

target_link_libraries(
    system
    PRIVATE
        common
        glfw3
        ${OPENGL_gl_LIBRARY}
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${CORE_VIDEO_LIBRARY}
)

target_include_directories(
    system
    PRIVATE
        "${CMAKE_SOURCE_DIR}/source"
)
