/***************************
 * File   : stellar.cpp
 * Author : Sinan Demir
 * Date   : 09/24/2025
 * Purpose: Source file for stellar.cpp contains stellar function definitions. contains function 
 * implementations to estimate stellar lifetime
 ***************************/
 

#include "stellar.h"

// Generic function to estimate stellar lifetime
double estimate_lifetime(double S0,
                         double (*L)(double),
                         double T_guess,
                         int n,
                         bool use_simpson) {
    // integrate luminosity over [0, T_guess]
    double burned = use_simpson
                    ? simpsons_rule(L, 0, T_guess, n)
                    : trapezoid_rule(L, 0, T_guess, n);

    // Scale guess so that total fuel matches S0
    // Idea: if burned(T_guess) != S0, rescale proportionally
    return S0 * (T_guess / burned);
}

// -----------------------------
// Example luminosity functions
// -----------------------------

// Constant luminosity (toy model)
double L_const(double /*t*/) {
    return 1.0; // 1 unit fuel per unit time
}

// Exponentially decaying luminosity (toy model)
double L_exp_decay(double t) {
    double L0 = 1.0;  // initial luminosity
    double k  = 0.1;  // decay rate
    return L0 * std::exp(-k * t);
}

// Sinusoidal luminosity variation (toy model)
double L_sinusoidal(double t) {
    double L0 = 1.0;  // average luminosity
    double A  = 0.2;  // amplitude of variation
    double w  = 2.0;  // frequency
    return L0 * (1.0 + A * std::sin(w * t));
}


