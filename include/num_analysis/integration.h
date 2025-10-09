/***************************
 * Author : Sinan Demir
 * Date   : 09/23/2025
 * File   : integrators.h
 * Purpose: Header file for integrators.cpp — contains numerical integration
 *           function declarations inside the num_analysis::integration namespace.
 ****************************/

#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <functional>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <iomanip>


#define M_PI 3.14159265358979323846

// =======================
// Numerical Integration Module
// =======================
// Provides methods for estimating definite integrals of a function f(x)
// using composite numerical integration rules (Trapezoid and Simpson).
// Part of the num_analysis::integration namespace.

namespace num_analysis::integration {

    // Composite Trapezoid Rule
    double trapezoid_rule(std::function<double(double)> f, double a, double b, int n);

    // Simpson's Rule (requires n to be even)
    double simpsons_rule(std::function<double(double)> f, double a, double b, int n);

}

#endif // INTEGRATION_H
