/**
 * @file differentiation_public.h
 * @author Sinan Demir
 * @brief Declaration of PUBLIC API for numerical differentiation
 * @version 0.1
 * @date 2026-01-29
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <string>
#include <vector>

namespace num_analysis::public_api {

/**
 * @brief Compute numerical derivative dy/dx from sampled data.
 *
 * This is the PUBLIC, binding-safe API.
 * It is data-driven and does not accept callbacks.
 *
 * @param x Sample points (must be strictly monotonic)
 * @param y Function values at sample points
 * @param method Differentiation scheme:
 *        - "forward"
 *        - "backward"
 *        - "central" (default)
 *
 * @return Vector of derivative values (same size as input)
 *
 * @throws std::invalid_argument on invalid input
 * @throws std::runtime_error on numerical failure
 */
std::vector<double> derivative(const std::vector<double> &x,
                               const std::vector<double> &y,
                               const std::string &method = "central");

} // namespace num_analysis::public_api
