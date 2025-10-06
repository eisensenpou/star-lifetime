/************************
 *  Author : Sinan Demir
 *  Date   : 09/23/2025
 *  File   : main.cpp
 *  Purpose: Main file for the project
 ************************/

#include "main.h"
#include "stellar_mass.h"


int main() {
    double S0 = 10.0;
    double T_guess = 20.0;

    // -----------------------------
    // Part 1: Luminosity model tests
    // -----------------------------
    struct Model {
        const char* name;
        double (*L)(double);
    } models[] = {
        {"Constant",   L_const},
        {"ExpDecay",   L_exp_decay},
        {"Sinusoidal", L_sinusoidal}
    };

    for (auto& model : models) {
        std::vector<std::vector<std::string>> rows;

        for (int n : {10, 20, 40, 80, 160}) {
            double T_trap = estimate_lifetime(S0, model.L, T_guess, n, false);
            double T_simp = estimate_lifetime(S0, model.L, T_guess, n, true);

            rows.push_back({
                std::to_string(n),
                std::to_string(T_trap),
                std::to_string(T_simp)
            });
        }

        // Save CSV to results folder
        std::string filename = "../results/" + std::string(model.name) + "_results.csv";
        write_csv(filename,
                  {"n", "Trap Lifetime", "Simp Lifetime"},
                  rows);

        std::cout << "Saved results for " << model.name
                  << " to " << filename << "\n";
    }

    // -----------------------------
    // Part 2: Stellar mass–lifetime tests
    // -----------------------------
    std::cout << std::scientific << std::setprecision(3);

    std::vector<std::vector<std::string>> mass_rows;
    for (double M : {0.5, 1.0, 2.0, 5.0, 10.0}) {
        double T = lifetime(M * 1.989e30); // convert Msun → kg
        std::cout << "Mass = " << M << " M(sun)"
                  << " | Lifetime ~= " << T << " years\n";

        mass_rows.push_back({
            std::to_string(M),
            std::to_string(T)
        });
    }

    // Save CSV for stellar mass results
    std::string mass_filename = "../results/stellar_mass_results.csv";
    write_csv(mass_filename,
              {"Mass (Msun)", "Lifetime (years)"},
              mass_rows);

    std::cout << "Saved stellar mass lifetimes to " << mass_filename << "\n";

    return 0;
}  // end of main
