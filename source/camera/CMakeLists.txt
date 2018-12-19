set(CAMERA_SOURCES
    "camera.cpp"
    "lens.cpp"
    "set_camera_on_renderer.cpp"
    )

add_library(camera ${CAMERA_SOURCES})

target_compile_features(
    camera
    PRIVATE
        cxx_std_14
)

target_link_libraries(
    camera
    PRIVATE
        common
        glfw3
        ${OPENGL_gl_LIBRARY}
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${CORE_VIDEO_LIBRARY}
)

target_include_directories(
    camera
    PRIVATE
        "${CMAKE_SOURCE_DIR}/source"
)

