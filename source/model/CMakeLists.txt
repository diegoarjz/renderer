set(MODEL_SOURCES
    "model.cpp"
    "render_model.cpp"
    )

add_library(model ${MODEL_SOURCES})

target_compile_features(
    model
    PRIVATE
        cxx_std_14
)

target_link_libraries(
    model
    PRIVATE
        transformations
        geometry
)

target_include_directories(
    model
    PRIVATE
        "${CMAKE_SOURCE_DIR}/source"
)


