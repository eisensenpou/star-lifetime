# -------------------------------------------------
# Fetch pybind11 (build-time only dependency)
# -------------------------------------------------
include(FetchContent)

FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.11.1
)

FetchContent_MakeAvailable(pybind11)

# -------------------------------------------------
# Python module
# -------------------------------------------------
pybind11_add_module(
    star_lifetime_py
    module.cpp
)

# -------------------------------------------------
# Link against your C++ core library
# -------------------------------------------------
target_link_libraries(
    star_lifetime_py
    PRIVATE
        star_lifetime_core
)

# -------------------------------------------------
# Include paths (public headers only)
# -------------------------------------------------
target_include_directories(
    star_lifetime_py
    PRIVATE
        ${PROJECT_SOURCE_DIR}/../../include
)
