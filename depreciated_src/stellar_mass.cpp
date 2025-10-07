/************************
 * File : stellar_mass.cpp
 * Author : Sinan Demir
 * Date   : 09/24/2025
 * Implementation of stellar_mass functions, fuel_stock, luminosity, lifetime
 ************************/


#include "stellar_mass.h"
#include <cmath>


double fuel_stock(double M) {
    /**********************
     * Estimate fuel stock, i.e. the hydrogen fuel available for fusion in the star
     * @param M: Stellar mass in kg
     * @return: Fuel stock in Joules
     * @note: f = 0.1, eta = 0.007, c2 = 9.0e16
     **********************/
    return F * M * C2 * ETA; // Joules
} // end of fuel_stock function

double luminosity(double M) {
    /**********************
     * Estimate stellar luminosity, i.e. the power output of the star
     * @param M: Stellar mass in kg
     * @return: Luminosity in Watts
     * @note: L_sun = 3.828e26, M_sun = 1.989e30
     **********************/
    return L_SUN * std::pow(M / M_SUN, 3.5); // Watts
}  // end of luminosity function

double lifetime(double M) {
    /***********************
     * Estimate the lifetime of the star, i.e. the time it takes for the star to burn all its fuel (Hydrogen)
     * @param M: Stellar mass in kg
     * @return: Lifetime in years  
     * @note: seconds_per_year = 60.0 * 60.0 * 24.0 * 365.0
     **********************/
    double S = fuel_stock(M);  // Joules
    double L = luminosity(M);  // Watts
    double T_seconds = S / L;  // seconds
    return T_seconds / SECONDS_PER_YEAR; // years
} // end of lifetime function

