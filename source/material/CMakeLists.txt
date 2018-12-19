set(MATERIAL_SOURCES
        "shader.cpp"
        "shader_program.cpp"
        "compile_shader.cpp"
        "create_shader_program.cpp"
        "set_shader_program.cpp"
        "uniform.cpp"
    )

add_library(material ${MATERIAL_SOURCES})

target_compile_features(
    material
    PRIVATE
        cxx_std_14
        cxx_lambdas
        cxx_constexpr
)

target_link_libraries(
    material
    PRIVATE
        common
        system
        glfw3
        glew
        ${OPENGL_gl_LIBRARY}
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${CORE_VIDEO_LIBRARY}
)

target_include_directories(
    material
    PRIVATE
        "${CMAKE_SOURCE_DIR}/source"
        ${GLEW_INCLUDE_DIRS}
)


