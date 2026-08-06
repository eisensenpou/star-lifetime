

#include "physics/star_physics_public.h"

#include <stdexcept>

// internal implementation (unchanged)
#include "physics/detail/star_physics.h"

namespace physics::public_api {

double fuel_stock(double mass_Msun) {
  if (mass_Msun <= 0.0)
    throw std::invalid_argument(
        "stellar mass must be positive and expressed in solar masses");

  return physics::stellar::fuel_stock(mass_Msun * physics::constants::M_SUN);
}

double luminosity(double mass_Msun) {
  if (mass_Msun <= 0.0)
    throw std::invalid_argument(
        "stellar mass must be positive and expressed in solar masses");

  return physics::stellar::luminosity(mass_Msun * physics::constants::M_SUN);
}

double lifetime(double mass_Msun) {
  if (mass_Msun <= 0.0)
    throw std::invalid_argument(
        "stellar mass must be positive and expressed in solar masses");

  return physics::stellar::lifetime(mass_Msun * physics::constants::M_SUN);
}

} // namespace physics::public_api
