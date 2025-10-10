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
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <vector>
#include <cassert>

/*************************
 * Project Includes
 *************************/
#include "num_analysis/integration.h"
#include "num_analysis/differentiation.h"
#include "num_analysis/errors.h"
#include "physics/constants.h"

using namespace physics::constants;

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
    
    // Table generation
    void generate_lifetime_table(int num_points = 50);

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
