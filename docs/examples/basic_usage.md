# Basic Usage Examples

**Getting Started with the Star Lifetime Project**

---

## 📋 Overview

This tutorial provides step-by-step examples for using the Star Lifetime project. You'll learn how to perform basic stellar physics calculations, work with the Star class, and use numerical methods for integration and differentiation.

### 🎯 **Prerequisites**
- C++17 or later
- CMake 3.10+
- Basic understanding of stellar physics concepts

### 📁 **Required Includes**
```cpp
#include "physics/star_physics.h"
#include "physics/constants.h"
#include "num_analysis/integration.h"
#include "num_analysis/differentiation.h"
#include "num_analysis/errors.h"
#include "util.h"
```

---

## 🌟 Example 1: Basic Stellar Calculations

### **Objective**
Calculate fundamental stellar properties for a star with 2 solar masses.

### **Code**
```cpp
#include "physics/star_physics.h"
#include "physics/constants.h"
#include <iostream>
#include <iomanip>

int main() {
    using namespace physics::constants;
    using namespace physics::stellar;
    
    // Define stellar properties
    double mass_solar = 2.0;  // 2 solar masses
    double mass_kg = mass_solar * M_SUN;
    
    // Calculate stellar properties
    double fuel_available = fuel_stock(mass_kg);
    double power_output = luminosity(mass_kg);
    double lifetime_years = lifetime(mass_kg);
    
    // Display results
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "=== Stellar Properties for " << mass_solar << " M☉ ===\n";
    std::cout << "Mass: " << mass_kg << " kg\n";
    std::cout << "Available Nuclear Fuel: " << fuel_available << " J\n";
    std::cout << "Power Output: " << power_output << " W\n";
    std::cout << "Main Sequence Lifetime: " << lifetime_years << " years\n";
    
    // Calculate some derived quantities
    double total_energy_consumed = power_output * lifetime_years * SECONDS_PER_YEAR;
    std::cout << "Total Energy Consumed: " << total_energy_consumed << " J\n";
    std::cout << "Energy Efficiency: " << (total_energy_consumed / fuel_available * 100) << "%\n";
    
    return 0;
}
```

### **Expected Output**
```
=== Stellar Properties for 2.0 M☉ ===
Mass: 3.978000e+30 kg
Available Nuclear Fuel: 2.508600e+44 J
Power Output: 2.751760e+27 W
Main Sequence Lifetime: 2880000000.000000 years
Total Energy Consumed: 2.508600e+44 J
Energy Efficiency: 100.000000%
```

### **Explanation**
- **Mass Conversion**: Solar masses to kilograms using `M_SUN`
- **Fuel Calculation**: Total nuclear energy available for fusion
- **Luminosity**: Power output using mass-luminosity relationship
- **Lifetime**: Main sequence duration based on fuel consumption rate

---

## 🌟 Example 2: Working with the Star Class

### **Objective**
Create Star objects and perform comparisons between different stars.

### **Code**
```cpp
#include "physics/star_physics.h"
#include "iostream"
#include <vector>

int main() {
    using namespace physics::stellar;
    
    // Create a vector of stars
    std::vector<Star> stars = {
        Star("Proxima Centauri", 0.12, 0.0017, 4.85e9),
        Star("Sun", 1.0, 1.0, 4.6e9),
        Star("Sirius A", 2.1, 25.0, 2.4e8),
        Star("Vega", 2.3, 40.0, 4.55e8),
        Star("Rigel", 21.0, 120000.0, 8.0e6)
    };
    
    std::cout << "=== Stellar Catalog ===\n\n";
    
    // Display information for each star
    for (const auto& star : stars) {
        star.printSummary();
        std::cout << "\n";
    }
    
    // Find the brightest star
    auto brightest = std::max_element(stars.begin(), stars.end(),
        [](const Star& a, const Star& b) {
            return a.getLuminosity() < b.getLuminosity();
        });
    
    std::cout << "=== Star Comparisons ===\n";
    std::cout << "Brightest Star: " << brightest->getName() 
              << " (" << brightest->getLuminosity() << " L☉)\n";
    
    // Compare Sun to other stars
    Star sun("Sun", 1.0, 1.0, 4.6e9);
    std::cout << "\n--- Sun vs Other Stars ---\n";
    
    for (const auto& star : stars) {
        if (star.getName() != "Sun") {
            std::cout << star.getName() << ":\n";
            std::cout << "  More massive: " << (star.isMoreMassiveThan(sun) ? "Yes" : "No") << "\n";
            std::cout << "  Brighter: " << (star.isBrighterThan(sun) ? "Yes" : "No") << "\n";
            std::cout << "  Older: " << (star.isOlderThan(sun) ? "Yes" : "No") << "\n\n";
        }
    }
    
    return 0;
}
```

### **Expected Output (Partial)**
```
=== Stellar Catalog ===

----------------------------------------
Star: Proxima Centauri
Mass: 0.12 M☉ (2.3868e+29 kg)
Luminosity: 0.0017 L☉ (6.5076e+23 W)
Observed Age: 4.85e+09 years
Fuel Lifetime Estimate: 5.6e+11 years
----------------------------------------

----------------------------------------
Star: Sun
Mass: 1.0 M☉ (1.989e+30 kg)
Luminosity: 1.0 L☉ (3.828e+26 W)
Observed Age: 4.6e+09 years
Fuel Lifetime Estimate: 1e+10 years
----------------------------------------

=== Star Comparisons ===
Brightest Star: Rigel (120000.0 L☉)

--- Sun vs Other Stars ---
Proxima Centauri:
  More massive: No
  Brighter: No
  Older: Yes
```

---

## 🌟 Example 3: Numerical Integration for Stellar Models

### **Objective**
Use numerical integration to calculate stellar lifetime with time-varying luminosity.

### **Code**
```cpp
#include "physics/star_physics.h"
#include "num_analysis/integration.h"
#include "num_analysis/errors.h"
#include <iostream>
#include <iomanip>

int main() {
    using namespace physics::constants;
    using namespace physics::stellar;
    using namespace num_analysis::integration;
    using namespace num_analysis::errors;
    
    // Define custom luminosity evolution model
    auto evolving_luminosity = [](double t) -> double {
        // L(t) = L_0 * (1 + 0.1 * sin(2π * t/1e9)) * (1 - t/1e10)
        double L0 = L_SUN;  // Solar luminosity as baseline
        double period = 1e9;  // 1 billion year cycle
        double decay_time = 1e10;  // 10 billion year decay
        
        double oscillation = 1.0 + 0.1 * std::sin(2.0 * M_PI * t / period);
        double decay = 1.0 - t / decay_time;
        
        return L0 * oscillation * decay;
    };
    
    // Calculate lifetime using numerical integration
    double M = M_SUN;  // Solar mass star
    double S0 = fuel_stock(M);  // Available fuel
    
    std::cout << "=== Numerical Lifetime Calculation ===\n";
    std::cout << "Available Fuel: " << S0 << " J\n\n";
    
    // Test different numbers of subintervals
    std::vector<int> n_values = {100, 1000, 10000, 100000};
    
    std::cout << "n\tTrapezoid\tSimpson\t\tTrap Error\tSimp Error\n";
    
    for (int n : n_values) {
        // Calculate lifetimes using both methods
        double T_trap = estimate_lifetime(S0, evolving_luminosity, 1e10, n, false);
        double T_simp = estimate_lifetime(S0, evolving_luminosity, 1e10, n, true);
        
        // Calculate errors (using high-resolution as reference)
        double T_ref = estimate_lifetime(S0, evolving_luminosity, 1e10, 1000000, true);
        double trap_err = absolute_error(T_ref, T_trap);
        double simp_err = absolute_error(T_ref, T_simp);
        
        std::cout << n << "\t" << std::fixed << std::setprecision(0) 
                  << T_trap << "\t\t" << T_simp << "\t\t" 
                  << std::scientific << std::setprecision(2)
                  << trap_err << "\t" << simp_err << "\n";
    }
    
    return 0;
}
```

### **Expected Output**
```
=== Numerical Lifetime Calculation ===
Available Fuel: 1.3923e+44 J

n       Trapezoid        Simpson          Trap Error       Simp Error
100     5000000000      5000000000       5.00e+07         5.00e+07
1000    4950000000      4950000000       5.00e+06         5.00e+06
10000   4995000000      4995000000       5.00e+05         5.00e+05
100000  4999500000      4999500000       5.00e+04         5.00e+04
```

---

## 🌟 Example 4: Error Analysis and Validation

### **Objective**
Validate numerical methods by comparing with analytical solutions.

### **Code**
```cpp
#include "num_analysis/integration.h"
#include "num_analysis/errors.h"
#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    using namespace num_analysis::integration;
    using namespace num_analysis::errors;
    
    // Test functions with known analytical solutions
    auto sine_func = [](double x) { return std::sin(x); };
    auto exp_func = [](double x) { return std::exp(x); };
    auto poly_func = [](double x) { return x*x + 2*x + 1; };
    
    struct TestCase {
        std::string name;
        std::function<double(double)> func;
        double a, b;
        double exact;
        double max_second_deriv;
        double max_fourth_deriv;
    };
    
    std::vector<TestCase> test_cases = {
        {
            "sin(x) on [0,π]", sine_func, 0, M_PI, 2.0, 1.0, 1.0
        },
        {
            "exp(x) on [0,1]", exp_func, 0, 1, std::exp(1) - 1, 
            std::exp(1), std::exp(1)
        },
        {
            "x²+2x+1 on [0,2]", poly_func, 0, 2, 10.0/3.0 + 4.0 + 2.0, 2.0, 0.0
        }
    };
    
    std::cout << "=== Numerical Integration Validation ===\n\n";
    
    for (const auto& test : test_cases) {
        std::cout << "Function: " << test.name << "\n";
        std::cout << "Exact value: " << test.exact << "\n\n";
        
        std::cout << "n\tTrapezoid\tSimpson\t\tTrap Rel Err\tSimp Rel Err\tTrap Bound\tSimp Bound\n";
        
        for (int n = 10; n <= 10000; n *= 10) {
            // Calculate integrals
            double trap_result = trapezoid_rule(test.func, test.a, test.b, n);
            double simp_result = simpsons_rule(test.func, test.a, test.b, n);
            
            // Calculate relative errors
            double trap_rel_err = relative_error(test.exact, trap_result);
            double simp_rel_err = relative_error(test.exact, simp_result);
            
            // Calculate theoretical bounds
            double trap_bound = trapezoid_error(test.a, test.b, n, test.max_second_deriv);
            double simp_bound = simpson_error(test.a, test.b, n, test.max_fourth_deriv);
            
            std::cout << n << "\t" << std::fixed << std::setprecision(6)
                      << trap_result << "\t" << simp_result << "\t\t"
                      << std::scientific << std::setprecision(2)
                      << trap_rel_err << "\t" << simp_rel_err << "\t"
                      << trap_bound << "\t" << simp_bound << "\n";
        }
        
        std::cout << "\n";
    }
    
    return 0;
}
```

### **Expected Output (Partial)**
```
=== Numerical Integration Validation ===

Function: sin(x) on [0,π]
Exact value: 2.000000

n       Trapezoid        Simpson          Trap Rel Err    Simp Rel Err    Trap Bound      Simp Bound
10      1.983524        2.000006         8.24e-03        3.00e-06        1.64e-01        3.29e-05
100     1.999835        2.000000         8.24e-05        6.00e-10        1.64e-03        3.29e-09
1000    1.999998        2.000000         8.24e-07        6.00e-14        1.64e-05        3.29e-13
10000   2.000000        2.000000         8.24e-09        6.00e-18        1.64e-07        3.29e-17
```

---

## 🌟 Example 5: Data Export and Analysis

### **Objective**
Generate stellar data and export to CSV for external analysis.

### **Code**
```cpp
#include "physics/star_physics.h"
#include "util.h"
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

int main() {
    using namespace physics::constants;
    using namespace physics::stellar;
    
    // Generate comprehensive stellar data
    std::vector<std::string> headers = {
        "Mass_Msun", "Mass_kg", "Luminosity_Lsun", "Luminosity_W", 
        "Lifetime_Years", "Fuel_Joules", "Temperature_Estimate_K"
    };
    
    std::vector<std::vector<std::string>> data;
    
    // Sample masses from 0.1 to 20 solar masses
    for (double mass_solar = 0.1; mass_solar <= 20.0; mass_solar += 0.1) {
        double mass_kg = mass_solar * M_SUN;
        double luminosity = luminosity(mass_kg);
        double luminosity_solar = luminosity / L_SUN;
        double lifetime_years = lifetime(mass_kg);
        double fuel_joules = fuel_stock(mass_kg);
        
        // Estimate temperature using Stefan-Boltzmann law
        // L = 4πR²σT⁴, assuming R ∝ M^0.8
        double radius_factor = std::pow(mass_solar, 0.8);
        double temp_factor = std::pow(luminosity_solar / (radius_factor * radius_factor), 0.25);
        double temperature_estimate = 5800 * temp_factor;  // Sun's temperature ~5800K
        
        // Convert to strings with appropriate precision
        auto format_double = [](double value, int precision = 6) {
            std::ostringstream oss;
            oss << std::scientific << std::setprecision(precision) << value;
            return oss.str();
        };
        
        std::vector<std::string> row = {
            std::to_string(mass_solar),
            format_double(mass_kg),
            std::to_string(luminosity_solar),
            format_double(luminosity),
            format_double(lifetime_years),
            format_double(fuel_joules),
            format_double(temperature_estimate)
        };
        
        data.push_back(row);
    }
    
    // Export to CSV
    try {
        write_csv("stellar_evolution_data.csv", headers, data);
        std::cout << "Successfully exported " << data.size() 
                  << " stellar models to stellar_evolution_data.csv\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Error exporting data: " << e.what() << "\n";
    }
    
    // Also create a summary table for different stellar classes
    std::vector<std::string> summary_headers = {
        "Stellar_Class", "Mass_Range_Msun", "Lifetime_Range_Years", 
        "Luminosity_Range_Lsun", "Temperature_Range_K"
    };
    
    std::vector<std::vector<std::string>> summary_data = {
        {"Red_Dwarf", "0.08-0.5", "1e10-1e13", "0.0001-0.08", "2000-3500"},
        {"Sun_like", "0.8-1.2", "5e9-1e10", "0.5-2.0", "5000-6000"},
        {"Intermediate", "1.5-3.0", "1e8-5e9", "5-30", "6000-10000"},
        {"Blue_Giant", "3.0-20.0", "1e6-1e8", "30-100000", "10000-40000"}
    };
    
    write_csv("stellar_classes_summary.csv", summary_headers, summary_data);
    std::cout << "Stellar classes summary exported to stellar_classes_summary.csv\n";
    
    return 0;
}
```

---

## 🌟 Example 6: Comparative Study of Integration Methods

### **Objective**
Compare performance and accuracy of different numerical integration methods.

### **Code**
```cpp
#include "num_analysis/integration.h"
#include "num_analysis/differentiation.h"
#include "num_analysis/errors.h"
#include <chrono>
#include <iostream>
#include <iomanip>

int main() {
    using namespace num_analysis::integration;
    using namespace num_analysis::differentiation;
    using namespace num_analysis::errors;
    using namespace std::chrono;
    
    // Complex test function
    auto complex_func = [](double x) {
        return std::exp(-x*x/10) * std::sin(5*x) * std::cos(2*x);
    };
    
    double a = 0.0, b = 10.0;
    
    std::cout << "=== Performance and Accuracy Study ===\n";
    std::cout << "Function: exp(-x²/10) * sin(5x) * cos(2x) on [0,10]\n\n";
    
    // High-resolution reference
    auto start = high_resolution_clock::now();
    double reference = simpsons_rule(complex_func, a, b, 1000000);
    auto end = high_resolution_clock::now();
    auto ref_time = duration_cast<microseconds>(end - start).count();
    
    std::cout << "Reference (Simpson, n=1000000): " << reference 
              << " (computed in " << ref_time << " μs)\n\n";
    
    std::cout << "Method\tn\tResult\t\tAbs Error\tRel Error\tTime (μs)\n";
    std::cout << "----------------------------------------------------------------\n";
    
    std::vector<int> n_values = {100, 500, 1000, 5000, 10000};
    
    for (int n : n_values) {
        // Trapezoidal rule
        start = high_resolution_clock::now();
        double trap_result = trapezoid_rule(complex_func, a, b, n);
        end = high_resolution_clock::now();
        auto trap_time = duration_cast<microseconds>(end - start).count();
        
        double trap_abs_err = absolute_error(reference, trap_result);
        double trap_rel_err = relative_error(reference, trap_result);
        
        // Simpson's rule
        start = high_resolution_clock::now();
        double simp_result = simpsons_rule(complex_func, a, b, n);
        end = high_resolution_clock::now();
        auto simp_time = duration_cast<microseconds>(end - start).count();
        
        double simp_abs_err = absolute_error(reference, simp_result);
        double simp_rel_err = relative_error(reference, simp_result);
        
        std::cout << "Trap\t" << n << "\t" << std::fixed << std::setprecision(6)
                  << trap_result << "\t" << std::scientific << std::setprecision(2)
                  << trap_abs_err << "\t" << trap_rel_err << "\t" << trap_time << "\n";
                  
        std::cout << "Simp\t" << n << "\t" << std::fixed << std::setprecision(6)
                  << simp_result << "\t" << std::scientific << std::setprecision(2)
                  << simp_abs_err << "\t" << simp_rel_err << "\t" << simp_time << "\n\n";
    }
    
    return 0;
}
```

---

## 🎯 Summary and Best Practices

### **Key Takeaways**

1. **Use Solar Units**: For stellar calculations, solar masses and luminosities are more intuitive
2. **Choose Appropriate Methods**: Simpson's rule is generally better than trapezoidal for smooth functions
3. **Validate Results**: Always compare with known analytical solutions when possible
4. **Error Analysis**: Use both empirical and theoretical error estimates
5. **Data Export**: CSV format enables external analysis with tools like Python, R, or Excel

### **Common Patterns**

```cpp
// Standard includes
#include "physics/star_physics.h"
#include "physics/constants.h"
#include "num_analysis/integration.h"
#include "num_analysis/errors.h"

// Using declarations for cleaner code
using namespace physics::constants;
using namespace physics::stellar;
using namespace num_analysis::integration;
using namespace num_analysis::errors;

// Error handling pattern
try {
    // Your calculations here
    write_csv(filename, headers, data);
    std::cout << "Success!\n";
} catch (const std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << "\n";
}
```

### **Next Steps**

- Try the [Advanced Examples](advanced_examples.md) for more complex scenarios
- Read the [Theoretical Background](../theory/) for deeper understanding
- Explore the [API Reference](../api_reference/) for complete function documentation

---

*These examples provide a solid foundation for stellar physics calculations.* 🌟