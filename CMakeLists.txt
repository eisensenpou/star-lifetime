cmake_minimum_required(VERSION 3.15)
project(universal_stockflow_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===============================
# Directory setup
# ===============================
set(SRC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(RES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")

# ===============================
# Source file collection
# ===============================
file(GLOB_RECURSE SRC_FILES
    "${SRC_ROOT}/main.cpp"
    "${SRC_ROOT}/num_analysis/*.cpp"
    "${SRC_ROOT}/physics/*.cpp"
    "${SRC_ROOT}/*.cpp"
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

# ===============================
# Output info
# ===============================
message(STATUS "Configured target: star_lifetime")
message(STATUS "Using C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Source root: ${SRC_ROOT}")
message(STATUS "Include root: ${INC_ROOT}")
