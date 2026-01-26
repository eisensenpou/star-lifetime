# Numerical Integration Module

**Module Overview for `num_analysis::integration` namespace**

---

## 📋 Module Overview

The `num_analysis::integration` namespace provides robust numerical integration algorithms for approximating definite integrals. This module is essential for stellar physics calculations where analytical solutions are not available, such as integrating time-varying luminosity functions to compute stellar lifetimes.

### 🎯 **Purpose**
- Implement composite numerical integration rules
- Provide accurate approximation of definite integrals
- Support both basic and high-precision integration methods
- Enable stellar physics calculations with time-varying functions

### 📁 **Files**
- **Header**: `include/num_analysis/integration.h`
- **Implementation**: `src/num_analysis/integration.cpp`

---

## 🧮 Integration Algorithms

### **Composite Trapezoidal Rule**

#### **Mathematical Foundation**
The trapezoidal rule approximates the definite integral by dividing the interval $[a,b]$ into $n$ subintervals of equal width $h$ and approximating the area under the curve with trapezoids.

**Formula**:
$$\int_a^b f(x) \,dx \approx h \left[ \frac{f(a) + f(b)}{2} + \sum_{i=1}^{n-1} f(a + ih) \right]$$

where $h = \frac{b-a}{n}$

#### **Function Signature**
```cpp
double trapezoid_rule(std::function<double(double)> f, double a, double b, int n);
```

#### **Parameters**
- `f` - Function to integrate (callable returning double)
- `a` - Lower limit of integration
- `b` - Upper limit of integration  
- `n` - Number of subintervals (must be positive)

#### **Return Value**
Approximation of the definite integral $\int_a^b f(x) \,dx$

#### **Accuracy**
- **Order**: $O(h^2)$ local truncation error
- **Global Error**: $O(h^2)$ or $O(n^{-2})$
- **Best For**: Linear or mildly curved functions
- **Limitations**: Less accurate for highly oscillatory functions

#### **Usage Example**
```cpp
#include "num_analysis/integration.h"
#include <cmath>

using namespace num_analysis::integration;

// Integrate f(x) = sin(x) from 0 to π
auto func = [](double x) { return std::sin(x); };
double result = trapezoid_rule(func, 0, M_PI, 1000);
// Expected: 2.0, Actual: ~1.999999 (high accuracy)
```

---

### **Composite Simpson's Rule**

#### **Mathematical Foundation**
Simpson's rule provides higher accuracy by fitting parabolic arcs to three consecutive points. It requires an even number of subintervals.

**Formula**:
$$\int_a^b f(x) \,dx \approx \frac{h}{3} \left[ f(a) + f(b) + 4\sum_{\text{odd } i} f(a + ih) + 2\sum_{\text{even } i} f(a + ih) \right]$$

where $h = \frac{b-a}{n}$ and $n$ is even

#### **Function Signature**
```cpp
double simpsons_rule(std::function<double(double)> f, double a, double b, int n);
```

#### **Parameters**
- `f` - Function to integrate (callable returning double)
- `a` - Lower limit of integration
- `b` - Upper limit of integration
- `n` - Number of subintervals (auto-adjusted to even if odd)

#### **Return Value**
Approximation of the definite integral $\int_a^b f(x) \,dx$

#### **Accuracy**
- **Order**: $O(h^4)$ local truncation error
- **Global Error**: $O(h^4)$ or $O(n^{-4})$
- **Best For**: Smooth functions with continuous derivatives
- **Advantage**: Much more accurate than trapezoidal rule for smooth functions

#### **Special Features**
- **Auto-correction**: Automatically adjusts odd $n$ to $n+1$
- **Efficiency**: Similar computational cost to trapezoidal rule
- **Versatility**: Works well for most smooth functions

#### **Usage Example**
```cpp
#include "num_analysis/integration.h"
#include <cmath>

using namespace num_analysis::integration;

// Integrate f(x) = exp(x) from 0 to 1
auto func = [](double x) { return std::exp(x); };
double result = simpsons_rule(func, 0, 1, 100);
// Expected: e - 1 ≈ 1.71828, Actual: ~1.71828 (very high accuracy)
```

---

## 🔬 Algorithm Comparison

### **Accuracy vs. Computational Cost**

| Method | Order | Error Rate | Best Use Case | Computational Cost |
|--------|-------|------------|---------------|-------------------|
| Trapezoidal | $O(h^2)$ | Moderate | Linear functions, quick estimates | Low |
| Simpson's | $O(h^4)$ | High | Smooth functions, high precision | Medium |

### **Convergence Rates**

For a function $f(x)$ with continuous derivatives:

```
Error ∝ 1/n²     (Trapezoidal Rule)
Error ∝ 1/n⁴     (Simpson's Rule)
```

This means Simpson's rule converges much faster as $n$ increases.

### **Function Suitability**

| Function Type | Trapezoidal | Simpson's | Recommendation |
|---------------|-------------|-----------|----------------|
| Linear | Excellent | Excellent | Either method |
| Quadratic | Good | Excellent | Simpson's preferred |
| Cubic/Poly | Fair | Excellent | Simpson's preferred |
| Oscillatory | Poor | Fair | Specialized methods |
| Discontinuous | Poor | Poor | Adaptive methods |

---

## 💡 Practical Usage Examples

### **Basic Integration**
```cpp
#include "num_analysis/integration.h"
#include <cmath>

using namespace num_analysis::integration;

// Example 1: Polynomial integration
auto polynomial = [](double x) { return x*x + 2*x + 1; };
double integral1_trap = trapezoid_rule(polynomial, 0, 2, 100);
double integral1_simp = simpsons_rule(polynomial, 0, 2, 100);
// Both should be close to exact: [x³/3 + x² + x]₀² = 8/3 + 4 + 2 = 6.666...

// Example 2: Trigonometric integration  
auto trig_func = [](double x) { return std::cos(x) * std::exp(-x/10); };
double integral2 = simpsons_rule(trig_func, 0, M_PI, 1000);
```

### **Stellar Physics Application**
```cpp
#include "num_analysis/integration.h"
#include "physics/star_physics.h"

using namespace num_analysis::integration;
using namespace physics::stellar;

// Integrate time-varying luminosity to compute total energy
double S0 = fuel_stock(M_SUN);  // Available fuel
auto L_function = L_exp_decay;  // Exponentially decaying luminosity
double total_energy = simpsons_rule(L_function, 0, 1e10, 10000);
```

### **Convergence Testing**
```cpp
#include <vector>
#include <iostream>

void test_convergence(std::function<double(double)> f, double a, double b) {
    std::vector<int> n_values = {10, 50, 100, 500, 1000, 5000};
    
    std::cout << "n\tTrapezoidal\tSimpson's\n";
    for (int n : n_values) {
        double trap = trapezoid_rule(f, a, b, n);
        double simp = simpsons_rule(f, a, b, n);
        std::cout << n << "\t" << trap << "\t" << simp << "\n";
    }
}
```

---

## ⚙️ Implementation Details

### **Error Handling**
- **Invalid Subintervals**: Throws `std::invalid_argument` for $n \leq 0$
- **Simpson's Adjustment**: Automatically corrects odd $n$ to $n+1$
- **Function Evaluation**: No error checking for function domain violations

### **Performance Characteristics**
- **Time Complexity**: $O(n)$ for both methods
- **Space Complexity**: $O(1)$ - constant additional memory
- **Function Evaluations**: $n+1$ for trapezoidal, $n+1$ for Simpson's
- **Cache Efficiency**: Sequential memory access pattern

### **Numerical Stability**
- **Round-off Error**: Accumulates linearly with $n$
- **Large Intervals**: May suffer from catastrophic cancellation
- **Oscillatory Functions**: Special handling recommended

---

## 🔗 Integration with Other Modules

### **Direct Dependencies**
- **[`num_analysis::errors`](num_analysis_errors.md)** - Error analysis and bounds
- **Standard Library**: `<functional>`, `<stdexcept>`, `<cmath>`

### **Used By**
- **[`physics::stellar`](physics_stellar.md)** - `estimate_lifetime()` function
- **Testing Suite** - Validation of integration accuracy
- **Stellar Models** - Time-dependent luminosity integration

### **Data Flow**
```
Physics Functions → Integration Methods → Stellar Lifetime Calculations
```

---

## 🎯 Best Practices

### **Choosing the Right Method**
1. **Use Simpson's rule** for:
   - Smooth, continuous functions
   - High accuracy requirements
   - Moderate computational budgets

2. **Use Trapezoidal rule** for:
   - Quick estimates
   - Linear or piecewise linear functions
   - When function evaluation is expensive

3. **Consider specialized methods** for:
   - Highly oscillatory functions
   - Functions with discontinuities
   - Adaptive integration requirements

### **Parameter Selection**
```cpp
// General guidelines for choosing 'n'
int choose_n(double a, double b, double required_accuracy) {
    double interval_length = std::abs(b - a);
    
    // Start with 100 points per unit interval
    int base_n = static_cast<int>(100 * interval_length);
    
    // Increase for high accuracy requirements
    if (required_accuracy < 1e-6) base_n *= 10;
    if (required_accuracy < 1e-10) base_n *= 10;
    
    return base_n;
}
```

### **Error Estimation**
```cpp
double estimate_error(std::function<double(double)> f, double a, double b) {
    // Richardson extrapolation for error estimation
    double I1 = simpsons_rule(f, a, b, n);
    double I2 = simpsons_rule(f, a, b, 2*n);
    return std::abs(I2 - I1) / 15.0;  // Error estimate for Simpson's rule
}
```

---

## 📖 Theoretical Background

### **Trapezoidal Rule Derivation**
The trapezoidal rule approximates the integral area by:
1. Dividing $[a,b]$ into $n$ equal subintervals
2. Approximating each subinterval area with a trapezoid
3. Summing all trapezoid areas

For subinterval $[x_i, x_{i+1}]$:
$$\text{Area}_i \approx \frac{h}{2}[f(x_i) + f(x_{i+1})]$$

### **Simpson's Rule Derivation**
Simpson's rule uses quadratic interpolation:
1. Takes three consecutive points $(x_i, f(x_i))$, $(x_{i+1}, f(x_{i+1}))$, $(x_{i+2}, f(x_{i+2}))$
2. Fits a parabola through these points
3. Integrates the parabola analytically

The integration of a quadratic over $2h$ width yields the Simpson's coefficients (1, 4, 1).

### **Error Analysis**
For trapezoidal rule:
$$E_T = -\frac{(b-a)^3}{12n^2} f''(\xi)$$

For Simpson's rule:
$$E_S = -\frac{(b-a)^5}{180n^4} f^{(4)}(\xi)$$

where $\xi$ is some point in $[a,b]$.

---

## 🚀 Quick Reference

### **Function Signatures**
```cpp
double trapezoid_rule(std::function<double(double)> f, double a, double b, int n);
double simpsons_rule(std::function<double(double)> f, double a, double b, int n);
```

### **Common Usage Patterns**
```cpp
// Basic integration
double result = simpsons_rule(my_function, 0.0, 1.0, 1000);

// Error estimation
double estimate = trapezoid_rule(func, a, b, n);
double refined = trapezoid_rule(func, a, b, 2*n);
double error = std::abs(refined - estimate) / 3.0;

// Convergence testing
for (int n : {10, 100, 1000, 10000}) {
    std::cout << "n=" << n << ": " << simpsons_rule(func, a, b, n) << "\n";
}
```

---

*Numerical integration transforms continuous problems into discrete approximations.* 📊