# Numerical Error Analysis Module

**Module Overview for `num_analysis::errors` namespace**

---

## 📋 Module Overview

The `num_analysis::errors` namespace provides comprehensive error analysis tools for numerical computations. This module is essential for validating the accuracy of numerical methods, quantifying uncertainties, and establishing confidence intervals in stellar physics calculations.

### 🎯 **Purpose**
- Calculate absolute and relative errors between exact and approximate values
- Provide theoretical error bounds for numerical integration methods
- Enable error estimation and validation of numerical results
- Support quality assurance in computational physics

### 📁 **Files**
- **Header**: `include/num_analysis/errors.h`
- **Implementation**: `src/num_analysis/errors.cpp`

---

## 📏 Error Metrics

### **Absolute Error**

#### **Mathematical Definition**
The absolute error measures the magnitude of the difference between exact and approximate values, regardless of sign.

**Formula**:
$$E_{absolute} = |x_{exact} - x_{approx}|$$

#### **Function Signature**
```cpp
double absolute_error(double exact, double approx);
```

#### **Parameters**
- `exact` - The true or reference value
- `approx` - The computed or approximate value

#### **Return Value**
Non-negative absolute error value

#### **Physical Interpretation**
- **Units**: Same as the input quantities
- **Meaning**: Absolute magnitude of deviation
- **Use Case**: When absolute accuracy is important
- **Context**: Physical quantities with fixed scales

#### **Usage Example**
```cpp
#include "num_analysis/errors.h"
#include <cmath>

using namespace num_analysis::errors;

// Compare numerical integration with known result
double exact_integral = 2.0;  // ∫₀^π sin(x) dx = 2
double numerical_result = 1.999999;
double error = absolute_error(exact_integral, numerical_result);
// error ≈ 1e-6
```

---

### **Relative Error**

#### **Mathematical Definition**
The relative error normalizes the absolute error by the magnitude of the exact value, providing a scale-independent measure of accuracy.

**Formula**:
$$E_{relative} = \left|\frac{x_{exact} - x_{approx}}{x_{exact}}\right|$$

#### **Function Signature**
```cpp
double relative_error(double exact, double approx);
```

#### **Parameters**
- `exact` - The true or reference value (must be non-zero)
- `approx` - The computed or approximate value

#### **Return Value**
Non-negative relative error (dimensionless)

#### **Exception Handling**
Throws `std::invalid_argument` when `exact == 0` (division by zero)

#### **Physical Interpretation**
- **Units**: Dimensionless (often expressed as percentage)
- **Meaning**: Fractional deviation from true value
- **Use Case**: When relative accuracy is important
- **Context**: Comparing results across different scales

#### **Usage Example**
```cpp
#include "num_analysis/errors.h"

using namespace num_analysis::errors;

// Compare stellar lifetime calculations
double exact_lifetime = 1e10;  // years
double computed_lifetime = 1.0001e10;  // years
double rel_error = relative_error(exact_lifetime, computed_lifetime);
// rel_error ≈ 1e-4 (0.01% error)
```

---

## 🧮 Theoretical Error Bounds

### **Trapezoidal Rule Error Bound**

#### **Mathematical Foundation**
The trapezoidal rule error bound provides a theoretical upper limit on the integration error based on the second derivative of the integrand.

**Error Formula**:
$$E_T \leq \frac{(b-a)^3}{12n^2} \max_{\xi \in [a,b]} |f''(\xi)|$$

#### **Function Signature**
```cpp
double trapezoid_error(double a, double b, int n, double max_second_derivative);
```

#### **Parameters**
- `a` - Lower limit of integration
- `b` - Upper limit of integration
- `n` - Number of subintervals (must be positive)
- `max_second_derivative` - Maximum absolute value of $|f''(x)|$ on $[a,b]$

#### **Return Value**
Theoretical upper bound on trapezoidal rule error

#### **Physical Interpretation**
- **Units**: Same units as the integral
- **Meaning**: Guaranteed upper limit on error magnitude
- **Use Case**: Error estimation and step size selection
- **Accuracy**: Conservative bound (actual error may be smaller)

#### **Usage Example**
```cpp
#include "num_analysis/errors.h"
#include <cmath>

using namespace num_analysis::errors;

// Error bound for ∫₀^π sin(x) dx using trapezoidal rule
// f(x) = sin(x), f''(x) = -sin(x), so |f''(x)| ≤ 1
double a = 0.0, b = M_PI;
int n = 100;
double max_f2 = 1.0;  // Maximum of |sin(x)| on [0,π]

double error_bound = trapezoid_error(a, b, n, max_f2);
// Provides conservative error estimate
```

---

### **Simpson's Rule Error Bound**

#### **Mathematical Foundation**
Simpson's rule error bound uses the fourth derivative to provide a much tighter error estimate than the trapezoidal rule.

**Error Formula**:
$$E_S \leq \frac{(b-a)^5}{180n^4} \max_{\xi \in [a,b]} |f^{(4)}(\xi)|$$

#### **Function Signature**
```cpp
double simpson_error(double a, double b, int n, double max_fourth_derivative);
```

#### **Parameters**
- `a` - Lower limit of integration
- `b` - Upper limit of integration
- `n` - Number of subintervals (must be positive)
- `max_fourth_derivative` - Maximum absolute value of $|f^{(4)}(x)|$ on $[a,b]$

#### **Return Value**
Theoretical upper bound on Simpson's rule error

#### **Physical Interpretation**
- **Units**: Same units as the integral
- **Meaning**: Guaranteed upper limit on error magnitude
- **Use Case**: High-precision error estimation
- **Accuracy**: Much tighter bound than trapezoidal rule

#### **Usage Example**
```cpp
#include "num_analysis/errors.h"
#include <cmath>

using namespace num_analysis::errors;

// Error bound for ∫₀^1 exp(x) dx using Simpson's rule
// f(x) = exp(x), f^(4)(x) = exp(x), so max on [0,1] = e
double a = 0.0, b = 1.0;
int n = 100;  // Must be even for Simpson's rule
double max_f4 = std::exp(1.0);  // Maximum of exp(x) on [0,1]

double error_bound = simpson_error(a, b, n, max_f4);
// Provides tight error estimate
```

---

## 🔍 Error Analysis Applications

### **Integration Accuracy Validation**
```cpp
#include "num_analysis/errors.h"
#include "num_analysis/integration.h"
#include <cmath>

using namespace num_analysis::errors;
using namespace num_analysis::integration;

void validate_integration() {
    // Test with known integral: ∫₀^π sin(x) dx = 2
    auto sine_func = [](double x) { return std::sin(x); };
    double exact = 2.0;
    
    // Trapezoidal rule
    int n_trap = 100;
    double trap_result = trapezoid_rule(sine_func, 0, M_PI, n_trap);
    double trap_error = absolute_error(exact, trap_result);
    double trap_bound = trapezoid_error(0, M_PI, n_trap, 1.0);
    
    // Simpson's rule
    int n_simp = 100;
    double simp_result = simpsons_rule(sine_func, 0, M_PI, n_simp);
    double simp_error = absolute_error(exact, simp_result);
    double simp_bound = simpson_error(0, M_PI, n_simp, 1.0);
    
    std::cout << "Trapezoidal - Error: " << trap_error << ", Bound: " << trap_bound << "\n";
    std::cout << "Simpson's   - Error: " << simp_error << ", Bound: " << simp_bound << "\n";
    
    // Actual errors should be less than theoretical bounds
}
```

### **Convergence Analysis**
```cpp
#include <vector>
#include <fstream>

void convergence_study(std::function<double(double)> f, double a, double b, double exact) {
    std::vector<int> n_values = {10, 20, 40, 80, 160, 320};
    
    std::ofstream results("convergence_analysis.csv");
    results << "n,Trapezoidal_Error,Simpson_Error,Trapezoidal_Bound,Simpson_Bound\n";
    
    for (int n : n_values) {
        double trap_val = trapezoid_rule(f, a, b, n);
        double simp_val = simpsons_rule(f, a, b, n);
        
        double trap_err = absolute_error(exact, trap_val);
        double simp_err = absolute_error(exact, simp_val);
        
        // For demonstration, assume maximum derivatives = 1
        double trap_bound = trapezoid_error(a, b, n, 1.0);
        double simp_bound = simpson_error(a, b, n, 1.0);
        
        results << n << "," << trap_err << "," << simp_err << "," 
                << trap_bound << "," << simp_bound << "\n";
    }
    
    results.close();
}
```

### **Adaptive Step Size Selection**
```cpp
int adaptive_step_size(std::function<double(double)> f, double a, double b, 
                      double tolerance, double max_derivative) {
    int n = 10;  // Start with coarse grid
    
    while (true) {
        double error_bound = simpson_error(a, b, n, max_derivative);
        
        if (error_bound <= tolerance) {
            return n;  // Sufficient accuracy achieved
        }
        
        // Double the number of subintervals (ensure even)
        n *= 2;
        
        // Prevent infinite loop
        if (n > 1000000) {
            std::cerr << "Warning: Could not achieve desired tolerance\n";
            return n;
        }
    }
}
```

---

## 📊 Error Comparison and Analysis

### **Method Accuracy Comparison**

| Method | Error Order | Typical Error Reduction | Computational Cost | Best Use Case |
|--------|-------------|------------------------|-------------------|---------------|
| Trapezoidal | $O(h^2)$ | 4× when n doubles | Low | Quick estimates |
| Simpson's | $O(h^4)$ | 16× when n doubles | Medium | High accuracy |

### **Error Scaling Behavior**

For a smooth function with continuous derivatives:

```
Trapezoidal Error ∝ 1/n²
Simpson's Error   ∝ 1/n⁴
```

This means:
- Doubling `n`: Trapezoidal error reduces by factor of 4, Simpson's by 16
- Increasing `n` from 100 to 1000: Trapezoidal error reduces by 100×, Simpson's by 10,000×

### **Practical Error Ranges**

| Number of Points | Trapezoidal Error | Simpson's Error | Relative Improvement |
|------------------|-------------------|-----------------|---------------------|
| n = 10 | ~10⁻² | ~10⁻³ | 10× better |
| n = 100 | ~10⁻⁴ | ~10⁻⁷ | 1000× better |
| n = 1000 | ~10⁻⁶ | ~10⁻¹¹ | 10⁵× better |

---

## ⚙️ Implementation Details

### **Error Handling**
- **Zero Division**: `relative_error()` throws for `exact == 0`
- **Invalid Parameters**: Both error bound functions throw for `n <= 0`
- **Derivative Estimates**: No automatic calculation of maximum derivatives

### **Numerical Considerations**
- **Floating Point Limits**: Error calculations subject to floating-point precision
- **Overflow Protection**: No special handling for extremely large values
- **Underflow Handling**: Relative error may suffer from catastrophic cancellation

### **Performance Characteristics**
- **Time Complexity**: $O(1)$ for all error calculation functions
- **Space Complexity**: $O(1)$ - constant additional memory
- **Computational Cost**: Minimal overhead for error analysis

---

## 🔗 Integration with Other Modules

### **Direct Dependencies**
- **Standard Library**: `<cmath>`, `<stdexcept>`

### **Used By**
- **[`num_analysis::integration`](num_analysis_integration.md)** - Error bounds for integration
- **[`physics::stellar`](physics_stellar.md)** - Validation of stellar calculations
- **Testing Suite** - Comprehensive accuracy validation

### **Data Flow**
```
Numerical Results → Error Analysis → Accuracy Assessment → Method Selection
```

---

## 🎯 Best Practices

### **Error Analysis Guidelines**

1. **Always Validate**: Compare numerical results with known analytical solutions
2. **Use Multiple Metrics**: Both absolute and relative errors provide different insights
3. **Consider Scale**: Use relative errors for scale-independent assessment
4. **Check Bounds**: Theoretical bounds provide guaranteed error limits

### **Step Size Selection**
```cpp
// Error-based step size selection
double select_step_size_for_tolerance(double tolerance, double max_derivative, 
                                   double interval_length) {
    // For Simpson's rule: error ≤ (b-a)⁵/(180n⁴) * max|f⁴|
    // Solve for n: n ≥ ((b-a)⁵ * max|f⁴| / (180 * tolerance))^(1/4)
    return std::pow(std::pow(interval_length, 5) * max_derivative / (180 * tolerance), 0.25);
}
```

### **Error Reporting**
```cpp
void report_integration_results(double exact, double approx, double a, double b, int n) {
    double abs_err = absolute_error(exact, approx);
    double rel_err = relative_error(exact, approx);
    
    std::cout << "Integration Results:\n";
    std::cout << "  Exact value: " << exact << "\n";
    std::cout << "  Approximate: " << approx << "\n";
    std::cout << "  Absolute error: " << abs_err << "\n";
    std::cout << "  Relative error: " << rel_err << "\n";
    
    // If derivatives are known, include theoretical bounds
    // double trap_bound = trapezoid_error(a, b, n, max_second_derivative);
    // double simp_bound = simpson_error(a, b, n, max_fourth_derivative);
}
```

### **Quality Assurance**
```cpp
bool meets_accuracy_requirements(double exact, double approx, 
                               double abs_tolerance, double rel_tolerance) {
    double abs_err = absolute_error(exact, approx);
    double rel_err = relative_error(exact, approx);
    
    return (abs_err <= abs_tolerance) && (rel_err <= rel_tolerance);
}
```

---

## 📖 Theoretical Background

### **Error Analysis Theory**

**Absolute Error** represents the absolute magnitude of deviation:
$$E_{abs} = |x_{true} - x_{approx}|$$

**Relative Error** normalizes by the true value:
$$E_{rel} = \frac{|x_{true} - x_{approx}|}{|x_{true}|}$$

### **Integration Error Derivation**

**Trapezoidal Rule Error**:
Using Taylor series expansion and integral remainder theorem:
$$E_T = -\frac{(b-a)^3}{12n^2} f''(\xi)$$
for some $\xi \in [a,b]$

Taking absolute value and maximum over interval:
$$|E_T| \leq \frac{(b-a)^3}{12n^2} \max_{\xi \in [a,b]} |f''(\xi)|$$

**Simpson's Rule Error**:
Similarly, using higher-order Taylor expansion:
$$E_S = -\frac{(b-a)^5}{180n^4} f^{(4)}(\xi)$$
for some $\xi \in [a,b]$

Taking absolute value and maximum:
$$|E_S| \leq \frac{(b-a)^5}{180n^4} \max_{\xi \in [a,b]} |f^{(4)}(\xi)|$$

### **Convergence Analysis**

The error bounds show theoretical convergence rates:
- **Trapezoidal**: $E_T = O(n^{-2})$
- **Simpson's**: $E_S = O(n^{-4})$

These theoretical rates match empirical observations for smooth functions.

---

## 🚀 Quick Reference

### **Function Signatures**
```cpp
double absolute_error(double exact, double approx);
double relative_error(double exact, double approx);
double trapezoid_error(double a, double b, int n, double max_second_derivative);
double simpson_error(double a, double b, int n, double max_fourth_derivative);
```

### **Common Usage Patterns**
```cpp
// Basic error calculation
double error = absolute_error(exact_value, computed_value);
double rel_error = relative_error(exact_value, computed_value);

// Error bound calculation
double bound = simpson_error(a, b, n, max_fourth_derivative);

// Accuracy validation
bool accurate = (absolute_error(exact, approx) < tolerance);
```

---

*Error analysis transforms uncertainty into quantifiable confidence.* 📊