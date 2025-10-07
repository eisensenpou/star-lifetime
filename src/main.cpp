/************************
 * File   : main.cpp
 * Author : Sinan Demir
 * Date   : 10/06/2025
 * Purpose: Main program to test the Star class and stellar lifetime model.
 ************************/

#include "main.h"

int main() {
    std::cout << std::scientific << std::setprecision(3);
    std::cout << "=== Stellar Lifetime Simulation ===\n";

    // -------------------------------
    // Create sample Star objects
    // -------------------------------
    Star sun("Sun", 1.0, 1.0, 4.6e9);
    Star sirius("Sirius A", 2.1, 25.0, 2.4e8);
    Star proxima("Proxima Centauri", 0.12, 0.0017, 4.85e9);
    Star betelgeuse("Betelgeuse", 20.0, 126000.0, 1.0e7);

    // Store in a vector
    std::vector<Star> stars = {sun, sirius, proxima, betelgeuse};

    // -------------------------------
    // Print each star summary
    // -------------------------------
    for (const auto& s : stars) {
        s.printSummary();
    }

    // -------------------------------
    // Compare stars (example)
    // -------------------------------
    std::cout << "\n=== Comparative Analysis ===\n";
    if (sirius.isMoreMassiveThan(sun)) {
        std::cout << sirius.getName() << " is more massive than " << sun.getName() << ".\n";
    }
    if (sun.isOlderThan(sirius)) {
        std::cout << sun.getName() << " is older than " << sirius.getName() << ".\n";
    }
    if (betelgeuse.isBrighterThan(sun)) {
        std::cout << betelgeuse.getName() << " is much brighter than " << sun.getName() << ".\n";
    }

    // -------------------------------
    // Save results to CSV
    // -------------------------------
    std::vector<std::vector<std::string>> rows;
    for (const auto& s : stars) {
        double lifetime_pred = s.computeFuelLifetime();
        double fuel_frac = 1.0 - (s.getAge() / lifetime_pred);

        rows.push_back({
            s.getName(),
            std::to_string(s.getMass()),
            std::to_string(s.getLuminosity()),
            std::to_string(s.getAge()),
            std::to_string(lifetime_pred),
            std::to_string(fuel_frac)
        });
    }

    write_csv("../results/star_lifetime_summary.csv",
              {"Name", "Mass(Msun)", "Luminosity(Lsun)", "Observed Age (yrs)",
               "Predicted Lifetime (yrs)", "Fuel Fraction Remaining"},
              rows);

    std::cout << "\nResults saved to ../results/star_lifetime_summary.csv\n";
    std::cout << "Simulation complete.\n";

    return 0;
}
