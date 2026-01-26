# Physics Constants Module

**Module Overview for `physics::constants` namespace**

---

## 📋 Module Overview

The `physics::constants` namespace provides fundamental physical and astrophysical constants used throughout the Star Lifetime project. These constants form the foundation for stellar physics calculations, ensuring consistency and accuracy across all computations.

### 🎯 **Purpose**
- Centralized constant definitions for maintainability
- Unit consistency across the project
- Reference values from established scientific literature
- Compile-time optimization using `constexpr`

### 📁 **Files**
- **Header**: `include/physics/constants.h`
- **Source**: No implementation file (header-only constants)

---

## 🔬 Physical Constants Reference

### **Fundamental Physics Constants**

| Constant | Symbol | Value | Units | Description |
|----------|--------|-------|-------|-------------|
| **Speed of Light Squared** | `C2` | `9.0e16` | m²/s² | $c^2$ - squared speed of light for energy calculations |
| **Energy Conversion Efficiency** | `ETA` | `0.007` | dimensionless | Mass-energy conversion efficiency for H→He fusion |

### **Astrophysical Constants**

| Constant | Symbol | Value | Units | Description |
|----------|--------|-------|-------|-------------|
| **Solar Mass** | `M_SUN` | `1.989e30` | kg | Mass of the Sun |
| **Solar Luminosity** | `L_SUN` | `3.828e26` | W | Total power output of the Sun |
| **Hydrogen Fuel Fraction** | `F` | `0.1` | dimensionless | Fraction of stellar mass available for fusion |

### **Time Conversion Constants**

| Constant | Symbol | Value | Units | Description |
|----------|--------|-------|-------|-------------|
| **Seconds per Year** | `SECONDS_PER_YEAR` | `3.154e7` | s/year | Conversion factor for time units |

---

## 📚 Theoretical Background

### **Speed of Light (c² = 9.0×10¹⁶ m²/s²)**
The speed of light is a fundamental constant in Einstein's mass-energy equivalence:
$$E = mc^2$$

For stellar physics, we use $c^2$ directly to calculate energy from mass:
$$E_{nuclear} = M \cdot c^2 \cdot \eta$$

### **Energy Conversion Efficiency (η = 0.007)**
This value represents the fraction of mass converted to energy during hydrogen fusion:
$$^4_1H + 2e^+ + 2\nu_e \rightarrow ^4_2He + 2\gamma + 2\nu_e$$

The theoretical maximum efficiency for H→He fusion is approximately 0.7% (0.007), accounting for:
- Mass difference between 4 hydrogen atoms and 1 helium atom
- Energy lost to neutrinos
- Actual nuclear reaction efficiency

### **Solar Mass (M☉ = 1.989×10³⁰ kg)**
The solar mass serves as the standard unit for stellar masses. This value comes from:
- Gravitational measurements of the solar system
- Kepler's laws applied to planetary orbits
- Modern astronomical observations

### **Solar Luminosity (L☉ = 3.828×10²⁶ W)**
The solar luminosity represents the total electromagnetic energy output of the Sun. This measurement includes:
- All wavelengths of electromagnetic radiation
- Integrated over the entire solar surface
- Measured at Earth's distance and corrected for inverse square law

### **Hydrogen Fuel Fraction (f = 0.1)**
Only a fraction of a star's mass is available for nuclear fusion:
- Only 10% of stellar mass is in the core where fusion occurs
- Outer layers are too cool for sustained fusion
- Core mass fraction depends on stellar mass and evolution stage

### **Seconds per Year**
Conversion factor for time calculations:
$$1\ \text{year} = 365.25\ \text{days} = 3.154 \times 10^7\ \text{seconds}$$

---

## 💡 Usage Examples

### **Basic Usage**
```cpp
#include "physics/constants.h"

using namespace physics::constants;

// Calculate total nuclear energy available
double stellar_mass = 2.0 * M_SUN;  // 2 solar masses
double total_energy = stellar_mass * C2 * ETA;  // Joules

// Calculate solar lifetime
double fuel_available = F * stellar_mass;  // Core mass only
double fusion_energy = fuel_available * C2 * ETA;
double lifetime_seconds = fusion_energy / L_SUN;
double lifetime_years = lifetime_seconds / SECONDS_PER_YEAR;
```

### **Unit Conversions**
```cpp
// Convert solar masses to kilograms
double mass_solar = 5.0;  // 5 M☉
double mass_kg = mass_solar * M_SUN;  // 9.945×10³⁰ kg

// Convert solar luminosities to watts
double luminosity_solar = 100.0;  // 100 L☉
double luminosity_watts = luminosity_solar * L_SUN;  // 3.828×10²⁸ W

// Convert years to seconds for calculations
double stellar_lifetime_years = 1e9;  // 1 billion years
double lifetime_seconds = stellar_lifetime_years * SECONDS_PER_YEAR;
```

---

## ⚠️ Important Notes

### **Numerical Considerations**
- All constants use `double` precision for adequate accuracy
- Values are optimized for stellar physics calculations
- Avoid integer division when using these constants

### **Physical Limitations**
- Constants are approximations for main-sequence stars
- May not apply to exotic stellar objects (neutron stars, black holes)
- Some values vary with stellar composition and metallicity

### **Unit Consistency**
- Always maintain consistent units in calculations
- Most physics calculations should use SI units (kg, m, s, W, J)
- Solar units are for convenience in stellar astrophysics

---

## 🔗 Related Modules

### **Direct Dependencies**
- **[`physics::stellar`](physics_stellar.md)** - Uses all constants for stellar calculations
- **[`main`](../examples/basic_usage.md)** - Constants in example calculations

### **Usage Context**
- Constants are used throughout the project for:
  - Energy calculations (`C2`, `ETA`)
  - Mass-luminosity relationships (`M_SUN`, `L_SUN`)
  - Fuel consumption modeling (`F`)
  - Time unit conversions (`SECONDS_PER_YEAR`)

---

## 📖 References

1. **CODATA 2018** - Committee on Data for Science and Technology
2. **IAU 2015 Resolution B2** - International Astronomical Union definitions
3. **Carroll & Ostlie (2017)** - "An Introduction to Modern Astrophysics"
4. **Kippenhahn & Weigert (1990)** - "Stellar Structure and Evolution"

---

## 🚀 Quick Reference

```cpp
namespace physics::constants {
    constexpr double F = 0.1;                    // Hydrogen fuel fraction
    constexpr double ETA = 0.007;                // Mass-energy conversion efficiency
    constexpr double C2 = 9.0e16;                // Speed of light squared (m²/s²)
    constexpr double L_SUN = 3.828e26;           // Solar luminosity (W)
    constexpr double M_SUN = 1.989e30;           // Solar mass (kg)
    constexpr double SECONDS_PER_YEAR = 3.154e7; // Seconds per year
}
```

---

*Constants form the foundation of accurate stellar physics calculations.* ⭐