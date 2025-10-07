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

#define M_SUN  (1.989e30) // kg
#define L_SUN  (3.828e26) // Watts
#define F (0.1) // fraction of mass that is hydrogen available for fusion
#define ETA (0.007) // efficiency of mass to energy conversion in fusion
#define C2 (9.0e16) // speed of light squared in m^2/s^2
#define SECONDS_PER_YEAR (3.154e7) // seconds in a year


// Fuel stock in Joules
double fuel_stock(double M);

// Luminosity in Watts
double luminosity(double M);

// Lifetime in years
double lifetime(double M);

#endif // STELLAR_MASS_H
