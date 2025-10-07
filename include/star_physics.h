/*************************
 * Author : Sinan Demir
 * Date   : 10/07/2025
 * File   : star_physics.h
 * Purpose: Consolidated header for stellar physics and models.
 *          This unifies the following original headers:
 *             - stellar_mass.h (09/26/2025)
 *             - stellar_models.h (09/24/2025)
 *             - star.h (10/06/2025)
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
 * (Keep same public surface as original headers)
 *************************/
#include "integrators.h"
#include "differentiators.h"
#include "errors.h"

/*************************
 * Physical constants
 *************************/
#define M_SUN  (1.989e30)     // kg
#define L_SUN  (3.828e26)     // Watts
#define F      (0.1)          // fraction of mass that is hydrogen available for fusion
#define ETA    (0.007)        // efficiency of mass to energy conversion in fusion
#define C2     (9.0e16)       // speed of light squared in m^2/s^2
#define SECONDS_PER_YEAR (3.154e7) // seconds in a year

/*************************
 * Physics core functions
 *************************/

/**********************
 * Estimate fuel stock, i.e. the hydrogen fuel available for fusion in the star
 * @param M: Stellar mass in kg
 * @return: Fuel stock in Joules
 * @note: f = 0.1, eta = 0.007, c2 = 9.0e16
 **********************/
double fuel_stock(double M);

/**********************
 * Estimate stellar luminosity, i.e. the power output of the star
 * @param M: Stellar mass in kg
 * @return: Luminosity in Watts
 * @note: L_sun = 3.828e26, M_sun = 1.989e30
 **********************/
double luminosity(double M);

/***********************
 * Estimate the lifetime of the star, i.e. the time it takes for the star to burn all its fuel (Hydrogen)
 * @param M: Stellar mass in kg
 * @return: Lifetime in years
 * @note: seconds_per_year = 60.0 * 60.0 * 24.0 * 365.0
 **********************/
double lifetime(double M);

/*************************
 * Stellar luminosity models
 *************************/

/*************************
 * Estimate stellar lifetime by integrating luminosity over time.
 * @param S0          initial fuel stock
 * @param L           luminosity function pointer (takes double t, returns double)
 * @param T_guess     initial guess for lifetime (integration horizon)
 * @param n           number of subintervals
 * @param use_simpson true → use Simpson's rule, false → trapezoid
 * @return            Scaled lifetime estimate where ∫_0^T L(t) dt ≈ S0
 *************************/
double estimate_lifetime(double S0,
                         double (*L)(double),
                         double T_guess,
                         int n,
                         bool use_simpson);

/*************************
 * Example luminosity functions (toy models)
 *************************/
double L_const(double t);            // constant luminosity
double L_exp_decay(double t);        // exponential decay
double L_sinusoidal(double t);       // sinusoidal variability

/************************
 * Star class
 * Purpose: Header for star class (data + behavior)
 ************************/
class Star {

public:

    /************************************************
     * Constructor / Destructor
     ************************************************/
    /*************************
     * Star class constructor that takes in
     * the name, mass, luminosity, and age of the star
     * @param name Name of the star
     * @param mass_Msun Mass of the star in solar masses
     * @param luminosity_Lsun Luminosity of the star in solar luminosities
     * @param observed_age_years Age of the star in years
     * @exception std::invalid_argument if mass, luminosity, or age is negative
     * @return A star object
     * @note M☉ = 1.989e30 kg, L☉ = 3.828e26 W, 1 year = 3.154e7 seconds
     **************************/
    Star(const std::string &name, double mass_Msun, double luminosity_Lsun, double observed_age_years);
    
    /*************************
     * Star class destructor
     * @param None
     * @exception None
     * @return None
     * @note
     **************************/
    ~Star();

    /************************************************
     * Getters / Accessors
    ***********************************************/
    /*********************
     * Get the name of the star
     * @param None
     * @exception None
     * @return Name of the star
     * @note
     **********************/
    std::string getName() const;

    /*************************
     * Get the mass of the star in solar masses
     * @param None
     * @exception None
     * @return Mass in solar masses
     * @note M☉ = 1.989e30 kg
     * **********************/
    double getMass() const;

    /*************************
     * Get the luminosity of the star in solar luminosities
     * @param None
     * @exception None
     * @return Luminosity in solar luminosities
     * @note L☉ = 3.828e26 W
     **************************/
    double getLuminosity() const;

    /*************************
     * Get the age of the star in years
     * @param None
     * @exception None
     * @return Age in years
     **************************/
    double getAge() const;

    /*************************
     * computeFuelLifetime returns analytic estimate (τ ~ E / L)
     * @param None
     * @exception None
     * @return Lifetime in years
     **************************/
    double computeFuelLifetime() const;

    /*************************
     * convert from L☉ to watts
     * @param None
     * @exception None
     * @return Luminosity in Watts
     **************************/
    double luminosityInWatts() const;

    /*************************
     * convert from M☉ to kg
     * @param None
     * @exception None
     * @return Mass in kg
     **************************/
    double massInKg() const;

    /************************************************
     * Setters / Mutators
     ************************************************/
    /*************************
     * Set the name of the star
     * @param name Name of the star
     * @exception None
     * @return None
     * @note
     **************************/
    void setName(const std::string& name);

    /*************************
     * Set the mass of the star in solar masses
     * @param mass_Msun Mass in solar masses
     * @exception std::invalid_argument if mass is negative
     * @return None
     * @note M☉ = 1.989e30 kg
     **************************/
    void setMass(double mass_Msun);

    /*************************
     * Set the luminosity of the star in solar luminosities
     * @param luminosity_Lsun Luminosity in solar luminosities
     * @exception std::invalid_argument if luminosity is negative
     * @return None
     * @note L☉ = 3.828e26 W
     **************************/
    void setLuminosity(double luminosity_Lsun);

    /*************************
     * Set the age of the star in years
     * @param observed_age_years Age in years
     * @exception std::invalid_argument if age is negative
     * @return None
     * @note
     **************************/
    void setAge(double observed_age_years);

    /************************************************
     * Printing
    *************************************************/
    void printSummary() const;

    /***********************************************
     * Comparison methods
     ***********************************************/
    /*************************
     * Compare ages of two stars
     * @param other Another Star object
     * @exception None
     * @return true if this star is older
     * @note
     **************************/
    bool isOlderThan(const Star& other) const;

    /*************************
     * Compare luminosities of two stars
     * @param other Another Star object
     * @exception None
     * @return true if this star is brighter
     * @note
     **************************/
    bool isBrighterThan(const Star& other) const;

    /*************************
     * Compare masses of two stars
     * @param other Another Star object
     * @exception None  
     * @return true if this star is more massive
     * @note
     **************************/
    bool isMoreMassiveThan(const Star& other) const;

    /************************************************
     * Other methods
    ************************************************/
    /*************************
     * Evolve the star forward in time using a simple fuel depletion model
     * @param t_final Final time increment (years)
     * @param dt      Timestep (years)
     * @exception None
     * @return None
     * @note Uses constant luminosity equal to current luminosityInWatts()
     **************************/
    void evolve(double t_final, double dt);

private:
    /************************************************
     * Attributes
     ***********************************************/
    std::string name;
    double mass_Msun;
    double luminosity_Lsun;
    double observed_age_years;
};

#endif // STAR_PHYSICS_H
