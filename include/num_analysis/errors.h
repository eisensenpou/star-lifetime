/*************************
 * File   : errors.h
 * Author : Sinan Demir
 * Date   : 10/09/2025
 * Purpose: Header file for errors.cpp — contains numerical error calculation functions
 *           inside the num_analysis::errors namespace.
 *************************/

#ifndef ERRORS_H
#define ERRORS_H

#include "differentiation.h"
#include <cmath>
#include <stdexcept>
#include <cmath>
#include <stdexcept>

// =======================
// Numerical Error Analysis Module
// =======================
// Provides functions for calculating absolute and relative errors,
// as well as theoretical error bounds for numerical integration methods
// (Trapezoid and Simpson's rules).
// Part of the num_analysis::errors namespace.

namespace num_analysis::errors {

    // Calculates the absolute error between exact and approximate values.
    double absolute_error(double exact, double approx);

    // Calculates the relative error between exact and approximate values.
    double relative_error(double exact, double approx);

    // Estimates the theoretical error bound for Simpson's rule.
    double simpson_error(double a, double b, int n, double max_fourth_derivative);

    // Estimates the theoretical error bound for the Trapezoid rule.
    double trapezoid_error(double a, double b, int n, double max_second_derivative);

}

#endif // ERRORS_H
