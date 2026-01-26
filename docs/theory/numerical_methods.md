# Numerical Methods Theory

**Mathematical Foundations of Computational Algorithms**

---

## 📋 Overview

This section provides theoretical background for numerical methods used in the Star Lifetime project. Understanding the mathematics behind these algorithms is essential for choosing appropriate methods and interpreting results.

---

## 🧮 Numerical Integration Theory

### **Fundamental Problem**

Numerical integration approximates the definite integral:
$$I = \int_a^b f(x) \,dx$$

When analytical integration is impossible or impractical, numerical methods provide approximations by evaluating $f(x)$ at discrete points.

### **Error Analysis**

**True Integral vs Numerical Approximation**:
$$I = I_n + E_n$$

Where:
- $I_n$ = Numerical approximation with $n$ subintervals
- $E_n$ = Error term

**Convergence**: $\lim_{n \to \infty} I_n = I$

---

## 🔺 Trapezoidal Rule

### **Mathematical Derivation**

The trapezoidal rule approximates area under curve using trapezoids:

**Single Trapezoid**:
$$\int_{x_i}^{x_{i+1}} f(x) \,dx \approx \frac{h}{2}[f(x_i) + f(x_{i+1})]$$

**Composite Rule**:
$$I \approx \sum_{i=0}^{n-1} \frac{h}{2}[f(x_i) + f(x_{i+1})]$$

Simplifying:
$$I \approx h \left[ \frac{f(x_0) + f(x_n)}{2} + \sum_{i=1}^{n-1} f(x_i) \right]$$

### **Error Analysis**

**Taylor Series Expansion**:
$$f(x_i + h) = f(x_i) + hf'(x_i) + \frac{h^2}{2}f''(x_i) + \frac{h^3}{6}f'''(x_i) + O(h^4)$$

**Local Truncation Error**:
$$E_{local} = -\frac{h^3}{12}f''(\xi_i)$$

**Global Error**:
$$E_{global} = -\frac{(b-a)h^2}{12}f''(\xi)$$

**Accuracy**: $O(h^2)$ - second-order accurate

---

## 🔺 Simpson's Rule

### **Mathematical Derivation**

Simpson's rule uses quadratic interpolation through three points:

**Quadratic Interpolation**:
For points $(x_i, f_i)$, $(x_{i+1}, f_{i+1})$, $(x_{i+2}, f_{i+2})$:

$$P_2(x) = f_i \frac{(x-x_{i+1})(x-x_{i+2})}{(x_i-x_{i+1})(x_i-x_{i+2}) + f_{i+1}\frac{(x-x_i)(x-x_{i+2})}{(x_{i+1}-x_i)(x_{i+1}-x_{i+2})} + f_{i+2}\frac{(x-x_i)(x-x_{i+1})}{(x_{i+2}-x_i)(x_{i+2}-x_{i+1})}$$

**Integral over Two Subintervals**:
$$\int_{x_i}^{x_{i+2}} P_2(x) \,dx = \frac{h}{3}[f_i + 4f_{i+1} + f_{i+2}]$$

### **Composite Simpson's Rule**

Summing over pairs of subintervals:
$$I \approx \frac{h}{3} \left[ f(x_0) + f(x_n) + 4\sum_{\text{odd } i} f(x_i) + 2\sum_{\text{even } i} f(x_i) \right]$$

### **Error Analysis**

**Local Truncation Error**:
$$E_{local} = -\frac{h^5}{90}f^{(4)}(\xi_i)$$

**Global Error**:
$$E_{global} = -\frac{(b-a)h^4}{180}f^{(4)}(\xi)$$

**Accuracy**: $O(h^4)$ - fourth-order accurate

### **Why Simpson's is More Accurate**

1. **Higher Order**: Error term involves $h^4$ vs $h^2$ for trapezoidal
2. **Cancelling Terms**: Even-order error terms cancel due to symmetry
3. **Parabolic Fit**: Better approximation than linear for smooth functions

---

## 📐 Numerical Differentiation Theory

### **Fundamental Problem**

Numerical differentiation approximates:
$$f'(x) = \lim_{h \to 0} \frac{f(x+h) - f(x)}{h}$$

In practice, we use small but finite $h$ due to numerical limitations.

### **Taylor Series Foundation**

**Forward Expansion**:
$$f(x+h) = f(x) + hf'(x) + \frac{h^2}{2}f''(x) + \frac{h^3}{6}f'''(x) + O(h^4)$$

**Backward Expansion**:
$$f(x-h) = f(x) - hf'(x) + \frac{h^2}{2}f''(x) - \frac{h^3}{6}f'''(x) + O(h^4)$$

---

## 🔸 Forward Difference Method

### **Derivation**

From Taylor expansion, solving for $f'(x)$:
$$f'(x) = \frac{f(x+h) - f(x)}{h} - \frac{h}{2}f''(x) - O(h^2)$$

**Numerical Approximation**:
$$f'(x) \approx \frac{f(x+h) - f(x)}{h}$$

**Truncation Error**: $E = -\frac{h}{2}f''(x)$
**Accuracy**: $O(h)$ - first-order accurate

### **Characteristics**

- **One-sided**: Only uses forward information
- **Endpoint Use**: Can differentiate at domain boundaries
- **Error Propagation**: Second derivative term dominates error

---

## 🔸 Backward Difference Method

### **Derivation**

From backward Taylor expansion:
$$f'(x) = \frac{f(x) - f(x-h)}{h} + \frac{h}{2}f''(x) - O(h^2)$$

**Numerical Approximation**:
$$f'(x) \approx \frac{f(x) - f(x-h)}{h}$$

**Truncation Error**: $E = \frac{h}{2}f''(x)$
**Accuracy**: $O(h)$ - first-order accurate

### **Characteristics**

- **One-sided**: Only uses backward information
- **Endpoint Use**: Can differentiate at domain boundaries
- **Mirror of Forward**: Same accuracy, opposite information direction

---

## 🔸 Central Difference Method

### **Derivation**

Subtract backward from forward expansion:
$$f(x+h) - f(x-h) = 2hf'(x) + \frac{h^3}{3}f'''(x) + O(h^5)$$

Solving for $f'(x)$:
$$f'(x) = \frac{f(x+h) - f(x-h)}{2h} - \frac{h^2}{6}f'''(x) - O(h^4)$$

**Numerical Approximation**:
$$f'(x) \approx \frac{f(x+h) - f(x-h)}{2h}$$

**Truncation Error**: $E = -\frac{h^2}{6}f'''(x)$
**Accuracy**: $O(h^2)$ - second-order accurate

### **Why Central Difference is Superior**

1. **Symmetry**: Uses information from both sides
2. **Error Cancellation**: Even-order terms cancel
3. **Higher Accuracy**: $O(h^2)$ vs $O(h)$ for one-sided methods

---

## ⚖️ Error Analysis Theory

### **Sources of Error**

1. **Truncation Error**: From finite approximation of infinite series
2. **Round-off Error**: From finite precision arithmetic
3. **Propagation Error**: From accumulation of computational errors

### **Total Error**

$$E_{total} = E_{truncation} + E_{round-off}$$

### **Optimal Step Size**

Balance between competing errors:

**Truncation Error Decreases**: $E_{trunc} \propto h^p$ (where $p$ is method order)
**Round-off Error Increases**: $E_{round-off} \propto \frac{\epsilon}{h}$

**Optimal Balance**:
$$\frac{dE_{total}}{dh} = 0 \Rightarrow h_{optimal} \propto \epsilon^{1/(p+1)}$$

**Central Difference Example**:
$$h_{optimal} \approx \sqrt{\epsilon}$$ for double precision
$$h_{optimal} \approx 10^{-8}$$ (approximately)

### **Richardson Extrapolation**

**Concept**: Use multiple step sizes to estimate and eliminate leading error term.

**For Forward Difference**:
$$f'(x) \approx 2\frac{f(x+h) - f(x)}{h} - \frac{f(x+2h) - f(x+h)}{h}$$

**Error Reduction**: Eliminates $O(h)$ term, achieves $O(h^2)$

---

## 🔢 Convergence and Stability

### **Convergence Rate**

**Definition**: Method converges with order $p$ if:
$$\lim_{h \to 0} \frac{|I(h) - I|}{|I(h/2) - I|} = 2^p$$

**Practical Test**: Compute with halved step sizes and verify convergence.

### **Stability Analysis**

**Definition**: Method is stable if small perturbations don't grow unboundedly.

**Integration Stability**:
- **Explicit Methods**: Can be unstable for stiff problems
- **Implicit Methods**: More stable but computationally expensive

**Differentiation Stability**:
- **Step Size Sensitivity**: Very small $h$ causes catastrophic cancellation
- **Function Behavior**: Discontinuities cause large errors

---

## 📊 Practical Considerations

### **Function Properties**

**Smoothness Requirements**:
- **Integration**: $C^2$ (continuous second derivative) for $O(h^2)$
- **Differentiation**: $C^3$ (continuous third derivative) for $O(h^2)$

**Discontinuities**:
- **Integration**: Adaptive methods or domain splitting
- **Differentiation**: Avoid differentiation across discontinuities

### **Computational Efficiency**

**Operation Counts**:

| Method | Function Evaluations | Memory | Computational Cost |
|--------|-------------------|--------|-------------------|
| Trapezoidal | $n+1$ | $O(1)$ | $O(n)$ |
| Simpson's | $n+1$ | $O(1)$ | $O(n)$ |
| Forward Diff | 2 | $O(1)$ | $O(1)$ |
| Central Diff | 2 | $O(1)$ | $O(1)$ |

### **Accuracy vs. Cost Trade-offs**

**Integration Methods**:
- **Trapezoidal**: Lower accuracy, simpler implementation
- **Simpson's**: Higher accuracy, similar cost
- **Higher Order**: Even better accuracy, more complex

**Differentiation Methods**:
- **One-sided**: Endpoint capability, lower accuracy
- **Central**: Higher accuracy, requires two-sided access

---

## 🎯 Method Selection Guidelines

### **Integration Method Selection**

**Use Trapezoidal** when:
- Function is piecewise linear
- Quick approximation needed
- Implementation simplicity is important
- Function has limited smoothness

**Use Simpson's** when:
- Function is smooth ($C^4$ or better)
- High accuracy required
- Computational cost is acceptable
- Function is well-behaved

### **Differentiation Method Selection**

**Use Forward/Backward** when:
- Computing at domain boundaries
- Only one-sided information available
- Computational efficiency is critical
- Lower accuracy is acceptable

**Use Central** when:
- Computing interior derivatives
- High accuracy required
- Two-sided information available
- Function is sufficiently smooth

### **Parameter Selection**

**Step Size Guidelines**:
```cpp
// For double precision
double machine_epsilon = 2.220446049250313e-16;

// Integration step size
double h_integration = std::pow(machine_epsilon, 1.0/3.0);

// Differentiation step size
double h_differentiation = std::pow(machine_epsilon, 1.0/2.0);
```

---

## 📖 Advanced Topics

### **Adaptive Methods**

**Adaptive Integration**:
- **Richardson Extrapolation**: Romberg integration
- **Error Estimation**: Automatic step size adjustment
- **Recursive Bisection**: Adaptive Simpson's method

### **Higher-Order Methods**

**Integration**:
- **Gaussian Quadrature**: Optimal point selection
- **Clenshaw-Curtis**: Spectral methods
- **Monte Carlo**: High-dimensional integrals

**Differentiation**:
- **Higher-Order Finite Differences**: $O(h^4)$ methods
- **Complex Step**: Avoids subtraction cancellation
- **Automatic Differentiation**: Algorithmic differentiation

### **Specialized Applications**

**Stellar Physics Context**:
- **Oscillatory Integrals**: Specialized quadrature
- **Singular Integrals**: Principal value methods
- **Multi-dimensional**: Stellar structure equations

---

## 🔗 Implementation Connection

### **Theory to Code**

The mathematical formulas translate directly to implementation:

**Trapezoidal Rule**:
```cpp
double trapezoid_rule(std::function<double(double)> f, double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    
    for (int i = 1; i < n; ++i) {
        sum += f(a + i * h);
    }
    
    return h * sum;  // Implements h[0.5(f(a)+f(b)) + Σf(x_i)]
}
```

**Central Difference**:
```cpp
double central_diff(std::function<double(double)> f, double x, double h) {
    return (f(x + h) - f(x - h)) / (2 * h);  // Implements (f(x+h)-f(x-h))/(2h)
}
```

### **Error Analysis Implementation**

**Theoretical Bounds**:
```cpp
double trapezoid_error(double a, double b, int n, double max_second_derivative) {
    double h = (b - a);
    return std::pow(h, 3) / (12.0 * std::pow(n, 2)) * std::abs(max_second_derivative);
}
```

---

## 🎯 Key Takeaways

1. **Mathematical Foundation**: All methods have rigorous theoretical basis
2. **Error Analysis**: Understanding errors enables method selection and validation
3. **Accuracy Trade-offs**: Higher accuracy often requires more computation
4. **Practical Limits**: Finite precision affects achievable accuracy
5. **Method Selection**: Choose methods based on function properties and requirements

---

*Numerical methods transform continuous mathematics into discrete computations with quantifiable accuracy.* 📊