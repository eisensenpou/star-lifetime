#include <cmath>
#include <fstream>
#include <iostream>

// -----------------------------
// Physical Constants
// -----------------------------
const double L_sun = 3.828e26; // Solar luminosity (W)
const double M_sun = 1.989e30; // Solar mass (kg)
const double c = 299792458.0;  // Speed of light (m/s)
const double epsilon = 0.007;  // Fusion efficiency (H -> He)

// -----------------------------
// Mass-Luminosity Relation
// L = L_sun * (M/M_sun)^3.5
// -----------------------------
double luminosity(double M) {
  double ratio = M / M_sun;
  return L_sun * std::pow(ratio, 3.5);
}

// -----------------------------
// Lifetime Model
// T = (epsilon * M * c^2) / L(M)
// -----------------------------
double lifetime_seconds(double M) {
  double fuel = epsilon * M * c * c;
  double L = luminosity(M);
  return fuel / L; // seconds
}

// Convert seconds to years
double seconds_to_years(double t) { return t / (60.0 * 60.0 * 24.0 * 365.25); }

int main() {
  std::ofstream out("lifetime_data.csv");

  if (!out) {
    std::cerr << "Error: Could not open output file.\n";
    return 1;
  }

  out << "mass_solar,lifetime_years\n";

  // Sweep mass from 0.5 to 10 solar masses
  for (double mass = 0.5; mass <= 10.0; mass += 0.1) {
    double M = mass * M_sun;
    double T_sec = lifetime_seconds(M);
    double T_years = seconds_to_years(T_sec);

    out << mass << "," << T_years << "\n";
  }

  out.close();
  std::cout << "CSV generated: lifetime_data.csv\n";
  return 0;
}
