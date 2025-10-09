/***************************
 * Author : Sinan Demir
 * Date   : 10/09/2025
 * File   : error.cpp
 * Purpose: Implements numerical error estimation and comparison functions
 *           declared in error.h inside the num_analysis::error namespace.
 ****************************/

#include "num_analysis/errors.h"

namespace num_analysis::errors {

    // =====================================================
    // Absolute Error
    // =====================================================
    // |exact - approx|
    // =====================================================
    double absolute_error(double exact, double approx) {
    /****************************
     *  Calculate absolute error
     * @param exact: Exact value
     * @param approx: Approximate value
     * @return double : Absolute error
     ****************************/
        return std::abs(exact - approx);
    }

    // =====================================================
    // Relative Error
    // =====================================================
    // |exact - approx| / |exact|
    // =====================================================
    double relative_error(double exact, double approx) {
    /****************************
     *  Calculate relative error
     * @param exact: Exact value
     * @param approx: Approximate value
     * @exception: std::invalid_argument if exact == 0
     * @return: Relative error
     ****************************/
        if (exact == 0)
            throw std::invalid_argument("Exact value cannot be zero in relative error calculation.");
        return std::abs((exact - approx) / exact);
    }

    // =====================================================
    // Simpson’s Rule Error Estimate
    // =====================================================
    // Theoretical bound:
    // E_s ≤ ((b - a)^5 / 180n^4) * max|f''''(ξ)|
    // =====================================================
    double simpson_error(double a, double b, int n, double max_fourth_derivative) {
    /*************************
     *  Calculate Simpson's rule error estimate
     * @param a: Lower limit of integration
     * @param b: Upper limit of integration
     * @param n: Number of subintervals
     * @param max_fourth_derivative: Maximum fourth derivative of the function
     * @return: Simpson's rule error estimate
     *************************/
        if (n <= 0)
            throw std::invalid_argument("Number of subintervals n must be positive.");
        double h = (b - a);
        return (std::pow(h, 5) / (180.0 * std::pow(n, 4))) * std::abs(max_fourth_derivative);
    }

    // =====================================================
    // Trapezoid Rule Error Estimate
    // =====================================================
    // Theoretical bound:
    // E_t ≤ ((b - a)^3 / 12n^2) * max|f''(ξ)|
    // =====================================================
    double trapezoid_error(double a, double b, int n, double max_second_derivative) {
    /*************************
     *  Calculate trapezoid rule error estimate
     * @param a: Lower limit of integration
     * @param b: Upper limit of integration
     * @param n: Number of subintervals
     * @param max_second_derivative: Maximum second derivative of the function
     * @return: Trapezoid rule error estimate
     *************************/        
        if (n <= 0)
            throw std::invalid_argument("Number of subintervals n must be positive.");
        double h = (b - a);
        return (std::pow(h, 3) / (12.0 * std::pow(n, 2))) * std::abs(max_second_derivative);
    }

} // namespace num_analysis::error