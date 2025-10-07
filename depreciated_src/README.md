# Deprecated Source (`deprecated_src/`)

## Overview
This folder preserves **legacy implementations** that were replaced by the unified module `star_physics.{h,cpp}` in October 2025.  
These files are no longer built by CMake but are retained for reference, validation, and version comparison.

## Contents
| File | Original Purpose |
|------|------------------|
| **star.cpp / star.h** | Defined the `Star` class before consolidation. |
| **stellar_mass.cpp / .h** | Contained the mass–luminosity–lifetime relations and constants. |
| **stellar_models.cpp / .h** | Defined toy luminosity functions and numerical lifetime estimators. |

## Reason for Deprecation
The older design caused redundant includes and inconsistent naming between modules.  
They were merged into a single, maintainable source under `src/star_physics.cpp` with unified documentation and error handling.

## Usage Notes
- These files **should not be compiled**.
- They remain available for archival comparison or rollback.
- The replacement is fully backward-compatible through `#include "star_physics.h"`.

## Version Tag
Consolidation performed by **Sinan Demir** on **2025-10-07**.
