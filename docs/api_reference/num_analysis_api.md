# Numerical Analysis API Reference

**Complete API Reference for Numerical Analysis Modules**

---

## 📋 Overview

This section provides a comprehensive reference for all numerical analysis functions in the Star Lifetime project, including integration, differentiation, and error analysis methods.

### 📁 **Related Files**
- **Headers**: `include/num_analysis/integration.h`, `include/num_analysis/differentiation.h`, `include/num_analysis/errors.h`
- **Source**: `src/num_analysis/integration.cpp`, `src/num_analysis/differentiation.cpp`, `src/num_analysis/errors.cpp`

---

## 🧮 num_analysis::integration Namespace

### **Integration Methods**

#### **`trapezoid_rule()`**

**Purpose**: Approximate definite integral using composite trapezoidal rule

```cpp
double trapezoid_rule(std::function<double(double)> f, double a, double b, int n);
```

**Parameters**:
- `f` (std::function<double(double)>): Function to integrate
- `a` (double): Lower limit of integration
- `b` (double): Upper limit of integration
- `n` (int): Number of subintervals (must be positive)

**Returns**: Approximation of $\int_a^b f(x) \,dx$

**Formula**: $h \left[ \frac{f(a) + f(b)}{2} + \sum_{i=1}^{n-1} f(a + ih) \right]$

**where**: $h = \frac{b-a}{n}$

**Accuracy**: $O(h^2)$ local truncation error

**Throws**: `std::invalid_argument` if $n \leq 0$

**Example**:
```cpp
auto sine = [](double x) { return std::sin(x); };
double result = trapezoid_rule(sine, 0, M_PI, 1000);  // ≈ 2.0
```

---

#### **`simpsons_rule()`**

**Purpose**: Approximate definite integral using composite Simpson's rule

```cpp
double simpsons_rule(std::function<double(double)> f, double a, double b, int n);
```

**Parameters**:
- `f` (std::function<double(double)>): Function to integrate
- `a` (double): Lower limit of integration
- `b` (double): Upper limit of integration
- `n` (int): Number of subintervals (auto-adjusted to even if odd)

**Returns**: Approximation of $\int_a^b f(x) \,dx$

**Formula**: $\frac{h}{3} \left[ f(a) + f(b) + 4\sum_{\text{odd } i} f(a + ih) + 2\sum_{\text{even } i} f(a + ih) \right]$

**where**: $h = \frac{b-a}{n}$ and $n$ is even

**Accuracy**: $O(h^4)$ local truncation error

**Throws**: `std::invalid_argument` if $n \leq 0$

**Auto-correction**: If $n$ is odd, automatically uses $n+1$

**Example**:
```cpp
auto exponential = [](double x) { return std::exp(x); };
double result = simpsons_rule(exponential, 0, 1, 100);  // ≈ e - 1
```

---

## 📐 num_analysis::differentiation Namespace

### **Differentiation Methods**

#### **`forward_diff()`**

**Purpose**: Approximate derivative using forward finite difference

```cpp
double forward_diff(std::function<double(double)> f, double x, double h);
```

**Parameters**:
- `f` (std::function<double(double)>): Function to differentiate
- `x` (double): Point where derivative is evaluated
- `h` (double): Step size (must be positive)

**Returns**: Approximation of $f'(x)$

**Formula**: $\frac{f(x + h) - f(x)}{h}$

**Accuracy**: $O(h)$ first-order accurate

**Throws**: `std::invalid_argument` if $h \leq 0$

**Example**:
```cpp
auto quadratic = [](double x) { return x * x; };
double derivative = forward_diff(quadratic, 2.0, 1e-6);  // ≈ 4.0
```

---

#### **`backward_diff()`**

**Purpose**: Approximate derivative using backward finite difference

```cpp
double backward_diff(std::function<double(double)> f, double x, double h);
```

**Parameters**:
- `f` (std::function<double(double)>): Function to differentiate
- `x` (double): Point where derivative is evaluated
- `h` (double): Step size (must be positive)

**Returns**: Approximation of $f'(x)$

**Formula**: $\frac{f(x) - f(x - h)}{h}$

**Accuracy**: $O(h)$ first-order accurate

**Throws**: `std::invalid_argument` if $h \leq 0$

**Example**:
```cpp
auto cubic = [](double x) { return x * x * x; };
double derivative = backward_diff(cubic, 1.0, 1e-6);  // ≈ 3.0
```

---

#### **`central_diff()`**

**Purpose**: Approximate derivative using central finite difference

```cpp
double central_diff(std::function<double(double)> f, double x, double h);
```

**Parameters**:
- `f` (std::function<double(double)>): Function to differentiate
- `x` (double): Point where derivative is evaluated
- `h` (double): Step size (must be positive)

**Returns**: Approximation of $f'(x)$

**Formula**: $\frac{f(x + h) - f(x - h)}{2h}$

**Accuracy**: $O(h^2)$ second-order accurate

**Throws**: `std::invalid_argument` if $h \leq 0$

**Example**:
```cpp
auto exponential = [](double x) { return std::exp(x); };
double derivative = central_diff(exponential, 1.0, 1e-6);  // ≈ e
```

---

## 📏 num_analysis::errors Namespace

### **Error Metrics**

#### **`absolute_error()`**

**Purpose**: Calculate absolute error between exact and approximate values

```cpp
double absolute_error(double exact, double approx);
```

**Parameters**:
- `exact` (double): True or reference value
- `approx` (double): Computed or approximate value

**Returns**: $|x_{exact} - x_{approx}|$

**Formula**: $E_{absolute} = |x_{exact} - x_{approx}|$

**Throws**: None

**Example**:
```cpp
double error = absolute_error(2.0, 1.999999);  // ≈ 1e-6
```

---

#### **`relative_error()`**

**Purpose**: Calculate relative error between exact and approximate values

```cpp
double relative_error(double exact, double approx);
```

**Parameters**:
- `exact` (double): True or reference value (must be non-zero)
- `approx` (double): Computed or approximate value

**Returns**: $\left|\frac{x_{exact} - x_{approx}}{x_{exact}}\right|$

**Formula**: $E_{relative} = \left|\frac{x_{exact} - x_{approx}}{x_{exact}}\right|$

**Throws**: `std::invalid_argument` if `exact == 0`

**Example**:
```cpp
double error = relative_error(100.0, 99.9);  // ≈ 0.001
```

---

### **Error Bounds**

#### **`trapezoid_error()`**

**Purpose**: Calculate theoretical error bound for trapezoidal rule

```cpp
double trapezoid_error(double a, double b, int n, double max_second_derivative);
```

**Parameters**:
- `a` (double): Lower limit of integration
- `b` (double): Upper limit of integration
- `n` (int): Number of subintervals (must be positive)
- `max_second_derivative` (double): Maximum absolute value of $|f''(x)|$ on $[a,b]$

**Returns**: Theoretical upper bound on trapezoidal rule error

**Formula**: $\frac{(b-a)^3}{12n^2} \max_{\xi \in [a,b]} |f''(\xi)|$

**Throws**: `std::invalid_argument` if $n \leq 0$

**Example**:
```cpp
double bound = trapezoid_error(0, M_PI, 100, 1.0);  // For sin(x) on [0,π]
```

---

#### **`simpson_error()`**

**Purpose**: Calculate theoretical error bound for Simpson's rule

```cpp
double simpson_error(double a, double b, int n, double max_fourth_derivative);
```

**Parameters**:
- `a` (double): Lower limit of integration
- `b` (double): Upper limit of integration
- `n` (int): Number of subintervals (must be positive)
- `max_fourth_derivative` (double): Maximum absolute value of $|f^{(4)}(x)|$ on $[a,b]$

**Returns**: Theoretical upper bound on Simpson's rule error

**Formula**: $\frac{(b-a)^5}{180n^4} \max_{\xi \in [a,b]} |f^{(4)}(\xi)|$

**Throws**: `std::invalid_argument` if $n \leq 0$

**Example**:
```cpp
double bound = simpson_error(0, 1, 100, std::exp(1.0));  // For exp(x) on [0,1]
```

---

## 🔧 Type Definitions

### **Function Types**

#### **Integration Functions**
```cpp
typedef std::function<double(double)> IntegrandFunction;
```
**Used for**: All integration method parameters
**Signature**: `double func(double x)`

**Compatible Examples**:
```cpp
// Lambda functions
auto lambda = [](double x) { return std::sin(x); };

// Function pointers
double my_func(double x) { return x * x; }

// Standard library functions
std::function<double(double)> exp_func = std::exp;
```

#### **Differentiation Functions**
```cpp
typedef std::function<double(double)> DerivativeFunction;
```
**Used for**: All differentiation method parameters
**Signature**: `double func(double x)`

---

## 📊 Performance Characteristics

### **Computational Complexity**

| Method | Time Complexity | Space Complexity | Function Evaluations |
|--------|----------------|------------------|---------------------|
| `trapezoid_rule` | $O(n)$ | $O(1)$ | $n+1$ |
| `simpsons_rule` | $O(n)$ | $O(1)$ | $n+1$ |
| `forward_diff` | $O(1)$ | $O(1)$ | 2 |
| `backward_diff` | $O(1)$ | $O(1)$ | 2 |
| `central_diff` | $O(1)$ | $O(1)$ | 2 |
| Error functions | $O(1)$ | $O(1)$ | 0 |

### **Accuracy Comparison**

| Method | Order | Error Reduction Rate |
|--------|-------|-------------------|
| Trapezoidal | $O(h^2)$ | 4× when n doubles |
| Simpson's | $O(h^4)$ | 16× when n doubles |
| Forward/Backward Diff | $O(h)$ | 2× when h halves |
| Central Diff | $O(h^2)$ | 4× when h halves |

---

## 🎯 Usage Patterns

### **Integration with Error Analysis**
```cpp
#include "num_analysis/integration.h"
#include "num_analysis/errors.h"

void integrate_with_error_bounds() {
    auto func = [](double x) { return std::exp(-x * x); };
    double a = 0.0, b = 2.0;
    int n = 100;
    
    // Compute integral
    double result = simpsons_rule(func, a, b, n);
    
    // Calculate error bound
    double max_fourth = 12.0;  // |d⁴/dx⁴(e^(-x²))| ≤ 12 on [0,2]
    double error_bound = simpson_error(a, b, n, max_fourth);
    
    std::cout << "Integral: " << result << " ± " << error_bound << "\n";
}
```

### **Differentiation with Error Estimation**
```cpp
#include "num_analysis/differentiation.h"
#include "num_analysis/errors.h"

void differentiate_with_accuracy() {
    auto func = [](double x) { return std::sin(x) * std::exp(-x/10); };
    double x = 1.0;
    double h = 1e-6;
    
    // Calculate derivative
    double derivative = central_diff(func, x, h);
    
    // Estimate error using Richardson extrapolation
    double refined = central_diff(func, x, h/2);
    double error_estimate = std::abs(refined - derivative) / 3.0;
    
    std::cout << "Derivative: " << derivative << " ± " << error_estimate << "\n";
}
```

### **Adaptive Integration**
```cpp
double adaptive_integration(std::function<double(double)> f, double a, double b, 
                          double tolerance, int max_iterations = 10) {
    int n = 10;
    double result, error_bound;
    
    for (int i = 0; i < max_iterations; ++i) {
        result = simpsons_rule(f, a, b, n);
        
        // Estimate error bound (requires max fourth derivative)
        double error_bound = simpson_error(a, b, n, /* max_f4_value */ 1.0);
        
        if (error_bound <= tolerance) {
            return result;
        }
        
        n *= 2;  // Double the resolution
    }
    
    return result;  // Return best effort
}
```

---

## 🚀 Quick Reference

### **Integration Examples**
```cpp
// Basic integration
auto f = [](double x) { return std::sin(x); };
double trap = trapezoid_rule(f, 0, M_PI, 1000);
double simp = simpsons_rule(f, 0, M_PI, 1000);

// Error analysis
double abs_err = absolute_error(2.0, trap);
double rel_err = relative_error(2.0, trap);
double bound = simpson_error(0, M_PI, 1000, 1.0);
```

### **Differentiation Examples**
```cpp
// Numerical derivatives
auto g = [](double x) { return x * x * x; };
double forward = forward_diff(g, 2.0, 1e-6);
double central = central_diff(g, 2.0, 1e-6);
double backward = backward_diff(g, 2.0, 1e-6);

// Central difference is most accurate
```

### **Error Analysis Examples**
```cpp
// Error calculations
double exact = 2.0, approx = 1.999999;
double abs_err = absolute_error(exact, approx);
double rel_err = relative_error(exact, approx);

// Theoretical bounds
double trap_bound = trapezoid_error(0, M_PI, 100, 1.0);
double simp_bound = simpson_error(0, M_PI, 100, 1.0);
```

---

## 🔗 Module Dependencies

### **External Dependencies**
- **Standard Library**: `<functional>`, `<cmath>`, `<stdexcept>`, `<iomanip>`

### **Internal Dependencies**
- **No cross-module dependencies** (self-contained numerical methods)

### **Used By**
- **[`physics::stellar`](physics_api.md)** - `estimate_lifetime()` function
- **Testing Suite** - Accuracy validation and convergence studies

---

*This API reference provides complete function signatures for numerical analysis methods.* 📊