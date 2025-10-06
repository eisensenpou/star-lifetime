/**********************
 * Author : Sinan Demir
 * Date   : 09/23/2025
 * File   : integrators.cpp
 * Purpose: Source file for integrators.cpp contains integrator function definitions.
 **********************/

#include "integrators.h"

double trapezoid_rule(std::function<double(double)> f, double a, double b, int n) {
    /******************
     * Composite trapezoid rule implementation
     * @param f: Function to integrate
     * @param a: Lower limit of integration
     * @param b: Upper limit of integration
     * @param n: Number of subintervals
     * @return: Approximation of the integral
     * @note: n must be greater than 0
     ******************/

    if (n <= 0) {
        throw std::invalid_argument("Number of subintervals must be greater than 0");
    }
    
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }
    return h * sum;
}   // end of trapezoid method

double simpsons_rule(std::function<double(double)> f, double a, double b, int n) {
    /*******************
     *  Simpson's rule for numerical integration
     * @param f: Function to integrate
     * @param a: Lower limit of integration
     * @param b: Upper limit of integration
     * @param n: Number of subintervals (must be even)
     * @return: Approximation of the integral
     * @note: n must be even and greater than 0
     *******************/
    if (n <= 0 || n % 2 != 0) {
        throw std::invalid_argument("Number of subintervals must be even and greater than 0");
    }
    double deltaX = (b - a) / n;
    double sum = f(a) + f(b);
    // numerical integration using Simpson's rule
    for (int i = 1; i < n; i++) {
        double x = a + i * deltaX;
        // The Simpson's rule: even index -> multiply by 2, odd index -> multiply by 4
        // f(x0) + 4f(x1) + 2f(x2) + 4f(x3) + ... + 2f(x(n-2)) + 4f(x(n-1)) + f(xn)
        sum += (i % 2 == 0) ? 2 * f(x) : 4 * f(x); 
    }
    return (deltaX / 3) * sum; 
}  // end of simpson method
