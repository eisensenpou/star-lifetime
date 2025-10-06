/************************
 * File : differentiators.cpp
 * Author : Sinan Demir
 * Date   : 09/25/2025
 * Implementation of differentiator functions.
 ************************/
 

#include "differentiators.h"

double forward_diff(std::function<double(double)> f, double x, double h) {
    /****************************
     *  Forward Difference Method for numerical differentiation
     * @param f: Function to differentiate
     * @param x: Point to differentiate at
     * @param h: Step size
     * @return: Approximation of the derivative
     * @note: h must be positive
     ****************************/

     if (h <=0){
        throw std::invalid_argument("Step size h must be positive.");
     } else {
        return (f(x + h) - f(x)) / h;
     }
} // end forward_diff

double central_diff(std::function<double(double)> f, double x, double h) {
    /****************************
     *  Central Difference Method for numerical differentiation
     * @param f: Function to differentiate
     * @param x: Point to differentiate at
     * @param h: Step size
     * @return: Approximation of the derivative
     * @note: h must be positive
     ****************************/

     if (h <=0){
        throw std::invalid_argument("Step size h must be positive.");
     } else {
        return (f(x + h) - f(x - h)) / (2 * h);
     }
} // end central_diff

double backward_diff(std::function<double(double)> f, double x, double h) {
    /****************************
     *  Backward Difference Method for numerical differentiation
     * @param f: Function to differentiate
     * @param x: Point to differentiate at
     * @param h: Step size
     * @return: Approximation of the derivative
     * @note: h must be positive
     ****************************/
    if (h <=0) {
        throw std::invalid_argument("Step size h must be positive.");
    } else {
        return (f(x) - f(x - h)) / h;
    }
} // end backward_diff

