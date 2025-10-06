/*************************
 * File : errors.h
 * Author : Sinan Demir
 * Date   : 09/25/2025
 * Purpose: Header file for errors.cpp contains error calculation function declarations.
*************************/

#ifndef ERRORS_H
#define ERRORS_H

#include "differentiators.h"
#include <cmath>
#include <stdexcept>

// Function to calculate absolute error
double absolute_error(double exact, double approx);

// Function to calculate relative error
double relative_error(double exact, double approx);

// Function to calculate  Simpson's rule error estimate
double simpson_error(double a, double b, int n, double max_fourth_derivative);

// Function to calculate trapezoid rule error estimate
double trapezoid_error(double a, double b, int n, double max_second_derivative);

#endif // ERRORS_H