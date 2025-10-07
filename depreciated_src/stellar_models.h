/*************************
 * File : stellar.h
 * Author : Sinan Demir
 * Date   : 09/24/2025
 * Purpose: Header file for stellar.cpp contains stellar function declarations. contains functions to estimate stellar lifetime
*************************/
 
#ifndef STELLAR_H
#define STELLAR_H

#include "integrators.h"
#include "differentiators.h"
#include "errors.h"
#include <cmath>
#include <stdexcept>

// Estimate stellar lifetime by integrating luminosity over time.
// S0          = initial fuel stock
// L           = luminosity function (takes double t, returns double)
// T_guess     = initial guess for lifetime (integration horizon)
// n           = number of subintervals
// use_simpson = true → use Simpson's rule, false → trapezoid
double estimate_lifetime(double S0,
                         double (*L)(double),
                         double T_guess,
                         int n,
                         bool use_simpson);

// Example luminosity functions
double L_const(double t);            // constant luminosity
double L_exp_decay(double t);        // exponential decay (toy example)
double L_sinusoidal(double t);       // sinusoidal variability (toy example)

//double fuel_stock(double )

#endif // STELLAR_H