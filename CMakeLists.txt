cmake_minimum_required(VERSION 3.15)
project(universal_stockflow_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===============================
# Source and include directories
# ===============================
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(RES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")

# ===============================
# Source files
# ===============================
set(SRC_FILES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/integrators.cpp
    ${SRC_DIR}/differentiators.cpp
    ${SRC_DIR}/errors.cpp
    ${SRC_DIR}/finance.cpp
    ${SRC_DIR}/util.cpp
    ${SRC_DIR}/star_physics.cpp   
    ${RES_DIR}/app_icon.rc
)

# ===============================
# Executable target
# ===============================
add_executable(star_lifetime ${SRC_FILES})

# Include directory for headers
target_include_directories(star_lifetime
    PUBLIC
        ${SRC_DIR}               
        ${CMAKE_CURRENT_SOURCE_DIR}/include
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
