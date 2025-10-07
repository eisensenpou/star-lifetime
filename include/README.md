# Header Files (`include/`)

## Overview
This folder defines all **public interfaces** for the project.  
Headers declare classes, constants, and function signatures for corresponding `.cpp` files in `/src`.

## Key Headers
| File | Purpose |
|------|----------|
| **star_physics.h** | Central astrophysics interface. Defines the `Star` class, stellar constants, and modeling functions. |
| **integrators.h** | Numerical integration method declarations (Simpson, Trapezoid, etc.). |
| **differentiators.h** | Finite difference derivative approximations. |
| **errors.h** | Error propagation and precision estimation utilities. |
| **finance.h** | Defines financial/economic model structures. |
| **util.h** | Helper functions, constants, and utility macros. |

## Coding Style
- Every header starts with a Doxygen-style block comment identical in format to `.cpp` files.
- Use `#ifndef / #define / #endif` guards (not `#pragma once`) for consistency.
- Avoid defining any logic in headers unless absolutely necessary (inline or template cases).

## Integration
All headers are included using quotes:
```cpp
#include "star_physics.h"
#include "integrators.h"
```
and are found automatically by CMake via:
```cmake
target_include_directories(star_lifetime PUBLIC ${SRC_DIR} ${INC_DIR})
```
