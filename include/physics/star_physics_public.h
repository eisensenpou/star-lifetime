

#pragma once

#include <stdexcept>

namespace physics::public_api {

/**
 * @brief Available nuclear fuel of a star.
 *
 * @param mass_Msun Stellar mass in solar masses.
 * @return Available nuclear fuel in joules.
 *
 * @throws std::invalid_argument if mass is not physically valid.
 */
double fuel_stock(double mass_Msun);

/**
 * @brief Stellar luminosity.
 *
 * @param mass_Msun Stellar mass in solar masses.
 * @return Luminosity in watts.
 *
 * @throws std::invalid_argument if mass is not physically valid.
 */
double luminosity(double mass_Msun);

/**
 * @brief Main-sequence stellar lifetime.
 *
 * @param mass_Msun Stellar mass in solar masses.
 * @return Lifetime in years.
 *
 * @throws std::invalid_argument if mass is not physically valid.
 * @throws std::runtime_error on numerical failure.
 */
double lifetime(double mass_Msun);

} // namespace physics::public_api
