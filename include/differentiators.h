/*************************
 * File : differentiators.h
 * Author : Sinan Demir
 * Date   : 09/24/2025
 * Purpose: Header file for differentiators.cpp contains differentiator function declarations.
*************************/

#ifndef DIFFERENTIATORS_H
#define DIFFERENTIATORS_H

#include <functional>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <iomanip>

#define M_PI 3.14159265358979323846

// Forward difference method
double forward_diff(std::function<double(double)> f, double x, double h); 

// Central difference method
double central_diff(std::function<double(double)> f, double x, double h);

// Backward differencemethod
double backward_diff(std::function<double(double)> f, double x, double h);


#endif // DIFFERENTIATORS_H