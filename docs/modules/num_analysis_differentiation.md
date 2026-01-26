# Numerical Differentiation Module

**Module Overview for `num_analysis::differentiation` namespace**

---

## 📋 Module Overview

The `num_analysis::differentiation` namespace provides finite difference methods for numerical differentiation. These algorithms approximate derivatives of functions when analytical differentiation is not possible or practical, which is crucial for sensitivity analysis, optimization, and error estimation in stellar physics calculations.

### 🎯 **Purpose**
- Implement forward, backward, and central finite difference schemes
- Provide flexible numerical differentiation with controllable accuracy
- Support derivative calculations for function analysis
- Enable gradient-based computations and sensitivity studies

### 📁 **Files**
- **Header**: `include/num_analysis/differentiation.h`
- **Implementation**: `src/num_analysis/differentiation.cpp`

---

## 📐 Finite Difference Methods

### **Forward Difference Method**

#### **Mathematical Foundation**
The forward difference approximates the derivative using points ahead of the evaluation point. It's particularly useful when only forward information is available.

**Formula**:
$$f'(x) \approx \frac{f(x + h) - f(x)}{h}$$

**Taylor Series Expansion**:
$$f(x + h) = f(x) + hf'(x) + \frac{h^2}{2}f''(x) + O(h^3)$$

**Truncation Error**: $O(h)$ - first-order accurate

#### **Function Signature**
```cpp
double forward_diff(std::function<double(double)> f, double x, double h);
```

#### **Parameters**
- `f` - Function to differentiate (callable returning double)
- `x` - Point where derivative is evaluated
- `h` - Step size (must be positive)

#### **Return Value**
Numerical approximation of $f'(x)$

#### **Characteristics**
- **Accuracy**: First-order ($O(h)$)
- **Best Use**: One-sided derivatives, endpoint calculations
- **Limitations**: Less accurate than central difference for interior points
- **Step Size Sensitivity**: Balance between truncation and round-off error

#### **Usage Example**
```cpp
#include "num_analysis/differentiation.h"
#include <cmath>

using namespace num_analysis::differentiation;

// Differentiate f(x) = sin(x) at x = π/2
auto sine_func = [](double x) { return std::sin(x); };
double derivative = forward_diff(sine_func, M_PI/2, 1e-6);
// Expected: cos(π/2) = 0, Actual: ~0 (within numerical precision)
```

---

### **Backward Difference Method**

#### **Mathematical Foundation**
The backward difference uses points behind the evaluation point, making it suitable for endpoint calculations from the right side.

**Formula**:
$$f'(x) \approx \frac{f(x) - f(x - h)}{h}$$

**Taylor Series Expansion**:
$$f(x - h) = f(x) - hf'(x) + \frac{h^2}{2}f''(x) - O(h^3)$$

**Truncation Error**: $O(h)$ - first-order accurate

#### **Function Signature**
```cpp
double backward_diff(std::function<double(double)> f, double x, double h);
```

#### **Parameters**
- `f` - Function to differentiate (callable returning double)
- `x` - Point where derivative is evaluated
- `h` - Step size (must be positive)

#### **Return Value**
Numerical approximation of $f'(x)$

#### **Characteristics**
- **Accuracy**: First-order ($O(h)$)
- **Best Use**: Right endpoint calculations, backward information only
- **Symmetry**: Mirror of forward difference method
- **Applications**: Time-stepping schemes, boundary conditions

#### **Usage Example**
```cpp
#include "num_analysis/differentiation.h"
#include <cmath>

using namespace num_analysis::differentiation;

// Differentiate f(x) = x² at x = 2
auto quadratic = [](double x) { return x * x; };
double derivative = backward_diff(quadratic, 2.0, 1e-6);
// Expected: 2*2 = 4, Actual: ~4 (high accuracy)
```

---

### **Central Difference Method**

#### **Mathematical Foundation**
The central difference provides the highest accuracy among the three methods by using symmetric points around the evaluation point.

**Formula**:
$$f'(x) \approx \frac{f(x + h) - f(x - h)}{2h}$$

**Taylor Series Expansion**:
$$f(x + h) = f(x) + hf'(x) + \frac{h^2}{2}f''(x) + \frac{h^3}{6}f'''(x) + O(h^4)$$
$$f(x - h) = f(x) - hf'(x) + \frac{h^2}{2}f''(x) - \frac{h^3}{6}f'''(x) + O(h^4)$$

Subtracting and solving for $f'(x)$ gives the central difference formula.

**Truncation Error**: $O(h^2)$ - second-order accurate

#### **Function Signature**
```cpp
double central_diff(std::function<double(double)> f, double x, double h);
```

#### **Parameters**
- `f` - Function to differentiate (callable returning double)
- `x` - Point where derivative is evaluated
- `h` - Step size (must be positive)

#### **Return Value**
Numerical approximation of $f'(x)$

#### **Characteristics**
- **Accuracy**: Second-order ($O(h^2)$) - most accurate of the three
- **Best Use**: Interior point calculations, general-purpose differentiation
- **Symmetry**: Eliminates even-order error terms
- **Efficiency**: Same computational cost as first-order methods

#### **Usage Example**
```cpp
#include "num_analysis/differentiation.h"
#include <cmath>

using namespace num_analysis::differentiation;

// Differentiate f(x) = exp(x) at x = 1
auto exponential = [](double x) { return std::exp(x); };
double derivative = central_diff(exponential, 1.0, 1e-6);
// Expected: e¹ ≈ 2.71828, Actual: ~2.71828 (very high accuracy)
```

---

## 🔍 Method Comparison

### **Accuracy Analysis**

| Method | Order | Error Term | Step Size Sensitivity | Best Application |
|--------|-------|------------|----------------------|------------------|
| Forward | $O(h)$ | $-\frac{h}{2}f''(x)$ | High sensitivity | Left endpoints |
| Backward | $O(h)$ | $\frac{h}{2}f''(x)$ | High sensitivity | Right endpoints |
| Central | $O(h^2)$ | $-\frac{h^2}{6}f'''(x)$ | Lower sensitivity | Interior points |

### **Convergence Behavior**

For a smooth function $f(x)$ with continuous derivatives:

```
Error ∝ h     (Forward/Backward Difference)
Error ∝ h²    (Central Difference)
```

This means central difference converges much faster as $h \to 0$.

### **Computational Cost**

| Method | Function Evaluations | Computational Complexity |
|--------|---------------------|-------------------------|
| Forward | 2 | $O(1)$ |
| Backward | 2 | $O(1)$ |
| Central | 2 | $O(1)$ |

All methods have the same computational cost, making central difference the clear choice for interior points.

---

## 💡 Practical Usage Examples

### **Basic Differentiation**
```cpp
#include "num_analysis/differentiation.h"
#include <cmath>
#include <iostream>

using namespace num_analysis::differentiation;

void demonstrate_methods() {
    // Test function: f(x) = x³
    auto cubic = [](double x) { return x * x * x; };
    double x = 2.0;
    double h = 1e-6;
    
    // Exact derivative: f'(x) = 3x² = 12 at x=2
    double forward = forward_diff(cubic, x, h);
    double backward = backward_diff(cubic, x, h);
    double central = central_diff(cubic, x, h);
    
    std::cout << "Expected: 12\n";
    std::cout << "Forward: " << forward << "\n";
    std::cout << "Backward: " << backward << "\n";
    std::cout << "Central: " << central << "\n";
    
    // Central difference should be most accurate
}
```

### **Step Size Optimization**
```cpp
#include <vector>
#include <algorithm>

double find_optimal_step_size(std::function<double(double)> f, double x) {
    std::vector<double> step_sizes = {1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8};
    
    std::cout << "Step Size\tCentral Difference\tError Estimate\n";
    
    for (double h : step_sizes) {
        double derivative = central_diff(f, x, h);
        // Use Richardson extrapolation for error estimation
        double refined = central_diff(f, x, h/2);
        double error_estimate = std::abs(refined - derivative) / 3.0;
        
        std::cout << h << "\t" << derivative << "\t" << error_estimate << "\n";
    }
    
    return 1e-6; // Typical good choice
}
```

### **Function Analysis**
```cpp
#include <vector>
#include <fstream>

void analyze_function(std::function<double(double)> f, 
                    std::function<double(double)> exact_derivative,
                    double a, double b, int num_points) {
    std::ofstream results("derivative_analysis.csv");
    results << "x,Exact,Numerical,Error\n";
    
    double h = 1e-6;
    double dx = (b - a) / (num_points - 1);
    
    for (int i = 0; i < num_points; ++i) {
        double x = a + i * dx;
        double exact = exact_derivative(x);
        double numerical = central_diff(f, x, h);
        double error = std::abs(exact - numerical);
        
        results << x << "," << exact << "," << numerical << "," << error << "\n";
    }
    
    results.close();
}
```

---

## ⚙️ Implementation Details

### **Error Handling**
- **Invalid Step Size**: Throws `std::invalid_argument` for $h \leq 0$
- **Function Domain**: No checking for function domain violations
- **Numerical Issues**: No automatic detection of catastrophic cancellation

### **Performance Characteristics**
- **Time Complexity**: $O(1)$ for all methods
- **Space Complexity**: $O(1)$ - constant additional memory
- **Function Evaluations**: Exactly 2 evaluations per derivative calculation

### **Numerical Stability**
- **Round-off Error**: Increases as $h \to 0$
- **Truncation Error**: Decreases as $h \to 0$
- **Optimal Balance**: Typically $h \approx \sqrt{\epsilon_{machine}}$ for central difference

### **Step Size Guidelines**
```cpp
double recommend_step_size(double x, double function_scale = 1.0) {
    const double machine_epsilon = 2.220446049250313e-16;
    return std::sqrt(machine_epsilon) * std::max(1.0, std::abs(x)) * function_scale;
}
```

---

## 🔗 Integration with Other Modules

### **Direct Dependencies**
- **[`num_analysis::errors`](num_analysis_errors.md)** - Error calculation functions
- **Standard Library**: `<functional>`, `<stdexcept>`, `<cmath>`

### **Used By**
- **Potential Applications**: Sensitivity analysis, optimization, error estimation
- **Testing Suite**: Validation of differentiation accuracy
- **Future Extensions**: Gradient-based stellar evolution models

### **Data Flow**
```
Function Input → Differentiation Method → Derivative Output → Error Analysis
```

---

## 🎯 Best Practices

### **Choosing the Right Method**

1. **Use Central Difference** for:
   - Interior point calculations
   - Highest accuracy requirements
   - General-purpose differentiation
   - When function is smooth and well-behaved

2. **Use Forward Difference** for:
   - Left endpoint calculations
   - One-sided information only
   - Real-time applications where future data is available
   - Initial condition problems

3. **Use Backward Difference** for:
   - Right endpoint calculations
   - Historical data analysis
   - Time-stepping from past to present
   - Boundary condition problems

### **Step Size Selection**
```cpp
// Adaptive step size selection
double adaptive_step_size(std::function<double(double)> f, double x) {
    double h = 1e-6;  // Initial guess
    
    // Refine based on function behavior
    double d1 = central_diff(f, x, h);
    double d2 = central_diff(f, x, h/2);
    
    // If change is too large, reduce step size
    while (std::abs(d2 - d1) > 1e-10 && h > 1e-12) {
        h /= 2;
        d1 = central_diff(f, x, h);
        d2 = central_diff(f, x, h/2);
    }
    
    return h;
}
```

### **Error Estimation**
```cpp
double richardson_extrapolation(std::function<double(double)> f, double x, double h) {
    // Central difference with Richardson extrapolation
    double D1 = central_diff(f, x, h);
    double D2 = central_diff(f, x, h/2);
    
    // Richardson extrapolation: D_extrap = D2 + (D2 - D1)/3
    return D2 + (D2 - D1) / 3.0;
}
```

### **Function Suitability**
```cpp
bool is_suitable_for_numerical_diff(std::function<double(double)> f, double x, double h) {
    // Check for potential issues
    double fx = f(x);
    double fxh = f(x + h);
    double fxmh = f(x - h);
    
    // Check for NaN or infinite values
    if (std::isnan(fx) || std::isnan(fxh) || std::isnan(fxmh)) return false;
    if (std::isinf(fx) || std::isinf(fxh) || std::isinf(fxmh)) return false;
    
    // Check for extreme jumps (possible discontinuities)
    double relative_jump1 = std::abs(fxh - fx) / std::abs(fx);
    double relative_jump2 = std::abs(fxmh - fx) / std::abs(fx);
    
    return (relative_jump1 < 100.0) && (relative_jump2 < 100.0);
}
```

---

## 📖 Theoretical Background

### **Finite Difference Derivation**

**Forward Difference**:
Starting from Taylor expansion:
$$f(x + h) = f(x) + hf'(x) + \frac{h^2}{2}f''(\xi)$$

Solving for $f'(x)$:
$$f'(x) = \frac{f(x + h) - f(x)}{h} - \frac{h}{2}f''(\xi)$$

**Backward Difference**:
$$f(x - h) = f(x) - hf'(x) + \frac{h^2}{2}f''(\xi)$$

Solving for $f'(x)$:
$$f'(x) = \frac{f(x) - f(x - h)}{h} + \frac{h}{2}f''(\xi)$$

**Central Difference**:
Subtracting the two Taylor expansions:
$$f(x + h) - f(x - h) = 2hf'(x) + \frac{h^3}{3}f'''(\xi)$$

Solving for $f'(x)$:
$$f'(x) = \frac{f(x + h) - f(x - h)}{2h} - \frac{h^2}{6}f'''(\xi)$$

### **Error Analysis**

The total error in numerical differentiation consists of:
1. **Truncation Error**: From Taylor series approximation
2. **Round-off Error**: From finite precision arithmetic

**Total Error**: $E_{total} = E_{truncation} + E_{round-off}$

For central difference:
$$E_{truncation} \approx \frac{h^2}{6}|f'''(x)|$$
$$E_{round-off} \approx \frac{\epsilon}{h}(|f(x)| + |f'(x)|)$$

Optimal $h$ occurs when these errors are balanced:
$$h_{optimal} \approx \sqrt{\frac{6\epsilon}{|f'''(x)|}}$$

---

## 🚀 Quick Reference

### **Function Signatures**
```cpp
double forward_diff(std::function<double(double)> f, double x, double h);
double backward_diff(std::function<double(double)> f, double x, double h);
double central_diff(std::function<double(double)> f, double x, double h);
```

### **Common Usage Patterns**
```cpp
// Best practice for interior points
double derivative = central_diff(my_function, x_point, 1e-6);

// Endpoint calculations
double left_derivative = forward_diff(my_function, left_endpoint, 1e-6);
double right_derivative = backward_diff(my_function, right_endpoint, 1e-6);

// Error estimation with Richardson extrapolation
double refined = richardson_extrapolation(my_function, x, h);
```

---

*Numerical differentiation converts continuous derivatives into discrete approximations.* 📈