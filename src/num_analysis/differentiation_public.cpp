/**
 * @file differentiation_public.cpp
 * @author Sinan Demir
 * @brief Implementation of PUBLIC API for numerical differentiation
 * @version 0.1
 * @date 2026-01-29
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "num_analysis/differentiation_public.h"

#include <stdexcept>

namespace num_analysis::public_api {

std::vector<double> derivative(const std::vector<double> &x,
                               const std::vector<double> &y,
                               const std::string &method) {
  // ----------------------------
  // Input validation
  // ----------------------------
  if (x.size() != y.size()) {
    throw std::invalid_argument("x and y must have the same length");
  }

  if (x.size() < 2) {
    throw std::invalid_argument("at least two points are required");
  }

  // Ensure monotonic x (simple check)
  for (size_t i = 1; i < x.size(); ++i) {
    if (x[i] <= x[i - 1]) {
      throw std::invalid_argument("x must be strictly increasing");
    }
  }

  // ----------------------------
  // Differentiation
  // ----------------------------
  std::vector<double> dydx(x.size());

  // ----------------------------
  // Forward difference
  // ----------------------------
  if (method == "forward") {
    for (size_t i = 0; i + 1 < x.size(); ++i) {
      dydx[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
    }
    // Defined boundary behavior
    dydx.back() = dydx[x.size() - 2];
  }

  // ----------------------------
  // Backward difference
  // ----------------------------
  else if (method == "backward") {
    dydx[0] = (y[1] - y[0]) / (x[1] - x[0]);
    for (size_t i = 1; i < x.size(); ++i) {
      dydx[i] = (y[i] - y[i - 1]) / (x[i] - x[i - 1]);
    }
  }

  // ----------------------------
  // Central difference (default)
  // ----------------------------
  else if (method == "central") {
    dydx[0] = (y[1] - y[0]) / (x[1] - x[0]);

    for (size_t i = 1; i + 1 < x.size(); ++i) {
      dydx[i] = (y[i + 1] - y[i - 1]) / (x[i + 1] - x[i - 1]);
    }

    dydx.back() = (y.back() - y[y.size() - 2]) / (x.back() - x[x.size() - 2]);
  }

  // ----------------------------
  // Unsupported method
  // ----------------------------
  else {
    throw std::invalid_argument("unsupported differentiation method");
  }

  return dydx;
}

} // namespace num_analysis::public_api
