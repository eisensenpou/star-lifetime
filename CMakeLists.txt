cmake_minimum_required(VERSION 3.15)
project(universal_stockflow_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell compiler where to look for headers
include_directories(include)

# Build executable from source files
add_executable(stockflow
    src/main.cpp
    src/integrators.cpp
    src/differentiators.cpp
    src/errors.cpp
    src/stellar_models.cpp
    src/finance.cpp
    src/util.cpp
    src/stellar_mass.cpp
    src/star.cpp
)
