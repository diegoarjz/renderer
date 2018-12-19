set(TRANSFORMATION_SOURCES
    "transformation.cpp"
    )

add_library(transformations ${TRANSFORMATION_SOURCES})

target_compile_features(
    transformations
    PRIVATE
        cxx_std_14
)

target_link_libraries(
    transformations
    PRIVATE
        common
)

target_include_directories(
    transformations
    PRIVATE
        "${CMAKE_SOURCE_DIR}/source"
)


