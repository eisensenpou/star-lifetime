cmake_minimum_required(VERSION 3.15)

# ===============================
# Project metadata
# ===============================
project(star_lifetime VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ===============================
# Directory setup
# ===============================
set(SRC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(RES_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/resources")

# ===============================
# Source file collection
# ===============================
file(GLOB_RECURSE SRC_FILES
    "${SRC_ROOT}/main.cpp"
    "${SRC_ROOT}/num_analysis/*.cpp"
    "${SRC_ROOT}/physics/*.cpp"
    "${SRC_ROOT}/util.cpp"
    "${SRC_ROOT}/finance.cpp"
    "${RES_DIR}/app_icon.rc"
)

# ===============================
# Executable target
# ===============================
add_executable(star_lifetime ${SRC_FILES})

# ===============================
# Include directories
# ===============================
target_include_directories(star_lifetime
    PUBLIC
        ${INC_ROOT}
        ${INC_ROOT}/num_analysis
        ${INC_ROOT}/physics
)

# ===============================
# Compiler warnings / options
# ===============================
if (MSVC)
    target_compile_options(star_lifetime PRIVATE /W4 /permissive-)
else()
    target_compile_options(star_lifetime PRIVATE -Wall -Wextra -pedantic)
endif()

# Optional: Color diagnostics for GCC/Clang
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-fdiagnostics-color=always)
endif()

# ===============================
# Install rules
# ===============================
install(TARGETS star_lifetime DESTINATION bin)

# ===============================
# Output info
# ===============================
message(STATUS "Configured target: star_lifetime")
message(STATUS "Using C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Source root: ${SRC_ROOT}")
message(STATUS "Include root: ${INC_ROOT}")
message(STATUS "Binary output: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
