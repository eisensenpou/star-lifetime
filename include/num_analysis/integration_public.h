/**
 * @file integration_public.h
 * @brief Public integration API (scientific endpoints only)
 *
 * This header exposes high-level integration operations backed by the
 * frozen numerical integration core. Numerical parameters such as step
 * size or subinterval count are not exposed.
 */

#pragma once

namespace num_analysis::public_api {

/**
 * @brief Integrate a scalar quantity over a closed interval.
 *
 * This function performs a numerically guaranteed integration using the
 * library's internal adaptive integrator. The numerical resolution is
 * chosen internally to satisfy a fixed accuracy contract.
 *
 * @param a Lower bound of integration
 * @param b Upper bound of integration
 *
 * @return Integral value
 *
 * @throws std::invalid_argument on invalid domain
 * @throws num_analysis::errors::NumericalError on numerical failure
 *
 * @note Numerical parameters (step size, method, refinement) are internal
 *       and not observable by API consumers.
 */
double integrate_scalar(double a, double b);

} // namespace num_analysis::public_api
