# Physics Stellar Module

**Module Overview for `physics::stellar` namespace**

---

## 📋 Module Overview

The `physics::stellar` namespace is the core of the Star Lifetime project, providing comprehensive stellar physics models, lifetime calculations, and the Star class for object-oriented stellar analysis. This module combines theoretical astrophysics with numerical methods to model stellar evolution and compute stellar lifetimes.

### 🎯 **Purpose**
- Implement mass-luminosity relationships for main-sequence stars
- Calculate stellar lifetimes based on nuclear fuel consumption
- Provide object-oriented interface for star properties and comparisons
- Support multiple luminosity evolution models
- Generate data tables for stellar parameter analysis

### 📁 **Files**
- **Header**: `include/physics/star_physics.h`
- **Implementation**: `src/physics/star_physics.cpp`

---

## 🌟 Core Physics Functions

### **`fuel_stock(double M)`**
**Purpose**: Calculate the total nuclear fuel available in a star

**Formula**:
$$S = f \cdot M \cdot c^2 \cdot \eta$$

**Parameters**:
- `M` - Stellar mass in kilograms

**Returns**: Available fuel energy in Joules

**Physical Meaning**:
- Only a fraction `f` (0.1) of stellar mass is in the fusion core
- Only fraction `η` (0.007) of mass converts to energy
- Uses Einstein's mass-energy equivalence

```cpp
double star_mass = 2.0 * M_SUN;  // 2 solar masses
double available_fuel = fuel_stock(star_mass);  // Joules
```

### **`luminosity(double M)`**
**Purpose**: Calculate stellar luminosity using mass-luminosity relationship

**Formula**:
$$L = L_{\odot} \cdot \left(\frac{M}{M_{\odot}}\right)^{3.5}$$

**Parameters**:
- `M` - Stellar mass in kilograms

**Returns**: Stellar luminosity in Watts

**Physical Meaning**:
- Empirical relationship for main-sequence stars
- More massive stars are exponentially more luminous
- Explains why massive stars have shorter lifetimes

```cpp
double star_mass = 1.5 * M_SUN;  // 1.5 solar masses
double power_output = luminosity(star_mass);  // Watts
```

### **`lifetime(double M)`**
**Purpose**: Estimate main-sequence lifetime based on fuel consumption

**Formula**:
$$T = \frac{S}{L} \cdot \frac{1}{\text{seconds per year}}$$

**Parameters**:
- `M` - Stellar mass in kilograms

**Returns**: Stellar lifetime in years

**Physical Meaning**:
- Simple division of available fuel by consumption rate
- Assumes constant luminosity (simplification)
- Provides first-order lifetime estimate

```cpp
double star_mass = 0.8 * M_SUN;  // 0.8 solar masses
double main_sequence_lifetime = lifetime(star_mass);  // years
```

---

## 🎭 Luminosity Evolution Models

### **`L_const(double t)`**
**Purpose**: Constant luminosity model (toy model)

**Formula**: $L(t) = 1.0$ (normalized units)

**Parameters**:
- `t` - Time (ignored in this model)

**Use Case**: Simple baseline for comparison and testing

### **`L_exp_decay(double t)`**
**Purpose**: Exponentially decaying luminosity model

**Formula**:
$$L(t) = L_{\odot} \cdot e^{-kt}$$
where $k = 10^{-10}$ years⁻¹

**Parameters**:
- `t` - Time in years

**Physical Meaning**:
- Models gradual luminosity decrease over stellar evolution
- Very slow decay rate for main-sequence approximation

### **`L_sinusoidal(double t)`**
**Purpose**: Sinusoidal luminosity variation (toy model)

**Formula**:
$$L(t) = L_0 \cdot (1 + A \sin(\omega t))$
where $L_0 = 1.0$, $A = 0.2$, $\omega = 2.0$

**Parameters**:
- `t` - Time (arbitrary units)

**Use Case**: Testing numerical integration with varying functions

---

## ⭐ Star Class

### **Class Overview**
The `Star` class provides an object-oriented interface for stellar properties and calculations.

### **Constructor**
```cpp
Star(const std::string &name, double mass_Msun, double luminosity_Lsun, double observed_age_years)
```

**Parameters**:
- `name` - Star identifier
- `mass_Msun` - Mass in solar masses
- `luminosity_Lsun` - Luminosity in solar units
- `observed_age_years` - Current age in years

**Exception Handling**: Throws `std::invalid_argument` for negative values

### **Getter Methods**
```cpp
std::string getName() const;           // Star name
double getMass() const;                // Mass in solar masses
double getLuminosity() const;          // Luminosity in solar units
double getAge() const;                 // Age in years
```

### **Physical Property Calculations**
```cpp
double massInKg() const;               // Convert mass to kg
double luminosityInWatts() const;      // Convert luminosity to W
double computeFuelLifetime() const;    // Calculate theoretical lifetime
```

### **Setter Methods**
```cpp
void setName(const std::string& name);
void setMass(double mass_Msun);
void setLuminosity(double luminosity_Lsun);
void setAge(double observed_age_years);
```

### **Comparison Methods**
```cpp
bool isOlderThan(const Star& other) const;      // Age comparison
bool isBrighterThan(const Star& other) const;   // Luminosity comparison
bool isMoreMassiveThan(const Star& other) const; // Mass comparison
```

### **Display Methods**
```cpp
void printSummary() const;           // Formatted star information
void evolve(double t_final, double dt); // Time evolution simulation
```

---

## 🔢 Numerical Lifetime Estimation

### **`estimate_lifetime()` Function**
**Purpose**: Estimate lifetime by integrating time-varying luminosity

**Signature**:
```cpp
double estimate_lifetime(double S0, double (*L)(double), double T_guess, int n, bool use_simpson);
```

**Parameters**:
- `S0` - Initial fuel stock (Joules)
- `L` - Luminosity function pointer
- `T_guess` - Initial lifetime estimate
- `n` - Number of integration subintervals
- `use_simpson` - Use Simpson's rule if true, trapezoid if false

**Algorithm**:
1. Integrate luminosity function over time interval
2. Calculate total energy consumed
3. Scale time interval to match available fuel

**Usage Example**:
```cpp
double fuel = fuel_star(M_SUN);
double T_est = estimate_lifetime(fuel, L_exp_decay, 1e10, 1000, true);
```

---

## 📊 Data Generation

### **`generate_lifetime_table()`**
**Purpose**: Create CSV table of stellar lifetimes for mass range

**Signature**:
```cpp
void generate_lifetime_table(int num_points = 50);
```

**Parameters**:
- `num_points` - Number of mass samples to generate

**Output**: CSV file with columns:
- Mass (solar masses)
- Luminosity (solar units)
- Lifetime (years)

**Mass Range**: 0.1 to 20.0 solar masses

```cpp
generate_lifetime_table(100);  // 100 data points
// Output: "../results/lifetime_table.csv"
```

---

## 💡 Usage Examples

### **Basic Star Analysis**
```cpp
#include "physics/star_physics.h"

using namespace physics::stellar;

// Create star objects
Star sun("Sun", 1.0, 1.0, 4.6e9);
Star sirius("Sirius A", 2.1, 25.0, 2.4e8);

// Display star information
sun.printSummary();
sirius.printSummary();

// Compare stars
if (sirius.isBrighterThan(sun)) {
    std::cout << "Sirius is brighter than the Sun\n";
}
```

### **Direct Physics Calculations**
```cpp
using namespace physics::stellar;

// Calculate properties for a 5 solar mass star
double mass = 5.0 * M_SUN;
double fuel = fuel_stock(mass);
double lumin = luminosity(mass);
double lifetime_years = lifetime(mass);

std::cout << "Fuel available: " << fuel << " J\n";
std::cout << "Power output: " << lumin << " W\n";
std::cout << "Main sequence lifetime: " << lifetime_years << " years\n";
```

### **Numerical Integration Example**
```cpp
using namespace physics::stellar;

// Use exponential decay model
double S0 = fuel_stock(M_SUN);
double T_estimate = estimate_lifetime(S0, L_exp_decay, 1e10, 1000, true);

std::cout << "Estimated lifetime with decay model: " << T_estimate << " years\n";
```

---

## ⚠️ Important Considerations

### **Physical Limitations**
- **Main Sequence Only**: Models apply to main-sequence phase only
- **Simplified Physics**: Ignores stellar evolution complexity
- **Composition Effects**: Assumes solar metallicity composition
- **Mass Range**: Best accuracy for 0.1-50 solar mass range

### **Numerical Considerations**
- **Integration Accuracy**: Simpson's rule preferred for smooth functions
- **Step Size**: Smaller steps improve accuracy but increase computation
- **Function Behavior**: Ensure luminosity functions are well-behaved

### **Computational Performance**
- **Object Creation**: Star objects have minimal overhead
- **Calculations**: Most functions are O(1) complexity
- **Memory Usage**: Light memory footprint

---

## 🔗 Related Modules

### **Dependencies**
- **[`physics::constants`](physics_constants.md)** - All physical constants
- **[`num_analysis::integration`](num_analysis_integration.md)** - Numerical integration methods
- **[`num_analysis::errors`](num_analysis_errors.md)** - Error analysis

### **Used By**
- **[`main`](../examples/basic_usage.md)** - Main application interface
- **[`test_stellar_physics.cpp`](../../src/test_stellar_physics.cpp)** - Comprehensive testing

---

## 📖 Theoretical Background

### **Mass-Luminosity Relationship**
The relationship $L \propto M^{3.5}$ is an empirical fit for main-sequence stars, derived from:
- Stellar structure equations
- Energy transport mechanisms
- Nuclear reaction rates

### **Stellar Lifetime Theory**
Main-sequence lifetime is governed by:
$$T_{MS} \propto \frac{M}{L} \propto M^{-2.5}$$

This explains why massive stars have much shorter lifetimes despite having more fuel.

### **Nuclear Fuel Considerations**
- Only core material participates in fusion
- Energy conversion follows $E = mc^2$
- H→He fusion efficiency is ~0.7%

---

## 🚀 Quick Reference

### **Core Functions**
```cpp
double fuel_stock(double M);           // Available nuclear fuel
double luminosity(double M);            // Stellar power output  
double lifetime(double M);              // Main-sequence lifetime
```

### **Star Class Key Methods**
```cpp
Star(name, mass, luminosity, age);     // Constructor
void printSummary() const;             // Display information
bool isBrighterThan(const Star&) const; // Comparison
double computeFuelLifetime() const;    // Calculate lifetime
```

### **Utility Functions**
```cpp
void generate_lifetime_table(int points); // CSV generation
double estimate_lifetime(S0, L_func, T, n, simpson); // Numerical
```

---

*This module forms the heart of stellar physics calculations in the project.* ⭐