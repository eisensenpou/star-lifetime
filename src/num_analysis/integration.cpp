/**********************
 * Author : Sinan Demir
 * Date   : 09/23/2025
 * File   : integration.cpp
 * Purpose: Source file for integration.cpp contains implementations of namespace num_analysis::integration
 * numerical integration functions definitions.
 **********************/

#include "num_analysis/integration.h"


namespace num_analysis::integration {

    // =====================================================
    // Composite Trapezoid Rule
    // =====================================================
    // Approximates ∫ₐᵇ f(x) dx using n subintervals of width h = (b - a) / n.
    // Formula:
    //      I ≈ h * [ (f(a) + f(b))/2 + Σ f(a + i*h) ]
    // =====================================================
    double trapezoid_rule(std::function<double(double)> f, double a, double b, int n) {
    /******************
    * Composite trapezoid rule implementation
    * @param f: Function to integrate
    * @param a: Lower limit of integration
    * @param b: Upper limit of integration
    * @param n: Number of subintervals
    * @exception: std::invalid_argument if n is not positive
    * @return: Approximation of the integral
    * @note: n must be greater than 0
    ******************/
        if (n <= 0)
            throw std::invalid_argument("Number of subintervals n must be positive.");

        double h = (b - a) / n;
        double sum = 0.5 * (f(a) + f(b));

        for (int i = 1; i < n; ++i)
            sum += f(a + i * h);

        return h * sum;
    }

    // =====================================================
    // Simpson’s Rule
    // =====================================================
    // Approximates ∫ₐᵇ f(x) dx using Simpson’s composite rule.
    // Requires n to be even (number of subintervals).
    // Formula:
    //      I ≈ (h/3) * [f(a) + f(b) + 4Σ f(odd) + 2Σ f(even)]
    // =====================================================
    double simpsons_rule(std::function<double(double)> f, double a, double b, int n) {
    /*******************
     *  Simpson's rule for numerical integration
     * @param f: Function to integrate
     * @param a: Lower limit of integration
     * @param b: Upper limit of integration
     * @param n: Number of subintervals (must be even)
     * @exception: std::invalid_argument if n is not even
     * @return: Approximation of the integral
     * @note: n must be even and greater than 0
     *******************/

        if (n <= 0)
            throw std::invalid_argument("Number of subintervals n must be positive.");

        if (n % 2 != 0)
            ++n; // auto-adjust to even n

        double h = (b - a) / n;
        double sum = f(a) + f(b);

        for (int i = 1; i < n; ++i)
            sum += f(a + i * h) * (i % 2 == 0 ? 2 : 4);

        return h / 3.0 * sum;
    }

} // namespace num_analysis::integration


