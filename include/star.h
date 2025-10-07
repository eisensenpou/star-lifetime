/************************
 * Author: Sinan Demir
 * Date  : 10/06/2025
 * File  : star.h
 * Purpose: Header file for star class
 ************************/
 

#ifndef STAR_H
#define STAR_H

#include <string>
#include <iostream>
#include "stellar_mass.h"
#include "stellar_models.h"


class Star {
    
    public:

    /******************************
    * Constructor / Destructor
    ******************************/
    Star(const std::string &name, double mass_Msun, double luminosity_Lsun, double observed_age_years);
    ~Star();

    /******************************
    * Getters / Accessors
    ******************************/
    std::string getName() const;
    double getMass() const;
    double getLuminosity() const;
    double getAge() const;
    double computeFuelLifetime() const;      // analytic estimate (τ ~ E / L)
    double luminosityInWatts() const;        // convert from L☉ to watts
    double massInKg() const;                 // convert from M☉ to kg
    /******************************
    * Setters / Mutators
    ******************************/
    void setName(const std::string& name);
    void setMass(double mass_Msun);
    void setLuminosity(double luminosity_Lsun);
    void setAge(double observed_age_years);

     /******************************
      * Printing
      ******************************/
    void printSummary() const;

    /******************************
    * Comparison methods
    ******************************/
    bool isOlderThan(const Star& other) const;
    bool isBrighterThan(const Star& other) const;
    bool isMoreMassiveThan(const Star& other) const;


private:
    /****************************
     * Attributes
     ***************************/
    std::string name;
    double mass_Msun;
    double luminosity_Lsun;
    double observed_age_years;

    /***************************
     * other methods
     ***************************/


    
};



#endif // STAR_H