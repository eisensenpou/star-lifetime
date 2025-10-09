/***************************
 * Author : Sinan Demir
 * Date   : 09/24/2025
 * File   : differentiation.cpp
 * Purpose: Implements numerical differentiation methods
 *           (Forward, Backward, and Central Difference)
 *           declared in differentiation.h inside the num_analysis::differentiation namespace.
 ****************************/

#include "num_analysis/differentiation.h"

namespace num_analysis::differentiation {

    // =====================================================
    // Forward Difference Method
    // =====================================================
    // Approximates f'(x) ≈ [f(x + h) - f(x)] / h
    // Accurate to O(h)
    // =====================================================
    double forward_diff(std::function<double(double)> f, double x, double h) {
    /****************************
     *  Forward Difference Method for numerical differentiation
     * @param f: Function to differentiate
     * @param x: Point to differentiate at
     * @param h: Step size
     * @exception: std::invalid_argument if h is not positive
     * @return: Approximation of the derivative
     * @note: h must be positive
     ****************************/
        if (h <= 0)
            throw std::invalid_argument("Step size h must be positive.");
        return (f(x + h) - f(x)) / h;
    }

    // =====================================================
    // Backward Difference Method
    // =====================================================
    // Approximates f'(x) ≈ [f(x) - f(x - h)] / h
    // Accurate to O(h)
    // =====================================================
    double backward_diff(std::function<double(double)> f, double x, double h) {
    /****************************
     *  Backward Difference Method for numerical differentiation
     * @param f: Function to differentiate
     * @param x: Point to differentiate at
     * @param h: Step size
     * @return: Approximation of the derivative
     * @note: h must be positive
     ****************************/
        if (h <= 0)
            throw std::invalid_argument("Step size h must be positive.");
        return (f(x) - f(x - h)) / h;
    }

    // =====================================================
    // Central Difference Method
    // =====================================================
    // Approximates f'(x) ≈ [f(x + h) - f(x - h)] / (2h)
    // Accurate to O(h²)
    // =====================================================
    double central_diff(std::function<double(double)> f, double x, double h) {
    /****************************
     *  Central Difference Method for numerical differentiation
     * @param f: Function to differentiate
     * @param x: Point to differentiate at
     * @param h: Step size
     * @exception: std::invalid_argument if h is not positive
     * @return: Approximation of the derivative
     * @note: h must be positive
     ****************************/
        if (h <= 0)
            throw std::invalid_argument("Step size h must be positive.");
        return (f(x + h) - f(x - h)) / (2 * h);
    }

} // namespace num_analysis::differentiation