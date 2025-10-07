/************************
 * Author: Sinan Demir
 * Date  : 10/06/2025
 * File  : star.h
 * Purpose: Header file for star class
 ************************/
 

#ifndef STAR_H
#define STAR_H

#include <string>

#define M_SUN  (1.989e30) // kg
#define L_SUN  (3.828e26) // Watts
#define F (0.1) // fraction of mass that is hydrogen available for fusion
#define ETA (0.007) // efficiency of mass to energy conversion in fusion
#define C2 (9.0e16) // speed of light squared in m^2/s^2
#define SECONDS_PER_YEAR (3.154e7) // seconds in a year


class Star {
    
    public:

    /******************************
    * Constructor / Destructor
    ******************************/
    Star(const std::string &name, double mass_Msun, double luminosity_Lsun, double observed_age_years);
    ~Star() {}

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