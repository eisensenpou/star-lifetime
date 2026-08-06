# Python API roadmap

---

## v1.0:
- compute_stellar_fuel_lifetime

## v1.1:
- compute_stellar_luminosity
- compute_stellar_age_limit (if applicable)

## v1.2:
- mass_solar_to_kg
- luminosity_solar_to_watts
- years_to_seconds

## v2.0+:
- advanced numerical utilities (explicit, opt-in)

### Never exposed:
- stateful classes
- mutation
- simulation workflows

---

## Example Pybind wrapper
```cpp
// bindings.cpp
#include <pybind11/pybind11.h>
#include "star_physics.h"

namespace py = pybind11;

PYBIND11_MODULE(stellar_bindings, m) {
    m.doc() = "Python bindings for stellar lifetime calculations";

    m.def(
        "stellar_lifetime",
        &physics::stellar_lifetime,
        "Compute stellar lifetime from mass (in solar masses)"
    );
}
```

```bash
Python User
   |
   |  (calls a pure function)
   v
Python API Function
   |
   |  (validate inputs, no physics)
   v
Binding Layer (pybind11)
   |
   |  (translate Python → C++)
   v
C++ Public API (physics::stellar)
   |
   |  (runs physics + numerics)
   v
C++ Core Engine
   |
   |  (returns values or errors)
   v
Binding Layer
   |
   |  (translate C++ → Python)
   v
Python User (gets results)
```

## example

```bash
+--------------------------------------------------+
| Python User Code                                 |
|                                                  |
|  star_lifetime.compute_fuel_lifetime(mass=10)    |
|                                                  |
+--------------------------+-----------------------+
                           |
                           v
+--------------------------------------------------+
| Python Public API (what you document)            |
|                                                  |
|  - function-centric                              |
|  - stateless                                     |
|  - explicit units                                |
|                                                  |
+--------------------------+-----------------------+
                           |
                           v
+--------------------------------------------------+
| Binding Layer (pybind11)                         |
|                                                  |
|  - argument translation                          |
|  - error translation                             |
|  - NO physics                                    |
|  - NO state                                      |
|                                                  |
+--------------------------+-----------------------+
                           |
                           v
+--------------------------------------------------+
| C++ Public Interface (approved headers only)     |
|                                                  |
|  physics::stellar                                |
|  physics::constants                              |
|  num_analysis                                    |
|                                                  |
+--------------------------+-----------------------+
                           |
                           v
+--------------------------------------------------+
| C++ Core Engine (internal)                       |
|                                                  |
|  - Star objects                                  |
|  - numerical solvers                             |
|  - physics models                                |
|                                                  |
+--------------------------------------------------+
```