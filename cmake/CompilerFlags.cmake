option(ENABLE_DEBUG              "Enable debug symbols (-g)"            ON)
option(ENABLE_WARNINGS           "Enable compiler warnings"             ON)
option(ENABLE_WARNINGS_AS_ERRORS "Treat warnings as errors"             ON)
option(ENABLE_ASAN               "Enable AddressSanitizer"              OFF)
option(ENABLE_UBSAN              "Enable UndefinedBehaviorSanitizer"    OFF)
option(ENABLE_TSAN               "Enable ThreadSanitizer"               OFF)
option(ENABLE_MSAN               "Enable MemorySanitizer"               OFF)
option(ENABLE_COVERAGE           "Enable code coverage"                 OFF)
option(ENABLE_LTO                "Enable Link Time Optimization"        OFF)
option(ENABLE_OPTIMIZATIONS      "Enable optimizations (-O2/-O3)"       OFF)
option(ENABLE_FAST_MATH          "Enable fast math optimizations"       OFF)
option(ENABLE_STACK_PROTECTION   "Enable stack protection"              OFF)

set(COMMON_COMPILE_FLAGS    "")
set(COMMON_LINK_FLAGS       "")

# Debug symbols
if(ENABLE_DEBUG)
    list(APPEND COMMON_COMPILE_FLAGS "-g")
endif()

# Warnings
if(ENABLE_WARNINGS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        list(APPEND COMMON_COMPILE_FLAGS
            "-Wall"
            "-Wextra"
            "-Wpedantic"
            "-Wshadow"
            "-Wformat=2"
            "-Wunused"
        )
    elseif(MSVC)
        list(APPEND COMMON_COMPILE_FLAGS "/W4")
    endif()
endif()

# Warnings as errors
if(ENABLE_WARNINGS_AS_ERRORS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        list(APPEND COMMON_COMPILE_FLAGS "-Werror")
    elseif(MSVC)
        list(APPEND COMMON_COMPILE_FLAGS "/WX")
    endif()
endif()

# AddressSanitizer
if(ENABLE_ASAN)
    list(APPEND COMMON_COMPILE_FLAGS "-fsanitize=address" "-fno-omit-frame-pointer")
    list(APPEND COMMON_LINK_FLAGS "-fsanitize=address")
    message(STATUS "AddressSanitizer enabled")
endif()

# UndefinedBehaviorSanitizer
if(ENABLE_UBSAN)
    list(APPEND COMMON_COMPILE_FLAGS "-fsanitize=undefined" "-fno-omit-frame-pointer")
    list(APPEND COMMON_LINK_FLAGS "-fsanitize=undefined")
    message(STATUS "UndefinedBehaviorSanitizer enabled")
endif()

# ThreadSanitizer
if(ENABLE_TSAN)
    if(ENABLE_ASAN)
        message(FATAL_ERROR "AddressSanitizer and ThreadSanitizer cannot be used together")
    endif()
    list(APPEND COMMON_COMPILE_FLAGS "-fsanitize=thread")
    list(APPEND COMMON_LINK_FLAGS "-fsanitize=thread")
    message(STATUS "ThreadSanitizer enabled")
endif()

# MemorySanitizer
if(ENABLE_MSAN)
    if(ENABLE_ASAN OR ENABLE_TSAN)
        message(FATAL_ERROR "MemorySanitizer cannot be combined with other sanitizers")
    endif()
    list(APPEND COMMON_COMPILE_FLAGS "-fsanitize=memory" "-fno-omit-frame-pointer")
    list(APPEND COMMON_LINK_FLAGS "-fsanitize=memory")
    message(STATUS "MemorySanitizer enabled")
endif()

# Code coverage
if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        list(APPEND COMMON_COMPILE_FLAGS "--coverage" "-fprofile-arcs" "-ftest-coverage")
        list(APPEND COMMON_LINK_FLAGS "--coverage")
    endif()
    message(STATUS "Code coverage enabled")
endif()

# Optimizations
if(ENABLE_OPTIMIZATIONS)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        list(APPEND COMMON_COMPILE_FLAGS "-O3")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
        list(APPEND COMMON_COMPILE_FLAGS "-O0")
    else()
        list(APPEND COMMON_COMPILE_FLAGS "-O2")
    endif()
endif()

# Fast math
if(ENABLE_FAST_MATH)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        list(APPEND COMMON_COMPILE_FLAGS "-ffast-math")
    endif()
endif()

# Stack protection
if(ENABLE_STACK_PROTECTION)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        list(APPEND COMMON_COMPILE_FLAGS "-fstack-protector-strong")
    endif()
endif()

# Link Time Optimization
if(ENABLE_LTO)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        list(APPEND COMMON_COMPILE_FLAGS "-flto")
        list(APPEND COMMON_LINK_FLAGS "-flto")
    endif()
    message(STATUS "Link Time Optimization enabled")
endif()

function(apply_compiler_flags)
    # Parse arguments: apply_compiler_flags(target1 target2 ...)
    foreach(target ${ARGN})
        if(TARGET ${target})
            target_compile_options(${target} PRIVATE ${COMMON_COMPILE_FLAGS})
            target_link_options(${target} PRIVATE ${COMMON_LINK_FLAGS})
            message(STATUS "Applied compiler flags to target: ${target}")
        else()
            message(WARNING "Target ${target} does not exist")
        endif()
    endforeach()
endfunction()

message(STATUS "=== Compiler Flags Configuration ===")
message(STATUS "Debug symbols:       ${ENABLE_DEBUG}")
message(STATUS "Warnings:            ${ENABLE_WARNINGS}")
message(STATUS "Warnings as errors:  ${ENABLE_WARNINGS_AS_ERRORS}")
message(STATUS "AddressSanitizer:    ${ENABLE_ASAN}")
message(STATUS "UBSanitizer:         ${ENABLE_UBSAN}")
message(STATUS "ThreadSanitizer:     ${ENABLE_TSAN}")
message(STATUS "MemorySanitizer:     ${ENABLE_MSAN}")
message(STATUS "Code coverage:       ${ENABLE_COVERAGE}")
message(STATUS "Optimizations:       ${ENABLE_OPTIMIZATIONS}")
message(STATUS "Fast math:           ${ENABLE_FAST_MATH}")
message(STATUS "Stack protection:    ${ENABLE_STACK_PROTECTION}")
message(STATUS "LTO:                 ${ENABLE_LTO}")
message(STATUS "====================================")
