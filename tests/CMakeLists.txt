add_subdirectory(test_utils)
add_subdirectory(open_window)
add_subdirectory(triangle)
add_subdirectory(write_image)

file(COPY regression_tests DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(GTest REQUIRED)
add_subdirectory(unit_tests)
