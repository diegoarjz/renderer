set(COMMON_SOURCES
        "version.cpp"
        "assertions.cpp"
        "logger.cpp"
        #"profiler.cpp"
        "utils.cpp"
    )

add_library(common ${COMMON_SOURCES})

target_compile_definitions(
    common
    PRIVATE
        -DRENDERER_VERSION=\"${Renderer_VERSION}\"
        -DRENDERER_BUILD_NUMBER=\"${Renderer_BUILD_NUMBER}\"
        -DRENDERER_BUILD_DATE=\"${Renderer_BUILD_DATE}\"
        "$<$<CONFIG:DEBUG>:DEBUG>"
)

target_compile_features(
    common
    PRIVATE
        cxx_std_14
        cxx_lambdas
        cxx_constexpr
)

