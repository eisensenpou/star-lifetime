# Error Analysis Theory

**Mathematical Foundations of Error Quantification**

---

## 📋 Overview

This section provides theoretical background for error analysis in numerical computations. Understanding error behavior is essential for validating numerical methods and quantifying uncertainty in stellar physics calculations.

---

## 🏷️ Types of Numerical Errors

### **Truncation Error**

**Definition**: Error from approximating infinite processes with finite operations.

**Sources**:
- **Taylor Series Truncation**: Using finite terms
- **Finite Differences**: Approximating derivatives/integrals
- **Iterative Methods**: Stopping before convergence

**Mathematical Form**:
$$E_{truncation} = \text{Exact Value} - \text{Finite Approximation}$$

**Example**: Forward difference approximation:
$$f'(x) = \frac{f(x+h) - f(x)}{h} + O(h)$$
Truncation error: $E_{truncation} = O(h) = -\frac{h}{2}f''(\xi)$

### **Round-off Error**

**Definition**: Error from finite precision arithmetic representation.

**Machine Epsilon**:
$$\epsilon_{machine} = \text{smallest number such that } 1 + \epsilon > 1$$

**Floating Point Representation**:
$$fl(x) = x(1 + \delta)$$ where $|\delta| \leq \epsilon_{machine}$

**Accumulation**: Errors can grow with multiple operations.

---

## 📏 Error Propagation Theory

### **Forward Error Analysis**

Given function $f(x_1, x_2, \ldots, x_n)$ with perturbed inputs:
$$\hat{x}_i = x_i + \Delta x_i$$

**Output Error**:
$$\Delta f = f(\hat{x}_1, \ldots, \hat{x}_n) - f(x_1, \ldots, x_n)$$

**Linear Approximation**:
$$\Delta f \approx \sum_{i=1}^{n} \frac{\partial f}{\partial x_i} \Delta x_i$$

### **Condition Number**

**Definition**: Sensitivity of output to input perturbations.

$$\kappa = \lim_{\epsilon \to 0} \sup_{\|\Delta x\| \leq \epsilon\|x\|} \frac{\|\Delta f\|/\|f\|}{\|\Delta x\|/\|x\|}$$

**Interpretation**:
- $\kappa \approx 1$: Well-conditioned problem
- $\kappa \gg 1$: Ill-conditioned problem

### **Backward Error Analysis**

**Definition**: Find smallest input perturbation that produces observed output error.

**Backward Error**:
$$\Delta x_{backward} = \min\{\Delta x : f(x + \Delta x) = \hat{f}\}$$

**Relevance**: More meaningful than forward error for many problems.

---

## 📊 Integration Error Analysis

### **Trapezoidal Rule Error**

**Derivation**:
Using Taylor series expansion around each subinterval:

$$\int_{x_i}^{x_{i+1}} f(x) \,dx = \frac{h}{2}[f(x_i) + f(x_{i+1})] - \frac{h^3}{12}f''(\xi_i)$$

**Total Error**:
$$E_T = -\frac{(b-a)h^2}{12}f''(\xi)$$

**Error Bound**:
$$|E_T| \leq \frac{(b-a)^3}{12n^2} \max_{x \in [a,b]} |f''(x)|$$

**Key Insights**:
- Error proportional to $h^2$ (second-order accuracy)
- Depends on second derivative (curvature)
- Reduces by factor of 4 when $n$ doubles

### **Simpson's Rule Error**

**Derivation**:
From Taylor series expansion and quadratic interpolation:

$$\int_{x_i}^{x_{i+2}} f(x) \,dx = \frac{h}{3}[f(x_i) + 4f(x_{i+1}) + f(x_{i+2})] - \frac{h^5}{90}f^{(4)}(\xi_i)$$

**Total Error**:
$$E_S = -\frac{(b-a)h^4}{180}f^{(4)}(\xi)$$

**Error Bound**:
$$|E_S| \leq \frac{(b-a)^5}{180n^4} \max_{x \in [a,b]} |f^{(4)}(x)|$$

**Key Insights**:
- Error proportional to $h^4$ (fourth-order accuracy)
- Depends on fourth derivative
- Reduces by factor of 16 when $n$ doubles
- Much more accurate than trapezoidal for smooth functions

---

## 📐 Differentiation Error Analysis

### **Forward Difference Error**

**Taylor Series**:
$$f(x+h) = f(x) + hf'(x) + \frac{h^2}{2}f''(x) + \frac{h^3}{6}f'''(x) + O(h^4)$$

**Solving for $f'(x)$**:
$$f'(x) = \frac{f(x+h) - f(x)}{h} - \frac{h}{2}f''(x) - O(h^2)$$

**Truncation Error**:
$$E_{forward} = -\frac{h}{2}f''(\xi)$$

**Round-off Error**:
$$E_{round-off} \approx \frac{2\epsilon |f(x)|}{h}$$

### **Central Difference Error**

**Taylor Series Subtraction**:
$$f(x+h) - f(x-h) = 2hf'(x) + \frac{h^3}{3}f'''(\xi)$$

**Solving for $f'(x)$**:
$$f'(x) = \frac{f(x+h) - f(x-h)}{2h} - \frac{h^2}{6}f'''(\xi)$$

**Truncation Error**:
$$E_{central} = -\frac{h^2}{6}f'''(\xi)$$

**Round-off Error**:
$$E_{round-off} \approx \frac{2\epsilon |f(x)|}{h}$$

### **Optimal Step Size**

**Total Error**:
$$E_{total} = |E_{truncation}| + |E_{round-off}|$$

**Balancing Terms**:
$$\frac{C h}{2} = \frac{2\epsilon}{h}$$

**Optimal Step Size**:
$$h_{optimal} = \sqrt{\frac{4\epsilon}{C}}$$

For central difference:
$$h_{optimal} \approx \sqrt{\epsilon_{machine}} \approx 10^{-8} \text{ (double precision)}$$

---

## 🔢 Error Metrics Theory

### **Absolute Error**

**Definition**:
$$E_{absolute} = |x_{true} - x_{approx}|$$

**Properties**:
- Scale-dependent
- Intuitive physical interpretation
- Useful for quantities with natural scales

### **Relative Error**

**Definition**:
$$E_{relative} = \left|\frac{x_{true} - x_{approx}}{x_{true}}\right|$$

**Properties**:
- Scale-independent
- Expressed as percentage
- Useful for comparing across scales

### **Significant Digits**

**Definition**: Number of correct significant digits.

**Formula**:
$$\text{Significant Digits} = -\log_{10}(E_{relative})$$

**Example**: If $E_{relative} = 10^{-4}$, then 4 significant digits are correct.

---

## 📈 Convergence Analysis

### **Order of Convergence**

**Definition**: Method converges with order $p$ if:
$$\lim_{h \to 0} \frac{|I(h) - I|}{|I(h/2) - I|} = 2^p$$

**Practical Test**:
1. Compute with step sizes $h$, $h/2$, $h/4$
2. Verify ratio approaches $2^p$

**Convergence Rate Implications**:
- **Linear** ($p=1$): Error proportional to step size
- **Quadratic** ($p=2$): Error proportional to $h^2$
- **Cubic** ($p=3$): Error proportional to $h^3$

### **Richardson Extrapolation**

**Concept**: Combine multiple approximations to eliminate leading error term.

**General Formula**:
$$I_{refined} = I(h) + \frac{I(h) - I(h/2)}{2^p - 1}$$

**For Simpson's Rule** ($p=4$):
$$I_{refined} = I(h) + \frac{I(h) - I(h/2)}{15}$$

**Benefits**:
- Higher accuracy without additional function evaluations
- Error estimation capability
- Adaptive refinement

---

## 🎯 Practical Error Analysis

### **Error Estimation Techniques**

**A Posteriori Error Estimation**:
1. **Richardson Extrapolation**: Use multiple step sizes
2. **Embedded Methods**: Compare different order methods
3. **Residual Estimation**: Check approximation quality

**A Priori Error Bounds**:
1. **Theoretical Bounds**: Use derivative bounds
2. **Interval Arithmetic**: Track uncertainty ranges
3. **Probabilistic Bounds**: Statistical error estimates

### **Stellar Physics Applications**

**Integration Error in Lifetime Calculations**:
- **Fuel Integration**: $\int_0^T L(t) \,dt \approx S_0$
- **Relative Lifetime Error**: $\frac{\Delta T}{T} \propto \frac{\Delta S}{S_0}$

**Differentiation Error in Sensitivity Analysis**:
- **Parameter Sensitivity**: $\frac{\partial T}{\partial M}$ using numerical differentiation
- **Error Propagation**: $\Delta T \approx \frac{\partial T}{\partial M} \Delta M$

---

## ⚖️ Stability Analysis

### **Numerical Stability**

**Definition**: Small perturbations don't grow unboundedly.

**Forward Stability**:
$$|x_{n+1} - \hat{x}_{n+1}| \leq C |x_n - \hat{x}_n|$$

**Backward Stability**:
$$|x_n - \hat{x}_n| \leq C |x_{n+1} - \hat{x}_{n+1}|$$

### **Ill-Conditioned Problems**

**Characteristics**:
- Small input changes cause large output changes
- Error amplification factors
- Difficult numerical solution

**Examples in Stellar Physics**:
- **Stiff Equations**: Multiple timescales
- **Subtractive Cancellation**: Nearly equal quantities
- **Ill-Conditioned Systems**: Near-singular matrices

---

## 📊 Computational Error Management

### **Preventive Measures**

**Algorithm Selection**:
- Choose numerically stable formulations
- Avoid subtraction of nearly equal numbers
- Use compensated arithmetic when possible

**Parameter Scaling**:
- Normalize variables to similar magnitudes
- Use dimensionless parameters
- Apply appropriate units

### **Corrective Techniques**

**Iterative Refinement**:
1. **Newton's Method**: Root finding refinement
2. **Fixed Point Iteration**: Successive approximation
3. **Deflation**: Remove known components

**Error Compensation**:
1. **Kahan Summation**: Compensated addition
2. **Double Precision**: Use higher precision internally
3. **Interval Methods**: Track uncertainty ranges

---

## 🔗 Implementation in Star Lifetime

### **Error Bounds Implementation**

**Trapezoidal Error Bound**:
```cpp
double trapezoid_error(double a, double b, int n, double max_second_derivative) {
    double h = (b - a);
    return std::pow(h, 3) / (12.0 * std::pow(n, 2)) * std::abs(max_second_derivative);
}
```

**Simpson's Error Bound**:
```cpp
double simpson_error(double a, double b, int n, double max_fourth_derivative) {
    double h = (b - a);
    return std::pow(h, 5) / (180.0 * std::pow(n, 4)) * std::abs(max_fourth_derivative);
}
```

### **Error Metrics Implementation**

**Absolute Error**:
```cpp
double absolute_error(double exact, double approx) {
    return std::abs(exact - approx);
}
```

**Relative Error**:
```cpp
double relative_error(double exact, double approx) {
    if (exact == 0.0) {
        throw std::invalid_argument("Exact value cannot be zero in relative error calculation.");
    }
    return std::abs((exact - approx) / exact);
}
```

---

## 🎯 Key Takeaways

1. **Error Sources**: Truncation and round-off errors are fundamental
2. **Error Propagation**: Input uncertainties affect output accuracy
3. **Method Selection**: Choose appropriate order for required accuracy
4. **Error Analysis**: Essential for validating numerical results
5. **Stability**: Numerical methods must be well-conditioned

---

*Error analysis transforms approximations into quantified uncertainty.* 📊