/***************************
 Author : Sinan Demir
 Date   : 09/23/2025
 File   : integrators.h
 Purpose: Header file for integrators.cpp contains integrator function declarations.
****************************/


#ifndef INTEGRATORS_H
#define INTEGRATORS_H

#include <functional>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <iomanip>

#define M_PI 3.14159265358979323846


// Composite trapezoid rule
double trapezoid_rule(std::function<double(double)> f, double a, double b, int n);

// Simpson's rule (requires n even)
double simpsons_rule(std::function<double(double)> f, double a, double b, int n);

#endif // INTEGRATORS_H
