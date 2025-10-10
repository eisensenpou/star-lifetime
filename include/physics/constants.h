/*******************
 * File   : constants.h
 * Author : Sinan Demir
 * Date   : 10/09/2025
 * Purpose: Constants used in the physics::constants namespace
 ******************/

#ifndef PHYSICS_CONSTANTS_H
#define PHYSICS_CONSTANTS_H


/*************************
 * Physical constants
 *************************/
namespace physics::constants {
    constexpr double F = 0.1;                    // hydrogen fuel fraction
    constexpr double ETA = 0.007;                // mass–energy conversion efficiency
    constexpr double C2 = 9.0e16;                // speed of light squared (m^2/s^2)
    constexpr double L_SUN = 3.828e26;           // solar luminosity (W)
    constexpr double M_SUN = 1.989e30;           // solar mass (kg)
    constexpr double SECONDS_PER_YEAR = 3.154e7; // seconds per year
}


#endif // PHYSICS_CONSTANTS_H