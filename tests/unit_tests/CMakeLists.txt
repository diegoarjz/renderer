set(TEST_SOURCES
    "main.cpp"
    )

add_executable(unit_tests ${TEST_SOURCES})

set_target_properties(
    unit_tests
    PROPERTIES 
        COMPILE_FLAGS ${COMPILE_FLAGS} "-Wno-gnu-zero-variadic-macro-arguments"
)

target_compile_features(
    unit_tests
    PRIVATE
        cxx_std_14
        cxx_constexpr
        cxx_relaxed_constexpr
)

target_compile_options(
    unit_tests
    PRIVATE
        -Wall
        -Werror
        -pedantic-errors
)

target_include_directories(
    unit_tests
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/source>
    PRIVATE
        ${CMAKE_SOURCE_DIR}/source
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(
    unit_tests
    PRIVATE
        renderer
        pthread
        gmock
        gtest
)

add_test(NAME unit_tests COMMAND unit_tests)

