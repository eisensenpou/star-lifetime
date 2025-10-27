# star-lifetime  

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)  
[![Build Status](https://img.shields.io/github/actions/workflow/status/eisensenpou/star-lifetime/ci.yml?branch=main)](https://github.com/eisensenpou/star-lifetime/actions)  

## Description  
**star-lifetime** is a C++ library and command‐line tool to estimate the lifetime of stars given their mass (in solar masses) and optionally metallicity or other physical parameters. Its goal is to provide a compact, easy‐to‐use implementation for educational or research use, with clear code and minimal dependencies.

## Features  
- Fast computation of main‐sequence lifetime (and optionally other stages) based on stellar parameters.  
- Support for different metallicities or compositions (if configured).  
- Command‐line interface for quick use and library interface for integration in other code.  
- Unit tests and example usage to validate correctness.  
- Modular design to allow extension or substitution of physical models.

## Getting Started  

### Prerequisites  
- A C++17‐compatible compiler (GCC, Clang, MSVC)  
- CMake version ≥ 3.x (for build orchestration)  
- Git (to clone the repository)  
- (Optional) Any third-party libraries or dependencies documented in `CMakeLists.txt`  
- Tested on Linux/macOS; Windows support may require minor adjustments.

### Installing / Building  
1. Clone the repository  
   ```bash
   git clone https://github.com/eisensenpou/star-lifetime.git  
   cd star-lifetime  
   ```  
2. Create and enter a build directory  
   ```bash
   mkdir build && cd build  
   cmake ..  
   make  
   ```  
   For a release build:  
   ```bash
   cmake .. -DCMAKE_BUILD_TYPE=Release  
   make  
   ```  
3. Run tests (if present)  
   ```bash
   make test  
   ```  
4. (Optional) Install the library/tool globally  
   ```bash
   make install  
   ```  
   By default, this installs into `/usr/local` (or as configured).

### Usage  
#### Command‐line mode  
```bash
./star-lifetime --mass 1.0 --metallicity 0.014  
# Example output: Lifetime = 10.0 Gyr  
```  
Additional parameters may include `--stage main‐sequence`, `--units Gyr`, etc.

#### Library mode  
In your C++ code:  
```cpp
#include "StarLifetime.hpp"

int main() {
    StarLifetime sl(/*mass=*/1.0, /*metallicity=*/0.014);
    double lifetimeGyr = sl.compute();
    std::cout << "Lifetime: " << lifetimeGyr << " Gyr\n";
    return 0;
}
```  

### Examples  
- Estimate the lifetime of a 2 M☉ star at solar metallicity:  
  ```bash
  ./star-lifetime --mass 2.0 --metallicity 0.014  
  # → Lifetime: ~1.0 Gyr  
  ```  
- Use the library interface in your application (see above) to embed lifetime calculations.

## Project Structure  
```
/star-lifetime/
 ├── src/                 # Implementation files  
 ├── include/             # Public headers  
 ├── tests/               # Unit tests  
 ├── examples/            # Example usage code  
 ├── CMakeLists.txt       # Build configuration  
 ├── README.md            # You are reading this  
 └── LICENSE              # MIT license  
```

## Contributing  
Contributions are welcome ! Please follow these steps:  
1. Fork the repository  
2. Create a feature branch (`git checkout -b feature/your-feature`)  
3. Commit your changes (`git commit -am 'Add feature X'`)  
4. Push to your branch (`git push origin feature/your-feature`)  
5. Create a Pull Request on GitHub  
Please include unit tests for new functionality, update documentation if you add or change behavior, and follow the code style in the project.

## License  
This project is licensed under the [MIT License](LICENSE) — see the LICENSE file for full details.

## Authors & Acknowledgments  
- **Eisen Senpou** — original creator, design & implementation  
- Thank you to all contributors who have submitted issues, pull requests, improvements.  
- Inspired by standard stellar-evolution theory and pedagogical astronomy frameworks.

## Roadmap / Future Work  
- Extend support to post‐main‐sequence lifetimes (giant branch, supernova, white dwarf phases)  
- Add wrappers for other languages (Python, Julia) for easier integration in data science workflows  
- Improve the physical model: add effects of rotation, binary interaction, differential metallicity, mass loss  
- Provide a web‐based API or a dockerized command-line version for easier deployment  
- Add more extensive benchmarking, validation against stellar modelling data sets  

---

Thank you for using **star-lifetime** and happy calculating!  
