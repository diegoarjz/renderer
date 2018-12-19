add_subdirectory(common)
add_subdirectory(system)
add_subdirectory(thread)
add_subdirectory(image)
add_subdirectory(geometry)
add_subdirectory(rendering)
add_subdirectory(material)
add_subdirectory(camera)
add_subdirectory(transformations)
add_subdirectory(model)

set(RENDERER_SOURCES
        "update_loop.cpp"
        "window.cpp"
        "window_creation_params.cpp"
    )

add_library(renderer ${RENDERER_SOURCES})

target_compile_features(
    renderer
    PRIVATE
        cxx_std_14
        cxx_lambdas
        cxx_constexpr
)

target_link_libraries(
    renderer
    PRIVATE
        common
        system
        rendering
        material
        camera
        image
        transformations
        model
        glfw3
        glew
        ${OPENGL_gl_LIBRARY}
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${CORE_VIDEO_LIBRARY}
)

target_include_directories(
    renderer
    PRIVATE
        "${CMAKE_SOURCE_DIR}/source"
        ${GLEW_INCLUDE_DIRS}
)
