/************************
 * File : errors.cpp
 * Author : Sinan Demir
 * Date   : 09/24/2025
 * Implementation of error calculation functions.
 ************************/


#include "errors.h"
#include <cmath>
#include <stdexcept>

double absolute_error(double exact, double approx) {
    /****************************
     *  Calculate absolute error
     * @param exact: Exact value
     * @param approx: Approximate value
     * @return: Absolute error
     ****************************/
    return std::abs(exact - approx);
} // end absolute_error

double relative_error(double exact, double approx) {
    /****************************
     *  Calculate relative error
     * @param exact: Exact value
     * @param approx: Approximate value
     * @exception: std::invalid_argument if exact or approx is NaN or exact is zero
     * @return: Relative error
     ****************************/
    if (std::isnan(exact) || std::isnan(approx)) {
        throw std::invalid_argument("Inputs cannot be NaN for error calculation.");
    }
    if (exact == 0.0) {
        throw std::invalid_argument("Exact value cannot be zero for relative error calculation.");
    }
    return std::abs((exact - approx) / exact); // relative error
} // end relative_error

double simpson_error(double a, double b, int n, double max_fourth_derivative){
    /*************************
     *  Calculate Simpson's rule error estimate
     * @param a: Lower limit of integration
     * @param b: Upper limit of integration
     * @param n: Number of subintervals
     * @param max_fourth_derivative: Maximum fourth derivative of the function
     * @return: Simpson's rule error estimate
     *************************/
    return -((std::pow(b - a, 5)) / (180.0 * std::pow(n, 4))) * max_fourth_derivative;
    // Simpson's rule error estimate: https://en.wikipedia.org/wiki/Simpson%27s_rule
}  // end simpson_error


double trapezoid_error(double a, double b, int n, double max_second_derivative){
    /*************************
     *  Calculate trapezoid rule error estimate
     * @param a: Lower limit of integration
     * @param b: Upper limit of integration
     * @param n: Number of subintervals
     * @param max_second_derivative: Maximum second derivative of the function
     * @return: Trapezoid rule error estimate
     *************************/
    return -((std::pow(b - a, 3)) / (12.0 * std::pow(n, 2))) * max_second_derivative;
     // Trapezoid rule error estimate: https://en.wikipedia.org/wiki/Trapezoidal_rule
} // end trapezoid_error

