# Physics API Reference

**Complete API Reference for Physics Modules**

---

## 📋 Overview

This section provides a comprehensive reference for all physics-related functions, classes, and constants in the Star Lifetime project. The API is organized by namespace for easy navigation.

### 📁 **Related Files**
- **Headers**: `include/physics/constants.h`, `include/physics/star_physics.h`
- **Source**: `src/physics/star_physics.cpp`

---

## 🌟 physics::constants Namespace

### **Constants**

| Constant | Type | Value | Units | Description |
|----------|------|-------|-------|-------------|
| `F` | `constexpr double` | `0.1` | dimensionless | Hydrogen fuel fraction available for fusion |
| `ETA` | `constexpr double` | `0.007` | dimensionless | Mass-energy conversion efficiency (H→He) |
| `C2` | `constexpr double` | `9.0e16` | m²/s² | Speed of light squared |
| `L_SUN` | `constexpr double` | `3.828e26` | W | Solar luminosity (total power output) |
| `M_SUN` | `constexpr double` | `1.989e30` | kg | Solar mass |
| `SECONDS_PER_YEAR` | `constexpr double` | `3.154e7` | s/year | Time conversion factor |

### **Usage Example**
```cpp
#include "physics/constants.h"

using namespace physics::constants;

// Calculate solar energy available for fusion
double solar_mass = M_SUN;
double available_energy = F * solar_mass * C2 * ETA;
```

---

## 🌟 physics::stellar Namespace

### **Core Physics Functions**

#### **`fuel_stock(double M)`**

**Purpose**: Calculate total nuclear fuel available in a star

```cpp
double fuel_stock(double M);
```

**Parameters**:
- `M` (double): Stellar mass in kilograms

**Returns**: Available fuel energy in Joules

**Formula**: $S = f \cdot M \cdot c^2 \cdot \eta$

**Throws**: None

**Example**:
```cpp
double star_mass = 2.0 * M_SUN;  // 2 solar masses
double fuel = fuel_stock(star_mass);
```

---

#### **`luminosity(double M)`**

**Purpose**: Calculate stellar luminosity using mass-luminosity relationship

```cpp
double luminosity(double M);
```

**Parameters**:
- `M` (double): Stellar mass in kilograms

**Returns**: Stellar luminosity in Watts

**Formula**: $L = L_{\odot} \cdot \left(\frac{M}{M_{\odot}}\right)^{3.5}$

**Throws**: None

**Example**:
```cpp
double star_mass = 1.5 * M_SUN;
double power_output = luminosity(star_mass);
```

---

#### **`lifetime(double M)`**

**Purpose**: Estimate main-sequence stellar lifetime

```cpp
double lifetime(double M);
```

**Parameters**:
- `M` (double): Stellar mass in kilograms

**Returns**: Stellar lifetime in years

**Formula**: $T = \frac{S}{L} \cdot \frac{1}{\text{seconds per year}}$

**Throws**: None

**Example**:
```cpp
double star_mass = 0.8 * M_SUN;
double main_sequence_lifetime = lifetime(star_mass);
```

---

### **Luminosity Evolution Models**

#### **`L_const(double t)`**

**Purpose**: Constant luminosity model (toy model)

```cpp
double L_const(double t);
```

**Parameters**:
- `t` (double): Time (ignored in this model)

**Returns**: Constant value of 1.0 (normalized units)

**Throws**: None

---

#### **`L_exp_decay(double t)`**

**Purpose**: Exponentially decaying luminosity model

```cpp
double L_exp_decay(double t);
```

**Parameters**:
- `t` (double): Time in years

**Returns**: $L_{\odot} \cdot e^{-kt}$ where $k = 10^{-10}$ years⁻¹

**Throws**: None

---

#### **`L_sinusoidal(double t)`**

**Purpose**: Sinusoidal luminosity variation (toy model)

```cpp
double L_sinusoidal(double t);
```

**Parameters**:
- `t` (double): Time (arbitrary units)

**Returns**: $L_0 \cdot (1 + A \sin(\omega t))$

**Constants**: $L_0 = 1.0$, $A = 0.2$, $\omega = 2.0$

**Throws**: None

---

### **Numerical Lifetime Estimation**

#### **`estimate_lifetime()`**

**Purpose**: Estimate lifetime by integrating time-varying luminosity

```cpp
double estimate_lifetime(double S0,
                      double (*L)(double),
                      double T_guess,
                      int n,
                      bool use_simpson);
```

**Parameters**:
- `S0` (double): Initial fuel stock in Joules
- `L` (function pointer): Luminosity function L(t)
- `T_guess` (double): Initial lifetime estimate in years
- `n` (int): Number of integration subintervals
- `use_simpson` (bool): Use Simpson's rule if true, trapezoid if false

**Returns**: Scaled lifetime estimate in years

**Algorithm**:
1. Integrate luminosity function using specified method
2. Scale time to match available fuel
3. Return estimated lifetime

**Throws**: None (depends on integration method)

**Example**:
```cpp
double fuel = fuel_stock(M_SUN);
double lifetime_est = estimate_lifetime(fuel, L_exp_decay, 1e10, 1000, true);
```

---

### **Data Generation**

#### **`generate_lifetime_table()`**

**Purpose**: Generate CSV table of stellar lifetimes

```cpp
void generate_lifetime_table(int num_points = 50);
```

**Parameters**:
- `num_points` (int): Number of mass samples (default: 50)

**Returns**: None

**Output**: Creates `../results/lifetime_table.csv`

**Mass Range**: 0.1 to 20.0 solar masses

**Throws**: `std::runtime_error` if file cannot be created

**Example**:
```cpp
generate_lifetime_table(100);  // 100 data points
```

---

## 🌟 Star Class

### **Class Overview**

The `Star` class provides an object-oriented interface for stellar properties and calculations.

```cpp
class Star {
public:
    // Constructor
    Star(const std::string &name, double mass_Msun, double luminosity_Lsun, double observed_age_years);
    
    // Destructor
    ~Star();
    
    // Getters
    std::string getName() const;
    double getMass() const;
    double getLuminosity() const;
    double getAge() const;
    
    // Physical calculations
    double computeFuelLifetime() const;
    double luminosityInWatts() const;
    double massInKg() const;
    
    // Setters
    void setName(const std::string& name);
    void setMass(double mass_Msun);
    void setLuminosity(double luminosity_Lsun);
    void setAge(double observed_age_years);
    
    // Display
    void printSummary() const;
    
    // Comparisons
    bool isOlderThan(const Star& other) const;
    bool isBrighterThan(const Star& other) const;
    bool isMoreMassiveThan(const Star& other) const;
    
    // Evolution
    void evolve(double t_final, double dt);

private:
    std::string name;
    double mass_Msun;
    double luminosity_Lsun;
    double observed_age_years;
};
```

---

### **Constructor**

#### **`Star()`**

**Purpose**: Initialize a Star object with stellar properties

```cpp
Star(const std::string &name, double mass_Msun, double luminosity_Lsun, double observed_age_years);
```

**Parameters**:
- `name` (const std::string&): Star identifier/name
- `mass_Msun` (double): Mass in solar masses
- `luminosity_Lsun` (double): Luminosity in solar units
- `observed_age_years` (double): Current age in years

**Throws**: `std::invalid_argument` if any parameter is negative

**Example**:
```cpp
Star sun("Sun", 1.0, 1.0, 4.6e9);
Star sirius("Sirius A", 2.1, 25.0, 2.4e8);
```

---

### **Getter Methods**

#### **`getName()`**

```cpp
std::string getName() const;
```
**Returns**: Star name as string

#### **`getMass()`**

```cpp
double getMass() const;
```
**Returns**: Mass in solar masses

#### **`getLuminosity()`**

```cpp
double getLuminosity() const;
```
**Returns**: Luminosity in solar units

#### **`getAge()`**

```cpp
double getAge() const;
```
**Returns**: Age in years

---

### **Physical Calculation Methods**

#### **`computeFuelLifetime()`**

```cpp
double computeFuelLifetime() const;
```
**Returns**: Theoretical fuel-based lifetime in years
**Formula**: Uses `lifetime(massInKg())` function

#### **`luminosityInWatts()`**

```cpp
double luminosityInWatts() const;
```
**Returns**: Luminosity in Watts
**Formula**: `luminosity_Lsun * L_SUN`

#### **`massInKg()`**

```cpp
double massInKg() const;
```
**Returns**: Mass in kilograms
**Formula**: `mass_Msun * M_SUN`

---

### **Setter Methods**

#### **`setName()`**

```cpp
void setName(const std::string& name);
```
**Parameters**: New star name

#### **`setMass()`**

```cpp
void setMass(double mass_Msun);
```
**Parameters**: New mass in solar masses
**Throws**: `std::invalid_argument` if mass is negative

#### **`setLuminosity()`**

```cpp
void setLuminosity(double luminosity_Lsun);
```
**Parameters**: New luminosity in solar units
**Throws**: `std::invalid_argument` if luminosity is negative

#### **`setAge()`**

```cpp
void setAge(double observed_age_years);
```
**Parameters**: New age in years
**Throws**: `std::invalid_argument` if age is negative

---

### **Display Methods**

#### **`printSummary()`**

```cpp
void printSummary() const;
```
**Purpose**: Display formatted star information
**Output Format**:
```
----------------------------------------
Star: [Name]
Mass: [M] M☉ ([mass] kg)
Luminosity: [L] L☉ ([watts] W)
Observed Age: [age] years
Fuel Lifetime Estimate: [lifetime] years
----------------------------------------
```

---

### **Comparison Methods**

#### **`isOlderThan()`**

```cpp
bool isOlderThan(const Star& other) const;
```
**Parameters**: Another Star object
**Returns**: true if this star is older than the other

#### **`isBrighterThan()`**

```cpp
bool isBrighterThan(const Star& other) const;
```
**Parameters**: Another Star object
**Returns**: true if this star is more luminous

#### **`isMoreMassiveThan()`**

```cpp
bool isMoreMassiveThan(const Star& other) const;
```
**Parameters**: Another Star object
**Returns**: true if this star is more massive

---

### **Evolution Method**

#### **`evolve()`**

```cpp
void evolve(double t_final, double dt);
```
**Parameters**:
- `t_final` (double): Final time increment in years
- `dt` (double): Time step in years

**Purpose**: Evolve star forward in time using simple fuel depletion model

**Throws**: `std::invalid_argument` if dt ≤ 0 or t_final < 0

**Algorithm**: Uses constant luminosity model for fuel consumption

---

## 🔗 Function Dependencies

### **Physics Functions Dependencies**

```
fuel_stock()    → physics::constants
luminosity()     → physics::constants  
lifetime()       → fuel_stock(), luminosity(), physics::constants
Star methods     → physics::constants, physics functions
```

### **Integration Dependencies**

```
estimate_lifetime() → num_analysis::integration
```

---

## 📊 Type Definitions

### **Function Pointers**

```cpp
typedef double (*LuminosityFunction)(double);
```
**Used for**: `estimate_lifetime()` parameter

**Compatible Functions**:
- `L_const`
- `L_exp_decay` 
- `L_sinusoidal`
- Custom functions with signature `double func(double)`

---

## 🚀 Quick Reference

### **Basic Stellar Calculations**
```cpp
// Simple calculations
double lifetime_years = lifetime(star_mass_kg);
double power_watts = luminosity(star_mass_kg);
double fuel_joules = fuel_stock(star_mass_kg);

// Object-oriented approach
Star star("Name", 1.5, 3.4, 1e9);
double theoretical_life = star.computeFuelLifetime();
double actual_power = star.luminosityInWatts();
```

### **Advanced Usage**
```cpp
// Custom luminosity model
auto custom_luminosity = [](double t) {
    return L_SUN * std::pow(1 + t/1e9, -0.5);  // Declining luminosity
};

double custom_lifetime = estimate_lifetime(fuel_stock(M_SUN), custom_luminosity, 1e10, 1000, true);
```

---

*This API reference provides complete function signatures and usage patterns for physics calculations.* ⭐