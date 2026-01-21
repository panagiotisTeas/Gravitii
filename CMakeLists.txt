cmake_minimum_required(VERSION 3.22)

project(Gravitii
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

################################
# cmake files
################################

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(CompilerFlags)

################################
# Gravitii library
################################

add_library(Gravitii)

target_sources(Gravitii
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gravitii/app.c
)

target_include_directories(Gravitii
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gravitii
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/raylib
)

target_link_libraries(Gravitii
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external/raylib/libraylib.a
)

target_link_libraries(Gravitii
    PRIVATE
        m pthread dl rt GL
)

################################
# main executable
################################

add_executable(Gravitii-main)

target_sources(Gravitii-main
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
)

target_link_libraries(Gravitii-main
    PRIVATE
        Gravitii
)

################################
# apply compiler and linker flags
################################

apply_compiler_flags(Gravitii Gravitii-main)