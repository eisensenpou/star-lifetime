/*************************
 * Author : Sinan Demir
 * Date   : 10/07/2025
 * File   : star_physics.h
 * Purpose: Consolidated header for stellar physics and models.
 *          Unifies stellar_mass.h, stellar_models.h, and star.h
 *************************/

#ifndef STAR_PHYSICS_H
#define STAR_PHYSICS_H

/*************************
 * Standard Library Includes
 *************************/
#include <string>
#include <iostream>
#include <cmath>
#include <stdexcept>

/*************************
 * Project Includes
 *************************/
#include "num_analysis/integration.h"
#include "num_analysis/differentiation.h"
#include "num_analysis/errors.h"

/*************************
 * Physical constants
 *************************/
#define M_SUN  (1.989e30)           // kg
#define L_SUN  (3.828e26)           // Watts
#define F      (0.1)                // hydrogen mass fraction
#define ETA    (0.007)              // efficiency of fusion
#define C2     (9.0e16)             // speed of light squared (m²/s²)
#define SECONDS_PER_YEAR (3.154e7)  // seconds in a year

namespace physics::stellar {

    /*************************
     * Core Physics Functions
     *************************/

    double fuel_stock(double M);     // Available nuclear fuel (Joules)
    double luminosity(double M);     // Luminosity (Watts)
    double lifetime(double M);       // Stellar lifetime (years)

    /*************************
     * Numerical lifetime estimation via integration
     *************************/
    double estimate_lifetime(double S0,
                             double (*L)(double),
                             double T_guess,
                             int n,
                             bool use_simpson);

    /*************************
     * Example luminosity functions
     *************************/
    double L_const(double t);
    double L_exp_decay(double t);
    double L_sinusoidal(double t);

    /*************************
     * Star class (Data + Behavior)
     *************************/
    class Star {

    public:
        Star(const std::string &name, double mass_Msun, double luminosity_Lsun, double observed_age_years);
        ~Star();

        // Getters
        std::string getName() const;
        double getMass() const;
        double getLuminosity() const;
        double getAge() const;

        // Core calculations
        double computeFuelLifetime() const;
        double luminosityInWatts() const;
        double massInKg() const;

        // Setters
        void setName(const std::string& name);
        void setMass(double mass_Msun);
        void setLuminosity(double luminosity_Lsun);
        void setAge(double observed_age_years);

        // Display
        void printSummary() const;

        // Comparisons
        bool isOlderThan(const Star& other) const;
        bool isBrighterThan(const Star& other) const;
        bool isMoreMassiveThan(const Star& other) const;

        // Evolution model
        void evolve(double t_final, double dt);

    private:
        std::string name;
        double mass_Msun;
        double luminosity_Lsun;
        double observed_age_years;
    };

} // namespace physics::stellar

#endif // STAR_PHYSICS_H
