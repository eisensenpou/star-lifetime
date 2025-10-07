# Source Code (`src/`)

## Overview
This directory contains all C++ source (`.cpp`) files implementing the logic of the **Universal Stockflow Project**.  
Each module handles a specific subsystem such as numerical integration, stellar physics, or finance.

## Modules
| File | Purpose |
|------|----------|
| **main.cpp** | Entry point of the executable. Parses input, initializes models, and runs simulations. |
| **star_physics.cpp** | Unified implementation of the Star class, stellar models, and astrophysical constants. Consolidates former modules `star.cpp`, `stellar_mass.cpp`, and `stellar_models.cpp`. |
| **integrators.cpp** | Numerical integration algorithms (e.g., trapezoid and Simpson’s rule). |
| **differentiators.cpp** | Numerical differentiation methods (forward, backward, central). |
| **errors.cpp** | Error estimation utilities for integration/differentiation. |
| **finance.cpp** | Economic/finance simulations (money supply models). |
| **util.cpp** | General utility functions (logging, formatting, etc.). |

## Notes
- All `.cpp` files include their corresponding headers from the `/include` folder.
- Each source file begins with a standardized documentation banner:
  ```
  /************************
   * Author : Sinan Demir
   * Date   : YYYY-MM-DD
   * File   : filename.cpp
   * Purpose: Short description...
   ************************/
  ```
- Follow the same style when adding new modules.
