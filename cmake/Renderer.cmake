# Default Renderer version, build number and date
if (NOT DEFINED RENDERER_VERSION)
    set(RENDERER_VERSION "0")
endif()

if (NOT DEFINED RENDERER_BUILD_NUMBER)
    set(RENDERER_BUILD_NUMBER "0")
endif()

if (NOT DEFINED RENDERER_BUILD_DATE)
    set(RENDERER_BUILD_DATE "0/0/0")
endif()

message(STATUS "Renderer version:      ${RENDERER_VERSION}")
message(STATUS "Renderer build number: ${RENDERER_BUILD_NUMBER}")
message(STATUS "Renderer build date:   ${RENDERER_BUILD_DATE}")
