set(IMAGE_SOURCES
    "image.cpp"
    "image_creation_params.cpp"
    "png_writer.cpp"
    )

add_library(image ${IMAGE_SOURCES})

target_compile_features(
    image
    PRIVATE
        cxx_std_14
)

target_link_libraries(
    image
    PRIVATE
        common
        png
)
