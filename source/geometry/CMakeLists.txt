set(GEOMETRY_SOURCES
    "element_data_source.cpp"
    "geometry_base.cpp"
    "load_geometry.cpp"
    "render_geometry.cpp"
    "vertex.cpp"
    "vertex_data_source.cpp"
    )

add_library(geometry ${GEOMETRY_SOURCES})

target_compile_features(
    geometry
    PRIVATE
        cxx_std_14
)

target_link_libraries(
    geometry
    PRIVATE
        common
        glfw3
        ${OPENGL_gl_LIBRARY}
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${CORE_VIDEO_LIBRARY}
)

target_include_directories(
    geometry
    PRIVATE
        "${CMAKE_SOURCE_DIR}/source"
)

