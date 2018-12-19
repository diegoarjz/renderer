set(THREAD_SOURCES
        "auto_reset_event.cpp"
        "thread.cpp"
    )

add_library(thread ${THREAD_SOURCES})

target_compile_features(
    thread
    PRIVATE
        cxx_std_14
)

target_link_libraries(
    thread
    PRIVATE
        common
)

target_include_directories(
    thread
    PRIVATE
        "${CMAKE_SOURCE_DIR}/source"
)

