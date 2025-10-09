/*************************
 * Author : Sinan Demir
 * Date   : 10/09/2025
 * File   : star_physics.cpp
 * Purpose: Consolidated implementation for stellar physics and models.
 *          This unifies the following original sources:
 *             - stellar_mass.cpp (09/24/2025)
 *             - stellar_models.cpp (09/24/2025)
 *             - star.cpp (10/06/2025)
 *************************/

#include "physics/star_physics.h"

namespace physics::stellar {

/************************
 * Implementation: Physics core functions
 ************************/

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


/************************
 * Implementation: Stellar model functions
 ************************/

double estimate_lifetime(double S0,
                         double (*L)(double),
                         double T_guess,
                         int n,
                         bool use_simpson) {
    /*************************
     * Estimate stellar lifetime by integrating luminosity over time.
     * @param S0          initial fuel stock
     * @param L           luminosity function pointer (takes double t, returns double)
     * @param T_guess     initial guess for lifetime (integration horizon)
     * @param n           number of subintervals
     * @param use_simpson true → use Simpson's rule, false → trapezoid
     * @return            Scaled lifetime estimate where ∫_0^T L(t) dt ≈ S0
     *************************/
    double burned = use_simpson
                    ? num_analysis::integration::simpsons_rule(L, 0, T_guess, n)
                    : num_analysis::integration::trapezoid_rule(L, 0, T_guess, n);

    // Scale guess so that total fuel matches S0
    // Idea: if burned(T_guess) != S0, rescale proportionally
    return S0 * (T_guess / burned);
}

// -----------------------------
// Example luminosity functions
// -----------------------------

double L_const(double /*t*/) {
    /*************************
     * Constant luminosity (toy model)
     * @param t time (unused)
     * @return 1.0 unit fuel per unit time
     *************************/
    return 1.0;
}

double L_exp_decay(double t) {
    /*************************
     * Exponentially decaying luminosity model (physically scaled)
     * @param t time in years
     * @return L_SUN * exp(-k * t), with k ≈ 1e-10 (slow decay)
     *************************/
    const double k = 1e-10; // per year decay rate
    return L_SUN * std::exp(-k * t);
}


double L_sinusoidal(double t) {
    /*************************
     * Sinusoidal luminosity variation (toy model)
     * @param t time
     * @return L0 * (1 + A sin(w t)), with L0=1.0, A=0.2, w=2.0
     *************************/
    double L0 = 1.0;  // average luminosity
    double A  = 0.2;  // amplitude of variation
    double w  = 2.0;  // frequency
    return L0 * (1.0 + A * std::sin(w * t));
}


/************************
 * Implementation: Star class
 ************************/

Star::Star(const std::string &name, double mass_Msun, double luminosity_Lsun, double observed_age_years) {
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
    if (mass_Msun < 0.0) {
        throw std::invalid_argument("Star::Star - mass_Msun must be non-negative");
    }
    if (luminosity_Lsun < 0.0) {
        throw std::invalid_argument("Star::Star - luminosity_Lsun must be non-negative");
    }
    if (observed_age_years < 0.0) {
        throw std::invalid_argument("Star::Star - observed_age_years must be non-negative");
    }

    this->name = name;
    this->mass_Msun = mass_Msun;
    this->luminosity_Lsun = luminosity_Lsun;
    this->observed_age_years = observed_age_years;
}

Star::~Star() {
    /*************************
    * Star class destructor
    * @param None
    * @exception None
    * @return None
    * @note
    **************************/
    // No dynamic memory to free
}

std::string Star::getName() const {
    /*********************
     * Get the name of the star
     * @param None
     * @exception None
     * @return Name of the star
     * @note
     **********************/
    return name;
}

double Star::getMass() const {
    /*************************
     * Get the mass of the star in solar masses
     * @param None
     * @exception None
     * @return Mass in solar masses
     * @note M☉ = 1.989e30 kg
     * **********************/
    return mass_Msun;
}

double Star::getLuminosity() const {
    /*************************
     * Get the luminosity of the star in solar luminosities
     * @param None
     * @exception None
     * @return Luminosity in solar luminosities
     * @note L☉ = 3.828e26 W
     **************************/
    return luminosity_Lsun;
}

double Star::getAge() const {
    /*************************
     * Get the age of the star in years
     * @param None
     * @exception None
     * @return Age in years
     **************************/
    return observed_age_years;
}

void Star::setName(const std::string& name) {
    /*************************
     * Set the name of the star
     * @param name Name of the star
     * @exception None
     * @return None
     * @note
     **************************/
    this->name = name;
}

void Star::setMass(double mass_Msun) {
    /*************************
     * Set the mass of the star in solar masses
     * @param mass_Msun Mass in solar masses
     * @exception std::invalid_argument if mass is negative
     * @return None
     * @note M☉ = 1.989e30 kg
     **************************/
    if (mass_Msun < 0.0) {
        throw std::invalid_argument("Star::setMass - mass_Msun must be non-negative");
    }
    this->mass_Msun = mass_Msun;
}

void Star::setLuminosity(double luminosity_Lsun) {
    /*************************
     * Set the luminosity of the star in solar luminosities
     * @param luminosity_Lsun Luminosity in solar luminosities
     * @exception std::invalid_argument if luminosity is negative
     * @return None
     * @note L☉ = 3.828e26 W
     **************************/
    if (luminosity_Lsun < 0.0) {
        throw std::invalid_argument("Star::setLuminosity - luminosity_Lsun must be non-negative");
    }
    this->luminosity_Lsun = luminosity_Lsun;
}

void Star::setAge(double observed_age_years) {
    /*************************
     * Set the age of the star in years
     * @param observed_age_years Age in years
     * @exception std::invalid_argument if age is negative
     * @return None
     * @note
     **************************/
    if (observed_age_years < 0.0) {
        throw std::invalid_argument("Star::setAge - observed_age_years must be non-negative");
    }
    this->observed_age_years = observed_age_years;
} 

double Star::computeFuelLifetime() const {
    /*************************
     * Compute analytic fuel lifetime using E/L with mass-dependent luminosity
     * @param None
     * @exception None
     * @return Lifetime in years
     * @note Reuses tested function lifetime(M_kg)
     **************************/
    double M_kg = massInKg();
    return lifetime(M_kg); // reuse your tested function
}

double Star::massInKg() const {
    /*************************
     * Convert mass from solar units to kg
     * @param None
     * @exception None
     * @return Mass in kg
     **************************/
    return mass_Msun * M_SUN;
}

double Star::luminosityInWatts() const {
    /*************************
     * Convert luminosity from solar units to Watts
     * @param None
     * @exception None
     * @return Luminosity in Watts
     **************************/
    return luminosity_Lsun * L_SUN;
}

void Star::printSummary() const {
    /*************************
     * Print a formatted summary of the star
     * @param None
     * @exception None
     * @return None
     **************************/
    std::cout << "----------------------------------------\n";
    std::cout << "Star: " << name << "\n";
    std::cout << "Mass: " << mass_Msun << " M☉ (" << this->massInKg() << " kg)\n";
    std::cout << "Luminosity: " << luminosity_Lsun << " L☉ (" << this->luminosityInWatts() << " W)\n";
    std::cout << "Observed Age: " << this->observed_age_years << " years\n";
    std::cout << "Fuel Lifetime Estimate: " << this->computeFuelLifetime() << " years\n";
    std::cout << "----------------------------------------\n";
} // end of printSummary

bool Star::isOlderThan(const Star& other) const {
    /*************************
     * Compare ages of two stars
     * @param other Another Star object
     * @exception None
     * @return true if this star is older
     * @note
     **************************/
    return observed_age_years > other.getAge();
}

bool Star::isBrighterThan(const Star& other) const {
    /*************************
     * Compare luminosities of two stars
     * @param other Another Star object
     * @exception None
     * @return true if this star is brighter
     * @note
     **************************/
    return luminosity_Lsun > other.getLuminosity();
}

bool Star::isMoreMassiveThan(const Star& other) const {
    /*************************
     * Compare masses of two stars
     * @param other Another Star object
     * @exception None  
     * @return true if this star is more massive
     * @note
     **************************/
    return mass_Msun > other.getMass();
}

void Star::evolve(double t_final, double dt) {
    /*************************
     * Evolve the star forward in time using a simple fuel depletion model
     * @param t_final Final time increment (years)
     * @param dt      Timestep (years)
     * @exception None
     * @return None
     * @note Uses constant luminosity equal to current luminosityInWatts().
     *       Fix: removed call to undefined luminosityAtTime(t).
     **************************/
    if (dt <= 0.0) {
        throw std::invalid_argument("Star::evolve - dt must be positive");
    }
    if (t_final < 0.0) {
        throw std::invalid_argument("Star::evolve - t_final must be non-negative");
    }

    double fuel = 1.0;
    double time = 0.0;

    // Use constant luminosity model for now; could be replaced with a function pointer for L(t).
    const double Lw = luminosityInWatts();

    while (time < t_final && fuel > 0.0) {
        fuel -= Lw * dt / Lw; // normalize fuel burn (dimensionless)
        time += dt;
    }
    observed_age_years += time;
}

} // namespace physics::stellar
