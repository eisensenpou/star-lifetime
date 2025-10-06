/************************
 *  Author : Sinan Demir
 *  Date   : 09/23/2025
 *  File   : main.cpp
 *  Purpose: testing file for stellar_mass
 ************************/

#include "main.h"
#include <iostream>
#include <fstream>


struct Star {
    std::string name;
    double mass_Msun;
    double luminosity_Lsun;
    double observed_age_years;
};

int main() {
    std::ifstream file("../../data/star_data.csv");
    if (!file.is_open()) {
        std::cerr << "Error: could not open input file\n";
        return 1;
    }

    std::string line;
    std::getline(file, line); // skip header

    std::vector<Star> stars;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Star star;
        std::string massStr, lumStr, ageStr;

        std::getline(ss, star.name, ',');
        std::getline(ss, massStr, ',');
        std::getline(ss, lumStr, ',');
        std::getline(ss, ageStr, ',');

        star.mass_Msun = std::stod(massStr);
        star.luminosity_Lsun = std::stod(lumStr);
        star.observed_age_years = std::stod(ageStr);

        stars.push_back(star);
    }

    file.close();

    std::vector<std::vector<std::string>> rows;
    for (auto& star : stars) {
        // Mass in kg
        double M_kg = star.mass_Msun * 1.989e30;
        double T_pred = lifetime(M_kg);

        double abs_err = std::abs(T_pred - star.observed_age_years);
        double rel_err = abs_err / star.observed_age_years;

        rows.push_back({
            star.name,
            std::to_string(star.mass_Msun),
            std::to_string(star.luminosity_Lsun),
            std::to_string(star.observed_age_years),
            std::to_string(T_pred),
            std::to_string(abs_err),
            std::to_string(rel_err)
        });
    }

    write_csv("../results/star_results.csv",
              {"Name","Mass(Msun)","Luminosity(Lsun)","Observed Age (yrs)",
               "Predicted Lifetime (yrs)","Abs Error","Rel Error"},
              rows);

    std::cout << "Saved results to ../results/star_results.csv\n";
    return 0;
}
