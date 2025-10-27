# Star Lifetime Project

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

## Overview
**Star Lifetime** is a C++ project developed by **Sinan Demir** for a **Calculus II course project**.  
The goal is to model and compute the lifetime of stars using mathematical and physical principles, implemented with structured numerical analysis and modular namespaces.

This project combines **numerical methods**, **astrophysical modeling**, and **computational design** into a clean, educational, and extensible C++ framework.

---

## 🧠 Project Purpose
The program estimates **stellar lifetime**, luminosity, and fuel consumption based on stellar mass and physical constants.  
It is designed to demonstrate the application of integral and differential calculus in physics, particularly in the study of stellar evolution.

---

## ⚙️ Namespaces & Structure

### **1. `num::analysis`**
Provides core numerical methods used in scientific computations.
- `integration` — Numerical integration algorithms (Trapezoidal, Simpson, etc.)
- `differentiation` — Numerical differentiation (finite differences)
- `errors` — Error propagation and accuracy estimation
- `ode` — (planned) Ordinary Differential Equation solvers

### **2. `physics::stellar`**
Implements core stellar physics models.
- `fuel_stock(double M)` — Estimates the hydrogen fuel available for fusion (Joules)
- `luminosity(double M)` — Calculates luminosity in watts
- `lifetime(double M)` — Estimates stellar lifetime in years
- `Star` class — Encapsulates stellar properties and computed parameters

### **3. `physics::constants`**
Holds universal and astrophysical constants (e.g., speed of light squared `C2`, energy conversion efficiency `ETA`, etc.).

---

## 🧩 Example API Usage

```cpp
#include "physics/star_physics.h"
#include <iostream>
using namespace physics::stellar;

int main() {
    double mass = 2.0; // Solar masses
    double L = luminosity(mass);
    double T = lifetime(mass);

    std::cout << "Luminosity: " << L << " W\n";
    std::cout << "Lifetime: " << T << " years\n";
    return 0;
}
```

Command-line example (once compiled):
```bash
./star_lifetime --mass 2.0
# Output: Luminosity = ... W, Lifetime = ... years
```

---

## 🛠️ Build Instructions

### Requirements
- **C++17 or later**
- **CMake 3.10+**
- Works on Linux, macOS, and Windows (MSVC)

### Build Steps
```bash
git clone https://github.com/eisensenpou/star-lifetime.git
cd star-lifetime
mkdir build && cd build
cmake ..
make
```

To run:
```bash
./star_lifetime
```

---

## 📁 Project Structure
```
/star-lifetime/
 ├── src/
 │   ├── physics/
 │   │   ├── star_physics.cpp
 │   │   ├── constants.h
 │   │   └── ...
 │   ├── num_analysis/
 │   │   ├── integration.cpp
 │   │   ├── differentiation.cpp
 │   │   ├── errors.cpp
 │   │   └── ...
 │   └── main.cpp
 ├── include/
 ├── CMakeLists.txt
 ├── LICENSE
 └── README.md
```

---

## 🧪 Educational Focus
This project demonstrates:
- Applications of calculus in real-world physics.
- Numerical integration and differentiation applied to stellar models.
- How modular C++ design supports scientific computation.

---

## 🧑‍💻 Author
**Sinan Demir**  
Calculus II Project – 2025  
No external contributors.

---

## 📜 License
This project is licensed under the [MIT License](LICENSE).

---

*“Where mathematics meets the stars.”*
