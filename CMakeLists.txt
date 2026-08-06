cmake_minimum_required(VERSION 3.15)

# ============================================================
# Project metadata
# ============================================================
project(star_lifetime VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ============================================================
# Directory roots
# ============================================================
set(SRC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/include")

# ============================================================
# num_analysis – internal implementation (NOT binding-safe)
# ============================================================
add_library(num_analysis_internal
    ${SRC_ROOT}/num_analysis/differentiation.cpp
    ${SRC_ROOT}/num_analysis/integration.cpp
    ${SRC_ROOT}/num_analysis/errors.cpp
)

target_include_directories(num_analysis_internal
    PRIVATE
        ${INC_ROOT}
)

set_target_properties(num_analysis_internal PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_compile_features(num_analysis_internal
    PUBLIC
        cxx_std_17
)

# ============================================================
# num_analysis – public API (binding-safe surface)
# ============================================================
add_library(num_analysis_public
    ${SRC_ROOT}/num_analysis/differentiation_public.cpp
    ${SRC_ROOT}/num_analysis/integration_public.cpp
    ${SRC_ROOT}/num_analysis/errors_public.cpp
)

target_include_directories(num_analysis_public
    PUBLIC
        ${INC_ROOT}
)

set_target_properties(num_analysis_public PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_compile_features(num_analysis_public
    PUBLIC
        cxx_std_17
)

# public API depends on internal implementation
target_link_libraries(num_analysis_public
    PRIVATE
        num_analysis_internal
)

# ============================================================
# physics – public API (binding-safe surface)
# ============================================================
add_library(physics_public
    ${SRC_ROOT}/physics/star_physics.cpp
    ${SRC_ROOT}/physics/star_physics_public.cpp
)

target_include_directories(physics_public
    PUBLIC
        ${INC_ROOT}
)

set_target_properties(physics_public PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_compile_features(physics_public
    PUBLIC
        cxx_std_17
)

target_link_libraries(physics_public
    PRIVATE
        num_analysis_internal
)

# ============================================================
# util – provisional convenience API
# ============================================================
add_library(util_public
    ${SRC_ROOT}/util.cpp
)

target_include_directories(util_public
    PUBLIC
        ${INC_ROOT}
)

set_target_properties(util_public PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_compile_features(util_public
    PUBLIC
        cxx_std_17
)

# ============================================================
# Public scientific surface (contract / aggregation target)
# ============================================================
add_library(star_lifetime_core INTERFACE)

target_link_libraries(star_lifetime_core
    INTERFACE
        num_analysis_public
        physics_public
        util_public
)

# ============================================================
# CLI executable
# ============================================================
add_executable(star_lifetime
    ${SRC_ROOT}/main.cpp
)

target_link_libraries(star_lifetime
    PRIVATE
        star_lifetime_core
)

target_include_directories(star_lifetime
    PRIVATE
        ${INC_ROOT}
)

# ============================================================
# Tests
# ============================================================
add_executable(test_stellar_physics
    ${SRC_ROOT}/test_stellar_physics.cpp
)

target_link_libraries(test_stellar_physics
    PRIVATE
        physics_public
        num_analysis_internal
)

target_include_directories(test_stellar_physics
    PRIVATE
        ${INC_ROOT}
)

add_test(NAME stellar_physics_tests COMMAND test_stellar_physics)

# ============================================================
# Python bindings (subproject)
# ============================================================
add_subdirectory(python_wrapper/bindings)

# ============================================================
# Compiler warnings
# ============================================================
if (MSVC)
    target_compile_options(star_lifetime PRIVATE /W4 /permissive-)
else()
    target_compile_options(star_lifetime PRIVATE -Wall -Wextra -pedantic)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-fdiagnostics-color=always)
endif()

# ============================================================
# Install rules
# ============================================================
install(TARGETS star_lifetime DESTINATION bin)

# ============================================================
# Diagnostics
# ============================================================
message(STATUS "Configured project: star_lifetime")
message(STATUS "Using C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Source root: ${SRC_ROOT}")
message(STATUS "Include root: ${INC_ROOT}")
message(STATUS "Binary output: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")