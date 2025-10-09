/*************************
 * File   : differentiators.h
 * Author : Sinan Demir
 * Date   : 10/09/2025
 * Purpose: Header file for differentiators.cpp — contains differentiator function declarations
 *           inside the num_analysis::differentiation namespace.
 *************************/

#ifndef DIFFERENTIATION_H
#define DIFFERENTIATION_H

#include <functional>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <iomanip>

#define M_PI 3.14159265358979323846

// =======================
// Numerical Differentiation Module
// =======================
// Contains forward, backward, and central finite difference methods
// for approximating first derivatives of a given function f(x).
// Part of the num_analysis::differentiation namespace.

namespace num_analysis::differentiation {

    // Forward difference method
    double forward_diff(std::function<double(double)> f, double x, double h); 

    // Central difference method
    double central_diff(std::function<double(double)> f, double x, double h);

    // Backward difference method
    double backward_diff(std::function<double(double)> f, double x, double h);

}

#endif // DIFFERENTIATION_H
