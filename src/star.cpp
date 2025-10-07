/************************
 * Author: Sinan Demir
 * Date  : 10/06/2025
 * File  : star.cpp
 * Purpose: implementation of star class
 ************************/

    
#include "star.h"

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
    this->observed_age_years = observed_age_years;
} 



void Star::printSummary() const {
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

double Star::computeFuelLifetime() const {
    double M_kg = massInKg();
    return lifetime(M_kg); // reuse your tested function
}