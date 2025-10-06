/*************************
 * File : stellar_mass.h
 * Author : Sinan Demir
 * Date   : 09/26/2025
 * Purpose: Header file for stellar_mass.cpp contains stellar_mass function declarations.
*************************/

#include <cmath>
#include <stdexcept>


#ifndef STELLAR_MASS_H
#define STELLAR_MASS_H
// Physical constants
const double M_sun = 1.989e30;        // Sun mass in kg
const double L_sun = 3.828e26;        // Sun luminosity in W
const double c2   = 9.0e16;           // constant (m/s)^2
const double f    = 0.1;              // fraction of mass available for fusion
const double eta  = 0.007;            // efficiency coefficient
const double seconds_per_year = 60.0 * 60.0 * 24.0 * 365.0;

// Fuel stock in Joules
double fuel_stock(double M);

// Luminosity in Watts
double luminosity(double M);

// Lifetime in years
double lifetime(double M);

#endif // STELLAR_MASS_H
